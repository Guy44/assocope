<?php
	atkimport("atk.assmetanode");

class competence_o extends assMetaNode
{
	var $table="organisme_competence";

function meta(&$policy)
  {

	//$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	//$policy->setOrder("libelle");
}
function competence_o()
{
  	$this->atkMetaNode();
  	$this->atkNode("competence_o", NF_ADD_LINK |NF_ADDAFTERADD);

	$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_type_competence_organisme","table.type_competence_organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 

	include_once(atkconfig("atkroot")."modules/include/association.inc");	
	$this->setSecurityAlias("organisme.organisme");

	//$this->setIndex("libelle");
  }
function descriptor_def()
  {
    return "[id]";
  }

function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

}

?>