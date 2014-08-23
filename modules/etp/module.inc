<?php

class mod_etp extends associationModule
{
	function getNodes()
	{
	}
	function getMenuItems()
	{
	}
	function getGgNodeName()
	{
		$res=array();
		$module="etp";
	 $res[]= $module."."."coeur";
$res[]= $module."."."poids";
	 	 return $res;
	}
}


?>