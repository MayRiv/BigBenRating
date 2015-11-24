<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Карта силы</h1>
	<body><table class="table_dark"><caption>Статистика совместных игр</caption>
		<tr><th>Ник игрока</th><th>Баланс побед</th></tr>
<?php
	{
		

		$players = arsort($obj->map);
		$zeroPlayerInserted = false;
		foreach ($obj->map as $player => $domination) {
			if ($domination==0 && !$zeroPlayerInserted)
			{
				echo "<tr style='color:#00FF00'><td>".$_SESSION['player']."</td><td>0</td></tr>";
				$zeroPlayerInserted = true;
			}
			echo "<tr><td>$player</td><td>$domination</td></tr>";
		}
		echo '</table>';
	}
?>
</div>
<?php getView("Footer.inc", null); ?>
</body>
