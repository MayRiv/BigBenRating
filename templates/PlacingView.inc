<?php getView("HeaderView.inc", $obj);?>
<body>
<table class="table_dark">


<tr><td><a href="/?action=getPlacing&round=1"> Раccадка на 1 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=2"> Раccадка на 2 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=3"> Раccадка на 3 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=4"> Раccадка на 4 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=5"> Раccадка на 5 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=6"> Раccадка на 6 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=7"> Раccадка на 7 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=8"> Раccадка на 8 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=9"> Раccадка на 9 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=10"> Раccадка на 10 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=9"> Раccадка на 9 раунд</a></td></tr>
<tr><td><a href="/?action=getPlacing&round=10"> Раccадка на 10 раунд</a></td></tr>
</table>

<?php
if (isset($obj))
{
	getView("placing/placing$obj.inc", null);
}
?>
<?php getView("Footer.inc", $obj);?>

</body>