/*
  ==============================================================================
    PluginImageCache.cpp
    Plugin Alliance Launcher - Plugin Image Download and Caching Implementation
  ==============================================================================
*/

#include "PluginImageCache.h"

namespace PALauncher
{

PluginImageCache::PluginImageCache()
    : Thread("PluginImageCache")
{
    initializeImageUrls();
    initializeThumbnailFilenames();
    initializeBundledImagesPath();
    startThread();
}

void PluginImageCache::initializeBundledImagesPath()
{
    // Try to find bundled images in various locations

    // First, try the VST3 bundle's Resources folder
    // On Windows, VST3 plugins are located in: plugin.vst3/Contents/x86_64-win/plugin.vst3
    // The Resources folder is at: plugin.vst3/Contents/Resources/
    auto executableFile = juce::File::getSpecialLocation(juce::File::currentExecutableFile);

    // Navigate from x86_64-win up to Contents, then to Resources
    auto contentsFolder = executableFile.getParentDirectory().getParentDirectory();
    auto resourcesInBundle = contentsFolder.getChildFile("Resources").getChildFile("Thumbnails");

    if (resourcesInBundle.isDirectory())
    {
        bundledImagesPath = resourcesInBundle;
        DBG("Found bundled images at: " + bundledImagesPath.getFullPathName());
        return;
    }

    // Try alternate: plugin located directly in VST3 folder
    auto vst3Folder = executableFile.getParentDirectory();
    auto resourcesAlt = vst3Folder.getChildFile("Resources").getChildFile("Thumbnails");

    if (resourcesAlt.isDirectory())
    {
        bundledImagesPath = resourcesAlt;
        DBG("Found bundled images at: " + bundledImagesPath.getFullPathName());
        return;
    }

    // Fallback: check common installation path
    auto programDataFolder = juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory);
    auto paLauncherResources = programDataFolder.getChildFile("PALauncher").getChildFile("Thumbnails");

    if (paLauncherResources.isDirectory())
    {
        bundledImagesPath = paLauncherResources;
        DBG("Found bundled images at: " + bundledImagesPath.getFullPathName());
        return;
    }

    DBG("No bundled images folder found");
}

