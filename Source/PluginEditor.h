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
#include "UI/PluginChainView.h"
#include "Core/PresetManager.h"

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

// Custom LookAndFeel for save button with floppy disk icon
class SaveButtonLookAndFeel : public ButtonLookAndFeel
{
public:
    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                        bool isMouseOverButton, bool isButtonDown) override
    {
        // Draw floppy disk icon instead of text
        auto buttonBounds = button.getLocalBounds().toFloat();

        // Make icon square based on button height
        float size = buttonBounds.getHeight() * 0.6f;  // Icon size
        float x = buttonBounds.getCentreX() - size / 2.0f;
        float y = buttonBounds.getCentreY() - size / 2.0f;

        g.setColour(button.findColour(isButtonDown ? juce::TextButton::textColourOnId
                                                    : juce::TextButton::textColourOffId)
                        .withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

        // Floppy disk icon (square)
        // Main body
        juce::Path diskPath;
        diskPath.addRoundedRectangle(x, y, size, size, 1.5f);
        g.strokePath(diskPath, juce::PathStrokeType(1.5f));

        // Top tab (label area)
        juce::Rectangle<float> tab(x + size * 0.15f, y, size * 0.7f, size * 0.25f);
        g.fillRect(tab);

        // Bottom shutter
        juce::Rectangle<float> shutter(x + size * 0.15f, y + size * 0.6f, size * 0.7f, size * 0.15f);
        g.fillRect(shutter);

        // Center circle (spindle hole)
        float centerX = x + size / 2.0f;
        float centerY = y + size / 2.0f + size * 0.1f;
        g.fillEllipse(centerX - size * 0.08f, centerY - size * 0.08f, size * 0.16f, size * 0.16f);
    }
};

// Custom A/B switch component - single toggle button that looks like segmented control
class ABSwitchComponent : public juce::Component
{
public:
    std::function<void()> onClick;

    void setActiveSlot(bool isSlotB)
    {
        if (slotBActive != isSlotB)
        {
            slotBActive = isSlotB;
            repaint();
        }
    }

    bool isSlotBActive() const { return slotBActive; }

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        float halfWidth = bounds.getWidth() / 2.0f;
        float cornerSize = 4.0f;

        auto leftBounds = bounds.withWidth(halfWidth);
        auto rightBounds = bounds.withLeft(bounds.getX() + halfWidth);

        // Determine colors based on active slot and hover state
        auto activeColour = juce::Colour(0xff0cbff2);   // Cyan
        auto inactiveColour = juce::Colour(0xff3a3a3a); // Dark

        if (isMouseOver())
        {
            activeColour = activeColour.brighter(0.1f);
            inactiveColour = inactiveColour.brighter(0.1f);
        }
        if (isMouseButtonDown())
        {
            activeColour = activeColour.darker(0.2f);
            inactiveColour = inactiveColour.darker(0.2f);
        }

        // Draw left side (A) - rounded on left, flat on right
        juce::Path leftPath;
        leftPath.addRoundedRectangle(leftBounds.getX(), leftBounds.getY(),
                                      leftBounds.getWidth(), leftBounds.getHeight(),
                                      cornerSize, cornerSize,
                                      true, false, true, false);
        g.setColour(slotBActive ? inactiveColour : activeColour);
        g.fillPath(leftPath);

        // Draw right side (B) - flat on left, rounded on right
        juce::Path rightPath;
        rightPath.addRoundedRectangle(rightBounds.getX(), rightBounds.getY(),
                                       rightBounds.getWidth(), rightBounds.getHeight(),
                                       cornerSize, cornerSize,
                                       false, true, false, true);
        g.setColour(slotBActive ? activeColour : inactiveColour);
        g.fillPath(rightPath);

        // Draw text
        auto font = juce::Font(getHeight() * 0.5f, juce::Font::bold);
        g.setFont(font);

