/*
  ==============================================================================
    PluginEditor.cpp
    Plugin Alliance Launcher - Main Plugin Editor UI Implementation
  ==============================================================================
*/

#include "PluginEditor.h"
#include "Utils/PluginImageCache.h"
#include "Data/PluginData.h"

// Pulled in for the "Audio/MIDI Settings..." menu item in standalone builds.
// StandalonePluginHolder::getInstance() returns nullptr when not running
// inside the JUCE standalone wrapper, so the same code is safe in VST3.
#include <juce_audio_plugin_client/Standalone/juce_StandaloneFilterWindow.h>

namespace PALauncher
{

// Details-pane layout constants shared by resized() and computeAdBounds().
// padding + brand + gap + name + gap + image + gap + tags + gap
static constexpr int kDetailsFixedTopBlock = 16 + 18 + 4 + 24 + 16 + 180 + 17 + 22 + 8;
static constexpr int kDetailsSidePad       = 20;
static constexpr int kDetailsBottomPad     = 12;
static constexpr int kDetailsGap           = 12;
static constexpr int kDetailsButtonHeight  = 36;

// Plugin Alliance logo SVG data
static const char* logoSvgData = R"SVG(
<svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 189 35" height="35" width="189">
<path fill="white" d="M4.38 24.13C4.38 24.9 3.75 25.53 2.96 25.53H1.42C0.65 25.53 0 24.9 0 24.13V6.63C0 5.86 0.63 5.23 1.42 5.23H2.96C3.73 5.23 4.38 5.86 4.38 6.63C4.38 6.63 4.38 24.13 4.38 24.13ZM10.01 9.55C10.01 8.78 9.38 8.15 8.59 8.15H7.07C6.3 8.15 5.65 8.78 5.65 9.55V26.77C5.65 27.54 6.28 28.17 7.07 28.17H8.61C9.38 28.17 10.03 27.54 10.03 26.77V9.55H10.02L10.01 9.55ZM15.66 5.11C15.66 4.33 15.03 3.71 14.24 3.71H12.7C11.93 3.71 11.28 4.34 11.28 5.11V24.13C11.28 24.9 11.91 25.53 12.7 25.53H14.24C15.02 25.53 15.66 24.9 15.66 24.13V5.11ZM21.31 6.63C21.31 5.86 20.68 5.23 19.89 5.23H18.35C17.58 5.23 16.93 5.86 16.93 6.63V24.14C16.93 24.91 17.56 25.54 18.35 25.54H19.89C20.66 25.54 21.31 24.91 21.31 24.14C21.31 24.14 21.31 6.63 21.31 6.63ZM26.94 6.63C26.94 5.86 26.31 5.23 25.52 5.23H23.98C23.2 5.23 22.56 5.86 22.56 6.63V26.77C22.56 27.54 23.19 28.17 23.98 28.17H25.52C26.29 28.17 26.94 27.54 26.94 26.77C26.94 26.77 26.94 6.63 26.94 6.63ZM32.59 1.4C32.59 0.63 31.96 0 31.17 0H29.63C28.86 0 28.21 0.63 28.21 1.4V24.15C28.21 24.92 28.84 25.55 29.63 25.55H31.17C31.95 25.55 32.59 24.92 32.59 24.15V1.4ZM38.22 6.63C38.22 5.86 37.59 5.23 36.8 5.23H35.28C34.51 5.23 33.86 5.86 33.86 6.63V26.77C33.86 27.54 34.49 28.17 35.28 28.17H36.82C37.59 28.17 38.24 27.54 38.24 26.77V6.63H38.23L38.22 6.63ZM43.87 6.63C43.87 5.86 43.24 5.23 42.45 5.23H40.91C40.14 5.23 39.49 5.86 39.49 6.63V24.14C39.49 24.91 40.12 25.54 40.91 25.54H42.45C43.22 25.54 43.87 24.91 43.87 24.14V6.63Z"></path>
<path fill="white" d="M51.9844 23.5737V8.21582H58.5854C61.4019 8.21582 63.0522 10.0425 63.0522 12.8369C63.0522 15.6309 61.4019 17.4575 58.5854 17.4575H54.4707V23.5737H51.9844ZM54.4707 15.2788H58.4316C59.6855 15.2788 60.4336 14.5967 60.4336 13.3647V12.3086C60.4336 11.0762 59.6855 10.3945 58.4316 10.3945H54.4707V15.2788Z"></path>
<path fill="white" d="M67.2222 23.5737C65.5938 23.5737 64.7798 22.6714 64.7798 21.1978V7.29199H67.1782V21.6157H68.7622V23.5737H67.2222Z"></path>
<path fill="white" d="M77.0454 21.6821H76.957C76.5391 22.8042 75.6372 23.8384 73.7446 23.8384C71.3906 23.8384 70.0044 22.2319 70.0044 19.4155V12.1328H72.4023V19.1074C72.4023 20.8457 73.1284 21.77 74.603 21.77C75.835 21.77 77.0454 21.1318 77.0454 19.7895V12.1328H79.4434V23.5737H77.0454V21.6821Z"></path>
<path fill="white" d="M86.2339 28.2388C82.4932 28.2388 81.041 27.2261 81.041 25.4878C81.041 24.2339 81.7891 23.5522 82.9995 23.2876V23.0454C82.1631 22.7817 81.7012 22.144 81.7012 21.2861C81.7012 20.0977 82.6255 19.5254 83.7256 19.2617V19.1738C82.3833 18.5356 81.6353 17.3252 81.6353 15.7852C81.6353 13.4526 83.2852 11.8687 86.1899 11.8687C86.96 11.8687 87.6641 11.9785 88.2583 12.2207V11.9126C88.2583 10.9004 88.7422 10.2842 89.7544 10.2842H91.5146V12.2207H89.1821V12.6826C90.2163 13.3647 90.7886 14.4648 90.7886 15.7852C90.7886 18.0952 89.1162 19.6577 86.2119 19.6577C85.6616 19.6577 85.1338 19.5918 84.7158 19.4814C84.1436 19.6797 83.6152 20.0537 83.6152 20.626C83.6152 21.2417 84.2095 21.4839 85.2217 21.4839H88.0381C90.8545 21.4839 92.0425 22.6714 92.0425 24.6519C92.0425 27.0288 90.3486 28.2388 86.2339 28.2388ZM87.708 23.6177H83.8354C83.3076 23.9263 83.0435 24.3882 83.0435 24.938C83.0435 25.8618 83.7256 26.5005 85.5078 26.5005H87.0039C88.874 26.5005 89.7983 25.9722 89.7983 24.9165C89.7983 24.1245 89.2705 23.6177 87.708 23.6177ZM88.4341 15.9829V15.543C88.4341 14.2451 87.6201 13.6069 86.2119 13.6069C84.8037 13.6069 83.9893 14.2451 83.9893 15.543V15.9829C83.9893 17.2812 84.8037 17.9194 86.2119 17.9194C87.6201 17.9194 88.4341 17.2812 88.4341 15.9829Z"></path>
<path fill="white" d="M93.0137 8.83203V8.45801C93.0137 7.73193 93.4541 7.2041 94.4438 7.2041C95.4341 7.2041 95.8521 7.73193 95.8521 8.45801V8.83203C95.8521 9.55811 95.4341 10.0864 94.4438 10.0864C93.4541 10.0864 93.0137 9.55811 93.0137 8.83203ZM93.2339 12.1328H95.6323V23.5737H93.2339V12.1328Z"></path>
<path fill="white" d="M98.1772 23.5737V12.1328H100.576V14.0249H100.686C101.17 12.7925 102.138 11.8687 103.898 11.8687C106.23 11.8687 107.616 13.4966 107.616 16.313V23.5737H105.218V16.6211C105.218 14.8389 104.536 13.937 103.062 13.937C101.808 13.937 100.576 14.5747 100.576 15.917V23.5737H98.1772Z"></path>
<path fill="white" d="M124.798 23.5737L123.412 19.4155H117.669L116.327 23.5737H113.797L119.033 8.21582H122.158L127.395 23.5737H124.798ZM120.596 10.5044H120.485L118.264 17.2812H122.796L120.596 10.5044Z"></path>
<path fill="white" d="M131.146 23.5737C129.518 23.5737 128.703 22.6714 128.703 21.1978V7.29199H131.102V21.6157H132.687V23.5737H131.146Z"></path>
<path fill="white" d="M136.567 23.5737C134.939 23.5737 134.125 22.6714 134.125 21.1978V7.29199H136.523V21.6157H138.108V23.5737H136.567Z"></path>
<path fill="white" d="M139.328 8.83203V8.45801C139.328 7.73193 139.769 7.2041 140.759 7.2041C141.749 7.2041 142.167 7.73193 142.167 8.45801V8.83203C142.167 9.55811 141.749 10.0864 140.759 10.0864C139.769 10.0864 139.328 9.55811 139.328 8.83203ZM139.548 12.1328H141.946V23.5737H139.548V12.1328Z"></path>
<path fill="white" d="M152.915 23.5737C151.661 23.5737 151.001 22.7817 150.847 21.6602H150.736C150.297 23.0903 149.064 23.8384 147.393 23.8384C145.038 23.8384 143.695 22.4961 143.695 20.4277C143.695 18.1616 145.39 16.9951 148.58 16.9951H150.648V16.0273C150.648 14.6411 149.9 13.8267 148.294 13.8267C146.952 13.8267 146.138 14.4868 145.565 15.3892L144.136 14.0908C144.884 12.8145 146.226 11.8687 148.448 11.8687C151.396 11.8687 153.047 13.3208 153.047 15.873V21.6157H154.257V23.5737H152.915ZM150.648 20.1855V18.5356H148.624C146.952 18.5356 146.138 19.0854 146.138 20.0757V20.4717C146.138 21.4839 146.886 22.0122 148.074 22.0122C149.549 22.0122 150.648 21.3081 150.648 20.1855Z"></path>
<path fill="white" d="M155.846 23.5737V12.1328H158.244V14.0249H158.354C158.839 12.7925 159.807 11.8687 161.567 11.8687C163.899 11.8687 165.285 13.4966 165.285 16.313V23.5737H162.887V16.6211C162.887 14.8389 162.205 13.937 160.73 13.937C159.477 13.937 158.244 14.5747 158.244 15.917V23.5737H155.846Z"></path>
<path fill="white" d="M167.132 17.8535C167.132 14.2007 169.024 11.8687 172.324 11.8687C174.612 11.8687 176.065 12.9907 176.747 14.6851L174.767 15.6089C174.437 14.5527 173.623 13.8706 172.324 13.8706C170.564 13.8706 169.662 15.0811 169.662 16.8413V18.8877C169.662 20.6479 170.564 21.8579 172.324 21.8579C173.711 21.8579 174.524 21.1099 175.009 19.9658L176.835 20.9336C176.087 22.8042 174.524 23.8384 172.324 23.8384C169.024 23.8384 167.132 21.5059 167.132 17.8535Z"></path>
<path fill="white" d="M177.705 17.8535C177.705 14.2007 179.707 11.8687 182.964 11.8687C186.33 11.8687 188.047 14.3989 188.047 17.5674V18.4697H180.191V18.8437C180.191 20.604 181.27 21.8579 183.206 21.8579C184.614 21.8579 185.561 21.1978 186.22 20.1416L187.628 21.5278C186.771 22.9136 185.098 23.8384 182.964 23.8384C179.707 23.8384 177.705 21.5059 177.705 17.8535ZM180.191 16.7314V16.8853H185.516V16.665C185.516 14.9048 184.548 13.7388 182.964 13.7388C181.313 13.7388 180.191 14.9712 180.191 16.7314Z"></path>
</svg>
)SVG";

