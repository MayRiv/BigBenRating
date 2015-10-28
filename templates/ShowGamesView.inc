<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
<?php
	if (isset($obj))
	{
		$isAdmin = false;
		if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
			$isAdmin = true;

		echo "<tr><th>Дата</th><th>Зал</th><th>Ведущий</th><th>Подробно</th>";
		if ($isAdmin)
			echo "<th>Удалить</th>";
		echo "</tr>";
		foreach ($obj as $date => $games) {
			foreach ($games as $game) {
				echo "<tr><td>$date</td><td>".$game[2]." зал</td><td>Ведущий $game[0]</td><td><a href='?action=showGame&GameId=$game[1]'>Игра №".$game[1]."</a></td>";
				if ($isAdmin)
					echo "<td><a href='?action=deleteGame&gameid=$game[1]'>Удалить</a>";
				echo "</tr>";
			}
		}
	}
?>
	</table>
<?php getView("Footer.inc", $obj);?>

</body>
