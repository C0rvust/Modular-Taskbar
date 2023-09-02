[Variables]
; vargen|Taskbar Position|Taskbar|int|0:#Body.Width#
Module.Taskbar.P=46
; vargen|Taskbar Anchor [0/1/2]|Taskbar|int|0:2
Module.Taskbar.A=0
Module.Taskbar.W=(#Module.Taskbar.ProgramCount#*#Module.Taskbar.ProgramW#)

Module.Taskbar.AddDep=#@#Modules\Taskbar\Include\Pinned
Module.Taskbar.DependenciesPath=#@#Modules\Taskbar\Include\Dependencies
Module.Taskbar.StockIconPath=#@#Modules\Taskbar\Include\StockIcon
; vargen|Taskbar Program Count|Taskbar|int|1:
Module.Taskbar.ProgramCount=8

; vargen|Taskbar Icon Padding|Taskbar|int|0:
Module.Taskbar.ProgramPadding=0
Module.Taskbar.ProgramW=(#Body.Element#+#Module.Taskbar.ProgramPadding#)
; The display size of icons, irrelevant to the seperation
Module.Taskbar.IconSize=(#Body.Element#*0.8)
; vargen|Taskbar Element Alignment [0/1/2]|Taskbar|int|0:2
Module.Taskbar.ElementAlignment=0

; vargen|Taskbar Use Minimal Icons [0/1]|Taskbar|int|0:1
Module.Taskbar.UseMinimalIcon=1

NeedsUpdate=1
Module.Taskbar.WindowName=
Module.Taskbar.IsPinned=
