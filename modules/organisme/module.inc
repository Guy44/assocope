<?php
class mod_organisme extends associationModule {
	function getNodes() {
		registerNode("organisme.tableaudebord", array (
		"tableau_organisme",
		"tableau_individu",
				"view"
				));
		registerNode("organisme.organisme", array (
			"admin",
			"add",
			"edit",
			"delete",
			"view",
			"lister",
			"view_all",
			"export",
			"import"
			));
			registerNode("organisme.domaine", array (
			"admin",
			"add",
			"edit",
			"delete",
			"view",
			"lister",
			"view_all",
			"export",
			"import"
			));
			registerNode("organisme.v_individu_recu_fiscal", array (
			"admin",
			"document",
			"add",
			"edit",
			"delete",
			"view",
			"lister",
			"view_all",
			"export",
			"import"
			));
			registerNode("organisme.v_organisme_lieu", array (
			"admin",
			"document",
			"add",
			"edit",
			"delete",
			"view",
			"lister",
			"view_all",
			"export",
			"import"
			));
			registerNode("organisme.v_organisme_lieu", array (
			"admin",
			"document",
			"add",
			"edit",
			"delete",
			"view",
			"save",
			"view_all",
			"export",
			"import"
			));
	}
	function getGgNodeName()
	{
		$res=array();
		$module="organisme";
		$res[]= $module."."."abandon_creance";
		$res[]= $module."."."budget";
		$res[]= $module."."."budget_ligne";
		$res[]= $module."."."calendrier";
		$res[]= $module."."."calendrier_rencontre";
		$res[]= $module."."."calendrier_groupe_travail";
		$res[]= $module."."."calendrier_lieu_rencontre";
		$res[]= $module."."."calendrier_element";

		$res[]= $module."."."compte";
	 $res[]= $module."."."contrat";
$res[]= $module."."."competence_o";
	 $res[]= $module."."."cotisation";
	 $res[]= $module."."."document";
	 $res[]= $module."."."document_communication";
	 $res[]= $module."."."document_officiel";
	 $res[]= $module."."."domaine";
	 $res[]= $module."."."ecriture_comptable";
	 $res[]= $module."."."financement";
	 $res[]= $module."."."fourniture";
	 $res[]= $module."."."gazette";
	 $res[]= $module."."."golf_parcours";
	 $res[]= $module."."."golf_parcours_trou";
	 $res[]= $module."."."groupe_travail";
	 $res[]= $module."."."groupe_travail_cyclus";
	 $res[]= $module."."."image";
	 $res[]= $module."."."immatriculation";
	 $res[]= $module."."."infolettre";
	 $res[]= $module."."."journal_comptable";
	 $res[]= $module."."."lieu_rencontre";
	 $res[]= $module."."."ligne_ecriture_comptable";
	 $res[]= $module."."."organisme";
	 $res[]= $module."."."organisme_simple";
	 $res[]= $module."."."organisme_lieu";
	 	 $res[]= $module."."."organisme_liste";
	 $res[]= $module."."."organisme_pda";
	 $res[]= $module."."."partenaire";
	 $res[]= $module."."."patrimoine";
	 $res[]= $module."."."printview";
	 $res[]= $module."."."referencement";
	 $res[]= $module."."."releve_banque";
	 $res[]= $module."."."remise_banque";
	 $res[]= $module."."."rencontre";
	 $res[]= $module."."."rencontre_communication";
	 $res[]= $module."."."rencontre_fournisseur";
	 $res[]= $module."."."rencontre_choix";
	 $res[]= $module."."."organisme_statistique";
	 $res[]= $module."."."organisme_statistique_ligne";
	 $res[]= $module."."."tableaudebord";
	 $res[]= $module."."."v_individu_recu_fiscal";
	 	 $res[]= $module."."."v_individu_recu_fiscal_abandon";
	 $res[]= $module."."."v_organisme_comptes_tiers";
	 $res[]= $module."."."v_organisme_fonction";
	 $res[]= $module."."."v_organisme_inscription";
	 $res[]= $module."."."v_organisme_inscription_controle";
	 $res[]= $module."."."v_organisme_lieu";
	 $res[]= $module."."."v_organisme_remise_banque";
	 $res[]= $module."."."v_organisme_rencontre";
	 $res[]= $module."."."virement_comptable";


	 return $res;
	}