void PluginImageCache::initializeThumbnailFilenames()
{
    // Map normalized plugin names to thumbnail filenames (without .png extension)
    // These match the files downloaded from Plugin Alliance

    // NEOLD
    thumbnailFilenames["neold rz062"] = "neold_rz062";
    thumbnailFilenames["neold v76u73"] = "neold_v76u73";
    thumbnailFilenames["neold warble"] = "neold_warble";
    thumbnailFilenames["neold big al"] = "neold_big_al";
    thumbnailFilenames["neold u17"] = "neold_u17";
    thumbnailFilenames["neold u2a"] = "neold_u2a";
    thumbnailFilenames["neold wunderlich"] = "neold_wunderlich";
    thumbnailFilenames["neold oldtimer"] = "neold_oldtimer";

    // Shadow Hills
    thumbnailFilenames["shadow hills mastering compressor"] = "shadow_hills_mastering_compressor";
    thumbnailFilenames["shadow hills mastering compressor class a"] = "shadow_hills_mastering_compressor_class_a";
    thumbnailFilenames["shadow hills optomax"] = "shadow_hills_optomax";

    // SPL
    thumbnailFilenames["spl vitalizer mk3-t"] = "spl_vitalizer_mk3t";
    thumbnailFilenames["spl vitalizer mk2-t"] = "spl_vitalizer_mk3t";
    thumbnailFilenames["spl big"] = "spl_big";
    thumbnailFilenames["spl machine head"] = "spl_machine_head";
    thumbnailFilenames["spl twintube"] = "spl_twintube";
    thumbnailFilenames["spl de-esser collection"] = "spl_de_esser_collection";
    thumbnailFilenames["spl de-esser"] = "spl_de_esser_collection";
    thumbnailFilenames["spl transient designer plus"] = "spl_transient_designer_plus";
    thumbnailFilenames["spl iron"] = "spl_iron";
    thumbnailFilenames["spl passeq"] = "spl_passeq";
    thumbnailFilenames["spl attacker plus"] = "spl_attacker_plus";
    thumbnailFilenames["spl de-verb plus"] = "spl_deverb_plus";
    thumbnailFilenames["spl drumxchanger"] = "spl_drumxchanger";
    thumbnailFilenames["spl eq ranger plus"] = "spl_eq_ranger_plus";
    thumbnailFilenames["spl mo-verb plus"] = "spl_moverb_plus";
    thumbnailFilenames["spl hawkeye"] = "spl_hawkeye";
    thumbnailFilenames["spl pq"] = "spl_pq";
    thumbnailFilenames["spl free ranger"] = "spl_free_ranger";

    // elysia
    thumbnailFilenames["elysia alpha compressor"] = "elysia_alpha_compressor";
    thumbnailFilenames["elysia alpha compressor v2"] = "elysia_alpha_compressor";
    thumbnailFilenames["elysia museq"] = "elysia_museq";
    thumbnailFilenames["elysia karacter"] = "elysia_karacter";
    thumbnailFilenames["elysia mpressor"] = "elysia_mpressor";
    thumbnailFilenames["elysia nvelope"] = "elysia_nvelope";
    thumbnailFilenames["elysia niveau filter"] = "elysia_niveau_filter";
    thumbnailFilenames["elysia phils cascade"] = "elysia_phils_cascade";

    // Maag Audio
    thumbnailFilenames["maag audio eq4"] = "maag_audio_eq4";
    thumbnailFilenames["mäag audio eq4"] = "maag_audio_eq4";
    thumbnailFilenames["maag audio eq4 ms"] = "maag_audio_eq4_ms";
    thumbnailFilenames["mäag audio eq4 ms"] = "maag_audio_eq4_ms";
    thumbnailFilenames["maag audio eq2"] = "maag_audio_eq2";
    thumbnailFilenames["mäag audio eq2"] = "maag_audio_eq2";
    thumbnailFilenames["maag audio magnum-k"] = "maag_audio_magnum_k";
    thumbnailFilenames["mäag audio magnum-k"] = "maag_audio_magnum_k";

    // ADPTR AUDIO
    thumbnailFilenames["adptr audio metric ab"] = "adptr_metric_ab";
    thumbnailFilenames["adptr audio streamliner"] = "adptr_streamliner";
    thumbnailFilenames["adptr audio sculpt"] = "adptr_sculpt";
    thumbnailFilenames["adptr audio utopia"] = "adptr_utopia";
    thumbnailFilenames["adptr audio hype"] = "adptr_hype";

    // Three-Body Technology
    thumbnailFilenames["kirchhoff-eq"] = "kirchhoff_eq";
    thumbnailFilenames["cenozoix compressor"] = "cenozoix_compressor";
    thumbnailFilenames["trinity shaper"] = "trinity_shaper";

    // Black Box Analog Design
    thumbnailFilenames["black box analog design hg-2ms"] = "black_box_hg2ms";
    thumbnailFilenames["black box analog design hg-2"] = "black_box_hg2";
    thumbnailFilenames["black box analog design hg-q"] = "black_box_hgq";

    // Brainworx
    thumbnailFilenames["bx_xl v3"] = "bx_xl_v3";
    thumbnailFilenames["bx_console ssl 4000 e"] = "bx_console_ssl_4000_e";
    thumbnailFilenames["bx_console ssl 4000 g"] = "bx_console_ssl_4000_g";
    thumbnailFilenames["bx_console ssl 9000 j"] = "bx_console_ssl_9000_j";
    thumbnailFilenames["bx_console amek 9099"] = "bx_console_amek_9099";
    thumbnailFilenames["bx_console amek 200"] = "bx_console_amek_200";
    thumbnailFilenames["bx_console focusrite sc"] = "bx_console_focusrite_sc";
    thumbnailFilenames["bx_console n"] = "bx_console_n";
    thumbnailFilenames["bx_digital v3"] = "bx_digital_v3";
    thumbnailFilenames["bx_pulsar"] = "bx_pulsar";
    thumbnailFilenames["bx_refinement v3"] = "bx_refinement_v3";
    thumbnailFilenames["bx_clipper"] = "bx_clipper";
    thumbnailFilenames["bx_aura"] = "bx_aura";
    thumbnailFilenames["bx_masterdesk pro"] = "bx_masterdesk_pro";
    thumbnailFilenames["bx_masterdesk"] = "bx_masterdesk";
    thumbnailFilenames["bx_masterdesk true peak"] = "bx_masterdesk_true_peak";
    thumbnailFilenames["bx_cleansweep pro"] = "bx_cleansweep_pro";
    thumbnailFilenames["bx_control v2"] = "bx_control_v2";
    thumbnailFilenames["bx_delay 2500"] = "bx_delay2500";
    thumbnailFilenames["bx_delay2500"] = "bx_delay2500";
    thumbnailFilenames["bx_rockergain100"] = "bx_rockergain100";
    thumbnailFilenames["bx_subsynth"] = "bx_subsynth";
    thumbnailFilenames["bx_roooms"] = "bx_rooms";
    thumbnailFilenames["bx_oberhausen"] = "bx_oberhausen";
    thumbnailFilenames["bx_paneq"] = "bx_paneq";
    thumbnailFilenames["bx_dyneq v2"] = "bx_dyneq_v2";
    thumbnailFilenames["bx_megadual"] = "bx_megadual";
    thumbnailFilenames["bx_opto"] = "bx_opto";
    thumbnailFilenames["bx_townhouse buss compressor"] = "bx_townhouse";
    thumbnailFilenames["bx_townhouse"] = "bx_townhouse";
    thumbnailFilenames["bx_2098 eq"] = "bx_2098_eq";
    thumbnailFilenames["bx_saturator v2"] = "bx_saturator_v2";
    thumbnailFilenames["bx_hybrid v2"] = "bx_hybrid_v2";
    thumbnailFilenames["bx_stereomaker"] = "bx_stereomaker";
    thumbnailFilenames["bx_limiter"] = "bx_limiter";
    thumbnailFilenames["bx_limiter true peak"] = "bx_limiter_true_peak";
    thumbnailFilenames["bx_bassdude"] = "bx_bassdude";
    thumbnailFilenames["bx_rockrack v3"] = "bx_rockrack_v3";
    thumbnailFilenames["bx_crispytuner"] = "bx_crispytuner";
    thumbnailFilenames["bx_crispyscale"] = "bx_crispyscale";
    thumbnailFilenames["bx_glue"] = "bx_glue";
    thumbnailFilenames["bx_enhancer"] = "bx_enhancer";
    thumbnailFilenames["bx_boom v3"] = "bx_boom_v3";
    thumbnailFilenames["bx_boom"] = "bx_boom_v3";
    thumbnailFilenames["bx_blackdist2"] = "bx_blackdist2";
    thumbnailFilenames["bx_bluechorus2"] = "bx_bluechorus2";
    thumbnailFilenames["bx_greenscreamer"] = "bx_greenscreamer";
    thumbnailFilenames["bx_distorange"] = "bx_distorange";
    thumbnailFilenames["bx_yellowdrive"] = "bx_yellowdrive";
    thumbnailFilenames["bx_metal2"] = "bx_metal2";
    thumbnailFilenames["bx_megasingle"] = "bx_megasingle";
    thumbnailFilenames["bx_tuner"] = "bx_tuner";
    thumbnailFilenames["bx_meter"] = "bx_meter";
    thumbnailFilenames["bx_solo"] = "bx_solo";
    thumbnailFilenames["bx_subfilter"] = "bx_subfilter";
    thumbnailFilenames["bx_shredspread"] = "bx_shredspread";

    // Vertigo
    thumbnailFilenames["vertigo vss-2"] = "vertigo_vss2";
    thumbnailFilenames["vertigo vsc-2"] = "vertigo_vsc2";
    thumbnailFilenames["vertigo vsm-3"] = "vertigo_vsm3";

    // HUM Audio Devices
    thumbnailFilenames["hum audio devices laal"] = "hum_laal";
    thumbnailFilenames["laal"] = "hum_laal";

    // Millennia
    thumbnailFilenames["millennia nseq-2"] = "millennia_nseq2";
    thumbnailFilenames["millennia tcl-2"] = "millennia_tcl2";

    // Lindell Audio
    thumbnailFilenames["lindell audio 80 series"] = "lindell_80_series";
    thumbnailFilenames["lindell 80 bus"] = "lindell_80_series";
    thumbnailFilenames["lindell 80 channel"] = "lindell_80_series";
    thumbnailFilenames["lindell audio eq825"] = "lindell_eq825";
    thumbnailFilenames["lindell eq825"] = "lindell_eq825";
    thumbnailFilenames["lindell audio 69 series"] = "lindell_69_series";
    thumbnailFilenames["lindell 69 buss"] = "lindell_69_series";
    thumbnailFilenames["lindell 69 channel"] = "lindell_69_series";
    thumbnailFilenames["lindell audio 50 series"] = "lindell_50_series";
    thumbnailFilenames["lindell 50 buss"] = "lindell_50_series";
    thumbnailFilenames["lindell 50 channel"] = "lindell_50_series";
    thumbnailFilenames["lindell audio 354e"] = "lindell_354e";
    thumbnailFilenames["lindell 354e"] = "lindell_354e";
    thumbnailFilenames["lindell audio 254e"] = "lindell_254e";
    thumbnailFilenames["lindell 254e"] = "lindell_254e";
    thumbnailFilenames["lindell audio channelx"] = "lindell_channelx";
    thumbnailFilenames["lindell channelx"] = "lindell_channelx";
    thumbnailFilenames["lindell mu-66"] = "lindell_mu66";
    thumbnailFilenames["lindell 6x-500"] = "lindell_6x500";
    thumbnailFilenames["lindell 7x-500"] = "lindell_7x500";
    thumbnailFilenames["lindell pex-500"] = "lindell_pex500";
    thumbnailFilenames["lindell te-100"] = "lindell_te100";
    thumbnailFilenames["lindell 902 de-esser"] = "lindell_902_deesser";
    thumbnailFilenames["lindell mbc"] = "lindell_mbc";
    thumbnailFilenames["lindell sbc"] = "lindell_sbc";

    // AMEK
    thumbnailFilenames["amek eq 200"] = "amek_eq200";
    thumbnailFilenames["amek eq 250"] = "amek_eq250";
    thumbnailFilenames["amek mastering compressor"] = "amek_mastering_compressor";

    // Ampeg (note: plugin names may or may not have hyphens)
    thumbnailFilenames["ampeg b-15n"] = "ampeg_b15n";
    thumbnailFilenames["ampeg b15n"] = "ampeg_b15n";
    thumbnailFilenames["ampeg svt-vr"] = "ampeg_svtvr";
    thumbnailFilenames["ampeg svtvr"] = "ampeg_svtvr";
    thumbnailFilenames["ampeg svt-vr classic"] = "ampeg_svtvr_classic";
    thumbnailFilenames["ampeg svtvr classic"] = "ampeg_svtvr_classic";
    thumbnailFilenames["ampeg svt-3pro"] = "ampeg_svt3pro";
    thumbnailFilenames["ampeg svt3pro"] = "ampeg_svt3pro";
    thumbnailFilenames["ampeg v-4b"] = "ampeg_v4b";
    thumbnailFilenames["ampeg v4b"] = "ampeg_v4b";

    // Diezel
    thumbnailFilenames["diezel herbert"] = "diezel_herbert";
    thumbnailFilenames["diezel vh4"] = "diezel_vh4";

    // Friedman
    thumbnailFilenames["friedman be-100"] = "friedman_be100";
    thumbnailFilenames["friedman buxom betty"] = "friedman_buxom_betty";
    thumbnailFilenames["friedman ds-40"] = "friedman_ds40";

    // ENGL
    thumbnailFilenames["engl savage 120"] = "engl_savage_120";
    thumbnailFilenames["engl e765 rt"] = "engl_e765_rt";
    thumbnailFilenames["engl e646 vs"] = "engl_e646_vs";

    // Suhr
    thumbnailFilenames["suhr pt100"] = "suhr_pt100";
    thumbnailFilenames["suhr se100"] = "suhr_se100";

    // Gallien-Krueger
    thumbnailFilenames["gallien-krueger 800rb"] = "gallien_krueger_800rb";

    // Fuchs
    thumbnailFilenames["fuchs train ii"] = "fuchs_train_ii";
    thumbnailFilenames["fuchs overdrive supreme 50"] = "fuchs_overdrive_supreme_50";

    // Unfiltered Audio
    thumbnailFilenames["unfiltered audio dent 2"] = "unfiltered_dent_2";
    thumbnailFilenames["unfiltered audio silo"] = "unfiltered_silo";
    thumbnailFilenames["unfiltered audio indent 2"] = "unfiltered_indent_2";
    thumbnailFilenames["unfiltered audio tails"] = "unfiltered_tails";
    thumbnailFilenames["unfiltered audio sandman pro"] = "unfiltered_sandman_pro";
    thumbnailFilenames["unfiltered audio sandman"] = "unfiltered_sandman";
    thumbnailFilenames["unfiltered audio specops"] = "unfiltered_specops";
    thumbnailFilenames["unfiltered audio fault"] = "unfiltered_fault";
    thumbnailFilenames["unfiltered audio lion"] = "unfiltered_lion";
    thumbnailFilenames["unfiltered audio zip"] = "unfiltered_zip";
    thumbnailFilenames["unfiltered audio byome"] = "unfiltered_byome";
    thumbnailFilenames["unfiltered audio g8"] = "unfiltered_g8";
    thumbnailFilenames["unfiltered audio battalion"] = "unfiltered_battalion";
    thumbnailFilenames["unfiltered audio instant delay"] = "unfiltered_instant_delay";
    thumbnailFilenames["unfiltered audio lo-fi-af"] = "unfiltered_lofiaf";
    thumbnailFilenames["unfiltered audio bass-mint"] = "unfiltered_bass_mint";
    thumbnailFilenames["unfiltered audio needlepoint"] = "mixland_needlepoint";
    thumbnailFilenames["unfiltered audio triad"] = "karanyi_triad";

    // Swivel Audio
    thumbnailFilenames["swivel audio spread"] = "swivel_spread";
    thumbnailFilenames["swivel audio the sauce"] = "swivel_the_sauce";
    thumbnailFilenames["swivel audio knocktonal"] = "swivel_knocktonal";
    thumbnailFilenames["swivel audio click boom"] = "swivel_click_boom";
    thumbnailFilenames["swivel audio bde"] = "swivel_bde";
    thumbnailFilenames["swivel audio hitstrip"] = "swivel_hitstrip";

    // Bettermaker
    thumbnailFilenames["bettermaker mastering compressor"] = "bettermaker_mastering_compressor";
    thumbnailFilenames["bettermaker bus compressor"] = "bettermaker_bus_compressor";
    thumbnailFilenames["bettermaker c502v"] = "bettermaker_c502v";
    thumbnailFilenames["bettermaker bm60"] = "bettermaker_bm60";
    thumbnailFilenames["bettermaker eq232d"] = "bettermaker_eq232d";
    thumbnailFilenames["bettermaker passive equalizer"] = "bettermaker_passive_equalizer";

    // Knif Audio
    thumbnailFilenames["knif audio soma"] = "knif_soma";
    thumbnailFilenames["knif audio knifonium"] = "knif_knifonium";

    // Noveltech
    thumbnailFilenames["noveltech character"] = "noveltech_character";
    thumbnailFilenames["noveltech vocal enhancer"] = "noveltech_vocal_enhancer";

    // fiedler audio
    thumbnailFilenames["fiedler audio stage"] = "fiedler_stage";
    thumbnailFilenames["fiedler audio spatial creator"] = "fiedler_spatial_creator";
    thumbnailFilenames["fiedler audio splat"] = "fiedler_splat";

    // DS Audio
    thumbnailFilenames["ds audio tantra 2"] = "ds_audio_tantra_2";
    thumbnailFilenames["ds audio thorn"] = "ds_audio_thorn";

    // Purple Audio
    thumbnailFilenames["purple audio mc77"] = "purple_audio_mc77";
    thumbnailFilenames["purple audio mc 77"] = "purple_audio_mc77";

    // Pro Audio DSP
    thumbnailFilenames["pro audio dsp dsm v3"] = "pro_audio_dsp_dsm_v3";

    // Looptrotter
    thumbnailFilenames["looptrotter sa2rate 2"] = "looptrotter_sa2rate_2";

    // Dangerous Music
    thumbnailFilenames["dangerous music bax eq"] = "dangerous_bax_eq";

    // A/DA
    thumbnailFilenames["a/da flanger"] = "ada_flanger";
    thumbnailFilenames["a/da std-1 stereo tapped delay"] = "ada_std1";

    // Chandler Limited
    thumbnailFilenames["chandler limited gav19t"] = "chandler_gav19t";

    // Louder Than Liftoff
    thumbnailFilenames["louder than liftoff silver bullet mk2"] = "louder_than_liftoff_silver_bullet";

    // TOMO Audiolabs
    thumbnailFilenames["tomo audiolabs lisa"] = "tomo_lisa";

    // Harris Doyle
    thumbnailFilenames["harris doyle natalus dsceq"] = "harris_doyle_natalus";

    // Mixland
    thumbnailFilenames["mixland the oven"] = "mixland_the_oven";
    thumbnailFilenames["mixland needlepoint"] = "mixland_needlepoint";

    // Acme Audio
    thumbnailFilenames["acme audio opticom xla-3"] = "acme_opticom_xla3";

    // Karanyi Sounds
    thumbnailFilenames["karanyi sounds triad"] = "karanyi_triad";
    thumbnailFilenames["karanyi sounds wavesurfer"] = "karanyi_wavesurfer";

    // HEARS
    thumbnailFilenames["hears perfection"] = "hears_perfection";

    // Kiive Audio
    thumbnailFilenames["kiive tape face"] = "kiive_tape_face";
    thumbnailFilenames["kiive xtcomp"] = "kiive_xtcomp";

    // Mixland
    thumbnailFilenames["mixland vac attack"] = "mixland_vac_attack";

    // Cut Classic
    thumbnailFilenames["cut classic high flyer"] = "cut_classic_high_flyer";

    // THX
    thumbnailFilenames["thx spatial creator"] = "thx_spatial_creator";

    // LTL (Louder Than Liftoff)
    thumbnailFilenames["ltl chop shop eq"] = "ltl_chop_shop";

    // Maor Appelbaum & Hendyamps
    thumbnailFilenames["maor appelbaum hawkeye"] = "maor_hawkeye";

    // Cut Classic
    thumbnailFilenames["cut classic high flyer"] = "cut_classic_high_flyer";
}

