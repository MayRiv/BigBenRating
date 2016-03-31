<?php
	require("viewer.inc");
	require("DBManager.inc");
	require_once("System.inc");
	require_once("Logger.inc");
	require_once('Router.inc');
	define ("DEV", 1);
	if (DEV)
	{
		$host = "mysql.hostinger.com.ua"; 
		$dbName = "u833869977_bbrat"; 
		$user = "u833869977_bbrat"; 
		$password = "konoplya_1";
	}
	else
	{
		$host = "mysql.hostinger.com.ua";
		$dbName = "u450038591_bbrat";
		$user = "u450038591_bbrat";
		$password = "konoplya_1";
	}	
	DBManager::getInstance()->connect($host, $dbName, $user, $password);
	session_start();
	/*$url = $_SERVER['REQUEST_URI'];
	$test = rtrim($url, '/');
  	$parsed = explode('/', $test);
  	if (method_exists('System', $parsed[1]))
  		echo "exist";
  	else
  		echo "not";*/
	/*if (isset($_GET['action']))
	{
		if ($_GET['action'] == 'getRating')
			System::getInstance()->getRating();
		else if ($_GET['action'] == 'showGames')
			System::getInstance()->showGames();
		else if ($_GET['action'] == 'getPersonalStat')
			System::getInstance()->getPersonalStat();
		else if ($_GET['action'] == 'getGlobalStat')
			System::getInstance()->getGlobalStat();
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
		else if ($_GET['action'] == 'getPowerMap')
			System::getInstance()->getPowerMap();
		else 
			System::getInstance()->getRating();
	}
	else 
		System::getInstance()->getRating();*/
	$url = $_SERVER['REQUEST_URI'];
  	$url = rtrim($url, '/');
  	$parsed = explode('/', $url);
  	if(count($parsed) > 1 && method_exists('System', $parsed[1]))
  		$method = $parsed[1];
  	else
  		$method = "getRating";

  	echo $parsed[1];
  	var_dump($_GET);
	System::getInstance()->$method();
	//Router::getInstance()->handle();
	Logger::getInstance()->save();
?>
