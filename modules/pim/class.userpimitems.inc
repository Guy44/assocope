<?php
useattrib("pim.pimitemattribute");
class userpimitems  extends assMetaNode
{
	var $table="app_pimitem";
function meta(&$policy)
  {

	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
  }
  function userpimitems()
  {
	$this->atkMetaNode();
  	$this->atkNode("userpimitems", NF_EXPORT|NF_IMPORT|NF_ADD_LINK|NF_TRACK_CHANGES);
    $this->add(new atkNumberAttribute("id",AF_AUTOKEY));
    $this->add(new atkManyToOneRelation("id_utilisateur","profil.utilisateur",AF_HIDE));
    $this->add(new pimItemAttribute("pimitem",AF_OBLIGATORY|AF_NO_TRANSLATION));
    $this->add(new atkDummyAttribute("pim_orderby_help",atktext("pim_orderby_help"),AF_BLANK_LABEL|AF_HIDE_LIST));
    $this->add(new atkNumberAttribute("ordre"));
     $this->add(new atkManyToOneRelation("id_creation","profil.utilisateur",AF_READONLY)); 
	$this->add(new atkDateAttribute("date_creation","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING|AF_READONLY));
	$id_modification=&$this->add(new atkManyToOneRelation("id_modification","profil.utilisateur",AF_READONLY)); 
	$id_modification->setForceUpdate(true);
	$date_modification=&$this->add(new atkDateAttribute("date_modification","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING|AF_READONLY));
	$date_modification->setForceUpdate(true);
	//$this->add(new atkRowCounter("#"),NULL,1);
	$this->setExtendedSearchAction('smartsearch');
	$this->addListener(atknew("atk.utils.atkeventlog"));
    $this->setOrder("ordre");
    $this->setTable("app_pimitem");
    $this->setDescriptorTemplate("[pimitem]");
  }

  /**
   * Return the attributes that are used when determining a descriptor.
   * @return array The names of the attributes forming the descriptor.
   */
  function descriptor_fields()
  {
    return array("pimitem");
  }

  /**
   * Determine a descriptor of a record.
   *
   * @param array $record Array containing the record for which a descriptor should be made
   * @return string Descriptor string
   */
  function descriptor(&$record)
  {
    $pimitemattr = &$this->getAttribute("pimitem");
    return $pimitemattr->display($record);
  }
}

?>