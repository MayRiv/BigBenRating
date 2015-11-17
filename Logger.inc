<?php
class Logger
{
	private static $fp;
	private static $_instance;
	public static  function getInstance()
	{
		if (System::$_instance == null) System::$_instance = new System("history.log");
		return System::$_instance;
	}

	private function __construct($logPath)
	{
		$this->fp = fopen($logPath, "a");
	}
	public function write($line)
	{
		fwrite($fp, "[".date("F j, g:i a")."] " . $line);
	}

}

?>