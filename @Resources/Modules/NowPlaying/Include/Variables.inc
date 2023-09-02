[Variables]
; vargen|NowPlaying Position|NowPlaying|int|0:#Body.Width#
Module.NowPlaying.P=600
; vargen|NowPlaying Anchor [0/1/2]|NowPlaying|int|0:2
Module.NowPlaying.A=1
Module.NowPlaying.W=(12*#Body.Element#)

Module.NowPlaying.DisplayW=(#Module.NowPlaying.W#-#Body.Element#*2)
Module.NowPlaying.DisplayFormat=%1
Module.NowPlaying.MiniCoverSize=178

; vargen|NowPlaying Element Alignment [0/1/2]|NowPlaying|int|0:2
Module.NowPlaying.ElementAlignment=1
