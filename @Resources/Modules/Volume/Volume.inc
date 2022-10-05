[Variables]
@IncludeVolumeVariables=#@#Modules\Volume\Include\Variables.inc

[Module.Volume.StyleIconString]
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

[Module.Volume.StyleInfoString]
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.2#,#Colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Volume.VolumeReader]
Measure=Plugin
Plugin=Win7AudioPlugin
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.Volume.calc][!UpdateMeterGroup Module.Volume.Display][!Redraw]

[Module.Volume.VolumeCalc]
Group=Module.Volume.calc
Measure=Calc
Formula=max(Module.Volume.VolumeReader,0)

[Module.Volume.VolumeIconS]
Group=Module.Volume.calc
Measure=Calc
Formula=(Module.Volume.VolumeCalc=0?0:(Module.Volume.VolumeCalc<50?1:2))

[Module.Volume.Container]
Meter=Image
x=(#Module.Volume.P#-(#Module.Volume.A#*0.5)*#Module.Volume.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.Volume.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
MouseScrollUpAction=[!CommandMeasure "Module.Volume.VolumeReader" "ChangeVolume 5"][!UpdateMeasure Module.Volume.VolumeReader]
MouseScrollDownAction=[!CommandMeasure "Module.Volume.VolumeReader" "ChangeVolume -5"][!UpdateMeasure Module.Volume.VolumeReader]
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Volume_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Volume_PopUp.ini"]

[Module.Volume.VolumeIcon]
Group=module.Volume.Display
MeterStyle=Module.Volume.StyleIconString
Meter=String
x=(#Body.Element#*0.5)
y=(#Body.Element#*0.5)
MeasureName=Module.Volume.VolumeIconS
Text=Volume%1
Container=Module.Volume.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure "Module.Volume.VolumeReader" "ToggleMute"][!UpdateMeasure Module.Volume.VolumeReader]

[Module.Volume.VolumePercentage]
Group=Module.Volume.Display
MeterStyle=Module.Volume.StyleInfoString
Meter=String
x=(#Body.Element#*1.5)
y=(#Body.Element#*0.5)
MeasureName=Module.Volume.VolumeCalc
Container=Module.Volume.Container
