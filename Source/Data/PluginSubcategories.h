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
// COMPRESSOR SUBCATEGORIES
// ============================================
enum class CompressorType
{
    Optical,        // LA-2A style
    VCA,            // SSL, API, dbx style
    FET,            // 1176 style
    Tube,           // Variable-mu, Fairchild style
    Diode,          // Neve style
    Digital,        // Modern digital designs
    MultiBand,      // Frequency-selective
    Parallel,       // Designed for parallel compression
    BusGlue,        // Mix bus compressors
    Mastering,      // Mastering applications
    Unknown
};

// ============================================
// EQ SUBCATEGORIES
// ============================================
enum class EQType
{
    Parametric,
    SemiParametric,
    Graphic,
    Shelving,
    Passive,        // Pultec-style
    Dynamic,
    Linear,         // Linear phase
    MinimumPhase,
    MidSide,
    Analog,
    Digital,
    Console,
    Mastering,
    Unknown
};

// ============================================
// REVERB SUBCATEGORIES
// ============================================
enum class ReverbType
{
    Hall,
    Room,
    Chamber,
    Plate,
    Spring,
    Convolution,
    Algorithmic,
    Shimmer,
    Gated,
    Ambient,
    Unknown
};

// ============================================
// DELAY SUBCATEGORIES
// ============================================
enum class DelayType
{
    Tape,
    Analog,
    Digital,
    PingPong,
    MultiTap,
    Modulated,
    Ducking,
    Rhythmic,
    Granular,
    Unknown
};

// ============================================
// AMP SIMULATOR SUBCATEGORIES
// ============================================
enum class AmpType
{
    // By Instrument
    GuitarAmp,
    BassAmp,

    // By Topology
    Tube,
    SolidState,
    Hybrid,

    // By Character
    Clean,
    Crunch,
    HighGain,
    Vintage,
    Modern,
    Boutique,

    // By Origin
    American,
    British,
    German,

    Unknown
};

// ============================================
// SATURATION SUBCATEGORIES
// ============================================
enum class SaturationType
{
    Tube,
    Tape,
    Transformer,
    Console,
    Transistor,
    Harmonic,
    Unknown
};

// ============================================
// CHANNEL STRIP SUBCATEGORIES
// ============================================
enum class ChannelStripType
{
    SSL,
    Neve,
    API,
    AMEK,
    Focusrite,
    Trident,
    Vintage,
    Modern,
    Recording,
    Mixing,
    Mastering,
    Unknown
};

// ============================================
// LIMITER SUBCATEGORIES
// ============================================
enum class LimiterType
{
    Brickwall,
    Soft,
    Tube,
    FET,
    Lookahead,
    Mastering,
    Unknown
};

// ============================================
// DISTORTION SUBCATEGORIES
// ============================================
enum class DistortionType
{
    Overdrive,
    Distortion,
    Fuzz,
    BitCrusher,
    WaveShaper,
    Amp,
    Unknown
};

// ============================================
// MODULATION SUBCATEGORIES
// ============================================
enum class ModulationType
{
    Chorus,
    Flanger,
    Phaser,
    Tremolo,
    Vibrato,
    Rotary,
    UniVibe,
    RingMod,
    Unknown
};

