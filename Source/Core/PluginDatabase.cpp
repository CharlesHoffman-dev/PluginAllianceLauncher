/*
  ==============================================================================
    PluginDatabase.cpp
    Plugin Alliance Launcher - Plugin Database Implementation
  ==============================================================================
*/

#include "PluginDatabase.h"
#include <algorithm>

namespace PALauncher
{

// Static category mappings
namespace CategoryMaps
{
    // Plugin name -> Category mapping
    static const std::map<juce::String, EffectCategory> pluginCategories = {
        // EQ
        {"bx_digital V3", EffectCategory::EQ},
        {"bx_digital V2", EffectCategory::EQ},
        {"bx_hybrid V2", EffectCategory::EQ},
        {"bx_dynEQ V2", EffectCategory::EQ},
        {"bx_2098 EQ", EffectCategory::EQ},
        {"bx_panEQ", EffectCategory::EQ},
        {"bx_refinement", EffectCategory::EQ},
        {"Maag Audio EQ4", EffectCategory::EQ},
        {"Maag Audio EQ2", EffectCategory::EQ},
        {"AMEK EQ 200", EffectCategory::EQ},
        {"Millennia NSEQ-2", EffectCategory::EQ},
        {"SPL Passeq", EffectCategory::EQ},
        {"elysia museq", EffectCategory::EQ},
        {"Dangerous Music BAX EQ", EffectCategory::EQ},
        {"Kirchhoff-EQ", EffectCategory::EQ},
        {"Lindell Audio EQ825", EffectCategory::EQ},

        // Filter
        {"bx_cleansweep Pro", EffectCategory::Filter},
        {"bx_cleansweep V2", EffectCategory::Filter},
        {"elysia niveau filter", EffectCategory::Filter},

        // Compressor
        {"Shadow Hills Mastering Compressor", EffectCategory::Compressor},
        {"Shadow Hills Mastering Compressor Class A", EffectCategory::Compressor},
        {"Shadow Hills OptoMax", EffectCategory::Compressor},
        {"elysia alpha compressor", EffectCategory::Compressor},
        {"elysia alpha compressor V2", EffectCategory::Compressor},
        {"elysia mpressor", EffectCategory::Compressor},
        {"Vertigo VSC-2", EffectCategory::Compressor},
        {"Purple Audio MC 77", EffectCategory::Compressor},
        {"SPL IRON", EffectCategory::Compressor},
        {"Bettermaker Mastering Compressor", EffectCategory::Compressor},
        {"bx_opto", EffectCategory::Compressor},
        {"bx_townhouse", EffectCategory::Compressor},
        {"bx_glue", EffectCategory::Compressor},
        {"Maag Audio MAGNUM-K", EffectCategory::Compressor},

        // Limiter
        {"bx_limiter True Peak", EffectCategory::Limiter},
        {"bx_limiter", EffectCategory::Limiter},
        {"bx_XL V2", EffectCategory::Limiter},
        {"bx_XL V3", EffectCategory::Limiter},
        {"HUM Audio Devices LAAL", EffectCategory::Limiter},

        // Gate
        {"Unfiltered Audio G8", EffectCategory::Gate},

        // Channel Strip
        {"bx_console SSL 4000 E", EffectCategory::ChannelStrip},
        {"bx_console SSL 4000 G", EffectCategory::ChannelStrip},
        {"bx_console SSL 9000 J", EffectCategory::ChannelStrip},
        {"bx_console AMEK 9099", EffectCategory::ChannelStrip},
        {"bx_console Focusrite SC", EffectCategory::ChannelStrip},
        {"bx_console N", EffectCategory::ChannelStrip},
        {"Lindell Audio 80 Series", EffectCategory::ChannelStrip},
        {"Vertigo VSS-2", EffectCategory::ChannelStrip},

        // Saturation
        {"Black Box Analog Design HG-2", EffectCategory::Saturation},
        {"Black Box Analog Design HG-2MS", EffectCategory::Saturation},
        {"bx_saturator V2", EffectCategory::Saturation},
        {"elysia karacter", EffectCategory::Saturation},
        {"SPL TwinTube", EffectCategory::Saturation},
        {"Vertigo VSM-3", EffectCategory::Saturation},
        {"Looptrotter SA2RATE 2", EffectCategory::Saturation},

        // Tape
        {"SPL Machine Head", EffectCategory::TapeEmulation},
        {"NEOLD WARBLE", EffectCategory::TapeEmulation},

        // Amp Simulator
        {"Diezel VH4", EffectCategory::AmpSimulator},
        {"Diezel Herbert", EffectCategory::AmpSimulator},
        {"Suhr SE100", EffectCategory::AmpSimulator},
        {"Suhr PT100", EffectCategory::AmpSimulator},
        {"ENGL Savage 120", EffectCategory::AmpSimulator},
        {"Friedman BE-100", EffectCategory::AmpSimulator},
        {"Ampeg SVT-VR", EffectCategory::AmpSimulator},
        {"Ampeg SVT-3 Pro", EffectCategory::AmpSimulator},
        {"Ampeg B-15N", EffectCategory::AmpSimulator},
        {"bx_megadual", EffectCategory::AmpSimulator},
        {"bx_rockrack V3", EffectCategory::AmpSimulator},
        {"bx_bassdude", EffectCategory::AmpSimulator},

        // Reverb
        {"bx_rooMS", EffectCategory::Reverb},
        {"Unfiltered Audio SILO", EffectCategory::Reverb},
        {"Unfiltered Audio TAILS", EffectCategory::Reverb},
        {"bx_aura", EffectCategory::Reverb},

        // Delay
        {"bx_delay 2500", EffectCategory::Delay},
        {"bx_pulsar", EffectCategory::Delay},
        {"ADPTR AUDIO Utopia", EffectCategory::Delay},

        // Modulation
        {"A/DA Flanger", EffectCategory::Flanger},
        {"bx_bluechorus2", EffectCategory::Chorus},

        // Mastering
        {"bx_masterdesk", EffectCategory::MasteringSuite},
        {"bx_masterdesk Classic", EffectCategory::MasteringSuite},
        {"bx_masterdesk PRO", EffectCategory::MasteringSuite},

        // Transient Shaper
        {"SPL Transient Designer Plus", EffectCategory::TransientShaper},
        {"elysia nvelope", EffectCategory::TransientShaper},

        // De-Esser
        {"SPL De-Esser", EffectCategory::DeEsser},
        {"SPL De-Essers", EffectCategory::DeEsser},

        // Stereo Width
        {"bx_stereomaker", EffectCategory::StereoWidth},
        {"bx_shredspread", EffectCategory::StereoWidth},
        {"fiedler audio stage", EffectCategory::StereoWidth},

        // Metering
        {"bx_meter", EffectCategory::SpectralAnalysis},
        {"ADPTR AUDIO Metric AB", EffectCategory::SpectralAnalysis},
        {"bx_control V2", EffectCategory::SpectralAnalysis},

        // Vocal
        {"bx_crispytuner", EffectCategory::VocalProcessing},
        {"Noveltech Vocal Enhancer", EffectCategory::VocalProcessing},

        // Distortion
        {"bx_yellowdrive", EffectCategory::Distortion},
        {"bx_greenscreamer", EffectCategory::Distortion},
        {"bx_distorange", EffectCategory::Distortion},
        {"bx_metal2", EffectCategory::Distortion},

        // Enhancer
        {"SPL BiG", EffectCategory::Enhancer},
        {"bx_subsynth", EffectCategory::Enhancer},
        {"bx_boom!", EffectCategory::DrumFX},
    };

