<?php
class point_coordinate extends assMetaNode {
	var $table = "gis_point_coordinate";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function point_coordinate() {
		$this->atkMetaNode();
		$this->atkNode("point_coordinate", NF_COPY | NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		$this->add(new atkManyToOneRelation("id_placemark", "gis.placemark", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE, 25, 5));
		$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE, 25, 5));
		$this->add(new atkNumberAttribute("altitude", AF_SEARCHABLE, 25, 0));
		$lonlat = & $this->add(new atkAttribute("lonlat", AF_SEARCHABLE | AF_READONLY));
		$lonlat->setForceUpdate(true);
		$this->setOrder("lonlat");
		$this->setSecurityAlias("gis.placemark");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function validate(& $record, $mode) {
		include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
		$record["lonlat"] = decimal2degree($record["longitude"], 'LON') . ' ' . decimal2degree($record["latitude"], 'LAT');
		parent :: validate($record, $mode);
	}

	function descriptor_def() {
		return "[lonlat]";
	}

}
?>