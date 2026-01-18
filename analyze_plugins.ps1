# Plugin Alliance plugin analysis script
# Maps installed plugins to thumbnail filenames

$paPlugins = @(
    # Format: @{Name="VST3 Name"; Thumbnail="expected_filename"; ProductUrl="plugin-alliance-url-slug"}

    # Acme Audio
    @{Name="Acme Opticom XLA-3"; Thumbnail="acme_opticom_xla3"; Slug="acme_audio_opticom_xla-3"}

    # ADA
    @{Name="ADA Flanger"; Thumbnail="ada_flanger"; Slug="ada_flanger"}
    @{Name="ADA STD-1 Stereo Tapped Delay"; Thumbnail="ada_std1"; Slug="ada_std-1_stereo_tapped_delay"}

    # ADPTR
    @{Name="ADPTR Hype"; Thumbnail="adptr_hype"; Slug="adptr_hype"}
    @{Name="ADPTR MetricAB"; Thumbnail="adptr_metric_ab"; Slug="adptr_metricab"}
    @{Name="ADPTR Sculpt"; Thumbnail="adptr_sculpt"; Slug="adptr_sculpt"}
    @{Name="ADPTR StreamLiner"; Thumbnail="adptr_streamliner"; Slug="adptr_streamliner"}
    @{Name="ADPTR Utopia"; Thumbnail="adptr_utopia"; Slug="adptr_utopia"}

    # AMEK
    @{Name="AMEK EQ 200"; Thumbnail="amek_eq200"; Slug="amek_eq_200"}
    @{Name="AMEK EQ 250"; Thumbnail="amek_eq250"; Slug="amek_eq_250"}
    @{Name="AMEK Mastering Compressor"; Thumbnail="amek_mastering_compressor"; Slug="amek_200_mastering_compressor"}

    # Ampeg
    @{Name="Ampeg B15N"; Thumbnail="ampeg_b15n"; Slug="ampeg_b-15n"}
    @{Name="Ampeg SVT3Pro"; Thumbnail="ampeg_svt3pro"; Slug="ampeg_svt-3pro"}
    @{Name="Ampeg SVTVR"; Thumbnail="ampeg_svtvr"; Slug="ampeg_svt-vr"}
    @{Name="Ampeg SVTVR Classic"; Thumbnail="ampeg_svtvr_classic"; Slug="ampeg_svt-vr_classic"}
    @{Name="Ampeg V4B"; Thumbnail="ampeg_v4b"; Slug="ampeg_v-4b"}

    # Bettermaker
    @{Name="Bettermaker BM60"; Thumbnail="bettermaker_bm60"; Slug="bettermaker_bm60"}
    @{Name="Bettermaker Bus Compressor"; Thumbnail="bettermaker_bus_compressor"; Slug="bettermaker_bus_compressor"}
    @{Name="Bettermaker Bus Compressor DSP"; Thumbnail="bettermaker_bus_compressor"; Slug="bettermaker_bus_compressor"}
    @{Name="Bettermaker C502V DSP"; Thumbnail="bettermaker_c502v"; Slug="bettermaker_c502v"}
    @{Name="Bettermaker EQ232D"; Thumbnail="bettermaker_eq232d"; Slug="bettermaker_eq232d"}
    @{Name="Bettermaker Mastering Compressor DSP"; Thumbnail="bettermaker_mastering_compressor"; Slug="bettermaker_mastering_compressor"}
    @{Name="Bettermaker Passive Equalizer"; Thumbnail="bettermaker_perfection"; Slug="bettermaker_perfection"}

    # Black Box Analog Design
    @{Name="Black Box Analog Design HG-2"; Thumbnail="black_box_hg2"; Slug="black_box_analog_design_hg-2"}
    @{Name="Black Box Analog Design HG-2MS"; Thumbnail="black_box_hg2ms"; Slug="black_box_analog_design_hg-2ms"}
    @{Name="Black Box Analog Design HG-Q"; Thumbnail="black_box_hgq"; Slug="black_box_analog_design_hg-q"}

    # Brainworx
    @{Name="bx_2098 EQ"; Thumbnail="bx_2098_eq"; Slug="bx_2098_eq"}
    @{Name="bx_aura"; Thumbnail="bx_aura"; Slug="bx_aura"}
    @{Name="bx_bassdude"; Thumbnail="bx_bassdude"; Slug="bx_bassdude"}
    @{Name="bx_blackdist2"; Thumbnail="bx_blackdist2"; Slug="bx_blackdist2"}
    @{Name="bx_bluechorus2"; Thumbnail="bx_bluechorus2"; Slug="bx_bluechorus2"}
    @{Name="bx_boom"; Thumbnail="bx_boom_v3"; Slug="bx_boom"}
    @{Name="bx_boom V3"; Thumbnail="bx_boom_v3"; Slug="bx_boom"}
    @{Name="bx_cleansweep Pro"; Thumbnail="bx_cleansweep_pro"; Slug="bx_cleansweep_pro"}
    @{Name="bx_cleansweep V2"; Thumbnail="bx_cleansweep_pro"; Slug="bx_cleansweep_pro"}
    @{Name="bx_clipper"; Thumbnail="bx_clipper"; Slug="bx_clipper"}
    @{Name="bx_console AMEK 200"; Thumbnail="bx_console_amek_200"; Slug="bx_console_amek_200"}
    @{Name="bx_console AMEK 9099"; Thumbnail="bx_console_amek_9099"; Slug="bx_console_amek_9099"}
    @{Name="bx_console Focusrite SC"; Thumbnail="bx_console_focusrite_sc"; Slug="bx_console_focusrite_sc"}
    @{Name="bx_console N"; Thumbnail="bx_console_n"; Slug="bx_console_n"}
    @{Name="bx_console SSL 4000 E"; Thumbnail="bx_console_ssl_4000_e"; Slug="bx_console_ssl_4000_e"}
    @{Name="bx_console SSL 4000 G"; Thumbnail="bx_console_ssl_4000_g"; Slug="bx_console_ssl_4000_g"}
    @{Name="bx_console SSL 9000 J"; Thumbnail="bx_console_ssl_9000_j"; Slug="bx_console_ssl_9000_j"}
    @{Name="bx_control V2"; Thumbnail="bx_control_v2"; Slug="bx_control_v2"}
    @{Name="bx_crispyscale"; Thumbnail="bx_crispyscale"; Slug="bx_crispyscale"}
    @{Name="bx_crispytuner"; Thumbnail="bx_crispytuner"; Slug="bx_crispytuner"}
    @{Name="bx_delay2500"; Thumbnail="bx_delay_2500"; Slug="bx_delay_2500"}
    @{Name="bx_digital V3"; Thumbnail="bx_digital_v3"; Slug="bx_digital_v3"}
    @{Name="bx_digital V3 mix"; Thumbnail="bx_digital_v3"; Slug="bx_digital_v3"}
    @{Name="bx_distorange"; Thumbnail="bx_distorange"; Slug="bx_distorange"}
    @{Name="bx_dynEQ V2"; Thumbnail="bx_dyneq_v2"; Slug="bx_dyneq_v2"}
    @{Name="bx_dynEQ V2 Mono"; Thumbnail="bx_dyneq_v2"; Slug="bx_dyneq_v2"}
    @{Name="bx_enhancer"; Thumbnail="bx_enhancer"; Slug="bx_enhancer"}
    @{Name="bx_glue"; Thumbnail="bx_glue"; Slug="bx_glue"}
    @{Name="bx_greenscreamer"; Thumbnail="bx_greenscreamer"; Slug="bx_greenscreamer"}
    @{Name="bx_hybrid V2"; Thumbnail="bx_hybrid_v2"; Slug="bx_hybrid_v2"}
    @{Name="bx_hybrid V2 mix"; Thumbnail="bx_hybrid_v2"; Slug="bx_hybrid_v2"}
    @{Name="bx_limiter"; Thumbnail="bx_limiter"; Slug="bx_limiter"}
    @{Name="bx_limiter True Peak"; Thumbnail="bx_limiter_true_peak"; Slug="bx_limiter_true_peak"}
    @{Name="bx_masterdesk"; Thumbnail="bx_masterdesk"; Slug="bx_masterdesk"}
    @{Name="bx_masterdesk Classic"; Thumbnail="bx_masterdesk"; Slug="bx_masterdesk"}
    @{Name="bx_masterdesk Pro"; Thumbnail="bx_masterdesk_pro"; Slug="bx_masterdesk_pro"}
    @{Name="bx_masterdesk True Peak"; Thumbnail="bx_masterdesk_true_peak"; Slug="bx_masterdesk_true_peak"}
    @{Name="bx_megadual"; Thumbnail="bx_megadual"; Slug="bx_megadual"}
    @{Name="bx_megasingle"; Thumbnail="bx_megasingle"; Slug="bx_megasingle"}
    @{Name="bx_metal2"; Thumbnail="bx_metal2"; Slug="bx_metal2"}
    @{Name="bx_meter"; Thumbnail="bx_meter"; Slug="bx_meter"}
    @{Name="bx_oberhausen"; Thumbnail="bx_oberhausen"; Slug="bx_oberhausen"}
    @{Name="bx_opto"; Thumbnail="bx_opto"; Slug="bx_opto"}
    @{Name="bx_opto Pedal"; Thumbnail="bx_opto"; Slug="bx_opto"}
    @{Name="bx_panEQ"; Thumbnail="bx_paneq"; Slug="bx_paneq"}
    @{Name="bx_pulsar"; Thumbnail="bx_pulsar"; Slug="bx_pulsar"}
    @{Name="bx_refinement"; Thumbnail="bx_refinement_v3"; Slug="bx_refinement"}
    @{Name="bx_refinement V3"; Thumbnail="bx_refinement_v3"; Slug="bx_refinement"}
    @{Name="bx_rockergain100"; Thumbnail="bx_rockergain100"; Slug="bx_rockergain100"}
    @{Name="bx_rockrack V3"; Thumbnail="bx_rockrack_v3"; Slug="bx_rockrack_v3"}
    @{Name="bx_rockrack V3 Player"; Thumbnail="bx_rockrack_v3"; Slug="bx_rockrack_v3"}
    @{Name="bx_rooMS"; Thumbnail="bx_rooms"; Slug="bx_roooms"}
    @{Name="bx_saturator V2"; Thumbnail="bx_saturator_v2"; Slug="bx_saturator_v2"}
    @{Name="bx_shredspread"; Thumbnail="bx_shredspread"; Slug="bx_shredspread"}
    @{Name="bx_solo"; Thumbnail="bx_solo"; Slug="bx_solo"}
    @{Name="bx_stereomaker"; Thumbnail="bx_stereomaker"; Slug="bx_stereomaker"}
    @{Name="bx_subfilter"; Thumbnail="bx_subfilter"; Slug="bx_subfilter"}
    @{Name="bx_subsynth"; Thumbnail="bx_subsynth"; Slug="bx_subsynth"}
    @{Name="bx_tonebox"; Thumbnail="bx_tonebox"; Slug="bx_tonebox"}
    @{Name="bx_townhouse Buss Compressor"; Thumbnail="bx_townhouse"; Slug="bx_townhouse_buss_compressor"}
    @{Name="bx_tuner"; Thumbnail="bx_tuner"; Slug="bx_tuner"}
    @{Name="bx_XL V2"; Thumbnail="bx_xl_v3"; Slug="bx_xl_v2"}
    @{Name="bx_XL V3"; Thumbnail="bx_xl_v3"; Slug="bx_xl_v2"}
    @{Name="bx_yellowdrive"; Thumbnail="bx_yellowdrive"; Slug="bx_yellowdrive"}

    # Chandler
    @{Name="Chandler GAV19T"; Thumbnail="chandler_gav19t"; Slug="chandler_limited_gav19t"}

    # Cut Classic
    @{Name="Cut Classic High Flyer"; Thumbnail="cut_classic_high_flyer"; Slug="cut_classic_high_flyer"}

    # Dangerous
    @{Name="Dangerous BAX EQ Master"; Thumbnail="dangerous_bax_eq"; Slug="dangerous_bax_eq"}
    @{Name="Dangerous BAX EQ Mix"; Thumbnail="dangerous_bax_eq"; Slug="dangerous_bax_eq"}

    # Diezel
    @{Name="Diezel Herbert"; Thumbnail="diezel_herbert"; Slug="diezel_herbert"}
    @{Name="Diezel VH4"; Thumbnail="diezel_vh4"; Slug="diezel_vh4"}

    # DS Audio (Dmitry Sches)
    @{Name="DS Tantra 2"; Thumbnail="ds_audio_tantra_2"; Slug="ds_audio_tantra_2"}
    @{Name="DS Thorn"; Thumbnail="ds_audio_thorn"; Slug="ds_audio_thorn"}

    # elysia
    @{Name="elysia alpha compressor V2"; Thumbnail="elysia_alpha_compressor"; Slug="elysia_alpha_compressor"}
    @{Name="elysia alpha master"; Thumbnail="elysia_alpha_compressor"; Slug="elysia_alpha_compressor"}
    @{Name="elysia alpha mix"; Thumbnail="elysia_alpha_compressor"; Slug="elysia_alpha_compressor"}
    @{Name="elysia karacter master"; Thumbnail="elysia_karacter"; Slug="elysia_karacter"}
    @{Name="elysia karacter mix"; Thumbnail="elysia_karacter"; Slug="elysia_karacter"}
    @{Name="elysia mpressor"; Thumbnail="elysia_mpressor"; Slug="elysia_mpressor"}
    @{Name="elysia museq master"; Thumbnail="elysia_museq"; Slug="elysia_museq"}
    @{Name="elysia museq mix"; Thumbnail="elysia_museq"; Slug="elysia_museq"}
    @{Name="elysia niveau filter"; Thumbnail="elysia_niveau_filter"; Slug="elysia_niveau_filter"}
    @{Name="elysia nvelope"; Thumbnail="elysia_nvelope"; Slug="elysia_nvelope"}
    @{Name="elysia phils cascade"; Thumbnail="elysia_phils_cascade"; Slug="elysia_phils_cascade"}

    # ENGL
    @{Name="ENGL E646 VS"; Thumbnail="engl_e646_vs"; Slug="engl_e646_vs"}
    @{Name="ENGL E765 RT"; Thumbnail="engl_e765_rt"; Slug="engl_e765_rt"}
    @{Name="ENGL Savage 120"; Thumbnail="engl_savage_120"; Slug="engl_savage_120"}

    # fiedler audio
    @{Name="fiedler audio spacelab beam"; Thumbnail="fiedler_spacelab_beam"; Slug="fiedler_audio_spacelab"}
    @{Name="fiedler audio spacelab ignition"; Thumbnail="fiedler_spacelab_ignition"; Slug="fiedler_audio_spacelab_ignition"}
    @{Name="fiedler audio splat"; Thumbnail="fiedler_splat"; Slug="fiedler_audio_splat"}
    @{Name="fiedler audio stage"; Thumbnail="fiedler_stage"; Slug="fiedler_audio_stage"}

    # Friedman
    @{Name="Friedman BE100"; Thumbnail="friedman_be100"; Slug="friedman_be-100"}
    @{Name="Friedman Buxom Betty"; Thumbnail="friedman_buxom_betty"; Slug="friedman_buxom_betty"}
    @{Name="Friedman DS40"; Thumbnail="friedman_ds40"; Slug="friedman_ds-40"}

    # Fuchs
    @{Name="Fuchs Overdrive Supreme 50"; Thumbnail="fuchs_overdrive_supreme_50"; Slug="fuchs_overdrive_supreme_50"}
    @{Name="Fuchs Train II"; Thumbnail="fuchs_train_ii"; Slug="fuchs_train_ii"}

    # Gallien Krueger
    @{Name="Gallien Krueger 800RB"; Thumbnail="gallien_krueger_800rb"; Slug="gallien-krueger_800rb"}

    # Harris Doyle
    @{Name="Harris Doyle Natalus DSCEQ"; Thumbnail="harris_doyle_natalus"; Slug="harris_doyle_natalus_dsceq"}

    # HEARS
    @{Name="HEARS Perfection"; Thumbnail="hears_perfection"; Slug="hears_perfection"}

    # HUM Audio
    @{Name="HUM Audio Devices LAAL"; Thumbnail="hum_laal"; Slug="hum_audio_devices_laal"}

    # Karanyi
    @{Name="Karanyi Sounds Wavesurfer"; Thumbnail="karanyi_wavesurfer"; Slug="karanyi_sounds_wavesurfer"}

    # Kiive
    @{Name="Kiive Tape Face"; Thumbnail="kiive_tape_face"; Slug="kiive_tape_face"}
    @{Name="Kiive XTComp"; Thumbnail="kiive_xtcomp"; Slug="kiive_xtcomp"}
    @{Name="Kiive Xtressor"; Thumbnail="kiive_xtressor"; Slug="kiive_xtressor"}

    # Knif Audio
    @{Name="Knif Audio Knifonium"; Thumbnail="knif_knifonium"; Slug="knif_audio_knifonium"}
    @{Name="Knif Audio Soma"; Thumbnail="knif_soma"; Slug="knif_audio_soma"}

    # Lindell
    @{Name="Lindell 254E"; Thumbnail="lindell_254e"; Slug="lindell_audio_254e"}
    @{Name="Lindell 354E"; Thumbnail="lindell_354e"; Slug="lindell_audio_354e"}
    @{Name="Lindell 50 Buss"; Thumbnail="lindell_50_series"; Slug="lindell_audio_50_series"}
    @{Name="Lindell 50 Channel"; Thumbnail="lindell_50_series"; Slug="lindell_audio_50_series"}
    @{Name="Lindell 69 Buss"; Thumbnail="lindell_69_series"; Slug="lindell_audio_69_series"}
    @{Name="Lindell 69 Channel"; Thumbnail="lindell_69_series"; Slug="lindell_audio_69_series"}
    @{Name="Lindell 6X-500"; Thumbnail="lindell_6x500"; Slug="lindell_audio_6x-500"}
    @{Name="Lindell 7X-500"; Thumbnail="lindell_7x500"; Slug="lindell_audio_7x-500"}
    @{Name="Lindell 80 Bus"; Thumbnail="lindell_80_series"; Slug="lindell_audio_80_series"}
    @{Name="Lindell 80 Channel"; Thumbnail="lindell_80_series"; Slug="lindell_audio_80_series"}
    @{Name="Lindell 902 De-esser"; Thumbnail="lindell_902_deesser"; Slug="lindell_audio_902_de-esser"}
    @{Name="Lindell ChannelX"; Thumbnail="lindell_channelx"; Slug="lindell_audio_channelx"}
    @{Name="Lindell EQ825"; Thumbnail="lindell_eq825"; Slug="lindell_audio_eq825"}
    @{Name="Lindell MBC"; Thumbnail="lindell_mbc"; Slug="lindell_audio_mbc"}
    @{Name="Lindell MU-66"; Thumbnail="lindell_mu66"; Slug="lindell_audio_mu-66"}
    @{Name="Lindell PEX-500"; Thumbnail="lindell_pex500"; Slug="lindell_audio_pex-500"}
    @{Name="Lindell SBC"; Thumbnail="lindell_sbc"; Slug="lindell_audio_sbc"}
    @{Name="Lindell TE-100"; Thumbnail="lindell_te100"; Slug="lindell_audio_te-100"}

    # Looptrotter
    @{Name="Looptrotter SA2RATE2"; Thumbnail="looptrotter_sa2rate_2"; Slug="looptrotter_sa2rate_2"}

    # LTL (Louder Than Liftoff)
    @{Name="LTL Chop Shop EQ"; Thumbnail="ltl_chop_shop"; Slug="louder_than_liftoff_chop_shop_eq"}
    @{Name="LTL SILVER BULLET mk2"; Thumbnail="louder_than_liftoff_silver_bullet"; Slug="louder_than_liftoff_silver_bullet_mk2"}

    # Maag
    @{Name="Maag EQ2"; Thumbnail="maag_audio_eq2"; Slug="maag_audio_eq2"}
    @{Name="Maag EQ4"; Thumbnail="maag_audio_eq4"; Slug="maag_audio_eq4"}
    @{Name="Maag EQ4 MS"; Thumbnail="maag_audio_eq4"; Slug="maag_audio_eq4_ms"}
    @{Name="Maag MAGNUM-K"; Thumbnail="maag_audio_magnumk"; Slug="maag_audio_magnum-k"}

    # Millennia
    @{Name="Millennia NSEQ-2"; Thumbnail="millennia_nseq2"; Slug="millennia_nseq-2"}
    @{Name="Millennia TCL-2"; Thumbnail="millennia_tcl2"; Slug="millennia_tcl-2"}

    # Mixland
    @{Name="Mixland Vac Attack"; Thumbnail="mixland_vac_attack"; Slug="mixland_vac_attack"}

    # NEOLD
    @{Name="NEOLD BIG AL"; Thumbnail="neold_big_al"; Slug="neold_big_al"}
    @{Name="NEOLD OLDTIMER"; Thumbnail="neold_oldtimer"; Slug="neold_oldtimer"}
    @{Name="NEOLD RZ062"; Thumbnail="neold_rz062"; Slug="neold_rz062"}
    @{Name="NEOLD U17"; Thumbnail="neold_u17"; Slug="neold_u17"}
    @{Name="NEOLD U2A"; Thumbnail="neold_u2a"; Slug="neold_u2a"}
    @{Name="NEOLD V76U73"; Thumbnail="neold_v76u73"; Slug="neold_v76u73"}
    @{Name="NEOLD WARBLE"; Thumbnail="neold_warble"; Slug="neold_warble"}
    @{Name="NEOLD WUNDERLICH"; Thumbnail="neold_wunderlich"; Slug="neold_wunderlich"}

    # Noveltech
    @{Name="Noveltech Character"; Thumbnail="noveltech_character"; Slug="noveltech_character"}
    @{Name="Noveltech Vocal Enhancer"; Thumbnail="noveltech_vocal_enhancer"; Slug="noveltech_vocal_enhancer"}

    # Pro Audio DSP
    @{Name="Pro Audio DSP DSM V3"; Thumbnail="pro_audio_dsp_dsm_v3"; Slug="pro_audio_dsp_dsm_v3"}

    # Purple Audio
    @{Name="Purple Audio MC 77"; Thumbnail="purple_audio_mc77"; Slug="purple_audio_mc_77"}

    # Shadow Hills
    @{Name="Shadow Hills Class A Mastering Comp"; Thumbnail="shadow_hills_mastering_compressor_class_a"; Slug="shadow_hills_mastering_compressor_class_a"}
    @{Name="Shadow Hills Mastering Compressor"; Thumbnail="shadow_hills_mastering_compressor"; Slug="shadow_hills_mastering_compressor"}
    @{Name="Shadow Hills OptoMax"; Thumbnail="shadow_hills_optomax"; Slug="shadow_hills_optomax"}

    # SPL
    @{Name="SPL Attacker Plus"; Thumbnail="spl_attacker_plus"; Slug="spl_attacker_plus"}
    @{Name="SPL BiG"; Thumbnail="spl_big"; Slug="spl_big"}
    @{Name="SPL De-Esser"; Thumbnail="spl_de_esser_collection"; Slug="spl_de-esser_collection"}
    @{Name="SPL De-Esser Dual-Band"; Thumbnail="spl_de_esser_collection"; Slug="spl_de-esser_collection"}
    @{Name="SPL De-Verb Plus"; Thumbnail="spl_deverb_plus"; Slug="spl_de-verb_plus"}
    @{Name="SPL DrumXchanger"; Thumbnail="spl_drumxchanger"; Slug="spl_drumxchanger"}
    @{Name="SPL EQ Ranger Plus"; Thumbnail="spl_eq_ranger_plus"; Slug="spl_eq_ranger_plus"}
    @{Name="SPL Free Ranger"; Thumbnail="spl_free_ranger"; Slug="spl_free_ranger"}
    @{Name="SPL HawkEye"; Thumbnail="spl_hawkeye"; Slug="spl_hawkeye"}
    @{Name="SPL IRON"; Thumbnail="spl_iron"; Slug="spl_iron"}
    @{Name="SPL Machine Head"; Thumbnail="spl_machine_head"; Slug="spl_machine_head"}
    @{Name="SPL Mo-Verb Plus"; Thumbnail="spl_moverb_plus"; Slug="spl_mo-verb_plus"}
    @{Name="SPL Passeq"; Thumbnail="spl_passeq"; Slug="spl_passeq"}
    @{Name="SPL Passeq Single"; Thumbnail="spl_passeq"; Slug="spl_passeq"}
    @{Name="SPL PQ"; Thumbnail="spl_pq"; Slug="spl_pq"}
    @{Name="SPL Transient Designer Plus"; Thumbnail="spl_transient_designer_plus"; Slug="spl_transient_designer_plus"}
    @{Name="SPL TwinTube"; Thumbnail="spl_twintube"; Slug="spl_twintube"}
    @{Name="SPL Vitalizer MK2-T"; Thumbnail="spl_vitalizer_mk3t"; Slug="spl_vitalizer_mk2-t"}
    @{Name="SPL Vitalizer MK3-T"; Thumbnail="spl_vitalizer_mk3t"; Slug="spl_vitalizer_mk3-t"}

    # Suhr
    @{Name="Suhr PT100"; Thumbnail="suhr_pt100"; Slug="suhr_pt100"}
    @{Name="Suhr SE100"; Thumbnail="suhr_se100"; Slug="suhr_se100"}

    # Swivel Audio
    @{Name="Swivel Audio BDE"; Thumbnail="swivel_bde"; Slug="swivel_audio_bde"}
    @{Name="Swivel Audio Click Boom"; Thumbnail="swivel_click_boom"; Slug="swivel_audio_click_boom"}
    @{Name="Swivel Audio HitStrip"; Thumbnail="swivel_hitstrip"; Slug="swivel_audio_hitstrip"}
    @{Name="Swivel Audio Knocktonal"; Thumbnail="swivel_knocktonal"; Slug="swivel_audio_knocktonal"}
    @{Name="Swivel Audio Spread"; Thumbnail="swivel_spread"; Slug="swivel_audio_spread"}
    @{Name="Swivel Audio The Sauce"; Thumbnail="swivel_the_sauce"; Slug="swivel_audio_the_sauce"}

    # TBTECH (Three Body Tech)
    @{Name="TBTECH Cenozoix Compressor"; Thumbnail="cenozoix_compressor"; Slug="cenozoix_compressor"}
    @{Name="TBTECH Kirchhoff-EQ"; Thumbnail="kirchhoff_eq"; Slug="kirchhoff-eq"}
    @{Name="TBTECH Trinity Shaper"; Thumbnail="trinity_shaper"; Slug="trinity_shaper"}

    # THE OVEN (Mixland)
    @{Name="THE OVEN"; Thumbnail="mixland_the_oven"; Slug="mixland_the_oven"}

    # THX
    @{Name="THX Spatial Creator"; Thumbnail="thx_spatial_creator"; Slug="thx_spatial_creator"}

    # TOMO
    @{Name="TOMO Audiolabs LISA"; Thumbnail="tomo_lisa"; Slug="tomo_audiolabs_lisa"}

    # Unfiltered Audio
    @{Name="Unfiltered Audio Bass Mint"; Thumbnail="unfiltered_bass_mint"; Slug="unfiltered_audio_bass-mint"}
    @{Name="Unfiltered Audio Battalion"; Thumbnail="unfiltered_battalion"; Slug="unfiltered_audio_battalion"}
    @{Name="Unfiltered Audio Byome"; Thumbnail="unfiltered_byome"; Slug="unfiltered_audio_byome"}
    @{Name="Unfiltered Audio Dent 2"; Thumbnail="unfiltered_dent_2"; Slug="unfiltered_audio_dent_2"}
    @{Name="Unfiltered Audio Fault"; Thumbnail="unfiltered_fault"; Slug="unfiltered_audio_fault"}
    @{Name="Unfiltered Audio G8"; Thumbnail="unfiltered_g8"; Slug="unfiltered_audio_g8"}
    @{Name="Unfiltered Audio Indent 2"; Thumbnail="unfiltered_indent_2"; Slug="unfiltered_audio_indent_2"}
    @{Name="Unfiltered Audio Instant Delay"; Thumbnail="unfiltered_instant_delay"; Slug="unfiltered_audio_instant_delay"}
    @{Name="Unfiltered Audio LION"; Thumbnail="unfiltered_lion"; Slug="unfiltered_audio_lion"}
    @{Name="Unfiltered Audio lo-fi-af"; Thumbnail="unfiltered_lofiaf"; Slug="unfiltered_audio_lo-fi-af"}
    @{Name="Unfiltered Audio Needlepoint"; Thumbnail="mixland_needlepoint"; Slug="mixland_needlepoint"}
    @{Name="Unfiltered Audio Sandman"; Thumbnail="unfiltered_sandman"; Slug="unfiltered_audio_sandman"}
    @{Name="Unfiltered Audio Sandman Pro"; Thumbnail="unfiltered_sandman_pro"; Slug="unfiltered_audio_sandman_pro"}
    @{Name="Unfiltered Audio Silo"; Thumbnail="unfiltered_silo"; Slug="unfiltered_audio_silo"}
    @{Name="Unfiltered Audio SpecOps"; Thumbnail="unfiltered_specops"; Slug="unfiltered_audio_specops"}
    @{Name="Unfiltered Audio Tails"; Thumbnail="unfiltered_tails"; Slug="unfiltered_audio_tails"}
    @{Name="Unfiltered Audio Triad"; Thumbnail="karanyi_triad"; Slug="karanyi_sounds_triad"}
    @{Name="Unfiltered Audio Zip"; Thumbnail="unfiltered_zip"; Slug="unfiltered_audio_zip"}

    # Vertigo
    @{Name="Vertigo VSC-2"; Thumbnail="vertigo_vsc2"; Slug="vertigo_vsc-2"}
    @{Name="Vertigo VSM-3"; Thumbnail="vertigo_vsm3"; Slug="vertigo_vsm-3"}
    @{Name="Vertigo VSS-2"; Thumbnail="vertigo_vss2"; Slug="vertigo_vss-2"}
)

# Check which thumbnails exist
$thumbnailsPath = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$existingThumbnails = Get-ChildItem $thumbnailsPath -Filter "*.png" | ForEach-Object { $_.BaseName }

$missing = @()
$found = @()

foreach ($plugin in $paPlugins) {
    if ($existingThumbnails -contains $plugin.Thumbnail) {
        $found += $plugin
    } else {
        $missing += $plugin
    }
}

Write-Host "=== FOUND THUMBNAILS ===" -ForegroundColor Green
foreach ($p in $found) {
    Write-Host "  $($p.Name) -> $($p.Thumbnail).png"
}

Write-Host ""
Write-Host "=== MISSING THUMBNAILS ===" -ForegroundColor Red
foreach ($p in $missing) {
    Write-Host "  $($p.Name) -> $($p.Thumbnail).png (need to download)"
}

Write-Host ""
Write-Host "Found: $($found.Count), Missing: $($missing.Count)"

# Output missing thumbnails to a file for further processing
$missing | ForEach-Object { "$($_.Name)|$($_.Thumbnail)|$($_.Slug)" } | Out-File "C:\Users\charl\PluginAllianceLauncher\missing_thumbnails.txt"