    // Plugin name -> Era mapping
    static const std::map<juce::String, Era> pluginEras = {
        // 1960s
        {"Purple Audio MC 77", Era::Era_1960s},
        {"Ampeg SVT-VR", Era::Era_1960s},
        {"Ampeg B-15N", Era::Era_1960s},
        {"bx_opto", Era::Era_1960s},

        // 1970s
        {"bx_console N", Era::Era_1970s},
        {"bx_console SSL 4000 E", Era::Era_1970s},
        {"bx_console SSL 4000 G", Era::Era_1970s},
        {"bx_console AMEK 9099", Era::Era_1970s},
        {"Maag Audio EQ4", Era::Era_1970s},
        {"Maag Audio EQ2", Era::Era_1970s},
        {"A/DA Flanger", Era::Era_1970s},
        {"bx_greenscreamer", Era::Era_1970s},
        {"bx_distorange", Era::Era_1970s},
        {"bx_oberhausen", Era::Era_1970s},

        // 1980s
        {"bx_console SSL 9000 J", Era::Era_1980s},
        {"bx_console Focusrite SC", Era::Era_1980s},
        {"Gallien Krueger 800RB", Era::Era_1980s},
        {"bx_townhouse", Era::Era_1980s},
        {"bx_bluechorus2", Era::Era_1980s},
        {"bx_blackdist2", Era::Era_1980s},
        {"Ampeg SVT-3 Pro", Era::Era_1980s},

        // 1990s
        {"Diezel VH4", Era::Era_1990s},
        {"Diezel Herbert", Era::Era_1990s},
        {"SPL Transient Designer Plus", Era::Era_1990s},
        {"SPL Vitalizer MK2-T", Era::Era_1990s},
        {"Millennia NSEQ-2", Era::Era_1990s},
        {"Dangerous Music BAX EQ", Era::Era_1990s},
        {"Shadow Hills Mastering Compressor", Era::Era_1990s},
        {"Shadow Hills Mastering Compressor Class A", Era::Era_1990s},
        {"Vertigo VSC-2", Era::Era_1990s},
        {"ENGL Savage 120", Era::Era_1990s},
        {"Friedman BE-100", Era::Era_1990s},
        {"Suhr SE100", Era::Era_1990s},
        {"Suhr PT100", Era::Era_1990s},

        // 2000s
        {"elysia alpha compressor", Era::Era_2000s},
        {"elysia alpha compressor V2", Era::Era_2000s},
        {"elysia mpressor", Era::Era_2000s},
        {"elysia museq", Era::Era_2000s},
        {"elysia nvelope", Era::Era_2000s},
        {"elysia karacter", Era::Era_2000s},
        {"SPL Passeq", Era::Era_2000s},
        {"Bettermaker Mastering Compressor", Era::Era_2000s},
        {"Lindell Audio 80 Series", Era::Era_2000s},

        // 2010s
        {"SPL IRON", Era::Era_2010s},
        {"Black Box Analog Design HG-2", Era::Era_2010s},
        {"Looptrotter SA2RATE 2", Era::Era_2010s},
        {"Lindell Audio EQ825", Era::Era_2010s},

        // 2020s
        {"Shadow Hills OptoMax", Era::Era_2020s},
        {"Kirchhoff-EQ", Era::Era_2020s},
        {"HUM Audio Devices LAAL", Era::Era_2020s},
    };

