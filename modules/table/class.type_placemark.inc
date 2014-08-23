<?php
useattrib("development.atgtextlibelleattribute");
class type_placemark extends assMetaNode {
	var $table = "type_placemark";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_placemark() {
		$this->atkMetaNode();
		$this->atkNode("type_placemark", NF_COPY| NF_ADDAFTERADD  | NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"id_icone",
				"id_seconde_icone",
				"id_symbole_gps",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Repères" => array (
				"placemarks"
			)
		), AF_NO_LABEL));
		$this->add(new atkManyToOneRelation("id_icone", "gis.icone", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_seconde_icone", "gis.icone", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_symbole_gps", "table.type_symbole_gps", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkOneToManyRelation("placemarks", "gis.placemark", "id_type_placemark", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>