        // A text
        g.setColour(slotBActive ? juce::Colours::grey : juce::Colours::white);
        g.drawText("A", leftBounds.toNearestInt(), juce::Justification::centred);

        // B text
        g.setColour(slotBActive ? juce::Colours::white : juce::Colours::grey);
        g.drawText("B", rightBounds.toNearestInt(), juce::Justification::centred);
    }

    void mouseUp(const juce::MouseEvent& e) override
    {
        if (contains(e.getPosition()) && onClick)
            onClick();
    }

    void mouseEnter(const juce::MouseEvent&) override { repaint(); }
    void mouseExit(const juce::MouseEvent&) override { repaint(); }
    void mouseDown(const juce::MouseEvent&) override { repaint(); }

private:
    bool slotBActive = false;
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

// Custom LookAndFeel for chain button with LED glow effect
class ChainButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void setGlowAlpha(float alpha) { glowAlpha = alpha; }

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

        // Draw LED glow effect if glowAlpha > 0
        if (glowAlpha > 0.0f)
        {
            auto glowColour = juce::Colour(0xff0cbff2).withAlpha(glowAlpha * 0.7f);

            // Outer glow
            for (int i = 0; i < 3; ++i)
            {
                float offset = (i + 1) * 2.0f;
                auto glowBounds = bounds.expanded(offset);
                g.setColour(glowColour.withAlpha(glowAlpha * (0.3f - i * 0.1f)));
                g.drawRoundedRectangle(glowBounds, 4.0f + offset, 2.0f);
            }
        }
    }

