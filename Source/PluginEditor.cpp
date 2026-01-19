/*
  ==============================================================================
    PluginEditor.cpp
    Plugin Alliance Launcher - Main Plugin Editor UI Implementation
  ==============================================================================
*/

#include "PluginEditor.h"
#include "Utils/PluginImageCache.h"
#include "Data/PluginData.h"

namespace PALauncher
{

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
    // Load logo
    loadLogo();

    // Set up subscription banner (sticky at bottom of plugin list)
    subscriptionLabel.setText("Access all plugins for $14.99/month", juce::dontSendNotification);
    subscriptionLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    subscriptionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    subscriptionLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(subscriptionLabel);

    subscribeButton.setButtonText("Subscribe");
    subscribeButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    subscribeButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
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
        currentSearchText = text;

        // Switch to browser mode if user starts typing while viewing a plugin
        if (!browserMode && text.isNotEmpty())
        {
            browserMode = true;
            toggleModeButton.setButtonText("Show Plugin");
            resizeForBrowser();
            resized();
        }

        filterPlugins();
    };
    addAndMakeVisible(searchBar);

    // Set up rescan button
    rescanButton.setButtonText("Rescan");
    rescanButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff0cbff2));
    rescanButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
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
    settingsButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2a2a2a));
    settingsButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    settingsButton.setLookAndFeel(&settingsButtonLookAndFeel);
    settingsButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    settingsButton.onClick = [this]() { showSettingsMenu(); };
    addAndMakeVisible(settingsButton);

    // Set up toggle mode button - white with black text
    toggleModeButton.setButtonText("Show Plugin");
    toggleModeButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    toggleModeButton.setColour(juce::TextButton::textColourOffId, juce::Colours::black);
    toggleModeButton.setLookAndFeel(&buttonLookAndFeel);
    toggleModeButton.setMouseCursor(juce::MouseCursor::PointingHandCursor);
    toggleModeButton.onClick = [this]() { toggleBrowserMode(); };
    addAndMakeVisible(toggleModeButton);

    // Set up category filter
    categoryFilter.onCategoryChanged = [this](DisplayCategory category)
    {
        currentCategory = category;
        subcategoryFilter.setCategory(category);
        filterPlugins();
        resized();  // Update layout to show/hide subcategory filter
    };
    addAndMakeVisible(categoryFilter);

    // Set up subcategory filter
    subcategoryFilter.onSubcategoryChanged = [this](int subcategory)
    {
        currentSubcategory = subcategory;
        filterPlugins();
    };
    addAndMakeVisible(subcategoryFilter);

    // Set up sort combo box
    sortComboBox.addItem("Brand A-Z", 1);
    sortComboBox.addItem("Brand Z-A", 2);
    sortComboBox.addItem("Name A-Z", 3);
    sortComboBox.addItem("Name Z-A", 4);
    sortComboBox.setSelectedId(1, juce::dontSendNotification);
    sortComboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xff2a2a2a));
    sortComboBox.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    sortComboBox.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xff3a3a3a));
    sortComboBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::white);
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
    eraComboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xff2a2a2a));
    eraComboBox.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    eraComboBox.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xff3a3a3a));
    eraComboBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::white);
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
    brandComboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xff2a2a2a));
    brandComboBox.setColour(juce::ComboBox::textColourId, juce::Colours::white);
    brandComboBox.setColour(juce::ComboBox::outlineColourId, juce::Colour(0xff3a3a3a));
    brandComboBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::white);
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
    detailsLoadButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2a2a2a));  // Dark charcoal
    detailsLoadButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
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
        // Database key is pluginFormatName + "_" + fileOrIdentifier
        auto pluginId = info.description.pluginFormatName + "_" + info.description.fileOrIdentifier;
        processor.getPluginDatabase().setFavorite(pluginId, favorite);
        processor.getPluginDatabase().saveToDisk();
        refreshPluginsPreservingScroll(); // Refresh without resetting scroll position
    };
    addAndMakeVisible(pluginListView);

    // Set up hosted plugin view
    hostedPluginView.setPluginHost(&processor.getPluginHost());
    hostedPluginView.onUnloadClicked = [this]()
    {
        // Hide editor BEFORE unloading to prevent crash
        hostedPluginView.hidePluginEditor();
        processor.unloadPlugin();

        // Clear the loaded plugin indicator
        pluginListView.setLoadedPluginId({});

        // Switch back to browser mode
        browserMode = true;
        toggleModeButton.setButtonText("Show Plugin");
        resizeForBrowser();
        resized();
    };
    addAndMakeVisible(hostedPluginView);

    // Listen to scanner for updates
    processor.getPluginScanner().addChangeListener(this);

    // Load database and set initial plugin list
    processor.getPluginDatabase().loadFromDisk();
    updatePluginList();

    // Timer for scan progress updates
    startTimer(100);

    // Check if a plugin is already loaded (e.g., when reopening the editor or restoring state)
    if (processor.hasLoadedPlugin())
    {
        // Switch to plugin mode
        browserMode = false;
        toggleModeButton.setButtonText("Show Browser");

        // Set the loaded plugin ID so it shows as loaded in the browser
        auto* desc = processor.getPluginHost().getLoadedPluginDescription();
        if (desc != nullptr)
            pluginListView.setLoadedPluginId(desc->fileOrIdentifier);
    }

    // Set editor size - wider to accommodate details panel
    setSize(1400, 900);
    setResizable(true, true);
    setResizeLimits(1000, 600, 2200, 1500);

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
    processor.getPluginScanner().removeChangeListener(this);
    stopTimer();
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
    g.fillAll(juce::Colour(0xff121212));

    // Top bar background
    g.setColour(juce::Colour(0xff1a1a1a));
    g.fillRect(0, 0, getWidth(), topBarHeight);

    // Draw logo in sidebar area (fills sidebar width)
    if (logoDrawable != nullptr)
    {
        auto logoBounds = juce::Rectangle<float>(8.0f, 8.0f,
                                                   static_cast<float>(sidebarWidth - 16),
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
        g.setColour(juce::Colour(0xff0cbff2));  // Brand cyan
        g.fillRect(bannerBounds);

        if (hasPlugins && selectedPlugin != nullptr)
        {
            int statusOffset = processor.getPluginScanner().isScanning() ? 28 : 0;
            // Paint full details column white (including area that aligns with banner)
            auto detailsBounds = juce::Rectangle<int>(getWidth() - detailsPanelWidth, topBarHeight + statusOffset,
                                                       detailsPanelWidth, getHeight() - topBarHeight - statusOffset);
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
        g.setColour(juce::Colour(0xff1a1a1a));
        g.fillRect(statusBounds);

        // Use statusBounds directly since it's already positioned correctly
        auto contentStatusBounds = statusBounds;

        auto statusMessage = processor.getPluginScanner().getStatusMessage();

        // Progress track area - align left edge with search bar (no left padding)
        auto trackBounds = contentStatusBounds.withTrimmedTop(6).withTrimmedBottom(6).withTrimmedRight(10);
        g.setColour(juce::Colour(0xff2a2a2a));
        g.fillRoundedRectangle(trackBounds.toFloat(), 4.0f);

        // Progress bar fill
        float progress = processor.getPluginScanner().getProgress();
        auto progressBounds = trackBounds.withWidth(static_cast<int>(trackBounds.getWidth() * progress));
        g.setColour(juce::Colour(0xff0cbff2));
        g.fillRoundedRectangle(progressBounds.toFloat(), 4.0f);

        // Status text
        if (!statusMessage.isEmpty())
        {
            g.setColour(juce::Colours::white);
            g.setFont(juce::Font(11.0f));
            g.drawText(statusMessage, trackBounds.reduced(8, 0), juce::Justification::centredLeft);
        }
    }

    // Loading overlay - shown when loading a plugin
    if (isLoadingPlugin)
    {
        // Semi-transparent overlay over the content area
        auto overlayBounds = getLocalBounds().withTop(topBarHeight);
        g.setColour(juce::Colour(0xdd121212));  // Dark semi-transparent
        g.fillRect(overlayBounds);

        // Loading text
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(18.0f, juce::Font::bold));

        juce::String loadingText = "Loading " + loadingPluginName + "...";
        g.drawText(loadingText, overlayBounds, juce::Justification::centred);

        // Animated dots would require timer-based repainting, so keep it simple
    }
}

