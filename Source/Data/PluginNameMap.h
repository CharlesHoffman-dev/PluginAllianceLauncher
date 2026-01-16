/*
  ==============================================================================
    PluginNameMap.h
    Plugin Alliance Launcher - Official Plugin Name Mappings
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

namespace PALauncher
{

// Maps internal/detected plugin names to official display names
// Key: lowercase version of the detected name (for matching)
// Value: official display name
inline const std::map<juce::String, juce::String>& getPluginNameMap()
{
    static const std::map<juce::String, juce::String> nameMap = {
        // ACME Audio
        {"acme opticom xla-3", "ACME Opticom XLA-3"},
        {"opticom xla-3", "ACME Opticom XLA-3"},

        // ADA
        {"a/da flanger", "ADA Flanger"},
        {"ada flanger", "ADA Flanger"},
        {"a/da std-1", "ADA STD-1 Stereo Tapped Delay"},
        {"ada std-1", "ADA STD-1 Stereo Tapped Delay"},
        {"a-da flanger", "ADA Flanger"},
        {"a-da std-1", "ADA STD-1 Stereo Tapped Delay"},

        // ADPTR Audio
        {"adptr audio streamliner", "ADPTR Audio Streamliner"},
        {"adptr streamliner", "ADPTR Audio Streamliner"},
        {"streamliner", "ADPTR Audio Streamliner"},
        {"adptr audio sculpt", "ADPTR AUDIO SCULPT"},
        {"adptr sculpt", "ADPTR AUDIO SCULPT"},
        {"sculpt", "ADPTR AUDIO SCULPT"},
        {"adptr audio metric ab", "ADPTR AUDIO Metric AB"},
        {"adptr metric ab", "ADPTR AUDIO Metric AB"},
        {"metric ab", "ADPTR AUDIO Metric AB"},
        {"adptr audio utopia", "ADPTR Audio Utopia"},
        {"adptr utopia", "ADPTR Audio Utopia"},
        {"utopia", "ADPTR Audio Utopia"},
        {"adptr audio hype", "ADPTR Audio HYPE"},
        {"adptr hype", "ADPTR Audio HYPE"},

        // AMEK
        {"amek eq 200", "AMEK EQ 200"},
        {"amek eq200", "AMEK EQ 200"},
        {"amek eq 250", "AMEK EQ 250"},
        {"amek eq250", "AMEK EQ 250"},
        {"amek mastering compressor", "AMEK Mastering Compressor"},

        // Ampeg
        {"ampeg b-15n", "Ampeg B-15N"},
        {"ampeg b15n", "Ampeg B-15N"},
        {"ampeg svt-vr", "Ampeg SVT-VR"},
        {"ampeg svtvr", "Ampeg SVT-VR"},
        {"ampeg svt-vr classic", "Ampeg SVT-VR Classic"},
        {"ampeg svtvr classic", "Ampeg SVT-VR Classic"},
        {"ampeg svt-3pro", "Ampeg SVT-3PRO"},
        {"ampeg svt3pro", "Ampeg SVT-3PRO"},
        {"ampeg svt-3 pro", "Ampeg SVT-3PRO"},
        {"ampeg v-4b", "Ampeg V-4B"},
        {"ampeg v4b", "Ampeg V-4B"},

        // Bettermaker
        {"bettermaker eq232d", "Bettermaker EQ232D"},
        {"bettermaker eq 232d", "Bettermaker EQ232D"},
        {"bettermaker mastering compressor", "Bettermaker Mastering Compressor"},
        {"bettermaker bus compressor", "Bettermaker Bus Compressor"},
        {"bettermaker c502v", "Bettermaker C502V"},
        {"bettermaker bm60", "Bettermaker BM60"},
        {"bettermaker passive equalizer", "Bettermaker Passive Equalizer"},

        // Black Box Analog Design
        {"black box analog design hg-2", "Black Box Analog Design HG-2"},
        {"black box hg-2", "Black Box Analog Design HG-2"},
        {"hg-2", "Black Box Analog Design HG-2"},
        {"black box analog design hg-2ms", "Black Box Analog Design HG-2MS"},
        {"black box hg-2ms", "Black Box Analog Design HG-2MS"},
        {"hg-2ms", "Black Box Analog Design HG-2MS"},
        {"black box analog design hgq", "Black Box Analog Design HGQ"},
        {"black box hgq", "Black Box Analog Design HGQ"},

        // Brainworx
        {"bx_masterdesk pro", "Brainworx bx_masterdesk PRO"},
        {"bx_masterdesk", "Brainworx bx_masterdesk"},
        {"bx_masterdesk classic", "Brainworx bx_masterdesk Classic"},
        {"bx_masterdesk true peak", "Brainworx bx_masterdesk True Peak"},
        {"bx_console amek 9099", "Brainworx bx_console AMEK 9099"},
        {"bx_console amek 200", "Brainworx bx_console AMEK 200"},
        {"bx_console ssl 4000 e", "Brainworx bx_console SSL 4000 E"},
        {"bx_console ssl 4000 g", "Brainworx bx_console SSL 4000 G"},
        {"bx_console ssl 9000 j", "Brainworx bx_console SSL 9000 J"},
        {"bx_console focusrite sc", "Brainworx bx_console Focusrite SC"},
        {"bx_console n", "Brainworx bx_console N"},
        {"bx_bassdude", "Brainworx bx_bassdude"},
        {"bx_oberhausen", "Brainworx bx_oberhausen"},
        {"bx_subsynth", "Brainworx bx_subsynth"},
        {"bx_subfilter", "Brainworx bx_subfilter"},
        {"bx_refinement", "Brainworx bx_refinement"},
        {"bx_refinement v3", "Brainworx bx_refinement"},
        {"bx_xl v2", "Brainworx bx_XL V2"},
        {"bx_xl v3", "Brainworx bx_XL V2"},
        {"bx_crispytuner", "Brainworx bx_crispytuner"},
        {"bx_limiter true peak", "Brainworx bx_limiter True Peak"},
        {"bx_limiter", "Brainworx bx_limiter"},
        {"bx_solo", "Brainworx bx_solo"},
        {"bx_digital v3", "Brainworx bx_digital V3"},
        {"bx_digital v2", "Brainworx bx_digital V3"},
        {"bx_meter", "Brainworx bx_meter"},
        {"bx_townhouse", "Brainworx bx_townhouse Buss Compressor"},
        {"bx_townhouse buss compressor", "Brainworx bx_townhouse Buss Compressor"},
        {"bx_cleansweep v2", "Brainworx bx_cleansweep V2"},
        {"bx_cleansweep pro", "Brainworx bx_cleansweep Pro"},
        {"bx_stereomaker", "Brainworx bx_stereomaker"},
        {"bx_control v2", "Brainworx bx_control V2"},
        {"bx_2098 eq", "Brainworx bx_2098 EQ"},
        {"bx_saturator v2", "Brainworx bx_saturator V2"},
        {"bx_opto", "Brainworx bx_opto"},
        {"bx_opto pedal", "Brainworx bx_opto Pedal"},
        {"bx_tuner", "Brainworx bx_tuner"},
        {"bx_paneq", "Brainworx bx_panEQ"},
        {"bx_shredspread", "Brainworx bx_shredspread"},
        {"bx_delay 2500", "Brainworx bx_delay 2500"},
        {"bx_dyneq v2", "Brainworx bx_dynEQ V2"},
        {"bx_boom", "Brainworx bx_boom"},
        {"bx_boom!", "Brainworx bx_boom"},
        {"bx_rooms", "Brainworx bx_rooMS"},
        {"bx_aura", "Brainworx bx_aura"},
        {"bx_rockergain 100", "Brainworx bx_rockergain 100"},
        {"bx_megadual", "Brainworx bx_megadual"},
        {"bx_megasingle", "Brainworx bx_megasingle"},
        {"bx_greenscreamer", "Brainworx bx_greenscreamer"},
        {"bx_bluechorus2", "Brainworx bx_bluechorus2"},
        {"bx_blackdist2", "Brainworx bx_blackdist2"},
        {"bx_hybrid v2", "Brainworx bx_hybrid V2"},
        {"bx_distorange", "Brainworx bx_distorange"},
        {"bx_yellowdrive", "Brainworx bx_yellowdrive"},
        {"bx_clipper", "Brainworx bx_clipper"},
        {"bx_metal2", "Brainworx bx_metal2"},
        {"bx_rockrack v3", "Brainworx bx_rockrack V3"},
        {"bx_rockrack v3 player", "Brainworx bx_rockrack V3 Player"},
        {"bx_glue", "Brainworx bx_glue"},
        {"bx_pulsar", "Brainworx bx_pulsar"},
        {"bx_enhancer", "Brainworx bx_enhancer"},

        // Cenozoix
        {"cenozoix compressor", "Cenozoix Compressor"},

        // Chandler Limited
        {"chandler limited gav19t", "Chandler Limited GAV19T"},
        {"chandler gav19t", "Chandler Limited GAV19T"},
        {"gav19t", "Chandler Limited GAV19T"},

        // Cut Classic
        {"cut classic high flyer", "Cut Classic High Flyer"},

        // Dangerous Music
        {"dangerous music bax eq", "Dangerous Music BAX EQ"},
        {"dangerous bax eq", "Dangerous Music BAX EQ"},
        {"bax eq", "Dangerous Music BAX EQ"},

        // Dear Reality
        {"dearvr pro", "Dear Reality DearVR PRO"},
        {"dear reality dearvr pro", "Dear Reality DearVR PRO"},
        {"dearvr music", "Dear Reality dearVR MUSIC"},
        {"dear reality dearvr music", "Dear Reality dearVR MUSIC"},
        {"dearvr monitor", "Dear Reality dearVR MONITOR"},
        {"dear reality dearvr monitor", "Dear Reality dearVR MONITOR"},

        // Diezel
        {"diezel vh4", "Diezel VH4"},
        {"diezel herbert", "Diezel Herbert"},

        // DS Audio
        {"ds audio thorn", "DS Audio Thorn"},
        {"thorn", "DS Audio Thorn"},
        {"ds audio tantra 2", "DS Audio TANTRA 2"},
        {"tantra 2", "DS Audio TANTRA 2"},
        {"tantra", "DS Audio TANTRA 2"},

        // elysia
        {"elysia niveau filter", "elysia niveau filter"},
        {"niveau filter", "elysia niveau filter"},
        {"elysia alpha compressor", "elysia alpha compressor"},
        {"alpha compressor", "elysia alpha compressor"},
        {"elysia mpressor", "elysia mpressor"},
        {"mpressor", "elysia mpressor"},
        {"elysia phil's cascade", "elysia Phil's Cascade"},
        {"phil's cascade", "elysia Phil's Cascade"},
        {"elysia museq", "elysia museq"},
        {"museq", "elysia museq"},
        {"elysia karacter", "elysia karacter"},
        {"karacter", "elysia karacter"},
        {"elysia nvelope", "elysia nvelope"},
        {"nvelope", "elysia nvelope"},

        // ENGL
        {"engl savage 120", "ENGL Savage 120"},
        {"engl e646 vs", "ENGL E646 VS"},
        {"engl e765 rt", "ENGL E765 RT"},

        // Fiedler Audio
        {"fiedler audio stage", "fiedler audio stage"},
        {"fiedler stage", "fiedler audio stage"},
        {"fiedler audio spatial creator", "Fiedler Audio Spatial Creator"},
        {"fiedler audio splat", "Fiedler Audio SPLAT"},

        // Focusrite
        {"focusrite sc channel strip", "Focusrite SC Channel Strip"},
        {"focusrite sc", "Focusrite SC Channel Strip"},

        // Friedman
        {"friedman be-100", "Friedman BE-100"},
        {"friedman be100", "Friedman BE-100"},
        {"friedman buxom betty", "Friedman Buxom Betty"},
        {"friedman ds-40", "Friedman DS-40"},
        {"friedman ds40", "Friedman DS-40"},

        // Fuchs
        {"fuchs overdrive supreme 50", "Fuchs Overdrive Supreme 50"},
        {"fuchs train ii", "Fuchs Train II"},
        {"fuchs train 2", "Fuchs Train II"},

        // Gallien-Krueger
        {"gallien-krueger 800rb", "Gallien-Krueger 800RB"},
        {"gallien krueger 800rb", "Gallien-Krueger 800RB"},
        {"gk 800rb", "Gallien-Krueger 800RB"},

        // Harris Doyle
        {"harris doyle natalus dsceq", "Harris Doyle Natalus DSCEQ"},
        {"harris doyle natalus", "Harris Doyle Natalus DSCEQ"},
        {"natalus", "Harris Doyle Natalus DSCEQ"},

        // Kiive Audio
        {"kiive audio tape face", "Kiive Audio Tape Face"},
        {"kiive tape face", "Kiive Audio Tape Face"},
        {"tape face", "Kiive Audio Tape Face"},
        {"kiive audio xtressor", "Kiive Audio Xtressor"},
        {"kiive xtressor", "Kiive Audio Xtressor"},
        {"xtressor", "Kiive Audio Xtressor"},
        {"kiive audio xtcomp", "Kiive Audio XTComp"},

        // Knif Audio
        {"knif audio knifonium", "Knif Audio Knifonium"},
        {"knif knifonium", "Knif Audio Knifonium"},
        {"knifonium", "Knif Audio Knifonium"},
        {"knif audio soma eq", "Knif Audio Soma EQ"},
        {"knif soma", "Knif Audio Soma EQ"},
        {"soma eq", "Knif Audio Soma EQ"},

        // Lindell Audio
        {"lindell audio 69 series", "Lindell Audio 69 Series"},
        {"lindell 69 series", "Lindell Audio 69 Series"},
        {"lindell audio sbc", "Lindell Audio SBC 2500 Compressor"},
        {"lindell audio sbc 2500", "Lindell Audio SBC 2500 Compressor"},
        {"lindell sbc", "Lindell Audio SBC 2500 Compressor"},
        {"lindell audio mbc", "Lindell Audio MBC Multi-Band Compressor"},
        {"lindell mbc", "Lindell Audio MBC Multi-Band Compressor"},
        {"lindell audio 254e", "Lindell Audio 254E"},
        {"lindell 254e", "Lindell Audio 254E"},
        {"lindell audio 354e", "Lindell Audio 354E"},
        {"lindell 354e", "Lindell Audio 354E"},
        {"lindell audio 80 series", "Lindell Audio 80 Series"},
        {"lindell 80 series", "Lindell Audio 80 Series"},
        {"lindell audio 50 series", "Lindell Audio 50 Series"},
        {"lindell 50 series", "Lindell Audio 50 Series"},
        {"lindell audio 6x-500", "Lindell Audio 6X-500"},
        {"lindell 6x-500", "Lindell Audio 6X-500"},
        {"lindell audio 7x-500", "Lindell Audio 7X-500"},
        {"lindell 7x-500", "Lindell Audio 7X-500"},
        {"lindell audio 902 de-esser", "Lindell Audio 902 De-esser"},
        {"lindell 902", "Lindell Audio 902 De-esser"},
        {"lindell audio pex-500", "Lindell Audio PEX-500"},
        {"lindell pex-500", "Lindell Audio PEX-500"},
        {"lindell audio te-100", "Lindell Audio TE-100"},
        {"lindell te-100", "Lindell Audio TE-100"},
        {"lindell audio channelx", "Lindell Audio ChannelX"},
        {"lindell channelx", "Lindell Audio ChannelX"},
        {"lindell audio eq825", "Lindell Audio EQ825"},
        {"lindell eq825", "Lindell Audio EQ825"},
        {"lindell audio mu66", "Lindell Audio MU66"},

        // Looptrotter
        {"looptrotter sa2rate 2", "Looptrotter SA2RATE 2"},
        {"looptrotter sa2rate", "Looptrotter SA2RATE 2"},
        {"sa2rate 2", "Looptrotter SA2RATE 2"},

        // Louder Than Liftoff
        {"louder than liftoff silver bullet mk2", "Louder Than Liftoff Silver Bullet mk2"},
        {"louder than liftoff silver bullet", "Louder Than Liftoff Silver Bullet mk2"},
        {"silver bullet mk2", "Louder Than Liftoff Silver Bullet mk2"},
        {"silver bullet", "Louder Than Liftoff Silver Bullet mk2"},
        {"louder than liftoff chop shop", "Louder Than Liftoff Chop Shop"},
        {"chop shop", "Louder Than Liftoff Chop Shop"},

        // Maag Audio
        {"maag audio eq2", "Maag EQ2"},
        {"maag eq2", "Maag EQ2"},
        {"mäag audio eq2", "Maag EQ2"},
        {"maag audio eq4", "Mäag Audio EQ4"},
        {"maag eq4", "Mäag Audio EQ4"},
        {"mäag audio eq4", "Mäag Audio EQ4"},
        {"maag audio magnum-k", "Maag Magnum-K"},
        {"maag audio magnumk", "Maag Magnum-K"},
        {"maag magnum-k", "Maag Magnum-K"},
        {"mäag audio magnum-k", "Maag Magnum-K"},

        // Maor Appelbaum & Hendyamps
        {"maor appelbaum mastering & hendyamps the oven", "Maor Appelbaum Mastering & Hendyamps THE OVEN"},
        {"the oven", "Maor Appelbaum Mastering & Hendyamps THE OVEN"},

        // Millennia
        {"millennia nseq-2", "Millennia NSEQ-2"},
        {"millennia nseq2", "Millennia NSEQ-2"},
        {"nseq-2", "Millennia NSEQ-2"},
        {"millennia tcl-2", "Millennia TCL-2"},
        {"millennia tcl2", "Millennia TCL-2"},
        {"tcl-2", "Millennia TCL-2"},

        // Mixland
        {"mixland needlepoint", "Mixland Needlepoint"},
        {"mixland the oven", "Mixland THE OVEN"},
        {"mixland vac attack", "Mixland VAC Attack"},

        // NEOLD
        {"neold u2a", "NEOLD U2A"},
        {"neold u17", "NEOLD U17"},
        {"neold warble", "NEOLD WARBLE"},
        {"neold big al", "NEOLD BIG AL"},
        {"neold v76u73", "NEOLD V76U73"},
        {"neold oldtimer", "NEOLD Oldtimer"},
        {"neold wunderlich", "NEOLD Wunderlich"},
        {"neold rz062", "NEOLD RZ062"},

        // Noveltech
        {"noveltech vocal enhancer", "Noveltech Vocal Enhancer"},
        {"noveltech character", "Noveltech Character"},

        // ProAudioDSP
        {"proaudiodsp dsm v3", "ProAudioDSP DSM V3"},
        {"pro audio dsp dsm v3", "ProAudioDSP DSM V3"},
        {"dsm v3", "ProAudioDSP DSM V3"},

        // Purple Audio
        {"purple audio mc77", "Purple Audio MC77"},
        {"purple mc77", "Purple Audio MC77"},
        {"mc77", "Purple Audio MC77"},
        {"mc 77", "Purple Audio MC77"},

        // Schoeps
        {"schoeps double ms", "Schoeps Double MS"},
        {"schoeps mono upmix", "Schoeps Mono Upmix"},

        // Shadow Hills
        {"shadow hills mastering compressor", "Shadow Hills Mastering Compressor"},
        {"shadow hills mastering compressor class a", "Shadow Hills Mastering Compressor Class A"},
        {"shadow hills optomax", "Shadow Hills OptoMax"},

        // sonible
        {"sonible smart:reverb", "sonible smart:reverb"},
        {"smart:reverb", "sonible smart:reverb"},

        // SPL
        {"spl hawkeye", "SPL HawkEye"},
        {"spl drumxchanger", "SPL DrumXchanger"},
        {"spl de-esser collection", "SPL De-Esser Collection"},
        {"spl de-esser", "SPL De-Esser Collection"},
        {"spl de-verb plus", "SPL De-Verb Plus"},
        {"spl de-verb", "SPL De-Verb"},
        {"spl deverb plus", "SPL De-Verb Plus"},
        {"spl deverb", "SPL De-Verb"},
        {"spl vitalizer mk2-t", "SPL Vitalizer MK2-T"},
        {"spl vitalizer", "SPL Vitalizer MK2-T"},
        {"spl transient designer plus", "SPL Transient Designer Plus"},
        {"spl transient designer", "SPL Transient Designer Plus"},
        {"spl iron", "SPL IRON"},
        {"spl pq", "SPL PQ"},
        {"spl free ranger", "SPL Free Ranger"},
        {"spl twin tube", "SPL Twin Tube"},
        {"spl twintube", "SPL Twin Tube"},
        {"spl eq ranger plus", "SPL EQ Ranger Plus"},
        {"spl eq ranger", "SPL EQ Ranger Plus"},
        {"spl passeq", "SPL Passeq"},
        {"spl attacker plus", "SPL Attacker Plus"},
        {"spl attacker", "SPL Attacker Plus"},
        {"spl mo-verb plus", "SPL Mo-Verb Plus"},
        {"spl moverb plus", "SPL Mo-Verb Plus"},
        {"spl big", "SPL BiG"},
        {"spl machine head", "SPL Machine Head"},

        // Suhr
        {"suhr pt100", "Suhr PT100"},
        {"suhr se100", "Suhr SE100"},

        // Swivel Audio (based on code reference)
        {"swivel bde", "Swivel BDE"},
        {"swivel click boom", "Swivel Click Boom"},
        {"swivel hitstrip", "Swivel HitStrip"},
        {"swivel knocktonal", "Swivel Knocktonal"},
        {"swivel spread", "Swivel Spread"},
        {"swivel the sauce", "Swivel The Sauce"},

        // Three-Body Technology
        {"three-body technology kirchoff eq", "Three-Body Technology Kirchoff EQ"},
        {"kirchhoff eq", "Three-Body Technology Kirchoff EQ"},
        {"kirchhoff-eq", "Three-Body Technology Kirchoff EQ"},

        // THX
        {"thx spatial creator", "THX Spatial Creator"},

        // TOMO Audiolabs
        {"tomo audiolabs lisa", "TOMO Audiolabs LISA"},
        {"tomo lisa", "TOMO Audiolabs LISA"},
        {"lisa", "TOMO Audiolabs LISA"},

        // Trinity (based on code)
        {"trinity shaper", "Trinity Shaper"},

        // Unfiltered Audio
        {"unfiltered audio lo-fi-af", "Unfiltered Audio LO-FI-AF"},
        {"unfiltered audio lofiaf", "Unfiltered Audio LO-FI-AF"},
        {"lo-fi-af", "Unfiltered Audio LO-FI-AF"},
        {"unfiltered audio specops", "Unfiltered Audio SpecOps"},
        {"specops", "Unfiltered Audio SpecOps"},
        {"unfiltered audio lion", "Unfiltered Audio LION"},
        {"lion", "Unfiltered Audio LION"},
        {"unfiltered audio bass-mint", "Unfiltered Audio Bass-Mint"},
        {"unfiltered audio bassmint", "Unfiltered Audio Bass-Mint"},
        {"bass-mint", "Unfiltered Audio Bass-Mint"},
        {"unfiltered audio silo", "Unfiltered Audio SILO"},
        {"silo", "Unfiltered Audio SILO"},
        {"unfiltered audio g8", "Unfiltered Audio G8"},
        {"g8", "Unfiltered Audio G8"},
        {"unfiltered audio byome", "Unfiltered Audio BYOME"},
        {"byome", "Unfiltered Audio BYOME"},
        {"unfiltered audio dent 2", "Unfiltered Audio Dent 2"},
        {"dent 2", "Unfiltered Audio Dent 2"},
        {"unfiltered audio triad", "Unfiltered Audio TRIAD"},
        {"triad", "Unfiltered Audio TRIAD"},
        {"unfiltered audio tails", "Unfiltered Audio TAILS"},
        {"tails", "Unfiltered Audio TAILS"},
        {"unfiltered audio sandman pro", "Unfiltered Audio Sandman Pro"},
        {"sandman pro", "Unfiltered Audio Sandman Pro"},
        {"unfiltered audio sandman", "Unfiltered Audio Sandman"},
        {"sandman", "Unfiltered Audio Sandman"},
        {"unfiltered audio fault", "Unfiltered Audio Fault"},
        {"fault", "Unfiltered Audio Fault"},
        {"unfiltered audio zip", "Unfiltered Audio Zip"},
        {"zip", "Unfiltered Audio Zip"},
        {"unfiltered audio instant delay", "Unfiltered Audio Instant Delay"},
        {"instant delay", "Unfiltered Audio Instant Delay"},
        {"unfiltered audio indent 2", "Unfiltered Audio Indent 2"},
        {"indent 2", "Unfiltered Audio Indent 2"},
        {"unfiltered audio needlepoint", "Unfiltered Audio Needlepoint"},
        {"unfiltered audio battalion", "Unfiltered Audio Battalion"},

        // Vertigo
        {"vertigo vsc-2", "Vertigo VSC-2"},
        {"vertigo vsc2", "Vertigo VSC-2"},
        {"vsc-2", "Vertigo VSC-2"},
        {"vertigo vsm-3", "Vertigo VSM-3"},
        {"vertigo vsm3", "Vertigo VSM-3"},
        {"vsm-3", "Vertigo VSM-3"},
        {"vertigo vss-2", "Vertigo VSS-2"},
        {"vertigo vss2", "Vertigo VSS-2"},
        {"vss-2", "Vertigo VSS-2"},

        // WEDGE FORCE
        {"wedge force hydro", "WEDGE FORCE Hydro"},
        {"wedge force keemun", "WEDGE FORCE Keemun"},
        {"wedge force oolong", "WEDGE FORCE Oolong"},
        {"wedge force matcha", "WEDGE FORCE Matcha"},
    };

    return nameMap;
}

// Get the official display name for a plugin
inline juce::String getOfficialPluginName(const juce::String& detectedName)
{
    auto lowerName = detectedName.toLowerCase().trim();
    const auto& nameMap = getPluginNameMap();

    auto it = nameMap.find(lowerName);
    if (it != nameMap.end())
        return it->second;

    // Return original name if no mapping found
    return detectedName;
}

} // namespace PALauncher
