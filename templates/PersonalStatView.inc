<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<h1>Личный кабинет</h1>
	<?php
		$obj->show();
	?>
	<a href="?action=changePassword">Сменить пароль</a>

</div>
<?php getView("Footer.inc", null); ?>
</body>
