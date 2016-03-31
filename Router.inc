<?php
require_once('System.inc');
class Router
{
	private static $_instance;
	public $lastMonthEnd = '2016-3-16';
	public static  function getInstance()
	{
		if (Router::$_instance == null) Router::$_instance = new Router();
		return Router::$_instance;
	}
	private static $url;
	private function __construct()
	{

	}
	public function handle()
	{	
		$this->url = $_GET['url'];
  		$this->url = rtrim($url, '/');
  		$parsed = explode('/', $url);
  		if(count($parsed) > 1 && property_exists('System', $parsed[1]))
  			$method = $parsed[1];
  		else
  			$method = 'getRating';
		System::$this->method();
	}
}


?>