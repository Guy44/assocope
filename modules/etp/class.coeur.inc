<?php
atkimport("atk.assmetanode");

class coeur extends assMetaNode
{
	var $table="etp_coeur";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function coeur()
	{
		$this->atkMetaNode();
		$this->atkNode("coeur", NF_ADD_LINK |NF_ADDAFTERADD);



		$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),140);
		$this->add(new atkDateAttribute("date_mesure", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY),150);
		$this->add(new atkTimeAttribute("heure_mesure",0,23,1,"",   AF_OBLIGATORY),151);
		$this->add(new atkRadioAttribute('bras',array('Gauche','Droit'), array('Gauche','Droit'),AF_DISPLAY_HOR|AF_NO_TRANSLATION|AF_OBLIGATORY),152);
		$this->add(new atkDummyAttribute("objectif_systole",0),158);
		$this->add(new atkNumberAttribute("diastole_mm_hg",AF_SEARCHABLE|AF_OBLIGATORY, 3, 0),161);
		$this->add(new atkNumberAttribute("systole_mm_hg",AF_SEARCHABLE|AF_OBLIGATORY, 3, 0),160);
		$this->add(new atkDummyAttribute("objectif_pulses",0),163);
		$this->add(new atkNumberAttribute("pulses_per_minute",AF_SEARCHABLE|AF_OBLIGATORY, 3, 0),164);
			

		include_once(atkconfig("atkroot")."modules/include/association.inc");

		$this->setSecurityAlias("individu.individu");
		$this->setOrder("date_mesure DESC , heure_mesure asc");

	}

	function systole_mm_hg_display($record, $mode) {

		$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_systole_mm_hg
 		FROM individu where id='".$record["id_individu"]["id"]."'");
		$diastole = $rang[0]["etp_systole_mm_hg"];
		if ($diastole>$record["systole_mm_hg"])
		{
			return '<p style="text-align: right;"><b><font color="ForestGreen"><b>'.$record["systole_mm_hg"].'</font></b></p>';
		}
		else
		return '<p style="text-align: right;"><b><font color="Red"><b>'.$record["systole_mm_hg"].'</font></b></p>';

	}
function diastole_mm_hg_display($record, $mode) {

		if ($record["diastole_mm_hg"]<90)
		{
			return '<p style="text-align: right;"><b><font color="ForestGreen"><b>'.$record["diastole_mm_hg"].'</font></b></p>';
		}
		else
		return '<p style="text-align: right;"><b><font color="Red"><b>'.$record["diastole_mm_hg"].'</font></b></p>';

	}
	


	function pulses_per_minute_display($record, $mode) {

		$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_pulses_per_minute
 		FROM individu where id='".$record["id_individu"]["id"]."'");
		$pulses = $rang[0]["etp_pulses_per_minute"];
		if ($pulses>$record["pulses_per_minute"])
		{
			return '<p style="text-align: right;"><b><font color="ForestGreen"><b>'.$record["pulses_per_minute"].'</font></b></p>';
		}
		else
		return '<p style="text-align: right;"><b><font color="Red"><b>'.$record["pulses_per_minute"].'</font></b></p>';

	}
	function objectif_systole_display($record, $mode) {
		$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_systole_mm_hg
 		FROM individu where id='".$record["id_individu"]["id"]."'");
		$diastole = $rang[0]["etp_systole_mm_hg"];
		return '<p style="text-align: right;">'.$diastole.'</p>';

	}
	function objectif_pulses_display($record, $mode) {

		$db = & atkGetDb();
		$rang = $db->getrows("SELECT etp_pulses_per_minute
 		FROM individu where id='".$record["id_individu"]["id"]."'");
		$pulses = $rang[0]["etp_pulses_per_minute"];
		return '<p style="text-align: right;">'.$pulses.'</p>';

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