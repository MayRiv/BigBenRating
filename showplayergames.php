<?php
require("DBManager.inc");
require("viewer.inc");
session_start();
getView("HeaderView.inc", null);
$host = "mysql.hostinger.com.ua";
$dbName = "u483570622_bbrat";
$user = "u483570622_bbrat";
$password = "konoplya_1";
DBManager::getInstance()->connect($host, $dbName, $user, $password);


echo "<html><body><div id='feed' style='margin-left: 300px;'><div style='text-align:left'>";
$res = SQL("Select player as Name, game as Id from PlayerGame group by Name order by player")->getAll();
foreach ($res as  $player) {
	echo "<p><a href='/showGame/?GameId=".$player['Id']."'>".$player['Name']."</a></p>";http:
}
echo "</div></div></body></html>";
?>