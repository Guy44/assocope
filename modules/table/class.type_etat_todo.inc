<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_etat_todo extends assMetaNode {
	var $table = "type_etat_todo";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_etat_todo() {
		$this->atkMetaNode();
		$this->atkNode("type_etat_todo", NF_ADD_LINK| NF_ADDAFTERADD | NF_MRA);
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
			"Todos" => array (
				"todo"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("todo", "todo.todo", "id_type_etat_todo", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>