/*
  ==============================================================================
    SettingsManager.cpp
    Plugin Alliance Launcher - Persistent Settings Manager Implementation
  ==============================================================================
*/

#include "SettingsManager.h"

namespace PALauncher
{

SettingsManager::SettingsManager()
{
    auto options = getPropertiesOptions();
    properties = std::make_unique<juce::PropertiesFile>(options);
}

juce::PropertiesFile::Options SettingsManager::getPropertiesOptions() const
{
    juce::PropertiesFile::Options options;
    options.applicationName = "PluginAllianceLauncher";
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = "Plugin Alliance Launcher";
    options.storageFormat = juce::PropertiesFile::storeAsXML;
    return options;
}

void SettingsManager::setWindowSize(int width, int height)
{
    properties->setValue("windowWidth", width);
    properties->setValue("windowHeight", height);
}

juce::Rectangle<int> SettingsManager::getWindowSize() const
{
    int width = properties->getIntValue("windowWidth", 1200);
    int height = properties->getIntValue("windowHeight", 800);
    return {0, 0, width, height};
}

void SettingsManager::setBrowserMode(bool browserMode)
{
    properties->setValue("browserMode", browserMode);
}

bool SettingsManager::getBrowserMode() const
{
    return properties->getBoolValue("browserMode", true);
}

void SettingsManager::setCustomScanPaths(const juce::StringArray& paths)
{
    properties->setValue("customScanPaths", paths.joinIntoString("|"));
}

juce::StringArray SettingsManager::getCustomScanPaths() const
{
    auto pathString = properties->getValue("customScanPaths", "");
    juce::StringArray paths;
    paths.addTokens(pathString, "|", "");
    return paths;
}

void SettingsManager::setLastCategory(int category)
{
    properties->setValue("lastCategory", category);
}

int SettingsManager::getLastCategory() const
{
    return properties->getIntValue("lastCategory", 0);
}

void SettingsManager::setLastEra(int era)
{
    properties->setValue("lastEra", era);
}

int SettingsManager::getLastEra() const
{
    return properties->getIntValue("lastEra", -1);
}

void SettingsManager::setShowOnlyInstalled(bool showOnlyInstalled)
{
    properties->setValue("showOnlyInstalled", showOnlyInstalled);
}

bool SettingsManager::getShowOnlyInstalled() const
{
    return properties->getBoolValue("showOnlyInstalled", false);  // Default: show all plugins
}

void SettingsManager::save()
{
    properties->saveIfNeeded();
}

void SettingsManager::load()
{
    properties->reload();
}

juce::File SettingsManager::getSettingsFile()
{
    auto options = juce::PropertiesFile::Options();
    options.applicationName = "PluginAllianceLauncher";
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = "Plugin Alliance Launcher";

    return options.getDefaultFile();
}

} // namespace PALauncher
