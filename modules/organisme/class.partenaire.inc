<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class partenaire extends assMetaNode {
	var $table = "organisme_partenaire";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function partenaire() {
		$this->atkMetaNode();
		$this->atkNode("partenaire", NF_ADD_LINK  );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atgOManyToOneRelation("id_organisme_partenaire", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_interlocuteur", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" organisme_partenaire.date_creation DESC ");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
function id_interlocuteur_display($record, $mode) {
		(!empty($record["id_interlocuteur"])) ? $retour=$this->descripteur_individu($record["id_interlocuteur"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_partenaire_display($record, $mode) {
		(!empty($record["id_organisme_partenaire"])) ? $retour=$this->descripteur_organisme($record["id_organisme_partenaire"]["id"],'n') : $retour="";
		return $retour;
	}	
}
?>