PluginAllianceLauncherEditor::PluginAllianceLauncherEditor(PluginAllianceLauncherProcessor& p)
    : AudioProcessorEditor(&p), processor(p)
{
    // Route all DBG()/Logger output to a file so we can capture it for debugging
    // load-target issues. The file lives next to the project root.
    static juce::FileLogger* fileLogger = juce::FileLogger::createDateStampedLogger(
        "PluginAllianceLauncher", "launcher-debug-", ".log",
        "Plugin Alliance Launcher debug log");
    if (fileLogger != nullptr)
        juce::Logger::setCurrentLogger(fileLogger);

    // Restore the user's chosen theme BEFORE building child components so
    // every Colors:: accessor returns the right value during construction.
    ThemeManager::get().setThemeById(processor.getSettingsManager().getThemeId());
    ThemeManager::get().addListener(this);

    // Load logo
    loadLogo();

    // Load promotional ad shown in the details pane. Try a few locations so it
    // works both from the standalone in this repo and from a bundled build.
    {
        juce::File candidates[] = {
            juce::File::getSpecialLocation(juce::File::currentExecutableFile)
                .getParentDirectory().getChildFile("Resources/Images/pa_pro_ad.png"),
            juce::File("C:/Users/charl/PluginAllianceLauncher/Resources/Images/pa_pro_ad.png"),
            juce::File("C:/Users/charl/Downloads/PRO-1080x1080.png"),
        };
        for (auto& f : candidates)
        {
            if (f.existsAsFile())
            {
                promoAdImage = juce::ImageFileFormat::loadFrom(f);
                if (promoAdImage.isValid())
                    break;
            }
        }
    }

    // Wrap the ad image in an ImageButton so it's clickable. Same image for
    // all three states; slight brightness lift on hover and a dim on press
    // give the user feedback that it's interactive. resized() positions it
    // via computeAdBounds(); hidden when no plugin is selected.
    if (promoAdImage.isValid())
    {
        promoAdButton.setImages(false, true, true,
                                promoAdImage, 1.0f,  juce::Colours::transparentBlack,
                                promoAdImage, 1.0f,  juce::Colours::white.withAlpha(0.08f),
                                promoAdImage, 0.85f, juce::Colours::transparentBlack);
        promoAdButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
        promoAdButton.onClick = []()
        {
            juce::URL("https://www.plugin-alliance.com/pages/subscriptions")
                .launchInDefaultBrowser();
        };
        addAndMakeVisible(promoAdButton);
    }

    // Set up subscription banner (sticky at bottom of plugin list)
    subscriptionLabel.setText("Access all plugins for $14.99/month", juce::dontSendNotification);
    subscriptionLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    subscriptionLabel.setColour(juce::Label::textColourId, Colors::textOnDark());
    subscriptionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(subscriptionLabel);

    subscribeButton.setButtonText("Subscribe");
    subscribeButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    subscribeButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    subscribeButton.setLookAndFeel(&buttonLookAndFeel);
    subscribeButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    subscribeButton.onClick = []()
    {
        juce::URL("https://www.plugin-alliance.com/pages/subscriptions").launchInDefaultBrowser();
    };
    addAndMakeVisible(subscribeButton);

    // Set up search bar
    searchBar.onSearchChanged = [this](const juce::String& text)
    {
        // ── Easter egg: typing "ilovecats" (with or without spaces) anywhere
        //    in the search swaps the UI for the cat-asteroid game until Esc.
        if (text.removeCharacters(" ").containsIgnoreCase("ilovecats"))
        {
            searchBar.clear();
            currentSearchText.clear();
            filterPlugins();
            enterGameMode();
            return;
        }

        currentSearchText = text;

        // Switch to browser mode if user starts typing while viewing a plugin
        if (!browserMode && text.isNotEmpty())
        {
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
            resized();
        }

        filterPlugins();
    };
    addAndMakeVisible(searchBar);

    // Set up A/B switch component
    abSwitch.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    abSwitch.onClick = [this]() { toggleABSlot(); };
    addAndMakeVisible(abSwitch);

    // Set up Undo / Redo buttons - white with black text, matching the rest of the UI
    auto setupSecondaryButton = [this](juce::TextButton& b, const juce::String& text)
    {
        b.setButtonText(text);
        b.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
        b.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
        b.setLookAndFeel(&buttonLookAndFeel);
        b.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    };
    setupSecondaryButton(undoButton, "Undo");
    setupSecondaryButton(redoButton, "Redo");
    undoButton.onClick = [this]() { doUndo(); };
    redoButton.onClick = [this]() { doRedo(); };
    addAndMakeVisible(undoButton);
    addAndMakeVisible(redoButton);
    updateUndoButtonStates();

    // Set up rescan button
    rescanButton.setButtonText("Rescan");
    rescanButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    rescanButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    rescanButton.setLookAndFeel(&buttonLookAndFeel);
    rescanButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    rescanButton.onClick = [this]()
    {
        processor.getPluginScanner().startScan();
        repaint(); // Immediate visual feedback
    };
    addAndMakeVisible(rescanButton);

    // Set up settings button - gear icon
    settingsButton.setButtonText("");  // No text, just icon
    settingsButton.setColour(juce::TextButton::buttonColourId, Colors::toolbarBackground());
    settingsButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
    settingsButton.setLookAndFeel(&settingsButtonLookAndFeel);
    settingsButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    settingsButton.onClick = [this]() { showSettingsMenu(); };
    addAndMakeVisible(settingsButton);

    // Set up toggle mode button - white with black text
    toggleModeButton.setButtonText("View Plugin");
    toggleModeButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    toggleModeButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    toggleModeButton.setLookAndFeel(&buttonLookAndFeel);
    toggleModeButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    toggleModeButton.onClick = [this]() { toggleBrowserMode(); };
    addAndMakeVisible(toggleModeButton);

    // Set up unload button - same style as toggle mode button
    unloadButton.setButtonText("Remove");
    unloadButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    unloadButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    unloadButton.setLookAndFeel(&buttonLookAndFeel);
    unloadButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    unloadButton.onClick = [this]()
    {
        // Snapshot before removing so the user can undo the unload.
        pushUndoSnapshot();

        // Hide editor BEFORE unloading to prevent crash
        hostedPluginView.hidePluginEditor();

        ABSlot currentSlot = processor.getActiveSlot();
        ABSlot otherSlot = (currentSlot == ABSlot::A) ? ABSlot::B : ABSlot::A;

        // Unload the active slot
        processor.unloadPluginFromSlot(currentSlot);

        // Check if the other slot has a plugin
        if (processor.hasPluginInSlot(otherSlot))
        {
            // Switch to the other slot
            processor.setActiveSlot(otherSlot);
            hostedPluginView.setPluginHost(&processor.getActivePluginHost());
            hostedPluginView.showPluginEditor();

            // Update the loaded plugin ID
            auto* desc = processor.getActivePluginHost().getLoadedPluginDescription();
            if (desc != nullptr)
                pluginListView.setLoadedPluginId(desc->fileOrIdentifier);

            // Update A/B switch appearance
            abSwitch.setActiveSlot(processor.getActiveSlot() == ABSlot::B);

            // Resize for the new plugin
            juce::MessageManager::callAsync([this]()
            {
                resizeForPlugin();
            });
        }
        else
        {
            // No plugin in either slot - go to browser mode
            pluginListView.setLoadedPluginId({});

            // Reset A/B switch to A
            processor.setActiveSlot(ABSlot::A);
            abSwitch.setActiveSlot(false);

            // Switch back to browser mode
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
            resized();
        }
    };
    addAndMakeVisible(unloadButton);

    // Set up sidebar viewport (scrollable container for category + subcategory filters)
    sidebarViewport.setScrollBarsShown(true, false);  // Vertical scrollbar only
    sidebarViewport.setScrollBarThickness(14);  // Match the plugin list scrollbar width
    sidebarViewport.setViewedComponent(&sidebarContent, false);  // Don't delete on destruction
    sidebarViewport.getVerticalScrollBar().setLookAndFeel(&scrollBarLookAndFeel);
    // Sidebar lives on a dark background, so its scrollbar track stays dark.
    sidebarViewport.getVerticalScrollBar().setColour(
        juce::ScrollBar::trackColourId, Colors::scrollTrackOnDark());
    addAndMakeVisible(sidebarViewport);

    // Use the constant-shade cyan scrollbar in the plugin list as well.
    pluginListView.setScrollBarLookAndFeel(&scrollBarLookAndFeel);
    // Plugin list scrollbar fills the full height of the grey panel, but its
    // BLUE thumb should start visually in line with the first card row, matching
    // the gap above the sidebar's scrollbar.
    pluginListView.setScrollBarExtraTopPad(8);
    // The plugin grid background is #f9f9f9; pick a track colour that's a touch
    // darker than that so the track reads as a subtle divider, not a black bar.
    pluginListView.setScrollBarTrackColour(Colors::scrollTrackOnLight());

    // Set up category filter
    categoryFilter.onCategoryChanged = [this](DisplayCategory category)
    {
        currentCategory = category;
        subcategoryFilter.setCategory(category);
        filterPlugins();
        resized();  // Update layout to show/hide subcategory filter

        // Save last category if "Remember Last Filter" is enabled
        if (processor.getSettingsManager().getRememberLastFilter())
        {
            processor.getSettingsManager().setLastCategory(static_cast<int>(category));
            processor.getSettingsManager().save();
        }
    };
    sidebarContent.addAndMakeVisible(categoryFilter);

    // Set up subcategory filter
    subcategoryFilter.onSubcategoryChanged = [this](int subcategory)
    {
        currentSubcategory = subcategory;
        filterPlugins();
    };
    sidebarContent.addAndMakeVisible(subcategoryFilter);

    // Set up sort combo box
    sortComboBox.addItem("Brand A-Z", 1);
    sortComboBox.addItem("Brand Z-A", 2);
    sortComboBox.addItem("Name A-Z", 3);
    sortComboBox.addItem("Name Z-A", 4);
    sortComboBox.setSelectedId(1, juce::dontSendNotification);
    sortComboBox.setColour(juce::ComboBox::backgroundColourId, Colors::buttonSurface());
    sortComboBox.setColour(juce::ComboBox::textColourId, Colors::textOnDark());
    sortComboBox.setColour(juce::ComboBox::outlineColourId, Colors::buttonOutline());
    sortComboBox.setColour(juce::ComboBox::arrowColourId, Colors::textOnDark());
    sortComboBox.setLookAndFeel(&topBarComboBoxLookAndFeel);
    sortComboBox.onChange = [this]()
    {
        currentSortOrder = sortComboBox.getSelectedId() - 1;  // 0-indexed
        filterPlugins();
    };
    addAndMakeVisible(sortComboBox);

    // Set up era combo box
    eraComboBox.addItem("All Eras", 1);
    eraComboBox.addItem("1950s", 2);
    eraComboBox.addItem("1960s", 3);
    eraComboBox.addItem("1970s", 4);
    eraComboBox.addItem("1980s", 5);
    eraComboBox.addItem("1990s", 6);
    eraComboBox.addItem("2000s", 7);
    eraComboBox.addItem("2010s", 8);
    eraComboBox.addItem("2020s", 9);
    eraComboBox.addItem("Original", 10);
    eraComboBox.setSelectedId(1, juce::dontSendNotification);
    eraComboBox.setColour(juce::ComboBox::backgroundColourId, Colors::buttonSurface());
    eraComboBox.setColour(juce::ComboBox::textColourId, Colors::textOnDark());
    eraComboBox.setColour(juce::ComboBox::outlineColourId, Colors::buttonOutline());
    eraComboBox.setColour(juce::ComboBox::arrowColourId, Colors::textOnDark());
    eraComboBox.setLookAndFeel(&topBarComboBoxLookAndFeel);
    eraComboBox.onChange = [this]()
    {
        int selected = eraComboBox.getSelectedId();
        switch (selected)
        {
            case 1: currentEra = Era::Era_Unknown; break;  // All
            case 2: currentEra = Era::Era_1950s; break;
            case 3: currentEra = Era::Era_1960s; break;
            case 4: currentEra = Era::Era_1970s; break;
            case 5: currentEra = Era::Era_1980s; break;
            case 6: currentEra = Era::Era_1990s; break;
            case 7: currentEra = Era::Era_2000s; break;
            case 8: currentEra = Era::Era_2010s; break;
            case 9: currentEra = Era::Era_2020s; break;
            case 10: currentEra = Era::Era_Original; break;
            default: currentEra = Era::Era_Unknown; break;
        }
        filterPlugins();

        // Save last era if "Remember Last Filter" is enabled
        if (processor.getSettingsManager().getRememberLastFilter())
        {
            processor.getSettingsManager().setLastEra(static_cast<int>(currentEra));
            processor.getSettingsManager().save();
        }
    };
    addAndMakeVisible(eraComboBox);

    // Set up brand combo box
    brandComboBox.addItem("All Brands", 1);
    brandComboBox.addItem("ACME Audio", 2);
    brandComboBox.addItem("ADA", 3);
    brandComboBox.addItem("ADPTR Audio", 4);
    brandComboBox.addItem("AMEK", 5);
    brandComboBox.addItem("Ampeg", 6);
    brandComboBox.addItem("Bettermaker", 7);
    brandComboBox.addItem("Black Box Analog Design", 8);
    brandComboBox.addItem("Brainworx", 9);
    brandComboBox.addItem("Chandler Limited", 10);
    brandComboBox.addItem("Cut Classic", 11);
    brandComboBox.addItem("Dangerous Music", 12);
    brandComboBox.addItem("Diezel", 13);
    brandComboBox.addItem("DS Audio", 14);
    brandComboBox.addItem("elysia", 15);
    brandComboBox.addItem("ENGL", 16);
    brandComboBox.addItem("fiedler audio", 17);
    brandComboBox.addItem("Focusrite", 18);
    brandComboBox.addItem("Friedman", 19);
    brandComboBox.addItem("Fuchs", 20);
    brandComboBox.addItem("Gallien-Krueger", 21);
    brandComboBox.addItem("Harris Doyle", 22);
    brandComboBox.addItem("HEARS", 23);
    brandComboBox.addItem("HUM Audio Devices", 24);
    brandComboBox.addItem("Karanyi Sounds", 25);
    brandComboBox.addItem("Kiive Audio", 26);
    brandComboBox.addItem("Knif Audio", 27);
    brandComboBox.addItem("Lindell Audio", 28);
    brandComboBox.addItem("Looptrotter", 29);
    brandComboBox.addItem("Louder Than Liftoff", 30);
    brandComboBox.addItem("Maor Appelbaum & Hendyamps", 31);
    brandComboBox.addItem("Millennia", 32);
    brandComboBox.addItem("Mixland", 33);
    brandComboBox.addItem("Mäag Audio", 34);
    brandComboBox.addItem("NEOLD", 35);
    brandComboBox.addItem("Noveltech", 36);
    brandComboBox.addItem("Plugin Alliance", 37);
    brandComboBox.addItem("Pro Audio DSP", 38);
    brandComboBox.addItem("Purple Audio", 39);
    brandComboBox.addItem("Shadow Hills", 40);
    brandComboBox.addItem("Solid State Logic (SSL)", 41);
    brandComboBox.addItem("SPL", 42);
    brandComboBox.addItem("Suhr", 43);
    brandComboBox.addItem("Swivel Audio", 44);
    brandComboBox.addItem("Three-Body Technology", 45);
    brandComboBox.addItem("THX", 46);
    brandComboBox.addItem("TOMO Audiolabs", 47);
    brandComboBox.addItem("Unfiltered Audio", 48);
    brandComboBox.addItem("Vertigo", 49);
    brandComboBox.setSelectedId(1, juce::dontSendNotification);
    brandComboBox.setColour(juce::ComboBox::backgroundColourId, Colors::buttonSurface());
    brandComboBox.setColour(juce::ComboBox::textColourId, Colors::textOnDark());
    brandComboBox.setColour(juce::ComboBox::outlineColourId, Colors::buttonOutline());
    brandComboBox.setColour(juce::ComboBox::arrowColourId, Colors::textOnDark());
    brandComboBox.setLookAndFeel(&brandComboBoxLookAndFeel);
    brandComboBox.onChange = [this]()
    {
        if (brandComboBox.getSelectedId() == 1)
            currentBrandFilter = "";
        else
            currentBrandFilter = brandComboBox.getText();
        filterPlugins();
    };
    addAndMakeVisible(brandComboBox);

    // Set up details panel load button
    detailsLoadButton.setButtonText("Load Plugin");
    detailsLoadButton.setColour(juce::TextButton::buttonColourId, Colors::ctaButton());  // Charcoal (default) / burnt orange (70s)
    detailsLoadButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
    detailsLoadButton.setLookAndFeel(&buttonLookAndFeel);
    detailsLoadButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    detailsLoadButton.onClick = [this]()
    {
        if (selectedPlugin != nullptr)
            loadSelectedPlugin(*selectedPlugin);
    };
    addAndMakeVisible(detailsLoadButton);

    // Set up plugin list view
    pluginListView.onPluginSelected = [this](const PluginInfo& info)
    {
        // Store the selected plugin
        selectedPlugin = std::make_unique<PluginInfo>(info);
        // Update details panel image
        detailsPluginImage = PluginImageCache::getInstance().getImage(info.description.name);
        // Update button state and repaint details panel
        resized();
        repaint();
    };

    pluginListView.onPluginDoubleClick = [this](const PluginInfo& info)
    {
        loadSelectedPlugin(info);
    };

    pluginListView.onFavoriteToggle = [this](const PluginInfo& info, bool favorite)
    {
        // Embedded catalog entries are keyed by JSON id, not by format+fileOrIdentifier,
        // so resolve via description match inside the database.
        processor.getPluginDatabase().setFavorite(info.description, favorite);
        processor.getPluginDatabase().saveToDisk();
        refreshPluginsPreservingScroll(); // Refresh without resetting scroll position
    };
    addAndMakeVisible(pluginListView);

    // Load-target banner - sits above the plugin list when the user has clicked
    // an empty A/B host on a chain slot, so the next "Load" goes to that target
    // instead of the next + slot.
    loadTargetBanner.setJustificationType(juce::Justification::centred);
    loadTargetBanner.setColour(juce::Label::backgroundColourId, Colors::appBackground());  // matches sidebar
    loadTargetBanner.setColour(juce::Label::textColourId, Colors::textOnDark());
    loadTargetBanner.setFont(juce::Font(13.0f, juce::Font::bold));
    loadTargetBanner.setVisible(false);
    addAndMakeVisible(loadTargetBanner);

    // Set up hosted plugin view - use active plugin host
    hostedPluginView.setPluginHost(&processor.getActivePluginHost());
    addAndMakeVisible(hostedPluginView);

    // Set up chain button - same style as other buttons
    chainButton.setButtonText("Chain");
    chainButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
    chainButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
    chainButton.setLookAndFeel(&buttonLookAndFeel);
    chainButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    chainButton.onClick = [this]()
    {
        chainViewVisible = !chainViewVisible;
        chainView.setVisible(chainViewVisible);

        // Change background color instead of text
        if (chainViewVisible)
        {
            chainButton.setColour(juce::TextButton::buttonColourId, Colors::accent());  // Cyan when visible
            chainButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
        }
        else
        {
            chainButton.setColour(juce::TextButton::buttonColourId, Colors::cardBackground());
            chainButton.setColour(juce::TextButton::textColourOffId, Colors::textOnLight());
        }

        // In plugin mode, resize the window to fit chain + plugin
        // In browser mode, just re-layout (chain pushes content down)
        if (!browserMode)
            resizeForPlugin();

        resized();
        // Force a full editor repaint. resized() alone only marks the chainView's
        // own bounds dirty, so the editor's paint() (which draws the right
        // details panel using a chainOffset-aware Y) wouldn't otherwise run, and
        // the old details panel pixels would linger below the chain view.
        repaint();
    };
    addAndMakeVisible(chainButton);

    // Set up chain view
    chainView.onSlotSelected = [this](int slot)
    {
        // Selecting a different slot cancels any pending "load into A/B host" target.
        if (pendingLoadTarget.has_value() && pendingLoadTarget->slotIndex != slot)
            clearPendingLoadTarget();

        processor.setCurrentSelectedSlot(slot);
        // setPluginHost() already builds the editor via refreshEditor();
        // a redundant showPluginEditor() call would rebuild it again.
        hostedPluginView.setPluginHost(&processor.getChainSlot(slot).getActiveHost());

        // Update A/B switch to reflect selected slot's state
        ABSlot slotAB = processor.getSlotActiveAB(slot);
        abSwitch.setActiveSlot(slotAB == ABSlot::B);

        if (!browserMode)
            resizeForPlugin();
    };

    chainView.onRemoveSlot = [this](int slot)
    {
        clearPendingLoadTarget();
        pushUndoSnapshot();

        // Tear down any open editor for this slot before the plugin instance is
        // destroyed - the editor holds back-references to its processor and would
        // be left dangling otherwise.
        hostedPluginView.hidePluginEditor();

        processor.removeAndCompactSlot(slot);
        chainView.setChainState(processor);

        // If no plugins left, go to browser mode
        if (processor.getLoadedSlotCount() == 0)
        {
            pluginListView.setLoadedPluginId({});
            abSwitch.setActiveSlot(false);
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
            resized();
        }
    };

    chainView.onAddSlot = [this]()
    {
        // Clicking + targets the next empty chain slot. Mark it active (cyan
        // border around the + button + banner) and switch to the browser so the
        // user can pick a plugin. The next Load click will land in this slot.
        int nextEmpty = -1;
        for (int i = 0; i < kMaxChainSlots; ++i)
        {
            if (!processor.hasPluginInSlot(i))
            {
                nextEmpty = i;
                break;
            }
        }
        if (nextEmpty == -1)
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Chain Full",
                "All 8 chain slots are filled. Remove a plugin before adding a new one.",
                "OK");
            return;
        }

        pendingLoadTarget = LoadTarget{ nextEmpty, ABSlot::A };
        chainView.setAddButtonHighlighted(true);
        updateLoadTargetBanner();

        if (!browserMode)
        {
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
        }
        juce::Component::unfocusAllComponents();
        resized();
    };

    chainView.onToggleAB = [this](int slotIndex, ABSlot newSlot)
    {
        // PluginChainView::handleToggleAB has already pushed the new A/B
        // state and selection into the processor and updated card visuals
        // incrementally - no setChainState() needed here.
        abSwitch.setActiveSlot(newSlot == ABSlot::B);

        auto& slot = processor.getChainSlot(slotIndex);
        auto& activeHost = (newSlot == ABSlot::A) ? slot.hostA : slot.hostB;

        if (activeHost.hasLoadedPlugin())
        {
            // setPluginHost() internally calls refreshEditor() ->
            // showPluginEditor(), so don't call showPluginEditor() again -
            // doing so destroys and recreates the just-built plugin editor.
            clearPendingLoadTarget();
            hostedPluginView.setPluginHost(&activeHost);
            if (!browserMode)
                resizeForPlugin();
        }
        else
        {
            // Empty host - the next Load click should target THIS slot/host (not the next + slot).
            pendingLoadTarget = LoadTarget{ slotIndex, newSlot };
            updateLoadTargetBanner();

            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
            // Actively remove keyboard focus from the search bar so its blinking
            // caret doesn't appear - the user is browsing, not typing a query.
            juce::Component::unfocusAllComponents();
            resized();
        }
    };

    chainView.onSlotViewPlugin = [this](int slotIndex)
    {
        // Double-clicking a chain slot's image should open that plugin's editor.
        auto& slot = processor.getChainSlot(slotIndex);
        auto& activeHost = slot.getActiveHost();
        if (!activeHost.hasLoadedPlugin())
            return;

        processor.setCurrentSelectedSlot(slotIndex);
        chainView.setChainState(processor);
        clearPendingLoadTarget();

        // setPluginHost() already creates the editor via refreshEditor();
        // don't call showPluginEditor() again.
        hostedPluginView.setPluginHost(&activeHost);

        ABSlot slotAB = processor.getSlotActiveAB(slotIndex);
        abSwitch.setActiveSlot(slotAB == ABSlot::B);

        if (browserMode)
        {
            defaultBrowserSize = getBounds();
            browserMode = false;
            toggleModeButton.setButtonText("Browser");
        }
        resized();
        juce::MessageManager::callAsync([this]() { resizeForPlugin(); });
    };

    chainView.onSlotReorder = [this](int fromIndex, int toIndex)
    {
        pushUndoSnapshot();
        processor.reorderSlots(fromIndex, toIndex);
        processor.updateParameterDistribution();
        chainView.setChainState(processor);
    };

    chainView.onAutoGainToggled = [this](int slotIndex, bool enabled)
    {
        if (slotIndex >= 0 && slotIndex < kMaxChainSlots)
        {
            processor.setSlotAutoGain(slotIndex, enabled);
        }
    };

    addAndMakeVisible(chainView);

    // Set up preset dropdown
    presetComboBox.setTextWhenNothingSelected("Default");
    presetComboBox.setTextWhenNoChoicesAvailable("No Presets");
    presetComboBox.setColour(juce::ComboBox::backgroundColourId, Colors::buttonSurface());
    presetComboBox.setColour(juce::ComboBox::textColourId, Colors::textOnDark());
    presetComboBox.setColour(juce::ComboBox::outlineColourId, Colors::buttonOutline());
    presetComboBox.setColour(juce::ComboBox::arrowColourId, Colors::textOnDark());
    presetComboBox.setLookAndFeel(&topBarComboBoxLookAndFeel);
    presetComboBox.onChange = [this]()
    {
        int selectedId = presetComboBox.getSelectedId();
        if (selectedId > 0)
        {
            auto presetFile = presetManager.getPresetFileById(selectedId);
            if (presetFile.existsAsFile())
                loadPresetFromFile(presetFile);
        }
    };
    addAndMakeVisible(presetComboBox);

    // Set up preset save button with floppy disk icon (no background)
    presetSaveButton.setButtonText("");  // No text, icon only
    presetSaveButton.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    presetSaveButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
    presetSaveButton.setLookAndFeel(&saveButtonLookAndFeel);
    presetSaveButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    presetSaveButton.onClick = [this]()
    {
        // Check if chain has any plugins
        if (processor.getLoadedSlotCount() == 0)
        {
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::InfoIcon,
                "Empty Chain",
                "Cannot save an empty chain. Load some plugins first.",
                "OK"
            );
            return;
        }

        auto chooserFlags = juce::FileBrowserComponent::saveMode
                          | juce::FileBrowserComponent::canSelectFiles
                          | juce::FileBrowserComponent::warnAboutOverwriting;

        auto* fileChooser = new juce::FileChooser("Save Chain Preset",
                                                    presetManager.getPresetsDirectory(),
                                                    "*.palpreset");

        fileChooser->launchAsync(chooserFlags, [this, fileChooser](const juce::FileChooser& fc)
        {
            auto file = fc.getResult();

            if (file != juce::File())
            {
                auto chainState = processor.getChainState();

                if (presetManager.savePreset(*chainState, file))
                {
                    refreshPresetDropdown();

                    juce::AlertWindow::showMessageBoxAsync(
                        juce::AlertWindow::InfoIcon,
                        "Preset Saved",
                        "Chain preset saved successfully:\n" + file.getFileNameWithoutExtension(),
                        "OK"
                    );
                }
                else
                {
                    juce::AlertWindow::showMessageBoxAsync(
                        juce::AlertWindow::WarningIcon,
                        "Save Failed",
                        "Could not save preset file.",
                        "OK"
                    );
                }
            }

            delete fileChooser;
        });
    };
    addAndMakeVisible(presetSaveButton);

    // Initial preset scan
    refreshPresetDropdown();

    // Listen to scanner for updates
    processor.getPluginScanner().addChangeListener(this);

    // Load database and set initial plugin list
    processor.getPluginDatabase().loadFromDisk();

    // Load settings
    showOnlyInstalled = processor.getSettingsManager().getShowOnlyInstalled();

    // Restore last filter if "Remember Last Filter" is enabled
    if (processor.getSettingsManager().getRememberLastFilter())
    {
        int lastCategory = processor.getSettingsManager().getLastCategory();
        int lastEra = processor.getSettingsManager().getLastEra();

        if (lastCategory >= 0 && lastCategory < static_cast<int>(DisplayCategory::Other) + 1)
        {
            currentCategory = static_cast<DisplayCategory>(lastCategory);
            categoryFilter.setSelectedCategory(currentCategory);
            subcategoryFilter.setCategory(currentCategory);
        }

        if (lastEra > 0)  // Only restore if a specific era was saved (not "All Eras" / Unknown)
        {
            currentEra = static_cast<Era>(lastEra);
            eraComboBox.setSelectedId(lastEra + 1, juce::dontSendNotification);
        }
    }

    // Ensure era combo box always has a valid selection (default to "All Eras")
    if (eraComboBox.getSelectedId() == 0)
        eraComboBox.setSelectedId(1, juce::dontSendNotification);

    updatePluginList();

    // Auto-scan on startup if enabled
    if (processor.getSettingsManager().getAutoScanOnStartup())
    {
        processor.getPluginScanner().startScan();
    }

    // Timer for scan progress updates
    startTimer(100);

    // Check if a plugin is already loaded (e.g., when reopening the editor or restoring state)
    if (processor.hasLoadedPlugin())
    {
        // Switch to plugin mode
        browserMode = false;
        toggleModeButton.setButtonText("Browser");

        // Update A/B switch appearance based on current active slot
        abSwitch.setActiveSlot(processor.getActiveSlot() == ABSlot::B);

        // Set the loaded plugin ID so it shows as loaded in the browser
        auto* desc = processor.getActivePluginHost().getLoadedPluginDescription();
        if (desc != nullptr)
            pluginListView.setLoadedPluginId(desc->fileOrIdentifier);
    }

    // Set editor size - wider to accommodate details panel
    // Chain view pushes content down within the window, doesn't extend it
    setSize(1400, 900);
    setResizable(true, false);
    // Minimum width ensures 2 plugin columns in browser mode
    static constexpr int minBrowserWidth = sidebarWidth + 2 * (PluginCard::preferredWidth + 6) + detailsPanelWidth + 14 + 20;
    setResizeLimits(minBrowserWidth, 600, 2200, 1500);

    // Defer hosted plugin editor creation to avoid audio stutter on window open
    // Creating the hosted plugin's GUI can be heavy, so do it after the window is shown
    if (!browserMode)
    {
        juce::MessageManager::callAsync([this]()
        {
            hostedPluginView.showPluginEditor();
            resizeForPlugin();
        });
    }
}