PluginImageCache::~PluginImageCache()
{
    shouldExit = true;
    wakeUp.signal();
    stopThread(2000);
}

PluginImageCache& PluginImageCache::getInstance()
{
    static PluginImageCache instance;
    return instance;
}

void PluginImageCache::initializeImageUrls()
{
    // Plugin name -> Image URL mapping
    // URLs are from Plugin Alliance's Shopify CDN
    const juce::String baseUrl = "https://www.plugin-alliance.com/cdn/shop/files/";

    // NEOLD
    imageUrls["neold rz062"] = baseUrl + "NEOLD_RZ062_GUI.jpg";
    imageUrls["neold v76u73"] = baseUrl + "V76U73_GUI.png";
    imageUrls["neold warble"] = baseUrl + "WARBLE_GUI.png";
    imageUrls["neold big al"] = baseUrl + "BIG_AL_GUI.png";
    imageUrls["neold u17"] = baseUrl + "U17_GUI.png";
    imageUrls["neold u2a"] = baseUrl + "U2A_GUI.png";
    imageUrls["neold wunderlich"] = baseUrl + "WUNDERLICH_GUI.png";
    imageUrls["neold oldtimer"] = baseUrl + "OLDTIMER_GUI.png";

    // Shadow Hills
    imageUrls["shadow hills mastering compressor"] = baseUrl + "productimage-300733_8559dc19-253d-4547-a89c-f15db5e971ac.png";
    imageUrls["shadow hills mastering compressor class a"] = baseUrl + "productimage-300477_e8983653-ad69-4077-b345-b55cc0c50e99.png";
    imageUrls["shadow hills optomax"] = baseUrl + "productimage-301332.jpg";

    // SPL
    imageUrls["spl vitalizer mk3-t"] = baseUrl + "productimage-301205.png";
    imageUrls["spl big"] = baseUrl + "productimage-301157_b5d6244c-127c-4e2c-8a42-d30e5886b545.png";
    imageUrls["spl machine head"] = baseUrl + "productimage-301150_00d7f9ee-0334-4ad6-9ae3-24c4567bf255.png";
    imageUrls["spl twintube"] = baseUrl + "productimage-300025_b2bd856a-47b9-433c-b622-31dd8c2d61a0.png";
    imageUrls["spl de-esser collection"] = baseUrl + "productimage-300027_ae01dbce-8b31-49cf-b644-e973cca25fa1.png";
    imageUrls["spl transient designer plus"] = baseUrl + "productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png";
    imageUrls["spl de-verb plus"] = baseUrl + "productimage-300305_8082d009-6270-4264-84f8-5801a3dad97e.png";
    imageUrls["spl mo-verb plus"] = baseUrl + "productimage-300307_b8dc9794-488c-4ffc-af14-deaa77633c9e.png";
    imageUrls["spl attacker plus"] = baseUrl + "productimage-300303_cf082f7d-27b1-4317-874f-3732caec074d.png";
    imageUrls["spl iron"] = baseUrl + "productimage-300386_5a609eb0-4eb3-4780-82b2-2bc2077c677b.png";
    imageUrls["spl passeq"] = baseUrl + "productimage-300014_41e6334f-ea81-4115-bcb2-ce021a984aae.png";
    imageUrls["spl drumxchanger"] = baseUrl + "productimage-300020_b30bc9e9-b50a-4559-9e06-353e837f36fd.png";
    imageUrls["spl eq ranger plus"] = baseUrl + "productimage-300186_672ca1e9-1e63-43ec-9c48-8a7cdb66b8d0.png";

    // elysia
    imageUrls["elysia alpha compressor"] = baseUrl + "productimage-301253.png";
    imageUrls["elysia alpha compressor v2"] = baseUrl + "productimage-301253.png";
    imageUrls["elysia museq"] = baseUrl + "productimage-300055_aa4bc727-7c4a-4c2c-839e-af90427a44eb.png";
    imageUrls["elysia karacter"] = baseUrl + "productimage-300256_1b500d94-b2ab-4d3d-8537-32ac61b673c9.png";
    imageUrls["elysia mpressor"] = baseUrl + "productimage-300018_1635b21e-7b69-439c-ba1b-37ce6236bbfc.png";
    imageUrls["elysia nvelope"] = baseUrl + "productimage-300145_9163302c-3621-412f-b57b-86b466130f7a.png";

    // Maag Audio
    imageUrls["maag audio eq4 ms"] = baseUrl + "productimage-301107_7eb64f8c-bf0d-4ee7-9460-10e01a67a783.png";
    imageUrls["maag audio eq4"] = baseUrl + "productimage-300035_428da437-d6de-412d-bbb1-9f804df6f30f.png";
    imageUrls["maag audio eq2"] = baseUrl + "productimage-300117_4ea7b383-e026-40eb-ad25-72287bdcd42e.png";
    imageUrls["maag audio magnum-k"] = baseUrl + "productimage-300396_1fab8194-5ca3-4b6d-99b1-0e53a025bcb9.png";

    // ADPTR AUDIO
    imageUrls["adptr audio metric ab"] = baseUrl + "productimage-300370_51fdb784-eaec-48b3-8609-4fccc7196d68.png";
    imageUrls["adptr audio streamliner"] = baseUrl + "productimage-300537_a0567c85-b2b2-4bd1-9f46-8f546e962030.png";
    imageUrls["adptr audio sculpt"] = baseUrl + "productimage-300570_a644e64a-2d6e-4492-a71a-2139f7043502.png";
    imageUrls["adptr audio utopia"] = baseUrl + "productimage-301236.png";

    // Three-Body Technology
    imageUrls["kirchhoff-eq"] = baseUrl + "productimage-300781_6b333574-9e0f-4247-9d6a-81a75d11eadd.png";
    imageUrls["cenozoix compressor"] = baseUrl + "productimage-300982_3397fcd0-2e7b-4b96-b08b-5d82fa4c3528.png";
    imageUrls["trinity shaper"] = baseUrl + "productimage-301099_9368cf32-6c6e-4541-ad84-f96fb8bcddbb.png";

    // Black Box Analog Design
    imageUrls["black box analog design hg-2ms"] = baseUrl + "productimage-300541_892dac09-0f4a-4c59-ac02-2419b76d461c.png";
    imageUrls["black box analog design hg-2"] = baseUrl + "productimage-300259_1e8913ea-66da-4ac3-aee0-171e176dfa13.png";
    imageUrls["black box analog design hg-q"] = baseUrl + "productimage-300902_7f6334fb-d403-47bc-baae-18a9cd266cf3.png";

    // Brainworx
    imageUrls["bx_xl v3"] = baseUrl + "productimage-300918_98828b43-9284-415c-bb93-6f0c88322ce4.png";
    imageUrls["bx_console ssl 4000 e"] = baseUrl + "productimage-300373_f5942771-0897-4d7f-8955-7795f96295a3.png";
    imageUrls["bx_console ssl 4000 g"] = baseUrl + "productimage-300374_b2b44f03-8e78-4736-a7b6-ef8820665d5b.png";
    imageUrls["bx_console ssl 9000 j"] = baseUrl + "productimage-300478_3bcb16b8-3645-45f3-9b99-4d738a5a344e.png";
    imageUrls["bx_console amek 9099"] = baseUrl + "productimage-300556_e7ec008e-826c-4aaf-86d3-fa8cc6b0ab20.png";
    imageUrls["bx_console amek 200"] = baseUrl + "productimage-300865_2bacbf1b-2cdf-4ab8-b1c6-59d6bc227cc4.png";
    imageUrls["bx_console focusrite sc"] = baseUrl + "productimage-300402_e0b1d7b5-7b9b-466c-a224-1547f722b0f0.png";
    imageUrls["bx_console n"] = baseUrl + "productimage-300345_47021cba-5c15-4974-aa89-ff492a889fed.png";
    imageUrls["bx_digital v3"] = baseUrl + "productimage-300214_d6cd321d-80bd-4c41-bd6a-4b05198f3e30.png";
    imageUrls["bx_pulsar"] = baseUrl + "productimage-301279_2.png";
    imageUrls["bx_refinement v3"] = baseUrl + "productimage-301160.png";
    imageUrls["bx_clipper"] = baseUrl + "productimage-300897_8836b232-ad58-4b7b-84ad-b3ecb5454842.png";
    imageUrls["bx_aura"] = baseUrl + "productimage-301029_e4a95235-3c07-4ddf-a316-956492d2217d.png";
    imageUrls["bx_masterdesk pro"] = baseUrl + "productimage-300899_7d13d505-a4ec-4fd8-ac5b-bee1432f5ddc.png";
    imageUrls["bx_masterdesk"] = baseUrl + "productimage-300383_a2601b0c-d04f-4feb-9a7c-5af3dbf5d472.png";
    imageUrls["bx_masterdesk true peak"] = baseUrl + "productimage-300643_9defaedc-3211-4098-970a-3985949b013f.png";
    imageUrls["bx_cleansweep pro"] = baseUrl + "productimage-300199_3640d2e9-1a04-4c7d-bc8e-6b03588f4b6b.png";
    imageUrls["bx_control v2"] = baseUrl + "productimage-300039_3f18bdee-2603-4bf6-902e-927155d0aad6.png";
    imageUrls["bx_delay 2500"] = baseUrl + "productimage-300340_a4f01894-db7b-4d8a-93f4-3ada49c34241.png";
    imageUrls["bx_rockergain100"] = baseUrl + "productimage-300464_722b950c-c750-41b2-b860-a90fdb759f0b.png";
    imageUrls["bx_subsynth"] = baseUrl + "productimage-300257_ba2617f8-37e4-45c9-881c-6dab16468e30.png";
    imageUrls["bx_roooms"] = baseUrl + "productimage-300218_b3b1d5e1-dcb0-4b24-a58a-3db127e0e259.png";
    imageUrls["bx_oberhausen"] = baseUrl + "productimage-300404_8690b6b0-99e3-4490-91e0-4dbb9fd154ca.png";
    imageUrls["bx_paneq"] = baseUrl + "productimage-300195_d89137fd-0dc4-467f-a63f-0bf16a73f309.png";
    imageUrls["bx_dyneq v2"] = baseUrl + "productimage-300008_23571076-2caa-4b69-809a-1d234d32eb18.png";
    imageUrls["bx_megadual"] = baseUrl + "productimage-300160_cf331a7a-0d2e-4d93-a0e8-ca026d93f930.png";
    imageUrls["bx_opto"] = baseUrl + "productimage-300149_0a8c4324-5cc3-45e3-b62e-9bea84ff8323.png";
    imageUrls["bx_townhouse buss compressor"] = baseUrl + "productimage-300365_671a1cf2-d3e3-4a18-a54a-0fe613fbd987.png";
    imageUrls["bx_townhouse"] = baseUrl + "productimage-300365_671a1cf2-d3e3-4a18-a54a-0fe613fbd987.png";
    imageUrls["bx_2098 eq"] = baseUrl + "productimage-300359_322c1bfe-9086-4af3-8fa9-ee42b6149d81.png";
    imageUrls["bx_saturator v2"] = baseUrl + "productimage-300129_803f3461-6ee8-423c-840c-3569bca891c0.png";
    imageUrls["bx_hybrid v2"] = baseUrl + "productimage-300097_74b90f56-7fc4-4c94-86f1-cdbb4ad2d724.png";
    imageUrls["bx_stereomaker"] = baseUrl + "productimage-300079_46914425-b10e-404b-b628-f16b93987535.png";
    imageUrls["bx_limiter"] = baseUrl + "productimage-300085_6cee96b9-0f1f-4499-9d6d-81bea3ca9da3.png";
    imageUrls["bx_limiter true peak"] = baseUrl + "productimage-300552_1d635dc7-5e4a-4717-8b41-3706351c5683.png";
    imageUrls["bx_bassdude"] = baseUrl + "productimage-300170_153cebea-6b47-432d-90b6-f4623bcd49e3.png";
    imageUrls["bx_rockrack v3"] = baseUrl + "productimage-300244_20a2ee7e-c696-432e-ae2f-641cd41b7723.png";
    imageUrls["bx_crispytuner"] = baseUrl + "productimage-300564_0f72ee8a-9c4f-43b7-9916-c4e1feca8f07.png";
    imageUrls["bx_crispyscale"] = baseUrl + "productimage-300564_0f72ee8a-9c4f-43b7-9916-c4e1feca8f07.png";
    imageUrls["bx_glue"] = baseUrl + "productimage-300988_dbbe8b26-3676-473a-8766-8a51308d591f.png";
    imageUrls["bx_enhancer"] = baseUrl + "productimage-300927_483a3bdf-0d3a-4970-a5b7-d0b6b37ba07c.png";
    imageUrls["bx_boom v3"] = baseUrl + "productimage-301127_e9ace067-330a-4797-9b22-85b8cb2bf870.png";

    // Vertigo
    imageUrls["vertigo vss-2"] = baseUrl + "productimage-301211_c9e80b87-6931-49a0-a3f3-c4bf0558adbc.png";
    imageUrls["vertigo vsc-2"] = baseUrl + "productimage-300016_b2d9cdc4-0a57-4ea9-ac82-c9be994d59a3.png";
    imageUrls["vertigo vsm-3"] = baseUrl + "productimage-300100_481634f1-902d-46ca-9da7-bbe7f2b83313.png";

    // HUM Audio Devices
    imageUrls["hum audio devices laal"] = baseUrl + "productimage-301243_6f932fc9-447c-45be-86e4-699151db7721.png";
    imageUrls["laal"] = baseUrl + "productimage-301243_6f932fc9-447c-45be-86e4-699151db7721.png";

    // Millennia
    imageUrls["millennia nseq-2"] = baseUrl + "productimage-300033_a9be6950-3a74-433a-bda2-fd86035e4ef3.png";

    // Lindell Audio
    imageUrls["lindell audio 80 series"] = baseUrl + "productimage-300475_de30a79f-c507-4963-9d9f-b09b50e2b91b.png";
    imageUrls["lindell audio eq825"] = baseUrl + "productimage-301272.jpg";
    imageUrls["lindell audio 69 series"] = baseUrl + "productimage-300738_552e118f-280c-45c0-bb35-df6d7492b686.png";
    imageUrls["lindell audio 50 series"] = baseUrl + "productimage-300543_18e03db2-391e-4555-ba69-376b1cc1842a.png";
    imageUrls["lindell audio mbc"] = baseUrl + "productimage-300737_d0202dc3-2fc5-432e-b972-f3b6edc13dbd.png";
    imageUrls["lindell audio pq"] = baseUrl + "productimage-300682_e9888535-781e-4df8-ad82-419b0fddb790.png";
    imageUrls["lindell audio sbc"] = baseUrl + "productimage-300627_3efa1f27-cc48-46d3-a800-a417c51b1e5c.png";
    imageUrls["lindell audio 354e"] = baseUrl + "productimage-300289_fadcef28-689f-493c-b1ae-a695928bf0a1.png";
    imageUrls["lindell audio 254e"] = baseUrl + "productimage-300150_4690a068-d00e-43e6-acf0-2f61f40d890e.png";
    imageUrls["lindell audio 902 de-esser"] = baseUrl + "productimage-300626_a2edb61f-a1c5-400e-96cb-656bbbda8fa9.png";
    imageUrls["lindell audio 7x-500"] = baseUrl + "productimage-300178_8bb5104f-8127-409a-89ec-25840ed22e19.png";
    imageUrls["lindell audio 6x-500"] = baseUrl + "productimage-300177_c6d72330-7dee-4c62-8c18-e10eb82e96ee.png";
    imageUrls["lindell audio pex-500"] = baseUrl + "productimage-300179_fa86a3d6-3911-480f-9f7d-85737184eaca.png";
    imageUrls["lindell audio channelx"] = baseUrl + "productimage-300175_b9f47d8b-15a3-4c65-9299-4baa15ee39cf.png";

    // AMEK
    imageUrls["amek eq 200"] = baseUrl + "productimage-300489_6767f358-fdda-4c8c-a54e-da06e303f0ef.png";
    imageUrls["amek eq 250"] = baseUrl + "productimage-300661_afa25549-2347-4ed7-9321-d48f261fc6ee.png";
    imageUrls["amek mastering compressor"] = baseUrl + "productimage-300733_8559dc19-253d-4547-a89c-f15db5e971ac.png";

    // Ampeg
    imageUrls["ampeg b-15n"] = baseUrl + "productimage-300233_b83aba8c-07b2-4ef5-90dd-472408ab5951.png";
    imageUrls["ampeg svt-vr"] = baseUrl + "productimage-300438_138d8e73-8761-4454-8704-30db1d9bd58f.png";
    imageUrls["ampeg svt-vr classic"] = baseUrl + "productimage-300439_cf6e9c57-eddc-40b0-af64-192174df03d0.png";
    imageUrls["ampeg svt-3pro"] = baseUrl + "productimage-300131_837f40bc-5a6c-43bc-a8df-806e318a7849.png";
    imageUrls["ampeg v-4b"] = baseUrl + "productimage-300423_1343a52c-eb70-4d7a-bdc9-3426cedee2e5.png";

    // Diezel
    imageUrls["diezel herbert"] = baseUrl + "productimage-300437_5daea3d8-36ba-490a-8a3b-e6e89b7d28a0.png";
    imageUrls["diezel vh4"] = baseUrl + "productimage-300434_bfdaa187-c253-4698-9ed7-c811a754c5ea.png";

    // Friedman
    imageUrls["friedman be-100"] = baseUrl + "productimage-300435_2754fb79-473f-4297-9053-282544fea9df.png";
    imageUrls["friedman buxom betty"] = baseUrl + "productimage-300354_3f55477d-a868-445a-8f27-0623149c67c1.png";
    imageUrls["friedman ds-40"] = baseUrl + "productimage-300436_8afc1d03-76bc-4a98-8f04-3d24ec7e327e.png";

    // ENGL
    imageUrls["engl savage 120"] = baseUrl + "productimage-300483_7726526f-00a8-4ebc-b38c-b344d7f42349.png";
    imageUrls["engl e765 rt"] = baseUrl + "productimage-300148_cdb32674-3646-451d-8b91-d5a793b68296.png";
    imageUrls["engl e646 vs"] = baseUrl + "productimage-300147_f2063d9f-b96b-4573-8e7a-2d30b50c3e05.png";

    // Suhr
    imageUrls["suhr pt100"] = baseUrl + "productimage-300557_5b344abb-f597-41e9-ac6d-bd3885b474fc.png";
    imageUrls["suhr se100"] = baseUrl + "productimage-300558_7a885e73-7f6b-4a7c-b1ab-3b8bf2413932.png";

    // Gallien-Krueger
    imageUrls["gallien-krueger 800rb"] = baseUrl + "productimage-300351_9869025a-e5c3-4f1a-bb8c-8c5e7c1c1791.png";

    // Fuchs
    imageUrls["fuchs train ii"] = baseUrl + "productimage-300486_5bd98aea-95ec-42eb-8701-c60accecc3cf.png";
    imageUrls["fuchs overdrive supreme 50"] = baseUrl + "productimage-300485_2c642e68-5464-414c-a429-dc89c1ef8300.png";

    // Unfiltered Audio
    imageUrls["unfiltered audio dent 2"] = baseUrl + "productimage-300342_49bc2c9c-005d-4e8a-a7ae-f2b85de716c1.png";
    imageUrls["unfiltered audio silo"] = baseUrl + "productimage-300512_2269d8cb-2801-4e4d-915c-7ad722d6d4a8.png";
    imageUrls["unfiltered audio indent 2"] = baseUrl + "productimage-300343_766af22f-b8ac-43e8-b214-e6c3f008677a.png";
    imageUrls["unfiltered audio instant delay"] = baseUrl + "productimage-300316_ce1f07a0-722d-4d3a-a1bf-b43231b62808.png";
    imageUrls["unfiltered audio tails"] = baseUrl + "productimage-300493_90634ade-c965-41fd-a5fe-ed40d14cec59.png";
    imageUrls["unfiltered audio bass-mint"] = baseUrl + "productimage-300490_3df7645c-3a98-4c49-93be-3d4a9700d3e5.png";
    imageUrls["unfiltered audio lo-fi-af"] = baseUrl + "productimage-300492_3815c462-512d-438e-a1f7-9796ef5e7296.png";
    imageUrls["unfiltered audio sandman pro"] = baseUrl + "productimage-300264_331f5d02-0ec3-4e58-9218-1ffbbbf2a9f2.png";
    imageUrls["unfiltered audio sandman"] = baseUrl + "productimage-300184_2882f84c-ac87-4aaa-aaaa-965d00bfe8b9.png";
    imageUrls["unfiltered audio specops"] = baseUrl + "productimage-300263_cda3010b-a419-4289-8245-3481b6409d10.png";
    imageUrls["unfiltered audio fault"] = baseUrl + "productimage-300235_426efe25-abe9-4c9d-95d2-542c264e1dfa.png";
    imageUrls["unfiltered audio lion"] = baseUrl + "productimage-300413_87e9ac60-f714-4a6d-9e6a-7e6cd43a070f.png";
    imageUrls["unfiltered audio zip"] = baseUrl + "productimage-300357_6d1acfe7-c862-4f57-aeeb-d9fe37986420.png";
    imageUrls["unfiltered audio byome"] = baseUrl + "productimage-300378_43bef938-0ea5-4f09-ad46-0b34c751df83.png";
    imageUrls["unfiltered audio g8"] = baseUrl + "productimage-300183_d5aedd52-8194-49bd-b280-24160da8aed4.png";

    // Swivel Audio
    imageUrls["swivel audio spread"] = baseUrl + "productimage-301296.png";
    imageUrls["swivel audio the sauce"] = baseUrl + "productimage-301290.png";
    imageUrls["swivel audio knocktonal"] = baseUrl + "productimage-301298.png";
    imageUrls["swivel audio click boom"] = baseUrl + "productimage-301299.png";
    imageUrls["swivel audio bde"] = baseUrl + "productimage-301297.png";
    imageUrls["swivel audio hitstrip"] = baseUrl + "productimage-301300.png";

    // Bettermaker
    imageUrls["bettermaker mastering compressor"] = baseUrl + "productimage-301237.png";
    imageUrls["bettermaker bus compressor"] = baseUrl + "productimage-300973_b69e8739-4394-49f1-bb2d-c4df85dd2bcb.png";
    imageUrls["bettermaker c502v"] = baseUrl + "productimage-301146_2bdf41cf-d9d8-4294-8d8a-270560c4cc74.png";
    imageUrls["bettermaker bm60"] = baseUrl + "productimage-301030_a53ec7b3-bdb8-4f9f-847c-c4ae1c766f78.png";
    imageUrls["bettermaker eq232d"] = baseUrl + "productimage-300421_fef58d06-aa5f-4482-8b6a-58c56f82a79a.png";
    imageUrls["bettermaker passive equalizer"] = baseUrl + "productimage-301098.png";

    // Knif Audio
    imageUrls["knif audio soma"] = baseUrl + "productimage-300517_d93d3d4e-3d3c-42e4-9694-c3bea8252618.png";
    imageUrls["knif audio knifonium"] = baseUrl + "productimage-300471_d66727a9-586b-47d0-97ed-9f176c296269.png";

    // Noveltech
    imageUrls["noveltech character"] = baseUrl + "productimage-300068_1e2c9ec6-8b04-49e6-ac20-bfbc963d0481.png";
    imageUrls["noveltech vocal enhancer"] = baseUrl + "productimage-300088_7acfec5d-912a-48ca-9ebd-fe07e741e6e1.png";

    // fiedler audio
    imageUrls["fiedler audio stage"] = baseUrl + "productimage-300309_43e9ff7b-b505-4425-8a9d-c4b6954b2b06.png";
    imageUrls["fiedler audio spatial creator"] = baseUrl + "productimage-300904_d1c9b86a-5c99-4a62-b809-5790a753b57b.png";

    // DS Audio
    imageUrls["ds audio tantra 2"] = baseUrl + "productimage-300554_8ace881a-39b6-471d-9a28-fe0cf0673018.png";
    imageUrls["ds audio thorn"] = baseUrl + "productimage-300401_98febeee-bda8-4fe9-b1c6-ba8fa2d7eff9.png";

    // Purple Audio
    imageUrls["purple audio mc77"] = baseUrl + "productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png";
    imageUrls["purple audio mc 77"] = baseUrl + "productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png";

    // Pro Audio DSP
    imageUrls["pro audio dsp dsm v3"] = baseUrl + "productimage-300403_9bb5d6c3-5d94-46d0-86c4-f8c86bd9a7c3.png";

    // Looptrotter
    imageUrls["looptrotter sa2rate 2"] = baseUrl + "productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png";

    // Dangerous Music
    imageUrls["dangerous music bax eq"] = baseUrl + "productimage-300095_e8339764-5fb2-4554-b4d2-14fee7d1b140.png";

    // A/DA
    imageUrls["a/da flanger"] = baseUrl + "productimage-300356_b75930af-e197-461f-a776-d0b40f6fbfd7.png";
    imageUrls["a/da std-1 stereo tapped delay"] = baseUrl + "productimage-300258_e4416d1c-8f75-4683-8195-cc03447e59a0.png";

    // Chandler Limited
    imageUrls["chandler limited gav19t"] = baseUrl + "productimage-300114_a26c0820-3eb1-42f1-b72c-81005a988f27.png";

    // Kiive Audio
    imageUrls["kiive audio xtcomp"] = baseUrl + "productimage-300998.png";

    // Louder Than Liftoff
    imageUrls["louder than liftoff silver bullet mk2"] = baseUrl + "productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png";

    // TOMO Audiolabs
    imageUrls["tomo audiolabs lisa"] = baseUrl + "productimage-300635_b22c3561-6e15-4c4d-ad52-4ac96b0e9d92.png";

    // Harris Doyle
    imageUrls["harris doyle natalus dsceq"] = baseUrl + "productimage-300852_e65cdbad-a648-40b8-88e6-4fb77bb3a976.png";

    // Mixland
    imageUrls["mixland the oven"] = baseUrl + "productimage-300653_a16226c9-f5b9-4820-92c2-4240b4adfa66.png";
    imageUrls["mixland needlepoint"] = baseUrl + "productimage-300663_e9b251cc-820d-41e8-86e9-f487dd48e022.png";

    // Acme Audio
    imageUrls["acme audio opticom xla-3"] = baseUrl + "productimage-300211_137be455-e2d4-4035-9eee-f1ef6d7a3a15.png";

    // SSL (Solid State Logic)
    imageUrls["ssl e-channel"] = baseUrl + "productimage-300373_f5942771-0897-4d7f-8955-7795f96295a3.png";

    // THX
    imageUrls["thx aaa"] = baseUrl + "";

    // Karanyi Sounds
    imageUrls["karanyi sounds triad"] = baseUrl + "productimage-300393_2300346d-45cc-4bd1-997d-10b1946db4e8.png";

    // HEARS
    imageUrls["hears perfection"] = baseUrl + "productimage-301331.png";

    // Maor Appelbaum & Hendyamps
    imageUrls["maor appelbaum hawkeye"] = baseUrl + "productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png";

    // Cut Classic
    imageUrls["cut classic high flyer"] = baseUrl + "productimage-301210.png";

    // Other
    imageUrls["phil's cascade"] = baseUrl + "productimage-300369_a8076339-2084-4197-a944-dbbf15f01efd.png";
    imageUrls["battalion"] = baseUrl + "productimage-301002_746463f1-14eb-4f80-83c3-5e524df6ffb4.png";
    imageUrls["eq232d"] = baseUrl + "productimage-300421_fef58d06-aa5f-4482-8b6a-58c56f82a79a.png";
    imageUrls["tcl-2"] = baseUrl + "productimage-300143_3c0a78f2-31be-436b-ab39-a877c73d8694.png";
    imageUrls["high flyer"] = baseUrl + "productimage-301210.png";
    imageUrls["splat"] = baseUrl + "productimage-301101_81645304-1805-44fb-86a9-f0a6f07eaa01.png";
    imageUrls["c502v"] = baseUrl + "productimage-301146_2bdf41cf-d9d8-4294-8d8a-270560c4cc74.png";
    imageUrls["mu-66"] = baseUrl + "productimage-301012_2e708038-ee2b-4bc1-97db-a55966cf2523.png";
    imageUrls["bm60"] = baseUrl + "productimage-301030_a53ec7b3-bdb8-4f9f-847c-c4ae1c766f78.png";
    imageUrls["hype"] = baseUrl + "productimage-300999_56d6bbd4-8d7d-408d-845b-51ae21f9a76c.png";
    imageUrls["vac attack"] = baseUrl + "productimage-300928_d5c2191a-2e0f-4cec-8c0d-552d33722598.png";
    imageUrls["wavesurfer"] = baseUrl + "productimage-301155_0af05e64-9d77-47bb-a38f-51bca26c4045.png";
    imageUrls["tape face"] = baseUrl + "productimage-300883_ea7d242f-aca6-4785-8ee4-155cbfbd9fd2.png";
    imageUrls["te-100"] = baseUrl + "productimage-300236_5566d6a5-698c-439c-82d1-35e8137524b4.png";

    // Short name aliases for better matching
    imageUrls["lion"] = baseUrl + "productimage-300413_87e9ac60-f714-4a6d-9e6a-7e6cd43a070f.png";
    imageUrls["knifonium"] = baseUrl + "productimage-300471_d66727a9-586b-47d0-97ed-9f176c296269.png";
    imageUrls["thorn"] = baseUrl + "productimage-300401_98febeee-bda8-4fe9-b1c6-ba8fa2d7eff9.png";
    imageUrls["oberhausen"] = baseUrl + "productimage-300404_8690b6b0-99e3-4490-91e0-4dbb9fd154ca.png";
    imageUrls["silo"] = baseUrl + "productimage-300512_2269d8cb-2801-4e4d-915c-7ad722d6d4a8.png";
    imageUrls["byome"] = baseUrl + "productimage-300378_43bef938-0ea5-4f09-ad46-0b34c751df83.png";
    imageUrls["g8"] = baseUrl + "productimage-300183_d5aedd52-8194-49bd-b280-24160da8aed4.png";
    imageUrls["tails"] = baseUrl + "productimage-300493_90634ade-c965-41fd-a5fe-ed40d14cec59.png";
    imageUrls["sandman"] = baseUrl + "productimage-300184_2882f84c-ac87-4aaa-aaaa-965d00bfe8b9.png";
    imageUrls["specops"] = baseUrl + "productimage-300263_cda3010b-a419-4289-8245-3481b6409d10.png";
    imageUrls["fault"] = baseUrl + "productimage-300235_426efe25-abe9-4c9d-95d2-542c264e1dfa.png";
    imageUrls["zip"] = baseUrl + "productimage-300357_6d1acfe7-c862-4f57-aeeb-d9fe37986420.png";
    imageUrls["indent 2"] = baseUrl + "productimage-300343_766af22f-b8ac-43e8-b214-e6c3f008677a.png";
    imageUrls["dent 2"] = baseUrl + "productimage-300342_49bc2c9c-005d-4e8a-a7ae-f2b85de716c1.png";
    imageUrls["instant delay"] = baseUrl + "productimage-300316_ce1f07a0-722d-4d3a-a1bf-b43231b62808.png";
    imageUrls["bass-mint"] = baseUrl + "productimage-300490_3df7645c-3a98-4c49-93be-3d4a9700d3e5.png";
    imageUrls["lo-fi-af"] = baseUrl + "productimage-300492_3815c462-512d-438e-a1f7-9796ef5e7296.png";
    imageUrls["needlepoint"] = baseUrl + "productimage-300663_e9b251cc-820d-41e8-86e9-f487dd48e022.png";

    // More Brainworx short names
    imageUrls["masterdesk"] = baseUrl + "productimage-300383_a2601b0c-d04f-4feb-9a7c-5af3dbf5d472.png";
    imageUrls["masterdesk pro"] = baseUrl + "productimage-300899_7d13d505-a4ec-4fd8-ac5b-bee1432f5ddc.png";
    imageUrls["townhouse"] = baseUrl + "productimage-300365_671a1cf2-d3e3-4a18-a54a-0fe613fbd987.png";
    imageUrls["digital v3"] = baseUrl + "productimage-300214_d6cd321d-80bd-4c41-bd6a-4b05198f3e30.png";
    imageUrls["rooms"] = baseUrl + "productimage-300218_b3b1d5e1-dcb0-4b24-a58a-3db127e0e259.png";
    imageUrls["roooms"] = baseUrl + "productimage-300218_b3b1d5e1-dcb0-4b24-a58a-3db127e0e259.png";
    imageUrls["aura"] = baseUrl + "productimage-301029_e4a95235-3c07-4ddf-a316-956492d2217d.png";
    imageUrls["pulsar"] = baseUrl + "productimage-301279_2.png";
    imageUrls["clipper"] = baseUrl + "productimage-300897_8836b232-ad58-4b7b-84ad-b3ecb5454842.png";
    imageUrls["saturator v2"] = baseUrl + "productimage-300129_803f3461-6ee8-423c-840c-3569bca891c0.png";
    imageUrls["hybrid v2"] = baseUrl + "productimage-300097_74b90f56-7fc4-4c94-86f1-cdbb4ad2d724.png";
    imageUrls["opto"] = baseUrl + "productimage-300149_0a8c4324-5cc3-45e3-b62e-9bea84ff8323.png";
    imageUrls["dyneq v2"] = baseUrl + "productimage-300008_23571076-2caa-4b69-809a-1d234d32eb18.png";
    imageUrls["xl v2"] = baseUrl + "productimage-300918_98828b43-9284-415c-bb93-6f0c88322ce4.png";
    imageUrls["xl v3"] = baseUrl + "productimage-300918_98828b43-9284-415c-bb93-6f0c88322ce4.png";
    imageUrls["crispytuner"] = baseUrl + "productimage-300564_0f72ee8a-9c4f-43b7-9916-c4e1feca8f07.png";
    imageUrls["glue"] = baseUrl + "productimage-300988_dbbe8b26-3676-473a-8766-8a51308d591f.png";
    imageUrls["limiter true peak"] = baseUrl + "productimage-300552_1d635dc7-5e4a-4717-8b41-3706351c5683.png";
    imageUrls["limiter"] = baseUrl + "productimage-300085_6cee96b9-0f1f-4499-9d6d-81bea3ca9da3.png";
    imageUrls["boom"] = baseUrl + "productimage-301127_e9ace067-330a-4797-9b22-85b8cb2bf870.png";
    imageUrls["boom v3"] = baseUrl + "productimage-301127_e9ace067-330a-4797-9b22-85b8cb2bf870.png";
    imageUrls["control v2"] = baseUrl + "productimage-300039_3f18bdee-2603-4bf6-902e-927155d0aad6.png";
    imageUrls["delay 2500"] = baseUrl + "productimage-300340_a4f01894-db7b-4d8a-93f4-3ada49c34241.png";
    imageUrls["cleansweep pro"] = baseUrl + "productimage-300199_3640d2e9-1a04-4c7d-bc8e-6b03588f4b6b.png";
    imageUrls["stereomaker"] = baseUrl + "productimage-300079_46914425-b10e-404b-b628-f16b93987535.png";
    imageUrls["subsynth"] = baseUrl + "productimage-300257_ba2617f8-37e4-45c9-881c-6dab16468e30.png";
    imageUrls["paneq"] = baseUrl + "productimage-300195_d89137fd-0dc4-467f-a63f-0bf16a73f309.png";
    imageUrls["shredspread"] = baseUrl + "productimage-300201_8a82a31c-3b25-4a5e-b0c5-d6c5be0a7fb1.png";
    imageUrls["refinement"] = baseUrl + "productimage-301160.png";
    imageUrls["refinement v3"] = baseUrl + "productimage-301160.png";
    imageUrls["meter"] = baseUrl + "productimage-300066_cf4b5c96-4b4d-4c04-8aa7-9a57c5f5af7a.png";
    imageUrls["tuner"] = baseUrl + "productimage-300199_3640d2e9-1a04-4c7d-bc8e-6b03588f4b6b.png";
    imageUrls["solo"] = baseUrl + "productimage-300200_a0f5e7c1-0e45-4e6c-97e7-8aaa2c6be4d5.png";
    imageUrls["enhancer"] = baseUrl + "productimage-300927_483a3bdf-0d3a-4970-a5b7-d0b6b37ba07c.png";

    // Guitar/bass amp short names
    imageUrls["megadual"] = baseUrl + "productimage-300160_cf331a7a-0d2e-4d93-a0e8-ca026d93f930.png";
    imageUrls["megasingle"] = baseUrl + "productimage-300161_a82bfe24-b69c-4b8e-8ed8-c48dcca7c8b5.png";
    imageUrls["bassdude"] = baseUrl + "productimage-300170_153cebea-6b47-432d-90b6-f4623bcd49e3.png";
    imageUrls["rockrack v3"] = baseUrl + "productimage-300244_20a2ee7e-c696-432e-ae2f-641cd41b7723.png";
    imageUrls["rockergain100"] = baseUrl + "productimage-300464_722b950c-c750-41b2-b860-a90fdb759f0b.png";

    // Pedal short names
    imageUrls["greenscreamer"] = baseUrl + "productimage-300172_bb27f44e-bd5f-4f1b-b09c-63d91e4c68cd.png";
    imageUrls["bluechorus2"] = baseUrl + "productimage-300169_ae1fbff4-c4dc-4e67-bb66-e6b3e1e4f14b.png";
    imageUrls["blackdist2"] = baseUrl + "productimage-300168_91e0b0b2-39b7-4cff-b3c5-c8f3a7bea723.png";
    imageUrls["distorange"] = baseUrl + "productimage-300171_05bf7a66-2b37-4a3e-8c2d-19e13a22e83c.png";
    imageUrls["yellowdrive"] = baseUrl + "productimage-300174_b4c8c2a8-b7e2-4b3b-a8e2-5f0e8e9c7d12.png";
    imageUrls["metal2"] = baseUrl + "productimage-300173_8b0e9e0c-7e2b-4c0b-b0e0-8c7e5e8c8d45.png";

    // elysia short names
    imageUrls["alpha compressor"] = baseUrl + "productimage-301253.png";
    imageUrls["mpressor"] = baseUrl + "productimage-300018_1635b21e-7b69-439c-ba1b-37ce6236bbfc.png";
    imageUrls["museq"] = baseUrl + "productimage-300055_aa4bc727-7c4a-4c2c-839e-af90427a44eb.png";
    imageUrls["karacter"] = baseUrl + "productimage-300256_1b500d94-b2ab-4d3d-8537-32ac61b673c9.png";
    imageUrls["nvelope"] = baseUrl + "productimage-300145_9163302c-3621-412f-b57b-86b466130f7a.png";
    imageUrls["niveau filter"] = baseUrl + "productimage-300146_28c03de7-f9ca-42d6-8dc3-7cc60a8f2e54.png";

    // SPL short names
    imageUrls["iron"] = baseUrl + "productimage-300386_5a609eb0-4eb3-4780-82b2-2bc2077c677b.png";
    imageUrls["passeq"] = baseUrl + "productimage-300014_41e6334f-ea81-4115-bcb2-ce021a984aae.png";
    imageUrls["vitalizer"] = baseUrl + "productimage-301205.png";
    imageUrls["twintube"] = baseUrl + "productimage-300025_b2bd856a-47b9-433c-b622-31dd8c2d61a0.png";
    imageUrls["transient designer plus"] = baseUrl + "productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png";
    imageUrls["transient designer"] = baseUrl + "productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png";
    imageUrls["de-esser"] = baseUrl + "productimage-300027_ae01dbce-8b31-49cf-b644-e973cca25fa1.png";
    imageUrls["de-verb plus"] = baseUrl + "productimage-300305_8082d009-6270-4264-84f8-5801a3dad97e.png";
    imageUrls["mo-verb plus"] = baseUrl + "productimage-300307_b8dc9794-488c-4ffc-af14-deaa77633c9e.png";
    imageUrls["attacker plus"] = baseUrl + "productimage-300303_cf082f7d-27b1-4317-874f-3732caec074d.png";
    imageUrls["drumxchanger"] = baseUrl + "productimage-300020_b30bc9e9-b50a-4559-9e06-353e837f36fd.png";
    imageUrls["eq ranger plus"] = baseUrl + "productimage-300186_672ca1e9-1e63-43ec-9c48-8a7cdb66b8d0.png";
    imageUrls["machine head"] = baseUrl + "productimage-301150_00d7f9ee-0334-4ad6-9ae3-24c4567bf255.png";
    imageUrls["big"] = baseUrl + "productimage-301157_b5d6244c-127c-4e2c-8a42-d30e5886b545.png";
    imageUrls["hawkeye"] = baseUrl + "productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png";

    // Shadow Hills short names
    imageUrls["mastering compressor"] = baseUrl + "productimage-300733_8559dc19-253d-4547-a89c-f15db5e971ac.png";
    imageUrls["optomax"] = baseUrl + "productimage-301332.jpg";

    // NEOLD short names
    imageUrls["u2a"] = baseUrl + "U2A_GUI.png";
    imageUrls["u17"] = baseUrl + "U17_GUI.png";
    imageUrls["warble"] = baseUrl + "WARBLE_GUI.png";
    imageUrls["big al"] = baseUrl + "BIG_AL_GUI.png";
    imageUrls["v76u73"] = baseUrl + "V76U73_GUI.png";
    imageUrls["oldtimer"] = baseUrl + "OLDTIMER_GUI.png";
    imageUrls["wunderlich"] = baseUrl + "WUNDERLICH_GUI.png";
    imageUrls["rz062"] = baseUrl + "NEOLD_RZ062_GUI.jpg";

    // Vertigo short names
    imageUrls["vsc-2"] = baseUrl + "productimage-300016_b2d9cdc4-0a57-4ea9-ac82-c9be994d59a3.png";
    imageUrls["vss-2"] = baseUrl + "productimage-301211_c9e80b87-6931-49a0-a3f3-c4bf0558adbc.png";
    imageUrls["vsm-3"] = baseUrl + "productimage-300100_481634f1-902d-46ca-9da7-bbe7f2b83313.png";

    // Maag Audio short names
    imageUrls["eq4"] = baseUrl + "productimage-300035_428da437-d6de-412d-bbb1-9f804df6f30f.png";
    imageUrls["eq4 ms"] = baseUrl + "productimage-301107_7eb64f8c-bf0d-4ee7-9460-10e01a67a783.png";
    imageUrls["eq2"] = baseUrl + "productimage-300117_4ea7b383-e026-40eb-ad25-72287bdcd42e.png";
    imageUrls["magnum-k"] = baseUrl + "productimage-300396_1fab8194-5ca3-4b6d-99b1-0e53a025bcb9.png";

    // Console short names
    imageUrls["console ssl 4000 e"] = baseUrl + "productimage-300373_f5942771-0897-4d7f-8955-7795f96295a3.png";
    imageUrls["console ssl 4000 g"] = baseUrl + "productimage-300374_b2b44f03-8e78-4736-a7b6-ef8820665d5b.png";
    imageUrls["console ssl 9000 j"] = baseUrl + "productimage-300478_3bcb16b8-3645-45f3-9b99-4d738a5a344e.png";
    imageUrls["console amek 9099"] = baseUrl + "productimage-300556_e7ec008e-826c-4aaf-86d3-fa8cc6b0ab20.png";
    imageUrls["console amek 200"] = baseUrl + "productimage-300865_2bacbf1b-2cdf-4ab8-b1c6-59d6bc227cc4.png";
    imageUrls["console focusrite sc"] = baseUrl + "productimage-300402_e0b1d7b5-7b9b-466c-a224-1547f722b0f0.png";
    imageUrls["console n"] = baseUrl + "productimage-300345_47021cba-5c15-4974-aa89-ff492a889fed.png";

    // Black Box short names
    imageUrls["hg-2"] = baseUrl + "productimage-300259_1e8913ea-66da-4ac3-aee0-171e176dfa13.png";
    imageUrls["hg-2ms"] = baseUrl + "productimage-300541_892dac09-0f4a-4c59-ac02-2419b76d461c.png";
    imageUrls["hg-q"] = baseUrl + "productimage-300902_7f6334fb-d403-47bc-baae-18a9cd266cf3.png";

    // ADPTR short names
    imageUrls["metric ab"] = baseUrl + "productimage-300370_51fdb784-eaec-48b3-8609-4fccc7196d68.png";
    imageUrls["streamliner"] = baseUrl + "productimage-300537_a0567c85-b2b2-4bd1-9f46-8f546e962030.png";
    imageUrls["sculpt"] = baseUrl + "productimage-300570_a644e64a-2d6e-4492-a71a-2139f7043502.png";
    imageUrls["utopia"] = baseUrl + "productimage-301236.png";

    // Kirchhoff short names
    imageUrls["kirchhoff-eq"] = baseUrl + "productimage-300781_6b333574-9e0f-4247-9d6a-81a75d11eadd.png";
    imageUrls["kirchhoff eq"] = baseUrl + "productimage-300781_6b333574-9e0f-4247-9d6a-81a75d11eadd.png";

    // Cenozoix and Trinity
    imageUrls["cenozoix"] = baseUrl + "productimage-300982_3397fcd0-2e7b-4b96-b08b-5d82fa4c3528.png";
    imageUrls["trinity"] = baseUrl + "productimage-301099_9368cf32-6c6e-4541-ad84-f96fb8bcddbb.png";

    // Lindell short names
    imageUrls["80 series"] = baseUrl + "productimage-300475_de30a79f-c507-4963-9d9f-b09b50e2b91b.png";
    imageUrls["69 series"] = baseUrl + "productimage-300738_552e118f-280c-45c0-bb35-df6d7492b686.png";
    imageUrls["50 series"] = baseUrl + "productimage-300543_18e03db2-391e-4555-ba69-376b1cc1842a.png";
    imageUrls["354e"] = baseUrl + "productimage-300289_fadcef28-689f-493c-b1ae-a695928bf0a1.png";
    imageUrls["254e"] = baseUrl + "productimage-300150_4690a068-d00e-43e6-acf0-2f61f40d890e.png";
    imageUrls["902 de-esser"] = baseUrl + "productimage-300626_a2edb61f-a1c5-400e-96cb-656bbbda8fa9.png";
    imageUrls["7x-500"] = baseUrl + "productimage-300178_8bb5104f-8127-409a-89ec-25840ed22e19.png";
    imageUrls["6x-500"] = baseUrl + "productimage-300177_c6d72330-7dee-4c62-8c18-e10eb82e96ee.png";
    imageUrls["pex-500"] = baseUrl + "productimage-300179_fa86a3d6-3911-480f-9f7d-85737184eaca.png";
    imageUrls["channelx"] = baseUrl + "productimage-300175_b9f47d8b-15a3-4c65-9299-4baa15ee39cf.png";
    imageUrls["eq825"] = baseUrl + "productimage-301272.jpg";
    imageUrls["mbc"] = baseUrl + "productimage-300737_d0202dc3-2fc5-432e-b972-f3b6edc13dbd.png";
    imageUrls["sbc"] = baseUrl + "productimage-300627_3efa1f27-cc48-46d3-a800-a417c51b1e5c.png";

    // Bettermaker short names
    imageUrls["mastering compressor"] = baseUrl + "productimage-301237.png";
    imageUrls["bus compressor"] = baseUrl + "productimage-300973_b69e8739-4394-49f1-bb2d-c4df85dd2bcb.png";
    imageUrls["passive equalizer"] = baseUrl + "productimage-301098.png";

    // HUM short names
    imageUrls["laal"] = baseUrl + "productimage-301243_6f932fc9-447c-45be-86e4-699151db7721.png";

    // Millennia short names
    imageUrls["nseq-2"] = baseUrl + "productimage-300033_a9be6950-3a74-433a-bda2-fd86035e4ef3.png";

    // A/DA short names
    imageUrls["flanger"] = baseUrl + "productimage-300356_b75930af-e197-461f-a776-d0b40f6fbfd7.png";
    imageUrls["std-1"] = baseUrl + "productimage-300258_e4416d1c-8f75-4683-8195-cc03447e59a0.png";

    // Swivel short names
    imageUrls["spread"] = baseUrl + "productimage-301296.png";
    imageUrls["the sauce"] = baseUrl + "productimage-301290.png";
    imageUrls["sauce"] = baseUrl + "productimage-301290.png";
    imageUrls["knocktonal"] = baseUrl + "productimage-301298.png";
    imageUrls["click boom"] = baseUrl + "productimage-301299.png";
    imageUrls["bde"] = baseUrl + "productimage-301297.png";
    imageUrls["hitstrip"] = baseUrl + "productimage-301300.png";

    // Noveltech short names
    imageUrls["character"] = baseUrl + "productimage-300068_1e2c9ec6-8b04-49e6-ac20-bfbc963d0481.png";
    imageUrls["vocal enhancer"] = baseUrl + "productimage-300088_7acfec5d-912a-48ca-9ebd-fe07e741e6e1.png";

    // Knif short names
    imageUrls["soma"] = baseUrl + "productimage-300517_d93d3d4e-3d3c-42e4-9694-c3bea8252618.png";
    imageUrls["soma eq"] = baseUrl + "productimage-300517_d93d3d4e-3d3c-42e4-9694-c3bea8252618.png";

    // Fiedler short names
    imageUrls["stage"] = baseUrl + "productimage-300309_43e9ff7b-b505-4425-8a9d-c4b6954b2b06.png";
    imageUrls["spatial creator"] = baseUrl + "productimage-300904_d1c9b86a-5c99-4a62-b809-5790a753b57b.png";

    // DS Audio short names
    imageUrls["tantra 2"] = baseUrl + "productimage-300554_8ace881a-39b6-471d-9a28-fe0cf0673018.png";
    imageUrls["tantra"] = baseUrl + "productimage-300554_8ace881a-39b6-471d-9a28-fe0cf0673018.png";

    // Misc short names
    imageUrls["mc77"] = baseUrl + "productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png";
    imageUrls["mc 77"] = baseUrl + "productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png";
    imageUrls["dsm v3"] = baseUrl + "productimage-300403_9bb5d6c3-5d94-46d0-86c4-f8c86bd9a7c3.png";
    imageUrls["sa2rate"] = baseUrl + "productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png";
    imageUrls["sa2rate 2"] = baseUrl + "productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png";
    imageUrls["bax eq"] = baseUrl + "productimage-300095_e8339764-5fb2-4554-b4d2-14fee7d1b140.png";
    imageUrls["gav19t"] = baseUrl + "productimage-300114_a26c0820-3eb1-42f1-b72c-81005a988f27.png";
    imageUrls["silver bullet"] = baseUrl + "productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png";
    imageUrls["silver bullet mk2"] = baseUrl + "productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png";
    imageUrls["lisa"] = baseUrl + "productimage-300635_b22c3561-6e15-4c4d-ad52-4ac96b0e9d92.png";
    imageUrls["natalus"] = baseUrl + "productimage-300852_e65cdbad-a648-40b8-88e6-4fb77bb3a976.png";
    imageUrls["the oven"] = baseUrl + "productimage-300653_a16226c9-f5b9-4820-92c2-4240b4adfa66.png";
    imageUrls["oven"] = baseUrl + "productimage-300653_a16226c9-f5b9-4820-92c2-4240b4adfa66.png";
    imageUrls["opticom xla-3"] = baseUrl + "productimage-300211_137be455-e2d4-4035-9eee-f1ef6d7a3a15.png";
    imageUrls["xla-3"] = baseUrl + "productimage-300211_137be455-e2d4-4035-9eee-f1ef6d7a3a15.png";
    imageUrls["triad"] = baseUrl + "productimage-300393_2300346d-45cc-4bd1-997d-10b1946db4e8.png";
    imageUrls["perfection"] = baseUrl + "productimage-301331.png";
    imageUrls["xtcomp"] = baseUrl + "productimage-300998.png";
    imageUrls["xtressor"] = baseUrl + "productimage-300800_d2c32a9b-7c2a-4b1e-8a89-4c3a7c8d9e12.png";
}

