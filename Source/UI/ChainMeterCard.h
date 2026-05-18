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

    // Gain value. 1.0 = 0dB unity. Range allows boost up to +12dB.
    float getGainValue() const { return gainValue; }
    void setGainValue(float newGain);

    // Auto-gain (LUFS matching). The AUTO toggle now lives at the top of the
    // output meter card itself; the cyan correction-dB readout still appears
    // below the meters when auto is on.
    void setAutoGainEnabled(bool enabled);
    bool isAutoGainEnabled() const { return autoGainEnabled; }
    void setAutoGainCorrectionDb(float correctionDb);
    void setAutoGainAnalyzing(bool analyzing);

    // Output meters (those sitting right of a plugin slot) own an AUTO toggle
    // and visually attach to the slot on their left. The leftmost input meter
    // is purely a level display.
    void setAutoGainSupported(bool supported) { autoGainSupported = supported; repaint(); }
    void setAttachedLeft(bool attached) { attachedLeft = attached; repaint(); }
    void setGainEditable(bool editable) { gainEditable = editable; repaint(); }

    // The slot+meter module's selected/bypassed state is shared so both halves
    // tint the same way. The slot owns these states; the chain view pushes
    // them to the meter whenever they change.
    void setSelected(bool isSelected);
    bool isSelected() const { return selected; }
    void setBypassed(bool bypass);
    bool isBypassed() const { return bypassed; }

    // Callback when gain changes
    std::function<void(int meterIndex, float newGain)> onGainChanged;

    // Callback when the AUTO button is clicked. The meter passes its own index;
    // the chain view translates that to the controlled slot (meterIndex - 1).
    std::function<void(int meterIndex, bool enabled)> onAutoGainToggled;

    // Fired when the user clicks anywhere on the meter outside the AUTO/X
    // buttons or gain slider. The chain view treats this as "select the slot
    // to my left" since slot + meter form one logical module.
    std::function<void(int meterIndex)> onSelectRequest;

    // X (remove) button click - removes the entire module (the slot + this
    // meter). The chain view routes this to its remove-slot handler.
    std::function<void(int meterIndex)> onRemoveRequest;

    // Card dimensions
    static constexpr int cardWidth = 48;
    static constexpr int cardHeight = 128;
    static constexpr int autoToolbarHeight = 24;  // Matches slot card toolbar

private:
    void timerCallback() override;
    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;
    void mouseMove(const juce::MouseEvent& e) override;

    // Map a mouse Y coordinate (in local space) to a gain value and apply it.
    void applyFaderPosition(float mouseY);

    int meterIdx;
    float leftLevel = 0.0f;
    float rightLevel = 0.0f;
    float leftPeak = 0.0f;
    float rightPeak = 0.0f;
    float gainValue = 1.0f;  // 1.0 = 0dB

    bool autoGainEnabled = false;
    bool autoGainSupported = false;
    bool autoGainAnalyzing = false;
    bool autoFlashOn = false;
    bool attachedLeft = false;
    bool gainEditable = true;
    bool selected = false;
    bool bypassed = false;
    float autoGainCorrectionDb = 0.0f;

    bool isDraggingSlider = false;
    bool fineDragMode = false;       // True while Shift is held during a drag
    float dragAnchorY = 0.0f;        // Mouse Y at last (re-)anchor point
    float dragAnchorDb = 0.0f;       // Gain in dB at last (re-)anchor point
    juce::Rectangle<int> sliderBounds;        // The fader thumb (hover/draw)
    juce::Rectangle<int> faderTrackBounds;    // The fader track (full drag area)
    juce::Rectangle<int> autoButtonBounds;
    juce::Rectangle<int> removeButtonBounds;

    // Gain range: -inf dB to +12 dB, expressed in linear units. The slider
    // works in dB space so motion is perceptually even across the range.
    static constexpr float kGainMaxLinear = 3.981071705534972f;  // +12 dB
    static constexpr float kGainMinDb = -60.0f;
    static constexpr float kGainMaxDb =  12.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChainMeterCard)
};

} // namespace PALauncher
