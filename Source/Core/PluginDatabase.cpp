/*
  ==============================================================================
    PluginDatabase.cpp
    Plugin Alliance Launcher - Plugin Database Implementation
  ==============================================================================
*/

#include "PluginDatabase.h"
#include "../Data/PluginData.h"
#include <algorithm>

namespace PALauncher
{

// Convert category string from PluginData.h to EffectCategory enum
// JSON category names should match display names exactly
static EffectCategory categoryFromString(const juce::String& category)
{
    static const std::map<juce::String, EffectCategory> categoryMap = {
        // === SIDEBAR CATEGORIES (main categories in plugins.json) ===
        // Guitar and Bass
        {"Amplifiers", EffectCategory::AmpSimulator},
        {"Preamps", EffectCategory::Preamp},
        {"Pedals", EffectCategory::Pedals},
        {"Suites", EffectCategory::GuitarSuite},

        // Channel Strips
        {"Channel Strips", EffectCategory::ChannelStrip},
        {"Channel Strip", EffectCategory::ChannelStrip},

        // Equalizers
        {"Equalizers", EffectCategory::EQ},
        {"Equalizer", EffectCategory::EQ},
        {"EQ", EffectCategory::EQ},
        {"Filter", EffectCategory::Filter},

        // Compressors
        {"Compressors", EffectCategory::Compressor},
        {"Compressor", EffectCategory::Compressor},
        {"De-Esser", EffectCategory::DeEsser},

        // Saturators
        {"Saturators", EffectCategory::Saturation},
        {"Saturator", EffectCategory::Saturation},
        {"Saturation", EffectCategory::Saturation},
        {"Tape", EffectCategory::TapeEmulation},

        // Delays
        {"Delays", EffectCategory::Delay},
        {"Delay", EffectCategory::Delay},

        // Reverbs
        {"Reverbs", EffectCategory::Reverb},
        {"Reverb", EffectCategory::Reverb},

        // Limiters
        {"Limiters", EffectCategory::Limiter},
        {"Limiter", EffectCategory::Limiter},

        // Meters
        {"Meters", EffectCategory::SpectralAnalysis},
        {"Meter", EffectCategory::SpectralAnalysis},

        // Mastering Suites
        {"Mastering Suites", EffectCategory::MasteringSuite},
        {"Mastering", EffectCategory::MasteringSuite},

        // Synthesizers
        {"Synthesizers", EffectCategory::Unknown},  // Handled separately as instrument

        // === OTHER CATEGORIES (appear under Other in sidebar) ===
        {"3D & Surround Sound", EffectCategory::ThreeDAndSurround},
        {"Gates", EffectCategory::Gates},
        {"Lo-Fi", EffectCategory::LoFi},
        {"Modulator", EffectCategory::Modulators},
        {"Multi-FX", EffectCategory::MultiFX},
        {"Pitch Correction", EffectCategory::PitchCorrection},
        {"Restoration", EffectCategory::Restoration},
        {"Stereo Imagers", EffectCategory::StereoImagers},
        {"Transient Shapers", EffectCategory::TransientShapers},
        {"Utility", EffectCategory::Utility},
        {"Vocal Processing", EffectCategory::VocalProcessing},
        {"Vocoders", EffectCategory::Vocoders},

        // Legacy/fallback
        {"Other", EffectCategory::Unknown},
    };

    auto it = categoryMap.find(category);
    if (it != categoryMap.end())
        return it->second;

    return EffectCategory::Unknown;
}

// Convert era string from PluginData.h tags to Era enum
static Era eraFromString(const juce::String& era)
{
    static const std::map<juce::String, Era> eraMap = {
        {"1950s", Era::Era_1950s},
        {"1960s", Era::Era_1960s},
        {"1970s", Era::Era_1970s},
        {"1980s", Era::Era_1980s},
        {"1990s", Era::Era_1990s},
        {"2000s", Era::Era_2000s},
        {"2010s", Era::Era_2010s},
        {"2020s", Era::Era_2020s},
        {"Original", Era::Era_Original},
    };

    auto it = eraMap.find(era);
    if (it != eraMap.end())
        return it->second;

    return Era::Era_Original;
}

// LEGACY: Minimal fallback maps for plugins not in plugins.json
// Most categories now come from findPluginMetadata() in PluginData.h
namespace CategoryMaps
{
    // Empty - all categories now in plugins.json
    static const std::map<juce::String, EffectCategory> pluginCategories = {
        {"Maag EQ4", EffectCategory::EQ},
        {"EQ4", EffectCategory::EQ},
        {"EQ2", EffectCategory::EQ},
        {"AMEK EQ 200", EffectCategory::EQ},
        {"AMEK EQ 250", EffectCategory::EQ},
        {"EQ 200", EffectCategory::EQ},
        {"EQ 250", EffectCategory::EQ},
        {"Millennia NSEQ-2", EffectCategory::EQ},
        {"NSEQ-2", EffectCategory::EQ},
        {"SPL Passeq", EffectCategory::EQ},
        {"Passeq", EffectCategory::EQ},
        {"SPL PQ", EffectCategory::EQ},
        {"SPL EQ Ranger Plus", EffectCategory::EQ},
        {"EQ Ranger Plus", EffectCategory::EQ},
        {"SPL Free Ranger", EffectCategory::EQ},
        {"Free Ranger", EffectCategory::EQ},
        {"elysia museq", EffectCategory::EQ},
        {"museq", EffectCategory::EQ},
        {"Dangerous Music BAX EQ", EffectCategory::EQ},
        {"BAX EQ", EffectCategory::EQ},
        {"Kirchhoff-EQ", EffectCategory::EQ},
        {"Kirchhoff EQ", EffectCategory::EQ},
        {"Three-Body Technology Kirchhoff EQ", EffectCategory::EQ},
        {"Bettermaker EQ232D", EffectCategory::EQ},
        {"EQ232D", EffectCategory::EQ},
        {"Lindell Audio 354E", EffectCategory::EQ},
        {"354E", EffectCategory::EQ},
        {"Lindell Audio PEX-500", EffectCategory::EQ},
        {"PEX-500", EffectCategory::EQ},
        {"Lindell Audio TE-100", EffectCategory::EQ},
        {"TE-100", EffectCategory::EQ},
        {"Knif Audio Soma EQ", EffectCategory::EQ},
        {"Soma EQ", EffectCategory::EQ},
        {"Harris Doyle Natalus DSCEQ", EffectCategory::EQ},
        {"Natalus DSCEQ", EffectCategory::EQ},
        {"DSCEQ", EffectCategory::EQ},
        {"TOMO Audiolabs LISA", EffectCategory::EQ},
        {"LISA", EffectCategory::EQ},
        {"ProAudioDSP DSM V3", EffectCategory::EQ},
        {"DSM V3", EffectCategory::EQ},
        {"Louder Than Liftoff Chop Shop", EffectCategory::EQ},
        {"Chop Shop", EffectCategory::EQ},

        // ============ FILTERS ============
        {"bx_cleansweep Pro", EffectCategory::Filter},
        {"bx_cleansweep V2", EffectCategory::Filter},
        {"bx_subfilter", EffectCategory::Filter},
        {"elysia niveau filter", EffectCategory::Filter},

        // ============ COMPRESSORS ============
        // Mastering Compressors
        {"Shadow Hills Mastering Compressor", EffectCategory::Compressor},
        {"Shadow Hills Mastering Compressor Class A", EffectCategory::Compressor},
        {"Mastering Compressor", EffectCategory::Compressor},
        {"Mastering Compressor Class A", EffectCategory::Compressor},
        {"Shadow Hills OptoMax", EffectCategory::Compressor},
        {"OptoMax", EffectCategory::Compressor},
        {"Bettermaker Mastering Compressor", EffectCategory::Compressor},
        {"AMEK Mastering Compressor", EffectCategory::Compressor},
        {"SPL IRON", EffectCategory::Compressor},
        {"IRON", EffectCategory::Compressor},
        // VCA Compressors
        {"elysia alpha compressor", EffectCategory::Compressor},
        {"elysia alpha compressor V2", EffectCategory::Compressor},
        {"alpha compressor", EffectCategory::Compressor},
        {"alpha compressor V2", EffectCategory::Compressor},
        {"elysia mpressor", EffectCategory::Compressor},
        {"mpressor", EffectCategory::Compressor},
        {"Vertigo VSC-2", EffectCategory::Compressor},
        {"VSC-2", EffectCategory::Compressor},
        {"bx_townhouse Buss Compressor", EffectCategory::Compressor},
        {"bx_townhouse", EffectCategory::Compressor},
        {"bx_glue", EffectCategory::Compressor},
        {"Lindell Audio SBC 2500 Compressor", EffectCategory::Compressor},
        {"SBC 2500 Compressor", EffectCategory::Compressor},
        {"Lindell Audio SBC", EffectCategory::Compressor},
        {"SBC", EffectCategory::Compressor},
        // FET Compressors
        {"Purple Audio MC 77", EffectCategory::Compressor},
        {"Purple Audio MC77", EffectCategory::Compressor},
        {"MC 77", EffectCategory::Compressor},
        {"MC77", EffectCategory::Compressor},
        {"Lindell Audio 7X-500", EffectCategory::Compressor},
        {"7X-500", EffectCategory::Compressor},
        // Optical Compressors
        {"bx_opto", EffectCategory::Compressor},
        {"bx_opto Pedal", EffectCategory::Compressor},
        {"Acme Opticom XLA-3", EffectCategory::Compressor},
        {"Opticom XLA-3", EffectCategory::Compressor},
        {"ACME Opticom XLA-3", EffectCategory::Compressor},
        {"ACME Audio Opticom XLA-3", EffectCategory::Compressor},
        {"XLA-3", EffectCategory::Compressor},
        {"TCL-2", EffectCategory::Compressor},
        {"Millennia TCL-2", EffectCategory::Compressor},
        {"U2A", EffectCategory::Compressor},
        {"NEOLD U2A", EffectCategory::Compressor},
        // Tube Compressors
        {"Mäag Audio MAGNUM-K", EffectCategory::Compressor},
        {"Maag Audio MAGNUM-K", EffectCategory::Compressor},
        {"Maag Magnum-K", EffectCategory::Compressor},
        {"MAGNUM-K", EffectCategory::Compressor},
        {"Magnum-K", EffectCategory::Compressor},
        {"NEOLD U17", EffectCategory::Compressor},
        {"U17", EffectCategory::Compressor},
        // Multi-band Compressors
        {"Lindell Audio MBC Multi-Band Compressor", EffectCategory::Compressor},
        {"MBC Multi-Band Compressor", EffectCategory::Compressor},
        {"Lindell Audio MBC", EffectCategory::Compressor},
        {"MBC", EffectCategory::Compressor},
        // Other Compressors
        {"Lindell Audio 254E", EffectCategory::Compressor},
        {"254E", EffectCategory::Compressor},
        {"Lindell Audio 6X-500", EffectCategory::Compressor},
        {"6X-500", EffectCategory::Compressor},
        {"Kiive Audio Xtressor", EffectCategory::Compressor},
        {"Xtressor", EffectCategory::Compressor},
        {"Unfiltered Audio Zip", EffectCategory::Compressor},
        {"Zip", EffectCategory::Compressor},
        {"ADPTR Audio Sculpt", EffectCategory::Compressor},
        {"ADPTR Sculpt", EffectCategory::Compressor},
        {"Sculpt", EffectCategory::Compressor},

        // ============ LIMITERS ============
        {"bx_limiter True Peak", EffectCategory::Limiter},
        {"bx_limiter", EffectCategory::Limiter},
        {"bx_XL V2", EffectCategory::Limiter},
        {"bx_XL V3", EffectCategory::Limiter},
        {"HUM Audio Devices LAAL", EffectCategory::Limiter},

        // ============ GATES ============
        {"Unfiltered Audio G8", EffectCategory::Gates},

        // ============ TRANSIENT SHAPERS ============
        {"SPL Transient Designer Plus", EffectCategory::TransientShapers},
        {"elysia nvelope", EffectCategory::TransientShapers},
        {"SPL Attacker Plus", EffectCategory::TransientShapers},
        {"Unfiltered Audio Indent 2", EffectCategory::TransientShapers},

        // ============ DE-ESSERS ============
        {"SPL De-Esser", EffectCategory::DeEsser},
        {"SPL De-Essers", EffectCategory::DeEsser},
        {"Lindell Audio 902 De-esser", EffectCategory::DeEsser},

        // ============ CHANNEL STRIPS ============
        {"bx_console SSL 4000 E", EffectCategory::ChannelStrip},
        {"bx_console SSL 4000 G", EffectCategory::ChannelStrip},
        {"bx_console SSL 9000 J", EffectCategory::ChannelStrip},
        {"bx_console AMEK 9099", EffectCategory::ChannelStrip},
        {"bx_console Focusrite SC", EffectCategory::ChannelStrip},
        {"Focusrite SC Channel Strip", EffectCategory::ChannelStrip},
        {"bx_console N", EffectCategory::ChannelStrip},
        {"Lindell Audio 80 Series", EffectCategory::ChannelStrip},
        {"Lindell Audio 50 Series", EffectCategory::ChannelStrip},
        {"Lindell Audio 69 Series", EffectCategory::ChannelStrip},
        {"Lindell Audio ChannelX", EffectCategory::ChannelStrip},
        {"NEOLD V76U73", EffectCategory::ChannelStrip},

        // ============ SATURATION ============
        {"Black Box Analog Design HG-2", EffectCategory::Saturation},
        {"Black Box Analog Design HG-2MS", EffectCategory::Saturation},
        {"bx_saturator V2", EffectCategory::Saturation},
        {"bx_clipper", EffectCategory::Saturation},
        {"elysia karacter", EffectCategory::Saturation},
        {"elysia Phil's Cascade", EffectCategory::Saturation},
        {"SPL TwinTube", EffectCategory::Saturation},
        {"SPL Twin Tube", EffectCategory::Saturation},
        {"SPL Vitalizer MK2-T", EffectCategory::Saturation},
        {"Vertigo VSM-3", EffectCategory::Saturation},
        {"Vertigo VSS-2", EffectCategory::Saturation},
        {"Looptrotter SA2RATE 2", EffectCategory::Saturation},
        {"Louder Than Liftoff Silver Bullet mk2", EffectCategory::Saturation},
        {"NEOLD BIG AL", EffectCategory::Saturation},
        {"Maor Appelbaum Mastering & Hendyamps THE OVEN", EffectCategory::Saturation},
        {"THE OVEN", EffectCategory::Saturation},
        {"bx_boom!", EffectCategory::Saturation},
        {"bx_boom", EffectCategory::Saturation},
        {"bx_subsynth", EffectCategory::Saturation},
        {"Noveltech Character", EffectCategory::Saturation},
        {"Noveltech Vocal Enhancer", EffectCategory::Saturation},
        {"Unfiltered Audio Bass-Mint", EffectCategory::Saturation},
        {"ADPTR Audio Hype", EffectCategory::Saturation},
        {"ADPTR Hype", EffectCategory::Saturation},
        {"Hype", EffectCategory::Saturation},

        // ============ TAPE EMULATION ============
        {"NEOLD WARBLE", EffectCategory::TapeEmulation},
        {"Kiive Audio Tape Face", EffectCategory::TapeEmulation},
        {"Unfiltered Audio Needlepoint", EffectCategory::TapeEmulation},
        {"Unfiltered Audio LO-FI-AF", EffectCategory::LoFi},
        {"Unfiltered Audio Dent 2", EffectCategory::LoFi},

        // ============ AMP SIMULATORS ============
        // German Amps
        {"Diezel VH4", EffectCategory::AmpSimulator},
        {"Diezel Herbert", EffectCategory::AmpSimulator},
        {"ENGL Savage 120", EffectCategory::AmpSimulator},
        {"ENGL E646 VS", EffectCategory::AmpSimulator},
        {"ENGL E765 RT", EffectCategory::AmpSimulator},
        // American Amps
        {"Friedman BE-100", EffectCategory::AmpSimulator},
        {"Friedman Buxom Betty", EffectCategory::AmpSimulator},
        {"Friedman DS-40", EffectCategory::AmpSimulator},
        {"Suhr SE100", EffectCategory::AmpSimulator},
        {"Suhr PT100", EffectCategory::AmpSimulator},
        {"Fuchs Overdrive Supreme 50", EffectCategory::AmpSimulator},
        {"Fuchs Train II", EffectCategory::AmpSimulator},
        {"bx_megadual", EffectCategory::AmpSimulator},
        {"bx_megasingle", EffectCategory::AmpSimulator},
        // Bass Amps
        {"Ampeg SVT-VR", EffectCategory::AmpSimulator},
        {"Ampeg SVT-VR Classic", EffectCategory::AmpSimulator},
        {"Ampeg SVT-3PRO", EffectCategory::AmpSimulator},
        {"Ampeg SVT-3 Pro", EffectCategory::AmpSimulator},
        {"Ampeg B-15N", EffectCategory::AmpSimulator},
        {"Ampeg V-4B", EffectCategory::AmpSimulator},
        {"Gallien-Krueger 800RB", EffectCategory::AmpSimulator},
        {"Gallien Krueger 800RB", EffectCategory::AmpSimulator},
        {"bx_bassdude", EffectCategory::AmpSimulator},
        // High Gain / Multi-Amp
        {"bx_rockrack V3", EffectCategory::AmpSimulator},
        {"bx_rockrack V3 Player", EffectCategory::AmpSimulator},
        {"bx_rockergain 100", EffectCategory::AmpSimulator},
        {"Chandler Limited GAV19T", EffectCategory::AmpSimulator},

        // ============ DISTORTION PEDALS ============
        {"bx_yellowdrive", EffectCategory::Distortion},
        {"bx_greenscreamer", EffectCategory::Distortion},
        {"bx_distorange", EffectCategory::Distortion},
        {"bx_metal2", EffectCategory::Distortion},
        {"bx_blackdist2", EffectCategory::Distortion},

        // ============ REVERBS ============
        {"bx_rooMS", EffectCategory::Reverb},
        {"Unfiltered Audio SILO", EffectCategory::Reverb},
        {"SILO", EffectCategory::Reverb},
        {"Unfiltered Audio TAILS", EffectCategory::Reverb},
        {"TAILS", EffectCategory::Reverb},
        {"bx_aura", EffectCategory::Reverb},
        {"sonible smart:reverb", EffectCategory::Reverb},
        {"smart:reverb", EffectCategory::Reverb},
        {"SPL Mo-Verb Plus", EffectCategory::Reverb},
        {"Mo-Verb Plus", EffectCategory::Reverb},
        {"SPL De-Verb", EffectCategory::Reverb},
        {"De-Verb", EffectCategory::Reverb},
        {"SPL De-Verb Plus", EffectCategory::Reverb},
        {"De-Verb Plus", EffectCategory::Reverb},
        {"ADPTR Audio Utopia", EffectCategory::Reverb},
        {"ADPTR Utopia", EffectCategory::Reverb},
        {"Utopia", EffectCategory::Reverb},

        // ============ DELAYS ============
        {"bx_delay 2500", EffectCategory::Delay},
        {"bx_pulsar", EffectCategory::Delay},
        {"A/DA STD-1 Stereo Tapped Delay", EffectCategory::Delay},
        {"ADA STD-1 Stereo Tapped Delay", EffectCategory::Delay},
        {"Unfiltered Audio Sandman", EffectCategory::Delay},
        {"Unfiltered Audio Sandman Pro", EffectCategory::Delay},
        {"Unfiltered Audio Instant Delay", EffectCategory::Delay},

        // ============ MODULATION ============
        {"A/DA Flanger", EffectCategory::Modulators},
        {"ADA Flanger", EffectCategory::Modulators},
        {"bx_bluechorus2", EffectCategory::Modulators},

        // ============ MASTERING SUITES ============
        {"bx_masterdesk", EffectCategory::MasteringSuite},
        {"bx_masterdesk Classic", EffectCategory::MasteringSuite},
        {"bx_masterdesk PRO", EffectCategory::MasteringSuite},
        {"bx_masterdesk True Peak", EffectCategory::MasteringSuite},

        // ============ STEREO / IMAGING ============
        {"bx_stereomaker", EffectCategory::StereoImagers},
        {"bx_shredspread", EffectCategory::StereoImagers},
        {"bx_solo", EffectCategory::StereoImagers},
        {"fiedler audio stage", EffectCategory::StereoImagers},
        {"Schoeps Double MS", EffectCategory::StereoImagers},
        {"Schoeps Mono Upmix", EffectCategory::StereoImagers},

        // ============ METERING / ANALYSIS ============
        {"bx_meter", EffectCategory::SpectralAnalysis},
        {"ADPTR Audio Metric AB", EffectCategory::SpectralAnalysis},
        {"MetricAB", EffectCategory::SpectralAnalysis},
        {"Metric AB", EffectCategory::SpectralAnalysis},
        {"bx_control V2", EffectCategory::SpectralAnalysis},
        {"SPL HawkEye", EffectCategory::SpectralAnalysis},
        {"HawkEye", EffectCategory::SpectralAnalysis},
        {"ADPTR Audio Streamliner", EffectCategory::SpectralAnalysis},
        {"ADPTR Streamliner", EffectCategory::SpectralAnalysis},
        {"StreamLiner", EffectCategory::SpectralAnalysis},
        {"Streamliner", EffectCategory::SpectralAnalysis},

        // ============ VOCAL PROCESSING ============
        {"bx_crispytuner", EffectCategory::VocalProcessing},

        // ============ MULTI-FX ============
        {"DS Audio TANTRA 2", EffectCategory::MultiFX},
        {"Unfiltered Audio BYOME", EffectCategory::MultiFX},
        {"Unfiltered Audio SpecOps", EffectCategory::MultiFX},
        {"Unfiltered Audio TRIAD", EffectCategory::MultiFX},
        {"Unfiltered Audio Fault", EffectCategory::MultiFX},

        // ============ UTILITY ============
        {"bx_tuner", EffectCategory::Unknown},
        {"SPL DrumXchanger", EffectCategory::Unknown},

        // ============ NEW PLUGINS (2024-2025) ============
        // ADPTR Audio
        {"ADPTR Audio Utopia", EffectCategory::Reverb},
        {"ADPTR Utopia", EffectCategory::Reverb},
        {"Utopia", EffectCategory::Reverb},
        {"ADPTR Audio Hype", EffectCategory::MultiFX},
        {"ADPTR Hype", EffectCategory::MultiFX},
        {"Hype", EffectCategory::MultiFX},

        // Shadow Hills
        {"Shadow Hills OptoMax", EffectCategory::Compressor},
        {"OptoMax", EffectCategory::Compressor},

        // NEOLD
        {"NEOLD RZ062", EffectCategory::EQ},
        {"RZ062", EffectCategory::EQ},

        // SPL new
        {"SPL Vitalizer MK3-T", EffectCategory::EQ},
        {"Vitalizer MK3-T", EffectCategory::EQ},
        {"SPL BiG", EffectCategory::StereoImagers},
        {"BiG", EffectCategory::StereoImagers},
        {"SPL Machine Head", EffectCategory::TapeEmulation},
        {"Machine Head", EffectCategory::TapeEmulation},

        // elysia new
        {"elysia alpha compressor V2", EffectCategory::Compressor},
        {"alpha compressor V2", EffectCategory::Compressor},

        // Maag Audio new
        {"Maag Audio EQ4 MS", EffectCategory::EQ},
        {"EQ4 MS", EffectCategory::EQ},

        // HEARS
        {"HEARS Perfection", EffectCategory::Unknown},
        {"Perfection", EffectCategory::Unknown},

        // Brainworx new
        {"Brainworx bx_XL V3", EffectCategory::Limiter},
        {"bx_XL V3", EffectCategory::Limiter},
        {"Brainworx bx_pulsar", EffectCategory::Delay},
        {"bx_pulsar", EffectCategory::Delay},
        {"Brainworx bx_aura", EffectCategory::Reverb},
        {"bx_aura", EffectCategory::Reverb},
        {"Brainworx bx_refinement V3", EffectCategory::EQ},
        {"bx_refinement V3", EffectCategory::EQ},

        // Vertigo new
        {"Vertigo VSS-2", EffectCategory::ChannelStrip},
        {"VSS-2", EffectCategory::ChannelStrip},

        // HUM Audio
        {"HUM Audio LAAL", EffectCategory::Limiter},
        {"LAAL", EffectCategory::Limiter},

        // Three-Body Technology new
        {"Three-Body Technology Cenozoix Compressor", EffectCategory::Compressor},
        {"Cenozoix Compressor", EffectCategory::Compressor},
        {"Cenozoix", EffectCategory::Compressor},

        // Black Box new
        {"Black Box Analog Design HG-Q", EffectCategory::EQ},
        {"HG-Q", EffectCategory::EQ},

        // Lindell Audio new
        {"Lindell Audio EQ825", EffectCategory::EQ},
        {"EQ825", EffectCategory::EQ},

        // Unfiltered Audio new
        {"Unfiltered Audio Battalion", EffectCategory::Utility},
        {"Battalion", EffectCategory::Utility},
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
        {"Mäag Audio EQ4", Era::Era_1970s},
        {"Mäag Audio EQ4 MS", Era::Era_1970s},
        {"Mäag Audio EQ2", Era::Era_1970s},
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
        // Optical Compressors
        {"bx_opto", CompressorType::Optical},
        {"bx_opto Pedal", CompressorType::Optical},
        {"Shadow Hills OptoMax", CompressorType::Optical},
        {"OptoMax", CompressorType::Optical},
        {"Acme Opticom XLA-3", CompressorType::Optical},
        {"Opticom XLA-3", CompressorType::Optical},
        {"ACME Opticom XLA-3", CompressorType::Optical},
        {"ACME Audio Opticom XLA-3", CompressorType::Optical},
        {"XLA-3", CompressorType::Optical},
        {"TCL-2", CompressorType::Optical},
        {"Millennia TCL-2", CompressorType::Optical},
        {"U2A", CompressorType::Optical},
        {"NEOLD U2A", CompressorType::Optical},
        // VCA Compressors
        {"bx_townhouse", CompressorType::VCA},
        {"bx_townhouse Buss Compressor", CompressorType::VCA},
        {"bx_glue", CompressorType::VCA},
        {"Vertigo VSC-2", CompressorType::VCA},
        {"elysia alpha compressor", CompressorType::VCA},
        {"elysia alpha compressor V2", CompressorType::VCA},
        {"elysia mpressor", CompressorType::VCA},
        // FET Compressors
        {"Purple Audio MC 77", CompressorType::FET},
        {"Purple Audio MC77", CompressorType::FET},
        {"Lindell Audio 7X-500", CompressorType::FET},
        // Tube Compressors
        {"Mäag Audio MAGNUM-K", CompressorType::Tube},
        {"Maag Audio MAGNUM-K", CompressorType::Tube},
        {"Maag Magnum-K", CompressorType::Tube},
        {"SPL IRON", CompressorType::Tube},
        {"NEOLD U17", CompressorType::Tube},
        // Bus Compressors
        {"Lindell Audio SBC 2500 Compressor", CompressorType::Bus},
        {"Lindell Audio SBC", CompressorType::Bus},
        // Multi-band Compressors
        {"Lindell Audio MBC Multi-Band Compressor", CompressorType::MultiBand},
        {"Lindell Audio MBC", CompressorType::MultiBand},
        // Mastering Compressors
        {"Shadow Hills Mastering Compressor", CompressorType::Mastering},
        {"Shadow Hills Mastering Compressor Class A", CompressorType::Mastering},
        {"Bettermaker Mastering Compressor", CompressorType::Mastering},
        {"AMEK Mastering Compressor", CompressorType::Mastering},
    };

