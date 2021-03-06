<?php

function getThemes()
{
  $s = array();

  // First look in the themes directory
  $handle=opendir("themes");
  while ($file = readdir($handle))
    if ($file != "." && $file != ".." && $file != "CVS")  $s[]= $file;
  closedir($handle);

  // Then look in the atk backend directory
  $handle=opendir("atk/themes");
  while ($file = readdir($handle))
    if ($file != "." && $file != ".." && $file != "CVS") $s[]= $file;
  closedir($handle);

  sort($s);

  // return array with themes
  return $s;
}


class userprefs extends atkNode
{
  function userprefs()
  {
    $this->atkNode("userprefs",NF_NO_ADD|NF_NO_DELETE);
	$this->add(new atkTabbedPane("Pane1",
	array(
	"G�n�ral"=>	array("passwordexplanation","mot_de_passe","theme","commentaire",
 "id_creation","date_creation","id_modification","date_modification"),
	"Rappels"=> array("pimitems")	
	),AF_NO_LABEL));
    $this->add(new atkNumberAttribute("id", AF_PRIMARY|AF_HIDE));
    $this->add(new atkAttribute("identifiant", AF_HIDE));
    if (atkconfig("authentication")=="db")
    {
      $this->add(new atkDummyAttribute("passwordexplanation", atktext("password_leaveblankifunchanged"), AF_HIDE_ADD|AF_HIDE_LIST));
      $this->add(new atkPasswordAttribute("mot_de_passe",AF_OBLIGATORY));
    }
    $themes = getThemes();
    $this->add(new atkListAttribute("theme",$themes,$themes,AF_HIDE_ADD|AF_NO_TRANSLATION));

    $this->setTable("app_utilisateur", "app_utilisateur");
  }

  function descriptor_def()
  {
    return "[identifiant]";
  }
  

function adminFooter()
    {
      return nodeSourceUrl("profil.userprefs");
    }

  function postUpdate($record)
  {
    global $g_user, $g_sessionManager, $g_securityManager;

    if($record["id"]==$g_user["id"])
    {
      // If the theme was updated, we must change it in the session (or you won't
      // see the update.
      $g_sessionManager->globalVar("atkTheme", $record["theme"], true);

      // Also, if we edited userpreferences, then the current record
      // should be stored in the session as user record, so Achievo
      // will immediately start to use the new settings.
      $g_securityManager->reloadUser();

      // Also, we must refresh the screen.
      echo '<script language="javascript">';
      echo 'parent.location = "index.php"';
      echo '</script>';
      exit;
    }
  }
}
?>