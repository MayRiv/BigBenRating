<?php getView("HeaderView.inc", null); ?>
<div id="feed">
	<form action="?action=login" method="post">
  			<p><input type="text" name="Player" placeholder="Введите ник"></p>
			<p><input type="password" name="Password"placeholder="Введите пароль"></p>
  			<p><input type="submit" value="Войти"></p>
 	</form>
</div>
<script type="text/javascript">
<?php
$names = "var choices = [";
        	foreach ($obj as $player)
    			$names .= "'".$player['Name']."',";
    		$names[strlen($names) - 1] = ']';
    		echo $names;
?>
bbr.generateAutocompleter("Player", choices);
/*new autoComplete({
    selector: 'input[name="Player"]',
    minChars: 2,
    source: function(term, suggest){
        term = term.toLowerCase();
        
<?php
        	$names = "var choices = [";
        	foreach ($obj as $player)
    			$names .= "'".$player['Name']."',";
    		$names[strlen($names) - 1] = ']';
    		echo $names.";";
?>
        var matches = [];
        for (i=0; i<choices.length; i++)
            if (~choices[i].toLowerCase().indexOf(term)) matches.push(choices[i]);
        suggest(matches);
    }
});*/
</script>
<?php getView("Footer.inc", null); ?>
</body>
<datalist id="players_list">
<?php	foreach ($obj as $player)
    		echo "<option>".$player['Name']."</option>";?>
</datalist>
