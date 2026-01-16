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

    // Plugin name (with brand removed) - dark text, larger font
    g.setColour(juce::Colour(0xff1a1a1a));
    g.setFont(juce::Font(16.0f, juce::Font::bold));
    auto nameBounds = contentBounds.removeFromTop(24);
    nameBounds.removeFromRight(26); // Space for favorite button
    g.drawText(displayName, nameBounds, juce::Justification::centredLeft, true);

    // Brand name - gray text, larger font
    g.setColour(juce::Colour(0xff666666));
    g.setFont(juce::Font(13.0f));
    g.drawText(brandName, contentBounds.removeFromTop(18),
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

    contentBounds.removeFromTop(8);

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

    // Favorite star - yellow when active, gray outline when inactive
    auto starBounds = getLocalBounds().reduced(8).removeFromTop(24).removeFromRight(24);
    float starCx = starBounds.getCentreX();
    float starCy = starBounds.getCentreY();
    float starRadius = 10.0f;

    // Create 5-pointed star path
    juce::Path starPath;
    for (int i = 0; i < 5; ++i)
    {
        float outerAngle = juce::MathConstants<float>::pi * 2.0f * i / 5.0f - juce::MathConstants<float>::halfPi;
        float innerAngle = outerAngle + juce::MathConstants<float>::pi / 5.0f;

        float outerX = starCx + starRadius * std::cos(outerAngle);
        float outerY = starCy + starRadius * std::sin(outerAngle);
        float innerX = starCx + starRadius * 0.4f * std::cos(innerAngle);
        float innerY = starCy + starRadius * 0.4f * std::sin(innerAngle);

        if (i == 0)
            starPath.startNewSubPath(outerX, outerY);
        else
            starPath.lineTo(outerX, outerY);

        starPath.lineTo(innerX, innerY);
    }
    starPath.closeSubPath();

    if (pluginInfo.isFavorite)
    {
        g.setColour(juce::Colour(0xffffc107));  // Yellow/gold color
        g.fillPath(starPath);
    }
    else
    {
        g.setColour(juce::Colour(0xffcccccc));  // Light gray outline
        g.strokePath(starPath, juce::PathStrokeType(1.5f));
    }
}

void PluginCard::resized()
{
    // Nothing to position - star is drawn directly in paint()
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
    // Check if click is on the star area (with expanded hit area for easier clicking)
    auto starBounds = getLocalBounds().reduced(4).removeFromTop(28).removeFromRight(28);
    if (starBounds.contains(e.getPosition()))
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
