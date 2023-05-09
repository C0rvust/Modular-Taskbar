$RootConfig=$RmAPI.VariableStr("RootConfig")
$Resources=$RmAPI.VariableStr("@")
$ModuleListFile=$RmAPI.VariableStr("@") + "ModuleList.inc"
$ModuleFolder=$RmAPI.VariableStr("@") + "Modules"
$SettingsFolder=$RmAPI.VariableStr("@") + "Settings"

# ==========================================================================
# Functions for setting menu navigation
# ==========================================================================

function MoveLabel { 
    # Moves sidebar button label with appropriate text and location
    Param([int] $Location,
    [string] $LabelText)
    
    $TBW=$RmAPI.VariableStr("TopBarWidth")
    $SBW=$RmAPI.VariableStr("SideBarWidth")
    $SH=$RmAPI.VariableStr("Skin.Height")
    
    if($Location -lt 0) {
        $Coord="($SH + $SBW * ($Location + 0.5))"
    } else {
        $Coord="($TBW + $SBW * ($Location + 0.5))"
    }

    $RmAPI.Bang("!SetOption Setting.Label Text `"`"`"$LabelText`"`"`" ")
    $RmAPI.Bang("!SetOption Setting.Label Y  `"`"`"$Coord`"`"`" ")
    $RmAPI.Bang("!ShowMeter `"`"`"Setting.Label`"`"`" ")
    $RmAPI.Bang("!ShowMeter `"`"`"Setting.LabelBackground`"`"`" ")
    $RmAPI.Bang("!UpdateMeter `"`"`"Setting.Label`"`"`" ")
    $RmAPI.Bang("!UpdateMeter `"`"`"Setting.LabelBackground`"`"`" ")
}

function HideLabel { # Hides sidebar button label
    $RmAPI.Bang("!HideMeter `"`"`"Setting.Label`"`"`" ")
    $RmAPI.Bang("!HideMeter `"`"`"Setting.LabelBackground`"`"`" ")
}

# ==========================================================================
# Functions for retrieving data from variables.inc and module info
# ==========================================================================

function AvaliableModules {
    # Lists avaliable modules 
    $AvaliableModules=@()
    $Dest=$ModuleFolder
    Get-ChildItem $Dest -Directory | ForEach-Object {
        $File="$Dest\$($_.BaseName)\$($_.BaseName).inc"
        $FileExist = Test-Path $File -PathType Leaf
        if($FileExist){
            $AvaliableModules+=$($_.BaseName)
        }
    }
    return $AvaliableModules
}

function GetActiveModules {
    # Lists currently active modules
    # https://stackoverflow.com/questions/50843357/returning-arraylist-from-function-script
    $Dest=$ModuleListFile
    $Content = [System.Collections.Arraylist]((Get-Content $Dest -Raw) -split [Environment]::NewLine)
    try {$Content.RemoveAt(0)} catch {}

    $ActiveModules = [System.Collections.Arraylist]@()
    $Content | ForEach-Object{
        if ($_) {
            [void]$ActiveModules.Add(($_ -replace '^.*\\(.*?)\.inc','$1'))
        }
    }
    return ,$ActiveModules
}

function IsModuleActive {
    # Returns if a module is active
    Param($Module)

    $ActiveModules=GetActiveModules
    if($ActiveModules){ # Check if any modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){
            return $True
        }
    }
    return $False
}

function AddModule {
    Param($Module)
    # Activates a module if it exists and is inactive

    $ActiveModules=GetActiveModules

    if((AvaliableModules).Contains($Module)){
        if($ActiveModules){ # Check if at least one modules are active to prevent operation on null object
            if(!$ActiveModules.Contains($Module)){ # Check if module is deactivated
                $ActiveModules+=$Module # Append module to array, return array
            }
        }
        else{
            $ActiveModules=,@($Module) # Set module as array, return array
        }
        WriteActiveModules $ActiveModules
    }
}

function RemoveModule {
    Param($Module)
    # Deactivates a module if it exists and is active

    $ActiveModules=GetActiveModules

    if($ActiveModules) { # Check if at least one modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){ # Check if module is activated
            if($ActiveModules.length -gt 1){ # Check if the array has more than one element
                $ActiveModules=$ActiveModules | Where-Object {$_ -ne $Module} # Remove module from array, Return array
            }
            else{
                $ActiveModules=,@() # Set array to empty, Return array
            }
            WriteActiveModules $ActiveModules
        }
    }
}

