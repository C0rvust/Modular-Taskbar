[Variables]
@IncludeShortcutVariables=#@#Modules\Shortcut\Include\Variables.inc

[Module.Shortcut.StyleIconString]
InlineSetting=Face | #Font.Icon#
InlineSetting2=Size | #Font.IconS#
InlineSetting3=Color | #Colour.2#,#Colour.2.Alpha#
InlineSetting4=Color | 0,0,0,0
InlinePattern4=Highlight
InlineSetting5=CharacterSpacing | 0 | (-[#CurrentSection#:h]*0.75)
InlinePattern5=Highlight
StringAlign=CenterCenter
Prefix=Highlight
AntiAlias=1
DynamicVariables=1

[Module.Shortcut.PSRM]
Measure=Plugin
Plugin=PowershellRM
Param=File Explorer|Internet Explorer|Notepad|Paint
ScriptFile=#@#Modules\Shortcut\Include\Shortcut.ps1

[Module.Shortcut.Container]
Meter=Image
x=(#Module.Shortcut.P#-(#Module.Shortcut.A#*0.5)*#Module.Shortcut.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.Shortcut.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1

[Module.Shortcut.AppListIcon]
MeterStyle=Module.Shortcut.StyleIconString
Meter=String
x=(#Body.Element#*0.5)
y=(#Body.Element#*0.5)
Text=MenuBento
Container=module.Shortcut.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Shortcut_PopUp.ini"][!ToggleConfig "#ROOTCONFIG#\PopUp" "Shortcut_PopUp.ini"]
