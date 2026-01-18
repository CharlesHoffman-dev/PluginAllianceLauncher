# Download missing thumbnail images from Plugin Alliance
# Run this script to fetch product images for plugins without thumbnails

$outputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$baseUrl = "https://www.plugin-alliance.com/cdn/shop/files/"

# Create output directory if it doesn't exist
if (!(Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir -Force | Out-Null
}

# Missing images with their CDN filenames
$missingImages = @{
    # SPL
    "spl_attacker_plus" = "productimage-300303_cf082f7d-27b1-4317-874f-3732caec074d.png"
    "spl_deverb_plus" = "productimage-300305_8082d009-6270-4264-84f8-5801a3dad97e.png"
    "spl_drumxchanger" = "productimage-300020_b30bc9e9-b50a-4559-9e06-353e837f36fd.png"
    "spl_eq_ranger_plus" = "productimage-300186_672ca1e9-1e63-43ec-9c48-8a7cdb66b8d0.png"
    "spl_moverb_plus" = "productimage-300307_b8dc9794-488c-4ffc-af14-deaa77633c9e.png"
    "spl_hawkeye" = "productimage-300400_d705cd7c-7087-4680-914b-646d0b0fe801.png"
    "spl_pq" = "productimage-300682_e9888535-781e-4df8-ad82-419b0fddb790.png"
    "spl_free_ranger" = "SPL_ranger_free.png"

    # elysia
    "elysia_niveau_filter" = "productimage-300019_b7f57860-ad8c-4188-b20c-645bd74e67c5.png"
    "elysia_phils_cascade" = "productimage-300369_a8076339-2084-4197-a944-dbbf15f01efd.png"

    # Brainworx bx_ pedals/effects
    "bx_blackdist2" = "productimage-300219.png"
    "bx_bluechorus2" = "productimage-300165.png"
    "bx_greenscreamer" = "productimage-300171_5a62cd13-d131-4b10-bfdc-0b354821f6e0.png"
    "bx_distorange" = "productimage-300196.png"
    "bx_yellowdrive" = "productimage-300197_69f8a5e2-6d60-40b9-aea2-8da18dbe5671.png"
    "bx_metal2" = "productimage-300208.png"
    "bx_megasingle" = "productimage-300161_5c17c827-8c0c-468b-aa25-f395ca06499f.png"
    "bx_tuner" = "productimage-300098.png"
    "bx_meter" = "productimage-300042.png"
    "bx_solo" = "bx_solo-gui-main-image.jpg"
    "bx_subfilter" = "productimage-300314.png"
    "bx_shredspread" = "productimage-300037.png"

    # Millennia
    "millennia_tcl2" = "productimage-300143_3c0a78f2-31be-436b-ab39-a877c73d8694.png"

    # Unfiltered Audio
    "unfiltered_battalion" = "productimage-301002_746463f1-14eb-4f80-83c3-5e524df6ffb4.png"
    "unfiltered_instant_delay" = "productimage-300316_ce1f07a0-722d-4d3a-a1bf-b43231b62808.png"
    "unfiltered_lofiaf" = "productimage-300492_3815c462-512d-438e-a1f7-9796ef5e7296.png"
    "unfiltered_bass_mint" = "productimage-300490_3df7645c-3a98-4c49-93be-3d4a9700d3e5.png"

    # Kiive
    "kiive_tape_face" = "productimage-300883_ea7d242f-aca6-4785-8ee4-155cbfbd9fd2.png"
    "kiive_xtcomp" = "productimage-300998.png"

    # fiedler audio
    "fiedler_splat" = "productimage-301101_81645304-1805-44fb-86a9-f0a6f07eaa01.png"

    # Karanyi
    "karanyi_wavesurfer" = "productimage-301155_0af05e64-9d77-47bb-a38f-51bca26c4045.png"

    # Mixland
    "mixland_vac_attack" = "productimage-300928_d5c2191a-2e0f-4cec-8c0d-552d33722598.png"

    # Cut Classic
    "cut_classic_high_flyer" = "productimage-301210.png"

    # THX
    "thx_spatial_creator" = "productimage-300904_d1c9b86a-5c99-4a62-b809-5790a753b57b.png"

    # Bettermaker
    "bettermaker_bm60" = "productimage-301030_a53ec7b3-bdb8-4f9f-847c-c4ae1c766f78.png"
    "bettermaker_eq232d" = "productimage-300421_fef58d06-aa5f-4482-8b6a-58c56f82a79a.png"

    # ADA
    "ada_std1" = "productimage-300258_e4416d1c-8f75-4683-8195-cc03447e59a0.png"

    # LTL (uses same as hears_chop_shop)
    "ltl_chop_shop" = "productimage-300389_fe0214bf-29af-44d3-b929-cfcd64b7e1de.png"
}

Write-Host "Downloading missing thumbnails to $outputDir" -ForegroundColor Cyan
Write-Host ""

$count = 0
$total = $missingImages.Count
$downloaded = 0
$failed = 0
$skipped = 0

foreach ($entry in $missingImages.GetEnumerator()) {
    $count++
    $name = $entry.Key
    $file = $entry.Value
    $outputFile = Join-Path $outputDir "$name.png"

    if (Test-Path $outputFile) {
        Write-Host "[$count/$total] Skipping $name (already exists)" -ForegroundColor Gray
        $skipped++
        continue
    }

    $url = $baseUrl + $file
    Write-Host "[$count/$total] Downloading $name..." -ForegroundColor Yellow
    Write-Host "  URL: $url" -ForegroundColor DarkGray

    try {
        # Download file
        Invoke-WebRequest -Uri $url -OutFile $outputFile -TimeoutSec 30

        if (Test-Path $outputFile) {
            $fileSize = (Get-Item $outputFile).Length
            Write-Host "  Downloaded successfully ($fileSize bytes)" -ForegroundColor Green
            $downloaded++
        } else {
            Write-Host "  File not created" -ForegroundColor Red
            $failed++
        }
    } catch {
        Write-Host "  Failed: $($_.Exception.Message)" -ForegroundColor Red
        $failed++

        # Remove partial file if it exists
        if (Test-Path $outputFile) {
            Remove-Item $outputFile -Force
        }
    }
}

Write-Host ""
Write-Host "Download complete!" -ForegroundColor Cyan
Write-Host "  Downloaded: $downloaded" -ForegroundColor Green
Write-Host "  Failed: $failed" -ForegroundColor $(if ($failed -gt 0) { "Red" } else { "Green" })
Write-Host "  Skipped: $skipped" -ForegroundColor Gray
