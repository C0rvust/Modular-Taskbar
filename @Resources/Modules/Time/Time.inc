[Variables]
@IncludeTimeVariables=#@#Modules\Time\Include\Variables.inc

[Module.Time.StyleInfoString]
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.2#,#Colour.2.Alpha#
InlineSetting4=Color | #Colour.2#,(#Colour.2.Alpha#*([Module.Time.Time.S]%2=0?0.5:1))
InlinePattern4=:
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Time.Time.S]
Measure=Time
Format=%S
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeter Module.Time.TimeDisplay]

[Module.Time.Time.HM]
Measure=Time
Format=%H : %M
UpdateDivider=(5000/#UpdateInterval#)
OnChangeAction=[!UpdateMeter Module.Time.TimeDisplay]

[Module.Time.Container]
Meter=Image
x=(#Body.Border#+#Module.Time.P#-(#Module.Time.A#*0.5)*#Module.Time.W#)
y=((#Skin.Height#-#Body.Element#)/2)
w=#Module.Time.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Time_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Time_PopUp.ini"]

[Module.Time.TimeDisplay]
Group=Module.Time.Display
MeterStyle=Module.Time.StyleInfoString
Meter=String
x=#Body.Element#
y=(#Body.Element#*12/24)
MeasureName=Module.Time.Time.HM
DynamicVariables=1
Container=Module.Time.Container