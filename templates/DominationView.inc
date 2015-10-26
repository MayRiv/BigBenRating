<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Доминация</h1>

	<form id="form" action="?action=getDomination" method="post">
		<p>Чтобы получить статистику общих игр двух игркоов введите их ники и нажмите "Сравнить"</p>
		<p><input id='ComparePlayer1' type="text"/><input id='ComparePlayer2' type="text"/></p>
		<p><input type="submit" value="Сравнить"/></p>
	</form>
<?php
	if (isset($obj))
	{
		echo $obj['comparePlayer1']. "vs". $obj['comparePlayer1'];

	}
?>
</div>

<?php getView("Footer.inc", null); ?>
</body>