<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Личный кабинет</h1>
	<?php
		$obj->show();
	?>
	
	<div id="CompareDiv">
	</div>
	<p>Чтобы получить статистику общих игр с игроком введите его ник и нажмите "Сравнить"</p>
<p><input id='ComparePlayer' type="text"/><input type="button" value="Сравнить" onclick="bbr.compare(this.value)"/></p>
<p><a href="?action=changePassword">Сменить пароль</a></p>
</div>

<?php getView("Footer.inc", null); ?>
</body>