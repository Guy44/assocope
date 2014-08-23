<?php

useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");
class placemark extends assMetaNode {
	var $table = "gis_placemark";
	function meta(& $policy) {

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("libelle", "etiquette", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	}
	function placemark() {
		$this->atkMetaNode();
		$this->atkNode("placemark", NF_COPY | NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		$this->add(new atgTextNomAttribute("libelle", AF_SEARCHABLE),100);
		$this->add(new atgTextNomAttribute("etiquette", AF_SEARCHABLE),110);

		$this->add(new atkfckattribute("description","", AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'150px')));

		$this->add(new atkManyToOneRelation("id_zone_region_pays", "table.type_zone_region_pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),120);
		$this->add(new atkManyToOneRelation("id_type_placemark", "table.type_placemark", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),105);
		$this->add(new atkManyToOneRelation("id_maree_meteo", "table.maree_meteo", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_HIDE_LIST|AF_RELATION_AUTOCOMPLETE),130);
  		$this->add(new atgFileManyToOneRelation("id_photo", "individu.document_i", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_HIDE_LIST|AF_RELATION_AUTOCOMPLETE),132);
		$this->add(new atkRadioAttribute("geometry", array (
			"Point",
			"LineString",
			"Polygon"
		), array (
			"Point",
			"LineString",
			"Polygon"
		), AF_OBLIGATORY | AF_HIDE_LIST),133);
		     $this->add(new atkBoolAttribute("extrude", AF_OBLIGATORY | AF_HIDE_LIST),134);
		     $this->add(new atkBoolAttribute("tesselate", AF_OBLIGATORY | AF_HIDE_LIST),135);

							$this->add(new atkRadioAttribute("altitudemode", array (
			"clampToGround",
			"relativeToGround",
			"absolute"
		), array (
			"clampToGround",
			"relativeToGround",
			"absolute"
		), AF_OBLIGATORY | AF_HIDE_LIST),136);
		$this->add(new atkOneToManyRelation("Point", "gis.point_coordinate", "id_placemark"),140);
		$this->add(new atkOneToManyRelation("Ligne", "gis.ligne_coordinate", "id_placemark"),142);
		$rel=$this->add(new atkOneToManyRelation("attribut", "gis.placemark_attribut", "id_placemark"),150);

		$this->setOrder("libelle");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}

  

	function descriptor_def() {
		return "[libelle]";
	}

}
?>