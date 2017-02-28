<?php
require("DBManager.inc");
require("viewer.inc");
require("Config.inc")
getView("HeaderView.inc", null);
DBManager::getInstance()->connect($host, $dbName, $user, $password);

echo "<html><body><div id='feed' style='margin-left: 300px;'><div style='text-align:left'>";
$res = SQL("Select  Name from Players where StatusID = 1 order by Name ASC")->getAll();
$i = 1;
foreach ($res as  $player) {
	echo "<p>$i) ".$player['Name']."</p>";
	$i++;
}
echo "</div></div></body></html>";
?>
