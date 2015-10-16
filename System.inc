<?php
class System 
{
	private static $_instance;
	public static  function getInstance()
	{
		if (System::$_instance == null) System::$_instance = new System();
		return System::$_instance;
	}

	private function __construct()
	{
		# code...
	}
	public function getRating()
	{
		getView("RatingView.inc", null);
	}
	public function showAdminPanel()
	{

	}
	public function login()
	{
		session_start();
		if ($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			echo $_POST['Password'];
			if (MD5($_POST['Password']) === $password)
			{		
				$_SESSION['authorizedAdmin'] = 1;
				header("Location: /maska9/?action=insertGame");
			
			}
			else echo "Wrong password or login";
		}
		else
		{

			getView("Auth.inc",NULL);
		}
	}
	public function logout()
	{

	}
}

?>