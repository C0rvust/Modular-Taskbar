[Variables]
ScrollPos=0
ScrollSpeed=8
NumInteractable=0
InteractableH=(#Element#+2*#Padding#)

[Setting.StyleBlockShape]
x=#Padding#
y=(#Padding#+[#CurrentSection#:h])r
w=([Setting.Container:w]-2*#Padding#)
h=#InteractableH#
Shape=Rectangle 0,0,[#CurrentSection#:w],[#CurrentSection#:h],#Padding# | StrokeWidth 0 | Fill Color #Colour.Foreground#,#Colour.Foreground.Alpha#
DynamicVariables=1
Hidden=1
Container=Setting.Container

[Setting.StyleLabelString]
x=(2*#Padding#)
y=(#Padding#+[#CurrentSection#:h])r
h=(#Element#+2*#Padding#)
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.Element#,#Colour.Element.Alpha#
InlineSetting4=Weight | 900
; InlinePattern4=^(.{1,}?)(?:\s-\s\[.{1,}?\]$|$)
StringAlign=LeftCenter
SolidColor=0,0,0,1
AntiAlias=1
DynamicVariables=1
Hidden=1
Container=Setting.Container

[Setting.StyleValueString]
x=([Setting.Container:w]-4*#Padding#-[Button.0:w])
y=(#Padding#+[#CurrentSection#:h])r
h=(#Element#+2*#Padding#)
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.Element#,#Colour.Element.Alpha#
InlineSetting4=Color | 0,223,0,#Colour.Element.Alpha#
InlinePattern4=^Active$
InlineSetting5=Color | 223,0,0,#Colour.Element.Alpha#
InlinePattern5=^Inactive$
StringAlign=RightCenter
SolidColor=0,0,0,1
AntiAlias=1
DynamicVariables=1
Hidden=1
Container=Setting.Container

[Setting.StyleButtonString]
x=([Setting.Container:w]-#Element#*0.5-2*#Padding#)
y=(#Padding#+[#CurrentSection#:h])r
h=(#Element#+2*#Padding#)
w=#Element#
Text=MenuMeatball
InlineSetting=Face | #Font.Icon#
InlineSetting2=Size | #Font.IconS#
InlineSetting3=Color | #Colour.Element#,#Colour.Element.Alpha#
InlineSetting4=Color | 0,0,0,0
InlinePattern4=Highlight
InlineSetting5=CharacterSpacing | 0 | (-#Font.IconS#)
InlinePattern5=Highlight
StringAlign=CenterCenter
SolidColor=0,0,0,1
Prefix=Highlight
AntiAlias=1
DynamicVariables=1
Hidden=1
Container=Setting.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.Highlight*#,(#*Colour.Highlight.Alpha*#*0.5)"][!UpdateMeter "#CurrentSection#"][!Redraw]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"][!Redraw]



[Setting.Container]
Meter=Shape
x=#SideBarWidth#
y=#TopBarWidth#
w=(#Skin.Width#-#SideBarWidth#)
h=(#Skin.Height#-#TopBarWidth#)
Shape=Rectangle 0,0,[#CurrentSection#:w],[#CurrentSection#:h] | StrokeWidth 0 | Fill Color 0,0,0
DynamicVariables=1
MouseActionCursor=0
MouseScrollUpAction=[!SetVariable ScrollPos "(clamp((#ScrollPos#+#ScrollSpeed#),(min([Setting.Container:h]-(#NumInteractable#*(#InteractableH#+#Padding#)+#Padding#),0)),0))"][!UpdateMeter #CurrentSection#][!UpdateMeterGroup Interactable][!Redraw]
MouseScrollDownAction=[!SetVariable ScrollPos "(clamp((#ScrollPos#-#ScrollSpeed#),(min([Setting.Container:h]-(#NumInteractable#*(#InteractableH#+#Padding#)+#Padding#),0)),0))"][!UpdateMeter #CurrentSection#][!UpdateMeterGroup Interactable][!Redraw]

[Interactable]
@IncludeInt=#@#Settings\Interactable.inc