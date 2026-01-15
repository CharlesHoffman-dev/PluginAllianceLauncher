/*
  ==============================================================================
    PluginEditor.h
    Plugin Alliance Launcher - Main Plugin Editor UI
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/SearchBar.h"
#include "UI/CategoryFilter.h"
#include "UI/SubcategoryFilter.h"
#include "UI/EraFilter.h"
#include "UI/PluginListView.h"
#include "UI/HostedPluginView.h"

namespace PALauncher
{

class PluginAllianceLauncherEditor : public juce::AudioProcessorEditor,
                                      public juce::ChangeListener,
                                      public juce::Timer
{
public:
    explicit PluginAllianceLauncherEditor(PluginAllianceLauncherProcessor& p);
    ~PluginAllianceLauncherEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    // ChangeListener - for scanner updates
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // Timer - for UI updates
    void timerCallback() override;

private:
    void updatePluginList();
    void filterPlugins();
    void loadSelectedPlugin(const PluginInfo& info);
    void toggleBrowserMode();

    PluginAllianceLauncherProcessor& processor;

    // Top bar components
    SearchBar searchBar;
    juce::TextButton rescanButton;
    juce::TextButton toggleModeButton;

    // Sidebar components
    CategoryFilter categoryFilter;
    SubcategoryFilter subcategoryFilter;
    EraFilter eraFilter;

    // Main content area
    PluginListView pluginListView;
    HostedPluginView hostedPluginView;

    // State
    bool browserMode = true;  // true = show browser, false = show hosted plugin fullscreen
    bool wasScanning = false;  // Track scanning state for layout updates
    DisplayCategory currentCategory = DisplayCategory::All;
    int currentSubcategory = -1;  // -1 = all
    Era currentEra = Era::Era_Unknown;  // Unknown = all
    juce::String currentSearchText;

    // Logo
    std::unique_ptr<juce::Drawable> logoDrawable;
    void loadLogo();

    // Window sizing
    juce::Rectangle<int> defaultBrowserSize { 0, 0, 1200, 800 };
    void resizeForPlugin();
    void resizeForBrowser();

    // Layout
    static constexpr int sidebarWidth = 180;
    static constexpr int topBarHeight = 48;
    static constexpr int hostedPluginMinHeight = 300;
    static constexpr int logoWidth = 140;
    static constexpr int logoHeight = 26;
    static constexpr int hostedPluginHeaderHeight = 36;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherEditor)
};

} // namespace PALauncher
