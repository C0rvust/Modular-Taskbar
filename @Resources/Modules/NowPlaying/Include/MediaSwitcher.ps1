function SetPlayerHierachy {
    $Reference=@("WEB", "AIMP", "CAD", "ITUNES", "WINAMP", "WMP")  # Given a reference list $Reference,
    $Hierachy=$RMAPI.VariableStr("NowPlaying.Hierachy","$Reference -join ','") -split "," # a user-defined list $Hierachy is retrieved
    if(@(Compare-Object $Reference $Hierachy).count -eq 0){ # If the user-defined list is valid, i.e. contains all the elements of the reference list
        $Global:PlayerList=$Hierachy # Then use this order of hierachy
    }
    else{
        $Global:PlayerList=$Reference # Otherwise use the reference hierachy
    }
}

function ReturnActivePlayer {

    $PlayerList=$Global:PlayerList 
    for ($state=1; $state -le 2; $state++){ # First find the first player that is playing media (1), if not then find the first player that is currently paused
        for ($i=0; $i -lt $PlayerList.length; $i++) {
            if($($RMAPI.Measure("MSState."+$PlayerList[$i])) -eq $state) {
                Return $PlayerList[$i]
            }
        }
    }
    Return $null # Otherwise return "no player avaliable"
}

function SetActivePlayer {
    $ActivePlayer=ReturnActivePlayer # Given the currently active player
    $CurrentPlayer=$RMAPI.Variable("NowPlaying.PlayerName") # Given the skin's current player
    If($ActivePlayer -ne $CurrentPlayer){ # If they are different, switch to the currently active player, otherwise do nothing (This function fires whenever any player has a state change so it can fire even when the player does not change)
        $RMAPI.Bang("!SetVariable `"`"`"NowPlaying.PlayerName`"`"`" `"`"`"$ActivePlayer`"`"`" ")

        switch($ActivePlayer) {
            $Null {
                $RMAPI.Bang("!SetVariable `"`"`"NowPlaying.PlayerPlugin`"`"`" `"`"`"NP`"`"`" ")
                $RMAPI.Bang("!DisableMeasureGroup `"`"`"MS.NP`"`"`" ")
                $RMAPI.Bang("!DisableMeasureGroup `"`"`"MS.WNP`"`"`" ")
            }
            "WEB" {
                $RMAPI.Bang("!SetVariable `"`"`"NowPlaying.PlayerPlugin`"`"`" `"`"`"WNP`"`"`" ")
                $RMAPI.Bang("!DisableMeasureGroup `"`"`"MS.NP`"`"`" ")
                $RMAPI.Bang("!EnableMeasureGroup `"`"`"MS.WNP`"`"`" ")
            }
            default {
                $RMAPI.Bang("!SetVariable `"`"`"NowPlaying.PlayerPlugin`"`"`" `"`"`"NP`"`"`" ")
                $RMAPI.Bang("!DisableMeasureGroup `"`"`"MS.WNP`"`"`" ")
                $RMAPI.Bang("!EnableMeasureGroup `"`"`"MS.NP`"`"`" ")
            }
        }
    $RMAPI.Bang("!UpdateMeasureGroup `"`"`"MS.Media`"`"`" ")
    }
}

# Initalise 
SetPlayerHierachy