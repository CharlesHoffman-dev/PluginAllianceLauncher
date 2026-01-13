/*
  ==============================================================================
    PluginCard.cpp
    Plugin Alliance Launcher - Individual Plugin Display Card Implementation
  ==============================================================================
*/

#include "PluginCard.h"

namespace PALauncher
{

PluginCard::PluginCard()
{
    favoriteButton.setButtonText("");
    favoriteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    favoriteButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);
    favoriteButton.onClick = [this]()
    {
        if (onFavoriteToggle)
            onFavoriteToggle(pluginInfo, !pluginInfo.isFavorite);
    };
    addAndMakeVisible(favoriteButton);
}

void PluginCard::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat().reduced(2.0f);

    // Background
    juce::Colour bgColor = juce::Colour(0xff1a1a1a);
    if (selected)
        bgColor = juce::Colour(0xff1e3a4a);
    else if (hovered)
        bgColor = juce::Colour(0xff252525);

    g.setColour(bgColor);
    g.fillRoundedRectangle(bounds, 6.0f);

    // Border
    if (selected)
    {
        g.setColour(juce::Colour(0xff0cbff2));
        g.drawRoundedRectangle(bounds, 6.0f, 2.0f);
    }

    // Content area
    auto contentBounds = getLocalBounds().reduced(10, 8);

    // Plugin name
    g.setColour(juce::Colours::white);
    g.setFont(juce::Font(13.0f, juce::Font::bold));
    auto nameBounds = contentBounds.removeFromTop(20);
    nameBounds.removeFromRight(24); // Space for favorite button
    g.drawText(pluginInfo.description.name, nameBounds, juce::Justification::centredLeft, true);

    // Manufacturer
    g.setColour(juce::Colour(0xfff9f9f9).withAlpha(0.6f));
    g.setFont(juce::Font(11.0f));
    g.drawText(pluginInfo.description.manufacturerName, contentBounds.removeFromTop(16),
               juce::Justification::centredLeft, true);

    contentBounds.removeFromTop(4);

    // Category tag
    juce::String categoryTag = getEffectCategoryName(pluginInfo.category);
    if (!categoryTag.isEmpty() && pluginInfo.category != EffectCategory::Unknown)
    {
        g.setColour(juce::Colour(0xff0cbff2).withAlpha(0.3f));
        auto tagBounds = contentBounds.removeFromLeft(80).removeFromTop(18);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff0cbff2));
        g.setFont(juce::Font(10.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
    }

    // Era tag
    if (pluginInfo.era != Era::Era_Unknown)
    {
        contentBounds.removeFromLeft(4);
        juce::String eraTag = getEraName(pluginInfo.era);
        // Shorten for display
        if (eraTag.contains(" - "))
            eraTag = eraTag.upToFirstOccurrenceOf(" - ", false, false);

        g.setColour(juce::Colour(0xfff9f9f9).withAlpha(0.2f));
        auto eraBounds = contentBounds.removeFromLeft(50).removeFromTop(18);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xfff9f9f9));
        g.setFont(juce::Font(10.0f));
        g.drawText(eraTag, eraBounds, juce::Justification::centred);
    }

    // Favorite star
    auto starBounds = getLocalBounds().reduced(8).removeFromTop(20).removeFromRight(20);
    g.setFont(juce::Font(16.0f));
    g.setColour(pluginInfo.isFavorite ? juce::Colour(0xff0cbff2) : juce::Colour(0xff555555));
    g.drawText(pluginInfo.isFavorite ? juce::CharPointer_UTF8("\xe2\x98\x85") : juce::CharPointer_UTF8("\xe2\x98\x86"),
               starBounds, juce::Justification::centred);
}

void PluginCard::resized()
{
    // Position favorite button over the star area
    auto starBounds = getLocalBounds().reduced(8).removeFromTop(20).removeFromRight(20);
    favoriteButton.setBounds(starBounds);
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

void PluginCard::mouseDown(const juce::MouseEvent&)
{
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
