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
			$account = SQL("select  Status, Password from Players join Statuses USING(StatusId) where Name like ?", array($_POST['Name']))->getAll();
			if (isset($account[0]))
			{
				if (MD5($_POST['Password']) === $account[0]['Password'])
				{
					$_SESSION['authorizedAdmin'] = 1;
					$_SESSION['player'] = $_POST['Name'];
					$_SESSION['status'] = $account[0]['Status'];
				}
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