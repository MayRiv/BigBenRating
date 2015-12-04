<?php
/*$host = "mysql.hostinger.com.ua";
$dbName = "u825515718_bbrat";
$user = "u825515718_bbrat";
$password = "B1gBenMafia";*/
$host = "mysql.hostinger.com.ua"; 
		$dbName = "u833869977_bbrat"; 
		$user = "u833869977_bbrat"; 
		$password = "konoplya_1";
DBManager::getInstance()->connect($host, $dbName, $user, $password);
$games = SQL("select GameId from Games")->getAll();
foreach ($games as $game) {
	SQL("set @i = 0;Update PlayerGame SET place= @i:=@i +1 where Game=?",array($game["GameId"]));
}

?>