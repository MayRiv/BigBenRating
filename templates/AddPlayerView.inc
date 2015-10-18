<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=addPlayer" method="post">
	<p><input type="text" name="Name" placeholder="Введите ник игрока"/></p>	
	<p>Установите права <select name="Status">
		<option selected value="1">Игрок</option>
		<option value="2">Ведущий</option>
	</select></p>
	<p><input type="submit" value="Добавить"></p>
	</form>
</div>
<?php getView("Footer.inc", null); ?>
</body>
