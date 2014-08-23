<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class requete_organisme_commanditaire extends assMetaNode {
	var $table = "biodiversite_requete_organisme_commanditaire";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function requete_organisme_commanditaire() {
		$this->atkMetaNode();
		$this->atkNode("requete_organisme_commanditaire",   NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_biodiversite_requete",
				"id_organisme_commanditaire",
				"exclure_o_n",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_biodiversite_requete","biodiversite.requete",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
				;
				$this->add(new atkManyToOneRelation("id_organisme_commanditaire","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
				;
				$this->add(new atkBoolAttribute("exclure_o_n"));
				$this->setSecurityAlias("organisme.organisme");
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				//		$this->setOrder(" organisme_requete_organisme_commanditaire.date_creation DESC ");
				//		$this->setIndex("libelle");
	}
	function recordActions($rec, & $actions, & $mraactions) {

		$mraactions['delete'] = "delete";


	}
	function preAdd(& $record) {

		$id_requete = $record['id_biodiversite_requete']["id"];
		$exclure_o_n = $record['exclure_o_n'];
		$table = "biodiversite_requete_organisme_commanditaire";
		$nombre=$this-> controle_requete_biodiversite_exclure_o_n ($table,$id_requete,  $exclure_o_n);
		if ($nombre > 0) {
			triggerError($record, "", "Pas de mélange inclure/exclure");
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$id_requete =$record['id_biodiversite_requete']["id"];
		$exclure_o_n = $record['exclure_o_n'];
		$table = "biodiversite_requete_organisme_commanditaire";
		$nombre=$this-> controle_requete_biodiversite_exclure_o_n ($table,$id_requete,  $exclure_o_n);
		if ($nombre > 1) {
			triggerError($record, "", "Pas de mélange inclure/exclure");
		}
		parent :: preUpdate($record);
	}

}
?>