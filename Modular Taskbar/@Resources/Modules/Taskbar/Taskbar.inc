[Variables]
@IncludeTaskbarVariables=#@#Modules\Taskbar\Include\Variables.inc
@IncludeTaskbarIcon=#@#Modules\Taskbar\Include\Item.inc

[Module.Taskbar.StyleIcon]
Group=Module.Taskbar.Icon
y=((#Body.Element#-#Module.Taskbar.IconSize#)/2)
w=#Module.Taskbar.IconSize#
ImageTint=#Module.Taskbar.DefaultShade#
DynamicVariables=1
AntiAlias=1
Container=Module.Taskbar.Container

[Module.Taskbar.ProgramOptions]
Measure=Plugin
Plugin=ProgramOptions
Indexes=#Module.Taskbar.ProgramCount#
AdditionalDependencies=#Module.Taskbar.AddDep#
WindowMirrorPath=#Module.Taskbar.WMPath#
UpdateDivider=(1000/#UpdateInterval#)

[Module.Taskbar.PSRM]
Measure=Plugin
Plugin=PowerShellRM
ScriptFile=#@#Modules\Taskbar\Include\Taskbar.ps1
UpdateDivider=(1000/#UpdateInterval#)

[Module.Taskbar.Container]
Meter=Image
x=(#Module.Taskbar.P#-(#Module.Taskbar.A#*0.5)*#Module.Taskbar.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.Taskbar.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
