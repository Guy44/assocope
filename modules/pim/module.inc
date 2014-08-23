<?php
  $modifiers[] = "profil.userprefs";
  
  class mod_pim extends associationModule
  {
    function getNodes()
    {
    registerNode("pim.pim", array("admin", "add", "edit", "delete" ,"view" ,"lister", "view_all", "export","import"));
    registerNode("pim.userpimitems", array("admin", "add", "edit", "delete" ,"view" ,"lister", "view_all", "export","import"));
    }
    
    function getMenuItems()
    {
    }
  	function getGgNodeName()
	{
		$res=array();
		$module="pim";
	 $res[]= $module."."."pim";
	 $res[]= $module."."."userpimitems";

	 return $res;
	}
    
   /* function pdaNodes()
    {
      return array("pim"=>dispatch_url("pim.pim","pim"));
    }
    */
    function userprefs_modifier(&$node)
    {
      userelation("atkOneToManyRelation");

      $node->add(new atkOneToManyRelation("pimitems","pim.userpimitems","id_utilisateur",AF_FORCE_LOAD));
    }

  }
  
?>