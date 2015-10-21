<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
<?php
	if (isset($obj))
	{
		echo "<tr><th>Дата</th><th>Зал</th><th>Ведущий</th><th>Подробно</th><th>Удалить</th></tr>";
		foreach ($obj as $date => $tables) {
			
			foreach ($tables as $roomId => $game) {
				$date_parsed = date_parse($date);
				$year = $date_parsed["year"];
				$month = $date_parsed["month"];
				$day = $date_parsed["day"];
				echo "<tr><td>$year-$month-$day</td><td>$roomId зал</td><td>Ведущий $game[0]</td><td><a href='?action=showGame&GameId=$game[1]'>Игра №".$game[1]."</a></td>";
				if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
					echo "<td><a href='?action=deleteGame&gameid=$game[1]'>Удалить</a></td>";
				echo "</tr>";
			}
		}
	}
?>
	</table>
<?php getView("Footer.inc", $obj);?>

</body>
