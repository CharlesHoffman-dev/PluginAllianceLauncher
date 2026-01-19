/*
  ==============================================================================
    SettingsManager.h
    Plugin Alliance Launcher - Persistent Settings Manager
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class SettingsManager
{
public:
    SettingsManager();
    ~SettingsManager() = default;

    // Window settings
    void setWindowSize(int width, int height);
    juce::Rectangle<int> getWindowSize() const;

    // Browser mode
    void setBrowserMode(bool browserMode);
    bool getBrowserMode() const;

    // Last scan paths (optional custom paths)
    void setCustomScanPaths(const juce::StringArray& paths);
    juce::StringArray getCustomScanPaths() const;

    // Last selected category
    void setLastCategory(int category);
    int getLastCategory() const;

    // Last selected era
    void setLastEra(int era);
    int getLastEra() const;

    // Show only installed plugins
    void setShowOnlyInstalled(bool showOnlyInstalled);
    bool getShowOnlyInstalled() const;

    // Save/load
    void save();
    void load();

    // Get the settings file
    static juce::File getSettingsFile();

private:
    juce::PropertiesFile::Options getPropertiesOptions() const;

    std::unique_ptr<juce::PropertiesFile> properties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SettingsManager)
};

} // namespace PALauncher
