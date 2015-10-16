<html>
<head>
	<link rel="stylesheet" type="text/css" href="maska9.css"/>
</head>
<body>
	<?php getView("HeaderView.inc", $obj);?>
	<div>
		<form action="authCaptain.php" method="post">
  			<p><input type="text" name="Team" placeholder="Введите номер команды"></p>
			<p><input type="text" name="Pass"placeholder="Введите пароль"></p>
  			<p><input type="submit" value="Authorize"></p>
 		</form>
	</div>
<?php getView("Footer.inc", $obj);?>

</body>
</html>