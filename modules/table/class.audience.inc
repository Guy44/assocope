<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class audience extends assMetaNode {
	var $table = "type_audience";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function audience() {
		$this->atkMetaNode();
		$this->atkNode("audience",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Rencontres" => array (
				"rencontres"
			),
			"Gazettes" => array (
				"gazettes"
			),
			"Infolettres" => array (
				"infolettres"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkOneToManyRelation("rencontres", "organisme.rencontre", "id_type_audience", AF_HIDE_LIST));
		$this->add(new atkOneToManyRelation("gazettes", "organisme.gazette", "id_type_audience", AF_HIDE_LIST));
		$this->add(new atkOneToManyRelation("infolettres", "organisme.infolettre", "id_type_audience", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>