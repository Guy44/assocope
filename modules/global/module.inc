<?php
class mod_global extends associationModule {
	function getNodes() {
	}
	function getMenuItems($topmenu) {

		// 	TRAITE DANS menu/assocope.inc 
		// $this->menuitem(string libelle_menu_item, "", "parent_menu", true);
		// string libelle_menu_item :  @libellé_pour_tootip@libelle_pour_libelle_menu#nombre
		// si @libellé_pour_tootip@ est absent c'est libelle_pour_libelle_menu qui est utilisé pour vaccès à tooltip
		//dans le fichier lng
		/*
		"menu_libelle_pour_libelle_menu"=>"contenu libellé menu",
		"menu_tooltip_libellé_pour_tootip"=>"contenu tooltip menu",
		"module_nomattribut_tooltip" => "contenu tooltip.",
		"wiki_module.node"=>"critère de recherche pour le wiki"
		'target_blank'
		'target_menu'
		début de name  ' / ' : pas de saut de ligne et insertion de ' | '
		début de name  '-/+' : pas de saut de ligne et insertion de "-|+"
		débute de name '!' : le nom n'est pas traduit  (on garde les _, ...)
		débute de name '%' : le nom est remplacé par rien en sortie
		*/
		$type_ecriture_journal=1;
		$type_ecriture_cotisation=2;
		$type_ecriture_participation_rencontre=3;
		$type_ecriture_rencontre=4;
		$type_ecriture_rencontre_fournisseur=5;
		$type_ecriture_depense=6;
		$type_ecriture_recette=7;
		$type_ecriture_virement=8;
		$type_ecriture_frais=9;
		$type_ecriture_abandon_creance=10;
		$node = new assmetanode();
		global $g_sessionManager;
		$g_utilisateur_individu = $g_sessionManager->getValue("utilisateur_individu", "globals");

		// Dernier organisme sélectionné
		$organismeid = 0;
		$user = getUser();
		$id = $user["id"];
		if (isset ($id)) {
			$db = & atkGetDb();
			$id_individu=$g_utilisateur_individu[$id];
		//	$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
		//	$id_individu = $data[0]["id_individu"];
			$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='organisme' order by date_recent_use desc");
			if (count($data) > 0) {
				$organismeid = $data[0]["id_entite"];
				$data = $db->getrows("select nom , courriel, site_internet, calendrier, calendrier_contacts_url, calendrier_contacts_refresh,
				calendrier_rencontres_url, calendrier_rencontres_refresh, telephone  from organisme where id=$organismeid");
				$nom_organisme = $data[0]["nom"];
				$courriel_organisme = $data[0]["courriel"];
				$calendrier_organisme = $data[0]["calendrier"];
				$calendrier_contacts_url_organisme = $data[0]["calendrier_contacts_url"];
				$calendrier_contacts_refresh_organisme = $data[0]["calendrier_contacts_refresh"];
				$calendrier_rencontres_url_organisme = $data[0]["calendrier_rencontres_url"];
				$calendrier_rencontres_refresh_organisme = $data[0]["calendrier_rencontres_refresh"];
				$site_internet_organisme = $data[0]["site_internet"];
				$telephone_organisme = $data[0]["telephone"];
				$data = $db->getrows("SELECT adresse1, adresse2, code_postal, ville, code_iso
				from organisme_lieu il, lieu l, type_cp_ville_pays cp, type_pays p
				where il.id_organisme=$organismeid and il.adresse_defaut_o_n='1'
				and il.id_lieu=l.id
				and l.id_ville=cp.id
				and cp.id_pays=p.id");
				if (!empty($data[0]["ville"] ))
				{$adresse_organisme = $data[0]["adresse1"] . '<br />'  . $data[0]["code_postal"] . ' ' . $data[0]["ville"] . ' (' . $data[0]["code_iso"].')';}
				else {$adresse_organisme="";}

				$data = $db->getrows("SELECT od.nom_domaine as domaine from organisme_domaine od
				where od.id_organisme=$organismeid and od.google_apps_o_n='1'
				");
				$google_apps='';
				if (!empty($data[0]["domaine"] ))
				{
					$google_apps='http://docs.google.com/a/'.$data[0]["domaine"].'#';
				}
				//				$adresse_organisme = $data[0]["adresse1"]  . '<br />' . $data[0]["code_postal"] . ' ' . $data[0]["ville"] . ' (' . $data[0]["code_iso"].')';
				$fiche_organisme = '<font color="Tomato"> <b>' . $nom_organisme . '</b>';
			}
		}
			
		// Utilisateur
		include (atkconfig("atkroot") . "version.inc");
		$title = '<b>' . $wikiassoc_user . ' avec' . href("http://www.wikistoma.org/wiki", atktext($wikiassoc_name), SESSION_NEW, false, 'target="_blank"')
		. ' <br /> version : ' . $wikiassoc_version . ' ' . $wikiassoc_state . ' du ' . $wikiassoc_date . '<br />'.
		href("http://www.atk-framework.com/wiki/ATK", atktext("Atk"), SESSION_NEW, false, 'target="_blank"') .'('. atkversion() . ')</b>';

		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$traitements_o_n = $g_sessionManager->getValue("traitements_o_n", "globals");
		$en_travaux_o_n = $g_sessionManager->getValue("en_travaux_o_n", "globals");
		$tracer_mysqldb_query_o_n = $g_sessionManager->getValue("tracer_mysqldb_query_o_n", "globals");
		$golf_o_n = $g_sessionManager->getValue("golf_o_n", "globals");
		$biodiversite_o_n = $g_sessionManager->getValue("biodiversite_o_n", "globals");
		global $g_user;
		if ($g_user["name"] != 'administrator') {
			$db = & atkGetDb();
			$query = "SELECT p.traitements_o_n, i.sexe, au.id_individu as id_individu, au.courriel as courriel, i.calendrier as calendrier, calendrier_contacts_url, calendrier_contacts_refresh,
				calendrier_rencontres_url, calendrier_rencontres_refresh, i.prenom as prenom , i.nom as nom ,i.identifiant_google,
			i.site_internet as site_internet, i.telephone_fixe as telephone_fixe, i.telephone_mobile as telephone_mobile , i.date_naissance as date_naissance, 
			au.biodiversite_o_n as biodiversite_o_n
			from app_utilisateur au, individu i , app_profil p
			where au.id=" . $g_user["id"] . " and au.id_individu=i.id and au.id_profil=p.id"  ;
			$row = $db->getrows($query);
			$idutilisateur = $row[0]["id_individu"];
			$sexe_utilisateur = $row[0]["sexe"];
			$courriel_utilisateur = $row[0]["courriel"];
			$calendrier_utilisateur = $row[0]["calendrier"];
			$calendrier_contacts_url_utilisateur = $row[0]["calendrier_contacts_url"];
			$calendrier_contacts_refresh_utilisateur = $row[0]["calendrier_contacts_refresh"];
			$calendrier_rencontres_url_utilisateur = $row[0]["calendrier_rencontres_url"];
			$calendrier_rencontres_refresh_utilisateur = $row[0]["calendrier_rencontres_refresh"];
			$traitement_o_n=$row[0]["traitements_o_n"];
			(strlen($row[0]["identifiant_google"])>0 ) ? $identifiant_google_o_n='1' : $identifiant_google_o_n='0';
			$option_biodiversite_o_n = $row[0]["biodiversite_o_n"];
			$site_internet_utilisateur = $row[0]["site_internet"];
			$telephone_fixe_utilisateur =$row[0]["telephone_fixe"];
			//			$telephone_fixe_utilisateur ='<a href="callto://'. $telephone_fixe_utilisateur.'+type=phone" ></a>';
			$telephone_mobile_utilisateur = $row[0]["telephone_mobile"];
			//						$telephone_mobile_utilisateur ='<a href="callto://'. $telephone_mobile_utilisateur.'+type=phone" ></a>';
			$data = $db->getrows("SELECT adresse1, adresse2, code_postal, ville, code_iso
			from individu_lieu il, lieu l, type_cp_ville_pays cp, type_pays p
			where il.id_individu=$idutilisateur and il.adresse_defaut_o_n='1'
			and il.id_lieu=l.id
			and l.id_ville=cp.id
			and cp.id_pays=p.id");
			if (!empty($data[0]["ville"] ))
			{$adresse_utilisateur = $data[0]["adresse1"] . '<br />'  . $data[0]["code_postal"] . ' ' . $data[0]["ville"] . ' (' . $data[0]["code_iso"].')';
			$qr_adresse_utilisateur=$data[0]["adresse1"] . ','  . $data[0]["code_postal"] . ',' . $data[0]["ville"] . ',' . $data[0]["code_iso"];}
			else {$adresse_utilisateur="";
			$adresse_utilisateur="";}
				
			$nomutilisateur = '<font color="Tomato"> <b>' . $row[0]["prenom"] . ' ' . $row[0]["nom"] . '</b>';
			$qr_nom_utilisateur=$row[0]["nom"] . ' , '. $row[0]["prenom"];
			$qr_anniversaire=substr($row[0]["date_naissance"], 0,10);
			$qr_anniversaire_utilisateur=str_replace('-', '', $qr_anniversaire);
				
				
			$idutilisateurutilisateur=$g_user["id"];
		}
			
		if ($topmenu=="main")
		{
			$accueil = href("index.php", '<img src="./atk/themes/t3skin/images/logo.gif" alt="" align=center border=0 hspace=20 vspace=3>', SESSION_DEFAULT, false, 'target="_top"');
			$this->menuitem($accueil, "", "main", true);
			$this->menuitem($title, "", "main", true);
		}
		if ($topmenu=="Google")
		{
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Google-icon.png" alt="Dashboard" title="Dashboard"></img>'." Dashboard";
			$this->menuitem($menu, "https://www.google.com/dashboard/b/0/", "Google", true);
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google_icon.png" alt="Composants google" title="Composants google"></img>'." Composants";
			$this->menuitem($menu, "http://www.google.fr/intl/fr/optionsl", "Google", true);
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Gmail-icon.png" alt="Gmail" title="Gmail"></img>'." Gmail";
			$this->menuitem($menu, "http://mail.google.com/mail/u/0/?hl=fr", "Google", true);
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Google-Plus-1-icon.png" alt="Google +" title="Google +"></img>'." Google +";
			$this->menuitem($menu, "http://plus.google.com/", "Google", true);
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/contactgoogle.png" alt="Contacts Google" title="Contacts Google"></img>'." Contacts";
			$this->menuitem("$menu","target_menu"."menu.php?atkmenutop=contacts_google", "Google", true);
			$menu=	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/albumpicasa.png" alt="Albums Google" title="Albums Google"></img>'." Albums";
			$this->menuitem("$menu", "target_menu"."menu.php?atkmenutop=albums_google", "Google", true);
		}

		if ($topmenu=="Utilisateur")

		{

			//TOP
			// Utilisateur

			$data = $db->getrows("SELECT count(id) as nombre from individu_activite where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_activite = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_attribut where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_attribut = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_bookmark where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_bookmark = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_carte_golf where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_carte_golf = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_competence where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_competence = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_individu=" . $idutilisateur . " or id_contact=" . $idutilisateur . " ");
			$nombre_utilisateur_contact = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotisation where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_cotisation = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotorep where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_cotorep = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_document where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_document = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from organisme_document where id_individu_auteur=" . $idutilisateur . " ");
			$nombre_utilisateur_document_auteur = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_envoi_groupe where id_utilisateur=" . $idutilisateur . " ");
			$nombre_utilisateur_envoi_groupe = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from app_pb_report where id_creation=" . $g_user["id"]  ."");
			$nombre_utilisateur_demande = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_fonction where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_fonction = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_historique = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_immatriculation where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_immatriculation= $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_inscription where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_inscription = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_lieu where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_lieu = $data[0]["nombre"];

			$data = $db->getrows("SELECT count(id) as nombre from app_utilisateur_liste_organismes  where id_utilisateur=" . $g_user["id"]  . " ");
			$nombre_utilisateur_liste_organismes = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from app_utilisateur_liste  where id_utilisateur=" . $g_user["id"]  . " ");
			$nombre_utilisateur_liste = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from tmp_copier_coller  where id_utilisateur=" . $g_user["id"]  . " ");
			$nombre_utilisateur_presse_papier = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_rencontre where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_rencontre = $data[0]["nombre"];
			//		$data = $db->getrows("SELECT count(id) as nombre from app_sauvegarde where id_individu=" . $idutilisateur . " ");
			//		$nombre_utilisateur_sauvegarde = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from todo where id_individu_a_faire=" . $idutilisateur . " ");
			$nombre_utilisateur_tache_a_faire = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from todo where id_creation=" . $g_user["id"] . " ");
			$nombre_utilisateur_tache_creees = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_web where id_individu=" . $idutilisateur . " ");
			$nombre_utilisateur_web = $data[0]["nombre"];

			$qr_utilisateur="MECARD:N:".$qr_nom_utilisateur.";TEL:".$telephone_fixe_utilisateur.";TEL:".$telephone_mobile_utilisateur.";BDAY:".$qr_anniversaire_utilisateur.";URL:".$site_internet_utilisateur.
";EMAIL:".$courriel_utilisateur.";ADR:".$qr_adresse_utilisateur.";;";
			$qr_utilisateur=str_replace(' ', '+', $qr_utilisateur);
			$qr_utilisateur=str_replace("'", "/'", $qr_utilisateur);
			$qr_utilisateur=utf8_encode($qr_utilisateur);
			$qr_utilisateur = href("index.php", '<img src="http://chart.apis.google.com/chart?cht=qr&chs=150x150&chl='.$qr_utilisateur.'" class="gwt-Image" style="">', SESSION_DEFAULT, false, 'target="_top"');

			// Nom Individu
			$data=$node->descripteur_individu($idutilisateur,'n','n','0','menu') ;
			$this->menuitem('!'.$data, null, "Utilisateur", true);
			/*
			 $this->menuitem($nomutilisateur, dispatch_url("individu.individu", "edit", array (
			 "atkselector" => "individu.id='" . $idutilisateur . "'"
			 )), "Utilisateur", true);

			 // Adresse u
			 if (!empty($adresse_utilisateur))
			 {$this->menuitem($adresse_utilisateur, dispatch_url("individu.individu", "googlemap", array (
			 "id" => "" . $idutilisateur . ""
			 )), "Utilisateur", true);}
			 if (!empty($telephone_fixe_utilisateur))		$this->menuitem($telephone_fixe_utilisateur, "target_blanktel:".$telephone_fixe_utilisateur.";","Utilisateur", true);
			 if (!empty($telephone_mobile_utilisateur)) $this->menuitem($telephone_mobile_utilisateur,"target_blanktel:".$telephone_mobile_utilisateur.";","Utilisateur", true);
			 if (!empty($courriel_utilisateur))		$this->menuitem($courriel_utilisateur, dispatch_url("individu.contact_i", "add", array (
			 "idcontactant" => "$idutilisateur",
			 "idcontacte" => "$idutilisateur",
			 "atgemail" => "$courriel_utilisateur"
			 )), "Utilisateur", true);
			 if (!empty($site_internet_utilisateur))			$this->menuitem($site_internet_utilisateur, $site_internet_utilisateur, "Utilisateur", true);

			 if (!empty ($calendrier_utilisateur)) {
				$this->menuitem("Calendrier", $calendrier_utilisateur, "Utilisateur", true);
				}
				if (!empty ($calendrier_contacts_url_utilisateur)) {
				$this->menuitem("Calendrier_contacts_u"."#".$calendrier_contacts_refresh_utilisateur, $calendrier_contacts_url_utilisateur, "Utilisateur", true);
				}
				*/
			if (!empty ($calendrier_rencontres_url_utilisateur)) {

				$this->menuitem("Calendrier_rencontres_u", $calendrier_rencontres_url_utilisateur, "Utilisateur", true);
				$this->menuitem('!<b><font color="Coral">('.$calendrier_rencontres_refresh_utilisateur.')</font></b>', null, "Utilisateur", true);
				$this->menuitem("(Rafraîchir)", dispatch_url("individu.individu", "rafraichir_calendrier_rencontres", array(
			"atkselector" => "individu.id='" . $idutilisateur . "'"
			)), "Utilisateur", true);

			}

			/*

			if (!empty($adresse_utilisateur)) 	$this->menuitem("Enveloppe", dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "individu.id='" . $idutilisateur . "'",
			"id" => $id_organisme,
			"atkfilter" => "v_individu_lieu.id='" . $idutilisateur . "'",
			"atkdoctpl" => "enveloppe_individu.odt",
			"atkdoctpl_prefix_id" => "0",
			"atkcode" => "2"
			)), "Utilisateur", true);
			*/
			$this->menuitem("Comptes Google", "http://www.google.com/accounts/b/0/ManageAccount?service=mail&hl=fr", "Utilisateur", true);


			$this->menuitem("-", "", "Utilisateur", true);

			// Activités
			$this->menuitem("Activités_u"."#".$nombre_utilisateur_activite, dispatch_url("individu.activite_i", "admin", array(
			"atkfilter" => "individu_activite.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Bloc Notes
			if ($g_user["name"] != 'administrator') {
				$data1 = $db->getrows("SELECT id from todo where blocnotes_o_n='1' and id_individu_a_faire=" . $idutilisateur . " ");
				$id_bloc = $data1[0]["id"];
				if (!empty ($id_bloc)) {
					$this->menuitem("Bloc_Notes_u", dispatch_url("todo.todo", "edit", array (
					"atkselector" => "todo.id='" . $id_bloc . "'"
					)), "Utilisateur", true);
				}
			}
			// Biodiversité_observations
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation where id_observateur=". $idutilisateur . " ");
			$this->menuitem("-/+biodiversité_observations_u"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation", "admin", array(
			"atkfilter" => "biodiversite_observation.id_observateur='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Biodiversité_observations_détail
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation_detail  where id_observation in (select id from biodiversite_observation where id_observateur=". $idutilisateur . ")");
			$this->menuitem("?biodiversité_observations_détails_u"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation_detail", "admin", array(
			"atkfilter" => "biodiversite_observation_detail.id_observation in (select id from biodiversite_observation where id_observateur=". $idutilisateur . ")"
			)), "Utilisateur", true);


			// Blogs
			$this->menuitem("Blogs_u"."#".$nombre_utilisateur_web, dispatch_url("individu.web_i", "admin", array (
			"atkfilter" => "individu_web.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Contacts
			$this->menuitem("Contacts_u"."#".$nombre_utilisateur_contact, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_contact='" . $idutilisateur . "' or individu_contact.id_individu='" . $idutilisateur . "' "
			)), "Utilisateur", true);
			// Contactant
			$this->menuitem("/Contactant_u", dispatch_url("individu.contact_i", "add", array (
			//		"atkfilter" =>"individu_contact.id_contact='".$idutilisateur."'",
			"idcontactant" => "$idutilisateur",
			"idcontacte" => "$individuid"
			)), "Utilisateur", true);

			// Contacté
			$this->menuitem("Contacté_u", dispatch_url("individu.contact_i", "add", array(
			"idcontactant" => "$individuid",
			"idcontacte" => "$idutilisateur"
			)), "Utilisateur", true);

			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where (id_contact=" . $idutilisateur . " or id_individu=" . $idutilisateur . " ) and date_realisee is null");
			$nombre = $data[0]["nombre"];
			// Contacts à faire
			$this->menuitem("/Contacts_a_traiter_u"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => " ( individu_contact.id_contact='" . $idutilisateur . "' or individu_contact.id_individu='" . $idutilisateur . "' )  and individu_contact.date_realisee is null  "
			)), "Utilisateur", true);
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where ( id_contact=" . $idutilisateur . " or id_individu=" . $idutilisateur . " ) and attente_reponse_o_n='1'");
			$nombre = $data[0]["nombre"];
			// Contacts à faire
			$this->menuitem("Contacts_attente_u"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => " ( individu_contact.id_contact='" . $idutilisateur . "'  or individu_contact.id_individu='" . $idutilisateur . "' ) and individu_contact.attente_reponse_o_n='1'  "
			)), "Utilisateur", true);

			$data = $db->getrows("SELECT count(id_type_correspondant) as nombre from individu_correspondant where ( id_individu=" . $idutilisateur . " ) group by id_type_correspondant");
			$nombre = count($data);
			$this->menuitem("-/+*Correspondants <<"."#".$nombre, dispatch_url("individu.v_individu_correspondant", "admin", array (
			"atkfilter" => "v_individu_correspondant.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Correspondants
			$data = $db->getrows("SELECT count(id) as nombre from individu_correspondant where ( id_individu=" . $idutilisateur . " ) ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("?Correspondants >>"."#".$nombre, dispatch_url("individu.correspondant", "admin", array (
			"atkfilter" => "individu_correspondant.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Demandes i
			$this->menuitem("Demandes_u"."#".$nombre_utilisateur_demande, dispatch_url("application.demande", "admin", array (
			"atkfilter" => "app_pb_report.id_creation='" . $g_user["id"]  . "'"
			)), "Utilisateur", true);
			// Documents
			$this->menuitem("Documents_u"."#".$nombre_utilisateur_document, dispatch_url("individu.document_i", "admin", array (
			"atkfilter" => "individu_document.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Documents auteur
			$this->menuitem("Documents_auteur_u"."#".$nombre_utilisateur_document_auteur, dispatch_url("organisme.document", "admin", array (
			"atkfilter" => "organisme_document.id_individu_auteur='" . $idutilisateur . "'"
			)), "Utilisateur", true);

			// Envois groupés
			$this->menuitem("Envoi_groupe_utilisateur_u"."#".$nombre_utilisateur_envoi_groupe, dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_utilisateur='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Historiques

			//http://www.wikistoma.org/association/dispatch.php?atknodetype=pim.pim&atkaction=pim&atklevel=-1&atkprevlevel=0&
			$this->menuitem("Etp (Coeur)", dispatch_url("etp.coeur", "admin", array (
			"atkfilter" => "etp_coeur.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// etp coeur
			$this->menuitem("Etp (Poids)", dispatch_url("etp.poids", "admin", array (
			"atkfilter" => "etp_poids.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);

			$this->menuitem("Gadgets"."#".$nombre_utilisateur_document_auteur, dispatch_url("individu.gadget_i", "gadget_i"), "Utilisateur", true);

			// Géolocalisation des individus
		
			$this->menuitem("Géolocalisation individus", dispatch_url("organisme.organisme", "geolocalisation_inscrits", array (
					"type" => "administrateur"
			)), "Utilisateur", true);
			
					
			$this->menuitem("Historique_u"."#".$nombre_utilisateur_historique, dispatch_url("profil.recent_use", "admin", array (
			"atkfilter" => "app_recent_use.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Immatriculations
			$this->menuitem("Immatriculations_u"."#".$nombre_utilisateur_immatriculation, dispatch_url("individu.immatriculation_i", "admin", array (
			"atkfilter" => "individu_immatriculation.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);

			// Listes
			$this->menuitem("Listes_organismes"."#".$nombre_utilisateur_liste_organismes, dispatch_url("profil.liste_organismes", "admin", array (
			"atkfilter" => "app_utilisateur_liste_organismes.id_utilisateur='" . $g_user["id"] . "'",
			"atklimit" => "10000"
			)), "Utilisateur", true);

			// Listes
			$this->menuitem("Listes_u"."#".$nombre_utilisateur_liste, dispatch_url("profil.liste", "admin", array (
			"atkfilter" => "app_utilisateur_liste.id_utilisateur='" . $g_user["id"] . "'",
			"atklimit" => "10000"
			)), "Utilisateur", true);
			// Marque-pages
			$this->menuitem("Marque-pages_u"."#".$nombre_utilisateur_bookmark, dispatch_url("individu.bookmark_i", "admin", array (
			"atkfilter" => "individu_bookmark.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			// Préférences
			$this->menuitem("Préférences_u", dispatch_url("profil.userprefs", "edit", array (
			"atkselector" => "app_utilisateur.id='" . $g_user["id"] . "'"
			)), "Utilisateur", true);
			// Presse-papier
			$this->menuitem("Presse-papier_u"."#".$nombre_utilisateur_presse_papier, dispatch_url("profil.copier_coller", "admin", array (
			"atkfilter" => "tmp_copier_coller.id_utilisateur='" . $g_user["id"] . "'",
			"atklimit" => "10000"
			)), "Utilisateur", true);
			// Rappels
			$this->menuitem("Rappels_u", dispatch_url("pim.pim", "pim"), "Utilisateur", true);
			// Règles de confidentialité
			$this->menuitem("Règles de confidentialité_u", dispatch_url("application.globales", "confidentialite"), "Utilisateur", true);
			// Rencontres
			$this->menuitem("Rencontres_u"."#".$nombre_utilisateur_rencontre, dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_individu='" . $idutilisateur . "'"
			)), "Utilisateur", true);
			/*			// Sauvegardes u
			 $this->menuitem("Sauvegardes_u"."#".$nombre_utilisateur_sauvegarde, dispatch_url("application.sauvegarde", "admin", array (
			 "atkfilter" => "app_sauvegarde.id_individu ='" . $idutilisateur . "'"
			 )), "Utilisateur", true);
			 */
			// Tâches
			$this->menuitem("Taches_u_af"."#".$nombre_utilisateur_tache_a_faire, dispatch_url("todo.todo", "admin", array (
			"atkfilter" => "todo.id_individu_a_faire='" . $idindividu . "'"
			)), "Utilisateur", true);
			$this->menuitem("Taches_u_creees"."#".$nombre_utilisateur_tache_creees, dispatch_url("todo.todo", "admin", array (
			"atkfilter" => "todo.id_creation='" . $g_user["id"] . "'"
			)), "Utilisateur", true);
			$this->menuitem("-", "", "Utilisateur", true);
			$this->menuitem($qr_utilisateur, "", "Utilisateur", true);
			//
			$this->menuitem("-", "", "main", true);
		}
		if ($topmenu=="Taxons")
		{
			//TOP
			// Taxons

			// Dernier taxon sélectionné
			$taxonid = 0;
			$user = getUser();
			$id = $user["id"];
			if (isset ($id)) {
				$db = & atkGetDb();

				$id_individu=$g_utilisateur_individu[$id];
				
		//		$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
		//		$id_individu = $data[0]["id_individu"];
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='taxon' order by date_recent_use desc");
				if (count($data) > 0) {
					$taxonid = $data[0]["id_entite"];
					$data = $db->getrows("select inpn_nom_complet from biodiversite_taxinomie where id=$taxonid");
					$nom_complet = $data[0]["inpn_nom_complet"];

					$fiche_taxon = '<font color="Tomato"> <b>' . $nom_complet . '</b>';
				}
			}

			$this->menuitem("Rechercher_o", dispatch_url("biodiversite.taxinomie", "admin"), "Taxons", true);
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='taxon' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];
			// Récents
			$this->menuitem("Récents_o"."#".$nombre, dispatch_url("profil.recent_use", "admin", array(
			"atkfilter" => "app_recent_use.type_entite='taxon' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Taxons", true);
			// Créer
			$this->menuitem("Créer_o", dispatch_url("biodiversite.taxinomie", "add"), "Taxons", true);
			//
			$this->menuitem("-", null, "Taxons", true);
			// Nom Taxon

			$data=$node->descripteur_biodiversite_taxinomie($taxonid,null,$destination='affichage',$aide_o_n='o',$image_o_n='o');
			$this->menuitem('!'.$data, null, "Taxons", true);

			$data=$node->descripteur_biodiversite_ascendance($taxonid, $destination='affichage');
			$this->menuitem('!'.$data, null, "Taxons", true);
			$data=$node->descripteur_biodiversite_web_info($taxonid,"taxinomie");
			$this->menuitem('!'.$data, null, "Taxons", true);
			$data=$node->descripteur_biodiversite_taxons_inpn($taxonid,"taxinomie");
			$this->menuitem('!'.$data, null, "Taxons", true);
		}

		if ($topmenu=="Organismes")
		{
			//TOP
			// Organismes

			$this->menuitem("Rechercher_o", dispatch_url("organisme.organisme", "admin"), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='organisme' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];
			// Récents
			$this->menuitem("Récents_o"."#".$nombre, dispatch_url("profil.recent_use", "admin", array(
			"atkfilter" => "app_recent_use.type_entite='organisme' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Organismes", true);
			// Créer
			$this->menuitem("Créer_o", dispatch_url("organisme.organisme", "add"), "Organismes", true);
			//
			$this->menuitem("-", null, "Organismes", true);
			// Nom Organisme

			$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
			$this->menuitem('!'.$data, null, "Organismes", true);
			/*
			 $this->menuitem("@fiche_organisme_o@".$fiche_organisme, dispatch_url("organisme.organisme", "edit", array (
			 "atkselector" => "organisme.id='" . $organismeid . "'"
			 )), "Organismes", true);

			 if (!empty($adresse_organisme))	$this->menuitem("@adresse_organisme_o@".$adresse_organisme, dispatch_url("organisme.organisme", "googlemap", array (
			 "id" => "" . $organismeid . ""
			 )), "Organismes", true);
			 if (!empty($telephone_organisme))
			 {$this->menuitem("@telephone_organisme_o@".$telephone_organisme, "target_blanktel:".$telephone_organisme.";","Organismes", true);}
			 if (!empty($site_internet_organisme))			$this->menuitem("@web_organisme_o@".$site_internet_organisme, $site_internet_organisme, "Organismes", true);

			 if (!empty ($calendrier_organisme)) {
				$this->menuitem("Calendrier_o", $calendrier_organisme, "Organismes", true);
				}
				*/
			if (!empty ($calendrier_contacts_url_organisme)) {
				$this->menuitem("Calendrier_contacts_o", $calendrier_contacts_url_organisme, "Organismes", true);
				$this->menuitem('!<b><font color="Coral">('.$calendrier_contacts_refresh_organisme.')</font></b>', null, "Organismes", true);
				$this->menuitem("(Rafraîchir)", dispatch_url("organisme.organisme", "rafraichir_calendrier_contacts", array(
			"atkselector" => "organisme.id='" . $organismeid . "'"
			)), "Organismes", true);}

			if (!empty ($calendrier_rencontres_url_organisme)) {
				$this->menuitem("Calendrier_rencontres_o<br />", $calendrier_rencontres_url_organisme, "Organismes", true);
				$this->menuitem('!<b><font color="Coral">('.$calendrier_rencontres_refresh_organisme.')</font></b>', null, "Organismes", true);
				$this->menuitem("(Rafraîchir)", dispatch_url("organisme.organisme", "rafraichir_calendrier_rencontres", array(
			"atkselector" => "organisme.id='" . $organismeid . "'"
			)), "Organismes", true);
			}
			/*
			 if (!empty($adresse_organisme))				$this->menuitem("Enveloppe_o", dispatch_url("organisme.v_organisme_lieu", "document", array (
			 "atkselector" => "organisme.id='" . $organismeid . "'",
			 "id" => "'" . $organismeid . "'",
			 "atkfilter" => "v_organisme_lieu.id='" . $organismeid . "'",
			 "atkdoctpl" => "enveloppe_organisme.odt",
			 "atkdoctpl_prefix_id" => "1",
			 "atkcode" => "2"
			 )), "Organismes", true);
				if (!empty ($google_apps)) {
				$this->menuitem("Google Apps",'target_blank'.$google_apps, "Organismes", true);

				}
				/*
				$this->menuitem("vcard_o", dispatch_url("organisme.organisme", "vcard", array (
				"organisme.id" =>"$organismeid" )), "Organismes", true);
				*/
			$this->menuitem("-", "", "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_lieu where id_organisme=" . $organismeid . " ");
			$nombre_organisme_adresse = $data[0]["nombre"];

			// Adresses
			$this->menuitem("Adresses_o"."#".$nombre_organisme_adresse, dispatch_url("organisme.organisme_lieu", "admin", array (
			"atkfilter" => "organisme_lieu.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);

			// Annuaire téléphonique
			$this->menuitem("Annuaire téléphonique_o",
		 "http://www.pagesjaunes.fr/quidonc/quiportecenom.do?nom=" . $nom_organisme , "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from individu_web where id_organisme=" . $organismeid . " ");
			$nombre_organisme_web = $data[0]["nombre"];
			// Notoriété o
			$this->menuitem("Notoriete_o", "http://www.google.fr/search?q=" . $nom_organisme . "&ie=utf-8&oe=utf-8&aq=t", "Organismes", true);
			if($option_biodiversite_o_n=='1')
			{
				//  Observations biodiversite
				$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation where  id_organisme=" . $organismeid . " ");
				$nombre_observations = $data[0]["nombre"];
				$this->menuitem("-/+Observations_o"."#".$nombre_observations, dispatch_url("biodiversite.observation", "admin", array (
			"atkfilter" => "biodiversite_observation.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);

			//  Observations biodiversite
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation_detail where  id_observation in (
				select id from biodiversite_observation where id_organisme=" . $organismeid . " )");
			$nombre_observations = $data[0]["nombre"];
			$this->menuitem("?Biodiversité_Observations_détails (commanditaire)"."#".$nombre_observations, dispatch_url("biodiversite.observation_detail", "admin", array (
			"atkfilter" => "biodiversite_observation_detail.id_observation in (
				select id from biodiversite_observation where id_organisme=" . $organismeid . " )"
				)), "Organismes", true);
					
				//  Observations biodiversite
				$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation where  id_organisme_observateur=" . $organismeid . " ");
				$nombre_observations = $data[0]["nombre"];
				$this->menuitem("-/+Observations_observateur"."#".$nombre_observations, dispatch_url("biodiversite.observation", "admin", array (
			"atkfilter" => "biodiversite_observation.id_organisme_observateur='" . $organismeid . "'"
			)), "Organismes", true);

			//  Observations biodiversite
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation_detail where  id_observation in (
				select id from biodiversite_observation where id_organisme_observateur=" . $organismeid . " )");
			$nombre_observations = $data[0]["nombre"];
			$this->menuitem("?Biodiversité_Observations_détails (observateur)"."#".$nombre_observations, dispatch_url("biodiversite.observation_detail", "admin", array (
			"atkfilter" => "biodiversite_observation_detail.id_observation in (
				select id from biodiversite_observation where id_organisme_observateur=" . $organismeid . " )"
				)), "Organismes", true);
					
					
				/*
				 //  Requêtes biodiversite
				 $data = $db->getrows("SELECT count(id) as nombre from biodiversite_requete where  id_organisme=" . $organismeid . " ");
				 $nombre_observations = $data[0]["nombre"];
				 $this->menuitem("Requetes_o"."#".$nombre_observations, dispatch_url("biodiversite.requete", "admin", array (
				 "atkfilter" => "biodiversite_requete.id_organisme='" . $organismeid . "'"
				 )), "Organismes", true);
				 */
					
				//  Points Observations biodiversite
				$data = $db->getrows("SELECT count(id) as nombre from biodiversite_point_observation where  id_organisme=" . $organismeid . " ");
				$nombre_points_observations = $data[0]["nombre"];
				$this->menuitem("/Points_observations_o"."#".$nombre_points_observations, dispatch_url("biodiversite.point_observation", "admin", array (
			"atkfilter" => "biodiversite_point_observation.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_parcours_observation where  id_organisme=" . $organismeid . " ");
			$nombre_parcours_observations = $data[0]["nombre"];
			$this->menuitem("Parcours_observations_o"."#".$nombre_parcours_observations, dispatch_url("biodiversite.parcours_observation", "admin", array (
			"atkfilter" => "biodiversite_parcours_observation.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			}

			// Blogs
			$this->menuitem("Blogs_o"."#".$nombre_organisme_web, dispatch_url("individu.web_i", "admin", array (
			"atkfilter" => "individu_web.id_organisme='" . $organismeid . "' "
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_calendrier where id_organisme=" . $organismeid . " ");
			$nombre_organisme_web = $data[0]["nombre"];
			// Blogs
			$this->menuitem("Calendriers_o"."#".$nombre_organisme_web, dispatch_url("organisme.calendrier", "admin", array (
			"atkfilter" => "organisme_calendrier.id_organisme='" . $organismeid . "' "
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_document_communication where id_organisme=" . $organismeid . " ");
			$nombre_organisme_document_communication = $data[0]["nombre"];
			// Communications o
			$this->menuitem("Communications_o"."#".$nombre_organisme_document_communication, dispatch_url("organisme.document_communication", "admin", array (
			"atkfilter" => "organisme_document_communication.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			// Compétences o
			$data = $db->getrows("SELECT count(id) as nombre from organisme_competence where id_organisme=" . $organismeid . " ");
			$nombre = $data[0]["nombre"];

			$this->menuitem("Competences_o"."#".$nombre, dispatch_url("organisme.competence_o", "admin", array (
			"atkfilter" => "organisme_competence.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);


			// Comptabilité
			$this->menuitem("Comptabilite_o", "target_menu".'menu.php?atkmenutop=Comptabilite_o', "Organismes", true);
	//			$this->menuitem("Traitements", "target_menu".'menu.php?atkmenutop=Traitements', "Organismes", true);
				
			$data = $db->getrows("SELECT count(id)  as nombre from individu_contact where id_organisme_contactant
		 ='" . $organismeid . "' or id_organisme_contacte ='" . $organismeid . "'");
			$nombre_organisme_contact_o = $data[0]["nombre"];
			// Contacts$qr_utilisateur
			$this->menuitem("Contacts_o"."#".$nombre_organisme_contact_o, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_organisme_contactant ='" . $organismeid . "'
																		or id_organisme_contacte ='" . $organismeid . "' "
																		)), "Organismes", true);
																			

																		$data = $db->getrows("SELECT count(id) as nombre from individu_contact where( individu_contact.id_organisme_contactant ='" . $organismeid . "'
																		or id_organisme_contacte ='" . $organismeid . "' ) and date_realisee is null");
																		$nombre = $data[0]["nombre"];
																			
																		// Contacts à faire
																		$this->menuitem("/Contacts_a_traiter_o"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => " ( individu_contact.id_organisme_contactant ='" . $organismeid . "'
																		or id_organisme_contacte ='" . $organismeid . "' ) and date_realisee is null "
																		)), "Organismes", true);

																		$data = $db->getrows("SELECT count(id) as nombre from individu_contact where ( individu_contact.id_organisme_contactant ='" . $organismeid . "'
																		or id_organisme_contacte ='" . $organismeid . "' ) and attente_reponse_o_n='1' ");
																		$nombre = $data[0]["nombre"];
																		// Contacts à faire
																		$this->menuitem("Contacts_attente_o"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
						"atkfilter" => " ( individu_contact.id_organisme_contactant ='" . $organismeid . "'
																		or id_organisme_contacte ='" . $organismeid . "' ) and attente_reponse_o_n='1' "
																		)), "Organismes", true);
																		// Contrats o
																		$data = $db->getrows("SELECT count(id) as nombre from organisme_contrat where id_organisme=" . $organismeid . " ");
																		$nombre_organisme_contrat = $data[0]["nombre"];
																		$this->menuitem("Contrats_souscripteur"."#".$nombre_organisme_contrat, dispatch_url("organisme.contrat", "admin", array (
			"atkfilter" => "organisme_contrat.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);

			// Contrats o
			$data = $db->getrows("SELECT count(id) as nombre from organisme_contrat where id_organisme_contrat=" . $organismeid . " ");
			$nombre_organisme_contrat = $data[0]["nombre"];
			$this->menuitem("Contrats_contractant"."#".$nombre_organisme_contrat, dispatch_url("organisme.contrat", "admin", array (
			"atkfilter" => "organisme_contrat.id_organisme_contrat='" . $organismeid . "'"
			)), "Organismes", true);


			$data = $db->getrows("SELECT count(id) as nombre from organisme_cotisation where id_organisme=" . $organismeid . " ");
			$nombre_organisme_cotisation_organisme = $data[0]["nombre"];
			// Cotisations o
			$this->menuitem("-/+*Cotisations <<"."#".$nombre_organisme_cotisation_organisme, dispatch_url("organisme.cotisation", "admin", array (
			"atkfilter" => "organisme_cotisation.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			

			// Cotisations
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotisation where id_organisme=" . $organismeid . " ");
			$nombre_organisme_cotisation_individu = $data[0]["nombre"];
			// Cotisations Détails
			$this->menuitem("?Cotisations >>"."#".$nombre_organisme_cotisation_individu, dispatch_url("individu.cotisation_i", "admin", array(
			//			"atkfilter" => " individu_cotisation.id_cotisation IN (select id from organisme_cotisation where id_organisme='" . $organismeid . "')"
			"atkfilter" => " individu_cotisation.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$this->menuitem(" TabVoir", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Cotisations")), "Organismes", true);

			// Cotisations
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotisation where id_organisme_cotisant=" . $organismeid . " ");
			$nombre_organisme_cotisation_individu = $data[0]["nombre"];
			// Cotisations Détails
			$this->menuitem("Cotisations_payées_o"."#".$nombre_organisme_cotisation_individu, dispatch_url("individu.cotisation_i", "admin", array(
			"atkfilter" => " individu_cotisation.id_organisme_cotisant='" . $organismeid . "'"
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_document where id_organisme=" . $organismeid . " ");
			$nombre_organisme_document = $data[0]["nombre"];
			// Documents o
			$this->menuitem("Documents_o"."#".$nombre_organisme_document, dispatch_url("organisme.document", "admin", array (
			"atkfilter" => "organisme_document.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_document_officiel where id_organisme=" . $organismeid . " ");
			$nombre_organisme_document_officiel = $data[0]["nombre"];
			// Documents Officiels o
			$this->menuitem("Documents_Officiels_o"."#".$nombre_organisme_document_officiel, dispatch_url("organisme.document_officiel", "admin", array (
			"atkfilter" => "organisme_document_officiel.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_domaine where id_organisme=" . $organismeid . " ");
			$nombre_organisme_domaine = $data[0]["nombre"];
			// Domaines internet o
			$this->menuitem("Domaines_internet_o"."#".$nombre_organisme_domaine, dispatch_url("organisme.domaine", "admin", array (
			"atkfilter" => "organisme_domaine.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);

			// Enveloppes
			$this->menuitem("Enveloppe_o", dispatch_url("organisme.v_organisme_lieu", "document", array (
			"atkselector" => "organisme.id='" . $organismeid . "'",
			"id" => "'" . $organismeid . "'",
			"atkfilter" => "v_organisme_lieu.id='" . $organismeid . "'",
			"atkdoctpl" => "enveloppe_organisme.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "2"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from individu_envoi_groupe where id_organisme_emetteur=" . $organismeid . " ");
			$nombre_organisme_envoi_groupe = $data[0]["nombre"];
			// Envois groupés
			$this->menuitem("Envoi_groupe_organisme"."#".$nombre_organisme_envoi_groupe, dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_organisme_emetteur='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(distinct id_fonction) as nombre from individu_fonction where id_organisme=" . $organismeid . " ");
			$nombre_organisme_fonction = $data[0]["nombre"];
			
			// Fonctions o
			$this->menuitem("-/+*Fonctions <<"."#".$nombre_organisme_fonction, dispatch_url("table.fonction", "admin", array (
			"atkfilter" => "type_fonction.id in (select individu_fonction.id_fonction from individu_fonction where id_organisme =$organismeid ) ",
					"id_organisme" => $organismeid
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from individu_fonction where id_organisme=" . $organismeid . " ");
			$nombre_organisme_fonction = $data[0]["nombre"];
			// Fonctions Détail
			$this->menuitem("?Fonctions >>"."#".$nombre_organisme_fonction, dispatch_url("individu.fonction_i", "admin", array (
			"atkfilter" => "individu_fonction.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			/*				$data = $db->getrows("SELECT count(id)  as nombre from individu_contact where id_individu
			 IN ( select distinct id_individu from individu_fonction where id_organisme ='" . $organismeid . "')
			 or individu_contact.id_contact IN ( select distinct id_individu from individu_fonction where id_organisme ='" . $organismeid . "')");
			 $nombre_organisme_contact_fonction = $data[0]["nombre"];
			 // Contacts fonctions
			 $this->menuitem("Contacts_fonctions"."#".$nombre_organisme_contact_fonction, dispatch_url("individu.contact_i", "admin", array (
			 "atkfilter" => "individu_contact.id_individu IN ( select distinct id_individu from individu_fonction where id_organisme ='" . $organismeid . "')
			 or individu_contact.id_contact IN ( select distinct id_individu from individu_fonction where id_organisme ='" . $organismeid . "') "
			 )), "Organismes", true);
			 */
			$this->menuitem("liste_fonctions_o", dispatch_url("organisme.organisme", "listeecran", array (
			"atkcode" => "2",
			"atkexport" => "n",
				"idfonctions" => "1,2,4,5,6,7,8,9,10",
			"id" => $organismeid
			)), "Organismes", true);
			// Globles
			$data = $db->getrows("SELECT count(id) as nombre from organisme_gazette where id_organisme=" . $organismeid . " ");
			$nombre_organisme_gazette = $data[0]["nombre"];
			// Gazettes(Organisme)
			$this->menuitem("gazettes_o"."#".$nombre_organisme_gazette, dispatch_url("organisme.gazette", "admin", array (
			"atkfilter" => "organisme_gazette.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			// Géolocalisation
			$this->menuitem("Geolocalisation_o", dispatch_url("organisme.organisme", "googlemap", array (
			"id" => "" . $organismeid . ""
			)), "Organismes", true);
			
			// Géolocalisation des inscrits et fonctions
			$this->menuitem("Géolocalisation inscrits", dispatch_url("organisme.organisme", "geolocalisation_inscrits", array (
					"type" => "organisme",
					"id" => "" . $organismeid . ""
			)), "Organismes", true);
				

			// Compétitions

			if ($golf_o_n==1)
			{		$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre where organisme_rencontre.id_organisme_parcours > 0 and id_organisme=" . $organismeid . " ");
			$nombre = $data[0]["nombre"];
			// Statistiques
			$this->menuitem("*Golf Compétitions"."#".$nombre, dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme_parcours > 0 && organisme_rencontre.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			}

			if ($golf_o_n==1)
			{		$data = $db->getrows("SELECT count(id) as nombre from organisme_serie_golf where  id_organisme=" . $organismeid . " ");
			$nombre = $data[0]["nombre"];
			// Statistiques
			$this->menuitem("*Golf Séries"."#".$nombre, dispatch_url("organisme.serie_golf", "admin", array (
			"atkfilter" => "organisme_serie_golf.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			}

			if ($golf_o_n==1)
			{		$data = $db->getrows("SELECT count(id) as nombre from organisme_tournoi where  id_organisme=" . $organismeid . " ");
			$nombre = $data[0]["nombre"];
			// Statistiques
			$this->menuitem("*Golf Tournois"."#".$nombre, dispatch_url("tournoi.tournoi", "admin", array (
			"atkfilter" => "organisme_tournoi.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			}



			// Groupes de travail
			$data = $db->getrows("SELECT count(id) as nombre from organisme_groupe_travail where  id_organisme=" . $organismeid . " and date_fin_groupe is null ");
			$nombre_organisme_groupe_travail_actif = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from organisme_groupe_travail where  id_organisme=" . $organismeid . "  ");
			$nombre_organisme_groupe_travail_archive = $data[0]["nombre"];

			$this->menuitem("Groupes_travail_o"."#".$nombre_organisme_groupe_travail_actif."/".$nombre_organisme_groupe_travail_archive, dispatch_url("organisme.groupe_travail", "admin", array (
			"atkfilter" => "organisme_groupe_travail.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_infolettre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_infolettre = $data[0]["nombre"];


			$data = $db->getrows("SELECT count(id) as nombre from organisme_image where id_type_entite='1' and  id_entite=" . $organismeid . " ");
			$nombre_organisme_image = $data[0]["nombre"];
			// Images (Organisme)
			$this->menuitem("images_o"."#".$nombre_organisme_image, dispatch_url("organisme.image", "admin", array (
			"atkfilter" => "organisme_image.id_entite='" . $organismeid . "'  "
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_immatriculation where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_immatriculation = $data[0]["nombre"];
			// Immatriculations o
			$this->menuitem("Immatriculations_o"."#".$nombre_organisme_immatriculation, dispatch_url("organisme.immatriculation", "admin", array (
			"atkfilter" => "organisme_immatriculation.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_infolettre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_infolettre = $data[0]["nombre"];
			// Infolettres o
			$this->menuitem("Infolettres_o"."#".$nombre_organisme_infolettre, dispatch_url("organisme.infolettre", "admin", array (
			"atkfilter" => "organisme_infolettre.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id_type_inscription) as nombre from v_organisme_inscription where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_inscription = $data[0]["nombre"];
			// Inscriptions o
			$this->menuitem("-/+*Inscriptions <<"."#".$nombre_organisme_inscription, dispatch_url("organisme.v_organisme_inscription", "admin", array (
			"atkfilter" => "v_organisme_inscription.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from individu_inscription where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_inscription = $data[0]["nombre"];
			// Inscriptions Détail
			$this->menuitem("?Inscriptions >>"."#".$nombre_organisme_inscription, dispatch_url("individu.inscription_i", "admin", array(
			"atkfilter" => "individu_inscription.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from type_inscription where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_type_inscription = $data[0]["nombre"];
			// Inscriptions
			$this->menuitem("Inscriptions_Types"."#".$nombre_organisme_type_inscription, dispatch_url("table.type_inscription", "admin", array (
			"atkfilter" => "type_inscription.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_lieu_rencontre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_lieux_rencontres = $data[0]["nombre"];
			// Lieux de rencontres
			$this->menuitem("Lieux_Rencontres"."#".$nombre_organisme_lieux_rencontres, dispatch_url("organisme.lieu_rencontre", "admin", array (
			"atkfilter" => "organisme_lieu_rencontre.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			/*
			 $data = $db->getrows("SELECT count(id) as nombre from organisme_contrat_lieu_rencontre where  id_organisme_loueur=" . $organismeid . " ");
			 $nombre_organisme_lieux_rencontres = $data[0]["nombre"];
			 // Contrats accordés
			 $this->menuitem("Contrats_Accordes"."#".$nombre_organisme_lieux_rencontres, dispatch_url("organisme.contrat_lieu_rencontre", "admin", array (
			 "atkfilter" => "organisme_contrat_lieu_rencontre.id_organisme_loueur ='" . $organismeid . "'"
			 )), "Organismes", true);
			 $data = $db->getrows("SELECT count(id) as nombre from organisme_contrat_lieu_rencontre where  id_organisme_locataire=" . $organismeid . " ");
			 $nombre_organisme_lieux_rencontres = $data[0]["nombre"];
			 // Contrats souscrits
			 $this->menuitem("Contrats_Souscrits"."#".$nombre_organisme_lieux_rencontres, dispatch_url("organisme.contrat_lieu_rencontre", "admin", array (
			 "atkfilter" => "organisme_contrat_lieu_rencontre.id_organisme_locataire ='" . $organismeid . "'"
			 )), "Organismes", true);
			 */

			/*
			 $data = $db->getrows("SELECT count(id) as nombre from individu_contact where  id_individu IN ( select distinct id_individu from individu_inscription where id_organisme ='" . $organismeid . "')
			 or individu_contact.id_contact IN ( select distinct id_individu from individu_inscription where id_organisme ='" . $organismeid . "') "
			 );
			 $nombre_organisme_contact_inscription = $data[0]["nombre"];

			 // Contacts inscriptions
			 $this->menuitem("Contacts_inscriptions"."#".$nombre_organisme_contact_inscription, dispatch_url("individu.contact_i", "admin", array (
			 "atkfilter" => "individu_contact.id_individu IN ( select distinct id_individu from individu_inscription where id_organisme ='" . $organismeid . "')
			 or individu_contact.id_contact IN ( select distinct id_individu from individu_inscription where id_organisme ='" . $organismeid . "') "
			 )), "Organismes", true);
			 */


			// Opérations de banque
			$this->menuitem("Comptes", "target_menu".'menu.php?atkmenutop=Comptes', "Organismes", true);
	//			$this->menuitem("Traitements", "target_menu".'menu.php?atkmenutop=Traitements', "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_golf_parcours where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_parcours = $data[0]["nombre"];
			// Parcours o
			$this->menuitem("Parcours_o"."#".$nombre_organisme_parcours, dispatch_url("organisme.golf_parcours", "admin", array (
			"atkfilter" => "organisme_golf_parcours.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_partenaire where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_partenaire = $data[0]["nombre"];
			// Partenaires o
			$this->menuitem("Partenaires_o"."#".$nombre_organisme_partenaire, dispatch_url("organisme.partenaire", "admin", array (
			"atkfilter" => "organisme_partenaire.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id)  as nombre from individu_groupe_travail where id_organisme_participant
		 ='" . $organismeid . "' ");
			$nombre_organisme_participant = $data[0]["nombre"];
			// Participants à des rencontres
			$this->menuitem("Participants_groupe_travail_o"."#".$nombre_organisme_participant, dispatch_url("individu.groupe_travail_i", "admin", array (
			"atkfilter" => "individu_groupe_travail.id_organisme_participant ='" . $organismeid . "'"
			)), "Organismes", true);

			$data = $db->getrows("SELECT count(id)  as nombre from individu_rencontre where id_organisme_participant
		 ='" . $organismeid . "' ");
			$nombre_organisme_participant = $data[0]["nombre"];
			// Participants à des rencontres
			$this->menuitem("Participants_o"."#".$nombre_organisme_participant, dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_organisme_participant ='" . $organismeid . "'"
			)), "Organismes", true);



			// Pouvoirs_CA
			$this->menuitem("Pouvoirs_CA", dispatch_url("individu.v_individu_lieu", "admin", array (
			"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1'  
			and v_individu_lieu.id IN
			(select distinct ifn.id_individu
			from individu_fonction ifn
			where ifn.id_fonction='2'
			and ifn.date_fin is null
			and ifn.id_organisme=$organismeid)",
			"atkaction" => "document",
			"atkselector" => "organisme.id=$organismeid",
			"id" => "$organismeid",
			"atkdoctpl" => "pouvoir_ca_organisme.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_patrimoine where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_patrimoine = $data[0]["nombre"];
			// Patrimoine o
			$this->menuitem("Patrimoine_o"."#".$nombre_organisme_patrimoine, dispatch_url("organisme.patrimoine", "admin", array (
			"atkfilter" => "organisme_patrimoine.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_referencement where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_referencement = $data[0]["nombre"];
			// Référencements o
			$this->menuitem("Référencements_o"."#".$nombre_organisme_referencement, dispatch_url("organisme.referencement", "admin", array (
			"atkfilter" => "organisme_referencement.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_regle where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_regle = $data[0]["nombre"];
			// Règles et définitions o
			$this->menuitem("Règles et définitions_o"."#".$nombre_organisme_regle, dispatch_url("manuel.manuel", "admin", array (
			"atkfilter" => "organisme_regle.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
			//
			
			// Rencontres
			// Types rencontre 
			$data = $db->getrows("SELECT count(id) as nombre from type_rencontre where id in (select id_type_rencontre from organisme_rencontre where id_organisme=$organismeid)");
			$nombre_type_rencontre= $data[0]["nombre"];
			$this->menuitem("-/+*Rencontres <<"."#".$nombre_type_rencontre, dispatch_url("table.type_rencontre", "admin"
					, array (
			"atkfilter" => "type_rencontre.id in (select id_type_rencontre from organisme_rencontre where id_organisme=$organismeid)",
			"id_organisme" => $organismeid
			)), "Organismes", true);
			// Rencontres Détails
			$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_rencontre = $data[0]["nombre"];
			$this->menuitem("?Rencontres >>"."#".$nombre_organisme_rencontre, dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme='" . $organismeid . "'"
			)), "Organismes", true);
/*			$data = $db->getrows("SELECT count(id) as nombre from organisme_statistique where  id_organisme=" . $organismeid . " ");
			$nombre = $data[0]["nombre"];
			// Statistiques
			$this->menuitem("Statistiques"."#".$nombre, dispatch_url("organisme.organisme_statistique", "admin", array (
			"atkfilter" => "organisme_statistique.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);
			*/
			// Tableau de bord
			$this->menuitem("Tableaux de bord (tout)", "target_blank".dispatch_url("organisme.tableaudebord", "tableau_organisme", array (
					"id_organisme" => $organismeid,
					"type_tableau"=>"organisme"
			)), "Organismes", true);
			
			// Tableau de bord
			$this->menuitem("Tableaux de bord (menu)", "target_menu".'menu.php?atkmenutop=Tableaux_de_bord_o', "Organismes", true);

			$data = $db->getrows("SELECT count(id) as nombre from scheduler_vacances where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_vacances = $data[0]["nombre"];
			// Vacances
			$this->menuitem("Vacances_o"."#".$nombre_organisme_vacances, dispatch_url("scheduler.scheduler_vacances", "admin", array (
			"atkfilter" => "scheduler_vacances.id_organisme ='" . $organismeid . "'"
			)), "Organismes", true);

			//Traitements
			$this->menuitem("Traitements", "target_menu".'menu.php?atkmenutop=Traitements', "Organismes", true);
	//		$this->menuitem('Global', "target_menu".'menu.php?atkmenutop=Global', "Administrer", true);


			$qr_organisme="MECARD:N:".$nom_organisme.";TEL:".$telephone_organisme.";URL:".$site_internet_organisme.
";EMAIL:".$courriel_organisme.";ADR:".$qr_adresse_organisme.";;";
			$qr_organisme=str_replace(' ', '+', $qr_organisme);
			$qr_organisme=str_replace("'", "/'", $qr_organisme);
			$qr_organisme=utf8_encode($qr_organisme);
			$qr_organisme = href("index.php", '<img src="http://chart.apis.google.com/chart?cht=qr&chs=150x150&chl='.$qr_organisme.'" class="gwt-Image" style="">', SESSION_DEFAULT, false, null);
			$this->menuitem("-", "", "Organismes", true);
			$this->menuitem($qr_organisme, "", "Organismes", true);

			$this->menuitem("-", '', "Organismes", true);
		}
		if ($topmenu=="Tableaux_de_bord_o")
		{
		
			// TOP
			// Tableaux de bord organisme
			$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
			$this->menuitem("!".$data, null, "Tableaux_de_bord_o", true);
			$this->menuitem("-", null, "Tableaux_de_bord_o", true);
			$this->menuitem("Tout", "target_blank".dispatch_url("organisme.tableaudebord", "tableau_organisme", array (
					"id_organisme" => $organismeid,
					"type_tableau"=>"organisme"
			)), "Tableaux_de_bord_o", true);
			
						$this->menuitem("Adhésions", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Adhésions")), "Tableaux_de_bord_o", true);
						$this->menuitem("Contacts", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
								"id_organisme"=>$organismeid,
								"nom_detail_tbdebord"=>"Contacts")), "Tableaux_de_bord_o", true);			
			$this->menuitem("Contrats", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Contrats")), "Tableaux_de_bord_o", true);
			$this->menuitem("Cotisations", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Cotisations")), "Tableaux_de_bord_o", true);
			$this->menuitem("Documents", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Documents")), "Tableaux_de_bord_o", true);
			$this->menuitem("Domaines internet", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Domaines internet")), "Tableaux_de_bord_o", true);
			$this->menuitem("Fonctions", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Fonctions")), "Tableaux_de_bord_o", true);
			
			$this->menuitem("Gazettes", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Gazettes")), "Tableaux_de_bord_o", true);
			$this->menuitem("Immatriculations", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Immatriculations")), "Tableaux_de_bord_o", true);
			$this->menuitem("Inscriptions", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Inscriptions")), "Tableaux_de_bord_o", true);
			$this->menuitem("Types d'inscriptions", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Types d'inscriptions")), "Tableaux_de_bord_o", true);
			$this->menuitem("Organisme", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Organisme")), "Tableaux_de_bord_o", true);
			$this->menuitem("Patrimoine", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Patrimoine")), "Tableaux_de_bord_o", true);
			


			$this->menuitem("Radiations", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Radiations")), "Tableaux_de_bord_o", true);
			$this->menuitem("Référencements", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Référencements")), "Tableaux_de_bord_o", true);
			$this->menuitem("Rencontres", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Rencontres")), "Tableaux_de_bord_o", true);

			$this->menuitem("Résultats comptables", dispatch_url("organisme.tableaudebord", "tableau_detail_organisme", array (
					"id_organisme"=>$organismeid,
					"nom_detail_tbdebord"=>"Résultats comptables")), "Tableaux_de_bord_o", true);

		
	
		}
		if ($topmenu=="Comptabilite_o")
		{

			// TOP
			// Comptabilité

			//			$this->menuitem("Top_Comptabilite", "", "Comptabilite_o", true);
			//			$this->menuitem("-", "", "Comptabilite_o", true);
			// Nom Organisme
			// Nom Organisme

			$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
			$this->menuitem("!".$data, null, "Comptabilite_o", true);
			$this->menuitem("-", null, "Comptabilite_o", true);
			
			$data = $db->getrows("SELECT count(id) as nombre from organisme_budget where  id_organisme=" . $organismeid . " ");
			$nombre_budgets = $data[0]["nombre"];
			$this->menuitem("!<b>Budget</b>", null, "Comptabilite_o", true);
			
			$this->menuitem("Budgets"."#".$nombre_budgets, dispatch_url("organisme.budget", "admin", array (
			"atkfilter" => "organisme_budget.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$this->menuitem("-", null, "Comptabilite_o", true);
			$this->menuitem("!<b>Opérations comptables</b>", null, "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_abandon_creance where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_virement = $data[0]["nombre"];
			// Abandon de créance
			$this->menuitem("Abandon_creances_i"."#".$nombre_organisme_virement, dispatch_url("organisme.abandon_creance", "admin", array (
			"atkfilter" => "organisme_abandon_creance.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);


			$data = $db->getrows("SELECT count(id) as nombre from individu_activite where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_activite = $data[0]["nombre"];

			// Activités Frais
			$this->menuitem("Activités Frais"."#".$nombre_organisme_activite, dispatch_url("individu.activite_i", "admin", array (
			"atkfilter" => "individu_activite.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_fourniture where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_fourniture = $data[0]["nombre"];
			// Dépenses Règlements
			$this->menuitem("Dépenses Règlements"."#".$nombre_organisme_fourniture, dispatch_url("organisme.fourniture", "admin", array (
			"atkfilter" => "organisme_fourniture.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_financement where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_financement = $data[0]["nombre"];
			// Recettes Subventions
			$this->menuitem("Recettes Subventions"."#".$nombre_organisme_financement, dispatch_url("organisme.financement", "admin", array (
			"atkfilter" => "organisme_financement.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_virement_comptable where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_virement = $data[0]["nombre"];
			// Virements Retraits
			$this->menuitem("Virements Retraits"."#".$nombre_organisme_virement, dispatch_url("organisme.virement_comptable", "admin", array (
			"atkfilter" => "organisme_virement_comptable.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$this->menuitem("-", null, "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id_organisme) as nombre from v_organisme_comptes_tiers where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_solde_usager = $data[0]["nombre"];
			// Soldes usagers
			$this->menuitem("Soldes usagers"."#".$nombre_organisme_solde_usager, dispatch_url("organisme.v_organisme_comptes_tiers", "admin", array (
					"atkfilter" => " v_organisme_comptes_tiers.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			
			
			$this->menuitem("-", null, "Comptabilite_o", true);
			$this->menuitem("!<b>Résultats (décimales)</b>", null, "Comptabilite_o", true);
			
			$this->menuitem("Tout", dispatch_url("organisme.resultat_comptable", "admin", array (
					"organisme_id" =>  $organismeid ,
					"classe_id" => "Tout"
			)), "Comptabilite_o", true);
			$this->menuitem("Recettes", dispatch_url("organisme.resultat_comptable", "admin", array (
					"organisme_id" =>  $organismeid ,
					"classe_id" => "7"
			)), "Comptabilite_o", true);
			$this->menuitem("Dépenses", dispatch_url("organisme.resultat_comptable", "admin", array (
					"organisme_id" =>  $organismeid ,
					"classe_id" => "6"
			)), "Comptabilite_o", true);
			$this->menuitem("Finances", dispatch_url("organisme.resultat_comptable", "admin", array (
					"organisme_id" =>  $organismeid ,
					"classe_id" => "5"
			)), "Comptabilite_o", true);
			$this->menuitem("Contributions volontaires", dispatch_url("organisme.resultat_comptable", "admin", array (
					"organisme_id" =>  $organismeid ,
					"classe_id" => "8"
			)), "Comptabilite_o", true);
			
			
			$this->menuitem("-", null, "Comptabilite_o", true);
			$this->menuitem("!<b>Plan comptable</b>", null, "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme=" . $organismeid . " and usuel='1' ");
			$nombre_organisme_plan_comptable = $data[0]["nombre"];
			// Plan comptable
			$this->menuitem("Plan comptable complet"."#".$nombre_organisme_plan_comptable, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);

			
			// Produits
			$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme=" . $organismeid . " and
																						( organisme_compte.code like '7%') and organisme_compte.id IN 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						);
			$nombre_organisme_produit = $data[0]["nombre"];


			$this->menuitem("Produits"."#".$nombre_organisme_produit, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "' and 
																						( organisme_compte.code like '7%') and organisme_compte.id IN 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme=" . $organismeid . " and
																						( organisme_compte.code like '6%') and organisme_compte.id IN 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						);
			$nombre_organisme_charge = $data[0]["nombre"];
			// Charges
			$this->menuitem("Charges"."#".$nombre_organisme_charge, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "' and 
																						( organisme_compte.code like '6%') and organisme_compte.id IN 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme=" . $organismeid . " and
																						( organisme_compte.code like '8%') and organisme_compte.id IN 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						);
			$nombre_organisme_contribution_volontaire = $data[0]["nombre"];
			// Contributions volontaires
			$this->menuitem("Contributions volontaires"."#".$nombre_organisme_contribution_volontaire, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "' and 
																						( organisme_compte.code like '8%') and organisme_compte.id in 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						)), "Comptabilite_o", true);
		$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme=" . $organismeid . " and
																						 organisme_compte.code like '5%' "
																						 );
		$nombre_organisme_finance = $data[0]["nombre"];
		// Finances
		$this->menuitem("Finances"."#".$nombre_organisme_finance, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "' and  organisme_compte.code like '5%'
																										"
																										)), "Comptabilite_o", true);
		$data = $db->getrows("SELECT count(id) as nombre from organisme_compte where  id_organisme='" . $organismeid . "' and
																						( organisme_compte.code like '4%') and organisme_compte.id in 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						);
		$nombre_organisme_tiers = $data[0]["nombre"];
		// Tiers
		$this->menuitem("Tiers"."#".$nombre_organisme_tiers, dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme='" . $organismeid . "' and 
																						( organisme_compte.code like '4%') and organisme_compte.id in 
																						(select distinct id_compte from organisme_ligne_ecriture_comptable)"
																						)), "Comptabilite_o", true);
			


			
			

			$this->menuitem("-", null, "Comptabilite_o", true);
			$this->menuitem("!<b>Journaux, écritures</b>", null, "Comptabilite_o", true);
																						$data = $db->getrows("SELECT count(id) as nombre from organisme_journal_comptable where  id_organisme=" . $organismeid . " ");
																						$nombre_organisme_journal_comptable = $data[0]["nombre"];
																						// Journaux
																						$this->menuitem("Journaux"."#".$nombre_organisme_journal_comptable, dispatch_url("organisme.journal_comptable", "admin", array (
			"atkfilter" => "organisme_journal_comptable.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_ecriture_comptable where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_ecriture_comptable = $data[0]["nombre"];

			$this->menuitem("Ecritures"."#".$nombre_organisme_ecriture_comptable, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "'"
			)), "Comptabilite_o", true);
			$this->menuitem("-", null, "Comptabilite_o", true);
			$this->menuitem("!<b>Outils de contrôle</b>", null, "Comptabilite_o", true);
			$this->menuitem("!<b>1- Déséquilibres</b>", null, "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_ecriture_comptable where  id_organisme=" . $organismeid . "
			 and id in (select id_ecriture FROM `v_ecriture_comptable_controle` WHERE   (debit is null or credit is null or not credit=debit))  ");
			$nombre=$data[0]["nombre"];
			$this->menuitem("<b><i>Ecritures_incomplètes</i></b>"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' and organisme_ecriture_comptable.id in 
			(select id_ecriture FROM `v_ecriture_comptable_controle` WHERE   (debit is null or credit is null or not credit=debit) 
			) "
			)), "Comptabilite_o", true);
			$this->menuitem("!<b>2- Descendance</b>", null, "Comptabilite_o", true);

			$data = $db->getrows("SELECT count(id ) as nombre from individu_cotisation where
			id_organisme=" . $organismeid . " 
			and date_reglement >'2007-12-31'
			 and 
			 (
			  id_ecriture_cotisation is null or id_ecriture_reglement is null or id_ecriture_cotisation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 or id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle ) 
			 or 
			 ( id_ecriture_cotisation_federation is not null and id_ecriture_cotisation_federation not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )  ");
			$nombre=$data[0]["nombre"];
			$this->menuitem("Cotisations"."#".$nombre, dispatch_url("individu.cotisation_i", "admin", array (
			"atkfilter" => "individu_cotisation.id_organisme='" . $organismeid . "' 
			and date_reglement >'2007-12-31' 
			and 
			( id_ecriture_cotisation is null or id_ecriture_reglement is null or id_ecriture_cotisation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 or id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle ) 
			 or 
			 (id_ecriture_cotisation_federation is not null and id_ecriture_cotisation_federation not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )  "
			 )), "Comptabilite_o", true);
			 	
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_rencontre where
			id_organisme=" . $organismeid . " 
			 and 
			 (
			 ( id_ecriture_participation is not null and id_ecriture_participation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			   ");
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Rencontres"."#".$nombre, dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme='" . $organismeid . "' 
			  and 
			 (
			 ( id_ecriture_participation is not null and id_ecriture_participation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )  "
			 ,
			   "atkorigine" => "comptabilite"
			   )), "Comptabilite_o", true);
			    
			   $data = $db->getrows("SELECT count(id ) as nombre from individu_rencontre where date_creation>'2007-11-17' and
			id_rencontre in (select distinct id from organisme_rencontre where id_organisme='" . $organismeid . "' ) 
			 and 
			 (
			 ( individu_rencontre.id_ecriture_participation is not null and individu_rencontre.id_ecriture_participation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (			 individu_rencontre.id_ecriture_reglement is not null and individu_rencontre.id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 or
			 ((individu_rencontre.id_ecriture_participation is  null or individu_rencontre.id_ecriture_reglement is null) and montant_versement >0)
			 )
			    ");
			   $nombre=$data[0]["nombre"];
			   $this->menuitem("Rencontres_participants"."#".$nombre, dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_rencontre in (select distinct id from organisme_rencontre where id_organisme='" . $organismeid . "' )   
			 and  individu_rencontre.date_creation>'2007-11-17'  and
			  ( 
			 ( individu_rencontre.id_ecriture_participation is not null and individu_rencontre.id_ecriture_participation not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (individu_rencontre.id_ecriture_reglement is not null and individu_rencontre.id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			  or
			 ((individu_rencontre.id_ecriture_participation is  null or individu_rencontre.id_ecriture_reglement is null) and montant_versement >0)
			 )
			    "
			    ,
			   "atkorigine" => "comptabilite"
			   )), "Comptabilite_o", true);
			    
			   $data = $db->getrows("SELECT count(id ) as nombre from organisme_rencontre where
			id_organisme=" . $organismeid . " 
			 and 
			 (
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_participation is not null and id_ecriture_participation not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			   ");
			   $nombre=$data[0]["nombre"];
			   $this->menuitem("Rencontres_fournisseurs"."#".$nombre, dispatch_url("organisme.rencontre_fournisseur", "admin", array (
			"atkfilter" => "organisme_rencontre_fournisseur.id_organisme='" . $organismeid . "' 
			 and 
			 (
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_participation is not null and id_ecriture_participation not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			     "
			     )), "Comptabilite_o", true);
			      
			     $data = $db->getrows("SELECT count(id ) as nombre from organisme_abandon_creance where
			id_organisme=" . $organismeid . " 
			 and 
			 ( id_ecriture_virement is  null or id_ecriture_virement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) ");
			     $nombre=$data[0]["nombre"];
			     $this->menuitem("Abandon_de_creances"."#".$nombre, dispatch_url("organisme.abandon_creance", "admin", array (
			"atkfilter" => "organisme_abandon_creance.id_organisme='" . $organismeid . "' 
			 and 
			 ( id_ecriture_virement is  null or id_ecriture_virement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 )"
			 )), "Comptabilite_o", true);
			 	
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_fourniture where
			id_organisme=" . $organismeid . " 
			 and 
			 (
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_depense is not null and id_ecriture_depense not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			      ");
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Depenses"."#".$nombre, dispatch_url("organisme.fourniture", "admin", array (
			"atkfilter" => "organisme_fourniture.id_organisme='" . $organismeid . "' 
			 and 
			 (
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) 
			 or 
			 (id_ecriture_depense is not null and id_ecriture_depense not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			 "
			 )), "Comptabilite_o", true);
			 	
			 	
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_financement where
			id_organisme=" . $organismeid . " 
			 and
			 ( 
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle   ) 
			 ) 
			 or 
			 (id_ecriture_recette is not null and id_ecriture_recette not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			      ");
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Recettes"."#".$nombre, dispatch_url("organisme.financement", "admin", array (
			"atkfilter" => "organisme_financement.id_organisme='" . $organismeid . "' 
			 and 
			 (
			 ( id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM  v_ecriture_comptable_controle    ) 
			 ) 
			 or 
			 (id_ecriture_recette is not null and id_ecriture_recette not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )
			     "
			     )), "Comptabilite_o", true);
			      
			     $data = $db->getrows("SELECT count(id ) as nombre from organisme_virement_comptable where
			id_organisme=" . $organismeid . " 
			 and 
			 ( id_ecriture_virement is  null or id_ecriture_virement not in (select id_ecriture FROM  v_ecriture_comptable_controle )
			 )");
			     $nombre=$data[0]["nombre"];
			     $this->menuitem("Virements"."#".$nombre, dispatch_url("organisme.virement_comptable", "admin", array (
			"atkfilter" => "organisme_virement_comptable.id_organisme='" . $organismeid . "' 
			 and 
			 ( id_ecriture_virement is  null or id_ecriture_virement not in (select id_ecriture FROM  v_ecriture_comptable_controle ) 
			 ) "
			 )), "Comptabilite_o", true);
			 	
			 	
			 $data = $db->getrows("SELECT count(id ) as nombre from individu_activite where
			id_organisme=" . $organismeid . " 
			 and 
			 (
			 ( id_ecriture_frais is not null and id_ecriture_frais not in (select id_ecriture FROM  v_ecriture_comptable_controle   )
			 )
			 or 
			 (id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 or 
			 (id_ecriture_benevolat is not null and id_ecriture_benevolat not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )       
			    ");
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Frais/activites"."#".$nombre, dispatch_url("organisme.activite_i", "admin", array (
			"atkfilter" => "individu_activite.id_organisme='" . $organismeid . "' 
			and 
			 (
			 ( id_ecriture_frais is not null and id_ecriture_frais not in (select id_ecriture FROM  v_ecriture_comptable_controle   )
			 )
			 or 
			 (id_ecriture_reglement is not null and id_ecriture_reglement not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 or 
			 (id_ecriture_benevolat is not null and id_ecriture_benevolat not in (select id_ecriture FROM v_ecriture_comptable_controle )
			 )
			 )  "
			 )), "Comptabilite_o", true);
			 $this->menuitem("!<b>3- Type écriture</b>", null, "Comptabilite_o", true);
			 $this->menuitem("<b><i>Mettre à jour et vérifier</i></b>",dispatch_url("organisme.ecriture_comptable", "insertion_type_ecriture", array (0)), "Comptabilite_o", true);
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_cotisation."
			and id_organisme=" . $organismeid  );
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Ecritures cotisation"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_cotisation
			 )), "Comptabilite_o", true);
			 $data = $db->getrows("SELECT count(id )   as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_participation_rencontre."
			and id_organisme=" . $organismeid  );
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Ecritures participation"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_participation_rencontre
			 )), "Comptabilite_o", true);
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_rencontre."
			and id_organisme=" . $organismeid  );
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Ecritures rencontre"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_rencontre
			 )), "Comptabilite_o", true);
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_rencontre_fournisseur."
			and id_organisme=" . $organismeid  );
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Ecritures fournisseur rencontre"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_rencontre_fournisseur
			 )), "Comptabilite_o", true);
			 $data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_depense."
			and id_organisme=" . $organismeid  );
			 $nombre=$data[0]["nombre"];
			 $this->menuitem("Ecritures dépense"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=6"
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_recette."
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("Ecritures recette"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_recette
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_virement."
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("Ecritures virement"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_virement
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_frais."
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("Ecritures frais"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_frais
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_abandon_creance."
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("Ecritures abandon créance"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_abandon_creance
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture=".$type_ecriture_journal."
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("Ecritures journal direct"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture=".$type_ecriture_journal
			)), "Comptabilite_o", true);
			$data = $db->getrows("SELECT count(id ) as nombre from organisme_ecriture_comptable where id_type_ecriture is null
			and id_organisme=" . $organismeid  );
			$nombre=$data[0]["nombre"];
			$this->menuitem("<b><i>Ecritures sans origine</i></b>"."#".$nombre, dispatch_url("organisme.ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ecriture_comptable.id_organisme='" . $organismeid . "' 
			and id_type_ecriture is null"
			)), "Comptabilite_o", true);			$this->menuitem("-", null, "Comptabilite_o", true);

			$this->menuitem("-", null, "Organismes", true);
		}
		if ($topmenu=="Individus")
		{


			// TOP
			// Individus
			// Dernier individu sélectionné
			$individuid = 0;
			$user = getUser();
			$id = $user["id"];
			if (isset ($id)) {
				$db = & atkGetDb();
//				$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
//				$id_individu = $data[0]["id_individu"];
				$id_individu=$g_utilisateur_individu[$id];
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='individu' order by date_recent_use desc");
				if (count($data) > 0) {
					$individuid = $data[0]["id_entite"];
					$data = $db->getrows("select sexe, nom, prenom, courriel, calendrier, calendrier_contacts_url, calendrier_contacts_refresh,
				calendrier_rencontres_url, calendrier_rencontres_refresh, telephone_fixe, telephone_mobile, date_naissance,site_internet, date_deces  
				from individu where id=$individuid");
					$nomindividu=$data[0]["nom"];
					$sexe_individu=$data[0]["sexe"];
					$prenomindividu=$data[0]["prenom"];
					$qr_nom_individu=$data[0]["nom"] . ' , '. $data[0]["prenom"];
					$qr_anniversaire=substr($data[0]["date_naissance"], 0,10);
					$qr_anniversaire_individu=str_replace('-', '', $qr_anniversaire);

					$nom_individu="";
					if (!empty($prenomindividu)) $nom_individu = $prenomindividu ." ";
					$nom_individu .= $nomindividu ;
					$courriel_individu = $data[0]["courriel"];
					$calendrier_individu = $data[0]["calendrier"];
					$calendrier_contacts_url_individu = $data[0]["calendrier_contacts_url"];
					$calendrier_contacts_refresh_individu = $data[0]["calendrier_contacts_refresh"];
					$calendrier_rencontres_url_individu = $data[0]["calendrier_rencontres_url"];
					$calendrier_rencontres_refresh_individu = $data[0]["calendrier_rencontres_refresh"];
					$site_internet_individu = $data[0]["site_internet"];
					$telephone_fixe_individu = $data[0]["telephone_fixe"];
					$telephone_mobile_individu = $data[0]["telephone_mobile"];
					$date_deces = $data[0]["date_deces"];
					$data = $db->getrows("SELECT adresse1, adresse2, code_postal, ville, code_iso
				from individu_lieu il, lieu l, type_cp_ville_pays cp, type_pays p
				where il.id_individu=$individuid and il.adresse_defaut_o_n='1'
				and il.id_lieu=l.id
				and l.id_ville=cp.id
				and cp.id_pays=p.id");
					if (!empty($data[0]["ville"] ))
					{ $adresse_individu = $data[0]["adresse1"] . '<br />'  . $data[0]["code_postal"] . ' ' . $data[0]["ville"] . ' (' . $data[0]["code_iso"].')';
					$qr_adresse_individu=$data[0]["adresse1"] . ','  . $data[0]["code_postal"] . ',' . $data[0]["ville"] . ',' . $data[0]["code_iso"];}
					else {$adresse_individu="";
					$qr_adresse_individu="";}
					//				$adresse_individu = $data[0]["adresse1"] . '<br />'  . $data[0]["code_postal"] . ' ' . $data[0]["ville"]. ' (' . $data[0]["code_iso"].')';

					$fiche_individu = '<font color="Tomato"> <b>' . $nom_individu . '</b>';
					$id_individu_utilisateur = "";
					$data = $db->getrows("SELECT id from app_utilisateur where id_individu=" . $individuid . " ");
					$id_individu_utilisateur = $data[0]["id"];


				}
			}
			$data = $db->getrows("SELECT count(id) as nombre from individu_activite where id_individu=" . $individuid . " ");
			$nombre_individu_activite = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_lieu where id_individu=" . $individuid . " ");
			$nombre_individu_adresse = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_attribut where id_individu=" . $individuid . " ");
			$nombre_individu_attribut = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_bookmark where id_individu=" . $individuid . " ");
			$nombre_individu_bookmark = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_carte_golf where id_individu=" . $individuid . " ");
			$nombre_individu_carte_golf = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_competence where id_individu=" . $individuid . " ");
			$nombre_individu_competence = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_carte_golf where id_individu=" . $individuid . " ");
			$nombre_individu_competition = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_individu=" . $individuid . " or id_contact=" . $individuid . " ");
			$nombre_individu_contact = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_contact=" . $individuid . "  ");
			$nombre_individu_contactant = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_individu=" . $individuid . " ");
			$nombre_individu_contacte = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotisation where id_individu=" . $individuid . " ");
			$nombre_individu_cotisation = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotorep where id_individu=" . $individuid . " ");
			$nombre_individu_cotorep = $data[0]["nombre"];

			if ($id_individu_utilisateur!="")
			{				$data = $db->getrows("SELECT count(id) as nombre from app_pb_report where id_creation=" . $id_individu_utilisateur .  "");
			$nombre_individu_demande = $data[0]["nombre"];}
			$data = $db->getrows("SELECT count(id) as nombre from individu_document where id_individu=" . $individuid . " ");

			$nombre_individu_document = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from organisme_document where id_individu_auteur=" . $individuid . " ");
			$nombre_individu_document_auteur = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_envoi_groupe where id_individu_emetteur=" . $individuid . " ");
			$nombre_individu_envoi_groupe = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_fonction where id_individu=" . $individuid . " ");
			$nombre_individu_fonction = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where id_individu=" . $individuid . " ");
			$nombre_individu_historique = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from organisme_image where id_type_entite='2' and id_entite=" . $individuid . " ");
			$nombre_individu_image= $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_immatriculation where id_individu=" . $individuid . " ");
			$nombre_individu_immatriculation= $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_inscription where id_individu=" . $individuid . " ");
			$nombre_individu_inscription = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_groupe_travail where id_individu=" . $individuid . " ");
			$nombre_individu_groupe_travail = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from organisme_ligne_ecriture_comptable where id_individu=" . $individuid . " ");
			$nombre_individu_ligne_comptable = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_cotorep where id_individu=" . $individuid . " ");
			$nombre_individu_mdph = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id) as nombre from individu_rencontre where id_individu=" . $individuid . " ");
			$nombre_individu_rencontre = $data[0]["nombre"];
			//			$data = $db->getrows("SELECT count(id) as nombre from app_sauvegarde where id_individu=" . $individuid . " ");
			//			$nombre_individu_sauvegarde = $data[0]["nombre"];
			$data = $db->getrows("SELECT count(id_individu) as nombre from v_organisme_comptes_tiers where id_individu=" . $individuid . " ");
			$nombre_individu_solde_compte = $data[0]["nombre"];

			$data = $db->getrows("SELECT count(id) as nombre from todo where id_individu_a_faire=" . $individuid . " ");
			$nombre_individu_tache_a_faire = $data[0]["nombre"];

			$data = $db->getrows("SELECT count(id) as nombre from individu_web where id_individu=" . $individuid . " ");
			$nombre_individu_web = $data[0]["nombre"];



			// Rechercher
			$this->menuitem("Rechercher_i", dispatch_url("individu.individu", "admin"), "Individus", true);
			// Récents
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='individu' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Récents_i"."#".$nombre, dispatch_url("profil.recent_use", "admin", array (
			"atkfilter" => "app_recent_use.type_entite='individu' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Individus", true);
			// Créer
			$this->menuitem("Créer_i", dispatch_url("individu.individu", "add"), "Individus", true);
			//
			$this->menuitem("-", null, "Individus", true);
			// Nom Individu

			$data=$node->descripteur_individu($individuid,'n','n','0','menu') ;
			$this->menuitem('!'.$data, null, "Individus", true);
			/*			$this->menuitem("@fiche_individu_i@".$fiche_individu, dispatch_url("individu.individu", "edit", array (
			 "atkselector" => "individu.id='" . $individuid . "'"
			 )), "Individus", true);
			 */
			if (!empty($date_deces)) $this->menuitem("@date_deces_i@".'dcd le : '.$date_deces, "","Individus", true);
			if (!empty($adresse_individu)) $this->menuitem("@adresse_individu_i@".$adresse_individu, dispatch_url("individu.individu", "googlemap", array (
			"id" => "$individuid"
			)), "Individus", true);
			/*			if (!empty($telephone_fixe_individu))		$this->menuitem("@telephone_fixe_i@".$telephone_fixe_individu, "target_blanktel:".$telephone_fixe_individu.";","Individus", true);
			 if (!empty($telephone_mobile_individu))		$this->menuitem("@telephone_mobile_i@".$telephone_mobile_individu, "target_blanktel:".$telephone_mobile_individu.";","Individus", true);
			 */
			if (!empty($courriel_individu))
			{$this->menuitem("@courriel_i@".$courriel_individu, dispatch_url("individu.contact_i", "add", array (
			"atkfilter" => "individu_contact.id_individu='" . $individuid . "' ",
"idcontactant" => "$idutilisateur",
			"atgemail" => "$courriel_individu"
			)), "Individus", true);}
			/*

			if (!empty($site_internet_individu))		$this->menuitem("@site_internet_i@".$site_internet_individu, $site_internet_individu, "Individus", true);
			if (!empty($adresse_individu))		$this->menuitem("@enveloppe_i@"."Enveloppe", dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "individu.id='" . $individuid . "'",
			"id" => $id_organisme,
			"atkfilter" => "v_individu_lieu.id='" . $individuid . "'",
			"atkdoctpl" => "enveloppe_individu.odt",
			"atkdoctpl_prefix_id" => "0",
			"atkcode" => "2"
			)), "Individus", true);
			if (!empty ($calendrier_individu)) {
			$this->menuitem("@calendrier_i@"."Calendrier", $calendrier_individu, "Individus", true);
			}
			*/
			/*						if (!empty ($calendrier_contacts_url_individu)) {
				$this->menuitem("Calendrier_contacts_i", $calendrier_contacts_url_individu, "Individus", true);
				$this->menuitem('!<b><font color="Coral">('.$calendrier_contacts_refresh_individu.')</font></b>', null, "Individus", true);
				$this->menuitem("(Rafraîchir)", dispatch_url("individu.individu", "rafraichir_calendrier_contacts", array(
				"atkselector" => "individu.id='" . $individuid . "'"
				)), "Individus", true);}
				*/
			if (!empty ($calendrier_rencontres_url_individu)) {
				$this->menuitem("Calendrier_rencontres_i", $calendrier_rencontres_url_individu, "Individus", true);
				$this->menuitem('!<b><font color="Coral">('.$calendrier_rencontres_refresh_individu.')</font></b>', null, "Individus", true);
				$this->menuitem("(Rafraîchir)", dispatch_url("individu.individu", "rafraichir_calendrier_rencontres", array(
			"atkselector" => "individu.id='" . $individuid . "'"
			)), "Individus", true);}

			$qr_individu="MECARD:N:".$qr_nom_individu.";TEL:".$telephone_fixe_individu.";TEL:".$telephone_mobile_individu.";BDAY:".$qr_anniversaire_individu.";URL:".$site_internet_individu.
";EMAIL:".$courriel_individu.";ADR:".$qr_adresse_individu.";;";
			$qr_individu=str_replace(' ', '+', $qr_individu);
			$qr_individu=str_replace("'", "/'", $qr_individu);
			$qr_individu=utf8_encode($qr_individu);
			$qr_individu = href("index.php", '<img src="http://chart.apis.google.com/chart?cht=qr&chs=150x150&chl='.$qr_individu.'" class="gwt-Image" style="">', SESSION_DEFAULT, false, 'target="_top"');

			/*
			 $this->menuitem("@vcard_i@"."vcard", dispatch_url("individu.individu", "vcard", array (
			 "individu.id" =>"$individuid" )), "Individus", true);
			 */			$this->menuitem("-", "", "Individus", true);

			$data = $db->getrows("SELECT count(id) as nombre from organisme_abandon_creance where  id_individu=" . $individuid . " ");
			$nombre_organisme_virement = $data[0]["nombre"];
			// Abandon de créance
			$this->menuitem("Abandon_creances_o"."#".$nombre_organisme_virement, dispatch_url("organisme.abandon_creance", "admin", array (
			"atkfilter" => "organisme_abandon_creance.id_individu='" . $individuid . "'"
			)), "Individus", true);

			// Activités
			$this->menuitem("Activités_i"."#".$nombre_individu_activite, dispatch_url("individu.activite_i", "admin", array (
			"atkfilter" => "individu_activite.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Adresses
			$this->menuitem("Adresses_i"."#".$nombre_individu_adresse, dispatch_url("individu.individu_lieu", "admin", array (
			"atkfilter" => "individu_lieu.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Annuaire téléphonique
			$this->menuitem("Annuaire_téléphonique_i",
		 "http://www.pagesjaunes.fr/quidonc/quiportecenom.do?nom=" . $nomindividu . "&prenom=". $prenomindividu, "Individus", true);
			// Attributs i
			$this->menuitem("Attributs_i"."#".$nombre_individu_attribut, dispatch_url("individu.attribut_i", "admin", array (
			"atkfilter" => "individu_attribut.id_individu='" . $individuid . "'"
			)), "Individus", true);

			// Biodiversité_observations
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation where id_observateur=". $individuid . " ");
			$this->menuitem("-/+biodiversité_observations_i"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation", "admin", array(
			"atkfilter" => "biodiversite_observation.id_observateur='" . $individuid . "'"
			)), "Individus", true);
			// Biodiversité_observations_détail
			$data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation_detail  where id_observation in (select id from biodiversite_observation where id_observateur=". $individuid . ")");
			$this->menuitem("?biodiversité_observations_détails_i"."#".$data[0]["nombre"], dispatch_url("biodiversite.observation_detail", "admin", array(
			"atkfilter" => "biodiversite_observation_detail.id_observation in (select id from biodiversite_observation where id_observateur=". $individuid . ")"
			)), "Individus", true);


			// Blogs
			$this->menuitem("Blogs"."#".$nombre_individu_web, dispatch_url("individu.web_i", "admin", array (
			"atkfilter" => "individu_web.id_individu='" . $individuid . "' "
			)), "Individus", true);

			// Compétences
			$this->menuitem("Compétences_i"."#".$nombre_individu_competence, dispatch_url("individu.competence_i", "admin", array(
			"atkfilter" => "individu_competence.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Compétitions
			$this->menuitem("Compétitions_i"."#".$nombre_individu_competition, dispatch_url("individu.carte_golf", "admin", array (
			"atkfilter" => "individu_carte_golf.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Contacts i
			$this->menuitem("Contacts_i"."#".$nombre_individu_contact, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_contact='" . $individuid . "' or individu_contact.id_individu='" . $individuid . "' "
			)), "Individus", true);
			// Contactant
			$this->menuitem("/Contactant"."#".$nombre_individu_contactant, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_contact='" . $individuid . "' "
			)), "Individus", true);
			// Contacté
			$this->menuitem("Contacté"."#".$nombre_individu_contacte, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_individu='" . $individuid . "' "
			)), "Individus", true);


			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_contact=" . $individuid . " and date_realisee is null");
			$nombre = $data[0]["nombre"];
			// Contacts à faire
			$this->menuitem("/Contacts_a_traiter_i"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_contact='" . $individuid . "' and date_realisee is null  "
			)), "Individus", true);
			$data = $db->getrows("SELECT count(id) as nombre from individu_contact where id_contact=" . $individuid . " and attente_reponse_o_n='1'");
			$nombre = $data[0]["nombre"];
			// Contacts à faire
			$this->menuitem("Contacts_attente_i"."#".$nombre, dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_contact='" . $individuid . "' and attente_reponse_o_n='1'  "
			)), "Individus", true);


			// Cotisations i
			$this->menuitem("Cotisations_i"."#".$nombre_individu_cotisation, dispatch_url("individu.cotisation_i", "admin", array (
			"atkfilter" => "individu_cotisation.id_individu='" . $individuid . "'"
			)), "Individus", true);

			// Demandes i
			if ($id_individu_utilisateur!="")
			{		$this->menuitem("Demandes_i"."#".$nombre_individu_demande, dispatch_url("application.demande", "admin", array (
			"atkfilter" => "app_pb_report.id_creation='" . $id_individu_utilisateur . "'"
			)), "Individus", true);}
			// Documents i
			$this->menuitem("Documents_i"."#".$nombre_individu_document, dispatch_url("individu.document_i", "admin", array (
			"atkfilter" => "individu_document.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Documents o
			$this->menuitem("Documents_auteur"."#".$nombre_individu_document_auteur, dispatch_url("organisme.document", "admin", array (
			"atkfilter" => "organisme_document.id_individu_auteur='" . $individuid . "'"
			)), "Individus", true);
			// Enveloppe i
			$this->menuitem("Enveloppe_i", dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "individu.id='" . $individuid . "'",
			"id" => $id_organisme,
			"atkfilter" => "v_individu_lieu.id='" . $individuid . "'",
			"atkdoctpl" => "enveloppe_individu.odt",
			"atkdoctpl_prefix_id" => "0",
			"atkcode" => "2"
			)), "Individus", true);
			// Envois groupés
			$this->menuitem("Envoi_groupe_individu"."#".$nombre_individu_envoi_groupe, dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_individu_emetteur='" . $individuid . "'"
			)), "Individus", true);
			// Facebook
			$this->menuitem("Facebook", "http://www.facebook.com/srch.php?nm=".$prenom_individu .'+'. $nom_individu ."&init=ffs" , "Individus", true);

			// Fonctions i
			$this->menuitem("Fonctions_i"."#".$nombre_individu_fonction, dispatch_url("individu.fonction_i", "admin", array (
			"atkfilter" => "individu_fonction.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Géolocalisation
			$this->menuitem("Geolocalisation_i", dispatch_url("individu.individu", "googlemap", array (
			"id" => "" . $individuid . ""
			)), "Individus", true);
			// Groupes de travail i
			$this->menuitem("Groupes_travail_i"."#".$nombre_individu_groupe_travail, dispatch_url("individu.groupe_travail_i", "admin", array (
			"atkfilter" => "individu_groupe_travail.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Historique
			$this->menuitem("Historique_i"."#".$nombre_individu_historique, dispatch_url("profil.recent_use", "admin", array (
			"atkfilter" => "app_recent_use.id_individu='" . $id_individu . "'"
			)), "Individus", true);
			// Images (Individu)
			$this->menuitem("Images_i"."#".$nombre_individu_image, dispatch_url("individu.image_i", "admin", array (
			"atkfilter" => "organisme_image.id_type_entite='2' and organisme_image.id_entite='" . $id_individu . "'  "
			)), "Individus", true);
			// Immatriculations i
			$this->menuitem("Immatriculations_i"."#".$nombre_individu_immatriculation, dispatch_url("individu.immatriculation_i", "admin", array (
			"atkfilter" => "individu_immatriculation.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Inscriptions i
			$this->menuitem("Inscriptions_i"."#".$nombre_individu_inscription, dispatch_url("individu.inscription_i", "admin", array (
			"atkfilter" => "individu_inscription.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Lignes comptables i
			$this->menuitem("Lignes comptables_i"."#".$nombre_individu_ligne_comptable, dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ligne_ecriture_comptable.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Marque pages i
			$this->menuitem("Marque pages_i"."#".$nombre_individu_bookmark, dispatch_url("individu.bookmark_i", "admin", array (
			"atkfilter" => "individu_bookmark.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Cotoreps i
			$this->menuitem("Cotoreps_i"."#".$nombre_individu_mdph, dispatch_url("individu.cotorep_i", "admin", array (
			"atkfilter" => "individu_cotorep.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Notoriété i
			$this->menuitem("Notoriete_i", "http://www.google.fr/search?q=" . $nom_individu . "&ie=utf-8&oe=utf-8&aq=t", "Individus", true);

			/*		//  Observations biodiversite
			 $data = $db->getrows("SELECT count(id) as nombre from biodiversite_observation where  id_observateur=" . $individuid . " ");
			 $nombre_observations = $data[0]["nombre"];
			 $this->menuitem("Observations_i"."#".$nombre_observations, dispatch_url("biodiversite.observation", "admin", array (
			 "atkfilter" => "biodiversite_observation.id_observateur='" . $individuid . "'"
			 )), "Individus", true);
			 */
			// Récapitulatif
			$this->menuitem("Récapitulatif", dispatch_url("individu.individu", "fiche", array (
			"id" => $individuid
			)), "Individus", true);
			// Rencontres i
			$this->menuitem("Rencontres_i"."#".$nombre_individu_rencontre, dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_individu='" . $individuid . "'"
			)), "Individus", true);
			/*			// Sauvegardes i
			 $this->menuitem("Sauvegardes_i"."#".$nombre_individu_sauvegarde, dispatch_url("application.sauvegarde", "admin", array (
			 "atkfilter" => "app_sauvegarde.id_individu ='" . $individuid . "'"
			 )), "Individus", true);
			 */
			// Soldes comptes i
			$this->menuitem("Soldes comptes_i"."#".$nombre_individu_solde_compte, dispatch_url("organisme.v_organisme_comptes_tiers", "admin", array (
			"atkfilter" => "v_organisme_comptes_tiers.id_individu='" . $individuid . "'"
			)), "Individus", true);
			// Tournois

			if ($golf_o_n==1)
			{
				$data = $db->getrows("SELECT count(id) as nombre from individu_tournoi where id_individu=" . $individuid . " ");
				$nombre=$data[0]["nombre"];
				$this->menuitem("Tournois_i"."#".$nombre, dispatch_url("tournoi.individu_tournoi", "admin", array (
			"atkfilter" => "individu_tournoi.id_individu='" . $individuid . "'"
			)), "Individus", true);

			$data = $db->getrows("SELECT count(trm.id) as nombre
				from tournoi_rencontre_match trm, tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_equipe_participant tep, individu_tournoi it
				 where trm.id=tre.id_tournoi_match 
				 and tre.id_tournoi_equipe=te.id
				 and te.id=tep.id_tournoi_equipe
				 and tep.id_individu_tournoi=it.id
				 and it.id_individu='" . $individuid . "'");
			$nombre= $data[0]["nombre"];
			$this->menuitem("Tournois_matches"."#".$nombre, dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
			"atkfilter" => "tournoi_rencontre_match.id in( 
			select trm.id from tournoi_rencontre_match trm, tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_equipe_participant tep, individu_tournoi it
			 where trm.id=tre.id_tournoi_match 
				 and tre.id_tournoi_equipe=te.id
				 and te.id=tep.id_tournoi_equipe
				 and tep.id_individu_tournoi=it.id
				 and it.id_individu='" . $individuid . "' )"
				 )),"Individus", true);


			}
			// Tâches
			$this->menuitem("Tâches_i"."#".$nombre_individu_tache_a_faire, dispatch_url("todo.todo", "admin", array (
			"atkfilter" => "todo.id_individu_a_faire='" . $individuid . "'"
			)), "Individus", true);
			// Utilisateur i
			$this->menuitem("Utilisateur_i", dispatch_url("profil.utilisateur", "admin", array (
			"atkfilter" => "app_utilisateur.id_individu='" . $individuid . "'"
			)), "Individus", true);
			$this->menuitem("-", "", "Individus", true);
			$this->menuitem($qr_individu, "", "Individus", true);

			//
			$this->menuitem("-", null, "Individus", true);
		}
		if ($topmenu=="Rencontres")
		{
			// TOP RENCONTRES

			// Dernière rencontre sélectionnée
			$rencontreid = 0;
			$user = getUser();
			$id = $user["id"];
			if (isset ($id)) {
				$db = & atkGetDb();
//				$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
//				$id_individu = $data[0]["id_individu"];
				$id_individu=$g_utilisateur_individu[$id];
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='rencontre' order by date_recent_use desc");
				if (count($data) > 0) {
					$rencontreid = $data[0]["id_entite"];
					$data = $db->getrows("select r.libelle, r.id_organisme,o.nom from organisme_rencontre r , organisme o where r.id=$rencontreid
				and r.id_organisme=o.id");
					$nom_rencontre = $data[0]["libelle"];
					$organisme_rencontre_id = $data[0]["id_organisme"];
					$organisme_rencontre_nom = $data[0]["nom"];
					$fiche_rencontre = '<font color="Tomato"> <b>' . $nom_rencontre . '<br />('.$organisme_rencontre_nom.') </b>';
				}
			}
			// Nom Organisme

			$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
			$this->menuitem("!".$data, null, "Rencontres", true);

			/*			$this->menuitem("@fiche_organisme_r@".$fiche_organisme, dispatch_url("organisme.organisme", "edit", array (
			 "atkselector" => "organisme.id='" . $organismeid . "'"
			 )), "Rencontres", true);
			 */
			// Rechercher
			$this->menuitem("Rechercher_r", dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme=$organismeid"
			)), "Rencontres", true);
			// Récents

			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='rencontre' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Récents_r"."#".$nombre, dispatch_url("profil.recent_use", "admin", array (
			"atkfilter" => "app_recent_use.type_entite='rencontre' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Rencontres", true);
			// Créer
			$this->menuitem("Créer_r", dispatch_url("organisme.rencontre", "add", array (
			"atkfilter" => "organisme_rencontre.id_organisme='" . $organismeid . "'"
			)), "Rencontres", true);
			//
			$data = $db->getrows("SELECT count(id_type_rencontre) as nombre from v_organisme_rencontre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_rencontre = $data[0]["nombre"];

			// Rencontres o
			// GGG
			$this->menuitem("-/+Rencontres_r"."#".$nombre_organisme_rencontre, dispatch_url("organisme.v_organisme_rencontre", "admin", array (
			"atkfilter" => "v_organisme_rencontre.id_organisme ='" . $organismeid . "'"
			)), "Rencontres", true);
			// Rencontres Détails
			$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre where  id_organisme=" . $organismeid . " ");
			$nombre_organisme_rencontre = $data[0]["nombre"];
			$this->menuitem("?Rencontres_Détails_r"."#".$nombre_organisme_rencontre, dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme='" . $organismeid . "'"
			)), "Rencontres", true);
			// 
			$this->menuitem("-", null, "Rencontres", true);
			// Nom Rencontre


			$data=$node->descripteur_rencontre($rencontreid,'n','n','n') ;
			$this->menuitem("!".$data, null, "Rencontres", true);


			/*
			 $this->menuitem("@fiche_rencontre_r@".$fiche_rencontre, dispatch_url("organisme.rencontre", "edit", array (
			 "atkselector" => "organisme_rencontre.id='" . $rencontreid . "'"
			 )), "Rencontres", true);
			 */

			$data = $db->getrows("SELECT count(id) as nombre from individu_rencontre where  id_rencontre ='" . $rencontreid . "' and id_individu= " . $idutilisateur . " ");
			$nombre_organisme_inscrit = $data[0]["nombre"];
			if ($nombre_organisme_inscrit ==0)
			{	// M'inscrire
				$this->menuitem("m_inscrire_r", dispatch_url("organisme.rencontre", "m_inscrire", array (
			"atkselector" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true); }
				
				
				$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre_choix where  id_rencontre ='" . $rencontreid . "'");
				$nombre_rencontre_choix = $data[0]["nombre"];
				// Fournisseurs
				$this->menuitem("Choix_r"."#".$nombre_rencontre_choix, dispatch_url("organisme.rencontre_choix", "admin", array (
						"atkfilter" => "organisme_rencontre_choix.id_rencontre ='" . $rencontreid . "'"
				)), "Rencontres", true);
		/*		$actions["balance_carree"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=balance_carree&atkselector=[pk]", SESSION_NESTED);
		

		*/
				
			$data = $db->getrows("SELECT count(id) as nombre from individu_rencontre where  id_rencontre ='" . $rencontreid . "'");
			$nombre_rencontre_participant = $data[0]["nombre"];
			// Participants
			$this->menuitem("Participants_r"."#".$nombre_rencontre_participant, dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_rencontre ='" . $rencontreid . "'"
			)), "Rencontres", true);
			// Liste des Participants
			$this->menuitem("Liste_Participants_r"."#".$nombre_rencontre_participant, dispatch_url("organisme.rencontre", "liste_participants", array (
			"atkfilter" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true);

			// Compte rendu
			$this->menuitem("Compte_rendu_r", dispatch_url("organisme.rencontre", "compte_rendu", array (
			"atkfilter" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true);

			// Enveloppes

			$this->menuitem("Enveloppes_Participants_r"."#".$nombre_rencontre_participant, dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "organisme_id='" . $organisme_rencontre_id . "'",
			"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1' and v_individu_lieu.id in 
(select distinct id_individu from individu_rencontre where id_rencontre ='" . $rencontreid . "')",
			"atkdoctpl" => "enveloppe_individus_organisme.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $organisme_rencontre_id
			)), "Rencontres", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre_fournisseur where  id_rencontre ='" . $rencontreid . "'");
			$nombre_rencontre_fournisseur = $data[0]["nombre"];
			// Fournisseurs
			$this->menuitem("Fournisseurs_r"."#".$nombre_rencontre_fournisseur, dispatch_url("organisme.rencontre_fournisseur", "admin", array (
			"atkfilter" => "organisme_rencontre_fournisseur.id_rencontre ='" . $rencontreid . "'"
			)), "Rencontres", true);
			$data = $db->getrows("SELECT count(id) as nombre from organisme_rencontre_communication where  id_rencontre ='" . $rencontreid . "'");
			$nombre_rencontre_communication = $data[0]["nombre"];
			// Communications
			$this->menuitem("Communications_r"."#".$nombre_rencontre_communication, dispatch_url("organisme.rencontre_communication", "admin", array (
			"atkfilter" => "organisme_rencontre_communication.id_rencontre ='" . $rencontreid . "'"
			)), "Rencontres", true);
			
			$this->menuitem("Dépenses/recettes rencontre", dispatch_url("organisme.rencontre", "depenses_recettes", array (
					"atkfilter" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true);
			$this->menuitem("Balance carrée participants_r", dispatch_url("organisme.rencontre", "balance_carree", array (
					"atkfilter" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true);
			$this->menuitem("Renseignements voyage_r", dispatch_url("organisme.rencontre", "renseignements_voyage", array (
					"atkfilter" => "organisme_rencontre.id ='" . $rencontreid . "'"
			)), "Rencontres", true);
			
			
			// Joueurs golf
			$data = $db->getrows("SELECT count(id) as nombre from individu_carte_golf where  id_rencontre ='" . $rencontreid . "'");
			$nombre_rencontre_joueur = $data[0]["nombre"];
			$data = $db->getrows("SELECT id_organisme_parcours from organisme_rencontre where  id ='" . $rencontreid . "'");
			if ($data[0]["id_organisme_parcours"]!="")
			{
				$this->menuitem("Joueurs_r"."#".$nombre_rencontre_joueur, dispatch_url("individu.carte_golf", "admin", array (
			"atkfilter" => "individu_carte_golf.id_rencontre ='" . $rencontreid . "'"
			)), "Rencontres", true);
			}
			//
			$this->menuitem("-", null, "Rencontres", true);

		}
		if ($topmenu=="Envois")
		{
			// TOP ENVOIS Envois
			// Dernier envoi sélectionné
			$envoiid = 0;
			$user = getUser();
			$id = $user["id"];
			if (isset ($id)) {
				$db = & atkGetDb();
//				$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
//				$id_individu = $data[0]["id_individu"];
				$id_individu=$g_utilisateur_individu[$id];
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='envoi' order by date_recent_use desc");
				if (count($data) > 0) {
					$envoiid = $data[0]["id_entite"];
					$data = $db->getrows("select objet from individu_envoi_groupe where id=$envoiid");
					$nom_envoi = $data[0]["objet"];

					$fiche_envoi = '<font color="Tomato"> <b>' . $nom_envoi . '</b>';
				}
			}



			//			$this->menuitem("<b>ENVOIS</b>", "", "Envois", true);
			//			$this->menuitem("-", "", "Envois", true);
			// Nom Organisme
			$this->menuitem('Organisme : '.$fiche_organisme, dispatch_url("organisme.organisme", "edit", array (
			"atkselector" => "organisme.id='" . $organismeid . "'"
			)), "Envois", true);
			// Rechercher
			$this->menuitem("Rechercher_o", dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_organisme_emetteur=$organismeid"
			)), "Envois", true);
			$this->menuitem("-", null, "Envois", true);
			// Nom Individu
			$this->menuitem('Individu : '.$fiche_individu, dispatch_url("individu.individu", "edit", array (
			"atkselector" => "individu.id='" . $individuid . "'"
			)), "Envois", true);
			// Rechercher
			$this->menuitem("Rechercher_i", dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_individu_emetteur=$individuid"
			)), "Envois", true);
			$this->menuitem("-", null, "Envois", true);
			// Nom Utilisateur

			$this->menuitem('Utilisateur : '.$nomutilisateur, dispatch_url("individu.individu", "edit", array (
			"atkselector" => "individu.id='" . $idutilisateur . "'"
			)), "Envois", true);
			// Rechercher
			$this->menuitem("Rechercher_u", dispatch_url("individu.envoi_groupe", "admin", array (
			"atkfilter" => "individu_envoi_groupe.id_utilisateur=$idutilisateur"
			)), "Envois", true);


			// Récents
			$this->menuitem("Récents", dispatch_url("profil.recent_use", "admin", array (
			"atkfilter" => "app_recent_use.type_entite='envoi' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Envois", true);


			$this->menuitem("-", null, "Envois", true);
			// Nom Envoi
			$this->menuitem($fiche_envoi, dispatch_url("individu.envoi_groupe", "edit", array (
			"atkselector" => "individu_envoi_groupe.id='" . $envoiid . "'"
			)), "Envois", true);

			// Contacts
			$this->menuitem("Destinataires", dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_envoi_groupe ='" . $envoiid . "'"
			)), "Envois", true);

			//
			$this->menuitem("-", null, "Envois", true);


		}
		if ($topmenu=="Comptes")
		{


			// TOP OPERATIONS DE BANQUE

			// Dernier compte sélectionné
			$compteid = 0;
			$user = getUser();
			$id = $user["id"];
			if (isset ($id)) {
				$db = & atkGetDb();
	//			$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
	//			$id_individu = $data[0]["id_individu"];
				$id_individu=$g_utilisateur_individu[$id];
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='compte' order by date_recent_use desc");
				if (count($data) > 0) {
					$compteid = $data[0]["id_entite"];
					$data = $db->getrows("select libelle, url_banque, id_organisme from organisme_compte where id=$compteid");
					$nom_compte = $data[0]["libelle"];
					$url_banque = $data[0]["url_banque"];
					$orgcompteid = $data[0]["id_organisme"];
					$data = $db->getrows("select nom  from organisme where id=$orgcompteid");
					$cptorganisme=$data[0]["nom"];
					$fiche_compte = '<font color="Tomato"> <b>' . $nom_compte . '<br />('.$cptorganisme.')</b>';
				}
			}

			// Comptes
			//			$this->menuitem("<b>OPERATIONS DE BANQUE</b>", "", "Comptes", true);
			// Récents
			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='compte' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];

			$this->menuitem("Récents_c", dispatch_url("profil.recent_use", "admin", array(
			"atkfilter" => "app_recent_use.type_entite='compte' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Comptes", true);
			$this->menuitem("-", "", "Comptes", true);
			// Nom Organisme

			$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
			$this->menuitem("!".$data, null, "Comptes", true);
			/*
			 $this->menuitem("@fiche_organisme_c@".$fiche_organisme, dispatch_url("organisme.organisme", "edit", array (
			 "atkselector" => "organisme.id='" . $organismeid . "'"
			 )), "Comptes", true);
			 */
			// Rechercher
			$this->menuitem("Rechercher_c", dispatch_url("organisme.compte", "admin", array (
			"atkfilter" => "organisme_compte.id_organisme=$organismeid and organisme_compte.code like '5%'"
			)), "Comptes", true);

			// Créer
			//		$this->menuitem("Créer", dispatch_url("organisme.organisme_compte", "add",array
			//			"atkfilter" => "app_recent_use.type_entite='compte' and app_recent_use.id_individu='" . $id_individu . "'"
			//		)), "Comptes", true);
			//
			$this->menuitem("-", null, "Comptes", true);
			// Nom Compte
			//		descripteur_compte_comptable($id_compte, $aide='o')
			($compteid>0) ? ($data=$node->descripteur_compte_comptable($compteid, 'n')) : ($data="Pas de compte") ;
			$this->menuitem("!".$data, null, "Comptes", true);
			/*
			 $this->menuitem("@fiche_compte_c@".$fiche_compte, dispatch_url("organisme.compte", "edit", array (
			 "atkselector" => "organisme_compte.id='" . $compteid . "'"
			 )), "Comptes", true);
			 */
			// Internet
			$this->menuitem("Site_de_la_banque_c", $url_banque, "Comptes", true);
			//		$this->menuitem("Site de la banque", href($url_banque,"xxx",SESSION_DEFAULT,false, 'target="_blank"'), "Comptes", true);

			// Lignes écritures

			$data = $db->getrows("SELECT count(id) as nombre from organisme_ligne_ecriture_comptable where organisme_ligne_ecriture_comptable.id_compte ='" . $compteid . "' ");
			$this->menuitem("Ecritures_c"."#".$data[0]["nombre"], dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ligne_ecriture_comptable.id_compte ='" . $compteid . "'"
			)), "Comptes", true);
			// Lignes écritures non remisées
			$data = $db->getrows("SELECT count(id) as nombre from organisme_ligne_ecriture_comptable where organisme_ligne_ecriture_comptable.id_compte ='" . $compteid . "'
			 and id_releve is null and id_remise is null");
			$this->menuitem("Ecritures_non_remises_c"."#".$data[0]["nombre"],  dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
			"atkfilter" => "organisme_ligne_ecriture_comptable.id_compte ='" . $compteid . "' and id_releve is null and id_remise is null"
			)), "Comptes", true);
			// Remises en banque
			$data = $db->getrows("SELECT count(id) as nombre from organisme_remise_banque where organisme_remise_banque.id_compte_banque ='" . $compteid . "'");
			$this->menuitem("Remises_c"."#".$data[0]["nombre"],  dispatch_url("organisme.remise_banque", "admin", array (
			"atkfilter" => "organisme_remise_banque.id_compte_banque ='" . $compteid . "'",
			"id_compte" => $compteid
			)), "Comptes", true);
			// Remises non rapprochées
			$data = $db->getrows("SELECT count(id) as nombre from organisme_remise_banque where organisme_remise_banque.id_compte_banque ='" . $compteid . "'  and id_releve is null");
			$this->menuitem("Remises_non_rapprochees_c"."#".$data[0]["nombre"],  dispatch_url("organisme.remise_banque", "admin", array (
			"atkfilter" => "organisme_remise_banque.id_compte_banque ='" . $compteid . "' and id_releve is null ",
			"id_compte" => $compteid
			)), "Comptes", true);
			/*	// Préparation des Remises en banque
			 $this->menuitem("Remises : préparation", dispatch_url("organisme.compte", "preparation_remise_banque", array
			 "atkselector" => "organisme_compte.id='" . $compteid. "'",
			 "id_organisme" => $organismeid,
			 "id" => $compteid
				)),  "Comptes", true);
				*/
			// Relevés
			$data = $db->getrows("SELECT count(id) as nombre from organisme_releve_banque  where organisme_releve_banque.id_compte_banque ='" . $compteid . "'");
			$this->menuitem("Relevés_c"."#".$data[0]["nombre"], dispatch_url("organisme.releve_banque", "admin", array (
			"atkfilter" => "organisme_releve_banque.id_compte_banque ='" . $compteid . "'"
			)), "Comptes", true);
			// Endosser
			$this->menuitem("Endosser_c", dispatch_url("organisme.compte", "document", array (
			"atkselector" => "organisme_compte.id='" . $compteid . "'",
			"id" => $compteid,
			"atkcode" => "1"
			)), "Comptes", true);
			//
			$this->menuitem("-", null, "Comptes", true);

		}
		if ($topmenu=="Lieux_l")
		{

			// TOP LIEUX
			// Lieux_l
			//		$this->menuitem("Lieux_l", "", "main", true);
			//			$this->menuitem("Lieux_l", "", "Lieux_l", true);
			//			$this->menuitem("-", "", "Lieux_l", true);
			// Individus l
			$this->menuitem('!<b>Géolocaliser des individus</b>', "", "Lieux_l", true);
			// Code Postal
			$data = $db->getrows("SELECT count(distinct code_postal,province_etat, id_pays) as nombre from type_cp_ville_pays ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Code_Postal_li"."#".$nombre, dispatch_url("table.v_lieu_cp", "admin", array ()), "Lieux_l", true);
			// Pays _1
			$data = $db->getrows("SELECT count(id) as nombre from type_pays ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Pays_li"."#".$nombre, dispatch_url("table.pays", "admin", array (
			"atgordre" => "nb_individus"
			)), "Lieux_l", true);
			// Province/Département
			$data = $db->getrows("SELECT count(distinct province_etat, id_pays) as nombre from type_cp_ville_pays ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Province/Département_li"."#".$nombre, dispatch_url("table.v_lieu_province", "admin", array ()), "Lieux_l", true);
			// Ville
			$data = $db->getrows("SELECT count(distinct ville,province_etat, id_pays) as nombre from type_cp_ville_pays ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Ville_li"."#".$nombre, dispatch_url("table.v_lieu_ville", "admin", array ()), "Lieux_l", true);
			//

			$this->menuitem("-", "", "Lieux_l", true);
			// Individus l
			$this->menuitem('!<b>Géolocaliser des observations</b>', "", "Lieux_l", true);
			/*			// Code Postal
			 $data = $db->getrows("SELECT count(id_pays) as nombre from v_lieu_cp ");
			 $nombre = $data[0]["nombre"];
			 $this->menuitem("Code_Postal_li"."#".$nombre, dispatch_url("table.v_lieu_cp", "admin", array ()), "Lieux_l", true);
			 */
			// Pays _1
			$data = $db->getrows("SELECT count(id) as nombre from type_pays where type_pays.id in (select distinct p.id
from
biodiversite_observation o,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id ) ");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Pays_li"."#".$nombre, dispatch_url("table.pays", "admin", array (
			 "atgordre" => "bio_observations"
			 )), "Lieux_l", true);
			 /*
			  // Province/Département
			  $data = $db->getrows("SELECT count(id_pays) as nombre from v_lieu_province ");
			  $nombre = $data[0]["nombre"];
			  $this->menuitem("Province/Département_li"."#".$nombre, dispatch_url("table.v_lieu_province", "admin", array ()), "Lieux_l", true);
			  */			// Ville
			 $data = $db->getrows("SELECT count(distinct ville,province_etat, id_pays) as nombre from type_cp_ville_pays ");
			 $nombre = $data[0]["nombre"];
			 $this->menuitem("Ville_bili"."#".$nombre, dispatch_url("biodiversite.bv_lieu_ville", "admin", array ()), "Lieux_l", true);
			 //


			 $this->menuitem("-", null, "Lieux_l", true);
			 // Administration_l
			 $this->menuitem('!<b>Administration</b>', "", "Lieux_l", true);
			 // Codes Postaux
			 $data = $db->getrows("SELECT count(code_postal) as nombre from type_cp_ville_pays ");
			 $nombre = $data[0]["nombre"];
			 $this->menuitem("Codes_Postaux_li"."#".$nombre, dispatch_url("table.cp_ville_pays", "admin", array ()), "Lieux_l", true);
			 // Lieux
			 $data = $db->getrows("SELECT count(id) as nombre from lieu ");
			 $nombre = $data[0]["nombre"];
			 $this->menuitem("Lieux_li"."#".$nombre, dispatch_url("individu.lieu", "admin", array ()), "Lieux_l", true);
			 // Pays_2
			 $data = $db->getrows("SELECT count(id) as nombre from type_pays ");
			 $nombre = $data[0]["nombre"];
			 $this->menuitem("Pays_2_li"."#".$nombre, dispatch_url("table.pays", "admin", array ()), "Lieux_l", true);
			 $this->menuitem("-", Null, "Lieux_l", true);
			 	
		}
		if ($topmenu=="albums_google")
		{
			//TOP albums_google
			//			$this->menuitem("Picasa web albums", "", "albums_google", true);
			//			$this->menuitem("-", "", "albums_google", true);
			if ($identifiant_google_o_n == '1' || $administrateur == '1' || ($g_user["name"] == "administrator"))
			{
				$data = $db->getrows("SELECT count(id) as nombre from individu_google_feed where ( id_individu=" . $idutilisateur . " and type_feed='2') ");
				$nombre = $data[0]["nombre"];
				$data = $db->getrows("SELECT sum(taille_octets) as nombre from individu_google_feed where ( id_individu=" . $idutilisateur . " and type_feed='2') ");
				$nombre .= " / ".number_format($data[0]["nombre"],0,"",".");
				$this->menuitem("Albums"."#".$nombre, dispatch_url("individu.google_feed", "admin", array (
			"atkfilter" => "individu_google_feed.id_individu='" . $idutilisateur . "' and type_feed='2'"
			)), "albums_google", true);
			$data = $db->getrows("SELECT count(igp.id) as nombre from individu_google_photo igp, individu_google_feed igf
			 where (igp.id_album=igf.id and igf.id_individu=" . $idutilisateur . " and igf.type_feed='2') ");
			$nombre = $data[0]["nombre"];
			$data = $db->getrows("SELECT sum(igp.size) as nombre from individu_google_photo igp, individu_google_feed igf
			 where (igp.id_album=igf.id and igf.id_individu=" . $idutilisateur . " and igf.type_feed='2') ");
			$nombre .= " / ".number_format($data[0]["nombre"],0,"",".");
			$this->menuitem("Photos"."#".$nombre, dispatch_url("individu.google_photos", "admin", array (
			"atkfilter" => "individu_google.id_album in (select id from individu_google_feed where id_individu='" . $idutilisateur . "' and type_feed='2')"
			)), "albums_google", true);
			$this->menuitem("(Synchroniser albums)", dispatch_url("individu.google_feed", "api_google", array (
			"feed_type" => "photos"
			)), "albums_google", true);
			}
			/*
			 * 			$this->menuitem("Contacts", dispatch_url("individu.google_feed", "api_google", array (
			 "feed_type" => "contacts"
			 )), "Rd", true);
			 $this->menuitem("Photos", dispatch_url("individu.google_feed", "api_google", array (
			 "feed_type" => "photos"
			 )), "Rd", true);
			 */
		}
		if ($topmenu=="contacts_google")
		{

			//TOP contacts_google
			//		$this->menuitem("Contacts Google", "", "contacts_google", true);
			//			$this->menuitem("-", "", "contacts_google", true);
			if ($identifiant_google_o_n == '1' || $administrateur == '1' || ($g_user["name"] == "administrator"))
			{
				$data = $db->getrows("SELECT count(id) as nombre from individu_google_feed where ( id_individu=" . $idutilisateur . " and type_feed='1') ");
				$nombre = $data[0]["nombre"];
				$this->menuitem("Google_contacts"."#".$nombre, dispatch_url("individu.google_feed", "admin", array (
			"atkfilter" => "individu_google_feed.id_individu='" . $idutilisateur . "' and type_feed='1'"
			)), "contacts_google", true);

			$this->menuitem("(Synchroniser contacts)", dispatch_url("individu.google_feed", "maj_contacts", array (
			"utilisateur" => $idutilisateur
			)), "contacts_google", true);
			$this->menuitem("(Lister contacts)", dispatch_url("individu.google_feed", "api_google", array (
			"feed_type" => "contacts"
			)), "contacts_google", true);

			}

		}
		if ($topmenu=="Outils")
		{

			//TOP OUTILS
			// Télécharger

			$this->menuitem("Téléchargements", "", "Outils", true);
			$this->menuitem("-", "", "Outils", true);
			// 7 zip
			$this->menuitem("7 zip", "http://downloads.sourceforge.net/sevenzip/", "Outils", true);
			// Acrobat reader
			$this->menuitem("Acrobat reader", "http://www.01net.com/outils/telecharger/windows/Internet/internet_utlitaire/fiches/tele14537.html", "Outils", true);
			// Firebug
			$this->menuitem("Firebug", "https://addons.mozilla.org/fr/firefox/addon/1843", "Outils", true);
			// Firefox
			$this->menuitem("Firefox", "http://www.01net.com/outils/telecharger/windows/Internet/navigateur/fiches/tele25711.html", "Outils", true);
			// Eclipse
			$this->menuitem("Eclipse", "http://www.eclipse.org/downloads/", "Outils", true);
			// Gimp
			$this->menuitem("Gimp", "http://sourceforge.net/project/downloading.php?groupname=gimp-win&filename=gimp-2.4.2-i686-setup.exe&use_mirror=mesh", "Outils", true);
			// Open Office
			$this->menuitem("Open Office", "http://fr.openoffice.org/about-downloads-contrib.html?product=OpenOffice.org&os=winwjre&lang=fr&version=2.4.1", "Outils", true);
			// PDFCreator
			$this->menuitem("PDFCreator", "https://sourceforge.net/project/showfiles.php?group_id=57796&package_id=53473&release_id=563252", "Outils", true);
			// SnIco
			$this->menuitem("SnIco", "http://www.clubic.com/lancer-le-telechargement-9533-0-snico-edit.html", "Outils", true);
			// Wink tutorial
			$this->menuitem("Wink tutorial", "http://www.clubic.com/lancer-le-telechargement-19160-0-wink.html", "Outils", true);
			//
			//			$this->menuitem("qr", "http://chart.apis.google.com/chart?cht=qr&chs=120x120&chl=MECARD%3AN%3AGuy+Gourmellet%3BTEL%3A0240267464%3BURL%3Awww.wikistoma.org%3BEMAIL%3Aguy.gourmellet%40gmail.com%3BADR%3A2%2C+la+M%C3%A9tellerie+44310+St+Colomban%3BNOTE%3AMemo%3B%3B", "Outils", true);
			//
			$this->menuitem('-', "", "Outils", true);
			//
			// Guides

			// Bien communiquer
			//			$this->menuitem("Guides", "", "Outils", true);
			//			$this->menuitem("-", "", "Outils", true);
			$this->menuitem("Bien communiquer", dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='395'",
			"afficher_direct" => "o"
			)), "Outils", true);
			// Comprendre la comptabilité
			$this->menuitem("Comprendre la comptabilité", dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='394'",
			"afficher_direct" => "o"
			)), "Outils", true);
			// Guide du président
			$this->menuitem("Guide du président", dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='397'",
			"afficher_direct" => "o"
			)), "Outils", true);
			// Guide du trésorier
			$this->menuitem("Guide du trésorier", dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='396'",
			"afficher_direct" => "o"
			)), "Outils", true);
			// Transparence et associations
			$this->menuitem("Transparence et associations", dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='176'",
			"afficher_direct" => "o"
			)), "Outils", true);
			// Principe application
			$this->menuitem("Principe application", "http://www.wikistoma.org/wiki",  "Outils", true);
			$this->menuitem('-', "", "Outils", true);
		}
		if ($topmenu=="Administrer")
		{


			// TOP ADMINISTRATION

			if ($administrateur == '1' || ($g_user["name"] == "administrator")) {
				// Administrer
				//		$this->menuitem('Administrer', "", "main", true);
				//				$this->menuitem("Administration", "", "Administrer", true);
				//				$this->menuitem("-", "", "Administrer", true);
				// Aide
				//			$this->menuitem("Aide", dispatch_url("application.aide", "admin"), "Administrer", true);
				// Demandes
				$this->menuitem("-", "", "Administrer", true);
				if ($en_travaux_o_n=='1')
				{
					$url=dispatch_url("organisme.organisme", "travaux", array (
			"atktravaux" => "fin" ));
					$this->menuitem("En travaux : arrêter", $url, "Administrer", true);
				}
				else {
					$url=dispatch_url("organisme.organisme", "travaux", array (
			"atktravaux" => "debut" ));
					$this->menuitem("En travaux : démarrer", $url, "Administrer", true);
				}
			if ($tracer_mysqldb_query_o_n=='1')
				{
					$url=dispatch_url("organisme.organisme", "tracer_mysqldb", array (
			"atktracer_mysqldb" => "fin" ));
					$this->menuitem("Tracer query mysqldb : arrêter", $url, "Administrer", true);
				}
				else {
					$url=dispatch_url("organisme.organisme", "tracer_mysqldb", array (
			"atktracer_mysqldb" => "debut" ));
					$this->menuitem("Tracer query mysqldb : démarrer", $url, "Administrer", true);
				}
				$this->menuitem("-", "", "Administrer", true);
				$this->menuitem("Hébergeur Dreamhost (guy.gourmellet@gmail.com mdpc)", "https://panel.dreamhost.com/index.cgi", "Administrer", true);
				$this->menuitem("-> Manage account", "https://panel.dreamhost.com/index.cgi?tree=billing.accounts&", "Administrer", true);
				$this->menuitem("-> Manage domains", "https://panel.dreamhost.com/index.cgi?tree=domain.manage&", "Administrer", true);
				$this->menuitem("-> Manage vps resources", "https://panel.dreamhost.com/index.cgi?tree=vserver.usage&", "Administrer", true);
				$this->menuitem("-> Manage MySql", "https://panel.dreamhost.com/index.cgi?tree=goodies.mysql&", "Administrer", true);
				$this->menuitem("-> phpMyAdmin (webmaster rf9999)", "http://www.wikistoma.org/association/modules/phpMyAdmin//", "Administrer", true);
				//		https://panel.dreamhost.com/index.cgi?tree=billing.accounts&
				$this->menuitem("-", "", "Administrer", true);
				$this->menuitem("Noms de domaine (Namebay (IL90969 IL86482) mdpc) ", "http://www.namebay.com/manage/main.asp", "Administrer", true);
				$this->menuitem("-", "", "Administrer", true);
				$this->menuitem("Activité_heure", dispatch_url("application.v_atkeventlog", "stats_heure", array (
			"jour_debut" => "" . gmdate('Y-m-d') . ""
			)), "Administrer", true);
			$this->menuitem("Activité_jour", dispatch_url("application.v_atkeventlog", "stats_jour", array (
			"mois_debut" => "" . gmdate('Y-m') . ""
			)), "Administrer", true);
			$this->menuitem("Activité_mois", dispatch_url("application.v_atkeventlog", "stats_mois", array (
			"an_debut" => "" . gmdate('Y') . ""
			)), "Administrer", true);
			$this->menuitem("Activité_an", dispatch_url("application.v_atkeventlog", "stats_an"), "Administrer", true);


			$this->menuitem("Demandes", dispatch_url("application.demande", "admin"), "Administrer", true);
			// Debugs
			$this->menuitem("Debugs", dispatch_url("profil.debug", "admin"), "Administrer", true);
			// Activité utilisateurs
			// Ex Administration
			$this->menuitem("Ex Administration", "http://wwww.wikistoma.org/association/top.old.php", "Administrer", true);
			// Export Contacts
			$this->menuitem("Export Contacts", dispatch_url("individu.individu", "listeecran", array (
				"atkcode" => '1'
				)), "Administrer", true);
				// Globles
			$this->menuitem("Globales", dispatch_url("application.globales", "edit", array (
			"atkfilter" => "app_globales.id='1'"
			)), "Administrer", true);
			// Global
	$this->menuitem('Global', "target_menu".'menu.php?atkmenutop=Global', "Administrer", true);
	//		$url= href('menu.php?atkmenutop=Global',atktext("menu_Global", "atk"),SESSION_DEFAULT, false, 'target="menu" ');
	//		$this->menuitem('Global', $url, "Administrer", true);
			
			
			//		$divers=href('menu.php?atkmenutop=Divers', atktext("Divers", "atk"), SESSION_DEFAULT, false, 'target="menu"' . $menutip) . $delimiter;
			// Logs
			$this->menuitem("Logs", dispatch_url("profil.log", "admin"), "Administrer", true);
			// Activité utilisateurs

			// Normalisation individus
			$this->menuitem("Normalisation individus", dispatch_url("individu.individu", "normalisation"), "Administrer", true);
			// Normalisation organismes
			$this->menuitem("Normalisation organismes", dispatch_url("organisme.organisme", "normalisation"), "Administrer", true);
			// Menus
			//			$this->menuitem("Menus", dispatch_url("menu.menu", "admin"), "Administrer", true);

			$this->menuitem("search db_search (webmaster rf9999)", "http://www.wikistoma.org/association/modules/search/db_search.php/", "Administrer", true);
			// Profils
			$this->menuitem("Profils", dispatch_url("profil.profil", "admin"), "Administrer", true);
			// Statistiques
			//			$this->menuitem("Statistiques Sites", "https://www.google.com/analytics/home/admin?scid=3719797", "Administrer", true);
			// Administrers
			$this->menuitem("Utilisateurs", dispatch_url("profil.utilisateur", "admin"), "Administrer", true);
			// Webmestre
			//			$this->menuitem("Webmestre Sites", "https://www.google.com/webmasters/tools/", "Administrer", true);
			//
			$this->menuitem('-', "", "Administrer", true);

				



				
			}

		}
		if ($topmenu=="Global" )
		{
				
			// TOP Global

			$this->menuitem("<b>GLOBAL</b>", "", "Global", true);
			$this->menuitem("-", "", "Global", true);
			// Profils
			$this->menuitem("profils", dispatch_url("profil.profil", "admin"), "Global", true);
			// Utilisateurs
			$this->menuitem("utilisateurs", dispatch_url("profil.utilisateur", "admin"), "Global", true);
			// préférences
			$this->menuitem("préferences", dispatch_url("profil.userprefs", "admin"), "Global", true);
			$this->menuitem("-", "", "Global", true);
			// Activités(Individu)
			$this->menuitem("activites(Individu)", dispatch_url("individu.activite_i", "admin"), "Global", true);
			// Attributs(Individu)
			$this->menuitem("attributs(Individu)", dispatch_url("individu.attribut_i", "admin"), "Global", true);
			// Compétences(Individu)
			$this->menuitem("competences(Individu)", dispatch_url("individu.competence_i", "admin"), "Global", true);
			// Contacts(Individu)
			$this->menuitem("contacts(Individu)", dispatch_url("individu.contact_i", "admin"), "Global", true);
			// Cotisations(Individu)
			$this->menuitem("cotisations(Individu)", dispatch_url("individu.cotisation_i", "admin"), "Global", true);
			// Cotorep(Individu)
			$this->menuitem("cotorep(Individu)", dispatch_url("individu.cotorep_i", "admin"), "Global", true);
			// Fonctions(Individu)
			$this->menuitem("fonctions(Individu)", dispatch_url("individu.fonction_i", "admin"), "Global", true);
			// Groupes de travail i
			$this->menuitem("groupes_travail(Individu)", dispatch_url("individu.groupe_travail_i", "admin"), "Global", true);
			// Inscriptions(Individu)
			$this->menuitem("inscriptions(Individu)", dispatch_url("individu.inscription_i", "admin"), "Global", true);
			// Immatriculations(Individu)
			$this->menuitem("immatriculations(Individu)", dispatch_url("individu.immatriculation_i", "admin"), "Global", true);
			// Marque pages(Individu)
			$this->menuitem("bookmarks(Individu)", dispatch_url("individu.bookmark_i", "admin"), "Global", true);
			// Rencontres(Individu)
			$this->menuitem("rencontres(Individu)", dispatch_url("individu.rencontre_i", "admin"), "Global", true);
			// Sauvegardes (organismes)
			//			$this->menuitem("sauvegardes(Individu)", dispatch_url("application.sauvegarde", "admin"), "Global", true);
			// Lieux(Individu)
			$this->menuitem("lieux(Individu)", dispatch_url("individu.individu_lieu", "admin"), "Global", true);
			// Listes(Individu)
			$this->menuitem("listes(Individu)", dispatch_url("individu.individu_liste", "admin"), "Global", true);
			$this->menuitem("-", "", "Global", true);
			// Compétences(Individu)
			$this->menuitem("competences(Organisme)", dispatch_url("organisme.competence_o", "admin"), "Global", true);
			// Comptes(Organisme)
			$this->menuitem("comptes(Organisme)", dispatch_url("organisme.compte", "admin"), "Global", true);
			// Contrats(Organisme)
			$this->menuitem("contrats(Organisme)", dispatch_url("organisme.contrat", "admin"), "Global", true);
			// Cotisations(Organisme)
			$this->menuitem("cotisations(Organisme)", dispatch_url("organisme.cotisation", "admin"), "Global", true);
			// Documents(Organisme)
			$this->menuitem("documents(Organisme)", dispatch_url("organisme.document", "admin"), "Global", true);
			// Documents communication(Organisme)
			$this->menuitem("documents communication(Organisme)", dispatch_url("organisme.document_communication", "admin"), "Global", true);
			// Documents officiels(Organisme)
			$this->menuitem("documents officiels(Organisme)", dispatch_url("organisme.document_officiel", "admin"), "Global", true);
			// Domaines(Organisme)
			$this->menuitem("domaines(Organisme)", dispatch_url("organisme.domaine", "admin"), "Global", true);
			// Ecritures comptables(Organisme)
			$this->menuitem("ecritures comptables(Organisme)", dispatch_url("organisme.ecriture_comptable", "admin"), "Global", true);
			// Financements(Organisme)
			$this->menuitem("financements(Organisme)", dispatch_url("organisme.financement", "admin"), "Global", true);
			// Fournitures(Organisme)
			$this->menuitem("fournitures(Organisme)", dispatch_url("organisme.fourniture", "admin"), "Global", true);
			// Gazettes(Organisme)
			$this->menuitem("gazettes(Organisme)", dispatch_url("organisme.gazette", "admin"), "Global", true);
			// Groupes(Organisme)
			$this->menuitem("groupes_travail(Organisme)", dispatch_url("organisme.groupe_travail", "admin"), "Global", true);
			// Images
			$this->menuitem("images(Tout)", dispatch_url("application.image_a", "admin"), "Global", true);
			// Immatriculations o
			$this->menuitem("immatriculations(Organisme)", dispatch_url("organisme.immatriculation", "admin"), "Global", true);
			// Infolettres(Organisme)
			$this->menuitem("infolettres(Organisme)", dispatch_url("organisme.infolettre", "admin"), "Global", true);
			// Journaux comptables(Organisme)
			$this->menuitem("journaux comptables(Organisme)", dispatch_url("organisme.journal_comptable", "admin"), "Global", true);
			// Lieux(Organisme)
			$this->menuitem("lieux(Organisme)", dispatch_url("organisme.organisme_lieu", "admin"), "Global", true);
			// Lieux de rencontres
			$this->menuitem("Lieux_Rencontres (Organisme)", dispatch_url("organisme.lieu_rencontre", "admin"), "Global", true);
			// Contrats accordés
			$this->menuitem("Contrats_Lieux_Rencontre (Organisme)", dispatch_url("organisme.contrat_lieu_rencontre", "admin"), "Global", true);
			// Observations
			$this->menuitem("Observations (Organisme)", dispatch_url("biodiversite.observation", "admin"), "Global", true);

			// Observations détails
			$this->menuitem("Observations détails (Organisme)", dispatch_url("biodiversite.observation_detail", "admin"), "Global", true);
			// Partenaires(Organisme)
			$this->menuitem("partenaires(Organisme)", dispatch_url("organisme.partenaire", "admin"), "Global", true);
			// Patrimoine(Organisme)
			$this->menuitem("patrimoine(Organisme)", dispatch_url("organisme.patrimoine", "admin"), "Global", true);
			// Points Observations
			$this->menuitem("Points_observations (Organisme)", dispatch_url("biodiversite.point_observation", "admin"), "Global", true);
			// Référencements(Organisme)
			$this->menuitem("referencements(Organisme)", dispatch_url("organisme.referencement", "admin"), "Global", true);
			// Règles(Organisme)
			$this->menuitem("regles(Organisme)", dispatch_url("manuel.manuel", "admin"), "Global", true);
			// Rencontres(Organisme)
			$this->menuitem("rencontres(Organisme)", dispatch_url("organisme.rencontre", "admin"), "Global", true);
			// Rencontres fournitures(Organisme)
			$this->menuitem("rencontres_fournisseurs(Organisme)", dispatch_url("organisme.rencontre_fournisseur", "admin"), "Global", true);
			// Rencontres communications(Organisme)
			$this->menuitem("rencontres_communications(Organisme)", dispatch_url("organisme.rencontre_communication", "admin"), "Global", true);
			$this->menuitem("-", null, "Global", true);
			// Sauvegardes (organismes)
			//			$this->menuitem("sauvegardes(Organisme)", dispatch_url("application.sauvegarde", "admin"), "Global", true);
			// Vacances (organismes)
			$this->menuitem("vacances(Organisme)", dispatch_url("scheduler.scheduler_vacances", "admin"), "Global", true);
		}
		if ($topmenu=="Divers")
		{
				

			// TOP DIVERS
			// Gis

			$this->menuitem("!<b>GIS</b>", "", "Divers", true);
			$this->menuitem("-", "", "Divers", true);
			// Régions
			$this->menuitem("Régions", dispatch_url("table.type_region_pays", "admin"), "Divers", true);
			// Repères
			$this->menuitem("Repères", dispatch_url("gis.placemark", "admin"), "Divers", true);
			// Symboles
			$this->menuitem("Symboles", dispatch_url("gis.icone", "admin"), "Divers", true);
			// Zones
			$this->menuitem("Zones", dispatch_url("table.type_zone_region_pays", "admin"), "Divers", true);
			//
			$this->menuitem("-", null, "Divers", true);
			// Attributs Repères
			$this->menuitem("Attributs Repères", dispatch_url("table.type_attribut_placemark", "admin"), "Divers", true);
			// Marée Météo
			$this->menuitem("Marée Météo", dispatch_url("table.maree_meteo", "admin"), "Divers", true);
			// Symboles Gps
			$this->menuitem("Symboles Gps", dispatch_url("table.type_symbole_gps", "admin"), "Divers", true);
			// Types Repères
			$this->menuitem("Types Repères", dispatch_url("table.type_placemark", "admin"), "Divers", true);
			// Types symboles
			$this->menuitem("Types symboles", dispatch_url("table.type_icone", "admin"), "Divers", true);
			//
			$this->menuitem("-", null, "Divers", true);
			// Golf

			$this->menuitem("!<b>Golf</b>", "", "Divers", true);
			$this->menuitem("-", "", "Divers", true);
			// Catégories
			$this->menuitem("Catégories", dispatch_url("table.categorie_golf", "admin"), "Divers", true);
			// Compétitions
			$this->menuitem("Compétitions", dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme_parcours > 0"
			)), "Divers", true);
			// Compétitions
			$this->menuitem("Compétiteurs", dispatch_url("individu.carte_golf", "admin"), "Divers", true);
			// Parcours
			$this->menuitem("Parcours", dispatch_url("organisme.golf_parcours", "admin"), "Divers", true);

			//			http://www.wikistoma.org/association/dispatch.php?atknodetype=tournoi.tournoi&atkaction=admin&atkfilter=organisme_tournoi.id_organisme%20%3D%27366%27&atklevel=-1&atkprevlevel=0&

			// Tournois
			$this->menuitem("Tournois", dispatch_url("tournoi.tournoi", "admin"), "Divers", true);

			//			$this->menuitem("Tournoi simple", atkconfig("atkroot")."modules/tournoi/example_basic.php", "Divers", true);
			//					$this->menuitem("Tournoi full", atkconfig("atkroot")."modules/tournoi/example_full.php", "Divers", true);
			//
			$this->menuitem("-", null, "Divers", true);

			$this->menuitem("!<b>Biodiversité</b>", "", "Divers", true);
			$this->menuitem("-", "", "Divers", true);
			// Rang taxinomique
			$this->menuitem("Rang_taxinomique", dispatch_url("biodiversite.rang_taxinomique", "admin"), "Divers", true);
			// Statut taxinomique
			$this->menuitem("Statut_taxinomique", dispatch_url("biodiversite.statut_taxinomique", "admin"), "Divers", true);
			// Taxinomie
			$this->menuitem("Taxinomie", dispatch_url("biodiversite.taxinomie", "admin"), "Divers", true);
			//
			$this->menuitem("-", null, "Divers", true);
			$this->menuitem("!<b>Education thérapeutique</b>", "", "Divers", true);
			$this->menuitem("-", "", "Divers", true);
			// etp coeur
			$this->menuitem("Coeur", dispatch_url("etp.coeur", "admin", array (
			"atkfilter" => "etp_coeur.id_individu='" . $idutilisateur . "'"
			)), "Divers", true);
			// etp coeur
			$this->menuitem("Poids", dispatch_url("etp.poids", "admin", array (
			"atkfilter" => "etp_poids.id_individu='" . $idutilisateur . "'"
			)), "Divers", true);

			$this->menuitem("-", null, "Divers", true);
				
		}
		if ($topmenu=="Rd")
		{
				
			$this->menuitem("-", null, "main", true);

			//  TOP R&D
			// DreamHost
			
/*			$this->menuitem("MySql Table", dispatch_url("application.mysql_table", "admin", array (
			"atkselector" => "type_audience.id='5'",
					"mysql_table"=> "type_audience"
			)), "Rd", true);
*/			
			$this->menuitem("MySql Table", dispatch_url("application.mysql_table", "edit",
					array("mysql_table"=>"organisme",
							 "atkselector"=>"organisme.id=2")), "Rd", true);
			$this->menuitem("!<b>Serveur web</b>", "", "Rd", true);

			$this->menuitem("-", "", "Rd", true);
			//			$this->menuitem("Compte", "https://panel.dreamhost.com/index.cgi?tree=billing.accounts&", "Rd", true);
			$this->menuitem("Panel", "https://panel.dreamhost.com/", "Rd", true);
			$this->menuitem("phpMyAdmin", "http://www.wikiservas.net/dh_phpmyadmin/mysql.wikiservas.net/", "Rd", true);
			$this->menuitem("phpInfo", "modules/application/phpinfo.php", "Rd", true);
			$this->menuitem("Webftp", "https://webftp.dreamhost.com/index.php", "Rd", true);
			$this->menuitem("Support wiki", "http://wiki.dreamhost.com/", "Rd", true);
				

			// Editeur
			$this->menuitem("Editeur fichier", dispatch_url("editeur.editeur", "admin"), "Rd", true);




			$this->menuitem("-", "", "Rd", true);
			$this->menuitem("!<b>Atk</b>", "", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
			// Api
			$this->menuitem("Api", "http://atk.achievo.org/docs/atk/latest/", "Rd", true);
			// Bug tracker
			$this->menuitem("Bugs", "http://bugzilla.achievo.org/index.cgi", "Rd", true);


			// Download
			$this->menuitem("Download", "http://www.atk-framework.com/download/", "Rd", true);
			// Fck Editor
			$this->menuitem("Fck Editor", "http://docs.fckeditor.net/FCKeditor_2.x/Users_Guide", "Rd", true);
			// Forum
			$this->menuitem("Forum", "http://www.atk-framework.com/forum/", "Rd", true);
			// Site
			$this->menuitem("Site", "http://www.atk-framework.com", "Rd", true);
			// Svn
			$this->menuitem("Svn", "http://svn.ibuildings.nl/svn/atk/atk/trunk/", "Rd", true);
			// Wiki
			$this->menuitem("Wiki", "http://www.atk-framework.com/wiki/ATK", "Rd", true);
			//
			$this->menuitem('-', "", "Rd", true);

			// Références

			$this->menuitem("!<b>Manuels de référence</b>", "", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
			//		http://developer.android.com/index.html
			// http://code.google.com/apis/ajax/playground/
			// Android
			$this->menuitem("Androïd", "http://developer.android.com/index.html", "Rd", true);
			// Css
			$this->menuitem("Css", "http://www.w3.org/TR/REC-CSS1", "Rd", true);
			// Eclipse
			$this->menuitem("Eclipse", "http://www.eclipse.org/", "Rd", true);
			// Google Ajax Api
			$this->menuitem("Google Apis", "http://code.google.com/intl/fr/", "Rd", true);
			// Google Créer un compte
			$this->menuitem("Google Créer un compte", "https://www.google.com/accounts/ServiceLogin?service=mail&passive=true&rm=false&continue=https%3A%2F%2Fmail.google.com%2Fmail%2F%3Fui%3Dhtml%26zy%3Dl&bsv=zpwhtygjntrz&ss=1&scc=1&ltmpl=default&ltmplcache=2&hl=fr", "Rd", true);
			// Google Créer un site Apps
			$this->menuitem("Google Créer un site Apps", "http://www.google.com/a/cpanel/domain/new?hl=fr", "Rd", true);

			// Google App engine
			$this->menuitem("Google App engine", "http://code.google.com/intl/fr/appengine/", "Rd", true);
			// Google App inventor
			$this->menuitem("Google App inventor", "http://appinventor.googlelabs.com/", "Rd", true);
				
			// Google App Maps JavaScript API
			$this->menuitem("Google Maps JavaScript API V3", "http://code.google.com/intl/no/apis/maps/documentation/javascript/reference.html", "Rd", true);
			// Google Web Toolkit
			$this->menuitem("Google Web Toolkit (GWT)", "http://code.google.com/intl/fr-FR/webtoolkit/download.html", "Rd", true);
				
			// Html 401
			$this->menuitem("Html", "http://www.w3.org/TR/html401/cover.html#minitoc", "Rd", true);
			// Icônes
			$this->menuitem("Icônes", "http://www.iconarchive.com/show/glaze-icons-by-mart/spreadsheet-icon.html", "Rd", true);
			// Java
			$this->menuitem("Java", "http://www.wikijava.org", "Rd", true);
			// Javascript
			$this->menuitem("Javascript", "http://en.wikipedia.org/wiki/JavaScript_syntax", "Rd", true);
			// Kml
			$this->menuitem("Kml", "http://code.google.com/apis/kml/documentation/kmlreference.html", "Rd", true);
			// Mysql 5.0
			$this->menuitem("Mysql", "http://dev.mysql.com/doc/refman/5.0/fr/index.html", "Rd", true);
			// Php http://www.manuelphp.com/php
			$this->menuitem("Php1", "http://www.php.net/manual/fr/", "Rd", true);
			$this->menuitem("Php2", "http://www.manuelphp.com", "Rd", true);
			$this->menuitem("Smarty", "http://www.smarty.net/manual/fr/", "Rd", true);
			$this->menuitem("Tiny but strong (doc templates)", "http://www.tinybutstrong.com", "Rd", true);
			// Ubuntu
			$this->menuitem("Ubuntu", "http://www.ubuntu-fr.org/", "Rd", true);
			// W3Schools
			$this->menuitem("W3Schools", "http://www.w3schools.com/", "Rd", true);
			// Xhtml
			$this->menuitem("Xhtml", "http://www.w3.org/TR/2003/WD-xhtml2-20030506/", "Rd", true);
			// Xml
			$this->menuitem("Xml", "http://www.w3.org/TR/2000/REC-xml-20001006", "Rd", true);
				
			$this->menuitem('-', "", "Rd", true);
			$this->menuitem("!<b>Google API</b>", "", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
			$this->menuitem("Contacts", dispatch_url("individu.google_feed", "api_google", array (
			"feed_type" => "contacts"
			)), "Rd", true);
			$this->menuitem("Photos", dispatch_url("individu.google_feed", "api_google", array (
			"feed_type" => "photos"
			)), "Rd", true);
			$this->menuitem("Contacts Photos", dispatch_url("individu.google_feed", "api_google", array (
			"feed_type" => "contacts_photos"
			)), "Rd", true);


			$this->menuitem("Blogger.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Blogger.php", "Rd", true);
			$this->menuitem("Calendar.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Calendar.php", "Rd", true);
			$this->menuitem("Docs.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Docs.php", "Rd", true);
			$this->menuitem("Gapps.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Gapps.php", "Rd", true);
			$this->menuitem("Gbase.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Gbase.php", "Rd", true);
			$this->menuitem("Health.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Health.php", "Rd", true);
			$this->menuitem("InstallationChecker.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/InstallationChecker.php", "Rd", true);
			$this->menuitem("Photos.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Photos.php", "Rd", true);
			$this->menuitem("Spreadsheet-ClientLogin.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/Spreadsheet-ClientLogin.php", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
			$this->menuitem("MyLibrary/demo.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/MyLibrary/demo.php", "Rd", true);
			$this->menuitem("3LeggedOAuth/index.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/3LeggedOAuth/index.php", "Rd", true);
			$this->menuitem("BooksBrowser/index.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/BooksBrowser/index.php", "Rd", true);
			$this->menuitem("YouTubeVideoApp/index.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/YouTubeVideoApp/index.php", "Rd", true);
			$this->menuitem("YouTubeVideoBrowser/index.php", "http://www.wikistoma.org/association/modules/demos/Zend/Gdata/YouTubeVideoBrowser/index.php", "Rd", true);
			$this->menuitem("-", "", "Rd", true);


			$this->menuitem("!<b>Tests</b>", "", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
			//
			$this->menuitem("Géolocalisation", "modules/geo/geo.html", "Rd", true);
			$this->menuitem("D3-Google-1", "modules/d3-google/demos_d3google/001.php", "Rd", true);
			$this->menuitem("D3-Google-2", "modules/d3-google/demos_d3google/002.php", "Rd", true);
			$this->menuitem("D3-Google-3", "modules/d3-google/demos_d3google/003.php", "Rd", true);
			$this->menuitem("D3-Google-4", "modules/d3-google/demos_d3google/004.php", "Rd", true);
			$this->menuitem("D3-Google-5", "modules/d3-google/demos_d3google/005.php", "Rd", true);
			$this->menuitem("D3-Google-6", "modules/d3-google/demos_d3google/006.php", "Rd", true);
			$this->menuitem("D3-Google-7", "modules/d3-google/demos_d3google/007.php", "Rd", true);
			$this->menuitem("D3-Google-8", "modules/d3-google/demos_d3google/008.php", "Rd", true);
			$this->menuitem("D3-Google-12", "modules/d3-google/demos_d3google/012.php", "Rd", true);
			$this->menuitem("D3-Google-14", "modules/d3-google/demos_d3google/014.php", "Rd", true);
			
			$this->menuitem("D3-1", "modules/d3-google/demos_d3/001.php", "Rd", true);
			$this->menuitem("D3-2", "modules/d3-google/demos_d3/002.php", "Rd", true);
			$this->menuitem("D3-3", "modules/d3-google/demos_d3/003.php", "Rd", true);
			$this->menuitem("D3-4", "modules/d3-google/demos_d3/004.php", "Rd", true);
			$this->menuitem("D3-5", "modules/d3-google/demos_d3/005.php", "Rd", true);
			$this->menuitem("D3-6", "modules/d3-google/demos_d3/006.php", "Rd", true);
			$this->menuitem("D3-20", "modules/d3-google/demos_d3/020.php", "Rd", true);
			$this->menuitem("D3-30", "modules/d3-google/demos_d3/030.php", "Rd", true);
			$this->menuitem("D3-40", "modules/d3-google/demos_d3/040.php", "Rd", true);
			$this->menuitem("D3-41", "modules/d3-google/demos_d3/041.php", "Rd", true);
			$this->menuitem("D3-60", "modules/d3-google/demos_d3/060.php", "Rd", true);
			
			
			
			$this->menuitem("Graphiques", "http://www.wikistoma.org/association/modules/gChart/gChartExample2.php", "Rd", true);
			$this->menuitem("Test vitesse Internet",  "http://performance.toast.net", "Rd", true);
			// debugging
			$deb = href("index.php?atkdebug[key]=titi", 'Mise au point', SESSION_NEW, false, 'target="_top"');
			$this->menuitem($deb, "",  "Rd", true);
			//			$this->menuitem("Mise au point",atkHref("index.php?atkdebug[key]=titi","", $sessionstatus=SESSION_NEW, false, 'target="_top"') , "Rd", true);


			// Tests
			$this->menuitem("gbif", "http://www.wikistoma.org/association/modules/test/testubio_keycode.php", "Rd", true);
			$this->menuitem("Rapports bio", dispatch_url("biodiversite.biodiversite_rapports", "observation"), "Rd", true);
			$this->menuitem("Tests Guy", dispatch_url("test.testguy", "intro"), "Rd", true);
			// Simpletest tutorial
			$this->menuitem("db_search", "http://www.wikistoma.org/association/modules/search/db_search.php", "Rd", true);
			$this->menuitem("Simpletest tutorial", "http://www.lastcraft.com/first_test_tutorial.php", "Rd", true);
			$this->menuitem("Simpletest unit_tests", atkconfig("atkroot")."simpletest/test/unit_tests.php", "Rd", true);
			$this->menuitem("Simpletest all_tests", atkconfig("atkroot")."simpletest/test/all_tests.php", "Rd", true);
			$this->menuitem("Tests atk", atkconfig("atkroot")."test.php", "Rd", true);
			$this->menuitem("Gdata Checker", atkconfig("atkroot")."modules/demos/Zend/Gdata/InstallationChecker.php", "Rd", true);
			$this->menuitem("Calendar", atkconfig("atkroot")."modules/demos/Zend/Gdata/Calendar.php", "Rd", true);
			$this->menuitem("-", "", "Rd", true);
		}
		if ($topmenu=="Traitements")
		{

			if ($traitement_o_n == '1' || $administrateur == '1' || ($g_user["name"] == "administrator"))

			{
				// TOP TRAITEMENTS
				//			$this->menuitem("Traitements_top", "", "Traitements", true);
				//		$this->menuitem("-", "", "Traitements", true);
				// Nom Organisme

				$data=$node->descripteur_organisme($organismeid,'n','n','0','menu') ;
				$this->menuitem("!".$data, null, "Traitements", true);

				/*		$this->menuitem($fiche_organisme, dispatch_url("organisme.organisme", "edit", array (
				 "atkselector" => "organisme.id='" . $organismeid . "'"
				 )), "Traitements", true);
				 */
					
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>1-Préparation</b>", "", "Traitements", true);
				// Cotisations fédé seulement
				$this->menuitem("Cotisations fédé seulement", dispatch_url("organisme.organisme", "traitement", array (
			"atkcode" => "100",
			"id"=>"$organismeid"
				)), "Traitements", true);

					
				$db = & atkGetDb();
				$data = $db->getrows("SELECT o.date_derniere_preparation, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_derniere_preparation=au.id where o.id= $organismeid ");
				$nombre_prepa = $data[0]["identifiant"]." le ".$data[0]["date_derniere_preparation"];
				$data = $db->getrows("SELECT o.date_derniere_preparation_fin, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_derniere_preparation_fin=au.id where o.id= $organismeid ");
			$nombre_prepa_fin = $data[0]["identifiant"]." le ".$data[0]["date_derniere_preparation_fin"];
				$data = $db->getrows("SELECT o.date_envoi_recu_fiscal, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_envoi_recu_fiscal=au.id where o.id=$organismeid");
				$nombre_recu_fiscal = $data[0]["identifiant"]." le ".$data[0]["date_envoi_recu_fiscal"];
				$data = $db->getrows("SELECT o.date_envoi_timbre, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_envoi_timbre=au.id where o.id=$organismeid");
				$nombre_timbre = $data[0]["identifiant"]." le ".$data[0]["date_envoi_timbre"];
				$data = $db->getrows("SELECT o.date_envoi_carte, au.identifiant
			from organisme o LEFT JOIN app_utilisateur  au ON o.id_envoi_carte=au.id where o.id=$organismeid");
				$nombre_carte = $data[0]["identifiant"]." le ".$data[0]["date_envoi_carte"];
				$data = $db->getrows("SELECT o.date_recu_abandon_creance, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_recu_abandon_creance=au.id where o.id=$organismeid");
				$nombre_abandon_creance = $data[0]["identifiant"]." le ".$data[0]["date_recu_abandon_creance"];
				$data = $db->getrows("SELECT o.date_synchronisation_federation, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_synchronisation_federation=au.id where o.id=$organismeid");
				$nombre_synchro_federation =$data[0]["identifiant"]." le ".$data[0]["date_synchronisation_federation"];
				$nombre_prepa="Début : ". $nombre_prepa."<br/>"."Fin : ". $nombre_prepa_fin;
				// Préparation
				$this->menuitem("Préparation##".$nombre_prepa, dispatch_url("traitement.trimestriel", "avertissement", array (
			"atkselector"=>"organisme.id='".$organismeid. "'",
			"id"=>"$organismeid"
				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>2-Vérifications</b>", "", "Traitements", true);
				// vérif globale
				$this->menuitem("Vérification globale", dispatch_url("organisme.v_organisme_inscription_controle", "edit", array (
			"atkselector"=>"v_organisme_inscription_controle.id_organisme='".$organismeid. "'",
			"atkfilter"=>"v_organisme_inscription_controle.id_organisme='".$organismeid. "'",
			"id"=>"$organismeid"
				)), "Traitements", true);

				$db = & atkGetDb();
				$data = $db->getrows("SELECT creer_adresse_postale_o_n, inscrire_federation_o_n,creer_cotisation_federation_o_n,reporter_inscription_federation_o_n,
 reporter_radiation_federation_o_n, regler_cotisation_federation_o_n, imprimer_adresse_o_n,envoyer_recu_fiscal_o_n, envoyer_timbre_o_n,
 envoyer_carte_adherent_o_n, reclamer_cotisation_o_n, avertir_radiation_cotisation_o_n, effectuer_radiation_cotisation_o_n, avertir_radiation_adhesion_o_n,
 effectuer_radiation_adhesion_o_n, adhesion_et_pas_de_cotisation_o_n from v_organisme_inscription_controle where id_organisme='".$organismeid. "'");

				$nombre = $data[0]["creer_adresse_postale_o_n"];
				$this->menuitem("Adresses manquantes"."#".$nombre, dispatch_url("individu.individu", "admin",
				array("atkfilter"=>"individu.id in (select id_individu from individu_inscription where creer_adresse_postale_o_n='1'
and id_organisme='".$organismeid. "')")), "Traitements", true);

				$nombre = $data[0]["inscrire_federation_o_n"];
				$this->menuitem("A inscrire à fédération"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where inscrire_federation_o_n=1
and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["creer_cotisation_federation_o_n"];
				$this->menuitem("Créer cotisation fédération"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where creer_cotisation_federation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["reporter_inscription_federation_o_n"];
				$this->menuitem("Reporter inscription fédération"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where reporter_inscription_federation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["reporter_radiation_federation_o_n"];
				$this->menuitem("Reporter radiation fédération"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where reporter_radiation_federation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["regler_cotisation_federation_o_n"];
				$this->menuitem("Règler cotisations fédération"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where regler_cotisation_federation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["imprimer_adresse_o_n"];
				$this->menuitem("Adresses à imprimer"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where imprimer_adresse_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["envoyer_recu_fiscal_o_n"];
				$this->menuitem("Reçus fiscaux à imprimer"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where envoyer_recu_fiscal_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["envoyer_timbre_o_n"];
				$this->menuitem("Timbres à envoyer"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where envoyer_timbre_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["envoyer_carte_adherent_o_n"];
				$this->menuitem("Cartes à envoyer"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where envoyer_carte_adherent_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["reclamer_cotisation_o_n"];
				$this->menuitem("Cotisations à relancer"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where reclamer_cotisation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["avertir_radiation_cotisation_o_n"];
				$this->menuitem("Avertir radiation cotisation"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where avertir_radiation_cotisation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);


				$nombre = $data[0]["effectuer_radiation_cotisation_o_n"];
				$this->menuitem("Effectuer radiation cotisation"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where effectuer_radiation_cotisation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["avertir_radiation_adhesion_o_n"];
				$this->menuitem("Avertir radiation adhésion"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where avertir_radiation_adhesion_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["effectuer_radiation_adhesion_o_n"];
				$this->menuitem("Effectuer radiation adhésion"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where effectuer_radiation_adhesion_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);

				$nombre = $data[0]["adhesion_et_pas_de_cotisation_o_n"];
				$this->menuitem("Adhésion sans cotisation"."#".$nombre, dispatch_url("individu.individu", "admin",
				array('atkfilter'=>"individu.id in (select id_individu from individu_inscription where adhesion_et_pas_de_cotisation_o_n=1
    		and id_organisme=".$organismeid.")"))
				, "Traitements", true);


				// vérif compléments courrier
				$this->menuitem("Vérification compléments courrier", dispatch_url("individu.v_individu_correspondance", "admin", array (
			"atkfilter"=>"v_individu_correspondance.id_organisme='".$organismeid. "'",
			"id"=>"$organismeid"
				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>3-Impressions</b>", "", "Traitements", true);
				// impression des enveloppes &atkselector=organisme_id%3D%272%27&atkfilter=v_individu_lieu.adresse_defaut_o_n%3D%271%27%20%20%0A%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09and%20v_individu_lieu.id%20in%20%0A%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%28select%20distinct%20ii.id_individu%0A%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%20from%20individu_inscription%20ii%20%0A%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%20where%20%20ii.imprimer_adresse_o_n%3D1%20%0A%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09%09and%20ii.id_organisme%3D%272%27%29&atkdoctpl=enveloppe_individus_organisme.odt&atkdoctpl_prefix_id=1&atkcode=1&id=2&atklevel=-1&atkprevlevel=0&
				$nombre = $data[0]["imprimer_adresse_o_n"];
				$this->menuitem("Impression enveloppes#".$nombre, dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1' and v_individu_lieu.id in 
(select distinct ii.id_individu from individu_inscription ii  where  ii.imprimer_adresse_o_n=1 and ii.id_organisme='" . $organismeid . "')",
			"atkdoctpl" => "enveloppe_individus_organisme.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $organismeid
				)), "Traitements", true);
				// Impression reçus fiscaux
				$nombre = $data[0]["envoyer_recu_fiscal_o_n"];
				$this->menuitem("Impression reçus fiscaux#".$nombre, dispatch_url("organisme.v_individu_recu_fiscal", "document", array (
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"atkfilter" => "v_individu_recu_fiscal.id_organisme='" . $organismeid . "'",
			"atkdoctpl" => "recu_fiscal.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $organismeid,

				)), "Traitements", true);
				// Impression notifications individuelles					
				$dataw = $db->getrows("SELECT count(id_organisme) as nombre from v_individu_correspondance where id_organisme='".$organismeid. "'");

				$nombre = $dataw[0]["nombre"];
				$this->menuitem("Impression notifications#".$nombre, dispatch_url("individu.v_individu_correspondance", "document", array (
			"atkselector" => "organisme_id='" . $organismeid. "'",
			"atkfilter" => "v_individu_correspondance.id_organisme='" . $organismeid . "'",
			"atkdoctpl" => "complement_gazette.odt",
			"atkdoctpl_prefix_id" => "1",
			"id" => $organismeid

				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>4-Mise sous pli</b>", "", "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>5-Mise à jour des dates</b>", "", "Traitements", true);
				// Mise à jour date envoi reçus fiscaux
				$this->menuitem("Mise à jour date reçus fiscaux##".$nombre_recu_fiscal, dispatch_url("traitement.trimestriel", "recu_maj", array (
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"id" => $organismeid

				)), "Traitements", true);
				// Mise à jour date timbres
				$this->menuitem("Mise à jour date timbres##".$nombre_timbre, dispatch_url("traitement.trimestriel", "timbre_maj", array(
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"id" => $organismeid

				)), "Traitements", true);
				// Mise à jour date cartes
				$this->menuitem("Mise à jour date cartes##".$nombre_carte, dispatch_url("traitement.trimestriel", "carte_maj", array(
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"id" => $organismeid

				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>6-Synchronisation avec la fédération</b>", "", "Traitements", true);
				$this->menuitem("Inscriptions, radiations, cotisations fédération", dispatch_url("organisme.organisme", "traitement", array (
			"atkcode" => "80",
			"id" =>$organismeid
				)), "Traitements", true);

				$this->menuitem("-", "", "Traitements", true);
				$this->menuitem("!<b>7-Mise à jour date synchronisation</b>", "", "Traitements", true);
				// Mise à jour envoi fédération 		http://www.wikistoma.org/association/dispatch.php?atkaction=traitement&id=2&atkcode=11&atklevel=1&atkprevlevel=0&atkstackid=48d6caa78d4ac&
				$this->menuitem("@miseàjourenvoifédération@"."Mise à jour envoi fédération##".$nombre_synchro_federation, dispatch_url("organisme.organisme", "traitement", array (
			"atkcode" => "11",
			"id" => $organismeid
				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);

				// Impression reçus fiscaux
				$this->menuitem("!<b>8-Reçus fiscaux pour abandon de créance</b>", "", "Traitements", true);
				$this->menuitem("Impression reçus fiscaux abandon de creance", dispatch_url("organisme.v_individu_recu_fiscal_abandon", "document", array(
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"atkfilter" => "v_individu_recu_fiscal_abandon.id_organisme='" . $organismeid . "'",
			"atkdoctpl" => "recu_fiscal_abandon.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $organismeid,

				)), "Traitements", true);

				// Mise à jour date envoi reçus fiscaux
				$this->menuitem("Mise à jour date reçus fiscaux abandon de creance##".$nombre_abandon_creance, dispatch_url("organisme.v_individu_recu_fiscal_abandon", "recu_maj", array (
			"atkselector" => "organisme_id='" . $organismeid . "'",
			"id" => $organismeid

				)), "Traitements", true);
				$this->menuitem("-", "", "Traitements", true);

			}

		}

	}
}
?>
