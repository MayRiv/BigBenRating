<?php
require("Field.inc");
require_once("DBManager.inc");

class Table
{
	protected $name;
	protected $caption;
	protected $primaryKey;
	protected $currentAction;   //browse  edit  insert

	protected $fields;
	protected $currentRowVal;
	protected $scriptName;

	protected $eventHandlers;

	protected $isExec = false;
	protected $isHTMLEditorNeed;

	protected $header;
	protected $footer;
	protected $css;

	protected $isHasCombo = false;

	//FOR MAIN-DETAIL INTERFACE
	protected $mainTable;
	protected $thisTableFK;
	protected $detailTable = array();
	//

	public function __construct($name, $caption, $primaryKey, $scriptName)
	{
		$this->name = $name;
		$this->caption = $caption;
		$this->scriptName = $scriptName;
		$this->fields = array();

		if(is_array($primaryKey))
		{
			$this->primaryKey = $primaryKey;
		}
		else
		{
			$this->primaryKey = array($primaryKey);
		}

		$this->eventHandlers['beforeUpdate'] = array();
		$this->eventHandlers['afterUpdate'] = array();
		$this->eventHandlers['beforeInsert'] = array();
		$this->eventHandlers['afterInsert'] = array();
		$this->eventHandlers['beforeDelete'] = array();
		$this->eventHandlers['afterDelete'] = array();


		$this->currentAction = "browse";

		if(isset($_GET['action']))
		{
			$this->currentAction = $_GET['action'];
		}

		if($this->currentAction == 'edit')
		{
			DBManager::getInstance()->connect("localhost", "maska9", "root", "");
			$query = " where ";
			foreach ($this->getPrimaryKeyAll() as $pk)
			{
				$query .= $pk." = ? and ";
			}
			$query = substr($query, 0, -4);
			$this->currentRowVal = SQL("select * from ".$this->name.$query,array($_GET['id']))->next();
		}
		
		if($this->currentAction == 'browse' && !empty($_POST))
		{
			$this->isExec = true;
		}
	}

	public function addField($name, $type, $caption, $formPrefix, 
		$cssClass, $defaultValue = "", $isVisibleBr = true, $isVisible = true, $isAutoInc = false)
	{
		$value = $this->currentRowVal[$name];
		if($this->isExec)
		{
			$value = (isset($_POST[$formPrefix.$name]))? $_POST[$formPrefix.$name] : $defaultValue;
		}
		if($type == 'html')
		{
			$this->isHTMLEditorNeed = true;
		}elseif(is_array($type))
		{
			$this->isHasCombo = true;
		}



		$this->fields[] = new Field($name, $type, $caption, $formPrefix, 
			$cssClass, $defaultValue, $isVisibleBr, $isVisible, $value, $isAutoInc);
	}

	public function addDetailTable($ref, $caption)
	{
		$this->detailTable[] = array('ref' => $ref,'caption'=> $caption);
	}

	public function setMainTable($ref, $fkName)
	{
		$this->mainTable = $ref;
		$this->thisTableFK = $fkName;
	}

	public function setScriptName($newScriptName)
	{
		$this->scriptName = $newScriptName;
	}

	public function addHeader($headerPath)
	{
		$this->header = $headerPath;
	}

	public function addFooter($footerPath)
	{
		$this->footer = $footerPath;
	}

	public function getBrowseReference($mainId, $detailPK)
	{
		$reference = $this->scriptName;
		if(isset($this->mainTable))
		{
			$query = 'select * from '.$this->name.' where '.$this->getPrimaryKey()." = '$mainId'";

			DBManager::getInstance()->connect("localhost", "maska9", "root", "");
			$refId = SQL($query)->next()[$this->thisTableFK];
			$reference.='?mainId='.$refId;
		}
		return $reference;
	}

	public function getName()
	{
		return $this->name;
	}

	public function getCaption()
	{
		return $this->caption;
	}

	public function getScriptName()
	{
		return $this->scriptName;
	}