private:
    float glowAlpha = 0.0f;
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

        // Only show background on hover or press
        if (isButtonDown || isMouseOverButton)
        {
            auto baseColour = backgroundColour;
            if (isButtonDown)
                baseColour = baseColour.darker(0.2f);
            else
                baseColour = baseColour.brighter(0.15f);

            g.setColour(baseColour);
            g.fillRoundedRectangle(bounds, 4.0f);
        }
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
                        bool isMouseOverButton, bool isButtonDown) override
    {
        // Draw gear/cog icon
        auto bounds = button.getLocalBounds().toFloat();
        auto cx = bounds.getCentreX();
        auto cy = bounds.getCentreY();
        auto size = juce::jmin(bounds.getWidth(), bounds.getHeight()) * 0.4f;

        g.setColour(button.findColour(juce::TextButton::textColourOffId));

        // Draw gear with 8 rectangular teeth (constant width)
        juce::Path gearPath;
        const int numTeeth = 8;
        const float outerRadius = size * 0.88f;
        const float innerRadius = size * 0.66f;
        const float toothWidth = size * 0.28f;  // Constant width for teeth
        const float toothStep = juce::MathConstants<float>::twoPi / numTeeth;

        // Start at the first tooth
        float startAngle = -juce::MathConstants<float>::halfPi;  // Start from top

        // Calculate perpendicular offset for constant-width teeth
        auto toothPoint = [&](float angle, float radius, float perpOffset) {
            float px = cx + std::cos(angle) * radius - std::sin(angle) * perpOffset;
            float py = cy + std::sin(angle) * radius + std::cos(angle) * perpOffset;
            return juce::Point<float>(px, py);
        };

        auto firstPt = toothPoint(startAngle, outerRadius, -toothWidth * 0.5f);
        gearPath.startNewSubPath(firstPt.x, firstPt.y);

        for (int i = 0; i < numTeeth; ++i)
        {
            float toothAngle = startAngle + i * toothStep;
            float nextToothAngle = startAngle + (i + 1) * toothStep;

            // Right edge of tooth tip (outer radius)
            auto p1 = toothPoint(toothAngle, outerRadius, toothWidth * 0.5f);
            gearPath.lineTo(p1.x, p1.y);

            // Right edge of tooth base (inner radius) - same perpendicular offset
            auto p2 = toothPoint(toothAngle, innerRadius, toothWidth * 0.5f);
            gearPath.lineTo(p2.x, p2.y);

            // Left edge of next tooth base (inner radius)
            auto p3 = toothPoint(nextToothAngle, innerRadius, -toothWidth * 0.5f);
            gearPath.lineTo(p3.x, p3.y);

            // Left edge of next tooth tip (outer radius)
            auto p4 = toothPoint(nextToothAngle, outerRadius, -toothWidth * 0.5f);
            gearPath.lineTo(p4.x, p4.y);
        }
        gearPath.closeSubPath();

        g.fillPath(gearPath);

        // Draw center hole - use button background when hovered, top bar color otherwise
        float holeRadius = size * 0.30f;
        if (isMouseOverButton || isButtonDown)
        {
            auto bgColour = button.findColour(juce::TextButton::buttonColourId);
            if (isButtonDown)
                bgColour = bgColour.darker(0.2f);
            else
                bgColour = bgColour.brighter(0.15f);
            g.setColour(bgColour);
        }
        else
        {
            g.setColour(juce::Colour(0xff1a1a1a));  // Top bar background color
        }
        g.fillEllipse(cx - holeRadius, cy - holeRadius, holeRadius * 2.0f, holeRadius * 2.0f);
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
    void toggleABSlot();  // Toggle between A and B plugin slots
    void refreshPresetDropdown();  // Rebuild preset dropdown menu
    void loadPresetFromFile(juce::File presetFile);  // Load a preset from file

    PluginAllianceLauncherProcessor& processor;
    PresetManager presetManager;
    juce::PopupMenu currentPresetMenu;  // Current preset menu

    // Subscription banner
    juce::Label subscriptionLabel;
    juce::TextButton subscribeButton;

    // Top bar components
    SearchBar searchBar;
    ABSwitchComponent abSwitch;     // A/B comparison toggle
    juce::TextButton chainButton;    // Toggle chain view visibility
    juce::ComboBox presetComboBox;     // Preset dropdown menu
    juce::TextButton presetSaveButton; // Save preset button
    juce::TextButton rescanButton;
    juce::TextButton settingsButton;
    juce::TextButton toggleModeButton;
    juce::TextButton unloadButton;

    // Settings menu
    void showSettingsMenu();

    // Sidebar components (inside scrollable viewport)
    juce::Viewport sidebarViewport;
    juce::Component sidebarContent;
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
    PluginChainView chainView;

    // State
    bool browserMode = true;  // true = show browser, false = show hosted plugin fullscreen
    bool chainViewVisible = true;  // true = chain view visible, false = hidden
    bool wasScanning = false;  // Track scanning state for layout updates
    bool isLoadingPlugin = false;  // True while a plugin is being loaded
    juce::String loadingPluginName;  // Name of plugin being loaded
    DisplayCategory currentCategory = DisplayCategory::All;
    int currentSubcategory = -1;  // -1 = all
    Era currentEra = Era::Era_Unknown;  // Unknown = all
    juce::String currentSearchText;
    bool showOnlyInstalled = false;  // If true, only show installed plugins
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
    static constexpr int chainViewHeight = 150;  // Reduced height for compact chain view
    static constexpr int hostedPluginMinHeight = 300;
    static constexpr int logoWidth = 140;
    static constexpr int logoHeight = 26;
    static constexpr int hostedPluginHeaderHeight = 0;  // Header removed, unload button now in top bar

    // Custom look and feel for buttons
    ButtonLookAndFeel buttonLookAndFeel;
    SaveButtonLookAndFeel saveButtonLookAndFeel;
    BrandComboBoxLookAndFeel brandComboBoxLookAndFeel;
    ChainButtonLookAndFeel chainButtonLookAndFeel;
    SettingsButtonLookAndFeel settingsButtonLookAndFeel;

    // LED glow animation state
    float chainButtonGlowPhase = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginAllianceLauncherEditor)
};

} // namespace PALauncher
