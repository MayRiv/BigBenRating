<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Личный кабинет</h1>
	<?php
		$obj->show();
	?>
<p><a href="?action=changePassword">Сменить пароль</a></p>
</div>

<?php getView("Footer.inc", null); ?>
</body>