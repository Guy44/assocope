<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_frequence extends assMetaNode {
	var $table = "type_frequence";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_frequence() {
		$this->atkMetaNode();
		$this->atkNode("type_frequence",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
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