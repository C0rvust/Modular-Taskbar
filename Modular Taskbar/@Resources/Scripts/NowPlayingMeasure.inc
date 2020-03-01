[Variables]
NowPlaying.PlayerName=AIMP
NowPlaying.PlayerPlugin=NowPlaying
NowPlaying.UpdateRate=250

; Assign appropriate actions to each playername as desired
NowPlaying.AIMP=["Aimp"]

[Module.NowPlaying.Refresh]
Measure=String
OnUpdateAction=[!UpdateMeasureGroup NPMeasure][!DisableMeasure #CurrentSection#]

[IncludePlayer]
@IncludePlayer=#@#Scripts\Player\#NowPlaying.PlayerPlugin#.inc
