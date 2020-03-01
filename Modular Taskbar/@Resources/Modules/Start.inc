[Variables]
module.Start.Position=226
module.Start.Anchor=0
module.Start.Width=#body.ElementSize#

[module.Start.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.Start.Container]
Meter=Image
x=(#module.Start.Position#-(#module.Start.Anchor#*0.5)*#module.Start.Width#)
y=#body.Padding#
w=#module.Start.Width#
h=#body.ElementSize#
SolidColor=0,0,0

[module.Start.StartIcon]
MeterStyle=module.Start.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=MI-Applist-MI
Container=module.Start.Container
LeftMouseUpAction=[!WriteKeyValue Variables Parent.Position "(#CurrentConfigX#+[Module.Start.Container:x])" "#RootConfigPath#\PopUp\Start_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Start_PopUp.ini"]
