<?php
require("DBManager.inc");
$host = "mysql.hostinger.com.ua";
$dbName = "u825515718_bbrat";
$user = "u825515718_bbrat";
$password = "B1gBenMafia";
DBManager::getInstance()->connect($host, $dbName, $user, $password);
echo "<html><body>"
$res = SQL("Select player as Name, game as Id from PlayerGame group by Name order by player")->getAll();
var_dump($res);
foreach ($res as  $player) {
	echo "<p><a href=showGame&GameId=".$player['Id'].">".$player['Player']."</a></p>";
}
echo "</body></html>"
?>