    // Compressor subcategories
    static const std::map<juce::String, CompressorType> compressorTypes = {
        {"bx_opto", CompressorType::Optical},
        {"Shadow Hills OptoMax", CompressorType::Optical},
        {"bx_townhouse", CompressorType::VCA},
        {"bx_glue", CompressorType::VCA},
        {"Vertigo VSC-2", CompressorType::VCA},
        {"elysia alpha compressor", CompressorType::VCA},
        {"elysia alpha compressor V2", CompressorType::VCA},
        {"elysia mpressor", CompressorType::VCA},
        {"Purple Audio MC 77", CompressorType::FET},
        {"Maag Audio MAGNUM-K", CompressorType::Tube},
        {"SPL IRON", CompressorType::Tube},
        {"Shadow Hills Mastering Compressor", CompressorType::Mastering},
        {"Shadow Hills Mastering Compressor Class A", CompressorType::Mastering},
        {"Bettermaker Mastering Compressor", CompressorType::Mastering},
    };

    // Channel strip subcategories
    static const std::map<juce::String, ChannelStripType> channelStripTypes = {
        {"bx_console SSL 4000 E", ChannelStripType::SSL},
        {"bx_console SSL 4000 G", ChannelStripType::SSL},
        {"bx_console SSL 9000 J", ChannelStripType::SSL},
        {"bx_console N", ChannelStripType::Neve},
        {"bx_console AMEK 9099", ChannelStripType::AMEK},
        {"bx_console Focusrite SC", ChannelStripType::Focusrite},
        {"Lindell Audio 80 Series", ChannelStripType::Vintage},
        {"Vertigo VSS-2", ChannelStripType::Vintage},
    };

