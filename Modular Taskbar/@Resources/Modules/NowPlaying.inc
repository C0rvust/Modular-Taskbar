[Metadata]
Name=NowPlaying
Description=Displays music info & controls music playing. Click to play/pause. Click the prev/next arrows to navigate. Right click to open popup; popup contains track progress/control & player changer.

[Variables]
module.NowPlaying.Position=750
module.NowPlaying.Anchor=1

; Controls size of song info
module.NowPlaying.InfoLength=(9*#body.ElementSize#)

; Controls song info format - %1 references Title, %2 references Artist(s)
module.NowPlaying.InfoFormat=%1
module.NowPlaying.InfoScrollSpeed=1

; Do not change
module.NowPlaying.Width=(#body.ElementSize#*2+#body.Padding#*2+#module.NowPlaying.InfoLength#)

[module.NowPlaying.StyleIconString]
InlineSetting=Face | #font.IconName#
InlineSetting2=Size | (0.75*#body.ElementSize#)
InlineSetting3=Color | #colour.2.Code#,(#colour.2.Alpha#*(1-(Cos([Module.NowPlaying.ControlAnimation]/100*PI/2))))
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.NowPlaying.StyleInfoString]
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Color | #colour.2.Code#,#colour.2.Alpha#
StringAlign=LeftCenter
AntiAlias=1
DynamicVariables=1

[NowPlayingMeasures]
@IncludeNowPlayingMeasures=#@#includes\NowPlaying\NowPlayingMeasure.inc

[module.NowPlaying.NPInfo.Title]
Group=NPMeasure | Module.NowPlaying.Title
Measure=String
String=[NowPlaying.Title]
DynamicVariables=1
RegExpSubstitute=1
Substitute="^$":"N/A"
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.Info]

[module.NowPlaying.NPInfo.Artist]
Group=NPMeasure | Module.NowPlaying.Artist
Measure=String
String=[NowPlaying.Artist]
DynamicVariables=1
RegExpSubstitute=1
Substitute="^$":"N/A"
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.Info]

[module.NowPlaying.NPInfo.Progress]
Group=NPMeasure | Module.NowPlaying.Progress
Measure=Calc
Formula=[NowPlaying.Progress]
DynamicVariables=1
OnChangeAction=[!UpdateMeasureGroup NowPlaying.Utilise.Progress][!UpdateMeterGroup NowPlaying.Utilise.Progress]

[Module.NowPlaying.NPInfo.InfoWidth]
Measure=Calc
Formula=[Module.NowPlaying.InfoSource:W]
DynamicVariables=1

[Module.NowPlaying.PreviousAction]
Group=NPMeasure | NowPlaying.Utilise.Progress
Measure=Calc
Formula=module.NowPlaying.NPInfo.Progress<2 ? 0 : 1
Substitute="0":"Previous","1":"SetPosition 0"
DynamicVariables=1

