<?php
useattrib("development.atgtextnomattribute");
class maree_meteo extends assMetaNode {
	var $table = "type_maree_meteo";
	function meta(& $policy) {
		$policy->addFlags("lieu", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function maree_meteo() {
		$this->atkMetaNode();
		$this->atkNode("maree_meteo",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
			"lieu",
			"zone",
			"url_maree",
"url_meteo",
			"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextNomAttribute("lieu", AF_SEARCHABLE));
		$this->add(new atgTextNomAttribute("zone", AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_maree", AF_POPUP), AF_SEARCHABLE);
		$this->add(new atkUrlAttribute("url_meteo", AF_POPUP), AF_SEARCHABLE);
		$this->setSecurityAlias("gis.placemark");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("lieu");
		$this->setOrder("lieu");
	}
	function descriptor_def() {
		return "[zone] - [lieu]";
	}

}
?>