juce::String PluginImageCache::normalizePluginName(const juce::String& name) const
{
    return name.toLowerCase().trim();
}

// Generate alternative name variants for lookup
juce::StringArray PluginImageCache::getNameVariants(const juce::String& normalizedName) const
{
    juce::StringArray variants;
    variants.add(normalizedName);

    // Common brand prefixes to try removing
    juce::StringArray brandPrefixes = {
        "unfiltered audio ", "brainworx ", "plugin alliance ", "ds audio ",
        "knif audio ", "lindell audio ", "maag audio ", "mäag audio ",
        "shadow hills ", "black box analog design ", "black box ",
        "three-body technology ", "fiedler audio ", "adptr audio ",
        "swivel audio ", "kiive audio ", "tomo audiolabs ", "hum audio devices ",
        "louder than liftoff ", "pro audio dsp ", "purple audio ",
        "dangerous music ", "chandler limited ", "harris doyle ",
        "karanyi sounds ", "cut classic ", "acme audio ", "mixland ",
        "maor appelbaum ", "noveltech ", "bettermaker ", "looptrotter ",
        "millennia ", "vertigo ", "elysia ", "spl ", "neold ", "amek ",
        "ampeg ", "diezel ", "engl ", "friedman ", "fuchs ", "suhr ",
        "gallien-krueger ", "gallien krueger "
    };

    // Try removing brand prefixes
    for (const auto& prefix : brandPrefixes)
    {
        if (normalizedName.startsWith(prefix))
        {
            auto withoutPrefix = normalizedName.substring(prefix.length()).trim();
            if (withoutPrefix.isNotEmpty() && !variants.contains(withoutPrefix))
                variants.add(withoutPrefix);
        }
    }

    // Also try adding common brand prefixes if we have a short name
    if (!normalizedName.contains(" ") || normalizedName.length() < 15)
    {
        // Try with common prefixes for known product names
        juce::StringArray prefixesToTry = {
            "unfiltered audio ", "brainworx ", "ds audio ", "knif audio ",
            "lindell audio ", "spl ", "neold ", "elysia ", "bettermaker "
        };

        for (const auto& prefix : prefixesToTry)
        {
            auto withPrefix = prefix + normalizedName;
            if (!variants.contains(withPrefix))
                variants.add(withPrefix);
        }
    }

    return variants;
}

