<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * This file is the skeleton main frameset file, which you can copy
 * to your application dir and modify if necessary. By default, it checks
 * the settings $config_top_frame to determine how many frames to show,
 * and reads the menu config to display the proper menu.
 *
 * @package atk
 * @subpackage skel
 *
 * @author Ivo Jansch <ivo@achievo.org>
 *
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 4912 $
 * $Id: app.php 4912 2008-03-18 20:32:17Z sandy $
 */

/**
 * @internal includes..
 */
//	echo "Finidebutapp";die();
$config_atkroot = "./";
include_once("atk.inc");

atksession();

atksecure();
//echo "Finidebutapres secure";die();
include "theme.inc";
global $g_sessionManager ;



global $g_user;



if ($g_user["name"] != "administrator") {
	$db = & atkGetDb();
	$user = getUser();
	$id = $user["id"];
	$data = $db->getrows("SELECT google_map_key, ubio_keycode, tracer_mysqldb_query_o_n, en_travaux_o_n, debug_o_n from app_globales");
	$google_map_key=$data[0]["google_map_key"];
	$ubio_keycode=$data[0]["ubio_keycode"];
	$g_tracer_mysqldb_query_o_n=$data[0]["tracer_mysqldb_query_o_n"];
	$g_en_travaux_o_n=$data[0]["en_travaux_o_n"];
	$g_debug_o_n=$data[0]["debug_o_n"];
	//	print_r($_SERVER);
	//	die();
	$data = $db->getrows("SELECT p.acces_public_seulement as acces_public, p.id as profil ,p.libelle as libelle_profil, i.nom as nom,
			i.prenom as prenom, i.id as id_individu_utilisateur, p.administrateur_general_o_n as administrateur,i.sexe, i.identifiant_google,
			p.traitements_o_n as traitements_o_n
			,
		 u.date_signature_contrat as date_signature_contrat, u.contexte_o_n as contexte_o_n,i.tz_offset_google  as tz_offset_google ,
		 u.tt_o_n as tooltip_menu_o_n,
		 u.sticky_tt_o_n as sticky_tooltip_o_n,
			u.stats_page_o_n as stats_page_o_n,
		 u.icones_detaillees_o_n as icones_detaillees_o_n,
		 u.afficher_portrait_o_n as afficher_portrait_o_n,
		 u.tt_couleur_bg as tooltip_color,
		 u.trace_db_o_n as trace_db_o_n,
		 u.log_o_n as log_o_n,
		 u.debug_o_n as debug_o_n,
		 u.golf_o_n as golf_o_n,
		 u.uploads_utilisateurs_o_n as uploads_utilisateurs_o_n,
		 u.uploads_organismes_o_n as uploads_organismes_o_n,
		 u.biodiversite_o_n as biodiversite_o_n,
		 u.manytoone_autocomplete_minchars as manytoone_autocomplete_minchars,
		 u.table_des_matieres_wiki_o_n as table_des_matieres_wiki_o_n,
		 u.debug_o_n as debug_o_n,
			u.acces_restreint_o_n,
			u.url_acces_restreint
				
				
			from
			app_utilisateur u, app_profil p, individu i
			where u.id =" . $id . "
					and u.id_profil=p.id
					and u.id_individu=i.id");

	$db->query("UPDATE app_utilisateur
			set nombre_de_logins=nombre_de_logins+1 ,
			date_dernier_login='".gmdate(c)."'
			where id=$id");


	global  $g_sessionManager;
	global $g_administrateur;
	$date_signature_contrat= $data[0]["date_signature_contrat"];
	$g_acces_public_seulement = $data[0]["acces_public"];
	$g_contexte_o_n= $data[0]["contexte_o_n"];
	$g_sexe= $data[0]["sexe"];
	$g_wiki_url="http://www.wikistoma.org/wiki/index.php?title=";
	$g_tooltip_menu_o_n= $data[0]["tooltip_menu_o_n"];
	$g_icones_detaillees_o_n= $data[0]["icones_detaillees_o_n"];
	$g_afficher_portrait_o_n= $data[0]["afficher_portrait_o_n"];
	$g_sticky_tooltip_o_n= $data[0]["sticky_tooltip_o_n"];
	$g_stats_page_o_n= $data[0]["stats_page_o_n"];
	$g_tooltip_color= $data[0]["tooltip_color"];
	$g_trace_db_o_n= $data[0]["trace_db_o_n"];
	$g_log_o_n= $data[0]["log_o_n"];
	$g_user_debug_o_n= $data[0]["debug_o_n"];
	$g_acces_restreint_o_n= $data[0]["acces_restreint_o_n"];
	$g_url_acces_restreint= $data[0]["url_acces_restreint"];
	$g_traitements_o_n=$data[0]["traitements_o_n"];
	$g_nomutilisateur=$data[0]["prenom"]." ".$data[0]["nom"];
	$g_manytoone_autocomplete_minchars=$data[0]["manytoone_autocomplete_minchars"];
	$g_table_des_matieres_wiki_o_n= $data[0]["table_des_matieres_wiki_o_n"];
	$g_golf_o_n= $data[0]["golf_o_n"];
	$g_uploads_utilisateurs_o_n= $data[0]["uploads_utilisateurs_o_n"];
	$g_uploads_organismes_o_n= $data[0]["uploads_organismes_o_n"];

	$g_biodiversite_o_n= $data[0]["biodiversite_o_n"];
	$g_administrateur=$data[0]["administrateur"];
	$g_id_individu_utilisateur=$data[0]["id_individu_utilisateur"];
	$g_identifiant_google = $data[0]["identifiant_google"];
	$g_id_profil = $data[0]["profil"];
	$g_libelle_profil = $data[0]["libelle_profil"];
	$g_tz_offset_google = $data[0]["tz_offset_google"];
	$data = $db->getrows("SELECT date_texte_contrat from app_globales ");
	$date_texte_contrat=$data[0]["date_texte_contrat"];
	$g_organismes_autorises = array ();
	$data = $db->getrows("SELECT id_organisme from app_profil_organisme
			where app_profil_organisme.id_profil =" . $g_id_profil . " ");
	for ($i = 0, $_i = count($data); $i < $_i; $i++) {
		$g_organismes_autorises = array ();
		$g_organismes_autorises[] = $data[$i]["id_organisme"];
	}
	global $g_compteur_appels_mysql_query;
	global $g_trace_mysql_query;
	$g_compteur_appels_mysql_query = 0;
	global $g_trace_atklanguage;
	$g_trace_atklanguage= "";
	$g_trace_mysql_query="";
	$lng = atkLanguage::getLanguage();
	$sql="select id from type_langue where
	code_iso_639_1='$lng'";
	$data = $db->getrows($sql);
	if (count($data) >0) $id_lng=$data[0]["id"];
	$g_sessionManager->globalVar("id_langue", $id_lng, true);
	$g_sessionManager->globalVar("google_map_key", $google_map_key, true);
	$g_sessionManager->globalVar("ubio_keycode", $ubio_keycode, true);
	$g_sessionManager->globalVar("id_individu_utilisateur", $g_id_individu_utilisateur, true);
	$g_sessionManager->globalVar("atgAccesPublicSeul_o_n", $g_acces_public_seulement, true);
	$g_sessionManager->globalVar("atgOrganismesAutorises", $g_organismes_autorises, true);
	$g_sessionManager->globalVar("atgAdministrateur_o_n", $g_administrateur, true);
	$g_sessionManager->globalVar("tracer_mysqldb_query_o_n", $g_tracer_mysqldb_query_o_n, true);
	$g_sessionManager->globalVar("en_travaux_o_n", $g_en_travaux_o_n, true);
	$g_debug_level=-1;
	$g_sessionManager->globalVar("traitements_o_n", $g_traitements_o_n, true);
	$g_sessionManager->globalVar("log_o_n", $g_log_o_n, true);
	$g_sessionManager->globalVar("user_debug_o_n", $g_user_debug_o_n, true);
	$g_sessionManager->globalVar("debug_o_n", $g_debug_o_n, true);
	$g_sessionManager->globalVar("acces_restreint_o_n", $g_acces_restreint_o_n, true);
	$g_sessionManager->globalVar("url_acces_restreint", $g_url_acces_restreint, true);
	$g_sessionManager->globalVar("golf_o_n", $g_golf_o_n, true);
	$g_sessionManager->globalVar("uploads_utilisateurs_o_n", $g_uploads_utilisateurs_o_n, true);
	$g_sessionManager->globalVar("uploads_organismes_o_n", $g_uploads_organismes_o_n, true);
	$g_sessionManager->globalVar("identifiant_google", $g_identifiant_google, true);
	$g_sessionManager->globalVar("biodiversite_o_n", $g_biodiversite_o_n, true);
	$g_sessionManager->globalVar("manytoone_autocomplete_minchars", $g_manytoone_autocomplete_minchars, true);
	$g_sessionManager->globalVar("table_des_matieres_wiki_o_n", $g_table_des_matieres_wiki_o_n, true);
	$g_sessionManager->globalVar("trace_db_o_n", $g_trace_db_o_n, true);

	$g_sessionManager->globalVar("contexte_o_n", $g_contexte_o_n, true);
	$g_sessionManager->globalVar("wiki_url", $g_wiki_url, true);
	$g_sessionManager->globalVar("sexe", $g_sexe, true);
	$g_sessionManager->globalVar("tooltip_menu_o_n", $g_tooltip_menu_o_n, true);
	$g_sessionManager->globalVar("icones_detaillees_o_n", $g_icones_detaillees_o_n, true);
	$g_sessionManager->globalVar("afficher_portrait_o_n", $g_afficher_portrait_o_n, true);
	$g_sessionManager->globalVar("sticky_tooltip_o_n", $g_sticky_tooltip_o_n, true);
	$g_sessionManager->globalVar("stats_page_o_n", $g_stats_page_o_n, true);
	$g_sessionManager->globalVar("tooltip_color", $g_tooltip_color, true);
	$g_sessionManager->globalVar("tz_offset_google", $g_tz_offset_google, true);
	$g_sessionManager->globalVar("atgNomUtilisateur", $g_nomutilisateur, true);
	$g_sessionManager->globalVar("atgIdIndividuUtilisateur", $g_id_individu_utilisateur, true);
	$g_sessionManager->globalVar("atgProfilUtilisateur", $g_libelle_profil, true);
	$db = & atkGetDb();

	global $g_utilisateur_individu;
	$g_utilisateur_individu = array ();
	$data = $db->getrows("SELECT id, id_individu FROM app_utilisateur ");
	for ($i = 0; $i <= count($data); $i++)
	{
		$g_utilisateur_individu[$data[$i]["id"]]=$data[$i]["id_individu"];
	}
	$g_sessionManager->globalVar("utilisateur_individu", $g_utilisateur_individu, true);


	// GG
	// Les stockers dans un tableau
	// Regarder ce tableau avant de traduire dans atklanguage
	//	echo "Pour voir";die();

	$time_debut=gettimeofday(false);
	$debut=	$time_debut["sec"];
	global $g_traduction_texte;
	$g_traduction_texte = array ();
	global $g_traduction_tt;
	$g_traduction_tt = array ();
	$data = $db->getrows("SELECT nom_module, nom_noeud, id_type_traduction, id_type_langue, texte_source, texte_tt
			FROM app_traduction
			WHERE LENGTH(texte_tt) >0
			AND id_type_langue =20
			AND (id_type_traduction=5 or id_type_traduction=2)
		 ");
	$separateur=" @|* ";
	for ($i = 0; $i <= count($data); $i++)
	{
		$g_traduction_tt[$data[$i]["nom_module"].$separateur.$data[$i]["id_type_langue"].$separateur.$data[$i]["nom_noeud"].$separateur.$data[$i]["id_type_traduction"].$separateur.$data[$i]["texte_source"]]=$data[$i]["texte_tt"];
	}
	$data = $db->getrows("SELECT nom_module, nom_noeud, id_type_traduction, id_type_langue, texte_source, texte_traduit
			FROM app_traduction
			WHERE texte_traduit !=  ''
			AND id_type_langue =20
			AND id_type_traduction <6
		 ");

	for ($i = 0; $i <= count($data); $i++)
	{
		$g_traduction_texte[$data[$i]["nom_module"].$separateur.$data[$i]["id_type_langue"].$separateur.$data[$i]["nom_noeud"].$separateur.$data[$i]["id_type_traduction"].$separateur.$data[$i]["texte_source"]]=$data[$i]["texte_traduit"];
	}
	/*
	 $time_fin=gettimeofday(false);
	$fin=$time_fin["sec"];
	*/
	//	 $nodeass = new assmetanode();
	//	 echo "durée : ".($fin-$debut);
	//	 $nodeass->p($g_traduction_tt);



	$g_sessionManager->globalVar("traduction_texte", $g_traduction_texte, true);
	$g_sessionManager->globalVar("traduction_tt", $g_traduction_tt, true);
	// GG



}
$res='<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN" "http://www.w3.org/TR/html4/frameset.dtd">';
$res.="\n<html>\n <head>\n";
$version = atkversion();
if ("\$Name$"!="\$"."Name:  $") $version.=" ($Name$)";
$res.= '  <meta name="atkversion" content="'.$version.'" />'."\n";
$urlsite = 'http://' . atkHost().'/association/';
$res.='<base href="'.$urlsite.'" />'."\n";
$res.='<meta name="Author" content="Guy Gourmellet">';
$res.='<meta name="Copyright" content="AssoCope">';
$res.= '  <meta http-equiv="Content-Type" content="text/html; charset='.atktext("charset","atk").'" />'."\n";
$res.='<meta name="google-site-verification" content="VV_BkbddP3GG-zIy6Rci-7AuqNE04qhQ3nvFuN84Gyg" />'."\n";
$res.="\n  <title>".text('app_title')."</title>\n </head>\n";

$favico = atkconfig("defaultfavico");
if ($favico!="")
{
	$res.= '  <link rel="icon" href="'.$favico.'" type="image/x-icon" />'."\n";
	$res.= '  <link rel="shortcut icon" href="'.$favico.'" type="image/x-icon" />'."\n";
}
$res.="</head>\n";
$output=$res;
atkimport("atk.menu.atkmenu");
atkimport("atk.utils.atkframeset");
if ($g_acces_restreint_o_n==0)
{
	$menu = &atkMenu::getMenu();
	$pda = browserInfo::detectPDA();
	$theme = &atkinstance('atk.ui.atktheme');

	$position = $menu->getPosition();
	$scrolling = ($menu->getScrollable()==MENU_SCROLLABLE?FRAME_SCROLL_AUTO:FRAME_SCROLL_NO);
	if(isset($ATK_VARS["atknodetype"]) && isset($ATK_VARS["atkaction"]))
	{
		$destination = "dispatch.php?atknodetype=".$ATK_VARS["atknodetype"]."&atkaction=".$ATK_VARS["atkaction"];
		if (isset($ATK_VARS["atkselector"])) $destination.="&atkselector=".$ATK_VARS["atkselector"];
		if (isset($ATK_VARS["searchstring"])) $destination.="&searchstring=".$ATK_VARS["searchstring"];
	}
	else
	{

		$session = &atkSessionManager::getSession();


		if (atkArrayNvl(atkGetUser(), "name") == "administrator")
		{
			$destination = session_url(dispatch_url("pim.pim", "adminpim"),SESSION_NEW);
			$session["contrat_accepte"]=1;
		}
		else
		{
			if (empty($date_signature_contrat) || $date_signature_contrat < $date_texte_contrat)
			{

				$destination = session_url(dispatch_url("pim.pim", "acceptecontrat"),SESSION_NEW);
				$session["contrat_accepte"]=0;


			}
			else
			{
				$destination = session_url(dispatch_url("pim.pim", "pim"),SESSION_NEW);
				$session["contrat_accepte"]=1;
			}
		}
	}
}
/* Pour l'utilisateur doit-on lancer une url automatiquement ?
 //$g_acces_restreint_o_n= $data[0]["acces_restreint_o_n"];
//$g_url_acces_restreint= $data[0]["url_acces_restreint"];
* */

/*
 echo "<br/>acces : ".$g_acces_restreint_o_n;
echo "<br/>url : ".$g_url_acces_restreint;
die();
*/

if ($g_acces_restreint_o_n==1)

{
	$indexpage = &atknew("atk.ui.atkindexpage");
	$url=$g_url_acces_restreint;
	/*$url = dispatch_url("organisme.tableaudebord", "tableau_organisme", array (
	 "id_organisme" => "366"
	));
	*/
	list($x, $url) = explode("?", $url ); // remove params from the dispatch program
	parse_str( $url, $url_array); // converts the string into an array
	$indexpage->setDefaultDestination( $url_array );
	$indexpage->generate();
}
else {

	$frame_top_height = $theme->getAttribute('frame_top_height');
	$frame_menu_width = $theme->getAttribute('frame_menu_width');
	$topframe = &new atkFrame($frame_top_height?$frame_top_height:"65", "top", "top.php", FRAME_SCROLL_NO, true,0, "ggtopframe");
	$menuframe = &new atkFrame(($position==MENU_LEFT||$position==MENU_RIGHT?($frame_menu_width?$frame_menu_width:220):$menu->getHeight()), "menu", "menu.php", $scrolling,true,0,"ggmenuframe");
//	$topframe = &new atkFrame("0", "top", "", FRAME_SCROLL_NO, true,0, "ggtopframe");
//	$menuframe = &new atkFrame("0", "menu", "", $scrolling,true,0,"ggmenuframe");
	$mainframe = &new atkFrame("*", "main", $destination, FRAME_SCROLL_AUTO, true,0,"ggmainframe");
	$noframes = '<p>Your browser doesnt support frames, but this is required to run '.atktext('app_title')."</p>\n";

	$root = &new atkRootFrameset();
	if (atkconfig("top_frame"))
	{
		$outer = &new atkFrameSet("*", FRAMESET_VERTICAL, 1, $noframes,"topframe");
		$outer->addChild($topframe);
		$root->addChild($outer);
	}
	else
	{
		$outer = &$root;
		$outer->m_noframes = $noframes;
	}

	$orientation = ($position==MENU_TOP||$position==MENU_BOTTOM?FRAMESET_VERTICAL:FRAMESET_HORIZONTAL);

	$wrapper = &new atkFrameSet("*", $orientation,1,"","leftframe");

	if($position==MENU_TOP||$position==MENU_LEFT)
	{
		$wrapper->addChild($menuframe);
		$wrapper->addChild($mainframe);
	}
	else
	{    $wrapper->addChild($menuframe);
	$wrapper->addChild($mainframe);

	}

	$outer->addChild($wrapper);

	$output.= $root->render();
	$output.= "</html>";
	echo $output;
}
?>
