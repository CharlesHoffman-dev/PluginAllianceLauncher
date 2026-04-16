/*
  ==============================================================================
    ChainSlotCard.cpp
    Plugin Alliance Launcher - Individual Chain Slot Display Card Implementation
  ==============================================================================
*/

#include "ChainSlotCard.h"
#include "../Utils/PluginImageCache.h"

namespace PALauncher
{

ChainSlotCard::ChainSlotCard(int slotIndex)
    : slotIdx(slotIndex)
{
    setWantsKeyboardFocus(false);
    setMouseClickGrabsKeyboardFocus(false);
    setInterceptsMouseClicks(true, false);  // Ensure this component receives mouse clicks
    setSize(cardWidth, cardHeight);
}

void ChainSlotCard::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background - white, with different tints for states
    juce::Colour bgColor = juce::Colours::white;

    if (bypassed)
    {
        // Grayed out when bypassed
        bgColor = juce::Colour(0xfff0f0f0);
    }
    else if (selected)
    {
        bgColor = juce::Colour(0xffe8f4fc);  // Light blue when selected
    }
    else if (hovered)
    {
        bgColor = juce::Colour(0xfffafafa);  // Slightly off-white on hover
    }

    // Drop shadow
    g.setColour(juce::Colour(0x15000000));
    g.fillRoundedRectangle(bounds.translated(1.0f, 2.0f), 6.0f);

    g.setColour(bgColor);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    if (selected)
    {
        // Cyan border when selected
        g.setColour(juce::Colour(0xff0cbff2));
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }
    else
    {
        // Subtle border
        g.setColour(juce::Colour(0xffe0e0e0));
        g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
    }

    // Content area - minimal padding
    auto contentBounds = getLocalBounds().reduced(3);

    // Top toolbar with charcoal background - rounded on top only
    auto toolbarBounds = contentBounds.removeFromTop(24);
    g.setColour(juce::Colour(0xff2a2a2a));  // Charcoal like main toolbar

    // Create path with rounded top corners only
    juce::Path toolbarPath;
    auto tbBounds = toolbarBounds.toFloat();
    toolbarPath.addRoundedRectangle(tbBounds.getX(), tbBounds.getY(),
                                     tbBounds.getWidth(), tbBounds.getHeight(),
                                     3.0f, 3.0f,
                                     true, true, false, false);
    g.fillPath(toolbarPath);

    // Buttons in toolbar
    auto buttonRow = toolbarBounds.reduced(2);
    int buttonSize = 17;
    int abButtonWidth = 30;  // Wider for A/B segmented control

    // Bypass button (top-left) - Power icon
    bypassButtonBounds = buttonRow.removeFromLeft(buttonSize).reduced(1);
    g.setColour(bypassed ? juce::Colour(0xff0cbff2) : juce::Colours::white);
    g.fillRoundedRectangle(bypassButtonBounds.toFloat(), 2.5f);

    // Draw power icon
    auto iconBounds = bypassButtonBounds.toFloat().reduced(3.5f);
    float cx = iconBounds.getCentreX();
    float cy = iconBounds.getCentreY();
    float radius = iconBounds.getWidth() / 2.5f;

    g.setColour(bypassed ? juce::Colours::white : juce::Colours::black);
    juce::Path powerIcon;
    powerIcon.addCentredArc(cx, cy, radius, radius, 0.0f, -2.2f, 2.2f, true);
    g.strokePath(powerIcon, juce::PathStrokeType(1.2f));
    g.drawLine(cx, cy - radius, cx, cy - radius * 0.3f, 1.2f);

    // Remove button (top-right)
    removeButtonBounds = buttonRow.removeFromRight(buttonSize).reduced(1);
    g.setColour(juce::Colour(0xffcc0000));
    g.fillRoundedRectangle(removeButtonBounds.toFloat(), 2.5f);
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(10.0f, juce::Font::bold));
    g.drawText("X", removeButtonBounds, juce::Justification::centred);

    // A/B button - centered in toolbar
    int abX = buttonRow.getCentreX() - (abButtonWidth / 2);
    abButtonBounds = juce::Rectangle<int>(abX, buttonRow.getY(), abButtonWidth, buttonRow.getHeight()).reduced(1);
    auto abBounds = abButtonBounds.toFloat();
    float halfWidth = abBounds.getWidth() / 2.0f;
    float cornerSize = 2.5f;

    auto leftBounds = abBounds.withWidth(halfWidth);
    auto rightBounds = abBounds.withLeft(abBounds.getX() + halfWidth);

    auto activeColour = juce::Colour(0xff0cbff2);   // Cyan
    auto inactiveColour = juce::Colour(0xff3a3a3a); // Dark

    // Draw left side (A) - rounded on left, flat on right
    juce::Path leftPath;
    leftPath.addRoundedRectangle(leftBounds.getX(), leftBounds.getY(),
                                  leftBounds.getWidth(), leftBounds.getHeight(),
                                  cornerSize, cornerSize,
                                  true, false, true, false);
    g.setColour(abSlot == ABSlot::B ? inactiveColour : activeColour);
    g.fillPath(leftPath);

    // Draw right side (B) - flat on left, rounded on right
    juce::Path rightPath;
    rightPath.addRoundedRectangle(rightBounds.getX(), rightBounds.getY(),
                                   rightBounds.getWidth(), rightBounds.getHeight(),
                                   cornerSize, cornerSize,
                                   false, true, false, true);
    g.setColour(abSlot == ABSlot::B ? activeColour : inactiveColour);
    g.fillPath(rightPath);

    // Draw A/B text
    auto font = juce::Font(8.0f, juce::Font::bold);
    g.setFont(font);
    g.setColour(abSlot == ABSlot::B ? juce::Colours::grey : juce::Colours::white);
    g.drawText("A", leftBounds.toNearestInt(), juce::Justification::centred);
    g.setColour(abSlot == ABSlot::B ? juce::Colours::white : juce::Colours::grey);
    g.drawText("B", rightBounds.toNearestInt(), juce::Justification::centred);

    // Plugin image - square with padding on all sides
    int availableWidth = contentBounds.getWidth();
    int sidePadding = 8;
    int topBottomPadding = 8;  // Add top/bottom padding like left/right
    int squareSize = availableWidth - (sidePadding * 2);

    auto imageBounds = contentBounds.removeFromTop(squareSize).reduced(sidePadding, topBottomPadding);
    imageBoundsCache = imageBounds;

    if (pluginImage.isValid())
    {
        if (bypassed)
        {
            // Draw image with transparency when bypassed
            g.setOpacity(0.3f);
        }

        g.drawImageWithin(pluginImage,
                          imageBounds.getX(), imageBounds.getY(),
                          imageBounds.getWidth(), imageBounds.getHeight(),
                          juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize);

        g.setOpacity(1.0f);
    }
    else
    {
        // Placeholder
        g.setColour(juce::Colour(0xffeeeeee));
        g.fillRoundedRectangle(imageBounds.toFloat(), 4.0f);
    }

    // Bypassed overlay text
    if (bypassed)
    {
        auto overlayBounds = imageBounds;
        g.setColour(juce::Colour(0x99000000));
        g.fillRoundedRectangle(overlayBounds.toFloat(), 3.5f);

        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(10.0f, juce::Font::bold));
        g.drawText("BYPASSED", overlayBounds, juce::Justification::centred);
    }
}

