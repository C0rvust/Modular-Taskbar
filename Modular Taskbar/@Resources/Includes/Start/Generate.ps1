$path = $RmAPI.VariableStr("@") + "\Includes\Start\Shortcuts"
$index = 1
$content = ""

Get-ChildItem $path -File | Where-Object Name -Match "lnk$" | ForEach-Object {
    $content += @"
[Module.Start.Item.$($index)]
MeterStyle=Module.Start.StyleItemString
Meter=String
Text=$($_.BaseName -replace '.*?-','')
LeftMouseUpAction=[`"#@#Includes\Start\Shortcuts\$($_.Name)`"]

"@
    $index++
}

$out = $RmAPI.VariableStr("@") + "\Includes\Start\Shortcut.inc"
$content | Out-File $out

function Update {
    return (Get-ChildItem $path).Count
}