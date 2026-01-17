/*
  ==============================================================================
    PluginCategories.h
    Plugin Alliance Launcher - Category and Era Definitions
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

namespace PALauncher
{

// ============================================
// EFFECTS CATEGORIES
// ============================================
enum class EffectCategory
{
    // Dynamics
    Compressor,
    Limiter,
    Gate,
    Expander,
    DynamicsProcessor,
    TransientShaper,
    EnvelopeShaper,
    DeEsser,

    // EQ & Filtering
    EQ,
    Filter,
    FrequencyShifter,

    // Time-Based
    Reverb,
    Delay,
    Echo,

    // Modulation
    Chorus,
    Flanger,
    Phaser,
    Tremolo,
    Vibrato,
    Modulator,

    // Distortion & Saturation
    Distortion,
    Saturation,
    BitCrusher,
    Exciter,
    TapeEmulation,

    // Amp & Preamp
    AmpSimulator,
    Preamp,

    // Channel & Mastering
    ChannelStrip,
    MasteringSuite,
    Mastering,

    // Pitch
    PitchShifter,
    Harmonizer,

    // Stereo & Spatial
    StereoWidth,
    SurroundTools,
    SpectralAnalysis,

    // Voice & Vocal
    VocalProcessing,
    Vocoder,

    // Creative & FX
    GranularFX,
    MultiEffect,
    Randomiser,

    // Utility
    DrumFX,
    DJTools,
    Enhancer,
    Sequencer,
    MIDIArp,

    // Other
    ExpansionPack,
    Unknown
};

// ============================================
// INSTRUMENT CATEGORIES
// ============================================
enum class InstrumentCategory
{
    Synth,
    DrumMachine,
    DrumSynth,
    Sampler,
    Groovebox,
    VirtualInstrument,
    VocalSynth,
    Generator,
    KontaktInstrument,
    ReaktorEnsemble,
    MaschineExpansion,
    SynthPresets,
    CompleteCollection,
    ExpansionPack
};

// ============================================
// DISPLAY CATEGORY (Simplified for UI - 12 Categories)
// ============================================
enum class DisplayCategory
{
    // Special - Always at top
    All,
    Favorites,
    Recent,

    // Effects (alphabetical)
    ChannelStrip,       // Console emulations (SSL, Neve, API, etc.)
    Delays,             // Analog, Digital, Granular, Tape, etc.
    Dynamics,           // Compressors, Gates, Transient Shapers, De-Essers
    Equalization,       // Parametric, Passive, Dynamic, Filters, etc.
    GuitarBass,         // Amps, Pedals, Cabinets
    Limiters,           // Limiters, Clippers, Maximizers
    Mastering,          // Mastering Suites, Limiters, Metering (legacy)
    Meters,             // Spectrum analyzers, loudness meters, phase meters
    Modulation,         // Chorus, Flanger, Phaser, Tremolo, Vibrato (legacy)
    PitchCorrection,    // Vocal Tuners, Pitch Shifters, Harmonizers (legacy)
    Reverbs,            // Algorithmic, Plate, Hall, Room, Chamber, etc.
    Saturation,         // Distortion, Tube, Tape, Transformer, Harmonic
    SpecialProcessing,  // Multi-FX, Lo-Fi, Stereo Wideners, 3D Audio, etc.

    // Instruments - subcategories (alphabetical)
    Inst_Bass,          // Bass instruments
    Inst_Drums,         // Drum machines, drum synths
    Inst_Guitars,       // Guitar instruments
    Inst_Keys,          // Keyboard instruments (pianos, etc.)
    Inst_Organs,        // Organ instruments
    Inst_Strings,       // String instruments
    Inst_Synths,        // Synthesizers

    // Legacy (keep for compatibility)
    VirtualInstruments, // All virtual instruments

    // Brands (alphabetical)
    Brand_ACMEAudio,
    Brand_ADA,
    Brand_ADPTRAudio,
    Brand_AMEK,
    Brand_Ampeg,
    Brand_Bettermaker,
    Brand_BlackBoxAnalogDesign,
    Brand_Brainworx,
    Brand_ChandlerLimited,
    Brand_CutClassic,
    Brand_DangerousMusic,
    Brand_Diezel,
    Brand_DSAudio,
    Brand_Elysia,
    Brand_ENGL,
    Brand_FiedlerAudio,
    Brand_Focusrite,
    Brand_Friedman,
    Brand_Fuchs,
    Brand_GallienKrueger,
    Brand_HarrisDoyle,
    Brand_HEARS,
    Brand_HUMAudioDevices,
    Brand_KaranyiSounds,
    Brand_KiiveAudio,
    Brand_KnifAudio,
    Brand_LindellAudio,
    Brand_Looptrotter,
    Brand_LouderThanLiftoff,
    Brand_MaorAppelbaumHendyamps,
    Brand_Millennia,
    Brand_Mixland,
    Brand_MaagAudio,
    Brand_NEOLD,
    Brand_Noveltech,
    Brand_ProAudioDSP,
    Brand_PurpleAudio,
    Brand_ShadowHills,
    Brand_SSL,
    Brand_SPL,
    Brand_Suhr,
    Brand_SwivelAudio,
    Brand_ThreeBodyTechnology,
    Brand_THX,
    Brand_TOMOAudiolabs,
    Brand_UnfilteredAudio,
    Brand_Vertigo
};

// ============================================
// ERA / VINTAGE DECADE CATEGORY
// ============================================
enum class Era
{
    Era_1920s,
    Era_1930s,
    Era_1940s,
    Era_1950s,
    Era_1960s,
    Era_1970s,
    Era_1980s,
    Era_1990s,
    Era_2000s,
    Era_2010s,
    Era_2020s,
    Era_Modern,
    Era_Unknown
};

// ============================================
// Display Name Mappings
// ============================================
inline juce::String getEffectCategoryName(EffectCategory cat)
{
    // Category names match sidebar categories for consistency
    static const std::map<EffectCategory, juce::String> names = {
        {EffectCategory::Compressor, "Compressor"},
        {EffectCategory::Limiter, "Limiter"},
        {EffectCategory::Gate, "Gate"},
        {EffectCategory::Expander, "Expander"},
        {EffectCategory::DynamicsProcessor, "Compressor"},
        {EffectCategory::TransientShaper, "Compressor"},
        {EffectCategory::EnvelopeShaper, "Compressor"},
        {EffectCategory::DeEsser, "Compressor"},
        {EffectCategory::EQ, "Equalizer"},
        {EffectCategory::Filter, "Equalizer"},
        {EffectCategory::FrequencyShifter, "Equalizer"},
        {EffectCategory::Reverb, "Reverb"},
        {EffectCategory::Delay, "Delay"},
        {EffectCategory::Echo, "Delay"},
        {EffectCategory::Chorus, "Other"},
        {EffectCategory::Flanger, "Other"},
        {EffectCategory::Phaser, "Other"},
        {EffectCategory::Tremolo, "Other"},
        {EffectCategory::Vibrato, "Other"},
        {EffectCategory::Modulator, "Other"},
        {EffectCategory::Distortion, "Saturator"},
        {EffectCategory::Saturation, "Saturator"},
        {EffectCategory::BitCrusher, "Saturator"},
        {EffectCategory::Exciter, "Saturator"},
        {EffectCategory::TapeEmulation, "Saturator"},
        {EffectCategory::AmpSimulator, "Amp Simulator"},
        {EffectCategory::Preamp, "Amp Simulator"},
        {EffectCategory::ChannelStrip, "Channel Strip"},
        {EffectCategory::MasteringSuite, "Channel Strip"},
        {EffectCategory::Mastering, "Channel Strip"},
        {EffectCategory::PitchShifter, "Other"},
        {EffectCategory::Harmonizer, "Other"},
        {EffectCategory::StereoWidth, "Other"},
        {EffectCategory::SurroundTools, "Other"},
        {EffectCategory::SpectralAnalysis, "Meter"},
        {EffectCategory::VocalProcessing, "Other"},
        {EffectCategory::Vocoder, "Other"},
        {EffectCategory::GranularFX, "Other"},
        {EffectCategory::MultiEffect, "Other"},
        {EffectCategory::Randomiser, "Other"},
        {EffectCategory::DrumFX, "Other"},
        {EffectCategory::DJTools, "Other"},
        {EffectCategory::Enhancer, "Other"},
        {EffectCategory::Sequencer, "Other"},
        {EffectCategory::MIDIArp, "Other"},
        {EffectCategory::ExpansionPack, "Other"},
        {EffectCategory::Unknown, ""}
    };

    auto it = names.find(cat);
    return it != names.end() ? it->second : "";
}

inline juce::String getEraName(Era era)
{
    static const std::map<Era, juce::String> names = {
        {Era::Era_1920s, "1920s"},
        {Era::Era_1930s, "1930s"},
        {Era::Era_1940s, "1940s"},
        {Era::Era_1950s, "1950s"},
        {Era::Era_1960s, "1960s"},
        {Era::Era_1970s, "1970s"},
        {Era::Era_1980s, "1980s"},
        {Era::Era_1990s, "1990s"},
        {Era::Era_2000s, "2000s"},
        {Era::Era_2010s, "2010s"},
        {Era::Era_2020s, "2020s"},
        {Era::Era_Modern, "Digital"},
        {Era::Era_Unknown, "Unknown Era"}
    };

    auto it = names.find(era);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getDisplayCategoryName(DisplayCategory cat)
{
    static const std::map<DisplayCategory, juce::String> names = {
        // Special
        {DisplayCategory::All, "All"},
        {DisplayCategory::Favorites, "Favorites"},
        {DisplayCategory::Recent, "Recent"},

        // Effects (alphabetical)
        {DisplayCategory::ChannelStrip, "Channel Strips"},
        {DisplayCategory::Delays, "Delays"},
        {DisplayCategory::Dynamics, "Dynamics"},
        {DisplayCategory::Equalization, "Equalizers"},
        {DisplayCategory::GuitarBass, "Amp Simulators"},
        {DisplayCategory::Mastering, "Mastering"},
        {DisplayCategory::Meters, "Meters"},
        {DisplayCategory::Modulation, "Modulation"},
        {DisplayCategory::PitchCorrection, "Pitch Correction"},
        {DisplayCategory::Reverbs, "Reverbs"},
        {DisplayCategory::Saturation, "Saturators"},
        {DisplayCategory::SpecialProcessing, "Other"},

        // Instruments - subcategories
        {DisplayCategory::Inst_Bass, "Bass"},
        {DisplayCategory::Inst_Drums, "Drums"},
        {DisplayCategory::Inst_Guitars, "Guitars"},
        {DisplayCategory::Inst_Keys, "Keys"},
        {DisplayCategory::Inst_Organs, "Organs"},
        {DisplayCategory::Inst_Strings, "Strings"},
        {DisplayCategory::Inst_Synths, "Synths"},
        {DisplayCategory::VirtualInstruments, "Virtual Instruments"},

        // Brands (alphabetical)
        {DisplayCategory::Brand_ACMEAudio, "ACME Audio"},
        {DisplayCategory::Brand_ADA, "ADA"},
        {DisplayCategory::Brand_ADPTRAudio, "ADPTR AUDIO"},
        {DisplayCategory::Brand_AMEK, "AMEK"},
        {DisplayCategory::Brand_Ampeg, "Ampeg"},
        {DisplayCategory::Brand_Bettermaker, "Bettermaker"},
        {DisplayCategory::Brand_BlackBoxAnalogDesign, "Black Box Analog Design"},
        {DisplayCategory::Brand_Brainworx, "Brainworx"},
        {DisplayCategory::Brand_ChandlerLimited, "Chandler Limited"},
        {DisplayCategory::Brand_CutClassic, "Cut Classic"},
        {DisplayCategory::Brand_DangerousMusic, "Dangerous Music"},
        {DisplayCategory::Brand_Diezel, "Diezel"},
        {DisplayCategory::Brand_DSAudio, "DS Audio"},
        {DisplayCategory::Brand_Elysia, "elysia"},
        {DisplayCategory::Brand_ENGL, "ENGL"},
        {DisplayCategory::Brand_FiedlerAudio, "fiedler audio"},
        {DisplayCategory::Brand_Focusrite, "Focusrite"},
        {DisplayCategory::Brand_Friedman, "Friedman"},
        {DisplayCategory::Brand_Fuchs, "Fuchs"},
        {DisplayCategory::Brand_GallienKrueger, "Gallien-Krueger"},
        {DisplayCategory::Brand_HarrisDoyle, "Harris Doyle"},
        {DisplayCategory::Brand_HEARS, "HEARS"},
        {DisplayCategory::Brand_HUMAudioDevices, "HUM Audio Devices"},
        {DisplayCategory::Brand_KaranyiSounds, "Karanyi Sounds"},
        {DisplayCategory::Brand_KiiveAudio, "Kiive Audio"},
        {DisplayCategory::Brand_KnifAudio, "Knif Audio"},
        {DisplayCategory::Brand_LindellAudio, "Lindell Audio"},
        {DisplayCategory::Brand_Looptrotter, "Looptrotter"},
        {DisplayCategory::Brand_LouderThanLiftoff, "Louder Than Liftoff"},
        {DisplayCategory::Brand_MaorAppelbaumHendyamps, "Maor Appelbaum & Hendyamps"},
        {DisplayCategory::Brand_Millennia, "Millennia"},
        {DisplayCategory::Brand_Mixland, "Mixland"},
        {DisplayCategory::Brand_MaagAudio, "Mäag Audio"},
        {DisplayCategory::Brand_NEOLD, "NEOLD"},
        {DisplayCategory::Brand_Noveltech, "Noveltech"},
        {DisplayCategory::Brand_ProAudioDSP, "Pro Audio DSP"},
        {DisplayCategory::Brand_PurpleAudio, "Purple Audio"},
        {DisplayCategory::Brand_ShadowHills, "Shadow Hills"},
        {DisplayCategory::Brand_SSL, "Solid State Logic (SSL)"},
        {DisplayCategory::Brand_SPL, "SPL"},
        {DisplayCategory::Brand_Suhr, "Suhr"},
        {DisplayCategory::Brand_SwivelAudio, "Swivel Audio"},
        {DisplayCategory::Brand_ThreeBodyTechnology, "Three-Body Technology"},
        {DisplayCategory::Brand_THX, "THX"},
        {DisplayCategory::Brand_TOMOAudiolabs, "TOMO Audiolabs"},
        {DisplayCategory::Brand_UnfilteredAudio, "Unfiltered Audio"},
        {DisplayCategory::Brand_Vertigo, "Vertigo"}
    };

    auto it = names.find(cat);
    return it != names.end() ? it->second : "Unknown";
}

// Helper to check if a DisplayCategory is a brand
inline bool isBrandCategory(DisplayCategory cat)
{
    return static_cast<int>(cat) >= static_cast<int>(DisplayCategory::Brand_ACMEAudio);
}

// ============================================
// Brand Detection and Name Extraction
// ============================================

// Get the brand name from a plugin's name or manufacturer
inline juce::String getBrandName(const juce::String& pluginName, const juce::String& manufacturerName)
{
    auto nameLower = pluginName.toLowerCase();
    auto mfrLower = manufacturerName.toLowerCase();

    // Check for Brainworx prefix first (most common)
    if (nameLower.startsWith("bx_") || nameLower.startsWith("bx "))
        return "Brainworx";

    // Alphabetical brand detection
    if (mfrLower.contains("acme") || nameLower.contains("acme"))
        return "ACME Audio";
    if (mfrLower.contains("a/da") || mfrLower.contains("a-da") || nameLower.startsWith("a/da") || nameLower.startsWith("a-da"))
        return "A/DA";
    if (mfrLower.contains("adptr") || nameLower.contains("adptr"))
        return "ADPTR AUDIO";
    if (mfrLower.contains("amek") || nameLower.contains("amek"))
        return "AMEK";
    if (mfrLower.contains("ampeg") || nameLower.contains("ampeg"))
        return "Ampeg";
    if (mfrLower.contains("bettermaker") || nameLower.contains("bettermaker"))
        return "Bettermaker";
    if (mfrLower.contains("black box") || nameLower.contains("black box"))
        return "Black Box Analog Design";
    if (mfrLower.contains("chandler") || nameLower.contains("chandler"))
        return "Chandler Limited";
    if (mfrLower.contains("cut classic") || nameLower.contains("cut classic"))
        return "Cut Classic";
    if (mfrLower.contains("dangerous") || nameLower.contains("dangerous"))
        return "Dangerous Music";
    if (mfrLower.contains("diezel") || nameLower.contains("diezel"))
        return "Diezel";
    if (mfrLower.contains("ds audio") || nameLower.contains("ds audio") || nameLower.contains("tantra"))
        return "DS Audio";
    if (mfrLower.contains("elysia") || nameLower.contains("elysia"))
        return "elysia";
    if (mfrLower.contains("engl") || nameLower.contains("engl "))
        return "ENGL";
    if (mfrLower.contains("fiedler") || nameLower.contains("fiedler"))
        return "fiedler audio";
    if (mfrLower.contains("focusrite") || nameLower.contains("focusrite"))
        return "Focusrite";
    if (mfrLower.contains("friedman") || nameLower.contains("friedman"))
        return "Friedman";
    if (mfrLower.contains("fuchs") || nameLower.contains("fuchs"))
        return "Fuchs";
    if (mfrLower.contains("gallien") || nameLower.contains("gallien"))
        return "Gallien-Krueger";
    if (mfrLower.contains("harris doyle") || nameLower.contains("harris doyle"))
        return "Harris Doyle";
    if (mfrLower.contains("hears") || nameLower.contains("hears"))
        return "HEARS";
    if (mfrLower.contains("hum audio") || nameLower.contains("laal"))
        return "HUM Audio Devices";
    if (mfrLower.contains("karanyi") || nameLower.contains("karanyi"))
        return "Karanyi Sounds";
    if (mfrLower.contains("kiive") || nameLower.contains("kiive"))
        return "Kiive Audio";
    if (mfrLower.contains("knif") || nameLower.contains("knif"))
        return "Knif Audio";
    if (mfrLower.contains("lindell") || nameLower.contains("lindell"))
        return "Lindell Audio";
    if (mfrLower.contains("looptrotter") || nameLower.contains("looptrotter"))
        return "Looptrotter";
    if (mfrLower.contains("louder than liftoff") || nameLower.contains("silver bullet"))
        return "Louder Than Liftoff";
    if (mfrLower.contains("maag") || mfrLower.contains("mäag") || nameLower.contains("maag") || nameLower.contains("mäag"))
        return "Mäag Audio";
    if (mfrLower.contains("maor appelbaum") || mfrLower.contains("hendyamps"))
        return "Maor Appelbaum & Hendyamps";
    if (mfrLower.contains("millennia") || nameLower.contains("millennia"))
        return "Millennia";
    if (mfrLower.contains("mixland") || nameLower.contains("mixland"))
        return "Mixland";
    if (mfrLower.contains("neold") || nameLower.contains("neold"))
        return "NEOLD";
    if (mfrLower.contains("noveltech") || nameLower.contains("noveltech"))
        return "Noveltech";
    if (mfrLower.contains("proaudiodsp") || mfrLower.contains("pro audio dsp") || nameLower.contains("dsm v"))
        return "Pro Audio DSP";
    if (mfrLower.contains("purple audio") || nameLower.contains("purple audio") || nameLower.contains("mc 77"))
        return "Purple Audio";
    if (mfrLower.contains("shadow hills") || nameLower.contains("shadow hills"))
        return "Shadow Hills";
    if (mfrLower.contains("ssl") || mfrLower.contains("solid state logic") || nameLower.contains("ssl"))
        return "SSL";
    if (mfrLower.contains("spl") || nameLower.startsWith("spl "))
        return "SPL";
    if (mfrLower.contains("suhr") || nameLower.contains("suhr"))
        return "Suhr";
    if (mfrLower.contains("swivel") || nameLower.contains("swivel"))
        return "Swivel Audio";
    if (mfrLower.contains("three-body") || mfrLower.contains("three body") || nameLower.contains("kirchhoff") || nameLower.contains("cenozoix"))
        return "Three-Body Technology";
    if (mfrLower.contains("thx") || nameLower.contains("thx"))
        return "THX";
    if (mfrLower.contains("tomo") || nameLower.contains("tomo") || nameLower.contains("lisa"))
        return "TOMO Audiolabs";
    if (mfrLower.contains("unfiltered") || nameLower.contains("unfiltered"))
        return "Unfiltered Audio";
    if (mfrLower.contains("vertigo") || nameLower.contains("vertigo"))
        return "Vertigo";
    if (mfrLower.contains("wedge force") || nameLower.contains("wedge force"))
        return "WEDGE FORCE";
    if (mfrLower.contains("schoeps") || nameLower.contains("schoeps"))
        return "Schoeps";
    if (mfrLower.contains("sonible") || nameLower.contains("sonible") || nameLower.contains("smart:reverb"))
        return "sonible";
    if (mfrLower.contains("dear reality") || nameLower.contains("dearvr"))
        return "Dear Reality";
    if (mfrLower.contains("trinity") || nameLower.contains("trinity"))
        return "Trinity";

    // Default to Plugin Alliance if no specific brand detected
    return "Plugin Alliance";
}

// Get display name with brand prefix removed (but keep bx_ prefix for Brainworx products)
inline juce::String getDisplayName(const juce::String& pluginName, const juce::String& brandName)
{
    auto name = pluginName;

    // Keep bx_ prefix for Brainworx products - it's part of the product name

    // Remove brand name prefix if present
    if (name.startsWithIgnoreCase(brandName + " "))
        name = name.substring(brandName.length() + 1);
    else if (name.startsWithIgnoreCase(brandName))
        name = name.substring(brandName.length()).trimStart();

    // Handle specific brand prefixes
    if (name.startsWithIgnoreCase("ACME Audio "))
        name = name.substring(11);
    else if (name.startsWithIgnoreCase("A/DA "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("ADPTR AUDIO "))
        name = name.substring(12);
    else if (name.startsWithIgnoreCase("ADPTR "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("AMEK "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Ampeg "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("Bettermaker "))
        name = name.substring(12);
    else if (name.startsWithIgnoreCase("Black Box Analog Design "))
        name = name.substring(24);
    else if (name.startsWithIgnoreCase("Black Box "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Chandler Limited "))
        name = name.substring(17);
    else if (name.startsWithIgnoreCase("Chandler "))
        name = name.substring(9);
    else if (name.startsWithIgnoreCase("Dangerous Music "))
        name = name.substring(16);
    else if (name.startsWithIgnoreCase("Dangerous "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Diezel "))
        name = name.substring(7);
    else if (name.startsWithIgnoreCase("DS Audio "))
        name = name.substring(9);
    else if (name.startsWithIgnoreCase("elysia "))
        name = name.substring(7);
    else if (name.startsWithIgnoreCase("ENGL "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("fiedler audio "))
        name = name.substring(14);
    else if (name.startsWithIgnoreCase("fiedler "))
        name = name.substring(8);
    else if (name.startsWithIgnoreCase("Focusrite "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Friedman "))
        name = name.substring(9);
    else if (name.startsWithIgnoreCase("Fuchs "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("Gallien-Krueger "))
        name = name.substring(16);
    else if (name.startsWithIgnoreCase("Gallien Krueger "))
        name = name.substring(16);
    else if (name.startsWithIgnoreCase("Harris Doyle "))
        name = name.substring(13);
    else if (name.startsWithIgnoreCase("HEARS "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("HUM Audio Devices "))
        name = name.substring(18);
    else if (name.startsWithIgnoreCase("HUM Audio "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Karanyi Sounds "))
        name = name.substring(15);
    else if (name.startsWithIgnoreCase("Karanyi "))
        name = name.substring(8);
    else if (name.startsWithIgnoreCase("Kiive Audio "))
        name = name.substring(12);
    else if (name.startsWithIgnoreCase("Kiive "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("Knif Audio "))
        name = name.substring(11);
    else if (name.startsWithIgnoreCase("Knif "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Lindell Audio "))
        name = name.substring(14);
    else if (name.startsWithIgnoreCase("Lindell "))
        name = name.substring(8);
    else if (name.startsWithIgnoreCase("Looptrotter "))
        name = name.substring(12);
    else if (name.startsWithIgnoreCase("Louder Than Liftoff "))
        name = name.substring(20);
    else if (name.startsWithIgnoreCase("Maag Audio "))
        name = name.substring(11);
    else if (name.startsWithIgnoreCase("Mäag Audio "))
        name = name.substring(11);
    else if (name.startsWithIgnoreCase("Maag "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Mäag "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Millennia "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Mixland "))
        name = name.substring(8);
    else if (name.startsWithIgnoreCase("NEOLD "))
        name = name.substring(6);
    else if (name.startsWithIgnoreCase("Noveltech "))
        name = name.substring(10);
    else if (name.startsWithIgnoreCase("Pro Audio DSP "))
        name = name.substring(14);
    else if (name.startsWithIgnoreCase("Purple Audio "))
        name = name.substring(13);
    else if (name.startsWithIgnoreCase("Shadow Hills "))
        name = name.substring(13);
    else if (name.startsWithIgnoreCase("SSL "))
        name = name.substring(4);
    else if (name.startsWithIgnoreCase("SPL "))
        name = name.substring(4);
    else if (name.startsWithIgnoreCase("Suhr "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Swivel Audio "))
        name = name.substring(13);
    else if (name.startsWithIgnoreCase("THX "))
        name = name.substring(4);
    else if (name.startsWithIgnoreCase("TOMO Audiolabs "))
        name = name.substring(15);
    else if (name.startsWithIgnoreCase("TOMO "))
        name = name.substring(5);
    else if (name.startsWithIgnoreCase("Unfiltered Audio "))
        name = name.substring(17);
    else if (name.startsWithIgnoreCase("Unfiltered "))
        name = name.substring(11);
    else if (name.startsWithIgnoreCase("Vertigo "))
        name = name.substring(8);

    return name.trim();
}

} // namespace PALauncher
