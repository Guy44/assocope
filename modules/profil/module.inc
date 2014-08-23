<?php
class mod_profil extends associationModule {
	function getNodes() {
		registerNode("profil.profil", array (
			"admin",
			"add",
			"edit",
			"delete",
			"view",
			"view_all",
			"grantall",
			"export",
			"import"
		));
		registerNode("profil.userprefs", array (
			"edit"
		));
		/*
		registerNode("profil.utilisateur", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		registerNode("profil.log", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		
		
		*/
	}
	function getGgNodeName()
	{
		$res=array();
		$module="profil";
	 $res[]= $module."."."copier_coller";
	 $res[]= $module."."."liste";
	 	 $res[]= $module."."."liste_organismes";
	 $res[]= $module."."."log";
	 $res[]= $module."."."profil";
	 $res[]= $module."."."profil_organisme";
	 $res[]= $module."."."recent_use";
	 $res[]= $module."."."userprefs";
	 $res[]= $module."."."utilisateur";
	 $res[]= $module."."."debug";
	 return $res;
	}
	
	function getMenuItems() {
	}
}
?>