/*
  ==============================================================================
    ChainMeterCard.cpp
    Plugin Alliance Launcher - L/R Peak Meter with Gain Slider Implementation
  ==============================================================================
*/

#include "ChainMeterCard.h"

namespace PALauncher
{

ChainMeterCard::ChainMeterCard(int meterIndex)
    : meterIdx(meterIndex)
{
    setSize(cardWidth, cardHeight);
    startTimerHz(30);  // 30 FPS refresh for smooth meter decay
}

void ChainMeterCard::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background - white card
    g.setColour(juce::Colours::white);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    g.setColour(juce::Colour(0xffe0e0e0));
    g.drawRoundedRectangle(bounds, 6.0f, 1.0f);

    auto contentBounds = getLocalBounds();

    // Add padding above meter
    contentBounds.removeFromTop(12);

    // Side padding - minimal/none for cleaner look
    contentBounds = contentBounds.reduced(0, 0);

    // Meter area (L/R side by side) - sized for balanced padding
    auto meterArea = contentBounds.removeFromTop(84);

    int meterWidth = 16;  // Increased from 12 to reduce side padding
    int meterGap = 4;
    int totalMeterWidth = meterWidth * 2 + meterGap;
    int meterX = meterArea.getCentreX() - totalMeterWidth / 2;

    auto leftMeterBounds = juce::Rectangle<int>(meterX, meterArea.getY(), meterWidth, meterArea.getHeight());
    auto rightMeterBounds = leftMeterBounds.translated(meterWidth + meterGap, 0);

    // Draw meter backgrounds
    g.setColour(juce::Colour(0xffeeeeee));
    g.fillRoundedRectangle(leftMeterBounds.toFloat(), 2.0f);
    g.fillRoundedRectangle(rightMeterBounds.toFloat(), 2.0f);

    // Draw meter levels
    auto drawMeter = [&](juce::Rectangle<int> meterBounds, float level)
    {
        if (level > 0.0f)
        {
            int fillHeight = static_cast<int>(level * meterBounds.getHeight());
            auto fillBounds = meterBounds.removeFromBottom(fillHeight).toFloat();

            // Color gradient: green -> yellow -> red
            juce::Colour meterColour;
            if (level < 0.7f)
                meterColour = juce::Colour(0xff00cc00);  // Green
            else if (level < 0.9f)
                meterColour = juce::Colour(0xffffaa00);  // Yellow
            else
                meterColour = juce::Colour(0xffcc0000);  // Red

            g.setColour(meterColour);
            g.fillRoundedRectangle(fillBounds, 2.0f);
        }
    };

    drawMeter(leftMeterBounds, leftLevel);
    drawMeter(rightMeterBounds, rightLevel);

    // Gain value text below meters (interactive area)
    contentBounds.removeFromTop(6);  // Increased spacing above dB text
    sliderBounds = contentBounds.removeFromTop(16);  // The dB text is the slider now

    float gainDb = 20.0f * std::log10(juce::jmax(0.001f, gainValue));
    juce::String gainText = juce::String(gainDb, 1) + " dB";

    // Highlight text on hover
    if (sliderBounds.contains(getMouseXYRelative()))
        g.setColour(juce::Colour(0xff0cbff2));
    else
        g.setColour(juce::Colour(0xff666666));

    g.setFont(juce::Font(10.0f, juce::Font::bold));
    g.drawText(gainText, sliderBounds, juce::Justification::centred);
}

void ChainMeterCard::resized()
{
    // Bounds calculated in paint()
}

void ChainMeterCard::setLevels(float newLeftPeak, float newRightPeak)
{
    // Update peak values
    leftLevel = juce::jmax(leftLevel, newLeftPeak);
    rightLevel = juce::jmax(rightLevel, newRightPeak);

    leftPeak = newLeftPeak;
    rightPeak = newRightPeak;

    repaint();
}

void ChainMeterCard::setGainValue(float newGain)
{
    gainValue = juce::jlimit(0.0f, 1.0f, newGain);
    repaint();
}

void ChainMeterCard::timerCallback()
{
    // Decay meter levels smoothly
    float decayRate = 0.95f;
    leftLevel *= decayRate;
    rightLevel *= decayRate;

    if (leftLevel < 0.001f) leftLevel = 0.0f;
    if (rightLevel < 0.001f) rightLevel = 0.0f;

    repaint();
}

void ChainMeterCard::mouseDown(const juce::MouseEvent& e)
{
    if (sliderBounds.contains(e.getPosition()))
    {
        isDraggingSlider = true;
        dragStartY = e.position.getY();
        dragStartGain = gainValue;
    }
}

void ChainMeterCard::mouseDrag(const juce::MouseEvent& e)
{
    if (isDraggingSlider)
    {
        // Vertical drag: up increases gain, down decreases gain
        // Sensitivity: 100 pixels = full range (0.0 to 1.0)
        float dragDelta = dragStartY - e.position.getY();
        float gainDelta = dragDelta / 100.0f;

        gainValue = juce::jlimit(0.0f, 1.0f, dragStartGain + gainDelta);

        if (onGainChanged)
            onGainChanged(meterIdx, gainValue);

        repaint();
    }
}

void ChainMeterCard::mouseUp(const juce::MouseEvent&)
{
    isDraggingSlider = false;
}

void ChainMeterCard::mouseMove(const juce::MouseEvent&)
{
    repaint();  // Repaint to update hover highlighting
}

} // namespace PALauncher