    // Channel strip subcategories
    static const std::map<juce::String, ChannelStripType> channelStripTypes = {
        // SSL
        {"bx_console SSL 4000 E", ChannelStripType::SSL},
        {"bx_console SSL 4000 G", ChannelStripType::SSL},
        {"bx_console SSL 9000 J", ChannelStripType::SSL},
        // Neve
        {"bx_console N", ChannelStripType::Neve},
        {"Lindell Audio 69 Series", ChannelStripType::Neve},
        // AMEK
        {"bx_console AMEK 9099", ChannelStripType::AMEK},
        // Focusrite
        {"bx_console Focusrite SC", ChannelStripType::Focusrite},
        {"Focusrite SC Channel Strip", ChannelStripType::Focusrite},
        // Vintage
        {"Lindell Audio 80 Series", ChannelStripType::Vintage},
        {"Lindell Audio 50 Series", ChannelStripType::Vintage},
        {"Lindell Audio ChannelX", ChannelStripType::Vintage},
        {"NEOLD V76U73", ChannelStripType::Vintage},
    };

    // Amp subcategories
    static const std::map<juce::String, AmpType> ampTypes = {
        // German Amps
        {"Diezel VH4", AmpType::German},
        {"Diezel Herbert", AmpType::German},
        {"ENGL Savage 120", AmpType::German},
        {"ENGL E646 VS", AmpType::German},
        {"ENGL E765 RT", AmpType::German},
        // American Amps
        {"Friedman BE-100", AmpType::American},
        {"Friedman Buxom Betty", AmpType::American},
        {"Friedman DS-40", AmpType::American},
        {"Suhr SE100", AmpType::American},
        {"Suhr PT100", AmpType::American},
        {"Fuchs Overdrive Supreme 50", AmpType::American},
        {"Fuchs Train II", AmpType::American},
        // Bass Amps
        {"Ampeg SVT-VR", AmpType::BassAmp},
        {"Ampeg SVT-VR Classic", AmpType::BassAmp},
        {"Ampeg SVT-3PRO", AmpType::BassAmp},
        {"Ampeg SVT-3 Pro", AmpType::BassAmp},
        {"Ampeg B-15N", AmpType::BassAmp},
        {"Ampeg V-4B", AmpType::BassAmp},
        {"Gallien-Krueger 800RB", AmpType::BassAmp},
        {"Gallien Krueger 800RB", AmpType::BassAmp},
        {"bx_bassdude", AmpType::BassAmp},
        // High Gain / Multi-Amp
        {"bx_megadual", AmpType::HighGain},
        {"bx_megasingle", AmpType::HighGain},
        {"bx_rockrack V3", AmpType::HighGain},
        {"bx_rockrack V3 Player", AmpType::HighGain},
        {"bx_rockergain 100", AmpType::HighGain},
        // British Amps
        {"Chandler Limited GAV19T", AmpType::British},
    };

