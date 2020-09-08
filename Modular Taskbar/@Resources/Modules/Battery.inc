[Metadata]
Name=Battery
Description=Displays Battery level. Click to display Uptime.

[Variables]
module.Battery.Position=1424
module.Battery.Anchor=2

; Do not change
module.Battery.Width=(2*#body.ElementSize#)

[module.Battery.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.Battery.StyleInfoString]
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Battery.BatteryPercentage]
Measure=Plugin
Plugin=PowerPlugin
PowerState=Percent
UpdateDivider=(5000/#UpdateInterval#)
RegExpSubstitute=1
Substitute="^(\d{1,3})$":"\1"
OnChangeAction=[!UpdateMeterGroup Module.Battery.Display][!Redraw]

[module.Battery.Container]
Meter=Image
x=(#module.Battery.Position#-(#module.Battery.Anchor#*0.5)*#module.Battery.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.Battery.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Battery_PopUp.ini"][!ToggleConfig "#ROOTCONFIG#\PopUp" "Battery_PopUp.ini"]

[module.Battery.BatteryIcon]
MeterStyle=module.Battery.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=Battery
Container=module.Battery.Container

[Module.Battery.PercentageDisplay]
Group=Module.Battery.Display
MeterStyle=module.Battery.StyleInfoString
Meter=String
x=(#body.ElementSize#*36/24)
y=(#body.ElementSize#*12/24)
MeasureName=Module.Battery.BatteryPercentage
Container=Module.Battery.Container
