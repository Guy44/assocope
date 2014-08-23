<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class contact extends assMetaNode {
	var $table = "type_contact";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE | AF_UNIQUE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function contact() {
		$this->atkMetaNode();
		$this->atkNode("contact",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
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
			"Individus" => array (
				"contactant"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("contactant", "individu.contact_i", "id_type_contact", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>