	public function mainProcess()
	{
		if($this->isExec)
		{
			$params = array();
			$isUpdate = isset($_POST['old_'.$this->getPrimaryKey()]);


			foreach ($this->fields as $f) 
			{
				if(!$isUpdate || ($isUpdate && $f->isVisible()))
				{
					if($f->isAutoInc())
					{
						$params[] = '';
					}
					else
					{
						$params[] = $f->getSQLValue();
					}
				}
			}

			if($isUpdate)
			{
				$this->createEvent('beforeUpdate');

				$params[] = $_POST['old_'.$this->getPrimaryKey()];
				
				try
				{


					DBManager::getInstance()->connect("localhost", "maska9", "root", "");
					SQL($this->generateSQL('update'), $params);
					$this->createEvent('afterUpdate');
				}
				catch(PDOException $e)
				{
					echo 'Update error';
				}
			}
			else
			{
				$this->createEvent('beforeInsert');
				try
				{
					DBManager::getInstance()->connect("localhost", "maska9", "root", "");
					SQL($this->generateSQL('insert'), $params);
					$this->createEvent('afterInsert');					
				}
				catch(PDOException $e) 
				{
					echo 'Insert error';
				}		
			}
		}

		if (isset($this->header)) 
		{
			include($this->header);	
		}
		if($this->isHTMLEditorNeed == true)
		{
			echo '<script src="ckeditor/ckeditor.js" ></script>';
		}

		switch($this->currentAction)
		{
			case 'browse':
				$this->browse();
				break;
			case 'edit':
				$this->edit();
				break;
			case 'insert':
				$this->insert();
				break;
			case 'delete':
				{
					$this->createEvent('beforeDelete');
					DBManager::getInstance()->connect("localhost", "maska9", "root", "");

					SQL($this->generateSQL('delete'), array($_GET['id']));

					$this->createEvent('afterDelete');

					$this->browse();
					break;
				}
			default:
				echo 'such mod not found';
		}
		if(isset($this->footer))
		{
			include($this->footer);
		}
	}

	protected function browse()
	{
		$select = "select ";
        $what = "*";
		$from = " from ".$this->name;
	    if($this->isHasCombo)
	    {
	    	$what = "";
	    	foreach ($this->fields as $f) {	    			    		
	    		$what .= $f->getName().", ";
	    		if($f->isLookup() != false)
	    		{
	    			$lookInf = $f->getLookupInfo();
	    			if($this->name != $lookInf['table'])
	    			{
	    				$n = $f->getName();
	    				$what .= "if (".$n." = '' || isnull(".$n."), ".$n.", ( select ".
	    				$lookInf['table'].".".$lookInf['captionfield']." from ".$lookInf['table']." where ".
	    				$lookInf['table'].".".$lookInf['field']." = ".$this->name.".".$f->getName().")) as ".$f->getName()."_combo, ";
	    			}
	    			else
	    			{
	    				$what .= $f->getName().", ";
	    			}
	    		}
	    	}
	    	$what = substr($what, 0, -2);
		}

		if(isset($_GET['mainId']))
		{
			$from .= ' where ';
			$temp = $_GET['mainId'];
			//foreach ($temp as $key => $value) 
			//{
				$from .= $this->thisTableFK." = '$temp'";//' and ';
			//}
			//$from = substr($from, 0, -4);
		}
		DBManager::getInstance()->connect("localhost", "maska9", "root", "");
		$rows = SQL($select.$what.$from)->getAll();


		$mId = '';
		if(isset($this->mainTable) && isset($_GET['mainId']))
		{
			$mId = '&mainId='.$_GET['mainId'];
		}

		echo "<a class='addlink' href = '".$this->scriptName."?action=insert".$mId."''><img src='Pictures/add.png'> <span>Добавить новую запись</span></a>";
		echo "<table class = 'browsetable'>";
		echo "<tr id='tablecaption'>";
		if(isset($this->mainTable) && isset($_GET['mainId']))
		{
			echo "<p><a class='backlink' href='".$this->mainTable->getBrowseReference($_GET['mainId'], $this->getPrimaryKey())."'>Назад у ".$this->mainTable->getCaption()."</a></p>";			
		}
		//<td></td> 
		echo "<td colspan = '100'>".$this->caption."</td> </tr>";
		echo "<tr id='tableheader'>";
		echo "<td>Змін.</td>";
		echo "<td>Вид.</td>";
		if(!empty($this->detailTable))
		{
			foreach ($this->detailTable as $t) 
			{
				echo '<td>Д. І.</td>';
			}
		}
		foreach ($this->fields as $f) {			
			if($f->isVisibleBrowse() == 'true')
			{
				echo "<td>";
				echo $f->getCaption();
				echo "</td>";
			}
		}
		echo "</tr>";
		foreach ($rows as $row) 
		{
			echo "<tr>";
			echo "<td class = 'changelink'>";
			echo "<a href = '".$this->scriptName."?action=edit&id=".$this->getPrimaryKeyValueFrom($row)."'><img src='Pictures/edit.png'></a>";
			echo "</td>";
			echo "<td class = 'deletelink'>";
			$t = "onclick=\"return confirm('Видалити запис?')\"";
			echo "<a href = '".$this->scriptName."?action=delete&id=".$this->getPrimaryKeyValueFrom($row)."'".$t." ><img src='Pictures/delete.png'></a>";
			echo "</td>";

			if(!empty($this->detailTable))
			{
				foreach ($this->detailTable as $t) 
				{
					echo '<td>';
					echo "<a class='detaillink' href='".$t['ref']->getScriptName()."?mainId=".$this->getPrimaryKeyValueFrom($row)."'>".$t['caption']."</a>";
					echo '</td>';	
				}
			}

			foreach ($this->fields as $f) 
			{
				if($f->isVisibleBrowse() == 'true')
				{
					echo "<td>";
					if($f->isLookup() && ($this->name != $f->getLookupInfo()['table']))
					{
						echo Field::prepareValue($row[$f->getName().'_combo']);
					}
					else
					{
						echo Field::prepareValue($row[$f->getName()]);			
					}
					echo "</td>";
				}
			}
			echo "</tr>";
		}
		echo "</table>";
	}

