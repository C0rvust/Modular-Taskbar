$MeterPrefix="module.Taskbar.Icon."
$RootConfigPath=$RmApi.VariableStr("RootConfigPath")
$RootConfig=$RmApi.VariableStr("RootConfig")

function MaxProgramCount { # Retrieves the #MasProgramCount# Variable
    $Count=$RmAPI.VariableStr("module.Taskbar.ProgramCount")
    return $Count
}

function StockIcons { # Retrieves an array of the avaliable png files in the path specified by #StockIconPath#
    $Path=$RmAPI.VariableStr("module.Taskbar.StockIconPath")
    $List=@()
    
    Get-ChildItem $Path -File | Where-Object Name -Match "png$" | ForEach-Object {
        $List+=$_.BaseName
    }
    Return $List
}

function RunGetIcons { # Runs the GetIcon.exe executable to get icon images of all currently running processes
    $GetIconsPath=$RmAPI.VariableStr("module.Taskbar.GetIconsPath") + "\getIcons.exe"
    $AddDepPath=$RmAPI.VariableStr("module.Taskbar.AddDep")
    & "$GetIconsPath" "$AddDepPath"
}

function GetProgramName { # Get the ProgramName of a particular program
    Param([int] $ID)
    
    $ProgramName=$RmAPI.VariableStr("ProgramName" + $ID)
    return $ProgramName
}
function GetProgramCount { # Get the number of children (instances) of a particular program
    Param([int] $ID)
    
    $ProgramCount=$RmAPI.VariableStr("ProgramsCount" + $ID)
    return $ProgramCount
}

function SetProgramCoord {
    Param([Int] $ID)

    $Width=$RmAPI.VariableStr("module.Taskbar.ProgramW")
    $Size=$RmAPI.VariableStr("module.Taskbar.IconSize")
    $Coord="($ID*$Width+($Width-$Size)*0.5)"

    $RmAPI.Bang("!SetOption $MeterPrefix$ID x $Coord")
}

