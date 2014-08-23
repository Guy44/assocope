<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_menu extends assMetaNode {
	var $table = "type_menu";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_menu() {
		$this->atkMetaNode();
		$this->atkNode("type_menu",NF_ADD_LINK| NF_ADDAFTERADD| NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Menus" => array (
				"menu"
			)
		), AF_NO_LABEL));
		$this->add(new atkAttribute("id"));
		$this->add(new atkOneToManyRelation("menu", "menu.menu", "id_type_menu", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>