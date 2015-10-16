<?php getView("HeaderView.inc", $obj);?>
<body>
	<table class="table_dark">
		<tr><th>Игрок</th><th>Баллы за роль</th><th>Лучшие</th><th>Лучший ход</th><th>Сюрприз</th><th>Штрафы</th></tr>
<?php 
	//echo "<tr><td>".$obj['game']['."</td><td></td><td></td><td></td>|
	foreach ($obj['players'] as $player) {
	echo "<tr><td>".$player['player']."</td><td>".$player['Role']."</td><td>".$player['BestVotes']."</td><td>".$player['BestMove']."</td><td>".$player['Surprise']."</td><td>".$player['Penalty']."</td></tr>";
}
?>
	</table>
	<div id="feed">
<?php
	echo "<p>Победила команда: ".$obj['game']["Status"]."</p>";
	echo "<p>Ведущий: ".$obj['game']["MasterName"]."</p>";
?>
	</div>
<?php getView("Footer.inc", $obj);?>

</body>