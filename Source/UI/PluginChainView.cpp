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

            // When the button is "highlighted" (toggle state on), draw a solid cyan
            // border instead of the dashed grey one - this signals that the next
            // Load click will land in this + slot.
            const bool highlighted = button.getToggleState();

            float cornerRadius = 6.0f;
            float strokeWidth = 2.0f;
            float dashLength = 6.0f;
            float gapLength = 4.0f;

            if (highlighted)
            {
                // Solid cyan border, matches the selected chain-slot border.
                g.setColour(juce::Colour(0xff0cbff2));
                g.drawRoundedRectangle(bounds, cornerRadius, 2.0f);
            }
            else
            {
                // Default dashed grey border drawn below.
                g.setColour(juce::Colour(0xffc0c0c0));
            }

            // Create the rounded rectangle path
            juce::Path borderPath;
            borderPath.addRoundedRectangle(bounds, cornerRadius);

            // Calculate approximate perimeter
            float width = bounds.getWidth();
            float height = bounds.getHeight();
            float perimeter = 2.0f * (width + height) - 8.0f * cornerRadius + 2.0f * juce::MathConstants<float>::pi * cornerRadius;

            // Draw dashes along the perimeter (skipped when highlighted - cyan
            // border is drawn solid above instead). dashUnit is rescaled so
            // numDashes * dashUnit == perimeter exactly; otherwise the leftover
            // slack from integer truncation leaves a visible gap at the top-left
            // corner where the perimeter loops back to its start.
            float dashUnit = dashLength + gapLength;
            int numDashes = highlighted ? 0
                : juce::jmax(1, static_cast<int>(std::round(perimeter / dashUnit)));
            if (numDashes > 0)
                dashUnit = perimeter / static_cast<float>(numDashes);

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
        // Layout: InputMeter [gap] Slot [no gap] OutputMeter [gap] Slot ...
        // Drop position is the X of the next slot's left edge.
        int cardSpacing = 4;
        int startX = 12;

        float dropX = startX + ChainMeterCard::cardWidth + cardSpacing;

        // Each preceding slot consumes slot + output-meter + spacing.
        for (int i = 0; i < dropTargetIndex; ++i)
        {
            dropX += ChainSlotCard::cardWidth;
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
        g.drawText("Add plugins from the browser to build a chain",
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

    // Layout: input meter [gap] slot [no gap, attached] output meter [gap] slot ...
    int cardSpacing = 4;
    int x = contentBounds.getX();
    int y = contentBounds.getY();

    // Hide all meters initially
    for (auto* meter : meterCards)
        meter->setVisible(false);

    // Input meter (no AUTO, no gain, no attachment)
    if (meterCards.size() > 0)
    {
        auto* meter = meterCards[0];
        meter->setAutoGainSupported(false);
        meter->setAttachedLeft(false);
        meter->setGainEditable(false);
        meter->setVisible(true);
        meter->setBounds(x, y, ChainMeterCard::cardWidth, ChainMeterCard::cardHeight);
        x += ChainMeterCard::cardWidth + cardSpacing;
    }

    // Each slot is immediately followed (no gap) by its output meter, which is
    // visually attached to the slot's right side.
    for (int i = 0; i < slotCards.size(); ++i)
    {
        auto* slotCard = slotCards[i];
        slotCard->setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
        x += ChainSlotCard::cardWidth;  // No gap before the attached meter

        int meterIdx = i + 1;
        if (meterIdx < meterCards.size())
        {
            auto* meter = meterCards[meterIdx];
            meter->setAutoGainSupported(true);
            meter->setAttachedLeft(true);
            meter->setGainEditable(true);
            meter->setVisible(true);
            meter->setBounds(x, y, ChainMeterCard::cardWidth, ChainMeterCard::cardHeight);
            x += ChainMeterCard::cardWidth + cardSpacing;
        }
    }

    addButton.setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
}

void PluginChainView::setChainState(PluginAllianceLauncherProcessor& proc)
{
    processor = &proc;
    currentSelectedSlot = proc.getCurrentSelectedSlot();

    // Clear existing cards
    slotCards.clear();
    meterCards.clear();

    // Create meter cards. For 8 slots we need 9 meters arranged as:
    //   M0 - S0 - M1 - S1 - M2 - ... - M8
    // where M_{i+1} is the output meter for slot S_i. M0 is the chain input
    // meter (no AUTO, no gain).
    for (int i = 0; i <= kMaxChainSlots; ++i)
    {
        auto* meter = new ChainMeterCard(i);
        meter->onGainChanged = [this](int idx, float gain) { handleMeterGainChanged(idx, gain); };
        meter->onAutoGainToggled = [this](int meterIndex, bool enabled)
        {
            // AUTO on meter[i+1] controls slot[i].
            int slotIndex = meterIndex - 1;
            if (slotIndex >= 0 && slotIndex < kMaxChainSlots && onAutoGainToggled)
                onAutoGainToggled(slotIndex, enabled);
        };
        meter->onSelectRequest = [this](int meterIndex)
        {
            // Clicks on the meter select the slot to its left - slot + meter
            // are treated as one logical module.
            int slotIndex = meterIndex - 1;
            if (slotIndex >= 0 && slotIndex < kMaxChainSlots)
                handleSlotSelected(slotIndex);
        };
        meter->onRemoveRequest = [this](int meterIndex)
        {
            // The X button on the meter removes the whole module (the slot
            // immediately to its left and this meter together).
            int slotIndex = meterIndex - 1;
            if (slotIndex >= 0 && slotIndex < kMaxChainSlots)
                handleRemoveSlot(slotIndex);
        };

        if (i > 0 && i - 1 < kMaxChainSlots)
        {
            int slotIdx = i - 1;
            meter->setAutoGainEnabled(proc.isSlotAutoGainEnabled(slotIdx));
            meter->setAutoGainCorrectionDb(proc.getSlotCorrectionDb(slotIdx));
            meter->setGainValue(proc.getSlotActiveGain(slotIdx));
            meter->setSelected(slotIdx == currentSelectedSlot);
            meter->setBypassed(proc.isSlotBypassed(slotIdx));
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
        card->onViewPlugin = [this](int idx) { if (onSlotViewPlugin) onSlotViewPlugin(idx); };
        card->onRemove = [this](int idx) { handleRemoveSlot(idx); };
        card->onToggleBypass = [this](int idx, bool bypass) { handleToggleBypass(idx, bypass); };
        card->onToggleAB = [this](int idx, ABSlot ab) { handleToggleAB(idx, ab); };
        card->onAutoGainToggled = [this](int idx, bool enabled)
        {
            if (onAutoGainToggled)
                onAutoGainToggled(idx, enabled);
        };
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

    // Slot + its right-hand output meter form one module; both halves get the
    // cyan border when this slot is selected.
    for (auto* card : slotCards)
        card->setSelected(card->getSlotIndex() == slotIndex);

    for (int i = 0; i < meterCards.size(); ++i)
    {
        // meter[i+1] is the output meter for slot[i].
        int ownedSlot = i - 1;
        meterCards[i]->setSelected(ownedSlot == slotIndex);
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

    // Update the slot card's bypass state and mirror it on the right-hand
    // meter so both halves of the module tint together.
    for (auto* card : slotCards)
    {
        if (card->getSlotIndex() == slotIndex)
        {
            card->setBypassed(bypass);
            break;
        }
    }

    int meterIndex = slotIndex + 1;
    if (meterIndex >= 0 && meterIndex < meterCards.size())
        meterCards[meterIndex]->setBypassed(bypass);
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

    // The output meter shows whichever host is active, so flip its displayed
    // gain to the now-active host's stored value.
    int meterIndex = slotIndex + 1;
    if (meterIndex >= 0 && meterIndex < meterCards.size())
        meterCards[meterIndex]->setGainValue(processor->getSlotActiveGain(slotIndex));

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
    auto localPos = getLocalPoint(nullptr, screenPos);

    // Layout: InputMeter [4] Slot [0] OutputMeter [4] Slot [0] OutputMeter ...
    int cardSpacing = 4;
    int startX = 12;

    int firstMeterWidth = ChainMeterCard::cardWidth + cardSpacing;
    int x = localPos.getX() - startX - firstMeterWidth;

    if (x < 0)
        return 0;  // Before first slot

    // Each slot + attached output meter consumes:
    //   Slot(120) + Meter(48) + spacing(4) = 172
    int slotMeterPairWidth = ChainSlotCard::cardWidth + ChainMeterCard::cardWidth + cardSpacing;

    int pairIndex = x / slotMeterPairWidth;
    int posInPair = x % slotMeterPairWidth;

    // If the pointer is past the slot's centre line, drop after this pair.
    int index = pairIndex;
    if (posInPair > ChainSlotCard::cardWidth / 2)
        index = pairIndex + 1;

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
    // Push the change straight into the processor so the audio thread picks it
    // up on the next block. Editor still gets notified for things like undo.
    if (processor != nullptr && meterIndex >= 1)
    {
        int slotIndex = meterIndex - 1;
        if (slotIndex < kMaxChainSlots)
            processor->setSlotActiveGain(slotIndex, newGain);
    }

    if (onMeterGainChanged)
        onMeterGainChanged(meterIndex, newGain);
}

void PluginChainView::updateAutoGainState(int slotIndex, bool enabled, bool analyzing, float correctionDb)
{
    // AUTO toggle (+ analyzing flash) now lives on the slot card so all four
    // header buttons sit at evenly-spaced positions. The cyan correction-dB
    // readout still belongs to the output meter where the auto-gain math is
    // visualised.
    for (auto* card : slotCards)
    {
        if (card->getSlotIndex() == slotIndex)
        {
            card->setAutoGainEnabled(enabled);
            card->setAutoGainAnalyzing(enabled && analyzing);
            break;
        }
    }

    int meterIndex = slotIndex + 1;
    if (meterIndex >= 0 && meterIndex < meterCards.size())
    {
        meterCards[meterIndex]->setAutoGainEnabled(enabled);
        meterCards[meterIndex]->setAutoGainCorrectionDb(correctionDb);
    }
}

} // namespace PALauncher
