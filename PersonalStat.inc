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
	
	public function show()
	{
		//getView("HeaderView.inc", NULL);
		echo "<div><h2>Статистика игрока $this->player</h2>";
		echo "<p>Получил $this->bestVotes лучших</p>";
		echo "<p>Убит в первую ночь $this->firstBloodCount раз</p>";
		if($this->firstBloodCount)
			echo "<p>В среднем $this->averageBestMove черных в лучших ходе</p></div>";
		

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

		echo "<div><p>Сыграл в играх: ";
		foreach ($this->games as $game) {
			echo "<a href='?action=showGame&GameId=".$game."'>".$game."</a> ";
		}
		echo "</p></div>";
	
	}
}
?>