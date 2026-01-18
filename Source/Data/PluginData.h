/*
  ==============================================================================
    PluginData.h
    AUTO-GENERATED FILE - DO NOT EDIT DIRECTLY
    Generated: 2026-01-18 10:23:28

    Edit plugins.json and run: python scripts/generate_plugin_data.py
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <map>

namespace PALauncher
{

struct PluginMetadata
{
    juce::String id;           // Unique identifier (e.g., "ada_flanger")
    juce::String brand;        // Brand name (e.g., "A/DA")
    juce::String product;      // Product name (e.g., "Flanger")
    juce::String fullName;     // Full display name (e.g., "ADA Flanger")
    juce::String description;  // Short description
    juce::String imageUrl;     // Thumbnail image URL
    juce::String productUrl;   // Product page URL
    juce::String category;     // Primary category
    juce::StringArray tags;    // All tags (category, era, type, etc.)
};

inline std::vector<PluginMetadata> getPluginDatabase()
{
    return {
        {
            "acme_opticom_xla_3",
            "ACME Audio",
            "Opticom XLA-3",
            "ACME Opticom XLA-3",
            "Optical compressor with tube sounds and opto-electric vibe for dynamic control or harmonic coloration.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300211_137be455-e2d4-4035-9eee-f1ef6d7a3a15.png",
            "https://www.plugin-alliance.com/en/products/acme_opticom_xla-3.html",
            "",
            {}
        },
        {
            "ada_flanger",
            "A/DA",
            "Flanger",
            "ADA Flanger",
            "Bucket-brigade analog flanging with threshold, manual sweep, range, speed, and resonance controls.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300356_b75930af-e197-461f-a776-d0b40f6fbfd7.png",
            "https://www.plugin-alliance.com/en/products/ada_flanger.html",
            "",
            {}
        },
        {
            "ada_std_1_stereo_tapped_delay",
            "A/DA",
            "STD-1 Stereo Tapped Delay",
            "ADA STD-1 Stereo Tapped Delay",
            "Six independent delay taps with modulation and flexible stereo routing for lush multi-voiced effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300258_e4416d1c-8f75-4683-8195-cc03447e59a0.png",
            "https://www.plugin-alliance.com/en/products/ada_std-1_stereo_tapped_delay.html",
            "",
            {}
        },
        {
            "adptr_audio_metric_ab",
            "ADPTR Audio",
            "Metric AB",
            "ADPTR Audio Metric AB",
            "Reference plugin for side-by-side audio comparison with instant loudness matching and analysis modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300370_51fdb784-eaec-48b3-8609-4fccc7196d68.png",
            "https://www.plugin-alliance.com/en/products/adptr_metricab.html",
            "",
            {}
        },
        {
            "adptr_audio_sculpt",
            "ADPTR Audio",
            "Sculpt",
            "ADPTR Audio Sculpt",
            "Intelligent audio sculpting tool for dynamic processing and spectral shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300370.png",
            "https://www.plugin-alliance.com/en/products/adptr_sculpt.html",
            "",
            {}
        },
        {
            "adptr_audio_streamliner",
            "ADPTR Audio",
            "Streamliner",
            "ADPTR Audio Streamliner",
            "Preview how audio sounds across 20 streaming platforms by simulating codec compression and loudness normalization.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300537_a0567c85-b2b2-4bd1-9f46-8f546e962030.png",
            "https://www.plugin-alliance.com/en/products/adptr_streamliner.html",
            "",
            {}
        },
        {
            "amek_eq_200",
            "AMEK",
            "EQ 200",
            "AMEK EQ 200",
            "Classic 1970s-80s parametric equalizer emulation with transparent, precise analog sound.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300489_6767f358-fdda-4c8c-a54e-da06e303f0ef.png",
            "https://www.plugin-alliance.com/en/products/amek_eq_200.html",
            "",
            {}
        },
        {
            "amek_eq_250",
            "AMEK",
            "EQ 250",
            "AMEK EQ 250",
            "Vintage parametric equalizer with musical character for mixing and mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300489.png",
            "https://www.plugin-alliance.com/en/products/amek_eq_250.html",
            "",
            {}
        },
        {
            "amek_mastering_compressor",
            "AMEK",
            "Mastering Compressor",
            "AMEK Mastering Compressor",
            "Professional mastering compressor with transparent dynamics control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300489.png",
            "https://www.plugin-alliance.com/en/products/amek_mastering_compressor.html",
            "",
            {}
        },
        {
            "ampeg_b_15n",
            "Ampeg",
            "B-15N",
            "Ampeg B-15N",
            "Classic tube bass amplifier emulation with warm vintage tone.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300438.png",
            "https://www.plugin-alliance.com/en/products/ampeg_b15n.html",
            "",
            {}
        },
        {
            "ampeg_svt_3pro",
            "Ampeg",
            "SVT-3PRO",
            "Ampeg SVT-3PRO",
            "Hybrid tube/solid-state bass amplifier with modern versatility.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300438.png",
            "https://www.plugin-alliance.com/en/products/ampeg_svt3pro.html",
            "",
            {}
        },
        {
            "ampeg_svt_vr",
            "Ampeg",
            "SVT-VR",
            "Ampeg SVT-VR",
            "Legendary 300-watt bass amplifier with roaring bottom, punchy mids, and pleasant highs.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300438_138d8e73-8761-4454-8704-30db1d9bd58f.png",
            "https://www.plugin-alliance.com/en/products/ampeg_svtvr.html",
            "",
            {}
        },
        {
            "ampeg_svt_vr_classic",
            "Ampeg",
            "SVT-VR Classic",
            "Ampeg SVT-VR Classic",
            "Vintage recreation of the iconic SVT bass amplifier.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300438.png",
            "https://www.plugin-alliance.com/en/products/ampeg_svtvr_classic.html",
            "",
            {}
        },
        {
            "ampeg_v_4b",
            "Ampeg",
            "V-4B",
            "Ampeg V-4B",
            "All-tube bass amplifier with classic Ampeg warmth and character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300438.png",
            "https://www.plugin-alliance.com/en/products/ampeg_v4b.html",
            "",
            {}
        },
        {
            "bettermaker_eq232d",
            "Bettermaker",
            "EQ232D",
            "Bettermaker EQ232D",
            "Mastering-grade equalizer with Pultec-style controls for incredible low and high-end shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300421_fef58d06-aa5f-4482-8b6a-58c56f82a79a.png",
            "https://www.plugin-alliance.com/en/products/bettermaker_eq232d.html",
            "",
            {}
        },
        {
            "black_box_analog_design_hg_2",
            "Black Box Analog Design",
            "HG-2",
            "Black Box Analog Design HG-2",
            "Tube saturation emulating vacuum tubes and transformers for warmth and harmonic richness.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300259_1e8913ea-66da-4ac3-aee0-171e176dfa13.png",
            "https://www.plugin-alliance.com/en/products/black_box_analog_design_hg-2.html",
            "",
            {}
        },
        {
            "black_box_analog_design_hg_2ms",
            "Black Box Analog Design",
            "HG-2MS",
            "Black Box Analog Design HG-2MS",
            "Mid-side version of the HG-2 tube saturation unit for mastering applications.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300259.png",
            "https://www.plugin-alliance.com/en/products/black_box_analog_design_hg-2ms.html",
            "",
            {}
        },
        {
            "brainworx_bx_2098_eq",
            "Brainworx",
            "bx_2098 EQ",
            "Brainworx bx_2098 EQ",
            "Neve 2098 channel EQ emulation with classic British console character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300214.png",
            "https://www.plugin-alliance.com/en/products/bx_2098_eq.html",
            "",
            {}
        },
        {
            "brainworx_bx_bassdude",
            "Brainworx",
            "bx_bassdude",
            "Brainworx bx_bassdude",
            "Bass amplifier simulation for warm, punchy bass tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_bassdude.html",
            "",
            {}
        },
        {
            "brainworx_bx_blackdist2",
            "Brainworx",
            "bx_blackdist2",
            "Brainworx bx_blackdist2",
            "Guitar distortion pedal emulation with aggressive tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_blackdist2.html",
            "",
            {}
        },
        {
            "brainworx_bx_bluechorus2",
            "Brainworx",
            "bx_bluechorus2",
            "Brainworx bx_bluechorus2",
            "Classic chorus effect with warm analog character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_bluechorus2.html",
            "",
            {}
        },
        {
            "brainworx_bx_boom",
            "Brainworx",
            "bx_boom",
            "Brainworx bx_boom",
            "Low-frequency enhancer for adding weight and punch to mixes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_boom.html",
            "",
            {}
        },
        {
            "brainworx_bx_cleansweep_pro",
            "Brainworx",
            "bx_cleansweep Pro",
            "Brainworx bx_cleansweep Pro",
            "High-pass and low-pass filter for cleaning up mix frequencies.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_cleansweep_pro.html",
            "",
            {}
        },
        {
            "brainworx_bx_cleansweep_v2",
            "Brainworx",
            "bx_cleansweep V2",
            "Brainworx bx_cleansweep V2",
            "Simple hi-pass and lo-pass filter for cleaning up tracks.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_cleansweep_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_clipper",
            "Brainworx",
            "bx_clipper",
            "Brainworx bx_clipper",
            "Soft clipper for transparent peak limiting and saturation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_clipper.html",
            "",
            {}
        },
        {
            "brainworx_bx_console_amek_9099",
            "Brainworx",
            "bx_console AMEK 9099",
            "Brainworx bx_console AMEK 9099",
            "Rupert Neve-designed AMEK 9098i console emulation with musical EQs and dynamics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300556_e7ec008e-826c-4aaf-86d3-fa8cc6b0ab20.png",
            "https://www.plugin-alliance.com/en/products/bx_console_amek_9099.html",
            "",
            {}
        },
        {
            "brainworx_bx_console_n",
            "Brainworx",
            "bx_console N",
            "Brainworx bx_console N",
            "72-channel vintage analog console emulation with Tolerance Modeling Technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300345_47021cba-5c15-4974-aa89-ff492a889fed.png",
            "https://www.plugin-alliance.com/en/products/bx_console_n.html",
            "",
            {}
        },
        {
            "brainworx_bx_console_ssl_4000_e",
            "Brainworx",
            "bx_console SSL 4000 E",
            "Brainworx bx_console SSL 4000 E",
            "SSL 4000 E console channel with 72 different emulations and Tolerance Modeling.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300373_f5942771-0897-4d7f-8955-7795f96295a3.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_4000_e.html",
            "",
            {}
        },
        {
            "brainworx_bx_console_ssl_4000_g",
            "Brainworx",
            "bx_console SSL 4000 G",
            "Brainworx bx_console SSL 4000 G",
            "SSL 4000 G console channel emulation with classic British sound.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300373.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_4000_g.html",
            "",
            {}
        },
        {
            "brainworx_bx_console_ssl_9000_j",
            "Brainworx",
            "bx_console SSL 9000 J",
            "Brainworx bx_console SSL 9000 J",
            "SSL 9000 J console emulation for mixing with legendary 1990s-2000s character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300478_3bcb16b8-3645-45f3-9b99-4d738a5a344e.png",
            "https://www.plugin-alliance.com/en/products/bx_console_ssl_9000_j.html",
            "",
            {}
        },
        {
            "brainworx_bx_control_v2",
            "Brainworx",
            "bx_control V2",
            "Brainworx bx_control V2",
            "Monitor controller with speaker simulation and reference tools.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_control_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_crispytuner",
            "Brainworx",
            "bx_crispytuner",
            "Brainworx bx_crispytuner",
            "Vocal pitch correction with adjustable strength from subtle to dramatic tuning effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300564_0f72ee8a-9c4f-43b7-9916-c4e1feca8f07.png",
            "https://www.plugin-alliance.com/en/products/bx_crispytuner.html",
            "",
            {}
        },
        {
            "brainworx_bx_delay_2500",
            "Brainworx",
            "bx_delay 2500",
            "Brainworx bx_delay 2500",
            "Creative delay with M/S processing, modulation, ducking, and distortion effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300340_a4f01894-db7b-4d8a-93f4-3ada49c34241.png",
            "https://www.plugin-alliance.com/en/products/bx_delay2500.html",
            "",
            {}
        },
        {
            "brainworx_bx_digital_v3",
            "Brainworx",
            "bx_digital V3",
            "Brainworx bx_digital V3",
            "11-band Mid/Side equalizer with parametric filters, dynamic EQ, and advanced metering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300214_d6cd321d-80bd-4c41-bd6a-4b05198f3e30.png",
            "https://www.plugin-alliance.com/en/products/bx_digital_v3.html",
            "",
            {}
        },
        {
            "brainworx_bx_distorange",
            "Brainworx",
            "bx_distorange",
            "Brainworx bx_distorange",
            "Orange distortion pedal emulation for guitar tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_distorange.html",
            "",
            {}
        },
        {
            "brainworx_bx_dyneq_v2",
            "Brainworx",
            "bx_dynEQ V2",
            "Brainworx bx_dynEQ V2",
            "Dynamic EQ combining equalizer and compressor for frequency-based dynamic control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300008_23571076-2caa-4b69-809a-1d234d32eb18.png",
            "https://www.plugin-alliance.com/en/products/bx_dyneq_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_greenscreamer",
            "Brainworx",
            "bx_greenscreamer",
            "Brainworx bx_greenscreamer",
            "Tube Screamer overdrive pedal emulation for warm guitar tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_greenscreamer.html",
            "",
            {}
        },
        {
            "brainworx_bx_hybrid_v2",
            "Brainworx",
            "bx_hybrid V2",
            "Brainworx bx_hybrid V2",
            "11-band mixing and mastering equalizer with analog filter sound and digital workflow.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300097_74b90f56-7fc4-4c94-86f1-cdbb4ad2d724.png",
            "https://www.plugin-alliance.com/en/products/bx_hybrid_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_limiter",
            "Brainworx",
            "bx_limiter",
            "Brainworx bx_limiter",
            "Transparent brickwall limiter for mastering and mix bus.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300552.png",
            "https://www.plugin-alliance.com/en/products/bx_limiter.html",
            "",
            {}
        },
        {
            "brainworx_bx_limiter_true_peak",
            "Brainworx",
            "bx_limiter True Peak",
            "Brainworx bx_limiter True Peak",
            "Mastering limiter preventing intersample peaks without compromising sound quality.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300552_1d635dc7-5e4a-4717-8b41-3706351c5683.png",
            "https://www.plugin-alliance.com/en/products/bx_limiter_true_peak.html",
            "",
            {}
        },
        {
            "brainworx_bx_masterdesk",
            "Brainworx",
            "bx_masterdesk",
            "Brainworx bx_masterdesk",
            "Complete analog mastering system with intuitive three-step workflow.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300383_a2601b0c-d04f-4feb-9a7c-5af3dbf5d472.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk.html",
            "",
            {}
        },
        {
            "brainworx_bx_masterdesk_classic",
            "Brainworx",
            "bx_masterdesk Classic",
            "Brainworx bx_masterdesk Classic",
            "Classic version of the all-in-one mastering solution.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300383.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk_classic.html",
            "",
            {}
        },
        {
            "brainworx_bx_masterdesk_pro",
            "Brainworx",
            "bx_masterdesk PRO",
            "Brainworx bx_masterdesk PRO",
            "Professional mastering suite with expanded controls and flexibility.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300383.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk_pro.html",
            "",
            {}
        },
        {
            "brainworx_bx_masterdesk_true_peak",
            "Brainworx",
            "bx_masterdesk True Peak",
            "Brainworx bx_masterdesk True Peak",
            "Mastering suite with true peak limiting for streaming compliance.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300383.png",
            "https://www.plugin-alliance.com/en/products/bx_masterdesk_true_peak.html",
            "",
            {}
        },
        {
            "brainworx_bx_megadual",
            "Brainworx",
            "bx_megadual",
            "Brainworx bx_megadual",
            "Mesa Boogie Dual Rectifier emulation with three channels and eight tone modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160_cf331a7a-0d2e-4d93-a0e8-ca026d93f930.png",
            "https://www.plugin-alliance.com/en/products/bx_megadual.html",
            "",
            {}
        },
        {
            "brainworx_bx_megasingle",
            "Brainworx",
            "bx_megasingle",
            "Brainworx bx_megasingle",
            "Mesa Boogie Single Rectifier emulation for high-gain guitar tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_megasingle.html",
            "",
            {}
        },
        {
            "brainworx_bx_metal2",
            "Brainworx",
            "bx_metal2",
            "Brainworx bx_metal2",
            "Metal distortion pedal emulation for aggressive guitar tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_metal2.html",
            "",
            {}
        },
        {
            "brainworx_bx_meter",
            "Brainworx",
            "bx_meter",
            "Brainworx bx_meter",
            "Metering tool displaying peak, RMS, and dynamic range with M/S support.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300042.png",
            "https://www.plugin-alliance.com/en/products/bx_meter.html",
            "",
            {}
        },
        {
            "brainworx_bx_oberhausen",
            "Brainworx",
            "bx_oberhausen",
            "Brainworx bx_oberhausen",
            "Analog synthesizer with 32-voice polyphony, Tolerance Modeling, and M/S processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300404_8690b6b0-99e3-4490-91e0-4dbb9fd154ca.png",
            "https://www.plugin-alliance.com/en/products/bx_oberhausen.html",
            "",
            {}
        },
        {
            "brainworx_bx_opto",
            "Brainworx",
            "bx_opto",
            "Brainworx bx_opto",
            "Optical compressor with smooth, musical compression character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_opto.html",
            "",
            {}
        },
        {
            "brainworx_bx_opto_pedal",
            "Brainworx",
            "bx_opto Pedal",
            "Brainworx bx_opto Pedal",
            "Pedal-format optical compressor for guitar and bass.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_opto_pedal.html",
            "",
            {}
        },
        {
            "brainworx_bx_paneq",
            "Brainworx",
            "bx_panEQ",
            "Brainworx bx_panEQ",
            "Frequency-dependent panning for creative stereo placement.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_paneq.html",
            "",
            {}
        },
        {
            "brainworx_bx_refinement",
            "Brainworx",
            "bx_refinement",
            "Brainworx bx_refinement",
            "High-frequency taming tool for removing harshness from mixes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_refinement.html",
            "",
            {}
        },
        {
            "brainworx_bx_rockergain_100",
            "Brainworx",
            "bx_rockergain 100",
            "Brainworx bx_rockergain 100",
            "Orange Rockerverb 100 amplifier emulation for British rock tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_rockergain100.html",
            "",
            {}
        },
        {
            "brainworx_bx_rockrack_v3",
            "Brainworx",
            "bx_rockrack V3",
            "Brainworx bx_rockrack V3",
            "Multi-amp plugin with eight guitar and bass amps and 40 impulse responses.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300244_20a2ee7e-c696-432e-ae2f-641cd41b7723.png",
            "https://www.plugin-alliance.com/en/products/bx_rockrack_v3.html",
            "",
            {}
        },
        {
            "brainworx_bx_rockrack_v3_player",
            "Brainworx",
            "bx_rockrack V3 Player",
            "Brainworx bx_rockrack V3 Player",
            "Streamlined version of bx_rockrack for quick amp selection.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300244.png",
            "https://www.plugin-alliance.com/en/products/bx_rockrack_v3_player.html",
            "",
            {}
        },
        {
            "brainworx_bx_rooms",
            "Brainworx",
            "bx_rooMS",
            "Brainworx bx_rooMS",
            "Reverb simulating acoustic spaces and mechanical plates with M/S processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300218_b3b1d5e1-dcb0-4b24-a58a-3db127e0e259.png",
            "https://www.plugin-alliance.com/en/products/bx_rooms.html",
            "",
            {}
        },
        {
            "brainworx_bx_saturator_v2",
            "Brainworx",
            "bx_saturator V2",
            "Brainworx bx_saturator V2",
            "Multi-band Mid/Side saturation for warmth and perceived loudness.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300129_803f3461-6ee8-423c-840c-3569bca891c0.png",
            "https://www.plugin-alliance.com/en/products/bx_saturator_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_shredspread",
            "Brainworx",
            "bx_shredspread",
            "Brainworx bx_shredspread",
            "Guitar stereo widener with tone shaping for heavy guitar recordings.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_shredspread.html",
            "",
            {}
        },
        {
            "brainworx_bx_solo",
            "Brainworx",
            "bx_solo",
            "Brainworx bx_solo",
            "Mid/Side utility for monitoring and soloing M/S channels.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_solo.html",
            "",
            {}
        },
        {
            "brainworx_bx_stereomaker",
            "Brainworx",
            "bx_stereomaker",
            "Brainworx bx_stereomaker",
            "Mono-to-stereo converter for adding width to mono sources.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_stereomaker.html",
            "",
            {}
        },
        {
            "brainworx_bx_subfilter",
            "Brainworx",
            "bx_subfilter",
            "Brainworx bx_subfilter",
            "Sub-bass filter for cleaning up low frequencies.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_subfilter.html",
            "",
            {}
        },
        {
            "brainworx_bx_subsynth",
            "Brainworx",
            "bx_subsynth",
            "Brainworx bx_subsynth",
            "Sub-bass synthesizer for adding low-end weight to tracks.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_subsynth.html",
            "",
            {}
        },
        {
            "brainworx_bx_townhouse_buss_compressor",
            "Brainworx",
            "bx_townhouse Buss Compressor",
            "Brainworx bx_townhouse Buss Compressor",
            "Rare 1978 SSL-based buss compressor for smooth, cohesive mix glue.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300365_671a1cf2-d3e3-4a18-a54a-0fe613fbd987.png",
            "https://www.plugin-alliance.com/en/products/bx_townhouse_buss_compressor.html",
            "",
            {}
        },
        {
            "brainworx_bx_tuner",
            "Brainworx",
            "bx_tuner",
            "Brainworx bx_tuner",
            "Precision chromatic tuner for instruments.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_tuner.html",
            "",
            {}
        },
        {
            "brainworx_bx_xl_v2",
            "Brainworx",
            "bx_XL V2",
            "Brainworx bx_XL V2",
            "Mastering limiter with M/S processing for loudness maximization.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_xl_v2.html",
            "",
            {}
        },
        {
            "brainworx_bx_yellowdrive",
            "Brainworx",
            "bx_yellowdrive",
            "Brainworx bx_yellowdrive",
            "Boss OD overdrive pedal emulation for classic rock tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/bx_yellowdrive.html",
            "",
            {}
        },
        {
            "chandler_limited_gav19t",
            "Chandler Limited",
            "GAV19T",
            "Chandler Limited GAV19T",
            "British tube amplifier emulation with 75 impulse responses and added features.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300114_a26c0820-3eb1-42f1-b72c-81005a988f27.png",
            "https://www.plugin-alliance.com/en/products/chandler_gav19t.html",
            "",
            {}
        },
        {
            "dangerous_music_bax_eq",
            "Dangerous Music",
            "BAX EQ",
            "Dangerous Music BAX EQ",
            "Baxandall shelving filters for smooth tonal adjustments without artifacts.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300095_e8339764-5fb2-4554-b4d2-14fee7d1b140.png",
            "https://www.plugin-alliance.com/en/products/dangerous_bax_eq.html",
            "",
            {}
        },
        {
            "diezel_herbert",
            "Diezel",
            "Herbert",
            "Diezel Herbert",
            "High-gain tube amplifier emulation for modern metal tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300434.png",
            "https://www.plugin-alliance.com/en/products/diezel_herbert.html",
            "",
            {}
        },
        {
            "diezel_vh4",
            "Diezel",
            "VH4",
            "Diezel VH4",
            "Legendary tube amplifier with four channels from clean to massive distortion.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300434_bfdaa187-c253-4698-9ed7-c811a754c5ea.png",
            "https://www.plugin-alliance.com/en/products/diezel_vh4.html",
            "",
            {}
        },
        {
            "ds_audio_tantra_2",
            "DS Audio",
            "TANTRA 2",
            "DS Audio TANTRA 2",
            "Rhythmic multi-effects with eight stages including filtering, distortion, delay, and glitch.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300554_8ace881a-39b6-471d-9a28-fe0cf0673018.png",
            "https://www.plugin-alliance.com/en/products/ds_tantra_2.html",
            "",
            {}
        },
        {
            "ds_audio_thorn",
            "DS Audio",
            "Thorn",
            "DS Audio Thorn",
            "Spectral synthesis instrument for modern electronic sounds with harmonic control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300401_98febeee-bda8-4fe9-b1c6-ba8fa2d7eff9.png",
            "https://www.plugin-alliance.com/en/products/ds_thorn.html",
            "",
            {}
        },
        {
            "elysia_alpha_compressor",
            "elysia",
            "alpha compressor",
            "elysia alpha compressor",
            "Precision mastering compressor with M/S processing and attack/release automation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301253.png",
            "https://www.plugin-alliance.com/en/products/elysia_alpha_compressor.html",
            "",
            {}
        },
        {
            "elysia_karacter",
            "elysia",
            "karacter",
            "elysia karacter",
            "Three distortion modes from subtle enhancement to aggressive sound destruction.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300256_1b500d94-b2ab-4d3d-8537-32ac61b673c9.png",
            "https://www.plugin-alliance.com/en/products/elysia_karacter.html",
            "",
            {}
        },
        {
            "elysia_mpressor",
            "elysia",
            "mpressor",
            "elysia mpressor",
            "Versatile compressor with negative ratios and gain reduction limiter for creative effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300018_1635b21e-7b69-439c-ba1b-37ce6236bbfc.png",
            "https://www.plugin-alliance.com/en/products/elysia_mpressor.html",
            "",
            {}
        },
        {
            "elysia_museq",
            "elysia",
            "museq",
            "elysia museq",
            "Musical equalizer with warm analog character and precise control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300018.png",
            "https://www.plugin-alliance.com/en/products/elysia_museq.html",
            "",
            {}
        },
        {
            "elysia_niveau_filter",
            "elysia",
            "niveau filter",
            "elysia niveau filter",
            "Simple tilt EQ for quick tonal adjustments.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300018.png",
            "https://www.plugin-alliance.com/en/products/elysia_niveau_filter.html",
            "",
            {}
        },
        {
            "elysia_nvelope",
            "elysia",
            "nvelope",
            "elysia nvelope",
            "Transient shaper controlling attack and sustain with frequency-based processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300145_9163302c-3621-412f-b57b-86b466130f7a.png",
            "https://www.plugin-alliance.com/en/products/elysia_nvelope.html",
            "",
            {}
        },
        {
            "elysia_phil's_cascade",
            "elysia",
            "Phil's Cascade",
            "elysia Phil's Cascade",
            "Cascading saturation stages for rich harmonic enhancement.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300018.png",
            "https://www.plugin-alliance.com/en/products/elysia_phils_cascade.html",
            "",
            {}
        },
        {
            "engl_e646_vs",
            "ENGL",
            "E646 VS",
            "ENGL E646 VS",
            "ENGL Victor Smolski signature amplifier for progressive metal tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300483.png",
            "https://www.plugin-alliance.com/en/products/engl_e646_vs.html",
            "",
            {}
        },
        {
            "engl_e765_rt",
            "ENGL",
            "E765 RT",
            "ENGL E765 RT",
            "ENGL Retro Tube amplifier with vintage-inspired high-gain tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300483.png",
            "https://www.plugin-alliance.com/en/products/engl_e765_rt.html",
            "",
            {}
        },
        {
            "engl_savage_120",
            "ENGL",
            "Savage 120",
            "ENGL Savage 120",
            "Legendary amplifier with four channels and 100+ recording chains.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300483_7726526f-00a8-4ebc-b38c-b344d7f42349.png",
            "https://www.plugin-alliance.com/en/products/engl_savage_120.html",
            "",
            {}
        },
        {
            "fiedler_audio_stage",
            "fiedler audio",
            "stage",
            "fiedler audio stage",
            "Stereo-spatial processing adding depth, width, and dimension through psychoacoustic algorithms.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300309_43e9ff7b-b505-4425-8a9d-c4b6954b2b06.png",
            "https://www.plugin-alliance.com/en/products/fiedler_audio_stage.html",
            "",
            {}
        },
        {
            "focusrite_sc_channel_strip",
            "Focusrite",
            "SC Channel Strip",
            "Focusrite SC Channel Strip",
            "Focusrite console channel strip with EQ and dynamics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300345.png",
            "https://www.plugin-alliance.com/en/products/bx_console_focusrite_sc.html",
            "",
            {}
        },
        {
            "friedman_be_100",
            "Friedman",
            "BE-100",
            "Friedman BE-100",
            "Modified Marshall Plexi design with versatile clean to saturated tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300435_2754fb79-473f-4297-9053-282544fea9df.png",
            "https://www.plugin-alliance.com/en/products/friedman_be100.html",
            "",
            {}
        },
        {
            "friedman_buxom_betty",
            "Friedman",
            "Buxom Betty",
            "Friedman Buxom Betty",
            "Friedman amplifier with full-bodied clean and crunch tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300435.png",
            "https://www.plugin-alliance.com/en/products/friedman_buxom_betty.html",
            "",
            {}
        },
        {
            "friedman_ds_40",
            "Friedman",
            "DS-40",
            "Friedman DS-40",
            "Friedman Dirty Shirley amplifier for classic rock tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300435.png",
            "https://www.plugin-alliance.com/en/products/friedman_ds40.html",
            "",
            {}
        },
        {
            "fuchs_overdrive_supreme_50",
            "Fuchs",
            "Overdrive Supreme 50",
            "Fuchs Overdrive Supreme 50",
            "Boutique amplifier with smooth overdrive and touch sensitivity.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300435.png",
            "https://www.plugin-alliance.com/en/products/fuchs_overdrive_supreme_50.html",
            "",
            {}
        },
        {
            "fuchs_train_ii",
            "Fuchs",
            "Train II",
            "Fuchs Train II",
            "High-gain Fuchs amplifier for modern rock and metal.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300435.png",
            "https://www.plugin-alliance.com/en/products/fuchs_train_ii.html",
            "",
            {}
        },
        {
            "gallien_krueger_800rb",
            "Gallien-Krueger",
            "800RB",
            "Gallien-Krueger 800RB",
            "Legendary 1982 bass amp with dual power amplifiers and patented Voicing Filters.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300351_9869025a-e5c3-4f1a-bb8c-8c5e7c1c1791.png",
            "https://www.plugin-alliance.com/en/products/gallien_krueger_800rb.html",
            "",
            {}
        },
        {
            "harris_doyle_natalus_dsceq",
            "Harris Doyle",
            "Natalus DSCEQ",
            "Harris Doyle Natalus DSCEQ",
            "Dynamic spectral control equalizer for precise frequency shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/harris_doyle_natalus_dsceq.html",
            "",
            {}
        },
        {
            "kiive_audio_tape_face",
            "Kiive Audio",
            "Tape Face",
            "Kiive Audio Tape Face",
            "Tape saturation emulation for analog warmth and character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/kiive_tape_face.html",
            "",
            {}
        },
        {
            "kiive_audio_xtressor",
            "Kiive Audio",
            "Xtressor",
            "Kiive Audio Xtressor",
            "Aggressive compressor/distortion hybrid for extreme dynamics processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/kiive_xtressor.html",
            "",
            {}
        },
        {
            "knif_audio_knifonium",
            "Knif Audio",
            "Knifonium",
            "Knif Audio Knifonium",
            "Rare vacuum tube synthesizer with 8 voices and studio-grade effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300471_d66727a9-586b-47d0-97ed-9f176c296269.png",
            "https://www.plugin-alliance.com/en/products/knif_audio_knifonium.html",
            "",
            {}
        },
        {
            "knif_audio_soma_eq",
            "Knif Audio",
            "Soma EQ",
            "Knif Audio Soma EQ",
            "Tube equalizer with musical character and smooth response.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300471.png",
            "https://www.plugin-alliance.com/en/products/knif_audio_soma.html",
            "",
            {}
        },
        {
            "lindell_audio_254e",
            "Lindell Audio",
            "254E",
            "Lindell Audio 254E",
            "Classic limiting amplifier emulation for smooth compression.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_254e.html",
            "",
            {}
        },
        {
            "lindell_audio_354e",
            "Lindell Audio",
            "354E",
            "Lindell Audio 354E",
            "Pultec-style passive EQ for musical tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_354e.html",
            "",
            {}
        },
        {
            "lindell_audio_50_series",
            "Lindell Audio",
            "50 Series",
            "Lindell Audio 50 Series",
            "500-series channel strip with preamp, EQ, and compression.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_50_series.html",
            "",
            {}
        },
        {
            "lindell_audio_69_series",
            "Lindell Audio",
            "69 Series",
            "Lindell Audio 69 Series",
            "Neve-style channel strip with transformer coloration.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_69_series.html",
            "",
            {}
        },
        {
            "lindell_audio_6x_500",
            "Lindell Audio",
            "6X-500",
            "Lindell Audio 6X-500",
            "500-series compressor with vintage character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_6x-500.html",
            "",
            {}
        },
        {
            "lindell_audio_7x_500",
            "Lindell Audio",
            "7X-500",
            "Lindell Audio 7X-500",
            "FET compressor for controlling aggressive transients with optional saturation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178_8bb5104f-8127-409a-89ec-25840ed22e19.png",
            "https://www.plugin-alliance.com/en/products/lindell_7x-500.html",
            "",
            {}
        },
        {
            "lindell_audio_80_series",
            "Lindell Audio",
            "80 Series",
            "Lindell Audio 80 Series",
            "Vintage British console with 32 tolerance-modeling channels for authentic analog character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300475_de30a79f-c507-4963-9d9f-b09b50e2b91b.png",
            "https://www.plugin-alliance.com/en/products/lindell_80_series.html",
            "",
            {}
        },
        {
            "lindell_audio_902_de_esser",
            "Lindell Audio",
            "902 De-esser",
            "Lindell Audio 902 De-esser",
            "Classic de-esser automatically reducing sibilance without manual threshold adjustment.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300626_a2edb61f-a1c5-400e-96cb-656bbbda8fa9.png",
            "https://www.plugin-alliance.com/en/products/lindell_902_de-esser.html",
            "",
            {}
        },
        {
            "lindell_audio_channelx",
            "Lindell Audio",
            "ChannelX",
            "Lindell Audio ChannelX",
            "Virtual 500 series with preamp, FET compressor, and Pultec-style EQ.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300175_b9f47d8b-15a3-4c65-9299-4baa15ee39cf.png",
            "https://www.plugin-alliance.com/en/products/lindell_channelx.html",
            "",
            {}
        },
        {
            "lindell_audio_mbc_multi_band_compressor",
            "Lindell Audio",
            "MBC Multi-Band Compressor",
            "Lindell Audio MBC Multi-Band Compressor",
            "Multi-band compressor for precise frequency-based dynamics control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_mbc.html",
            "",
            {}
        },
        {
            "lindell_audio_pex_500",
            "Lindell Audio",
            "PEX-500",
            "Lindell Audio PEX-500",
            "Pultec-style passive EQ in 500-series format.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_pex-500.html",
            "",
            {}
        },
        {
            "lindell_audio_sbc_2500_compressor",
            "Lindell Audio",
            "SBC 2500 Compressor",
            "Lindell Audio SBC 2500 Compressor",
            "SSL-style buss compressor for mix glue.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_sbc.html",
            "",
            {}
        },
        {
            "lindell_audio_te_100",
            "Lindell Audio",
            "TE-100",
            "Lindell Audio TE-100",
            "Tube equalizer with warm vintage character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300178.png",
            "https://www.plugin-alliance.com/en/products/lindell_te-100.html",
            "",
            {}
        },
        {
            "looptrotter_sa2rate_2",
            "Looptrotter",
            "SA2RATE 2",
            "Looptrotter SA2RATE 2",
            "Saturation with harmonic warmth and controlled peak reduction while maintaining clarity.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png",
            "https://www.plugin-alliance.com/en/products/looptrotter_sa2rate2.html",
            "",
            {}
        },
        {
            "louder_than_liftoff_chop_shop",
            "Louder Than Liftoff",
            "Chop Shop",
            "Louder Than Liftoff Chop Shop",
            "EQ with surgical precision and musical character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300952.png",
            "https://www.plugin-alliance.com/en/products/louder_than_liftoff_chop_shop_eq.html",
            "",
            {}
        },
        {
            "louder_than_liftoff_silver_bullet_mk2",
            "Louder Than Liftoff",
            "Silver Bullet mk2",
            "Louder Than Liftoff Silver Bullet mk2",
            "Analog console warmth through multiple amplifier stages with DYNA REALISM technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png",
            "https://www.plugin-alliance.com/en/products/louder_than_liftoff_silver_bullet_mk2.html",
            "",
            {}
        },
        {
            "maag_audio_eq4",
            "Maag Audio",
            "EQ4",
            "Maag Audio EQ4",
            "Musical equalizer with AIR BAND technology for vocal and mix-bus enhancement.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300035_428da437-d6de-412d-bbb1-9f804df6f30f.png",
            "https://www.plugin-alliance.com/en/products/maag_eq4.html",
            "",
            {}
        },
        {
            "maag_eq2",
            "Maag Audio",
            "EQ2",
            "Maag EQ2",
            "Two-band EQ with AIR BAND for adding sheen and presence.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300035.png",
            "https://www.plugin-alliance.com/en/products/maag_eq2.html",
            "",
            {}
        },
        {
            "maag_magnum_k",
            "Maag Audio",
            "Magnum-K",
            "Maag Magnum-K",
            "Compressor with smooth, musical dynamics control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300035.png",
            "https://www.plugin-alliance.com/en/products/maag_magnum-k.html",
            "",
            {}
        },
        {
            "maor_appelbaum_mastering_&_hendyamps_the_oven",
            "Maor Appelbaum & Hendyamps",
            "THE OVEN",
            "Maor Appelbaum Mastering & Hendyamps THE OVEN",
            "Colorful Mojo Box adding warmth and saturation through tube and solid-state emulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300653_a16226c9-f5b9-4820-92c2-4240b4adfa66.png",
            "https://www.plugin-alliance.com/en/products/the_oven.html",
            "",
            {}
        },
        {
            "millennia_nseq_2",
            "Millennia",
            "NSEQ-2",
            "Millennia NSEQ-2",
            "Mastering parametric EQ with switchable tube and JFET processing modes.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300033_a9be6950-3a74-433a-bda2-fd86035e4ef3.png",
            "https://www.plugin-alliance.com/en/products/millennia_nseq-2.html",
            "",
            {}
        },
        {
            "millennia_tcl_2",
            "Millennia",
            "TCL-2",
            "Millennia TCL-2",
            "Twin Com Leveler with smooth optical compression character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300033.png",
            "https://www.plugin-alliance.com/en/products/millennia_tcl-2.html",
            "",
            {}
        },
        {
            "neold_big_al",
            "NEOLD",
            "BIG AL",
            "NEOLD BIG AL",
            "Dual-stage tube saturator with 1930s transformer-coupled circuitry.",
            "https://www.plugin-alliance.com/cdn/shop/files/BIG_AL_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_big_al.html",
            "",
            {}
        },
        {
            "neold_u17",
            "NEOLD",
            "U17",
            "NEOLD U17",
            "Vintage tube compressor emulation with warm character.",
            "https://www.plugin-alliance.com/cdn/shop/files/U17_GUI.png?v=1760534783",
            "https://www.plugin-alliance.com/en/products/neold_u17.html",
            "",
            {}
        },
        {
            "neold_u2a",
            "NEOLD",
            "U2A",
            "NEOLD U2A",
            "Classic optical tube compressor for smooth leveling.",
            "https://www.plugin-alliance.com/cdn/shop/files/U17_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_u2a.html",
            "",
            {}
        },
        {
            "neold_v76u73",
            "NEOLD",
            "V76U73",
            "NEOLD V76U73",
            "1950s Telefunken V76 preamp and U73 compressor with warm low-end and smooth highs.",
            "https://www.plugin-alliance.com/cdn/shop/files/V76U73_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_v76u73.html",
            "",
            {}
        },
        {
            "neold_warble",
            "NEOLD",
            "WARBLE",
            "NEOLD WARBLE",
            "Vintage tape modulation with wow/flutter, aging, and resonant filtering.",
            "https://www.plugin-alliance.com/cdn/shop/files/WARBLE_GUI.png",
            "https://www.plugin-alliance.com/en/products/neold_warble.html",
            "",
            {}
        },
        {
            "noveltech_character",
            "Noveltech",
            "Character",
            "Noveltech Character",
            "Intelligent tonal and dynamic enhancement by auto-adjusting complex parameters.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300068_1e2c9ec6-8b04-49e6-ac20-bfbc963d0481.png",
            "https://www.plugin-alliance.com/en/products/noveltech_character.html",
            "",
            {}
        },
        {
            "noveltech_vocal_enhancer",
            "Noveltech",
            "Vocal Enhancer",
            "Noveltech Vocal Enhancer",
            "Intelligent vocal processing for presence and clarity.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300068.png",
            "https://www.plugin-alliance.com/en/products/noveltech_vocal_enhancer.html",
            "",
            {}
        },
        {
            "proaudiodsp_dsm_v3",
            "ProAudioDSP",
            "DSM V3",
            "ProAudioDSP DSM V3",
            "Spectral matching and dynamic control to capture and apply sonic character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300403_9bb5d6c3-5d94-46d0-86c4-f8c86bd9a7c3.png",
            "https://www.plugin-alliance.com/en/products/pro_audio_dsp_dsm_v3.html",
            "",
            {}
        },
        {
            "purple_audio_mc77",
            "Purple Audio",
            "MC77",
            "Purple Audio MC77",
            "1176 limiter recreation with stereo processing, sidechain filtering, and parallel mixing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png",
            "https://www.plugin-alliance.com/en/products/purple_audio_mc_77.html",
            "",
            {}
        },
        {
            "schoeps_double_ms",
            "Schoeps",
            "Double MS",
            "Schoeps Double MS",
            "Double mid-side decoding and processing for surround recordings.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/schoeps_double_ms.html",
            "",
            {}
        },
        {
            "schoeps_mono_upmix",
            "Schoeps",
            "Mono Upmix",
            "Schoeps Mono Upmix",
            "Convert mono recordings to immersive stereo and surround.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/schoeps_mono_upmix.html",
            "",
            {}
        },
        {
            "shadow_hills_mastering_compressor",
            "Shadow Hills",
            "Mastering Compressor",
            "Shadow Hills Mastering Compressor",
            "Dual-stage compression with switchable output transformers for mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300081_a9a2e16c-5b2f-47ae-9537-3073a3ed18f9.png",
            "https://www.plugin-alliance.com/en/products/shadow_hills_mastering_compressor.html",
            "",
            {}
        },
        {
            "shadow_hills_mastering_compressor_class_a",
            "Shadow Hills",
            "Mastering Compressor Class A",
            "Shadow Hills Mastering Compressor Class A",
            "Class A version of the legendary mastering compressor.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300081.png",
            "https://www.plugin-alliance.com/en/products/shadow_hills_class_a_mastering_comp.html",
            "",
            {}
        },
        {
            "sonible_smart:reverb",
            "sonible",
            "smart:reverb",
            "sonible smart:reverb",
            "AI-powered reverb that adapts to your source material.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300160.png",
            "https://www.plugin-alliance.com/en/products/x-sonible-smart-reverb.html",
            "",
            {}
        },
        {
            "spl_attacker_plus",
            "SPL",
            "Attacker Plus",
            "SPL Attacker Plus",
            "Transient enhancer for adding punch and attack.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_attacker_plus.html",
            "",
            {}
        },
        {
            "spl_de_verb",
            "SPL",
            "De-Verb",
            "SPL De-Verb",
            "Reverb reduction tool for cleaning up room ambience.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_de-verb.html",
            "",
            {}
        },
        {
            "spl_de_verb_plus",
            "SPL",
            "De-Verb Plus",
            "SPL De-Verb Plus",
            "Advanced reverb reduction with more control and precision.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_de-verb_plus.html",
            "",
            {}
        },
        {
            "spl_drumxchanger",
            "SPL",
            "DrumXchanger",
            "SPL DrumXchanger",
            "Drum replacement and augmentation tool.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_drumxchanger.html",
            "",
            {}
        },
        {
            "spl_eq_ranger_plus",
            "SPL",
            "EQ Ranger Plus",
            "SPL EQ Ranger Plus",
            "Full-range parametric equalizer with precise control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_eq_ranger_plus.html",
            "",
            {}
        },
        {
            "spl_free_ranger",
            "SPL",
            "Free Ranger",
            "SPL Free Ranger",
            "Four-band EQ based on the Passeq circuit.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_free_ranger.html",
            "",
            {}
        },
        {
            "spl_hawkeye",
            "SPL",
            "HawkEye",
            "SPL HawkEye",
            "Metering suite with level, loudness, bit monitoring, vectorscope, and spectrum analyzer.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png",
            "https://www.plugin-alliance.com/en/products/spl_hawkeye.html",
            "",
            {}
        },
        {
            "spl_iron",
            "SPL",
            "IRON",
            "SPL IRON",
            "Tube compressor with dual-circuit topology for transparent mastering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300386_5a609eb0-4eb3-4780-82b2-2bc2077c677b.png",
            "https://www.plugin-alliance.com/en/products/spl_iron.html",
            "",
            {}
        },
        {
            "spl_mo_verb_plus",
            "SPL",
            "Mo-Verb Plus",
            "SPL Mo-Verb Plus",
            "Room simulation and reverb modeling.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_mo-verb_plus.html",
            "",
            {}
        },
        {
            "spl_passeq",
            "SPL",
            "Passeq",
            "SPL Passeq",
            "Six-band passive mastering EQ with component-level modeling.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300014_41e6334f-ea81-4115-bcb2-ce021a984aae.png",
            "https://www.plugin-alliance.com/en/products/spl_passeq.html",
            "",
            {}
        },
        {
            "spl_pq",
            "SPL",
            "PQ",
            "SPL PQ",
            "Mastering equalizer with five bands of precise control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300014.png",
            "https://www.plugin-alliance.com/en/products/spl_pq.html",
            "",
            {}
        },
        {
            "spl_transient_designer_plus",
            "SPL",
            "Transient Designer Plus",
            "SPL Transient Designer Plus",
            "Threshold-independent transient processing with separate Attack and Sustain controls.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png",
            "https://www.plugin-alliance.com/en/products/spl_transient_designer_plus.html",
            "",
            {}
        },
        {
            "spl_twin_tube",
            "SPL",
            "Twin Tube",
            "SPL Twin Tube",
            "Dual tube saturation processor for warmth and harmonics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_twintube.html",
            "",
            {}
        },
        {
            "spl_vitalizer_mk2_t",
            "SPL",
            "Vitalizer MK2-T",
            "SPL Vitalizer MK2-T",
            "Psychoacoustic processor for enhancing bass and presence.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300187.png",
            "https://www.plugin-alliance.com/en/products/spl_vitalizer_mk2-t.html",
            "",
            {}
        },
        {
            "suhr_pt100",
            "Suhr",
            "PT100",
            "Suhr PT100",
            "Three-channel amplifier with American clean, British vintage, and high-gain tones.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300557_5b344abb-f597-41e9-ac6d-bd3885b474fc.png",
            "https://www.plugin-alliance.com/en/products/suhr_pt100.html",
            "",
            {}
        },
        {
            "suhr_se100",
            "Suhr",
            "SE100",
            "Suhr SE100",
            "High-end guitar amplifier with versatile tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300557.png",
            "https://www.plugin-alliance.com/en/products/suhr_se100.html",
            "",
            {}
        },
        {
            "three_body_technology_kirchoff_eq",
            "Three-Body Technology",
            "Kirchoff EQ",
            "Three-Body Technology Kirchoff EQ",
            "32-band parametric EQ with analog curves, dynamics processing, and vintage emulations.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300781_6b333574-9e0f-4247-9d6a-81a75d11eadd.png",
            "https://www.plugin-alliance.com/en/products/tbt_kirchhoff-eq.html",
            "",
            {}
        },
        {
            "tomo_audiolabs_lisa",
            "TOMO Audiolabs",
            "LISA",
            "TOMO Audiolabs LISA",
            "Six-band opto-compression dynamic EQ for sophisticated tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300635_b22c3561-6e15-4c4d-ad52-4ac96b0e9d92.png",
            "https://www.plugin-alliance.com/en/products/tomo_audiolabs_lisa.html",
            "",
            {}
        },
        {
            "unfiltered_audio_bass_mint",
            "Unfiltered Audio",
            "Bass-Mint",
            "Unfiltered Audio Bass-Mint",
            "Bass enhancement and synthesis for adding low-end weight.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_bass_mint.html",
            "",
            {}
        },
        {
            "unfiltered_audio_byome",
            "Unfiltered Audio",
            "BYOME",
            "Unfiltered Audio BYOME",
            "Modular effects with 40 unique types including reverbs, delays, and dynamics.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300378_43bef938-0ea5-4f09-ad46-0b34c751df83.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_byome.html",
            "",
            {}
        },
        {
            "unfiltered_audio_dent_2",
            "Unfiltered Audio",
            "Dent 2",
            "Unfiltered Audio Dent 2",
            "Waveform manipulation with clipping algorithms, bit-crushing, and modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300342_49bc2c9c-005d-4e8a-a7ae-f2b85de716c1.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_dent_2.html",
            "",
            {}
        },
        {
            "unfiltered_audio_fault",
            "Unfiltered Audio",
            "Fault",
            "Unfiltered Audio Fault",
            "Glitch and stutter effects for creative sound design.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_fault.html",
            "",
            {}
        },
        {
            "unfiltered_audio_g8",
            "Unfiltered Audio",
            "G8",
            "Unfiltered Audio G8",
            "Dynamic gate with MIDI control and alternate modes for creative gating.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183_d5aedd52-8194-49bd-b280-24160da8aed4.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_g8.html",
            "",
            {}
        },
        {
            "unfiltered_audio_indent_2",
            "Unfiltered Audio",
            "Indent 2",
            "Unfiltered Audio Indent 2",
            "Transient shaping with precise attack and sustain control.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_indent_2.html",
            "",
            {}
        },
        {
            "unfiltered_audio_instant_delay",
            "Unfiltered Audio",
            "Instant Delay",
            "Unfiltered Audio Instant Delay",
            "Zero-latency delay for creative timing effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_instant_delay.html",
            "",
            {}
        },
        {
            "unfiltered_audio_lion",
            "Unfiltered Audio",
            "LION",
            "Unfiltered Audio LION",
            "Dual-oscillator synthesizer with 26 modes, 16 filters, and 40+ effects.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300413_87e9ac60-f714-4a6d-9e6a-7e6cd43a070f.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_lion.html",
            "",
            {}
        },
        {
            "unfiltered_audio_lo_fi_af",
            "Unfiltered Audio",
            "LO-FI-AF",
            "Unfiltered Audio LO-FI-AF",
            "Vintage degradation with four rearrangeable modules for nostalgic character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300492_3815c462-512d-438e-a1f7-9796ef5e7296.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_lo-fi-af.html",
            "",
            {}
        },
        {
            "unfiltered_audio_needlepoint",
            "Unfiltered Audio",
            "Needlepoint",
            "Unfiltered Audio Needlepoint",
            "Vinyl and tape emulation for analog warmth and character.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_needlepoint.html",
            "",
            {}
        },
        {
            "unfiltered_audio_sandman",
            "Unfiltered Audio",
            "Sandman",
            "Unfiltered Audio Sandman",
            "Delay with sleep mode for infinite frozen repeats.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300264.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_sandman.html",
            "",
            {}
        },
        {
            "unfiltered_audio_sandman_pro",
            "Unfiltered Audio",
            "Sandman Pro",
            "Unfiltered Audio Sandman Pro",
            "Sophisticated delay with multiple modes for echo to granular synthesis.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300264_331f5d02-0ec3-4e58-9218-1ffbbbf2a9f2.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_sandman_pro.html",
            "",
            {}
        },
        {
            "unfiltered_audio_silo",
            "Unfiltered Audio",
            "SILO",
            "Unfiltered Audio SILO",
            "Spectral freezing and manipulation for ambient textures.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_silo.html",
            "",
            {}
        },
        {
            "unfiltered_audio_specops",
            "Unfiltered Audio",
            "SpecOps",
            "Unfiltered Audio SpecOps",
            "36 spectral effects applied to different frequency bands simultaneously.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300263_cda3010b-a419-4289-8245-3481b6409d10.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_specops.html",
            "",
            {}
        },
        {
            "unfiltered_audio_tails",
            "Unfiltered Audio",
            "TAILS",
            "Unfiltered Audio TAILS",
            "Next-gen reverb removing dissonances and transients with auto-ducking.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300493_90634ade-c965-41fd-a5fe-ed40d14cec59.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_tails.html",
            "",
            {}
        },
        {
            "unfiltered_audio_triad",
            "Unfiltered Audio",
            "TRIAD",
            "Unfiltered Audio TRIAD",
            "Multi-band distortion with three independent processing bands.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_triad.html",
            "",
            {}
        },
        {
            "unfiltered_audio_zip",
            "Unfiltered Audio",
            "Zip",
            "Unfiltered Audio Zip",
            "Compressor/limiter with aggressive character and fast response.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300183.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_zip.html",
            "",
            {}
        },
        {
            "vertigo_vsc_2",
            "Vertigo",
            "VSC-2",
            "Vertigo VSC-2",
            "VCA compressor with 1979-style VCAs for smooth, glossy compression.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300016_b2d9cdc4-0a57-4ea9-ac82-c9be994d59a3.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vsc-2.html",
            "",
            {}
        },
        {
            "vertigo_vsm_3",
            "Vertigo",
            "VSM-3",
            "Vertigo VSM-3",
            "Mastering saturation with dual harmonic circuitry for flexible tone shaping.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300100_481634f1-902d-46ca-9da7-bbe7f2b83313.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vsm-3.html",
            "",
            {}
        },
        {
            "adptr_audio_utopia",
            "ADPTR Audio",
            "Utopia",
            "ADPTR Audio Utopia",
            "Spectral reverb for lush, evolving, cinematic soundscapes with real-time harmonic transformation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301236.png",
            "https://www.plugin-alliance.com/en/products/adptr_utopia.html",
            "",
            {}
        },
        {
            "adptr_audio_hype",
            "ADPTR Audio",
            "Hype",
            "ADPTR Audio Hype",
            "Multi-band enhancement with compression, harmonics, and stereo width adjustment.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300999_56d6bbd4-8d7d-408d-845b-51ae21f9a76c.png",
            "https://www.plugin-alliance.com/en/products/adptr_hype.html",
            "",
            {}
        },
        {
            "shadow_hills_optomax",
            "Shadow Hills",
            "OptoMax",
            "Shadow Hills OptoMax",
            "New generation optical compressor with expanded ratio, speed, push mode, and transformer options.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301332.jpg",
            "https://www.plugin-alliance.com/en/products/shadow_hills_optomax.html",
            "",
            {}
        },
        {
            "neold_rz062",
            "NEOLD",
            "RZ062",
            "NEOLD RZ062",
            "Recreation of the legendary 1960s Siemens Klangfilm tube equalizer with vintage warmth.",
            "https://www.plugin-alliance.com/cdn/shop/files/NEOLD_RZ062_GUI.jpg",
            "https://www.plugin-alliance.com/en/products/neold_rz062.html",
            "",
            {}
        },
        {
            "spl_vitalizer_mk3_t",
            "SPL",
            "Vitalizer MK3-T",
            "SPL Vitalizer MK3-T",
            "Mix finishing tool with frequency shaping, bass processing, and de-masking technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301205.png",
            "https://www.plugin-alliance.com/en/products/spl_vitalizer_mk3-t.html",
            "",
            {}
        },
        {
            "elysia_alpha_compressor_v2",
            "elysia",
            "alpha compressor V2",
            "elysia alpha compressor V2",
            "Detailed emulation of revered analog mastering compressor with M/S capability and TMT technology.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301253.png",
            "https://www.plugin-alliance.com/en/products/elysia_alpha_compressor_v2.html",
            "",
            {}
        },
        {
            "maag_audio_eq4_ms",
            "Maag Audio",
            "EQ4 MS",
            "Maag Audio EQ4 MS",
            "Dual-channel mastering EQ with AIR BAND and M/S processing.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301107_7eb64f8c.png",
            "https://www.plugin-alliance.com/en/products/maag_eq4_ms.html",
            "",
            {}
        },
        {
            "spl_big",
            "SPL",
            "BiG",
            "SPL BiG",
            "TEC Award-winning stereo expander with unique stereo processing and AirBass EQ.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301157_b5d6244c.png",
            "https://www.plugin-alliance.com/en/products/spl_big.html",
            "",
            {}
        },
        {
            "hears_perfection",
            "HEARS",
            "Perfection",
            "HEARS Perfection",
            "Personalized frequency correction addressing hearing loss for accurate mix monitoring.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301331.png",
            "https://www.plugin-alliance.com/en/products/hears_perfection.html",
            "",
            {}
        },
        {
            "spl_machine_head",
            "SPL",
            "Machine Head",
            "SPL Machine Head",
            "Digital tape saturator with Original and Ultimate modes for authentic analog warmth.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301150_00d7f9ee.png",
            "https://www.plugin-alliance.com/en/products/spl_machine_head.html",
            "",
            {}
        },
        {
            "brainworx_bx_xl_v3",
            "Brainworx",
            "bx_XL V3",
            "Brainworx bx_XL V3",
            "M/S mastering limiter with four-stage limiting, XL harmonics, and advanced metering.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300918_98828b43.png",
            "https://www.plugin-alliance.com/en/products/bx_xl_v3.html",
            "",
            {}
        },
        {
            "brainworx_bx_pulsar",
            "Brainworx",
            "bx_pulsar",
            "Brainworx bx_pulsar",
            "Creative delay with five modes, 8-step sequencer, and advanced modulation.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301279_2.png",
            "https://www.plugin-alliance.com/en/products/bx_pulsar.html",
            "",
            {}
        },
        {
            "vertigo_vss_2",
            "Vertigo",
            "VSS-2",
            "Vertigo VSS-2",
            "Channel strip combining VSC-3 compressor, VSE-4 EQ, and VSM-4 tube sections.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301211_c9e80b87.png",
            "https://www.plugin-alliance.com/en/products/vertigo_vss-2.html",
            "",
            {}
        },
        {
            "hum_audio_laal",
            "HUM Audio Devices",
            "LAAL",
            "HUM Audio LAAL",
            "Look Ahead Analog Limiter for mastering with fully analog look ahead delay line.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301243_6f932fc9.png",
            "https://www.plugin-alliance.com/en/products/hum_audio_laal.html",
            "",
            {}
        },
        {
            "three_body_technology_cenozoix_compressor",
            "Three-Body Technology",
            "Cenozoix Compressor",
            "Three-Body Technology Cenozoix Compressor",
            "Next-gen compressor with 12 algorithms including modern and vintage emulations.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300982_3397fcd0.png",
            "https://www.plugin-alliance.com/en/products/tbt_cenozoix.html",
            "",
            {}
        },
        {
            "brainworx_bx_aura",
            "Brainworx",
            "bx_aura",
            "Brainworx bx_aura",
            "Creative reverb with five algorithms, gate/ducking, drive section, and freeze mode.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301029_e4a95235.png",
            "https://www.plugin-alliance.com/en/products/bx_aura.html",
            "",
            {}
        },
        {
            "black_box_analog_design_hg_q",
            "Black Box Analog Design",
            "HG-Q",
            "Black Box Analog Design HG-Q",
            "Six-band EQ with dual circuit design, tube boosts, and solid-state cuts.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-300902_7f6334fb.png",
            "https://www.plugin-alliance.com/en/products/black_box_hg-q.html",
            "",
            {}
        },
        {
            "lindell_audio_eq825",
            "Lindell Audio",
            "EQ825",
            "Lindell Audio EQ825",
            "Rare mastering EQ emulation with tube and transformer design.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301272.jpg",
            "https://www.plugin-alliance.com/en/products/lindell_eq825.html",
            "",
            {}
        },
        {
            "unfiltered_audio_battalion",
            "Unfiltered Audio",
            "Battalion",
            "Unfiltered Audio Battalion",
            "Modern drum machine with 20 synthesis engines and 1000+ samples.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301002_746463f1.png",
            "https://www.plugin-alliance.com/en/products/unfiltered_audio_battalion.html",
            "",
            {}
        },
        {
            "brainworx_bx_refinement_v3",
            "Brainworx",
            "bx_refinement V3",
            "Brainworx bx_refinement V3",
            "Dynamic EQ for removing harshness with tube saturation and de-esser.",
            "https://www.plugin-alliance.com/cdn/shop/files/productimage-301160.png",
            "https://www.plugin-alliance.com/en/products/bx_refinement_v3.html",
            "",
            {}
        }
    };
}

// Lookup plugin metadata by various identifiers
inline const PluginMetadata* findPluginMetadata(const juce::String& searchName)
{
    static std::vector<PluginMetadata> database = getPluginDatabase();
    static bool initialized = false;
    static std::map<juce::String, const PluginMetadata*> lookupByName;
    static std::map<juce::String, const PluginMetadata*> lookupById;

    if (!initialized)
    {
        for (const auto& plugin : database)
        {
            lookupByName[plugin.fullName.toLowerCase()] = &plugin;
            lookupById[plugin.id.toLowerCase()] = &plugin;
            // Also index by brand + product
            lookupByName[(plugin.brand + " " + plugin.product).toLowerCase()] = &plugin;
        }
        initialized = true;
    }

    auto searchLower = searchName.toLowerCase();

    // Try exact match by full name
    auto it = lookupByName.find(searchLower);
    if (it != lookupByName.end())
        return it->second;

    // Try by ID
    it = lookupById.find(searchLower);
    if (it != lookupById.end())
        return it->second;

    // Try partial match
    for (const auto& plugin : database)
    {
        if (plugin.fullName.containsIgnoreCase(searchName) ||
            searchName.containsIgnoreCase(plugin.fullName))
            return &plugin;
    }

    return nullptr;
}

} // namespace PALauncher
