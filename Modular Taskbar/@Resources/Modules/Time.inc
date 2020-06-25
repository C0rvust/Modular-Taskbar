[Metadata]
Name=Time
Description=Displays current time. Click to open a calendar popup. Click on a date to view/edit events. Scroll/click the controls at the top to navigate dates. Change first day of week in context menu.

[Variables]
Module.Time.Position=1492
Module.Time.Anchor=2

; Controls time format
Module.Time.TimeFormat=%H : %M

; Do not change
Module.Time.Width=(#body.ElementSize#*2)

[module.Time.StyleInfoString]
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Time.Time.HM]
Measure=Time
Format=#Module.Time.TimeFormat#
UpdateDivider=(5000/#UpdateInterval#)
OnChangeAction=[!UpdateMeter Module.Time.Display.Time]

[Module.Time.Container]
Meter=Image
x=(#module.Time.Position#-(#module.Time.Anchor#*0.5)*#module.Time.Width#)
y=#body.Padding#
w=#Module.Time.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Time_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Time_PopUp.ini"]

[Module.Time.Display.Time]
Group=Module.Time.Display
MeterStyle=module.Time.StyleInfoString
Meter=String
x=(#body.ElementSize#*24/24)
y=(#body.ElementSize#*12/24)
MeasureName=Module.Time.Time.HM
DynamicVariables=1
Container=Module.Time.Container
