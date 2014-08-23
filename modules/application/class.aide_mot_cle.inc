<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class aide_mot_cle extends assMetaNode {
	var $table = "app_aide_mot_cle";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function aide_mot_cle() {
		$this->atkMetaNode();
		$this->atkNode("aide_mot_cle", NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		$this->setSecurityAlias("application.aide");
		$this->add(new atgTextLibelleAttribute("mot", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"mot",
				"id_aide",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		$this->add(new atkManyToOneRelation("id_aide", "application.aide", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE), 300);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("mot");
		$this->setOrder("mot");
	}
	function descriptor_def() {
		return "[mot]";
	}

}
?>