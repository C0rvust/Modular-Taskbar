[Main.Background]
Meter=Shape
Shape=Rectangle 0,0,#Skin.Width#,#Skin.Height#,#Body.Corner# | StrokeWidth 0 | Fill Color 0,0,0,0

[Main.Border]
Meter=Shape
Shape=Rectangle 0,0,#Skin.Width#,#Skin.Height#,#Body.Corner# | StrokeWidth 0 | Fill Color #Colour.4#,#Colour.4.Alpha#

[Main.Background.Skin]
Meter=Shape
Shape=Rectangle #Body.Border#,#Body.Border#,(#Skin.Width#-#Body.Border#*2),(#Skin.Height#-#Body.Border#*2),#Body.Corner# | StrokeWidth 0 | Fill Color #Colour.1#,#Colour.1.Alpha#
