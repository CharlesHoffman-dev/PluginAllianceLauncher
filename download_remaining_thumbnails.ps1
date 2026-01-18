# Download remaining missing thumbnail images from Plugin Alliance

$outputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$baseUrl = "https://www.plugin-alliance.com/cdn/shop/files/"

# Remaining missing images
$missingImages = @{
    # Lindell Audio
    "lindell_mu66" = "productimage-301012_2e708038-ee2b-4bc1-97db-a55966cf2523.png"
    "lindell_6x500" = "productimage-300177_c6d72330-7dee-4c62-8c18-e10eb82e96ee.png"
    "lindell_7x500" = "productimage-300178_8bb5104f-8127-409a-89ec-25840ed22e19.png"
    "lindell_pex500" = "productimage-300179_fa86a3d6-3911-480f-9f7d-85737184eaca.png"
    "lindell_te100" = "productimage-300236_5566d6a5-698c-439c-82d1-35e8137524b4.png"
    "lindell_902_deesser" = "productimage-300626_a2edb61f-a1c5-400e-96cb-656bbbda8fa9.png"
    "lindell_mbc" = "productimage-300737_d0202dc3-2fc5-432e-b972-f3b6edc13dbd.png"
    "lindell_sbc" = "productimage-300627_3efa1f27-cc48-46d3-a800-a417c51b1e5c.png"

    # Kiive
    "kiive_xtcomp" = "300998.png"

    # HEARS (uses bettermaker_perfection image)
    "hears_perfection" = "productimage-301331.png"
}

Write-Host "Downloading remaining missing thumbnails to $outputDir" -ForegroundColor Cyan
Write-Host ""

$count = 0
$total = $missingImages.Count
$downloaded = 0
$failed = 0

foreach ($entry in $missingImages.GetEnumerator()) {
    $count++
    $name = $entry.Key
    $file = $entry.Value
    $outputFile = Join-Path $outputDir "$name.png"

    if (Test-Path $outputFile) {
        Write-Host "[$count/$total] Skipping $name (already exists)" -ForegroundColor Gray
        continue
    }

    $url = $baseUrl + $file
    Write-Host "[$count/$total] Downloading $name..." -ForegroundColor Yellow
    Write-Host "  URL: $url" -ForegroundColor DarkGray

    try {
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

        if (Test-Path $outputFile) {
            Remove-Item $outputFile -Force
        }
    }
}

Write-Host ""
Write-Host "Done! Downloaded: $downloaded, Failed: $failed" -ForegroundColor Cyan
