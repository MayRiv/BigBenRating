<?php
class PersonalStat
{
	public $player;
	public $games;
	public $citizensGameCount=0;	
	public $sherifGameCount=0;	
	public $mafiaGameCount=0;	
	public $donGameCount=0;
	public $citizensVictoryCount=0;	
	public $sherifVictoryCount=0;
	public $mafiaVictoryCount=0;
	public $donVictoryCount=0;
	public $firstBloodCount=0;
	public $averageBestMove = 0;
	public $bestVotes = 0;



	public $totalRedCountGames;
	public $totalRedVictoryGames;
	public $totalBlackCountGames;
	public $totalBlackVictoryGames;
	public $totalGamesCount;
	public $totalVictoryCount;

	public $compareResult;
	public function __construct($playerName)
	{
		$this->player = $playerName;
		$games  = SQL("Select Game,Role, Won, WasShotFirst, BestMove, BestPlayer from PlayerGame where player like ?", array($playerName))->getAll();
		$totalBestMove = 0;
		foreach($games as $game)
		{	
			$this->games[] = $game['Game'];
			if ($game['Role'] == "Citizen")
			{
				$this->citizensGameCount++;
				if ($game['Won'])
					$this->citizensVictoryCount++;
			}
			if ($game['Role'] == "Sherif")
			{
				$this->sherifGameCount++;
				if ($game['Won'])
					$this->sherifVictoryCount++;
			}
			if ($game['Role'] == "Mafia")
			{
				$this->mafiaGameCount++;
				if ($game['Won'])
					$this->mafiaVictoryCount++;
			}
			if ($game['Role'] == "Don")
			{
				$this->donGameCount++;
				if ($game['Won'])
					$this->donVictoryCount++;
			}
			if ($game['WasShotFirst'])
			{
				$this->firstBloodCount++;
				$totalBestMove += $game['BestMove'];
			}
			if ($game['BestPlayer'])
				$this->bestVotes+= $game['BestPlayer'];
		}
		if($this->firstBloodCount)
			$this->averageBestMove = $totalBestMove / $this->firstBloodCount;


		$totalRedCountGames = $this->citizensGameCount + $this->sherifGameCount;
		$totalRedVictoryGames = $this->citizensVictoryCount + $this->sherifVictoryCount;
		$totalBlackCountGames = $this->mafiaGameCount + $this->donGameCount;
		$totalBlackVictoryGames = $this->mafiaVictoryCount + $this->donVictoryCount;
		$totalGamesCount = $totalRedCountGames + $totalBlackCountGames;
		$totalVictoryCount = $totalRedVictoryGames + $totalBlackVictoryGames;
	}
}
?>