void ChainSlotCard::resized()
{
    // Button bounds are calculated in paint()
}

void ChainSlotCard::mouseEnter(const juce::MouseEvent&)
{
    hovered = true;
    repaint();
}

void ChainSlotCard::mouseExit(const juce::MouseEvent&)
{
    hovered = false;
    repaint();
}

void ChainSlotCard::mouseDown(const juce::MouseEvent& e)
{
    // Check button clicks
    if (bypassButtonBounds.contains(e.getPosition()))
    {
        if (onToggleBypass)
            onToggleBypass(slotIdx, !bypassed);
        return;
    }

    if (abButtonBounds.contains(e.getPosition()))
    {
        ABSlot newSlot = (abSlot == ABSlot::A) ? ABSlot::B : ABSlot::A;
        if (onToggleAB)
            onToggleAB(slotIdx, newSlot);
        return;
    }

    if (removeButtonBounds.contains(e.getPosition()))
    {
        if (onRemove)
            onRemove(slotIdx);
        return;
    }

    // Otherwise, select this slot and prepare for potential drag
    DBG("Mouse down on slot " << slotIdx);
    if (onSelected)
        onSelected(slotIdx);

    dragStartPos = e.getPosition();
}

void ChainSlotCard::mouseDoubleClick(const juce::MouseEvent& e)
{
    // Double-clicking the plugin image opens the plugin's editor (when a plugin is loaded).
    // Ignore double-clicks on the toolbar buttons - they're handled by mouseDown.
    if (bypassButtonBounds.contains(e.getPosition())
        || abButtonBounds.contains(e.getPosition())
        || removeButtonBounds.contains(e.getPosition()))
        return;

    if (pluginName.isNotEmpty() && onViewPlugin)
        onViewPlugin(slotIdx);
}

void ChainSlotCard::mouseDrag(const juce::MouseEvent& e)
{
    // Start drag if moved far enough (reduced threshold to 2 pixels)
    if (!isDragging && e.getDistanceFromDragStart() > 2)
    {
        isDragging = true;
        DBG("Starting drag for slot " << slotIdx);
        if (onDragStart)
            onDragStart(slotIdx, e.getScreenPosition());
    }

    if (isDragging)
    {
        if (onDragMove)
            onDragMove(slotIdx, e.getScreenPosition());
        setAlpha(0.5f);  // Semi-transparent while dragging
    }
}

void ChainSlotCard::mouseUp(const juce::MouseEvent&)
{
    if (isDragging)
    {
        isDragging = false;
        setAlpha(1.0f);

        if (onDragEnd)
            onDragEnd(slotIdx);
    }
}

void ChainSlotCard::setSlotData(const ChainSlot& slot, int slotIndex, bool isSelected)
{
    slotIdx = slotIndex;
    selected = isSelected;
    bypassed = slot.bypassed;
    abSlot = slot.activeSlot;

    // Get plugin name from active host
    const auto& activeHost = slot.getActiveHost();
    if (activeHost.hasLoadedPlugin())
    {
        auto desc = activeHost.getLoadedPluginDescription();
        if (desc != nullptr)
        {
            pluginName = desc->name;
            updateImage();
        }
    }
    else
    {
        pluginName.clear();
        pluginImage = juce::Image();
    }

    repaint();
}

void ChainSlotCard::setSelected(bool shouldBeSelected)
{
    if (selected != shouldBeSelected)
    {
        selected = shouldBeSelected;
        repaint();
    }
}

void ChainSlotCard::setBypassed(bool shouldBeBypassed)
{
    if (bypassed != shouldBeBypassed)
    {
        bypassed = shouldBeBypassed;
        repaint();
    }
}

void ChainSlotCard::setABSlot(ABSlot slot)
{
    if (abSlot != slot)
    {
        abSlot = slot;
        repaint();
    }
}

void ChainSlotCard::updateImage()
{
    if (pluginName.isEmpty())
    {
        pluginImage = juce::Image();
        repaint();
        return;
    }

    // Try to get image from cache
    auto& imageCache = PluginImageCache::getInstance();
    pluginImage = imageCache.getImage(pluginName);

    repaint();
}

} // namespace PALauncher
