<?php

  class mod_search extends associationModule
  {
 function getNodes()
    {
      registerNode("search.search", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
     
    }
  	function getGgNodeName()
	{
		$res=array();
		$module="search";
	 $res[]= $module."."."search";
	 return $res;
	}


  }
  
?>