// ============================================
// Display Name Functions
// ============================================
inline juce::String getCompressorTypeName(CompressorType type)
{
    static const std::map<CompressorType, juce::String> names = {
        {CompressorType::Optical, "Optical"},
        {CompressorType::VCA, "VCA"},
        {CompressorType::FET, "FET"},
        {CompressorType::Tube, "Tube"},
        {CompressorType::Diode, "Diode"},
        {CompressorType::Digital, "Digital"},
        {CompressorType::MultiBand, "Multi-Band"},
        {CompressorType::Parallel, "Parallel"},
        {CompressorType::BusGlue, "Bus Glue"},
        {CompressorType::Mastering, "Mastering"},
        {CompressorType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getEQTypeName(EQType type)
{
    static const std::map<EQType, juce::String> names = {
        {EQType::Parametric, "Parametric"},
        {EQType::SemiParametric, "Semi-Parametric"},
        {EQType::Graphic, "Graphic"},
        {EQType::Shelving, "Shelving"},
        {EQType::Passive, "Passive"},
        {EQType::Dynamic, "Dynamic"},
        {EQType::Linear, "Linear Phase"},
        {EQType::MinimumPhase, "Minimum Phase"},
        {EQType::MidSide, "Mid/Side"},
        {EQType::Analog, "Analog"},
        {EQType::Digital, "Digital"},
        {EQType::Console, "Console"},
        {EQType::Mastering, "Mastering"},
        {EQType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getAmpTypeName(AmpType type)
{
    static const std::map<AmpType, juce::String> names = {
        {AmpType::GuitarAmp, "Guitar"},
        {AmpType::BassAmp, "Bass"},
        {AmpType::Tube, "Tube"},
        {AmpType::SolidState, "Solid State"},
        {AmpType::Hybrid, "Hybrid"},
        {AmpType::Clean, "Clean"},
        {AmpType::Crunch, "Crunch"},
        {AmpType::HighGain, "High Gain"},
        {AmpType::Vintage, "Vintage"},
        {AmpType::Modern, "Modern"},
        {AmpType::Boutique, "Boutique"},
        {AmpType::American, "American"},
        {AmpType::British, "British"},
        {AmpType::German, "German"},
        {AmpType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getSaturationTypeName(SaturationType type)
{
    static const std::map<SaturationType, juce::String> names = {
        {SaturationType::Tube, "Tube"},
        {SaturationType::Tape, "Tape"},
        {SaturationType::Transformer, "Transformer"},
        {SaturationType::Console, "Console"},
        {SaturationType::Transistor, "Transistor"},
        {SaturationType::Harmonic, "Harmonic"},
        {SaturationType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getChannelStripTypeName(ChannelStripType type)
{
    static const std::map<ChannelStripType, juce::String> names = {
        {ChannelStripType::SSL, "SSL"},
        {ChannelStripType::Neve, "Neve"},
        {ChannelStripType::API, "API"},
        {ChannelStripType::AMEK, "AMEK"},
        {ChannelStripType::Focusrite, "Focusrite"},
        {ChannelStripType::Trident, "Trident"},
        {ChannelStripType::Vintage, "Vintage"},
        {ChannelStripType::Modern, "Modern"},
        {ChannelStripType::Recording, "Recording"},
        {ChannelStripType::Mixing, "Mixing"},
        {ChannelStripType::Mastering, "Mastering"},
        {ChannelStripType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getReverbTypeName(ReverbType type)
{
    static const std::map<ReverbType, juce::String> names = {
        {ReverbType::Hall, "Hall"},
        {ReverbType::Room, "Room"},
        {ReverbType::Chamber, "Chamber"},
        {ReverbType::Plate, "Plate"},
        {ReverbType::Spring, "Spring"},
        {ReverbType::Convolution, "Convolution"},
        {ReverbType::Algorithmic, "Algorithmic"},
        {ReverbType::Shimmer, "Shimmer"},
        {ReverbType::Gated, "Gated"},
        {ReverbType::Ambient, "Ambient"},
        {ReverbType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getDelayTypeName(DelayType type)
{
    static const std::map<DelayType, juce::String> names = {
        {DelayType::Tape, "Tape"},
        {DelayType::Analog, "Analog"},
        {DelayType::Digital, "Digital"},
        {DelayType::PingPong, "Ping-Pong"},
        {DelayType::MultiTap, "Multi-Tap"},
        {DelayType::Modulated, "Modulated"},
        {DelayType::Ducking, "Ducking"},
        {DelayType::Rhythmic, "Rhythmic"},
        {DelayType::Granular, "Granular"},
        {DelayType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getLimiterTypeName(LimiterType type)
{
    static const std::map<LimiterType, juce::String> names = {
        {LimiterType::Brickwall, "Brickwall"},
        {LimiterType::Soft, "Soft"},
        {LimiterType::Tube, "Tube"},
        {LimiterType::FET, "FET"},
        {LimiterType::Lookahead, "Lookahead"},
        {LimiterType::Mastering, "Mastering"},
        {LimiterType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

inline juce::String getDistortionTypeName(DistortionType type)
{
    static const std::map<DistortionType, juce::String> names = {
        {DistortionType::Overdrive, "Overdrive"},
        {DistortionType::Distortion, "Distortion"},
        {DistortionType::Fuzz, "Fuzz"},
        {DistortionType::BitCrusher, "Bit Crusher"},
        {DistortionType::WaveShaper, "Wave Shaper"},
        {DistortionType::Amp, "Amp-in-a-Box"},
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
        {ModulationType::Tremolo, "Tremolo"},
        {ModulationType::Vibrato, "Vibrato"},
        {ModulationType::Rotary, "Rotary"},
        {ModulationType::UniVibe, "Uni-Vibe"},
        {ModulationType::RingMod, "Ring Mod"},
        {ModulationType::Unknown, "Unknown"}
    };
    auto it = names.find(type);
    return it != names.end() ? it->second : "Unknown";
}

} // namespace PALauncher
