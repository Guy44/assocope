<?php
class mod_table extends associationModule {
	function getNodes() {
		registerNode("table.activite", array (
			"admin",
			"add",
			"edit",
			"delete",
			"view",
			"view_all",
			"export",
			"import"
			));

	}
	function getMenuItems($topmenu) {
		if ($topmenu=="Tables")

		{
		$db = & atkGetDb();
			
		// TOP TABLES
		// Tables
		$data = $db->getrows("SELECT count(id) as nombre from type_activite ");
		$nombre_type_activite = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_attribut ");
		$nombre_type_attribut = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_attribut_placemark ");
		$nombre_type_attribut_placemark = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_audience ");
		$nombre_type_audience = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_banque ");
		$nombre_type_banque = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_bookmark ");
		$nombre_type_bookmark = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_calendrier ");
		$nombre_type_calendrier = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_categorie_golf ");
		$nombre_type_categorie_golf = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_competence ");
		$nombre_type_competence = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_competence_organisme ");
		$nombre_type_competence_organisme = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_contact ");
		$nombre_type_contact = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_contrat ");
		$nombre_type_contrat = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_cp_ville_pays ");
		$nombre_type_cp_ville_pays = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_demande ");
		$nombre_type_demande = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_document ");
		$nombre_type_document = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_entite ");
		$nombre_type_entite = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_envoi_groupe ");
		$nombre_type_envoi_groupe = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_etat_referencement ");
		$nombre_type_etat_referencement = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_etat_todo ");
		$nombre_type_etat_todo = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_fonction ");
		$nombre_type_fonction = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_icone ");
		$nombre_type_icone = $data[0]["nombre"];

		$data = $db->getrows("SELECT count(id) as nombre from type_image ");
		$nombre_type_image = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_inscription ");
		$nombre_type_inscription = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_langue ");
		$nombre_type_langue = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_liste ");
		$nombre_type_liste = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_maree_meteo ");
		$nombre_type_maree_meteo = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_menu ");
		$nombre_type_menu = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_moteur ");
		$nombre_type_moteur = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_normalisation_libelle ");
		$nombre_type_normalisation_libelle = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_organisme ");
		$nombre_type_organisme = $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_origine ");
		$nombre_type_origine= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_pays ");
		$nombre_type_pays= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_placemark ");
		$nombre_type_placemark= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_radiation ");
		$nombre_type_radiation= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_referencement ");
		$nombre_type_referencement= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_region_pays ");
		$nombre_type_region_pays= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_reglement ");
		$nombre_type_reglement= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_remise_banque ");
		$nombre_type_remise_banque= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_rencontre ");
		$nombre_type_rencontre= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_rencontre_participation ");
		$nombre_type_rencontre_participation= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_role_groupe_travail ");
		$nombre_type_role_groupe_travail= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_statistique ");
		$nombre_type_statistique= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_symbole_gps ");
		$nombre_type_symbole_gps= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_traduction ");
		$nombre_type_traduction= $data[0]["nombre"];
			
		$data = $db->getrows("SELECT count(id) as nombre from app_traduction ");
		$nombre_app_traduction= $data[0]["nombre"];
			
		$data = $db->getrows("SELECT count(id) as nombre from type_titre ");
		$nombre_type_titre= $data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from type_zone_region_pays ");
		$nombre_type_zone_region_pays= $data[0]["nombre"];



		//		$this->menuitem("Tables", "", "main", true);
		//			$this->menuitem("Tables_top", "", "Tables", true);
		//			$this->menuitem("-", "", "Tables", true);
		// Activites
		$this->menuitem("activites_t"."#".$nombre_type_activite, dispatch_url("table.activite", "admin"), "Tables", true);
		// Attributs
		$this->menuitem("attributs_t"."#".$nombre_type_attribut, dispatch_url("table.type_attribut", "admin"), "Tables", true);
		// Audiences
		$this->menuitem("audiences_t"."#".$nombre_type_audience, dispatch_url("table.audience", "admin"), "Tables", true);

		// Banques
		$this->menuitem("banques_t"."#".$nombre_type_banque, dispatch_url("table.banque", "admin"), "Tables", true);

		// Biodiversité_observations
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation ");
		$this->menuitem("biodiversité_observations"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation", "admin"), "Tables", true);
		// Biodiversité_observations_détail
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation_detail ");
		$this->menuitem("biodiversité_observations_détails"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation_detail", "admin"), "Tables", true);
		// Biodiversité_protection
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_protection");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Biodiversite_protection"."#".$nombre, dispatch_url("biodiversite.protection", "admin"), "Tables", true);
		// Biodiversité_protection_taxinomie
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_protection_taxinomie");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Biodiversite_protection_taxinomie"."#".$nombre, dispatch_url("biodiversite.protection_taxinomie", "admin"), "Tables", true);
			
		// Calendriers
		$this->menuitem("calendriers_t"."#".$nombre_type_calendrier, dispatch_url("table.type_calendrier", "admin"), "Tables", true);
		// Catalogue of life : taxa
		$data = $db->getrows("SELECT count(record_id) as nombre from col_taxa");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Catalogue of life"."#".$nombre, dispatch_url("biodiversite.col_taxa", "admin"), "Tables", true);

		$data = $db->getrows("SELECT count(id) as nombre from type_categorie_golf ");
		$nombre_categories= $data[0]["nombre"];
		// atégories golf
		$this->menuitem("catégories_golf"."#".$nombre_categories, dispatch_url("table.categorie_golf", "admin"), "Tables", true);
		// Compétences
		$this->menuitem("compétences_t"."#".$nombre_type_competence, dispatch_url("table.competence", "admin"), "Tables", true);
		// Compétences organisme
		$this->menuitem("compétences_organisme_t"."#".$nombre_type_competence_organisme, dispatch_url("table.type_competence_organisme", "admin"), "Tables", true);
		// Contacts
		$this->menuitem("contacts_t"."#".$nombre_type_contact, dispatch_url("table.contact", "admin"), "Tables", true);
		// Contrats
		$this->menuitem("contrats_t"."#".$nombre_type_contrat, dispatch_url("table.type_contrat", "admin"), "Tables", true);
			
		$data = $db->getrows("SELECT count(id) as nombre from type_correspondant ");
		$nombre_type_correspondant= $data[0]["nombre"];
		// Correspondant
		$this->menuitem("correspondants"."#".$nombre_type_correspondant, dispatch_url("table.type_correspondant", "admin"), "Tables", true);
			
		$data = $db->getrows("SELECT count(id) as nombre from type_couleur ");
		$nombre_type_couleur= $data[0]["nombre"];
		// Codes couleurs
		$this->menuitem("couleurs"."#".$nombre_type_couleur, dispatch_url("table.type_couleur", "admin"), "Tables", true);
			
			
		// Codes postaux
		$this->menuitem("codes_postaux_t"."#".$nombre_type_cp_ville_pays, dispatch_url("table.cp_ville_pays", "admin"), "Tables", true);
		// Demandes
		$this->menuitem("demandes_t"."#".$nombre_type_demande, dispatch_url("table.type_demande", "admin"), "Tables", true);
		// Documents
		$this->menuitem("documents_t"."#".$nombre_type_document, dispatch_url("table.type_document", "admin"), "Tables", true);
		// Entités
		$this->menuitem("entités_t"."#".$nombre_type_entite, dispatch_url("table.type_entite", "admin"), "Tables", true);
		// Type Ecriture comptable
		$data = $db->getrows("SELECT count(id) as nombre from type_ecriture ");
		$nombre=$data[0]["nombre"];
		$this->menuitem("ecritures"."#".$nombre, dispatch_url("table.type_ecriture", "admin"), "Tables", true);
		// Envois_groupes
		$this->menuitem("envois_groupés_t"."#".$nombre_type_envoi_groupe, dispatch_url("table.type_envoi_groupe", "admin"), "Tables", true);
		// Etats referencement
		$this->menuitem("etats_referencement_t"."#".$nombre_type_etat_referencement, dispatch_url("table.type_etat_referencement", "admin"), "Tables", true);
		// Fonctions
		$this->menuitem("fonctions_t"."#".$nombre_type_fonction, dispatch_url("table.fonction", "admin"), "Tables", true);
		// Images
		$this->menuitem("images_t"."#".$nombre_type_image, dispatch_url("table.type_image", "admin"), "Tables", true);
		// Inscriptions
		$this->menuitem("inscriptions_t"."#".$nombre_type_inscription, dispatch_url("table.type_inscription", "admin"), "Tables", true);
		// Langues
		$this->menuitem("langues_t"."#".$nombre_type_langue, dispatch_url("table.type_langue", "admin"), "Tables", true);
		// Listes
		$this->menuitem("listes_t"."#".$nombre_type_liste, dispatch_url("table.type_liste", "admin"), "Tables", true);
		// Marque pages
		$this->menuitem("marque_pages_t"."#".$nombre_type_bookmark, dispatch_url("table.type_bookmark", "admin"), "Tables", true);
		// Menus
		$this->menuitem("menus_t"."#".$nombre_type_menu, dispatch_url("table.type_menu", "admin"), "Tables", true);
		// Moteurs
		$this->menuitem("moteurs_t"."#".$nombre_type_moteur, dispatch_url("table.type_moteur", "admin"), "Tables", true);
		// Normalisation
		$this->menuitem("normalisation_t"."#".$nombre_type_normalisation_libelle, dispatch_url("table.type_normalisation_libelle", "admin"), "Tables", true);
		// Organismes
		$this->menuitem("organismes_t"."#".$nombre_type_organisme, dispatch_url("table.type_organisme", "admin"), "Tables", true);
		// Origines
		$this->menuitem("origines_t"."#".$nombre_type_origine, dispatch_url("table.origine", "admin"), "Tables", true);
		// Parcours de golf 
		
		$data = $db->getrows("SELECT count(id) as nombre from organisme_golf_parcours ");
		$nombre_golf_parcours = $data[0]["nombre"];
		$this->menuitem("parcours_golf_t"."#".$nombre_golf_parcours, dispatch_url("organisme.golf_parcours", "admin"), "Tables", true);
		// Pays
		$this->menuitem("pays_t"."#".$nombre_type_pays, dispatch_url("table.pays", "admin"), "Tables", true);
		// Radiations
		$this->menuitem("radiations_t"."#".$nombre_type_radiation, dispatch_url("table.type_radiation", "admin"), "Tables", true);
		// Fréquences
		//								$data = $db->getrows("SELECT count(id) as nombre from type_frequence ");
		//			$nombre_type_frequence = $data[0]["nombre"];
		//			$this->menuitem("frequence_t"."#".$nombre_type_frequence, dispatch_url("table.type_frequence", "admin"), "Tables", true);
		$data = $db->getrows("SELECT count(id) as nombre from scheduler_cyclus");
		$nombre_recurrence= $data[0]["nombre"];

		// Récurrences
		$this->menuitem("recurrence_t"."#".$nombre_recurrence, dispatch_url("scheduler.scheduler_cyclus", "admin"), "Tables", true);
		// Remises banque
		$this->menuitem("remises_banque_t"."#".$nombre_type_remise_banque, dispatch_url("table.type_remise_banque", "admin"), "Tables", true);
		// Referencements
		$this->menuitem("referencements_t"."#".$nombre_type_referencement, dispatch_url("table.type_referencement", "admin"), "Tables", true);
		// Reglements
		$this->menuitem("reglements_t"."#".$nombre_type_reglement, dispatch_url("table.reglement", "admin"), "Tables", true);
		// Rencontres
		$this->menuitem("rencontres_t"."#".$nombre_type_rencontre, dispatch_url("table.type_rencontre", "admin"), "Tables", true);
		// Rôle groupe de travail
		$this->menuitem("role_groupe_travail_t"."#".$nombre_type_role_groupe_travail, dispatch_url("table.type_role_groupe_travail", "admin"), "Tables", true);
		// Statistiques
		$this->menuitem("Statistique"."#".$nombre_type_statistique, dispatch_url("table.type_statistique", "admin"), "Tables", true);
		// Participation rencontres
		$this->menuitem("participation_rencontres_t"."#".$nombre_type_rencontre_participation, dispatch_url("table.type_rencontre_participation", "admin"), "Tables", true);

			
			
		// Rang taxinomique
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_rang_taxinomique");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Taxinomie_rang"."#".$nombre, dispatch_url("biodiversite.rang_taxinomique", "admin"), "Tables", true);
		// Statut taxinomique
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_statut_taxinomique");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Taxinomie_statut"."#".$nombre, dispatch_url("biodiversite.statut_taxinomique", "admin"), "Tables", true);
		// Taxinomie
		$data = $db->getrows("SELECT count(id) as nombre from biodiversite_taxinomie");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Taxinomie_taxons"."#".$nombre, dispatch_url("biodiversite.taxinomie", "admin"), "Tables", true);
		$this->menuitem("Taxinomie_reduite"."#".$nombre, dispatch_url("biodiversite.taxinomie_reduite", "admin"), "Tables", true);



