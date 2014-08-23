<?php
class menu_dashboard extends atkNode {
	function menu_dashboard() {
		$this->atkNode("menu_dashboard", NF_MRA);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkDummyAttribute("titre", "titre", AF_NOLABEL), null, 10);
		$this->add(new atkDummyAttribute("ligne_perso", "Ligne personnelle", AF_NOLABEL));
		//	$this->add(new atkDummyAttribute("ligne_recherche", "Ligne recherche", AF_NOLABEL));
		$this->add(new atkTabbedPane("Pane1", array (
			"Utilisateur" => array (
				"ligne_perso"
			),
			"Individus" => array (
				"individu",
				"description_individu",
				"menu_item_individu",
				"go_individu"
			),
			"Organismes" => array (
				"organisme",
				"description_organisme",
				"menu_item_organisme",
				"go_organisme"
			),
			"Lieux" => array (
							"ind_lieu",
				"go_pays",
				"go_province",
				"go_ville",
				"go_code_postal",
				"adm_lieux",
				"adm_pays",
				"adm_cp",
				"adm_lieu"

			),
			"Tables" => array (
				"table",
				//			"menu_item_table",
				"go_table"
			) /*,
															"Recherche" => array (
																"ligne_recherche"
															)
															*/
			
		), AF_NO_LABEL));
		$individu = $this->add(new atkManyToOneRelation("individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOCOMPLETE));
		$menu_item_individu = $this->add(new atkManyToOneRelation("menu_item_individu", "menu.menu_item"));
		$menu_item_individu->addDestinationFilter("id_menu in (select id from menu where libelle='Individus' )");
		$this->add(new atkDummyAttribute("go_individu", "Go"));
		$this->add(new atkDummyAttribute("description_individu", "Description"));
		$individu->addDependee("go_individu");
		$individu->addDependee("description_individu");
		$menu_item_individu->addDependee("go_individu");
		$organisme = $this->add(new atkManyToOneRelation("organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOCOMPLETE));
		$menu_item_organisme = $this->add(new atkManyToOneRelation("menu_item_organisme", "menu.menu_item"));
		$menu_item_organisme->addDestinationFilter("id_menu in (select id from menu where libelle='Organismes' )");
		$organisme->addDependee("go_organisme");
		$organisme->addDependee("description_organisme");
		$menu_item_organisme->addDependee("go_organisme");
		$this->add(new atkDummyAttribute("go_organisme", "Go"));
		$this->add(new atkDummyAttribute("description_organisme", "Description"));
		$table = $this->add(new atkManyToOneRelation("table", "menu.menu"));
		$table->addDestinationFilter("id_type_menu in (select id from type_menu where libelle='Tables' )");
		//	$table->addDependee("menu_item_table");
		//	$menu_item_table = $this->add(new atkManyToOneRelation("menu_item_table", "menu.menu_item"));
		//	$menu_item_table->addDestinationFilter("id_menu in (select id from menu where id='[table.id]' )");
		$table->addDependee("go_table");
		//	$menu_item_table->addDependee("go_table");
		$this->add(new atkDummyAttribute("go_table", "Go"));
		$this->add(new atkDummyAttribute("adm_lieux", "Administration",AF_NO_LABEL));
		$this->add(new atkParserAttribute("adm_pays", href(dispatch_url("table.pays", "admin", array ()), atktext("Pays", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkParserAttribute("adm_cp", href(dispatch_url("table.cp_ville_pays", "admin", array ()), atktext("Codes Postaux", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkParserAttribute("adm_lieu", href(dispatch_url("individu.lieu", "admin", array ()), atktext("Lieux", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkDummyAttribute("ind_lieu", "Individus",AF_NO_LABEL));
		$this->add(new atkParserAttribute("go_pays", href(dispatch_url("table.pays", "admin", array ("atgordre"=> "nb_individus")
), atktext("par pays", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkParserAttribute("go_province", href(dispatch_url("table.v_lieu_province", "admin", array ()), atktext("par provinces/départements", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkParserAttribute("go_ville", href(dispatch_url("table.v_lieu_ville", "admin", array ()), atktext("par villes", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		$this->add(new atkParserAttribute("go_code_postal", href(dispatch_url("table.v_lieu_cp", "admin", array ()), atktext("par codes postaux", "core"), SESSION_NEW, false, 'target="_blank"'),AF_NO_LABEL));
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_libelle_profil = $g_sessionManager->getValue("atgProfilUtilisateur", "globals");
		$loggedin = "<b>" . $g_nomutilisateur . "</b> (" . $g_libelle_profil.")";
		$this->addStyle("guy.css");
		$loggedin .= ' &nbsp; <a href="index.php?atklogout=1" target="_top">' . ucfirst(atktext("logout", "atk")) . '</a> &nbsp;';
		$this->add(new atkDummyAttribute("aide", ">>>>>>>>>> " . $loggedin . " ". nodeHelpUrl($this->atkNodeType()) . " Tutoriel " . nodeDemandeUrl($this->atkNodeType()) . " " . nodeSourceUrl($this->atkNodeType()) ." " .gmdate('c')." <<<<<<<<<<", AF_NO_LABEL | AF_HIDE_LIST));
		$this->setTable("");
	}
	function ligne_perso_edit() {
		global $g_user;
		$content = "";
		if ($g_user["name"] != "administrator") {
			$db = & atkGetDb();
			$query = "SELECT au.id_individu as id_individu, au.courriel as courriel, i.calendrier as calendrier from app_utilisateur au, individu i where au.id=" . $g_user["id"] . " and au.id_individu=i.id ";
			$row = $db->getrows($query);
			$idindividu = $row[0]["id_individu"];
			$courriel = $row[0]["courriel"];
			$calendrier = $row[0]["calendrier"];
			$centerpiece = ' <b>Personnel :</b> ' . href(dispatch_url("profil.userprefs", "edit", array (
				"atkselector" => "app_utilisateur.id='" . $g_user["id"] . "'"
			)), atktext("userprefs", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$url=href("$calendrier", atktext("calendrier", "core"), SESSION_NEW, false, 'target="_blank"');
			$centerpiece .= ' ' . $url;
			$url = href(dispatch_url("individu.contact_i", "admin", array (
				"atkfilter" => "individu_contact.id_contact='" . $idindividu . "'
								or individu_contact.id_contact='" . $idindividu . "'"
			)), atktext(atk_htmlentities(Contacts), "core"), SESSION_NEW, false, 'target="main"');
			$centerpiece .= ' ' . $url;
			$url = href(dispatch_url("individu.rencontre_i", "admin", array (
				"atkfilter" => "individu_rencontre.id_individu='" . $idindividu . "'"
			)), atktext(atk_htmlentities(Rencontres), "core"), SESSION_NEW, false, 'target="main"');
			$centerpiece .= ' ' . $url;
			$centerpiece .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
				"atgsens" => 'from',
				"atgemail" => '',
				"atgtable" => 'individu',
				"atgcle" => 'id',
				"atgvaleur" => $idindividu
			)), atktext(atk_htmlentities('Contactant'), "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("pim.pim", "pim"), atktext("pim", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("todo.todo", "admin", array (
				"atkfilter" => "todo.id_individu_a_faire='" . $idindividu . "'"
			)), atktext("tâches", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.bookmark_i", "admin", array (
				"atkfilter" => "individu_bookmark.id_individu='" . $idindividu . "'"
			)), atktext("bookmarks", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.immatriculation_i", "admin", array (
				"atkfilter" => "individu_immatriculation.id_individu='" . $idindividu . "'"
			)), atktext("immatriculations", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.document_i", "admin", array (
				"atkfilter" => "individu_document.id_individu='" . $idindividu . "'"
			)), atktext("documents", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$data1 = $db->getrows("SELECT id from todo where blocnotes_o_n='1' and id_individu_a_faire=" . $idindividu . " ");
			$id_bloc = $data1[0]["id"];
			$centerpiece .= href(dispatch_url("profil.copier_coller", "admin", array (
				"atkfilter" => "tmp_copier_coller.id_utilisateur='" . $g_user["id"] . "'",
				"atklimit" => "10000"
			)), atktext("Presse-papier", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("profil.liste", "admin", array (
				"atkfilter" => "app_utilisateur_liste.id_utilisateur='" . $g_user["id"] . "'",
				"atklimit" => "10000"
			)), atktext("Listes", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("todo.todo", "edit", array (
				"atkselector" => "todo.id='" . $id_bloc . "'"
			)), atktext("Bloc Notes", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		} else {
			// Administrator has a link to setup.php
			$centerpiece = href("setup.php", atktext("setup", "core"), SESSION_NEW, false, 'target="_top"');
		}
		$oldtop = '';
		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		if ($administrateur == '1' || ($g_user["name"] == "administrator")) {
			$oldtop = '<br> <b>Administrer :</b> ' . href(dispatch_url("profil.utilisateur", "admin"), atktext("Utilisateurs", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';

			$oldtop .= href(dispatch_url("profil.profil", "admin"), atktext("Profils", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("profil.log", "admin"), atktext("Logs", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("menu.menu", "admin"), atktext("Menus", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("application.aide", "admin"), atktext("Aide", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("application.demande", "admin"), atktext("Demandes", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("editeur.editeur", "admin"), atktext("Editeur", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("individu.individu_pda", "admin"), atktext("individus pda", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= href(dispatch_url("organisme.organisme_pda", "admin"), atktext("organisme pda", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' &nbsp; <a href="top.php?" target="_self"><b>' . ucfirst(atktext("admin", "admin")) . '</b></a> &nbsp;';
			$oldtop .= '<br> <b>Développer :</b> '  .href(dispatch_url("test.testguy", "intro"), atktext("Tests", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
	$oldtop .='.&nbsp <b> Atk :</b> '. href("http://www.atk-framework.com", atktext("site", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://www.atk-framework.com/wiki/ATK", atktext("wiki", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://www.atk-framework.com/forum/", atktext("forum", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://atk.achievo.org/docs/atk/latest/", atktext("api", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://www.atk-framework.com/download/", atktext("download", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://svn.ibuildings.nl/svn/atk/atk/trunk/", atktext("svn", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://docs.fckeditor.net/FCKeditor_2.x/Users_Guide", atktext("fck Editor", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= '.&nbsp <b> Réf :</b> ' . href("http://www.php.net/manual/fr/", atktext("php", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://www.w3.org/TR/html401/cover.html#minitoc", atktext("html 401", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://dev.mysql.com/doc/refman/5.0/fr/index.html", atktext("mysql 5.0", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://http://www.w3.org/TR/REC-CSS1", atktext("css", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://www.w3.org/TR/2000/REC-xml-20001006", atktext("xml", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
			$oldtop .= ' ' . href("http://http://www.w3.org/TR/2003/WD-xhtml2-20030506/", atktext("xhtml", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';


		}
		$content .= $centerpiece . $oldtop;
		$downloads = '<br> <b>Télécharger :</b> ' . href("http://fr.openoffice.org/about-downloads-contrib.html?product=OpenOffice.org&os=winwjre&lang=fr&version=2.4.1", atktext("Open Office 2.4.1", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("https://sourceforge.net/project/showfiles.php?group_id=57796&package_id=53473&release_id=563252", atktext("PDFCreator 0.9.5", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://sourceforge.net/project/downloading.php?groupname=gimp-win&filename=gimp-2.4.2-i686-setup.exe&use_mirror=mesh", atktext("Gimp 2.4.2", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://www.clubic.com/lancer-le-telechargement-19160-0-wink.html", atktext("Wink tutorial", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://www.01net.com/outils/telecharger/windows/Internet/internet_utlitaire/fiches/tele14537.html", atktext("Acrobat reader 9", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://downloads.sourceforge.net/sevenzip/", atktext("7 zip 4.57", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://www.01net.com/outils/telecharger/windows/Internet/navigateur/fiches/tele25711.html", atktext("Firefox 2.0.0.15", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$downloads .= ' ' . href("http://www.eclipse.org/downloads/", atktext("Eclipse 3.4", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$content .= $downloads;
		$guides = '<br> <b>Guides associatifs</b> : ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='395'",
			"afficher_direct" => "o"
		)), atktext("Bien communiquer", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$guides .= ' ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='176'",
			"afficher_direct" => "o"
		)), atktext("Transparence et associations", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$guides .= ' ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='397'",
			"afficher_direct" => "o"
		)), atktext("Guide du président", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$guides .= ' ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='396'",
			"afficher_direct" => "o"
		)), atktext("Guide du trésorier", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$guides .= ' ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='394'",
			"afficher_direct" => "o"
		)), atktext("Comprendre la comptabilité", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$guides .= ' ' . href(dispatch_url("organisme.document", "edit", array (
			"atkselector" => "organisme_document.id='428'",
			"afficher_direct" => "o"
		)), atktext("Principe application", "core"), SESSION_NEW, false, 'target="_blank"') . '&nbsp; ';
		$content .= $guides;
		return $content;
	}
	function ligne_recherche_edit() {
		$searchnode = getNode("search.search");
		$searchpiece = $searchnode->simpleSearchForm("", "main", SESSION_NEW);
		return $searchpiece;
	}
	function titre_edit() {
		include ("version.inc");
		return '<b>' . $wikiassoc_user . ' avec ' . $wikiassoc_name . ' - version : ' . $wikiassoc_version . ' ' . $wikiassoc_state . ' du ' . $wikiassoc_date . '.(Atk : ' . atkversion() . ')</b>';
	}
	function description_individu_edit($record, $prefix = "") {
		if (!isset ($record["individu"]["id"])) {
			return false;
		}
		$description = href(dispatch_url("individu.individu", "add", array ()), atktext(atk_htmlentities('Créer'), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' (' . $record["individu"]["id"] . ')';
		$identification = ' ' . $record["individu"]["prenom"];
		$identification .= ' ' . $record["individu"]["nom"];
		$url = href(dispatch_url("individu.individu", "edit", array (
			"id" => $record["individu"]["id"],
			"atkselector" => "individu.id='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities($identification), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $url;
		$url = href(dispatch_url("individu.fonction_i", "admin", array (
			"atkfilter" => "individu_fonction.id_individu='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities(Fonctions), "core"), SESSION_NEW, false, 'target="main"');
		$description .= '&nbsp' . $url;
		$url = href(dispatch_url("individu.inscription_i", "admin", array (
			"atkfilter" => "individu_inscription.id_individu='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities(Inscriptions), "core"), SESSION_NEW, false, 'target="main"');
		$description .= '&nbsp' . $url;
		$url = href(dispatch_url("individu.contact_i", "admin", array (
			"atkfilter" => "individu_contact.id_individu='" . $record["individu"]["id"] . "'
						or individu_contact.id_contact='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities(Contacts), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $url;
		$url = href(dispatch_url("individu.rencontre_i", "admin", array (
			"atkfilter" => "individu_rencontre.id_individu='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities(Rencontres), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $url;
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu");
		$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
		$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("individu.courriel as courriel");
		$query->addField("individu.date_deces as date_deces");
		$query->addField("individu.calendrier as calendrier");
		$query->addField("individu.site_internet as site_internet");
		$query->addField("individu.telephone_fixe as telephone_fixe");
		$query->addField("individu.telephone_mobile as telephone_mobile");
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_cp_ville_pays.province_etat as province");
		$query->addField("type_pays.libelle_anglais as pays");
		$query->addCondition("individu.id='" . $record["individu"]["id"] . "'");
		//		$query->addCondition("individu_lieu.adresse_defaut_o_n='1'");
		$sql = ($query->buildSelect());
		$stuff = $db->getrows($sql);

		$i = 0;
		if (!empty($stuff[$i]["date_deces"]))
		{$description.='<b> dcd le '.$stuff[$i]["date_deces"].'</b>';}
		$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
			"atgsens" => 'to',
			"atgemail" => $stuff[$i]["courriel"],
			"atgtable" => 'individu',
			"atgcle" => 'id',
			"atgvaleur" => $record["individu"]["id"]
		)), atktext(atk_htmlentities('Contacté'), "core"), SESSION_NEW, false, 'target="_blank"');
		$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
			"atgsens" => 'from',
			"atgemail" => $stuff[$i]["courriel"],
			"atgtable" => 'individu',
			"atgcle" => 'id',
			"atgvaleur" => $record["individu"]["id"]
		)), atktext(atk_htmlentities('Contactant'), "core"), SESSION_NEW, false, 'target="_blank"');
		if (isset ($stuff[$i]["telephone_fixe"])) {
			$description .= ' ' . $stuff[$i]["telephone_fixe"] . ' -';
		}
		if (isset ($stuff[$i]["telephone_mobile"])) {
			$description .= ' ' . $stuff[$i]["telephone_mobile"];
		}
		//		$description = atk_htmlentities($description);
		if (isset ($stuff[$i]["courriel"])) {
			$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
				"atgsens" => 'to',
				"atgemail" => $stuff[$i]["courriel"],
				"atgtable" => 'individu',
				"atgcle" => 'id',
				"atgvaleur" => $record["individu"]["id"]
			)), atktext($stuff[$i]["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
		}
		
		if (isset ($stuff[$i]["calendrier"])) {
			$description .= ' <a href="' . $stuff[$i]["calendrier"] . '" target="_blank">  ' . 'calendrier'. '</a>';
					}
		
		
		if (isset ($stuff[$i]["site_internet"])) {
			$description .= ' <a href="' . $stuff[$i]["site_internet"] . '" target="_blank">  ' . $stuff[$i]["site_internet"] . '</a>';
		}
		if (isset ($stuff[$i]["ville"])) {
			$adresse = ' ' . atk_htmlentities($stuff[$i]["adresse1"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["code_postal"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["ville"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["province"]);
			$adresse .= ' ' . $stuff[$i]["pays"];
			$googlemap = href(dispatch_url("individu.individu", "googlemap", array (
				"id" => "" . $record["individu"]["id"] . ""
			)), atktext($adresse, "core"), SESSION_NEW, false, 'target="_blank"');
			$description .= ' ' . $googlemap;
			$enveloppe = href(dispatch_url("individu.v_individu_lieu", "document", array (
				"atkselector" => "individu.id='" . $record["individu"]["id"] . "'",
				"id" => $record["individu"]["id"],
				"atkfilter" => "v_individu_lieu.id='" . $record["individu"]["id"] . "'",
				"atkdoctpl" => "enveloppe_individu.odt",
				"atkdoctpl_prefix_id" => "0",
				"atkcode" => "2"
			)), atktext("enveloppe", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $enveloppe;
		}
		$fiche = href(dispatch_url("individu.individu", "fiche", array (
			"id" => $record["individu"]["id"]
		)), atktext("fiche", "core"), SESSION_NEW, false, 'target="_blank"');
		$description .= ' ' . $fiche;
		$vcard = href(dispatch_url("individu.individu", "vcard", array (
			"id" => $record["individu"]["id"]
		)), atktext("vcard", "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $vcard;
		$google = href("http://www.google.fr/search?q=" . $record["individu"]["nom"] . "+" . $record["individu"]["prenom"] . "&ie=utf-8&oe=utf-8&aq=t", atktext("Google", "core"), SESSION_NEW, false, 'target="_blank"');
		$description .= ' ' . $google;
		return $description;
	}
	function description_organisme_edit($record, $prefix = "") {
		if (!isset ($record["organisme"]["id"])) {
			return false;
		}
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("organisme");
		$query->addJoin("organisme_lieu", "", "organisme.id = organisme_lieu.id_organisme", true);
		$query->addJoin("lieu", "", "organisme_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addField("organisme.nom as nom");
		$query->addField("organisme.sigle as sigle");
		$query->addField("organisme.courriel as courriel");
				$query->addField("organisme.calendrier as calendrier");
		$query->addField("organisme.site_internet as site_internet");
		$query->addField("organisme.telephone as telephone");
		$query->addField("organisme.acces_public_o_n as acces_public_o_n");
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_cp_ville_pays.province_etat as province");
		$query->addField("type_pays.libelle_anglais as pays");
		$query->addCondition("organisme.id='" . $record["organisme"]["id"] . "'");
		//		$query->addCondition("organisme_lieu.adresse_defaut_o_n='1'");
		$sql = ($query->buildSelect());
		$stuff = $db->getrows($sql);
		$description = href(dispatch_url("organisme.organisme", "add", array ()), atktext(atk_htmlentities('Créer'), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' (' . $record["organisme"]["id"] . ')';
		$identification = ' ' . $record["organisme"]["nom"];
		if (isset ($stuff[0]["sigle"]) || $stuff[0]["sigle"] == "") {
			$identification .= ' - ' . atk_htmlentities($stuff[$i]["sigle"]);
		}
		global $g_sessionManager;
		$g_acces_public_seulement = $g_sessionManager->getValue("atgAccesPublicSeul_o_n", "globals");
		$g_organismes_autorises = $g_sessionManager->getValue("atgOrganismesAutorises", "globals");
		if (($stuff[0]["acces_public_o_n"] == '1') || ($g_acces_public_seulement == '0') || (($g_acces_public_seulement == '1') && ($stuff[0]["acces_public_o_n"] == '0') && (in_array($record["organisme"]["id"], $g_organismes_autorises)))) {
			$url = href(dispatch_url("organisme.organisme", "edit", array (
				"id" => "" . $record["organisme"]["id"] . "",
				"atkselector" => "organisme.id='" . $record["organisme"]["id"] . "'"
			)), atktext(atk_htmlentities($identification), "core"), SESSION_NEW, false, 'target="main"');
		} else {
			$url = atk_htmlentities($identification);
		}
		$description .= ' ' . $url;
		$url = href(dispatch_url("individu.fonction_i", "admin", array (
			"atkfilter" => "individu_fonction.id_organisme='" . $record["organisme"]["id"] . "'"
		)), atktext(atk_htmlentities(Fonctions), "core"), SESSION_NEW, false, 'target="main"');
		$description .= '&nbsp' . $url;
		$url = href(dispatch_url("individu.inscription_i", "admin", array (
			"atkfilter" => "individu_inscription.id_organisme='" . $record["organisme"]["id"] . "'"
		)), atktext(atk_htmlentities(Inscriptions), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $url;
		$url = href(dispatch_url("organisme.rencontre", "admin", array (
			"atkfilter" => "organisme_rencontre.id_organisme='" . $record["organisme"]["id"] . "'"
		)), atktext(atk_htmlentities(Rencontres), "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $url;
		$i = 0;
		if (isset ($stuff[$i]["telephone"])) {
			$description .= ' ' . $stuff[$i]["telephone"];
		}
		if (isset ($stuff[$i]["courriel"])) {
			$description .= ' ' . '<a href="mailto:' . $stuff[$i]["courriel"] . '" target="_blank">  ' . $stuff[$i]["courriel"] . '</a>';
			
		}
		
				if (isset ($stuff[$i]["calendrier"])) {
			$description .= ' <a href="' . $stuff[$i]["calendrier"] . '" target="_blank">  ' . 'calendrier'. '</a>';
					}
		
		
		if (isset ($stuff[$i]["site_internet"])) {
			$description .= ' ' . '<a href="' . $stuff[$i]["site_internet"] . '" target="_blank">  ' . $stuff[$i]["site_internet"] . '</a>';
		}
		if (isset ($stuff[$i]["ville"])) {
			$adresse = ' ' . atk_htmlentities($stuff[$i]["adresse1"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["code_postal"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["ville"]);
			$adresse .= ' ' . atk_htmlentities($stuff[$i]["province"]);
			$adresse .= ' ' . $stuff[$i]["pays"];
			$googlemap = href(dispatch_url("organisme.organisme", "googlemap", array (
				"id" => "" . $record["organisme"]["id"] . ""
			)), atktext($adresse, "core"), SESSION_NEW, false, 'target="_blank"');
			$description .= ' ' . $googlemap;
			$enveloppe = href(dispatch_url("organisme.v_organisme_lieu", "document", array (
				"atkselector" => "organisme.id='" . $record["organisme"]["id"] . "'",
				"id" => "'" . $record["organisme"]["id"] . "'",
				"atkfilter" => "v_organisme_lieu.id='" . $record["organisme"]["id"] . "'",
				"atkdoctpl" => "enveloppe_organisme.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "2"
			)), atktext("enveloppe", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $enveloppe;
		}
		$vcard = href(dispatch_url("organisme.organisme", "vcard", array (
			"id" => "" . $record["organisme"]["id"] . ""
		)), atktext("vcard", "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $vcard;
		$google = href("http://www.google.fr/search?q=" . $record["organisme"]["nom"] . "&ie=utf-8&oe=utf-8&aq=t", atktext("Google", "core"), SESSION_NEW, false, 'target="_blank"');
		$description .= ' ' . $google;
		return $description;
	}
	function go_individu_edit($record, $prefix = "") {
		global $g_sessionManager;
		$g_acces_public_seulement = $g_sessionManager->getValue("atgAccesPublicSeul_o_n", "globals");
		$g_organismes_autorises = $g_sessionManager->getValue("atgOrganismesAutorises", "globals");
		if (!isset ($record["menu_item_individu"])) {
			return false;
		}
		if (!isset ($record["individu"]["id"]) && $g_acces_public_seulement == '1' && ($record["menu_item_individu"]["libelle"] != '.Lister') && ($record["menu_item_individu"]["libelle"] != '.Creer')) {
			return false;
		}
		$id_entite = $record["individu"]["id"];
		$action = $record["menu_item_individu"]["id"];
		$nom_entite = $record["individu"]["prenom"] . ' ' . $record["individu"]["nom"];
		$nom_action = $record["menu_item_individu"]["libelle"];
		return $this->get_options_menu($id_entite, $action, $nom_entite, $nom_action);
	}
	function go_lieu_edit($record, $prefix = "") {
		if (!isset ($record["lieu"]) || !isset ($record["menu_item_lieu"])) {
			return false;
		}
		$id_entite = $record["lieu"]["id"];
		$action = $record["menu_item_lieu"]["id"];
		$nom_entite = $record["lieu"]["adresse1"] . ' ' . $record["lieu"]["code_postal"] . ' ' . $record["lieu"]["ville"];
		$nom_action = $record["menu_item_lieu"]["libelle"];
		return $this->get_options_menu($id_entite, $action, $nom_entite, $nom_action);
	}
	function go_organisme_edit($record, $prefix = "") {
		global $g_sessionManager;
		$g_acces_public_seulement = $g_sessionManager->getValue("atgAccesPublicSeul_o_n", "globals");
		$g_organismes_autorises = $g_sessionManager->getValue("atgOrganismesAutorises", "globals");
		if (!isset ($record["menu_item_organisme"])) {
			return false;
		}
		if ((!isset ($record["menu_item_organisme"]["id"])) && (!isset ($record["menu_item_organisme"]["id"]))) {
			return false;
		}
		global $g_id_profil;
		global $g_organismes_autorises;
		$id_entite = $record["organisme"]["id"];
		$action = $record["menu_item_organisme"]["id"];
		$nom_entite = $record["organisme"]["nom"];
		$nom_action = $record["menu_item_organisme"]["libelle"];
		/*
		echo 'acces public seul : '.$g_acces_public_seulement.'<br>';
		echo 'id_profil : '.$g_id_profil.'<br>';
		print_r($g_organismes_autorises);
		echo '<br>nom entité : '.$nom_entite.'<br>';
		echo 'nom action : '.$nom_action.'<br>';
		echo '<br>id entité : '.$id_entite.'<br>';
		echo 'id action : '.$action.'<br>';	
		*/
		if ($g_acces_public_seulement == '1' && $record["menu_item_organisme"]["libelle"] != '.Lister' && ($record["menu_item_individu"]["libelle"] != '.Creer')) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("organisme");
			$query->addField("organisme.acces_public_o_n as acces_public_o_n");
			$query->addCondition("organisme.id='" . $record["organisme"]["id"] . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			if (($stuff[0]["acces_public_o_n"] == '1') || ($g_acces_public_seulement == '0') || (($g_acces_public_seulement == '1') && ($stuff[0]["acces_public_o_n"] == '0') && (in_array($record["organisme"]["id"], $g_organismes_autorises)))) {
				return $this->get_options_menu($id_entite, $action, $nom_entite, $nom_action);
			} else {
				return '<b><span style="color: rgb(255, 0, 0);">' . atk_htmlentities($nom_action . ' : ' . $nom_entite . '===> Non autorisé') . '</span></b>';
			};
		} else {
			return $this->get_options_menu($id_entite, $action, $nom_entite, $nom_action);
		}
	}
	function go_table_edit($record, $prefix = "") {
		if (!isset ($record["table"]["id"])) {
			return false;
		}
		$nom_entite = $record["table"]["libelle"];
		$nom_action = ".Lister";
		$id_entite = $record["table"]["id"];
		$db = & atkGetDb();
		$query = "SELECT  id FROM menu_item where id_menu =" . $id_entite . " and libelle='.Lister'";
		$r = $db->getrows($query);
		$action = $r[0]["id"];
		return $this->get_options_menu($id_entite, $action, $nom_entite, $nom_action);
	}
	function get_options_menu($id_entite, $action, $nom_entite, $nom_action) {
		global $g_acces_public_seulement;
		if (!isset ($action)) {
			return false;
		}
		if ($nom_action == '') {
			return false;
		}
		if (($nom_action == '.Creer') && (isset ($id_entite))) {
			return false;
		}
		if ((($nom_action == '.Afficher') || ($nom_action == '.Effacer') || ($nom_action == '.Modifier')) && (!isset ($id_entite))) {
			return false;
		}
		if ($g_acces_public_seulement == '1' && (!isset ($id_entite)) && ($nom_action != '.Creer') && $nom_action != '.Lister') {
			return false;
		}
		$db = & atkGetDb();
		$query = "SELECT  module, classe, atk_action, atk_id, atk_selector, atk_filter, atk_orderby, atk_search, atk_doctpl,atk_doctpl_prefix_id, atk_code, atk_startat, atk_limit
																									 FROM menu_item where id =" . $action;
		$r = $db->getrows($query);
		$module = $r[0]["module"];
		$classe = $r[0]["classe"];
		$atkaction = $r[0]["atk_action"];
		$atkid = $r[0]["atk_id"];
		$atkselector = $r[0]["atk_selector"];
		$atkfilter = $r[0]["atk_filter"];
		$atkorderby = $r[0]["atk_orderby"];
		$atksearch = $r[0]["atk_search"];
		$atkdoctpl = $r[0]["atk_doctpl"];
		$atkdoctpl_prefix_id = $r[0]["atk_doctpl_prefix_id"];
		$atkcode = $r[0]["atk_code"];
		$atkstartat = $r[0]["atk_startat"];
		$atklimit = $r[0]["atk_limit"];
		$atkoptions = array ();
		if ($atkselector != null && $atkselector != "" && $id_entite != null) {
			$atkoptions["atkselector"] = "$atkselector='" . $id_entite . "'";
		}
		if ($id_entite != null) {
			if ($atkfilter != null && $atkfilter != "") {
				//print_r(strstr($atkfilter,"(ID)"));
				// die();
				if (strstr($atkfilter, "(ID)") != false) {
					$atkfilter = str_replace("(ID)", "'" . $id_entite . "'", $atkfilter);
					$atkoptions["atkfilter"] = "$atkfilter";
				} else {
					if (substr($atkfilter, -1, 1) == ')') {
						$atkfilter = substr($atkfilter, 0, strlen($atkfilter) - 1);
						$atkoptions["atkfilter"] = "$atkfilter='" . $id_entite . "')";
					} else {
						$atkoptions["atkfilter"] = "$atkfilter='" . $id_entite . "'";
					}
				}
			}
		}
		if ($atkorderby != null) {
			$atkoptions["atkorderby"] = "$atkorderby";
		}
		if ($atkdoctpl != null) {
			$atkoptions["atkdoctpl"] = "$atkdoctpl";
			$atkoptions["atkdoctpl_prefix_id"] = "$atkdoctpl_prefix_id";
		}
		if ($atksearch != null) {
			$atkoptions["atksearch"] = "$atksearch";
		}
		if (($atkid = '1') && (isset ($id_entite))) {
			$atkoptions["id"] = "'" . $id_entite . "'";
		}
		$atkoptions["atkcode"] = "$atkcode";
		$atkoptions["atkstartat"] = "$atkstartat";
		$atkoptions["atklimit"] = "$atklimit";
		// print_r($atkoptions);
		$urlpiece = href(dispatch_url("$module.$classe", "$atkaction", $atkoptions), atktext('<b><span style="color: rgb(0, 153, 0);">' . atk_htmlentities($nom_action) . ' : ' . atk_htmlentities($nom_entite) . ' ===></span></b>', "core"), SESSION_NEW, false, 'target="main"');
		return $urlpiece;
	}
	function getFormButtons($mode, $record) {
		return array ();
	}
}
?>