[Module.NowPlaying.ControlAnimation]
Measure=Loop
StartValue=0
EndValue=100
Increment=10
IfCondition=(#CurrentSection#=100) || (#CurrentSection#=0)
IfTrueAction=[!PauseMeasure #CurrentSection#]
UpdateDivider=1
OnChangeAction=[!UpdateMeterGroup NowPlaying.ControlAnimation]

[Module.NowPlaying.Scroller]
Measure=Loop
StartValue=0
EndValue=([Module.NowPlaying.NPInfo.InfoWidth]+#body.ElementSize#)
Increment=#module.NowPlaying.InfoScrollSpeed#
LoopCount=1
IfCondition=((Module.NowPlaying.NPInfo.InfoWidth<=#module.NowPlaying.InfoLength#) || (#CurrentSection#=(Module.NowPlaying.NPInfo.InfoWidth+#body.ElementSize#)))
IfTrueAction=[!UpdateMeterGroup Module.NowPlaying.InfoActual][!CommandMeasure #CurrentSection# "Reset"][!DisableMeasure #CurrentSection#]
Disabled=1
DynamicVariables=1
UpdateDivider=1
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.InfoActual][!Redraw]

[Module.NowPlaying.Container]
Group=Module.NowPlaying.Info
Meter=Image
x=(#module.NowPlaying.Position#-(#module.NowPlaying.Anchor#*0.5)*#module.NowPlaying.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.NowPlaying.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure "NowPlaying.Title" "PlayPause"]
RightMouseUpAction=#UpdateCoord#[!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\NowPlaying_PopUp.ini"][!ToggleConfig "#ROOTCONFIG#\PopUp" "NowPlaying_PopUp.ini"]
MouseOverAction=[!SetOption Module.NowPlaying.ControlAnimation InvertMeasure 0][!UnPauseMeasure Module.NowPlaying.ControlAnimation][!UpdateMeasure Module.NowPlaying.ControlAnimation]
MouseLeaveAction=[!SetOption Module.NowPlaying.ControlAnimation InvertMeasure 1][!UnPauseMeasure Module.NowPlaying.ControlAnimation][!UpdateMeasure Module.NowPlaying.ControlAnimation]
OnUpdateAction=[!UpdateMeter Module.NowPlaying.ContainerInfo]

[Module.NowPlaying.ContainerInfo]
Meter=Image
x=([Module.NowPlaying.Container:x]+([Module.NowPlaying.Container:w]-#module.NowPlaying.InfoLength#)/2)
y=[Module.NowPlaying.Container:y]
w=#module.NowPlaying.InfoLength#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
MouseOverAction=[!UpdateMeasure Module.NowPlaying.Scroller][!EnableMeasure Module.NowPlaying.Scroller]

[Module.NowPlaying.InfoSource]
Group=Module.NowPlaying.Info
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=module.NowPlaying.NPInfo.Title
MeasureName2=module.NowPlaying.NPInfo.Artist
Text=#module.NowPlaying.InfoFormat#
y=(#body.ElementSize#*2)
OnUpdateAction=[!UpdateMeasure Module.NowPlaying.NPInfo.InfoWidth]
Container=Module.NowPlaying.Container

[Module.NowPlaying.ControlPrevious]
Group=Module.NowPlaying.Info | NowPlaying.Utilise.Progress | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleIconString
Meter=String
x=(#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=Previous
Container=Module.NowPlaying.Container
LeftMouseUpAction=[!CommandMeasure "NowPlaying.Title" "[Module.NowPlaying.PreviousAction]"]

[Module.NowPlaying.ControlNext]
Group=Module.NowPlaying.Info | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleIconString
Meter=String
x=(#module.NowPlaying.Width#-#body.ElementSize#*12/24)
y=(#body.ElementSize#*12/24)
Text=Next
Container=Module.NowPlaying.Container
LeftMouseUpAction=[!CommandMeasure "NowPlaying.Title" "Next"]

[Module.NowPlaying.InfoPrimary]
Group=Module.NowPlaying.Info | Module.NowPlaying.InfoActual
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=module.NowPlaying.NPInfo.Title
MeasureName2=module.NowPlaying.NPInfo.Artist
Text=#module.NowPlaying.InfoFormat#
x=((([Module.NowPlaying.NPInfo.InfoWidth]>=#module.NowPlaying.InfoLength#)?0:(#module.NowPlaying.InfoLength#-[Module.NowPlaying.NPInfo.InfoWidth])/2)-[Module.NowPlaying.Scroller])
y=(#body.ElementSize#*12/24)
Container=Module.NowPlaying.ContainerInfo

[Module.NowPlaying.InfoSecondary]
Group=Module.NowPlaying.Info | Module.NowPlaying.InfoActual
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=module.NowPlaying.NPInfo.Title
MeasureName2=module.NowPlaying.NPInfo.Artist
Text=#module.NowPlaying.InfoFormat#
x=#body.ElementSize#R
y=r
Hidden=(([Module.NowPlaying.NPInfo.InfoWidth]>#module.NowPlaying.InfoLength#)?0:1)
Container=Module.NowPlaying.ContainerInfo
