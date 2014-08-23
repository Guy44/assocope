<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class journal_comptable extends assMetaNode {
	var $table = "organisme_journal_comptable";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->setOrder("libelle");
	}
	function journal_comptable() {
		$this->atkMetaNode();
		$this->atkNode("journal_comptable", NF_ADD_LINK | NF_COMPACT );
	$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
					"descripteur_journal",
				"libelle",
					"id_organisme",
				"id_compte_banque",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Ecritures" => array (
				"ecritures"
			),
						"Lignes" => array (
				"lignes"
			)
		), AF_NO_LABEL));
		
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkDummyAttribute("descripteur_journal","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_COMPACT),NULL,10);


		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_compte_banque", "organisme.compte", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkOneToManyRelation("ecritures", "organisme.ecriture_comptable", "id_journal", AF_HIDE_LIST));
		$this->add(new atkOneToManyRelation("lignes", "organisme.ligne_ecriture_comptable", "id_journal", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,55 );
		$an_exercice=$this->m_postvars["an_exercice_comptable"];
		if (!isset($an_exercice)) 
		{$ancours=gmdate('Y');}
	
	

		
	}
					function rowColor($record) {

		if ($record["debit"]!=$record["credit"]
		|| $record["debit_1"]!=$record["credit_1"]
			|| $record["debit_2"]!=$record["credit_2"] )
		{	return $this->couleurrouge;}
	}	
	function descriptor_def() {
		return "[libelle]";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function descripteur_journal_display($record, $mode) {
		return $this->descripteur_journal_comptable($record["id"],'o', 'o');
	}
}
?>