<?php
atkimport("atk.assmetanode");
userelation("atkmanytoonerelation");
useattrib("atkdateattribute");
useattrib("atkemailattribute");
userelation("atkonetomanyrelation");
useattrib("atknumberattribute");
useattrib("atkrowcounter");
useattrib("atkfckattribute");

class placemark extends assMetaNode {
	var $table = "gis_placemark";
	var $m_count = 0;
	function countDb($selector = "", $excludeList = "", $includeList = "", $mode = "") {
		$this->m_count = parent :: countDb($selector, $excludeList, $includeList, $mode);
		return $this->m_count;
	}

	function meta(& $policy) {

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("libelle", "etiquette", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	}
	function placemark() {
		$this->atkMetaNode();
		$this->atkNode("placemark", NF_COPY | NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);

		$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE, 25, 15));
		$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE, 25, 15));
		$this->add(new atkNumberAttribute("altitude", AF_SEARCHABLE, 25, 15));

		$this->add(new atkfckattribute("description", "", AF_HIDE_LIST), "html");

		$this->add(new atkManyToOneRelation("id_zone_region_pays", "table.type_zone_region_pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		$this->add(new atkManyToOneRelation("id_type_placemark", "table.type_placemark", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		$this->add(new atkOneToManyRelation("attribut", "gis.placemark_attribut", "id_placemark", AF_HIDE_LIST));
		$this->setOrder("latitude desc");
		include_once ($config_atkroot . "modules/include/association.inc");
	}
	function adminFooter() {
		return "Nombre de lignes : " . $this->m_count . " <br>  " . nodeSourceUrl("gis.placemark");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>