[Variables]
@IncludePowerVariables=#@#Modules\Power\Include\Variables.inc

[Module.Power.StyleIconString]
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

[Module.Power.Container]
Meter=Image
x=(#Module.Power.P#-(#Module.Power.A#*0.5)*#Module.Power.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.Power.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1

[Module.Power.PowerIcon]
MeterStyle=Module.Power.StyleIconString
Meter=String
x=(#Body.Element#*0.5)
y=(#Body.Element#*0.5)
Text=PowerDown
Container=module.Power.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Power_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Power_PopUp.ini"]
