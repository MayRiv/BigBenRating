<?php
require("DBManager.inc");
require("viewer.inc");
require("Config.inc")
session_start();
getView("HeaderView.inc", null);
DBManager::getInstance()->connect($host, $dbName, $user, $password);


echo "<html><body><div id='feed' style='margin-left: 300px;'><div style='text-align:left'>";
$res = SQL("Select player as Name, game as Id from PlayerGame group by Name order by player")->getAll();
foreach ($res as  $player) {
	echo "<p><a href='/showGame/?GameId=".$player['Id']."'>".$player['Name']."</a></p>";http:
}
echo "</div></div></body></html>";
?>