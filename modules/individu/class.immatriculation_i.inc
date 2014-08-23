<?php
	atkimport("atk.assmetanode");
	useattrib("development.atgtextlibelleattribute");
class immatriculation_i extends assMetaNode
{
	var $table="individu_immatriculation";

function meta(&$policy)
  {

	$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

	$policy-> addFlags("commentaire",AF_HIDE_LIST);

}
function immatriculation_i()
{
  	$this->atkMetaNode();
  	$this->atkNode("immatriculation_i", NF_ADD_LINK);

	$this->setSecurityAlias("individu.individu");
 $this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),200);
 

	$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),400); 
	

	$this->add(new atkattribute("immatriculation"),300); 
	$this->add(new atkUrlAttribute("url",AF_POPUP),350);
/*$this->add(new atkfckattribute("commentaire","", AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'150px')),400); 
                 */
	include_once(atkconfig("atkroot")."modules/include/useronly.inc");
	include_once(atkconfig("atkroot")."modules/include/association.inc");	
 $this->setOrder("libelle");
	$this->setIndex("libelle");
  }
function descriptor_def()
  {
   return " [libelle] ";

  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
}

?>