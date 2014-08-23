<?php
atkimport("atk.assmetanode");

class tournoi_rencontre_equipe extends assMetaNode
{
	var $table="tournoi_rencontre_equipe";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi_rencontre_equipe()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi_rencontre_equipe", NF_ADDAFTERADD | NF_ADD_LINK);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_tournoi_match",
				"id_tournoi_equipe",
				"numero_de_rencontre_equipes",
				"score",
				"remarque",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Descripteurs" => array (
			"descripteur_equipe",
			"descripteur_match",
			"descripteur_rencontre",
			"descripteur_tournoi",
				
			)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_equipe"),NULL,20);
		$this->add(new atkDummyAttribute("descripteur_match"),NULL,21);
		$this->add(new atkDummyAttribute("descripteur_tournoi"),NULL,25);
		$this->add(new atkDummyAttribute("descripteur_rencontre"),NULL,23);
		
		$this->add(new atkManyToOneRelation("id_tournoi_match","tournoi.tournoi_rencontre_match",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE ),12010);
		$this->add(new atkManyToOneRelation("id_tournoi_equipe","tournoi.tournoi_equipe",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE  ),12020);
		$this->add(new atkAttribute('numero_de_rencontre_equipes',null),12030);
		$this->add(new atkAttribute('remarque',null,500),12031);
//		$this->add(new atkDateAttribute("date_rencontre_effective","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),12040);
		$this->add(new atkNumberAttribute('score',null,2,0),12050);

		include_once(atkconfig("atkroot")."modules/include/association.inc");

		$this->setSecurityAlias("individu.individu");
		//$this->setOrder("numero_de_equipe");

	}
			function descriptor_def()
	 {
		return "[id_tournoi_match.numero_de_rencontre_equipes]";
		}
	function descripteur_rencontre_display($record, $mode) {
			$db = & atkGetDb();
		$sql="select trm.id_tournoi_rencontre  from  tournoi_rencontre_match trm
	 where  trm.id = ".$record['id_tournoi_match']["id"]." ";
		$row = $db->getrows($sql);
		return $this->descripteur_tournoi_rencontre($row[0]["id_tournoi_rencontre"],'o');
	}
	function descripteur_tournoi_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select tr.id_tournoi  from tournoi_rencontre tr, tournoi_rencontre_match trm
	 where  trm.id_tournoi_rencontre=tr.id and trm.id = ".$record['id_tournoi_match']["id"]." ";
		$row = $db->getrows($sql);
		return $this->descripteur_tournoi($row[0]["id_tournoi"],'o');
	}

	function descripteur_match_display($record, $mode) {
		return $this->descripteur_tournoi_rencontre_match($record["id_tournoi_match"]["id"],'o');

	}
function descripteur_equipe_display($record, $mode) {
		return $this->descripteur_tournoi_rencontre_equipe($record["id"],'o');

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