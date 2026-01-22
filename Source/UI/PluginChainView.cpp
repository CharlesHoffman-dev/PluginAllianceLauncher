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
    // Set up add button
    addButton.setButtonText("+");
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
        // Draw vertical cyan line at drop position
        float dropX = 20.0f + dropTargetIndex * (ChainSlotCard::cardWidth + 8);

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
    auto bounds = getLocalBounds().reduced(12, 10);  // Reduced padding for compact view

    // Layout cards horizontally with spacing
    int cardSpacing = 8;
    int x = bounds.getX();
    int y = bounds.getY();

    for (auto* card : slotCards)
    {
        card->setBounds(x, y, ChainSlotCard::cardWidth, ChainSlotCard::cardHeight);
        x += ChainSlotCard::cardWidth + cardSpacing;
    }

    // Position add button
    if (slotCards.isEmpty())
    {
        // Center the add button if no cards
        addButton.setBounds(bounds.getCentreX() - 30, bounds.getCentreY() - 30, 60, 60);
    }
    else
    {
        // Position add button after last card
        addButton.setBounds(x, y + (ChainSlotCard::cardHeight - 40) / 2, 40, 40);
    }
}

void PluginChainView::setChainState(PluginAllianceLauncherProcessor& proc)
{
    processor = &proc;
    currentSelectedSlot = proc.getCurrentSelectedSlot();

    // Clear existing cards
    slotCards.clear();

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
        card->onDragStart = [this](int idx, juce::Point<int> pos) { handleDragStart(idx, pos); };
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
}

void PluginChainView::handleDragStart(int slotIndex, juce::Point<int> dragPos)
{
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

    // Calculate which slot position this corresponds to
    int cardSpacing = 8;
    int totalCardWidth = ChainSlotCard::cardWidth + cardSpacing;

    int index = (localPos.getX() - 20 + totalCardWidth / 2) / totalCardWidth;

    // Clamp to valid range
    index = juce::jlimit(0, slotCards.size(), index);

    return index;
}

} // namespace PALauncher
