<?php
require("Game.inc");
require("PersonalStat.inc");
require("GlobalStat.inc");
require("PowerMap.inc");
require ("Domination.inc");
require("Rating.inc");
require_once("Logger.inc");
class System 
{
	private static $_instance;
	//public $lastMonthEnd = '2016-4-13';
	//public $lastMonthEnd = '2016-5-18';
	//public $lastMonthEnd = '2016-6-16';
	//public $lastMonthEnd = '2016-7-14';
	//public $lastMonthEnd = '2016-8-10';
	//public $lastMonthEnd = '2016-10-1';
	//public $lastMonthEnd = '2016-12-31';
	//public $lastMonthEnd = '2016-11-30';
	//public $lastMonthEnd = '2017-1-31';
	public $lastMonthEnd = '2017-3-1';
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
		//$firstMonth = '2016-6-19';
        //$firstMonth = '2016-7-15';
        //$firstMonth = '2016-8-11';
        //$firstMonth = '2016-12-1';
        $firstMonth = '2017-2-1';
        //$firstMonth = '2017-1-1';
        //$firstMonth = '2016-11-1';
		if (isset($_GET['p']) && $_GET['p']=='a')
			$firstMonth = '2015-10-19';
		//$maxGameCount = SQL("select max(t) total from (SELECT COUNT( * ) t FROM PlayerGame JOIN Players ON ( player = Name ) WHERE StatusId !=2 GROUP BY player) t")->getAll()[0]['total'];
		//$players = SQL("SELECT player, p /(t * 3.25 + ? - t) AS r, t, b FROM ( SELECT player, ( SUM( Won ) *2 + SUM( BestPlayer ) * 0.5 + SUM( BestMove ) * 0.25) p, COUNT( * ) t, SUM(BestPlayer) b FROM PlayerGame JOIN Players ON ( player = Name ) WHERE StatusId !=2 GROUP BY player ) s  ORDER BY r DESC", array($maxGameCount))->getAll();

		/*$players = SQL("SELECT player, p / t AS r, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE <= CAST(  '2015-11-11' AS DATE ) 
GROUP BY player
) s
ORDER BY r DESC, b DESC")->getAll();*/
		/*$players = SQL("SELECT player, p / t AS r, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE BETWEEN CAST(  '2015-11-12' AS DATE ) AND CAST('2015-11-21' AS DATE)
GROUP BY player
) s
ORDER BY player DESC,r DESC, b DESC")->getAll();*/
/*$players = SQL("SELECT player, t, b, v FROM (SELECT player, (SUM( Won ) *2 + SUM( BestPlayer ) * 1.5 + SUM( BestMove ) * 0.25
) p, COUNT( * ) t, SUM( BestPlayer ) b, SUM( Won ) v FROM PlayerGame
JOIN Games ON(Game=GameId)
JOIN Players ON ( player = Name ) 
WHERE StatusId !=2 AND StatusId != 0 AND DATE BETWEEN CAST(  '2015-11-12' AS DATE ) AND CAST('2015-11-30' AS DATE)
GROUP BY player
) s
ORDER BY player ASC, b DESC")->getAll();*/

		
		//$r = new Rating('2015-12-10', '2016-01-06');
		//$r = new Rating('2016-2-17', System::getInstance()->lastMonthEnd);
		//$r = new Rating('2016-4-14', System::getInstance()->lastMonthEnd);
		//$r = new Rating('2016-5-19', System::getInstance()->lastMonthEnd);
		//$r = new Rating($firstMonth, System::getInstance()->lastMonthEnd);
		$r = new Rating($firstMonth, System::getInstance()->lastMonthEnd);
	
