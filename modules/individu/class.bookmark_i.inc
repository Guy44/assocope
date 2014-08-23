<?php
	atkimport("atk.assmetanode");
		useattrib("development.atgtextlibelleattribute");
	
class bookmark_i extends assMetaNode
{
	var $table="individu_bookmark";

function meta(&$policy)
  {

	$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		$policy->addFlags("nombre_acces", AF_READONLY);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);

}
function bookmark_i()
{
  	$this->atkMetaNode();
  	$this->atkNode("bookmark_i",NF_ADD_LINK | NF_EDITAFTERCOPY |NF_ADDAFTERADD);
  	$this->add(new atkattribute("nombre_acces",AF_READONLY),45); 
$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE|AF_OBLIGATORY),50);

	$this->setSecurityAlias("individu.individu");

	$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),150); 

				$a = &$this->add(new atkManyToOneTreeRelation("id_type_bookmark","table.type_bookmark", AF_RELATION_AUTOLINK|AF_SEARCHABLE|AF_FORCE_LOAD|AF_OBLIGATORY),NULL,351);
               $a->setLabel("Catégorie");
	
//	$this->add(new atkattribute("libelle"),AF_SEARCHABLE,200); 
	
	$this->add(new atkUrlAttribute("url",AF_POPUP|AF_SEARCHABLE |AF_OBLIGATORY),55);
		$this->add(new atkattribute("tags"),AF_SEARCHABLE,352); 
	$this->add(new atkBoolAttribute("actif", AF_OBLIGATORY),NULL,355);
$this->add(new atkfckattribute("commentaire","", AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'150px')),400); 
			global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
	
	if ($administrateur==0)
	{include_once(atkconfig("atkroot")."modules/include/useronly.inc");}
	include_once(atkconfig("atkroot")."modules/include/association.inc");
	$this->setOrder("libelle");
//	$this->setIndex("libelle");
  }
function descriptor_def()
  {
    return " [libelle] ";
  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	
	function preAdd(& $record) {
		$record["nombre_acces"]=0;
	parent :: preAdd($record);
	}


}

?>