<?php
class PersonalStat
{
	private $player;
	private $citizensGameCount=0;	
	private $sherifGameCount=0;	
	private $mafiaGameCount=0;	
	private $donGameCount=0;
	private $citizensVictoryCount=0;	
	private $sherifVictoryCount=0;
	private $mafiaVictoryCount=0;
	private $donVictoryCount=0;
	private $firstBloodCount=0;
	private $averageBestMove = 0;
	public function __construct($playerName)
	{
		$this->player = $playerName;
		$games  = SQL("Select Role, Won, WasShotFirst, BestMove from PlayerGame where player like ?", array($playerName))->getAll();
		$totalBestMove = 0;
		foreach($games as $game)
		{	
			
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
		}
		if($this->firstBloodCount)
			$this->averageBestMove = $totalBestMove / $this->firstBloodCount;
	}
	
	public function show()
	{
		//getView("HeaderView.inc", NULL);
		echo "<div><p>Статистика игрока $this->player</p>";
		echo "<p>Убит в первую ночь $this->firstBloodCount раз</p>";
		if($this->firstBloodCount)
			echo "<p>В среднем $this->firstBloodCount черных в лучших ходе</p></div>";
		$totalRedCountGames = $this->citizensGameCount + $this->sherifGameCount;
		$totalRedVictoryGames = $this->citizensVictoryCount + $this->sherifVictoryCount;
		$totalBlackCountGames = $this->mafiaGameCount + $this->donGameCount;
		$totalBlackVictoryGames = $this->mafiaVictoryCount + $this->donVictoryCount;
		$totalGamesCount = $totalRedCountGames + $totalBlackCountGames;
		$totalVictoryCount = $totalRedVictoryGames + $totalBlackVictoryGames;

		echo '<body><table class="table_dark">';
		echo "<tr><th>Роль</th><th>Всего сыграно</th><th>Побед</th>";
		echo	"<tr><td>Всего</td><td>$totalGamesCount</td><td>$totalVictoryCount</th></td>";
		echo	"<tr><td>Красный</td><td>$totalRedCountGames</td><td>$totalRedVictoryGames</th></td>";
		echo	"<tr><td>Черный</td><td>$totalBlackCountGames</td><td>$totalBlackVictoryGames</th></td>";
		
		echo "<tr><th colspan='3'>Подробно</th></tr>";
		echo	"<tr><td>Мирный житель</td><td>$this->citizensGameCount</td><td>$this->citizensVictoryCount</td></tr>";
		echo	"<tr><td>Шериф</td><td>$this->sherifGameCount</td><td>$this->sherifVictoryCount</td></tr>";
		echo	"<tr><td>Мафия</td><td>$this->mafiaGameCount</td><td>$this->mafiaVictoryCount</td></tr>";
		echo	"<tr><td>Дон</td><td>$this->donGameCount</td><td>$this->donVictoryCount</th></td>";
		
		echo '</table>';
	
		
		//getView("Footer.inc", NULL);
		//echo "</body>";
	}
}
?>