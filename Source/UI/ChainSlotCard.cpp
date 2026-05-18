/*
  ==============================================================================
    ChainSlotCard.cpp
    Plugin Alliance Launcher - Individual Chain Slot Display Card Implementation
  ==============================================================================
*/

#include "ChainSlotCard.h"
#include "../Utils/PluginImageCache.h"
#include "Colors.h"
#include "ModuleHeaderLayout.h"

namespace PALauncher
{

namespace
{
    // Builds an OPEN rounded-rectangle path for the LEFT half of a unified
    // module: rounded top-left + bottom-left, flat right (no right edge drawn
    // by the stroke). The slot card uses this so its border stops exactly at
    // the seam, where the meter card picks it up with its mirror path.
    static juce::Path horseshoeLeftPath(juce::Rectangle<float> b, float r)
    {
        const float L = b.getX();
        const float R = b.getRight();
        const float T = b.getY();
        const float B = b.getBottom();
        const float halfPi = juce::MathConstants<float>::halfPi;
        const float pi     = juce::MathConstants<float>::pi;

        juce::Path p;
        p.startNewSubPath(R, T);                                  // top-right (flat seam)
        p.lineTo(L + r, T);                                       // top edge
        p.addCentredArc(L + r, T + r, r, r, 0.0f,  0.0f, -halfPi);// top-left arc
        p.lineTo(L, B - r);                                       // left edge
        p.addCentredArc(L + r, B - r, r, r, 0.0f, -halfPi, -pi);  // bottom-left arc
        p.lineTo(R, B);                                           // bottom edge
        return p;
    }
}

ChainSlotCard::ChainSlotCard(int slotIndex)
    : slotIdx(slotIndex)
{
    setWantsKeyboardFocus(false);
    setMouseClickGrabsKeyboardFocus(false);
    setInterceptsMouseClicks(true, false);  // Ensure this component receives mouse clicks
    setMouseCursor(juce::MouseCursor::PointingHandCursor);
    setSize(cardWidth, cardHeight);
}

void ChainSlotCard::paint(juce::Graphics& g)
{
    // The slot and its output meter form one visual module. We pad top/bottom/
    // left for the border and shadow, but extend flush to the right edge so the
    // meter sits seamlessly against us.
    auto bounds = getLocalBounds().toFloat();
    bounds.removeFromTop(2.0f);
    bounds.removeFromBottom(2.0f);
    bounds.removeFromLeft(2.0f);

    // Background colour - white; selection is signaled by the cyan border
    // alone (no body tint). Bypass and hover still tint subtly.
    juce::Colour bgColor = Colors::cardBackground();
    if (bypassed)     bgColor = Colors::cardBackgroundBypassed();
    else if (hovered) bgColor = Colors::cardBackgroundHover();

    constexpr float cardRadius = 6.0f;

    // Card body fill: rounded left, FLAT right (bool corner variant). The
    // meter card fills its half the same way mirrored, so the two flat seams
    // abut without a gap.
    juce::Path cardFill;
    cardFill.addRoundedRectangle(bounds.getX(), bounds.getY(),
                                 bounds.getWidth(), bounds.getHeight(),
                                 cardRadius, cardRadius,
                                 true,  false,   // top-left rounded, top-right flat
                                 true,  false);  // bottom-left rounded, bottom-right flat

    // Drop shadow under just the slot's half.
    g.setColour(Colors::shadow());
    {
        juce::Path shadow;
        auto sb = bounds.translated(1.0f, 2.0f);
        shadow.addRoundedRectangle(sb.getX(), sb.getY(), sb.getWidth(), sb.getHeight(),
                                   cardRadius, cardRadius,
                                   true, false, true, false);
        g.fillPath(shadow);
    }

    g.setColour(bgColor);
    g.fillPath(cardFill);

    // Border: 3-sided horseshoe (no right edge) so the slot's outline merges
    // seamlessly with the meter's mirror horseshoe at the seam.
    g.setColour(selected ? Colors::accent() : Colors::borderSubtle());
    g.strokePath(horseshoeLeftPath(bounds, cardRadius),
                 juce::PathStrokeType(selected ? 2.0f : 1.0f));

    // Content area - 3px padding on top/left/bottom, flush to the slot's
    // right edge so the charcoal toolbar continues into the meter.
    auto contentBounds = getLocalBounds();
    contentBounds.removeFromLeft(3);
    contentBounds.removeFromTop(3);
    contentBounds.removeFromBottom(3);
    // No right padding here.

    auto toolbarBounds = contentBounds.removeFromTop(24);

    // Toolbar background - rounded top-left only; flat top-right meets the
    // meter's toolbar at the seam.
    juce::Path toolbarPath;
    auto tbF = toolbarBounds.toFloat();
    toolbarPath.addRoundedRectangle(tbF.getX(), tbF.getY(),
                                    tbF.getWidth(), tbF.getHeight(),
                                    3.0f, 3.0f,
                                    true,  false,   // top-left rounded, top-right flat
                                    false, false);  // bottom corners flat
    g.setColour(Colors::toolbarBackground());
    g.fillPath(toolbarPath);

    // All four header-button rects come from ModuleHeaderLayout so the layout
    // lives in one file. The slot card owns Power, A/B, and AUTO; X lives in
    // the meter card and reads the same constants.
    bypassButtonBounds = ModuleHeader::toSlotRect(ModuleHeader::power, toolbarBounds.getY());
    g.setColour(bypassed ? Colors::accent() : Colors::cardBackground());
    g.fillRoundedRectangle(bypassButtonBounds.toFloat(), 2.5f);

    auto iconBounds = bypassButtonBounds.toFloat().reduced(3.0f);
    float cx = iconBounds.getCentreX();
    float cy = iconBounds.getCentreY() + 0.5f;  // visually centre after bar extends above
    float radius = iconBounds.getWidth() * 0.42f;
    float strokeWidth = 1.4f;

    g.setColour(bypassed ? Colors::textOnDark() : Colors::textOnLight());

    const float halfGap = 0.42f;  // ~24° half-gap → ~48° total gap at top
    juce::Path powerArc;
    powerArc.addCentredArc(cx, cy, radius, radius, 0.0f,
                           halfGap,
                           juce::MathConstants<float>::twoPi - halfGap,
                           true);
    g.strokePath(powerArc, juce::PathStrokeType(strokeWidth,
                                                juce::PathStrokeType::curved,
                                                juce::PathStrokeType::rounded));

    // Vertical bar: starts slightly above the circle, ends a bit shy of centre.
    g.drawLine(cx, cy - radius - 1.2f,
               cx, cy - radius * 0.15f,
               strokeWidth);

    // Remove button has moved to the meter's half of the header.
    removeButtonBounds = {};

    // A/B segmented control
    abButtonBounds = ModuleHeader::toSlotRect(ModuleHeader::ab, toolbarBounds.getY());
    auto abBounds = abButtonBounds.toFloat();
    float halfWidth = abBounds.getWidth() / 2.0f;
    float cornerSize = 2.5f;

    auto leftBounds = abBounds.withWidth(halfWidth);
    auto rightBounds = abBounds.withLeft(abBounds.getX() + halfWidth);

    // Active side = accent (orange in 70s, cyan in default). Inactive = white
    // card surface so the pair reads as a clean active/white toggle.
    auto activeColour   = Colors::accent();
    auto inactiveColour = Colors::cardBackground();

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

    // Active letter: white on accent. Inactive letter: dark on white.
    auto font = juce::Font(8.0f, juce::Font::bold);
    g.setFont(font);
    const auto activeText   = Colors::textOnDark();
    const auto inactiveText = Colors::textOnLight();
    g.setColour(abSlot == ABSlot::B ? inactiveText : activeText);
    g.drawText("A", leftBounds.toNearestInt(), juce::Justification::centred);
    g.setColour(abSlot == ABSlot::B ? activeText : inactiveText);
    g.drawText("B", rightBounds.toNearestInt(), juce::Justification::centred);

    // AUTO button - third evenly-spaced position in the unified header.
    autoButtonBounds = ModuleHeader::toSlotRect(ModuleHeader::autoBtn, toolbarBounds.getY());
    auto autoBoundsF = autoButtonBounds.toFloat();
    if (autoGainEnabled && autoGainAnalyzing)
    {
        g.setColour(autoFlashOn ? activeColour : inactiveColour);
        g.fillRoundedRectangle(autoBoundsF, 2.5f);
        g.setColour(autoFlashOn ? Colors::textOnDark() : Colors::textMuted());
    }
    else if (autoGainEnabled)
    {
        g.setColour(activeColour);
        g.fillRoundedRectangle(autoBoundsF, 2.5f);
        g.setColour(Colors::textOnDark());
    }
    else
    {
        g.setColour(inactiveColour);
        g.fillRoundedRectangle(autoBoundsF, 2.5f);
        g.setColour(Colors::textOnDark());
    }
    g.setFont(juce::Font(8.0f, juce::Font::bold));
    g.drawText("AUTO", autoButtonBounds, juce::Justification::centred);

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
        g.setColour(Colors::placeholderImage());
        g.fillRoundedRectangle(imageBounds.toFloat(), 4.0f);
    }

