[Metadata]
Name=Power
Description=Click to open options to shutdown device.

[Variables]
module.Power.Position=46
module.Power.Anchor=0

; Do not change
module.Power.Width=#body.ElementSize#

[module.Power.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Power.Container]
Meter=Image
x=(#module.Power.Position#-(#module.Power.Anchor#*0.5)*#module.Power.Width#)
y=#body.Padding#
w=#module.Power.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1

[module.Power.StartIcon]
MeterStyle=module.Power.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=PowerDown
Container=module.Power.Container
LeftMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Power_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Power_PopUp.ini"]