    // Amp subcategories
    static const std::map<juce::String, AmpType> ampTypes = {
        {"Diezel VH4", AmpType::German},
        {"Diezel Herbert", AmpType::German},
        {"ENGL Savage 120", AmpType::German},
        {"Friedman BE-100", AmpType::American},
        {"Suhr SE100", AmpType::American},
        {"Suhr PT100", AmpType::American},
        {"Ampeg SVT-VR", AmpType::BassAmp},
        {"Ampeg SVT-3 Pro", AmpType::BassAmp},
        {"Ampeg B-15N", AmpType::BassAmp},
        {"bx_bassdude", AmpType::BassAmp},
        {"bx_megadual", AmpType::HighGain},
        {"bx_rockrack V3", AmpType::HighGain},
    };
}

PluginDatabase::PluginDatabase()
{
}

PluginDatabase::~PluginDatabase()
{
}

void PluginDatabase::updatePlugins(const juce::Array<juce::PluginDescription>& newPlugins)
{
    juce::ScopedLock scopedLock(lock);

    for (const auto& desc : newPlugins)
    {
        auto id = getPluginId(desc);
        auto it = plugins.find(id);

        if (it == plugins.end())
        {
            // New plugin
            PluginInfo info;
            info.description = desc;
            categorizePlugin(info);
            assignEra(info);
            assignSubcategory(info);
            plugins[id] = info;
        }
        else
        {
            // Update existing plugin's description
            it->second.description = desc;
        }
    }
}

void PluginDatabase::clear()
{
    juce::ScopedLock scopedLock(lock);
    plugins.clear();
}

juce::Array<PluginInfo> PluginDatabase::getAllPlugins() const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    for (const auto& pair : plugins)
        result.add(pair.second);

    return result;
}

juce::Array<PluginInfo> PluginDatabase::search(const juce::String& query) const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    auto lowerQuery = query.toLowerCase();

    for (const auto& pair : plugins)
    {
        const auto& info = pair.second;

        // Search in name and manufacturer
        if (info.description.name.toLowerCase().contains(lowerQuery) ||
            info.description.manufacturerName.toLowerCase().contains(lowerQuery))
        {
            result.add(info);
        }
    }

    return result;
}

juce::Array<PluginInfo> PluginDatabase::getByCategory(EffectCategory category) const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    for (const auto& pair : plugins)
    {
        if (pair.second.category == category)
            result.add(pair.second);
    }

    return result;
}

juce::Array<PluginInfo> PluginDatabase::getByEra(Era era) const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    for (const auto& pair : plugins)
    {
        if (pair.second.era == era)
            result.add(pair.second);
    }

    return result;
}

juce::Array<PluginInfo> PluginDatabase::getByDisplayCategory(DisplayCategory category) const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    for (const auto& pair : plugins)
    {
        const auto& info = pair.second;
        bool matches = false;

        switch (category)
        {
            case DisplayCategory::All:
                matches = true;
                break;
            case DisplayCategory::EQ:
                matches = (info.category == EffectCategory::EQ);
                break;
            case DisplayCategory::Dynamics:
                matches = (info.category == EffectCategory::Compressor ||
                          info.category == EffectCategory::Limiter ||
                          info.category == EffectCategory::Gate ||
                          info.category == EffectCategory::TransientShaper);
                break;
            case DisplayCategory::Reverb:
                matches = (info.category == EffectCategory::Reverb);
                break;
            case DisplayCategory::Delay:
                matches = (info.category == EffectCategory::Delay ||
                          info.category == EffectCategory::Echo);
                break;
            case DisplayCategory::Modulation:
                matches = (info.category == EffectCategory::Chorus ||
                          info.category == EffectCategory::Flanger ||
                          info.category == EffectCategory::Phaser);
                break;
            case DisplayCategory::Saturation:
                matches = (info.category == EffectCategory::Saturation ||
                          info.category == EffectCategory::TapeEmulation);
                break;
            case DisplayCategory::Distortion:
                matches = (info.category == EffectCategory::Distortion);
                break;
            case DisplayCategory::AmpSim:
                matches = (info.category == EffectCategory::AmpSimulator);
                break;
            case DisplayCategory::ChannelStrip:
                matches = (info.category == EffectCategory::ChannelStrip);
                break;
            case DisplayCategory::Mastering:
                matches = (info.category == EffectCategory::MasteringSuite ||
                          info.category == EffectCategory::Mastering);
                break;
            case DisplayCategory::Vocal:
                matches = (info.category == EffectCategory::VocalProcessing ||
                          info.category == EffectCategory::DeEsser);
                break;
            case DisplayCategory::Metering:
                matches = (info.category == EffectCategory::SpectralAnalysis);
                break;
            case DisplayCategory::StereoImaging:
                matches = (info.category == EffectCategory::StereoWidth);
                break;
            case DisplayCategory::Favorites:
                matches = info.isFavorite;
                break;
            default:
                break;
        }

        if (matches)
            result.add(info);
    }

    return result;
}