    // Bypassed overlay text
    if (bypassed)
    {
        auto overlayBounds = imageBounds;
        g.setColour(Colors::appBackground().withAlpha(0.6f));
        g.fillRoundedRectangle(overlayBounds.toFloat(), 3.5f);

        g.setColour(Colors::textOnDark());
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

    if (autoButtonBounds.contains(e.getPosition()))
    {
        autoGainEnabled = !autoGainEnabled;
        if (onAutoGainToggled)
            onAutoGainToggled(slotIdx, autoGainEnabled);
        repaint();
        return;
    }

    // The Remove (X) button lives on the meter half of the module; the chain
    // view wires its click through to onRemoveSlot for this slot.

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
        || autoButtonBounds.contains(e.getPosition()))
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
    autoGainEnabled = slot.autoGainEnabled;

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

void ChainSlotCard::setAutoGainEnabled(bool enabled)
{
    if (autoGainEnabled != enabled)
    {
        autoGainEnabled = enabled;
        if (!enabled)
            setAutoGainAnalyzing(false);
        repaint();
    }
}

void ChainSlotCard::setAutoGainAnalyzing(bool analyzing)
{
    if (autoGainAnalyzing == analyzing)
        return;

    autoGainAnalyzing = analyzing;
    if (analyzing)
    {
        autoFlashOn = true;
        startTimer(250);  // ~2 Hz flash
    }
    else
    {
        stopTimer();
        autoFlashOn = false;
    }
    repaint();
}

void ChainSlotCard::timerCallback()
{
    autoFlashOn = !autoFlashOn;
    repaint();
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
