<?php
require("DBManager.inc");
require("viewer.inc");
getView("HeaderView.inc", null);
$host = "mysql.hostinger.com.ua";
$dbName = "u450038591_bbrat";
$user = "u450038591_bbrat";
$password = "konoplya_1";
DBManager::getInstance()->connect($host, $dbName, $user, $password);

echo "<html><body><div id='feed' style='margin-left: 300px;'><div style='text-align:left'>";
$res = SQL("SELECT player as Name, COUNT( * )  as c
FROM PlayerGame
GROUP BY player
ORDER BY c DESC ")->getAll();
foreach ($res as  $player) {
	echo "<p>".$player['Name']."</p><p>".$player['c']."</p>";
}
echo "</div></div></body></html>";


?>