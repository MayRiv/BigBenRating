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
$res = SQL("  SELECT player as Name, COUNT( * ) as t FROM PlayerGame JOIN Games ON ( Game = GameId ) JOIN Players ON (player = Name ) WHERE StatusId !=2 AND StatusId !=0 AND DATE BETWEEN CAST(  2015-12-16 AS DATE )  AND CAST( 2016-3-16AS DATE )  GROUP BY player  ORDER BY  t DESC")->getAll();
foreach ($res as  $player) {
	echo "<p>".$player['Name'].":".$player['t']."</p>";
}
echo "</div></div></body></html>";


?>