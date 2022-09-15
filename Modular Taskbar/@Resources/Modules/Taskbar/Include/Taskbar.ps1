$MeterPrefix="Module.Taskbar.Icon."
$RootConfig=$RmApi.VariableStr("RootConfig")
$RootConfigPath=$RmApi.VariableStr("RootConfigPath")

function ReturnMaxProgramCount { # Retrieves the #ProgramCount# Variable
    return ($RmAPI.Variable("Module.Taskbar.ProgramCount",0))
}

function ReturnStockIcons { # Retrieves an array of the avaliable image files in the path specified by #StockIconPath#
    $Path=$RMAPI.VariableStr("Module.Taskbar.StockIconPath")
    $List=@()
    Get-ChildItem $Path -File | Where-Object Name -Match "png$|jpg$" | ForEach-Object {
        $List+=$_.BaseName
    }
    Return $List
}

function ReturnProgramName { # Returns the ProgramName of a particular program
    Param([int] $ID)
    return ($RmAPI.VariableStr("ProgramName$ID"))
}
function ReturnProgramCount { # Returns the number of children (instances) of a particular program
    Param([int] $ID)
    return ($RmAPI.VariableStr("ProgramsCount$ID"))
}

function ReturnIsProgramPinned { # Returns the pinned status of a particular program
    Param([int] $ID)
    $RMAPI.Bang("!CommandMeasure Module.Taskbar.ProgramOptions `"`"`"SetVariable|Module.Taskbar.IsPinned|IsPinned|$($ID)`"`"`" ")
    $IsPinned=$RMAPI.Variable("Module.Taskbar.IsPinned",0) # 1 if pinned, 0 if unpinned
    Return $IsPinned
}

function RunGetIcons { # Runs the GetIcon.exe executable to get icon images of all currently running processes
    $GetIconsPath="$($RMAPI.VariableStr("Module.Taskbar.DependenciesPath"))\getIcons.exe"
    $Pinned=$RmAPI.VariableStr("Module.Taskbar.AddDep")
    & "$GetIconsPath" "$Pinned" | Out-Null
}
function SetProgramPin { # Toggle the pinned status of a particularp program
    Param([int] $ID)
    $IsPinned=ReturnIsProgramPinned($ID) 
    If($IsPinned -eq "1"){
        $RMAPI.Bang("!CommandMeasure Module.Taskbar.ProgramOptions `"`"`"UnpinItem|$($ID)`"`"`" ")
    }
    Else{
        $RMAPI.Bang("!CommandMeasure Module.Taskbar.ProgramOptions `"`"`"PinItem|$($ID)`"`"`" ")
    }
}

function SetProgramImage { # Set the icon image of a particular program
    Param([Int] $ID)

    $ProgramName=ReturnProgramName($ID)
    $StockIcons=ReturnStockIcons
    $StockIconPath=$RmAPI.VariableStr("Module.Taskbar.StockIconPath")
    $GenIconPath="$($RmAPI.VariableStr("Module.Taskbar.DependenciesPath"))\Icons"

    If($ProgramName -Match "Empty") { # Note: having "" instead of `"`"`"`"`"`" breaks because of the lack of magic quotes (as expected)
        $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageName `"`"`"`"`"`" ")
    }
    Else {
        If($StockIcons -clike $ProgramName){ # if there exist a stock icon, then use the stock icon instead, if not use the generated one
            $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageName `"`"`"$StockIconPath\$ProgramName.png`"`"`" ")
        }
        Else{
            $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageName `"`"`"$GenIconPath\$ProgramName.png`"`"`" ")
        }
    }
}

