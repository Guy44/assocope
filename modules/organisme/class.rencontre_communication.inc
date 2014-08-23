<?php
	atkimport("atk.assmetanode");
	userelation ("atkmanytoonerelation");
	useattrib("atkdateattribute");
	useattrib("atkrowcounter");
	 	useattrib("atkparserattribute");




class rencontre_communication extends assMetaNode
{
	var $table="organisme_rencontre_communication";
function meta(&$policy)
  {
	$policy-> addFlags("commentaire","description",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	
	$policy->setOrder("id_rencontre");
}
function rencontre_communication()
{
  	$this->atkMetaNode();
  	$this->atkNode("rencontre_communication", NF_ADD_LINK);
	$this->setSecurityAlias("organisme.organisme");

	$this->add(new atkManyToOneRelation("id_organisme_communication","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
		$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_rencontre","organisme.rencontre",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 
	$this->add(new atkDateAttribute("date_communication","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_passage","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING));
	include_once(atkconfig("atkroot")."modules/include/association.inc");	
	  }
function descriptor_def()
  {
    return "[id_rencontre]";
  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_communication_display($record, $mode) {
		(!empty($record["id_organisme_communication"])) ? $retour=$this->descripteur_organisme($record["id_organisme_communication"]["id"],'n') : $retour="";
		return $retour;
	}

}

?>