function SetProgramImage { # Set the icon image of a particular program
    Param([Int] $ID)

    $ProgramName=GetProgramName($ID)
    $StockIcons=StockIcons
    $StockIconPath=$RmAPI.VariableStr("module.Taskbar.StockIconPath")
    $GenIconPath=$RmAPI.VariableStr("module.Taskbar.GetIconsPath") + "\Icons"

    If($ProgramName -Match "Empty") { 
        $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageName "" ")
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

function SetProgramMouseAction { #Set the relevant mouse actions of a particular program
    Param([Int] $ID)

    $ProgramName=GetProgramName($ID)
    If($ProgramName -Match "Empty"){ # Not in use
        $RmAPI.Bang("!SetOption $MeterPrefix$ID LeftMouseUpAction `"`"`"$Null`"`"`" ")
        $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseOverAction `"`"`"$Null`"`"`" ")
        $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseLeaveAction `"`"`"$Null`"`"`" ")
        $RmAPI.Bang("!SetOption $MeterPrefix$ID MiddleMouseUpAction `"`"`"$Null`"`"`" ")
    }
    else{
        $ProgramCount=GetProgramCount($ID)
        if($ProgramCount -gt 0) { # Has open windows
            $RmAPI.Bang("!SetOption $MeterPrefix$ID LeftMouseUpAction `"`"`"[!CommandMeasure module.Taskbar.ProgramOptions ToFront|Main|$ID]`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseOverAction `"`"`"!CommandMeasure module.Taskbar.PSRM `"`"`"MouseOverIconAction $ID`"`"`"`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseLeaveAction `"`"`"!CommandMeasure module.Taskbar.PSRM `"`"`"MouseLeaveIconAction $ID`"`"`"`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MiddleMouseUpAction `"`"`"!CommandMeasure module.Taskbar.ProgramOptions `"`"`"StartNew|$ID`"`"`"`"`"`" ")
        }
        else{ # Pinned Program but no open windows
            $RmAPI.Bang("!SetOption $MeterPrefix$ID LeftMouseUpAction `"`"`"[!CommandMeasure module.Taskbar.ProgramOptions StartNew|$ID]`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseOverAction `"`"`"$Null`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MouseLeaveAction `"`"`"$Null`"`"`" ")
            $RmAPI.Bang("!SetOption $MeterPrefix$ID MiddleMouseUpAction `"`"`"!CommandMeasure module.Taskbar.ProgramOptions `"`"`"StartNew|$ID`"`"`"`"`"`" ")
        }
    }
}

function MouseOverIconAction {
    Param([Int] $ID)

    # MouseOver Animation
    $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageTint `"`"`"255,255,255`"`"`" ")
    $RmAPI.Bang("!UpdateMeter $MeterPrefix$ID ")

    # Update coords
    $UpdateCoord=$RmAPI.ReplaceVariablesStr("#UpdateCoord#")
    $RmAPI.Bang("$UpdateCoord")
    
    # Set PopUp Coord
    $ContainerCoord=$RmAPI.ReplaceVariables("[module.Taskbar.Container:x]")
    $Width=$RmAPI.VariableStr("module.Taskbar.ProgramW")
    $Size=$RmAPI.VariableStr("module.Taskbar.IconSize")
    $Coord="($ContainerCoord+$ID*$Width+($Width-$Size)*0.5+$Width*0.5)"
    $RmAPI.Bang("!WriteKeyValue Variables Parent.Position `"`"`"$Coord`"`"`" `"`"`"$($RootConfigPath)PopUp\Taskbar_PopUp.ini`"`"`" ")

    #EstablishPopUp
    EstablishPopUp($ID)
}

function MouseLeaveIconAction  {
    Param([Int] $ID)

    # MouseLeave Animation
    $RmAPI.Bang("!SetOption $MeterPrefix$ID ImageTint `"`"`"180,180,180`"`"`" ")
    $RmAPI.Bang("!UpdateMeter $MeterPrefix$ID ")

    # Start Deactivate queue
    $RmAPI.Bang("!CommandMeasure module.Taskbar.PopUpTimer `"`"`"Execute 1`"`"`" ")
}

function EstablishPopUp {
    Param([Int] $ID)

    # Stop Deactivate queue
    $RmAPI.Bang("!CommandMeasure module.Taskbar.PopUpTimer `"`"`"Stop 1`"`"`" ")

    $ProgramCount=GetProgramCount($ID)
    If($ProgramCount -gt 0){ # If a popup is needed
        # Set size
        $ProgramCount=GetProgramCount($ID)
        $RmAPI.Bang("!WriteKeyValue Variables Module.Taskbar.NumProgram `"`"`"$ProgramCount`"`"`" `"`"`"$($RootConfigPath)PopUp\Taskbar_PopUp.ini`"`"`" ")

        # Activate Popup
        $RmAPI.Bang("!DeactivateConfig `"`"`"$RootConfig\Popup`"`"`" `"`"`"Taskbar_PopUp.ini`"`"`" ")
        $RmAPI.Bang("!ActivateConfig `"`"`"$RootConfig\Popup`"`"`" `"`"`"Taskbar_PopUp.ini`"`"`" ")

        # Set ID
        $RmAPI.Bang("!SetVariable Module.Taskbar.ProgramID `"`"`"$ID`"`"`" `"`"`"$RootConfig\PopUp`"`"`" ")

        # Set window names
        for($i=0; $i -lt $ProgramCount; $i++) {
            $RmAPI.Bang("!CommandMeasure module.Taskbar.ProgramOptions `"`"`"SetVariable|module.Taskbar.WindowName|ChildWindowName|$ID|$i`"`"`" ")
            $WinName=$RmAPI.VariableStr("module.Taskbar.WindowName")
            $RmAPI.Bang("!SetOption $i Text `"`"`"$WinName`"`"`" `"`"`"$RootConfig\PopUp`"`"`" ")
        }
        $RmAPI.Bang("!UpdateMeterGroup TaskbarChildString `"`"`"$RootConfig\PopUp`"`"`" ")
        $RmAPI.Bang("!Redraw `"`"`"$RootConfig\PopUp`"`"`" ")
    }
}

function UpdateNow {
    RunGetIcons
    $MaxProgramCount=MaxProgramCount 
    for($i=0; $i -lt $MaxProgramCount; $i++) { # iterate through all programs
        SetProgramCoord($i)
        SetProgramImage($i)
        SetProgramMouseAction($i)
    }
    $RmAPI.Bang("!UpdateMeterGroup module.Taskbar.Icon")
    $RmAPI.Bang("!Redraw")
}

function Update {
    $NeedsUpdate=$RmAPI.VariableStr("NeedsUpdate") # Checks if an update is required
    If($NeedsUpdate -eq 1){ 
        UpdateNow # If so, run all relevant instructions
        $RmAPI.Bang("!SetVariable NeedsUpdate 0") # Reset variable
    }
}