Add-Type -AssemblyName System.Drawing

$baseUrl = "https://www.plugin-alliance.com/cdn/shop/files/"
$outputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$targetWidth = 400

# Corrected image URL mappings (filename -> url suffix)
$imageUrls = @{
    # NEOLD
    "neold_rz062" = "NEOLD_RZ062_GUI.jpg"
    "neold_v76u73" = "V76U73_GUI.png"
    "neold_warble" = "WARBLE_GUI.png"
    "neold_big_al" = "BIG_AL_GUI.png"
    "neold_u17" = "U17_GUI.png"
    "neold_u2a" = "U2A_GUI.png"
    "neold_wunderlich" = "WUNDERLICH_GUI.png"
    "neold_oldtimer" = "OLDTIMER_GUI.png"

    # Brainworx bx_ Console Channel Strips
    "bx_console_ssl_4000_e" = "productimage-300373_f5942771-0897-4d7f-8955-7795f96295a3.png"
    "bx_console_ssl_4000_g" = "productimage-300374_b2b44f03-8e78-4736-a7b6-ef8820665d5b.png"
    "bx_console_ssl_9000_j" = "productimage-300478_3bcb16b8-3645-45f3-9b99-4d738a5a344e.png"
    "bx_console_n" = "productimage-300345_47021cba-5c15-4974-aa89-ff492a889fed.png"
    "bx_console_focusrite_sc" = "productimage-300402_e0b1d7b5-7b9b-466c-a224-1547f722b0f0.png"
    "bx_console_amek_9099" = "productimage-300983.png"
    "bx_console_amek_200" = "productimage-301049.png"

    # Brainworx bx_ Mastering
    "bx_masterdesk" = "productimage-300383_a2601b0c-d04f-4feb-9a7c-5af3dbf5d472.png"
    "bx_masterdesk_pro" = "productimage-300899_7d13d505-a4ec-4fd8-ac5b-bee1432f5ddc.png"
    "bx_masterdesk_true_peak" = "productimage-300643_9defaedc-3211-4098-970a-3985949b013f.png"
    "bx_digital_v3" = "productimage-300214_d6cd321d-80bd-4c41-bd6a-4b05198f3e30.png"
    "bx_hybrid_v2" = "productimage-300097_74b90f56-7fc4-4c94-86f1-cdbb4ad2d724.png"

    # Brainworx bx_ Dynamics
    "bx_townhouse" = "productimage-300365_671a1cf2-d3e3-4a18-a54a-0fe613fbd987.png"
    "bx_opto" = "productimage-300149_0a8c4324-5cc3-45e3-b62e-9bea84ff8323.png"
    "bx_limiter" = "productimage-300085_6cee96b9-0f1f-4499-9d6d-81bea3ca9da3.png"
    "bx_limiter_true_peak" = "productimage-300552_1d635dc7-5e4a-4717-8b41-3706351c5683.png"
    "bx_glue" = "productimage-300988_dbbe8b26-3676-473a-8766-8a51308d591f.png"

    # Brainworx bx_ EQ/Processing
    "bx_subsynth" = "productimage-300257_ba2617f8-37e4-45c9-881c-6dab16468e30.png"
    "bx_saturator_v2" = "productimage-300129_803f3461-6ee8-423c-840c-3569bca891c0.png"
    "bx_refinement_v3" = "productimage-301160.png"
    "bx_dyneq_v2" = "productimage-300008_23571076-2caa-4b69-809a-1d234d32eb18.png"
    "bx_aura" = "productimage-301243.png"

    # Brainworx Guitar
    "bx_rockrack_v3" = "productimage-300244_20a2ee7e-c696-432e-ae2f-641cd41b7723.png"

    # Bettermaker
    "bettermaker_mastering_compressor" = "productimage-301237.png"
    "bettermaker_bus_compressor" = "productimage-300973_b69e8739-4394-49f1-bb2d-c4df85dd2bcb.png"
    "bettermaker_c502v" = "productimage-301146_2bdf41cf-d9d8-4294-8d8a-270560c4cc74.png"
    "bettermaker_bm60" = "productimage-301030_a53ec7b3-bdb8-4f9f-847c-c4ae1c766f78.png"
    "bettermaker_eq232d" = "productimage-300421_fef58d06-aa5f-4482-8b6a-58c56f82a79a.png"
    "bettermaker_passive_equalizer" = "productimage-301098.png"

    # Shadow Hills
    "shadow_hills_mastering_compressor" = "productimage-300081_a9a2e16c-5b2f-47ae-9537-3073a3ed18f9.png"

    # elysia
    "elysia_alpha_compressor" = "productimage-301253.png"
    "elysia_mpressor" = "productimage-300018_1635b21e-7b69-439c-ba1b-37ce6236bbfc.png"
    "elysia_phils_cascade" = "productimage-300369_a8076339-2084-4197-a944-dbbf15f01efd.png"

    # SPL
    "spl_iron" = "productimage-300386_5a609eb0-4eb3-4780-82b2-2bc2077c677b.png"
    "spl_passeq" = "productimage-300014_41e6334f-ea81-4115-bcb2-ce021a984aae.png"
    "spl_vitalizer_mk3t" = "productimage-301205.png"
    "spl_transient_designer_plus" = "productimage-300187_f60f1190-959c-48af-b3e7-0d907bc344e9.png"

    # Lindell Audio
    "lindell_80_series" = "productimage-300475_de30a79f-c507-4963-9d9f-b09b50e2b91b.png"
    "lindell_mu66" = "productimage-301012_2e708038-ee2b-4bc1-97db-a55966cf2523.png"
    "lindell_te100" = "productimage-300236_5566d6a5-698c-439c-82d1-35e8137524b4.png"

    # ADPTR
    "adptr_hype" = "productimage-300999_56d6bbd4-8d7d-408d-845b-51ae21f9a76c.png"

    # Swivel
    "swivel_spread" = "productimage-301296.png"
    "swivel_the_sauce" = "productimage-301290.png"
    "swivel_knocktonal" = "productimage-301298.png"
    "swivel_click_boom" = "productimage-301299.png"
    "swivel_bde" = "productimage-301297.png"
    "swivel_hitstrip" = "productimage-301300.png"

    # Cut Classic
    "cut_classic_high_flyer" = "productimage-301210.png"

    # Knif
    "knif_soma" = "productimage-300517_d93d3d4e-3d3c-42e4-9694-c3bea8252618.png"
    "knif_knifonium" = "productimage-300471_d66727a9-586b-47d0-97ed-9f176c296269.png"

    # Noveltech
    "noveltech_character" = "productimage-300068_1e2c9ec6-8b04-49e6-ac20-bfbc963d0481.png"
    "noveltech_vocal_enhancer" = "productimage-300088_7acfec5d-912a-48ca-9ebd-fe07e741e6e1.png"

    # Fiedler
    "fiedler_stage" = "productimage-300309_43e9ff7b-b505-4425-8a9d-c4b6954b2b06.png"
    "fiedler_spatial_creator" = "productimage-300904_d1c9b86a-5c99-4a62-b809-5790a753b57b.png"
    "fiedler_splat" = "productimage-301101_81645304-1805-44fb-86a9-f0a6f07eaa01.png"

    # DS Audio
    "ds_audio_tantra_2" = "productimage-300554_8ace881a-39b6-471d-9a28-fe0cf0673018.png"
    "ds_audio_thorn" = "productimage-300401_98febeee-bda8-4fe9-b1c6-ba8fa2d7eff9.png"

    # Pro Audio DSP
    "pro_audio_dsp_dsm_v3" = "productimage-300403_9bb5d6c3-5d94-46d0-86c4-f8c86bd9a7c3.png"

    # Looptrotter
    "looptrotter_sa2rate_2" = "productimage-300629_fe5b41c8-37fd-4fa6-a20e-831a09f0f481.png"

    # LTL
    "louder_than_liftoff_silver_bullet" = "productimage-300952_ae72f079-fed9-499f-a15f-c00e2d9fe988.png"
    "ltl_chop_shop" = "productimage-300389_fe0214bf-29af-44d3-b929-cfcd64b7e1de.png"

    # TOMO
    "tomo_lisa" = "productimage-300635_b22c3561-6e15-4c4d-ad52-4ac96b0e9d92.png"

    # Harris Doyle
    "harris_doyle_natalus" = "productimage-300852_e65cdbad-a648-40b8-88e6-4fb77bb3a976.png"

    # Mixland
    "mixland_the_oven" = "productimage-300653_a16226c9-f5b9-4820-92c2-4240b4adfa66.png"
    "mixland_needlepoint" = "productimage-300663_e9b251cc-820d-41e8-86e9-f487dd48e022.png"
    "mixland_vac_attack" = "productimage-300928_d5c2191a-2e0f-4cec-8c0d-552d33722598.png"

    # Karanyi
    "karanyi_triad" = "productimage-300393_2300346d-45cc-4bd1-997d-10b1946db4e8.png"
    "karanyi_wavesurfer" = "productimage-301155_0af05e64-9d77-47bb-a38f-51bca26c4045.png"

    # HEARS
    "hears_perfection" = "productimage-301331.png"

    # Kiive
    "kiive_tape_face" = "productimage-300883_ea7d242f-aca6-4785-8ee4-155cbfbd9fd2.png"

    # Maor Appelbaum
    "maor_hawkeye" = "productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png"

    # Chandler
    "chandler_gav19t" = "productimage-300114_a26c0820-3eb1-42f1-b72c-81005a988f27.png"

    # Dangerous
    "dangerous_bax_eq" = "productimage-300095_e8339764-5fb2-4554-b4d2-14fee7d1b140.png"

    # Purple Audio
    "purple_audio_mc77" = "productimage-300417_8eceb4b6-1550-4496-aa2a-45aadb2e1c92.png"

    # Unfiltered Audio
    "unfiltered_battalion" = "productimage-301002_746463f1-14eb-4f80-83c3-5e524df6ffb4.png"

    # A/DA
    "ada_flanger" = "productimage-300356_b75930af-e197-461f-a776-d0b40f6fbfd7.png"

    # Acme
    "acme_opticom_xla3" = "productimage-300211_137be455-e2d4-4035-9eee-f1ef6d7a3a15.png"

    # Millennia
    "millennia_tcl2" = "productimage-300143_3c0a78f2-31be-436b-ab39-a877c73d8694.png"
}

