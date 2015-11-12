<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Доминация</h1>
	
	<form id="form" action="?action=getDomination" method="post">
		<p>Чтобы получить статистику общих игр двух игркоов введите их ники и нажмите "Сравнить"</p>
		<p><input name='ComparePlayer1' type="text" list='players_list'/><input name='ComparePlayer2' type="text" list='players_list'/></p>
		<p><input type="submit" value="Сравнить"/></p>
	</form>
<?php
	if (isset($obj['BRed']))
	{
		echo '<body><table class="table_dark"><caption>Статистика совместных игр</caption>';
		echo "	<tr><th>Роли</th><th>Всего игр</th><th>Побед у ".$obj['comparePlayer1']."</th><th>Побед у ".$obj['comparePlayer2']."</th></tr>";
		
		echo "<tr><td>Оба красных</td><td>".$obj['BRed']['total']."</td><td>".$obj['BRed']['v1']."</td><td>".$obj['BRed']['v2']."</td></tr>";
		echo "<tr><td>Оба черных</td><td>".$obj['BBlack']['total']."</td><td>".$obj['BBlack']['v1']."</td><td>".$obj['BBlack']['v2']."</td></tr>";
		echo "<tr><td>".$obj['comparePlayer1']." красный, ".$obj['comparePlayer2']." черный</td><td>".$obj['RB']['total']."</td><td>".$obj['RB']['v1']."</td><td>".$obj['RB']['v2']."</td></tr>";
		echo "<tr><td>".$obj['comparePlayer1']." черный, ".$obj['comparePlayer2']." красный</td><td>".$obj['BR']['total']."</td><td>".$obj['BR']['v1']."</td><td>".$obj['BR']['v2']."</td></tr>";
		echo '</table>';
		echo "<p>".$obj['comparePlayer1']." застрелил ".$obj['comparePlayer2']." ". $obj['BR']['s']." раз</p>";
		echo "<p>".$obj['comparePlayer2']." застрелил ".$obj['comparePlayer1']." ". $obj['RB']['s']." раз</p>";
	}
?>
</div>
<datalist id="players_list">
<?php	foreach ($obj['players'] as $player)
			if (!($player['Status'] === "Master" || $player['Status'] === "Admin"))
    			echo "<option>".$player['Name']."</option>";?>
</datalist>
<?php getView("Footer.inc", null); ?>
</body>
