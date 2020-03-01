[Variables]
module.Power.Position=264
module.Power.Anchor=0
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

[module.Power.StartIcon]
MeterStyle=module.Power.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=MI-PowerDown-MI
Container=module.Power.Container
RightMouseUpAction=[shutdown -a]
LeftMouseDoubleClickAction=[shutdown -s -t 30]