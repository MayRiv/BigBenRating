<?php
require_once('System.inc');
class Router
{
	private static $_instance;
	private static $url;
	public static  function getInstance()
	{
		if (Router::$_instance == null) Router::$_instance = new Router();
		return Router::$_instance;
	}
	private function __construct()
	{

	}
	public function handle()
	{	
		Router::$url = $_GET['url'];
  		Router::$url = rtrim($url, '/');
  		$parsed = explode('/', Router::$url);
  		if(count($parsed) > 1 && property_exists('System', $parsed[1]))
  			$method = $parsed[1];
  		else
  			$method = "getRating";
		System::getInstance()->$method();
	}
}


?>