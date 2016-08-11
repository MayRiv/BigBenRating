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
$res = SQL("Select  Name from Players where StatusID = 1 order by Name ASC")->getAll();
foreach ($res as  $player) {
	echo "<p>".$player['Name']."</p>";
}
echo "</div></div></body></html>";
?>
