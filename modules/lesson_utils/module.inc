<?php
class mod_lesson_utils extends atkModule {
	function getNodes() {
		registerNode("lesson_utils.sourceviewer", array (
			"admin",
			"add",
			"edit",
			"delete",
			"view",
			"view_all",
			"grantall"
		));
	}
}
function getGgNodeName()
	{
		$res=array();
		$module="lesson_utils";
	 $res[]= $module."."."helpviewer";
	 $res[]= $module."."."sourceviewer";

	 return $res;
	}
	
function nodeSourceUrl($nodetype) {
	list ($module, $node) = explode(".", $nodetype);
	return href(dispatch_url("lesson_utils.sourceviewer", "view", array (
		"module" => $module,
		"node" => $node
	)), text('view_source'), SESSION_NEW, false, 'target="_blank"');
}
function moduleSourceUrl($module) {
	return dispatch_url("lesson_utils.sourceviewer", "view", array (
		"module" => $module
	));
}
function nodeHelpUrl($nodetype) {
	list ($module, $node) = explode(".", $nodetype);
	global $g_sessionManager;
	$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
	$db = & atkGetDb();
	$query = "SELECT id as id from app_aide 
	where module='" . $module . "' and node='" . $node . "' ";
	;
	$row = $db->getrows($query);
	if (count($row) > 0) {
		if ($administrateur == '0') {
			return href(dispatch_url("lesson_utils.helpviewer", "view", array (
				"module" => $module,
				"node" => $node
			)), text('view_help'), SESSION_NEW, false, 'target="_blank"');
		} else {
			return href(dispatch_url("application.aide", "edit", array (
				"atkselector" => "app_aide.id='" . $row[0]["id"] . "'",
				"node" => $node
			)), text('view_help'), SESSION_NEW, false, 'target="_blank"');
		}
	} else {
		if ($administrateur == '0') {
			return text('view_help');
		} else {
			return href(dispatch_url("application.aide", "add", array (
				"module" => $module,
				"node" => $node
			)), text('view_help'), SESSION_NEW, false, 'target="_blank"');
		}
	}
}
	function nodeDemandeUrl($nodetype) {
	list ($module, $node) = explode(".", $nodetype);

				return href(dispatch_url("application.demande", "add", array (
				"module" => $module,
				"node" => $node
			)), text('Demande'), SESSION_NEW, false, 'target="_blank"');
	
	}
	

?>
