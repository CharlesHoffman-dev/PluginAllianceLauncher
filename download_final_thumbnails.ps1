# Download final missing thumbnail images

$outputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$baseUrl = "https://www.plugin-alliance.com/cdn/shop/files/"

$missingImages = @{
    "ampeg_svtvr_classic" = "productimage-300439_cf6e9c57-eddc-40b0-af64-192174df03d0.png"
}

Write-Host "Downloading final thumbnails to $outputDir" -ForegroundColor Cyan

foreach ($entry in $missingImages.GetEnumerator()) {
    $name = $entry.Key
    $file = $entry.Value
    $outputFile = Join-Path $outputDir "$name.png"

    if (Test-Path $outputFile) {
        Write-Host "Skipping $name (already exists)" -ForegroundColor Gray
        continue
    }

    $url = $baseUrl + $file
    Write-Host "Downloading $name..." -ForegroundColor Yellow

    try {
        Invoke-WebRequest -Uri $url -OutFile $outputFile -TimeoutSec 30
        $fileSize = (Get-Item $outputFile).Length
        Write-Host "  Downloaded ($fileSize bytes)" -ForegroundColor Green
    } catch {
        Write-Host "  Failed: $($_.Exception.Message)" -ForegroundColor Red
    }
}

Write-Host "Done!" -ForegroundColor Cyan
