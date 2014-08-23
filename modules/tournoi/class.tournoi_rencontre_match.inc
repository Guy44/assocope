<?php
atkimport("atk.assmetanode");

class tournoi_rencontre_match extends assMetaNode
{
	var $table="tournoi_rencontre_match";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi_rencontre_match()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi_rencontre_match", NF_NO_ADD | NF_NO_DELETE | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"numero_de_match",
				"id_lieu_match",
				"date_rencontre_effective",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Scores" => array (
				"score_tout"
				),
				"Descripteurs" => array (
			"descripteur_match",
			"descripteur_rencontre",
			"descripteur_tournoi"

			)
			), AF_NO_LABEL));
			$this->add(new atkDummyAttribute("descripteur_match",0,AF_COMPACT),NULL,21);
			$this->add(new atkDummyAttribute("descripteur_tournoi",0,AF_COMPACT),NULL,25);
			$this->add(new atkDummyAttribute("descripteur_rencontre",0,AF_COMPACT),NULL,23);
			//	$this->add(new atkManyToOneRelation("id_tournoi_rencontre","tournoi.tournoi_rencontre",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE ),10);
			$this->add(new atkAttribute('numero_de_match',null),10120);
			//		$this->add(new atkOneToManyRelation("Equipes", "tournoi.tournoi_rencontre_equipe", "id_tournoi_match",AF_HIDE_LIST),10171);
			$this->add(new atgNoStorageAttribute("score_tout",AF_COMPACT,0),NULL,22);
			$this->add(new atgNoStorageAttribute("score_1",0,4),NULL,31);
			$this->add(new atgNoStorageAttribute("score_2",0,4),NULL,33);
			$this->add(new atgNoStorageAttribute("remarque_1",0,50),NULL,32);
			$this->add(new atgNoStorageAttribute("remarque_2",0,50),NULL,34);

			$this->add(new atkManyToOneRelation("id_lieu_match","organisme.golf_parcours",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE ),10135);
			$this->add(new atkDateAttribute("date_rencontre_effective","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING ),30);


			include_once(atkconfig("atkroot")."modules/include/association.inc");
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,40);
			$this->setSecurityAlias("individu.individu");
			$this->m_securityMap["maj"] = "view";
			$this->setOrder("id_tournoi_rencontre, numero_de_match");

	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['maj'] = "maj";
	}
	function score_tout_display($record, $mode='list')
	{
		$db = & atkGetDb();
		$id=$record["id"];
//		$this->p($record);
		$prefix = "data_AE_".$record["id"]."_AE_";
		$retour="Joué le : ".$this->getAttribute('date_rencontre_effective')->edit($record, $prefix, 'edit');

		$retour.="<table>";
		$retour.="<tr><td>Score</td><td>Remarques</td></tr>";

		$sql="SELECT  score,remarque
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$record["score_1"]=$data[0]["score"];
		$retour.="<tr><td>".$this->getAttribute('score_1')->edit($record, $prefix, 'edit')."</td>";
		$record["remarque_1"]=$data[0]["remarque"];
		$retour.="<td>".$this->getAttribute('remarque_1')->edit($record, $prefix, 'edit')."</td></tr>";
		$record["score_2"]=$data[1]["score"];
		$retour.="<tr><td>".$this->getAttribute('score_2')->edit($record, $prefix, 'edit')."</td>";
		$record["remarque_2"]=$data[1]["remarque"];
		$retour.="<td>".$this->getAttribute('remarque_2')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="</table>";

		return $retour;
	}


	function action_maj() {

		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$selection=$this->get_row_selection_information(false);
		foreach ($selection["node_ids"] as $id)
		{
		$remarque_1=escapeSQL($this->m_postvars["data"][$id]["remarque_1"]) ;
		$remarque_2=escapeSQL($this->m_postvars["data"][$id]["remarque_2"]) ;
		$score_1=$this->m_postvars["data"][$id]["score_1"] ;
		$score_2=$this->m_postvars["data"][$id]["score_2"];
		( is_numeric($score_1) || $score_1=="") ? null: die ("valeur de score 1 non numérique") ;
		( is_numeric($score_2) || $score_2=="") ? null : die ("valeur de score 2 non numérique") ;
		( (is_numeric($score_1) && $score_2=="") || (is_numeric($score_2) && $score_1=="")) ?  die ("les deux scores doivent être numériques") : null ;
		$date_rencontre_effective=$this->m_postvars["data"][$id]["date_rencontre_effective"]["date"];
//		$this->p($this->m_postvars);
		if ($date_rencontre_effective!="")
		{		$sql="UPDATE tournoi_rencontre_match set date_rencontre_effective='$date_rencontre_effective',
				id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=".$id."";

		}
		else
		{
			$sql="UPDATE tournoi_rencontre_match set date_rencontre_effective=NULL,
				id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=".$id."";
		}
		$db->query($sql);
		$sql="SELECT  id, id_tournoi_equipe
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$id_tre_1=$data[0]["id"];
		$id_tre_2=$data[1]["id"];
		if ($id_tre_1!="")
		{$sql="UPDATE tournoi_rencontre_equipe set score='$score_1', remarque='$remarque_1',
				id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=$id_tre_1";
		$db->query($sql);}
		if ($id_tre_2!="")
		{$sql="UPDATE tournoi_rencontre_equipe set score='$score_2', remarque='$remarque_2',
				id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=$id_tre_2";
		$db->query($sql);}
		}

		$sql="select tr.id_tournoi from tournoi_rencontre tr, tournoi_rencontre_match trm where trm.id=$id and trm.id_tournoi_rencontre =tr.id ";
		$data=$db->getrows($sql);
		$tournoi_id=$data[0]["id_tournoi"];
		$tournoi_node=newNode("tournoi.tournoi",true);
		$tournoi_node->m_postvars["atkselector"][0]="organisme_tournoi.id='$tournoi_id'";
		$tournoi_node->action_lister_tout();
		$this->redirect();
			
	}

	function date_rencontre_effective_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('date_rencontre_effective')->display($record, $mode);
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('date_rencontre_effective')->edit($record, $prefix, 'edit');
	}
	function score_1_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('score_1')->display($record, $mode);
		$this->p($record);
		$db = & atkGetDb();
		$id=$record["id"];
		$sql="SELECT  score,remarque
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$record["score_1"]=$data[0]["score"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('score_1')->edit($record, $prefix, 'edit');
	}
	function score_2_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('score_2')->display($record, $mode);
		$db = & atkGetDb();
		$id=$record["id"];
		$sql="SELECT  score,remarque
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$record["score_2"]=$data[1]["score"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('score_2')->edit($record, $prefix, 'edit');
	}
	function remarque_1_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('remarque_1')->display($record, $mode);
		$db = & atkGetDb();
		$id=$record["id"];
		$sql="SELECT  score,remarque
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$record["remarque_1"]=$data[0]["remarque"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('remarque_1')->edit($record, $prefix, 'edit');
	}
	function remarque_2_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('remarque_2')->display($record, $mode);
		$db = & atkGetDb();
		$id=$record["id"];
		$sql="SELECT  score,remarque
			from tournoi_rencontre_equipe tre
		where id_tournoi_match=$id";
		$data=$db->getrows($sql);
		$record["remarque_2"]=$data[1]["remarque"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('remarque_2')->edit($record, $prefix, 'edit');
	}



	function id_lieu_match_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_golf_parcours($record["id_lieu_match"]["id"],'o').'<br />',150);
	}

	function descriptor_def()
	{
		return "[numero_de_match]";
	}
	/*	function descripteur_tournoi_match_display($record, $mode) {
		return $this->descripteur_tournoi_match($record["id"],'o');
		}
		*/
	function descripteur_rencontre_display($record, $mode) {
		return $this->descripteur_tournoi_rencontre($record["id_tournoi_rencontre"],'o');
	}
	function descripteur_tournoi_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select id_tournoi  from tournoi_rencontre
	 where  id = ".$record['id_tournoi_rencontre']." ";
		$row = $db->getrows($sql);
		return $this->descripteur_tournoi($row[0]["id_tournoi"],'o');
	}

	function descripteur_match_display($record, $mode) {
		//	$this->p($record);
		return $this->descripteur_tournoi_rencontre_match($record["id"],'o');

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