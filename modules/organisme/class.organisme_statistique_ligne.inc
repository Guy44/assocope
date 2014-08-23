<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class organisme_statistique_ligne extends assMetaNode {
	var $table = "organisme_statistique_ligne";
	function meta(& $policy) {

		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function organisme_statistique_ligne() {
		$this->atkMetaNode();
		$this->atkNode("organisme_statistique_ligne",  NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_organisme_statistique",
				"id_type",
		"an",
		"mois",
		"nombre",
						"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));

		$this->add(new atkManyToOneRelation("id_organisme_statistique", "organisme.organisme_statistique", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
		$this->add(new atkAttribute("id_type"));
		$this->add(new atkAttribute("an"));
		$this->add(new atkAttribute("mois"));
		$this->add(new atkAttribute("nombre"));		
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("date_modification desc");
	}


}
?>