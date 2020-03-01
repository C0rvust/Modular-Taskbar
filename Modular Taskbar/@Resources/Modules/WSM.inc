[Variables]
module.WSM.NumIndicator=4

module.WSM.Position=302
module.WSM.Anchor=0
module.WSM.Width=(#module.WSM.NumIndicator#*#body.ElementSize#)

[module.WSM.StyleVDInd]
Group=module.WSM.VDInd
x=#body.ElementSize#r
y=r
w=#body.ElementSize#
h=#body.ElementSize#
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Face | #font.IconName#
InlinePattern3=(MI-.*?-MI)
InlineSetting4=Size | (0.75*#body.ElementSize#)
InlinePattern4=(MI-.*?-MI)
InlineSetting5=Color | #colour.2.Code#,(#colour.2.Alpha#*0.50)
InlineSetting6=Color | #colour.2.Code#,#colour.2.Alpha#
InlinePattern6=[module.WSM.VDScript.Current]
SolidColor=0,0,0,1
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1

[module.WSM.VDScript]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
ScriptFile=#@#Scripts/VirtualDesktop.ps1
UpdateDivider=-1

[module.WSM.VDScript.Total]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
Parent=module.WSM.VDScript
Line=Get-DesktopCount
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.VDScript.Current]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
Parent=module.WSM.VDScript
Line=(Get-CurrentDesktop | Get-DesktopIndex) + 1
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.PageCalc.Current]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))
DynamicVariables=1

