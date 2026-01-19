/*
  ==============================================================================
    PluginData.h
    AUTO-GENERATED - DO NOT EDIT

    Generated: 2026-01-18 19:01:40
    Source: plugins.json

    To update: Edit plugins.json then run: python scripts/generate_plugin_data.py
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <map>

namespace PALauncher
{

// =============================================================================
// Plugin Metadata Structure
// =============================================================================

struct PluginMetadata
{
    juce::String id;           // Unique identifier (e.g., "ada_flanger")
    juce::String vstFileName;  // Exact VST3 reported name - used for matching
    juce::String displayName;  // Name shown in UI
    juce::String brand;        // Manufacturer name
    juce::String description;  // Plugin description text
    juce::String imageUrl;     // Thumbnail image URL
    juce::String productUrl;   // Product page URL
    juce::String category;     // Primary category
    juce::StringArray tags;    // Additional tags
};

// =============================================================================
// Plugin Database
// =============================================================================

inline const std::vector<PluginMetadata>& getPluginDatabase()
{
    static const std::vector<PluginMetadata> database = {
        {
            "acme_opticom_xla3",
            "Acme Opticom XLA-3",
            "ACME Audio Opticom CLA-3",
            "ACME Audio",
            "Triple-curve optical tube compressor with smooth leveling and harmonic warmth.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300196_93d7cf64-bfa3-470f-bbb9-96b1d2dde9f9.png",
            "https://www.plugin-alliance.com/en/products/acme_opticom_xla-3.html",
            "Compressors",
            {"2010s", "Optical"}
        },
        {
            "ada_flanger",
            "ADA Flanger",
            "ADA Flanger",
            "ADA",
            "Classic 1979 analog flanger with bucket-brigade circuitry for lush modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300339_ed23a5bb-1f30-4c03-ac02-a0bfb39dbc65.png",
            "https://www.plugin-alliance.com/en/products/ada_flanger.html",
            "Modulator",
            {"1970s"}
        },
        {
            "ada_std1",
            "ADA STD-1 Stereo Tapped Delay",
            "ADA STD-1 Stereo Tapped Delay",
            "ADA",
            "Rare 1980 stereo tapped analog delay for rich chorusing and doubling effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300339.png",
            "https://www.plugin-alliance.com/en/products/ada_std-1_stereo_tapped_delay.html",
            "Delays",
            {"1980s"}
        },
        {
            "adptr_metricab",
            "ADPTR MetricAB",
            "ADPTR Metric AB",
            "ADPTR Audio",
            "Reference comparison tool for A/B testing mixes against commercial releases.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300287_30b5be99-27d7-49b3-a39f-52f46cf45987.png",
            "https://www.plugin-alliance.com/en/products/adptr_metricab.html",
            "Meters",
            {"Original"}
        },
        {
            "adptr_sculpt",
            "ADPTR Sculpt",
            "ADPTR SCULPT",
            "ADPTR Audio",
            "Multiband dynamics with four parallel modules for transparent mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300351_d1d58e0b-eeef-492b-b534-e17d94d12c38.png",
            "https://www.plugin-alliance.com/en/products/adptr_sculpt.html",
            "Compressors",
            {"Original", "Multi-Band"}
        },
        {
            "adptr_streamliner",
            "Streamliner",
            "ADPTR Streamliner",
            "ADPTR Audio",
            "AI-assisted mastering with LUFS targeting and adaptive processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300287.png",
            "https://www.plugin-alliance.com/en/products/adptr_streamliner.html",
            "Meters",
            {"Original"}
        },
        {
            "amek_eq200",
            "EQ 200",
            "AMEK EQ 200",
            "AMEK",
            "Legendary analog parametric EQ with Massenburg-style precision.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300375_a06e2b91-11f1-4fc0-9d21-fe1b9a9de6b7.png",
            "https://www.plugin-alliance.com/en/products/amek_eq_200.html",
            "Equalizers",
            {"1970s", "Parametric"}
        },
        {
            "amek_mastering_compressor",
            "Mastering Compressor",
            "AMEK Mastering Compressor",
            "AMEK",
            "Smooth mastering compressor with versatile VCA and optical modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300375.png",
            "https://www.plugin-alliance.com/en/products/amek_mastering_compressor.html",
            "Compressors",
            {"1990s", "Mastering"}
        },
        {
            "ampeg_b15n",
            "B-15N",
            "Ampeg B-15N",
            "Ampeg",
            "The classic 1960 Portaflex bass amp with warm tube tone.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300306_f99f79f4-3b68-439a-a025-a1f90f6fbe13.png",
            "https://www.plugin-alliance.com/en/products/ampeg_b15n.html",
            "Amplifiers",
            {"1960s"}
        },
        {
            "ampeg_svt3pro",
            "SVT-3PRO",
            "Ampeg SVT-3PRO",
            "Ampeg",
            "Hybrid tube/solid-state bass amp with modern punch and clarity.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300306.png",
            "https://www.plugin-alliance.com/en/products/ampeg_svt3pro.html",
            "Amplifiers",
            {"1990s"}
        },
        {
            "ampeg_svtvr",
            "SVT-VR",
            "Ampeg SVT-VR",
            "Ampeg",
            "The legendary 1969 SVT all-tube bass amp with 300-watt power.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300154_2cb58dff-84c5-4f9d-aee6-bd1fce67d1d7.png",
            "https://www.plugin-alliance.com/en/products/ampeg_svtvr.html",
            "Amplifiers",
            {"1960s"}
        },
        {
            "ampeg_v4b",
            "V-4B",
            "Ampeg V-4B",
            "Ampeg",
            "100-watt all-tube bass amp from 1971 with classic SVT preamp.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300530_e5bf95b6-a1d5-4f20-8e9a-da1f1b22d0b8.png",
            "https://www.plugin-alliance.com/en/products/ampeg_v4b.html",
            "Amplifiers",
            {"1970s"}
        },
        {
            "bettermaker_eq232d",
            "EQ232D",
            "Bettermaker EQ232D",
            "Bettermaker",
            "Modern mastering EQ with Pultec-style passive curves and extended control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300325_45026c47-87af-406e-80a2-d5d5ee6bf93b.png",
            "https://www.plugin-alliance.com/en/products/bettermaker_eq232d.html",
            "Equalizers",
            {"2000s", "Mastering", "Passive"}
        },
        {
            "black_box_hg2",
            "HG-2",
            "Black Box Analog Design HG-2",
            "Black Box Analog Design",
            "Tube saturation processor with pentode and triode stages for rich harmonics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300097_1ec3b92b-f2f9-431f-b851-4ac0ce3e4971.png",
            "https://www.plugin-alliance.com/en/products/black_box_analog_design_hg-2.html",
            "Saturators",
            {"2010s"}
        },
        {
            "black_box_hg2ms",
            "HG-2MS",
            "Black Box Analog Design HG-2MS",
            "Black Box Analog Design",
            "Mid-side version of the HG-2 tube saturator for mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300097.png",
            "https://www.plugin-alliance.com/en/products/black_box_analog_design_hg-2ms.html",
            "Saturators",
            {"2010s"}
        },
        {
            "brainworx_bx_bassdude",
            "bx_bassdude",
            "Brainworx bx_bassdude",
            "Brainworx",
            "Bass amp simulator with Fender-style warmth and flexibility.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300113.png",
            "https://www.plugin-alliance.com/en/products/bx_bassdude.html",
            "Amplifiers",
            {"Original"}
        },
        {
            "brainworx_bx_console_focusrite",
            "bx_console Focusrite SC",
            "Brainworx bx_console Focusrite SC",
            "Brainworx",
            "Focusrite Studio Console emulation with 72 unique channels.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300296_c5d27ec6-1dcd-4ed1-acc7-bb8d1daab7ad.png",
            "https://www.plugin-alliance.com/en/products/bx_console_focusrite_sc.html",
            "Channel Strips",
            {"1980s"}
        },
        {
            "brainworx_bx_console_n",
            "bx_console N",
            "Brainworx bx_console N",
            "Brainworx",
            "Neve console channel strip with classic 1073-style EQ and preamp.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300203.png",
            "https://www.plugin-alliance.com/en/products/bx_console_n.html",
            "Channel Strips",
            {"1970s"}
        },
        {
            "brainworx_bx_console_ssl_4000_e",
            "bx_console SSL 4000 E",
            "Brainworx bx_console SSL 4000 E",
            "Brainworx",
            "SSL 4000 E console channel strip with 72 unique TMT-modeled channels.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300203_89c0db5e-13ab-428c-9f7d-b3d9e89e8a17.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_4000_e.html",
            "Channel Strips",
            {"1970s"}
        },
        {
            "brainworx_bx_console_ssl_4000_g",
            "bx_console SSL 4000 G",
            "Brainworx bx_console SSL 4000 G",
            "Brainworx",
            "SSL 4000 G console channel strip with enhanced EQ curves.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300238_e5d61c62-6974-460f-ad4f-1f5e5f78e1ab.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_4000_g.html",
            "Channel Strips",
            {"1980s"}
        },
        {
            "brainworx_bx_console_ssl_9000_j",
            "bx_console SSL 9000 J",
            "Brainworx bx_console SSL 9000 J",
            "Brainworx",
            "SSL 9000 J console channel strip for modern clarity and punch.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300352_6af23f8d-a7ba-4bc2-9d9f-cf9b78ee1e5f.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_9000_j.html",
            "Channel Strips",
            {"1990s"}
        },
        {
            "brainworx_bx_delay_2500",
            "bx_delay 2500",
            "Brainworx bx_delay 2500",
            "Brainworx",
            "Versatile stereo delay with extensive modulation and filtering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300111.png",
            "https://www.plugin-alliance.com/en/products/bx_delay_2500.html",
            "Delays",
            {"Original"}
        },
        {
            "brainworx_bx_digital_v3",
            "bx_digital V3",
            "Brainworx bx_digital V3",
            "Brainworx",
            "M/S mastering EQ with dynamic bands and mono-maker.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300071_2ff6ba00-4bef-40af-8ba7-dd11c9b27b23.png",
            "https://www.plugin-alliance.com/en/products/bx_digital_v3.html",
            "Equalizers",
            {"Original", "Mid-Side"}
        },
        {
            "brainworx_bx_distorange",
            "bx_distorange",
            "Brainworx bx_distorange",
            "Brainworx",
            "Boss DS-1 distortion pedal emulation from 1978.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300113_98f18c30-f64d-42ce-8b14-d4a8d2ed4db6.png",
            "https://www.plugin-alliance.com/en/products/bx_distorange.html",
            "Pedals",
            {"1970s"}
        },
        {
            "brainworx_bx_dynEQ_v2",
            "bx_dynEQ V2",
            "Brainworx bx_dynEQ V2",
            "Brainworx",
            "Dynamic EQ with M/S and surround support.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300096.png",
            "https://www.plugin-alliance.com/en/products/bx_dyneq_v2.html",
            "Equalizers",
            {"Original", "Dynamic"}
        },
        {
            "brainworx_bx_greenscreamer",
            "bx_greenscreamer",
            "Brainworx bx_greenscreamer",
            "Brainworx",
            "Ibanez TS808 Tube Screamer overdrive from 1979.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300113_5a36e09c-6a5e-46d4-b1a4-3e9ade3c2587.png",
            "https://www.plugin-alliance.com/en/products/bx_greenscreamer.html",
            "Pedals",
            {"1970s"}
        },
        {
            "brainworx_bx_hybrid_v2",
            "bx_hybrid V2",
            "Brainworx bx_hybrid V2",
            "Brainworx",
            "11-band M/S EQ with analog-modeled filters.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300096_8deef5cc-dc37-4b3c-a4e9-0ec4f390efb5.png",
            "https://www.plugin-alliance.com/en/products/bx_hybrid_v2.html",
            "Equalizers",
            {"Original", "Mid-Side"}
        },
        {
            "brainworx_bx_limiter_true_peak",
            "bx_limiter True Peak",
            "Brainworx bx_limiter True Peak",
            "Brainworx",
            "Transparent true peak limiter for streaming compliance.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300177_6d87aa2f-b1ba-402e-b025-0f51ac80abca.png",
            "https://www.plugin-alliance.com/en/products/bx_limiter_true_peak.html",
            "Limiters",
            {"Original"}
        },
        {
            "brainworx_bx_masterdesk",
            "bx_masterdesk",
            "Brainworx bx_masterdesk",
            "Brainworx",
            "One-knob mastering chain with saturation, dynamics, and limiting.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300177.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk.html",
            "Mastering",
            {"Original"}
        },
        {
            "brainworx_bx_masterdesk_classic",
            "bx_masterdesk Classic",
            "Brainworx bx_masterdesk Classic",
            "Brainworx",
            "Simplified mastering chain with analog saturation focus.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300265.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk_classic.html",
            "Mastering",
            {"Original"}
        },
        {
            "brainworx_bx_masterdesk_pro",
            "bx_masterdesk Pro",
            "Brainworx bx_masterdesk Pro",
            "Brainworx",
            "Advanced mastering suite with M/S control and multiple saturation modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300388_29ddb7bc-4d36-4b3f-889b-5f8bdb3e90b9.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk_pro.html",
            "Mastering",
            {"Original"}
        },
        {
            "brainworx_bx_meter",
            "bx_meter",
            "Brainworx bx_meter",
            "Brainworx",
            "Precision metering with peak, RMS, and correlation display.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300091_d0b86bd3-4809-4ec5-b0ed-c86c00dfbdd3.png",
            "https://www.plugin-alliance.com/en/products/bx_meter.html",
            "Meters",
            {"Original"}
        },
        {
            "brainworx_bx_opto",
            "bx_opto",
            "Brainworx bx_opto",
            "Brainworx",
            "Optical compressor with smooth leveling and vintage character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300283.png",
            "https://www.plugin-alliance.com/en/products/bx_opto.html",
            "Compressors",
            {"Original", "Optical"}
        },
        {
            "brainworx_bx_opto_pedal",
            "bx_opto Pedal",
            "Brainworx bx_opto Pedal",
            "Brainworx",
            "Stompbox-style optical compressor for guitar and bass.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300298_17f1df47-dc47-4cf2-a3a6-9fc4f6f18fa9.png",
            "https://www.plugin-alliance.com/en/products/bx_opto_pedal.html",
            "Pedals",
            {"Original"}
        },
        {
            "brainworx_bx_panEQ",
            "bx_panEQ",
            "Brainworx bx_panEQ",
            "Brainworx",
            "EQ with per-band stereo panning for creative sound design.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300091.png",
            "https://www.plugin-alliance.com/en/products/bx_paneq.html",
            "Equalizers",
            {"Original"}
        },
        {
            "brainworx_bx_refinement",
            "bx_refinement",
            "Brainworx bx_refinement",
            "Brainworx",
            "Harshness removal tool for taming digital brightness.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300274.png",
            "https://www.plugin-alliance.com/en/products/bx_refinement.html",
            "Equalizers",
            {"Original", "Dynamic"}
        },
        {
            "brainworx_bx_rockrack_v3",
            "bx_rockrack V3",
            "Brainworx bx_rockrack V3",
            "Brainworx",
            "Multi-amp guitar processor with cab simulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300113_dc4b6b3d-ae2b-445a-9b3f-30e8b97a39d9.png",
            "https://www.plugin-alliance.com/en/products/bx_rockrack_v3.html",
            "Suites",
            {"Original"}
        },
        {
            "brainworx_bx_saturator_v2",
            "bx_saturator V2",
            "Brainworx bx_saturator V2",
            "Brainworx",
            "M/S saturation with XL mode for enhanced harmonics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300110.png",
            "https://www.plugin-alliance.com/en/products/bx_saturator_v2.html",
            "Saturators",
            {"Original"}
        },
        {
            "brainworx_bx_shredspread",
            "bx_shredspread",
            "Brainworx bx_shredspread",
            "Brainworx",
            "Guitar stereo spreader for wide double-tracked tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300110_a2de98a9-67ab-48e2-b78a-fafd1b6c7b3e.png",
            "https://www.plugin-alliance.com/en/products/bx_shredspread.html",
            "Stereo Imagers",
            {"Original"}
        },
        {
            "brainworx_bx_ssl_v2",
            "bx_ssl V2",
            "Brainworx bx_ssl V2",
            "Brainworx",
            "SSL G-series bus compressor with M/S processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300262.png",
            "https://www.plugin-alliance.com/en/products/bx_ssl_v2.html",
            "Compressors",
            {"1980s", "Bus"}
        },
        {
            "brainworx_bx_subfilter",
            "bx_subfilter",
            "Brainworx bx_subfilter",
            "Brainworx",
            "Precision high-pass filter for sub-bass management.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300266.png",
            "https://www.plugin-alliance.com/en/products/bx_subfilter.html",
            "Utility",
            {"Original"}
        },
        {
            "brainworx_bx_subsynth",
            "bx_subsynth",
            "Brainworx bx_subsynth",
            "Brainworx",
            "Sub-bass synthesizer for adding low-end weight.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300164_3a93a60d-1a1f-4e83-9daf-97009caa08ef.png",
            "https://www.plugin-alliance.com/en/products/bx_subsynth.html",
            "Saturators",
            {"Original"}
        },
        {
            "brainworx_bx_townhouse",
            "bx_townhouse",
            "Brainworx bx_townhouse",
            "Brainworx",
            "SSL bus compressor from the legendary Townhouse Studios.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300157_d75f2fe4-c76d-4e45-a270-e1f9baafb74f.png",
            "https://www.plugin-alliance.com/en/products/bx_townhouse.html",
            "Compressors",
            {"1980s", "Bus"}
        },
        {
            "brainworx_bx_tuner",
            "bx_tuner",
            "Brainworx bx_tuner",
            "Brainworx",
            "Precision chromatic tuner with strobe and needle modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300091_dc9b81bb-a8ef-4f8d-b43f-6ff361d4fc8e.png",
            "https://www.plugin-alliance.com/en/products/bx_tuner.html",
            "Utility",
            {"Original"}
        },
        {
            "brainworx_bx_xl_v2",
            "bx_XL V2",
            "Brainworx bx_XL V2",
            "Brainworx",
            "M/S mastering limiter with XL saturation mode.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300172.png",
            "https://www.plugin-alliance.com/en/products/bx_xl_v2.html",
            "Limiters",
            {"Original"}
        },
        {
            "chandler_gav19t",
            "GAV19T",
            "Chandler Limited GAV19T",
            "Chandler Limited",
            "19-watt Class A tube amp inspired by vintage British designs from 2012.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300252.png",
            "https://www.plugin-alliance.com/en/products/chandler_gav19t.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "dangerous_bax_eq",
            "BAX EQ",
            "Dangerous Music BAX EQ",
            "Dangerous Music",
            "Mastering EQ based on the 1950s Baxandall tone control design, released 2009.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300120_e2f34e44-7d84-4fd1-ab13-2203f87a2b0e.png",
            "https://www.plugin-alliance.com/en/products/dangerous_bax_eq.html",
            "Equalizers",
            {"2000s", "Mastering"}
        },
        {
            "diezel_herbert",
            "Herbert",
            "Diezel Herbert",
            "Diezel",
            "180-watt high-gain German tube amp from 2000 for modern metal.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300175_27a0fd9b-cc3a-488e-8aab-f78b40b3dbdd.png",
            "https://www.plugin-alliance.com/en/products/diezel_herbert.html",
            "Amplifiers",
            {"2000s"}
        },
        {
            "diezel_vh4",
            "VH4",
            "Diezel VH4",
            "Diezel",
            "Legendary 1994 4-channel German tube amp with versatile gain staging.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300175.png",
            "https://www.plugin-alliance.com/en/products/diezel_vh4.html",
            "Amplifiers",
            {"1990s"}
        },
        {
            "ds_audio_thorn",
            "Thorn",
            "DS Audio Thorn",
            "DS Audio Software",
            "Spectral wavetable synthesizer with complex modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300291.png",
            "https://www.plugin-alliance.com/en/products/ds_audio_thorn.html",
            "Synthesizers",
            {"Original"}
        },
        {
            "elysia_alpha_compressor",
            "alpha compressor",
            "elysia alpha compressor",
            "elysia",
            "Mastering-grade discrete Class A compressor from 2008.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300144_c2df89cc-bc07-45d6-ae2c-59f5d437eb5b.png",
            "https://www.plugin-alliance.com/en/products/elysia_alpha_compressor.html",
            "Compressors",
            {"2000s", "Mastering", "VCA"}
        },
        {
            "elysia_museq",
            "museq",
            "elysia museq",
            "elysia",
            "Mastering EQ with warm tube-like character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300144.png",
            "https://www.plugin-alliance.com/en/products/elysia_museq.html",
            "Equalizers",
            {"2000s", "Mastering"}
        },
        {
            "elysia_mpressor",
            "mpressor",
            "elysia mpressor",
            "elysia",
            "Creative discrete Class A compressor with unique character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300099_5063cabe-5e9e-47b5-a3e9-8a35ecb6e2e0.png",
            "https://www.plugin-alliance.com/en/products/elysia_mpressor.html",
            "Compressors",
            {"2000s", "VCA"}
        },
        {
            "elysia_niveau_filter",
            "niveau filter",
            "elysia niveau filter",
            "elysia",
            "Single-knob tilt EQ for broad tonal shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300099.png",
            "https://www.plugin-alliance.com/en/products/elysia_niveau_filter.html",
            "Equalizers",
            {"2000s"}
        },
        {
            "engl_e646_vs",
            "E646 VS",
            "ENGL E646 VS",
            "ENGL",
            "Victor Smolski signature amp for progressive metal.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300236.png",
            "https://www.plugin-alliance.com/en/products/engl_e646_vs.html",
            "Amplifiers",
            {"2000s"}
        },
        {
            "engl_e765_rt",
            "E765 Retro Tube",
            "ENGL E765 Retro Tube",
            "ENGL",
            "Vintage-voiced German tube amp with EL34 power section.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300236_02a8e4cf-e49d-4e23-8b1a-ecd76e2f5bbe.png",
            "https://www.plugin-alliance.com/en/products/engl_e765_rt.html",
            "Amplifiers",
            {"2000s"}
        },
        {
            "engl_savage_120",
            "Savage 120",
            "ENGL Savage 120",
            "ENGL",
            "High-gain German metal amp from 1993 with tight low end.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300236_35ca3f14-ccc9-4b77-8393-bda3c13f2d7b.png",
            "https://www.plugin-alliance.com/en/products/engl_savage_120.html",
            "Amplifiers",
            {"1990s"}
        },
        {
            "fiedler_audio_dolby_atmos_composer",
            "Dolby Atmos Composer",
            "fiedler audio Dolby Atmos Composer",
            "fiedler audio",
            "3D audio panning and object-based mixing for Atmos.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300410.png",
            "https://www.plugin-alliance.com/en/products/fiedler_audio_dolby_atmos_composer.html",
            "3D & Surround Sound",
            {"Original"}
        },
        {
            "fiedler_audio_stage",
            "STAGE",
            "fiedler audio STAGE",
            "fiedler audio",
            "Advanced stereo positioning and depth control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300304_8e80efd1-82eb-4a45-9b6f-7ef1a4da64a5.png",
            "https://www.plugin-alliance.com/en/products/fiedler_audio_stage.html",
            "Stereo Imagers",
            {"Original"}
        },
        {
            "fiedler_audio_spacelab_interstellar",
            "Spacelab Interstellar",
            "fiedler audio Spacelab Interstellar",
            "fiedler audio",
            "Multichannel reverb for immersive audio production.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300516_ba88f00a-b2dc-49af-be33-5cdf43d64d51.png",
            "https://www.plugin-alliance.com/en/products/fiedler_audio_spacelab_interstellar.html",
            "Reverbs",
            {"Original"}
        },
        {
            "focusrite_red2_red3",
            "Red 2 & Red 3",
            "Focusrite Red 2 & Red 3",
            "Focusrite",
            "Classic 1993 Red range EQ and compressor with Neve-inspired sound.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300241_9157b7c4-e2b9-4ad3-87f9-58e7e4ac1a02.png",
            "https://www.plugin-alliance.com/en/products/focusrite_red_2_red_3.html",
            "Channel Strips",
            {"1990s"}
        },
        {
            "friedman_be100",
            "BE-100",
            "Friedman BE-100",
            "Friedman",
            "Boutique high-gain amp inspired by modified Plexi designs.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300246_03f32b94-be80-4b08-9d80-c11c6e4cc933.png",
            "https://www.plugin-alliance.com/en/products/friedman_be100.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "friedman_buxom_betty",
            "Buxom Betty",
            "Friedman Buxom Betty",
            "Friedman",
            "American-voiced clean to crunch amp with 6V6 power tubes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300246.png",
            "https://www.plugin-alliance.com/en/products/friedman_buxom_betty.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "friedman_ds40",
            "DS40",
            "Friedman DS40",
            "Friedman",
            "EL34-powered British tone with smooth gain.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300246_c8e3e3ca-e5f9-4b45-bc92-a62ed3e38da0.png",
            "https://www.plugin-alliance.com/en/products/friedman_ds40.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "fuchs_overdrive_supreme",
            "Overdrive Supreme 50",
            "Fuchs Overdrive Supreme 50",
            "Fuchs Audio",
            "Boutique American amp with transparent overdrive.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300256.png",
            "https://www.plugin-alliance.com/en/products/fuchs_overdrive_supreme.html",
            "Amplifiers",
            {"2000s"}
        },
        {
            "fuchs_train_45",
            "Train 45",
            "Fuchs Train 45",
            "Fuchs Audio",
            "Tweed-inspired tone with modern reliability.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300256_c70e1be7-9dc5-4f18-8c76-b4e462f00e45.png",
            "https://www.plugin-alliance.com/en/products/fuchs_train_45.html",
            "Amplifiers",
            {"2000s"}
        },
        {
            "gallien_krueger_800rb",
            "800RB",
            "Gallien-Krueger 800RB",
            "Gallien-Krueger",
            "Iconic 1982 bi-amped bass head with aggressive punch.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300355_4f8bbe3f-c5d8-4fc9-a64f-3f3d5a8d63b4.png",
            "https://www.plugin-alliance.com/en/products/gallien_krueger_800rb.html",
            "Amplifiers",
            {"1980s"}
        },
        {
            "kiive_xtcomp",
            "XTComp",
            "Kiive Audio XTComp",
            "Kiive Audio",
            "FET compressor inspired by the Empirical Labs Distressor (1995).",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300768.png",
            "https://www.plugin-alliance.com/en/products/kiive_xtcomp.html",
            "Compressors",
            {"1990s", "FET"}
        },
        {
            "knif_audio_soma",
            "Soma",
            "Knif Audio Soma",
            "Knif Audio",
            "Finnish passive tube EQ for mastering from 2013.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300455.png",
            "https://www.plugin-alliance.com/en/products/knif_audio_soma.html",
            "Equalizers",
            {"2010s", "Passive", "Mastering"}
        },
        {
            "lindell_254e",
            "254E",
            "Lindell Audio 254E",
            "Lindell Audio",
            "Neve 2254 diode bridge compressor from 1968.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300181_5bca4a41-cb3c-4e95-8a3c-71f79e99ea66.png",
            "https://www.plugin-alliance.com/en/products/lindell_254e.html",
            "Compressors",
            {"1960s", "Diode"}
        },
        {
            "lindell_6x500",
            "6X-500",
            "Lindell Audio 6X-500",
            "Lindell Audio",
            "Transformer-coupled preamp with passive EQ from 2012.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300181.png",
            "https://www.plugin-alliance.com/en/products/lindell_6x-500.html",
            "Preamps",
            {"2010s"}
        },
        {
            "lindell_7x500",
            "7X-500",
            "Lindell Audio 7X-500",
            "Lindell Audio",
            "FET compressor with 1176-style compression.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300199.png",
            "https://www.plugin-alliance.com/en/products/lindell_7x-500.html",
            "Compressors",
            {"2010s", "FET"}
        },
        {
            "lindell_80_series",
            "80 Series",
            "Lindell Audio 80 Series",
            "Lindell Audio",
            "Neve 1073/1084/2254 channel strip from 1970.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300313_f6a0b0b9-0860-4916-9b3c-2f35d21e6a41.png",
            "https://www.plugin-alliance.com/en/products/lindell_80_series.html",
            "Channel Strips",
            {"1970s"}
        },
        {
            "lindell_pex500",
            "PEX-500",
            "Lindell Audio PEX-500",
            "Lindell Audio",
            "Pultec-style passive EQ with modern enhancements.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300181_31ac25bc-f0c7-4e4b-b9fc-ff58f0e91e9e.png",
            "https://www.plugin-alliance.com/en/products/lindell_pex-500.html",
            "Equalizers",
            {"2010s", "Passive"}
        },
        {
            "lindell_retro",
            "Retro",
            "Lindell Audio Retro",
            "Lindell Audio",
            "Complete channel strip with vintage British character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300535_f4d5b9d7-aba0-4a31-8e0b-61cce47e0a4a.png",
            "https://www.plugin-alliance.com/en/products/lindell_retro.html",
            "Channel Strips",
            {"1970s"}
        },
        {
            "looptrotter_monster",
            "Monster",
            "Looptrotter Monster",
            "Looptrotter",
            "Aggressive bus compressor with harmonic saturation from 2013.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300459_b4a9c7d4-0f1b-4e2e-8cef-daeee4f8e0a6.png",
            "https://www.plugin-alliance.com/en/products/looptrotter_monster.html",
            "Compressors",
            {"2010s", "Bus"}
        },
        {
            "louder_than_liftoff_silver_bullet_mk2",
            "SILVER BULLET mk2",
            "Louder Than Liftoff SILVER BULLET mk2",
            "Louder Than Liftoff",
            "Console-style tone shaping with dual saturation paths from 2014.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png",
            "https://www.plugin-alliance.com/en/products/louder_than_liftoff_silver_bullet_mk2.html",
            "Saturators",
            {"2010s"}
        },
        {
            "maag_eq4",
            "EQ4",
            "Maag Audio EQ4",
            "Maag Audio",
            "6-band EQ with legendary Air Band for high-frequency presence.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300284_06dd5fd0-71b9-4f15-a9e4-ed4f64b94a84.png",
            "https://www.plugin-alliance.com/en/products/maag_eq4.html",
            "Equalizers",
            {"2010s"}
        },
        {
            "millennia_nseq2",
            "NSEQ-2",
            "Millennia NSEQ-2",
            "Millennia",
            "Mastering parametric EQ with tube/solid-state topology from 1999.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300218_24fa8cd1-4c88-4f76-a617-e314ea56ae09.png",
            "https://www.plugin-alliance.com/en/products/millennia_nseq-2.html",
            "Equalizers",
            {"1990s", "Mastering", "Parametric"}
        },
        {
            "millennia_tclv",
            "TCL-V",
            "Millennia TCL-V",
            "Millennia",
            "Tube compressor/limiter for transparent mastering dynamics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300218.png",
            "https://www.plugin-alliance.com/en/products/millennia_tclv.html",
            "Compressors",
            {"1990s", "Tube", "Mastering"}
        },
        {
            "neold_big_al",
            "BIG AL",
            "NEOLD BIG AL",
            "NEOLD",
            "Dual-stage tube saturator modeled from custom-built hardware with NOS components (2021).",
            "https://www.plugin-alliance.com/cdn/shop/files/BIG_AL_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_big_al.html",
            "Saturators",
            {"2020s"}
        },
        {
            "neold_u17",
            "U17",
            "NEOLD U17",
            "NEOLD",
            "Tube compressor modeled from rare 1954 broadcast compressor, custom hardware built for plugin (2022).",
            "https://www.plugin-alliance.com/cdn/shop/files/U17_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_u17.html",
            "Compressors",
            {"2020s", "Tube"}
        },
        {
            "neold_u2a",
            "U2A",
            "NEOLD U2A",
            "NEOLD",
            "LA-2A style optical compressor modeled from custom-built hardware (2023).",
            "https://www.plugin-alliance.com/cdn/shop/files/U2A_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_u2a.html",
            "Compressors",
            {"2020s", "Optical"}
        },
        {
            "neold_v76u73",
            "V76U73",
            "NEOLD V76U73",
            "NEOLD",
            "1950s Telefunken V76 preamp (1958) and U73 compressor (1954).",
            "https://www.plugin-alliance.com/cdn/shop/files/V76U73_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_v76u73.html",
            "Channel Strips",
            {"1950s"}
        },
        {
            "neold_warble",
            "WARBLE",
            "NEOLD WARBLE",
            "NEOLD",
            "Vintage tape modulation modeled from custom-built hardware (2021).",
            "https://www.plugin-alliance.com/cdn/shop/files/WARBLE_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_warble.html",
            "Lo-Fi",
            {"2020s"}
        },
        {
            "noveltech_character",
            "Character",
            "Noveltech Character",
            "Noveltech",
            "Intelligent tonal and dynamic enhancement by auto-adjusting complex parameters.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300068_1e2c9ec6-8b04-49e6-ac20-bfbc963d0481.png",
            "https://www.plugin-alliance.com/en/products/noveltech_character.html",
            "Saturators",
            {"Original"}
        },
        {
            "noveltech_vocal_enhancer",
            "Vocal Enhancer",
            "Noveltech Vocal Enhancer",
            "Noveltech",
            "Intelligent vocal processing for presence and clarity.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300068.png",
            "https://www.plugin-alliance.com/en/products/noveltech_vocal_enhancer.html",
            "Vocal Processing",
            {"Original"}
        },
        {
            "proaudiodsp_dsm_v3",
            "DSM V3",
            "ProAudioDSP DSM V3",
            "ProAudioDSP",
            "Spectral matching and dynamic control to capture and apply sonic character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300403_9bb5d6c3-5d94-46d0-86c4-f8c86bd9a7c3.png",
            "https://www.plugin-alliance.com/en/products/pro_audio_dsp_dsm_v3.html",
            "Equalizers",
            {"Original", "Dynamic"}
        },
        {
            "purple_audio_mc77",
            "MC77",
            "Purple Audio MC77",
            "Purple Audio",
            "1176 limiter recreation from 2002 with stereo processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png",
            "https://www.plugin-alliance.com/en/products/purple_audio_mc_77.html",
            "Compressors",
            {"2000s", "FET"}
        },
        {
            "schoeps_double_ms",
            "Double MS",
            "Schoeps Double MS",
            "Schoeps",
            "Double mid-side decoding and processing for surround recordings.",
            "https://schoeps.de/fileadmin/user_upload/_processed_/5/8/csm_DoubleMS_PlugIn_9e5c8e5c68.jpg",
            "https://www.plugin-alliance.com/en/products/schoeps_double_ms.html",
            "3D & Surround Sound",
            {"Original"}
        },
        {
            "schoeps_mono_upmix",
            "Mono Upmix",
            "Schoeps Mono Upmix",
            "Schoeps",
            "Convert mono recordings to immersive stereo and surround.",
            "https://schoeps.de/fileadmin/user_upload/_processed_/a/c/csm_MonoUpmix_0788687428.jpg",
            "https://www.plugin-alliance.com/en/products/schoeps_mono_upmix.html",
            "3D & Surround Sound",
            {"Original"}
        },
        {
            "shadow_hills_mastering_compressor",
            "Mastering Compressor",
            "Shadow Hills Mastering Compressor",
            "Shadow Hills",
            "Dual-stage compression with switchable output transformers from 2008.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300081_a9a2e16c-5b2f-47ae-9537-3073a3ed18f9.png",
            "https://www.plugin-alliance.com/en/products/shadow_hills_mastering_compressor.html",
            "Compressors",
            {"2000s", "Mastering"}
        },
        {
            "shadow_hills_mastering_compressor_class_a",
            "Mastering Compressor Class A",
            "Shadow Hills Mastering Compressor Class A",
            "Shadow Hills",
            "Class A version of the legendary mastering compressor from 2012.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300081.png",
            "https://www.plugin-alliance.com/en/products/shadow_hills_class_a_mastering_comp.html",
            "Compressors",
            {"2010s", "Mastering"}
        },
        {
            "sonible_smart:reverb",
            "smart:reverb",
            "sonible smart:reverb",
            "sonible",
            "AI-powered reverb that adapts to your source material.",
            "https://www.sonible.com/wp-content/uploads/2025/06/smartReverb2_productpage_header-logo.png",
            "https://www.plugin-alliance.com/en/products/x-sonible-smart-reverb.html",
            "Reverbs",
            {"Original"}
        },
        {
            "spl_attacker_plus",
            "Attacker Plus",
            "SPL Attacker Plus",
            "SPL",
            "Transient enhancer for adding punch and attack.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300303_cf082f7d-27b1-4317-874f-3732caec074d.png",
            "https://www.plugin-alliance.com/en/products/spl_attacker_plus.html",
            "Transient Shapers",
            {"2000s"}
        },
        {
            "spl_de_verb",
            "De-Verb",
            "SPL De-Verb",
            "SPL",
            "Reverb reduction tool for cleaning up room ambience.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_de-verb.html",
            "Restoration",
            {"Original"}
        },
        {
            "spl_de_verb_plus",
            "De-Verb Plus",
            "SPL De-Verb Plus",
            "SPL",
            "Advanced reverb reduction with more control and precision.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300305_8082d009-6270-4264-84f8-5801a3dad97e.png",
            "https://www.plugin-alliance.com/en/products/spl_de-verb_plus.html",
            "Restoration",
            {"Original"}
        },
        {
            "spl_drumxchanger",
            "DrumXchanger",
            "SPL DrumXchanger",
            "SPL",
            "Drum replacement and augmentation tool.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300020_b30bc9e9-b50a-4559-9e06-353e837f36fd.png",
            "https://www.plugin-alliance.com/en/products/spl_drumxchanger.html",
            "Utility",
            {"Original"}
        },
        {
            "spl_eq_ranger_plus",
            "EQ Ranger Plus",
            "SPL EQ Ranger Plus",
            "SPL",
            "Full-range parametric equalizer with precise control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300186_672ca1e9-1e63-43ec-9c48-8a7cdb66b8d0.png",
            "https://www.plugin-alliance.com/en/products/spl_eq_ranger_plus.html",
            "Equalizers",
            {"Original", "Parametric"}
        },
        {
            "spl_free_ranger",
            "Free Ranger",
            "SPL Free Ranger",
            "SPL",
            "Four-band EQ based on the Passeq circuit.",
            "https://www.plugin-alliance.com/cdn/shop/files/SPL_ranger_free.png",
            "https://www.plugin-alliance.com/en/products/spl_free_ranger.html",
            "Equalizers",
            {"2000s", "Passive"}
        },
        {
            "spl_hawkeye",
            "HawkEye",
            "SPL HawkEye",
            "SPL",
            "Metering suite with level, loudness, bit monitoring, vectorscope, and spectrum analyzer.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png",
            "https://www.plugin-alliance.com/en/products/spl_hawkeye.html",
            "Meters",
            {"Original"}
        },
        {
            "spl_iron",
            "IRON",
            "SPL IRON",
            "SPL",
            "Tube compressor from 2015 with dual-circuit topology for transparent mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300386_5a609eb0-4eb3-4780-82b2-2bc2077c677b.png",
            "https://www.plugin-alliance.com/en/products/spl_iron.html",
            "Compressors",
            {"2010s", "Tube", "Mastering"}
        },
        {
            "spl_mo_verb_plus",
            "Mo-Verb Plus",
            "SPL Mo-Verb Plus",
            "SPL",
            "Room simulation and reverb modeling.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300307_b8dc9794-488c-4ffc-af14-deaa77633c9e.png",
            "https://www.plugin-alliance.com/en/products/spl_mo-verb_plus.html",
            "Reverbs",
            {"Original"}
        },
        {
            "spl_passeq",
            "Passeq",
            "SPL Passeq",
            "SPL",
            "Six-band passive mastering EQ from 2007.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300014_41e6334f-ea81-4115-bcb2-ce021a984aae.png",
            "https://www.plugin-alliance.com/en/products/spl_passeq.html",
            "Equalizers",
            {"2000s", "Passive", "Mastering"}
        },
        {
            "spl_pq",
            "PQ",
            "SPL PQ",
            "SPL",
            "Mastering equalizer with five bands of precise control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300014.png",
            "https://www.plugin-alliance.com/en/products/spl_pq.html",
            "Equalizers",
            {"2000s", "Mastering"}
        },
        {
            "spl_transient_designer_plus",
            "Transient Designer Plus",
            "SPL Transient Designer Plus",
            "SPL",
            "Threshold-independent transient processing from 1998.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png",
            "https://www.plugin-alliance.com/en/products/spl_transient_designer_plus.html",
            "Transient Shapers",
            {"1990s"}
        },
        {
            "spl_twin_tube",
            "Twin Tube",
            "SPL Twin Tube",
            "SPL",
            "Dual tube saturation processor for warmth and harmonics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300025_b2bd856a-47b9-433c-b622-31dd8c2d61a0.png",
            "https://www.plugin-alliance.com/en/products/spl_twintube.html",
            "Saturators",
            {"2000s"}
        },
        {
            "spl_vitalizer_mk2_t",
            "Vitalizer MK2-T",
            "SPL Vitalizer MK2-T",
            "SPL",
            "Psychoacoustic processor from 1999 for enhancing bass and presence.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_vitalizer_mk2-t.html",
            "Saturators",
            {"1990s"}
        },
        {
            "suhr_pt100",
            "PT100",
            "Suhr PT100",
            "Suhr",
            "Three-channel amplifier from 2011 with American clean, British vintage, and high-gain tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300557_5b344abb-f597-41e9-ac6d-bd3885b474fc.png",
            "https://www.plugin-alliance.com/en/products/suhr_pt100.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "suhr_se100",
            "SE100",
            "Suhr SE100",
            "Suhr",
            "High-end guitar amplifier with versatile tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300558_7a885e73-7f6b-4a7c-b1ab-3b8bf2413932.png",
            "https://www.plugin-alliance.com/en/products/suhr_se100.html",
            "Amplifiers",
            {"2010s"}
        },
        {
            "three_body_technology_kirchoff_eq",
            "Kirchoff EQ",
            "Three-Body Technology Kirchoff EQ",
            "Three-Body Technology",
            "32-band parametric EQ with analog curves, dynamics processing, and vintage emulations.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300781_6b333574-9e0f-4247-9d6a-81a75d11eadd.png",
            "https://www.plugin-alliance.com/en/products/tbt_kirchhoff-eq.html",
            "Equalizers",
            {"Original", "Parametric", "Dynamic"}
        },
        {
            "tomo_audiolabs_lisa",
            "LISA",
            "TOMO Audiolabs LISA",
            "TOMO Audiolabs",
            "Six-band opto-compression dynamic EQ for sophisticated tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300635_b22c3561-6e15-4c4d-ad52-4ac96b0e9d92.png",
            "https://www.plugin-alliance.com/en/products/tomo_audiolabs_lisa.html",
            "Equalizers",
            {"Original", "Dynamic"}
        },
        {
            "unfiltered_audio_bass_mint",
            "Bass-Mint",
            "Unfiltered Audio Bass-Mint",
            "Unfiltered Audio",
            "Bass enhancement and synthesis for adding low-end weight.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300490_3df7645c-3a98-4c49-93be-3d4a9700d3e5.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_bass_mint.html",
            "Saturators",
            {"Original"}
        },
        {
            "unfiltered_audio_byome",
            "BYOME",
            "Unfiltered Audio BYOME",
            "Unfiltered Audio",
            "Modular effects with 40 unique types including reverbs, delays, and dynamics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300378_43bef938-0ea5-4f09-ad46-0b34c751df83.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_byome.html",
            "Multi-FX",
            {"Original"}
        },
        {
            "unfiltered_audio_dent_2",
            "Dent 2",
            "Unfiltered Audio Dent 2",
            "Unfiltered Audio",
            "Waveform manipulation with clipping algorithms, bit-crushing, and modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300342_49bc2c9c-005d-4e8a-a7ae-f2b85de716c1.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_dent_2.html",
            "Lo-Fi",
            {"Original"}
        },
        {
            "unfiltered_audio_fault",
            "Fault",
            "Unfiltered Audio Fault",
            "Unfiltered Audio",
            "Glitch and stutter effects for creative sound design.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300235_426efe25-abe9-4c9d-95d2-542c264e1dfa.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_fault.html",
            "Multi-FX",
            {"Original"}
        },
        {
            "unfiltered_audio_g8",
            "G8",
            "Unfiltered Audio G8",
            "Unfiltered Audio",
            "Dynamic gate with MIDI control and alternate modes for creative gating.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183_d5aedd52-8194-49bd-b280-24160da8aed4.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_g8.html",
            "Gates",
            {"Original"}
        },
        {
            "unfiltered_audio_indent_2",
            "Indent 2",
            "Unfiltered Audio Indent 2",
            "Unfiltered Audio",
            "Transient shaping with precise attack and sustain control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300343_766af22f-b8ac-43e8-b214-e6c3f008677a.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_indent_2.html",
            "Transient Shapers",
            {"Original"}
        },
        {
            "unfiltered_audio_instant_delay",
            "Instant Delay",
            "Unfiltered Audio Instant Delay",
            "Unfiltered Audio",
            "Zero-latency delay for creative timing effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300316_ce1f07a0-722d-4d3a-a1bf-b43231b62808.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_instant_delay.html",
            "Delays",
            {"Original"}
        },
        {
            "unfiltered_audio_lion",
            "LION",
            "Unfiltered Audio LION",
            "Unfiltered Audio",
            "Dual-oscillator synthesizer with 26 modes, 16 filters, and 40+ effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300413_87e9ac60-f714-4a6d-9e6a-7e6cd43a070f.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_lion.html",
            "Synthesizers",
            {"Original"}
        },
        {
            "unfiltered_audio_lo_fi_af",
            "LO-FI-AF",
            "Unfiltered Audio LO-FI-AF",
            "Unfiltered Audio",
            "Vintage degradation with four rearrangeable modules for nostalgic character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300492_3815c462-512d-438e-a1f7-9796ef5e7296.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_lo-fi-af.html",
            "Lo-Fi",
            {"Original"}
        },
        {
            "unfiltered_audio_needlepoint",
            "Needlepoint",
            "Unfiltered Audio Needlepoint",
            "Unfiltered Audio",
            "Vinyl and tape emulation for analog warmth and character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300663_e9b251cc-820d-41e8-86e9-f487dd48e022.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_needlepoint.html",
            "Lo-Fi",
            {"Original"}
        },
        {
            "unfiltered_audio_sandman",
            "Sandman",
            "Unfiltered Audio Sandman",
            "Unfiltered Audio",
            "Delay with sleep mode for infinite frozen repeats.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300264.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_sandman.html",
            "Delays",
            {"Original"}
        },
        {
            "unfiltered_audio_sandman_pro",
            "Sandman Pro",
            "Unfiltered Audio Sandman Pro",
            "Unfiltered Audio",
            "Sophisticated delay with multiple modes for echo to granular synthesis.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300264_331f5d02-0ec3-4e58-9218-1ffbbbf2a9f2.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_sandman_pro.html",
            "Delays",
            {"Original"}
        },
        {
            "unfiltered_audio_silo",
            "SILO",
            "Unfiltered Audio SILO",
            "Unfiltered Audio",
            "Spectral freezing and manipulation for ambient textures.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300512_2269d8cb-2801-4e4d-915c-7ad722d6d4a8.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_silo.html",
            "Reverbs",
            {"Original"}
        },
        {
            "unfiltered_audio_specops",
            "SpecOps",
            "Unfiltered Audio SpecOps",
            "Unfiltered Audio",
            "36 spectral effects applied to different frequency bands simultaneously.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300263_cda3010b-a419-4289-8245-3481b6409d10.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_specops.html",
            "Multi-FX",
            {"Original"}
        },
        {
            "unfiltered_audio_tails",
            "TAILS",
            "Unfiltered Audio TAILS",
            "Unfiltered Audio",
            "Next-gen reverb removing dissonances and transients with auto-ducking.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300493_90634ade-c965-41fd-a5fe-ed40d14cec59.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_tails.html",
            "Reverbs",
            {"Original"}
        },
        {
            "unfiltered_audio_triad",
            "TRIAD",
            "Unfiltered Audio TRIAD",
            "Unfiltered Audio",
            "Multi-band distortion with three independent processing bands.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300393_2300346d-45cc-4bd1-997d-10b1946db4e8.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_triad.html",
            "Saturators",
            {"Original"}
        },
        {
            "unfiltered_audio_zip",
            "Zip",
            "Unfiltered Audio Zip",
            "Unfiltered Audio",
            "Compressor/limiter with aggressive character and fast response.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300357_6d1acfe7-c862-4f57-aeeb-d9fe37986420.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_zip.html",
            "Compressors",
            {"Original"}
        },
        {
            "vertigo_vsc_2",
            "VSC-2",
            "Vertigo VSC-2",
            "Vertigo",
            "VCA compressor from 2007 with 1979-style VCAs for smooth, glossy compression.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300016_b2d9cdc4-0a57-4ea9-ac82-c9be994d59a3.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vsc-2.html",
            "Compressors",
            {"2000s", "VCA"}
        },
        {
            "vertigo_vsm_3",
            "VSM-3",
            "Vertigo VSM-3",
            "Vertigo",
            "Mastering saturation with dual harmonic circuitry for flexible tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300100_481634f1-902d-46ca-9da7-bbe7f2b83313.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vsm-3.html",
            "Saturators",
            {"2000s"}
        },
        {
            "adptr_audio_utopia",
            "Utopia",
            "ADPTR Audio Utopia",
            "ADPTR Audio",
            "Spectral reverb for lush, evolving, cinematic soundscapes with real-time harmonic transformation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301236.png",
            "https://www.plugin-alliance.com/en/products/adptr_utopia.html",
            "Reverbs",
            {"Original"}
        },
        {
            "adptr_audio_hype",
            "Hype",
            "ADPTR Audio Hype",
            "ADPTR Audio",
            "Multi-band enhancement with compression, harmonics, and stereo width adjustment.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300999_56d6bbd4-8d7d-408d-845b-51ae21f9a76c.png",
            "https://www.plugin-alliance.com/en/products/adptr_hype.html",
            "Saturators",
            {"Original"}
        },
        {
            "shadow_hills_optomax",
            "OptoMax",
            "Shadow Hills OptoMax",
            "Shadow Hills",
            "New generation optical compressor with expanded ratio, speed, push mode, and transformer options.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301332.jpg",
            "https://www.plugin-alliance.com/en/products/shadow_hills_optomax.html",
            "Compressors",
            {"2020s", "Optical"}
        },
        {
            "neold_rz062",
            "RZ062",
            "NEOLD RZ062",
            "NEOLD",
            "Recreation of the legendary 1960s Siemens Klangfilm tube equalizer with vintage warmth.",
            "https://www.plugin-alliance.com/cdn/shop/files/NEOLD_RZ062_GUI.jpg",
            "https://www.plugin-alliance.com/en/products/neold_rz062.html",
            "Equalizers",
            {"1960s"}
        },
        {
            "spl_vitalizer_mk3_t",
            "Vitalizer MK3-T",
            "SPL Vitalizer MK3-T",
            "SPL",
            "Mix finishing tool with frequency shaping, bass processing, and de-masking technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301205.png",
            "https://www.plugin-alliance.com/en/products/spl_vitalizer_mk3-t.html",
            "Mastering",
            {"2020s"}
        },
        {
            "elysia_alpha_compressor_v2",
            "alpha compressor V2",
            "elysia alpha compressor V2",
            "elysia",
            "Detailed emulation of revered analog mastering compressor with M/S capability and TMT technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301253.png",
            "https://www.plugin-alliance.com/en/products/elysia_alpha_compressor_v2.html",
            "Compressors",
            {"2000s", "VCA", "Mastering"}
        },
        {
            "maag_audio_eq4_ms",
            "EQ4 MS",
            "Maag Audio EQ4 MS",
            "Maag Audio",
            "Dual-channel mastering EQ with AIR BAND and M/S processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301107_7eb64f8c.png",
            "https://www.plugin-alliance.com/en/products/maag_eq4_ms.html",
            "Equalizers",
            {"2010s", "Mid-Side", "Mastering"}
        },
        {
            "spl_big",
            "BiG",
            "SPL BiG",
            "SPL",
            "TEC Award-winning stereo expander with unique stereo processing and AirBass EQ.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301157_b5d6244c.png",
            "https://www.plugin-alliance.com/en/products/spl_big.html",
            "Stereo Imagers",
            {"2010s"}
        },
        {
            "hears_perfection",
            "Perfection",
            "HEARS Perfection",
            "HEARS",
            "Personalized frequency correction addressing hearing loss for accurate mix monitoring.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301331.png",
            "https://www.plugin-alliance.com/en/products/hears_perfection.html",
            "Utility",
            {"Original"}
        },
        {
            "spl_machine_head",
            "Machine Head",
            "SPL Machine Head",
            "SPL",
            "Digital tape saturator with Original and Ultimate modes for authentic analog warmth.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301150_00d7f9ee.png",
            "https://www.plugin-alliance.com/en/products/spl_machine_head.html",
            "Saturators",
            {"Original"}
        },
        {
            "brainworx_bx_xl_v3",
            "bx_XL V3",
            "Brainworx bx_XL V3",
            "Brainworx",
            "M/S mastering limiter with four-stage limiting, XL harmonics, and advanced metering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300918_98828b43.png",
            "https://www.plugin-alliance.com/en/products/bx_xl_v3.html",
            "Limiters",
            {"Original"}
        },
        {
            "brainworx_bx_pulsar",
            "bx_pulsar",
            "Brainworx bx_pulsar",
            "Brainworx",
            "Creative delay with five modes, 8-step sequencer, and advanced modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301279_2.png",
            "https://www.plugin-alliance.com/en/products/bx_pulsar.html",
            "Delays",
            {"Original"}
        },
        {
            "vertigo_vss_2",
            "VSS-2",
            "Vertigo VSS-2",
            "Vertigo",
            "Channel strip combining VSC-3 compressor, VSE-4 EQ, and VSM-4 tube sections.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301211_c9e80b87.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vss-2.html",
            "Channel Strips",
            {"2010s"}
        },
        {
            "hum_audio_laal",
            "LAAL",
            "HUM Audio LAAL",
            "HUM Audio Devices",
            "Look Ahead Analog Limiter for mastering with fully analog look ahead delay line.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301243_6f932fc9.png",
            "https://www.plugin-alliance.com/en/products/hum_audio_laal.html",
            "Limiters",
            {"2020s"}
        },
        {
            "three_body_technology_cenozoix_compressor",
            "Cenozoix Compressor",
            "Three-Body Technology Cenozoix Compressor",
            "Three-Body Technology",
            "Next-gen compressor with 12 algorithms including modern and vintage emulations.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300982_3397fcd0.png",
            "https://www.plugin-alliance.com/en/products/tbt_cenozoix.html",
            "Compressors",
            {"Original"}
        },
        {
            "brainworx_bx_aura",
            "bx_aura",
            "Brainworx bx_aura",
            "Brainworx",
            "Creative reverb with five algorithms, gate/ducking, drive section, and freeze mode.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301029_e4a95235.png",
            "https://www.plugin-alliance.com/en/products/bx_aura.html",
            "Reverbs",
            {"Original"}
        },
        {
            "black_box_analog_design_hg_q",
            "HG-Q",
            "Black Box Analog Design HG-Q",
            "Black Box Analog Design",
            "Six-band EQ with dual circuit design, tube boosts, and solid-state cuts.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300902_7f6334fb.png",
            "https://www.plugin-alliance.com/en/products/black_box_hg-q.html",
            "Equalizers",
            {"2010s"}
        },
        {
            "lindell_audio_eq825",
            "EQ825",
            "Lindell Audio EQ825",
            "Lindell Audio",
            "Rare mastering EQ emulation with tube and transformer design.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301272.jpg",
            "https://www.plugin-alliance.com/en/products/lindell_eq825.html",
            "Equalizers",
            {"2010s", "Mastering"}
        },
        {
            "unfiltered_audio_battalion",
            "Battalion",
            "Unfiltered Audio Battalion",
            "Unfiltered Audio",
            "Modern drum machine with 20 synthesis engines and 1000+ samples.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301002_746463f1.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_battalion.html",
            "Synthesizers",
            {"Original"}
        },
        {
            "brainworx_bx_refinement_v3",
            "bx_refinement V3",
            "Brainworx bx_refinement V3",
            "Brainworx",
            "Dynamic EQ for removing harshness with tube saturation and de-esser.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301160.png",
            "https://www.plugin-alliance.com/en/products/bx_refinement_v3.html",
            "Equalizers",
            {"Original", "Dynamic"}
        }
    };
    return database;
}

// =============================================================================
// Metadata Lookup Function
// =============================================================================
//
// Finds plugin metadata by matching the VST3's reported name.
//
// Matching priority:
//   1. Exact match on vstFileName (case-insensitive)
//   2. Exact match on displayName (case-insensitive)
//   3. Partial match - vstFileName contains search or vice versa
//
// Returns nullptr if no match found.
//

inline const PluginMetadata* findPluginMetadata(const juce::String& vstReportedName)
{
    static bool initialized = false;
    static std::map<juce::String, const PluginMetadata*> vstNameLookup;
    static std::map<juce::String, const PluginMetadata*> displayNameLookup;

    const auto& database = getPluginDatabase();

    // Build lookup tables on first call
    if (!initialized)
    {
        for (const auto& plugin : database)
        {
            // Index by vstFileName (primary match)
            auto vstLower = plugin.vstFileName.toLowerCase();
            if (vstNameLookup.find(vstLower) == vstNameLookup.end())
                vstNameLookup[vstLower] = &plugin;

            // Index by displayName (secondary match)
            auto displayLower = plugin.displayName.toLowerCase();
            if (displayNameLookup.find(displayLower) == displayNameLookup.end())
                displayNameLookup[displayLower] = &plugin;
        }
        initialized = true;
    }

    auto searchLower = vstReportedName.toLowerCase();

    // 1. Try exact match on vstFileName
    auto it = vstNameLookup.find(searchLower);
    if (it != vstNameLookup.end())
        return it->second;

    // 2. Try exact match on displayName
    it = displayNameLookup.find(searchLower);
    if (it != displayNameLookup.end())
        return it->second;

    // 3. Try partial match (for plugins with slightly different names)
    for (const auto& plugin : database)
    {
        if (plugin.vstFileName.containsIgnoreCase(vstReportedName) ||
            vstReportedName.containsIgnoreCase(plugin.vstFileName))
            return &plugin;
    }

    return nullptr;
}

} // namespace PALauncher
