<?php

class mod_gis extends associationModule
{
	function getNodes()
	{
		registerNode("gis.placemark", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall","lister", "export", "import"));
		registerNode("table.type_zone_region_pays", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall","lister", "export_kml", "import_kml"));
	}
	function getMenuItems()
	{
	}
	function getGgNodeName()
	{
		$res=array();
		$module="gis";
	 $res[]= $module."."."icone";
	 $res[]= $module."."."ligne_coordinate";
	 $res[]= $module."."."placemark";
	 $res[]= $module."."."placemark_attribut";
	 $res[]= $module."."."point_coordinate";

	 return $res;
	}
}


?>