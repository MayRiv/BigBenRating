<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>Глобальная статистика</h2>
<?php
foreach ($obj->top as $role=>$stat) {

	 echo "<p>Top-3 $role</p><table class='table_dark'>
	 <th>Игрок</th><th>Сыграно игр</th><th>Процент победы</th>";

	 foreach ($stat as $player) {
	 	echo "<tr><td>".$player['player']."</td><td>".$player['t']."</td><td>".$player['r']."</td></tr>";
	 }

}
?>
</div>
<?php getView("Footer.inc", null); ?>
</body>
