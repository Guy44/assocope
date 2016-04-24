<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * This file is the skeleton menu loader, which you can copy to your
 * application dir and modify if necessary. By default, it checks
 * the menu settings and loads the proper menu.
 *
 * @package atk
 * @subpackage skel
 *
 * @author Ivo Jansch <ivo@achievo.org>
 * @author Peter C. Verhage <peter@ibuildings.nl>
 *
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 5.7 $
 * $Id: menu.php,v 5.7 2005/09/22 17:39:08 sandy Exp $
 */

/**
 * @internal includes
 */
$time_debut=gettimeofday(true);


$config_atkroot = "./";
include_once("atk.inc");

atksession();

$session = &atkSessionManager::getSession();

// print_r ($session["contrat_accepte"]);
// die();
if ($session["contrat_accepte"]==0)
{die();}
global $g_compteur_appels_mysql_query;
$g_compteur_appels_mysql_query = 0;
global $html_page_output_size;
$html_page_output_size = 0;
global $g_trace_mysql_query;
$g_trace_mysql_query="";
global $g_trace_atklanguage;
$g_trace_atklanguage= "";
	

atksecure();

$output = &atkOutput::getInstance();

/*
 * Traitement menu assocope
 */
$user = getUser();
$id = $user["id"];
$db = & atkGetDb();

// Pour ne pas être obligé de relancer app
$data = $db->getrows("SELECT google_map_key, ubio_keycode, tracer_mysqldb_query_o_n, en_travaux_o_n, debug_o_n from app_globales");
	global $g_sessionManager;
	$g_sessionManager->globalVar("tracer_mysqldb_query_o_n", $data[0]["tracer_mysqldb_query_o_n"], true);
	$g_sessionManager->globalVar("debug_o_n", $data[0]["debug_o_n"], true);

	
$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
$id_individu = $data[0]["id_individu"];
$selectedsearchstring_2=atkArrayNvl($_REQUEST, "searchstring_2");
$selectedindividu = atkArrayNvl($_REQUEST, "selectedindividu");
//print_r ($_REQUEST);
//die ();
if ($selectedindividu>='0') {
	if (!empty($selectedsearchstring_2))
	{
		$db->query("insert into app_recent_use
set id_individu=$id_individu, type_entite='individu', id_entite=$selectedsearchstring_2, date_recent_use=UTC_TIMESTAMP(), compteur=1
				ON DUPLICATE KEY UPDATE date_recent_use=UTC_TIMESTAMP(),compteur=compteur+1 "  ); 
	}
	else
	{	$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where type_entite='individu'
			and id_individu=$id_individu and id_entite=$selectedindividu"); 
	}
}
$selectedorganisme = atkArrayNvl($_REQUEST, "selectedorganisme");
//echo $selectedorganisme."<br/>";
//echo $selectedsearchstring_2."<br/>";
//die ();

if ($selectedorganisme>='0') {
	if (!empty($selectedsearchstring_2))
	{
		$db->query("insert into app_recent_use
set id_individu=$id_individu, type_entite='organisme', id_entite=$selectedsearchstring_2, date_recent_use=UTC_TIMESTAMP(), compteur=1
				ON DUPLICATE KEY UPDATE date_recent_use=UTC_TIMESTAMP(),compteur=compteur+1 "  ); 
	}
	else
	{
		$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where type_entite='organisme'
			and id_individu=$id_individu and id_entite=$selectedorganisme"); 
	}
}
$selectedcompte = atkArrayNvl($_REQUEST, "selectedcompte");
if ($selectedcompte>='0') {
	$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where type_entite='compte'
			and id_individu=$id_individu and id_entite=$selectedcompte"); 
}
$selectedrencontre = atkArrayNvl($_REQUEST, "selectedrencontre");
if ($selectedrencontre>='0') {
	$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where type_entite='rencontre'
			and id_individu=$id_individu and id_entite=$selectedrencontre"); 
}

$selectedtaxon = atkArrayNvl($_REQUEST, "selectedtaxon");
if ($selectedtaxon>='0' ) {

	if (!empty($selectedsearchstring_2))
	{
		$db->query("insert into app_recent_use
set id_individu=$id_individu, type_entite='taxon', id_entite=$selectedsearchstring_2, date_recent_use=UTC_TIMESTAMP(), compteur=1
				ON DUPLICATE KEY UPDATE date_recent_use=UTC_TIMESTAMP(),compteur=compteur+1 "  ); 
	}
	else
	{	$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where type_entite='taxon'
			and id_individu=$id_individu and id_entite=$selectedtaxon"); 
	}
}

/* load menu layout */
// GG
global $ATK_VARS,$g_menu, $g_menu_parent;
$atkmenutop = atkArrayNvl($ATK_VARS, "atkmenutop", "main");
// GG


atkimport("atk.menu.atkmenu");
$menu = &atkMenu::getMenu($atkmenutop);
$frameshow='<script language="JavaScript" type="text/javascript">
    var lfr = window.top.document.getElementById("leftframe");
lfr.cols ="220, *";

';
/*
 *
		window.top.document.getElementById("blocio").innerHTML="";

 */
$time_fin=gettimeofday(true);

$frameshow.='</script>';
if (is_object($menu)) $output->output($menu->render().$frameshow);
else atkerror("no menu object created!");

//		$output->output(" <script type='text/javascript' src='./modules/development/javascript/wz_tooltip.js'></script>
//        <script type='text/javascript' src='./modules/development/javascript/tip_balloon.js'></script> ");
//GG
global $g_sessionManager;
$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
$stats_page_o_n = $g_sessionManager->getValue("stats_page_o_n", "globals");
if ($stats_page_o_n=='1')
{
$stats="(request/output/sql/page) : <br/>      ".(substr(($time_fin-$time_debut), 0,5))." | ".(substr((gettimeofday(true)-$time_debut),0,5))." | ".$g_compteur_appels_mysql_query." | ".$html_page_output_size."<br/>";
//$stats.="<br/>".print_r($GLOBALS);
$output->output($stats);
$output->output($g_trace_atklanguage);
}
//GG
$output->outputFlush();

$time_fin_elapsed=gettimeofday(true);

$dispatch_ms_time=$time_fin-$time_debut;
$dispatch_ms_elapsed_time=$time_fin_elapsed-$time_debut;
$html_page_output_ms_time=$time_fin_elapsed-$time_fin;

// GG LOg
$node =$atkmenutop;

$origine='menu.php';
$action="dispatch_menu";
atk_log_event($origine, $node, $action, null, null, null, null,$dispatch_ms_time,$dispatch_ms_elapsed_time, $g_compteur_appels_mysql_query,$html_page_output_ms_time,$html_page_output_size);


?>