/*
  ==============================================================================
    PluginCard.cpp
    Plugin Alliance Launcher - Individual Plugin Display Card Implementation
  ==============================================================================
*/

#include "PluginCard.h"
#include "../Utils/PluginImageCache.h"

namespace PALauncher
{

PluginCard::PluginCard()
{
    // Prevent focus grabbing - don't steal focus from other components
    setWantsKeyboardFocus(false);
    setMouseClickGrabsKeyboardFocus(false);
}

void PluginCard::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background - white with subtle shadow effect
    juce::Colour bgColor = juce::Colours::white;
    if (selected)
        bgColor = juce::Colour(0xffe8f4fc);  // Light blue tint when selected
    else if (hovered)
        bgColor = juce::Colour(0xfffafafa);  // Slightly off-white on hover

    // Drop shadow effect
    g.setColour(juce::Colour(0x15000000));
    g.fillRoundedRectangle(bounds.translated(1.0f, 2.0f), 6.0f);

    g.setColour(bgColor);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    if (selected)
    {
        g.setColour(juce::Colour(0xff0cbff2));
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }
    else
    {
        // Subtle border for non-selected cards
        g.setColour(juce::Colour(0xffe0e0e0));
        g.drawRoundedRectangle(bounds, 6.0f, 1.0f);
    }

    // Content area
    auto contentBounds = getLocalBounds().reduced(10, 8);

    // Get brand name and display name (with brand removed)
    auto brandName = getBrandName(pluginInfo.description.name, pluginInfo.description.manufacturerName);
    auto displayName = getDisplayName(pluginInfo.description.name, brandName);

    // Brand name - gray text, in line with star
    g.setColour(juce::Colour(0xff666666));
    g.setFont(juce::Font(13.0f));
    auto brandBounds = contentBounds.removeFromTop(18);
    brandBounds.removeFromRight(26); // Space for favorite button
    g.drawText(brandName, brandBounds, juce::Justification::centredLeft, true);

    // Plugin name (with brand removed) - dark text, larger bold font
    g.setColour(juce::Colour(0xff1a1a1a));
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    g.drawText(displayName, contentBounds.removeFromTop(24),
               juce::Justification::centredLeft, true);

    contentBounds.removeFromTop(8);

    // Plugin image - square area for better vertical thumbnail support
    auto imageBounds = contentBounds.removeFromTop(140);
    if (pluginImage.isValid())
    {
        // Draw the image centered in the bounds
        float imageAspect = (float)pluginImage.getWidth() / (float)pluginImage.getHeight();
        float boundsAspect = (float)imageBounds.getWidth() / (float)imageBounds.getHeight();

        juce::Rectangle<float> drawBounds;
        if (imageAspect > boundsAspect)
        {
            // Image is wider - fit to width
            float drawWidth = (float)imageBounds.getWidth();
            float drawHeight = drawWidth / imageAspect;
            float y = imageBounds.getY() + (imageBounds.getHeight() - drawHeight) / 2.0f;
            drawBounds = juce::Rectangle<float>((float)imageBounds.getX(), y, drawWidth, drawHeight);
        }
        else
        {
            // Image is taller - fit to height
            float drawHeight = (float)imageBounds.getHeight();
            float drawWidth = drawHeight * imageAspect;
            float x = imageBounds.getX() + (imageBounds.getWidth() - drawWidth) / 2.0f;
            drawBounds = juce::Rectangle<float>(x, (float)imageBounds.getY(), drawWidth, drawHeight);
        }

        g.drawImage(pluginImage, drawBounds, juce::RectanglePlacement::centred);
    }
    else
    {
        // Draw placeholder - light gray
        g.setColour(juce::Colour(0xffeeeeee));
        g.fillRoundedRectangle(imageBounds.toFloat(), 4.0f);

        g.setColour(juce::Colour(0xff999999));
        g.setFont(juce::Font(12.0f));
        g.drawText("Loading...", imageBounds, juce::Justification::centred);
    }

    contentBounds.removeFromTop(14);

