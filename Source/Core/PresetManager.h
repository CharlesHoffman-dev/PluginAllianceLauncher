/*
  ==============================================================================
    PresetManager.h
    Plugin Alliance Launcher - Preset Management System
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

namespace PALauncher
{

class PresetManager
{
public:
    PresetManager();
    ~PresetManager() = default;

    // Get the presets directory (~/Documents/Plugin Alliance Launcher/Presets/)
    juce::File getPresetsDirectory() const;

    // Save a chain state to a preset file
    bool savePreset(const juce::XmlElement& chainState, juce::File destination);

    // Load a preset from file
    std::unique_ptr<juce::XmlElement> loadPreset(juce::File presetFile);

    // Scan the presets directory and build folder tree
    void scanPresets();

    // Build a hierarchical menu from the preset directory
    void buildPresetMenu(juce::PopupMenu& menu, juce::File folder, int& idCounter);

    // Get preset file by menu item ID
    juce::File getPresetFileById(int menuItemId) const;

    // Get all preset files (flat list)
    juce::Array<juce::File> getAllPresetFiles() const;

    // Get recently used presets
    juce::Array<juce::File> getRecentPresets() const;

    // Add a preset to recent list
    void addToRecent(juce::File presetFile);

private:
    void ensurePresetsDirectoryExists();

    std::map<int, juce::File> presetIdToFile;
    juce::Array<juce::File> recentPresets;
    static constexpr int maxRecentPresets = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PresetManager)
};

} // namespace PALauncher