function ToggleModule {
    Param($Module)
    
    if((IsModuleActive $Module)){
        RemoveModule $Module
    }
    else{
        AddModule $Module
    }
}

function WriteActiveModules {
    # Retrieves the active modules and write them as a list of @Include files @ ModuleList.inc
    Param([Array] $ActiveModules)

    $Content="[ModuleList]"
    if($ActiveModules){ # Checks if there is at least one active module
        $ActiveModules | Sort-Object | ForEach-Object {
            $content += @"

@IncludeModule$_=#@#Modules\$_\$_.inc
"@
        }
    }
    $Content | Out-File -FilePath $ModuleListFile
}

function GenerateInteractableField {
    # Generates an @include file which contains a framework for the interactable elements of the setting skin
    Param([Int] $NumInteractable)

    $Dest = "$SettingsFolder\Interactable.inc"
    $Content = @"
[Variables]
NumInteractableAvaliable=$NumInteractable

"@
    $Content += @"
[Block.Dummy]
Meter=Image
MeterStyle=Setting.StyleBlockShape
Group=Interactable
y=(#ScrollPos#-#InteractableH#)

"@
    for ($i=0; $i -lt $NumInteractable; $i++) { # Background for each elment
        $Content += @"
[Block.$i]
Meter=Shape
MeterStyle=Setting.StyleBlockShape
Group=Interactable | Interactable$i

"@
    }

    $Content += @"
[Label.Dummy]
Meter=Image
MeterStyle=Setting.StyleLabelString
Group=Interactable
y=(#ScrollPos#-#InteractableH#/2)

"@
    for ($i=0; $i -lt $NumInteractable; $i++) { # Title for each element
        $Content += @"
[Label.$i]
Meter=String
MeterStyle=Setting.StyleLabelString
Group=Interactable | Interactable$i
Text=Label $i

"@
    }

    $Content += @"
[Value.Dummy]
Meter=Image
MeterStyle=Setting.StyleValueString
Group=Interactable
y=(#ScrollPos#-#InteractableH#/2)

"@
    for ($i=0; $i -lt $NumInteractable; $i++) { # Value for each element
        $Content += @"
[Value.$i]
Meter=String
MeterStyle=Setting.StyleValueString
Group=Interactable | Interactable$i
Text=Value $i
LeftMouseUpAction=[]

"@
    }
    $Content += @"
[Button.Dummy]
Meter=String
MeterStyle=Setting.StyleButtonString
Group=Interactable
y=(#ScrollPos#-#InteractableH#/2)

"@
    for ($i=0; $i -lt $NumInteractable; $i++) { # Value for each element
        $Content += @"
[Button.$i]
Meter=String
MeterStyle=Setting.StyleButtonString
Group=Interactable | Interactable$i
LeftMouseUpAction=[]

"@
    }
    $Content | Out-File -FilePath $Dest
}

# Pulls all relevant variables within the designated file, and compiles an array of all relevant data
# ; vargen|"Desc"|"Group"|"Type"|"Bound"
# : "Name"="Value"
# Returns an array $Final, each element is the data array of one variable
# Each array contains 6 elements: "Desc","Group","Type","Bound","Name","Value"
# Can be accessed as $Final[0]["Value"] etc
# https://stackoverflow.com/questions/42612241/output-multiple-regex-matches-to-another-array-using-powershell
# function GenerateInteractableData2 {
#     Param([String] $Page)

#     switch($Page) {
#         "General" {
#             $File=$VariablesFile
#         }
#         default {
#             $File="$ModuleFolder\$Page\Include\Variables.inc"
#         }
#     }

#     $regexmatch="; vargen\|.*$" # Pattern to fish out all the matching results
#     $regexparse="; vargen(?(?=\|)\|(?<Desc>[^\|\n\r]*)|)(?(?=\|)\|(?<Group>[^\|\n\r]*)|)(?(?=\|)\|(?<Type>[^\|\n\r]*)|)(?(?=\|)\|(?<Bound>[^\|\n\r]*)|)[\W]*(?<Name>.*?)=(?<Value>.*)" # Pattern to parse out relevant information from within the result

#     $Lines=@() # Create an array for all matching results
#     $Content=Get-Content $File | select-string -pattern $regexmatch -context 0,1 # Find $regexmatch, copy the line, the 0 line(s) above and the 1 line(s) below; Each result is an array in $Content
#     foreach ($Line in $Content) {
#         $Line=$Line.ToString() -replace '^([^;]*)','' # Converts each result to a string, then rids the leading " > " 
#         $Lines+=$Line
#     }
#     $Final=@() # Create an array for all relevant information
#     foreach ($Result in $Lines) {
#         $Result -match $regexparse > $null # Parses the result and produces each relevant information
#         $Final += $Matches # Here, $Matches is implicitly created from the regex match
#     }
#     return $Final
# }

function GenerateInteractableData {
    # Pulls all relevant variables from the skin folder, and compiles an array of all relevant data
    # ; vargen|"Desc"|"Group"|"Type"|"Bound"
    # : "Name"="Value"
    # Returns an array $Final, each element is the data array of one variable
    # Each array contains 6 elements: "Desc","Group","Type","Bound","Name","Value"
    # Can be accessed as $Final[0]["Value"] etc
    # https://stackoverflow.com/questions/42612241/output-multiple-regex-matches-to-another-array-using-powershell
    Param([String] $Group)

    $regexmatch="; vargen\|.*$" # Pattern to fish out all the matching results
    $regexparse="; vargen(?(?=\|)\|(?<Desc>[^\|\n\r]*)|)(?(?=\|)\|(?<Group>[^\|\n\r]*)|)(?(?=\|)\|(?<Type>[^\|\n\r]*)|)(?(?=\|)\|(?<Bound>[^\|\n\r]*)|)[\W]*(?<Name>.*?)=(?<Value>.*)" # Pattern to parse out relevant information from within the result
    $ConfigFiles=Get-ChildItem -Path $Resources -Recurse | Where-Object Name -Match ".inc$|.ini$" | Where-Object {$_.FullName -notlike "$($Resources)Settings*"}

    $Final=@()
    $ConfigFiles | ForEach-Object {
        $Content=Get-Content $_.FullName | select-string -pattern $regexmatch -context 0,1 # Find $regexmatch, copy the line, the 0 line(s) above and the 1 line(s) below; Each result is an array in $Content
        foreach ($Line in $Content) {
            $Line=$Line.ToString() -replace '^([^;]*)','' # Converts each result to a string, then rids the leading " > " 
            $Line -match $regexparse > $null # Parses the result and produces each relevant information
            if($Matches["Group"] -eq $Group) { # Here, $Matches is implicitly created from the regex match above
                $Final += ($Matches + @{Path=$_.FullName}) # Adding the file path of the variable into the match result for later referencing
            }
        }
    }
    return $Final
}

function SetInteractableData {
    # Takes the relevant variables, and sets the labels and values of the relevant meters
    Param([String] $Page)

    Switch -Regex ($Page) {
        "General" {
            $Data = GenerateInteractableData $Page 

            if($($Data.length) -gt $RmAPI.Variable("NumInteractableAvaliable",0)){ #Ensures that there are enough fields
                GenerateInteractableField $($Data.length+1) 
                $RmAPI.Bang("!Update *")
            }
            $RmAPI.Bang("!SetVariable NumInteractable `"`"`"$($Data.length)`"`"`" ")
            
            $RmAPI.Bang("!HideMeterGroup `"`"`"Interactable`"`"`" ")

            for ($i=0; $i -lt $Data.length; $i++) { # Sets the fields with data
                $RmAPI.Bang("!ShowMeterGroup `"`"`"Interactable$i`"`"`" ")
                $RmAPI.Bang("!HideMeter `"`"`"Button.$i`"`"`" ")
                $RmAPI.Bang("!SetOption Label.$i Text `"`"`"$($Data[$i]["Desc"])`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i Text `"`"`"$($Data[$i]["Value"])`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i LeftMouseUpAction `"`"`"[!SetOption InputText Command1 `"`"`"[!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"ValidateVariableInput $Page $i `"$($Data[$i]["Path"])`" `'$`UserInput$`' `"`"`"] y=([`*Value.$i`:y*]`+#*Padding*#) defaultvalue=$($Data[$i]["Value"]) `"`"`"][!UpdateMeasure InputText][!CommandMeasure InputText `"`"`"ExecuteBatch 1`"`"`"]`"`"`" ")
            }
            $RmAPI.Bang("!UpdateMeterGroup `"`"`"Interactable`"`"`" ")
            $RmAPI.Bang("!Redraw")
        }
        "Modules" {
            $Data = AvaliableModules

            if($($Data.length) -gt $RmAPI.Variable("NumInteractableAvaliable",0)){ #Ensures that there are enough fields
                GenerateInteractableField $($Data.length+1) 
                $RmAPI.Bang("!Update *")
            }
            $RmAPI.Bang("!SetVariable NumInteractable `"`"`"$($Data.length)`"`"`" ")
            
            $RmAPI.Bang("!HideMeterGroup `"`"`"Interactable`"`"`" ")

            for ($i=0; $i -lt $Data.length; $i++) { # Sets the fields with data
                $RmAPI.Bang("!ShowMeterGroup `"`"`"Interactable$i`"`"`" ")
                $RmAPI.Bang("!SetOption Label.$i Text `"`"`"Module | $($Data[$i])`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i Text `"`"`"$($(IsModuleActive $($Data[$i])) -replace "^True$","Active" -replace "^False$","Inactive")`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i LeftMouseUpAction `"`"`"[!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"ToggleModule $($Data[$i])`"`"`"][!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"SetInteractableData Modules`"`"`"][!Refresh `"`"`"$RootConfig`"`"`"] `"`"`" ")
                $RmAPI.Bang("!SetOption Button.$i LeftMouseUpAction `"`"`"[!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"SetInteractableData $($Data[$i])`"`"`"] `"`"`" ")
            }
            $RmAPI.Bang("!UpdateMeterGroup `"`"`"Interactable`"`"`" ")
            $RmAPI.Bang("!Redraw")
        }
        $($(AvaliableModules | ForEach-Object {"^$_$"}) -join "|") { 
            $Data = GenerateInteractableData $Page 

            if($($Data.length) -gt $RmAPI.Variable("NumInteractableAvaliable",0)){ #Ensures that there are enough fields
                GenerateInteractableField $($Data.length+1) 
                $RmAPI.Bang("!Update *")
            }
            $RmAPI.Bang("!SetVariable NumInteractable `"`"`"$($Data.length)`"`"`" ")
            
            $RmAPI.Bang("!HideMeterGroup `"`"`"Interactable`"`"`" ")

            for ($i=0; $i -lt $Data.length; $i++) { # Sets the fields with data
                $RmAPI.Bang("!ShowMeterGroup `"`"`"Interactable$i`"`"`" ")
                $RmAPI.Bang("!HideMeter `"`"`"Button.$i`"`"`" ")
                $RmAPI.Bang("!SetOption Label.$i Text `"`"`"$($Data[$i]["Desc"])`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i Text `"`"`"$($Data[$i]["Value"])`"`"`" ")
                $RmAPI.Bang("!SetOption Value.$i LeftMouseUpAction `"`"`"[!SetOption InputText Command1 `"`"`"[!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"ValidateVariableInput $Page $i `"$($Data[$i]["Path"])`" `'$`UserInput$`' `"`"`"] y=([`*Value.$i`:y*]`+#*Padding*#) defaultvalue=$($Data[$i]["Value"]) `"`"`"][!UpdateMeasure InputText][!CommandMeasure InputText `"`"`"ExecuteBatch 1`"`"`"]`"`"`" ")
            }
            $RmAPI.Bang("!ShowMeter `"`"`"Setting.ButtonReturn`"`"`" ")
            $RmAPI.Bang("!SetOption `"`"`"Setting.ButtonReturn`"`"`" LeftMouseUpAction `"`"`"[!CommandMeasure $($RmAPI.GetMeasureName()) `"`"`"SetInteractableData Modules`"`"`"] `"`"`" ")

            $RmAPI.Bang("!UpdateMeterGroup `"`"`"Interactable`"`"`" ")
            $RmAPI.Bang("!Redraw")
        }
    }
}

function ValidateVariableInput {
    Param([String] $Page, # Page of setting skin that should be refreshed
    [String] $VariableID, # ID of variable in the data set
    [String] $File, # File which this variable can be found
    [String] $NewInput) # The new value of the variable that is being validated

    $NewInput = $NewInput.Trim('"') # Trim '"", artifact left by inputtext plugin

    $Data=GenerateInteractableData $Page # Retrieve variable bounds and type
    $Bound=$Data[$VariableID]['Bound']
    $Type=$Data[$VariableID]['Type']

    if(!$NewInput) { # Check if Input is null
        return
    }
    switch($Type) { # Sort according to supposed variable type for sainity check
        "rgb" {
            # Validate type and bounds
            # $Length=0
            # $($NewInput -split ",") | ForEach-Object { if($_ -In 0..255) {$Length += 1}} # Splits input into xxx,xxx,xxx , check if each of the three numbers are between 0 & 255
            # if($Length -ne 3) {
            #     return
            # }
            if(!$NewInput -match "^\s*(0|[1-9]\d?|1\d\d?|2[0-4]\d|25[0-5])%?\s*,\s*(0|[1-9]\d?|1\d\d?|2[0-4]\d|25[0-5])%?\s*,\s*(0|[1-9]\d?|1\d\d?|2[0-4]\d|25[0-5])%?\s*$") {
                return
            }
        }
        "int" {
            # Validate type
            $NewInput -match "(?<num>[-]{0,1}\d{1,})" # Parses integer from input
            $Match=[int]$Matches.num

            # Validate bounds
            $Lower=$RmAPI.ReplaceVariablesStr($($Bound -split ":")[0]) # Obtains lower bound and upper bound, $RmAPI.ReplaceVariableStr is used to parse any bounds that may be represented by a rm variable
            $Upper=$RmAPI.ReplaceVariablesStr($($Bound -split ":")[1])

            if((!$Match -and ($Match -ne 0))) { # If the parsed result is not an integer
                return
            } 
            if(($Lower) -and ($Match -lt $Lower)) { # If a lower bound exist, and if the input is smaller than the lower bound, reject
                return
            }
            if(($Upper) -and  ($Match -gt $Upper)) { # If an upper bound exist, and if the input is greater than the upper bound, reject
                return 
            }
        }
        # "string" { # 
        # }
    }
    $RmAPI.Bang("!WriteKeyValue Variables `"`"`"$($Data[$VariableID]['Name'])`"`"`" `"`"`"$NewInput`"`"`" `"`"`"$File`"`"`"") # Write new input to file
    $RmAPI.Bang("!Refresh `"`"`"$RootConfig`"`"`" ") # Refresh taskbar
    ValidateModulePositions
    SetInteractableData $Page # Refresh settings
}

function GetTaskbarWidth {
    $Data=GenerateInteractableData "General"

    for ($i=0; $i -lt $Data.length; $i++) { # Iterate over all avaliable variables within file and returns the taskbar width variable
        if($Data[$i]['Name'] -match "Body.Width") {
            $TaskbarWidth=$Data[$i]['Value']
            return $TaskbarWidth
        }
    }
}

function GetModulePosition {
    Param([String] $Module)
    $Data=GenerateInteractableData $Module

    for ($i=0; $i -lt $Data.length; $i++) { # Iterate over all avaliable variables within file and returns the position variable
        if($Data[$i]['Name'] -match "Module.$($Module).P") {
            $Position=$Data[$i]['Value']
            return $Position
        }
    }
}

function ValidateModulePositions {
    $ActiveModules=GetActiveModules

    # Retrieve taskbar length
    $TaskbarWidth=GetTaskbarWidth

    $ActiveModules | ForEach-Object{
        $Position=GetModulePosition $_
        if($($TaskbarWidth - $Position) -lt 0) { # Iterate over each active module and check if they are within bounds
            $RmAPI.Bang("!WriteKeyValue Variables `"`"`"Module.$($_).P`"`"`" `"`"`"$TaskbarWidth`"`"`" `"`"`"$ModuleFolder\$_\Include\Variables.inc`"`"`" ") # Write new input to file
        }
    }
}

# ==========================================================================
# Initialisation of Setting menu
# ==========================================================================

function Initialise {
    # Initialise
    switch(($RmAPI.VariableStr("CurrentPage"))){
        "General"{
            SetInteractableData "General"
        }
        "Modules"{
            SetInteractableData "Modules"
        }
    }
}

Initialise