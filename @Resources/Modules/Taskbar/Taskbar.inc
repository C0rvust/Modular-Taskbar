[Variables]
@IncludeTaskbarVariables=#@#Modules\Taskbar\Include\Variables.inc

[Module.Taskbar.StyleIcon]
Group=Module.Taskbar.Icon
y=((#Body.Element#-#Module.Taskbar.IconSize#)/2)
w=#Module.Taskbar.IconSize#
ImageAlpha=(#Colour.2.Alpha#*0.5)
DynamicVariables=1
AntiAlias=1
Container=Module.Taskbar.Container

[Module.Taskbar.ProgramOptions]
Measure=Plugin
Plugin=ProgramOptions
Indexes=#Module.Taskbar.ProgramCount#
AdditionalDependencies=#Module.Taskbar.AddDep#
UpdateDivider=(1000/#UpdateInterval#)

[Module.Taskbar.PSRM]
Measure=Plugin
Plugin=PowerShellRM
ScriptFile=#@#Modules\Taskbar\Include\Taskbar.ps1
UpdateDivider=(1000/#UpdateInterval#)

[Module.Taskbar.PSRMParam]
Measure=Plugin
Plugin=PowershellRM
Param=193,149,193|255
Line=$Saved=$RmAPI.OptionStr("Param")
Line2=$Var0=$RmAPI.VariableStr("Colour.2"); $Var1=$RmAPI.VariableStr("Colour.2.Alpha"); $Exist=[System.IO.File]::Exists("#@#Modules\Taskbar\Include\Dependencies\Icons\.Default.png"); $Var="$Var0|$Var1"
Line3=if(($Saved -ne $Var) -or ($Exist -eq $False)) {$RmAPI.Bang("!WriteKeyValue $($RmAPI.GetMeasureName()) Param `"`"`"$Var`"`"`" `"`"`"$($RmAPI.VariableStr("@") + "Modules\Taskbar\Taskbar.inc")`"`"`" "); $RmAPI.Bang("!EnableMeasure Module.Taskbar.MM.IconDefault"); $RmAPI.Bang("!CommandMeasure Module.Taskbar.MM.IconDefault Update")}

[Module.Taskbar.MM.IconDefault]
Measure=Plugin
Plugin=MagickMeter
Image=File #@#Modules\Taskbar\Include\StockIcon\.Default.png | AdaptiveResize 64,64 | Colorize (#Colour.2.Alpha#*100/255);#Colour.2#
DynamicVariables=1
ExportTo=#@#Modules\Taskbar\Include\Dependencies\Icons\.Default.png
Disabled=1
OnFinishAction=[!DisableMeasure #CurrentSection#]

[Module.Taskbar.Container]
Meter=Image
x=(#Body.Border#+#Module.Taskbar.P#-(#Module.Taskbar.A#*0.5)*#Module.Taskbar.W#)
y=((#Skin.Height#-#Body.Element#)/2)
w=#Module.Taskbar.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1

[Module.Taskbar.Icons]
@IncludeTaskbarIcon=#@#Modules\Taskbar\Include\Item.inc
