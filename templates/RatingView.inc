<?php getView("HeaderView.inc", null); ?>
<div id="feed"><h2>BigBen Rating</h2>
		<p>Рейтинг игроков за период от 12 до 21 ноября. Ограничения на количество игр пока нет.</p></div>
<table class="table_dark">
		<tr><th>#</th><th>Игрок</th><th>Рейтинг</th><th>Сыграно игр</th><th>Победы</th><th>Количество лучших</th></tr>

<?php
	//if (($_SESSION['isAuth'] && ($_SESSION['status'] === "Master" || $_SESSION['status'] === "Admin")))
	{
		$i = 1;
		$others = array();
		foreach ($obj as $player) 
			//if ($player['t'] >= 15)		
			{
			
				echo "<tr><td>$i</th><td>".$player['player']."</td><td>".(int)(1000 * $player['r'])."</td><td>".$player['t']."</td><td>";
				$percent = round($player['v'] / $player['t'] * 100, 2);
				echo $player['v']." ($percent%)";
				echo"</td><td>".$player['b']."</td></tr>";
				$i++;
			}
			/*else
			{
				$others[] = $player;
			}*/
		/*echo "<tr><td colspan='6'>Игроки, сыгравшие менее 15 игр</td></tr>";
		foreach($others as $player)
		{
			echo "<tr><td>$i</th><td>".$player['player']."</td><td>".(int)(1000 * $player['r'])."</td><td>".$player['t']."</td><td>";
				$percent = round($player['v'] / $player['t'] * 100, 2);
				echo $player['v']."($percent%)";
				echo"</td><td>".$player['b']."</td></tr>";
				$i++;
		}*/
	}
?>
</table>
<?php getView("Footer.inc", null); ?>
</body>
