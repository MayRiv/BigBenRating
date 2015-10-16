<?php
	require("viewer.inc");
	require("DBManager.inc");
	$host = "mysql.hostinger.com.ua";
	$dbName = "u558605037_maska";
	$user = "u558605037_maska";
	$password = "konoplya_1";

	$passwordAdmin = "4efe3aff7e691264809e8e65282c96d0";
	if ($_SERVER['REQUEST_METHOD'] == 'POST')
	{
		session_start();

		if (MD5($_POST['Pass']) === $passwordAdmin)
		{		
			$_SESSION['authorizedAdmin'] = 1;
			header("Location: /maska9/?action=insertGame");
			
		}
		else echo "Wrong password or login";
	}
	else
		getView("AuthAdminView.inc",NULL);

?>