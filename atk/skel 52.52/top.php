<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * This file is the skeleton top frame file, which you can copy
 * to your application dir and modify if necessary. By default,
 * it displays the currently logged-in user and a logout link.
 *
 * @package atk
 * @subpackage skel
 *
 * @author Ivo Jansch <ivo@achievo.org>
 *
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 4913 $
 * $Id: top.php 4913 2008-03-18 20:39:29Z sandy $
 */
/**
 * @internal includes.
 */

$config_atkroot = "./";
include_once ("atk.inc");
include_once (atkconfig("atkroot") . "modules/include/fairetooltip.inc");
atksession();
atksecure();
//  require("theme.inc");
$page = & atkNew("atk.ui.atkpage");
$ui = & atkInstance("atk.ui.atkui");
$theme = & atkInstance("atk.ui.atktheme");
$output = & atkInstance("atk.ui.atkoutput");
$page->register_style($theme->stylePath("style.css"));
$page->register_style($theme->stylePath("top.css"));
// GG
global $g_sessionManager;
global $g_nomutilisateur;
global $g_tooltip_menu_o_n;
$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
$g_identifiant_google = $g_sessionManager->getValue("identifiant_google", "globals");
$g_tooltip_menu_o_n = $g_sessionManager->getValue("tooltip_menu_o_n", "globals");
$g_sexe = $g_sessionManager->getValue("sexe", "globals");
$g_libelle_profil = $g_sessionManager->getValue("atgProfilUtilisateur", "globals");
$Administrateur_o_n=$g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
$username = "<b>" . $g_nomutilisateur . "</b> (" . $g_libelle_profil . ")";


