[Metadata]
Name=Start
Description=Click to open a shortcut menu popup. Customize shortcuts through the context menu in the popup.

[Variables]
module.Start.Position=8
module.Start.Anchor=0

; Do not change
module.Start.Width=#body.ElementSize#

[module.Start.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.Start.PSRM]
Measure=Plugin
Plugin=PowerShellRM
ScriptFile=#@#Includes\Start\Generate.ps1
DynamicVariables=1
IfCondition=#CurrentSection#=0
IfFalseAction=[!WriteKeyValue Variables Module.Start.NumProgram "[#CurrentSection#]" "#RootConfigPath#\PopUp\Start_PopUp.ini"]

[module.Start.Container]
Meter=Image
x=(#module.Start.Position#-(#module.Start.Anchor#*0.5)*#module.Start.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.Start.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Start_PopUp.ini"][!ToggleConfig "#RootCOnfig#\PopUp" "Start_PopUp.ini"]

[module.Start.StartIcon]
MeterStyle=module.Start.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=AppList
Container=module.Start.Container
