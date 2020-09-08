# Variables -------------------------------------------------------------

# Main skin directory
$RootConfig=$RmAPI.VariableStr("RootConfig")
# Module folder directory
$ModuleFolder=$RmAPI.VariableStr("@") + "Modules"
# Main skin variable file directory
$Variables=$RmAPI.VariableStr("@") + "Variables.inc"
# Module list file directory
$ModuleList=$RmAPI.VariableStr("@") + "ModuleList.inc"
# Setting module list file diredctory
$SettingConfig=$RmAPI.VariableStr("@") + "Settings\List.inc"

# Initialise $ModuleString with the rainmeter variable
# Easier to handle within powershell env
$ModuleString=$RmAPI.VariableStr("ActiveModules")

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
function IsModuleActive{
    Param($Module)

    $ActiveModules=ActiveModules
    if($ActiveModules){ # Check if any modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){
            return $True
        }
    }
    return $False
}

# Activate a module
function AddModule{
    Param($Module)

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
function RemoveModule{
    Param($Module)

    $ActiveModules=ActiveModules
    if($ActiveModules) { # Check if any modules are active to prevent operation on null object
        if($ActiveModules.Contains($Module)){ # Check if module is indeed activated
            if($ActiveModules.length -gt 1){ # Check if the array has more than one element
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
function ToggleModule{
    Param($Module)
    
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

$NewAvaliableModules=AvaliableModules
$NumAvaliableModules=$NewAvaliableModules.length
$NewAvaliableModules=$NewAvaliableModules -join ","
$OldAvaliableModules=$RmAPI.VariableStr("AvaliableModules")
$ActiveModules=ActiveModules
if($NewAvaliableModules -ne $OldAvaliableModules){ # Check if there has been a change to list of modules
	$RmAPI.bang("!WriteKeyValue Variables AvaliableModules `"`"`"$NewAvaliableModules`"`"`" `"`"`"$Variables`"`"`" ")
	$ActiveModules | ForEach-Object {
		if(!$NewAvaliableModules.Contains($_)){ # Remove any modules that are considered active but have been removed from the module folder
			RemoveModule($_)
		}
	}
	EstablishActiveModules
	EstabilishSettingsConfig
	$RmAPI.bang("!WriteKeyValue Variables NumAvaliableModules `"`"`"$NumAvaliableModules`"`"`" ")
	$RmAPI.bang("!Refresh `"`"`"$RootConfig`"`"`" ") # This refresh is only done so if there are changes detected
	$RmAPI.bang("!Refresh")
}