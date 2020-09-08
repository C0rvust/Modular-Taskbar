# Variables -------------------------------------------------------------

# Main skin directory
$RootConfig=$RmAPI.VariableStr("RootConfig")
# Module folder directory
$ModuleFolder=$RmAPI.VariableStr("@") + "Modules"

# functions -------------------------------------------------------------

# Return all avaliable modules in $ModuleFolder
function AvaliableModules{
    $List=@()
    Get-ChildItem $ModuleFolder -File | Where-Object Name -Match "inc$" | Sort-Object | ForEach-Object {
        $List+=$_.BaseName
    }
    return $List
}

function RetrievePosition{
	Param($Module)

	$Location=$ModuleFolder + "\$Module.inc"
	$Content=Get-Content $Location | Select-Object -First 7
	$Position=$Content[5] -replace '.*?=',''
	return $Position
}

function ConstrainPosition{
	$BodyWidth=$RmAPI.VariableStr("body.Width")
	$RefreshReq=$False
	$AvaliableModules=AvaliableModules
	$AvaliableModules | ForEach-Object {
		$Position=RetrievePosition($_)
		if([int]$Position -gt $BodyWidth){
			$Location=$ModuleFolder + "\$_.inc"
			$RmAPI.Bang("!WriteKeyValue Variables module.$_.Position $BodyWidth `"`"`"$Location`"`"`" ")
			# $RefreshReq=$True
		}
	}
	# if($RefreshReq){
	# 	$RmAPI.bang("!Refresh `"`"`"$RootConfig`"`"`" ")
	# 	$RmAPI.bang("!Refresh")
	# }
}

function SetColourConstituents{
	Param($Colour)
	$ColourArray=$Colour -split ","
	$R=$ColourArray[0]; $G=$ColourArray[1]; $B=$ColourArray[2]
	$RmAPI.Bang("!SetVariable R $R")
	$RmAPI.Bang("!SetVariable G $G")
	$RmAPI.Bang("!SetVariable B $B")
}