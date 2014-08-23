<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgFileManyToOneRelation");
class document_officiel extends assMetaNode {
	var $table = "organisme_document_officiel";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function document_officiel() {
		$this->atkMetaNode();
		$this->atkNode("document_officiel",  NF_ADD_LINK );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atgFileManyToOneRelation("id_document", "organisme.document", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkDateAttribute("date_depot", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" date_depot DESC ");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>