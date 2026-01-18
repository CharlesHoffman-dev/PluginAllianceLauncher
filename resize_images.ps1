Add-Type -AssemblyName System.Drawing

$inputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\PluginImages"
$outputDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"

$targetWidth = 160
$targetHeight = 100

if (-not (Test-Path $outputDir)) {
    New-Item -ItemType Directory -Path $outputDir | Out-Null
}

$files = Get-ChildItem -Path $inputDir -File
$count = 0
$total = $files.Count

foreach ($file in $files) {
    $count++
    $outputFile = Join-Path $outputDir ($file.BaseName + ".png")

    Write-Host "[$count/$total] Resizing $($file.Name)..."

    try {
        $img = [System.Drawing.Image]::FromFile($file.FullName)

        # Calculate aspect-fit dimensions
        $srcRatio = $img.Width / $img.Height
        $targetRatio = $targetWidth / $targetHeight

        if ($srcRatio -gt $targetRatio) {
            # Image is wider - fit to width
            $newWidth = $targetWidth
            $newHeight = [int]($targetWidth / $srcRatio)
        } else {
            # Image is taller - fit to height
            $newHeight = $targetHeight
            $newWidth = [int]($targetHeight * $srcRatio)
        }

        $thumb = New-Object System.Drawing.Bitmap($newWidth, $newHeight)
        $graphics = [System.Drawing.Graphics]::FromImage($thumb)
        $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
        $graphics.DrawImage($img, 0, 0, $newWidth, $newHeight)

        $thumb.Save($outputFile, [System.Drawing.Imaging.ImageFormat]::Png)

        $graphics.Dispose()
        $thumb.Dispose()
        $img.Dispose()
    } catch {
        Write-Host "  Failed: $_"
    }
}

Write-Host "Done! Resized images saved to $outputDir"