juce::String PluginImageCache::findImageUrl(const juce::String& normalizedName) const
{
    // Try to find URL using multiple name variants
    auto variants = getNameVariants(normalizedName);

    for (const auto& variant : variants)
    {
        auto it = imageUrls.find(variant);
        if (it != imageUrls.end() && it->second.isNotEmpty())
            return it->second;
    }

    return juce::String();
}

juce::File PluginImageCache::getCacheDirectory() const
{
    return juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
        .getChildFile("PluginAllianceLauncher")
        .getChildFile("ImageCache");
}

juce::File PluginImageCache::getCacheFile(const juce::String& pluginName) const
{
    // Create a safe filename from the plugin name
    auto safeName = pluginName.toLowerCase()
        .replaceCharacter(' ', '_')
        .replaceCharacter('/', '-')
        .retainCharacters("abcdefghijklmnopqrstuvwxyz0123456789_-");
    return getCacheDirectory().getChildFile(safeName + ".png");
}

juce::File PluginImageCache::getBundledImageFile(const juce::String& pluginName) const
{
    if (!bundledImagesPath.isDirectory())
        return juce::File();

    // Normalize the plugin name for lookup (lowercase, trimmed)
    auto normalizedName = pluginName.toLowerCase().trim();

    // Try multiple name variants
    auto variants = getNameVariants(normalizedName);

    for (const auto& variant : variants)
    {
        // Look up the thumbnail filename from our mapping
        auto it = thumbnailFilenames.find(variant);
        if (it != thumbnailFilenames.end())
        {
            auto file = bundledImagesPath.getChildFile(it->second + ".png");
            if (file.existsAsFile())
                return file;
        }

        // Also try deriving filename programmatically for each variant
        auto safeName = variant
            .replaceCharacter(' ', '_')
            .replaceCharacter('/', '_')
            .replaceCharacter('-', '_')
            .retainCharacters("abcdefghijklmnopqrstuvwxyz0123456789_");

        auto derivedFile = bundledImagesPath.getChildFile(safeName + ".png");
        if (derivedFile.existsAsFile())
            return derivedFile;
    }

    // Fallback: search for files containing key parts of the plugin name
    auto searchPattern = normalizedName
        .replaceCharacter(' ', '_')
        .replaceCharacter('-', '_')
        .retainCharacters("abcdefghijklmnopqrstuvwxyz0123456789_");

    // Try to find a file that starts with a significant portion of the name
    for (auto& file : bundledImagesPath.findChildFiles(juce::File::findFiles, false, "*.png"))
    {
        auto fileName = file.getFileNameWithoutExtension().toLowerCase();
        // Check if filenames share significant overlap
        if (fileName.contains(searchPattern.substring(0, juce::jmin(10, searchPattern.length()))) ||
            searchPattern.contains(fileName.substring(0, juce::jmin(10, fileName.length()))))
        {
            return file;
        }
    }

    return juce::File();
}

