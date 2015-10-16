<?php
	require("Table.inc");
	require("viewer.inc");

	$table = new Table('PlayerGame', 'Players', array('Id'), 'admin.php');

	$arr1 = array('table' => 'Games', 'field' => 'GameId','isRequired' => false);
	$table->addField('Id','int','','','','null',false,false,true);
	$table->addField('Player','varchar','PlayerName','','');
	$table->addField('GameId',$arr1,'Game','','input-txt');
	//$table->addField('GameId','int','PlayerName','','','null',false,false,true);
	
	//$table->addField('Title','varchar','Title','','input-txt');

	/*$table->addField('Body','varchar','Body','','input-txt');
	$table->addField('ParentId',$arr1,'ParentId','','input-txt');
	
	$table->addField('sortField','varchar','SortField','','input-txt');
	
	$table->addField('IsContainer','int','IsContainer','','input-txt');*/
function beforeUpdateListener($params)
{
	//echo 'listenerBeforeWorks ';
}

function afterUpdateListener($params)
{
	//echo 'listenerAfterWorks ';
}

$table->addEventListener('beforeUpdate', 'beforeUpdateListener');
$table->addEventListener('afterUpdate', 'afterUpdateListener');
$table->addEventListener('beforeInsert', 'beforeUpdateListener');
$table->addEventListener('afterInsert', 'afterUpdateListener');
$table->addEventListener('beforeDelete', 'beforeUpdateListener');
$table->addEventListener('afterDelete', 'afterUpdateListener');


getView("HeaderView.inc", null);
$table->mainProcess();

?>
