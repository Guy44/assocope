<?php
class helpviewer extends atkNode {
	function helpviewer() {
		$this->atkNode("helpviewer");
		$this->setSecurityAlias("individu.individu");
	}
	function action_view() {
		global $g_sessionManager;
		$module = $g_sessionManager->pageVar("module");
		$node = $g_sessionManager->pageVar("node");
		$lng = atkLanguage::getLanguage();
		$lng = strtolower($lng);
		$db = & atkGetDb();
		$query = "SELECT texte_tt as description from app_traduction 
	where  id_type_traduction='6' and nom_noeud='".$node."' and nom_module='".$module."' and id_type_langue in (select id from type_langue where code_iso_639_1='".$lng."')";
//		print_r($query);
//		die();
		
		$row = $db->getrows($query);
				if (atkLevel() > 0) {
//			$content = '<br><br>' . atkButton(text("back"), "", SESSION_BACK, false);
		}
		$content = '<div align="left" style="font-size: 8pt">';
		$content .= '<br>Aide de <b>' . $module . ' ' . $node . '</b>:<br><br>';
//		$content .=htmlentities($row[0]["description"]) . '</div>';
		$content .=$row[0]["description"]. '</div>';
		if (atkLevel() > 0) {
			$content .= '<br><br>' . atkButton(text("back"), "", SESSION_BACK, false);
		}
		$ui = & $this->getUi();
		$output = $ui->renderBox(array (
			"title" => text("view_help"
		), "content" => $content));
		$actionpage = $this->renderActionPage("view", $output);
		$page = & $this->getPage();
		$theme = & atkTheme :: getInstance();
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent($actionpage);
	}
}
?>