PluginAllianceLauncherEditor::~PluginAllianceLauncherEditor()
{
    // Drop our LookAndFeel from anything that uses it before its members are destroyed.
    // (LookAndFeel members are declared after the components, so they would be destroyed
    // first - leaving children with dangling L&F pointers.)
    sidebarViewport.getVerticalScrollBar().setLookAndFeel(nullptr);
    pluginListView.setScrollBarLookAndFeel(nullptr);

    subscribeButton.setLookAndFeel(nullptr);
    undoButton.setLookAndFeel(nullptr);
    redoButton.setLookAndFeel(nullptr);
    rescanButton.setLookAndFeel(nullptr);
    settingsButton.setLookAndFeel(nullptr);
    toggleModeButton.setLookAndFeel(nullptr);
    unloadButton.setLookAndFeel(nullptr);
    brandComboBox.setLookAndFeel(nullptr);
    sortComboBox.setLookAndFeel(nullptr);
    eraComboBox.setLookAndFeel(nullptr);
    presetComboBox.setLookAndFeel(nullptr);
    detailsLoadButton.setLookAndFeel(nullptr);
    chainButton.setLookAndFeel(nullptr);
    presetSaveButton.setLookAndFeel(nullptr);

    ThemeManager::get().removeListener(this);
    processor.getPluginScanner().removeChangeListener(this);
    stopTimer();
}

void PluginAllianceLauncherEditor::themeChanged()
{
    // Re-push setColour() values that controls cache from the active theme,
    // then ask the whole tree to repaint so paint()-time Colors:: lookups
    // pick up new values too.
    applyThemedControlColours();

    // Recursively repaint every child.
    std::function<void(juce::Component&)> repaintAll = [&](juce::Component& c)
    {
        c.repaint();
        for (auto* child : c.getChildren())
            if (child != nullptr)
                repaintAll(*child);
    };
    repaintAll(*this);
}

void PluginAllianceLauncherEditor::applyTheme(const juce::String& themeId)
{
    processor.getSettingsManager().setThemeId(themeId);
    processor.getSettingsManager().save();
    ThemeManager::get().setThemeById(themeId);   // fires themeChanged() above
}

void PluginAllianceLauncherEditor::applyThemedControlColours()
{
    // Labels
    subscriptionLabel.setColour(juce::Label::textColourId,         Colors::textOnDark());
    loadTargetBanner .setColour(juce::Label::backgroundColourId,   Colors::appBackground());
    loadTargetBanner .setColour(juce::Label::textColourId,         Colors::textOnDark());

    // AlertWindow LookAndFeel caches its setColour() values at construction.
    // Re-push them so the next AlertWindow popup picks up the active theme.
    alertLookAndFeel.setColour(juce::AlertWindow::backgroundColourId, Colors::accent());
    alertLookAndFeel.setColour(juce::AlertWindow::textColourId,       Colors::textOnDark());
    alertLookAndFeel.setColour(juce::AlertWindow::outlineColourId,    Colors::accent());
    alertLookAndFeel.setColour(juce::TextButton::buttonColourId,      Colors::cardBackground());
    alertLookAndFeel.setColour(juce::TextButton::textColourOffId,     Colors::textOnLight());
    alertLookAndFeel.setColour(juce::TextButton::textColourOnId,      Colors::textOnLight());

    // "Card-style" buttons (white body, dark text in default theme)
    auto cardButton = [](juce::TextButton& b)
    {
        b.setColour(juce::TextButton::buttonColourId,    Colors::cardBackground());
        b.setColour(juce::TextButton::textColourOffId,   Colors::textOnLight());
    };
    cardButton(subscribeButton);
    cardButton(undoButton);
    cardButton(redoButton);
    cardButton(rescanButton);
    cardButton(toggleModeButton);
    cardButton(unloadButton);
    // Chain button toggles between cardBg/charcoal + cyan; reset to the
    // default (off) appearance here. The click handler retints it when on.
    cardButton(chainButton);

    // Dark-bodied buttons
    settingsButton    .setColour(juce::TextButton::buttonColourId,  Colors::toolbarBackground());
    settingsButton    .setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
    detailsLoadButton .setColour(juce::TextButton::buttonColourId,  Colors::ctaButton());
    detailsLoadButton .setColour(juce::TextButton::textColourOffId, Colors::textOnDark());

    // ComboBoxes
    auto styleCombo = [](juce::ComboBox& cb)
    {
        cb.setColour(juce::ComboBox::backgroundColourId, Colors::buttonSurface());
        cb.setColour(juce::ComboBox::textColourId,       Colors::textOnDark());
        cb.setColour(juce::ComboBox::outlineColourId,    Colors::buttonOutline());
        cb.setColour(juce::ComboBox::arrowColourId,      Colors::textOnDark());
    };
    styleCombo(sortComboBox);
    styleCombo(eraComboBox);
    styleCombo(brandComboBox);
    styleCombo(presetComboBox);

    // Save (floppy) button stays transparent; text colour follows theme.
    presetSaveButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());

    // Scrollbars
    sidebarViewport.getVerticalScrollBar()
                   .setColour(juce::ScrollBar::trackColourId, Colors::scrollTrackOnDark());
    pluginListView.setScrollBarTrackColour(Colors::scrollTrackOnLight());
}

