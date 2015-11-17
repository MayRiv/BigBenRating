<?php
	require("viewer.inc");
	require("DBManager.inc");
	require("System.inc");
	require("Logger.inc");
	define ("DEV", 0);
	if (DEV)
	{
		$host = "localhost";
		$dbName = "u825515718_bbrat";
		$user = "root";
		$password = "";
	}
	else
	{
		$host = "mysql.hostinger.com.ua";
		$dbName = "u825515718_bbrat";
		$user = "u825515718_bbrat";
		$password = "B1gBenMafia";
	}	
	DBManager::getInstance()->connect($host, $dbName, $user, $password);
	if (isset($_GET['action']))
	{
		if ($_GET['action'] == 'getRating')
			System::getInstance()->getRating();
		else if ($_GET['action'] == 'showGames')
			System::getInstance()->showGames();
		else if ($_GET['action'] == 'getPersonalStat')
			System::getInstance()->getPersonalStat();
		else if ($_GET['action'] == 'compare')
			System::getInstance()->comparePlayer();
		else if ($_GET['action'] == 'showAdminPanel')
			System::getInstance()->showAdminPanel();
		else if ($_GET['action'] == 'logout')
			System::getInstance()->logout();
		else if ($_GET['action'] == 'login')
			System::getInstance()->login();
		else if ($_GET['action'] == 'addGame')
			System::getInstance()->addGame();
		else if ($_GET['action'] == 'deleteGame')
			System::getInstance()->deleteGame();
		else if ($_GET['action'] == 'editGame')
			System::getInstance()->editGame();
		else if ($_GET['action'] == 'addPlayer')
			System::getInstance()->addPlayer();
		else if ($_GET['action'] == 'changePassword')
			System::getInstance()->changePassword();
		else if ($_GET['action'] == 'showGame')
			System::getInstance()->showGame();
		else if ($_GET['action'] == 'getDomination')
			System::getInstance()->getDomination();
		else 
			System::getInstance()->getRating();
	}
	else 
		System::getInstance()->getRating();

	Logger::getInstance()->save();
?>
