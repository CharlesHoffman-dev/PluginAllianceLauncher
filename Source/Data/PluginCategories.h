/*
  ==============================================================================
    PluginCategories.h
    Plugin Alliance Launcher - Category and Era Definitions
    Based on Plugin Boutique taxonomy
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

namespace PALauncher
{

// ============================================
// EFFECTS CATEGORIES (46 types)
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
    // Effects
    All,
    EQ,
    Dynamics,
    Reverb,
    Delay,
    Modulation,
    Distortion,
    Saturation,
    AmpSim,
    ChannelStrip,
    Mastering,
    Pitch,
    StereoImaging,
    Vocal,
    Metering,
    Creative,
    Utility,

    // Instruments
    Synth,
    Drums,
    Sampler,

    // Special
    Favorites,
    Recent
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
        {DisplayCategory::All, "All"},
        {DisplayCategory::EQ, "EQ"},
        {DisplayCategory::Dynamics, "Dynamics"},
        {DisplayCategory::Reverb, "Reverb"},
        {DisplayCategory::Delay, "Delay"},
        {DisplayCategory::Modulation, "Modulation"},
        {DisplayCategory::Distortion, "Distortion"},
        {DisplayCategory::Saturation, "Saturation"},
        {DisplayCategory::AmpSim, "Amp Simulators"},
        {DisplayCategory::ChannelStrip, "Channel Strips"},
        {DisplayCategory::Mastering, "Mastering"},
        {DisplayCategory::Pitch, "Pitch"},
        {DisplayCategory::StereoImaging, "Stereo/Imaging"},
        {DisplayCategory::Vocal, "Vocal"},
        {DisplayCategory::Metering, "Metering"},
        {DisplayCategory::Creative, "Creative"},
        {DisplayCategory::Utility, "Utility"},
        {DisplayCategory::Synth, "Synths"},
        {DisplayCategory::Drums, "Drums"},
        {DisplayCategory::Sampler, "Samplers"},
        {DisplayCategory::Favorites, "Favorites"},
        {DisplayCategory::Recent, "Recent"}
    };

    auto it = names.find(cat);
    return it != names.end() ? it->second : "Unknown";
}

} // namespace PALauncher
