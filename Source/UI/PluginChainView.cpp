/*
  ==============================================================================
    PluginChainView.cpp
    Plugin Alliance Launcher - Horizontal Plugin Chain View Implementation
  ==============================================================================
*/

#include "PluginChainView.h"

namespace PALauncher
{

PluginChainView::PluginChainView()
{
    // Ensure child components receive mouse events
    setInterceptsMouseClicks(false, true);

    // Set up add button with custom styling
    class AddButtonLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                                  const juce::Colour& /*backgroundColour*/,
                                  bool isMouseOverButton, bool isButtonDown) override
        {
            auto bounds = button.getLocalBounds().toFloat().reduced(2.0f);

            // Draw card background
            g.setColour(juce::Colours::white);
            g.fillRoundedRectangle(bounds, 6.0f);

            // Draw dashed border following the rounded rectangle outline
            g.setColour(juce::Colour(0xffc0c0c0));

            float cornerRadius = 6.0f;
            float strokeWidth = 2.0f;
            float dashLength = 6.0f;
            float gapLength = 4.0f;

            // Create the rounded rectangle path
            juce::Path borderPath;
            borderPath.addRoundedRectangle(bounds, cornerRadius);

            // Calculate approximate perimeter
            float width = bounds.getWidth();
            float height = bounds.getHeight();
            float perimeter = 2.0f * (width + height) - 8.0f * cornerRadius + 2.0f * juce::MathConstants<float>::pi * cornerRadius;

            // Draw dashes along the perimeter
            float dashUnit = dashLength + gapLength;
            int numDashes = static_cast<int>(perimeter / dashUnit);

            for (int i = 0; i < numDashes; ++i)
            {
                float startDist = i * dashUnit;
                float endDist = startDist + dashLength;

                // Create a small path segment for this dash
                juce::Path dashSegment;

                // Approximate position along the rounded rectangle perimeter
                auto getPointOnPerimeter = [&](float distance) -> juce::Point<float>
                {
                    float x = bounds.getX();
                    float y = bounds.getY();
                    float w = bounds.getWidth();
                    float h = bounds.getHeight();
                    float r = cornerRadius;
                    float arcLength = juce::MathConstants<float>::pi * r / 2.0f;

                    // Normalize distance to perimeter
                    while (distance > perimeter)
                        distance -= perimeter;

                    // Top-left corner arc (starting point)
                    if (distance < arcLength)
                    {
                        float angle = juce::MathConstants<float>::pi + (distance / arcLength) * juce::MathConstants<float>::pi / 2.0f;
                        return juce::Point<float>(x + r + r * std::cos(angle), y + r + r * std::sin(angle));
                    }
                    distance -= arcLength;

                    // Top edge
                    float topLength = w - 2 * r;
                    if (distance < topLength)
                        return juce::Point<float>(x + r + distance, y);
                    distance -= topLength;

                    // Top-right corner arc
                    if (distance < arcLength)
                    {
                        float angle = -juce::MathConstants<float>::pi / 2.0f + (distance / arcLength) * juce::MathConstants<float>::pi / 2.0f;
                        return juce::Point<float>(x + w - r + r * std::cos(angle), y + r + r * std::sin(angle));
                    }
                    distance -= arcLength;

                    // Right edge
                    float rightLength = h - 2 * r;
                    if (distance < rightLength)
                        return juce::Point<float>(x + w, y + r + distance);
                    distance -= rightLength;

                    // Bottom-right corner arc
                    if (distance < arcLength)
                    {
                        float angle = (distance / arcLength) * juce::MathConstants<float>::pi / 2.0f;
                        return juce::Point<float>(x + w - r + r * std::cos(angle), y + h - r + r * std::sin(angle));
                    }
                    distance -= arcLength;

                    // Bottom edge
                    if (distance < topLength)
                        return juce::Point<float>(x + w - r - distance, y + h);
                    distance -= topLength;

                    // Bottom-left corner arc
                    if (distance < arcLength)
                    {
                        float angle = juce::MathConstants<float>::pi / 2.0f + (distance / arcLength) * juce::MathConstants<float>::pi / 2.0f;
                        return juce::Point<float>(x + r + r * std::cos(angle), y + h - r + r * std::sin(angle));
                    }
                    distance -= arcLength;

                    // Left edge
                    return juce::Point<float>(x, y + h - r - distance);
                };

                auto startPoint = getPointOnPerimeter(startDist);
                auto endPoint = getPointOnPerimeter(juce::jmin(endDist, perimeter));

                juce::Line<float> dash(startPoint, endPoint);
                g.drawLine(dash, strokeWidth);
            }

            // Draw centered circle
            float circleDiameter = 50.0f;
            auto centerX = bounds.getCentreX();
            auto centerY = bounds.getCentreY();
            auto circleX = centerX - circleDiameter / 2.0f;
            auto circleY = centerY - circleDiameter / 2.0f;

            auto circleColour = juce::Colour(0xff0cbff2);
            if (isButtonDown)
                circleColour = circleColour.darker(0.2f);
            else if (isMouseOverButton)
                circleColour = circleColour.brighter(0.1f);

            g.setColour(circleColour);
            g.fillEllipse(circleX, circleY, circleDiameter, circleDiameter);
        }

