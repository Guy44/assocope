<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class requete_individu_observateur extends assMetaNode {
	var $table = "biodiversite_requete_individu_observateur";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function requete_individu_observateur() {
		$this->atkMetaNode();
		$this->atkNode("requete_individu_observateur",   NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_biodiversite_requete",
				"id_individu_observateur",
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
		$this->add(new atkManyToOneRelation("id_individu_observateur","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
		;
				$this->add(new atkBoolAttribute("exclure_o_n"));
				$this->setSecurityAlias("organisme.organisme");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
//		$this->setOrder(" individu_requete_individu_observateur.date_creation DESC ");
//		$this->setIndex("libelle");
	}
	function recordActions($rec, & $actions, & $mraactions) {

				$mraactions['delete'] = "delete";


			}

}
?>