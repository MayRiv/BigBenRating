<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="inserter">
<div>
	
	<form action="/?action=insertGame" method="post">
		<div>
		<p><input type='text' name="Master" placeholder="Ник ведущего" list='masters_list'></p>
		<p><input type='text' name="RoundNumber" placeholder="Номер раунда"></p>			
		<table>
						
		<tr><th>Игрок</th><th>Роль</th><th>Оценка ведущего</th><th>Штрафные баллы</th><th>ДрессКод</th>
<?php	for ( $i = 0; $i < 10; $i++)	
	echo "<tr><td><input type='text' name=Player$i list='players_list'></td>
		<td><select name='Role$i'>
			<option>Citizen</option>
			<option>Sherif</option>
			<option>Mafia</option>
			<option>Don</option>
		</select></td>
		<td><input type='text' name='MasterMark[]'/></td>
		<td><input type='text' name='Penalty$i'/></td>
		<td><input type='text' name='DressCode$i'/></td></tr>";
?>
		</table></div>
		<div>
		<div>
		<table><caption>Голосование за лучшего игрока</caption>
		<tr><th>Ник игрока</th><th>Баллі</th></tr>
<?php	for ( $i = 0; $i < 5; $i++) 
			echo "<tr><td><input type='text' name='BestPlayer$i' placeholder='Ник игрока' list='players_list'/></td><td><input type='text' name='BestVotes$i' placeholder='Количество голосов'/></td></tr>";
?>
		<input type='text' name='BestMovePlayer' placeholder='Первоубиенній' list='players_list'/>
		<input type='text' name='BestMovePoints' placeholder="Баллы за лучший ход" />
		<table></div>
		<div>
			<p>Номинация сюрприз, введите от 1 до3 игроков</p>
<?php	for ( $i = 0; $i < 3; $i++) 
			echo "<input type='text' name='Surprise[]' placeholder='Íèê èãðîêà' list='players_list'/>";
?>
		</div>		
			Победила команда:
			<select name="result">
				<option value="City" selected>City</option>
				<option value="Mafia">Mafia</option>
				<option value="Draw">Draw</option>
			</select>
			<p><input type="text" name="RoomId" placeholder="Enter room number"/></p>
		</div>
		<p><input type="submit" value="Send"></p>
	</form>

<datalist id="players_list">
<?php	foreach ($obj['players'] as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
<datalist id="masters_list">
<?php	foreach ($obj['masters'] as $master)
    		echo "<option>".$master['MasterName']."</option>";?>
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