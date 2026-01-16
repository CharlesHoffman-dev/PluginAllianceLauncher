/*
  ==============================================================================
    PluginDatabase.h
    Plugin Alliance Launcher - Plugin Database with Categories and Search
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Data/PluginCategories.h"
#include "../Data/PluginSubcategories.h"

namespace PALauncher
{

// Extended plugin info with categories
struct PluginInfo
{
    juce::PluginDescription description;
    EffectCategory category = EffectCategory::Unknown;
    Era era = Era::Era_Unknown;
    bool isFavorite = false;
    int64_t lastUsed = 0;  // Unix timestamp

    // Instrument info
    bool isInstrument = false;
    InstrumentCategory instrumentCategory = InstrumentCategory::Synth;

    // Subcategory (optional, based on category)
    CompressorType compressorType = CompressorType::Unknown;
    EQType eqType = EQType::Unknown;
    ReverbType reverbType = ReverbType::Unknown;
    DelayType delayType = DelayType::Unknown;
    AmpType ampType = AmpType::Unknown;
    SaturationType saturationType = SaturationType::Unknown;
    ChannelStripType channelStripType = ChannelStripType::Unknown;
    LimiterType limiterType = LimiterType::Unknown;
    DistortionType distortionType = DistortionType::Unknown;
};

class PluginDatabase
{
public:
    PluginDatabase();
    ~PluginDatabase();

    // Database operations
    void updatePlugins(const juce::Array<juce::PluginDescription>& plugins);
    void clear();

    // Querying
    juce::Array<PluginInfo> getAllPlugins() const;
    juce::Array<PluginInfo> search(const juce::String& query) const;
    juce::Array<PluginInfo> getByCategory(EffectCategory category) const;
    juce::Array<PluginInfo> getByEra(Era era) const;
    juce::Array<PluginInfo> getByDisplayCategory(DisplayCategory category) const;
    juce::Array<PluginInfo> getFavorites() const;
    juce::Array<PluginInfo> getRecent(int maxCount = 10) const;

    // Favorites
    void setFavorite(const juce::String& pluginId, bool isFavorite);
    bool isFavorite(const juce::String& pluginId) const;

    // Recent
    void addToRecent(const juce::PluginDescription& desc);

    // Persistence
    void saveToDisk();
    void loadFromDisk();

    // Plugin lookup
    PluginInfo* findPlugin(const juce::String& pluginId);
    const PluginInfo* findPlugin(const juce::String& pluginId) const;

    // Display name helpers - returns official plugin names
    juce::String getDisplayName(const juce::PluginDescription& desc) const;
    juce::String getDisplayBrand(const juce::PluginDescription& desc) const;

private:
    void categorizePlugin(PluginInfo& info);
    void assignEra(PluginInfo& info);
    void assignSubcategory(PluginInfo& info);
    bool matchesBrand(const PluginInfo& info, DisplayCategory brandCategory) const;
    juce::String getPluginId(const juce::PluginDescription& desc) const;
    void sortPluginsByBrandAndName(juce::Array<PluginInfo>& pluginList) const;

    juce::File getDatabaseFile() const;

    std::map<juce::String, PluginInfo> plugins;
    mutable juce::CriticalSection lock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginDatabase)
};

} // namespace PALauncher
