[Metadata]
Name=Taskbar
Description=Displays running applications. Click to focus on the application window, mouse over to open a list of children, middle mouse click to open a new child. Customize pinned programs and icons through the context menu in the popup.

[Variables]
module.Taskbar.Position=86
module.Taskbar.Anchor=0

; Can Change
module.Taskbar.AddDep=#@#includes\Taskbar\Pinned
module.Taskbar.WMPath=#@#includes\Taskbar\Dependencies\WindowMirror.exe
module.Taskbar.GetIconsPath=#@#Includes\Taskbar\Dependencies
module.Taskbar.StockIconPath=#@#includes\Taskbar\StockIcon
module.Taskbar.ProgramCount=10
module.Taskbar.ProgramW=(#body.ElementSize#+2*#body.Padding#)
module.Taskbar.IconSize=(#body.ElementSize#*0.8)

; Do not change
module.Taskbar.Width=(#module.Taskbar.ProgramCount#*#module.Taskbar.ProgramW#)
NeedsUpdate=1
module.Taskbar.WindowName=
module.Taskbar.IsPinned=

[module.Taskbar.StyleIcon]
Group=module.Taskbar.Icon
y=((#body.ElementSize#-#module.Taskbar.IconSize#)/2)
h=#module.Taskbar.IconSize#
ImageTint=180,180,180
DynamicVariables=1
AntiAlias=1
Container=module.Taskbar.Container

[module.Taskbar.ProgramOptions]
Measure=Plugin
Plugin=ProgramOptions
Indexes=#module.Taskbar.ProgramCount#
AdditionalDependencies=#module.Taskbar.AddDep#
WindowMirrorPath=#module.Taskbar.WMPath#
UpdateDivider=(1000/#UpdateInterval#)

[module.Taskbar.StockIconMonitor]
Measure=Plugin
Plugin=FolderInfo
Folder="#module.Taskbar.StockIconPath#"
InfoType=FileCount
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!SetVariable NeedsUpdate 1][!UpdateMeasure module.Taskbar.PSRM]

[module.Taskbar.GetIconMonitor]
Measure=Plugin
Plugin=FolderInfo
Folder="#module.Taskbar.GetIconsPath#\Icons"
InfoType=FileCount
UpdateDivider=(1000/#UpdateInterval#)
OnChangeAction=[!SetVariable NeedsUpdate 1][!UpdateMeasure module.Taskbar.PSRM]

[module.Taskbar.PSRM]
Measure=Plugin
Plugin=PowerShellRM
ScriptFile=#@#Includes\Taskbar\Taskbar.ps1
UpdateDivider=(1000/#UpdateInterval#)

[module.Taskbar.PopUpTimer]
Measure=Plugin
Plugin=ActionTimer
ActionList1=Wait 500 | DeactivatePopup
ActionList2=Wait 500 | DeactivatePopup | ActivatePopup
DeactivatePopup=[!DeactivateConfig "#RootConfig#\Popup"]
DeactivatePopup=[!ActivateConfig "#RootConfig#\Popup" "Taskbar_PopUp.ini"]
DynamicVariables=1
IgnoreWarnings=1

[module.Taskbar.Container]
Meter=Image
x=(#module.Taskbar.Position#-(#module.Taskbar.Anchor#*0.5)*#module.Taskbar.Width#)
y=((#body.Height#-#body.ElementSize#)/2)
w=#module.Taskbar.Width#
h=#body.ElementSize#
SolidColor=0,0,0
DynamicVariables=1

[module.Taskbar.Icon.Dummy]
Meter=string
Container=module.Taskbar.Container
[module.Taskbar.Icon.0]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.1]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.2]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.3]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.4]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.5]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.6]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.7]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.8]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon
[module.Taskbar.Icon.9]
Meter=Image
MeterStyle=module.Taskbar.StyleIcon

; If more are needed just C&V sections and change #module.Taskbar.ProgramCount#