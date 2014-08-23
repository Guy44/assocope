<?php

class placemark_attribut extends assMetaNode {
	var $table = "gis_placemark_attribut";
	function meta(& $policy) {

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function placemark_attribut() {
		$this->atkMetaNode();
		$this->atkNode("placemark_attribut", NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);

		$this->add(new atkManyToOneRelation("id_placemark", "gis.placemark", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_type_attribut_placemark", "table.type_attribut_placemark", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkfckattribute("valeur", "", AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'150px')));

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setSecurityAlias("gis.placemark");

		//$this->setIndex("libelle");
	}
	function descriptor_def() {
		return "[type_attribut_placemark.libelle],' - ', [valeur]";
	}



}
?>