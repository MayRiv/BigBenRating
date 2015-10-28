<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Доминация</h1>
	
	<form id="form" action="?action=getDomination" method="post">
		<p>Чтобы получить статистику общих игр двух игркоов введите их ники и нажмите "Сравнить"</p>
		<p><input name='ComparePlayer1' type="text"/><input name='ComparePlayer2' type="text"/></p>
		<p><input type="submit" value="Сравнить"/></p>
	</form>
<?php
	if (isset($obj))
	{
		echo '<body><table class="table_dark"><caption>Статистика совместных игр</caption>';
		echo "	<tr><th>Роли</th><th>Всего игр</th><th>Побед у ".$obj['comparePlayer1']."</th>";
		
		echo "<tr><td>Оба красных</td><td>".$obj['BRed']['total']."</td><td>".$obj['BRed']['v']."</td></tr>";
		echo "<tr><td>Оба черных</td><td>".$obj['BBlack']['total']."</td><td>".$obj['BBlack']['v']."</td></tr>";
		echo "<tr><td>".$obj['comparePlayer1']." красный, ".$obj['comparePlayer2']." черный</td><td>".$obj['RB']['total']."</td><td>".$obj['RB']['v']."</td></tr>";
		echo "<tr><td>".$obj['comparePlayer1']." черный, ".$obj['comparePlayer2']." красный</td><td>".$obj['BR']['total']."</td><td>".$obj['BR']['v']."</td></tr>";
		echo '</table>';
	}
?>
</div>

<?php getView("Footer.inc", null); ?>
</body>