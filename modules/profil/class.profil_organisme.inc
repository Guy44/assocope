<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
class profil_organisme extends assMetaNode {
	var $table = "app_profil_organisme";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function profil_organisme() {
		$this->atkMetaNode();
		$this->atkNode("profil_organisme", NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		/*
		 	$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
					"libelle",
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
			* 
		 */
		$this->setSecurityAlias("profil.profil");
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_profil", "profil.profil", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function descriptor_def() {
		return "";
	}
}
?>