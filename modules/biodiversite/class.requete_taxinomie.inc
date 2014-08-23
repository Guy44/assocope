<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class requete_taxinomie extends assMetaNode {
	var $table = "biodiversite_requete_taxinomie";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function requete_taxinomie() {
		$this->atkMetaNode();
		$this->atkNode("requete_taxinomie",   NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_biodiversite_requete",
				"id_taxinomie",
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
//		$this->add(new atkManyToOneRelation("id_taxinomie","biodiversite.taxinomie",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
//		;
						$ordre = & $this->add(new atkManyToOneRelation("id_taxinomie","biodiversite.taxinomie",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
				$ordre->addDestinationFilter("biodiversite_taxinomie.id_rang_taxinomique in ( select distinct id from biodiversite_rang_taxinomique where rang_inpn='OR' )");
		
				
				$this->add(new atkBoolAttribute("exclure_o_n"));
				$this->setSecurityAlias("organisme.organisme");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
//		$this->setOrder(" organisme_requete_taxinomie.date_creation DESC ");
//		$this->setIndex("libelle");
	}
	function preAdd(& $record) {

		$id_requete = $record['id_biodiversite_requete']["id"];
		$exclure_o_n = $record['exclure_o_n'];
		$table = "biodiversite_requete_taxinomie";
		$nombre=$this-> controle_requete_biodiversite_exclure_o_n ($table,$id_requete,  $exclure_o_n);
		if ($nombre > 0) {
			triggerError($record, "", "Pas de mélange inclure/exclure");
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$id_requete =$record['id_biodiversite_requete']["id"];
		$exclure_o_n = $record['exclure_o_n'];
		$table = "biodiversite_requete_taxinomie";
		$nombre=$this-> controle_requete_biodiversite_exclure_o_n ($table,$id_requete,  $exclure_o_n);
		if ($nombre > 1) {
			triggerError($record, "", "Pas de mélange inclure/exclure");
		}
		parent :: preUpdate($record);
	}

}
?>