void PluginAllianceLauncherEditor::enterGameMode()
{
    if (gameActive)
        return;
    gameActive = true;
    hideMainUI (true);

    processor.loadGameSfxResources();    // first-time load (no-op afterwards)
    processor.startGameMusic();
    processor.setGameActive(true);       // bypass the plugin chain while playing

    catGame = std::make_unique<CatGameComponent> (processor.getMidiKeyboardState(),
                                                  &processor.getSettingsManager());
    catGame->onExitRequested = [this]() { exitGameMode(); };
    catGame->onSfxRequested  = [this] (CatGameComponent::Sfx s)
    {
        using GS = CatGameComponent::Sfx;
        using ES = GameSfxEngine::Sound;
        ES mapped = ES::Hit;
        switch (s)
        {
            case GS::Shoot:       mapped = ES::Shoot;       break;
            case GS::Hit:         mapped = ES::Hit;         break;
            case GS::Powerup:     mapped = ES::Powerup;     break;
            case GS::BossHit:     mapped = ES::BossHit;     break;
            case GS::BossKill:    mapped = ES::BossKill;    break;
            case GS::ShieldBlock: mapped = ES::ShieldBlock; break;
            case GS::LifeLost:    mapped = ES::LifeLost;    break;
            case GS::GameOver:    mapped = ES::GameOver;    break;
        }
        processor.triggerGameSfx (mapped);
    };
    addAndMakeVisible (catGame.get());
    catGame->setBounds (getLocalBounds());
    catGame->toFront (true);
    catGame->grabKeyboardFocus();   // so Esc gets here
}

void PluginAllianceLauncherEditor::exitGameMode()
{
    if (! gameActive)
        return;
    gameActive = false;
    processor.stopGameMusic();
    processor.setGameActive(false);      // resume normal chain processing
    if (catGame != nullptr)
    {
        removeChildComponent (catGame.get());
        catGame.reset();
    }
    hideMainUI (false);
    resized();
}

void PluginAllianceLauncherEditor::hideMainUI (bool hide)
{
    // Hide/show every top-level child while the game overlay owns the view.
    // We don't dig into hostedPluginView's children - it manages itself.
    const bool show = ! hide;
    for (auto* c : getChildren())
    {
        if (catGame != nullptr && c == catGame.get())
            continue;
        c->setVisible (show);
    }
    if (hide)
    {
        // Force-hide a few that are conditionally shown by resized()
        detailsLoadButton.setVisible (false);
        promoAdButton    .setVisible (false);
        loadTargetBanner .setVisible (false);
    }
}

void PluginAllianceLauncherEditor::loadLogo()
{
    auto xmlDoc = juce::XmlDocument::parse(logoSvgData);
    if (xmlDoc != nullptr)
    {
        logoDrawable = juce::Drawable::createFromSVG(*xmlDoc);
    }
}

void PluginAllianceLauncherEditor::paint(juce::Graphics& g)
{
    g.fillAll(Colors::appBackground());

    // Top bar background
    g.setColour(Colors::panelBackground());
    g.fillRect(0, 0, getWidth(), topBarHeight);

    // Draw logo in sidebar area (matches blue selector width in category filter)
    if (logoDrawable != nullptr)
    {
        auto logoBounds = juce::Rectangle<float>(12.0f, 8.0f,
                                                   static_cast<float>(sidebarWidth - 24),
                                                   static_cast<float>(topBarHeight - 16));
        logoDrawable->drawWithin(g, logoBounds, juce::RectanglePlacement::centred, 1.0f);
    }

    // Browser mode UI elements
    if (browserMode)
    {
        // Details panel on the right - show if we have plugins
        bool hasPlugins = !currentFilteredPlugins.isEmpty();

        // Subscription banner at bottom - only over plugin list area, not details panel
        int bannerWidth = getWidth() - sidebarWidth - (hasPlugins ? detailsPanelWidth : 0);
        auto bannerBounds = juce::Rectangle<int>(sidebarWidth, getHeight() - bannerHeight,
                                                  bannerWidth, bannerHeight);
        g.setColour(Colors::accent());  // Brand cyan
        g.fillRect(bannerBounds);

        if (hasPlugins && selectedPlugin != nullptr)
        {
            int statusOffset = processor.getPluginScanner().isScanning() ? 28 : 0;
            int chainOffset = chainViewVisible ? chainViewHeight : 0;
            // Paint full details column white (including area that aligns with banner)
            auto detailsBounds = juce::Rectangle<int>(getWidth() - detailsPanelWidth, topBarHeight + statusOffset + chainOffset,
                                                       detailsPanelWidth, getHeight() - topBarHeight - statusOffset - chainOffset);
            paintDetailsPanel(g, detailsBounds);
        }
    }

    // Only show status area when scanning
    bool isScanning = processor.getPluginScanner().isScanning();
    if (isScanning)
    {
        int progressBarHeight = 28;
        auto statusBounds = juce::Rectangle<int>(sidebarWidth, topBarHeight, getWidth() - sidebarWidth, progressBarHeight);

        // Background for status area
        g.setColour(Colors::panelBackground());
        g.fillRect(statusBounds);

        // Use statusBounds directly since it's already positioned correctly
        auto contentStatusBounds = statusBounds;

        auto statusMessage = processor.getPluginScanner().getStatusMessage();

        // Progress track area - align left edge with search bar (no left padding)
        auto trackBounds = contentStatusBounds.withTrimmedTop(6).withTrimmedBottom(6).withTrimmedRight(10);
        g.setColour(Colors::toolbarBackground());
        g.fillRoundedRectangle(trackBounds.toFloat(), 4.0f);

        // Progress bar fill
        float progress = processor.getPluginScanner().getProgress();
        auto progressBounds = trackBounds.withWidth(static_cast<int>(trackBounds.getWidth() * progress));
        g.setColour(Colors::accent());
        g.fillRoundedRectangle(progressBounds.toFloat(), 4.0f);

        // Status text
        if (!statusMessage.isEmpty())
        {
            g.setColour(Colors::textOnDark());
            g.setFont(juce::Font(11.0f));
            g.drawText(statusMessage, trackBounds.reduced(8, 0), juce::Justification::centredLeft);
        }
    }

    // Loading overlay - shown when loading a plugin
    if (isLoadingPlugin)
    {
        // Semi-transparent overlay over the content area
        auto overlayBounds = getLocalBounds().withTop(topBarHeight);
        g.setColour(Colors::appBackground().withAlpha(0.87f));  // Dark semi-transparent
        g.fillRect(overlayBounds);

        // Loading text
        g.setColour(Colors::textOnDark());
        g.setFont(juce::Font(18.0f, juce::Font::bold));

        juce::String loadingText = "Loading " + loadingPluginName + "...";
        g.drawText(loadingText, overlayBounds, juce::Justification::centred);

        // Animated dots would require timer-based repainting, so keep it simple
    }

}

void PluginAllianceLauncherEditor::paintOverChildren(juce::Graphics& g)
{
    // Default theme only: 1px divider under the chain, full window width, in
    // the scrollbar-track grey. Painted AFTER the children so the browser and
    // the details pane don't overdraw it. 70s already has enough contrast.
    if (chainViewVisible && ThemeManager::get().current().id == "default")
    {
        const int statusOffset = processor.getPluginScanner().isScanning() ? 28 : 0;
        const int dividerY     = topBarHeight + statusOffset + chainViewHeight;
        g.setColour(Colors::scrollTrackOnLight());
        g.fillRect(0, dividerY, getWidth(), 1);
    }
}

void PluginAllianceLauncherEditor::resized()
{
    // Easter-egg game takes the whole view when active.
    if (gameActive && catGame != nullptr)
    {
        catGame->setBounds (getLocalBounds());
        return;
    }

    // Keep the settings overlay covering the full editor area.
    if (settingsPanel != nullptr)
        settingsPanel->setBounds (getLocalBounds());

    auto bounds = getLocalBounds();

    // Top bar - always visible
    auto topBar = bounds.removeFromTop(topBarHeight);
    topBar.reduce(10, 8);

    // Skip sidebar area (logo is there)
    topBar.removeFromLeft(sidebarWidth - 10);  // -10 because we already reduced by 10

    // Undo / Redo buttons - sit immediately after the logo, visible in both modes.
    undoButton.setBounds(topBar.removeFromLeft(60));
    topBar.removeFromLeft(4);
    redoButton.setBounds(topBar.removeFromLeft(60));
    topBar.removeFromLeft(12);
    undoButton.setVisible(true);
    redoButton.setVisible(true);

    // Settings button (gear icon) - rightmost
    settingsButton.setBounds(topBar.removeFromRight(36));
    topBar.removeFromRight(8);

    // Button logic:
    // - In plugin mode: show "Browser", "Chain", "Remove", and A/B switch; hide search and rescan
    // - In browser mode: show search, rescan, "Browser", "Chain", and A/B switch
    if (!browserMode)
    {
        // Hide search bar and rescan in plugin mode
        searchBar.setVisible(false);
        rescanButton.setVisible(false);

        // A/B switch (rightmost)
        abSwitch.setVisible(true);
        abSwitch.setBounds(topBar.removeFromRight(56));
        topBar.removeFromRight(8);

        // Remove button
        unloadButton.setVisible(true);
        unloadButton.setBounds(topBar.removeFromRight(70));
        topBar.removeFromRight(8);

        // Chain button
        chainButton.setVisible(true);
        chainButton.setBounds(topBar.removeFromRight(70));
        topBar.removeFromRight(8);

        // Browser button
        toggleModeButton.setButtonText("Browser");
        toggleModeButton.setVisible(true);
        toggleModeButton.setBounds(topBar.removeFromRight(80));
        topBar.removeFromRight(8);
    }
    else
    {
        // Show search bar and rescan in browser mode
        searchBar.setVisible(true);
        rescanButton.setVisible(true);

        // A/B switch (rightmost)
        abSwitch.setVisible(true);
        abSwitch.setBounds(topBar.removeFromRight(56));
        topBar.removeFromRight(8);

        // Chain button
        chainButton.setVisible(true);
        chainButton.setBounds(topBar.removeFromRight(70));
        topBar.removeFromRight(8);

        // Rescan button
        rescanButton.setBounds(topBar.removeFromRight(80));
        topBar.removeFromRight(8);

        // Show Browser/Plugin toggle if a plugin is loaded
        if (processor.getLoadedSlotCount() > 0)
        {
            toggleModeButton.setButtonText("View Plugin");
            toggleModeButton.setVisible(true);
            toggleModeButton.setBounds(topBar.removeFromRight(100));
            topBar.removeFromRight(8);
        }
        else
        {
            toggleModeButton.setVisible(false);
        }

        unloadButton.setVisible(false);

        searchBar.setBounds(topBar.removeFromLeft(300));
    }

    // Era, Brand, and Sort dropdowns in top bar (right of search, in browser mode)
    if (browserMode)
    {
        topBar.removeFromLeft(12);  // Gap after search
        eraComboBox.setBounds(topBar.removeFromLeft(100));
        topBar.removeFromLeft(8);
        brandComboBox.setBounds(topBar.removeFromLeft(160));
        topBar.removeFromLeft(8);
        sortComboBox.setBounds(topBar.removeFromLeft(100));
    }

    // Center preset controls in the top bar (only in plugin mode)
    if (!browserMode)
    {
        auto fullTopBar = getLocalBounds().removeFromTop(topBarHeight).reduced(10, 8);
        int presetDropdownWidth = 120;
        int saveButtonWidth = 60;
        int spacing = 4;
        int totalWidth = presetDropdownWidth + spacing + saveButtonWidth;

        int centerX = fullTopBar.getCentreX() - (totalWidth / 2);
        int y = fullTopBar.getY();
        int height = fullTopBar.getHeight();

        presetComboBox.setBounds(centerX, y, presetDropdownWidth, height);
        presetComboBox.setVisible(true);
        presetSaveButton.setBounds(centerX + presetDropdownWidth + spacing, y, saveButtonWidth, height);
        presetSaveButton.setVisible(true);
    }
    else
    {
        // Hide preset controls in browser mode
        presetComboBox.setVisible(false);
        presetSaveButton.setVisible(false);
    }

    // Only reserve space for status bar when scanning
    if (processor.getPluginScanner().isScanning())
    {
        static constexpr int statusBarHeight = 28;
        bounds.removeFromTop(statusBarHeight);
    }

    // Chain view - visible in both modes (can be toggled)
    if (chainViewVisible)
    {
        auto chainArea = bounds.removeFromTop(chainViewHeight);
        chainView.setBounds(chainArea);
        chainView.setVisible(true);
    }
    else
    {
        chainView.setVisible(false);
    }

    if (browserMode)
    {
        // Show sidebar and subscription banner in browser mode
        sidebarViewport.setVisible(true);
        categoryFilter.setVisible(true);
        sortComboBox.setVisible(true);
        eraComboBox.setVisible(true);
        brandComboBox.setVisible(true);
        subscriptionLabel.setVisible(true);
        subscribeButton.setVisible(true);

        // Check if current category has subcategories
        bool hasSubcategories = (currentCategory == DisplayCategory::Compressors ||
                                 currentCategory == DisplayCategory::Equalizers ||
                                 currentCategory == DisplayCategory::GuitarAndBass ||
                                 currentCategory == DisplayCategory::Other);
        subcategoryFilter.setVisible(hasSubcategories);

        auto sidebar = bounds.removeFromLeft(sidebarWidth);
        sidebar.removeFromTop(6);  // Breathing room above the sidebar (and its scrollbar)

        // Categories: 18 items * 30px row height + 8px padding
        int categoryHeight = 18 * 30 + 8;

        // Calculate subcategory height if visible
        int subcategoryHeight = hasSubcategories ? subcategoryFilter.getRequiredHeight() : 0;

        // Total content height
        int totalContentHeight = categoryHeight + subcategoryHeight;

        // Set the sidebar content size (let it be taller than viewport if needed)
        sidebarContent.setSize(sidebarWidth - 8, totalContentHeight);  // -8 for scrollbar space

        // Layout filters within the content
        categoryFilter.setBounds(0, 0, sidebarContent.getWidth(), categoryHeight);
        if (hasSubcategories)
        {
            subcategoryFilter.setBounds(0, categoryHeight, sidebarContent.getWidth(), subcategoryHeight);
        }

        // Position the viewport
        sidebarViewport.setBounds(sidebar);

        // Details panel on the right - show if we have plugins
        bool hasPlugins = !currentFilteredPlugins.isEmpty();
        if (hasPlugins && selectedPlugin != nullptr)
        {
            auto detailsPanel = bounds.removeFromRight(detailsPanelWidth);
            detailsLoadButton.setVisible(true);
            // Load button sits immediately beneath the description text;
            // the ad fills whatever space remains at the bottom of the panel.
            int buttonY = computeDetailsButtonY(detailsPanel);
            detailsLoadButton.setBounds(detailsPanel.getX() + kDetailsSidePad,
                                        buttonY,
                                        detailsPanelWidth - 2 * kDetailsSidePad,
                                        kDetailsButtonHeight);
            auto adBounds = computeAdBounds(detailsPanel);
            if (! adBounds.isEmpty())
            {
                promoAdButton.setVisible(true);
                promoAdButton.setBounds(adBounds);
            }
            else
            {
                promoAdButton.setVisible(false);
            }
        }
        else
        {
            detailsLoadButton.setVisible(false);
            promoAdButton.setVisible(false);
        }

        // Subscription banner at bottom of plugin list area (not over details panel)
        auto bannerArea = bounds.removeFromBottom(bannerHeight);
        // Center the label and button within the banner area
        int buttonWidth = 90;
        int labelWidth = 280;
        int totalWidth = labelWidth + 12 + buttonWidth;  // label + gap + button
        int startX = bannerArea.getX() + (bannerArea.getWidth() - totalWidth) / 2;
        subscriptionLabel.setBounds(startX, bannerArea.getY() + (bannerHeight - 24) / 2, labelWidth, 24);
        subscribeButton.setBounds(startX + labelWidth + 12, bannerArea.getY() + (bannerHeight - 28) / 2, buttonWidth, 28);

        // Load-target banner sits at the top of the plugin list area when active.
        if (pendingLoadTarget.has_value())
        {
            auto banner = bounds.removeFromTop(28);
            loadTargetBanner.setBounds(banner);
            loadTargetBanner.setVisible(true);
        }
        else
        {
            loadTargetBanner.setVisible(false);
        }

        // Plugin list takes the full remaining content area - the breathing room
        // above the grid is added INSIDE pluginListView so the grey background
        // extends all the way up (no dark band behind the cards).
        pluginListView.setBounds(bounds);
        pluginListView.setVisible(true);
        hostedPluginView.setVisible(false);
    }
    else
    {
        // Hide sidebar and subscription banner in plugin mode - plugin takes over entire area below top bar
        sidebarViewport.setVisible(false);
        categoryFilter.setVisible(false);
        subcategoryFilter.setVisible(false);
        sortComboBox.setVisible(false);
        eraComboBox.setVisible(false);
        brandComboBox.setVisible(false);
        pluginListView.setVisible(false);
        subscriptionLabel.setVisible(false);
        subscribeButton.setVisible(false);
        detailsLoadButton.setVisible(false);
        promoAdButton.setVisible(false);
        loadTargetBanner.setVisible(false);

        // Hosted plugin view takes the full area below top bar
        hostedPluginView.setBounds(bounds);
        hostedPluginView.setVisible(true);
    }
}

