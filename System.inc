<?php
require("Game.inc");
require("PersonalStat.inc");
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
		if ($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin"))	
			getView("AdminPanelView.inc", null);
		else 
			header("Location: ?action=getRating");
	}
	public function comparePlayer()
	{
		echo $_POST['name'];
		//echo "Тестируем" + $_POST['name'];
	}
	public function getPersonalStat()
	{
		session_start();
		if (!$_SESSION['isAuth'])
		{
			$players = SQL("Select Name from Players")->getAll();
			getView("Auth.inc",$players);
		}
		else
		{
			$stat = new PersonalStat($_SESSION['player']);
			if (isset($_POST['name']))
			{
				$player = $_POST["name"];

				$stat->compare($player);		
			}
			getView("PersonalStatView.inc", $stat);
		}
	}
	public function login()
	{
		session_start();
		if ($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			$account = SQL("select  Status, Password from Players join Statuses USING(StatusId) where Name like ?", array($_POST['Player']))->getAll();
			if (isset($account[0]))
			{
				if (MD5($_POST['Password']) === $account[0]['Password'])
				{
					$_SESSION['isAuth'] = 1;
					$_SESSION['player'] = $_POST['Player'];
					$_SESSION['status'] = $account[0]['Status'];
					header("Location: ?action=getPersonalStat");
				}
			}
			else echo "Wrong password or login";
		}
		else
		{
			$players = SQL("Select Name from Players")->getAll();
			getView("Auth.inc",$players);
		}
	}
	public function changePassword()
	{
		session_start();
		if (!($_SESSION['isAuth']))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				getView("ChangePasswordView.inc", NULL);
			}
			else
			{
				$oldPass = MD5($_POST['OldPass']);
				if ($oldPass === SQL("select Password from Players where Name like ?", array($_SESSION['player']))->getAll()[0]['Password'])
				{
					if ($_POST['NewPass1'] === $_POST['NewPass2'])
					{
						SQL("Update Players SET Password=? where Name like ?", array(MD5($_POST['NewPass1']),$_SESSION['player']));
					}
				}
				header("Location: ?action=getPersonalStat");
			}
		}
	}
	public function logout()
	{
		session_start();
		$_SESSION['isAuth'] = 0;
		header("Location: ?action=getRating");
	}
	public function addGame()
	{
		session_start();
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("select  Status, Name from Players join Statuses USING(StatusId)")->getAll();
				$obj = array('players'=>$players,'date'=>date("Y-m-d"));
				getView("AddGameView.inc",$obj);
			}
			else
			{
				$game = new Game($_POST);
				$game->saveToSql();
				header("Location: ?action=showAdminPanel");
			}
		}
	}
	public function deleteGame()
	{
		session_start();

		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("delete from Games where gameid=?", array($_GET['gameid']));
				$players = SQL("delete from PlayerGame where game=?", array($_GET['gameid']));
				header("Location: ?action=showGames");
			}
		}
	}

	public function addPlayer()
	{
		session_start();
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: ?action=getRating");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("Select Name from Players")->getAll();
				getView("AddPlayerView.inc", $players);
			}
			else
			{
				if ($_POST['Status'] == 1)
					$pass = MD5("player");
				else
					$pass = MD5("bbmaster123");
				SQL("INSERT IGNORE INTO `Players`(`Name`, `Password`, `StatusId`) VALUES (?,?,?)", array($_POST['Name'],$pass, $_POST['Status']));
			header("Location: ?action=showAdminPanel");
			}
		}
	}
	public function showGames()
	{
		session_start();
		$games = array();
		$res = SQL("select GameId, Master, date, RoomId from Games  order by date DESC, roomId", null)->getAll();
		foreach($res as $game)
		{
			$games[$game['date']][] = array($game['Master'], $game['GameId'], $game['RoomId']);		
		}		
		getView("ShowGamesView.inc", $games);
	}
	public function showGame()
	{
		session_start();
		$gameId = (int)$_GET['GameId'];
		$game = new Game($gameId);
		$game->show();
	}
	public function getDomination()
	{
		session_start();
		$data = null;
		if (!$_SERVER['REQUEST_METHOD'] == 'GET')
		{
				$data['comparePlayer1'] = $_POST['comparePlayer1'];
				$data['comparePlayer2'] = $_POST['comparePlayer2'];
		}
		getView("DominationView.inc", $data);
	}
}

?>