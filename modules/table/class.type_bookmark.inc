<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");

class type_bookmark extends assMetaNode {
	var $table = "type_bookmark";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_bookmark() {
		$this->atkMetaNode();
		$this->atkNode("type_bookmark",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA );
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
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
		$this->add(new atkManyToOneTreeRelation("id_parent", "table.type_bookmark", AF_PARENT), NULL);
		//	$this->add(new atkBoolAttribute("actif", 0),NULL);		
		$this->add(new atkOneToManyRelation("individu", "individu.bookmark_i", "id_type_bookmark", AF_HIDE_LIST));
		$a = & $this->add(new atkOneToManyRelation("descendants", "table.type_bookmark", "id_parent", AF_HIDE_LIST | AF_CASCADE_DELETE), NULL, 1210);
		$a->setLabel("Sous catégories");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>