bool PluginImageCache::loadFromBundled(const juce::String& pluginName)
{
    auto bundledFile = getBundledImageFile(pluginName);

    if (bundledFile.existsAsFile())
    {
        auto image = juce::ImageFileFormat::loadFrom(bundledFile);
        if (image.isValid())
        {
            juce::ScopedLock scopedLock(lock);
            // Store with normalized name so getImage() can find it
            loadedImages[normalizePluginName(pluginName)] = image;
            return true;
        }
    }

    return false;
}

juce::Image PluginImageCache::getImage(const juce::String& pluginName)
{
    juce::ScopedLock scopedLock(lock);

    auto normalizedName = normalizePluginName(pluginName);
    auto it = loadedImages.find(normalizedName);

    if (it != loadedImages.end())
        return it->second;

    // Not loaded yet, return empty image
    return juce::Image();
}

bool PluginImageCache::hasImage(const juce::String& pluginName) const
{
    juce::ScopedLock scopedLock(lock);

    auto normalizedName = normalizePluginName(pluginName);
    return loadedImages.find(normalizedName) != loadedImages.end();
}

void PluginImageCache::requestImage(const juce::String& pluginName)
{
    juce::ScopedLock scopedLock(lock);

    auto normalizedName = normalizePluginName(pluginName);

    // Already loaded
    if (loadedImages.find(normalizedName) != loadedImages.end())
        return;

    // Already pending
    if (pendingRequests.count(normalizedName) > 0)
        return;

    // Queue the request - we'll try bundled images, cache, then URL download
    pendingRequests.insert(normalizedName);
    wakeUp.signal();
}

