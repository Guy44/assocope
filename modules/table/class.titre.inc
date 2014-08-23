<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgtextnomattribute");
class titre extends assMetaNode {
	var $table = "type_titre";

	function meta(& $policy) {
		$policy->addFlags("titre_long", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function titre() {
		$this->atkMetaNode();
		$this->atkNode("titre", NF_ADD_LINK| NF_ADDAFTERADD);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"titre_court",
				"titre_long",
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
		$this->add(new atgTextLibelleAttribute("titre_court", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atgTextNomAttribute("titre_long", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkOneToManyRelation("individu", "individu.individu", "id_titre", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("titre_long");
		$this->setOrder("titre_long");
	}
	function descriptor_def() {
		return "[titre_long]";
	}
}
?>