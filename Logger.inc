<?php
class Logger
{
	private $fp;
	private static $_instance;
	public static  function getInstance()
	{
		if (Logger::$_instance == null) Logger::$_instance = new Logger("history.log");
		return Logger::$_instance;
	}

	private function __construct($logPath)
	{
		$this->fp = fopen($logPath, "a");
	}
	public function write($line)
	{
		fwrite($this->fp, "[".date("F j, g:i a")."]  ".urldecode($line)."\n");
	}
	public function save()
	{
		fclose($this->fp);
	}
	public function show()
	{
		//$this->fp = fopen($logPath, "r");
		echo "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' /></head><body><div id='feed'>";
		/*while(!feof($this->fp)) { 
	    	echo fgets($this->fp) . "<br />";
		}*/
		//echo file_get_contents($fp);
		echo "</div></body></html>";
		//fclose($this->fp);
	}
}

?>