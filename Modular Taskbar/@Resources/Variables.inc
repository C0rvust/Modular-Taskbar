[Variables]
; Adjust as necessary
body.ElementSize=30
body.Padding=8
body.CornerRadius=6

; -------------------------------------

; Adjust as necessary
; Background
colour.1.Code=25,25,25
colour.1.Alpha=255
; Element
colour.2.Code=200,200,200
colour.2.Alpha=255
; Highlight
colour.3.Code=220,220,220
colour.3.Alpha=20

; -------------------------------------

; Adjustable but not recommended
font.DisplayName=Inconsolata
font.SizeStd=(#body.ElementSize#*1/3)

; Do not adjust
font.IconName=MaterialIcon

; -------------------------------------

; Adjust as necessary
body.PopUpGap=5
body.Width=1500

; Do not adjust
body.Verticality=0
body.X=210
body.Y=0
body.Height=(#body.ElementSize#+#body.Padding#*2)
ActiveModules=Battery,Power,Start,Time,Volume,WSM,NowPlaying