bool PluginImageCache::loadFromCache(const juce::String& pluginName)
{
    auto cacheFile = getCacheFile(pluginName);

    if (cacheFile.existsAsFile())
    {
        auto image = juce::ImageFileFormat::loadFrom(cacheFile);
        if (image.isValid())
        {
            juce::ScopedLock scopedLock(lock);
            // Store with normalized name so getImage() can find it
            loadedImages[normalizePluginName(pluginName)] = image;
            return true;
        }
    }

    return false;
}

bool PluginImageCache::downloadImage(const juce::String& pluginName, const juce::String& url)
{
    if (url.isEmpty())
        return false;

    // Use JUCE's URL class to download
    juce::URL imageUrl(url);

    auto options = juce::URL::InputStreamOptions(juce::URL::ParameterHandling::inAddress)
        .withConnectionTimeoutMs(10000)
        .withNumRedirectsToFollow(5);

    auto stream = imageUrl.createInputStream(options);

    if (stream != nullptr)
    {
        juce::MemoryBlock data;
        stream->readIntoMemoryBlock(data);

        auto image = juce::ImageFileFormat::loadFrom(data.getData(), data.getSize());

        if (image.isValid())
        {
            // Resize to a reasonable thumbnail size
            const int thumbnailWidth = 160;
            const int thumbnailHeight = 100;

            auto thumbnail = image.rescaled(thumbnailWidth, thumbnailHeight, juce::Graphics::highResamplingQuality);

            // Save to cache
            auto cacheFile = getCacheFile(pluginName);
            cacheFile.getParentDirectory().createDirectory();

            juce::FileOutputStream outputStream(cacheFile);
            if (outputStream.openedOk())
            {
                juce::PNGImageFormat pngFormat;
                pngFormat.writeImageToStream(thumbnail, outputStream);
            }

            // Store in memory
            {
                juce::ScopedLock scopedLock(lock);
                loadedImages[pluginName] = thumbnail;
            }

            return true;
        }
    }

    return false;
}

void PluginImageCache::run()
{
    while (!shouldExit)
    {
        juce::String pluginToLoad;
        juce::String urlToLoad;

        // Get next pending request
        {
            juce::ScopedLock scopedLock(lock);

            if (!pendingRequests.empty())
            {
                pluginToLoad = *pendingRequests.begin();
                pendingRequests.erase(pendingRequests.begin());

                // Use name variants to find URL
                urlToLoad = findImageUrl(pluginToLoad);
            }
        }

        if (pluginToLoad.isNotEmpty())
        {
            // Try loading from bundled resources first (fastest)
            if (!loadFromBundled(pluginToLoad))
            {
                // Try loading from cache
                if (!loadFromCache(pluginToLoad))
                {
                    // Download from web as fallback
                    downloadImage(pluginToLoad, urlToLoad);
                }
            }

            // Notify that image is loaded
            if (onImageLoaded)
            {
                juce::MessageManager::callAsync([this, pluginToLoad]() {
                    if (onImageLoaded)
                        onImageLoaded(pluginToLoad);
                });
            }
        }
        else
        {
            // Wait for new requests
            wakeUp.wait(1000);
        }
    }
}

} // namespace PALauncher
