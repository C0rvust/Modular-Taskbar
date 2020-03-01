[NowPlaying.Title]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=#NowPlaying.PlayerName#
PlayerType=Title
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Title]

[NowPlaying.Artist]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Artist
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Artist]

[NowPlaying.Album]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Album
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Album]

[NowPlaying.Cover]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Cover
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Cover]

[NowPlaying.Progress]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Progress
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Progress]

[NowPlaying.Position]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Position
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Position]

[NowPlaying.Duration]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Duration
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Duration]

[NowPlaying.Status]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=Status
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.Status]

[NowPlaying.State]
Group=NPMeasure
Measure=Plugin
Plugin=NowPlaying
PlayerName=[NowPlaying.Title]
PlayerType=State
UpdateDivider=(#NowPlaying.UpdateRate#/#UpdateInterval#)
OnChangeAction=[!UpdateMeasureGroup Module.NowPlaying.State]