<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_rencontre_participation extends assMetaNode {
	var $table = "type_rencontre_participation";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_rencontre_participation() {
		$this->atkMetaNode();
		$this->atkNode("type_rencontre_participation",  NF_ADD_LINK | NF_ADDAFTERADD| NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>