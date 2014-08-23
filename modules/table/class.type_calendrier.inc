<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_calendrier extends assMetaNode {
	var $table = "type_calendrier";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_calendrier() {
		$this->atkMetaNode();
		$this->atkNode("type_calendrier", NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"couleur_fond",
				"couleur_lettre",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		$this->add(new atkColorPickerAttribute("couleur_fond", "", AF_OBLIGATORY | AF_HIDE_LIST | AF_FORCE_LOAD | AF_POPUP));
		$this->add(new atkColorPickerAttribute("couleur_lettre", "", AF_OBLIGATORY | AF_HIDE_LIST | AF_FORCE_LOAD | AF_FORCE_LOAD | AF_POPUP));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>