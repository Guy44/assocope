<?php

/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage ui
 *
 * @copyright (c)2000-2004 Ivo Jansch
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 1684 $
 * $Id: function.stacktrace.php 1684 2004-05-31 22:11:12Z ivo $
 */

/**
 * Implements the {stacktrace} plugin for use in templates.
 *
 * The {stacktrace} tag does not output anything. Instead, it loads
 * a stacktrace into the template variables {$stacktrace}, which is
 * an array of elements, each with a 'title' and 'url' field.
 *
 * <b>Example:</b>
 * <code>
 *   {stacktrace}
 *
 *   {foreach from=$stacktrace item=item}
 *     <a href="{$item.url}">{$item.title}</a>
 *   {/foreach}
 * </code>
 *
 * @author Ivo Jansch <ivo@achievo.org>
 *
 */

function smarty_function_piedpage($params, &$smarty)
{
	$nodetype=$_GET["atknodetype"];
	list ($module, $node) = explode(".", $nodetype);

	//	$texte=atktext("wiki_".$node, $module, $node);
	$texte="Module ".$module.'.'.$node;
	$texte=str_replace(' ', '_', $texte);
	$an=gmdate('Y');
	$menutip1=fairetooltip("menu_tooltip_topmenu_Copyright");

	$menutip3=fairetooltip("menu_tooltip_topmenu_Confidentialite");
	$menutip4=fairetooltip("menu_tooltip_topmenu_Atkpowered");

	$menutip6=fairetooltip("menu_tooltip_topmenu_Source");
	$menutip7=fairetooltip("menu_tooltip_topmenu_Explicationnoeud");
	$menutip8=fairetooltip("menu_tooltip_topmenu_Traductionnoeud");
	$footer.=" <div class='piedpage'>
	<a ".$menutip1."class='piedpage' href='http://www.wikistoma.org/wiki/index.php?title=Accueil' target='_blank'>© 2006-".$an." AssoCope</a>";
	if ($module!="" and $node!="")
	{
		$footer.="	&nbsp;|&nbsp;
	". href(dispatch_url("lesson_utils.sourceviewer", "view", array (
		"module" => $module,
		"node" => $node
		)), text('view_source'), SESSION_NEW, false, 'target="_blank" '. $menutip6 .' class="piedpage" ' ) . "
	&nbsp;|&nbsp;
		". href(dispatch_url("application.traduction", "admin", array (
		//	"atkfilter" => "app_traduction.nom_module='" . $module . "' and app_traduction.nom_noeud='". $node . "' "
				"atkfilter" => "app_traduction.nom_module='" . $module . "' and app_traduction.nom_noeud='". $node . "' "
				)), text('traduire_entité'), SESSION_NESTED, false, 'target="_self" '. $menutip8 .' class="piedpage" ' ) . "";
	}
	$duree=GetWikiPageAge($texte);
	if (empty($duree))
	{$aide='Aide';}
	else if ($duree<8)
	{		$aide='<span style="color:Red"><b>Aide</b></span>';	}
	else if ($duree<32)
	{		$aide='<span style="color:Orange"><b>Aide</b></span>';	}
	else
	{		$aide='<b>Aide</b>';	}
	$menutip2=fairetooltip("menu_tooltip_topmenu_Aideentite",'o',$duree);
	$href_aide=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)),    $aide,	SESSION_NEW,	false, 'class="piedpage" target="_blank"'. $menutip2);
	$faqspage='AssoCope_faqs';
	$duree=GetWikiPageAge($faqspage);
	if (empty($duree))
	{$faqs='Faqs';}
	else if ($duree<8)
	{		$faqs='<span style="color:Red"><b>Faqs</b></span>';	}
	else if ($duree<32)
	{		$faqs='<span style="color:Orange"><b>Faqs</b></span>';	}
	else
	{		$faqs='<b>Faqs</b>';	}
	$menutip5=fairetooltip("menu_tooltip_topmenu_Faqs",'o',$duree);
	$href_faqs=href(dispatch_url("search.search", "wiki",	array("title"=>"AssoCope_faqs")),    $faqs,	SESSION_NEW,	false, 'class="piedpage" target="_blank"'. $menutip5);
	$footer.="	&nbsp;|&nbsp;
	
	
	".$href_aide."
	&nbsp;|&nbsp;
	".$href_faqs."
	&nbsp;|&nbsp;
	<a  ".$menutip3."class='piedpage' href='http://www.wikistoma.org/association/dispatch.php?atknodetype=application.globales&atkaction=confidentialite&'>Règles de confidentialité</a>
	&nbsp;|&nbsp;
	<a  ".$menutip4."class='piedpage' href='http://www.achievo.org/atk' target='_blank'>Powered by Achievo Tool Kit</a>
	</div>"         ;
	$wikinode = &atkGetNode("search.search");
	global $g_sessionManager;
	$table_des_matieres_wiki_o_n= $g_sessionManager->getValue("table_des_matieres_wiki_o_n", "globals");
	if ($table_des_matieres_wiki_o_n==1)
	{$footer.=$wikinode->toc_wiki();}
	
	return $footer;

}
function GetWikiPageAge($pagename)
{
		$dbw = & atkGetDb("assocopewiki");
	$data=$dbw->getrows("select page_touched from mw_page where page_title='". $pagename ."'");
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
include_once (atkconfig("atkroot") . "modules/include/fairetooltip.inc");

?>
