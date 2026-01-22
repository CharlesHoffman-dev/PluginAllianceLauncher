/*
  ==============================================================================
    PresetManager.cpp
    Plugin Alliance Launcher - Preset Management System Implementation
  ==============================================================================
*/

#include "PresetManager.h"

namespace PALauncher
{

PresetManager::PresetManager()
{
    ensurePresetsDirectoryExists();
}

juce::File PresetManager::getPresetsDirectory() const
{
    auto documentsDir = juce::File::getSpecialLocation(juce::File::userDocumentsDirectory);
    return documentsDir.getChildFile("Plugin Alliance Launcher").getChildFile("Presets");
}

void PresetManager::ensurePresetsDirectoryExists()
{
    auto presetsDir = getPresetsDirectory();
    if (!presetsDir.exists())
    {
        presetsDir.createDirectory();
    }
}

bool PresetManager::savePreset(const juce::XmlElement& chainState, juce::File destination)
{
    // Ensure the file has the correct extension
    if (!destination.hasFileExtension(".palpreset"))
    {
        destination = destination.withFileExtension(".palpreset");
    }

    // Create a wrapper XML element with metadata
    auto presetXml = std::make_unique<juce::XmlElement>("PALauncherPreset");
    presetXml->setAttribute("version", "1.0");
    presetXml->setAttribute("name", destination.getFileNameWithoutExtension());
    presetXml->setAttribute("createdDate", juce::Time::getCurrentTime().toString(true, true, false, true));

    // Add the chain state as a child
    presetXml->addChildElement(new juce::XmlElement(chainState));

    // Write to file
    bool success = presetXml->writeTo(destination);

    if (success)
    {
        addToRecent(destination);
    }

    return success;
}

std::unique_ptr<juce::XmlElement> PresetManager::loadPreset(juce::File presetFile)
{
    if (!presetFile.existsAsFile())
        return nullptr;

    auto presetXml = juce::parseXML(presetFile);

    if (presetXml == nullptr || !presetXml->hasTagName("PALauncherPreset"))
        return nullptr;

    // Extract the chain state from the preset
    auto* chainState = presetXml->getChildByName("PALauncherChain");
    if (chainState == nullptr)
    {
        // Try old format (PALauncherState)
        chainState = presetXml->getChildByName("PALauncherState");
    }

    if (chainState == nullptr)
        return nullptr;

    // Add to recent presets
    addToRecent(presetFile);

    return std::make_unique<juce::XmlElement>(*chainState);
}

void PresetManager::scanPresets()
{
    presetIdToFile.clear();
}

void PresetManager::buildPresetMenu(juce::PopupMenu& menu, juce::File folder, int& idCounter)
{
    if (!folder.isDirectory())
        return;

    // Get all items in this folder
    juce::Array<juce::File> files;
    juce::Array<juce::File> subfolders;

    auto folderIterator = juce::RangedDirectoryIterator(folder, false);
    for (const auto& entry : folderIterator)
    {
        auto file = entry.getFile();

        if (file.isDirectory())
        {
            subfolders.add(file);
        }
        else if (file.hasFileExtension(".palpreset"))
        {
            files.add(file);
        }
    }

    // Sort alphabetically
    struct FileComparator
    {
        static int compareElements(const juce::File& first, const juce::File& second)
        {
            return first.getFileName().compareIgnoreCase(second.getFileName());
        }
    };

    FileComparator comparator;
    subfolders.sort(comparator);
    files.sort(comparator);

    // Add subfolders as submenus
    for (const auto& subfolder : subfolders)
    {
        juce::PopupMenu submenu;
        buildPresetMenu(submenu, subfolder, idCounter);

        if (submenu.getNumItems() > 0)
        {
            menu.addSubMenu(subfolder.getFileName(), submenu);
        }
    }

    // Add preset files
    for (const auto& file : files)
    {
        int itemId = ++idCounter;
        presetIdToFile[itemId] = file;
        menu.addItem(itemId, file.getFileNameWithoutExtension());
    }
}

juce::File PresetManager::getPresetFileById(int menuItemId) const
{
    auto it = presetIdToFile.find(menuItemId);
    if (it != presetIdToFile.end())
        return it->second;

    return juce::File();
}

juce::Array<juce::File> PresetManager::getAllPresetFiles() const
{
    juce::Array<juce::File> allPresets;
    auto presetsDir = getPresetsDirectory();

    if (!presetsDir.isDirectory())
        return allPresets;

    // Recursively find all .palpreset files
    auto findPresetsRecursive = [&allPresets](const juce::File& folder, auto& self) -> void
    {
        auto folderIterator = juce::RangedDirectoryIterator(folder, false);
        for (const auto& entry : folderIterator)
        {
            auto file = entry.getFile();

            if (file.isDirectory())
            {
                self(file, self);  // Recurse into subdirectories
            }
            else if (file.hasFileExtension(".palpreset"))
            {
                allPresets.add(file);
            }
        }
    };

    findPresetsRecursive(presetsDir, findPresetsRecursive);

    // Sort alphabetically
    struct FileComparator
    {
        static int compareElements(const juce::File& first, const juce::File& second)
        {
            return first.getFileNameWithoutExtension().compareIgnoreCase(second.getFileNameWithoutExtension());
        }
    };

    FileComparator comparator;
    allPresets.sort(comparator);

    return allPresets;
}

juce::Array<juce::File> PresetManager::getRecentPresets() const
{
    return recentPresets;
}

void PresetManager::addToRecent(juce::File presetFile)
{
    // Remove if already in list
    recentPresets.removeAllInstancesOf(presetFile);

    // Add to front
    recentPresets.insert(0, presetFile);

    // Limit size
    while (recentPresets.size() > maxRecentPresets)
        recentPresets.removeLast();
}

} // namespace PALauncher
