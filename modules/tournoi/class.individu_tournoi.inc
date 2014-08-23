<?php
atkimport("atk.assmetanode");

class individu_tournoi extends assMetaNode
{
	var $table="individu_tournoi";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function individu_tournoi()
	{
		$this->atkMetaNode();
		$this->atkNode("individu_tournoi", NF_ADDAFTERADD | NF_ADD_LINK|NF_TRACK_CHANGES | NF_MRA| NF_COMPACT_NULL);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_individu",
				"id_tournoi",
				"date_inscription",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Descripteurs" => array (
				"descripteur_tournoi"
			)
		), AF_NO_LABEL));
		$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE | AF_PRIMARY |AF_COMPACT ),10 );
		$this->add(new atkManyToOneRelation("id_tournoi","tournoi.tournoi",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE | AF_PRIMARY ),20010);
		$this->add(new atkDateAttribute("date_inscription","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),20020);
$this->add(new atkDummyAttribute("descripteur_tournoi",0,AF_COMPACT),NULL,20);
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,25);

		$this->setSecurityAlias("individu.individu");
		$this->setOrder("id_individu.nom, id_individu.prenom");

	}
	function descriptor_def()
	{
		return "[id_individu.nom] [id_individu.prenom] - [id_tournoi.libelle]";
	}
	function descripteur_tournoi_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_tournoi($record["id_tournoi"]["id"]),50);
	}

	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n','o',50,'tournoi','o','o') : $retour="";
		return $retour;
	}
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);
		
		$mraactions['delete'] = "delete";
		//		$mraactions['participation'] = "participation";
		
	
	}
	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();
	
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_tournoi
					where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}
	
		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	
}
?>