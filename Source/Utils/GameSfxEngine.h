/*
  ==============================================================================
    GameSfxEngine.h
    Tiny synth that renders short arcade-style SFX cues for the easter-egg game.
    Triggered from the UI thread, rendered from the audio thread, sums into the
    plugin's output buffer.
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <atomic>

namespace PALauncher
{

class GameSfxEngine
{
public:
    enum class Sound { Shoot, Hit, Powerup, BossHit, BossKill, ShieldBlock, LifeLost, GameOver };

    GameSfxEngine() = default;

    void prepare (double sr)
    {
        sampleRate = sr > 0.0 ? sr : 44100.0;
        for (auto& v : voices) v.active = false;
        pendingRead.store (0, std::memory_order_relaxed);
        pendingWrite.store (0, std::memory_order_relaxed);
    }

    // Safe to call from the message thread. Drops the trigger if the queue is
    // full (32 pending hits = something is very wrong upstream).
    void trigger (Sound s)
    {
        const int w    = pendingWrite.load (std::memory_order_relaxed);
        const int next = (w + 1) % kPendingCap;
        if (next == pendingRead.load (std::memory_order_acquire))
            return;
        pending[w] = s;
        pendingWrite.store (next, std::memory_order_release);
    }

    // Audio-thread render. Drains pending triggers into voice slots, then sums
    // every active voice's sample into the buffer.
    void renderInto (juce::AudioBuffer<float>& buffer)
    {
        // Drain pending triggers
        int r = pendingRead.load (std::memory_order_relaxed);
        const int w = pendingWrite.load (std::memory_order_acquire);
        while (r != w)
        {
            allocVoice (pending[r]);
            r = (r + 1) % kPendingCap;
        }
        pendingRead.store (r, std::memory_order_release);

        const int numSamples  = buffer.getNumSamples();
        const int numChannels = buffer.getNumChannels();
        if (numSamples <= 0 || numChannels <= 0)
            return;

        bool anyActive = false;
        for (auto& v : voices) if (v.active) { anyActive = true; break; }
        if (! anyActive)
            return;

        float* const* writePtrs = buffer.getArrayOfWritePointers();
        if (writePtrs == nullptr)
            return;

        for (int n = 0; n < numSamples; ++n)
        {
            float mix = 0.0f;
            for (auto& v : voices)
            {
                if (! v.active) continue;
                mix += renderVoiceSample (v);
                if (--v.samplesLeft <= 0 || v.amp < 0.0005f)
                    v.active = false;
            }
            mix = juce::jlimit (-1.0f, 1.0f, mix * 0.35f);
            for (int c = 0; c < numChannels; ++c)
                if (writePtrs[c] != nullptr)
                    writePtrs[c][n] += mix;
        }
    }

private:
    static constexpr int kPendingCap = 32;
    static constexpr int kMaxVoices  = 12;

    struct Voice
    {
        bool   active = false;
        int    type = 0;             // 0 sine, 1 square, 2 triangle, 3 noise
        double phase = 0.0;
        double freq  = 440.0;
        double freqSlide = 0.0;      // freq added per sample
        float  amp = 0.0f;
        float  ampDecay = 1.0f;
        int    samplesLeft = 0;
        juce::Random noiseRng;
    };

    Voice  voices[kMaxVoices];
    Sound  pending[kPendingCap];
    std::atomic<int> pendingRead  { 0 };
    std::atomic<int> pendingWrite { 0 };
    double sampleRate = 44100.0;

    void allocVoice (Sound s)
    {
        for (auto& v : voices)
            if (! v.active) { configureVoice (v, s); return; }
        configureVoice (voices[0], s);   // steal oldest
    }

    void configureVoice (Voice& v, Sound s)
    {
        v.active   = true;
        v.phase    = 0.0;
        v.noiseRng.setSeed ((juce::int64) (juce::Time::getMillisecondCounter()
                                            ^ static_cast<juce::uint32> (s)));

        switch (s)
        {
            case Sound::Shoot:
                v.type = 2; v.freq = 1200.0; v.freqSlide = -8.0;
                v.amp = 0.55f; v.ampDecay = 0.9985f;
                v.samplesLeft = (int) (0.08 * sampleRate); break;

            case Sound::Hit:
                v.type = 3; v.freq = 0.0;
                v.amp = 0.65f; v.ampDecay = 0.995f;
                v.samplesLeft = (int) (0.10 * sampleRate); break;

            case Sound::Powerup:
                v.type = 0; v.freq = 600.0; v.freqSlide = 2.0;
                v.amp = 0.55f; v.ampDecay = 0.9992f;
                v.samplesLeft = (int) (0.30 * sampleRate); break;

            case Sound::BossHit:
                v.type = 1; v.freq = 220.0; v.freqSlide = -0.4;
                v.amp = 0.55f; v.ampDecay = 0.997f;
                v.samplesLeft = (int) (0.07 * sampleRate); break;

            case Sound::BossKill:
                v.type = 3; v.freq = 0.0;
                v.amp = 0.85f; v.ampDecay = 0.998f;
                v.samplesLeft = (int) (0.50 * sampleRate); break;

            case Sound::ShieldBlock:
                v.type = 0; v.freq = 900.0; v.freqSlide = -1.0;
                v.amp = 0.40f; v.ampDecay = 0.999f;
                v.samplesLeft = (int) (0.20 * sampleRate); break;

            case Sound::LifeLost:
                v.type = 2; v.freq = 400.0; v.freqSlide = -2.5;
                v.amp = 0.65f; v.ampDecay = 0.998f;
                v.samplesLeft = (int) (0.30 * sampleRate); break;

            case Sound::GameOver:
                v.type = 1; v.freq = 220.0; v.freqSlide = -0.3;
                v.amp = 0.70f; v.ampDecay = 0.9995f;
                v.samplesLeft = (int) (0.80 * sampleRate); break;
        }
    }

    float renderVoiceSample (Voice& v)
    {
        v.freq = juce::jmax (20.0, v.freq + v.freqSlide);
        const double inc = juce::MathConstants<double>::twoPi * v.freq / sampleRate;
        v.phase += inc;
        if (v.phase > juce::MathConstants<double>::twoPi)
            v.phase -= juce::MathConstants<double>::twoPi;

        float out = 0.0f;
        switch (v.type)
        {
            case 0: out = (float) std::sin (v.phase); break;
            case 1: out = std::sin (v.phase) > 0.0 ? 1.0f : -1.0f; break;
            case 2: // triangle via asin(sin)
                out = (float) ((2.0 / juce::MathConstants<double>::pi)
                               * std::asin (std::sin (v.phase)));
                break;
            case 3: out = v.noiseRng.nextFloat() * 2.0f - 1.0f; break;
        }
        out *= v.amp;
        v.amp *= v.ampDecay;
        return out;
    }
};

} // namespace PALauncher