void PluginAllianceLauncherEditor::resizeForPlugin()
{
    // Get the plugin editor bounds
    auto editorBounds = hostedPluginView.getPluginEditorBounds();

    if (editorBounds.isEmpty())
        return;

    // Calculate window size: plugin size + top bar + hosted view header
    int requiredWidth = editorBounds.getWidth();
    int requiredHeight = editorBounds.getHeight() + topBarHeight + hostedPluginHeaderHeight;

    // Add chain view height if visible
    if (chainViewVisible)
        requiredHeight += chainViewHeight;

    // Top bar in plugin mode:
    //   left  : sidebar/logo (180) + Undo (60) + 4 + Redo (60) + 12   = 316
    //   right : settings (36) + 8 + A/B (56) + 8 + Remove (70) + 8
    //         + Chain (70) + 8 + Browser (80) + 8                      = 352
    //   centre: preset combo (120) + 4 + save (60)                     = 184
    //   outer padding 10 px each side                                  =  20
    // Total ~872 px - bump to 900 to leave a little breathing room so
    // adjacent buttons never visually touch.
    constexpr int kPluginModeMinWidth = 900;

    // Apply minimum sizes and constraints
    requiredWidth = juce::jmax(requiredWidth, kPluginModeMinWidth);
    requiredHeight = juce::jmax(requiredHeight, 300);

    // Limit to reasonable maximums
    requiredWidth = juce::jmin(requiredWidth, 2000);
    requiredHeight = juce::jmin(requiredHeight, 1500);

    // Temporarily remove constrainer to prevent aspect ratio enforcement
    setConstrainer(nullptr);
    setSize(requiredWidth, requiredHeight);

    // Re-apply resize limits without aspect ratio
    setResizeLimits(kPluginModeMinWidth, 300, 2200, 1500);
}

void PluginAllianceLauncherEditor::resizeForBrowser()
{
    int width = defaultBrowserSize.getWidth();
    int height = defaultBrowserSize.getHeight();

    // Browser min width matches the default launch width so all top-bar items
    // (logo + Undo + Redo + search + filters + Browser/Chain/Remove + A/B + settings)
    // are guaranteed to fit without overlap.
    const int minBrowserWidth = defaultBrowserSize.getWidth();

    // Re-apply resize limits for browser mode
    setResizeLimits(minBrowserWidth, 600, 2200, 1500);

    // Ensure current size meets the minimum
    width = juce::jmax(width, minBrowserWidth);

    setSize(width, height);
}

void PluginAllianceLauncherEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &processor.getPluginScanner())
    {
        // Scan complete - update database and plugin list
        juce::MessageManager::callAsync([this]()
        {
            auto scannedPlugins = processor.getPluginScanner().getScannedPlugins();
            processor.getPluginDatabase().updateInstalledPlugins(scannedPlugins);
            processor.getPluginDatabase().saveToDisk();
            updatePluginList();
        });
    }
}

void PluginAllianceLauncherEditor::timerCallback()
{
    bool isScanning = processor.getPluginScanner().isScanning();

    // Update layout when scanning state changes
    if (isScanning != wasScanning)
    {
        wasScanning = isScanning;
        resized();
    }

    // Repaint the status area when scanning
    if (isScanning)
        repaint(sidebarWidth, topBarHeight, getWidth() - sidebarWidth, 24);

    // Defensive chain-view resync. setChainState() destroys + recreates all
    // 17 slot/meter cards, so it's expensive - skip the rebuild when the
    // structural fingerprint (loaded plugin per A/B, bypass, A/B active,
    // selected slot) is unchanged from last tick. Also skip while dragging
    // so the dragged card doesn't disappear mid-gesture.
    static int updateCounter = 0;
    if (++updateCounter % 10 == 0
        && !juce::Desktop::getInstance().getMainMouseSource().isDragging())
    {
        juce::String sig;
        for (int i = 0; i < kMaxChainSlots; ++i)
        {
            const auto& slot = processor.getChainSlot(i);
            sig << slot.hostA.getLoadedPluginName() << '|'
                << slot.hostB.getLoadedPluginName() << '|'
                << (slot.activeSlot == ABSlot::A ? 'A' : 'B')
                << (slot.bypassed ? '1' : '0') << ';';
        }
        sig << "sel=" << processor.getCurrentSelectedSlot();
        static juce::String lastChainSig;
        if (sig != lastChainSig)
        {
            lastChainSig = sig;
            chainView.setChainState(processor);
        }
    }

    // Push auto-gain state (toggle, flashing, correction-dB readout) to the
    // output meter card for each slot. AUTO lives on the meter now.
    if (chainViewVisible)
    {
        for (int i = 0; i < kMaxChainSlots; ++i)
        {
            bool autoEnabled = processor.isSlotAutoGainEnabled(i);
            bool analyzing = processor.isSlotAutoGainAnalyzing(i);
            float correctionDb = processor.getSlotCorrectionDb(i);
            chainView.updateAutoGainState(i, autoEnabled, analyzing, correctionDb);
        }
    }

    // Animate chain button LED glow effect
    bool shouldGlow = !chainViewVisible && processor.getLoadedSlotCount() >= 2;

    if (shouldGlow)
    {
        // Breathing animation: 2 second cycle (sine wave)
        chainButtonGlowPhase += 0.05f;  // Increment per timer tick (assuming ~30 FPS)
        if (chainButtonGlowPhase > juce::MathConstants<float>::twoPi)
            chainButtonGlowPhase -= juce::MathConstants<float>::twoPi;

        float glowAlpha = 0.5f + 0.5f * std::sin(chainButtonGlowPhase);
        chainButtonLookAndFeel.setGlowAlpha(glowAlpha);
        chainButton.repaint();
    }
    else
    {
        // No glow
        chainButtonLookAndFeel.setGlowAlpha(0.0f);
        chainButtonGlowPhase = 0.0f;
    }
}

void PluginAllianceLauncherEditor::updatePluginList()
{
    filterPlugins();
}

void PluginAllianceLauncherEditor::filterPlugins()
{
    juce::Array<PluginInfo> filtered;

    // Start with appropriate base set
    if (currentCategory == DisplayCategory::Favorites)
    {
        filtered = processor.getPluginDatabase().getFavorites();
    }
    else if (currentCategory == DisplayCategory::Recent)
    {
        filtered = processor.getPluginDatabase().getRecent(20);
    }
    else if (!currentSearchText.isEmpty())
    {
        filtered = processor.getPluginDatabase().search(currentSearchText);
    }
    else if (currentCategory != DisplayCategory::All)
    {
        filtered = processor.getPluginDatabase().getByDisplayCategory(currentCategory);
    }
    else
    {
        filtered = processor.getPluginDatabase().getAllPlugins();
    }

    // Apply "show only installed" filter
    if (showOnlyInstalled)
    {
        juce::Array<PluginInfo> installedOnly;
        for (const auto& plugin : filtered)
        {
            if (plugin.isInstalled)
                installedOnly.add(plugin);
        }
        filtered = installedOnly;
    }

    // Apply era filter (unless showing all)
    if (currentEra != Era::Era_Unknown)
    {
        juce::Array<PluginInfo> eraFiltered;
        for (const auto& plugin : filtered)
        {
            if (plugin.era == currentEra)
                eraFiltered.add(plugin);
        }
        filtered = eraFiltered;
    }

    // Apply subcategory filter if set
    if (currentSubcategory >= 0)
    {
        juce::Array<PluginInfo> subFiltered;
        for (const auto& plugin : filtered)
        {
            bool matches = false;

            // Check based on current category type
            switch (currentCategory)
            {
                case DisplayCategory::Compressors:
                    matches = (static_cast<int>(plugin.compressorType) == currentSubcategory);
                    break;
                case DisplayCategory::Equalizers:
                    matches = (static_cast<int>(plugin.eqType) == currentSubcategory);
                    break;
                case DisplayCategory::Reverbs:
                    matches = (static_cast<int>(plugin.reverbType) == currentSubcategory);
                    break;
                case DisplayCategory::GuitarAndBass:
                    matches = (static_cast<int>(plugin.guitarBassType) == currentSubcategory);
                    break;
                case DisplayCategory::Saturators:
                    matches = (static_cast<int>(plugin.saturationType) == currentSubcategory);
                    break;
                case DisplayCategory::Other:
                    matches = (static_cast<int>(plugin.otherType) == currentSubcategory);
                    break;
                default:
                    matches = true;
                    break;
            }

            if (matches)
                subFiltered.add(plugin);
        }
        filtered = subFiltered;
    }

    // Apply brand filter if set
    if (currentBrandFilter.isNotEmpty())
    {
        juce::Array<PluginInfo> brandFiltered;
        for (const auto& plugin : filtered)
        {
            auto pluginBrand = getBrandName(plugin.description.name, plugin.description.manufacturerName);
            if (pluginBrand.equalsIgnoreCase(currentBrandFilter) ||
                pluginBrand == currentBrandFilter)
                brandFiltered.add(plugin);
        }
        filtered = brandFiltered;
    }

    // Apply sorting
    std::sort(filtered.begin(), filtered.end(), [this](const PluginInfo& a, const PluginInfo& b)
    {
        auto brandA = getBrandName(a.description.name, a.description.manufacturerName);
        auto brandB = getBrandName(b.description.name, b.description.manufacturerName);
        auto nameA = getDisplayName(a.description.name, brandA);
        auto nameB = getDisplayName(b.description.name, brandB);

        switch (currentSortOrder)
        {
            case 0:  // Brand A-Z
                if (brandA.compareIgnoreCase(brandB) != 0)
                    return brandA.compareIgnoreCase(brandB) < 0;
                return nameA.compareIgnoreCase(nameB) < 0;
            case 1:  // Brand Z-A
                if (brandA.compareIgnoreCase(brandB) != 0)
                    return brandA.compareIgnoreCase(brandB) > 0;
                return nameA.compareIgnoreCase(nameB) < 0;
            case 2:  // Name A-Z
                return nameA.compareIgnoreCase(nameB) < 0;
            case 3:  // Name Z-A
                return nameA.compareIgnoreCase(nameB) > 0;
            default:
                return brandA.compareIgnoreCase(brandB) < 0;
        }
    });

    pluginListView.setPlugins(filtered);

    // Store the current filtered list for auto-selection
    currentFilteredPlugins = filtered;

    // Always select the first plugin when filter changes
    if (!filtered.isEmpty())
    {
        selectedPlugin = std::make_unique<PluginInfo>(filtered[0]);
        detailsPluginImage = PluginImageCache::getInstance().getImage(filtered[0].description.name);
        pluginListView.selectPluginAtIndex(0);  // Also select in list view for visual feedback
    }
    else
    {
        // Clear selection if no plugins
        selectedPlugin.reset();
        detailsPluginImage = juce::Image();
    }

    // Always trigger layout update
    resized();
    repaint();
}

void PluginAllianceLauncherEditor::refreshPluginsPreservingScroll()
{
    // Same filtering logic as filterPlugins, but uses updatePlugins to preserve scroll position
    juce::Array<PluginInfo> filtered;

    if (currentCategory == DisplayCategory::Favorites)
        filtered = processor.getPluginDatabase().getFavorites();
    else if (currentCategory == DisplayCategory::Recent)
        filtered = processor.getPluginDatabase().getRecent(20);
    else if (!currentSearchText.isEmpty())
        filtered = processor.getPluginDatabase().search(currentSearchText);
    else if (currentCategory != DisplayCategory::All)
        filtered = processor.getPluginDatabase().getByDisplayCategory(currentCategory);
    else
        filtered = processor.getPluginDatabase().getAllPlugins();

    // Apply era filter
    if (currentEra != Era::Era_Unknown)
    {
        juce::Array<PluginInfo> eraFiltered;
        for (const auto& plugin : filtered)
        {
            if (plugin.era == currentEra)
                eraFiltered.add(plugin);
        }
        filtered = eraFiltered;
    }

    // Apply subcategory filter
    if (currentSubcategory >= 0)
    {
        juce::Array<PluginInfo> subFiltered;
        for (const auto& plugin : filtered)
        {
            bool matches = false;
            switch (currentCategory)
            {
                case DisplayCategory::Compressors:
                    matches = (static_cast<int>(plugin.compressorType) == currentSubcategory);
                    break;
                case DisplayCategory::Equalizers:
                    matches = (static_cast<int>(plugin.eqType) == currentSubcategory);
                    break;
                case DisplayCategory::Reverbs:
                    matches = (static_cast<int>(plugin.reverbType) == currentSubcategory);
                    break;
                case DisplayCategory::GuitarAndBass:
                    matches = (static_cast<int>(plugin.guitarBassType) == currentSubcategory);
                    break;
                case DisplayCategory::Saturators:
                    matches = (static_cast<int>(plugin.saturationType) == currentSubcategory);
                    break;
                case DisplayCategory::Other:
                    matches = (static_cast<int>(plugin.otherType) == currentSubcategory);
                    break;
                default:
                    matches = true;
                    break;
            }
            if (matches)
                subFiltered.add(plugin);
        }
        filtered = subFiltered;
    }

    // Apply brand filter if set
    if (currentBrandFilter.isNotEmpty())
    {
        juce::Array<PluginInfo> brandFiltered;
        for (const auto& plugin : filtered)
        {
            auto pluginBrand = getBrandName(plugin.description.name, plugin.description.manufacturerName);
            if (pluginBrand.equalsIgnoreCase(currentBrandFilter) ||
                pluginBrand == currentBrandFilter)
                brandFiltered.add(plugin);
        }
        filtered = brandFiltered;
    }

    // Apply sorting (same as filterPlugins)
    std::sort(filtered.begin(), filtered.end(), [this](const PluginInfo& a, const PluginInfo& b)
    {
        auto brandA = getBrandName(a.description.name, a.description.manufacturerName);
        auto brandB = getBrandName(b.description.name, b.description.manufacturerName);
        auto nameA = getDisplayName(a.description.name, brandA);
        auto nameB = getDisplayName(b.description.name, brandB);

        switch (currentSortOrder)
        {
            case 0:  // Brand A-Z
                if (brandA.compareIgnoreCase(brandB) != 0)
                    return brandA.compareIgnoreCase(brandB) < 0;
                return nameA.compareIgnoreCase(nameB) < 0;
            case 1:  // Brand Z-A
                if (brandA.compareIgnoreCase(brandB) != 0)
                    return brandA.compareIgnoreCase(brandB) > 0;
                return nameA.compareIgnoreCase(nameB) < 0;
            case 2:  // Name A-Z
                return nameA.compareIgnoreCase(nameB) < 0;
            case 3:  // Name Z-A
                return nameA.compareIgnoreCase(nameB) > 0;
            default:
                return brandA.compareIgnoreCase(brandB) < 0;
        }
    });

    pluginListView.updatePlugins(filtered);
}