    // Category and Era tags row
    auto tagRow = contentBounds.removeFromTop(20);

    // Category tag
    juce::String categoryTag = getEffectCategoryName(pluginInfo.category);
    if (!categoryTag.isEmpty() && pluginInfo.category != EffectCategory::Unknown)
    {
        g.setColour(juce::Colour(0xff0cbff2).withAlpha(0.15f));
        auto tagBounds = tagRow.removeFromLeft(85);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff0099cc));
        g.setFont(juce::Font(12.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
    }

    // Era tag
    if (pluginInfo.era != Era::Era_Unknown)
    {
        tagRow.removeFromLeft(4);
        juce::String eraTag = getEraName(pluginInfo.era);

        g.setColour(juce::Colour(0xff888888).withAlpha(0.15f));
        auto eraBounds = tagRow.removeFromLeft(55);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff666666));
        g.setFont(juce::Font(12.0f));
        g.drawText(eraTag, eraBounds, juce::Justification::centred);
    }

    // Favorite heart - red when active, gray outline when inactive
    auto heartBounds = getLocalBounds().reduced(8).removeFromTop(24).removeFromRight(24);
    float cx = static_cast<float>(heartBounds.getCentreX());
    float cy = static_cast<float>(heartBounds.getCentreY());
    float size = 10.0f;

    // Create heart path using bezier curves
    juce::Path heartPath;
    heartPath.startNewSubPath(cx, cy + size * 0.7f);  // Bottom point
    // Left curve
    heartPath.cubicTo(cx - size * 1.2f, cy + size * 0.2f,   // Control point 1
                      cx - size * 1.2f, cy - size * 0.5f,   // Control point 2
                      cx, cy - size * 0.2f);                 // End at top center dip
    // Right curve
    heartPath.cubicTo(cx + size * 1.2f, cy - size * 0.5f,   // Control point 1
                      cx + size * 1.2f, cy + size * 0.2f,   // Control point 2
                      cx, cy + size * 0.7f);                 // Back to bottom point
    heartPath.closeSubPath();

    if (pluginInfo.isFavorite)
    {
        g.setColour(juce::Colour(0xffff4d6a));  // Pink/red color
        g.fillPath(heartPath);
    }
    else
    {
        g.setColour(juce::Colour(0xffcccccc));  // Light gray outline
        g.strokePath(heartPath, juce::PathStrokeType(1.5f));
    }
}

void PluginCard::resized()
{
    // Nothing to position - heart is drawn directly in paint()
}

void PluginCard::mouseEnter(const juce::MouseEvent&)
{
    hovered = true;
    repaint();
}

void PluginCard::mouseExit(const juce::MouseEvent&)
{
    hovered = false;
    repaint();
}

void PluginCard::mouseDown(const juce::MouseEvent& e)
{
    // Check if click is on the heart area (with expanded hit area for easier clicking)
    auto heartBounds = getLocalBounds().reduced(4).removeFromTop(28).removeFromRight(28);
    if (heartBounds.contains(e.getPosition()))
    {
        // Toggle favorite
        if (onFavoriteToggle)
            onFavoriteToggle(pluginInfo, !pluginInfo.isFavorite);
        return;
    }

    if (onSelected)
        onSelected(pluginInfo);
}

void PluginCard::mouseDoubleClick(const juce::MouseEvent&)
{
    if (onDoubleClick)
        onDoubleClick(pluginInfo);
}

void PluginCard::setPluginInfo(const PluginInfo& info)
{
    pluginInfo = info;

    // Try to get image from cache
    updateImage();

    // Request image download if not cached
    PluginImageCache::getInstance().requestImage(pluginInfo.description.name);

    repaint();
}

void PluginCard::updateImage()
{
    pluginImage = PluginImageCache::getInstance().getImage(pluginInfo.description.name);
    repaint();
}

void PluginCard::setSelected(bool sel)
{
    if (selected != sel)
    {
        selected = sel;
        repaint();
    }
}

} // namespace PALauncher
