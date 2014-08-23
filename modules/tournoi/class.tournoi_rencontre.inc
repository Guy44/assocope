<?php
atkimport("atk.assmetanode");

class tournoi_rencontre extends assMetaNode
{
	var $table="tournoi_rencontre";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi_rencontre()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi_rencontre", NF_NO_ADD | NF_NO_DELETE | NF_COMPACT_NULL);
//		$this->atkNode("tournoi_rencontre_match", NF_NO_ADD | NF_NO_DELETE );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_tournoi",
				"numero_de_rencontre",
				"date_rencontre",
		"date_rattrapage_rencontre",
		"date_limite_rencontre",
		"id_lieu_rencontre",
		"matchs",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
//			"Matches" => array (
//			"Matches"
//			),
			"Descripteurs" => array (
			"descripteur_rencontre"
			)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_rencontre",0,AF_COMPACT),NULL,10);
		$this->add(new atkManyToOneRelation("id_tournoi","tournoi.tournoi",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE | AF_PRIMARY | AF_COMPACT),15);
//	$this->add(new atkOneToManyRelation("Matches", "tournoi.tournoi_rencontre_match", "id_tournoi_rencontre",AF_HIDE_LIST),10161);
		$this->add(new atkDummyAttribute("matchs"),NULL,10115);

		$this->add(new atkNumberAttribute('numero_de_rencontre',AF_PRIMARY,2,0),10120);
		$this->add(new atkDateAttribute("date_rencontre","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),10130);
		$this->add(new atkDateAttribute("date_rattrapage_rencontre","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),10140);
		$this->add(new atkDateAttribute("date_limite_rencontre","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),10150);
		$this->add(new atkManyToOneRelation("id_lieu_rencontre","organisme.golf_parcours",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE ),10135);

		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,20);
		$this->setSecurityAlias("individu.individu");
		$this->setOrder("numero_de_rencontre");

	}
	function id_lieu_rencontre_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_golf_parcours($record["id_lieu_rencontre"]["id"],'o').'<br />',150);
	}
	
	function descriptor_def()
	{
		return "[id_tournoi.libelle] ([numero_rencontre])";
	}
	function descripteur_rencontre_display($record, $mode) {
					return $this->descripteur_tournoi_rencontre($record['id'],'o');
	}
	function id_tournoi_display($record, $mode) {
					return $this->descripteur_tournoi($record['id_tournoi']["id"],'o');
	}
	function matchs_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select count(id)  as nombre from tournoi_rencontre_match
	 where  id_tournoi_rencontre = ".$record['id']." ";
		$row = $db->getrows($sql);
		$matchs=	$row[0]["nombre"];

		$ret= href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
				'atkfilter' => "tournoi_rencontre_match.id_tournoi_rencontre='" . $record['id'] . "'"
				), "dispatch.php"), text($matchs), SESSION_NESTED);
				return $ret;
	}


	/*
	 function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
		}
		*/
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}


}
?>