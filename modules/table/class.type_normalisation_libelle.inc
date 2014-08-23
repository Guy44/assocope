<?php
atkimport("atk.assmetanode");
class type_normalisation_libelle extends assMetaNode {
	var $table = "type_normalisation_libelle";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_normalisation_libelle() {
		$this->atkMetaNode();
		$this->atkNode("type_normalisation_libelle", NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function validate(& $record, $mode) {
		$record["libelle"] = trim($record["libelle"]);
		$record["libelle"] = strtolower($record["libelle"]);
		parent :: validate($record, $mode);
	}
	//
	function descriptor_def() {
		return "[libelle]";
	}

}
?>