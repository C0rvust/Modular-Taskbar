[Metadata]
Name=WSM
Description=Displays virtual desktop info. Click a number to navigate to that workspace. Click the highlighted (current) workspace to remove it. Click a + sign to create new workspace. Right click on either end to jump to a new page.

[Variables]
module.WSM.Position=86
module.WSM.Anchor=0

; Do not change
module.WSM.NoInd=4
module.WSM.Width=(#module.WSM.NoInd#*#body.ElementSize#)

[module.WSM.StyleVDInd]
Group=module.WSM.VDInd
x=#body.ElementSize#r
y=r
w=#body.ElementSize#
h=#body.ElementSize#
MeasureName=#CurrentSection#.Calc
InlineSetting=Face | #font.DisplayName#
InlineSetting2=Size | #font.SizeStd#
InlineSetting3=Face | #font.IconName#
InlinePattern3=(ItemEmpty|ItemAdd)
InlineSetting4=Size | (0.75*#body.ElementSize#)
InlinePattern4=(ItemEmpty|ItemAdd)
InlineSetting5=Color | #colour.2.Code#,(#colour.2.Alpha#*0.50)
InlineSetting6=Color | #colour.2.Code#,#colour.2.Alpha#
InlinePattern6=[module.WSM.PSRM.Current]
SolidColor=0,0,0,1
StringAlign=CenterCenter
AntiAlias=1
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure module.WSM.PSRM "[#CurrentSection#.Act]" ][!SetOption module.WSM.PageCalc.Current formula "(floor((module.WSM.PSRM.Current-1)/#module.WSM.NoInd#))"][!UpdateMeasureGroup module.WSM.VirtualDesktop][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
Container=module.WSM.Container

[module.WSM.PSRM]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
ScriptFile=#@#includes\WSM\VirtualDesktop.ps1

[module.WSM.PSRM.Total]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
Parent=module.WSM.PSRM
Line=Get-DesktopCount
UpdateDivider=(500/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.PSRM.Current]
Group=module.WSM.VirtualDesktop
Measure=Plugin
Plugin=PowershellRM
Parent=module.WSM.PSRM
Line=(Get-CurrentDesktop | Get-DesktopIndex) + 1
UpdateDivider=(500/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

[module.WSM.PageCalc]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(floor((module.WSM.PSRM.Current-1)/#module.WSM.NoInd#))
DynamicVariables=1

[module.WSM.PageCalc.Prev]
Group=module.WSM.PageCalc
Measure=Calc
Formula=Clamp((module.WSM.PageCalc-1),0,(ceil(module.WSM.PSRM.Total/#module.WSM.NoInd#)-1))

[module.WSM.PageCalc.Next]
Group=module.WSM.PageCalc
Measure=Calc
Formula=Clamp((module.WSM.PageCalc+1),0,(ceil(module.WSM.PSRM.Total/#module.WSM.NoInd#)-1))

[Module.WSM.ControlNextAction]
Measure=Calc
Formula=((module.WSM.PSRM.Total%#module.WSM.NoInd#)+((ceil(module.WSM.PSRM.Total/#module.WSM.NoInd#)-1)-(module.WSM.PageCalc)))
IfCondition=((module.WSM.PSRM.Total%#module.WSM.NoInd#)+((ceil(module.WSM.PSRM.Total/#module.WSM.NoInd#)-1)-(module.WSM.PageCalc)))=0
IfTrueAction=[!CommandMeasure module.WSM.PSRM "New-Desktop | Switch-Desktop"]
IfFalseAction=[!SetOption module.WSM.PageCalc formula "[module.WSM.PageCalc.Next]"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
DynamicVariables=1
Disabled=1
IfConditionMode=1
OnUpdateAction=[!DisableMeasure #CurrentSection#]

[module.WSM.VDInd.1.Calc]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NoInd#*module.WSM.PageCalc+1)>module.WSM.PSRM.Total+1) ? (-1) : (((#module.WSM.NoInd#*module.WSM.PageCalc+1)=(module.WSM.PSRM.Total+1)) ? (-2) : (#module.WSM.NoInd#*module.WSM.PageCalc+1)))
RegExpSubstitute=1
Substitute="^-1$":"ItemEmpty","^-2$":"ItemAdd"

[module.WSM.VDInd.2.Calc]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NoInd#*module.WSM.PageCalc+2)>module.WSM.PSRM.Total+1) ? (-1) : (((#module.WSM.NoInd#*module.WSM.PageCalc+2)=(module.WSM.PSRM.Total+1)) ? (-2) : (#module.WSM.NoInd#*module.WSM.PageCalc+2)))
RegExpSubstitute=1
Substitute="^-1$":"ItemEmpty","^-2$":"ItemAdd"

[module.WSM.VDInd.3.Calc]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NoInd#*module.WSM.PageCalc+3)>module.WSM.PSRM.Total+1) ? (-1) : (((#module.WSM.NoInd#*module.WSM.PageCalc+3)=(module.WSM.PSRM.Total+1)) ? (-2) : (#module.WSM.NoInd#*module.WSM.PageCalc+3)))
RegExpSubstitute=1
Substitute="^-1$":"ItemEmpty","^-2$":"ItemAdd"

[module.WSM.VDInd.4.Calc]
Group=module.WSM.PageCalc
Measure=Calc
Formula=(((#module.WSM.NoInd#*module.WSM.PageCalc+4)>module.WSM.PSRM.Total+1) ? (-1) : (((#module.WSM.NoInd#*module.WSM.PageCalc+4)=(module.WSM.PSRM.Total+1)) ? (-2) : (#module.WSM.NoInd#*module.WSM.PageCalc+4)))
RegExpSubstitute=1
Substitute="^-1$":"ItemEmpty","^-2$":"ItemAdd"

[Module.WSM.VDInd.1.Act]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.VDInd.1.Calc=module.WSM.PSRM.Current) ? (((module.WSM.VDInd.1.Calc=1) && (module.WSM.PSRM.Total=1)) ? (-2) : (module.WSM.VDInd.1.Calc-0.5)) : (module.WSM.VDInd.1.Calc-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.VDInd.2.Act]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.VDInd.2.Calc=module.WSM.PSRM.Current) ? (((module.WSM.VDInd.2.Calc=1) && (module.WSM.PSRM.Total=1)) ? (-2) : (module.WSM.VDInd.2.Calc-0.5)) : (module.WSM.VDInd.2.Calc-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.VDInd.3.Act]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.VDInd.3.Calc=module.WSM.PSRM.Current) ? (((module.WSM.VDInd.3.Calc=1) && (module.WSM.PSRM.Total=1)) ? (-2) : (module.WSM.VDInd.3.Calc-0.5)) : (module.WSM.VDInd.3.Calc-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[Module.WSM.VDInd.4.Act]
Group=module.WSM.PageCalc
Measure=Calc
Formula=((module.WSM.VDInd.4.Calc=module.WSM.PSRM.Current) ? (((module.WSM.VDInd.4.Calc=1) && (module.WSM.PSRM.Total=1)) ? (-2) : (module.WSM.VDInd.4.Calc-0.5)) : (module.WSM.VDInd.4.Calc-1))
RegExpSubstitute=1
Substitute="^-3$":"New-desktop | Switch-Desktop","^-2$":"","^(\d{0,})\.5$":"Remove-Desktop \1","^(\d){1,}$":"Switch-Desktop \1"
DynamicVariables=1

[module.WSM.Container]
Meter=Image
x=(#module.WSM.Position#-(#module.WSM.Anchor#*0.5)*#module.WSM.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.WSM.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1
MouseOverAction=[!SetOption module.WSM.PageCalc formula "(floor((module.WSM.PSRM.Current-1)/#module.WSM.NoInd#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
MouseLeaveAction=[!SetOption module.WSM.PageCalc formula "(floor((module.WSM.PSRM.Current-1)/#module.WSM.NoInd#))"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]
MouseActionCursor=0

[module.WSM.Control.PrevPage]
Group=module.WSM.VDInd
Meter=Image
w=(#module.WSM.Width#*0.5)
h=#body.ElementSize#
SolidColor=0,0,0,1
Container=module.WSM.Container
RightMouseUpAction=[!SetOption module.WSM.PageCalc formula "[module.WSM.PageCalc.Prev]"][!UpdateMeasureGroup module.WSM.PageCalc][!UpdateMeterGroup module.WSM.VDInd][!Redraw]

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

[Module.WSM.VDInd.1]
MeterStyle=module.WSM.StyleVDInd
Meter=String

[Module.WSM.VDInd.2]
MeterStyle=module.WSM.StyleVDInd
Meter=String

[Module.WSM.VDInd.3]
MeterStyle=module.WSM.StyleVDInd
Meter=String

[module.WSM.VDInd.4]
MeterStyle=module.WSM.StyleVDInd
Meter=String
