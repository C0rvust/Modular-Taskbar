[Rainmeter]
SkinWidth=(#Skin.Width#+2*#Body.Border#)
SkinHeight=(#Skin.Height#+2*#Body.Border#)
Update=#UpdateInterval#
DefaultUpdateDivider=-1
AccurateText=1
OnRefreshAction=[!CommandMeasure Main.ActionTimer "Stop 1" "#RootConfig#"][!Move "#Skin.X#" "#Skin.Y#"][!Update]
MouseLeaveAction=[!CommandMeasure Main.ActionTimer "Execute 1" "#RootConfig#"]
MouseOverAction=[!CommandMeasure Main.ActionTimer "Stop 1" "#RootConfig#"]
DefaultAlwaysOnTop=2

[Variables]
@IncludeVar=#@#variables.inc
UpdateInterval=1000

; Dicatates popup size
Skin.Width=(#Body.Element#*#var#)
Skin.Height=(#Body.Element#*10)

; Do not change
Parent.Position=0
Skin.X=(clamp((#Body.X#+#Parent.Position#-#Skin.Width#/2),(#Body.X#),(#Body.X#+(#Body.Width#+2*#Body.Border#)-#Skin.Width#)))
Skin.Y=(((#Body.Y#+#Body.Height#/2)<(#ScreenAreaHeight#/2)?(#Body.Y#+#Body.Height#+#Body.PopUp#+2*#Body.Border#):(#Body.Y#-#body.PopUp#-#Skin.Height#-2*#Body.Border#)))

[Module.Template.Border]
Meter=Shape
Shape=Rectangle 0,0,(#Skin.Width#+2*#Body.Border#),(#Skin.Height#+2*#Body.Border#),(#Body.Corner#+#Body.Border#) | StrokeWidth 0 | Fill Color #Colour.4#,#Colour.4.Alpha#

[Module.Template.Container]
Meter=Shape
x=#Body.Border#
y=#Body.Border#
Shape=Rectangle 0,0,#Skin.Width#,#Skin.Height#,#Body.Corner# | StrokeWidth 0 | Fill Color #Colour.1#,#Colour.1.Alpha#