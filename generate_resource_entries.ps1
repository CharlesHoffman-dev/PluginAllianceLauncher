$files = Get-ChildItem "C:\Users\charl\PluginAllianceLauncher\Resources\Thumbnails"

foreach ($file in $files) {
    $id = "img_" + ($file.BaseName -replace '[^a-zA-Z0-9]','_')
    $entry = '        <FILE id="' + $id + '" name="' + $file.Name + '" compile="0" resource="1" file="Resources/Thumbnails/' + $file.Name + '"/>'
    Write-Output $entry
}
