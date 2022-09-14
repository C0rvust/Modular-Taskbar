[Variables]
; vargen|Taskbar Position|Taskbar|int|0:#Body.Width#
Module.Taskbar.P=86
; vargen|Taskbar Anchor [0/1/2]|Taskbar|int|0:2
Module.Taskbar.A=0
Module.Taskbar.W=(#Module.Taskbar.ProgramCount#*#Module.Taskbar.ProgramW#)

Module.Taskbar.AddDep=#@#Modules\Taskbar\Include\Pinned
Module.Taskbar.WMPath=#@#Modules\Taskbar\Include\Dependencies\WindowMirror.exe
Module.Taskbar.DependenciesPath=#@#Modules\Taskbar\Include\Dependencies
Module.Taskbar.StockIconPath=#@#Modules\Taskbar\Include\StockIcon
; vargen|Taskbar Program Count|Taskbar|int|1:
Module.Taskbar.ProgramCount=8

; Seperation between icons
Module.Taskbar.ProgramW=(#Body.Element#+#Body.Padding#*2)
; The display size of icons, irrelevant to the seperation
Module.Taskbar.IconSize=(#Body.Element#*0.8)

Module.Taskbar.DefaultShade=180,180,180

NeedsUpdate=1
Module.Taskbar.WindowName=
Module.Taskbar.IsPinned=