		getView("RatingView.inc", $r);
	}
	public function showAdminPanel()
	{
		if ($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin"))	
			getView("AdminPanelView.inc", null);
		else 
			header("Location: /getRating/");
	}
	public function getPersonalStat()
	{
		if (!$_SESSION['isAuth'] && !isset($_GET['player']))
		{
			$players = SQL("Select Name from Players")->getAll();
			getView("Auth.inc",$players);
		}
		else
		{
			$playerName = null;
			
			if (isset($_GET['player']))
			{
				$playerName = urldecode($_GET['player']);
				$result = SQL("Select isPrivate from Players where Name like ?", array($playerName))->getAll()[0];
				if ($result['isPrivate'] && ($_SESSION['player'] != $playerName) && ($_SESSION['status']!='Admin' && $_SESSION['status'] != 'Master'))
				{
					getView("PrivateError.inc", null);
					return;
				}
			}
			else
			{
				$playerName = $_SESSION['player'];
			}
			if ($_GET['p']=='m')
				$stat = new PersonalStat($playerName,'m');
			else
				$stat = new PersonalStat($playerName,'a');
			if (isset($_POST['name']))
			{
				$player = $_POST["name"];

				$stat->compare($player);		
			}
			getView("PersonalStatView.inc", $stat);
		}
	}
	public function getGlobalStat()
	{
		$stat = new GlobalStat();
		getView("GlobalStatView.inc", $stat);
	}
	public function login()
	{
		if ($_SERVER['REQUEST_METHOD'] == 'POST')
		{
			$account = SQL("select  Status, Password from Players join Statuses USING(StatusId) where Name like ?", array($_POST['Player']))->getAll();
			if (isset($account[0]) && MD5($_POST['Password']) === $account[0]['Password'])
			{
				
				$_SESSION['isAuth'] = 1;
				$_SESSION['player'] = $_POST['Player'];
				$_SESSION['status'] = $account[0]['Status'];
				header("Location: /getPersonalStat/");
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
		
		if (!($_SESSION['isAuth']))
			header("Location: /getRating/");
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
				header("Location: /getPersonalStat/");
			}
		}
	}
	public function changePrivate()
	{
		if (!($_SESSION['isAuth']))
			header("Location: /getRating/");
		else
		{
				SQL("Update Players SET isPrivate=isPrivate XOR 1 where Name like ?", array($_SESSION['player']));
				header("Location: /getPersonalStat/");
		}
		
	}
	public function logout()
	{
		$_SESSION['isAuth'] = 0;
		header("Location: /getRating/");
	}
	public function addGame()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: /getRating/");
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
				header("Location: /showAdminPanel/");
			}
		}
	}
	public function deleteGame()
	{

		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: /getRating/");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("delete from Games where gameid=?", array($_GET['GameId']));
				$players = SQL("delete from PlayerGame where game=?", array($_GET['GameId']));
				Logger::getInstance()->write("Game with id ".$_GET['GameId']." has been deleted, deleter is " . $_SESSION['player']);
				header("Location: /showGames/");
			}
		}
	}

	public function addPlayer()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: /getRating/");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{
				$players = SQL("Select Name from Players")->getAll();
				getView("AddPlayerView.inc", $players);
			}
			else
			{
				if ($_POST['Status'] == 1 || $_POST['Status'] == 0)
					$pass = MD5("player");
				else
					$pass = MD5("bbmaster123");
				SQL("INSERT IGNORE INTO `Players`(`Name`, `Password`, `StatusId`) VALUES (?,?,?)", array($_POST['Name'],$pass, $_POST['Status']));
				Logger::getInstance()->write("Player ".$_POST['Name']." has been added to system, Status is ".$_POST['Status']." adder is " . $_SESSION['player']);
				header("Location: /showAdminPanel/");
			}
		}
	}
	public function showGames()
	{
		$games = null;
		if (isset($_GET['date']))
		{
			$games = array();
			$res = SQL("select GameId, Master, date, RoomId from Games  where date = ? order by roomId", array($_GET['date']))->getAll();
			foreach($res as $game)
			{
				$games[$game['date']][] = array($game['Master'], $game['GameId'], $game['RoomId']);		
			}
			getView("ShowGamesView.inc", array('type'=>"games", 'games'=>$games));
		}	
		else
		{
			$dates = SQL("select DISTINCT(date) from Games order by date DESC")->getAll();	
			getView("ShowGamesView.inc", array('type'=>"dates", 'dates'=>$dates));
		}
		
	}
	public function showGame()
	{
		$gameId = (int)$_GET['GameId'];
		$game = new Game($gameId);
		$game->show();
	}
	public function editGame()
	{
		if (!($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			header("Location: /getRating/");
		else
		{
			if ($_SERVER['REQUEST_METHOD'] == 'GET')
			{	
				$players = SQL("select  Status, Name from Players join Statuses USING(StatusId)")->getAll();
				$data['players'] = $players;
				$gameId = (int)$_GET['GameId'];
				$game = new Game($gameId);
				$data['game'] = $game;
				getView("EditGameView.inc", $data);
				//$game->editShow();
			}
			if ($_SERVER['REQUEST_METHOD'] == 'POST')
			{
				$gameId = (int)$_POST['GameId'];
				$game = new Game($_POST);
				$game->update($gameId);
				header("Location: /showGame/?GameId=$gameId");
			}
		}
	}
	public function getDomination()
	{
		$players = SQL("Select Name from Players")->getAll();
		$data['players'] = $players;

		if (isset($_GET['ComparePlayer1']) && isset( $_GET['ComparePlayer2']))
		{		
				$data['domination'] = new Domination($_GET['ComparePlayer1'], $_GET['ComparePlayer2']);
		}
		getView("DominationView.inc", $data);
	}
	public function getPowerMap()
	{
		if ($_SESSION['isAuth'])
		{
			$pm = new PowerMap($_SESSION['player']);
			getView("PowerMapView.inc", $pm);
		}
		
		else
			getView("Auth.inc",$players);
	}

}

?>
