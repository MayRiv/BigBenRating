<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=login" method="post">
  			<p><input type="text" name="Player" placeholder="Введите ник" list='players_list'></p>
			<p><input type="text" name="Password"placeholder="Введите пароль"></p>
  			<p><input type="submit" value="Войти"></p>
 	</form>
</div>
</body>
<datalist id="players_list">
<?php	foreach ($obj as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
