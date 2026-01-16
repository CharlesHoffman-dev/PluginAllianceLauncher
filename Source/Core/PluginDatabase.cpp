/*
  ==============================================================================
    PluginDatabase.cpp
    Plugin Alliance Launcher - Plugin Database Implementation
  ==============================================================================
*/

#include "PluginDatabase.h"
#include "../Data/PluginNameMap.h"
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

    sortPluginsByBrandAndName(result);
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

    sortPluginsByBrandAndName(result);
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

    sortPluginsByBrandAndName(result);
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

    sortPluginsByBrandAndName(result);
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

        // Check if this is a brand category
        if (isBrandCategory(category))
        {
            matches = matchesBrand(info, category);
        }
        else
        {
            switch (category)
            {
                case DisplayCategory::All:
                    matches = true;
                    break;
                case DisplayCategory::EQ:
                    matches = (info.category == EffectCategory::EQ ||
                              info.category == EffectCategory::Filter);
                    break;
                case DisplayCategory::Compressors:
                    matches = (info.category == EffectCategory::Compressor ||
                              info.category == EffectCategory::Limiter ||
                              info.category == EffectCategory::TransientShaper);
                    break;
                case DisplayCategory::Expanders:
                    matches = (info.category == EffectCategory::Expander ||
                              info.category == EffectCategory::Gate);
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
                              info.category == EffectCategory::Phaser ||
                              info.category == EffectCategory::Tremolo ||
                              info.category == EffectCategory::Vibrato);
                    break;
                case DisplayCategory::Saturation:
                    matches = (info.category == EffectCategory::Saturation ||
                              info.category == EffectCategory::TapeEmulation ||
                              info.category == EffectCategory::Exciter);
                    break;
                case DisplayCategory::Distortion:
                    matches = (info.category == EffectCategory::Distortion ||
                              info.category == EffectCategory::BitCrusher);
                    break;
                case DisplayCategory::AmpSim:
                    matches = (info.category == EffectCategory::AmpSimulator ||
                              info.category == EffectCategory::Preamp);
                    break;
                case DisplayCategory::ChannelStrip:
                    matches = (info.category == EffectCategory::ChannelStrip);
                    break;
                case DisplayCategory::Mastering:
                    matches = (info.category == EffectCategory::MasteringSuite ||
                              info.category == EffectCategory::Mastering);
                    break;
                case DisplayCategory::Mixing:
                    matches = (info.category == EffectCategory::DynamicsProcessor ||
                              info.category == EffectCategory::EnvelopeShaper);
                    break;
                case DisplayCategory::Vocal:
                    matches = (info.category == EffectCategory::VocalProcessing ||
                              info.category == EffectCategory::DeEsser ||
                              info.category == EffectCategory::Vocoder);
                    break;
                case DisplayCategory::Metering:
                    matches = (info.category == EffectCategory::SpectralAnalysis);
                    break;
                case DisplayCategory::StereoImaging:
                    matches = (info.category == EffectCategory::StereoWidth ||
                              info.category == EffectCategory::SurroundTools);
                    break;
                case DisplayCategory::Pitch:
                    matches = (info.category == EffectCategory::PitchShifter ||
                              info.category == EffectCategory::Harmonizer);
                    break;
                case DisplayCategory::Creative:
                    matches = (info.category == EffectCategory::GranularFX ||
                              info.category == EffectCategory::MultiEffect ||
                              info.category == EffectCategory::Randomiser);
                    break;
                case DisplayCategory::Utility:
                    matches = (info.category == EffectCategory::DrumFX ||
                              info.category == EffectCategory::DJTools ||
                              info.category == EffectCategory::Sequencer ||
                              info.category == EffectCategory::MIDIArp ||
                              info.category == EffectCategory::Unknown);
                    break;
                case DisplayCategory::Synth:
                    matches = (info.isInstrument && info.instrumentCategory == InstrumentCategory::Synth);
                    break;
                case DisplayCategory::Drums:
                    matches = (info.isInstrument && (info.instrumentCategory == InstrumentCategory::DrumMachine ||
                              info.instrumentCategory == InstrumentCategory::DrumSynth));
                    break;
                case DisplayCategory::Sampler:
                    matches = (info.isInstrument && info.instrumentCategory == InstrumentCategory::Sampler);
                    break;
                case DisplayCategory::Favorites:
                    matches = info.isFavorite;
                    break;
                case DisplayCategory::Recent:
                    matches = (info.lastUsed > 0);
                    break;
                default:
                    break;
            }
        }

        if (matches)
            result.add(info);
    }

    sortPluginsByBrandAndName(result);
    return result;
}

