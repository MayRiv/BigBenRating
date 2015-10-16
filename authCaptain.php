<?php
	require("viewer.inc");
	require("DBManager.inc");
	/*$host = "mysql.hostinger.com.ua";
	$dbName = "u558605037_maska";
	$user = "u558605037_maska";
	$password = "konoplya_1";*/
	$host = "localhost";
	$dbName = "maska9";
	$user = "root";
	$password = "";
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		session_start();
		DBManager::getInstance()->connect($host, $dbName, $user, $password);
		$result = SQL("Select password from Teams where TeamId = ?", array($_POST['Team']))->getAll()[0];
		if (MD5($_POST['Pass']) === $result['password'])
		{		
			$_SESSION['authorizedCaptain'] = 1;
			$_SESSION['team'] = $_POST['Team'];
			header("Location: /maska9/?action=getTeams");
		}
		else echo "Wrong password or login";
	}
	else
		getView("AuthCaptainView.inc",NULL);

?>