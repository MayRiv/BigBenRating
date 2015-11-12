<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2></div>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Рейтинг</th><th>Сыграно игр</th><th>Победы</th><th>Количество лучших</th></tr>

<?php
	if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
	{
		$i = 1;
		foreach ($obj as $player) {
			echo "<tr><td>$i</th><td>".$player['player']."</td><td>".(int)(1000 * $player['r'])."</td><td>".$player['t']."</td><td>";
$percent = round($player['v'] / $player['t'] * 100, 2);
echo $player['v']."($percent%)";
echo "</td><td>".$player['b']."</td></tr>";
			$i++;
		}
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
