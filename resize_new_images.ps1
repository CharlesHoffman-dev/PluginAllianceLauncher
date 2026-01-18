Add-Type -AssemblyName System.Drawing

$images = @(
    @{Input="C:\Users\charl\PluginAllianceLauncher\Resources\PluginImages\adptr_hype.png"; Output="C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails\adptr_hype.png"},
    @{Input="C:\Users\charl\PluginAllianceLauncher\Resources\PluginImages\bettermaker_c502v.png"; Output="C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails\bettermaker_c502v.png"}
)

$targetWidth = 160
$targetHeight = 100

foreach ($item in $images) {
    $img = [System.Drawing.Image]::FromFile($item.Input)

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
    $graphics.DrawImage($img, 0, 0, $newWidth, $newHeight)
    $thumb.Save($item.Output, [System.Drawing.Imaging.ImageFormat]::Png)

    $graphics.Dispose()
    $thumb.Dispose()
    $img.Dispose()

    Write-Host "Resized: $($item.Output)"
}

Write-Host "Done!"