	function getMenuItems() {
	}
	/*
	 function getMenuItems()
	 {
	 $selectedorganisme = array_key_exists("selectedorganisme", $_REQUEST) ? $_REQUEST["selectedorganisme"] : 0;
	 if ($selectedorganisme == 0)
	 {
	 $this->menuitem("organismes",dispatch_url("organisme.organisme", "admin"),"main",array("organisme.organisme", "admin"),400); // organismes submenu
	 $target_planning = "dispatch.php?atknodetype=organisme.organisme&atkaction=edit&selectedorganismeid=[id]";
	 $this->menuitem("organisme_admin", dispatch_url("organisme.organisme", "admin"), "organismes", array("organisme.organisme", "admin"));
	 }
	 else
	 {
	 $this->menuitem("organismes",dispatch_url("organisme.organisme", "admin"),"main",array("organisme.organisme", "admin"),400); // organismes submenu
	 $this->menuitem("organisme_edit", dispatch_url("organisme.organisme", "edit", array("atkselector" => "organisme.id='".$selectedorganisme."'")), "organismes", array("organisme.organisme", "edit"));
	 $this->menuitem("organisme_view", dispatch_url("organisme.organisme", "view", array("atkselector" => "organisme.id='".$selectedorganisme."'")), "organismes", array("organisme.organisme", "admin"));

	  
	 }
	  

	 }
	  
	 */
	function getDescription() {
		return "Gestion d'un organisme et de toutes ses dépendances";
	}
	function getDependencies($mode) {
		return array (
			"person"
			);
	}
	function search($expression) {
		$res = array ();
		$custnode = & getNode("organisme.organisme");
		$recs = $custnode->searchDb($expression);
		$res["organismes"] = $this->recLinks($recs, "organisme.organisme");
		//$comptenode = &getNode("organisme.compte");
		//$res["comptes"] = $this->recLinks($comptenode->searchDb($expression), "organisme.compte");
		$etatbudgetsnode = & getNode("organisme.budget");
		$res["Organisme_budget"] = $this->recLinks($etatbudgetsnode->searchDb($expression), "organisme.budget");
		$etatbudgetlignesnode = & getNode("organisme.budget_ligne");
		$res["Organisme_budget_ligne"] = $this->recLinks($etatbudgetlignesnode->searchDb($expression), "organisme.budget_ligne");
		$contratnode = & getNode("organisme.contrat");
		$res["Organisme_contrats"] = $this->recLinks($contratnode->searchDb($expression), "organisme.contrat");
	//			$contratnode = & getNode("organisme.convention");
	//	$res["Organisme_conventions"] = $this->recLinks($contratnode->searchDb($expression), "organisme.convention");
		
		$documentnode = & getNode("organisme.document");
		$res["Organisme_documents"] = $this->recLinks($documentnode->searchDb($expression), "organisme.document");
		$documentcommunicationnode = & getNode("organisme.document_communication");
		$res["Organisme_communications"] = $this->recLinks($documentcommunicationnode->searchDb($expression), "organisme.document_communication");
		$documentofficielnode = & getNode("organisme.document_officiel");
		$res["Organisme_documents_officiels"] = $this->recLinks($documentofficielnode->searchDb($expression), "organisme.document_officiel");
		//$journal_comptablenode = &getNode("organisme.journal_comptable");
		//$res["journal_comptable"] = $this->recLinks($journal_comptablenode ->searchDb($expression), "organisme.journal_comptable");
		//$ecriture_comptablenode = &getNode("organisme.ecriture_comptable");
		//$res["ecriture_comptable"] = $this->recLinks($ecriture_comptablenode ->searchDb($expression), "organisme.ecriture_comptable");
		//$ligne_ecriture_comptablenode = &getNode("organisme.ligne_ecriture_comptable");
		//$res["ligne_ecriture_comptable"] = $this->recLinks($ligne_ecriture_comptablenode ->searchDb($expression), "organisme.ligne_ecriture_comptable");
		$financementnode = & getNode("organisme.financement");
		$res["Organisme_financement"] = $this->recLinks($financementnode->searchDb($expression), "organisme.financement");
		$fourniturenode = & getNode("organisme.fourniture");
		$res["Organisme_fourniture"] = $this->recLinks($fourniturenode->searchDb($expression), "organisme.fourniture");
		$immatriculationnode = & getNode("organisme.immatriculation");
		$res["Organisme_immatriculation"] = $this->recLinks($immatriculationnode->searchDb($expression), "organisme.immatriculation");
		$partenairenode = & getNode("organisme.partenaire");
		$res["Organisme_partenaire"] = $this->recLinks($partenairenode->searchDb($expression), "organisme.partenaire");
		$domainenode = & getNode("organisme.domaine");
		$res["Organisme_domaine"] = $this->recLinks($domainenode->searchDb($expression), "organisme.domaine");
		$patrimoinenode = & getNode("organisme.patrimoine");
		$res["Organisme_patrimoine"] = $this->recLinks($patrimoinenode->searchDb($expression), "organisme.patrimoine");
		$referencementnode = & getNode("organisme.referencement");
		$res["Organisme_referencement"] = $this->recLinks($referencementnode->searchDb($expression), "organisme.referencement");
		$rencontrenode = & getNode("organisme.rencontre");
		$res["Organisme_rencontre"] = $this->recLinks($rencontrenode->searchDb($expression), "organisme.rencontre");
		//	$rencontre_fournisseurnode = & getNode("organisme.rencontre_fournisseur");
		//		$res["Organisme_rencontre_fournisseur"] = $this->recLinks($rencontre_fournisseurnode->searchDb($expression), "organisme.rencontre_fournisseur");
		$rencontre_communicationnode = & getNode("organisme.rencontre_communication");
		$res["Organisme_rencontre_communication"] = $this->recLinks($rencontre_communicationnode->searchDb($expression), "organisme.rencontre_communication");
		$cotisationnode = & getNode("organisme.cotisation");
		$res["cotisation"] = $this->recLinks($cotisationnode->searchDb($expression), "organisme.cotisation");
		$gazettenode = & getNode("organisme.gazette");
		$res["Organisme_gazette"] = $this->recLinks($gazettenode->searchDb($expression), "organisme.gazette");
		$infolettrenode = & getNode("organisme.infolettre");
		$res["Organisme_infolettre"] = $this->recLinks($infolettrenode->searchDb($expression), "organisme.infolettre");
		$tableaudebordnode = & getNode("organisme.tableaudebord");
		$res["Tableaudebord"] = $this->recLinks($tableaudebordnode->searchDb($expression), "organisme.tableaudebord");
		$manuelnode = & getNode("manuel.manuel");
		$res["manuel"] = $this->recLinks($manuelnode->searchDb($expression), "manuel.manuel");
		$todonode = & getNode("todo.todo");
		$res["todo"] = $this->recLinks($todonode->searchDb($expression), "todo.todo");
		$individunode = & getNode("individu.individu");
		$res["individu"] = $this->recLinks($individunode->searchDb($expression), "individu.individu");
		//     $individu_lieunode = &getNode("individu.individu_lieu");
		//      $res["individus_lieux"] = $this->recLinks($individu_lieunode ->searchDb($expression), "individu.individu_lieu");
		$individu_listenode = & getNode("individu.individu_liste");
		$res["individus_listes"] = $this->recLinks($individu_listenode->searchDb($expression), "individu.individu_liste");
		$lieunode = & getNode("individu.lieu");
		$res["Individu_lieux"] = $this->recLinks($lieunode->searchDb($expression), "individu.lieu");
		$attribut_inode = & getNode("individu.attribut_i");
		$res["Individu_attributs"] = $this->recLinks($attribut_inode->searchDb($expression), "individu.attribut_i");
		$bookmark_inode = & getNode("individu.bookmark_i");
		$res["Individu_bookmarks"] = $this->recLinks($bookmark_inode->searchDb($expression), "individu.bookmark_i");
		$competence_inode = & getNode("individu.competence_i");
		$res["Individu_competences"] = $this->recLinks($competence_inode->searchDb($expression), "individu.competence_i");
		$contact_inode = & getNode("individu.contact_i");
		$res["Individu_contacts"] = $this->recLinks($contact_inode->searchDb($expression), "individu.contact_i");
		$cotisation_inode = & getNode("individu.cotisation_i");
		$res["Individu_cotisations"] = $this->recLinks($cotisation_inode->searchDb($expression), "individu.cotisation_i");
		$cotorep_inode = & getNode("individu.cotorep_i");
		$res["Individu_cotoreps"] = $this->recLinks($cotorep_inode->searchDb($expression), "individu.cotorep_i");
		$fonction_inode = & getNode("individu.fonction_i");
		$res["Individu_fonctions"] = $this->recLinks($fonction_inode->searchDb($expression), "individu.fonction_i");
		$inscription_inode = & getNode("individu.inscription_i");
		$res["Individu_inscriptions"] = $this->recLinks($inscription_inode->searchDb($expression), "individu.inscription_i");
		//	$rencontre_inode = & getNode("individu.rencontre_i");
		//	$res["Individu_rencontres"] = $this->recLinks($rencontre_inode->searchDb($expression), "individu.inscription_i");
		$activite_inode = & getNode("individu.activite_i");
		$res["Individu_activites"] = $this->recLinks($activite_inode->searchDb($expression), "individu.activite_i");
		$activitesnode = & getNode("table.activite");
		$res["Type_activites"] = $this->recLinks($activitesnode->searchDb($expression), "table.activite");
		$attributsnode = & getNode("table.type_attribut");
		$res["Type_attributs"] = $this->recLinks($attributsnode->searchDb($expression), "table.type_attribut");
		$audiencesnode = & getNode("table.audience");
		$res["Type_audiences"] = $this->recLinks($audiencesnode->searchDb($expression), "table.audience");
		$banquesnode = & getNode("table.banque");
		$res["Type_banques"] = $this->recLinks($banquesnode->searchDb($expression), "table.banque");
		$bookmarksnode = & getNode("table.type_bookmark");
		$res["Type_bookmarks"] = $this->recLinks($bookmarksnode->searchDb($expression), "table.type_bookmark");
		$calendriersnode = & getNode("table.type_calendrier");
		$res["type_calendriers"] = $this->recLinks($calendriersnode->searchDb($expression), "table.type_calendrier");
		$competencesnode = & getNode("table.competence");
		$res["Type_competences"] = $this->recLinks($competencesnode->searchDb($expression), "table.competence");
		$contactsnode = & getNode("table.contact");
		$res["Type_contacts"] = $this->recLinks($contactsnode->searchDb($expression), "table.contact");
		$codespostauxnode = & getNode("table.cp_ville_pays");
		$res["Type_codespostaux"] = $this->recLinks($codespostauxnode->searchDb($expression), "table.cp_ville_pays");
		$documentsnode = & getNode("table.type_document");
		$res["Type_documents"] = $this->recLinks($documentsnode->searchDb($expression), "table.type_document");
		$etats_referencementnode = & getNode("table.type_etat_referencement");
		$res["Type_etats_referencements"] = $this->recLinks($etats_referencementnode->searchDb($expression), "table.type_etat_referencement");
		$fonctionsnode = & getNode("table.fonction");
		$res["Type_fonctions"] = $this->recLinks($fonctionsnode->searchDb($expression), "table.fonction");
		$inscriptionsnode = & getNode("table.type_inscription");
		$res["Type_inscriptions"] = $this->recLinks($inscriptionsnode->searchDb($expression), "table.type_inscription");
		$listesnode = & getNode("table.type_liste");
		$res["Type_listes"] = $this->recLinks($listesnode->searchDb($expression), "table.type_liste");
		$organismesnode = & getNode("table.type_organisme");
		$res["Type_organismes"] = $this->recLinks($organismesnode->searchDb($expression), "table.type_organisme");
		$paysnode = & getNode("table.pays");
		$res["Type_pays"] = $this->recLinks($paysnode->searchDb($expression), "table.pays");
		$radiationsnode = & getNode("table.type_radiation");
		$res["Type_radiations"] = $this->recLinks($radiationsnode->searchDb($expression), "table.type_radiation");
		$referencementsnode = & getNode("table.type_referencement");
		$res["Type_referencements"] = $this->recLinks($referencementsnode->searchDb($expression), "table.type_referencement");
		$reglementsnode = & getNode("table.reglement");
		$res["Type_reglements"] = $this->recLinks($reglementsnode->searchDb($expression), "table.reglement");
		$rencontresnode = & getNode("table.type_rencontre");
		$res["Type_rencontres"] = $this->recLinks($rencontresnode->searchDb($expression), "table.type_rencontre");
		$titresnode = & getNode("table.titre");
		$res["Type_titres"] = $this->recLinks($titresnode->searchDb($expression), "table.titre");
		$originesnode = & getNode("table.origine");
		$res["Type_origines"] = $this->recLinks($originesnode->searchDb($expression), "table.origine");
		$etattodosnode = & getNode("table.type_etat_todo");
		$res["Type_etattodos"] = $this->recLinks($etattodosnode->searchDb($expression), "table.type_etat_todo");
		//$abonnesinfolettrenode = &getNode("infolettre");
		//$res["Abonnes_Infolettre"] = $this->recLinks($abonnesinfolettrenode ->searchDb($expression), "table.infolettre");
		return $res;
	}
}
?>