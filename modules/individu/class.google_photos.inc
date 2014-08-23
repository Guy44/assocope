<?php
	atkimport("atk.assmetanode");

class google_photos extends assMetaNode
{
	var $table="individu_google_photo";

function meta(&$policy)
  {

	//$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	//$policy->setOrder("libelle");
}
function google_photos()
{
  	$this->atkMetaNode();
  	$this->atkNode("google_photos",  NF_ADD_LINK  | NF_MRA);
 
$this->add(new atkDummyAttribute("descripteur_photo"),NULL,10);
	$this->add(new atkManyToOneRelation("id_album","individu.google_feed",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOCOMPLETE),15); 
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),20 );
	$this->add(new atkUrlAttribute("url_thumbnail", AF_POPUP),10110);
	$this->add(new atkUrlAttribute("url_image", AF_POPUP),10120);
	$this->add(new atkAttribute("titre", AF_SEARCHABLE ,200),10130);
	$this->add(new atkAttribute("date_prise_de_vue", AF_SEARCHABLE ),10140);
	$this->add(new atkAttribute("geo_rss", AF_SEARCHABLE ,200),10150);
	$this->add(new atkAttribute("date_synchronisation_google", AF_SEARCHABLE ),10160);
	$this->add(new atkCurrencyAttribute("size",  AF_SEARCHABLE|AF_TOTAL , 10,"", 0,",","."),10170);
	$this->add(new atkAttribute("heigth", AF_SEARCHABLE ),10180);
	$this->add(new atkAttribute("width", AF_SEARCHABLE ),10190);
	$this->add(new atkAttribute("tags", AF_SEARCHABLE ),10200);

	include_once(atkconfig("atkroot")."modules/include/association.inc");

$this->setSecurityAlias("individu.individu");

  }
  function descripteur_photo_display($record,$mode)
  {
  	return $this->descripteur_google_photo($record["id"], 'o');
  }
function id_album_display($record, $mode)
	{
		return $this->descripteur_google_feed_album($record["id_album"]["id"],'o');
	}

function descriptor_def()
  {
    return "[id]";
  }


}
?>