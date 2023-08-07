[Variables]
@IncludeNetworkVariables=#@#Modules\Network\Include\Variables.inc

[Module.Network.StyleIconString]
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

[Module.Network.StyleInfoString]
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.2#,#Colour.2.Alpha#
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[Module.Network.ConnectivityReader]
Measure=SysInfo
SysInfoType=INTERNET_CONNECTIVITY
SysInfoData=Best
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.Network.calc][!UpdateMeterGroup Module.Network.Display][!Redraw]
Substitute="-1":"NA","1":"OK"

[Module.Network.NetworkIconS]
Group=Module.Network.calc
Measure=Calc
Formula=(Module.Network.ConnectivityReader=-1?0:(Module.Network.ConnectivityReader=1?1:0))

[Module.Network.Container]
Meter=Image
x=(#Body.Border#+#Module.Network.P#-(#Module.Network.A#*0.5)*#Module.Network.W#)
y=((#Skin.Height#-#Body.Element#)/2)
w=#Module.Network.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\Network_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "Network_PopUp.ini"]

[Module.Network.NetworkIcon]
Group=module.Network.Display
MeterStyle=Module.Network.StyleIconString
Meter=String
x=(#Body.Element#*0.5)
y=(#Body.Element#*0.5)
MeasureName=Module.Network.NetworkIconS
Text=Network%1
Container=Module.Network.Container

[Module.Network.ConnectivityDisplay]
Group=Module.Network.Display
MeterStyle=Module.Network.StyleInfoString
Meter=String
x=(#Body.Element#*1.5)
y=(#Body.Element#*0.5)
MeasureName=Module.Network.ConnectivityReader
Container=Module.Network.Container
