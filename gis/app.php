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
$config_atkroot = "./";
include_once("atk.inc");
atksession();
atksecure();
include "theme.inc";
global $g_sessionManager ;
global $g_user;

if ($g_user["name"] != "administrator") {
	$db = & atkGetDb();
	$user = getUser();
	$id = $user["id"];

	//	print_r($_SERVER);
	//	die();
	$data = $db->getrows("SELECT p.acces_public_seulement as acces_public, p.id as profil ,p.libelle as libelle_profil, i.nom as nom,
		i.prenom as prenom, i.id as id_individu_utilisateur, p.administrateur_general_o_n as administrateur,
		 u.date_signature_contrat as date_signature_contrat, u.contexte_o_n as contexte_o_n,i.tz_offset_google  as tz_offset_google ,
		 u.tt_o_n as tooltip_menu_o_n,
		 u.sticky_tt_o_n as sticky_tooltip_o_n,
		 u.tt_couleur_bg as tooltip_color,
		 u.trace_db_o_n as trace_db_o_n
		 
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
	$g_tooltip_menu_o_n= $data[0]["tooltip_menu_o_n"];
	$g_sticky_tooltip_o_n= $data[0]["sticky_tooltip_o_n"];
		$g_tooltip_color= $data[0]["tooltip_color"];
	$g_trace_db_o_n= $data[0]["trace_db_o_n"];

	$g_nomutilisateur=$data[0]["prenom"]." ".$data[0]["nom"];
	$g_administrateur=$data[0]["administrateur"];
	$g_id_individu_utilisateur=$data[0]["id_individu_utilisateur"];
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
	$g_sessionManager->globalVar("atgAccesPublicSeul_o_n", $g_acces_public_seulement, true);
	$g_sessionManager->globalVar("atgOrganismesAutorises", $g_organismes_autorises, true);
	$g_sessionManager->globalVar("atgAdministrateur_o_n", $g_administrateur, true);
	$g_sessionManager->globalVar("contexte_o_n", $g_contexte_o_n, true);
	$g_sessionManager->globalVar("tooltip_menu_o_n", $g_tooltip_menu_o_n, true);
	$g_sessionManager->globalVar("sticky_tooltip_o_n", $g_sticky_tooltip_o_n, true);
	$g_sessionManager->globalVar("tooltip_color", $g_tooltip_color, true);
	$g_sessionManager->globalVar("tz_offset_google", $g_tz_offset_google, true);
	$g_sessionManager->globalVar("atgNomUtilisateur", $g_nomutilisateur, true);
	$g_sessionManager->globalVar("atgIdIndividuUtilisateur", $g_id_individu_utilisateur, true);
	$g_sessionManager->globalVar("atgProfilUtilisateur", $g_libelle_profil, true);
	$g_sessionManager->globalVar("atgProfilUtilisateur", $g_libelle_profil, true);
}
$output='<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Frameset//EN" "http://www.w3.org/TR/html4/frameset.dtd">';
$output.="\n<html>\n <head>\n";

$output.='  <META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset='.atktext("charset","","","","atk").'">';
//  $output.="\n  <title>".getAchievoTitle()."</title>\n </head>\n";
$output.="\n  <title>".text('app_title')."</title>\n </head>\n";
atkimport("atk.menu.atkmenu");
atkimport("atk.utils.atkframeset");

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

$frame_top_height = $theme->getAttribute('frame_top_height');
$frame_menu_width = $theme->getAttribute('frame_menu_width');
$topframe = &new atkFrame($frame_top_height?$frame_top_height:"65", "top", "top.php", FRAME_SCROLL_NO, true,0, "ggtopframe");

$menuframe = &new atkFrame(($position==MENU_LEFT||$position==MENU_RIGHT?($frame_menu_width?$frame_menu_width:220):$menu->getHeight()), "menu", "menu.php", $scrolling,true,0,"ggmenuframe");
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
?>
