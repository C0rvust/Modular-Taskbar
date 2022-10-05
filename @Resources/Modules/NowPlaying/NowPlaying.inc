[Variables]
@IncludeNowPlayingVariables=#@#Modules\NowPlaying\Include\Variables.inc
@IncludeMediaSwitcher=#@#Modules\NowPlaying\Include\MediaSwitcher.inc

[Module.NowPlaying.StyleIconString]
InlineSetting=Face | #Font.Icon#
InlineSetting2=Size | #Font.IconS#
InlineSetting3=Color | #Colour.2#,(#Colour.2.Alpha#*[Module.NowPlaying.ControlAnimation]/100)
InlineSetting4=Color | 0,0,0,0
InlinePattern4=Highlight
InlineSetting5=CharacterSpacing | 0 | (-[#CurrentSection#:h]*0.75)
InlinePattern5=Highlight
StringAlign=CenterCenter
Prefix=Highlight
AntiAlias=1
DynamicVariables=1

[Module.NowPlaying.StyleInfoString]
InlineSetting=Face | #Font.Display#
InlineSetting2=Size | #Font.DisplayS#
InlineSetting3=Color | #Colour.2#,(#Colour.2.Alpha#*(1-0.5*[Module.NowPlaying.ControlAnimation]/100))
StringAlign=LeftCenter
AntiAlias=1
DynamicVariables=1

[Module.NowPlaying.Title]
Group=MS.Media | MS.NP.Title
Measure=String
String=[&MS.[#NowPlaying.PlayerPlugin].Title]
DynamicVariables=1
RegExpSubstitute=1
Substitute="^$":"N/A","(\(.*?\))|(\[.*?\])|(\s#[\S]*)|(^\-)|^(\s*)|(\s*)$":"","\s\s":" "
; Substitute="^$":"N/A"
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.Display]

[Module.NowPlaying.Artist]
Group=MS.Media | MS.NP.Artist
Measure=String
String=[&MS.[#NowPlaying.PlayerPlugin].Artist]
DynamicVariables=1
RegExpSubstitute=1
Substitute="^$":"N/A"
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.Display]

[Module.NowPlaying.Progress]
Group=MS.Media | MS.NP.Progress
Measure=Calc
Formula=[&MS.[#NowPlaying.PlayerPlugin].Progress]
DynamicVariables=1
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Progress][!UpdateMeterGroup Module.NowPlaying.Progress]

[Module.NowPlaying.State]
Group=MS.Media | MS.NP.State
Measure=Calc
Formula=[&MS.[#NowPlaying.PlayerPlugin].State]
DynamicVariables=1
RegExpSubstitute=1
Substitute="0":"Play","1":"Pause","2":"Play"
OnChangeAction=[!UpdateMeterGroup Module.NowPlaying.State]

[Module.NowPlaying.DisplayW]
Measure=Calc
Formula=[Module.NowPlaying.DisplaySource:W]
DynamicVariables=1

[Module.NowPlaying.PreviousAction]
Group=Module.NowPlaying.Progress
Measure=Calc
Formula=Module.NowPlaying.Progress<2 ? 0 : 1
Substitute="0":"Previous","1":"SetPosition 0"

[Module.NowPlaying.ControlAnimation]
Measure=Loop
StartValue=0
EndValue=100
Increment=25
IfCondition=(#CurrentSection#=100) || (#CurrentSection#=0)
IfTrueAction=[!PauseMeasure #CurrentSection#]
UpdateDivider=(30/#UpdateInterval#)
OnChangeAction=[!UpdateMeterGroup NowPlaying.ControlAnimation]

[Module.NowPlaying.DisplayAnimation]
Measure=Loop
StartValue=0
EndValue=([Module.NowPlaying.DisplayW]+#Body.Element#)
Increment=1
LoopCount=1
IfCondition=((Module.NowPlaying.DisplayW<=#Module.NowPlaying.DisplayW#) || (#CurrentSection#=(Module.NowPlaying.DisplayW+#Body.Element#)))
IfTrueAction=[!UpdateMeterGroup NowPlaying.DisplayAnimation][!CommandMeasure #CurrentSection# "Reset"][!DisableMeasure #CurrentSection#]
Disabled=1
DynamicVariables=1
UpdateDivider=(30/#UpdateInterval#)
OnChangeAction=[!UpdateMeterGroup NowPlaying.DisplayAnimation][!Redraw]

[Module.NowPlaying.PSRM]
Measure=Plugin
Plugin=PowershellRM
Param=214,85,113|255|178|6
Line=$Saved=$RmAPI.OptionStr("Param")
Line2=$Var0=$RmAPI.VariableStr("Colour.2"); $Var1=$RmAPI.VariableStr("Colour.2.Alpha"); $Var2=$RmAPI.VariableStr("Module.NowPlaying.MiniCoverSize"); $Var3=$RmAPI.VariableStr("Body.Corner"); $Exist=[System.IO.File]::Exists("#@#Modules\NowPlaying\Include\CoverMM.png"); $Var="$Var0|$Var1|$Var2|$Var3"
Line3=if(($Saved -ne $Var) -or ($Exist -eq $False)) {$RmAPI.Bang("!WriteKeyValue $($RmAPI.GetMeasureName()) Param `"`"`"$Var`"`"`" `"`"`"$($RmAPI.VariableStr("@") + "Modules\NowPlaying\NowPlaying.inc")`"`"`" "); $RmAPI.Bang("!EnableMeasure Module.NowPlaying.MM.CoverMiniDefault"); $RmAPI.Bang("!CommandMeasure Module.NowPlaying.MM.CoverMiniDefault Update")}

[Module.NowPlaying.MM.CoverMiniDefault]
Measure=Plugin
Plugin=MagickMeter
Image=File #@#Modules\NowPlaying\Include\Cover.png | AdaptiveResize #Module.NowPlaying.MiniCoverSize#,#Module.NowPlaying.MiniCoverSize#
Image2=Rectangle 0,0,#Module.NowPlaying.MiniCoverSize#,#Module.NowPlaying.MiniCoverSize#,#Body.Corner# | Color #Colour.2#,#Colour.2.Alpha#
Image3=Combine Image2 | DstOutComp Image
DynamicVariables=1
ExportTo=#@#Modules\NowPlaying\Include\CoverMM.png
Disabled=1
OnFinishAction=[!DisableMeasure #CurrentSection#]

[Module.NowPlaying.Container]
Group=Module.NowPlaying.Display
Meter=Image
x=(#Module.NowPlaying.P#-(#Module.NowPlaying.A#*0.5)*#Module.NowPlaying.W#)
y=((#Body.Height#-#Body.Element#)/2)
w=#Module.NowPlaying.W#
h=#Body.Element#
SolidColor=0,0,0
DynamicVariables=1
LeftMouseUpAction=[!CommandMeasure Main.PSRM "Update"][!WriteKeyValue Variables Parent.Position "([#CurrentSection#:x]+[#CurrentSection#:w]/2)" "#RootConfigPath#\PopUp\NowPlaying_PopUp.ini"][!ActivateConfig "#ROOTCONFIG#\PopUp" "NowPlaying_PopUp.ini"]
MouseOverAction=[!UnPauseMeasure Module.NowPlaying.ControlAnimation][!SetOption Module.NowPlaying.ControlAnimation InvertMeasure 0][!UpdateMeasure Module.NowPlaying.ControlAnimation]
MouseLeaveAction=[!UnPauseMeasure Module.NowPlaying.ControlAnimation][!SetOption Module.NowPlaying.ControlAnimation InvertMeasure 1][!UpdateMeasure Module.NowPlaying.ControlAnimation]
OnUpdateAction=[!UpdateMeter Module.NowPlaying.ContainerInfo]

[Module.NowPlaying.ContainerInfo]
Meter=Image
x=([Module.NowPlaying.Container:x]+([Module.NowPlaying.Container:w]-#Module.NowPlaying.DisplayW#)/2)
y=[Module.NowPlaying.Container:y]
w=#Module.NowPlaying.DisplayW#
h=#Body.Element#
SolidColor=255,0,0
DynamicVariables=1
MouseOverAction=[!UpdateMeasure Module.NowPlaying.DisplayAnimation][!EnableMeasure Module.NowPlaying.DisplayAnimation]

[Module.NowPlaying.DisplaySource]
Group=Module.NowPlaying.Display
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=Module.NowPlaying.Title
MeasureName2=Module.NowPlaying.Artist
Text=#Module.NowPlaying.DisplayFormat#
y=(#Body.Element#*2)
OnUpdateAction=[!UpdateMeasure Module.NowPlaying.DisplayW]
Container=Module.NowPlaying.Container

[Module.NowPlaying.ControlPrevious]
Group=Module.NowPlaying.Display | Module.NowPlaying.Progress | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleIconString
Meter=String
x=(#Body.Element#*12/24)
y=(#Body.Element#*12/24)
Text=Previous
Container=Module.NowPlaying.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*[*Module.NowPlaying.ControlAnimation*]/100*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure "MS.#NowPlaying.PlayerPlugin#.Title" "[Module.NowPlaying.PreviousAction]"]

[Module.NowPlaying.ControlNext]
Group=Module.NowPlaying.Display | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleIconString
Meter=String
x=(#Module.NowPlaying.W#-#Body.Element#*12/24)
y=(#Body.Element#*12/24)
Text=Next
Container=Module.NowPlaying.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*[*Module.NowPlaying.ControlAnimation*]/100*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure "MS.#NowPlaying.PlayerPlugin#.Title" "Next"]

[Module.NowPlaying.ControlPlayPause]
Group=Module.NowPlaying.State | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleIconString
Meter=String
x=(#Module.NowPlaying.W#*0.5)
y=(#Body.Element#*12/24)
MeasureName=Module.NowPlaying.State
Text=%1
Container=Module.NowPlaying.Container
MouseOverAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | #*Colour.2*#,(#*Colour.2.Alpha*#*[*Module.NowPlaying.ControlAnimation*]/100*0.5)"][!UpdateMeter "#CurrentSection#"]
MouseLeaveAction=[!SetOption "#CurrentSection#" "InlineSetting4" "Color | 0,0,0,0"][!UpdateMeter "#CurrentSection#"]
LeftMouseUpAction=[!CommandMeasure "MS.#NowPlaying.PlayerPlugin#.Title" "PlayPause"]

[Module.NowPlaying.InfoPrimary]
Group=Module.NowPlaying.Display | NowPlaying.DisplayAnimation | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=Module.NowPlaying.Title
MeasureName2=Module.NowPlaying.Artist
Text=#Module.NowPlaying.DisplayFormat#
x=((([Module.NowPlaying.DisplayW]>=#Module.NowPlaying.DisplayW#)?0:(#Module.NowPlaying.DisplayW#-[Module.NowPlaying.DisplayW])/2)-[Module.NowPlaying.DisplayAnimation])
y=(#Body.Element#*12/24)
Container=Module.NowPlaying.ContainerInfo

[Module.NowPlaying.InfoSecondary]
Group=Module.NowPlaying.Display | NowPlaying.DisplayAnimation | NowPlaying.ControlAnimation
MeterStyle=module.NowPlaying.StyleInfoString
Meter=String
MeasureName=Module.NowPlaying.Title
MeasureName2=Module.NowPlaying.Artist
Text=#Module.NowPlaying.DisplayFormat#
x=#Body.Element#R
y=r
Hidden=(([Module.NowPlaying.DisplayW]>#Module.NowPlaying.DisplayW#)?0:1)
Container=Module.NowPlaying.ContainerInfo