        void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                            bool /*isMouseOverButton*/, bool /*isButtonDown*/) override
        {
            // Draw + text centered in the circle, adjusted up slightly
            auto font = juce::Font(32.0f, juce::Font::bold);
            g.setFont(font);
            g.setColour(juce::Colours::white);

            auto bounds = button.getLocalBounds();
            // Move up by 2 pixels for better visual centering
            auto textBounds = bounds.withY(bounds.getY() - 2);
            g.drawText(button.getButtonText(), textBounds, juce::Justification::centred, false);
        }
    };

    static AddButtonLookAndFeel addButtonLookAndFeel;

    addButton.setButtonText("+");
    addButton.setLookAndFeel(&addButtonLookAndFeel);
    addButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    addButton.onClick = [this]()
    {
        if (onAddSlot)
            onAddSlot();
    };
    addAndMakeVisible(addButton);

    setSize(minWidth, viewHeight);
}

void PluginChainView::paint(juce::Graphics& g)
{
    // Background - light gray
    g.fillAll(juce::Colour(0xfff5f5f5));

    // Top and bottom borders
    g.setColour(juce::Colour(0xffe0e0e0));
    g.drawHorizontalLine(0, 0.0f, static_cast<float>(getWidth()));
    g.drawHorizontalLine(getHeight() - 1, 0.0f, static_cast<float>(getWidth()));

    // If dragging, draw drop zone indicator
    if (draggedSlotIndex >= 0 && dropTargetIndex >= 0)
    {
        // Draw vertical cyan line at drop position, accounting for meters
        // Layout: Meter(60) - Slot(140) - Meter(60) - Slot(140) - ...
        int cardSpacing = 4;
        int startX = 12;

        // Start after first meter
        float dropX = startX + ChainMeterCard::cardWidth + cardSpacing;

        // Add each previous slot + meter pair
        for (int i = 0; i < dropTargetIndex; ++i)
        {
            dropX += ChainSlotCard::cardWidth + cardSpacing;
            dropX += ChainMeterCard::cardWidth + cardSpacing;
        }

        g.setColour(juce::Colour(0xff0cbff2));
        g.fillRect(dropX - 2.0f, 20.0f, 4.0f, static_cast<float>(getHeight() - 40));
    }

    // If empty, show help text
    if (slotCards.isEmpty())
    {
        g.setColour(juce::Colour(0xff999999));
        g.setFont(juce::Font(16.0f));
        auto textBounds = getLocalBounds().reduced(20);
        g.drawText("Add plugins from browser to build your chain",
                   textBounds,
                   juce::Justification::centred);
    }
}

void PluginChainView::resized()
{
    auto bounds = getLocalBounds();

    // Calculate vertical centering for cards
    int totalHeight = bounds.getHeight();
    int cardHeight = ChainSlotCard::cardHeight;
    int topPadding = (totalHeight - cardHeight) / 2;

    auto contentBounds = bounds.reduced(12, 0);
    contentBounds.removeFromTop(topPadding);

    // Layout cards horizontally with spacing: Meter - Slot - Meter - Slot - ...
    int cardSpacing = 4;  // Spacing between cards
    int x = contentBounds.getX();
    int y = contentBounds.getY();

    // Hide all meters initially
    for (auto* meter : meterCards)
        meter->setVisible(false);

    // Always show at least the first meter (before any slots)
    if (meterCards.size() > 0)
    {
        auto* meter = meterCards[0];
        meter->setVisible(true);
        meter->setBounds(x, y, ChainMeterCard::cardWidth, ChainMeterCard::cardHeight);
        x += ChainMeterCard::cardWidth + cardSpacing;
    }

    // Alternate between slot cards and meter cards
    for (int i = 0; i < slotCards.size(); ++i)
    {
        // Place slot card
        auto* slotCard = slotCards[i];
        slotCard->setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
        x += ChainSlotCard::cardWidth + cardSpacing;

        // Place meter card after this slot (if it exists)
        int meterIdx = i + 1;
        if (meterIdx < meterCards.size())
        {
            auto* meter = meterCards[meterIdx];
            meter->setVisible(true);
            meter->setBounds(x, y, ChainMeterCard::cardWidth, ChainMeterCard::cardHeight);
            x += ChainMeterCard::cardWidth + cardSpacing;
        }
    }

    // Position add button in a card-sized area
    if (slotCards.isEmpty())
    {
        // Center the add button card if no cards (but after first meter)
        addButton.setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
    }
    else
    {
        // Position add button card after last meter
        addButton.setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
    }
}

