<?php
class GlobalStat
{
	public $top;
	private $roleSQLCount;
	private $topSQL;
	public function __construct()
	{
		$this->roleSQLCount = "SELECT MAX(t) as m from (SELECT count(*) t from PlayerGame where Role=? group by player) s";
		$this->topSQL = "SELECT player, w / t * 100 as r, t  as m from (SELECT player, count(*) t, SUM(Won) w from PlayerGame where Role=? group by player) s where t > ? order by r DESC";
		$this->getStatRole("Sherif");
		$this->getStatRole("Don");
		$this->getStatRole("Mafia");
		$this->getStatRole("Citizen");
	}
	private function getStatRole($role)
	{
		$count = array();
		$count[$role] = DSQL($this->roleSQLCount, array($role))->getAll()[0]['m'];
		$this->top[$role] = DSQL($this->topSQL, array($role, $count[$role]));//->getAll();
	}
}

?>