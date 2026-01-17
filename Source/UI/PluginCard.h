/*
  ==============================================================================
    PluginCard.h
    Plugin Alliance Launcher - Individual Plugin Display Card
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Core/PluginDatabase.h"

namespace PALauncher
{

class PluginCard : public juce::Component
{
public:
    PluginCard();
    ~PluginCard() override = default;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseEnter(const juce::MouseEvent&) override;
    void mouseExit(const juce::MouseEvent&) override;
    void mouseDown(const juce::MouseEvent&) override;
    void mouseDoubleClick(const juce::MouseEvent&) override;

    // Set the plugin info to display
    void setPluginInfo(const PluginInfo& info);
    const PluginInfo& getPluginInfo() const { return pluginInfo; }

    // Selection state
    void setSelected(bool selected);
    bool isSelected() const { return selected; }

    // Loaded state - shows as hovered with "View" button
    void setLoaded(bool loaded);
    bool isLoaded() const { return isLoadedPlugin; }

    // Update image from cache
    void updateImage();

    // Callbacks
    std::function<void(const PluginInfo&)> onSelected;
    std::function<void(const PluginInfo&)> onDoubleClick;
    std::function<void(const PluginInfo&, bool)> onFavoriteToggle;

    // Preferred card size - square thumbnail area with room for text
    static constexpr int preferredWidth = 210;
    static constexpr int preferredHeight = 235;

private:
    PluginInfo pluginInfo;
    bool selected = false;
    bool hovered = false;
    bool isLoadedPlugin = false;

    juce::Image pluginImage;
    juce::TextButton loadButton;
    juce::Rectangle<int> imageBoundsCache;  // Cached for hit testing

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginCard)
};

} // namespace PALauncher
