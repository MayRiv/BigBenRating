<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Карта силы</h1>
	<body><table class="table_dark"><caption>Статистика совместных игр</caption>
		<tr><th>Ник игрока</th><th>Баланс побед</th></tr>
<?php
	{
		

		$players = arsort($obj->map);
		$zeroPlayerInserted = false;
		foreach ($player as $player => $domination) {
			if ($domination==0 && !$zeroPlayerInserted)
			{
				echo "<tr style='color:#00FF00'><td>".$_SESSION['player']."</td><td>0</td></tr>";
				$zeroPlayerInserted = true;
			}
			echo "<tr><td>$player</td><td>$domination</td></tr>";
		}
		echo '</table>';
		if (isset($obj['BR']['s']))
			echo "<p>".$obj['comparePlayer1']." застрелил ".$obj['comparePlayer2']." ". $obj['BR']['s']." раз</p>";
		if (isset($obj['RB']['s']))
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