$menutip=fairetooltip("menu_tooltip_topmenu_Deconnexion");
$logout = ' <a href="index.php?atklogout=1" target="_top" '. $menutip .'>' . ucfirst(atktext("logout", "atk")) . '</a>';
;
$centerpiecelinks = array ();
// Get center piece
$user = & atkGetUser();
if ($user["name"] != "administrator") {
	$dispatcher = $theme->getAttribute('dispatcher', atkconfig("dispatcher", "dispatch.php")); // do not use atkSelf here!
	$c = & atkinstance("atk.atkcontroller");
	$c->setPhpFile($dispatcher);

	if ($theme->getAttribute('useframes', true)) {
		$target = 'target="main"';
	} else {
		$target = "";
	}

	$menutip=fairetooltip("menu_tooltip_topmenu_Outils");
	$outils=href('menu.php?atkmenutop=Outils', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/tool-icon.png" alt="Outils" title="Outils"></img>', SESSION_DEFAULT, false, 'target="menu"' . $menutip) . $delimiter;
	$menutip=fairetooltip("menu_tooltip_topmenu_Rd");
	$retd=href('menu.php?atkmenutop=Rd', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/development-tools-icon.png" alt="R&D" title="R&D"></img>', SESSION_DEFAULT, false, 'target="menu"' . $menutip) . $delimiter;
	$menutip=fairetooltip("menu_tooltip_topmenu_Divers");
	$divers=href('menu.php?atkmenutop=Divers', atktext("Divers", "atk"), SESSION_DEFAULT, false, 'target="menu"' . $menutip) . $delimiter;
	$menutip=fairetooltip("menu_tooltip_topmenu_Rappels");
	$rappels= $centerpiecelinks['rappels'] = href(dispatch_url("pim.pim", "pim"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/App-reminders-icon.png" alt="Rappels" title="Rappels"></img>', SESSION_NEW, false, $target  . $menutip);
	$menutip=fairetooltip("menu_tooltip_topmenu_Préférences");
	$preferences= href(dispatch_url("profil.userprefs", "edit", array (
			"atkselector" => "app_utilisateur.id='" . $g_user["id"] . "'"
	)), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/gear-icon.png" alt="Préférences" title="Préférences"></img>', SESSION_NEW, false, $target . $menutip);
	$menutip=fairetooltip("menu_tooltip_Google");
	$google= href('menu.php?atkmenutop=Google',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Google-Plus-1-icon.png" alt="Google" title="Google"></img>',SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
}

// $menutip=fairetooltip("menu_tooltip_topmenu_BlocNote");
	

$duree=GetWikiPageAge("Menu_haut");
if (empty($duree))
{
	$aided='Aide';
}
else if ($duree<8)
{
	$aided='<span style="color:Red"><b>Aide</b></span>';
}
else if ($duree<32)
{
	$aided='<span style="color:Orange"><b>Aide</b></span>';
}
else
{		$aided='<b>Aide</b>';
}
$aided.='|<a href="https://groups.google.com/forum/#!forum/assocope" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/user-group-icon.png" alt="Forum AssoCope" title="Forum AssoCope" target="_blank"></img></a>'.'' ;

$menutip=fairetooltip("menu_tooltip_topmenu_Aide");
$aide=href(dispatch_url("search.search", "wiki",	array("title"=>"Menu_haut")),    $aided,	SESSION_NEW,	false, ' target="_blank"'. $menutip);
$menutip=fairetooltip("menu_tooltip_topmenu_Tousmenus");
$tousmenus=href(dispatch_url("search.search", "tousmenus",	array("title"=>"Tous menus")),    "?",	SESSION_NEW,	false, ' target="_blank"'. $menutip);
	
//			$aide=href("http://www.wikistoma.org/wiki/index.php?title=Menu_haut",$aided, SESSION_NEW, false, 'target="_blank"'. $menutip);
$menutip=fairetooltip("menu_tooltip_topmenu_Faqs");
$duree=GetWikiPageAge("AssoCope_faqs");
if (empty($duree))
{
	$faqs='Faqs';
}
else if ($duree<8)
{
	$faqs='<span style="color:Red"><b>Faqs</b></span>';
}
else if ($duree<32)
{
	$faqs='<span style="color:Orange"><b>Faqs</b></span>';
}
else
{		$faqs='<b>Faqs</b>';
}
$faqs=href(dispatch_url("search.search", "wiki",	array("title"=>"AssoCope_faqs")),    $faqs,	SESSION_NEW,	false, ' target="_blank"'. $menutip);
//			$faqs=href("http://www.wikistoma.org/wiki/index.php?title=AssoCope_faqs", $faqs, SESSION_NEW, false, 'target="_blank"' . $menutip);
$duree=GetWikiPageAge("AssoCope_nouveaut%C3%A9s");
if (empty($duree))
{
	$aided='Nouveau';
}
else if ($duree<8)
{
	$aided='<span style="color:Red"><b>Nouveau</b></span>';
}
else if ($duree<32)
{
	$aided='<span style="color:Orange"><b>Nouveau</b></span>';
}
else
{		$aided='<b>Nouveau</b>';
}
$menutip=fairetooltip("menu_tooltip_topmenu_Nouveau");
$nouveau=href(dispatch_url("search.search", "wiki",	array("title"=>"AssoCope_nouveaut%C3%A9s")),    $aided,	SESSION_NEW,	false, ' target="_blank"'. $menutip);
//			$nouveau=href("http://www.wikistoma.org/wiki/index.php?title=AssoCope_nouveaut%C3%A9s", $aided, SESSION_NEW, false, 'target="_blank"' . $menutip);

if (is_allowed("profil.userprefs", "edit")) {
}
else {
	// Administrator has a link to setup.php
	$centerpiece = $centerpiecelinks['setup'] = href("setup.php", atktext("setup"), SESSION_NEW, false, 'target="_top"');
}
// Get search piece
if ($theme->getAttribute('useframes', true)) {
	$target = 'target="main"';
} else {
	$target = "";
}


$node = atkconfig("top_search_node") ? atkconfig("top_search_node") : "search.search";
$searchnode = & atkGetNode($node);
$searchpiece = $searchnode->simpleSearchForm("", $target, SESSION_NEW);
$menutip=fairetooltip("menu_tooltip_topmenu_Nomutilisateur");
$centerpiece="<font color='Blue'>".href('menu.php?atkmenutop=Utilisateur', atktext($username, "atk"), SESSION_DEFAULT, false, 'target="menu"' . $menutip);


(($g_identifiant_google)=="") ? $centerpiece.="" : $centerpiece.='|'.$google;
$centerpiece.='|'.$aide . '|'.$tousmenus . '|'.$faqs . '|'.$nouveau;
if ($Administrateur_o_n=='1') {
	$menutip=fairetooltip("menu_tooltip_topmenu_Administrer");
	$centerpiece.='|' .href('menu.php?atkmenutop=Administrer', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Administrator-icon.png" alt="Administrer" title="Administrer"></img>', SESSION_DEFAULT, false, 'target="menu"'. $menutip);
	$log=href(dispatch_url("organisme.tableaudebord", "tableau_logs", array ("type_tableau"=>"logs"
			)), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/log-icon.png" alt="AssoCope wiki" title="Logs" target="_blank"></img>', SESSION_NEW, false, 'target="_blank" '  ) . "";
	$centerpiece.='|' .$log;
	$menutip=fairetooltip("menu_tooltip_topmenu_Langues_lng");
	$centerpiece.='|' .href('menu.php?atkmenutop=Langues', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google-translate-android-app.png" alt="Traduction des messages" title="Traduction des messages"></img>', SESSION_DEFAULT, false, 'target="menu"'. $menutip);
	$centerpiece.='|' .$retd.'|' .$divers;
}
$centerpiece.='|'.$outils.'|'.$preferences . '|'.$rappels.'|'.$logout."</font>";
$delimiter=' ';
$menu ='<script language="JavaScript" type="text/javascript">
		function hideLeftFrame() {
		var lfr = window.top.document.getElementById("leftframe");
		if (lfr.cols == "220, *")
		{ lfr.cols ="0, *";   }
		else
		{ lfr.cols ="220, *";}
}
		</script>';

$user = getUser();
$id = $user["id"];
if (isset ($id)) {
	$db = & atkGetDb();
	$data = $db->getrows("SELECT id_individu, biodiversite_o_n from app_utilisateur where id=" . $id . " ");
	$id_individu = $data[0]["id_individu"];
	$option_biodiversite_o_n = $data[0]["biodiversite_o_n"];
	$data = $db->getrows("select id_entite, nom from app_recent_use, organisme where
			id_individu=$id_individu and type_entite='organisme' and id_entite=organisme.id order by date_recent_use desc");
	$id_organisme = $data[0]["id_entite"];
	$organisme_nom = $data[0]["nom"];
	$data = $db->getrows("select nom, prenom, sexe,id_entite from app_recent_use, individu where
			id_individu=$id_individu and type_entite='individu' and id_entite=individu.id order by date_recent_use desc");
	$individu_sexe = $data[0]["sexe"];
	$individu_nom = $data[0]["nom"].' '.$data[0]["prenom"];
	$id_individu = $data[0]["id_entite"];
}
	
$menutip=fairetooltip("menu_tooltip_topmenu_Montrercachermenugauche");
$menu .='<a href="javascript:void(0)" color="blue" onclick="javascript:hideLeftFrame(this)" '.$menutip.' title="Montrer/cacher le menu gauche" alt="ouvrir/fermer" ><b>&lt;&gt;</b></a>'. $delimiter	;
$menutip=fairetooltip("menu_tooltip_topmenu_Accueil");
$menu .= href('index.php?atkdebug[key]=toto', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/home.png" alt="Accueil" title="Accueil" ></img> '.atktext("Accueil", "atk"), SESSION_DEFAULT, false, 'target="_top" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Utilisateur");
($g_sexe=='F')? $icon='moi_elle.png' : $icon='moi_lui.png';
$menu .= href('menu.php?atkmenutop=Utilisateur','<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icon.'" alt="Utilisateur" title="Utilisateur" ></img> '.atktext("Utilisateur", "atk"),SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Individus");
($individu_sexe=='F')? $icon='individu_elle.png' : $icon='individu.png';

$popup=atkPopup(atkconfig("atkroot").'atk/popups/qrpopup.inc','type=individu&id='.$id_individu,'Coordonnées individu',700,350,'yes','no');
$icone_individu='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icon.'" alt="Coordonnées individu" title="Coordonnées '.$individu_nom.'" target="_blank"></img></a>'.'' ;

$menu .= '<span id="blocio">'.$icone_individu;
$menu .= href('menu.php?atkmenutop=Individus', atktext("Individus", "atk"),SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;

$popup=atkPopup(atkconfig("atkroot").'atk/popups/qrpopup.inc','type=organisme&id='.$id_organisme,'Coordonnées organisme',700,300,'yes','no');
$icone_organisme='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/organisme.png" alt="Coordonnées organisme" title="Coordonnées '.$organisme_nom.'" target="_blank"></img></a>'.'' ;

$menutip=fairetooltip("menu_tooltip_topmenu_Organismes");
$menu .= $icone_organisme;
$menu .= href('menu.php?atkmenutop=Organismes', atktext("Organismes", "atk"),SESSION_DEFAULT, false, 'target="menu" '.$menutip) ;
$url_tbdebord=dispatch_url("organisme.tableaudebord", "tableau_organisme", array (
"id_organisme" => $id_organisme,
"type_tableau"=>"organisme" ));
$icone_organisme_tbdebord='<a href='.$url_tbdebord.' target="_blank" ><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/chart-search-icon.png" alt="Tableaux de bord organisme" title="Tableaux de bord de '.$organisme_nom.'" target="_blank"></img></a>'.'' ;
$menu .=" ".$icone_organisme_tbdebord . '</span>'.$delimiter;

if ($option_biodiversite_o_n=='1' )
{
	$menutip=fairetooltip("menu_tooltip_topmenu_Taxons");
	$menu .= href('menu.php?atkmenutop=Taxons',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/taxinomie.png" alt="Taxons" title="Taxons"></img> '.atktext("Taxons", "atk"),SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
}
$menutip=fairetooltip("menu_tooltip_topmenu_Rencontres");
$menu .= href('menu.php?atkmenutop=Rencontres',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/rencontre.png" alt="Rencontres" title="Rencontres"></img> '.atktext("Rencontres", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Traitements");
$menu .= href('menu.php?atkmenutop=Traitements', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/traitement.png" alt="Traitements" title="Traitements"></img> '.atktext("Traitements", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Envois");
// $menu .= href('menu.php?atkmenutop=Envois', atktext("Envois", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Comptabilite");
$menu .= href('menu.php?atkmenutop=Comptabilite_o',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/comptabilite.png" alt="Comptabilité" title="Comptabilité"></img> '.atktext("Comptabilité", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Operationsdebanque");
$menu .= href('menu.php?atkmenutop=Comptes', '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/banque.png" alt="Opérations de banque" title="Opérations de banque"></img> '.atktext("Opérations de banque", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Lieux");
$menu .= href('menu.php?atkmenutop=Lieux_l',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/lieu.png" alt="Lieux" title="Lieux"></img> '.atktext("Lieux", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menutip=fairetooltip("menu_tooltip_topmenu_Tables");
$menu .= href('menu.php?atkmenutop=Tables',  '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/table.png" alt="Tables" title="Tables"></img> '.atktext("Tables", "atk"), SESSION_DEFAULT, false, 'target="menu" '.$menutip) . $delimiter;
$menu .= '&nbsp&nbsp&nbsp&nbsp';
$accueil=$menu;
$content="";
// $title = '<b>' . $wikiassoc_user . ' avec ' . href("http://www.wikistoma.org/wiki", atktext($wikiassoc_name), SESSION_NEW, false, 'target="_blank"') . ' - version : ' . $wikiassoc_version . ' ' . $wikiassoc_state . ' du ' . $wikiassoc_date . '.(Atk : ' . atkversion() . ')</b>';
$top = $ui->renderBox(array (
		"centerpiece" => $centerpiece,
		"accueil" => $accueil,
		"searchpiece" =>$searchpiece,
)
		, "top");
$page->addContent($top);
$output->output($page->render(atktext("app_title"), true));
//$output->output(" <script type='text/javascript' src='./modules/development/javascript/wz_tooltip.js'></script>
//        <script type='text/javascript' src='./modules/development/javascript/tip_balloon.js'></script> ");


$output->outputFlush();

function GetWikiPageAge($pagename)
{
	$dbw = & atkGetDb("assocopewiki");
	if ($pagename=="AssoCope_nouveaut%C3%A9s")
	{
		$data=$dbw->getrows("select page_touched from mw_page where page_id='47'");
	}
	else
	{$data=$dbw->getrows("select page_touched from mw_page where page_title='". $pagename ."'");
	}
	$page_touched=$data[0]["page_touched"];
	if (empty($page_touched)) return "";
	$hours=substr($page_touched, 8,2);
	$minutes=substr($page_touched, 10,2);
	$seconds=substr($page_touched, 12,2);
	$month=substr($page_touched, 4,2);
	$day=substr($page_touched, 6,2);
	$year=substr($page_touched, 0,4);
	$page_touched= mktime($hours,$minutes,$seconds,$month,$day,$year);
	$time=time();
	return (($time-$page_touched)/3600/24);
}


?>