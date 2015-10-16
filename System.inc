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
		session_start();
		getView("RatingView.inc", null);
	}
	public function showAdminPanel()
	{
		session_start();
		getView("AdminPanelView.inc", null);
	}
	public function getPersonalStat()
	{
		session_start();
		getView("PersonalStatView.inc", null);
	}
	public function login()
	{
		session_start();
		if ($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			echo $_POST['Password'];
			$account = SQL("select  Status, Password from Players join Statuses USING(StatusId) where Name like ?", array($_POST['Player']))->getAll();
			if (isset($account[0]))
			{
				if (MD5($_POST['Password']) === $account[0]['Password'])
				{
					$_SESSION['isAuth'] = 1;
					$_SESSION['player'] = $_POST['Player'];
					$_SESSION['status'] = $account[0]['Status'];
					header("Location: \?action=getPersonalStat");
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