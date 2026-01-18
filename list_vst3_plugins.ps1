# List all VST3 plugins in the common folder
$vst3Path = "C:\Program Files\Common Files\VST3"

Get-ChildItem $vst3Path -Filter "*.vst3" |
    Where-Object { $_.Name -ne "Plugin Alliance Launcher.vst3" } |
    ForEach-Object { $_.BaseName } |
    Sort-Object