void PluginAllianceLauncherEditor::loadSelectedPlugin(PluginInfo info)
{
    {
        juce::String s;
        s << "loadSelectedPlugin: plugin='" << info.description.name
          << "' pendingLoadTarget=" << (pendingLoadTarget.has_value()
                ? juce::String("(slot=") + juce::String(pendingLoadTarget->slotIndex)
                    + ", ab=" + (pendingLoadTarget->abSlot == ABSlot::A ? "A" : "B") + ")"
                : juce::String("<none>"))
          << " selectedSlot=" << processor.getCurrentSelectedSlot();
        juce::Logger::writeToLog(s);
    }

    // Check if the plugin is installed before attempting to load
    if (!info.isInstalled)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::InfoIcon,
            "Plugin Not Installed",
            "This plugin is not installed on your system.\n\nVisit plugin-alliance.com to purchase and download it.",
            "OK"
        );
        return;
    }

    // Resolve target slot/host:
    //   1. pendingLoadTarget (set when user clicked an empty A or B on a chain slot)
    //   2. currently selected slot's active A/B host (so re-selecting + Load replaces it)
    //   3. next empty + slot (the legacy default)
    int targetChainSlot = -1;
    ABSlot targetABSlot = ABSlot::A;

    if (pendingLoadTarget.has_value())
    {
        targetChainSlot = pendingLoadTarget->slotIndex;
        targetABSlot = pendingLoadTarget->abSlot;
    }
    else
    {
        int sel = processor.getCurrentSelectedSlot();
        if (sel >= 0 && sel < kMaxChainSlots && processor.hasPluginInSlot(sel))
        {
            // The selected chain slot has a plugin in either A or B - target its active host.
            // The user explicitly picked this slot, so a Load click means "swap THIS slot".
            targetChainSlot = sel;
            targetABSlot = processor.getSlotActiveAB(sel);
        }
        else
        {
            // Fall back to next empty + slot.
            for (int i = 0; i < kMaxChainSlots; ++i)
            {
                if (!processor.hasPluginInSlot(i))
                {
                    targetChainSlot = i;
                    break;
                }
            }
            targetABSlot = abSwitch.isSlotBActive() ? ABSlot::B : ABSlot::A;
        }
    }

    // If chain is full, show error
    if (targetChainSlot == -1)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Chain Full",
            "All 8 chain slots are filled. Remove a plugin before adding a new one.",
            "OK"
        );
        return;
    }

    // If the target host already has a plugin loaded, ask before replacing - the user
    // may have unsaved tweaks they don't want to lose.
    auto& slot = processor.getChainSlot(targetChainSlot);
    auto& targetHost = (targetABSlot == ABSlot::A) ? slot.hostA : slot.hostB;
    if (targetHost.hasLoadedPlugin())
    {
        auto* existingDesc = targetHost.getLoadedPluginDescription();
        juce::String existingName = (existingDesc != nullptr) ? existingDesc->name : juce::String("the existing plugin");
        const char abChar = (targetABSlot == ABSlot::B) ? 'B' : 'A';
        juce::String message = juce::String::formatted("Replace Slot %d (%c) ", targetChainSlot + 1, abChar)
            + existingName + " with " + info.description.name + "?";

        auto pluginCopy = info;
        int slotCopy = targetChainSlot;
        ABSlot abCopy = targetABSlot;

        auto* alertWindow = new juce::AlertWindow(
            "Replace Plugin?", message, juce::AlertWindow::NoIcon);
        alertWindow->setLookAndFeel(&alertLookAndFeel);
        alertWindow->getProperties().set("paMessage", message);
        alertWindow->addButton("Replace", 1, juce::KeyPress(juce::KeyPress::returnKey));
        alertWindow->addButton("Cancel",  0, juce::KeyPress(juce::KeyPress::escapeKey));
        // Fixed size with generous padding around the centred title + single-line message + buttons.
        alertWindow->setSize(520, 200);
        alertWindow->enterModalState(true,
            juce::ModalCallbackFunction::create([this, pluginCopy, slotCopy, abCopy](int result)
            {
                if (result == 1)
                    performLoad(pluginCopy, slotCopy, abCopy);
            }),
            true);  // deleteWhenDismissed
        return;
    }

    performLoad(info, targetChainSlot, targetABSlot);
}

void PluginAllianceLauncherEditor::loadSelectedPluginToNextEmpty(PluginInfo info)
{
    // The "+" Add button path - always target the next empty slot, regardless
    // of which slot is currently selected.
    if (!info.isInstalled)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::InfoIcon,
            "Plugin Not Installed",
            "This plugin is not installed on your system.\n\nVisit plugin-alliance.com to purchase and download it.",
            "OK"
        );
        return;
    }

    int targetChainSlot = -1;
    for (int i = 0; i < kMaxChainSlots; ++i)
    {
        if (!processor.hasPluginInSlot(i))
        {
            targetChainSlot = i;
            break;
        }
    }
    if (targetChainSlot == -1)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Chain Full",
            "All 8 chain slots are filled. Remove a plugin before adding a new one.",
            "OK"
        );
        return;
    }

    ABSlot targetABSlot = abSwitch.isSlotBActive() ? ABSlot::B : ABSlot::A;
    performLoad(info, targetChainSlot, targetABSlot);
}

void PluginAllianceLauncherEditor::performLoad(PluginInfo info, int targetChainSlot, ABSlot targetABSlot)
{
    {
        juce::String s;
        s << "performLoad: requested plugin='" << info.description.name
          << "' fileOrIdentifier='" << info.description.fileOrIdentifier
          << "' -> slot=" << targetChainSlot
          << " ab=" << (targetABSlot == ABSlot::A ? "A" : "B");
        juce::Logger::writeToLog(s);
    }

    // Snapshot before mutating the chain so the user can undo this load/replace.
    pushUndoSnapshot();

    // Consume the pending load target if it was the source of this load.
    if (pendingLoadTarget.has_value()
        && pendingLoadTarget->slotIndex == targetChainSlot
        && pendingLoadTarget->abSlot == targetABSlot)
    {
        pendingLoadTarget.reset();
        chainView.setAddButtonHighlighted(false);
        updateLoadTargetBanner();
    }

    // Show loading indicator
    isLoadingPlugin = true;
    loadingPluginName = info.description.name;
    repaint();

    auto pluginToLoad = info;
    {
        juce::String s;
        s << "performLoad: pluginToLoad COPY name='" << pluginToLoad.description.name
          << "' fileOrIdentifier='" << pluginToLoad.description.fileOrIdentifier
          << "' (info.description.name='" << info.description.name << "')";
        juce::Logger::writeToLog(s);
    }

    // Defer the actual loading to allow the UI to update with the loading indicator
    juce::MessageManager::callAsync([this, pluginToLoad, targetChainSlot, targetABSlot]()
    {
        {
            juce::String s;
            s << "performLoad async ENTRY: pluginToLoad name='" << pluginToLoad.description.name
              << "' fileOrIdentifier='" << pluginToLoad.description.fileOrIdentifier << "'";
            juce::Logger::writeToLog(s);
        }
        // IMPORTANT: Hide the current editor BEFORE loading a new plugin
        // The editor holds a reference to the AudioPluginInstance, so it must be
        // destroyed before we unload/replace the plugin instance
        hostedPluginView.hidePluginEditor();

        // Load to the target chain slot and A/B slot
        {
            juce::String s;
            s << "performLoad async: loading '" << pluginToLoad.description.name
              << "' fileOrIdentifier='" << pluginToLoad.description.fileOrIdentifier
              << "' into slot=" << targetChainSlot
              << " ab=" << (targetABSlot == ABSlot::A ? "A" : "B");
            juce::Logger::writeToLog(s);
        }
        bool success = processor.loadPluginToSlot(targetChainSlot, targetABSlot, pluginToLoad.description);
        if (success)
        {
            auto& slot = processor.getChainSlot(targetChainSlot);
            auto& host = (targetABSlot == ABSlot::A) ? slot.hostA : slot.hostB;
            auto* loadedDesc = host.getLoadedPluginDescription();
            juce::String s;
            s << "performLoad async: load OK. slot " << targetChainSlot
              << " activeAB=" << (slot.activeSlot == ABSlot::A ? "A" : "B")
              << " stored desc name='" << (loadedDesc ? loadedDesc->name : juce::String("<empty>")) << "'";
            // The instance's getName() comes from the actually-instantiated VST3,
            // so if the disk file was mislabelled or JUCE picked the wrong factory
            // out of a multi-plugin .vst3 bundle, this is where it'd show up.
            if (auto* instance = host.getLoadedPlugin())
            {
                s << " ACTUAL instance name='" << instance->getName() << "'";
                juce::PluginDescription instDesc;
                instance->fillInPluginDescription(instDesc);
                s << " ACTUAL instance fileOrIdentifier='" << instDesc.fileOrIdentifier
                  << "' uid=" << (int)instDesc.uniqueId;
            }
            juce::Logger::writeToLog(s);
        }
        else
        {
            juce::Logger::writeToLog("performLoad async: load FAILED");
        }

        // Clear loading state
        isLoadingPlugin = false;
        loadingPluginName.clear();

        if (success)
        {
            // Select the newly loaded slot AND mark the host we just loaded into
            // as the slot's active A/B - otherwise getActiveHost() would still
            // return the previously-active host (e.g. loading into B but A is
            // marked active would show A's plugin in the editor).
            processor.setCurrentSelectedSlot(targetChainSlot);
            processor.setSlotActiveAB(targetChainSlot, targetABSlot);

            // Update hosted plugin view to point to the just-loaded host
            auto& slot = processor.getChainSlot(targetChainSlot);
            auto& loadedHost = (targetABSlot == ABSlot::A) ? slot.hostA : slot.hostB;
            hostedPluginView.setPluginHost(&loadedHost);
            hostedPluginView.showPluginEditor();

            // Add to recent
            processor.getPluginDatabase().addToRecent(pluginToLoad.description);
            processor.getPluginDatabase().saveToDisk();

            // Update the plugin list to show this plugin as loaded
            pluginListView.setLoadedPluginId(pluginToLoad.description.fileOrIdentifier);

            // Update chain view to show the new plugin
            chainView.setChainState(processor);

            // Update A/B switch appearance
            abSwitch.setActiveSlot(targetABSlot == ABSlot::B);

            // Store current browser size before switching
            if (browserMode)
            {
                defaultBrowserSize = getBounds();
            }

            // Switch to plugin mode
            browserMode = false;
            toggleModeButton.setButtonText("Browser");

            // Update layout first, then resize to fit plugin
            resized();

            // Resize window to fit the loaded plugin
            juce::MessageManager::callAsync([this]()
            {
                resizeForPlugin();
            });
        }
        else
        {
            // Reset switch if load failed
            abSwitch.setActiveSlot(targetABSlot == ABSlot::B);
            repaint();  // Clear the loading overlay
            juce::AlertWindow::showMessageBoxAsync(
                juce::AlertWindow::WarningIcon,
                "Failed to Load Plugin",
                "Could not load the selected plugin.\nIt may be damaged or incompatible.",
                "OK"
            );
        }
    });
}

void PluginAllianceLauncherEditor::toggleBrowserMode()
{
    clearPendingLoadTarget();

    if (browserMode)
    {
        // Switching from browser to plugin mode
        if (processor.getLoadedSlotCount() > 0)
        {
            browserMode = false;
            toggleModeButton.setButtonText("Browser");

            hostedPluginView.setPluginHost(&processor.getChainSlot(processor.getCurrentSelectedSlot()).getActiveHost());
            hostedPluginView.showPluginEditor();
            resizeForPlugin();
            resized();
        }
    }
    else
    {
        // Switching from plugin to browser mode
        browserMode = true;
        toggleModeButton.setButtonText("View Plugin");

        // Restore browser size
        resizeForBrowser();
        resized();
    }
}

void PluginAllianceLauncherEditor::toggleABSlot()
{
    int slot = processor.getCurrentSelectedSlot();
    ABSlot currentSlot = processor.getSlotActiveAB(slot);
    ABSlot newSlot = (currentSlot == ABSlot::A) ? ABSlot::B : ABSlot::A;

    // Hide current plugin editor before switching
    hostedPluginView.hidePluginEditor();

    // Switch the A/B slot for the current selected chain slot
    processor.setSlotActiveAB(slot, newSlot);

    // Update hosted plugin view to point to the new active host
    auto& newActiveHost = processor.getChainSlot(slot).getActiveHost();
    hostedPluginView.setPluginHost(&newActiveHost);

    // Rebuild the chain view so the slot card immediately picks up the new
    // active host's plugin image. updateSlotABButton on its own only swaps the
    // A/B chip; the slot thumbnail otherwise had to wait for the next periodic
    // refresh tick before reflecting the change.
    chainView.setChainState(processor);

    // Update A/B switch appearance
    abSwitch.setActiveSlot(newSlot == ABSlot::B);

    if (newActiveHost.hasLoadedPlugin())
    {
        // New host has a plugin - show its editor.
        clearPendingLoadTarget();
        hostedPluginView.showPluginEditor();

        // Update the loaded plugin ID in the browser list
        auto* desc = newActiveHost.getLoadedPluginDescription();
        if (desc != nullptr)
            pluginListView.setLoadedPluginId(desc->fileOrIdentifier);

        // If we're in plugin mode, resize for the new plugin
        if (!browserMode)
        {
            juce::MessageManager::callAsync([this]()
            {
                resizeForPlugin();
            });
        }
    }
    else
    {
        // New host is empty - flip to the browser with the chain visible and
        // prime the "Loading into Slot N (X)" banner so the next Load click
        // targets this empty A/B host.
        pendingLoadTarget = LoadTarget{ slot, newSlot };
        updateLoadTargetBanner();

        if (!chainViewVisible)
        {
            chainViewVisible = true;
            chainView.setVisible(true);
            chainButton.setColour(juce::TextButton::buttonColourId, Colors::accent());
            chainButton.setColour(juce::TextButton::textColourOffId, Colors::textOnDark());
        }

        if (!browserMode)
        {
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
        }

        pluginListView.setLoadedPluginId({});
        juce::Component::unfocusAllComponents();
        resized();
        repaint();
    }
}

void PluginAllianceLauncherEditor::clearPendingLoadTarget()
{
    if (pendingLoadTarget.has_value())
    {
        pendingLoadTarget.reset();
        chainView.setAddButtonHighlighted(false);
        updateLoadTargetBanner();
    }
}

void PluginAllianceLauncherEditor::updateLoadTargetBanner()
{
    if (pendingLoadTarget.has_value())
    {
        const char abChar = (pendingLoadTarget->abSlot == ABSlot::B) ? 'B' : 'A';
        loadTargetBanner.setText(
            juce::String::formatted("Loading into Slot %d (%c) - Click a plugin's Load button below",
                                    pendingLoadTarget->slotIndex + 1, abChar),
            juce::dontSendNotification);
        loadTargetBanner.setVisible(true);
    }
    else
    {
        loadTargetBanner.setVisible(false);
    }
    resized();
}

