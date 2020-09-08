[Metadata]
Name=Volume
Description=Displays volume info. Click the icon to mute/unmute. Scroll on the text to change volume. Click the text to open popup; popup displays current audio device & volume slider. Click audio device to switch to next device. 

[Variables]
module.Volume.Position=1356
module.Volume.Anchor=2

; Do not change
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

[module.Volume.Main]
Measure=Plugin
Plugin=Win7AudioPlugin
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup module.Volume.calc][!UpdateMeterGroup module.Volume.Display][!Redraw]

[module.Volume.VolumeCalc]
Group=module.Volume.calc
Measure=Calc
Formula=module.Volume.Main
Substitute="-1":"0"

[module.Volume.VolumeDisplay]
Group=module.Volume.calc
Measure=Calc
Formula=(module.Volume.Main<=0?0:(module.Volume.Main<50?1:2))
RegExpSubstitute=1
Substitute="^(.*)$":"Volume\1"

[module.Volume.Container]
Meter=Image
x=(#module.Volume.Position#-(#module.Volume.Anchor#*0.5)*#module.Volume.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.Volume.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
MouseActionCursor=0
MouseScrollUpAction=[!CommandMeasure "Module.Volume.Main" "ChangeVolume 5"][!UpdateMeasure module.Volume.Main]
MouseScrollDownAction=[!CommandMeasure "Module.Volume.Main" "ChangeVolume -5"][!UpdateMeasure module.Volume.Main]
LeftMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Volume_PopUp.ini"][!ToggleConfig "#ROOTCONFIG#\PopUp" "Volume_PopUp.ini"]

[module.Volume.VolumeIcon]
Group=module.Volume.Display
MeterStyle=module.Volume.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
MeasureName=module.Volume.VolumeDisplay
Container=module.Volume.Container
LeftMouseUpAction=[!CommandMeasure "Module.Volume.Main" "ToggleMute"][!UpdateMeasure module.Volume.Main]

[module.Volume.VolumePercentage]
Group=module.Volume.Display
MeterStyle=module.Volume.StyleInfoString
Meter=String
x=(#body.ElementSize#*36/24)
y=(#body.ElementSize#*12/24)
MeasureName=Module.Volume.VolumeCalc
Container=Module.Volume.Container
