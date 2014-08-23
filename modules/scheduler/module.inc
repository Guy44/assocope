<?php

  define('HOUR',3600);
  define('DAY',86400);

 

  class mod_scheduler extends associationModule
  {
    function getNodes()
    {
      registerNode("scheduler.scheduler_cyclus", array("admin", "add", "edit", "delete","all_non_private"));
 
    }
  	function getMenuItems()
	{
	}
	function getGgNodeName()
	{
		$res=array();
		$module="scheduler";
	 $res[]= $module."."."scheduler_cyclus";
	 $res[]= $module."."."scheduler_cyclus_not";
	 $res[]= $module."."."scheduler_vacances";
	

	 return $res;
	}
 
  }

?>