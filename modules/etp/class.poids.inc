<?php
atkimport("atk.assmetanode");

class poids extends assMetaNode
{
	var $table="etp_poids";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function poids()
	{
		$this->atkMetaNode();
		$this->atkNode("poids", NF_ADD_LINK);



		$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),140);
		$this->add(new atkDateAttribute("date_mesure", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY),150);
		$this->add(new atkTimeAttribute("heure_mesure",0,23,1,"",   AF_OBLIGATORY),151);
		$this->add(new atkDummyAttribute("objectif_poids", 0),153);
		$this->add(new atkNumberAttribute("poids_kg",AF_SEARCHABLE|AF_OBLIGATORY, 8, 3),162);
		$this->add(new atkDummyAttribute("imc"),200);
		
			

		include_once(atkconfig("atkroot")."modules/include/association.inc");

		$this->setSecurityAlias("individu.individu");
				$this->setOrder("date_mesure DESC , heure_mesure asc");

	}
	function imc_display($record, $mode) {
		$db = & atkGetDb();
		$rang = $db->getrows("SELECT
		taille 
		FROM individu where id='".$record["id_individu"]["id"]."'");

		$taille = $rang[0]["taille"]/100;

if ($taille>0)
{
$imc=round($record["poids_kg"]/($taille*$taille),2);
if ($imc >0 )
{
	$texte="Maigreur extrême (Risque élevé)";
}
if ($imc >16)
{
	$texte="Maigreur (Risque accru)";
}
if ($imc >18.5 )
{
	$texte="Poids normal (Risque faible)";
}
if ($imc >25 )
{
	$texte="Embonpoint (Risque accru)";
	}
if ($imc >30 )
{
	$texte="Obésité classe 1 (Risque élevé)";
	}
if ($imc >35 )
{
	$texte="Obésité classe 2 (Risque très élevé)";
	}
if ($imc >40 )
{
	$texte="Obésité classe 3 (Risque extrêmement élevé)";
	}
		
 return '<p style="text-align: right;">'.$imc.' '.$texte.'</p>';}
		else
			{			return null;}
		
	}
	
	function poids_kg_display($record, $mode) {
			$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_poids_kg
 		FROM individu where id='".$record["id_individu"]["id"]."'");
			$poids = $rang[0]["etp_poids_kg"];
		if ($poids>$record["poids_kg"])
		{
			return '<p style="text-align: right;"><b><font color="ForestGreen"><b>'.$record["poids_kg"].'</font></b></p>';
		}
		else
		return '<p style="text-align: right;"><b><font color="Red"><b>'.$record["poids_kg"].'</font></b></p>';
		
	}
		
	function objectif_poids_display($record, $mode) {
				$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_poids_kg
 		FROM individu where id='".$record["id_individu"]["id"]."'");
			$poids = $rang[0]["etp_poids_kg"];
		return '<p style="text-align: right;">'.$poids.'</p>';
		
	}



	function descriptor_def()
	{
		return "[id]";
	}

	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>