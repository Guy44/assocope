<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_liste extends assMetaNode {
	var $table = "type_liste";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_liste() {
		$this->atkMetaNode();
		$this->atkNode("type_liste",NF_ADD_LINK| NF_ADDAFTERADD | NF_MRA);
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
			),
			"Listes" => array (
				"liste"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("liste", "profil.liste", "id_liste", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>