void PluginAllianceLauncherEditor::pushUndoSnapshot()
{
    if (applyingUndoOrRedo)
        return;  // Don't snapshot while applying an undo/redo

    juce::MemoryBlock block;
    processor.getStateInformation(block);
    undoStack.push_back(std::move(block));
    if ((int)undoStack.size() > kUndoStackCap)
        undoStack.erase(undoStack.begin());
    redoStack.clear();  // A new branch invalidates the redo history
    updateUndoButtonStates();
}

void PluginAllianceLauncherEditor::doUndo()
{
    if (undoStack.empty())
        return;

    juce::MemoryBlock current;
    processor.getStateInformation(current);
    redoStack.push_back(std::move(current));

    auto target = std::move(undoStack.back());
    undoStack.pop_back();
    applyStateBlock(target);
    updateUndoButtonStates();
}

void PluginAllianceLauncherEditor::doRedo()
{
    if (redoStack.empty())
        return;

    juce::MemoryBlock current;
    processor.getStateInformation(current);
    undoStack.push_back(std::move(current));

    auto target = std::move(redoStack.back());
    redoStack.pop_back();
    applyStateBlock(target);
    updateUndoButtonStates();
}

void PluginAllianceLauncherEditor::applyStateBlock(const juce::MemoryBlock& block)
{
    applyingUndoOrRedo = true;

    // Tear down the visible plugin editor before swapping plugin instances.
    hostedPluginView.hidePluginEditor();
    processor.setStateInformation(block.getData(), (int)block.getSize());

    // Refresh UI to reflect the restored state.
    chainView.setChainState(processor);
    clearPendingLoadTarget();

    int sel = processor.getCurrentSelectedSlot();
    if (sel >= 0 && sel < kMaxChainSlots && processor.hasPluginInSlot(sel))
    {
        auto& slot = processor.getChainSlot(sel);
        auto& host = slot.getActiveHost();
        hostedPluginView.setPluginHost(&host);
        if (!browserMode)
            hostedPluginView.showPluginEditor();

        if (auto* desc = host.getLoadedPluginDescription())
            pluginListView.setLoadedPluginId(desc->fileOrIdentifier);

        abSwitch.setActiveSlot(processor.getSlotActiveAB(sel) == ABSlot::B);
    }
    else
    {
        pluginListView.setLoadedPluginId({});
        abSwitch.setActiveSlot(false);
        if (!browserMode)
        {
            // Nothing to show - fall back to browser
            browserMode = true;
            toggleModeButton.setButtonText("View Plugin");
            resizeForBrowser();
        }
    }

    resized();
    repaint();
    applyingUndoOrRedo = false;
}

void PluginAllianceLauncherEditor::updateUndoButtonStates()
{
    undoButton.setEnabled(!undoStack.empty());
    redoButton.setEnabled(!redoStack.empty());
}

juce::String PluginAllianceLauncherEditor::resolveDescriptionText() const
{
    if (selectedPlugin == nullptr)
        return {};
    juce::String text;
    if (auto* metadata = findPluginMetadata(selectedPlugin->description.name))
        text = metadata->description;
    if (text.isEmpty())
    {
        juce::String pluginType = selectedPlugin->description.isInstrument ? "virtual instrument" : "audio effect";
        text = "A professional " + pluginType + " from Plugin Alliance. "
               "Part of the extensive Plugin Alliance catalog of high-quality audio processing tools. "
               "Visit plugin-alliance.com for more information about this product.";
    }
    return text;
}

int PluginAllianceLauncherEditor::measureDescriptionHeight(int width) const
{
    auto text = resolveDescriptionText();
    if (text.isEmpty() || width <= 0)
        return 0;
    juce::AttributedString attrStr;
    attrStr.append(text, juce::Font(13.0f), juce::Colours::black);
    attrStr.setLineSpacing(1.2f);
    juce::TextLayout layout;
    layout.createLayout(attrStr, static_cast<float>(width));
    return static_cast<int>(std::ceil(layout.getHeight()));
}

int PluginAllianceLauncherEditor::computeDetailsButtonY(juce::Rectangle<int> detailsPanel) const
{
    const int innerWidth = detailsPanelWidth - 2 * kDetailsSidePad;
    const int descHeight = measureDescriptionHeight(innerWidth);
    return detailsPanel.getY() + kDetailsFixedTopBlock + descHeight + kDetailsGap;
}

juce::Rectangle<int> PluginAllianceLauncherEditor::computeAdBounds(juce::Rectangle<int> detailsPanel) const
{
    if (!promoAdImage.isValid())
        return {};

    const int innerWidth     = detailsPanelWidth - 2 * kDetailsSidePad;
    const int buttonY        = computeDetailsButtonY(detailsPanel);
    const int adAvailableTop = buttonY + kDetailsButtonHeight + kDetailsGap;
    const int adBottom       = detailsPanel.getBottom() - kDetailsBottomPad;
    const int available      = adBottom - adAvailableTop;
    if (available <= 0)
        return {};

    const int adHeight = juce::jmin(innerWidth, available);   // square cap
    return { detailsPanel.getX() + kDetailsSidePad,
             adBottom - adHeight,
             innerWidth, adHeight };
}