juce::Array<PluginInfo> PluginDatabase::getFavorites() const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    for (const auto& pair : plugins)
    {
        if (pair.second.isFavorite)
            result.add(pair.second);
    }

    return result;
}

juce::Array<PluginInfo> PluginDatabase::getRecent(int maxCount) const
{
    juce::ScopedLock scopedLock(lock);
    juce::Array<PluginInfo> result;

    // Collect all plugins with lastUsed > 0
    for (const auto& pair : plugins)
    {
        if (pair.second.lastUsed > 0)
            result.add(pair.second);
    }

    // Sort by lastUsed (most recent first)
    std::sort(result.begin(), result.end(), [](const PluginInfo& a, const PluginInfo& b) {
        return a.lastUsed > b.lastUsed;
    });

    // Limit results
    if (result.size() > maxCount)
        result.removeRange(maxCount, result.size() - maxCount);

    return result;
}

void PluginDatabase::setFavorite(const juce::String& pluginId, bool favorite)
{
    juce::ScopedLock scopedLock(lock);

    auto it = plugins.find(pluginId);
    if (it != plugins.end())
    {
        it->second.isFavorite = favorite;
    }
}

bool PluginDatabase::isFavorite(const juce::String& pluginId) const
{
    juce::ScopedLock scopedLock(lock);

    auto it = plugins.find(pluginId);
    if (it != plugins.end())
        return it->second.isFavorite;

    return false;
}

void PluginDatabase::addToRecent(const juce::PluginDescription& desc)
{
    juce::ScopedLock scopedLock(lock);

    auto id = getPluginId(desc);
    auto it = plugins.find(id);

    if (it != plugins.end())
    {
        it->second.lastUsed = juce::Time::currentTimeMillis();
    }
}

PluginInfo* PluginDatabase::findPlugin(const juce::String& pluginId)
{
    juce::ScopedLock scopedLock(lock);

    auto it = plugins.find(pluginId);
    if (it != plugins.end())
        return &it->second;

    return nullptr;
}

const PluginInfo* PluginDatabase::findPlugin(const juce::String& pluginId) const
{
    juce::ScopedLock scopedLock(lock);

    auto it = plugins.find(pluginId);
    if (it != plugins.end())
        return &it->second;

    return nullptr;
}

void PluginDatabase::categorizePlugin(PluginInfo& info)
{
    // Check explicit mapping first
    auto it = CategoryMaps::pluginCategories.find(info.description.name);
    if (it != CategoryMaps::pluginCategories.end())
    {
        info.category = it->second;
        return;
    }

    // Fallback: keyword-based categorization
    auto nameLower = info.description.name.toLowerCase();

    if (nameLower.contains("eq") || nameLower.contains("equalizer"))
        info.category = EffectCategory::EQ;
    else if (nameLower.contains("comp") || nameLower.contains("compressor"))
        info.category = EffectCategory::Compressor;
    else if (nameLower.contains("limit"))
        info.category = EffectCategory::Limiter;
    else if (nameLower.contains("reverb") || nameLower.contains("verb"))
        info.category = EffectCategory::Reverb;
    else if (nameLower.contains("delay") || nameLower.contains("echo"))
        info.category = EffectCategory::Delay;
    else if (nameLower.contains("console") || nameLower.contains("channel"))
        info.category = EffectCategory::ChannelStrip;
    else if (nameLower.contains("satur"))
        info.category = EffectCategory::Saturation;
    else if (nameLower.contains("amp") || nameLower.contains("guitar"))
        info.category = EffectCategory::AmpSimulator;
    else if (nameLower.contains("distort") || nameLower.contains("overdrive"))
        info.category = EffectCategory::Distortion;
    else if (nameLower.contains("master"))
        info.category = EffectCategory::Mastering;
    else
        info.category = EffectCategory::Unknown;
}

