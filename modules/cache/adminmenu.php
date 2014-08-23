<?php
$xoops_admin_menu_js = "function popUpL1() {
shutdown();
popUp(\"L1\",true);
}
";
$xoops_admin_menu_ml[1] = "setleft('L1',105);
settop('L1',150);
";
$xoops_admin_menu_sd[1] = "popUp('L1',false);
";
$xoops_admin_menu_ft[1] = "<a href='".XOOPS_URL."/modules/system/admin.php' onmouseover='moveLayerY(\"L1\", currentY,event) ; popUpL1();'><img src='".XOOPS_URL."/modules/system/images/system_slogo.png' alt='' /></a><br />
";
$xoops_admin_menu_dv = "<div id='L1' style='position: absolute; visibility: hidden; z-index:1000;'><table class='outer' width='150' cellspacing='1'><tr><th nowrap='nowrap'>Syst&egrave;me</th></tr><tr><td class='even' nowrap='nowrap'><img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=banners' onmouseover='popUpL1();'>Banni&egrave;res</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=blocksadmin' onmouseover='popUpL1();'>Blocs</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=groups' onmouseover='popUpL1();'>Groupes</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=images' onmouseover='popUpL1();'>Images</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=modulesadmin' onmouseover='popUpL1();'>Modules</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=preferences' onmouseover='popUpL1();'>Pr&eacute;f&eacute;rences</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=smilies' onmouseover='popUpL1();'>Emotic&ocirc;nes</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=userrank' onmouseover='popUpL1();'>Classement des utilisateurs</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=users' onmouseover='popUpL1();'>Editer des utilisateurs</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=findusers' onmouseover='popUpL1();'>Trouver des utilisateurs</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=mailusers' onmouseover='popUpL1();'>Envoyer un mail aux utilisateurs</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=avatars' onmouseover='popUpL1();'>Avatars</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=tplsets' onmouseover='popUpL1();'>Templates</a><br />
<img src='".XOOPS_URL."/images/pointer.gif' width='8' height='8' alt='' />&nbsp;<a href='".XOOPS_URL."/modules/system/admin.php?fct=comments' onmouseover='popUpL1();'>Commentaires</a><br />
<div style='margin-top: 5px; font-size: smaller; text-align: right;'><a href='#' onmouseover='shutdown();'>[Fermer]</a></div></td></tr><tr><th style='font-size: smaller; text-align: left;'><img src='".XOOPS_URL."/modules/system/images/system_slogo.png' alt='' /><br /><b>"._VERSION.":</b> 1<br /><b>"._DESCRIPTION.":</b> Pour l'administration des param&egrave;tres du coeur du site.</th></tr></table></div>
<script language='JavaScript'>
<!--
moveLayers();
loaded = 1;
// -->
</script>
";

?>