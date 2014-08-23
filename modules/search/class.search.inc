<?php
/**
 * Global search functionality
 */
include_once (atkconfig("atkroot") . "modules/include/fairetooltip.inc");
atkimport("atk.assmetanode");
class search extends assMetaNode {
	function search() {
		$this->atkNode("search", NF_NO_SECURITY);
		// Anyone may perform global search. (security is enforced per
		// search result)
	}
	function action_search_schema(& $handler) {
		global $g_sessionManager;
		$searchstring = strip_tags($g_sessionManager->stackVar("searchstring"));
		$outil = strip_tags($g_sessionManager->stackVar("outil"));
		$langue = strip_tags($g_sessionManager->stackVar("langue"));
		$marquepage = strip_tags($g_sessionManager->stackVar("marquepage"));
		if (!empty($outil))
		{			$db = & atkGetDb();

		$data = $db->getrows("SELECT url_recherche, url_english, url_site  from type_moteur where id=$outil");
		$db->query("update type_moteur set nombre_acces=nombre_acces+1 where id=$outil");
		if (!empty($searchstring)) $url = $data[0]["url_recherche"];
		else { $url = $data[0]["url_site"];}
		if ($langue=='en') $url = $data[0]["url_english"];
		if (!empty($searchstring)) $url = str_replace("[lang]", $langue, $url);
		if (!empty($searchstring)) 			$url = str_replace("[string]", $searchstring, $url);
		$url_racine = $_SERVER["SCRIPT_URI"];
		$url_racine = str_replace("dispatch.php", '', $url_racine);
		$url = str_replace("[assocope]", $url_racine, $url);
		// GG LOg
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$param =$url;
		$sql="INSERT INTO atkeventlog (id, userid, stamp, node, action, parametres)
		VALUES(".$db->nextid("atkeventlog").", $id, UTC_TIMESTAMP, '.', 'recherche(assocope)', '$param')";
		$db->query($sql);
		$db->commit();
		// GG FIN
		header('Location: ' . $url);

		}

	}
	function action_wiki(& $handler) {
		$wiki_url="http://www.wikistoma.org/wiki/index.php?title=";
		$title=$this->m_postvars["title"];
		$url=$wiki_url.$title;
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$param =$url;
		$sql="INSERT INTO atkeventlog (id, userid, stamp, node, action, parametres)
		VALUES(".$db->nextid("atkeventlog").", $id, UTC_TIMESTAMP, '.', 'wiki', '$param')";
		$db->query($sql);
		$db->commit();
		header('Location: ' . $url);

	}
	function action_tousmenus(& $handler) {
		global $ATK_VARS;
		global $g_compteur_appels_mysql_query;
		atkimport("atk.menu.atkmenu");
		$dbw = & atkGetDb("assocopewiki");
		$menus=array();
		$menus[]="Utilisateur";
		$menus[]="Organismes";
		$menus[]="Individus";
		$menus[]="Rencontres";
		$menus[]="Traitements";
		$menus[]="Comptabilite_o";
		$menus[]="Comptes";
		$menus[]="Lieux_l";
		$menus[]="Tableaux_de_bord_o";
		$menus[]="Taxons";
		$menusadministrateur=array();
		$menusadministrateur[]="Administrer";
		$menusadministrateur[]="Tables";
		$menusadministrateur[]="Langues";
		$menusadministrateur[]="Rd";
		$menusadministrateur[]="Divers";
		$menusadministrateur[]="Outils";
		$menusadministrateur[]="Google";
		$menusadministrateur[]="contacts_google";
		$menusadministrateur[]="albums_google";
		$tableaumenus.="<h2>Menus AssoCope</h2></b>";
		$tableaumenus.="<table style=\"table-layout:fixed; width:1600px;\"><tr style=\"vertical-align:top \">";
		$time_debut=gettimeofday(true);
		for ($i = 0; $i < count($menus); $i++)
		{
			$ATK_VARS['atkmenutop'] = $menus[$i];
			$menu = &atkMenu::getMenu($ATK_VARS['atkmenutop']);
			$tableaumenus.="<td>".$menu->render().$this->getstats($time_debut,$compteur_appels_mysql_query_debut)."</td>";
			$time_debut=gettimeofday(true);
			$compteur_appels_mysql_query_debut=$g_compteur_appels_mysql_query;
		}

		$tableaumenus.="</tr></table>";
	$tableaumenus.="<h2>Menus administration AssoCope</h2></b>";
		$tableaumenus.="<table style=\"table-layout:fixed; width:1600px;\"><tr style=\"vertical-align:top \">";
		for ($i = 0; $i < count($menusadministrateur); $i++)
		{
			$ATK_VARS['atkmenutop'] = $menusadministrateur[$i];
			$menu = &atkMenu::getMenu($ATK_VARS['atkmenutop']);
			$tableaumenus.="<td>".$menu->render().$this->getstats($time_debut,$compteur_appels_mysql_query_debut)."</td>";
			$time_debut=gettimeofday(true);
			$compteur_appels_mysql_query_debut=$g_compteur_appels_mysql_query;
		}
		$tableaumenus.="</tr></table>";
		$tableaumenus.=$this->toc_wiki();
		$tableaumenus.="<table style=\"table-layout:fixed; width:1000px;\"><tr style=\"vertical-align:top \"><td>";

		$data=$dbw->getrows("select  mp.page_title  from mw_page mp
		where  mp.page_namespace=6  order by 1 ");
		$tableaumenus.="<h2>Images</h2></b>";
		for ($i = 0; $i < count($data); $i++)
		{
			$data[$j]["page_title"]=utf8_decode($data[$j]["page_title"]);
			$lien_page_title="<a href=\"http://www.wikistoma.org/wiki/index.php?title=Fichier:".$data[$i]["page_title"]."\" target=\"_blank\">".$data[$i]["page_title"]."</a>";

			$tableaumenus.=$lien_page_title." | ";
			

		}
		$tableaumenus.="</td></tr></table>";
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("wiki_main.css"));
		$page->register_style($ui->stylePath("wiki_shared.css"));
		$page->register_style($ui->stylePath("wiki_commonPrint.css"));
		$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
		$page->addContent($tableaumenus);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
	}
	function getstats($time_debut,$compteur_appels_mysql_query_debut)
	{
		global $g_sessionManager;
$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
if ($administrateur!='1') return "";
global $g_compteur_appels_mysql_query;
		$time_fin=gettimeofday(true);
		
		return "(".substr(($time_fin-$time_debut), 0,3)." sec. / ".($g_compteur_appels_mysql_query-$compteur_appels_mysql_query_debut)." queries)";
	}
	function toc_wiki() {
		global $ATK_VARS;
		atkimport("atk.menu.atkmenu");
		$dbw = & atkGetDb("assocopewiki");
		$data=$dbw->getrows("select  mp.page_title from mw_page mp
		where  mp.page_namespace!=6 and mp.page_title like 'Module_%' order by 1 ");
		$tableaumodules='<table class="toc  sortable">';
		$tableaumodules.='<td><div id="toctitle"><h2 class="toc  sortable">Modules</h2></div><ul>';
		for ($j = 0; $j < count($data); $j++)
		{
			$data[$j]["page_title"]=utf8_decode($data[$j]["page_title"]);
			$lien_page_title="<a href=\"dispatch.php?atknodetype=search.search&atkaction=wiki&title=".$data[$j]["page_title"]."\" target=\"_blank\">".($j+1)." ".ucfirst(str_replace("Module_","",$data[$j]["page_title"]))."</a>";
			$tableaumodules.="<li class=\"toclevel-1\"><span class=\"toctext\">$lien_page_title</span>";
			$tableaumodules.="</li>";
		}
		$tableaumodules.="</ul></table>";
		$data=$dbw->getrows("select  mp.page_title from mw_page mp
		where  mp.page_namespace!=6 and mp.page_title like 'Descripteur_%' order by 1 ");
		$tableaudescripteurs='<table class="toc  sortable">';
		$tableaudescripteurs.='<td><div id="toctitle"><h2 class="toc  sortable">Descripteurs</h2></div><ul>';
		for ($j = 0; $j < count($data); $j++)
		{
			$data[$j]["page_title"]=utf8_decode($data[$j]["page_title"]);
			$lien_page_title="<a href=\"dispatch.php?atknodetype=search.search&atkaction=wiki&title=".$data[$j]["page_title"]."\" target=\"_blank\">".($j+1)." ".ucfirst(str_replace("Descripteur_","",$data[$j]["page_title"]))."</a>";
			$tableaudescripteurs.="<li class=\"toclevel-1\"><span class=\"toctext\">$lien_page_title</span>";
			$tableaudescripteurs.="</li>";
		}
		$tableaudescripteurs.="</ul></table>";
		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Rest_Client');
		try {
			$texte_intro=$this->get_wiki_toc("Accueil","Introduction");
			$texte_interface=$this->get_wiki_toc("AssoCope_principes","Interface utilisateur");
			$texte_faqs=$this->get_wiki_toc("AssoCope_faqs","Faqs");
			$texte_nouveau=$this->get_wiki_toc("AssoCope_nouveautés","Nouveautés");
			$texte_internet=$this->get_wiki_toc("Internet","Internet");
			$texte_schema=$this->get_wiki_toc("AssoCope_schéma","Schéma");
			$texte_google=$this->get_wiki_toc("Google","Google");
		} catch (Exception $e) {
			die('ERROR: ' . $e->getMessage());
		}
		$tableaumenus.="<table style=\"border-color:black; border-style:solid; border-width:1px; background-color: lightyellow;\">";
		$tableaumenus.="<tr style=\"vertical-align:top;\"><td><b>Wiki AssoCope</b></td></tr>";
		$tableaumenus.="<tr style=\"vertical-align:top;\"><td>";
		$tableaumenus.="<table style=\"border-style:none;\">";
		$tableaumenus.="<tr style=\"vertical-align:top;\">";
		$tableaumenus.='<td class="toc  sortable">'.$texte_intro."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$texte_interface."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$texte_schema."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$tableaudescripteurs."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$tableaumodules."</td>";
		$tableaumenus.="</tr>";
		$tableaumenus.="</table>";
		$tableaumenus.="</td></tr>";
		$tableaumenus.="<tr style=\"vertical-align:top;\"><td>";
		$tableaumenus.="<table style=\"border-style:none;\">";
		$tableaumenus.="<tr style=\"vertical-align:top;\">";
		$tableaumenus.='<td class="toc  sortable">'.$texte_internet."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$texte_google."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$texte_faqs."</td>";
		$tableaumenus.='<td class="toc  sortable">'.$texte_nouveau."</td>";
		$tableaumenus.="</tr>";
		$tableaumenus.="</table>";
		$tableaumenus.="</td></tr>";
		$tableaumenus.="</table>";
		return $tableaumenus;

	}
	function get_wiki_toc($query,$libelle)
	{
		$wikipedia = new Zend_Rest_Client('http://www.wikistoma.org/wiki/api.php');
		$wikipedia->action('parse');
		$wikipedia->page($query);
		$wikipedia->format('xml');
		$result = $wikipedia->get();
		$texte=$result->api->parse->text;
		$texte=utf8_decode($texte);
		$texte=substr($texte, strpos($texte, "<table "),strpos($texte, "</table>")+8);
		$texte=str_replace(">Sommaire<", ">".$libelle."<", $texte);
		$texte=str_replace("href=\"#", " target=\"_blank\" href=\"dispatch.php?atknodetype=search.search&atkaction=wiki&title=$query#", $texte);
		$texte=substr($texte, strpos($texte, "<table "),strpos($texte, "</table>")+8);
		return $texte;
	}

	function action_search(& $handler) {
		global $g_sessionManager;
		// Searchstring is a stackvar. We get it through the post_vars,
		// but we need to store it in the session stack, so the system
		// remembers the last searchstring when coming back from a
		// view action.
		$searchstring = strip_tags($g_sessionManager->stackVar("searchstring"));
		$outil = strip_tags($g_sessionManager->stackVar("outil"));
		$langue = strip_tags($g_sessionManager->stackVar("langue"));
		$marquepage = strip_tags($g_sessionManager->stackVar("marquepage"));
		if (!empty($marquepage))
		{$db = & atkGetDb();
		$data = $db->getrows("SELECT url  from individu_bookmark where id=$marquepage");
		$db->query("update individu_bookmark set nombre_acces=nombre_acces+1 where id=$marquepage");
		$url = $data[0]["url"];
		$url_racine = $_SERVER["SCRIPT_URI"];
		$url_racine = str_replace("dispatch.php", '', $url_racine);
		$url = str_replace("[assocope]", $url_racine, $url);

		// GG LOg
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$param =$url;
		$sql="INSERT INTO atkeventlog (id, userid, stamp, node, action, parametres)
		VALUES(".$db->nextid("atkeventlog").", $id, UTC_TIMESTAMP, '.', 'recherche(utilisateur)', '$param')";
		$db->query($sql);
		$db->commit();
		// GG FIN

		header('Location: ' . $url);
		}
		if (!empty($outil))
		{			$db = & atkGetDb();
		$data = $db->getrows("SELECT url_recherche, url_english, url_site  from type_moteur where id=$outil");
		$db->query("update type_moteur set nombre_acces=nombre_acces+1 where id=$outil");
		if (!empty($searchstring)) $url = $data[0]["url_recherche"];
		else { $url = $data[0]["url_site"];}
		if ($langue=='en') $url = $data[0]["url_english"];
		if (!empty($searchstring)) $url = str_replace("[lang]", $langue, $url);
		if (!empty($searchstring)) 			$url = str_replace("[string]", $searchstring, $url);
		$url_racine = $_SERVER["SCRIPT_URI"];
		$url_racine = str_replace("dispatch.php", '', $url_racine);
		$url = str_replace("[assocope]", $url_racine, $url);
		// GG LOg
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$param =$url;
		$sql="INSERT INTO atkeventlog (id, userid, stamp, node, action, parametres)
		VALUES(".$db->nextid("atkeventlog").", $id, UTC_TIMESTAMP, '.', 'recherche(assocope)', '$param')";
		$db->query($sql);
		$db->commit();
		// GG FIN
		header('Location: ' . $url);

		}
	}
	function action_search_assocope(& $handler) {
		global $g_sessionManager;
		// Searchstring is a stackvar. We get it through the post_vars,
		// but we need to store it in the session stack, so the system
		// remembers the last searchstring when coming back from a
		// view action.
		$searchstring = strip_tags($g_sessionManager->stackVar("searchstring"));


		$db = & atkGetDb();

		if ($searchstring != "") {
			$results = atkHarvestModules("search", $searchstring, true);
			$firsturl = "";
			$res = "";
			foreach ($results as $module => $moduleresults) {
				foreach ($moduleresults as $category => $items) {
					$cnt = count($items);
					if ($cnt > 0) {
						$hasresults += $cnt;
						$res .= '<br><b>' . atktext($category, $module) . '</b><br>';
						for ($i = 0; $i < $cnt; $i++) {
							$res .= '<br>&nbsp; &nbsp;' . href($items[$i]["url"], $items[$i]["title"], SESSION_NESTED);
							if ($firsturl == "")
							$firsturl = $items[$i]["url"];
						}
						$res .= '<br>';
					}
				}
			}
			if ($hasresults == 0) {
				$res = '<br>' . sprintf(atktext("search_noresults"), $searchstring);
			} else
			if ($hasresults == 1) {
				// autoview first url
				return $this->redirect(session_url($firsturl, SESSION_REPLACE));
			}
		} else {
			$res = '<br>' . atktext("search_emptysearchstring");
		}
		$res .= '<br><br>' . atktext('search_again') . ':<br>';
		$res .= $this->simpleSearchForm($searchstring, "", SESSION_DEFAULT) . '<br><br>';
		$ui = & $this->getUi();
		$page = & $this->getPage();
		$this->addStyle("style.css");
		$box = $ui->renderBox(array (
			"title" => atkText("search",
			"search"
			), "content" => $res));
			$actionpage = $this->renderActionPage("search", $box);
			$page->addContent($actionpage);
			return true;
	}
	function simpleSearchForm($searchstring, $targetframe = "", $sessionstatus = SESSION_NESTED) {


		$res = '<td align="left"><form name="recherche" action="dispatch.php"' . ($targetframe != "" ? 'target="' . $targetframe . '"' : '') . '>';

		$res .= '<input type="hidden" name="atknodetype" value="search.search">';
		$res .= '<input type="hidden" name="atkaction" value="search">';
		$res .= session_form($sessionstatus);
		$menutip=fairetooltip("menu_tooltip_topmenu_Critererecherche");
		$res .= '&nbsp;<input '.$menutip.' name="searchstring" style="width: 100px;" type="text" size="18" value="' . $searchstring . '">&nbsp;';
		$res .= '&nbsp;en&nbsp;';
		$res .= $this->liste_langues();
		$res .= '&nbsp;dans&nbsp;';
		$res .= $this->liste_moteurs();
		$res .= '&nbsp;<input class="atkbutton" type="submit" value="' . atktext("Ok") . '">';
		$res .= '</form></td><td align="right">';

		$res .= '<form  name="marquepages" action="dispatch.php"' . ($targetframe != "" ? 'target="' . $targetframe . '"' : '') . '>';
		$res .= '<input type="hidden" name="atknodetype" value="search.search">';
		$res .= '<input type="hidden" name="atkaction" value="search">';
		$res .= session_form($sessionstatus);
		$res .= ' Marques pages&nbsp;';
		$res .= $this->liste_bookmarks();
		$res .= '&nbsp;<input class="atkbutton" type="submit" value="' . atktext("Ok") . '">';
		$res .= '</form></td>';
		return $res;
	}
	function liste_langues() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT code_iso_639_1, libelle_francais from type_langue order by libelle_francais");
		$language = atkconfig("language");
		$menutip=fairetooltip("menu_tooltip_topmenu_Langues");
		//  	      $values = $this->getValues($record);
		$result = '<select '.$menutip.'style="width: 75px;"  ';

		$result .= 'name="langue">';
		for ($i = 0, $_i = count($data); $i < $_i; $i++) {
			if ($data[$i]["code_iso_639_1"] == $language) {
				$sel = "selected";
			} else {
				$sel = "";
			}
			$result .= '<option value="' . $data[$i]["code_iso_639_1"] . '" ' . $sel . '>' . $data[$i]["libelle_francais"];
		}
		$result .= '</select>';
		return $result;
	}
	function liste_moteurs() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id, concat(sujet,' (',moteur,')') as nom from type_moteur order by 2");
		$moteur = 3;
		$menutip=fairetooltip("menu_tooltip_topmenu_Moteurs");
		$result = '<select '.$menutip.' style="width: 150px;" ';
		$result .= 'name="outil">';
		for ($i = 0, $_i = count($data); $i < $_i; $i++) {
			if ($data[$i]["id"] == $moteur) {
				$sel = "selected";
			} else {
				$sel = "";
			}
			$result .= '<option value="' . $data[$i]["id"] . '" ' . $sel . '>' . $data[$i]["nom"];
		}
		$result .= '</select>';
		return $result;
	}
	function liste_bookmarks() {
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
		$id_individu = $data[0]["id_individu"];
		$data = $db->getrows("SELECT libelle,id  from individu_bookmark where id_individu=$id_individu and actif='1' order by libelle");
		//		$result = '<select  name="marquepage" style="width: 300px;" onchange="document.marquepages.submit();" > ';
		$menutip=fairetooltip("menu_tooltip_topmenu_Marquepages");
		$result = '<select '.$menutip.' name="marquepage" style="width: 300px;"  > ';
		for ($i = 0, $_i = count($data); $i < $_i; $i++) {

			$result .= '<option value="' . $data[$i]["id"] . '" ' . ' ' . '>' . $data[$i]["libelle"];
		}
		$result .= '</select>';
		return $result;
	}


}
?>