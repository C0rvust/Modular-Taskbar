# Variables -------------------------------------------------------------

$ModuleFolder=$RmAPI.VariableStr("@") + "\Modules"
$Variables=$RmAPI.VariableStr("@") + "Variables.inc"
$ModuleList=$RmAPI.VariableStr("@") + "\ModuleList.inc"
$ModuleString=$RmAPI.VariableStr("ActiveModules")
$RootConfig=$RmAPI.VariableStr("RootConfig")
$SettingConfig=$RmAPI.VariableStr("@") + "\Settings\List.inc"

# functions -------------------------------------------------------------

# Return all avaliable modules in $ModuleFolder
function AvaliableModules{
    $List=@()
    Get-ChildItem $ModuleFolder -File | Where-Object Name -Match "inc$" | Sort-Object | ForEach-Object {
        $List+=$_.BaseName
    }
    return $List
}

# Return all currently active modules
function ActiveModules{
    if($ModuleString){ # Check if rm variable is a null string
        if($ModuleString -Match ","){ # Check if rm variable contains more than one module
            $List=($ModuleString -split ',') | Sort-Object
            return $List
        }
        else{ 
            return ,@($ModuleString)
        }
    }
    return $null
}

# Return if a given module is active
function IsModuleActive([String] $Module){
    $ActiveModules=ActiveModules
    if($ActiveModules){ # Check if any modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){
            return $True
        }
    }
    return $False
}

# Activate a module
function AddModule([String] $Module){
    $AvaliableModules=AvaliableModules
    $ActiveModules=ActiveModules
    if($AvaliableModules.Contains($Module)){ # Check if module is a valid module
        if($ActiveModules){ # Check if any modules are active to prevent operation on null object
            if(!$ActiveModules.Contains($Module)){ # Check if module is indeed deactivated
                $ActiveModules+=$Module
                $global:ModuleString=$ActiveModules -join ","
            }
        }
        else{
            $global:ModuleString=$Module
        }
		EstablishActiveModules
    }
}

# Deactivate a module
function RemoveModule([String] $Module){
    $ActiveModules=ActiveModules
    if($ActiveModules) { # Check if any modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){ # Check if module is indeed activated
            if($ActiveModules.length -gt "1"){ # Check if the array has more than one element
                $ActiveModules=$ActiveModules | Where-Object {$_ -ne $Module}
                $global:ModuleString=$ActiveModules -join ","
            }
            else{
                $global:ModuleString=""
            }
        }
		EstablishActiveModules
    }
}

# Toggle a module
function ToggleModule([String] $Module){
    $IsModuleActive=IsModuleActive($Module)
    if($IsModuleActive){
        RemoveModule($Module)
    }
    else{
        AddModule($Module)
    }
}

# Write the @Include file for active modules
function EstablishActiveModules{
    $ActiveModules=ActiveModules

    $RmAPI.bang("!SetVariable ActiveModules `"`"`"$global:ModuleString`"`"`" ") # Write the new list to setting skin
    $RmAPI.bang("!WriteKeyValue Variables ActiveModules `"`"`"$global:ModuleString`"`"`" `"`"`"$Variables`"`"`" ") # Write the new list to variable file
	# Refresh is done at the rainmeter skin's end
    $Content="[ModuleList]"
    if($ActiveModules){
        $index=1;
        $ActiveModules | ForEach-Object {
            $content += @"

@IncludeModule$index=#@#Modules\$_.inc
"@
    $index++;
        }
    }
    $content | Out-File -FilePath $ModuleList
}

# Write the @Include file for the setting skin
function EstabilishSettingsConfig{
    $AvaliableModules=AvaliableModules
    $Content="" # Generates the scrollable window in the setting skin
	$content += @"
[R1]
Group=ModuleElement
Meter=String
x=#Padding#
y=#ScrollPosition#
Container=Container.ModuleElement
DynamicVariables=1

"@
	
    $AvaliableModules | ForEach-Object {
    $content += @"
[$($_)BG]
MeterStyle=Setting.StyleShapeModuleBox
Meter=Shape

"@
    }
    $content += @"
[R2]
Group=ModuleElement
Meter=String
x=(#IntAreaWidth#/2)
y=(#ScrollPosition#+#MEHeight#/2)
Container=Container.ModuleElement
DynamicVariables=1

"@
    $AvaliableModules | ForEach-Object {
    $content += @"
[$_]
MeterStyle=Setting.StyleStringModuleText
Meter=String

"@
    }
    $content | Out-File -FilePath $SettingConfig
}

# Runtime code ----------------------------------------------------------

$ActiveModules=ActiveModules
$AvaliableModules=AvaliableModules
$AM1=$AvaliableModules.length
$AM2=$RmAPI.VariableStr("AvaliableModules")
# Check if there are new modules 
# Admittedly this should not check for the number of avaliable modules, but rather the complete list
# For all intent and purpose this works alright
if($AM1 -ne $AM2){
	$ActiveModules | ForEach-Object {
		if(!$AvaliableModules.Contains($_)){ # Remove any modules that are considered active but have been removed from the module folder
			RemoveModule($_)
		}
	}
	$RmAPI.bang("!WriteKeyValue Variables AvaliableModules `"`"`"$AM1`"`"`" ")
	EstablishActiveModules
	EstabilishSettingsConfig
	$RmAPI.bang("!Refresh `"`"`"$RootConfig`"`"`" ") # This refresh is only done so if there are changes detected
	$RmAPI.bang("!Refresh")
}
	