void PluginChainView::setChainState(PluginAllianceLauncherProcessor& proc)
{
    processor = &proc;
    currentSelectedSlot = proc.getCurrentSelectedSlot();

    // Clear existing cards
    slotCards.clear();
    meterCards.clear();

    // Create meter cards (one before each slot, plus one at the end)
    // For 8 slots, we need 9 meters: M0-S0-M1-S1-M2-S2-M3-S3-M4-S4-M5-S5-M6-S6-M7-S7-M8
    for (int i = 0; i <= kMaxChainSlots; ++i)
    {
        auto* meter = new ChainMeterCard(i);
        meter->onGainChanged = [this](int idx, float gain) { handleMeterGainChanged(idx, gain); };
        meter->onAutoGainToggled = [this](int idx, bool enabled) { handleAutoGainToggled(idx, enabled); };
        // Sync auto-gain state: meter i+1 corresponds to slot i
        if (i > 0 && i - 1 < kMaxChainSlots)
        {
            int slotIdx = i - 1;
            meter->setAutoGainEnabled(proc.isSlotAutoGainEnabled(slotIdx));
            meter->setAutoGainCorrectionDb(proc.getSlotCorrectionDb(slotIdx));
        }

        addAndMakeVisible(meter);
        meterCards.add(meter);
    }

    // Create cards for all loaded slots
    for (int i = 0; i < kMaxChainSlots; ++i)
    {
        const auto& slot = proc.getChainSlot(i);

        if (!slot.hasPlugin())
            continue;  // Skip empty slots

        auto* card = new ChainSlotCard(i);

        // Set up callbacks
        card->onSelected = [this](int idx) { handleSlotSelected(idx); };
        card->onRemove = [this](int idx) { handleRemoveSlot(idx); };
        card->onToggleBypass = [this](int idx, bool bypass) { handleToggleBypass(idx, bypass); };
        card->onToggleAB = [this](int idx, ABSlot ab) { handleToggleAB(idx, ab); };
        card->onDragStart = [this](int idx, juce::Point<int> pos) {
            DBG("PluginChainView: onDragStart called for slot " << idx);
            handleDragStart(idx, pos);
        };
        card->onDragMove = [this](int idx, juce::Point<int> pos) { handleDragMove(idx, pos); };
        card->onDragEnd = [this](int idx) { handleDragEnd(idx); };

        // Update card data
        bool isSelected = (i == currentSelectedSlot);
        card->setSlotData(slot, i, isSelected);

        addAndMakeVisible(card);
        slotCards.add(card);
    }

    // Hide add button if chain is full
    bool chainFull = (slotCards.size() >= kMaxChainSlots);
    addButton.setVisible(!chainFull);

    resized();
    repaint();
}

void PluginChainView::updateSlotABButton(int slotIndex, ABSlot newSlot)
{
    // Find the card for this slot and update its A/B state
    for (auto* card : slotCards)
    {
        if (card->getSlotIndex() == slotIndex)
        {
            card->setABSlot(newSlot);
            break;
        }
    }
}

void PluginChainView::handleSlotSelected(int slotIndex)
{
    if (processor == nullptr)
        return;

    currentSelectedSlot = slotIndex;

    // Update card selection states
    for (auto* card : slotCards)
    {
        card->setSelected(card->getSlotIndex() == slotIndex);
    }

    if (onSlotSelected)
        onSlotSelected(slotIndex);
}

void PluginChainView::handleRemoveSlot(int slotIndex)
{
    if (onRemoveSlot)
        onRemoveSlot(slotIndex);
}

