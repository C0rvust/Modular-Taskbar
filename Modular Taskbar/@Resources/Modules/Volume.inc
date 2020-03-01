[Variables]
module.Volume.Position=1558
module.Volume.Anchor=2
module.Volume.Width=(2*#body.ElementSize#)

[module.Volume.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.Volume.StyleInfoString]
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Volume.Volume]
Measure=Plugin
Plugin=Win7AudioPlugin
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasure Module.Volume.VolumePercentage][!UpdateMeter module.Volume.VolumeDisplay][!Redraw]

[Module.Volume.VolumePercentage]
Measure=Calc
Formula=Module.Volume.Volume
RegExpSubstitute=1
Substitute="^-1$|^0$":"Mute","(^\d{1,3}$)":"\1"

[module.Volume.Container]
Meter=Image
x=(#module.Volume.Position#-(#module.Volume.Anchor#*0.5)*#module.Volume.Width#)
y=#body.Padding#
w=#module.Volume.Width#
h=#body.ElementSize#
SolidColor=0,0,0
LeftMouseUpAction=[!CommandMeasure "Module.Volume.Volume" "ToggleMute"][!UpdateMeasure module.Volume.VolumeDisplay]
MouseScrollUpAction=[!CommandMeasure "Module.Volume.Volume" "ChangeVolume 1"][!UpdateMeasure module.Volume.VolumeDisplay]
MouseScrollDownAction=[!CommandMeasure "Module.Volume.Volume" "ChangeVolume -1"][!UpdateMeasure module.Volume.VolumeDisplay]

[module.Volume.VolumeIcon]
MeterStyle=module.Volume.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=MI-Volume-MI
Container=module.Volume.Container

[module.Volume.VolumeDisplay]
MeterStyle=module.Volume.StyleInfoString
Meter=String
x=(#body.ElementSize#*36/24)
y=(#body.ElementSize#*12/24)
MeasureName=Module.Volume.VolumePercentage
Container=Module.Volume.Container