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
// DISPLAY CATEGORY (Simplified for UI)
// ============================================
enum class DisplayCategory
{
    // Special - Always at top
    All,
    Favorites,
    Recent,

    // Effects (alphabetical)
    AmpSim,
    ChannelStrip,
    Compressors,
    Creative,
    Delay,
    Distortion,
    EQ,
    Expanders,
    Mastering,
    Metering,
    Mixing,
    Modulation,
    Pitch,
    Reverb,
    Saturation,
    StereoImaging,
    Utility,
    Vocal,

    // Instruments (alphabetical)
    Drums,
    Sampler,
    Synth,

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
    static const std::map<EffectCategory, juce::String> names = {
        {EffectCategory::Compressor, "Compressor"},
        {EffectCategory::Limiter, "Limiter"},
        {EffectCategory::Gate, "Gate"},
        {EffectCategory::Expander, "Expander"},
        {EffectCategory::DynamicsProcessor, "Dynamics"},
        {EffectCategory::TransientShaper, "Transient Shaper"},
        {EffectCategory::EnvelopeShaper, "Envelope Shaper"},
        {EffectCategory::DeEsser, "De-Esser"},
        {EffectCategory::EQ, "EQ"},
        {EffectCategory::Filter, "Filter"},
        {EffectCategory::FrequencyShifter, "Frequency Shifter"},
        {EffectCategory::Reverb, "Reverb"},
        {EffectCategory::Delay, "Delay"},
        {EffectCategory::Echo, "Echo"},
        {EffectCategory::Chorus, "Chorus"},
        {EffectCategory::Flanger, "Flanger"},
        {EffectCategory::Phaser, "Phaser"},
        {EffectCategory::Tremolo, "Tremolo"},
        {EffectCategory::Vibrato, "Vibrato"},
        {EffectCategory::Modulator, "Modulator"},
        {EffectCategory::Distortion, "Distortion"},
        {EffectCategory::Saturation, "Saturation"},
        {EffectCategory::BitCrusher, "Bit Crusher"},
        {EffectCategory::Exciter, "Exciter"},
        {EffectCategory::TapeEmulation, "Tape"},
        {EffectCategory::AmpSimulator, "Amp Simulator"},
        {EffectCategory::Preamp, "Preamp"},
        {EffectCategory::ChannelStrip, "Channel Strip"},
        {EffectCategory::MasteringSuite, "Mastering Suite"},
        {EffectCategory::Mastering, "Mastering"},
        {EffectCategory::PitchShifter, "Pitch Shifter"},
        {EffectCategory::Harmonizer, "Harmonizer"},
        {EffectCategory::StereoWidth, "Stereo Width"},
        {EffectCategory::SurroundTools, "Surround"},
        {EffectCategory::SpectralAnalysis, "Metering"},
        {EffectCategory::VocalProcessing, "Vocal"},
        {EffectCategory::Vocoder, "Vocoder"},
        {EffectCategory::GranularFX, "Granular"},
        {EffectCategory::MultiEffect, "Multi-FX"},
        {EffectCategory::Randomiser, "Randomiser"},
        {EffectCategory::DrumFX, "Drum FX"},
        {EffectCategory::DJTools, "DJ Tools"},
        {EffectCategory::Enhancer, "Enhancer"},
        {EffectCategory::Sequencer, "Sequencer"},
        {EffectCategory::MIDIArp, "MIDI Arp"},
        {EffectCategory::ExpansionPack, "Expansion"},
        {EffectCategory::Unknown, "Unknown"}
    };

    auto it = names.find(cat);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getEraName(Era era)
{
    static const std::map<Era, juce::String> names = {
        {Era::Era_1920s, "1920s"},
        {Era::Era_1930s, "1930s"},
        {Era::Era_1940s, "1940s"},
        {Era::Era_1950s, "1950s - Tube Era"},
        {Era::Era_1960s, "1960s - Rock Era"},
        {Era::Era_1970s, "1970s - Console Era"},
        {Era::Era_1980s, "1980s - Digital Dawn"},
        {Era::Era_1990s, "1990s - Modern Analog"},
        {Era::Era_2000s, "2000s"},
        {Era::Era_2010s, "2010s"},
        {Era::Era_2020s, "2020s"},
        {Era::Era_Modern, "Modern / Digital"},
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
        {DisplayCategory::AmpSim, "Amp Simulators"},
        {DisplayCategory::ChannelStrip, "Channel Strips"},
        {DisplayCategory::Compressors, "Compressors"},
        {DisplayCategory::Creative, "Creative"},
        {DisplayCategory::Delay, "Delay"},
        {DisplayCategory::Distortion, "Distortion"},
        {DisplayCategory::EQ, "EQs"},
        {DisplayCategory::Expanders, "Expanders"},
        {DisplayCategory::Mastering, "Mastering"},
        {DisplayCategory::Metering, "Metering"},
        {DisplayCategory::Mixing, "Mixing"},
        {DisplayCategory::Modulation, "Modulation"},
        {DisplayCategory::Pitch, "Pitch"},
        {DisplayCategory::Reverb, "Reverb"},
        {DisplayCategory::Saturation, "Saturation"},
        {DisplayCategory::StereoImaging, "Stereo Imaging"},
        {DisplayCategory::Utility, "Utility"},
        {DisplayCategory::Vocal, "Vocal Processing"},

        // Instruments
        {DisplayCategory::Drums, "Drums"},
        {DisplayCategory::Sampler, "Samplers"},
        {DisplayCategory::Synth, "Synths"},

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
    return cat >= DisplayCategory::Brand_ACMEAudio && cat <= DisplayCategory::Brand_Vertigo;
}

} // namespace PALauncher
