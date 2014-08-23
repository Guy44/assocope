<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_etat_referencement extends assMetaNode {
	var $table = "type_etat_referencement";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_etat_referencement() {
		$this->atkMetaNode();
		$this->atkNode("type_etat_referencement",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
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
			"Référencements" => array (
				"etat_referencement"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("etat_referencement", "organisme.referencement", "id_type_etat_referencement", AF_HIDE_LIST), "referencement");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->addListener(atknew("atk.utils.atkeventlog"));
		$this->setOrder("libelle");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>