void PluginChainView::handleToggleBypass(int slotIndex, bool bypass)
{
    if (processor == nullptr)
        return;

    processor->bypassSlot(slotIndex, bypass);

    // Update the card's bypass state
    for (auto* card : slotCards)
    {
        if (card->getSlotIndex() == slotIndex)
        {
            card->setBypassed(bypass);
            break;
        }
    }
}

void PluginChainView::handleToggleAB(int slotIndex, ABSlot newSlot)
{
    if (processor == nullptr)
        return;

    processor->setSlotActiveAB(slotIndex, newSlot);

    // Update the card's A/B state
    for (auto* card : slotCards)
    {
        if (card->getSlotIndex() == slotIndex)
        {
            card->setABSlot(newSlot);
            break;
        }
    }

    // Notify parent (editor) so it can sync main A/B switch
    if (onToggleAB)
        onToggleAB(slotIndex, newSlot);
}

void PluginChainView::handleDragStart(int slotIndex, juce::Point<int> dragPos)
{
    DBG("handleDragStart: slot " << slotIndex << " at " << dragPos.toString());
    draggedSlotIndex = slotIndex;
    currentDragPosition = dragPos;
    repaint();
}

void PluginChainView::handleDragMove(int slotIndex, juce::Point<int> dragPos)
{
    currentDragPosition = dragPos;

    // Calculate drop target index
    int newDropTarget = calculateDropIndex(dragPos);

    if (newDropTarget != dropTargetIndex)
    {
        dropTargetIndex = newDropTarget;
        repaint();
    }
}

void PluginChainView::handleDragEnd(int slotIndex)
{
    if (dropTargetIndex >= 0 && dropTargetIndex != slotIndex && onSlotReorder)
    {
        // Perform reorder
        onSlotReorder(slotIndex, dropTargetIndex);
    }

    // Reset drag state
    draggedSlotIndex = -1;
    dropTargetIndex = -1;
    repaint();
}

int PluginChainView::calculateDropIndex(juce::Point<int> screenPos)
{
    // Convert screen position to local position
    auto localPos = getLocalPoint(nullptr, screenPos);

    // Calculate which slot position this corresponds to, accounting for meters
    // Layout: Meter(60) - Slot(140) - Meter(60) - Slot(140) - ...
    // Spacing between each card is 4px

    int cardSpacing = 4;
    int startX = 12;  // contentBounds left padding

    // Start position accounts for first meter
    int firstMeterWidth = ChainMeterCard::cardWidth + cardSpacing;
    int x = localPos.getX() - startX - firstMeterWidth;

    if (x < 0)
        return 0;  // Before first slot

    // Each slot + meter pair is: Slot(140) + spacing(4) + Meter(60) + spacing(4) = 208
    int slotMeterPairWidth = ChainSlotCard::cardWidth + cardSpacing + ChainMeterCard::cardWidth + cardSpacing;

    // Find which pair we're in
    int pairIndex = x / slotMeterPairWidth;
    int posInPair = x % slotMeterPairWidth;

    // If we're in the first half of the pair (on the slot), insert before next
    // If we're in the second half (on the meter), insert after current
    int index = pairIndex;
    if (posInPair > (ChainSlotCard::cardWidth + cardSpacing) / 2)
        index = pairIndex + 1;

    // Clamp to valid range
    index = juce::jlimit(0, slotCards.size(), index);

    return index;
}

void PluginChainView::updateMeterLevels(int meterIndex, float leftPeak, float rightPeak)
{
    if (meterIndex >= 0 && meterIndex < meterCards.size())
    {
        meterCards[meterIndex]->setLevels(leftPeak, rightPeak);
    }
}

void PluginChainView::handleMeterGainChanged(int meterIndex, float newGain)
{
    if (onMeterGainChanged)
        onMeterGainChanged(meterIndex, newGain);
}

void PluginChainView::handleAutoGainToggled(int meterIndex, bool enabled)
{
    if (onAutoGainToggled)
        onAutoGainToggled(meterIndex, enabled);
}

void PluginChainView::updateAutoGainState(int meterIndex, bool enabled, float correctionDb)
{
    if (meterIndex >= 0 && meterIndex < meterCards.size())
    {
        meterCards[meterIndex]->setAutoGainEnabled(enabled);
        meterCards[meterIndex]->setAutoGainCorrectionDb(correctionDb);
    }
}

} // namespace PALauncher
