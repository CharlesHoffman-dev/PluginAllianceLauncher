/*
  ==============================================================================
    LUFSAnalyzer.h
    Plugin Alliance Launcher - LUFS Loudness Measurement (ITU-R BS.1770)
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

// Biquad filter for K-weighting (ITU-R BS.1770-4)
struct BiquadFilter
{
    double b0 = 1.0, b1 = 0.0, b2 = 0.0;
    double a1 = 0.0, a2 = 0.0;
    double z1 = 0.0, z2 = 0.0;

    void reset()
    {
        z1 = z2 = 0.0;
    }

    float process(float input)
    {
        double in = static_cast<double>(input);
        double out = b0 * in + b1 * z1 + b2 * z2 - a1 * z1 - a2 * z2;

        // Direct Form II Transposed
        out = b0 * in + z1;
        z1 = b1 * in - a1 * out + z2;
        z2 = b2 * in - a2 * out;

        return static_cast<float>(out);
    }
};

// Per-channel K-weighting filter chain: high-shelf + high-pass
struct KWeightingFilter
{
    BiquadFilter highShelf;  // Stage 1: +4dB shelf at ~1.5kHz
    BiquadFilter highPass;   // Stage 2: high-pass at ~38Hz

    void prepare(double sampleRate)
    {
        // Stage 1: High shelf filter (pre-filter)
        // Coefficients from ITU-R BS.1770-4 for 48kHz, recalculated for other rates
        // Using bilinear transform of the analog prototype
        double f0 = 1681.974450955533;
        double G = 3.999843853973347;   // dB
        double Q = 0.7071752369554196;

        double K = std::tan(juce::MathConstants<double>::pi * f0 / sampleRate);
        double Vh = std::pow(10.0, G / 20.0);
        double Vb = std::pow(Vh, 0.4996667741545416);

        double a0h = 1.0 + K / Q + K * K;
        highShelf.b0 = (Vh + Vb * K / Q + K * K) / a0h;
        highShelf.b1 = 2.0 * (K * K - Vh) / a0h;
        highShelf.b2 = (Vh - Vb * K / Q + K * K) / a0h;
        highShelf.a1 = 2.0 * (K * K - 1.0) / a0h;
        highShelf.a2 = (1.0 - K / Q + K * K) / a0h;

        // Stage 2: High-pass filter (RLB weighting)
        double f1 = 38.13547087602444;
        double Q1 = 0.5003270373238773;

        double K1 = std::tan(juce::MathConstants<double>::pi * f1 / sampleRate);
        double a0hp = 1.0 + K1 / Q1 + K1 * K1;
        highPass.b0 = 1.0 / a0hp;
        highPass.b1 = -2.0 / a0hp;
        highPass.b2 = 1.0 / a0hp;
        highPass.a1 = 2.0 * (K1 * K1 - 1.0) / a0hp;
        highPass.a2 = (1.0 - K1 / Q1 + K1 * K1) / a0hp;
    }

    void reset()
    {
        highShelf.reset();
        highPass.reset();
    }

    float process(float input)
    {
        return highPass.process(highShelf.process(input));
    }
};

// LUFS analyzer with separate input/output measurement for auto-gain
class LUFSAnalyzer
{
public:
    LUFSAnalyzer() = default;

    void prepare(double sampleRate, int blockSize)
    {
        currentSampleRate = sampleRate;

        // Prepare K-weighting filters (2 channels x 2 measurement points)
        for (int ch = 0; ch < 2; ++ch)
        {
            inputFilters[ch].prepare(sampleRate);
            outputFilters[ch].prepare(sampleRate);
        }

        // Ring buffer for short-term measurement (~3 seconds)
        // We accumulate mean-square energy per block, store in ring buffer
        int blocksFor3Seconds = static_cast<int>(std::ceil(3.0 * sampleRate / blockSize));
        inputEnergyBuffer.resize(blocksFor3Seconds, 0.0);
        outputEnergyBuffer.resize(blocksFor3Seconds, 0.0);
        bufferSize = blocksFor3Seconds;
        writeIndex = 0;
        samplesInBlock = 0;
        currentBlockInputEnergy = 0.0;
        currentBlockOutputEnergy = 0.0;
        blockSampleCount = blockSize;

        reset();
    }

    void reset()
    {
        for (int ch = 0; ch < 2; ++ch)
        {
            inputFilters[ch].reset();
            outputFilters[ch].reset();
        }

        std::fill(inputEnergyBuffer.begin(), inputEnergyBuffer.end(), 0.0);
        std::fill(outputEnergyBuffer.begin(), outputEnergyBuffer.end(), 0.0);
        writeIndex = 0;
        samplesInBlock = 0;
        currentBlockInputEnergy = 0.0;
        currentBlockOutputEnergy = 0.0;
        inputLUFS = -100.0f;
        outputLUFS = -100.0f;
        blocksWritten = 0;
    }

    // Call BEFORE the plugin processes the buffer
    void measureInput(const juce::AudioBuffer<float>& buffer)
    {
        int numSamples = buffer.getNumSamples();
        int numChannels = juce::jmin(buffer.getNumChannels(), 2);

        for (int s = 0; s < numSamples; ++s)
        {
            double energy = 0.0;
            for (int ch = 0; ch < numChannels; ++ch)
            {
                float filtered = inputFilters[ch].process(buffer.getSample(ch, s));
                energy += static_cast<double>(filtered) * static_cast<double>(filtered);
            }
            currentBlockInputEnergy += energy;
            samplesInBlock++;

            if (samplesInBlock >= blockSampleCount)
                flushBlock();
        }
    }

    // Call AFTER the plugin processes the buffer
    void measureOutput(const juce::AudioBuffer<float>& buffer)
    {
        int numSamples = buffer.getNumSamples();
        int numChannels = juce::jmin(buffer.getNumChannels(), 2);

        for (int s = 0; s < numSamples; ++s)
        {
            double energy = 0.0;
            for (int ch = 0; ch < numChannels; ++ch)
            {
                float filtered = outputFilters[ch].process(buffer.getSample(ch, s));
                energy += static_cast<double>(filtered) * static_cast<double>(filtered);
            }
            currentBlockOutputEnergy += energy;
        }
    }

    // Get current short-term LUFS values
    float getInputLUFS() const { return inputLUFS; }
    float getOutputLUFS() const { return outputLUFS; }

    // Get the auto-gain correction in dB (input - output)
    float getCorrectionDb() const
    {
        // Gate: if either measurement is very quiet, return 0 correction
        if (inputLUFS < gateThreshold || outputLUFS < gateThreshold)
            return 0.0f;

        float correction = inputLUFS - outputLUFS;

        // Clamp correction range to avoid runaway
        return juce::jlimit(-maxCorrectionDb, maxCorrectionDb, correction);
    }

private:
    void flushBlock()
    {
        // Average the energy over the block
        double avgInputEnergy = currentBlockInputEnergy / static_cast<double>(samplesInBlock);
        double avgOutputEnergy = currentBlockOutputEnergy / static_cast<double>(samplesInBlock);

        // Store in ring buffer
        inputEnergyBuffer[writeIndex] = avgInputEnergy;
        outputEnergyBuffer[writeIndex] = avgOutputEnergy;
        writeIndex = (writeIndex + 1) % bufferSize;
        if (blocksWritten < bufferSize)
            blocksWritten++;

        // Recalculate short-term LUFS from ring buffer
        double inputSum = 0.0;
        double outputSum = 0.0;
        int count = blocksWritten;

        for (int i = 0; i < count; ++i)
        {
            inputSum += inputEnergyBuffer[i];
            outputSum += outputEnergyBuffer[i];
        }

        double meanInputEnergy = inputSum / static_cast<double>(count);
        double meanOutputEnergy = outputSum / static_cast<double>(count);

        // LUFS = -0.691 + 10 * log10(mean_square)
        if (meanInputEnergy > 1e-10)
            inputLUFS = static_cast<float>(-0.691 + 10.0 * std::log10(meanInputEnergy));
        else
            inputLUFS = -100.0f;

        if (meanOutputEnergy > 1e-10)
            outputLUFS = static_cast<float>(-0.691 + 10.0 * std::log10(meanOutputEnergy));
        else
            outputLUFS = -100.0f;

        // Reset block accumulator
        currentBlockInputEnergy = 0.0;
        currentBlockOutputEnergy = 0.0;
        samplesInBlock = 0;
    }

    double currentSampleRate = 48000.0;

    // K-weighting filters: [channel][input/output]
    KWeightingFilter inputFilters[2];
    KWeightingFilter outputFilters[2];

    // Ring buffer for short-term energy (~3 seconds of blocks)
    std::vector<double> inputEnergyBuffer;
    std::vector<double> outputEnergyBuffer;
    int bufferSize = 0;
    int writeIndex = 0;
    int blocksWritten = 0;

    // Block accumulation
    int blockSampleCount = 512;
    int samplesInBlock = 0;
    double currentBlockInputEnergy = 0.0;
    double currentBlockOutputEnergy = 0.0;

    // Current LUFS values
    float inputLUFS = -100.0f;
    float outputLUFS = -100.0f;

    // Thresholds
    static constexpr float gateThreshold = -70.0f;   // Below this LUFS, hold gain steady
    static constexpr float maxCorrectionDb = 12.0f;   // Max +/- correction
};

} // namespace PALauncher
