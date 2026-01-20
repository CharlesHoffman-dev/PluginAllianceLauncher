/*
  ==============================================================================
    PluginSubcategories.h
    Plugin Alliance Launcher - Detailed Subcategory Definitions
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

namespace PALauncher
{

// ============================================
// COMPRESSOR SUBCATEGORIES (alphabetical)
// ============================================
enum class CompressorType
{
    Bus,            // Mix bus "glue" compressors
    Digital,        // Modern digital designs
    Diode,          // Neve style - colorful, punchy
    FET,            // 1176 style - fast attack, aggressive
    Mastering,      // Designed for mastering applications
    Mixing,         // General-purpose mix compression
    MultiBand,      // Frequency-selective compression
    Optical,        // LA-2A style - smooth, program-dependent
    Parallel,       // Designed for parallel compression
    Tube,           // Variable-mu, Fairchild style - warm, musical
    VCA,            // SSL, API, dbx - fast, precise, punchy
    Unknown
};

// ============================================
// EQ SUBCATEGORIES (alphabetical)
// ============================================
enum class EQType
{
    Analog,         // Analog-modeled EQ
    Console,        // Console channel EQ
    Digital,        // Modern digital design
    Dynamic,        // Frequency-dependent compression/expansion
    Graphic,        // Fixed frequency bands
    Linear,         // Linear phase EQ
    Mastering,      // Mastering-focused EQ
    MidSide,        // M/S processing capability
    MinimumPhase,   // Traditional minimum phase
    Mixing,         // General-purpose mix EQ
    Parametric,     // Fully adjustable bands (Q, freq, gain)
    Passive,        // Pultec-style passive EQ
    SemiParametric, // Fixed Q, adjustable freq/gain
    Shelving,       // High/low shelf focused
    Unknown
};

// ============================================
// REVERB SUBCATEGORIES (alphabetical)
// ============================================
enum class ReverbType
{
    Algorithmic,    // Digital algorithmic
    Ambient,        // Subtle ambient reverb
    Chamber,        // Echo chamber
    Convolution,    // IR-based reverb
    Gated,          // Gated reverb (80s style)
    Hall,           // Concert hall simulation
    Plate,          // EMT-style plate reverb
    Room,           // Small/medium room
    Shimmer,        // Pitch-shifted reverb tails
    Spring,         // Spring reverb
    Unknown
};

// ============================================
// DELAY SUBCATEGORIES (alphabetical)
// ============================================
enum class DelayType
{
    Analog,         // BBD/analog delay
    Digital,        // Clean digital delay
    Ducking,        // Ducking delay
    Granular,       // Granular delay
    Modulated,      // Delay with modulation
    MultiTap,       // Multiple delay taps
    PingPong,       // Stereo ping-pong
    Rhythmic,       // Tempo-synced patterns
    Tape,           // Tape echo emulation
    Unknown
};

// ============================================
// AMP SIMULATOR SUBCATEGORIES (alphabetical within groups)
// ============================================
enum class AmpType
{
    // By Instrument
    BassAmp,
    GuitarAmp,

    // By Origin
    American,       // Fender-style
    British,        // Marshall/Vox style
    German,         // Diezel, ENGL style

    // By Character
    Boutique,
    Clean,
    Crunch,
    HighGain,
    Modern,
    Vintage,

    // By Topology
    Hybrid,
    SolidState,
    Tube,

    Unknown
};

// ============================================
// SATURATION SUBCATEGORIES (alphabetical)
// ============================================
enum class SaturationType
{
    Console,        // Console/summing saturation
    Harmonic,       // Harmonic enhancement
    Tape,           // Tape saturation
    Transformer,    // Transformer color
    Transistor,     // Transistor clipping
    Tube,           // Tube saturation/warmth
    Unknown
};

// ============================================
// CHANNEL STRIP SUBCATEGORIES (alphabetical within groups)
// ============================================
enum class ChannelStripType
{
    // By Console Brand
    AMEK,           // AMEK consoles
    API,            // API consoles
    Focusrite,      // Focusrite ISA series
    Neve,           // Neve consoles
    SSL,            // Solid State Logic
    Trident,        // Trident consoles

    // By Era/Application
    Mastering,      // Mastering-focused
    Mixing,         // Mix-focused
    Modern,         // Modern console designs
    Recording,      // Recording-focused
    Vintage,        // Vintage console emulations

    Unknown
};

// ============================================
// LIMITER SUBCATEGORIES (alphabetical)
// ============================================
enum class LimiterType
{
    Brickwall,      // True peak limiting
    FET,            // FET-based limiting
    Lookahead,      // Lookahead limiting
    Mastering,      // Mastering limiters
    Soft,           // Soft limiting/clipping
    Tube,           // Tube limiting
    Unknown
};

// ============================================
// DISTORTION SUBCATEGORIES (alphabetical)
// ============================================
enum class DistortionType
{
    Amp,            // Amp-in-a-Box / Amp emulation pedals
    BitCrusher,     // Digital bit reduction
    Distortion,     // Hard clipping distortion
    Fuzz,           // Fuzz pedal style
    Overdrive,      // Soft clipping overdrive
    WaveShaper,     // Waveshaping distortion
    Unknown
};

// ============================================
// MODULATION SUBCATEGORIES (alphabetical)
// ============================================
enum class ModulationType
{
    Chorus,         // Chorus effect
    Flanger,        // Flanger effect
    Phaser,         // Phaser effect
    RingMod,        // Ring modulation
    Rotary,         // Leslie/rotary speaker
    Tremolo,        // Amplitude tremolo
    UniVibe,        // Uni-Vibe style
    Vibrato,        // Pitch vibrato
    Unknown
};

// ============================================
// GUITAR & BASS SUBCATEGORIES (alphabetical)
// ============================================
enum class GuitarBassType
{
    Amp,            // Amp simulators
    Pedal,          // Pedal effects (overdrive, distortion)
    Unknown
};

// ============================================
// MASTERING SUBCATEGORIES (alphabetical)
// ============================================
enum class MasteringType
{
    Clipper,        // Soft/hard clippers
    Compressor,     // Mastering compressors
    EQ,             // Mastering EQ
    Limiter,        // Mastering limiters
    Loudness,       // Loudness metering/matching
    Metering,       // Metering tools
    Suite,          // Complete mastering suites
    Unknown
};

// ============================================
// OTHER SUBCATEGORIES (alphabetical)
// ============================================
enum class OtherType
{
    Gates,              // Dynamic gates
    LoFi,               // Lo-fi/vintage effects
    Modulators,         // Chorus, Flanger, Phaser, Tremolo, etc.
    MultiFX,            // Multi-effects processors
    PitchCorrection,    // Pitch correction, harmonizers
    Restoration,        // Noise reduction, de-click, etc.
    StereoImagers,      // Stereo imaging/widening
    ThreeDAndSurround,  // 3D Audio / Surround sound
    TransientShapers,   // Transient shapers/designers
    Utility,            // Gain, phase, routing tools
    VocalProcessing,    // Vocal processing
    Vocoders,           // Vocoders
    Unknown
};

// ============================================
// Display Name Functions (alphabetical order)
// ============================================
inline juce::String getCompressorTypeName(CompressorType type)
{
    static const std::map<CompressorType, juce::String> names = {
        {CompressorType::Bus, "Bus"},
        {CompressorType::Digital, "Digital"},
        {CompressorType::Diode, "Diode"},
        {CompressorType::FET, "FET"},
        {CompressorType::Mastering, "Mastering"},
        {CompressorType::Mixing, "Mixing"},
        {CompressorType::MultiBand, "Multi-Band"},
        {CompressorType::Optical, "Optical"},
        {CompressorType::Parallel, "Parallel"},
        {CompressorType::Tube, "Tube"},
        {CompressorType::VCA, "VCA"},
        {CompressorType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getEQTypeName(EQType type)
{
    static const std::map<EQType, juce::String> names = {
        {EQType::Analog, "Analog"},
        {EQType::Console, "Console"},
        {EQType::Digital, "Digital"},
        {EQType::Dynamic, "Dynamic"},
        {EQType::Graphic, "Graphic"},
        {EQType::Linear, "Linear Phase"},
        {EQType::Mastering, "Mastering"},
        {EQType::MidSide, "Mid/Side"},
        {EQType::MinimumPhase, "Minimum Phase"},
        {EQType::Mixing, "Mixing"},
        {EQType::Parametric, "Parametric"},
        {EQType::Passive, "Passive"},
        {EQType::SemiParametric, "Semi-Parametric"},
        {EQType::Shelving, "Shelving"},
        {EQType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getReverbTypeName(ReverbType type)
{
    static const std::map<ReverbType, juce::String> names = {
        {ReverbType::Algorithmic, "Algorithmic"},
        {ReverbType::Ambient, "Ambient"},
        {ReverbType::Chamber, "Chamber"},
        {ReverbType::Convolution, "Convolution"},
        {ReverbType::Gated, "Gated"},
        {ReverbType::Hall, "Hall"},
        {ReverbType::Plate, "Plate"},
        {ReverbType::Room, "Room"},
        {ReverbType::Shimmer, "Shimmer"},
        {ReverbType::Spring, "Spring"},
        {ReverbType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getDelayTypeName(DelayType type)
{
    static const std::map<DelayType, juce::String> names = {
        {DelayType::Analog, "Analog"},
        {DelayType::Digital, "Digital"},
        {DelayType::Ducking, "Ducking"},
        {DelayType::Granular, "Granular"},
        {DelayType::Modulated, "Modulated"},
        {DelayType::MultiTap, "Multi-Tap"},
        {DelayType::PingPong, "Ping-Pong"},
        {DelayType::Rhythmic, "Rhythmic"},
        {DelayType::Tape, "Tape"},
        {DelayType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getAmpTypeName(AmpType type)
{
    static const std::map<AmpType, juce::String> names = {
        {AmpType::American, "American"},
        {AmpType::BassAmp, "Bass"},
        {AmpType::Boutique, "Boutique"},
        {AmpType::British, "British"},
        {AmpType::Clean, "Clean"},
        {AmpType::Crunch, "Crunch"},
        {AmpType::German, "German"},
        {AmpType::GuitarAmp, "Guitar"},
        {AmpType::HighGain, "High Gain"},
        {AmpType::Hybrid, "Hybrid"},
        {AmpType::Modern, "Modern"},
        {AmpType::SolidState, "Solid State"},
        {AmpType::Tube, "Tube"},
        {AmpType::Vintage, "Vintage"},
        {AmpType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getSaturationTypeName(SaturationType type)
{
    static const std::map<SaturationType, juce::String> names = {
        {SaturationType::Console, "Console"},
        {SaturationType::Harmonic, "Harmonic"},
        {SaturationType::Tape, "Tape"},
        {SaturationType::Transformer, "Transformer"},
        {SaturationType::Transistor, "Transistor"},
        {SaturationType::Tube, "Tube"},
        {SaturationType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getChannelStripTypeName(ChannelStripType type)
{
    static const std::map<ChannelStripType, juce::String> names = {
        {ChannelStripType::AMEK, "AMEK"},
        {ChannelStripType::API, "API"},
        {ChannelStripType::Focusrite, "Focusrite"},
        {ChannelStripType::Mastering, "Mastering"},
        {ChannelStripType::Mixing, "Mixing"},
        {ChannelStripType::Modern, "Modern"},
        {ChannelStripType::Neve, "Neve"},
        {ChannelStripType::Recording, "Recording"},
        {ChannelStripType::SSL, "SSL"},
        {ChannelStripType::Trident, "Trident"},
        {ChannelStripType::Vintage, "Vintage"},
        {ChannelStripType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getLimiterTypeName(LimiterType type)
{
    static const std::map<LimiterType, juce::String> names = {
        {LimiterType::Brickwall, "Brickwall"},
        {LimiterType::FET, "FET"},
        {LimiterType::Lookahead, "Lookahead"},
        {LimiterType::Mastering, "Mastering"},
        {LimiterType::Soft, "Soft"},
        {LimiterType::Tube, "Tube"},
        {LimiterType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getDistortionTypeName(DistortionType type)
{
    static const std::map<DistortionType, juce::String> names = {
        {DistortionType::Amp, "Amp-in-a-Box"},
        {DistortionType::BitCrusher, "Bit Crusher"},
        {DistortionType::Distortion, "Distortion"},
        {DistortionType::Fuzz, "Fuzz"},
        {DistortionType::Overdrive, "Overdrive"},
        {DistortionType::WaveShaper, "Wave Shaper"},
        {DistortionType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getModulationTypeName(ModulationType type)
{
    static const std::map<ModulationType, juce::String> names = {
        {ModulationType::Chorus, "Chorus"},
        {ModulationType::Flanger, "Flanger"},
        {ModulationType::Phaser, "Phaser"},
        {ModulationType::RingMod, "Ring Mod"},
        {ModulationType::Rotary, "Rotary"},
        {ModulationType::Tremolo, "Tremolo"},
        {ModulationType::UniVibe, "Uni-Vibe"},
        {ModulationType::Vibrato, "Vibrato"},
        {ModulationType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getGuitarBassTypeName(GuitarBassType type)
{
    static const std::map<GuitarBassType, juce::String> names = {
        {GuitarBassType::Amp, "Amplifier"},
        {GuitarBassType::Pedal, "Pedal"},
        {GuitarBassType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getMasteringTypeName(MasteringType type)
{
    static const std::map<MasteringType, juce::String> names = {
        {MasteringType::Clipper, "Clipper"},
        {MasteringType::Compressor, "Compressor"},
        {MasteringType::EQ, "EQ"},
        {MasteringType::Limiter, "Limiter"},
        {MasteringType::Loudness, "Loudness"},
        {MasteringType::Metering, "Metering"},
        {MasteringType::Suite, "Suite"},
        {MasteringType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getOtherTypeName(OtherType type)
{
    static const std::map<OtherType, juce::String> names = {
        {OtherType::Gates, "Gates"},
        {OtherType::LoFi, "Lo-Fi"},
        {OtherType::Modulators, "Modulators"},
        {OtherType::MultiFX, "Multi-FX"},
        {OtherType::PitchCorrection, "Pitch Correction"},
        {OtherType::Restoration, "Restoration"},
        {OtherType::StereoImagers, "Stereo Imagers"},
        {OtherType::ThreeDAndSurround, "3D & Surround"},
        {OtherType::TransientShapers, "Transient Shapers"},
        {OtherType::Utility, "Utility"},
        {OtherType::VocalProcessing, "Vocal Processing"},
        {OtherType::Vocoders, "Vocoders"},
        {OtherType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

} // namespace PALauncher
