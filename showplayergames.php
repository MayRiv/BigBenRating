<?php
require("DBManager.inc");
$host = "mysql.hostinger.com.ua";
$dbName = "u825515718_bbrat";
$user = "u825515718_bbrat";
$password = "B1gBenMafia";
DBManager::getInstance()->connect($host, $dbName, $user, $password);

$res = SQL("Select player as Name, game as Id from PlayerGame order by player")->getAll();
foreach ($res as  $player) {
	echo "<p><a href=showGame&GameId=".$player['Id'].">".$player['Player']."</a></p>"
}
?>