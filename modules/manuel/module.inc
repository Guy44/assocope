<?php

  class mod_manuel extends associationModule
  {
    function getNodes()
    {
      registerNode("manuel.manuel", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall","export","import"));
     
    }
  function getGgNodeName()
	{
		$res=array();
		$module="manuel";
	 $res[]= $module."."."manuel";
	 return $res;
	}

  
}


?>