[Variables]
; vargen|Element size|General|int|0:
Body.Element=30
; vargen|Element padding|General|int|0:
Body.Padding=8
; vargen|Taskbar width|General|int|0:
Body.Width=1500
Body.Height=(#Body.Element#+2*#Body.Padding#)
; vargen|Corner size|General|int|0:
Body.Corner=6
; vargen|PopUp gap|General|int|0:
Body.PopUp=5

; Background
; vargen|Background colour|General|rgb
Colour.1=214,192,197
; vargen|Background alpha|General|int|0:255
Colour.1.Alpha=255

; Element
; vargen|Element colour|General|rgb
Colour.2=214,85,113
; vargen|Element alpha|General|int|0:255
Colour.2.Alpha=255

; Highlight
; vargen|Highlight colour|General|rgb
Colour.3=216,0,46
; vargen|Highlight alpha|General|int|0:255
Colour.3.Alpha=255


; Adjustable but not recommended
Font.Display=Inconsolata
Font.DisplayS=(#Body.Element#*1/3)

; Do not adjust
Font.Icon=MaterialIcon
Font.IconS=(#Body.Element#*0.75)

; Do not adjust
Body.X=210
Body.Y=20
