[Variables]
NowPlaying.PlayerName=
NowPlaying.PlayerPlugin=WNP
NowPlaying.MSUpdate=500
; Arrange the six (6) player names [WEB,AIMP,CAD,ITUNES,WINAMP,WMP] in descending order of hierachy, higher hierachy means the algo will select it over the other ones
NowPlaying.Hierachy=WEB,AIMP,CAD,ITUNES,WINAMP,WMP

[MSState.Web]
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.AIMP]
Measure=NowPlaying
PlayerName=AIMP
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.CAD]
Measure=NowPlaying
PlayerName=CAD
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.ITUNES]
Measure=NowPlaying
PlayerName=ITUNES
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.WINAMP]
Measure=NowPlaying
PlayerName=WINAMP
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.WMP]
Measure=NowPlaying
PlayerName=WMP
PlayerType=State
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!CommandMeasure "MS.PSRM" "SetActivePlayer"]

[MSState.Update]
Measure=String
OnUpdateAction=[!Delay 250][!CommandMeasure "MS.PSRM" "SetActivePlayer"][!DisableMeasure #CurrentSection#]

[MS.PSRM]
Measure=Plugin
Plugin=PowershellRM
ScriptFile=#@#Modules\NowPlaying\Include\MediaSwitcher.ps1

[MS.NP.Title]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=#NowPlaying.PlayerName#
PlayerType=Title
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Title]

[MS.NP.Artist]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Artist
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Artist]

[MS.NP.Album]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Album
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Album]

[MS.NP.Cover]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Cover
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Cover]

[MS.NP.Progress]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Progress
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Progress]

[MS.NP.Position]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Position
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Position]

[MS.NP.Duration]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Duration
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Duration]

[MS.NP.Status]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=Status
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Status]

[MS.NP.State]
Group=MS.Media | MS.NP
Measure=NowPlaying
PlayerName=[MS.NP.Title]
PlayerType=State
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.State]

[MS.WNP.Title]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Title
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Title]

[MS.WNP.Artist]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Artist
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Artist]

[MS.WNP.Album]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Album
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Album]

[MS.WNP.Cover]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Cover
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Cover]

[MS.WNP.Progress]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Progress
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Progress]

[MS.WNP.Position]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Position
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Position]

[MS.WNP.Duration]
Group=MS.Media | MS.WNP 
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Duration
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Duration]

[MS.WNP.Status]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=Status
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.Status]

[MS.WNP.State]
Group=MS.Media | MS.WNP
Measure=Plugin
Plugin=WebNowPlaying
PlayerType=State
DynamicVariables=1
Disabled=1
UpdateDivider=(#NowPlaying.MSUpdate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup MS.NP.State]
