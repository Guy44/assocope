<?php

class mod_individu extends associationModule
{
	function getNodes()
	{
		registerNode("individu.individu", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall","lister", "export", "import"));
		registerNode("v_individu_lieu", array("admin", "document", "add", "edit", "delete" ,"view" ,"view_all", "grantall","lister", "export", "import"));

		/*
		 registerNode("individu.lieu", array("admin", "add", "edit", "delete" ,"view","view_all", "grantall"));
		 registerNode("individu.individu_lieu", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.individu_liste", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.liste", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.attribut_i", array("admin", "add", "edit", "delete","view"  ,"view_all", "grantall"));
		 registerNode("individu.competence_i", array("admin", "add", "edit", "delete","view"  ,"view_all", "grantall"));
		 registerNode("individu.contact_i", array("admin", "add", "edit", "delete","view"  ,"view_all", "grantall"));
		 registerNode("individu.cotisation_i", array("admin", "add", "edit", "delete","view"  ,"view_all", "grantall"));
		 registerNode("individu.cotorep_i", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.fonction_i", array("admin", "add", "edit", "delete","view"  ,"view_all", "grantall"));
		 registerNode("individu.inscription_i", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.rencontre_i", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("individu.ACTIVITE_i", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 */
		 
	}
	function getGgNodeName()
	{
		$res=array();
		$module="individu";
	 $res[]= $module."."."activite_i";
	 $res[]= $module."."."attribut_i";
	 $res[]= $module."."."bookmark_i";
	 $res[]= $module."."."carte_golf";
	 $res[]= $module."."."carte_golf_trou";
	 $res[]= $module."."."competence_i";
	 $res[]= $module."."."contact_i";
	 $res[]= $module."."."cotisation_i";
	 $res[]= $module."."."cotorep_i";
	 $res[]= $module."."."document_i";
	 $res[]= $module."."."envoi_groupe";
	 $res[]= $module."."."fonction_i";
	 	 $res[]= $module."."."gadget_i";
	 	 $res[]= $module."."."google_feed";
	 	 $res[]= $module."."."google_photos";
	 $res[]= $module."."."groupe_travail_i";
	 $res[]= $module."."."image_i";
	 $res[]= $module."."."immatriculation_i";
	 $res[]= $module."."."individu";
	 $res[]= $module."."."individu_simple";
	 $res[]= $module."."."individu_lieu";
	 $res[]= $module."."."individu_liste";
	 $res[]= $module."."."individu_pda";
	 $res[]= $module."."."inscription_i";
	 $res[]= $module."."."lieu";
	 $res[]= $module."."."menu_dashboard";
	 $res[]= $module."."."rencontre_i";
	 $res[]= $module."."."v_individu_correspondance";
	 $res[]= $module."."."v_individu_correspondant";
	 $res[]= $module."."."v_individu_lieu";
	 $res[]= $module."."."web_i";
	 $res[]= $module."."."correspondant";

	 return $res;
	}

	function getMenuItems()
	{
	}

	function getDescription()
	{
		return "Gestion d'un individu et de toutes ses dépendances";
	}

	function getPimItems()
	{
		return array("contact_i"=>"getContact","rencontre_i"=>"getRencontre", "activite_i"=>"getActivite");
	}

	function getContact()
	{
		include_once(moduleDir("individu")."pim.inc");
		return pimContacts();
	}

	function getRencontre()
	{
		include_once(moduleDir("individu")."pim.inc");
		return pimRencontres();
	}

	function getActivite()
	{
		include_once(moduleDir("individu")."pim.inc");
		return pimActivite();
	}

}

function search($expression)
{
	$res = array();
	$custnode = &getNode("individu.individu");
	$recs = $custnode->searchDb($expression);

	$res["individus"] = $this->recLinks($recs, "individu.individu");

	$individu_lieunode = &getNode("individu.individu_lieu");
	$res["individus_lieux"] = $this->recLinks($individu_lieunode ->searchDb($expression), "individu.individu_lieu");

	$individu_listenode = &getNode("individu.individu_liste");
	$res["individus_listes"] = $this->recLinks($individu_listenode ->searchDb($expression), "individu.individu_liste");

	$lieunode = &getNode("individu.lieu");
	$res["lieux"] = $this->recLinks($lieunode ->searchDb($expression), "individu.lieu");

	$listenode = &getNode("individu.liste");
	$res["listes"] = $this->recLinks($listenode ->searchDb($expression), "individu.liste");

	$attribut_inode = &getNode("individu.attribut_i");
	$res["attributs_i"] = $this->recLinks($attribut_inode ->searchDb($expression), "individu.attribut_i");

	$competence_inode = &getNode("individu.competence_i");
	$res["competences_i"] = $this->recLinks($competence_inode ->searchDb($expression), "individu.competence_i");

	$contact_inode = &getNode("individu.contact_i");
	$res["contacts_i"] = $this->recLinks($contact_inode ->searchDb($expression), "individu.contact_i");

	$cotisation_inode = &getNode("individu.cotisation_i");
	$res["cotisations_i"] = $this->recLinks($cotisation_inode ->searchDb($expression), "individu.cotisation_i");

	$cotorep_inode = &getNode("individu.cotorep_i");
	$res["cotoreps_i"] = $this->recLinks($cotorep_inode ->searchDb($expression), "individu.cotorep_i");

	$fonction_inode = &getNode("individu.fonction_i");
	$res["fonctions_i"] = $this->recLinks($fonction_inode ->searchDb($expression), "individu.fonction_i");

	$inscription_inode = &getNode("individu.inscription_i");
	$res["inscriptions_i"] = $this->recLinks($inscription_inode ->searchDb($expression), "individu.inscription_i");

	$rencontre_inode = &getNode("individu.rencontre_i");
	$res["rencontres_i"] = $this->recLinks($rencontre_inode ->searchDb($expression), "individu.inscription_i");

	$activite_inode = &getNode("individu.activite_i");
	$res["activites_i"] = $this->recLinks($activite_inode ->searchDb($expression), "individu.activite_i");
	$activite_inode = &getNode("individu.google_feed");
	$res["google_feed"] = $this->recLinks($activite_inode ->searchDb($expression), "individu.google_feed");


	return $res;
}


?>