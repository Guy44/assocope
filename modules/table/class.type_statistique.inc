<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_statistique extends assMetaNode {
	var $table = "type_statistique";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_statistique() {
		$this->atkMetaNode();
		$this->atkNode("type_statistique",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA | NF_COPY);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
		"id_type_entite",
		"sql_an",
		"sql_mois",
		"url_module",
		"url_entite",
				"url_date_heure",
		"url_type",
		"lien_id_type",
						"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE),null,100);
		$this->add(new atkManyToOneRelation("id_type_entite", "table.type_entite", AF_SEARCHABLE | AF_RELATION_AUTOLINK),null,110);
		$this->add(new atkTextAttribute("sql_an",array ('rows' => '6'), AF_SEARCHABLE),null,120);
		$this->add(new atkTextAttribute("sql_mois",array ('rows' => '6'), AF_SEARCHABLE),null,130);
		$this->add(new atkTextAttribute("lien_id_type",array ('rows' => '2'), AF_SEARCHABLE),null,140);
		$this->add(new atkTextAttribute("url_module",array ('rows' => '2'), AF_SEARCHABLE),null,150);
		$this->add(new atkTextAttribute("url_entite",array ('rows' => '2'), AF_SEARCHABLE),null,155);
		$this->add(new atkTextAttribute("url_date_heure",array ('rows' => '2'), AF_SEARCHABLE),null,160);
		$this->add(new atkTextAttribute("url_type",array ('rows' => '2'), AF_SEARCHABLE),null,180);
		
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>