    // Special Processing subcategories
    static const std::map<juce::String, OtherType> otherTypes = {
        // Gates
        {"Unfiltered Audio G8", OtherType::Gates},
        // Transient Shapers
        {"SPL Transient Designer Plus", OtherType::TransientShapers},
        {"elysia nvelope", OtherType::TransientShapers},
        {"SPL Attacker Plus", OtherType::TransientShapers},
        {"Unfiltered Audio Indent 2", OtherType::TransientShapers},
        // Stereo Imaging
        {"bx_stereomaker", OtherType::StereoImagers},
        {"bx_shredspread", OtherType::StereoImagers},
        {"bx_solo", OtherType::StereoImagers},
        {"fiedler audio stage", OtherType::StereoImagers},
        {"Schoeps Double MS", OtherType::ThreeDAndSurround},
        {"Schoeps Mono Upmix", OtherType::ThreeDAndSurround},
        // Multi-FX
        {"DS Audio TANTRA 2", OtherType::MultiFX},
        {"Unfiltered Audio BYOME", OtherType::MultiFX},
        {"Unfiltered Audio SpecOps", OtherType::MultiFX},
        {"Unfiltered Audio TRIAD", OtherType::MultiFX},
        {"Unfiltered Audio Fault", OtherType::MultiFX},
        // Lo-Fi
        {"Unfiltered Audio LO-FI-AF", OtherType::LoFi},
        {"Unfiltered Audio Dent 2", OtherType::LoFi},
        // Utility
        {"bx_tuner", OtherType::Utility},
        {"SPL DrumXchanger", OtherType::Utility},
    };
}

PluginDatabase::PluginDatabase()
{
}

PluginDatabase::~PluginDatabase()
{
}

void PluginDatabase::loadAllPluginsFromDatabase()
{
    juce::ScopedLock scopedLock(lock);

    // Load all plugins from the embedded database
    const auto& database = getPluginDatabase();

    for (const auto& meta : database)
    {
        PluginInfo info;

        // Create a plugin description from metadata
        info.description.name = meta.vstFileName;  // Use vstFileName for matching
        info.description.descriptiveName = meta.displayName;
        info.description.manufacturerName = meta.brand;
        info.description.pluginFormatName = "VST3";
        info.description.fileOrIdentifier = meta.vstFileName + ".vst3";
        info.description.uniqueId = meta.id.hashCode();

        info.isInstalled = false;  // Not installed until scan confirms

        categorizePlugin(info);
        assignEra(info);
        assignSubcategory(info);

        // Use the plugin ID as the key
        plugins[meta.id] = info;
    }

    DBG("Loaded " + juce::String(plugins.size()) + " plugins from embedded database");
}

void PluginDatabase::updateInstalledPlugins(const juce::Array<juce::PluginDescription>& installedPlugins)
{
    juce::ScopedLock scopedLock(lock);

    // First, reset all plugins to not installed
    for (auto& pair : plugins)
    {
        pair.second.isInstalled = false;
    }

    // Mark installed plugins
    for (const auto& desc : installedPlugins)
    {
        // Try to find matching plugin in our database
        bool found = false;

        for (auto& pair : plugins)
        {
            // Match by vstFileName (description.name)
            if (pair.second.description.name.equalsIgnoreCase(desc.name) ||
                pair.second.description.name.equalsIgnoreCase(desc.descriptiveName))
            {
                // Update the description with actual scan data
                pair.second.description = desc;
                pair.second.isInstalled = true;
                found = true;
                break;
            }
        }

        // If not found in embedded database, add it as a new installed plugin
        if (!found)
        {
            auto id = getPluginId(desc);

            PluginInfo info;
            info.description = desc;
            info.isInstalled = true;
            categorizePlugin(info);
            assignEra(info);
            assignSubcategory(info);
            plugins[id] = info;

            DBG("Added new installed plugin not in database: " + desc.name);
        }
    }

    int installedCount = 0;
    for (const auto& pair : plugins)
    {
        if (pair.second.isInstalled)
            installedCount++;
    }
    DBG("Marked " + juce::String(installedCount) + " plugins as installed out of " + juce::String(plugins.size()) + " total");
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

                // 11 Effects Categories
                case DisplayCategory::ChannelStrips:
                    matches = (info.category == EffectCategory::ChannelStrip);
                    break;

                case DisplayCategory::Delays:
                    matches = (info.category == EffectCategory::Delay ||
                              info.category == EffectCategory::Echo);
                    break;

                case DisplayCategory::Compressors:
                    matches = (info.category == EffectCategory::Compressor ||
                              info.category == EffectCategory::Expander ||
                              info.category == EffectCategory::DynamicsProcessor ||
                              info.category == EffectCategory::EnvelopeShaper ||
                              info.category == EffectCategory::DeEsser);
                    break;

                case DisplayCategory::Equalizers:
                    matches = (info.category == EffectCategory::EQ ||
                              info.category == EffectCategory::Filter ||
                              info.category == EffectCategory::FrequencyShifter);
                    break;

                case DisplayCategory::GuitarAndBass:
                    // Legacy - maps to Amplifiers for backwards compatibility
                    matches = (info.category == EffectCategory::AmpSimulator);
                    break;

                case DisplayCategory::Amplifiers:
                    matches = (info.category == EffectCategory::AmpSimulator);
                    break;

                case DisplayCategory::Preamps:
                    matches = (info.category == EffectCategory::Preamp);
                    break;

                case DisplayCategory::Pedals:
                    matches = (info.category == EffectCategory::Pedals ||
                              info.category == EffectCategory::Distortion);
                    break;

                case DisplayCategory::Suites:
                    matches = (info.category == EffectCategory::GuitarSuite);
                    break;

                case DisplayCategory::Limiters:
                    matches = (info.category == EffectCategory::Limiter);
                    break;

                case DisplayCategory::Mastering:
                    matches = (info.category == EffectCategory::MasteringSuite ||
                              info.category == EffectCategory::Mastering);
                    break;

                case DisplayCategory::Meters:
                    matches = (info.category == EffectCategory::SpectralAnalysis);
                    break;

                case DisplayCategory::Modulation:
                    matches = (info.category == EffectCategory::Modulators);
                    break;

                case DisplayCategory::PitchCorrection:
                    matches = (info.category == EffectCategory::PitchShifter ||
                              info.category == EffectCategory::Harmonizer ||
                              info.category == EffectCategory::VocalProcessing);
                    break;

                case DisplayCategory::Reverbs:
                    matches = (info.category == EffectCategory::Reverb);
                    break;

                case DisplayCategory::Saturators:
                    matches = (info.category == EffectCategory::Saturation ||
                              info.category == EffectCategory::TapeEmulation ||
                              info.category == EffectCategory::Exciter);
                    break;

                case DisplayCategory::Other:
                    matches = (info.category == EffectCategory::Gates ||
                              info.category == EffectCategory::LoFi ||
                              info.category == EffectCategory::Modulators ||
                              info.category == EffectCategory::MultiFX ||
                              info.category == EffectCategory::PitchCorrection ||
                              info.category == EffectCategory::Restoration ||
                              info.category == EffectCategory::StereoImagers ||
                              info.category == EffectCategory::ThreeDAndSurround ||
                              info.category == EffectCategory::TransientShapers ||
                              info.category == EffectCategory::Utility ||
                              info.category == EffectCategory::VocalProcessing ||
                              info.category == EffectCategory::Vocoders ||
                              info.category == EffectCategory::PitchShifter ||
                              info.category == EffectCategory::Harmonizer ||
                              info.category == EffectCategory::Unknown);
                    break;

                // Instrument Subcategories
                case DisplayCategory::VirtualInstruments:
                    matches = info.isInstrument;
                    break;
                case DisplayCategory::Inst_Bass:
                    matches = info.isInstrument &&
                              (info.instrumentCategory == InstrumentCategory::Sampler ||
                               info.description.name.toLowerCase().contains("bass"));
                    break;
                case DisplayCategory::Inst_Drums:
                    matches = info.isInstrument &&
                              (info.instrumentCategory == InstrumentCategory::DrumMachine ||
                               info.instrumentCategory == InstrumentCategory::DrumSynth ||
                               info.description.name.toLowerCase().contains("drum"));
                    break;
                case DisplayCategory::Inst_Guitars:
                    matches = info.isInstrument &&
                              info.description.name.toLowerCase().contains("guitar");
                    break;
                case DisplayCategory::Inst_Keys:
                    matches = info.isInstrument &&
                              (info.description.name.toLowerCase().contains("piano") ||
                               info.description.name.toLowerCase().contains("keys") ||
                               info.description.name.toLowerCase().contains("keyboard"));
                    break;
                case DisplayCategory::Inst_Organs:
                    matches = info.isInstrument &&
                              info.description.name.toLowerCase().contains("organ");
                    break;
                case DisplayCategory::Inst_Strings:
                    matches = info.isInstrument &&
                              info.description.name.toLowerCase().contains("string");
                    break;
                case DisplayCategory::Synthesizers:
                    matches = info.isInstrument &&
                              (info.instrumentCategory == InstrumentCategory::Synth ||
                               info.instrumentCategory == InstrumentCategory::VocalSynth ||
                               info.description.name.toLowerCase().contains("synth"));
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
            return mfr.contains("a/da") || mfr.contains("a-da") || mfr == "ada" ||
                   name.startsWith("a/da") || name.startsWith("a-da") || name.startsWith("ada ") ||
                   name.contains("ada flanger") || name.contains("ada std-1") || path.contains("ada_");
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
    auto nameLower = info.description.name.toLowerCase();

    // Check for Plugin Alliance synths/instruments first
    if (nameLower.contains("knifonium") ||
        nameLower.contains("bx_oberhausen") ||
        nameLower.contains("thorn") ||
        (nameLower.contains("lion") && !nameLower.contains("battalion")) ||
        nameLower.contains("battalion"))
    {
        info.isInstrument = true;
        info.instrumentCategory = InstrumentCategory::Synth;
        return;
    }

    // Check if plugin is categorized as an instrument by the host
    if (info.description.isInstrument)
    {
        info.isInstrument = true;
        info.instrumentCategory = InstrumentCategory::Synth;
        return;
    }

    // PRIMARY: Look up category from PluginData.h (generated from plugins.json)
    if (auto* metadata = findPluginMetadata(info.description.name))
    {
        if (metadata->category.isNotEmpty())
        {
            info.category = categoryFromString(metadata->category);
            if (info.category != EffectCategory::Unknown)
                return;
        }
    }

    // FALLBACK: Keyword-based categorization for plugins not in plugins.json

    // Equalizers
    if (nameLower.contains("eq") || nameLower.contains("equalizer") ||
        nameLower.contains("passeq") || nameLower.contains("pultec") ||
        nameLower.contains("nseq") || nameLower.contains("paneq") ||
        nameLower.contains("dyneq") || nameLower.contains("kirchhoff"))
        info.category = EffectCategory::EQ;

    // Filters
    else if (nameLower.contains("filter") || nameLower.contains("cleansweep") ||
             nameLower.contains("niveau"))
        info.category = EffectCategory::Filter;

    // Compressors
    else if (nameLower.contains("comp") || nameLower.contains("opto") ||
             nameLower.contains("opticom") || nameLower.contains("xla-3") ||
             nameLower.contains("alpha") || nameLower.contains("mpressor") ||
             nameLower.contains("vsc-2") || nameLower.contains("mc 77") ||
             nameLower.contains("mc77") || nameLower.contains("iron") ||
             nameLower.contains("glue") || nameLower.contains("townhouse") ||
             nameLower.contains("sculpt") || nameLower.contains("xtressor") ||
             nameLower.contains("254e") || nameLower.contains("tcl-2") ||
             nameLower.contains("u17") || nameLower.contains("u2a") ||
             nameLower.contains("magnum") || nameLower.contains("7x-500") ||
             nameLower.contains("6x-500") || nameLower.contains("mbc") ||
             nameLower.contains("sbc") || nameLower.contains("zip"))
        info.category = EffectCategory::Compressor;

    // Limiters
    else if (nameLower.contains("limit") || nameLower.contains("laal") ||
             nameLower.contains("xl v"))
        info.category = EffectCategory::Limiter;

    // Gates
    else if (nameLower.contains("gate") || nameLower.contains(" g8"))
        info.category = EffectCategory::Gates;

    // Transient Shapers
    else if (nameLower.contains("transient") || nameLower.contains("nvelope") ||
             nameLower.contains("attacker") || nameLower.contains("indent"))
        info.category = EffectCategory::TransientShapers;

    // De-essers
    else if (nameLower.contains("de-ess") || nameLower.contains("deess") ||
             nameLower.contains("902"))
        info.category = EffectCategory::DeEsser;

    // Channel Strips
    else if (nameLower.contains("console") || nameLower.contains("channel") ||
             nameLower.contains("80 series") || nameLower.contains("50 series") ||
             nameLower.contains("69 series") || nameLower.contains("v76u73"))
        info.category = EffectCategory::ChannelStrip;

    // Saturation
    else if (nameLower.contains("satur") || nameLower.contains("hg-2") ||
             nameLower.contains("karacter") || nameLower.contains("twintube") ||
             nameLower.contains("twin tube") || nameLower.contains("vsm-3") ||
             nameLower.contains("vss-2") || nameLower.contains("sa2rate") ||
             nameLower.contains("silver bullet") || nameLower.contains("big al") ||
             nameLower.contains("oven") || nameLower.contains("boom") ||
             nameLower.contains("subsynth") || nameLower.contains("character") ||
             nameLower.contains("vocal enhancer") || nameLower.contains("bass-mint") ||
             nameLower.contains("clipper") || nameLower.contains("cascade") ||
             nameLower.contains("vitalizer"))
        info.category = EffectCategory::Saturation;

    // Tape
    else if (nameLower.contains("tape") || nameLower.contains("warble") ||
             nameLower.contains("needlepoint"))
        info.category = EffectCategory::TapeEmulation;

    // Lo-Fi / Bit Crusher
    else if (nameLower.contains("lo-fi") || nameLower.contains("lofi") ||
             nameLower.contains("dent 2") || nameLower.contains("dent2"))
        info.category = EffectCategory::LoFi;

    // Amp Simulators
    else if (nameLower.contains("diezel") || nameLower.contains("vh4") ||
             nameLower.contains("herbert") || nameLower.contains("engl") ||
             nameLower.contains("savage") || nameLower.contains("friedman") ||
             nameLower.contains("be-100") || nameLower.contains("buxom") ||
             nameLower.contains("suhr") || nameLower.contains("pt100") ||
             nameLower.contains("se100") || nameLower.contains("fuchs") ||
             nameLower.contains("ampeg") || nameLower.contains("svt") ||
             nameLower.contains("b-15") || nameLower.contains("v-4b") ||
             nameLower.contains("gallien") || nameLower.contains("800rb") ||
             nameLower.contains("megadual") || nameLower.contains("megasingle") ||
             nameLower.contains("rockrack") || nameLower.contains("rockergain") ||
             nameLower.contains("bassdude") || nameLower.contains("gav19t"))
        info.category = EffectCategory::AmpSimulator;

    // Distortion Pedals
    else if (nameLower.contains("distort") || nameLower.contains("overdrive") ||
             nameLower.contains("drive") || nameLower.contains("screamer") ||
             nameLower.contains("metal2") || nameLower.contains("blackdist"))
        info.category = EffectCategory::Distortion;

    // Reverbs
    else if (nameLower.contains("reverb") || nameLower.contains("verb") ||
             nameLower.contains("rooms") || nameLower.contains("silo") ||
             nameLower.contains("tails") || nameLower.contains("mo-verb"))
        info.category = EffectCategory::Reverb;

    // Delays
    else if (nameLower.contains("delay") || nameLower.contains("echo") ||
             nameLower.contains("sandman") || nameLower.contains("std-1"))
        info.category = EffectCategory::Delay;

    // Modulation
    else if (nameLower.contains("flanger") || nameLower.contains("chorus") ||
             nameLower.contains("phaser") || nameLower.contains("tremolo") ||
             nameLower.contains("vibrato"))
        info.category = EffectCategory::Modulators;  // Will be refined later

    // Mastering
    else if (nameLower.contains("masterdesk") || nameLower.contains("master"))
        info.category = EffectCategory::MasteringSuite;

    // Stereo / Imaging
    else if (nameLower.contains("stereo") || nameLower.contains("stage") ||
             nameLower.contains("shredspread") || nameLower.contains("solo") ||
             nameLower.contains("schoeps"))
        info.category = EffectCategory::StereoImagers;

    // Meters
    else if (nameLower.contains("meter") || nameLower.contains("metric") ||
             nameLower.contains("control v") || nameLower.contains("hawkeye") ||
             nameLower.contains("streamliner"))
        info.category = EffectCategory::SpectralAnalysis;

    // Vocal Processing
    else if (nameLower.contains("tuner") && nameLower.contains("crispy"))
        info.category = EffectCategory::VocalProcessing;

    // Multi-FX
    else if (nameLower.contains("tantra") || nameLower.contains("byome") ||
             nameLower.contains("specops") || nameLower.contains("triad") ||
             nameLower.contains("fault"))
        info.category = EffectCategory::MultiFX;

    // Utility
    else if (nameLower.contains("tuner") || nameLower.contains("drumxchanger"))
        info.category = EffectCategory::Unknown;

    else
        info.category = EffectCategory::Unknown;
}

void PluginDatabase::assignEra(PluginInfo& info)
{
    // PRIMARY: Look up era from PluginData.h tags (generated from plugins.json)
    if (auto* metadata = findPluginMetadata(info.description.name))
    {
        for (const auto& tag : metadata->tags)
        {
            Era era = eraFromString(tag);
            if (era != Era::Era_Original || tag == "Original")
            {
                info.era = era;
                return;
            }
        }
    }

    // Default to Original for plugins without explicit era
    info.era = Era::Era_Original;
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
        case EffectCategory::Distortion:
        {
            auto it = CategoryMaps::ampTypes.find(info.description.name);
            if (it != CategoryMaps::ampTypes.end())
                info.ampType = it->second;
            break;
        }
        case EffectCategory::Gates:
            info.otherType = OtherType::Gates;
            break;
        case EffectCategory::TransientShapers:
            info.otherType = OtherType::TransientShapers;
            break;
        case EffectCategory::StereoImagers:
            info.otherType = OtherType::StereoImagers;
            break;
        case EffectCategory::ThreeDAndSurround:
            info.otherType = OtherType::ThreeDAndSurround;
            break;
        case EffectCategory::MultiFX:
            info.otherType = OtherType::MultiFX;
            break;
        case EffectCategory::Modulators:
            info.otherType = OtherType::Modulators;
            break;
        case EffectCategory::PitchShifter:
        case EffectCategory::Harmonizer:
            info.otherType = OtherType::PitchCorrection;
            break;
        case EffectCategory::VocalProcessing:
            info.otherType = OtherType::PitchCorrection;
            break;
        case EffectCategory::Unknown:
            info.otherType = OtherType::Utility;
            break;
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

    // Only update metadata (favorites, lastUsed) for existing plugins
    // Don't add new plugins - the embedded database is the source of truth
    for (auto* pluginXml : xml->getChildIterator())
    {
        if (pluginXml->hasTagName("Plugin"))
        {
            auto savedName = pluginXml->getStringAttribute("name");
            auto isFavorite = pluginXml->getBoolAttribute("favorite", false);
            auto lastUsed = pluginXml->getStringAttribute("lastUsed").getLargeIntValue();

            // Skip if no user data to restore
            if (!isFavorite && lastUsed == 0)
                continue;

            // Find matching plugin in the database by name
            for (auto& pair : plugins)
            {
                if (pair.second.description.name.equalsIgnoreCase(savedName))
                {
                    pair.second.isFavorite = isFavorite;
                    pair.second.lastUsed = lastUsed;
                    break;
                }
            }
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
