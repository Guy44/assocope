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
 function normalisation_chaine($chaine)
 {
 	 global $config_language;
 	 
 
 // dans la base deux types de chaîne (par langue) :
//les chaînes (petits mots) à laisser en minuscule (de, la , le , les, un, l, d ...)
//les chaînes (liaisons) qui sont des séparateurs et pour lesquelles il faut une majuscule après : Marie-Odile
 $db = &atkGetDb();
    $data = $db->getrows(
	"SELECT  libelle" .
	" from type_normalisation_libelle " .
	" where type_normalisation='min'") ;
	$petitsmots=array();
	 if (count($data) != 0)
{ for ($i=0; $i<count($data); $i++)
    	{    	$petitsmots[$i]=$data[$i]["libelle"];    }
}
 $data = $db->getrows(
	"SELECT  libelle" .
	" from type_normalisation_libelle " .
	" where type_normalisation='sep'") ;
$separateurs=array();
	 if (count($data) != 0)
{
for ($i=0; $i<count($data); $i++)
    	{
    	$separateurs[$i]=$data[$i]["libelle"];
    }
}
$separateurs[$i+1]=' ';
$token='';
$chaine=trim($chaine);
$chaine=strtolower($chaine);
$chaine_normalisee='';
$splitstring=str_split($chaine);
$premierpassage=true;
for ($i=0; $i<strlen($chaine); $i++)
  {
 $token.=$splitstring[$i];
 if (in_array($splitstring[$i],$separateurs)or $i==strlen($chaine)-1)
 { 	
 	$separateur=$splitstring[$i];
 	$token=substr($token,0,strlen($token)-1);
 	if (in_array($token,$petitsmots))
 	{
 	}
 	else
 	{
 		$token=ucfirst($token);
 	}
 	$chaine_normalisee.=$token;
 	$chaine_normalisee.=$separateur;
 	$token='';
 }}
  $chaine_normalisee=trim($chaine_normalisee);
  $chaine_normalisee=ucfirst($chaine_normalisee);
 return  $chaine_normalisee;
  
 }
 function normalisation_libelle($chaine)
 {
 $chaine=trim($chaine);
$chaine=strtolower($chaine);
$chaine_normalisee=ucfirst($chaine);	
 return  $chaine_normalisee;
 	
 }
  function normalisation_telephone($chaine)
 {
 $chaine=trim($chaine);
$chaine=str_replace(" ","",$chaine);
if (empty($chaine)) return "";
$chaine_normalisee="";
for ($i=0;$i>strlen($chaine); $i=$i+2)
{
$chaine_normalisee=' '.substr($chaine, strlen($chaine) -$i -2, 2).$chaine_normalisee;	
print_r ($chaine_normalisee);}
 return  $chaine_normalisee;
 	
 }

?>
