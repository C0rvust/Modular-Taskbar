[Variables]
@IncludeBatteryVariables=#@#Modules\Battery\Include\Variables.inc

[Module.Battery.StyleIconString]
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

[Module.Battery.StyleInfoString]
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.2#,#Colour.2.Alpha#
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

[Module.Battery.Container]
Meter=Image
x=(#Module.Battery.P#-(#Module.Battery.A#*0.5)*#Module.Battery.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.Battery.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Battery_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Battery_PopUp.ini"]

[module.Battery.BatteryIcon]
MeterStyle=module.Battery.StyleIconString
Meter=String
x=(#Body.Element#*0.5)
y=(#Body.Element#*0.5)
Text=Battery
Container=Module.Battery.Container
; LeftMouseUpAction=[]
; MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*0.5)"][!UpdateMeter "#CurrentSection#"]
; MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]

[Module.Battery.PercentageDisplay]
Group=Module.Battery.Display
MeterStyle=Module.Battery.StyleInfoString
Meter=String
x=(#Body.Element#*1.5)
y=(#Body.Element#*0.5)
MeasureName=Module.Battery.BatteryPercentage
Container=Module.Battery.Container
