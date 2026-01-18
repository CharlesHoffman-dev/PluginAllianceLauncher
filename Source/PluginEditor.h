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
#include "UI/PluginListView.h"
#include "UI/HostedPluginView.h"

namespace PALauncher
{

// Custom LookAndFeel for buttons - no outline, 4px radius, bold text
class ButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);
        auto baseColour = backgroundColour;

        if (isButtonDown)
            baseColour = baseColour.darker(0.2f);
        else if (isMouseOverButton)
            baseColour = baseColour.brighter(0.1f);

        g.setColour(baseColour);
        g.fillRoundedRectangle(bounds, 4.0f);
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                        bool /*isMouseOverButton*/, bool isButtonDown) override
    {
        auto font = juce::Font(button.getHeight() * 0.48f, juce::Font::bold);
        g.setFont(font);
        g.setColour(button.findColour(isButtonDown ? juce::TextButton::textColourOnId
                                                    : juce::TextButton::textColourOffId)
                        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        auto bounds = button.getLocalBounds();
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, true);
    }
};

// Custom LookAndFeel for brand combo box with reduced popup height
class BrandComboBoxLookAndFeel : public juce::LookAndFeel_V4
{
public:
    juce::PopupMenu::Options getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label&) override
    {
        return juce::PopupMenu::Options()
            .withTargetComponent(&box)
            .withMaximumNumColumns(1)
            .withMinimumNumColumns(1)
            .withStandardItemHeight(20)
            .withItemThatMustBeVisible(box.getSelectedId());
    }

    void getIdealPopupMenuItemSize(const juce::String& text, bool isSeparator, int standardMenuItemHeight,
                                   int& idealWidth, int& idealHeight) override
    {
        juce::LookAndFeel_V4::getIdealPopupMenuItemSize(text, isSeparator, standardMenuItemHeight, idealWidth, idealHeight);
        idealHeight = 20;  // Smaller row height
    }
};

