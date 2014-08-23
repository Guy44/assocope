<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_demande extends assMetaNode {
	var $table = "type_demande";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_demande() {
		$this->atkMetaNode();
		$this->atkNode("type_demande",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
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
			"Demandes" => array (
				"demande"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("demande", "application.demande", "id_type_demande", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>