$downloaded = 0
$failed = 0

foreach ($item in $imageUrls.GetEnumerator()) {
    $filename = $item.Key
    $urlSuffix = $item.Value
    $url = $baseUrl + $urlSuffix
    $outputPath = Join-Path $outputDir "$filename.png"
    $tempPath = Join-Path $outputDir "$filename.temp.png"

    Write-Host "Downloading $filename..." -NoNewline

    try {
        # Download
        Invoke-WebRequest -Uri $url -OutFile $tempPath -UseBasicParsing -ErrorAction Stop

        # Resize
        $img = [System.Drawing.Image]::FromFile($tempPath)
        $ratio = $targetWidth / $img.Width
        $newWidth = $targetWidth
        $newHeight = [int]($img.Height * $ratio)

        $bmp = New-Object System.Drawing.Bitmap($newWidth, $newHeight)
        $g = [System.Drawing.Graphics]::FromImage($bmp)
        $g.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $g.DrawImage($img, 0, 0, $newWidth, $newHeight)

        $img.Dispose()
        $g.Dispose()

        $bmp.Save($outputPath, [System.Drawing.Imaging.ImageFormat]::Png)
        $bmp.Dispose()

        Remove-Item $tempPath -Force

        Write-Host " OK ($newWidth x $newHeight)" -ForegroundColor Green
        $downloaded++
    }
    catch {
        Write-Host " FAILED: $($_.Exception.Message)" -ForegroundColor Red
        $failed++
        if (Test-Path $tempPath) { Remove-Item $tempPath -Force }
    }
}

Write-Host ""
Write-Host "Downloaded: $downloaded" -ForegroundColor Green
Write-Host "Failed: $failed" -ForegroundColor Red
