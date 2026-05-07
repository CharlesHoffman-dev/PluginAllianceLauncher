/*
  ==============================================================================
    ChainMeterCard.h
    Plugin Alliance Launcher - L/R Peak Meter with Gain Slider
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class ChainMeterCard : public juce::Component,
                       private juce::Timer
{
public:
    ChainMeterCard(int meterIndex);
    ~ChainMeterCard() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Update peak levels (0.0 to 1.0, where 1.0 = 0dB)
    void setLevels(float leftPeak, float rightPeak);

    // Get/Set gain value (0.0 to 2.0, where 1.0 = 0dB)
    float getGainValue() const { return gainValue; }
    void setGainValue(float newGain);

    // Auto-gain (LUFS matching) display state. The toggle button itself moved
    // to ChainSlotCard; this card only renders the cyan correction-dB readout
    // and the cyan border + label colour to indicate "auto-gain active".
    void setAutoGainEnabled(bool enabled);
    bool isAutoGainEnabled() const { return autoGainEnabled; }
    void setAutoGainCorrectionDb(float correctionDb);

    // Callback when gain changes
    std::function<void(int meterIndex, float newGain)> onGainChanged;

    // Card dimensions
    static constexpr int cardWidth = 60;
    static constexpr int cardHeight = 128;

private:
    void timerCallback() override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;
    void mouseMove(const juce::MouseEvent& e) override;

    int meterIdx;
    float leftLevel = 0.0f;
    float rightLevel = 0.0f;
    float leftPeak = 0.0f;
    float rightPeak = 0.0f;
    float gainValue = 1.0f;  // 1.0 = 0dB

    bool autoGainEnabled = false;
    float autoGainCorrectionDb = 0.0f;

    bool isDraggingSlider = false;
    float dragStartY = 0.0f;
    float dragStartGain = 1.0f;
    juce::Rectangle<int> sliderBounds;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChainMeterCard)
};

} // namespace PALauncher
