<html>
<head>
	<link rel="stylesheet" type="text/css" href="templates/bigbenrating.css"/>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
	<div id="auth-div">
		<?php
		if (isset($_SESSION['isAuth']) && $_SESSION['isAuth'] == 1)
		{
			echo "<p>Привет".$_SESSION['player']."</p>";
			echo "<a href='/?action=logout'>Выйти</a>";
		}
		else
		{
			echo "<a href='/?action=login'>Авторизироваться</a>";
		}
		?>
	</div>
	<div><p>Рейтинг клуба BigBen</p></div>
	<div id="css-menu-wrapper">
		<div id="css-menu">
			<ul>
				<li><a href="/?action=getRating">
					<span class="text-top">Общий рейтинг</span>
					<span class="text-bottom">Рейтинг игроков</span>
				</a></li>
				<li><a href="/?action=getPersonalStat">
					<span class="text-top">Личный кабинет</span>
					<span class="text-bottom">Статистика игрока</span>
				</a></li>
				<li><a href="/?action=showGames">
					<span class="text-top">Подробно про игры</span>
					<span class="text-bottom">История игр</span>
				</a></li>
				<li><a href="/?action=showAdminPanel">
					<span class="text-top">Административная панель</span>
					<span class="text-bottom">Для ведущих</span>
				</a></li>
			</ul>
		</div>
	</div>