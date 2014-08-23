<?php
useattrib("atktextattribute");
$this->add($commentaire = new atkTextAttribute("commentaire", array (

	'rows' => '2'
), AF_HIDE_LIST | AF_FORCE_LOAD),10000);
$this->add(new atkAttribute("id_creation",  AF_READONLY| AF_HIDE_ADD| AF_HIDE_VIEW | AF_HIDE_EDIT| AF_FORCE_LOAD),null,10110 );
// $this->add(new atkManyToOneRelation("id_creation", "profil.utilisateur", AF_SEARCHABLE | AF_READONLY| AF_HIDE_ADD| AF_HIDE_VIEW | AF_HIDE_EDIT| AF_FORCE_LOAD),null,10110 );
$this->add(new atkDateTimeAttribute("date_creation", "Y-m-d", "hh:mm:ss",  AF_DATE_STRING | AF_READONLY| AF_HIDE_VIEW| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD),null,10120 );
//$id_modification = & $this->add(new atkManyToOneRelation("id_modification", "profil.utilisateur", AF_SEARCHABLE | AF_READONLY| AF_HIDE_VIEW| AF_HIDE_ADD | AF_HIDE_EDIT | AF_FORCE_LOAD),null,10130 );
$id_modification = & $this->add(new atkAttribute("id_modification",  AF_READONLY| AF_HIDE_ADD| AF_HIDE_VIEW | AF_HIDE_EDIT| AF_FORCE_LOAD),null,10110 );
$id_modification->setForceUpdate(true);
$date_modification = & $this->add(new atkDateTimeAttribute("date_modification", "Y-m-d", "hh:mm:ss",  AF_DATE_STRING | AF_HIDE_VIEW|AF_READONLY| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD),null,10140 );
$date_modification->setForceUpdate(true);
// $this->add(new atkNumberAttribute("id", AF_PRIMARY | AF_HIDE | AF_FORCE_LOAD));
$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT | AF_HIDE_EDIT  | AF_NO_LABEL),null,10100 );
$this->add(new atkRowCounter("#", AF_COMPACT), NULL, 1);
$this->setExtendedSearchAction('smartsearch');
$this->addListener(atknew("atk.utils.atkeventlog"));
		include_once (atkconfig("atkroot") . "modules/include/actions.inc");
?>
