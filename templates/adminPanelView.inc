<?php getView("HeaderView.inc", $obj);?>
<body>
<div id="css-menu-wrapper">
	<div id="css-menu">
		<ul>
			<li><a href="/?action=adminPanel&players">Игроки</a></li>
			<li><a href="/?action=adminPanel&teams">Команды</a></li>
			<li><a href="/?action=adminPanel&masters">Ведущие</a></li>
			<li><a href="/?action=adminPanel&best">Лучшие</a></li>
			<li><a href="/?action=adminPanel&surprise">Сюрприз</a></li>
			<li><a href="/?action=adminPanel&dressm">М. дресс</a></li>
			<li><a href="/?action=adminPanel&dressw">Ж. дресс</a></li>
			<li><a href="/?action=adminPanel&dresst">К. дресс</a></li>
		</ul>
	</div>
</div>
<div id="feed">
	<table class="table_dark">
			
		<?php
		if (isset($obj))
		{
			$i = 1;
			foreach ($obj['list'] as $queryResult)
			{	
	    			echo "<tr><td>$i</td><td>".$queryResult[$obj["title"]]."</td><td>".$queryResult["points"]."</td></tr>";
				$i++;
			}
		}
	?>
	</table>
	
</div>
<?php getView("Footer.inc", $obj);?>
</body>