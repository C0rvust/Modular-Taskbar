[Variables]
; Controls the nowplaying measures' update rate
NowPlaying.UpdateRate=250

; Change using the popup's menu
NowPlaying.PlayerName=AIMP
NowPlaying.PlayerPlugin=NowPlaying

[Module.NowPlaying.Refresh]
Measure=String
OnUpdateAction=[!UpdateMeasureGroup NPMeasure][!DisableMeasure #CurrentSection#]

[IncludePlayer]
@IncludePlayer=#@#includes\NowPlaying\Player\#NowPlaying.PlayerPlugin#.inc
