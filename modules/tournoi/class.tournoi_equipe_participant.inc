<?php
atkimport("atk.assmetanode");

class tournoi_equipe_participant extends assMetaNode
{
	var $table="tournoi_equipe_participant";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi_equipe_participant()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi_equipe_participant", NF_ADDAFTERADD | NF_ADD_LINK);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id_tournoi_equipe",
				"id_individu_tournoi",
				"index",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
				$this->add(new atkAttribute("id_tournoi_equipe",null),10);
		
		$this->add(new atkManyToOneRelation("id_individu_tournoi","tournoi.individu_tournoi",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK ),20);
		$this->add(new atkNumberAttribute('index',null,2,2),60);
		include_once(atkconfig("atkroot")."modules/include/association.inc");

		$this->setSecurityAlias("individu.individu");
		//$this->setOrder("numero_de_equipe");

	}
			function descriptor_def()
	 {
		return "[id_individu_tournoi.id]";
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
/*	function preAdd(& $record) {
		
		$db = & atkGetDb();
		$id_individu_tournoi=$record["id_individu_tournoi"]["id"];
		$requete = "SELECT i.golf_index as index1 from
		individu i, individu_tournoi it
		 where it.id_individu= i.id and 
		it.id=$id_individu_tournoi";
		$data = $db->getrows($requete);
		$record["index"]=$data[0]["index1"];
	//	$this->p($record);
	//	parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$db = & atkGetDb();
		$id_individu_tournoi=$record["id_individu_tournoi"]["id"];
		$requete = "SELECT i.golf_index as index from
		individu i, individu_tournoi it
		 where 
		it.id=$id_individu_tournoi";
		$data = $db->getrows($requete);
		$record["index"]=$data[0]["index"];;
		parent :: preUpdate($record);
	}
*/


}
?>