		//Tâches(état)
		$this->menuitem("Tâches(état)_t"."#".$nombre_type_etat_todo, dispatch_url("table.type_etat_todo", "admin"), "Tables", true);
		// Titres
		$this->menuitem("titres_t"."#".$nombre_type_titre, dispatch_url("table.titre", "admin"), "Tables", true);
		$data = $db->getrows("SELECT count(id) as nombre from type_tournoi");
		$nombre= $data[0]["nombre"];
		// tournoi
		$this->menuitem("Tournois"."#".$nombre , dispatch_url("table.type_tournoi", "admin"), "Tables", true);
		$data = $db->getrows("SELECT count(id) as nombre from tournoi_rencontre_match");
		$nombre= $data[0]["nombre"];
		$this->menuitem("Tournoismatches"."#".$nombre, dispatch_url("tournoi.tournoi_rencontre_match", "admin"), "Tables", true);
			
		// traductions
		$this->menuitem("Traductions(types)"."#".$nombre_type_traduction , dispatch_url("table.type_traduction", "admin"), "Tables", true);
		$this->menuitem("Traductions"."#".$nombre_app_traduction , dispatch_url("application.traduction", "admin"), "Tables", true);
		$this->menuitem('-', "", "Tables", true);
		$this->menuitem('-', "", "main", true);

		}		
	}
	function getGgNodeName()
	{
		$res=array();
		$module="table";
		$res[]= $module."."."activite";
	 $res[]= $module."."."audience";
	 $res[]= $module."."."banque";
	 $res[]= $module."."."categorie_golf";
	 $res[]= $module."."."competence";
	 $res[]= $module."."."contact";
	 $res[]= $module."."."cp_ville_pays";
	 $res[]= $module."."."fonction";
	 $res[]= $module."."."maree_meteo";
	 $res[]= $module."."."origine";
	 $res[]= $module."."."pays";
	 $res[]= $module."."."reglement";
	 $res[]= $module."."."titre";
	 $res[]= $module."."."type_attribut";
	 $res[]= $module."."."type_bookmark";
	 $res[]= $module."."."type_attribut_placemark";
	 $res[]= $module."."."type_calendrier";

	 $res[]= $module."."."type_competence_organisme";
	 $res[]= $module."."."type_contrat";
	 $res[]= $module."."."type_couleur";
	 $res[]= $module."."."type_demande";
	 $res[]= $module."."."type_document";
	 $res[]= $module."."."type_ecriture";
	 $res[]= $module."."."type_entite";
	 $res[]= $module."."."type_envoi_groupe";
	 $res[]= $module."."."type_etat_referencement";
	 $res[]= $module."."."type_etat_todo";
	 $res[]= $module."."."type_frequence";
	 $res[]= $module."."."type_icone";
	 $res[]= $module."."."type_image";
	 $res[]= $module."."."type_inscription";
	 $res[]= $module."."."type_langue";
	 $res[]= $module."."."type_zone_region_pays";
	 $res[]= $module."."."type_liste";
	 $res[]= $module."."."type_menu";
	 $res[]= $module."."."type_moteur";
	 $res[]= $module."."."type_normalisation_libelle";

	 $res[]= $module."."."type_organisme";
	 $res[]= $module."."."type_placemark";
	 $res[]= $module."."."type_radiation";
	 $res[]= $module."."."type_referencement";
	 $res[]= $module."."."type_region_pays";
	 $res[]= $module."."."type_remise_banque";
	 $res[]= $module."."."type_rencontre";
	 $res[]= $module."."."type_rencontre_participation";
	 $res[]= $module."."."type_role_groupe_travail";
	 $res[]= $module."."."type_statistique";
	 $res[]= $module."."."type_symbole_gps";
	 $res[]= $module."."."type_tournoi";
	 $res[]= $module."."."type_traduction";
//	 $res[]= $module."."."app_traduction";
	 $res[]= $module."."."type_zone_region_pays";
	 $res[]= $module."."."v_lieu_cp";
	 $res[]= $module."."."v_lieu_province";
	 $res[]= $module."."."v_lieu_ville";
	 return $res;
	}

}
?>