void PluginAllianceLauncherEditor::paintDetailsPanel(juce::Graphics& g, juce::Rectangle<int> bounds)
{
    if (selectedPlugin == nullptr)
        return;

    // Background - card surface
    g.setColour(Colors::cardBackground());
    g.fillRect(bounds);

    // Left border line
    g.setColour(Colors::borderSubtle());
    g.fillRect(bounds.getX(), bounds.getY(), 1, bounds.getHeight());

    auto contentBounds = bounds.reduced(20, 16);

    // Get brand and display name
    auto brandName = getBrandName(selectedPlugin->description.name, selectedPlugin->description.manufacturerName);
    auto displayName = getDisplayName(selectedPlugin->description.name, brandName);

    // Brand name
    g.setColour(Colors::textDisabled());
    g.setFont(juce::Font(13.0f));
    g.drawText(brandName, contentBounds.removeFromTop(18), juce::Justification::centredLeft);

    contentBounds.removeFromTop(4);

    // Plugin name
    g.setColour(Colors::textOnLight());
    g.setFont(juce::Font(18.0f, juce::Font::bold));
    g.drawText(displayName, contentBounds.removeFromTop(24), juce::Justification::centredLeft);

    contentBounds.removeFromTop(16);

    // Plugin image - larger display, get fresh from cache
    auto imageBounds = contentBounds.removeFromTop(180);
    auto currentImage = PluginImageCache::getInstance().getImage(selectedPlugin->description.name);
    if (currentImage.isValid())
    {
        // Draw the image centered, maintaining aspect ratio, not stretching
        g.drawImageWithin(currentImage,
                          imageBounds.getX(), imageBounds.getY(),
                          imageBounds.getWidth(), imageBounds.getHeight(),
                          juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize);
    }
    else
    {
        // Placeholder
        g.setColour(Colors::cardBackgroundBypassed());
        g.fillRoundedRectangle(imageBounds.toFloat(), 6.0f);
        g.setColour(Colors::textMuted());
        g.setFont(juce::Font(12.0f));
        g.drawText("Loading...", imageBounds, juce::Justification::centred);
    }

    contentBounds.removeFromTop(17);  // Spacing below thumbnail

    // Category and Era tags row (same as plugin card)
    auto tagRow = contentBounds.removeFromTop(22);
    int tagX = tagRow.getX();

    // Category tag
    juce::String categoryTag = getEffectCategoryName(selectedPlugin->category);
    if (!categoryTag.isEmpty() && selectedPlugin->category != EffectCategory::Unknown)
    {
        g.setColour(Colors::accent().withAlpha(0.15f));
        int tagWidth = juce::jmax(70, static_cast<int>(g.getCurrentFont().getStringWidthFloat(categoryTag) + 16));
        auto tagBounds = juce::Rectangle<int>(tagX, tagRow.getY(), tagWidth, 20);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(Colors::accent().darker(0.2f));
        g.setFont(juce::Font(12.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
        tagX += tagWidth + 6;
    }

    // Era tag
    if (selectedPlugin->era != Era::Era_Unknown)
    {
        juce::String eraTag = getEraName(selectedPlugin->era);
        g.setColour(Colors::textMuted().withAlpha(0.15f));
        int eraWidth = juce::jmax(50, static_cast<int>(g.getCurrentFont().getStringWidthFloat(eraTag) + 16));
        auto eraBounds = juce::Rectangle<int>(tagX, tagRow.getY(), eraWidth, 20);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(Colors::textDisabled());
        g.setFont(juce::Font(12.0f));
        g.drawText(eraTag, eraBounds, juce::Justification::centred);
    }

    contentBounds.removeFromTop(8);

    // Plugin description - look up from PluginData.h using VST3 reported name
    juce::String descriptionText;
    if (auto* metadata = findPluginMetadata(selectedPlugin->description.name))
        descriptionText = metadata->description;

    // Fallback description if no match found in database
    if (descriptionText.isEmpty())
    {
        juce::String pluginType = selectedPlugin->description.isInstrument ? "virtual instrument" : "audio effect";
        descriptionText = "A professional " + pluginType + " from Plugin Alliance. ";
        descriptionText += "Part of the extensive Plugin Alliance catalog of high-quality audio processing tools. ";
        descriptionText += "Visit plugin-alliance.com for more information about this product.";
    }

    g.setColour(Colors::textDisabled());
    g.setFont(juce::Font(13.0f));

    // Draw multi-line description with word wrap
    juce::AttributedString attrStr;
    attrStr.append(descriptionText, juce::Font(13.0f), Colors::textDisabled());
    attrStr.setLineSpacing(1.2f);

    juce::TextLayout textLayout;
    textLayout.createLayout(attrStr, static_cast<float>(contentBounds.getWidth()));
    textLayout.draw(g, contentBounds.toFloat());

    // The promotional ad is drawn by promoAdButton (an ImageButton child)
    // so it can handle clicks. resized() positions it at computeAdBounds().
}

// ── Settings dialog ─────────────────────────────────────────────────────────
// SettingsPanel sits in the PALauncher namespace (not anonymous) so the
// editor's `friend class SettingsPanel` declaration can find it.
class SettingsPanel : public juce::Component,
                      public ThemeManager::Listener
    {
    public:
        SettingsPanel (PluginAllianceLauncherEditor& ed, PluginAllianceLauncherProcessor& proc)
            : editor (ed), processor (proc)
        {
            setInterceptsMouseClicks (true, true);

            auto& s = processor.getSettingsManager();

            auto setSectionLabelText = [] (juce::Label& l, const juce::String& text)
            {
                l.setText (text, juce::dontSendNotification);
                l.setFont (juce::Font (12.0f, juce::Font::bold));
            };

            auto setToggleText = [] (juce::ToggleButton& tb, const juce::String& text)
            {
                tb.setButtonText (text);
                tb.setMouseCursor (juce::MouseCursor::PointingHandCursor);
            };

            auto setButtonText = [this] (juce::TextButton& b, const juce::String& text)
            {
                b.setButtonText (text);
                b.setMouseCursor (juce::MouseCursor::PointingHandCursor);
                b.setLookAndFeel (&editor.buttonLookAndFeel);
            };

            // ── General tab ────────────────────────────────────────────
            generalPanel.addAndMakeVisible (pluginListLabel);
            setSectionLabelText (pluginListLabel, "PLUGIN LIST");

            generalPanel.addAndMakeVisible (showAllPluginsToggle);
            generalPanel.addAndMakeVisible (showOnlyInstalledToggle);
            setToggleText (showAllPluginsToggle,    "Show all plugins");
            setToggleText (showOnlyInstalledToggle, "Show only installed plugins");
            showAllPluginsToggle   .setRadioGroupId (1);
            showOnlyInstalledToggle.setRadioGroupId (1);
            showAllPluginsToggle   .setToggleState (! s.getShowOnlyInstalled(), juce::dontSendNotification);
            showOnlyInstalledToggle.setToggleState (  s.getShowOnlyInstalled(), juce::dontSendNotification);
            showAllPluginsToggle.onClick = [this]
            {
                editor.showOnlyInstalled = false;
                processor.getSettingsManager().setShowOnlyInstalled (false);
                processor.getSettingsManager().save();
                editor.filterPlugins();
            };
            showOnlyInstalledToggle.onClick = [this]
            {
                editor.showOnlyInstalled = true;
                processor.getSettingsManager().setShowOnlyInstalled (true);
                processor.getSettingsManager().save();
                editor.filterPlugins();
            };

            generalPanel.addAndMakeVisible (behaviourLabel);
            setSectionLabelText (behaviourLabel, "BEHAVIOUR");
            generalPanel.addAndMakeVisible (autoScanToggle);
            generalPanel.addAndMakeVisible (rememberFilterToggle);
            setToggleText (autoScanToggle,       "Auto-scan plugin folder on startup");
            setToggleText (rememberFilterToggle, "Remember last filter selection");
            autoScanToggle      .setToggleState (s.getAutoScanOnStartup(),  juce::dontSendNotification);
            rememberFilterToggle.setToggleState (s.getRememberLastFilter(), juce::dontSendNotification);
            autoScanToggle.onClick = [this]
            {
                processor.getSettingsManager().setAutoScanOnStartup (autoScanToggle.getToggleState());
                processor.getSettingsManager().save();
            };
            rememberFilterToggle.onClick = [this]
            {
                processor.getSettingsManager().setRememberLastFilter (rememberFilterToggle.getToggleState());
                processor.getSettingsManager().save();
            };

            generalPanel.addAndMakeVisible (themeLabel);
            setSectionLabelText (themeLabel, "THEME");
            generalPanel.addAndMakeVisible (themeDefaultToggle);
            generalPanel.addAndMakeVisible (themeSeventiesToggle);
            setToggleText (themeDefaultToggle,   Themes::defaultTheme.displayName);
            setToggleText (themeSeventiesToggle, Themes::seventiesTheme.displayName);
            themeDefaultToggle   .setRadioGroupId (2);
            themeSeventiesToggle .setRadioGroupId (2);
            const auto curThemeId = ThemeManager::get().current().id;
            themeDefaultToggle  .setToggleState (curThemeId == Themes::defaultTheme.id,   juce::dontSendNotification);
            themeSeventiesToggle.setToggleState (curThemeId == Themes::seventiesTheme.id, juce::dontSendNotification);
            themeDefaultToggle.onClick = [this]
            {
                if (themeDefaultToggle.getToggleState())
                    editor.applyTheme (Themes::defaultTheme.id);
            };
            themeSeventiesToggle.onClick = [this]
            {
                if (themeSeventiesToggle.getToggleState())
                    editor.applyTheme (Themes::seventiesTheme.id);
            };

            generalPanel.addAndMakeVisible (actionsLabel);
            setSectionLabelText (actionsLabel, "ACTIONS");
            generalPanel.addAndMakeVisible (clearCacheButton);
            generalPanel.addAndMakeVisible (resetFiltersButton);
            setButtonText (clearCacheButton,   "Clear Image Cache");
            setButtonText (resetFiltersButton, "Reset All Filters");
            clearCacheButton.onClick = [this]
            {
                PluginImageCache::getInstance().clearCache();
                editor.filterPlugins();
            };
            resetFiltersButton.onClick = [this]
            {
                editor.currentCategory   = DisplayCategory::All;
                editor.currentSubcategory = -1;
                editor.currentEra        = Era::Era_Unknown;
                editor.currentBrandFilter = "";
                editor.currentSearchText  = "";
                editor.searchBar.clear();
                editor.categoryFilter.setSelectedCategory (DisplayCategory::All);
                editor.subcategoryFilter.setCategory (DisplayCategory::All);
                editor.eraComboBox.setSelectedId  (1, juce::dontSendNotification);
                editor.brandComboBox.setSelectedId (1, juce::dontSendNotification);
                editor.sortComboBox.setSelectedId  (1, juce::dontSendNotification);
                editor.currentSortOrder = 0;
                editor.filterPlugins();
            };

            // ── Audio / MIDI tab (standalone only) ──────────────────────
           #if JucePlugin_Build_Standalone
            if (auto* holder = juce::StandalonePluginHolder::getInstance())
            {
                hasAudioTab = true;
                audioSelector = std::make_unique<juce::AudioDeviceSelectorComponent>(
                    holder->deviceManager,
                    /* minInputCh  */ 0,
                    /* maxInputCh  */ 2,
                    /* minOutputCh */ 2,
                    /* maxOutputCh */ 2,
                    /* showMidiIn  */ true,
                    /* showMidiOut */ false,
                    /* stereoPairs */ true,
                    /* hideAdvanced*/ false);
                audioPanel.addAndMakeVisible (audioSelector.get());
            }
           #endif

            // ── About tab ──────────────────────────────────────────────
            aboutPanel.addAndMakeVisible (aboutVersionLabel);
            aboutVersionLabel.setText ("Plugin Alliance Launcher v1.0.0",
                                       juce::dontSendNotification);
            aboutVersionLabel.setFont (juce::Font (15.0f, juce::Font::bold));
            aboutVersionLabel.setJustificationType (juce::Justification::centred);

            aboutPanel.addAndMakeVisible (aboutBodyLabel);
            aboutBodyLabel.setText (
                "Developed by Charles Hoffman, Matt Lara, and Tolmie MacRae",
                juce::dontSendNotification);
            aboutBodyLabel.setFont (juce::Font (16.0f));
            aboutBodyLabel.setJustificationType (juce::Justification::centredTop);

            aboutPanel.addAndMakeVisible (updatesButton);
            aboutPanel.addAndMakeVisible (websiteButton);
            setButtonText (updatesButton, "Check for Updates");
            setButtonText (websiteButton, "Visit plugin-alliance.com");
            updatesButton.onClick = []
            {
                juce::URL ("https://www.plugin-alliance.com/pages/downloads").launchInDefaultBrowser();
            };
            websiteButton.onClick = []
            {
                juce::URL ("https://www.plugin-alliance.com").launchInDefaultBrowser();
            };

            // ── Tab strip ──────────────────────────────────────────────
            auto setupTab = [this] (juce::TextButton& b, const juce::String& text, int idx)
            {
                b.setButtonText (text);
                b.setClickingTogglesState (true);
                b.setRadioGroupId (200);
                b.setMouseCursor (juce::MouseCursor::PointingHandCursor);
                b.setLookAndFeel (&editor.buttonLookAndFeel);
                b.onClick = [this, idx] { showTab (idx); };
                addAndMakeVisible (b);
            };
            setupTab (tabGeneral, "General",      0);
            if (hasAudioTab)
                setupTab (tabAudio, "Audio / MIDI", 1);
            setupTab (tabAbout, "About",          hasAudioTab ? 2 : 1);

            addChildComponent (generalPanel);
            addChildComponent (audioPanel);
            addChildComponent (aboutPanel);

            // ── Done button (themed via ButtonLookAndFeel - no JUCE default grey border) ──
            closeButton.setButtonText ("Done");
            closeButton.setMouseCursor (juce::MouseCursor::PointingHandCursor);
            closeButton.setLookAndFeel (&editor.buttonLookAndFeel);
            addAndMakeVisible (closeButton);
            closeButton.onClick = [this] { editor.closeSettingsPanel(); };

            applyThemedColours();
            ThemeManager::get().addListener (this);

            cardW = 500;
            cardH = 620;
            showTab (0);
        }

        ~SettingsPanel() override
        {
            ThemeManager::get().removeListener (this);

            // Detach themed L&Fs before the editor's instance dies.
            tabGeneral        .setLookAndFeel (nullptr);
            tabAudio          .setLookAndFeel (nullptr);
            tabAbout          .setLookAndFeel (nullptr);
            closeButton       .setLookAndFeel (nullptr);
            clearCacheButton  .setLookAndFeel (nullptr);
            resetFiltersButton.setLookAndFeel (nullptr);
            updatesButton     .setLookAndFeel (nullptr);
            websiteButton     .setLookAndFeel (nullptr);
        }

        void themeChanged() override
        {
            applyThemedColours();
            repaint();
        }

        void paint (juce::Graphics& g) override
        {
            // Dim backdrop over the rest of the editor.
            g.fillAll (juce::Colours::black.withAlpha (0.55f));

            // Centred card body.
            const auto card = getCardBounds().toFloat();
            g.setColour (Colors::panelBackground());
            g.fillRoundedRectangle (card, 10.0f);
            g.setColour (Colors::accent());
            g.drawRoundedRectangle (card, 10.0f, 1.5f);

            // Plugin Alliance logo at top of the card.
            if (editor.logoDrawable != nullptr)
            {
                auto logoArea = getCardBounds().removeFromTop (kLogoStripH)
                                               .reduced (32, 14)
                                               .toFloat();
                editor.logoDrawable->drawWithin (g, logoArea,
                                                 juce::RectanglePlacement::centred, 1.0f);
            }
        }

        void mouseDown (const juce::MouseEvent& e) override
        {
            // Click outside the card dismisses the panel.
            if (! getCardBounds().contains (e.getPosition()))
                editor.closeSettingsPanel();
        }

        void resized() override
        {
            auto card = getCardBounds();
            card.removeFromTop (kLogoStripH);  // painted in paint()

            // Tab strip
            auto tabRow = card.removeFromTop (36).reduced (20, 2);
            const int tabCount = hasAudioTab ? 3 : 2;
            const int tabW     = tabRow.getWidth() / tabCount;
            tabGeneral.setBounds (tabRow.removeFromLeft (tabW).reduced (2, 0));
            if (hasAudioTab)
                tabAudio.setBounds (tabRow.removeFromLeft (tabW).reduced (2, 0));
            tabAbout.setBounds (tabRow.reduced (2, 0));

            card.removeFromTop (10);

            // Done button reserved at bottom (40px tall, comfortably wide).
            auto bottom = card.removeFromBottom (56);
            closeButton.setBounds (bottom.reduced (140, 8));

            // Content area - the three tab panels overlap here, visibility swaps.
            auto content = card.reduced (20, 4);
            generalPanel.setBounds (content);
            audioPanel  .setBounds (content);
            aboutPanel  .setBounds (content);

            layoutGeneralTab();
            layoutAboutTab();

            if (audioSelector != nullptr)
                audioSelector->setBounds (audioPanel.getLocalBounds());
        }

    private:
        void applyThemedColours()
        {
            auto themeSectionLabel = [] (juce::Label& l)
            {
                l.setColour (juce::Label::textColourId, Colors::textMuted());
            };
            themeSectionLabel (pluginListLabel);
            themeSectionLabel (behaviourLabel);
            themeSectionLabel (themeLabel);
            themeSectionLabel (actionsLabel);

            auto themeToggle = [] (juce::ToggleButton& tb)
            {
                tb.setColour (juce::ToggleButton::textColourId,         Colors::textOnDark());
                tb.setColour (juce::ToggleButton::tickColourId,         Colors::accent());
                tb.setColour (juce::ToggleButton::tickDisabledColourId, Colors::buttonOutline());
            };
            themeToggle (showAllPluginsToggle);
            themeToggle (showOnlyInstalledToggle);
            themeToggle (autoScanToggle);
            themeToggle (rememberFilterToggle);
            themeToggle (themeDefaultToggle);
            themeToggle (themeSeventiesToggle);

            auto themeSurfaceButton = [] (juce::TextButton& b)
            {
                b.setColour (juce::TextButton::buttonColourId,   Colors::buttonSurface());
                b.setColour (juce::TextButton::textColourOffId,  Colors::textOnDark());
                b.setColour (juce::TextButton::textColourOnId,   Colors::textOnDark());
            };
            themeSurfaceButton (clearCacheButton);
            themeSurfaceButton (resetFiltersButton);
            themeSurfaceButton (updatesButton);
            themeSurfaceButton (websiteButton);

            auto themeTab = [] (juce::TextButton& b)
            {
                b.setColour (juce::TextButton::buttonColourId,   Colors::buttonSurface());
                b.setColour (juce::TextButton::buttonOnColourId, Colors::accent());
                b.setColour (juce::TextButton::textColourOffId,  Colors::textOnDark());
                b.setColour (juce::TextButton::textColourOnId,   Colors::textOnDark());
            };
            themeTab (tabGeneral);
            themeTab (tabAudio);
            themeTab (tabAbout);

            closeButton.setColour (juce::TextButton::buttonColourId,  Colors::accent());
            closeButton.setColour (juce::TextButton::textColourOffId, Colors::textOnDark());
            closeButton.setColour (juce::TextButton::textColourOnId,  Colors::textOnDark());

            aboutVersionLabel.setColour (juce::Label::textColourId, Colors::textOnDark());
            aboutBodyLabel   .setColour (juce::Label::textColourId, Colors::textMuted());
        }

        void layoutGeneralTab()
        {
            auto r = generalPanel.getLocalBounds();
            constexpr int sectionGap  = 12;
            constexpr int rowHeight   = 26;
            constexpr int labelHeight = 18;

            pluginListLabel        .setBounds (r.removeFromTop (labelHeight));
            r.removeFromTop (4);
            showAllPluginsToggle   .setBounds (r.removeFromTop (rowHeight));
            showOnlyInstalledToggle.setBounds (r.removeFromTop (rowHeight));
            r.removeFromTop (sectionGap);

            behaviourLabel         .setBounds (r.removeFromTop (labelHeight));
            r.removeFromTop (4);
            autoScanToggle         .setBounds (r.removeFromTop (rowHeight));
            rememberFilterToggle   .setBounds (r.removeFromTop (rowHeight));
            r.removeFromTop (sectionGap);

            themeLabel             .setBounds (r.removeFromTop (labelHeight));
            r.removeFromTop (4);
            themeDefaultToggle     .setBounds (r.removeFromTop (rowHeight));
            themeSeventiesToggle   .setBounds (r.removeFromTop (rowHeight));
            r.removeFromTop (sectionGap);

            actionsLabel           .setBounds (r.removeFromTop (labelHeight));
            r.removeFromTop (4);
            {
                auto row = r.removeFromTop (32);
                clearCacheButton  .setBounds (row.removeFromLeft (row.getWidth() / 2 - 4));
                row.removeFromLeft (8);
                resetFiltersButton.setBounds (row);
            }
        }

        void layoutAboutTab()
        {
            auto r = aboutPanel.getLocalBounds().reduced (8, 0);
            r.removeFromTop (12);
            aboutVersionLabel.setBounds (r.removeFromTop (24));
            r.removeFromTop (12);
            aboutBodyLabel   .setBounds (r.removeFromTop (84));
            r.removeFromTop (24);
            auto row = r.removeFromTop (36);
            updatesButton.setBounds (row.removeFromLeft (row.getWidth() / 2 - 6));
            row.removeFromLeft (12);
            websiteButton.setBounds (row);
        }

        void showTab (int idx)
        {
            const int generalIdx = 0;
            const int audioIdx   = hasAudioTab ? 1 : -1;
            const int aboutIdx   = hasAudioTab ? 2 : 1;

            generalPanel.setVisible (idx == generalIdx);
            audioPanel  .setVisible (idx == audioIdx);
            aboutPanel  .setVisible (idx == aboutIdx);

            tabGeneral.setToggleState (idx == generalIdx, juce::dontSendNotification);
            if (hasAudioTab)
                tabAudio.setToggleState (idx == audioIdx, juce::dontSendNotification);
            tabAbout.setToggleState (idx == aboutIdx, juce::dontSendNotification);
        }

        juce::Rectangle<int> getCardBounds() const
        {
            return juce::Rectangle<int> (0, 0, cardW, cardH)
                       .withCentre (getLocalBounds().getCentre());
        }

        static constexpr int kLogoStripH = 72;
        int cardW = 500;
        int cardH = 620;
        bool hasAudioTab = false;

        PluginAllianceLauncherEditor& editor;
        PluginAllianceLauncherProcessor& processor;

        // Tab buttons
        juce::TextButton tabGeneral, tabAudio, tabAbout;

        // Tab content panels (lightweight containers - visibility swaps via showTab).
        juce::Component generalPanel, audioPanel, aboutPanel;

        // General tab controls
        juce::Label        pluginListLabel, behaviourLabel, themeLabel, actionsLabel;
        juce::ToggleButton showAllPluginsToggle, showOnlyInstalledToggle;
        juce::ToggleButton autoScanToggle, rememberFilterToggle;
        juce::ToggleButton themeDefaultToggle, themeSeventiesToggle;
        juce::TextButton   clearCacheButton, resetFiltersButton;

        // Audio / MIDI tab
        std::unique_ptr<juce::AudioDeviceSelectorComponent> audioSelector;

        // About tab controls
        juce::Label      aboutVersionLabel, aboutBodyLabel;
        juce::TextButton updatesButton, websiteButton;

        // Footer
        juce::TextButton closeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};

void PluginAllianceLauncherEditor::showSettingsMenu()
{
    if (settingsPanel != nullptr) return;          // already open

    settingsPanel = std::make_unique<SettingsPanel> (*this, processor);
    settingsPanel->setBounds (getLocalBounds());
    addAndMakeVisible (settingsPanel.get());
    settingsPanel->toFront (false);
}

void PluginAllianceLauncherEditor::closeSettingsPanel()
{
    settingsPanel.reset();
}

void PluginAllianceLauncherEditor::refreshPresetDropdown()
{
    // Scan presets
    presetManager.scanPresets();

    // Clear and rebuild ComboBox
    presetComboBox.clear();

    // Add "Default" as first option (ID 0, which means nothing selected)
    presetComboBox.addItem("Default", 999);

    // Build menu for hierarchical structure
    currentPresetMenu.clear();
    int idCounter = 1000;  // Start IDs at 1000

    // Build hierarchical menu from presets directory
    presetManager.buildPresetMenu(currentPresetMenu, presetManager.getPresetsDirectory(), idCounter);

    // Add flat list to combo box (for simplicity, or we can keep the popup menu approach)
    // For now, populate with preset files directly
    auto presetFiles = presetManager.getAllPresetFiles();
    for (int i = 0; i < presetFiles.size(); ++i)
    {
        auto name = presetFiles[i].getFileNameWithoutExtension();
        presetComboBox.addItem(name, 1000 + i);
    }

    // Set default selection
    presetComboBox.setSelectedId(999, juce::dontSendNotification);
}

void PluginAllianceLauncherEditor::loadPresetFromFile(juce::File presetFile)
{
    auto chainState = presetManager.loadPreset(presetFile);

    if (chainState == nullptr)
    {
        juce::AlertWindow::showMessageBoxAsync(
            juce::AlertWindow::WarningIcon,
            "Load Failed",
            "Could not load preset. The file may be corrupted or in an unsupported format.",
            "OK"
        );
        return;
    }

    // Hide current plugin editor before loading preset
    hostedPluginView.hidePluginEditor();

    // Load the chain state into the processor
    processor.setChainState(*chainState);

    // Update chain view to reflect the loaded preset
    chainView.setChainState(processor);

    // If any plugins were loaded, select the first slot and show its plugin
    if (processor.getLoadedSlotCount() > 0)
    {
        processor.setCurrentSelectedSlot(0);
        hostedPluginView.setPluginHost(&processor.getChainSlot(0).getActiveHost());

        // Update A/B switch to reflect first slot's state
        ABSlot slotAB = processor.getSlotActiveAB(0);
        abSwitch.setActiveSlot(slotAB == ABSlot::B);

        // If we're in plugin mode, show the plugin editor
        if (!browserMode && processor.hasPluginInSlot(0))
        {
            hostedPluginView.showPluginEditor();

            juce::MessageManager::callAsync([this]()
            {
                resizeForPlugin();
            });
        }
    }

    // Update UI
    resized();
    repaint();
}

} // namespace PALauncher
