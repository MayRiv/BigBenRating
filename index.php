<?php
	require("viewer.inc");
	require("DBManager.inc");
	require("System.inc");
	$host = "mysql.hostinger.com.ua";
	$dbName = "u551009485_bbrat";
	$user = "u551009485_bbrat";
	$password = "B1gBenMafia";
	DBManager::getInstance()->connect($host, $dbName, $user, $password);
	if (isset($_GET['action']))
	{
		if ($_GET['action'] == 'getRating')
			System::getInstance()->getRating();
		else if ($_GET['action'] == 'showGames')
			System::getInstance()->showGames();
		else if ($_GET['action'] == 'getPersonalStat')
			System::getInstance()->getPersonalStat();
		else 
			System::getInstance()->getRating();
	}
	else 
		System::getInstance()->getRating();
?>