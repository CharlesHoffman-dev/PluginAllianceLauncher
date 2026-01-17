/*
  ==============================================================================
    PluginDescriptions.h
    Plugin Alliance Launcher - Plugin Description Database
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <map>

namespace PALauncher
{

// Get plugin description by name (case-insensitive lookup)
inline juce::String getPluginDescription(const juce::String& pluginName)
{
    static std::map<juce::String, juce::String> descriptions;
    static bool initialized = false;

    if (!initialized)
    {
        initialized = true;

        // ============================================
        // NEOLD
        // ============================================
        descriptions["neold rz062"] = "Emulation of a legendary Russian broadcast compressor known for its aggressive character and unique colorful compression. Perfect for adding weight and punch to drums, bass, and mix bus applications. Features authentic saturation and a distinctively musical response.";
        descriptions["neold v76u73"] = "1950s Telefunken V76 preamp and U73 compressor emulation with rich low-end warmth and smooth high-frequency character.";
        descriptions["neold warble"] = "Vintage tape modulation with wow/flutter effects, magnetic tape aging, and resonant filtering for warm analog character.";
        descriptions["neold big al"] = "Dual-stage tube saturator with 1930s transformer-coupled pre and power amplifier circuitry for vintage harmonic saturation.";
        descriptions["neold u17"] = "Recreation of the legendary Fairchild-style variable-mu tube compressor with exceptional musical compression. Provides smooth, program-dependent compression that enhances rather than squashes dynamics. A go-to choice for vocals, bass, and mix bus duties.";
        descriptions["neold u2a"] = "Authentic emulation of the classic LA-2A optical compressor known for its smooth, transparent compression. Features the signature optical attenuator response that's perfect for vocals and bass. Delivers effortless gain reduction with a warm, musical character.";
        descriptions["neold wunderlich"] = "Based on a rare German broadcast compressor with a distinctive aggressive compression character. Adds punch and excitement to drums and percussion with its fast attack capabilities. Features unique saturation characteristics and program-dependent release.";
        descriptions["neold oldtimer"] = "Captures the essence of vintage broadcast limiters with smooth, musical compression and rich harmonic saturation. Ideal for adding vintage warmth and cohesion to full mixes and stems. Features simple controls for fast, intuitive operation.";

        // ============================================
        // Shadow Hills
        // ============================================
        descriptions["shadow hills mastering compressor"] = "Industry-standard mastering compressor featuring dual compression stages with optical and discrete VCA sections. Offers unparalleled flexibility with selectable output transformers (nickel, iron, steel) for tonal shaping. The definitive tool for professional mastering and mix bus processing.";
        descriptions["shadow hills mastering compressor class a"] = "Class A variant of the legendary mastering compressor with enhanced harmonic richness and extended headroom. Features the same dual-stage compression topology with refined Class A circuitry throughout. Delivers even smoother compression with increased detail and air.";
        descriptions["shadow hills optomax"] = "Premium optical compressor based on Shadow Hills' custom design philosophy with musical program-dependent behavior. Combines the smoothness of optical compression with modern clarity and precision. Excellent for vocals, bass, and any source requiring transparent dynamic control.";

        // ============================================
        // SPL
        // ============================================
        descriptions["spl vitalizer mk3-t"] = "Legendary psychoacoustic processor that enhances audio using SPL's proprietary bass and presence algorithms. Adds depth, clarity, and dimension without conventional EQ artifacts or phase issues. An industry staple for bringing mixes to life in mastering and mixing.";
        descriptions["spl big"] = "Powerful stereo imaging tool that provides precise control over width, mono compatibility, and bass management. Features SPL's renowned M/S processing for surgical stereo field adjustments. Essential for mastering and creating wide, impactful mixes.";
        descriptions["spl machine head"] = "Unique amplifier and saturation processor combining multiple classic amp circuits and tape saturation stages. Delivers everything from subtle warmth to aggressive distortion with musical character. Perfect for adding edge and excitement to any source.";
        descriptions["spl twintube"] = "Dual-channel tube saturation processor offering rich harmonic enhancement and musical coloration. Features independent drive controls for subtle warmth or aggressive tube saturation. Ideal for adding analog character to digital recordings.";
        descriptions["spl de-esser collection"] = "Professional de-essing solution featuring multiple modes for surgical or musical sibilance control. Uses SPL's intelligent detection algorithms for transparent, artifact-free processing. Essential for polished vocal production in any genre.";
        descriptions["spl transient designer plus"] = "Threshold-independent transient processing with separate Attack and Sustain controls.";
        descriptions["spl de-verb plus"] = "Intelligent reverb reduction tool that removes unwanted room ambience and reverb tails from recordings. Uses advanced algorithms to preserve the natural character of the source material. Essential for cleaning up problematic recordings and dialogue.";
        descriptions["spl mo-verb plus"] = "Creative modulation reverb processor combining classic reverb algorithms with dynamic modulation effects. Produces lush, animated spatial effects from subtle ambience to dramatic washes. Perfect for sound design and creative production.";
        descriptions["spl attacker plus"] = "Advanced transient enhancement processor with multiple modes for different shaping characteristics. Adds punch, attack, and presence to drums, guitars, and any percussive material. Features expanded controls compared to the original Transient Designer.";
        descriptions["spl iron"] = "Tube compressor with dual-circuit topology for transparent, musical compression in mastering and tracking.";
        descriptions["spl passeq"] = "Six-band passive mastering EQ with component-level modeling for precise equalization.";
        descriptions["spl drumxchanger"] = "Intelligent drum replacement and augmentation tool that analyzes and replaces drum hits with samples. Features automatic detection and natural-sounding triggering algorithms. Perfect for enhancing or replacing drum sounds in any production.";
        descriptions["spl eq ranger plus"] = "Comprehensive multi-band equalizer with surgical precision and musical character. Offers flexible filter types and precise gain control across all bands. Ideal for corrective and creative EQ applications.";
        descriptions["spl hawkeye"] = "Metering suite with level, loudness, bit monitoring, vectorscope, and spectrum analyzer.";
        descriptions["spl pq"] = "Mastering-grade parametric equalizer with extremely precise controls and transparent sound quality. Features five fully parametric bands with surgical Q control and pristine filters. A benchmark tool for professional mastering engineers.";
        descriptions["spl free ranger"] = "Streamlined four-band equalizer offering essential EQ functions with SPL's signature sound quality. Provides musical equalization with intuitive controls and low CPU usage. Great for everyday mixing tasks and quick tonal adjustments.";

        // ============================================
        // elysia
        // ============================================
        descriptions["elysia alpha compressor"] = "Precision mastering compressor with M/S processing and customizable attack/release automation.";
        descriptions["elysia alpha compressor v2"] = "Updated version of the celebrated mastering compressor with enhanced features and refined algorithms. Maintains the pristine Class A sound while adding new creative possibilities. The ultimate choice for professional mastering and critical mixing.";
        descriptions["elysia museq"] = "Musical passive equalizer with transformer-coupled circuitry and vintage-inspired tone shaping. Offers five bands of smooth, phase-coherent equalization with signature elysia character. Excellent for adding warmth and musicality to any source.";
        descriptions["elysia karacter"] = "Three distortion modes for subtle enhancement to aggressive sound destruction with harmonic coloration.";
        descriptions["elysia mpressor"] = "Versatile compressor with negative ratios and gain reduction limiter for pristine to extreme creative effects.";
        descriptions["elysia nvelope"] = "Transient shaper controlling attack and sustain with frequency-based processing modes.";
        descriptions["elysia niveau filter"] = "Elegant tilt-style equalizer that shifts the overall tonal balance with a single control. Redistributes energy between low and high frequencies with phase-coherent processing. Ideal for quick mix adjustments and mastering polish.";
        descriptions["elysia phils cascade"] = "Cascaded compressor design offering multiple stages of compression for complex dynamic control. Provides smooth, multi-stage gain reduction with extensive tonal shaping options. Excellent for vocals, mix bus, and mastering applications.";

        // ============================================
        // Maag Audio
        // ============================================
        descriptions["maag audio eq4"] = "Legendary six-band equalizer featuring the famous Air Band for adding pristine high-frequency shimmer. Simple yet powerful design that adds instant polish and dimension to any source. An industry-standard tool for vocals, drums, and mix bus processing.";
        descriptions["maag audio eq4 ms"] = "Mid-side version of the iconic EQ4, adding stereo width control to the famous Air Band design. Enables separate processing of center and side information for surgical stereo enhancement. Perfect for mastering and detailed stereo imaging work.";
        descriptions["maag audio eq2"] = "Streamlined two-band equalizer featuring the signature Air Band plus a musical low-frequency shelf. Provides quick, effective tonal shaping with Maag's legendary high-frequency character. Ideal for adding polish to individual tracks or full mixes.";
        descriptions["maag audio magnum-k"] = "Premium compressor with transformer-coupled signal path and musical program-dependent response. Offers smooth, vintage-style compression with modern precision and flexibility. Excellent for vocals, bass, and any source requiring musical dynamic control.";

        // ============================================
        // ADPTR AUDIO
        // ============================================
        descriptions["adptr audio metric ab"] = "Professional audio comparison and referencing tool for critical listening and mix decisions. Provides instant level-matched A/B comparison with multiple reference tracks. Essential for mixing, mastering, and quality control workflows.";
        descriptions["adptr audio streamliner"] = "Intelligent loudness optimization tool that prepares audio for streaming platforms and broadcast. Automatically analyzes and adjusts dynamics to meet platform-specific requirements. Ensures your music sounds its best across all streaming services.";
        descriptions["adptr audio sculpt"] = "Dynamic multi-band processor offering transparent compression, expansion, and tonal shaping in one plugin. Features intelligent automatic gain staging and musical attack/release characteristics. Perfect for detailed mix sculpting and mastering.";
        descriptions["adptr audio utopia"] = "Ultimate mastering suite combining limiting, clipping, and saturation for maximum loudness with clarity. Provides transparent loudness maximization without sacrificing dynamic impact or musicality. The final word in competitive loudness for modern masters.";
        descriptions["adptr audio hype"] = "Multiband exciter and enhancer that adds presence, clarity, and excitement to any audio source. Uses musical saturation and dynamic processing to bring tracks to life. Ideal for vocals, drums, and full mix enhancement.";

        // ============================================
        // Three-Body Technology
        // ============================================
        descriptions["kirchhoff-eq"] = "State-of-the-art parametric equalizer combining analog modeling with modern digital precision. Features multiple filter types per band including authentic analog console emulations. Delivers pristine sound quality with zero latency operation.";
        descriptions["cenozoix compressor"] = "Advanced compressor with multiple compression styles and intelligent automatic gain compensation. Offers everything from transparent limiting to aggressive pumping with musical results. Features comprehensive sidechain options and visual feedback.";
        descriptions["trinity shaper"] = "Versatile transient shaping and dynamic enhancement tool with three independent processing stages. Provides surgical control over attack, sustain, and overall dynamics of any source. Perfect for drums, percussion, and adding definition to complex mixes.";

        // ============================================
        // Black Box Analog Design
        // ============================================
        descriptions["black box analog design hg-2"] = "Legendary tube saturation processor delivering rich harmonic enhancement and vintage warmth. Features multiple tube stages with air and presence controls for tonal shaping. The industry standard for adding tube character to mixes and masters.";
        descriptions["black box analog design hg-2ms"] = "Mid-side version of the acclaimed HG-2 tube saturator for advanced stereo processing. Enables independent saturation of center and side information for width enhancement. Perfect for mastering and creating dimensional, tube-flavored mixes.";
        descriptions["black box analog design hg-q"] = "Tube equalizer with musical fixed frequencies and the signature Black Box harmonic character. Offers smooth, vintage-style EQ curves with rich tube saturation. Excellent for adding warmth and presence to vocals, drums, and full mixes.";

        // ============================================
        // Brainworx
        // ============================================
        descriptions["bx_console ssl 4000 e"] = "SSL 4000 E console channel with 72 different emulations and Tolerance Modeling Technology for authentic analog warmth.";
        descriptions["bx_console ssl 4000 g"] = "Faithful recreation of the SSL 4000 G channel strip with its musical EQ and smooth dynamics. Features the refined G-series sound preferred for its versatility and polish. Ideal for modern productions requiring SSL quality and workflow.";
        descriptions["bx_console ssl 9000 j"] = "SSL 9000 J console emulation for mixing with the legendary 1990s-2000s recording console character.";
        descriptions["bx_console amek 9099"] = "Rupert Neve-designed AMEK 9098i console emulation with musical EQs, dynamics, and Tolerance Modeling.";
        descriptions["bx_console amek 200"] = "Emulation of the classic AMEK 200 broadcast console with its clean, musical characteristics. Features the signature AMEK sound with modern precision and recall. Ideal for broadcast, voice-over, and clean mixing applications.";
        descriptions["bx_console focusrite sc"] = "Recreation of the legendary Focusrite Studio Console channel strip designed by Rupert Neve. Delivers the unmistakable warmth and punch of the original Class A design. A must-have for vocals, bass, and adding premium character to any track.";
        descriptions["bx_console n"] = "72-channel vintage analog console emulation with Tolerance Modeling Technology for authentic analog variation.";
        descriptions["bx_digital v3"] = "11-band Mid/Side equalizer with parametric filters, dynamic EQ, and advanced metering for mixing and mastering.";
        descriptions["bx_pulsar"] = "Advanced multiband compressor with intelligent automatic gain and musical dynamics processing. Offers transparent to aggressive compression across customizable frequency bands. Ideal for mastering, mix bus, and complex dynamic control tasks.";
        descriptions["bx_refinement v3"] = "De-harsh and smooth processor that removes digital harshness while preserving natural detail. Uses intelligent detection to target only problematic frequencies without over-processing. Essential for polishing digital recordings and harsh sources.";
        descriptions["bx_clipper"] = "Transparent soft clipper and saturation tool for adding controlled harmonic density. Provides clean gain staging with musical saturation characteristics. Perfect for drums, mix bus, and maximizing loudness without limiting.";
        descriptions["bx_aura"] = "Intelligent tonal enhancement tool that adds life and dimension to dull or lifeless recordings. Uses psychoacoustic processing to enhance presence and clarity naturally. Ideal for reviving old recordings and adding modern polish.";
        descriptions["bx_masterdesk pro"] = "All-in-one mastering suite combining EQ, compression, saturation, and limiting in a unified workflow. Features professional metering and comprehensive processing for complete masters. A complete mastering solution in a single plugin.";
        descriptions["bx_masterdesk"] = "Streamlined mastering processor combining essential tools for quick, professional results. Offers one-knob mastering with automatic gain staging and musical processing. Perfect for fast masters and demo polishing.";
        descriptions["bx_masterdesk true peak"] = "True peak limited mastering desk ensuring compliance with streaming and broadcast standards. Combines musical processing with transparent true peak limiting. Essential for modern delivery requirements.";
        descriptions["bx_cleansweep pro"] = "High-quality filter plugin with resonant high-pass and low-pass filters for surgical cleanup. Features smooth filter curves and precise control for removing unwanted frequencies. Ideal for mixing preparation and creative filtering effects.";
        descriptions["bx_control v2"] = "Comprehensive monitoring and metering plugin with level matching and reference playback. Provides essential tools for critical listening and mix comparison. Indispensable for professional mixing and mastering environments.";
        descriptions["bx_delay 2500"] = "Versatile stereo delay with extensive modulation and creative processing options. Features multiple delay modes with filtering, saturation, and rhythmic variations. Perfect for creative effects and ambient sound design.";
        descriptions["bx_rockergain100"] = "High-gain guitar amplifier emulation delivering modern metal and rock tones. Features tight low-end response and aggressive harmonic character. Ideal for heavy guitar tones requiring precision and power.";
        descriptions["bx_subsynth"] = "Subharmonic generator that adds controlled low-frequency content below the fundamental. Creates massive bass enhancement without muddiness or phase issues. Essential for bass-heavy genres and adding weight to mixes.";
        descriptions["bx_roooms"] = "Creative reverb processor with unique room modeling and spatial enhancement capabilities. Offers everything from intimate spaces to vast, atmospheric environments. Perfect for adding depth and dimension to any production.";
        descriptions["bx_oberhausen"] = "Powerful virtual analog synthesizer inspired by the classic Oberheim sound. Features rich oscillators, classic filter designs, and extensive modulation options. Ideal for warm pads, punchy basses, and classic synth sounds.";
        descriptions["bx_paneq"] = "Pan-frequency equalizer with unique spectral tilt and phase controls. Offers creative tonal shaping with emphasis on spatial characteristics. Excellent for adding movement and interest to static sources.";
        descriptions["bx_dyneq v2"] = "Dynamic equalizer combining precise EQ with intelligent frequency-dependent compression. Features up to five bands of dynamic processing with visual feedback. Perfect for surgical problem-solving and creative mixing.";
        descriptions["bx_megadual"] = "Dual-channel high-gain amplifier emulation with extreme tonal flexibility. Delivers everything from clean to crushing metal tones with studio quality. Features comprehensive tone shaping and cabinet options.";
        descriptions["bx_opto"] = "Optical compressor emulation with smooth, musical compression characteristics. Captures the classic opto sound with modern precision and control. Ideal for vocals, bass, and program material requiring gentle compression.";
        descriptions["bx_townhouse buss compressor"] = "Emulation of the legendary SSL bus compressor with its signature pump and glue. Delivers the cohesive mix bus compression that defined modern production. Essential for adding energy and unity to stereo mixes.";
        descriptions["bx_townhouse"] = "Emulation of the legendary SSL bus compressor with its signature pump and glue. Delivers the cohesive mix bus compression that defined modern production. Essential for adding energy and unity to stereo mixes.";
        descriptions["bx_2098 eq"] = "Recreation of the classic Neve 2098 console EQ with its musical, warm character. Offers the legendary Neve sound with modern precision and flexibility. Perfect for adding warmth and dimension to any source.";
        descriptions["bx_saturator v2"] = "Versatile saturation processor with multiple distortion types and M/S processing. Delivers everything from subtle warmth to aggressive distortion. Ideal for adding analog character and excitement to digital mixes.";
        descriptions["bx_hybrid v2"] = "Comprehensive equalizer combining the best of digital precision and analog character. Features multiple EQ modes with automatic gain compensation. Excellent for both corrective and creative equalization.";
        descriptions["bx_stereomaker"] = "Mono-to-stereo converter and stereo width enhancement tool with natural results. Creates convincing stereo images from mono sources without artifacts. Perfect for widening mono recordings and enhancing stereo field.";
        descriptions["bx_limiter"] = "Transparent peak limiter with intelligent release and true peak detection options. Provides clean gain reduction without pumping or distortion. Essential for mastering and broadcast delivery.";
        descriptions["bx_limiter true peak"] = "True peak limiter ensuring compliance with streaming and broadcast standards. Combines transparent limiting with accurate inter-sample peak detection. The final stage in professional mastering chains.";
        descriptions["bx_bassdude"] = "Bass amplifier emulation delivering warm, punchy tones for modern bass production. Features multiple amp models with comprehensive tone shaping. Ideal for everything from vintage thump to modern aggressive bass.";
        descriptions["bx_rockrack v3"] = "Comprehensive guitar amp suite with multiple amplifier models and cabinet options. Delivers professional guitar tones for any genre or style. Features intuitive workflow and high-quality amp emulations.";
        descriptions["bx_crispytuner"] = "Real-time pitch correction with natural-sounding results and zero latency operation. Provides transparent tuning correction without the robotic artifacts. Essential for modern vocal production requiring pitch perfection.";
        descriptions["bx_crispyscale"] = "Advanced scale correction and pitch mapping tool for creative vocal processing. Offers automatic and manual pitch manipulation with natural results. Perfect for creative vocal effects and hard tuning styles.";
        descriptions["bx_glue"] = "Mix bus compressor combining multiple compression characteristics for cohesive glue. Delivers the unity and punch that brings mixes together. Ideal for stereo bus, stems, and adding cohesion to groups.";
        descriptions["bx_enhancer"] = "Harmonic exciter adding presence, air, and clarity to any audio source. Uses multiple enhancement algorithms for musical results. Perfect for vocals, drums, and bringing dull mixes to life.";
        descriptions["bx_boom v3"] = "Low-frequency enhancement and resonance control tool for powerful, controlled bass. Adds weight and punch without muddiness or boominess. Essential for electronic music and bass-heavy productions.";
        descriptions["bx_xl v3"] = "Mastering-grade limiter with intelligent automatic gain and transparent limiting characteristics. Provides competitive loudness without sacrificing dynamics or clarity. A benchmark tool for professional mastering.";
        descriptions["bx_blackdist2"] = "Distortion pedal emulation based on the classic ProCo RAT with extended features. Delivers aggressive, cutting distortion with extensive tone shaping. Perfect for heavy guitar tones and aggressive bass sounds.";
        descriptions["bx_bluechorus2"] = "Lush chorus effect based on classic analog chorus designs with extended modulation. Creates rich, dimensional chorus effects from subtle to extreme. Ideal for guitars, synths, and adding width to any source.";
        descriptions["bx_greenscreamer"] = "Tube screamer emulation delivering the classic mid-focused overdrive sound. Provides warm, musical overdrive with extended bass response options. Essential for blues, rock, and pushing amp front-ends.";
        descriptions["bx_distorange"] = "Orange amplifier distortion emulation with thick, warm overdrive character. Delivers the classic British crunch and lead tones. Perfect for classic rock and vintage-inspired guitar sounds.";
        descriptions["bx_yellowdrive"] = "Boutique overdrive emulation with transparent gain and musical harmonic content. Provides clean boost to medium overdrive with exceptional clarity. Ideal for stacking and adding subtle grit to clean tones.";
        descriptions["bx_metal2"] = "High-gain metal distortion with tight low-end and aggressive harmonic character. Delivers modern metal tones with precision and clarity. Essential for extreme guitar tones requiring maximum gain.";
        descriptions["bx_megasingle"] = "Single-channel version of the MegaDual amp with focused high-gain capabilities. Provides professional metal tones with streamlined controls. Perfect for tracking and live applications requiring consistency.";
        descriptions["bx_tuner"] = "Professional chromatic tuner with high accuracy and clear visual feedback. Provides reliable tuning reference for recording and live applications. Essential for any session requiring precise intonation.";
        descriptions["bx_meter"] = "Comprehensive metering plugin with multiple display modes and broadcast standards. Provides accurate level, loudness, and dynamic range measurement. Indispensable for professional mixing and mastering.";
        descriptions["bx_solo"] = "Simple yet powerful solo monitoring tool for isolating frequency ranges during mixing. Enables focused listening for problem-solving and detailed work. Essential for training ears and making precise mix decisions.";
        descriptions["bx_subfilter"] = "Surgical high-pass filter for removing subsonic content and cleaning up low end. Features variable slope and precise frequency control. Essential for mixing preparation and removing rumble.";
        descriptions["bx_shredspread"] = "Guitar stereo widening tool designed specifically for doubled guitar tracks. Creates wide, immersive guitar panoramas without phase issues. Perfect for modern rock and metal productions.";

        // ============================================
        // Vertigo
        // ============================================
        descriptions["vertigo vsc-2"] = "Emulation of the acclaimed Vertigo Sound VCA compressor with its punchy, musical character. Delivers aggressive yet musical compression perfect for drums and mix bus. Features the signature Vertigo sound with modern precision.";
        descriptions["vertigo vsm-3"] = "Unique saturation and mix processor combining vintage and modern harmonic enhancement. Offers multiple saturation modes from subtle warmth to aggressive distortion. Essential for adding analog character and excitement to mixes.";
        descriptions["vertigo vss-2"] = "Premium saturation processor with versatile coloration and harmonics generation. Provides everything from subtle warmth to intense saturation with musical results. Perfect for adding analog character to digital recordings.";

        // ============================================
        // HUM Audio Devices
        // ============================================
        descriptions["hum audio devices laal"] = "Unique lo-fi processing tool adding tape-style degradation and vintage character. Creates authentic vintage tones with controllable noise and saturation. Perfect for adding nostalgic character to modern productions.";
        descriptions["laal"] = "Unique lo-fi processing tool adding tape-style degradation and vintage character. Creates authentic vintage tones with controllable noise and saturation. Perfect for adding nostalgic character to modern productions.";

        // ============================================
        // Millennia
        // ============================================
        descriptions["millennia nseq-2"] = "Emulation of the legendary Millennia NSEQ-2 parametric EQ known for pristine transparency. Delivers surgical precision with minimal coloration and phase shift. The benchmark for transparent mastering equalization.";
        descriptions["millennia tcl-2"] = "Recreation of the Millennia TCL-2 twin topology compressor with tube and solid-state paths. Offers the choice between warm tube or clean solid-state compression. Ideal for vocals and critical mixing requiring flexibility.";

        // ============================================
        // Lindell Audio
        // ============================================
        descriptions["lindell audio 80 series"] = "Channel strip inspired by the legendary Neve 80-series console with rich harmonic character. Delivers the classic British sound with modern workflow and precision. Essential for adding warmth and punch to any source.";
        descriptions["lindell audio eq825"] = "Precision equalizer based on vintage American console designs with musical character. Offers smooth, musical EQ curves with classic tonal shaping. Perfect for adding vintage warmth and dimension.";
        descriptions["lindell audio 69 series"] = "Channel strip based on the iconic Neve 1073 design with transformer-coupled sound. Captures the legendary preamp and EQ combination loved by engineers worldwide. The gold standard for rock, pop, and vocal production.";
        descriptions["lindell audio 50 series"] = "Channel strip inspired by classic API console designs with punchy, aggressive character. Delivers the tight, focused sound that defined American rock records. Essential for drums, guitars, and punchy mix processing.";
        descriptions["lindell audio mbc"] = "Musical multiband compressor offering transparent dynamics control across frequency bands. Provides gentle or aggressive multiband compression with intuitive controls. Ideal for mastering and complex mix bus processing.";
        descriptions["lindell audio pq"] = "Precision parametric equalizer with surgical control and musical character. Features comprehensive frequency shaping with high-quality filters. Excellent for detailed mix work and mastering applications.";
        descriptions["lindell audio sbc"] = "Simple bus compressor delivering cohesive mix glue with musical compression. Offers classic SSL-style compression with streamlined controls. Perfect for quick mix bus processing and stem compression.";
        descriptions["lindell audio 354e"] = "Passive EQ design based on vintage broadcast equalizers with smooth, musical curves. Delivers gentle, phase-coherent equalization with classic character. Ideal for mastering and adding vintage polish.";
        descriptions["lindell audio 254e"] = "Vintage-style compressor with smooth, program-dependent compression characteristics. Offers classic limiting with musical results and easy operation. Perfect for vocals and gentle dynamic control.";
        descriptions["lindell audio 902 de-esser"] = "Dedicated de-essing processor with surgical precision and transparent operation. Removes sibilance without affecting the natural character of vocals. Essential for polished vocal production.";
        descriptions["lindell audio 7x-500"] = "500-series format compressor with fast, punchy compression for drums and percussion. Delivers aggressive dynamic control with musical results. Ideal for adding punch and impact to drum tracks.";
        descriptions["lindell audio 6x-500"] = "Versatile 500-series compressor offering multiple compression flavors in one unit. Provides flexible dynamic control for various applications. Excellent for vocals, instruments, and mix bus.";
        descriptions["lindell audio pex-500"] = "500-series format passive EQ with smooth, musical frequency shaping. Delivers vintage-style equalization with modern precision. Perfect for adding warmth and dimension.";
        descriptions["lindell audio channelx"] = "Comprehensive channel strip combining preamp, EQ, and compression in one workflow. Offers complete signal processing with vintage character. Ideal for tracking and mixing applications.";
        descriptions["lindell mu-66"] = "Variable-mu tube compressor emulation with smooth, musical compression characteristics. Delivers classic tube compression with rich harmonic enhancement. Perfect for vocals, mix bus, and mastering.";
        descriptions["lindell te-100"] = "Tube equalizer offering warm, musical frequency shaping with harmonic enhancement. Features smooth tube saturation with precise EQ control. Excellent for adding vintage character and warmth.";

        // ============================================
        // AMEK
        // ============================================
        descriptions["amek eq 200"] = "Recreation of the classic AMEK 200 console EQ with its musical, refined character. Offers smooth equalization with distinctive AMEK tonality. Ideal for broadcast, vocals, and clean mixing applications.";
        descriptions["amek eq 250"] = "Advanced AMEK equalizer with extended features and enhanced precision. Delivers the signature AMEK sound with comprehensive frequency control. Perfect for detailed mix work requiring musical EQ.";
        descriptions["amek mastering compressor"] = "Professional mastering compressor with the refined AMEK sound and comprehensive controls. Provides transparent to musical compression for critical applications. Excellent for mastering and high-end mix bus processing.";

        // ============================================
        // Ampeg
        // ============================================
        descriptions["ampeg b-15n"] = "Legendary Portaflex bass amplifier known for its warm, vintage tone and smooth breakup. Captures the classic sound that defined Motown and countless recordings. Essential for vintage bass tones with character and warmth.";
        descriptions["ampeg svt-vr"] = "Recreation of the iconic SVT with its powerful, authoritative bass tone. Delivers the full-stack sound that defined rock bass for generations. The benchmark for loud, aggressive bass amplification.";
        descriptions["ampeg svt-vr classic"] = "Classic version of the SVT capturing the vintage circuit with period-correct components. Offers the original SVT sound with authentic tube response. Perfect for vintage rock and blues bass tones.";
        descriptions["ampeg svt-3pro"] = "Modern SVT variant with tighter low-end and extended clean headroom. Provides the SVT character with modern reliability and consistency. Ideal for contemporary rock and metal bass.";
        descriptions["ampeg v-4b"] = "All-tube bass head delivering warm, dynamic tone with natural compression. Offers the classic Ampeg sound in a more portable format. Excellent for recording and smaller venues.";

        // ============================================
        // Diezel
        // ============================================
        descriptions["diezel herbert"] = "Emulation of the legendary three-channel Diezel Herbert amplifier. Delivers pristine cleans through crushing high-gain with exceptional clarity. Essential for modern metal and progressive rock guitar tones.";
        descriptions["diezel vh4"] = "Recreation of the iconic VH4 amplifier revered for its tight, articulate high-gain sound. Provides four channels of Diezel tone from clean to extreme gain. The benchmark for modern metal rhythm and lead tones.";

        // ============================================
        // Friedman
        // ============================================
        descriptions["friedman be-100"] = "Emulation of the acclaimed BE-100 amplifier with its legendary high-gain tones. Delivers the famous brown sound with tight low-end and smooth sustain. Essential for classic rock to modern metal applications.";
        descriptions["friedman buxom betty"] = "Recreation of the Buxom Betty amplifier known for its dynamic cleans and crunchy overdrive. Offers exceptional touch sensitivity and musical breakup. Perfect for blues, rock, and country guitar tones.";
        descriptions["friedman ds-40"] = "Compact Friedman amplifier delivering signature tones in a streamlined format. Provides the Friedman sound with focused controls and consistent response. Ideal for recording and smaller performance spaces.";

        // ============================================
        // ENGL
        // ============================================
        descriptions["engl savage 120"] = "Powerful high-gain amplifier emulation with extreme saturation and tight response. Delivers crushing metal tones with exceptional clarity and definition. Essential for modern extreme metal productions.";
        descriptions["engl e765 rt"] = "Versatile ENGL amplifier offering clean to high-gain tones with German precision. Features the retro tube design with modern reliability. Perfect for rock, metal, and versatile studio applications.";
        descriptions["engl e646 vs"] = "Victor Smolski signature amplifier with aggressive high-gain character. Delivers tight, focused distortion for technical metal applications. Ideal for progressive and modern metal guitar tones.";

        // ============================================
        // Suhr
        // ============================================
        descriptions["suhr pt100"] = "Premium amplifier emulation based on the Suhr PT100 with exceptional clarity. Delivers boutique-quality tones from clean to high-gain with musical response. Perfect for professional studio and live applications.";
        descriptions["suhr se100"] = "Signature Edition amplifier with refined high-gain capabilities and touch sensitivity. Offers the Suhr sound with enhanced features and tonal flexibility. Excellent for rock, fusion, and modern guitar styles.";

        // ============================================
        // Gallien-Krueger
        // ============================================
        descriptions["gallien-krueger 800rb"] = "Iconic bass amplifier known for its articulate, punchy sound and legendary growl. Delivers the classic GK tone that defined slap bass and rock bass. Essential for players seeking clarity and cutting power.";

        // ============================================
        // Fuchs
        // ============================================
        descriptions["fuchs train ii"] = "Boutique amplifier emulation delivering warm, dynamic tones with exceptional touch response. Offers vintage-inspired sound with modern reliability and consistency. Perfect for blues, rock, and expressive playing.";
        descriptions["fuchs overdrive supreme 50"] = "Premium overdrive amplifier with rich harmonic content and smooth saturation. Delivers singing lead tones with excellent sustain and clarity. Ideal for blues, classic rock, and fusion applications.";

        // ============================================
        // Unfiltered Audio
        // ============================================
        descriptions["unfiltered audio dent 2"] = "Advanced waveform destruction processor with multiple distortion algorithms and modulation. Creates everything from subtle saturation to extreme digital mayhem. Essential for sound design and experimental production.";
        descriptions["unfiltered audio silo"] = "Granular delay and looping processor with extensive real-time manipulation capabilities. Transforms audio into evolving textures and ambient soundscapes. Perfect for experimental music and cinematic sound design.";
        descriptions["unfiltered audio indent 2"] = "Dynamic transient processor with gate-like capabilities and creative modulation options. Provides precise control over dynamics with unique creative possibilities. Ideal for drums, percussion, and rhythmic effects.";
        descriptions["unfiltered audio instant delay"] = "Zero-latency delay processor with comprehensive modulation and filtering options. Offers immediate delay effects with extensive sound design capabilities. Essential for live performance and creative mixing.";
        descriptions["unfiltered audio tails"] = "Reverb processor creating lush, infinite sustain and frozen texture effects. Generates evolving ambient soundscapes from any audio source. Perfect for ambient music and atmospheric sound design.";
        descriptions["unfiltered audio bass-mint"] = "Dedicated bass enhancement and saturation processor for powerful low-end. Adds weight and harmonic richness to bass without muddiness. Essential for electronic music and bass-heavy productions.";
        descriptions["unfiltered audio lo-fi-af"] = "Comprehensive lo-fi processing suite with bit-crushing, saturation, and degradation. Creates authentic vintage and degraded tones with extensive control. Perfect for lo-fi hip-hop and nostalgic productions.";
        descriptions["unfiltered audio sandman pro"] = "Advanced delay processor with extensive modulation and rhythmic capabilities. Creates complex delay patterns and evolving textures. Ideal for creative production and experimental mixing.";
        descriptions["unfiltered audio sandman"] = "Streamlined delay processor with musical modulation and tempo-sync capabilities. Offers quick access to creative delay effects with intuitive controls. Perfect for everyday mixing and sound design.";
        descriptions["unfiltered audio specops"] = "Multi-effect processor combining spectral processing with modulation and distortion. Creates unique tonal transformations and spectral effects. Essential for experimental sound design and creative mixing.";
        descriptions["unfiltered audio fault"] = "Distortion and modulation processor with envelope following and creative mangling. Delivers dynamic distortion effects that respond to input. Perfect for aggressive sound design and creative effects.";
        descriptions["unfiltered audio lion"] = "Powerful virtual synthesizer with advanced modulation and extensive sound design capabilities. Creates everything from classic synth sounds to complex evolving textures. Ideal for electronic music and sound design.";
        descriptions["unfiltered audio zip"] = "Compressor with extreme compression capabilities and creative pumping effects. Provides transparent to aggressive dynamics control with unique character. Essential for drum processing and creative mixing.";
        descriptions["unfiltered audio byome"] = "Modular effects with 40 unique types including reverbs, delays, dynamics, and mixing tools.";
        descriptions["unfiltered audio g8"] = "Dynamic gate with MIDI control and alternate modes for creative sound shaping and transient manipulation.";
        descriptions["unfiltered audio battalion"] = "Comprehensive distortion and amp processor with multiple gain stages and tonal options. Delivers everything from subtle warmth to crushing distortion. Ideal for guitar, bass, and creative sound mangling.";

        // ============================================
        // Swivel Audio
        // ============================================
        descriptions["swivel audio spread"] = "Stereo enhancement processor creating wide, immersive stereo images with mono compatibility. Uses advanced algorithms for natural-sounding width expansion. Perfect for creating spacious mixes without phase issues.";
        descriptions["swivel audio the sauce"] = "Multi-effect processor combining saturation, compression, and tonal enhancement. Adds instant warmth and presence to any source with simple controls. Essential for quick mix enhancement and polish.";
        descriptions["swivel audio knocktonal"] = "Kick drum enhancer with sub-harmonic generation and tonal shaping capabilities. Adds weight, punch, and definition to kick drums. Perfect for electronic music and modern drum production.";
        descriptions["swivel audio click boom"] = "Transient enhancement tool specifically designed for kick drums and bass. Adds attack and low-end power with precise control. Essential for impactful drum sounds in any genre.";
        descriptions["swivel audio bde"] = "Bass enhancement processor adding harmonics and weight to low-frequency content. Creates fuller, more powerful bass without muddiness. Ideal for bass-heavy music and adding low-end presence.";
        descriptions["swivel audio hitstrip"] = "Mix bus processing chain optimized for hip-hop and modern production styles. Combines essential processing tools in one streamlined workflow. Perfect for quick, professional mix enhancement.";

        // ============================================
        // Bettermaker
        // ============================================
        descriptions["bettermaker mastering compressor"] = "High-end mastering compressor with musical compression and harmonic enhancement. Delivers transparent to colored compression with exceptional quality. The pinnacle of Polish audio engineering for professional mastering.";
        descriptions["bettermaker bus compressor"] = "Professional bus compressor with the signature Bettermaker sound and extensive controls. Provides cohesive mix glue with musical compression characteristics. Ideal for mix bus and stem processing.";
        descriptions["bettermaker c502v"] = "500-series format compressor with variable-mu characteristics and vintage warmth. Offers smooth, musical compression with rich harmonic content. Perfect for vocals and instruments requiring character.";
        descriptions["bettermaker bm60"] = "Parametric mastering equalizer with motorized controls and exceptional precision. Delivers surgical EQ with analog recall capabilities. Essential for professional mastering requiring precision and workflow.";
        descriptions["bettermaker eq232d"] = "Dual mono parametric equalizer with mastering-grade precision and musical character. Offers comprehensive frequency shaping with top-tier components. Ideal for critical mixing and mastering applications.";
        descriptions["bettermaker passive equalizer"] = "Passive EQ design with smooth, phase-coherent frequency shaping and tube output stage. Delivers gentle, musical equalization with vintage character. Perfect for mastering and adding vintage polish.";

        // ============================================
        // Knif Audio
        // ============================================
        descriptions["knif audio soma"] = "Unique stereo enhancement processor using proprietary harmonic generation technology. Creates wide, dimensional stereo images with analog warmth. Perfect for mastering and adding depth to mixes.";
        descriptions["knif audio knifonium"] = "Monophonic tube synthesizer with authentic analog warmth and character. Delivers rich, organic synth tones impossible to recreate digitally. Essential for basslines, leads, and vintage synth sounds.";

        // ============================================
        // Noveltech
        // ============================================
        descriptions["noveltech character"] = "Intelligent audio enhancement processor that analyzes and improves tonal balance automatically. Uses advanced algorithms to enhance clarity and presence musically. Perfect for quick enhancement of any audio source.";
        descriptions["noveltech vocal enhancer"] = "Dedicated vocal processor optimizing vocals for clarity, presence, and impact. Provides automatic enhancement with minimal setup required. Essential for polished vocal production.";

        // ============================================
        // fiedler audio
        // ============================================
        descriptions["fiedler audio stage"] = "Revolutionary spatial positioning tool for precise placement in 3D sound fields. Enables accurate positioning of sources in immersive audio productions. Essential for Dolby Atmos and 3D audio mixing.";
        descriptions["fiedler audio spatial creator"] = "Immersive reverb and spatial processor for creating realistic 3D environments. Generates convincing spatial audio with comprehensive room modeling. Perfect for immersive audio and game sound design.";

        // ============================================
        // DS Audio
        // ============================================
        descriptions["ds audio tantra 2"] = "Powerful rhythmic multi-effect with extensive modulation and sequencing capabilities. Creates complex rhythmic effects synced to tempo with visual editing. Essential for electronic music and creative production.";
        descriptions["ds audio thorn"] = "Advanced virtual synthesizer with wavetable and subtractive synthesis combined. Delivers everything from classic analog sounds to modern digital tones. Perfect for contemporary electronic music production.";

        // ============================================
        // Purple Audio
        // ============================================
        descriptions["purple audio mc77"] = "Emulation of the legendary 1176-style FET compressor with fast, aggressive compression. Delivers the iconic punch and attitude of the original hardware. Essential for vocals, drums, and adding excitement to any source.";

        // ============================================
        // Pro Audio DSP
        // ============================================
        descriptions["pro audio dsp dsm v3"] = "Dynamic spectrum mapper for mastering with intelligent multi-band processing. Provides automatic tonal balance correction with musical results. Perfect for mastering and detailed mix refinement.";

        // ============================================
        // Looptrotter
        // ============================================
        descriptions["looptrotter sa2rate 2"] = "Dual-stage saturation processor with multiple saturation types and routing options. Delivers everything from subtle warmth to aggressive distortion. Ideal for adding analog character and excitement.";

        // ============================================
        // Dangerous Music
        // ============================================
        descriptions["dangerous music bax eq"] = "Legendary mastering equalizer with musical shelf curves and transformer character. Delivers smooth, broad strokes for tonal shaping in mastering. A benchmark tool for professional mastering engineers.";

        // ============================================
        // A/DA
        // ============================================
        descriptions["a/da flanger"] = "Classic analog flanger emulation with the signature A/DA sweep and character. Delivers rich, jet-like flanging effects from subtle to extreme. Essential for recreating iconic modulation sounds.";
        descriptions["a/da std-1 stereo tapped delay"] = "Recreation of the legendary STD-1 delay with its unique tapped delay algorithm. Creates complex rhythmic delays with vintage character. Perfect for creative guitar effects and sound design.";

        // ============================================
        // Chandler Limited
        // ============================================
        descriptions["chandler limited gav19t"] = "Emulation of the rare Chandler germanium amplifier with unique harmonic character. Delivers warm, vintage saturation with distinctive tonal qualities. Ideal for adding organic character to any source.";

        // ============================================
        // Kiive Audio
        // ============================================
        descriptions["kiive audio xtcomp"] = "Versatile compressor with multiple compression topologies and extensive control. Offers transparent to aggressive compression with tonal flexibility. Perfect for any mixing or mastering application.";

        // ============================================
        // Louder Than Liftoff
        // ============================================
        descriptions["louder than liftoff silver bullet mk2"] = "Dual-path coloration processor offering N and A type analog circuits. Provides instant analog warmth and character with simple controls. Essential for adding console mojo to digital mixes.";

        // ============================================
        // Tomo Audiolabs
        // ============================================
        descriptions["tomo audiolabs lisa"] = "Analog-modeling saturation processor with harmonic enhancement capabilities. Delivers musical saturation with extensive tonal control. Perfect for adding warmth and character to any source.";

        // ============================================
        // Harris Doyle
        // ============================================
        descriptions["harris doyle natalus dsceq"] = "Dynamic shelving EQ with intelligent frequency-dependent processing. Offers musical tonal shaping with automatic dynamic control. Ideal for mastering and intelligent mix adjustment.";

        // ============================================
        // Mixland
        // ============================================
        descriptions["mixland the oven"] = "Tube saturation processor adding rich harmonics and analog warmth. Delivers musical saturation from subtle to aggressive. Perfect for adding character to digital recordings.";
        descriptions["mixland needlepoint"] = "Transient shaping processor with precise attack and sustain control. Provides surgical dynamic shaping with musical results. Essential for drums and adding punch to any source.";

        // ============================================
        // ACME Audio
        // ============================================
        descriptions["acme audio opticom xla-3"] = "Optical compressor with musical program-dependent compression characteristics. Delivers smooth, transparent gain reduction with vintage warmth. Ideal for vocals, bass, and gentle dynamic control.";

        // ============================================
        // THX
        // ============================================
        descriptions["thx aaa"] = "Professional headphone and speaker calibration system for accurate monitoring. Ensures translation between different playback systems. Essential for critical listening and mix accuracy.";

        // ============================================
        // Karanyi Sounds
        // ============================================
        descriptions["karanyi sounds triad"] = "Creative delay and modulation processor with unique sound design capabilities. Creates complex rhythmic and textural effects. Perfect for ambient music and experimental production.";

        // ============================================
        // HEARS
        // ============================================
        descriptions["hears perfection"] = "Mastering-grade loudness maximizer with transparent limiting and enhancement. Delivers competitive loudness without sacrificing dynamics. Essential for modern mastering requirements.";

        // ============================================
        // Maor Appelbaum & Hendyamps
        // ============================================
        descriptions["maor appelbaum hawkeye"] = "Professional metering and analysis tool designed by mastering engineer Maor Appelbaum. Provides comprehensive loudness and dynamic range visualization. Essential for professional mastering quality control.";

        // ============================================
        // Cut Classic
        // ============================================
        descriptions["cut classic high flyer"] = "Mastering dynamics processor with compression and limiting capabilities. Delivers polished, professional results with intuitive operation. Perfect for final stage mastering processing.";

        // ============================================
        // Additional short-name entries
        // ============================================
        descriptions["phil's cascade"] = "Cascaded compressor design offering multiple stages of compression for complex dynamic control. Provides smooth, multi-stage gain reduction with extensive tonal shaping options. Excellent for vocals, mix bus, and mastering applications.";
        descriptions["battalion"] = "Comprehensive distortion and amp processor with multiple gain stages and tonal options. Delivers everything from subtle warmth to crushing distortion. Ideal for guitar, bass, and creative sound mangling.";
        descriptions["eq232d"] = "Dual mono parametric equalizer with mastering-grade precision and musical character. Offers comprehensive frequency shaping with top-tier components. Ideal for critical mixing and mastering applications.";
        descriptions["tcl-2"] = "Recreation of the Millennia TCL-2 twin topology compressor with tube and solid-state paths. Offers the choice between warm tube or clean solid-state compression. Ideal for vocals and critical mixing requiring flexibility.";
        descriptions["high flyer"] = "Mastering dynamics processor with compression and limiting capabilities. Delivers polished, professional results with intuitive operation. Perfect for final stage mastering processing.";
        descriptions["splat"] = "Transient enhancement tool adding punch and impact to drums and percussion. Provides aggressive attack shaping with musical results. Essential for powerful drum sounds.";
        descriptions["c502v"] = "500-series format compressor with variable-mu characteristics and vintage warmth. Offers smooth, musical compression with rich harmonic content. Perfect for vocals and instruments requiring character.";
        descriptions["mu-66"] = "Variable-mu tube compressor emulation with smooth, musical compression characteristics. Delivers classic tube compression with rich harmonic enhancement. Perfect for vocals, mix bus, and mastering.";
        descriptions["bm60"] = "Parametric mastering equalizer with motorized controls and exceptional precision. Delivers surgical EQ with analog recall capabilities. Essential for professional mastering requiring precision and workflow.";
        descriptions["hype"] = "Multiband exciter and enhancer that adds presence, clarity, and excitement to any audio source. Uses musical saturation and dynamic processing to bring tracks to life. Ideal for vocals, drums, and full mix enhancement.";
        descriptions["vac attack"] = "Transient enhancer with aggressive attack shaping and punch enhancement. Adds impact and definition to drums and percussive material. Essential for powerful, punchy drum production.";
        descriptions["wavesurfer"] = "Modulation and spectral processing tool for creative sound design and mixing. Creates unique tonal transformations and movement effects. Perfect for experimental production and mixing.";
        descriptions["tape face"] = "Tape saturation emulation adding vintage warmth and compression characteristics. Recreates the sound of classic tape machines with controllable saturation. Ideal for adding analog character to digital recordings.";
        descriptions["te-100"] = "Tube equalizer offering warm, musical frequency shaping with harmonic enhancement. Features smooth tube saturation with precise EQ control. Excellent for adding vintage character and warmth.";
        descriptions["lion"] = "Powerful virtual synthesizer with advanced modulation and extensive sound design capabilities. Creates everything from classic synth sounds to complex evolving textures. Ideal for electronic music and sound design.";
        descriptions["knifonium"] = "Monophonic tube synthesizer with authentic analog warmth and character. Delivers rich, organic synth tones impossible to recreate digitally. Essential for basslines, leads, and vintage synth sounds.";
        descriptions["thorn"] = "Advanced virtual synthesizer with wavetable and subtractive synthesis combined. Delivers everything from classic analog sounds to modern digital tones. Perfect for contemporary electronic music production.";
        descriptions["utopia"] = "Ultimate mastering suite combining limiting, clipping, and saturation for maximum loudness with clarity. Provides transparent loudness maximization without sacrificing dynamic impact or musicality. The final word in competitive loudness for modern masters.";
        descriptions["metric ab"] = "Professional audio comparison and referencing tool for critical listening and mix decisions. Provides instant level-matched A/B comparison with multiple reference tracks. Essential for mixing, mastering, and quality control workflows.";
        descriptions["streamliner"] = "Intelligent loudness optimization tool that prepares audio for streaming platforms and broadcast. Automatically analyzes and adjusts dynamics to meet platform-specific requirements. Ensures your music sounds its best across all streaming services.";
        descriptions["sculpt"] = "Dynamic multi-band processor offering transparent compression, expansion, and tonal shaping in one plugin. Features intelligent automatic gain staging and musical attack/release characteristics. Perfect for detailed mix sculpting and mastering.";

        // ============================================
        // Additional exact-name entries for VST3 matching
        // ============================================

        // ADA
        descriptions["ada flanger"] = "Classic analog flanger emulation with the signature A/DA sweep and character. Delivers rich, jet-like flanging effects from subtle to extreme. Essential for recreating iconic modulation sounds.";
        descriptions["ada std-1 stereo tapped delay"] = "Recreation of the legendary STD-1 delay with its unique tapped delay algorithm. Creates complex rhythmic delays with vintage character. Perfect for creative guitar effects and sound design.";

        // Bettermaker variants
        descriptions["bettermaker c502v dsp"] = "500-series format compressor with variable-mu characteristics and vintage warmth. Offers smooth, musical compression with rich harmonic content. Perfect for vocals and instruments requiring character.";
        descriptions["bettermaker mastering compressor dsp"] = "High-end mastering compressor with musical compression and harmonic enhancement. Delivers transparent to colored compression with exceptional quality. The pinnacle of Polish audio engineering for professional mastering.";
        descriptions["bettermaker bus compressor dsp"] = "Professional bus compressor with the signature Bettermaker sound and extensive controls. Provides cohesive mix glue with musical compression characteristics. Ideal for mix bus and stem processing.";

        // bx_ plugins with exact names
        descriptions["bx_tonebox"] = "Amp-style tone shaping processor with guitar-focused EQ and saturation. Provides classic amp tones with modern flexibility. Perfect for adding amp character to any source.";
        descriptions["bx_boom"] = "Low-frequency enhancement and resonance control tool for powerful, controlled bass. Adds weight and punch without muddiness or boominess. Essential for electronic music and bass-heavy productions.";
        descriptions["bx_cleansweep v2"] = "High-quality filter plugin with resonant high-pass and low-pass filters for surgical cleanup. Features smooth filter curves and precise control for removing unwanted frequencies. Ideal for mixing preparation and creative filtering effects.";
        descriptions["bx_digital v3 mix"] = "11-band Mid/Side equalizer with parametric filters, dynamic EQ, and advanced metering for mixing and mastering.";
        descriptions["bx_dyneq v2 mono"] = "Dynamic equalizer combining precise EQ with intelligent frequency-dependent compression. Features up to five bands of dynamic processing with visual feedback. Perfect for surgical problem-solving and creative mixing.";
        descriptions["bx_hybrid v2 mix"] = "Comprehensive equalizer combining the best of digital precision and analog character. Features multiple EQ modes with automatic gain compensation. Excellent for both corrective and creative equalization.";
        descriptions["bx_opto pedal"] = "Compact optical compressor emulation with smooth, musical compression characteristics. Captures the classic opto sound with modern precision and control. Ideal for vocals, bass, and program material requiring gentle compression.";
        descriptions["bx_rockrack v3 player"] = "Streamlined guitar amp suite with essential amplifier models and cabinet options. Delivers professional guitar tones for any genre or style. Features intuitive workflow and high-quality amp emulations.";
        descriptions["bx_xl v2"] = "Mastering-grade limiter with intelligent automatic gain and transparent limiting characteristics. Provides competitive loudness without sacrificing dynamics or clarity. A benchmark tool for professional mastering.";
        descriptions["bx_masterdesk classic"] = "Classic mastering processor combining essential tools for quick, professional results. Offers one-knob mastering with automatic gain staging and musical processing. Perfect for fast masters and demo polishing.";
        descriptions["bx_delay2500"] = "Versatile stereo delay with extensive modulation and creative processing options. Features multiple delay modes with filtering, saturation, and rhythmic variations. Perfect for creative effects and ambient sound design.";

        // elysia variants
        descriptions["elysia alpha master"] = "Precision mastering compressor with M/S processing and customizable attack/release automation.";
        descriptions["elysia alpha mix"] = "Precision mixing compressor with M/S processing and customizable attack/release automation.";
        descriptions["elysia karacter master"] = "Three distortion modes for subtle enhancement to aggressive sound destruction with harmonic coloration.";
        descriptions["elysia karacter mix"] = "Three distortion modes for subtle enhancement to aggressive sound destruction with harmonic coloration.";
        descriptions["elysia museq master"] = "Musical passive equalizer with transformer-coupled circuitry and vintage-inspired tone shaping. Offers five bands of smooth, phase-coherent equalization with signature elysia character.";
        descriptions["elysia museq mix"] = "Musical passive equalizer with transformer-coupled circuitry and vintage-inspired tone shaping. Offers five bands of smooth, phase-coherent equalization with signature elysia character.";
        descriptions["elysia phils cascade"] = "Cascaded compressor design offering multiple stages of compression for complex dynamic control. Provides smooth, multi-stage gain reduction with extensive tonal shaping options. Excellent for vocals, mix bus, and mastering applications.";

        // fiedler audio
        descriptions["fiedler audio spacelab beam"] = "Spatial audio processor for precise positioning and immersive mixing. Creates accurate 3D placement in surround and binaural formats. Essential for immersive audio production.";
        descriptions["fiedler audio spacelab ignition"] = "Immersive audio processor for creating realistic spatial environments. Provides comprehensive room modeling and spatial enhancement. Perfect for immersive audio and game sound design.";
        descriptions["fiedler audio splat"] = "Transient enhancement tool adding punch and impact to drums and percussion. Provides aggressive attack shaping with musical results. Essential for powerful drum sounds.";
        descriptions["fiedler audio spatial creator"] = "Immersive reverb and spatial processor for creating realistic 3D environments. Generates convincing spatial audio with comprehensive room modeling. Perfect for immersive audio and game sound design.";

        // Kiive
        descriptions["kiive tape face"] = "Tape saturation emulation adding vintage warmth and compression characteristics. Recreates the sound of classic tape machines with controllable saturation. Ideal for adding analog character to digital recordings.";
        descriptions["kiive xtcomp"] = "Versatile compressor with multiple compression topologies and extensive control. Offers transparent to aggressive compression with tonal flexibility. Perfect for any mixing or mastering application.";
        descriptions["kiive xtressor"] = "Advanced compression processor with flexible topology and creative controls. Delivers everything from transparent dynamics control to aggressive pumping. Ideal for drums, vocals, and mix bus processing.";

        // Karanyi
        descriptions["karanyi sounds wavesurfer"] = "Modulation and spectral processing tool for creative sound design and mixing. Creates unique tonal transformations and movement effects. Perfect for experimental production and mixing.";

        // Lindell variants
        descriptions["lindell 50 buss"] = "Bus compressor inspired by classic API designs with punchy, aggressive character. Delivers tight, focused compression perfect for mix bus and stems. Essential for adding punch and cohesion.";
        descriptions["lindell 50 channel"] = "Channel strip inspired by classic API console designs with punchy, aggressive character. Delivers the tight, focused sound that defined American rock records. Essential for drums, guitars, and punchy mix processing.";
        descriptions["lindell 69 buss"] = "Bus compressor based on the iconic Neve 1073 design with transformer-coupled sound. Captures the legendary compression loved by engineers worldwide. Perfect for mix bus glue and warmth.";
        descriptions["lindell 69 channel"] = "Channel strip based on the iconic Neve 1073 design with transformer-coupled sound. Captures the legendary preamp and EQ combination loved by engineers worldwide. The gold standard for rock, pop, and vocal production.";
        descriptions["lindell 80 bus"] = "Bus compressor inspired by the legendary Neve 80-series console with rich harmonic character. Delivers classic British compression with modern workflow and precision. Essential for adding warmth and punch.";
        descriptions["lindell 80 channel"] = "Channel strip inspired by the legendary Neve 80-series console with rich harmonic character. Delivers the classic British sound with modern workflow and precision. Essential for adding warmth and punch to any source.";
        descriptions["lindell eq825"] = "Precision equalizer based on vintage American console designs with musical character. Offers smooth, musical EQ curves with classic tonal shaping. Perfect for adding vintage warmth and dimension.";
        descriptions["lindell 254e"] = "Vintage-style compressor with smooth, program-dependent compression characteristics. Offers classic limiting with musical results and easy operation. Perfect for vocals and gentle dynamic control.";
        descriptions["lindell 354e"] = "Passive EQ design based on vintage broadcast equalizers with smooth, musical curves. Delivers gentle, phase-coherent equalization with classic character. Ideal for mastering and adding vintage polish.";
        descriptions["lindell 6x-500"] = "Versatile 500-series compressor offering multiple compression flavors in one unit. Provides flexible dynamic control for various applications. Excellent for vocals, instruments, and mix bus.";
        descriptions["lindell 7x-500"] = "500-series format compressor with fast, punchy compression for drums and percussion. Delivers aggressive dynamic control with musical results. Ideal for adding punch and impact to drum tracks.";
        descriptions["lindell 902 de-esser"] = "Dedicated de-essing processor with surgical precision and transparent operation. Removes sibilance without affecting the natural character of vocals. Essential for polished vocal production.";
        descriptions["lindell channelx"] = "Comprehensive channel strip combining preamp, EQ, and compression in one workflow. Offers complete signal processing with vintage character. Ideal for tracking and mixing applications.";
        descriptions["lindell mbc"] = "Musical multiband compressor offering transparent dynamics control across frequency bands. Provides gentle or aggressive multiband compression with intuitive controls. Ideal for mastering and complex mix bus processing.";
        descriptions["lindell pex-500"] = "500-series format passive EQ with smooth, musical frequency shaping. Delivers vintage-style equalization with modern precision. Perfect for adding warmth and dimension.";
        descriptions["lindell sbc"] = "Simple bus compressor delivering cohesive mix glue with musical compression. Offers classic SSL-style compression with streamlined controls. Perfect for quick mix bus processing and stem compression.";
        descriptions["lindell te-100"] = "Tube equalizer offering warm, musical frequency shaping with harmonic enhancement. Features smooth tube saturation with precise EQ control. Excellent for adding vintage character and warmth.";

        // Mixland
        descriptions["mixland vac attack"] = "Transient enhancer with aggressive attack shaping and punch enhancement. Adds impact and definition to drums and percussive material. Essential for powerful, punchy drum production.";
        descriptions["mixland needlepoint"] = "Transient shaping processor with precise attack and sustain control. Provides surgical dynamic shaping with musical results. Essential for drums and adding punch to any source.";
        descriptions["mixland the oven"] = "Tube saturation processor adding rich harmonics and analog warmth. Delivers musical saturation from subtle to aggressive. Perfect for adding character to digital recordings.";

        // Purple Audio
        descriptions["purple audio mc 77"] = "Emulation of the legendary 1176-style FET compressor with fast, aggressive compression. Delivers the iconic punch and attitude of the original hardware. Essential for vocals, drums, and adding excitement to any source.";

        // SPL variants
        descriptions["spl de-esser dual-band"] = "Professional de-essing solution featuring dual-band modes for surgical or musical sibilance control. Uses SPL's intelligent detection algorithms for transparent, artifact-free processing. Essential for polished vocal production.";
        descriptions["spl vitalizer mk2-t"] = "Legendary psychoacoustic processor that enhances audio using SPL's proprietary bass and presence algorithms. Adds depth, clarity, and dimension without conventional EQ artifacts or phase issues. An industry staple for bringing mixes to life.";
        descriptions["spl passeq single"] = "Six-band passive mastering EQ with component-level modeling for precise equalization.";

        // THX
        descriptions["thx spatial creator"] = "Professional spatial audio creation tool for immersive 3D sound experiences. Enables accurate positioning and movement in immersive formats. Essential for game audio and immersive content creation.";

        // Unfiltered Audio
        descriptions["unfiltered audio triad"] = "Creative delay and modulation processor with unique sound design capabilities. Creates complex rhythmic and textural effects. Perfect for ambient music and experimental production.";
        descriptions["unfiltered audio needlepoint"] = "Transient shaping processor with precise attack and sustain control. Provides surgical dynamic shaping with musical results. Essential for drums and adding punch to any source.";
        descriptions["unfiltered audio bass mint"] = "Dedicated bass enhancement and saturation processor for powerful low-end. Adds weight and harmonic richness to bass without muddiness. Essential for electronic music and bass-heavy productions.";

        // Dangerous Music
        descriptions["dangerous bax eq master"] = "Legendary mastering equalizer with musical shelf curves and transformer character. Delivers smooth, broad strokes for tonal shaping in mastering. A benchmark tool for professional mastering engineers.";
        descriptions["dangerous bax eq mix"] = "Musical equalizer with smooth shelf curves and transformer character for mixing. Delivers broad strokes for tonal shaping with analog warmth. Perfect for mix bus and individual tracks.";

        // Louder Than Liftoff
        descriptions["louder than liftoff silver bullet mk2"] = "Dual-path coloration processor offering N and A type analog circuits. Provides instant analog warmth and character with simple controls. Essential for adding console mojo to digital mixes.";
        descriptions["silver bullet mk2"] = "Dual-path coloration processor offering N and A type analog circuits. Provides instant analog warmth and character with simple controls. Essential for adding console mojo to digital mixes.";

        // Shadow Hills variants
        descriptions["shadow hills class a mastering comp"] = "Class A variant of the legendary mastering compressor with enhanced harmonic richness and extended headroom. Features the same dual-stage compression topology with refined Class A circuitry throughout. Delivers even smoother compression with increased detail and air.";
        descriptions["shadow hills optomax"] = "Premium optical compressor based on Shadow Hills' custom design philosophy with musical program-dependent behavior. Combines the smoothness of optical compression with modern clarity and precision. Excellent for vocals, bass, and any source requiring transparent dynamic control.";

        // Chandler
        descriptions["chandler gav19t"] = "Emulation of the rare Chandler germanium amplifier with unique harmonic character. Delivers warm, vintage saturation with distinctive tonal qualities. Ideal for adding organic character to any source.";

        // Looptrotter
        descriptions["looptrotter sa2rate2"] = "Dual-stage saturation processor with multiple saturation types and routing options. Delivers everything from subtle warmth to aggressive distortion. Ideal for adding analog character and excitement.";

        // TOMO
        descriptions["tomo audiolabs lisa"] = "Analog-modeling saturation processor with harmonic enhancement capabilities. Delivers musical saturation with extensive tonal control. Perfect for adding warmth and character to any source.";

        // Acme
        descriptions["acme opticom xla-3"] = "Optical compressor with musical program-dependent compression characteristics. Delivers smooth, transparent gain reduction with vintage warmth. Ideal for vocals, bass, and gentle dynamic control.";

        // Harris Doyle
        descriptions["harris doyle natalus dsceq"] = "Dynamic shelving EQ with intelligent frequency-dependent processing. Offers musical tonal shaping with automatic dynamic control. Ideal for mastering and intelligent mix adjustment.";

        // HEARS
        descriptions["hears perfection"] = "Mastering-grade loudness maximizer with transparent limiting and enhancement. Delivers competitive loudness without sacrificing dynamics. Essential for modern mastering requirements.";

        // Cut Classic
        descriptions["cut classic high flyer"] = "Mastering dynamics processor with compression and limiting capabilities. Delivers polished, professional results with intuitive operation. Perfect for final stage mastering processing.";

        // Gallien Krueger
        descriptions["gallien krueger 800rb"] = "Iconic bass amplifier known for its articulate, punchy sound and legendary growl. Delivers the classic GK tone that defined slap bass and rock bass. Essential for players seeking clarity and cutting power.";

        // Maag (without Audio)
        descriptions["maag eq4"] = "Legendary six-band equalizer featuring the famous Air Band for adding pristine high-frequency shimmer. Simple yet powerful design that adds instant polish and dimension to any source. An industry-standard tool for vocals, drums, and mix bus processing.";
        descriptions["maag eq4 ms"] = "Mid-side version of the iconic EQ4, adding stereo width control to the famous Air Band design. Enables separate processing of center and side information for surgical stereo enhancement. Perfect for mastering and detailed stereo imaging work.";
        descriptions["maag eq2"] = "Streamlined two-band equalizer featuring the signature Air Band plus a musical low-frequency shelf. Provides quick, effective tonal shaping with Maag's legendary high-frequency character. Ideal for adding polish to individual tracks or full mixes.";
        descriptions["maag magnum-k"] = "Premium compressor with transformer-coupled signal path and musical program-dependent response. Offers smooth, vintage-style compression with modern precision and flexibility. Excellent for vocals, bass, and any source requiring musical dynamic control.";

        // Knif (without Audio)
        descriptions["knif soma"] = "Unique stereo enhancement processor using proprietary harmonic generation technology. Creates wide, dimensional stereo images with analog warmth. Perfect for mastering and adding depth to mixes.";
        descriptions["knif knifonium"] = "Monophonic tube synthesizer with authentic analog warmth and character. Delivers rich, organic synth tones impossible to recreate digitally. Essential for basslines, leads, and vintage synth sounds.";

        // HUM/LAAL
        descriptions["hum laal"] = "Unique lo-fi processing tool adding tape-style degradation and vintage character. Creates authentic vintage tones with controllable noise and saturation. Perfect for adding nostalgic character to modern productions.";

        // Three-Body Tech (short names)
        descriptions["kirchhoff-eq"] = "State-of-the-art parametric equalizer combining analog modeling with modern digital precision. Features multiple filter types per band including authentic analog console emulations. Delivers pristine sound quality with zero latency operation.";
        descriptions["cenozoix"] = "Advanced compressor with multiple compression styles and intelligent automatic gain compensation. Offers everything from transparent limiting to aggressive pumping with musical results. Features comprehensive sidechain options and visual feedback.";
        descriptions["cenozoix compressor"] = "Advanced compressor with multiple compression styles and intelligent automatic gain compensation. Offers everything from transparent limiting to aggressive pumping with musical results. Features comprehensive sidechain options and visual feedback.";
        descriptions["trinity shaper"] = "Versatile transient shaping and dynamic enhancement tool with three independent processing stages. Provides surgical control over attack, sustain, and overall dynamics of any source. Perfect for drums, percussion, and adding definition to complex mixes.";

        // DS Audio short names
        descriptions["thorn"] = "Advanced virtual synthesizer with wavetable and subtractive synthesis combined. Delivers everything from classic analog sounds to modern digital tones. Perfect for contemporary electronic music production.";
        descriptions["tantra 2"] = "Powerful rhythmic multi-effect with extensive modulation and sequencing capabilities. Creates complex rhythmic effects synced to tempo with visual editing. Essential for electronic music and creative production.";
        descriptions["ds audio tantra 2"] = "Powerful rhythmic multi-effect with extensive modulation and sequencing capabilities. Creates complex rhythmic effects synced to tempo with visual editing. Essential for electronic music and creative production.";
        descriptions["ds audio thorn"] = "Advanced virtual synthesizer with wavetable and subtractive synthesis combined. Delivers everything from classic analog sounds to modern digital tones. Perfect for contemporary electronic music production.";

        // Pro Audio DSP
        descriptions["pro audio dsp dsm v3"] = "Dynamic spectrum mapper for mastering with intelligent multi-band processing. Provides automatic tonal balance correction with musical results. Perfect for mastering and detailed mix refinement.";
        descriptions["dsm v3"] = "Dynamic spectrum mapper for mastering with intelligent multi-band processing. Provides automatic tonal balance correction with musical results. Perfect for mastering and detailed mix refinement.";

        // Additional bx_ variants (exact file names)
        descriptions["bx_rooms"] = "Creative reverb processor with unique room modeling and spatial enhancement capabilities. Offers everything from intimate spaces to vast, atmospheric environments. Perfect for adding depth and dimension to any production.";
        descriptions["bx_refinement"] = "De-harsh and smooth processor that removes digital harshness while preserving natural detail. Uses intelligent detection to target only problematic frequencies without over-processing. Essential for polishing digital recordings and harsh sources.";
        descriptions["bx_dyneq v2"] = "Dynamic equalizer combining precise EQ with intelligent frequency-dependent compression. Features up to five bands of dynamic processing with visual feedback. Perfect for surgical problem-solving and creative mixing.";
        descriptions["bx_hybrid v2"] = "Comprehensive equalizer combining the best of digital precision and analog character. Features multiple EQ modes with automatic gain compensation. Excellent for both corrective and creative equalization.";

        // elysia exact names
        descriptions["elysia alpha compressor v2"] = "Updated version of the celebrated mastering compressor with enhanced features and refined algorithms. Maintains the pristine Class A sound while adding new creative possibilities. The ultimate choice for professional mastering and critical mixing.";

        // ADPTR exact names
        descriptions["adptr hype"] = "Multiband exciter and enhancer that adds presence, clarity, and excitement to any audio source. Uses musical saturation and dynamic processing to bring tracks to life. Ideal for vocals, drums, and full mix enhancement.";
        descriptions["adptr metricab"] = "Professional audio comparison and referencing tool for critical listening and mix decisions. Provides instant level-matched A/B comparison with multiple reference tracks. Essential for mixing, mastering, and quality control workflows.";
        descriptions["adptr sculpt"] = "Dynamic multi-band processor offering transparent compression, expansion, and tonal shaping in one plugin. Features intelligent automatic gain staging and musical attack/release characteristics. Perfect for detailed mix sculpting and mastering.";
        descriptions["adptr streamliner"] = "Intelligent loudness optimization tool that prepares audio for streaming platforms and broadcast. Automatically analyzes and adjusts dynamics to meet platform-specific requirements. Ensures your music sounds its best across all streaming services.";
        descriptions["adptr utopia"] = "Ultimate mastering suite combining limiting, clipping, and saturation for maximum loudness with clarity. Provides transparent loudness maximization without sacrificing dynamic impact or musicality. The final word in competitive loudness for modern masters.";

        // Swivel Audio exact names
        descriptions["swivel audio bde"] = "Bass enhancement processor adding harmonics and weight to low-frequency content. Creates fuller, more powerful bass without muddiness. Ideal for bass-heavy music and adding low-end presence.";
        descriptions["swivel audio click boom"] = "Transient enhancement tool specifically designed for kick drums and bass. Adds attack and low-end power with precise control. Essential for impactful drum sounds in any genre.";
        descriptions["swivel audio hitstrip"] = "Mix bus processing chain optimized for hip-hop and modern production styles. Combines essential processing tools in one streamlined workflow. Perfect for quick, professional mix enhancement.";
        descriptions["swivel audio knocktonal"] = "Kick drum enhancer with sub-harmonic generation and tonal shaping capabilities. Adds weight, punch, and definition to kick drums. Perfect for electronic music and modern drum production.";
        descriptions["swivel audio spread"] = "Stereo enhancement processor creating wide, immersive stereo images with mono compatibility. Uses advanced algorithms for natural-sounding width expansion. Perfect for creating spacious mixes without phase issues.";
        descriptions["swivel audio the sauce"] = "Multi-effect processor combining saturation, compression, and tonal enhancement. Adds instant warmth and presence to any source with simple controls. Essential for quick mix enhancement and polish.";

        // SPL exact names
        descriptions["spl attacker plus"] = "Advanced transient enhancement processor with multiple modes for different shaping characteristics. Adds punch, attack, and presence to drums, guitars, and any percussive material. Features expanded controls compared to the original Transient Designer.";
        descriptions["spl big"] = "Powerful stereo imaging tool that provides precise control over width, mono compatibility, and bass management. Features SPL's renowned M/S processing for surgical stereo field adjustments. Essential for mastering and creating wide, impactful mixes.";
        descriptions["spl de-esser"] = "Professional de-essing solution featuring multiple modes for surgical or musical sibilance control. Uses SPL's intelligent detection algorithms for transparent, artifact-free processing. Essential for polished vocal production in any genre.";
        descriptions["spl de-verb plus"] = "Intelligent reverb reduction tool that removes unwanted room ambience and reverb tails from recordings. Uses advanced algorithms to preserve the natural character of the source material. Essential for cleaning up problematic recordings and dialogue.";
        descriptions["spl drumxchanger"] = "Intelligent drum replacement and augmentation tool that analyzes and replaces drum hits with samples. Features automatic detection and natural-sounding triggering algorithms. Perfect for enhancing or replacing drum sounds in any production.";
        descriptions["spl eq ranger plus"] = "Comprehensive multi-band equalizer with surgical precision and musical character. Offers flexible filter types and precise gain control across all bands. Ideal for corrective and creative EQ applications.";
        descriptions["spl free ranger"] = "Streamlined four-band equalizer offering essential EQ functions with SPL's signature sound quality. Provides musical equalization with intuitive controls and low CPU usage. Great for everyday mixing tasks and quick tonal adjustments.";
        descriptions["spl hawkeye"] = "Metering suite with level, loudness, bit monitoring, vectorscope, and spectrum analyzer.";
        descriptions["spl iron"] = "Tube compressor with dual-circuit topology for transparent, musical compression in mastering and tracking.";
        descriptions["spl machine head"] = "Unique amplifier and saturation processor combining multiple classic amp circuits and tape saturation stages. Delivers everything from subtle warmth to aggressive distortion with musical character. Perfect for adding edge and excitement to any source.";
        descriptions["spl mo-verb plus"] = "Creative modulation reverb processor combining classic reverb algorithms with dynamic modulation effects. Produces lush, animated spatial effects from subtle ambience to dramatic washes. Perfect for sound design and creative production.";
        descriptions["spl passeq"] = "Six-band passive mastering EQ with component-level modeling for precise equalization.";
        descriptions["spl pq"] = "Mastering-grade parametric equalizer with extremely precise controls and transparent sound quality. Features five fully parametric bands with surgical Q control and pristine filters. A benchmark tool for professional mastering engineers.";
        descriptions["spl transient designer plus"] = "Threshold-independent transient processing with separate Attack and Sustain controls.";
        descriptions["spl twintube"] = "Dual-channel tube saturation processor offering rich harmonic enhancement and musical coloration. Features independent drive controls for subtle warmth or aggressive tube saturation. Ideal for adding analog character to digital recordings.";
        descriptions["spl vitalizer mk3-t"] = "Legendary psychoacoustic processor that enhances audio using SPL's proprietary bass and presence algorithms. Adds depth, clarity, and dimension without conventional EQ artifacts or phase issues. An industry staple for bringing mixes to life in mastering and mixing.";

        // Millennia exact names
        descriptions["millennia nseq-2"] = "Emulation of the legendary Millennia NSEQ-2 parametric EQ known for pristine transparency. Delivers surgical precision with minimal coloration and phase shift. The benchmark for transparent mastering equalization.";
        descriptions["millennia tcl-2"] = "Recreation of the Millennia TCL-2 twin topology compressor with tube and solid-state paths. Offers the choice between warm tube or clean solid-state compression. Ideal for vocals and critical mixing requiring flexibility.";

        // Noveltech exact names
        descriptions["noveltech character"] = "Intelligent audio enhancement processor that analyzes and improves tonal balance automatically. Uses advanced algorithms to enhance clarity and presence musically. Perfect for quick enhancement of any audio source.";
        descriptions["noveltech vocal enhancer"] = "Dedicated vocal processor optimizing vocals for clarity, presence, and impact. Provides automatic enhancement with minimal setup required. Essential for polished vocal production.";

        // Diezel, Friedman, ENGL, Suhr, Fuchs exact names
        descriptions["diezel herbert"] = "Emulation of the legendary three-channel Diezel Herbert amplifier. Delivers pristine cleans through crushing high-gain with exceptional clarity. Essential for modern metal and progressive rock guitar tones.";
        descriptions["diezel vh4"] = "Recreation of the iconic VH4 amplifier revered for its tight, articulate high-gain sound. Provides four channels of Diezel tone from clean to extreme gain. The benchmark for modern metal rhythm and lead tones.";
        descriptions["friedman be100"] = "Emulation of the acclaimed BE-100 amplifier with its legendary high-gain tones. Delivers the famous brown sound with tight low-end and smooth sustain. Essential for classic rock to modern metal applications.";
        descriptions["friedman buxom betty"] = "Recreation of the Buxom Betty amplifier known for its dynamic cleans and crunchy overdrive. Offers exceptional touch sensitivity and musical breakup. Perfect for blues, rock, and country guitar tones.";
        descriptions["friedman ds40"] = "Compact Friedman amplifier delivering signature tones in a streamlined format. Provides the Friedman sound with focused controls and consistent response. Ideal for recording and smaller performance spaces.";
        descriptions["engl e646 vs"] = "Victor Smolski signature amplifier with aggressive high-gain character. Delivers tight, focused distortion for technical metal applications. Ideal for progressive and modern metal guitar tones.";
        descriptions["engl e765 rt"] = "Versatile ENGL amplifier offering clean to high-gain tones with German precision. Features the retro tube design with modern reliability. Perfect for rock, metal, and versatile studio applications.";
        descriptions["engl savage 120"] = "Powerful high-gain amplifier emulation with extreme saturation and tight response. Delivers crushing metal tones with exceptional clarity and definition. Essential for modern extreme metal productions.";
        descriptions["suhr pt100"] = "Premium amplifier emulation based on the Suhr PT100 with exceptional clarity. Delivers boutique-quality tones from clean to high-gain with musical response. Perfect for professional studio and live applications.";
        descriptions["suhr se100"] = "Signature Edition amplifier with refined high-gain capabilities and touch sensitivity. Offers the Suhr sound with enhanced features and tonal flexibility. Excellent for rock, fusion, and modern guitar styles.";
        descriptions["fuchs overdrive supreme 50"] = "Premium overdrive amplifier with rich harmonic content and smooth saturation. Delivers singing lead tones with excellent sustain and clarity. Ideal for blues, classic rock, and fusion applications.";
        descriptions["fuchs train ii"] = "Boutique amplifier emulation delivering warm, dynamic tones with exceptional touch response. Offers vintage-inspired sound with modern reliability and consistency. Perfect for blues, rock, and expressive playing.";

        // Vertigo exact names
        descriptions["vertigo vsc-2"] = "Emulation of the acclaimed Vertigo Sound VCA compressor with its punchy, musical character. Delivers aggressive yet musical compression perfect for drums and mix bus. Features the signature Vertigo sound with modern precision.";
        descriptions["vertigo vsm-3"] = "Unique saturation and mix processor combining vintage and modern harmonic enhancement. Offers multiple saturation modes from subtle warmth to aggressive distortion. Essential for adding analog character and excitement to mixes.";
        descriptions["vertigo vss-2"] = "Premium saturation processor with versatile coloration and harmonics generation. Provides everything from subtle warmth to intense saturation with musical results. Perfect for adding analog character to digital recordings.";

        // Ampeg exact names
        descriptions["ampeg b15n"] = "Legendary Portaflex bass amplifier known for its warm, vintage tone and smooth breakup. Captures the classic sound that defined Motown and countless recordings. Essential for vintage bass tones with character and warmth.";
        descriptions["ampeg svtvr"] = "Recreation of the iconic SVT with its powerful, authoritative bass tone. Delivers the full-stack sound that defined rock bass for generations. The benchmark for loud, aggressive bass amplification.";
        descriptions["ampeg svtvr classic"] = "Classic version of the SVT capturing the vintage circuit with period-correct components. Offers the original SVT sound with authentic tube response. Perfect for vintage rock and blues bass tones.";
        descriptions["ampeg svt3pro"] = "Modern SVT variant with tighter low-end and extended clean headroom. Provides the SVT character with modern reliability and consistency. Ideal for contemporary rock and metal bass.";
        descriptions["ampeg v4b"] = "All-tube bass head delivering warm, dynamic tone with natural compression. Offers the classic Ampeg sound in a more portable format. Excellent for recording and smaller venues.";

        // NEOLD exact names
        descriptions["neold big al"] = "Dual-stage tube saturator with 1930s transformer-coupled pre and power amplifier circuitry for vintage harmonic saturation.";
        descriptions["neold oldtimer"] = "Captures the essence of vintage broadcast limiters with smooth, musical compression and rich harmonic saturation. Ideal for adding vintage warmth and cohesion to full mixes and stems. Features simple controls for fast, intuitive operation.";
        descriptions["neold rz062"] = "Emulation of a legendary Russian broadcast compressor known for its aggressive character and unique colorful compression. Perfect for adding weight and punch to drums, bass, and mix bus applications. Features authentic saturation and a distinctively musical response.";
        descriptions["neold u17"] = "Recreation of the legendary Fairchild-style variable-mu tube compressor with exceptional musical compression. Provides smooth, program-dependent compression that enhances rather than squashes dynamics. A go-to choice for vocals, bass, and mix bus duties.";
        descriptions["neold u2a"] = "Authentic emulation of the classic LA-2A optical compressor known for its smooth, transparent compression. Features the signature optical attenuator response that's perfect for vocals and bass. Delivers effortless gain reduction with a warm, musical character.";
        descriptions["neold v76u73"] = "1950s Telefunken V76 preamp and U73 compressor emulation with rich low-end warmth and smooth high-frequency character.";
        descriptions["neold warble"] = "Vintage tape modulation with wow/flutter effects, magnetic tape aging, and resonant filtering for warm analog character.";
        descriptions["neold wunderlich"] = "Based on a rare German broadcast compressor with a distinctive aggressive compression character. Adds punch and excitement to drums and percussion with its fast attack capabilities. Features unique saturation characteristics and program-dependent release.";

        // Unfiltered Audio exact names
        descriptions["unfiltered audio byome"] = "Modular effects with 40 unique types including reverbs, delays, dynamics, and mixing tools.";
        descriptions["unfiltered audio dent 2"] = "Advanced waveform destruction processor with multiple distortion algorithms and modulation. Creates everything from subtle saturation to extreme digital mayhem. Essential for sound design and experimental production.";
        descriptions["unfiltered audio fault"] = "Distortion and modulation processor with envelope following and creative mangling. Delivers dynamic distortion effects that respond to input. Perfect for aggressive sound design and creative effects.";
        descriptions["unfiltered audio g8"] = "Dynamic gate with MIDI control and alternate modes for creative sound shaping and transient manipulation.";
        descriptions["unfiltered audio indent 2"] = "Dynamic transient processor with gate-like capabilities and creative modulation options. Provides precise control over dynamics with unique creative possibilities. Ideal for drums, percussion, and rhythmic effects.";
        descriptions["unfiltered audio instant delay"] = "Zero-latency delay processor with comprehensive modulation and filtering options. Offers immediate delay effects with extensive sound design capabilities. Essential for live performance and creative mixing.";
        descriptions["unfiltered audio lion"] = "Powerful virtual synthesizer with advanced modulation and extensive sound design capabilities. Creates everything from classic synth sounds to complex evolving textures. Ideal for electronic music and sound design.";
        descriptions["unfiltered audio lo-fi-af"] = "Comprehensive lo-fi processing suite with bit-crushing, saturation, and degradation. Creates authentic vintage and degraded tones with extensive control. Perfect for lo-fi hip-hop and nostalgic productions.";
        descriptions["unfiltered audio sandman"] = "Streamlined delay processor with musical modulation and tempo-sync capabilities. Offers quick access to creative delay effects with intuitive controls. Perfect for everyday mixing and sound design.";
        descriptions["unfiltered audio sandman pro"] = "Advanced delay processor with extensive modulation and rhythmic capabilities. Creates complex delay patterns and evolving textures. Ideal for creative production and experimental mixing.";
        descriptions["unfiltered audio silo"] = "Granular delay and looping processor with extensive real-time manipulation capabilities. Transforms audio into evolving textures and ambient soundscapes. Perfect for experimental music and cinematic sound design.";
        descriptions["unfiltered audio specops"] = "Multi-effect processor combining spectral processing with modulation and distortion. Creates unique tonal transformations and spectral effects. Essential for experimental sound design and creative mixing.";
        descriptions["unfiltered audio tails"] = "Reverb processor creating lush, infinite sustain and frozen texture effects. Generates evolving ambient soundscapes from any audio source. Perfect for ambient music and atmospheric sound design.";
        descriptions["unfiltered audio zip"] = "Compressor with extreme compression capabilities and creative pumping effects. Provides transparent to aggressive dynamics control with unique character. Essential for drum processing and creative mixing.";
        descriptions["unfiltered audio battalion"] = "Comprehensive distortion and amp processor with multiple gain stages and tonal options. Delivers everything from subtle warmth to crushing distortion. Ideal for guitar, bass, and creative sound mangling.";
    }

    // Normalize the plugin name for lookup
    auto normalizedName = pluginName.toLowerCase().trim();

    // Try direct lookup
    auto it = descriptions.find(normalizedName);
    if (it != descriptions.end())
        return it->second;

    // Try removing common brand prefixes
    juce::StringArray brandPrefixes = {
        "brainworx ", "unfiltered audio ", "plugin alliance ", "ds audio ",
        "knif audio ", "knif ", "lindell audio ", "lindell ", "maag audio ", "maag ", "mäag audio ",
        "shadow hills ", "black box analog design ", "black box ",
        "three-body technology ", "fiedler audio ", "adptr audio ", "adptr ",
        "swivel audio ", "kiive audio ", "kiive ", "tomo audiolabs ", "hum audio devices ", "hum ",
        "louder than liftoff ", "pro audio dsp ", "purple audio ",
        "dangerous music ", "dangerous ", "chandler limited ", "chandler ", "harris doyle ",
        "karanyi sounds ", "cut classic ", "acme audio ", "acme ", "mixland ",
        "maor appelbaum ", "noveltech ", "bettermaker ", "looptrotter ",
        "millennia ", "vertigo ", "elysia ", "spl ", "neold ", "amek ",
        "ampeg ", "diezel ", "engl ", "friedman ", "fuchs ", "suhr ",
        "gallien-krueger ", "gallien krueger ", "thx "
    };

    for (const auto& prefix : brandPrefixes)
    {
        if (normalizedName.startsWith(prefix))
        {
            auto withoutPrefix = normalizedName.substring(prefix.length()).trim();
            it = descriptions.find(withoutPrefix);
            if (it != descriptions.end())
                return it->second;
        }
    }

    // Try adding brand prefixes for short names
    for (const auto& prefix : brandPrefixes)
    {
        auto withPrefix = prefix + normalizedName;
        it = descriptions.find(withPrefix);
        if (it != descriptions.end())
            return it->second;
    }

    return juce::String();
}

} // namespace PALauncher
