# Resize downloaded images to thumbnail size
Add-Type -AssemblyName System.Drawing

$thumbnailsDir = "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"
$targetWidth = 160
$targetHeight = 100
$maxFileSize = 50000  # 50KB threshold - files larger than this need resizing

Write-Host "Checking for oversized thumbnails in $thumbnailsDir" -ForegroundColor Cyan
Write-Host ""

$resized = 0
$skipped = 0

Get-ChildItem $thumbnailsDir -Filter "*.png" | ForEach-Object {
    $file = $_
    $fileSize = $file.Length

    # Only resize if file is larger than threshold (likely full-size image)
    if ($fileSize -gt $maxFileSize) {
        Write-Host "Resizing $($file.Name) ($([math]::Round($fileSize/1024))KB)..." -ForegroundColor Yellow

        try {
            $img = [System.Drawing.Image]::FromFile($file.FullName)

            $srcRatio = $img.Width / $img.Height
            $targetRatio = $targetWidth / $targetHeight

            if ($srcRatio -gt $targetRatio) {
                $newWidth = $targetWidth
                $newHeight = [int]($targetWidth / $srcRatio)
            } else {
                $newHeight = $targetHeight
                $newWidth = [int]($targetHeight * $srcRatio)
            }

            $thumb = New-Object System.Drawing.Bitmap($newWidth, $newHeight)
            $graphics = [System.Drawing.Graphics]::FromImage($thumb)
            $graphics.InterpolationMode = [System.Drawing.Drawing2D.InterpolationMode]::HighQualityBicubic
            $graphics.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::HighQuality
            $graphics.DrawImage($img, 0, 0, $newWidth, $newHeight)

            $graphics.Dispose()
            $img.Dispose()

            # Save to temp file first
            $tempFile = $file.FullName + ".tmp"
            $thumb.Save($tempFile, [System.Drawing.Imaging.ImageFormat]::Png)
            $thumb.Dispose()

            # Replace original with resized
            Remove-Item $file.FullName -Force
            Move-Item $tempFile $file.FullName -Force

            $newSize = (Get-Item $file.FullName).Length
            Write-Host "  Resized to ${newWidth}x${newHeight} ($([math]::Round($newSize/1024))KB)" -ForegroundColor Green
            $resized++
        } catch {
            Write-Host "  Failed: $($_.Exception.Message)" -ForegroundColor Red
        }
    } else {
        $skipped++
    }
}

Write-Host ""
Write-Host "Done! Resized: $resized, Already small: $skipped" -ForegroundColor Cyan
