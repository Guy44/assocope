<?php
	atkimport("atk.assmetanode");
	userelation ("atkmanytoonerelation");
	userelation ("atkonetomanyrelation");
	useattrib("atkdateattribute");

	  	useattrib("atkboolattribute");

class menu_item  extends assMetaNode
{
	var $table="menu_item";


function meta(&$policy)
  {

	$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

//	$policy->setOrder("libelle");
}
function menu_item()
{
  	$this->atkMetaNode();
  	$this->atkNode("menu_item", NF_COPY|NF_EXPORT|NF_IMPORT|NF_ADD_LINK|NF_TRACK_CHANGES|NF_MRA);  
	$this->setSecurityAlias("menu.menu");
  $this->add(new atkBoolAttribute("atk_id"));
  $this->add(new atkBoolAttribute("atk_doctpl_prefix_id"));
  	$this->add(new atkTextAttribute("atk_filter",array('autoadjust'=>'yes','rows'=>'2'),AF_HIDE_LIST)); 
	$this->add(new atkTextAttribute("atk_search",array('autoadjust'=>'yes','rows'=>'2'),AF_HIDE_LIST)); 
  
	$this->add(new atkManyToOneRelation("id_menu","menu.menu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK));
	include_once(atkconfig("atkroot")."modules/include/association.inc");	
	$this->setIndex("libelle");
	$this->setOrder("libelle");
  }
function descriptor_def()
  {
    return "[libelle]";
  }


}

?>