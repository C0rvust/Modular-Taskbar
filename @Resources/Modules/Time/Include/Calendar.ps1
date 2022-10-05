function GetCurrentMonth {
    $Month=$RMAPI.Measure("Month")
    Return $Month
}
function GetCurrentYear {
    $Year=$RMAPI.Measure("Year")
    Return $Year
}

function ControlPrevAction {
    $Month=GetCurrentMonth
    $Year=GetCurrentYear
    If($Month -eq 1){
        $RMAPI.Bang("!SetOption Month Formula `"`"`"12`"`"`"")
        $RMAPI.Bang("!SetOption Year Formula `"`"`"$($Year-1)`"`"`"")
    }
    Else{
        $RMAPI.Bang("!SetOption Month Formula `"`"`"$($Month-1)`"`"`"")
    }
    $RMAPI.Bang("!UpdateMeasureGroup TimeMeasure")
    $RMAPI.Bang("!UpdateMeterGroup Day")
}

function ControlNextAction {
    $Month=GetCurrentMonth
    $Year=GetCurrentYear
    If($Month -eq 12){
        $RMAPI.Bang("!SetOption Month Formula `"`"`"1`"`"`"")
        $RMAPI.Bang("!SetOption Year Formula `"`"`"$($Year+1)`"`"`"")
    }
    Else{
        $RMAPI.Bang("!SetOption Month Formula `"`"`"$($Month+1)`"`"`"")
    }
    $RMAPI.Bang("!UpdateMeasureGroup TimeMeasure")
    $RMAPI.Bang("!UpdateMeterGroup Day")
}