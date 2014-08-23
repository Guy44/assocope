<?php
	atkimport("atk.assmetanode");
	useattrib("development.atgtextlibelleattribute");
class profil extends assMetaNode
{
var $table="app_profil";

function meta(&$policy)
  {
$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

	$policy-> addFlags("commentaire",AF_HIDE_LIST);
$policy->setOrder("libelle");

  }
function profil()
{
$this->atkMetaNode();
$this->atkNode("profil",  NF_COPY|NF_EXPORT|NF_IMPORT|NF_ADD_LINK|NF_EDITAFTERADD|NF_NO_VIEW|NF_TRACK_CHANGES|NF_MRA); 
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"acces_public_seulement",
				"administrateur_general_o_n",
		"traitements_o_n",
				"organismes_autorises",
				"profil_droit_acces",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Utilisateurs" => array (
				"utilisateur"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),100);
		$this->add(new atkBoolAttribute("acces_public_seulement"),150);
		$this->add(new atkBoolAttribute("administrateur_general_o_n"),151);
				$this->add(new atkBoolAttribute("traitements_o_n"),152);
		$this->add(new atkOneToManyRelation("organismes_autorises", "profil.profil_organisme", "id_profil", AF_HIDE_LIST),200);
	 		$this->add(new atkOneToManyRelation("utilisateur", "profil.utilisateur", "id", AF_HIDE_LIST));
	
	 
$this->add(new atkProfileAttribute("profil_droit_acces",AF_HIDE_LIST|AF_HIDE_ADD|AF_BLANKLABEL),250);
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