<?php
	atkimport("atk.assmetanode");

class competence_i extends assMetaNode
{
	var $table="individu_competence";

function meta(&$policy)
  {

	//$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	//$policy->setOrder("libelle");
}
function competence_i()
{
  	$this->atkMetaNode();
  	$this->atkNode("competence_i", NF_ADD_LINK);

	$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_type_competence","table.competence",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 

	include_once(atkconfig("atkroot")."modules/include/association.inc");	
	$this->setSecurityAlias("individu.individu");

	//$this->setIndex("libelle");
  }
function descriptor_def()
  {
    return "[id]";
  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}



}

?>