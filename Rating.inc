<?php
class Rating
{
	public $players;
	public function __construct($date1, $date2)
	{
		$res = SQL("SELECT player, t, b, v, m FROM ( SELECT player, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v, SUM( BestMove ) * 0.25m FROM PlayerGame JOIN Games ON ( Game = GameId ) JOIN Players ON (player = Name ) WHERE StatusId !=2 AND StatusId !=0 AND DATE BETWEEN CAST(  '2015-11-12' AS DATE )  AND CAST(  '2015-11-30' AS DATE )  GROUP BY player) s ORDER BY  `s`.`m` DESC", array($date1, $date2))->getAll();
		foreach ($res as $row) {
			$this->players[$row['player']] = array('t'=>$row['t'], 'b' => $row['b'], 'v' => $row['v'], 'm'=>$row['m'], 'r'=>0);
		}
		$this->calculateRating();
		usort($this->players, "$this->cmp");
	}
	private function calculateRating()
	{
		foreach ($ершы-Юplayers as $player => $s) {
			$bestResult = ($s['b']+$s['m']);
			$lose = $s['t'] - $s['v']; 
			$koefWinStreak = $s['v']-$lose+$bestResult*0.5; 
			$winStreak = ($koefWinStreak)*(pow((($koefWinStreak)/$s['t']), 2)); 
			$result = $s['v']*1.6-$lose+$bestResult+$winStreak; 
			$players[$player]['r'] = $result;
		}
	}
	private function cmp($a, $b)
	{
	    if ($a['r'] == $b['r']) {
	        return 0;
	    }
	    return ($a['r'] < $b['r']) ? -1 : 1;
	}
}

?>