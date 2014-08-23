<?php

class mod_tournoi extends associationModule
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
		$module="tournoi";
	 $res[]= $module."."."tournoi";
	 $res[]= $module."."."individu_tournoi";
	 $res[]= $module."."."tournoi_rencontre";
	 $res[]= $module."."."tournoi_rencontre_match";
	 $res[]= $module."."."tournoi_equipe";
	 $res[]= $module."."."tournoi_rencontre_equipe";
	 $res[]= $module."."."tournoi_equipe_participant";

	 return $res;
	}
}


?>