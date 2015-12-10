<?php
class GlobalStat
{
	public $top;
	private $roleSQLCount;
	private $topSQL;
	public function __construct()
	{
		$this->roleSQLCount = "SELECT MAX(t) as m from (SELECT count(*) t from PlayerGame where Role=? group by player) s";
		$this->topSQL = "SELECT player, w / t * 100 as r, t  as m from (SELECT count(*) t, SUM(Won) w from PlayerGame where Role=? group by player) s where t > ? order by r DESC";
		GlobalStat::getStatRole("Sherif");
		GlobalStat::getStatRole("Don");
		GlobalStat::getStatRole("Mafia");
		GlobalStat::getStatRole("Citizen");
	}
	private getStatRole($role)
	{
		$count = array();
		$count[$role] = SQL($this->roleSQLCount, array($role))->getAll()[0]['m'];
		$this->top[$role] = SQL($this->topSQL, array($role, $count[$role]))->getAll();
	}
}

?>