<?php
atkimport("atk.assmetanode");
class mysql_table extends assMetaNode {
	var $table = "xxxxxxx";
	function meta(& $policy) {
//		$policy->addFlags("libelle", AF_SEARCHABLE);
//		$policy->addFlags("commentaire", AF_HIDE_LIST);
//		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	}
	function mysql_table() {
		global $ATK_VARS,$g_user;
		$this->table=$ATK_VARS["mysql_table"];
		$this->atkMetaNode();
		$this->atkNode("mysql_table",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("individu.individu");
//		$this->p($this->getAttributeNames());

	/*	$this->add(new atkTabbedPane("Pane1", array (
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
		*/
//		include_once (atkconfig("atkroot") . "modules/include/association.inc");
//		$this->setIndex("libelle");
//		$this->setOrder("libelle");
	}
/*	function descriptor_def() {
		return "[libelle]";
	}
	*/

}
?>