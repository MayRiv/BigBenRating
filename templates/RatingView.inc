<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2></div>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Рейтинг</th><th>Количество игр</th></tr>

<?php
	$i = 1;
	foreach ($obj as $player) {
		echo "<tr><th>$i++</th><th>".$player['player']."</th><th>".$player['r']."</th><th>".$player['t']."</th></tr>";
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>