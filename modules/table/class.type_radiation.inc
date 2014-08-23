<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_radiation extends assMetaNode {
	var $table = "type_radiation";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_radiation() {
		$this->atkMetaNode();
		$this->atkNode("type_radiation", NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
		$this->add(new atkRowCounter("#"), NULL, 1);
		$this->setExtendedSearchAction('smartsearch');
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
			"Individus" => array (
				"individu"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("individu", "individu.inscription_i", "id_type_radiation", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>