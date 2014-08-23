<?php
atkimport("atk.assmetanode");

useattrib("development.atgtextlibelleattribute");
class activite extends assMetaNode {
	var $table = "type_activite";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function activite() {
		$this->atkMetaNode();
		$this->atkNode("activite",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
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
				"individu"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkOneToManyRelation("individu", "individu.activite_i", "id_type_activite", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>