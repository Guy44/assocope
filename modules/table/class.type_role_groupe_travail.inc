<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_role_groupe_travail extends assMetaNode {
	var $table = "type_role_groupe_travail";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_role_groupe_travail() {
		$this->atkMetaNode();
		$this->atkNode("type_role_groupe_travail",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>