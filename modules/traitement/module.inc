<?php

  class mod_traitement extends associationModule
  {
  	   function getNodes()
    {
            
      registerNode("traitement.trimestriel", array("admin", "intro", "adresse", "carte", "cotisation" ,"impressionenveloppe" ,"recu", "timbre",
       "impressioncomplement", "impressionrecufiscal", "miseajourenvois",  "adhesion", "export","import"));
  
    
    }
  
  	function getGgNodeName()
	{
		$res=array();
		$module="traitement";
	 $res[]= $module."."."trimestriel";
	 $res[]= $module."."."yaquelquun";

	 return $res;
	}
    function getMenuItems()
    {
  
   
     
    }
  }
  
?>