<?php
function fairetooltip($titre,$duree_o_n='n', $duree=null)
{
	global $g_sessionManager;
	if ($titre=="") return false;
	$g_tooltip_menu_o_n = $g_sessionManager->getValue("tooltip_menu_o_n", "globals");
	if ($g_tooltip_menu_o_n=='0') return "";
	$g_sticky_tooltip_o_n = $g_sessionManager->getValue("sticky_tooltip_o_n", "globals");
	$g_tooltip_color = $g_sessionManager->getValue("tooltip_color", "globals");
	if (!empty($duree) && $duree<8)
	{ $complement='<br /><b>Mise à jour il y a moins d\'une semaine.</b>';}
	else if (!empty($duree) && $duree<32)
	{$complement='<br /><b>Mise à jour dans le mois écoulé.</b>';}
	else if (!empty($duree) && $duree>31)
	{$complement='<br /><b>Existante et mise à jour il y a plus d\'un mois.</b>';}
	else 
	{$complement='<br /><b>Inexistante : créer ?.</b>';}
	($duree_o_n=='o') ? $ttip=atktext($titre).$complement : $ttip=atktext($titre);
	$ttip=str_replace("'","\'",$ttip);
	$ttip=str_replace("<br />","<br />",$ttip);
//	$ttip=htmlentities($ttip,ENT_QUOTES);
	if ($g_sticky_tooltip_o_n=='1')
	{$sticky="true";}
	else
	{$sticky="false";}
	$menutip=' onmouseover="Tip(\''.$ttip.'\',WIDTH,-300,CLICKSTICKY,'.$sticky.', CLICKCLOSE,'.$sticky.',SHADOW, true, SHADOWWIDTH, 3,BGCOLOR,'.$g_tooltip_color.')" onmouseout="UnTip()" ';
	return $menutip;

}
?>
