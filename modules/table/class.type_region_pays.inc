<?php
useattrib("development.atgtextnomattribute");
class type_region_pays extends assMetaNode {
	var $table = "type_region_pays";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_region_pays() {
		$this->atkMetaNode();
		$this->atkNode("type_region_pays",  NF_ADD_LINK| NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextNomAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_pays",
"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Zones" => array (
				"zone"
			)
		), AF_NO_LABEL));
		$this->add(new atkManyToOneRelation("id_pays", "table.pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkOneToManyRelation("zone", "table.type_zone_region_pays", "id_region_pays", AF_HIDE_LIST));
					$this->addUniqueFieldset(array("id_pays","libelle"));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>