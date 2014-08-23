<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_remise_banque extends assMetaNode {
	var $table = "type_remise_banque";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_remise_banque() {
		$this->atkMetaNode();
		$this->atkNode("type_remise_banque",  NF_ADD_LINK| NF_ADDAFTERADD );
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
	//	$this->add(new atkOneToManyRelation("ecritures", "organisme.ecriture_comptable", "id_type_remise_banque", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>