// Custom LookAndFeel for settings button with gear icon
class SettingsButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isMouseOverButton, bool isButtonDown) override
    {
        auto bounds = button.getLocalBounds().toFloat().reduced(0.5f);
        auto baseColour = backgroundColour;

        if (isButtonDown)
            baseColour = baseColour.darker(0.2f);
        else if (isMouseOverButton)
            baseColour = baseColour.brighter(0.15f);

        g.setColour(baseColour);
        g.fillRoundedRectangle(bounds, 4.0f);
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                        bool /*isMouseOverButton*/, bool /*isButtonDown*/) override
    {
        // Draw gear/cog icon
        auto bounds = button.getLocalBounds().toFloat();
        auto centerX = bounds.getCentreX();
        auto centerY = bounds.getCentreY();
        auto size = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.45f;

        g.setColour(button.findColour(juce::TextButton::textColourOffId));

        // Draw gear with proper rectangular teeth
        juce::Path gearPath;
        const int numTeeth = 6;
        const float outerRadius = size;
        const float innerRadius = size * 0.65f;
        const float toothWidth = 0.35f;  // Width of tooth as fraction of tooth spacing

        // Create gear outline with rectangular teeth
        for (int i = 0; i < numTeeth; ++i)
        {
            float baseAngle = (float)i * juce::MathConstants<float>::twoPi / numTeeth;
            float halfTooth = toothWidth * juce::MathConstants<float>::pi / numTeeth;

            // Tooth outer edge (4 points per tooth)
            float a1 = baseAngle - halfTooth;
            float a2 = baseAngle + halfTooth;

            // Inner radius points before tooth
            float prevAngle = baseAngle - juce::MathConstants<float>::pi / numTeeth;
            if (i == 0)
            {
                gearPath.startNewSubPath(centerX + std::cos(prevAngle + halfTooth) * innerRadius,
                                         centerY + std::sin(prevAngle + halfTooth) * innerRadius);
            }

            // Rise to outer radius
            gearPath.lineTo(centerX + std::cos(a1) * innerRadius, centerY + std::sin(a1) * innerRadius);
            gearPath.lineTo(centerX + std::cos(a1) * outerRadius, centerY + std::sin(a1) * outerRadius);

            // Across tooth top
            gearPath.lineTo(centerX + std::cos(a2) * outerRadius, centerY + std::sin(a2) * outerRadius);

            // Down to inner radius
            gearPath.lineTo(centerX + std::cos(a2) * innerRadius, centerY + std::sin(a2) * innerRadius);
        }
        gearPath.closeSubPath();

        // Center hole
        float holeRadius = size * 0.3f;
        gearPath.addEllipse(centerX - holeRadius, centerY - holeRadius,
                           holeRadius * 2.0f, holeRadius * 2.0f);

        g.fillPath(gearPath);
    }
};

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
    void refreshPluginsPreservingScroll();  // For favorites toggle - doesn't reset scroll
    void loadSelectedPlugin(const PluginInfo& info);
    void toggleBrowserMode();

    PluginAllianceLauncherProcessor& processor;

    // Subscription banner
    juce::Label subscriptionLabel;
    juce::TextButton subscribeButton;

    // Top bar components
    SearchBar searchBar;
    juce::TextButton rescanButton;
    juce::TextButton settingsButton;
    juce::TextButton toggleModeButton;

    // Settings menu
    void showSettingsMenu();

    // Sidebar components
    CategoryFilter categoryFilter;
    SubcategoryFilter subcategoryFilter;

    // Filter dropdowns (in top bar)
    juce::ComboBox sortComboBox;
    juce::ComboBox eraComboBox;
    juce::ComboBox brandComboBox;
    juce::String currentBrandFilter;  // Empty = all brands
    int currentSortOrder = 0;  // 0=Brand A-Z, 1=Brand Z-A, 2=Name A-Z, 3=Name Z-A

    // Plugin details panel (right side)
    void paintDetailsPanel(juce::Graphics& g, juce::Rectangle<int> bounds);
    juce::TextButton detailsLoadButton;
    juce::Image detailsPluginImage;
    static constexpr int detailsPanelWidth = 280;

    // Main content area
    PluginListView pluginListView;
    HostedPluginView hostedPluginView;

    // State
    bool browserMode = true;  // true = show browser, false = show hosted plugin fullscreen
    bool wasScanning = false;  // Track scanning state for layout updates
    bool isLoadingPlugin = false;  // True while a plugin is being loaded
    juce::String loadingPluginName;  // Name of plugin being loaded
    DisplayCategory currentCategory = DisplayCategory::All;
    int currentSubcategory = -1;  // -1 = all
    Era currentEra = Era::Era_Unknown;  // Unknown = all
    juce::String currentSearchText;
    std::unique_ptr<PluginInfo> selectedPlugin;  // Currently selected plugin in browser
    juce::Array<PluginInfo> currentFilteredPlugins;  // Current filtered plugin list for auto-selection

    // Logo
    std::unique_ptr<juce::Drawable> logoDrawable;
    void loadLogo();

    // Window sizing
    juce::Rectangle<int> defaultBrowserSize { 0, 0, 1200, 900 };
    void resizeForPlugin();
    void resizeForBrowser();

    // Layout
    static constexpr int sidebarWidth = 180;
    static constexpr int bannerHeight = 50;
    static constexpr int topBarHeight = 48;
    static constexpr int hostedPluginMinHeight = 300;
    static constexpr int logoWidth = 140;
    static constexpr int logoHeight = 26;
    static constexpr int hostedPluginHeaderHeight = 36;

    // Custom look and feel for buttons
    ButtonLookAndFeel buttonLookAndFeel;
    BrandComboBoxLookAndFeel brandComboBoxLookAndFeel;
    SettingsButtonLookAndFeel settingsButtonLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherEditor)
};

} // namespace PALauncher
