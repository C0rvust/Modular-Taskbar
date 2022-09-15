$Shortcuts="$($RmAPI.VariableStr("@"))Modules\Shortcut\Include\Shortcuts"

function GenerateItemInc { # Only accepts .lnk files, all other file types are ignored (but will still be copied into the folder)
    $Dest="$($RmAPI.VariableStr("@"))Modules\Shortcut\Include\Item.inc"

    $Count=Get-ChildItem $Shortcuts | Where-Object Name -Match "lnk$" | Sort-Object
    $Param=$($Count | ForEach-Object {$_.BaseName}) -join "|"
    $Saved=$RmAPI.OptionStr("Param")
    if($Saved -ne $Param) {
        $RMAPI.Bang("!WriteKeyValue $($RmAPI.GetMeasureName()) `"`"`"Param`"`"`" `"`"`"$Param`"`"`" `"`"`"$($RmAPI.VariableStr("@") + "Modules\Shortcut\Shortcut.inc")`"`"`"")
        $RMAPI.Bang("!WriteKeyValue Variables `"`"`"Module.Shortcut.GennedItemCount`"`"`" `"`"`"$($Count.length)`"`"`" `"`"`"$($RmAPI.VariableStr("RootConfigPath") + "PopUp\Shortcut_PopUp.ini")`"`"`"")
        $Content=""
        Get-ChildItem $Shortcuts -File | Where-Object Name -Match "lnk$" | ForEach-Object {
            $Content += @"
[$($_.BaseName)]
MeterStyle=Module.Shortcut.StyleInfoString
Meter=String
Text=$($_.BaseName -replace '.*?-','')
LeftMouseUpAction=[`"#@#Modules\Shortcut\Include\Shortcuts\$($_.Name)`"]

"@
        }
        $Content | Out-File $Dest
    }
}

function RemoveItem {
    Param([String] $Name)

    Remove-Item "$Shortcuts\$Name.lnk" | Out-Null
    GenerateItemInc
    $RMAPI.Bang("!Refresh `"`"`"$($RmAPI.VariableStr("RootConfig") + "\PopUp")`"`"`"")
}

GenerateItemInc # Attempts to generate item inc on refresh