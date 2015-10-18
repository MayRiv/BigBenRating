<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
<?php
	if (isset($obj))
	{
		echo "<tr><th>Дата</th><th>Зал</th><th>Ведущий</th><th>Подробно</th></tr>";
		foreach ($obj as $date => $tables) {
			
			foreach ($tables as $roomId => $game) {
				echo "<tr><td>$date</td><td>$roomId зал</td><td>Ведущий $game[0]</td><td><a href='?action=showGame&GameId=$game[1]'>Игра №".$game[1]."</a></td></tr>";
			}
		}
	}
?>
	</table>
<?php getView("Footer.inc", $obj);?>

</body>
