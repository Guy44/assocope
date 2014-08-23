<?php
class type_symbole_gps extends assMetaNode {
	var $table = "type_symbole_gps";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_symbole_gps() {
		$this->atkMetaNode();
		$this->atkNode("type_symbole_gps", NF_COPY | NF_ADDAFTERADD|  NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"constructeur",
				"id_constructeur",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		//$this->add(new atkOneToManyRelation("symbole_gpss","gis.symbole_gps","id_type_symbole_gps",AF_HIDE_LIST),"symbole_gpss");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>