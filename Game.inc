<?php
class Game
{
	public $gameId;
	public $roomId;
	public $date;
	public $status;
	public $players;
	public function __construct($par)
	{
		if (is_array($par))
			$this->initByPostArray($par);
		else
			$this->initByGameId($par);
	}
	public function saveToSql()
	{
		SQL("INSERT INTO `Games`(`GameId`, `RoomId`, `Master`, `CityVictory`, `date`) VALUES (?,?,?,?,?)", array($this->gameId,$this->roomId, $this->master, $this->status, $this->date));
		
		foreach ($this->players as $playerName => $info)
		{	
		SQL("INSERT INTO `PlayerGame`(`Player`, `Game`, `Role`, `BestPlayer`, `Warnings`, `WasShotFirst`, `BestMove`, `Won`) VALUES (?,?,?,?,?,?,?,?)", array($playerName, $this->gameId, $info['Role'], $info['BestPlayer'], $info['Warnings'], $info['WasShotFirst'], $info['BestMove'], $info['Won']));
		}
	}

	private function initByPostArray($post)
	{
		$this->roomId = $post['RoomId'];
		$this->master = $_SESSION['player'];
		if ($post['result'] === "City")
			$this->status = 1;
		if ($post['result'] === "Mafia")
			$this->status = -1;
		if ($post['result'] === "Draw")
			$this->status = 0;
		$this->date = date("Y-m-d H:i:s");  
		$this->gameId = SQL("select max(GameId) as m from Games")->getAll()[0]['m'] + 1;
				
		$this->players = array();
		for ($i = 0; $i < 10; $i++)
		{
			$this->players[$post["Player$i"]] = array('Role'=>$post["Role$i"], 'WasShotFirst'=>0, 'BestMove'=> 0, 'BestPlayer'=>0, 'Won' => 0, 'Warnings' => $post["Warnings$i"]);
			if(isset($post["Best$i"]))
				$this->players[$post["Player$i"]]['BestPlayer'] = 1;
			
			if (($this->status == 1 && ($post["Role$i"] === "Citizen" || $post["Role$i"] === "Sherif")) ||
			   ($this->status == -1 && ($post["Role$i"] === "Mafia" || $post["Role$i"] === "Don")))
					$this->players[$post["Player$i"]]['Won'] = 1;
					
		}
		$this->players[$post['BestMovePlayer']]['BestMove'] = $post['BestMovePoints'];
		$this->players[$post['BestMovePlayer']]['WasShotFirst'] = 1;
	}
	private function initByGameId($GameId)
	{
		$this->gameId = $GameId;
		$game = SQL("Select RoomId, Master, date, CityVictory as Status from Games where GameId=?", array($GameId))->getAll();
		if (count($game) == 1)
		{
			$this->roomId = $game[0]['RoomId'];
			$this->date = $game[0]['date'];
			$this->master = $game[0]['Master'];
			$this->status = $game[0]['Status'];
		
			$res = SQL("Select `Player`, `Game`, `Role`, `BestPlayer`, `Warnings`, `WasShotFirst`, `BestMove`, `Won` from `PlayerGame` WHERE Game = ?", array($GameId))->getAll();
			foreach($res as $p)
			{
				$this->players[$p['Player']] = array('Role'=>$p["Role"], 'WasShotFirst'=>$p["WasShotFirst"], 'BestMove'=> $p["BestMove"], 'BestPlayer'=> $p["BestPlayer"], 'Won' => $p["Won"], 'Warnings' => $p["Warnings"]);
			}
		} 
	}
	public function show()
	{
		getView("HeaderView.inc", NULL);
		echo '<body><table class="table_dark">';
		echo "<tr><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Лучший ход</th><th>Фолы</th></tr>";
		foreach ($this->players as $name =>$player) 
		{
			echo "<tr><td>$name</td><td>".$player['Role']."</td><td>".$player['BestPlayer']."</td><td>".$player['BestMove']."</td><td>".$player['Warnings']."</td></tr>";
		}
	echo '</table><div id="feed">';
	if ($this->status == 1)
		$victoryTeam = "Город";
	if ($this->status == -1)
		$victoryTeam = "Мафия";
	if ($this->status == 0)
		$victoryTeam = "Ничья";
	echo "<p>Победила команда: $victoryTeam</p>";
	echo "<p>Ведущий: ".$this->master."</p></div>";
	getView("Footer.inc", NULL);
echo "</body>";
	}
}
?>