<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>Глобальная статистика</h2>
<?php
var_dump($obj);
foreach ($obj->top as $role=>$stat) {
	echo "<table class='table_dark'>
	 <caption>Top-3 $role</caption>
	 <th>Игрок</th><th>Сыграно игр</th><th>Процент победы</th>";

	 foreach ($stat as $player) {
	 	echo "<tr><td>".$player['player']."</td><td>".$player['t']."</td><td>".$player['r']."</td></tr>";
	 }
}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