[module.WSM.PageCalc.Prev]
Group=module.WSM.PageCalc
Measure=Calc
Formula=Clamp((module.WSM.PageCalc.Current-1),0,(ceil(module.WSM.VDScript.Total/#module.WSM.NumIndicator#)-1))

[module.WSM.PageCalc.Next]
Group=module.WSM.PageCalc
Measure=Calc
Formula=Clamp((module.WSM.PageCalc.Current+1),0,(ceil(module.WSM.VDScript.Total/#module.WSM.NumIndicator#)-1))

[Module.WSM.ControlNextAction]
Measure=Calc
Formula=((module.WSM.VDScript.Total%#module.WSM.NumIndicator#)+((ceil(module.WSM.VDScript.Total/#module.WSM.NumIndicator#)-1)-(module.WSM.PageCalc.Current)))
IfCondition=((module.WSM.VDScript.Total%#module.WSM.NumIndicator#)+((ceil(module.WSM.VDScript.Total/#module.WSM.NumIndicator#)-1)-(module.WSM.PageCalc.Current)))=0
IfTrueAction=[!CommandMeasure module.WSM.VDScript "New-Desktop | Switch-Desktop"]
IfFalseAction=[!SetOption module.WSM.PageCalc.Current formula "[module.WSM.PageCalc.Next]"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
DynamicVariables=1
Disabled=1
IfConditionMode=1
OnUpdateAction=[!DisableMeasure #CurrentSection#]

[module.WSM.IndChar.1]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+1)>module.WSM.VDScript.Total+1) ? (-1) : (((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+1)=(module.WSM.VDScript.Total+1)) ? (-2) : (#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+1)))
RegExpSubstitute=1
Substitute="^-1$":"MI-ItemEmpty-MI","^-2$":"MI-ItemAdd-MI"

[module.WSM.IndChar.2]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+2)>module.WSM.VDScript.Total+1) ? (-1) : (((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+2)=(module.WSM.VDScript.Total+1)) ? (-2) : (#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+2)))
RegExpSubstitute=1
Substitute="^-1$":"MI-ItemEmpty-MI","^-2$":"MI-ItemAdd-MI"

[module.WSM.IndChar.3]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+3)>module.WSM.VDScript.Total+1) ? (-1) : (((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+3)=(module.WSM.VDScript.Total+1)) ? (-2) : (#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+3)))
RegExpSubstitute=1
Substitute="^-1$":"MI-ItemEmpty-MI","^-2$":"MI-ItemAdd-MI"

[module.WSM.IndChar.4]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+4)>module.WSM.VDScript.Total+1) ? (-1) : (((#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+4)=(module.WSM.VDScript.Total+1)) ? (-2) : (#module.WSM.NumIndicator#*module.WSM.PageCalc.Current+4)))
RegExpSubstitute=1
Substitute="^-1$":"MI-ItemEmpty-MI","^-2$":"MI-ItemAdd-MI"

[Module.WSM.IndAct.1]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.IndChar.1=module.WSM.VDScript.Current) ? (((module.WSM.IndChar.1=1) && (module.WSM.VDScript.Total=1)) ? (-2) : (module.WSM.IndChar.1-0.5)) : (module.WSM.IndChar.1-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.IndAct.2]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.IndChar.2=module.WSM.VDScript.Current) ? (((module.WSM.IndChar.2=1) && (module.WSM.VDScript.Total=1)) ? (-2) : (module.WSM.IndChar.2-0.5)) : (module.WSM.IndChar.2-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.IndAct.3]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.IndChar.3=module.WSM.VDScript.Current) ? (((module.WSM.IndChar.3=1) && (module.WSM.VDScript.Total=1)) ? (-2) : (module.WSM.IndChar.3-0.5)) : (module.WSM.IndChar.3-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.IndAct.4]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.IndChar.4=module.WSM.VDScript.Current) ? (((module.WSM.IndChar.4=1) && (module.WSM.VDScript.Total=1)) ? (-2) : (module.WSM.IndChar.4-0.5)) : (module.WSM.IndChar.4-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[module.WSM.Container]
Meter=Image
x=(#module.WSM.Position#-(#module.WSM.Anchor#*0.5)*#module.WSM.Width#)
y=#body.Padding#
w=#module.WSM.Width#
h=#body.ElementSize#
SolidColor=0,0,0
MouseOverAction=[!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
MouseLeaveAction=[!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.Control.PrevPage]
Group=module.WSM.VDInd
Meter=Image
w=(#module.WSM.Width#*0.5)
h=#body.ElementSize#
SolidColor=0,0,0,1
Container=module.WSM.Container
RightMouseUpAction=[!SetOption module.WSM.PageCalc.Current formula "[module.WSM.PageCalc.Prev]"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.Control.NextPage]
Group=module.WSM.VDInd
Meter=Image
x=R
w=(#module.WSM.Width#*0.5)
h=#body.ElementSize#
SolidColor=0,0,0,1
Container=module.WSM.Container
RightMouseUpAction=[!EnableMeasure Module.WSM.ControlNextAction][!UpdateMeasure Module.WSM.ControlNextAction][!UpdateMeterGroup Module.WSM.ControlNextAction][!Redraw]

[module.WSM.VDInd.Dummy]
Meter=String
x=(#body.ElementSize#*-12/24)
y=(#body.ElementSize#*12/24)
Container=module.WSM.Container

[module.WSM.VDInd.1]
MeterStyle=module.WSM.StyleVDInd
Meter=String
MeasureName=module.WSM.IndChar.1
Container=module.WSM.Container
LeftMouseUpAction=[!CommandMeasure module.WSM.VDScript "[Module.WSM.IndAct.1]"][!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.VDInd.2]
MeterStyle=module.WSM.StyleVDInd
Meter=String
MeasureName=module.WSM.IndChar.2
Container=module.WSM.Container
LeftMouseUpAction=[!CommandMeasure module.WSM.VDScript "[Module.WSM.IndAct.2]"][!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.VDInd.3]
MeterStyle=module.WSM.StyleVDInd
Meter=String
MeasureName=module.WSM.IndChar.3
Container=module.WSM.Container
LeftMouseUpAction=[!CommandMeasure module.WSM.VDScript "[Module.WSM.IndAct.3]"][!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.VDInd.4]
MeterStyle=module.WSM.StyleVDInd
Meter=String
MeasureName=module.WSM.IndChar.4
Container=module.WSM.Container
LeftMouseUpAction=[!CommandMeasure module.WSM.VDScript "[Module.WSM.IndAct.4]"][!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.VDScript.Current-1)/#module.WSM.NumIndicator#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
