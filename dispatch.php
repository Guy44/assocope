<?php

/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * This file is the skeleton dispatcher file, which you can copy
 * to your application dir and modify if necessary. By default, it
 * checks the $atknodetype and $atkaction postvars and creates the
 * node and dispatches the action.
 *
 * @package atk
 * @subpackage skel
 *
 * @author Ivo Jansch <ivo@achievo.org>
 *
 * @copyright (c)2000-2004 Ivo Jansch
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 6083 $
 * @GG
 * Statistiques du node (taille, temps ...)
 * 
 * $Id: dispatch.php 6083 2008-08-05 19:59:45Z maurice $
 */

/**
 * @internal Setup the system
 */
$config_atkroot = "./";
include_once("atk.inc");
atkdebug("avant atksession (dispatch.php)");
atksession();

$session = &atkSessionManager::getSession();
$output = &atkOutput::getInstance();
// GG
$time_debut=gettimeofday(true);
global $g_compteur_appels_mysql_query;
$g_compteur_appels_mysql_query = 0;
global $html_page_output_size;
$html_page_output_size = 0;
global $g_trace_mysql_query;
$g_trace_mysql_query="";
global $g_trace_atklanguage;
$g_trace_atklanguage= "";

// Pour ne pas être obligé de relancer app
$db = & atkGetDb();
$data = $db->getrows("SELECT google_map_key, ubio_keycode, tracer_mysqldb_query_o_n, en_travaux_o_n, debug_o_n from app_globales");
	global $g_sessionManager;
	$g_sessionManager->globalVar("tracer_mysqldb_query_o_n", $data[0]["tracer_mysqldb_query_o_n"], true);
	$g_sessionManager->globalVar("debug_o_n", $data[0]["debug_o_n"], true);


if($ATK_VARS["atknodetype"]=="" && $session["login"]==1)
{
	echo "Action terminée";
	die();
}
// GG FIN
if($ATK_VARS["atknodetype"]=="" || $session["login"]!=1)
{
	// no nodetype passed, or session expired

	$page = &atknew("atk.ui.atkpage");
	$ui = &atkinstance("atk.ui.atkui");
	$theme = &atkTheme::getInstance();


	$page->register_style($theme->stylePath("style.css"));

	$destination = "index.php?atklogout=true";
	if(isset($ATK_VARS["atknodetype"]) && isset($ATK_VARS["atkaction"]))
	{
		$destination .= "&atknodetype=".$ATK_VARS["atknodetype"]."&atkaction=".$ATK_VARS["atkaction"];
		if (isset($ATK_VARS["atkselector"])) $destination.="&atkselector=".$ATK_VARS["atkselector"];
	}

	$title = atktext("title_session_expired");
	$contenttpl = '<br>%s<br><br><input type="button" onclick="top.location=\'%s\';" value="%s"><br><br>';
	$content = sprintf($contenttpl, atktext("explain_session_expired"), str_replace("'", "\\'", $destination), atktext("relogin"));
	$box = $ui->renderBox(array("title" => $title, "content" => $content));

	$page->addContent($box);
	$output->output($page->render(atktext("title_session_expired"), true));
}
else
{
	atksecure();
	atkimport("atk.ui.atkpage");

	$lockType = atkconfig("lock_type");
	if (!empty($lockType)) atklock();

	$flags = array_key_exists("atkpartial", $ATK_VARS) ? HTML_PARTIAL : HTML_STRICT;

	//Load controller
	if ($ATK_VARS["atkcontroller"]=="")
	$controller = &atkinstance("atk.atkcontroller");
	else
	$controller = &atkinstance($ATK_VARS["atkcontroller"]);

	//Handle http request
	//   $value = atk_iconv("UTF-8",atktext("charset"),$field['html']);


	$controller->dispatch($ATK_VARS, $flags);


}


global $g_sessionManager;
$user = getUser();
if($user["id"]=='0')
{$output->output("ATK_VARS : ".p($ATK_VARS));
$output->output('$_GET : '.p($_GET));
$output->output('$_POST : '.p($_POST));
$output->output('$_REQUEST : '.p($_REQUEST));}
//$output->output(" <script type='text/javascript' src='./modules/development/javascript/wz_tooltip.js'></script>
//        <script type='text/javascript' src='./modules/development/javascript/tip_balloon.js'></script> ");
$time_fin=gettimeofday(true);
//GG
global $g_sessionManager;
$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
$stats_page_o_n = $g_sessionManager->getValue("stats_page_o_n", "globals");
if ($stats_page_o_n=='1')
{
$stats="(request/output/sql/page) : ".(substr(($time_fin-$time_debut), 0,5))." | ".(substr((gettimeofday(true)-$time_debut),0,5))." | ".$g_compteur_appels_mysql_query." | ".$html_page_output_size."<br/>";
$output->output($stats);
$output->output($g_trace_atklanguage);
}
//GG
$output->outputFlush();

$time_fin_elapsed=gettimeofday(true);
$dispatch_ms_time=$time_fin-$time_debut;
$dispatch_ms_elapsed_time=$time_fin_elapsed-$time_debut;
$html_page_output_ms_time=$time_fin_elapsed-$time_fin;
$origine='dispatch.php';
$node = $ATK_VARS["atknodetype"];
//$action="dispatch_node";
//$selector=$ATK_VARS["atkselector"];

$action=$ATK_VARS["atkaction"];

$parametres=escapeSQL(print_r($ATK_VARS,true));
$selector=escapeSQL($ATK_VARS["atkselector"]);
// $g_trace_mysql_query=escapeSQL($g_trace_mysql_query);
// activer trace en décommentant dans atkmysqldb.inc
atk_log_event($origine, $node, $action, $parametres, $selector, null, null,$dispatch_ms_time,$dispatch_ms_elapsed_time,$g_compteur_appels_mysql_query,$html_page_output_ms_time,$html_page_output_size);




function p($a, $btag = "", $etag = "") {
	if (is_array($a)) {
		$out=sprintf("<table cellpadding=0 cellspacing=0 border='1'> ");
		while (list ($one, $two) = each($a)) {
			/*        printf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
			 "&nbsp;$btag=>$etag</td>".
			 "<td align=right>&nbsp;%s</td></tr>\n"
			 ,$this->sprint_array($two,$btag,$etag));
			 */
			$out.=sprintf("\n<tr valign=baseline><td>$btag$one$etag</td>" . "<td align=right>&nbsp;%s</td></tr>\n", sprint_array($two, $btag, $etag));
		}
		$out.=sprintf("</table>");
	} else {
		$out.=sprintf("%s%s%s", $btag, $a, $etag);
	}
	return $out;
}
function sprint_array($a, $btag = "", $etag = "") {
	if (is_array($a)) {
		$out = sprintf("<table cellpadding=0 cellspacing=0 border='1'>");
		while (list ($one, $two) = each($a)) {
			/*       $out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
			 "&nbsp;$btag=>$etag</td>".
			 "<td align=right>&nbsp;%s</td></tr>\n"
			 ,$this->sprint_array($two,$btag,$etag));
			 */
			$out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td>" . "<td align=right>&nbsp;%s</td></tr>\n", sprint_array($two, $btag, $etag));
		}
		$out .= "</table>";
			
	} else {
		$out=sprintf("%s%s%s", $btag, $a, $etag);
	}
	return $out;
}
?>