void PluginAllianceLauncherEditor::resized()
{
    auto bounds = getLocalBounds();

    // Top bar - always visible
    auto topBar = bounds.removeFromTop(topBarHeight);
    topBar.reduce(10, 8);

    // Skip sidebar area (logo is there)
    topBar.removeFromLeft(sidebarWidth - 10);  // -10 because we already reduced by 10

    // Settings button (gear icon) - rightmost
    settingsButton.setBounds(topBar.removeFromRight(36));
    topBar.removeFromRight(8);

    rescanButton.setBounds(topBar.removeFromRight(80));
    topBar.removeFromRight(8);

    // Button logic:
    // - In plugin mode: show "Show Browser"
    // - In browser mode: hide (Load Plugin button is in the details panel)
    if (!browserMode)
    {
        toggleModeButton.setButtonText("Show Browser");
        toggleModeButton.setVisible(true);
        toggleModeButton.setBounds(topBar.removeFromRight(110));
        topBar.removeFromRight(8);
    }
    else
    {
        toggleModeButton.setVisible(false);
    }

    searchBar.setBounds(topBar.removeFromLeft(300));

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

    // Only reserve space for status bar when scanning
    if (processor.getPluginScanner().isScanning())
    {
        static constexpr int statusBarHeight = 28;
        bounds.removeFromTop(statusBarHeight);
    }

    if (browserMode)
    {
        // Show sidebar and subscription banner in browser mode
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
        sidebar.removeFromBottom(8);  // Only pad bottom, not top

        // Categories take most of the sidebar (more space now that era is removed)
        int categoryHeight = hasSubcategories
            ? static_cast<int>(sidebar.getHeight() * 0.6)
            : sidebar.getHeight();
        categoryFilter.setBounds(sidebar.removeFromTop(categoryHeight));

        // Subcategory filter (only if category has subcategories)
        if (hasSubcategories)
        {
            subcategoryFilter.setBounds(sidebar);
        }

        // Details panel on the right - show if we have plugins
        // If no selection but we have plugins, auto-select the first one
        if (selectedPlugin == nullptr && !currentFilteredPlugins.isEmpty())
        {
            selectedPlugin = std::make_unique<PluginInfo>(currentFilteredPlugins[0]);
            detailsPluginImage = PluginImageCache::getInstance().getImage(currentFilteredPlugins[0].description.name);
            pluginListView.selectPluginAtIndex(0);  // Also select in list view for visual feedback
        }

        bool hasPlugins = !currentFilteredPlugins.isEmpty();
        if (hasPlugins && selectedPlugin != nullptr)
        {
            auto detailsPanel = bounds.removeFromRight(detailsPanelWidth);
            detailsLoadButton.setVisible(true);
            // Position load button below content area (brand + name + image + tags + description)
            // Content starts at Y+16, then: brand(18) + gap(4) + name(24) + gap(16) + image(180) + gap(12) + tags(22) + gap(8) + description(~120) = ~420px
            int buttonY = detailsPanel.getY() + 16 + 18 + 4 + 24 + 16 + 180 + 17 + 22 + 8 + 130;  // After description area
            detailsLoadButton.setBounds(detailsPanel.getX() + 20, buttonY, detailsPanelWidth - 40, 36);
        }
        else
        {
            detailsLoadButton.setVisible(false);
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

        // Plugin list takes the remaining content area
        pluginListView.setBounds(bounds);
        pluginListView.setVisible(true);
        hostedPluginView.setVisible(false);
    }
    else
    {
        // Hide sidebar and subscription banner in plugin mode - plugin takes over entire area below top bar
        categoryFilter.setVisible(false);
        subcategoryFilter.setVisible(false);
        sortComboBox.setVisible(false);
        eraComboBox.setVisible(false);
        brandComboBox.setVisible(false);
        pluginListView.setVisible(false);
        subscriptionLabel.setVisible(false);
        subscribeButton.setVisible(false);
        detailsLoadButton.setVisible(false);

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

    // Apply minimum sizes and constraints
    requiredWidth = juce::jmax(requiredWidth, 400);
    requiredHeight = juce::jmax(requiredHeight, 300);

    // Limit to reasonable maximums
    requiredWidth = juce::jmin(requiredWidth, 2000);
    requiredHeight = juce::jmin(requiredHeight, 1500);

    setSize(requiredWidth, requiredHeight);
}

void PluginAllianceLauncherEditor::resizeForBrowser()
{
    setSize(defaultBrowserSize.getWidth(), defaultBrowserSize.getHeight());
}

void PluginAllianceLauncherEditor::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &processor.getPluginScanner())
    {
        // Scan complete - update database and plugin list
        juce::MessageManager::callAsync([this]()
        {
            auto scannedPlugins = processor.getPluginScanner().getScannedPlugins();
            processor.getPluginDatabase().updatePlugins(scannedPlugins);
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

    // Auto-select the first plugin if we have plugins but nothing selected
    if (!filtered.isEmpty() && selectedPlugin == nullptr)
    {
        selectedPlugin = std::make_unique<PluginInfo>(filtered[0]);
        detailsPluginImage = PluginImageCache::getInstance().getImage(filtered[0].description.name);
        pluginListView.selectPluginAtIndex(0);  // Also select in list view for visual feedback
    }
    // Clear selection if no plugins
    else if (filtered.isEmpty())
    {
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

void PluginAllianceLauncherEditor::loadSelectedPlugin(const PluginInfo& info)
{
    // Show loading indicator immediately
    isLoadingPlugin = true;
    loadingPluginName = info.description.name;
    repaint();

    // Store the plugin info for the async load
    auto pluginToLoad = info;

    // Defer the actual loading to allow the UI to update with the loading indicator
    juce::MessageManager::callAsync([this, pluginToLoad]()
    {
        // IMPORTANT: Hide the current editor BEFORE loading a new plugin
        // The editor holds a reference to the AudioPluginInstance, so it must be
        // destroyed before we unload/replace the plugin instance
        hostedPluginView.hidePluginEditor();

        bool success = processor.loadPlugin(pluginToLoad.description);

        // Clear loading state
        isLoadingPlugin = false;
        loadingPluginName.clear();

        if (success)
        {
            hostedPluginView.showPluginEditor();

            // Add to recent
            processor.getPluginDatabase().addToRecent(pluginToLoad.description);
            processor.getPluginDatabase().saveToDisk();

            // Update the plugin list to show this plugin as loaded
            pluginListView.setLoadedPluginId(pluginToLoad.description.fileOrIdentifier);

            // Store current browser size before switching
            if (browserMode)
            {
                defaultBrowserSize = getBounds();
            }

            // Switch to plugin mode
            browserMode = false;
            toggleModeButton.setButtonText("Show Browser");

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
    if (browserMode)
    {
        // In browser mode - if we have a selected plugin, load it
        if (selectedPlugin != nullptr)
        {
            loadSelectedPlugin(*selectedPlugin);
        }
    }
    else
    {
        // Switching from plugin to browser mode
        browserMode = true;
        toggleModeButton.setButtonText("Load Plugin");

        // Restore browser size
        resizeForBrowser();
        resized();
    }
}

void PluginAllianceLauncherEditor::paintDetailsPanel(juce::Graphics& g, juce::Rectangle<int> bounds)
{
    if (selectedPlugin == nullptr)
        return;

    // Background - white
    g.setColour(juce::Colours::white);
    g.fillRect(bounds);

    // Left border line
    g.setColour(juce::Colour(0xffe0e0e0));
    g.fillRect(bounds.getX(), bounds.getY(), 1, bounds.getHeight());

    auto contentBounds = bounds.reduced(20, 16);

    // Get brand and display name
    auto brandName = getBrandName(selectedPlugin->description.name, selectedPlugin->description.manufacturerName);
    auto displayName = getDisplayName(selectedPlugin->description.name, brandName);

    // Brand name
    g.setColour(juce::Colour(0xff666666));
    g.setFont(juce::Font(13.0f));
    g.drawText(brandName, contentBounds.removeFromTop(18), juce::Justification::centredLeft);

    contentBounds.removeFromTop(4);

    // Plugin name
    g.setColour(juce::Colour(0xff1a1a1a));
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
        g.setColour(juce::Colour(0xfff0f0f0));
        g.fillRoundedRectangle(imageBounds.toFloat(), 6.0f);
        g.setColour(juce::Colour(0xff999999));
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
        g.setColour(juce::Colour(0xff0cbff2).withAlpha(0.15f));
        int tagWidth = juce::jmax(70, static_cast<int>(g.getCurrentFont().getStringWidthFloat(categoryTag) + 16));
        auto tagBounds = juce::Rectangle<int>(tagX, tagRow.getY(), tagWidth, 20);
        g.fillRoundedRectangle(tagBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff0099cc));
        g.setFont(juce::Font(12.0f));
        g.drawText(categoryTag, tagBounds, juce::Justification::centred);
        tagX += tagWidth + 6;
    }

    // Era tag
    if (selectedPlugin->era != Era::Era_Unknown)
    {
        juce::String eraTag = getEraName(selectedPlugin->era);
        g.setColour(juce::Colour(0xff888888).withAlpha(0.15f));
        int eraWidth = juce::jmax(50, static_cast<int>(g.getCurrentFont().getStringWidthFloat(eraTag) + 16));
        auto eraBounds = juce::Rectangle<int>(tagX, tagRow.getY(), eraWidth, 20);
        g.fillRoundedRectangle(eraBounds.toFloat(), 3.0f);

        g.setColour(juce::Colour(0xff666666));
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

    g.setColour(juce::Colour(0xff444444));
    g.setFont(juce::Font(13.0f));

    // Draw multi-line description with word wrap
    juce::AttributedString attrStr;
    attrStr.append(descriptionText, juce::Font(13.0f), juce::Colour(0xff444444));
    attrStr.setLineSpacing(1.2f);

    juce::TextLayout textLayout;
    textLayout.createLayout(attrStr, static_cast<float>(contentBounds.getWidth()));
    textLayout.draw(g, contentBounds.toFloat());
}

void PluginAllianceLauncherEditor::showSettingsMenu()
{
    juce::PopupMenu menu;

    // Display Settings submenu
    juce::PopupMenu displayMenu;
    displayMenu.addItem(101, "Small Cards", true, false);
    displayMenu.addItem(102, "Medium Cards", true, true);  // Default checked
    displayMenu.addItem(103, "Large Cards", true, false);
    displayMenu.addSeparator();
    displayMenu.addItem(104, "Show Descriptions", true, true);
    menu.addSubMenu("Display", displayMenu);

    // Scan Settings submenu
    juce::PopupMenu scanMenu;
    scanMenu.addItem(201, "Auto-Scan on Startup", true, false);
    scanMenu.addSeparator();
    scanMenu.addItem(202, "Add Scan Path...");
    scanMenu.addItem(203, "Manage Scan Paths...");
    menu.addSubMenu("Scanning", scanMenu);

    // Behavior submenu
    juce::PopupMenu behaviorMenu;
    behaviorMenu.addItem(301, "Remember Last Filter", true, true);
    behaviorMenu.addItem(302, "Remember Scroll Position", true, true);
    behaviorMenu.addSeparator();
    behaviorMenu.addItem(303, "Open Links in Browser", true, true);
    menu.addSubMenu("Behavior", behaviorMenu);

    menu.addSeparator();

    // Data section
    menu.addItem(401, "Clear Image Cache");
    menu.addItem(402, "Reset All Filters");

    menu.addSeparator();

    // About section
    menu.addItem(501, "About Plugin Alliance Launcher...");
    menu.addItem(502, "Check for Updates...");

    // Show menu and handle selection
    menu.showMenuAsync(juce::PopupMenu::Options()
        .withTargetComponent(&settingsButton)
        .withMinimumWidth(180),
        [this](int result)
        {
            switch (result)
            {
                case 101: // Small cards
                case 102: // Medium cards
                case 103: // Large cards
                    // TODO: Implement card size setting
                    break;

                case 104: // Show descriptions
                    // TODO: Implement description visibility toggle
                    break;

                case 201: // Auto-scan on startup
                    // TODO: Implement auto-scan setting
                    break;

                case 202: // Add scan path
                    // TODO: Implement add scan path dialog
                    break;

                case 203: // Manage scan paths
                    // TODO: Implement scan paths manager
                    break;

                case 301: // Remember last filter
                case 302: // Remember scroll position
                case 303: // Open links in browser
                    // TODO: Implement behavior settings
                    break;

                case 401: // Clear image cache
                    PluginImageCache::getInstance().clearCache();
                    filterPlugins();  // Refresh to reload images
                    break;

                case 402: // Reset all filters
                    currentCategory = DisplayCategory::All;
                    currentSubcategory = -1;
                    currentEra = Era::Era_Unknown;
                    currentBrandFilter = "";
                    currentSearchText = "";
                    searchBar.clear();
                    categoryFilter.setSelectedCategory(DisplayCategory::All);
                    subcategoryFilter.setCategory(DisplayCategory::All);
                    eraComboBox.setSelectedId(1, juce::dontSendNotification);
                    brandComboBox.setSelectedId(1, juce::dontSendNotification);
                    sortComboBox.setSelectedId(1, juce::dontSendNotification);
                    currentSortOrder = 0;
                    filterPlugins();
                    break;

                case 501: // About
                    juce::AlertWindow::showMessageBoxAsync(
                        juce::AlertWindow::InfoIcon,
                        "About Plugin Alliance Launcher",
                        "Plugin Alliance Launcher v1.0.0\n\n"
                        "A plugin browser and host for Plugin Alliance plugins.\n\n"
                        "Visit plugin-alliance.com for more information.",
                        "OK");
                    break;

                case 502: // Check for updates
                    juce::URL("https://www.plugin-alliance.com/pages/downloads").launchInDefaultBrowser();
                    break;

                default:
                    break;
            }
        });
}

} // namespace PALauncher
