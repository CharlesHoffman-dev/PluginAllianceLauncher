/*
  ==============================================================================
    PluginListView.h
    Plugin Alliance Launcher - Scrollable Plugin Grid View
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Core/PluginDatabase.h"
#include "PluginCard.h"

namespace PALauncher
{

class PluginListView : public juce::Component,
                       public juce::ScrollBar::Listener
{
public:
    PluginListView();
    ~PluginListView() override;

    void paint(juce::Graphics& g) override;
    void paintOverChildren(juce::Graphics& g) override;
    void resized() override;

    void mouseWheelMove(const juce::MouseEvent& e, const juce::MouseWheelDetails& wheel) override;

    // Set plugins to display
    void setPlugins(const juce::Array<PluginInfo>& plugins);

    // Update plugins while preserving scroll position (for favorites, etc.)
    void updatePlugins(const juce::Array<PluginInfo>& plugins);

    // Set the currently loaded plugin (shown with "View" button)
    void setLoadedPluginId(const juce::String& pluginId);

    // Get currently selected plugin
    const PluginInfo* getSelectedPlugin() const;

    // Select a plugin by index (for auto-selection)
    void selectPluginAtIndex(int index);

    // Callbacks
    std::function<void(const PluginInfo&)> onPluginSelected;
    std::function<void(const PluginInfo&)> onPluginDoubleClick;
    std::function<void(const PluginInfo&, bool)> onFavoriteToggle;

private:
    void scrollBarMoved(juce::ScrollBar* scrollBar, double newRangeStart) override;
    void updateLayout();
    void updateVisibleCards();
    int calculateNumColumns() const;

    juce::Array<PluginInfo> allPlugins;
    juce::OwnedArray<PluginCard> visibleCards;
    juce::Viewport viewport;
    juce::Component contentComponent;
    juce::ScrollBar verticalScrollBar { true }; // true = vertical

    int selectedIndex = -1;
    int scrollOffset = 0;
    int numColumns = 4;
    int cardSpacing = 6;
    juce::String loadedPluginId;  // fileOrIdentifier of currently loaded plugin

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginListView)
};

} // namespace PALauncher
