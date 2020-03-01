[Variables]
Module.Clock.TimeFormat=%H : %M

Module.Clock.Position=1694
Module.Clock.Anchor=2
Module.Clock.Width=(#body.ElementSize#*2)

[module.Clock.StyleInfoString]
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
InlineSetting4=Color | #colour.2.Code#,(#colour.2.Alpha#*(([Module.Clock.Time.S]%4) <= 1 ? 1.0 : 0.50))
InlinePattern4=:
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Clock.Time.HM]
Measure=Time
Format=#Module.Clock.TimeFormat#
UpdateDivider=(5000/#UpdateInterval#)
OnChangeAction=[!UpdateMeter Module.Clock.Display.Time]

[Module.Clock.Time.S]
Measure=Time
Format=%S
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeter Module.Clock.Display.Time]

[Module.Clock.Container]
Meter=Image
x=(#module.Clock.Position#-(#module.Clock.Anchor#*0.5)*#module.Clock.Width#)
y=#body.Padding#
w=#Module.Clock.Width#
h=#body.ElementSize#
SolidColor=0,0,0

[Module.Clock.Display.Time]
Group=Module.Clock.Display
MeterStyle=module.Clock.StyleInfoString
Meter=String
x=(#body.ElementSize#*24/24)
y=(#body.ElementSize#*12/24)
MeasureName=Module.Clock.Time.HM
DynamicVariables=1
Container=Module.Clock.Container