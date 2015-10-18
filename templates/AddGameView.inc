<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="inserter">
<div>
	
	<form action="?action=addGame" method="post">
		<div>
		<p>Выберите номер игрового зала
		<select name='RoomId'>
			<option selected>1</option>
			<option>2</option>
			<option>3</option>
			<option>4</option>
		</select></p>
		<table>
		
		<tr><th>№</th><th>Игрок</th><th>Роль</th><th>Лучший</th><th>Фолы</th>
<?php	for ( $i = 0; $i < 10; $i++)	
	echo "<tr><td>".($i+1)."</td><td><input type='text' name=Player$i list='players_list'></td>
		<td><select name='Role$i'>
			<option>Citizen</option>
			<option>Sherif</option>
			<option>Mafia</option>
			<option>Don</option>
		</select></td>
		<td><input type='checkbox' name='Best$i'/></td>
		<td><select name='Warnings$i'>
			<option>0</option>
			<option>1</option>
			<option>2</option>
			<option>3</option>
			<option>4</option>
		</select></td>
		</tr>"
?>
		
			<tr><td></td><td><input type='text' name='BestMovePlayer' placeholder='Первоубиенный' list='players_list'/></td>
			<td><select name='BestMovePoints'>
				<option selected value="0">Не попал</option>
				<option value="2">Назвал 2</option>
				<option value="3">Назвал 3</option>
			</select></td></tr></div>
		</table></div>
<div>	
			Победила команда:
			<select name="result">
				<option value="City" selected>Мирных жителей</option>
				<option value="Mafia">Мафии</option>
				<option value="Draw">Ничья</option>
			</select>
			</div>
		<p><input type="submit" value="Send"></p>
	</form>

<datalist id="players_list">
<?php	foreach ($obj as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
<datalist id="roles_list">
    		<option>citizen</option>
		<option>sherif</option>
		<option>mafia</option>
		<option>don</option>	
</datalist>
</div>
<?php getView("Footer.inc", $obj);?>

</body>
