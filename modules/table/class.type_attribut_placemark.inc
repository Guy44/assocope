<?php
useattrib("development.atgtextlibelleattribute");
class type_attribut_placemark extends assMetaNode {
	var $table = "type_attribut_placemark";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_attribut_placemark() {
		$this->atkMetaNode();
		$this->atkNode("type_attribut_placemark", NF_COPY| NF_ADDAFTERADD  | NF_ADD_LINK  | NF_MRA);
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
			)
		), AF_NO_LABEL));
		//$this->add(new atkOneToManyRelation("attribut_placemarks","gis.attribut_placemark","id_type_attribut_placemark",AF_HIDE_LIST),"attribut_placemarks");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>