function SetProgramMouseAction { # Set the relevant mouse actions of a particular program
    Param([Int] $ID)

    $ProgramName=ReturnProgramName($ID)
    $ProgramOption="Module.Taskbar.ProgramOptions"
    $PSRM=$RmAPI.GetMeasureName()

    switch($ProgramName) {
        "Empty" { # Not in use
            $RmAPI.Bang("!ClearMouseAction $MeterPrefix$ID `"`"`"LeftMouseUpAction|MouseOverAction|MouseLeaveAction|MiddleMouseUpAction|RightMouseUpAction`"`"`" ")
        }
        default {
            $RmAPI.Bang("!EnableMouseAction $MeterPrefix$ID `"`"`"LeftMouseUpAction|MouseOverAction|MouseLeaveAction|MiddleMouseUpAction|RightMouseUpAction`"`"`" ")

            $ProgramCount=ReturnProgramCount($ID)

            switch ($ProgramCount) {
                0 {
                    $RmAPI.Bang("!SetOption $MeterPrefix$ID LeftMouseUpAction `"`"`"[!CommandMeasure $($ProgramOption) StartNew|$ID]`"`"`" ")
                }
                default {
                    $RmAPI.Bang("!SetOption $MeterPrefix$ID LeftMouseUpAction `"`"`"[!CommandMeasure $($ProgramOption) ToFront|Main|$ID]`"`"`" ")
                }
            }
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseOverAction `"`"`"!CommandMeasure $($PSRM) `"`"`"MouseOverAction $ID`"`"`"`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseLeaveAction `"`"`"!CommandMeasure $($PSRM) `"`"`"MouseLeaveAction $ID`"`"`"`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MiddleMouseUpAction `"`"`"!CommandMeasure $($ProgramOption) `"`"`"StartNew|$ID`"`"`"`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID RightMouseUpAction `"`"`"!CommandMeasure $($PSRM) `"`"`"SetProgramPin $ID`"`"`"`"`"`" ")
        }
    }
}

function MouseOverAction {
    Param([Int] $ID)

    # MouseOver Animation
    $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageTint `"`"`"255,255,255`"`"`" ")
    $RmAPI.Bang("!UpdateMeter $MeterPrefix$ID")

    $ProgramCount=ReturnProgramCount($ID)
    if($ProgramCount -gt 0){
        # Set PopUp coordinates
        $RMAPI.Bang("!CommandMeasure Main.PSRM `"`"`"Update`"`"`"")
        $Container=$RmAPI.ReplaceVariables("[Module.Taskbar.Container:x]")
        $Width=$RmAPI.VariableStr("Module.Taskbar.ProgramW")
        $Size=$RmAPI.VariableStr("Module.Taskbar.IconSize")
        $Coord="($Container+$ID*$Width+($Width-$Size)*0.5+$Width*0.5)"
        $RmAPI.Bang("!WriteKeyValue Variables Parent.Position `"`"`"$Coord`"`"`" `"`"`"$($RootConfigPath)PopUp\Taskbar_PopUp.ini`"`"`" ")
        
        # Generates Item List
        GeneratePopUpItemInc($ID)
    }
}

function MouseLeaveAction {
    Param([Int] $ID)

    # MouseLeave Animation
    $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageTint `"`"`"$($RmAPI.VariableStr("Module.Taskbar.DefaultShade"))`"`"`" ")
    $RmAPI.Bang("!UpdateMeter $MeterPrefix$ID")

    $ProgramCount=ReturnProgramCount($ID)
    if($ProgramCount -gt 0){
        # Start Deactivate queue
        $RmAPI.Bang("!CommandMeasure Main.ActionTimer `"`"`"Execute 1`"`"`" ")
    }
}

function GenerateBarItemInc { # Generates an .inc file containing the appropriate amount of meters in the module
    $Count=ReturnMaxProgramCount
    $CurrentCount=$RMAPI.Variable("Module.Taskbar.GennedItemCount",-1)
    If($Count -ne $CurrentCount){ # Generator only runs if necessary
        $Destination=$RmAPI.VariableStr("@") + "Modules\Taskbar\Include\Item.inc"
        $Content=@"
[Variables]

"@    
        For($i=0; $i -lt $Count; $i++){
            $Content+=@"
[$($MeterPrefix)$($i)]
Meter=Image
MeterStyle=Module.Taskbar.StyleIcon
x=($($i)*#Module.Taskbar.ProgramW#+(#Module.Taskbar.ProgramW#-#Module.Taskbar.IconSize#)*0.5)

"@
        }
        $Content | Out-File $Destination
        $RMAPI.Bang("!Refresh")
    }
}

function GeneratePopUpItemInc { # Generates an .inc file containing the appropriate amount of meters in the popup
    Param([Int] $ID)

    # Stop Deactivate queue
    $RmAPI.Bang("!CommandMeasure Main.ActionTimer `"`"`"Stop 1`"`"`" ")

    # Set size
    $ProgramCount=ReturnProgramCount($ID)
    $RMAPI.Bang("!WriteKeyValue Variables `"`"`"Module.Taskbar.GennedItemCount`"`"`" `"`"`"$($ProgramCount)`"`"`" `"`"`"$($RmAPI.VariableStr("RootConfigPath") + "PopUp\Taskbar_PopUp.ini")`"`"`"")

    # Activate Popup
    $RmAPI.Bang("!DeactivateConfig `"`"`"$RootConfig\Popup`"`"`" `"`"`"Taskbar_PopUp.ini`"`"`" ")
    $RmAPI.Bang("!ActivateConfig `"`"`"$RootConfig\Popup`"`"`" `"`"`"Taskbar_PopUp.ini`"`"`" ")
    
    # Set window names
    $RmAPI.Bang("!SetVariable Module.Taskbar.ProgramID `"`"`"$ID`"`"`" `"`"`"$RootConfig\PopUp`"`"`" ")
    for($i=0; $i -lt $ProgramCount; $i++) {
        $RmAPI.Bang("!CommandMeasure Module.Taskbar.ProgramOptions `"`"`"SetVariable|Module.Taskbar.WindowName|ChildWindowName|$ID|$i`"`"`" ")
        $RmAPI.Bang("!SetOption $i Text `"`"`"$($RmAPI.VariableStr("Module.Taskbar.WindowName"))`"`"`" `"`"`"$RootConfig\PopUp`"`"`" ")
    }
    $RmAPI.Bang("!UpdateMeterGroup Module.Taskbar.Child `"`"`"$RootConfig\PopUp`"`"`" ")
    $RmAPI.Bang("!Redraw `"`"`"$RootConfig\PopUp`"`"`" ")
}

function UpdateNow {
    RunGetIcons
    $ProgramCount=ReturnMaxProgramCount 
    for($i=0; $i -lt $ProgramCount; $i++) { # iterate through all programs
        SetProgramImage $i
        SetProgramMouseAction $i
    }
    $RmAPI.Bang("!UpdateMeterGroup Module.Taskbar.Icon")
    $RmAPI.Bang("!Redraw")
}

function Update {
    $NeedsUpdate=$RMAPI.VariableStr("NeedsUpdate") # Checks if an update is required
    If($NeedsUpdate -eq 1){ 
        UpdateNow # If so, run all relevant instructions
        $RmAPI.Bang("!SetVariable NeedsUpdate 0") # Reset variable
    }
}

GenerateBarItemInc # Attempts to generate item inc on refresh