	protected function edit()
	{
		echo "<div id = 'edittable'>";
		$this->createForm();
		echo "</div>";
	}

	protected function insert()
	{
		echo "<div id = 'edittable'>";
		$this->createForm();
		echo "</div>";
	}

	protected function createForm()
	{
		$mId = '';
		if($this->currentAction == 'insert' && isset($_GET['mainId']))
		{
			$mId = '?mainId='.$_GET['mainId'];
		}

		echo "<form action='".$this->scriptName.$mId."' method='post'>";
		echo "<table>";
		foreach ($this->fields as $f) {
			if($f->isAutoInc() == false && $f->isVisible() == true)
			{
				if($this->compareWithPrimaryKey($f->getName()))
				{
					echo "<tr id='txt-primary'>";
				}
				else
				{
					echo "<tr>";
				}
			
				if($f->getType() == 'html')
				{
					echo "<td colspan='2'><p>".$f->getCaption()."</p>".$f->createControl()."</td>";
				}
				else
				{
					echo "<td>".$f->getCaption()."</td>";
					if($this->currentAction == 'insert' && isset($_GET['mainId']) && $f->getName() == $this->thisTableFK)
					{
						echo "<td>".$f->createControl($_GET['mainId'], $this->thisTableFK)."</td>";
					}
					else
					{
						echo "<td>".$f->createControl()."</td>";
					}
				}
				echo "</tr>";	
			}
		}
		if($this->currentAction == 'edit')
		{
			$pkValue = $this->getPrimaryKeyValueFrom();
			echo "<tr> <td> <input type='hidden' name='old_".$this->getPrimaryKey()."' value='".$pkValue."'> </td> </tr>";
		}
		echo "<tr> <td colspan = '2'> <input type='submit' class = 'input-submit'> </td></tr>";
		echo "</table>";
		echo "</form>";
	}

	protected function generateSQL($type)
	{
		$query = "";

		switch($type)
		{
			case 'insert':
			{
				$query = "INSERT INTO ".$this->name." VALUES( ";
				foreach ($this->fields as $f) 
				{
					$query .= '?,';
				}
				$query = substr($query, 0, -1);
				$query .= " )";
				return $query;
			}
			case 'update':
			{
				$query .= "UPDATE ".$this->name." SET ";
			    foreach ($this->fields as $f) 
			    {
					if($f->isVisible())
					{
						$query .= $f->getName().' = ?,';
					}
				}
				$query = substr($query, 0, -1);
				$query .= " where ";

				foreach ($this->getPrimaryKeyAll() as $pk)
				{
					$query .= $pk." = ? and ";
				}
				return substr($query, 0, -4);
			}
			case 'delete':
			{
			    return "DELETE FROM ".$this->name." WHERE ".$this->getPrimaryKey()." = ?";
			}
		}
	}

	public function addEventListener($eventName, $listener)
	{
		if(isset($this->eventHandlers[$eventName]))
		{
			$this->eventHandlers[$eventName][] = $listener;
		}
	}

	protected function createEvent($eventName, $params = array())
	{
		if(isset($this->eventHandlers[$eventName]))
		{
			foreach ($this->eventHandlers[$eventName] as $handler) 
			{
				$handler($params);
			}
		}
	}

	protected function getPrimaryKey()
	{
		$result = "";
		foreach ($this->primaryKey as $pk) 
		{
			$result .= $pk."|";
		}
		return substr($result, 0, -1);
	}

	protected function getPrimaryKeyAll()
	{
		return $this->primaryKey;
	}

	protected function compareWithPrimaryKey($what)
	{
		$result = false;
		foreach($this->primaryKey as $pk)
		{
			if($what == $pk)
			{
				$result = true;
			}
		}
		return $result;
	}

	protected function getPrimaryKeyValueFrom($array = null)
	{
		$result = "";
		if(is_null($array))
		{
			foreach($this->fields as $f)
			{
				if($this->compareWithPrimaryKey($f->getName()))
				{
					$result .= $f->getSQLValue()."|";
				}
			}
		}
		else
		{
			foreach ($array as $key => $val) 
			{
				if($this->compareWithPrimaryKey($key))
				{
					$result .= $val."|";
				}
			}
		}
		return substr($result, 0, -1);
	}

	protected function getPrimaryKeyValuesFromLine($line)
	{
		$temp = split('\|', $line);
		$result = array();
		for($i = 0; $i < count($temp); $i++) 
		{
			$result[$this->primaryKey[$i]] = $temp[$i];
		}
		return $result;
	}
}
?>

