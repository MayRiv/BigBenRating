<?php
	$pass = $_GET['pass'];
	$hash = MD5($pass);
	echo $hash;
?>