bool PluginDatabase::matchesBrand(const PluginInfo& info, DisplayCategory brandCategory) const
{
    auto mfr = info.description.manufacturerName.toLowerCase();
    auto name = info.description.name.toLowerCase();
    auto path = info.description.fileOrIdentifier.toLowerCase();

    switch (brandCategory)
    {
        case DisplayCategory::Brand_ACMEAudio:
            return mfr.contains("acme") || name.contains("acme");
        case DisplayCategory::Brand_ADA:
            return mfr.contains("a/da") || mfr.contains("a-da") || name.startsWith("a/da") || name.startsWith("a-da");
        case DisplayCategory::Brand_ADPTRAudio:
            return mfr.contains("adptr") || name.contains("adptr");
        case DisplayCategory::Brand_AMEK:
            return mfr.contains("amek") || name.contains("amek");
        case DisplayCategory::Brand_Ampeg:
            return mfr.contains("ampeg") || name.contains("ampeg");
        case DisplayCategory::Brand_Bettermaker:
            return mfr.contains("bettermaker") || name.contains("bettermaker");
        case DisplayCategory::Brand_BlackBoxAnalogDesign:
            return mfr.contains("black box") || name.contains("black box");
        case DisplayCategory::Brand_Brainworx:
            return mfr.contains("brainworx") || name.startsWith("bx_") || name.startsWith("bx ");
        case DisplayCategory::Brand_ChandlerLimited:
            return mfr.contains("chandler") || name.contains("chandler");
        case DisplayCategory::Brand_CutClassic:
            return mfr.contains("cut classic") || name.contains("cut classic");
        case DisplayCategory::Brand_DangerousMusic:
            return mfr.contains("dangerous") || name.contains("dangerous");
        case DisplayCategory::Brand_Diezel:
            return mfr.contains("diezel") || name.contains("diezel");
        case DisplayCategory::Brand_DSAudio:
            return mfr.contains("ds audio") || name.contains("ds audio") || name.contains("tantra");
        case DisplayCategory::Brand_Elysia:
            return mfr.contains("elysia") || name.contains("elysia");
        case DisplayCategory::Brand_ENGL:
            return mfr.contains("engl") || name.contains("engl ");
        case DisplayCategory::Brand_FiedlerAudio:
            return mfr.contains("fiedler") || name.contains("fiedler");
        case DisplayCategory::Brand_Focusrite:
            return mfr.contains("focusrite") || name.contains("focusrite");
        case DisplayCategory::Brand_Friedman:
            return mfr.contains("friedman") || name.contains("friedman");
        case DisplayCategory::Brand_Fuchs:
            return mfr.contains("fuchs") || name.contains("fuchs");
        case DisplayCategory::Brand_GallienKrueger:
            return mfr.contains("gallien") || name.contains("gallien");
        case DisplayCategory::Brand_HarrisDoyle:
            return mfr.contains("harris doyle") || name.contains("harris doyle");
        case DisplayCategory::Brand_HEARS:
            return mfr.contains("hears") || name.contains("hears");
        case DisplayCategory::Brand_HUMAudioDevices:
            return mfr.contains("hum audio") || name.contains("laal");
        case DisplayCategory::Brand_KaranyiSounds:
            return mfr.contains("karanyi") || name.contains("karanyi");
        case DisplayCategory::Brand_KiiveAudio:
            return mfr.contains("kiive") || name.contains("kiive");
        case DisplayCategory::Brand_KnifAudio:
            return mfr.contains("knif") || name.contains("knif");
        case DisplayCategory::Brand_LindellAudio:
            return mfr.contains("lindell") || name.contains("lindell");
        case DisplayCategory::Brand_Looptrotter:
            return mfr.contains("looptrotter") || name.contains("looptrotter");
        case DisplayCategory::Brand_LouderThanLiftoff:
            return mfr.contains("louder than liftoff") || name.contains("silver bullet");
        case DisplayCategory::Brand_MaorAppelbaumHendyamps:
            return mfr.contains("maor appelbaum") || mfr.contains("hendyamps");
        case DisplayCategory::Brand_Millennia:
            return mfr.contains("millennia") || name.contains("millennia");
        case DisplayCategory::Brand_Mixland:
            return mfr.contains("mixland") || name.contains("mixland");
        case DisplayCategory::Brand_MaagAudio:
            return mfr.contains("maag") || mfr.contains("mäag") || name.contains("maag") || name.contains("mäag");
        case DisplayCategory::Brand_NEOLD:
            return mfr.contains("neold") || name.contains("neold");
        case DisplayCategory::Brand_Noveltech:
            return mfr.contains("noveltech") || name.contains("noveltech");
        case DisplayCategory::Brand_ProAudioDSP:
            return mfr.contains("proaudiodsp") || mfr.contains("pro audio dsp") || name.contains("dsm v");
        case DisplayCategory::Brand_PurpleAudio:
            return mfr.contains("purple audio") || name.contains("purple audio") || name.contains("mc 77");
        case DisplayCategory::Brand_ShadowHills:
            return mfr.contains("shadow hills") || name.contains("shadow hills");
        case DisplayCategory::Brand_SSL:
            return mfr.contains("ssl") || mfr.contains("solid state logic") || name.contains("ssl");
        case DisplayCategory::Brand_SPL:
            return mfr.contains("spl") || name.startsWith("spl ");
        case DisplayCategory::Brand_Suhr:
            return mfr.contains("suhr") || name.contains("suhr");
        case DisplayCategory::Brand_SwivelAudio:
            return mfr.contains("swivel") || name.contains("swivel");
        case DisplayCategory::Brand_ThreeBodyTechnology:
            return mfr.contains("three-body") || mfr.contains("three body") || name.contains("kirchhoff") || name.contains("cenozoix");
        case DisplayCategory::Brand_THX:
            return mfr.contains("thx") || name.contains("thx");
        case DisplayCategory::Brand_TOMOAudiolabs:
            return mfr.contains("tomo") || name.contains("tomo") || name.contains("lisa");
        case DisplayCategory::Brand_UnfilteredAudio:
            return mfr.contains("unfiltered") || name.contains("unfiltered");
        case DisplayCategory::Brand_Vertigo:
            return mfr.contains("vertigo") || name.contains("vertigo");
        default:
            return false;
    }
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

    sortPluginsByBrandAndName(result);
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

void PluginDatabase::sortPluginsByBrandAndName(juce::Array<PluginInfo>& pluginList) const
{
    std::sort(pluginList.begin(), pluginList.end(),
        [](const PluginInfo& a, const PluginInfo& b)
        {
            // Get brand names for comparison using official name mapping
            auto brandA = getBrandName(a.description.name, a.description.manufacturerName);
            auto brandB = getBrandName(b.description.name, b.description.manufacturerName);

            // First sort by brand (case-insensitive)
            int brandCompare = brandA.compareIgnoreCase(brandB);
            if (brandCompare != 0)
                return brandCompare < 0;

            // Then sort by product name using official names (case-insensitive)
            auto nameA = getOfficialPluginName(a.description.name);
            auto nameB = getOfficialPluginName(b.description.name);
            return nameA.compareIgnoreCase(nameB) < 0;
        });
}

juce::String PluginDatabase::getDisplayName(const juce::PluginDescription& desc) const
{
    return getOfficialPluginName(desc.name);
}

juce::String PluginDatabase::getDisplayBrand(const juce::PluginDescription& desc) const
{
    return getBrandName(desc.name, desc.manufacturerName);
}

} // namespace PALauncher
