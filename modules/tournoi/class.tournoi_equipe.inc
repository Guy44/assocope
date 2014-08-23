<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");

class tournoi_equipe extends assMetaNode
{
	var $table="tournoi_equipe";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi_equipe()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi_equipe", NF_NO_ADD | NF_NO_DELETE | NF_COMPACT_NULL);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_tournoi",
				"numero_d_equipe",
				"nom_d_equipe",
				"jour_rattrapage_o_n",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
			,
			"Matchs" => array (
			"nombre_de_matchs",
			"matches"
			),
			"Joueurs" => array (
			"joueurs"
			),
			"Descripteurs" => array (
			"descripteur_equipe"
			)
			
		), AF_NO_LABEL));
		
		$this->add(new atkDummyAttribute("descripteur_equipe",0,AF_COMPACT),NULL,10);
		$this->add(new atkManyToOneRelation("id_tournoi","tournoi.tournoi",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE | AF_PRIMARY | AF_COMPACT ),15);
		$this->add(new atkNumberAttribute('numero_d_equipe',null,2,0),10105);
		$this->add(new atgTextLibelleAttribute("nom_d_equipe", AF_SEARCHABLE | AF_UNIQUE),10310);
		$this->add(new atkBoolAttribute("jour_rattrapage_o_n"),10320);
		$this->add(new atkDummyAttribute("nombre_de_matchs"),NULL,10120);
		$this->add(new atkOneToManyRelation("matches", "tournoi.tournoi_rencontre_equipe", "id_tournoi_equipe",AF_HIDE_LIST),10130);
		$this->add(new atkOneToManyRelation("joueurs", "tournoi.tournoi_equipe_participant", "id_tournoi_equipe",AF_HIDE_LIST),10140);
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,20);
		$this->setSecurityAlias("individu.individu");
		$this->setOrder("numero_d_equipe");

	}
	function descriptor_def()
	{
		return "[id_tournoi.libelle] ([numero_d_equipe])";
	}
	function descripteur_equipe_display($record, $mode) {
					return $this->descripteur_tournoi_equipe($record['id'],'o');
	}
	function id_tournoi_display($record, $mode) {
					return $this->descripteur_tournoi($record['id_tournoi']["id"],'o');
	}

	function nombre_de_matchs_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select count(id)  as nombre from tournoi_rencontre_equipe
	 where  id_tournoi_equipe = ".$record['id']." ";
		$row = $db->getrows($sql);
		$actifs=	$row[0]["nombre"];

		$ret= href(dispatch_url("tournoi.tournoi_rencontre_equipe", "admin", array (
				'atkfilter' => "tournoi_rencontre_equipe.id_tournoi_equipe='" . $record['id'] . "'"
				), "dispatch.php"), text($actifs), SESSION_NESTED);
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