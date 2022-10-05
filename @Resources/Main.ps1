$Resources=$RmApi.VariableStr("@")

function ReturnBodyCoordinates {
    $X=$RMAPI.Variable("CurrentConfigX")
    $Y=$RMAPI.Variable("CurrentConfigY")
    Return "$X $Y"
}

function ReturnStoredCoordinates {
    $X=$RMAPI.Variable("Body.X")
    $Y=$RMAPI.Variable("Body.Y")
    Return "$X $Y"
}

function SetCoordinates {
    $Stored=ReturnStoredCoordinates
    $Current=ReturnBodyCoordinates
    If($Stored -ne $Current){
        $X=$RMAPI.Variable("CurrentConfigX")
        $Y=$RMAPI.Variable("CurrentConfigY")
        $RMAPI.Bang("!SetVariable Body.X `"`"`"$X`"`"`" ")
        $RMAPI.Bang("!SetVariable Body.Y `"`"`"$Y`"`"`" ")
        $RmAPI.Bang("!WriteKeyValue Variables Body.X `"`"`"$X`"`"`" `"`"`"$($Resources)variables.inc`"`"`" ")
        $RmAPI.Bang("!WriteKeyValue Variables Body.Y `"`"`"$Y`"`"`" `"`"`"$($Resources)variables.inc`"`"`" ")
    }
}

function Update {
    SetCoordinates
}