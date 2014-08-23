<?php
class menu_dashboard extends atkNode {
	function menu_dashboard() {
		$this->atkNode("menu_dashboard", NF_MRA);
		$this->setSecurityAlias("individu.individu");
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
				"lieu",
				"menu_item_lieu",
				"go_lieu"
			),
			"Tables" => array (
				"table",
				"menu_item_table",
				"go_table"
			) /*,
									"Recherche" => array (
										"ligne_recherche"
									)
									*/
			
		), AF_NO_LABEL));
		$individu = $this->add(new atkManyToOneRelation("individu", "individu.individu", AF_RELATION_AUTOCOMPLETE));
		$menu_item_individu = $this->add(new atkManyToOneRelation("menu_item_individu", "menu.menu_item"));
		$menu_item_individu->addDestinationFilter("id_menu in (select id from menu where libelle='Individus' )");
		$this->add(new atkDummyAttribute("go_individu", "Go"));
		$this->add(new atkDummyAttribute("description_individu", "Description"));
		$individu->addDependee("go_individu");
		$individu->addDependee("description_individu");
		$menu_item_individu->addDependee("go_individu");
		$organisme = $this->add(new atkManyToOneRelation("organisme", "organisme.organisme", AF_RELATION_AUTOCOMPLETE));
		$menu_item_organisme = $this->add(new atkManyToOneRelation("menu_item_organisme", "menu.menu_item"));
		$menu_item_organisme->addDestinationFilter("id_menu in (select id from menu where libelle='Organismes' )");
		$organisme->addDependee("go_organisme");
		$organisme->addDependee("description_organisme");
		$menu_item_organisme->addDependee("go_organisme");
		$this->add(new atkDummyAttribute("go_organisme", "Go"));
		$this->add(new atkDummyAttribute("description_organisme", "Description"));
		$table = $this->add(new atkManyToOneRelation("table", "menu.menu"));
		$table->addDestinationFilter("id_type_menu in (select id from type_menu where libelle='Tables' )");
		$table->addDependee("menu_item_table");
		$menu_item_table = $this->add(new atkManyToOneRelation("menu_item_table", "menu.menu_item"));
		$menu_item_table->addDestinationFilter("id_menu in (select id from menu where id='[table.id]' )");
		$table->addDependee("go_table");
		$menu_item_table->addDependee("go_table");
		$this->add(new atkDummyAttribute("go_table", "Go"));
		$lieu = $this->add(new atkManyToOneRelation("lieu", "individu.lieu", AF_RELATION_AUTOCOMPLETE));
		$menu_item_lieu = $this->add(new atkManyToOneRelation("menu_item_lieu", "menu.menu_item"));
		$menu_item_lieu->addDestinationFilter("id_menu in (select id from menu where libelle='Lieux' )");
		$this->add(new atkDummyAttribute("go_lieu", "Go"));
		$lieu->addDependee("go_lieu");
		$menu_item_lieu->addDependee("go_lieu");
		$this->add(new atkDummyAttribute("separateur", "================================================================================================"));
		$this->setTable("");


	}
	function ligne_perso_edit() {
		global $g_user;
		$loggedin = atktext("logged_in_as") . ": <b>" . $g_user["name"] . "</b>";
		$content = $loggedin . ' &nbsp; <a href="index.php?atklogout=1" target="_top">' . ucfirst(atktext("logout", "atk")) . '</a> &nbsp;';
		if ($g_user["name"] != "administrator") {
			$db = & atkGetDb();
			$query = "SELECT id_individu from app_utilisateur where id=" . $g_user["id"] . " ";
			$row = $db->getrows($query);
			$idindividu = $row[0]["id_individu"];
			$centerpiece = href(dispatch_url("profil.userprefs", "edit", array (
				"atkselector" => "app_utilisateur.id='" . $g_user["id"] . "'"
			)), atktext("userprefs", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("pim.pim", "pim"), atktext("pim", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("todo.todo", "admin", array (
				"atkfilter" => "todo.id_individu_a_faire='" . $idindividu . "'"
			)), atktext("tâches", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.bookmark_i", "admin", array (
				"atkfilter" => "individu_bookmark.id_individu='" . $idindividu . "'"
			)), atktext("bookmarks", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.immatriculation_i", "admin", array (
				"atkfilter" => "individu_immatriculation.id_individu='" . $idindividu . "'"
			)), atktext("immatriculations", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= href(dispatch_url("individu.document_i", "admin", array (
				"atkfilter" => "individu_document.id_individu='" . $idindividu . "'"
			)), atktext("documents", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$centerpiece .= '<br>Aide Tutoriel Demandes '.nodeSourceUrl($this->atkNodeType()).';&nbsp;';
		} else {
			// Administrator has a link to setup.php
			$centerpiece = href("setup.php", atktext("setup", "core"), SESSION_NEW, false, 'target="_top"');
		}
		$oldtop='';
		global  $g_sessionManager;
		$administrateur=$g_sessionManager->getValue("atgAdministrateur_o_n","globals");
		if ($administrateur=='1' || ($g_user["name"] == "administrator"))
		{
			$oldtop = '<br>' . href(dispatch_url("profil.utilisateur", "admin"), atktext("Utilisateurs", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .=  href(dispatch_url("profil.profil", "admin"), atktext("Profils", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .=  href(dispatch_url("profil.log", "admin"), atktext("Logs", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .=  href(dispatch_url("menu.menu", "admin"), atktext("Menus", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .=  href(dispatch_url("application.aide", "admin"), atktext("Gestion de l'aide", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .=  href(dispatch_url("editeur.editeur", "admin"), atktext("Editeur", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ';
			$oldtop .= ' &nbsp; <a href="top.php?" target="_self">' . ucfirst(atktext("admin", "admin")) . '</a> &nbsp;';
		}
		$content .= $centerpiece . $oldtop;
		return $content;
	}
	function ligne_recherche_edit() {
		$searchnode = getNode("search.search");
		$searchpiece = $searchnode->simpleSearchForm("", "main", SESSION_NEW);
		return $searchpiece;
	}
	function description_individu_edit($record, $prefix = "") {
		if (!isset ($record["individu"]["id"])) {
			return false;
		}
		$description = '(' . $record["individu"]["id"] . ')';
		$identification = ' ' . $record["individu"]["prenom"];
		$identification .= ' ' . $record["individu"]["nom"];
		$url = href(dispatch_url("individu.individu", "edit", array (
			"id" => $record["individu"]["id"],
			"atkselector" => "individu.id='" . $record["individu"]["id"] . "'"
		)), atktext(atk_htmlentities($identification), "core"), SESSION_NEW, false, 'target="main"');
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
		$fdw = fopen("tempguy", "w");
		fwrite($fdw, $sql);
		fclose($fdw);
		$stuff = $db->getrows($sql);
		$i = 0;
		if (isset ($stuff[$i]["telephone_fixe"])) {
			$description .= ' ' . $stuff[$i]["telephone_fixe"] . ' -';
		}
		if (isset ($stuff[$i]["telephone_mobile"])) {
			$description .= ' ' . $stuff[$i]["telephone_mobile"];
		}
		//		$description = atk_htmlentities($description);
		if (isset ($stuff[$i]["courriel"])) {
			$description .= ' <a href="mailto:' . $stuff[$i]["courriel"] . '" target="_blank">  ' . $stuff[$i]["courriel"] . '</a>';
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
			)), atktext($adresse, "core"), SESSION_NEW, false, 'target="main"');
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
		$vcard = href(dispatch_url("individu.individu", "vcard", array (
			"id" => $record["individu"]["id"]
		)), atktext("vcard", "core"), SESSION_NEW, false, 'target="main"');
		$description .= ' ' . $vcard;
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
		$description = '(' . $record["organisme"]["id"] . ')';
		$identification = ' ' . $record["organisme"]["nom"];
		global $g_sessionManager;
		$g_acces_public_seulement=$g_sessionManager->getValue("atgAccesPublicSeul_o_n","globals");
		$g_organismes_autorises=$g_sessionManager->getValue("atgOrganismesAutorises","globals");
		
		if (($stuff[0]["acces_public_o_n"] == '1') || ($g_acces_public_seulement == '0') || (($g_acces_public_seulement == '1') && ($stuff[0]["acces_public_o_n"] == '0') && (in_array($record["organisme"]["id"], $g_organismes_autorises)))) {
			$url = href(dispatch_url("organisme.organisme", "edit", array (
				"id" => "" . $record["organisme"]["id"] . "",
				"atkselector" => "organisme.id='" . $record["organisme"]["id"] . "'"
			)), atktext(atk_htmlentities($identification), "core"), SESSION_NEW, false, 'target="main"');
		} else {
			$url = atk_htmlentities($identification);
		}
		$description .= ' ' . $url;
		$i = 0;
		if (isset ($stuff[$i]["sigle"])) {
			$description .= ' - ' . atk_htmlentities($stuff[$i]["sigle"]);
		}
		if (isset ($stuff[$i]["telephone"])) {
			$description .= ' ' . $stuff[$i]["telephone"];
		}
		if (isset ($stuff[$i]["courriel"])) {
			$description .= ' <a href="mailto:' . $stuff[$i]["courriel"] . '" target="_blank">  ' . $stuff[$i]["courriel"] . '</a>';
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
			$googlemap = href(dispatch_url("organisme.organisme", "googlemap", array (
				"id" => "" . $record["organisme"]["id"] . ""
			)), atktext($adresse, "core"), SESSION_NEW, false, 'target="main"');
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
		return $description;
	}
	function go_individu_edit($record, $prefix = "") {
		global $g_sessionManager;
		$g_acces_public_seulement=$g_sessionManager->getValue("atgAccesPublicSeul_o_n","globals");
		$g_organismes_autorises=$g_sessionManager->getValue("atgOrganismesAutorises","globals");

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
		$g_acces_public_seulement=$g_sessionManager->getValue("atgAccesPublicSeul_o_n","globals");
		$g_organismes_autorises=$g_sessionManager->getValue("atgOrganismesAutorises","globals");

		if (!isset ($record["menu_item_organisme"])) {
			return false;
		}
		if ((!isset ($record["menu_item_organisme"]["id"])) && (!isset($record["menu_item_organisme"]["id"]))) {
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
		if (!isset ($record["table"])) {
			return false;
		}
		$nom_entite = $record["table"]["libelle"];
		$nom_action = $record["menu_item_table"]["libelle"];
		//		$id_entite = $record["table"]["id"];
		$id_entite = array ();
		$action = $record["menu_item_table"]["id"];
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
		if (($nom_action == '.Creer')  && (isset ($id_entite))) {
			return false;
		}
		if ((($nom_action == '.Afficher') || ($nom_action == '.Effacer') || ($nom_action == '.Modifier')) && (!isset ($id_entite))) {
			return false;
		}
		if ($g_acces_public_seulement=='1' && (!isset ($id_entite)) && ($nom_action != '.Creer') && $nom_action != '.Lister' ){
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