void PluginDatabase::assignEra(PluginInfo& info)
{
    // Check explicit mapping
    auto it = CategoryMaps::pluginEras.find(info.description.name);
    if (it != CategoryMaps::pluginEras.end())
    {
        info.era = it->second;
        return;
    }

    // Default to Modern for plugins without explicit era
    info.era = Era::Era_Modern;
}

void PluginDatabase::assignSubcategory(PluginInfo& info)
{
    // Assign subcategory based on main category
    switch (info.category)
    {
        case EffectCategory::Compressor:
        {
            auto it = CategoryMaps::compressorTypes.find(info.description.name);
            if (it != CategoryMaps::compressorTypes.end())
                info.compressorType = it->second;
            break;
        }
        case EffectCategory::ChannelStrip:
        {
            auto it = CategoryMaps::channelStripTypes.find(info.description.name);
            if (it != CategoryMaps::channelStripTypes.end())
                info.channelStripType = it->second;
            break;
        }
        case EffectCategory::AmpSimulator:
        {
            auto it = CategoryMaps::ampTypes.find(info.description.name);
            if (it != CategoryMaps::ampTypes.end())
                info.ampType = it->second;
            break;
        }
        default:
            break;
    }
}

juce::String PluginDatabase::getPluginId(const juce::PluginDescription& desc) const
{
    // Create unique ID from plugin format and identifier
    return desc.pluginFormatName + "_" + desc.fileOrIdentifier;
}

juce::File PluginDatabase::getDatabaseFile() const
{
    return juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
        .getChildFile("PluginAllianceLauncher")
        .getChildFile("database.xml");
}

void PluginDatabase::saveToDisk()
{
    juce::ScopedLock scopedLock(lock);

    auto file = getDatabaseFile();
    file.getParentDirectory().createDirectory();

    auto xml = std::make_unique<juce::XmlElement>("PALauncherDatabase");

    for (const auto& pair : plugins)
    {
        const auto& info = pair.second;
        auto* pluginXml = xml->createNewChildElement("Plugin");

        pluginXml->setAttribute("id", pair.first);
        pluginXml->setAttribute("name", info.description.name);
        pluginXml->setAttribute("manufacturer", info.description.manufacturerName);
        pluginXml->setAttribute("format", info.description.pluginFormatName);
        pluginXml->setAttribute("fileOrIdentifier", info.description.fileOrIdentifier);
        pluginXml->setAttribute("uid", juce::String(info.description.uniqueId));
        pluginXml->setAttribute("category", static_cast<int>(info.category));
        pluginXml->setAttribute("era", static_cast<int>(info.era));
        pluginXml->setAttribute("favorite", info.isFavorite);
        pluginXml->setAttribute("lastUsed", juce::String(info.lastUsed));
    }

    xml->writeTo(file);
}

void PluginDatabase::loadFromDisk()
{
    juce::ScopedLock scopedLock(lock);

    auto file = getDatabaseFile();
    if (!file.existsAsFile())
        return;

    auto xml = juce::XmlDocument::parse(file);
    if (xml == nullptr || !xml->hasTagName("PALauncherDatabase"))
        return;

    for (auto* pluginXml : xml->getChildIterator())
    {
        if (pluginXml->hasTagName("Plugin"))
        {
            PluginInfo info;
            info.description.name = pluginXml->getStringAttribute("name");
            info.description.manufacturerName = pluginXml->getStringAttribute("manufacturer");
            info.description.pluginFormatName = pluginXml->getStringAttribute("format");
            info.description.fileOrIdentifier = pluginXml->getStringAttribute("fileOrIdentifier");
            info.description.uniqueId = pluginXml->getStringAttribute("uid").getIntValue();
            info.category = static_cast<EffectCategory>(pluginXml->getIntAttribute("category", 0));
            info.era = static_cast<Era>(pluginXml->getIntAttribute("era", 0));
            info.isFavorite = pluginXml->getBoolAttribute("favorite", false);
            info.lastUsed = pluginXml->getStringAttribute("lastUsed").getLargeIntValue();

            auto id = pluginXml->getStringAttribute("id");
            plugins[id] = info;
        }
    }
}

} // namespace PALauncher
