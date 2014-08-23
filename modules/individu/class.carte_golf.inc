<?php
atkimport("atk.assmetanode");
atkimport("atk.utils.atkstringparser");
useattrib("atgnostorageattribute");


class carte_golf extends assMetaNode {
	var $table = "individu_carte_golf";
	function meta(& $policy) {
		//$policy-> addFlags("annee",AF_SEARCHABLE);
		$policy->addFlags("commentaire","score_1",
"score_2",
"score_3",
"score_4",
"score_5",
"score_6",
"score_7",
"score_8",
"score_9",
"score_10",
"score_11",
"score_12",
"score_13",
"score_14",
"score_15",
"score_16",
"score_17",
"score_18", 
		"id_creation",AF_HIDE_LIST);

//		$policy->addFlags("commentaire", AF_READONLY);
		//	$policy->addFlags("participation_partielle", "participation_complete", "montant_versement", AF_TOTAL);
		//	$policy->setOrder("id_rencontre");
	}
	function carte_golf() {
		$this->atkMetaNode();
		$this->atkNode("carte_golf", NF_MRA | NF_ADD_LINK | NF_TRACK_CHANGES | NF_ADDAFTERADD | NF_COMPACT_NULL);
		$this->setSecurityAlias("individu.individu");
		$this->m_securityMap["resultats"] = "view";

		$this->add(new atkTabbedPane("Pane1",
		array(
	"Général"=>	array("descripteur_carte_golf","id_individu","id_rencontre","id_organisme_parcours","date_depart","heure_depart","trou_depart",
"couleur_depart","sss","slope","distance_aller","distance_retour",
 "distance_totale","id_type_categorie_golf","index_avant","handicap","par", "score_brut","eagle_et_moins","birdie","pars",
 "bogey","double_bogey","triple_bogey_et_plus","stableford","stableford_brut","ssj","net_corrige","index_apres",
 "commentaire",
 "id_creation","date_creation","id_modification","date_modification")
		,
"Trous"=> array("trous")
		

,
"Scores"=> array(
"score_tout",
"score_1",
"score_2",
"score_3",
"score_4",
"score_5",
"score_6",
"score_7",
"score_8",
"score_9",
"score_10",
"score_11",
"score_12",
"score_13",
"score_14",
"score_15",
"score_16",
"score_17",
"score_18"
)
		),AF_NO_LABEL));
		$this->add(new atkDummyAttribute("analyse",0,AF_COMPACT),NULL, 21);
		$this->add(new atkDummyAttribute("descripteur_carte_golf",0,AF_COMPACT),NULL, 20);
		$this->add(new atkOneToManyRelation("trous", "individu.carte_golf_trou", "id_carte", AF_HIDE_LIST));
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_HIDE_LIST | AF_FORCE_LOAD | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),null,40);
		$this->add(new atkManyToOneRelation("id_rencontre", "organisme.rencontre", AF_SEARCHABLE |  AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE|AF_COMPACT),null,25);
		$this->add(new atkManyToOneRelation("id_organisme_parcours", "organisme.golf_parcours", AF_HIDE_LIST | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),null,39);
		$this->add(new atkManyToOneRelation("id_organisme_club", "organisme.organisme", AF_HIDE_LIST | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),null,39);$this->add(new atkDateAttribute("date_depart","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkAttribute("date_depart", AF_HIDE_LIST ),NULL,5);
		$this->add(new atkTimeAttribute("heure_depart", 00, 23, 1, "", AF_TIME_STRING| AF_COMPACT),NULL,5);
		$this->add(new atkNumberAttribute("trou_depart", AF_SEARCHABLE| AF_COMPACT, 2, 0),null,4);
		$this->add(new atkRadioAttribute("couleur_depart", array (
			"Blanc",
			"Jaune",
			"Bleu",
			"Rouge"
			), array (
			"Blanc",
			"Jaune",
			"Bleu",
			"Rouge"
			), AF_OBLIGATORY | AF_HIDE_LIST | AF_HIDE_ADD));
			$this->add(new atkNumberAttribute("sss", AF_HIDE_LIST, 2, 1));
			$this->add(new atkNumberAttribute("slope", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("distance_aller", AF_HIDE_LIST, 5, 0));
			$this->add(new atkNumberAttribute("distance_retour", AF_HIDE_LIST, 5, 0));
			$this->add(new atkNumberAttribute("distance_totale", AF_HIDE_LIST, 5, 0));
			$this->add(new atkManyToOneRelation("id_type_categorie_golf", "table.categorie_golf", AF_HIDE_ADD | AF_COMPACT),null, 21);
			$this->add(new atkManyToOneRelation("id_serie", "organisme.serie_golf", AF_HIDE_LIST|AF_FORCE_LOAD|AF_HIDE_ADD),null, 21);
			$this->add(new atkNumberAttribute("index_avant", AF_HIDE_LIST, 4, 2));
			$this->add(new atkNumberAttribute("handicap", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("par", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("score_brut", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("eagle_et_moins", AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("birdie", AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("pars", AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("bogey", AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("double_bogey", AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("triple_bogey_et_plus",AF_HIDE_LIST, 2, 0));
			$this->add(new atkNumberAttribute("stableford", AF_HIDE_LIST|AF_FORCE_LOAD, 3, 0));
			$this->add(new atkNumberAttribute("stableford_brut", AF_HIDE_LIST|AF_FORCE_LOAD, 3, 0));
			$this->add(new atkNumberAttribute("ssj", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("net_corrige", AF_HIDE_LIST, 3, 0));
			$this->add(new atkNumberAttribute("index_apres",AF_HIDE_LIST, 4, 2));
	$this->add(new atgNoStorageAttribute("score_tout",AF_COMPACT,2),NULL, 8);
	$this->add(new atgNoStorageAttribute("score_1",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_2",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_3",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_4",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_5",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_6",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_7",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_8",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_9",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_10",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_11",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_12",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_13",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_14",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_15",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_16",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_17",AF_HIDE_LIST,2),NULL, 300);
	$this->add(new atgNoStorageAttribute("score_18",AF_HIDE_LIST,2),NULL, 300);

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		
					$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,35);
			$this->m_securityMap["maj_index_golf"] = "view";
			$this->m_securityMap["maj_depart"] = "view";
			$this->m_securityMap["maj_scores_trous"] = "view";
			$this->m_securityMap["maj_scores_stableford"] = "view";
			$this->setOrder("id_individu.nom, id_individu.prenom");
	}
	function action_admin(&$handler) {
	
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	
	
	function score_tout_display($record, $mode='list') 
    { 
  //      if ($mode != 'list') 
  //      return $this->getAttribute('score_1')->display($record, $mode); 
  $id_rencontre=$record["id_rencontre"]["id"];
			$rencontre_node = & getNode("organisme.rencontre");
			$recrencontre=array();
			$recs=$rencontre_node->selectDb("organisme_rencontre.id=".$id_rencontre);
			$recrencontre=$recs[0];
			$forcer_couleur_depart_o_n=$recrencontre["forcer_couleur_depart_o_n"];
			$generer_carte_o_n=$recrencontre["generer_carte_o_n"];
			$saisir_score_trou_o_n=$recrencontre["saisir_score_trou_o_n"];
    	if ($saisir_score_trou_o_n=="1")
    	{
        $db = & atkGetDb(); 
        $id=$record["id"]; 
        $sql="SELECT  score_brut 
            from individu_carte_trou_golf 
        where id_carte=$id order by numero_trou"; 
        $data=$db->getrows($sql); 
 
        $prefix = "data_AE_".$record["id"]."_AE_"; 
        $retour="<table>";
        for ($i = 0; $i < count($data); $i++)
			{
				 ($i==0) ? $retour.="<tr><td><table>" : null;
				 $record["score_".($i+1)]=$data[$i]["score_brut"]; 
//				$retour.=($i+1)."".$this->getAttribute('score_'.($i+1))->edit($record, $prefix, 'edit')." ";
							$retour.="<tr><td>".($i+1)." : </td><td>".$this->getAttribute('score_'.($i+1))->edit($record, $prefix, 'edit')."</td></tr>";
				($i==8) ? $retour.="</table></td><td><table>" : null;
			}
			$retour.="</table></td></tr></table>";
    	}
    	else
    	{
    	$id=$record["id"];  
        $prefix = "data_AE_".$record["id"]."_AE_"; 
        $retour.="Net : ".$this->getAttribute('stableford')->edit($record, $prefix, 'edit')." Brut : ".$this->getAttribute('stableford_brut')->edit($record, $prefix, 'edit');
    }
        return $retour; 
    }
 
	function action_maj_depart() {
		$db = & atkGetDb();

		foreach ($this->m_postvars["atkselector"] as $value)
		{$idarray=explode("=",$value);
		$id=$idarray[1];
		$id=str_replace("'","",$id);
		$carte_node = & getNode("individu.carte_golf");
		$record=array();
		$recs=$carte_node->selectDb("individu_carte_golf.id=".$id);
		$record=$recs[0];
		$record["heure_depart"]=$this->m_postvars["data"][$id]["heure_depart"];
		$record["trou_depart"]=$this->m_postvars["data"][$id]["trou_depart"];
		$carte_node->updateDb($record);
		//	$idcarte=$record["id_carte"]["id"];
		$this->redirect();


		}
	}
	function action_maj_scores_trous() {
		$selection=$this->get_row_selection_information(false);
		foreach ($selection["node_ids"] as $idcarte)
		{
		$carte_trou_node = & getNode("individu.carte_golf_trou");
		$record=array();
		$recs=$carte_trou_node->selectDb("individu_carte_trou_golf.id_carte=".$idcarte);
		 for ($i = 0; $i < count($recs); $i++)
			{
				$record=$recs[$i];
		$record["score_brut"]=$this->m_postvars["data"][$idcarte]["score_".($i+1)];
		$carte_trou_node->updateDb($record);
			}
			$this->calcul_resultats($type="détail",$idcarte);
			}
		echo "Les scores de ".$selection["rows_number"]." cartes ont été enregistrés";
		}
function action_maj_scores_stableford() {
		$selection=$this->get_row_selection_information(false);
		foreach ($selection["node_ids"] as $idcarte)
		{ 
		$carte_node = & getNode("individu.carte_golf");
		$record=array();
		$recs=$carte_node->selectDb("individu_carte_golf.id=".$idcarte);
		$record=$recs[0];
		$record["stableford"]=$this->m_postvars["data"][$idcarte]["stableford"];
		$record["stableford_brut"]=$this->m_postvars["data"][$idcarte]["stableford_brut"];
		$carte_node->updateDb($record);
			}
			echo "Les scores de ".$selection["rows_number"]." cartes ont été enregistrés";
		}
		
		
		
	function heure_depart_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('heure_depart')->display($record, $mode);
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('heure_depart')->edit($record, $prefix, 'edit');
	}
	function trou_depart_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('trou_depart')->display($record, $mode);
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('trou_depart')->edit($record, $prefix, 'edit');
	}



	function id_type_categorie_golf_display($record, $mode) {
		$category_node = & getNode("table.categorie_golf");
		$rec=$category_node->selectDb("type_categorie_golf.id=".$record['id_type_categorie_golf']['id']);
		return $category_node->descripteur($rec[0]);
	}
	function id_rencontre_display($record, $mode) {
		($record["id_rencontre"]["id"]!="") ? $retour=$this->descripteur_rencontre($record["id_rencontre"]["id"],'o').'<br />' : null;
		return $retour;
	}


	function descripteur_carte_golf_display($record, $mode) {
		return $this->descriptor($record);
	}
	/*
	 function descripteur_carte_golf_edit($record, $mode) {
		return $this->descriptor($record);
		}
		*/

	function initial_values() {
		/*
		 $db = & atkGetDb();
		 $select = "select date_debut from organisme_rencontre where id=" . $id_individu . "";
		 $data = $db->getrows($select);

		 return array (
			"date_depart" => array (
			"day" => null,
			"month" => null,
			"year" => null
			));
			*/
	}

	function preAdd(& $record) {

		parent :: preAdd($record);


		$id_individu = $record['id_individu']['id'];
		$id_parcours = $record['id_organisme_parcours']['id'];

		$db = & atkGetDb();
		$select = "select golf_index, sexe from individu where id=" . $id_individu . "";
		$data = $db->getrows($select);
		$golfindex = $data[0]["golf_index"];
		if (!isset ($golfindex) || $golfindex == 0) {
			triggerError($record, "", "Index non renseigné pour ce compétiteur");
			return false;
		}
		$sexe = $data[0]["sexe"];
		$record["index_avant"] = $golfindex;
		$select = "select id from type_categorie_golf where  " . $golfindex . " <= index_haut and " . $golfindex . " >= index_bas  ";
		$data = $db->getrows($select);
		$record["id_type_categorie_golf"]['id'] = $data[0]["id"];
		if ($sexe == 'F') {
			if ($golfindex < 18) {
				$record["couleur_depart"] = 'Bleu';
				$select = "select sss_bleu as sss, slope_bleu as slope from organisme_golf_parcours  where id=" . $id_parcours;
				$seldistance = "select sum(distance_bleu) as distance ";
			} else {
				$record["couleur_depart"] = 'Rouge';
				$select = "select sss_rouge as sss, slope_rouge as slope from organisme_golf_parcours  where id=" . $id_parcours;
				$seldistance = "select sum(distance_rouge) as distance ";
			}
		}
		if ($sexe == 'M') {
			if ($golfindex < 18) {
				$record["couleur_depart"] = 'Blanc';
				$select = "select sss_blanc as sss, slope_blanc as slope from organisme_golf_parcours  where id=" . $id_parcours;
				$seldistance = "select sum(distance_blanc) as distance ";
			} else {
				$record["couleur_depart"] = 'Jaune';
				$select = "select sss_jaune as sss, slope_jaune as slope from organisme_golf_parcours  where id=" . $id_parcours;
				$seldistance = "select sum(distance_jaune) as distance ";
			}
		}
		$seldistancealler = $seldistance . ' from organisme_golf_parcours_trou where numero_trou <10 and id_organisme_parcours=' . $id_parcours;
		$seldistanceretour = $seldistance . ' from organisme_golf_parcours_trou where numero_trou >9 and id_organisme_parcours=' . $id_parcours;
		$data = $db->getrows("select sum(par) as par from organisme_golf_parcours_trou where id_organisme_parcours=" . $id_parcours);
		$par = $data[0]["par"];
		$data = $db->getrows($select);
		$sss = $data[0]["sss"];
		$record["sss"] = $sss;
		$slope = $data[0]["slope"];
		$record["slope"] = $slope;
		$record["handicap"] = round(($golfindex * $slope / 113) + ($sss - $par));
		$handicap36=(round((36 * $slope / 113) + ($sss - $par)))-36;
		if ($golfindex>36)
		{$record["handicap"]=$record["handicap"]+$handicap36;}
		if ($record["handicap"] > 54) {
			$record["handicap"] = 54;
		}
		$record["par"] = $par;
		$data = $db->getrows($seldistancealler);
		$record["distance_aller"] = $data[0]["distance"];
		$data = $db->getrows($seldistanceretour);
		$record["distance_retour"] = $data[0]["distance"];
		$record["distance_totale"] = $record["distance_aller"] + $record["distance_retour"];
		($record["trou_depart"]>0) ? null : $record["trou_depart"]="1";


	}
	function postAdd($record) {
		//	$this->p($record);
		$id_carte = $record['id'];
		$id_individu = $record['id_individu']['id'];
		$id_parcours = $record['id_organisme_parcours']['id'];
		$handicap = $record['handicap'];
		$couleur = $record['couleur_depart'];
		$db = & atkGetDb();
		$select = "select id, numero_trou, distance_blanc, distance_jaune,
																 distance_bleu, distance_rouge, par, coups_recus from organisme_golf_parcours_trou where 
																 id_organisme_parcours=" . $id_parcours . " order by coups_recus";
		$trous = $db->getrows($select);
		for ($i = 0; $i < count($trous); $i++) {
			$trous[$i]["coups_donnes"] = 0;
			$trous[$i]["par_net"] = $trous[$i]["par"];
		}
		while ($handicap > 0) {
			for ($i = 0; $i < count($trous); $i++) {
				$trous[$i]["coups_donnes"]++;
				$handicap--;
				if ($handicap == 0) {
					break;
				}
			}
		}
		for ($i = 0; $i < count($trous); $i++) {
			$trous[$i]["par_net"] += $trous[$i]["coups_donnes"];
		}
		for ($i = 0; $i < count($trous); $i++) {
			$carte_trous_node = & getNode("individu.carte_golf_trou");
			$carte_trous_record = array ();
			$carte_trous_record["id_carte"]["id"] = $id_carte;
			$carte_trous_record["id_trou"]["id"] = $trous[$i]["id"];
			$carte_trous_record["numero_trou"] = $trous[$i]["numero_trou"];
			if ($couleur == 'Blanc') {
				$carte_trous_record["couleur"] = 'Blanc';
				$carte_trous_record["distance"] = $trous[$i]["distance_blanc"];
				$carte_trous_record["sss"] = $trous[$i]["sss_blanc"];
				$carte_trous_record["slope"] = $trous[$i]["slope_blanc"];
			}
			if ($couleur == 'Jaune') {
				$carte_trous_record["couleur"] = 'Jaune';
				$carte_trous_record["distance"] = $trous[$i]["distance_jaune"];
				$carte_trous_record["sss"] = $trous[$i]["sss_jaune"];
				$carte_trous_record["slope"] = $trous[$i]["slope_jaune"];
			}
			if ($couleur == 'Bleu') {
				$carte_trous_record["couleur"] = 'Bleu';
				$carte_trous_record["distance"] = $trous[$i]["distance_bleu"];
				$carte_trous_record["sss"] = $trous[$i]["sss_bleu"];
				$carte_trous_record["slope"] = $trous[$i]["slope_bleu"];
			}
			if ($couleur == 'Rouge') {
				$carte_trous_record["couleur"] = 'Rouge';
				$carte_trous_record["distance"] = $trous[$i]["distance_rouge"];
				$carte_trous_record["sss"] = $trous[$i]["sss_rouge"];
				$carte_trous_record["slope"] = $trous[$i]["slope_rouge"];
			}
			$carte_trous_record["coups_recus"] = $trous[$i]["coups_recus"];
			$carte_trous_record["coups_donnes"] = $trous[$i]["coups_donnes"];
			$carte_trous_record["par"] = $trous[$i]["par"];
			$carte_trous_record["par_net"] = $trous[$i]["par_net"];

			$carte_trous_node->addDb($carte_trous_record);
		}
		parent :: postAdd($record);
	}
	function getFormButtons($mode, $record) {
		// Get the normal buttons
		$buttons = parent :: getFormButtons($mode, $record);
		if ($mode === 'edit') {
			$temp = atkbutton($this->text("Calcul à partir du détail par trou"), dispatch_url("individu.carte_golf", "resultats", array (
				"id" => $record["id"],
				"type"=> "détail"), "dispatch.php"));
			array_unshift($buttons,$temp);
			$temp = atkbutton($this->text("Calcul à partir du global saisi sur la carte"), dispatch_url("individu.carte_golf", "resultats", array (
				"id" => $record["id"],
				"type"=> "global"), "dispatch.php"));
			array_unshift($buttons,$temp);
		}
		return $buttons;
	}
	function action_resultats() {
		$type=$this->m_postvars["type"];
		$idcarte=$this->m_postvars["id_carte"];
		//		$this->p($this->m_postvars);
		$carte_node = & getNode("individu.carte_golf");

		$carte_record_org = $carte_node->selectDb("individu_carte_golf.id=".$idcarte);
		$carte_record = $carte_record_org[0];
		$record=$carte_record["trous"];
		$nombre_trous=count($record);
		//		$this->p($record);



		if ($type =="détail")
		{
			//pour chaque trou
			for ($i = 0; $i < $nombre_trous; $i++)
			{		$carte_trou_node = & getNode("individu.carte_golf_trou");
			$rectrou=array();
			$rectrou=$carte_trou_node->selectDb("individu_carte_trou_golf.id=".$record[$i]["id"]);
			$rectrou=$rectrou[0];
			if ($rectrou["score_brut"]=='')
			{$rectrou["stableford"] = '';
			$rectrou["stableford_brut"] = '';
			$rectrou["coup_nomme"] = '';}
			else

			{		if ($rectrou["score_brut"] > 0) {
				$rectrou["stableford"] = - ($rectrou["score_brut"] - $rectrou["par_net"] - 2);
				$rectrou["stableford_brut"] = - ($rectrou["score_brut"] - $rectrou["par"] - 2);
				if ($rectrou["stableford"] < 0) {
					$rectrou["stableford"] = 0;
				}
				if ($rectrou["stableford_brut"] < 0) {
					$rectrou["stableford_brut"] = 0;
				}
				$rectrou["coup_nomme"] = ($rectrou["score_brut"] - $rectrou["par"] + 3);
				if ($rectrou["coup_nomme"] < 1) {
					$rectrou["coup_nomme"] = 1;
				}
				if ($rectrou["coup_nomme"] > 6) {
					$rectrou["coup_nomme"] = 6;
				}
			}

			if ($rectrou["score_brut"] == 'X') {
				$rectrou["stableford"] =  $rectrou["par_net"]+2;
				$rectrou["stableford_brut"] = $rectrou["par"]+2;
				$rectrou["coup_nomme"] = 6;
			}
			}
			//			$this->p($rectrou);
			$carte_trou_node->updateDb($rectrou);
			}

			// fin pour chaque trou

			$select = "select sum(score_brut) as score_brut,
		
										sum(stableford) as stableford,
										sum(stableford_brut) as stableford_brut
										from individu_carte_trou_golf where id_carte=$idcarte";
			$db = & atkGetDb();
			$resultats = $db->getrows($select);

			$carte_record["score_brut"] = $resultats[0]["score_brut"];
			$carte_record["stableford"] = $resultats[0]["stableford"];
			$carte_record["stableford_brut"] = $resultats[0]["stableford_brut"];

			$select = "select count(coup_nomme) as eagle
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=1 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["eagle_et_moins"] = $coup_nomme[0]["eagle"];
			$select = "select count(coup_nomme) as birdie
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=2 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["birdie"] = $coup_nomme[0]["birdie"];
			$select = "select count(coup_nomme) as pars
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=3 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["pars"] = $coup_nomme[0]["pars"];
			$select = "select count(coup_nomme) as bogey
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=4 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["bogey"] = $coup_nomme[0]["bogey"];
			$select = "select count(coup_nomme) as double_bogey
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=5 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["double_bogey"] = $coup_nomme[0]["double_bogey"];
			$select = "select count(coup_nomme) as triple_bogey
										from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=6 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["triple_bogey_et_plus"] = $coup_nomme[0]["triple_bogey"];
		}


		if (($carte_record["id_rencontre"]["id"])!="")
		{$select = 'select ssj
										from organisme_rencontre where id=' . $carte_record["id_rencontre"]["id"] . ' ';
		$db = & atkGetDb();
		$data = $db->getrows($select);
		$carte_record["ssj"] = $data[0]["ssj"];
		}
		if (!isset ($carte_record["ssj"])) {
			echo "Le ssj n\'a pas été renseigné ";
			die();
		}


		$carte_record["net_corrige"] = $carte_record["stableford"] + $carte_record["ssj"];
		$carte_record["brut_corrige"] = $carte_record["stableford_brut"] + $carte_record["ssj"];
		$select = 'select coefficient_performance, coefficient_contre_performance, zone_tampon from type_categorie_golf
										 where id=' . $carte_record["id_type_categorie_golf"]["id"] . ' ';
		$db = & atkGetDb();
		$data = $db->getrows($select);
		$coefficient_asc = $data[0]["coefficient_performance"];
		$coefficient_desc = $data[0]["coefficient_contre_performance"];
		$zone_tampon = $data[0]["zone_tampon"];
		$stbcorr = $carte_record["stableford"] + $carte_record["ssj"];
		$differentiel = 36 - $stbcorr;
		if ($differentiel < 0) {
			$carte_record["index_apres"] = $carte_record["index_avant"] + ($differentiel * $coefficient_asc);
		}
		if ($differentiel > 0) {
			if ($differentiel > $zone_tampon) {
				$carte_record["index_apres"] = $carte_record["index_avant"] + ($differentiel * $coefficient_desc);
			} else {
				$carte_record["index_apres"] = $carte_record["index_avant"];
			}
		}
		if ($differentiel == 0) {
			$carte_record["index_apres"] = $carte_record["index_avant"];
		}
		if ($carte_record["index_apres"] > 53.5)
		$carte_record["index_apres"] = 53.5;
		$carte_record["atkorgkey"] = $carte_record_org[0]["atkprimkey"];
		$carte_record["atkprimkey"] = $carte_record_org[0]["atkprimkey"];
		$carte_node->updateDb($carte_record);
		//	echo "Mise à jour effectuée";
		//		$location = $carte_node->feedbackUrl("resultats", ACTION_SUCCESS);
		$location=dispatch_url("individu.carte_golf", "admin", array (
		 "atkfilter" => "individu_carte_golf.id_rencontre='" . $carte_record["id_rencontre"]["id"]  . "'"
			)) ;
			//			$this->p($location);

		echo "Résultats calculés";
die ();
//	$carte_node->redirect($location);
	}
	
	function calcul_resultats($type="détail",$idcarte) {
		
		$carte_node = & getNode("individu.carte_golf");
	
		$carte_record_org = $carte_node->selectDb("individu_carte_golf.id=".$idcarte);
		$carte_record = $carte_record_org[0];
		$record=$carte_record["trous"];
		$nombre_trous=count($record);
		//		$this->p($record);
	
	
	
		if ($type =="détail")
		{
			//pour chaque trou
			for ($i = 0; $i < $nombre_trous; $i++)
			{		$carte_trou_node = & getNode("individu.carte_golf_trou");
			$rectrou=array();
			$rectrou=$carte_trou_node->selectDb("individu_carte_trou_golf.id=".$record[$i]["id"]);
			$rectrou=$rectrou[0];
			if ($rectrou["score_brut"]=='')
			{$rectrou["stableford"] = '';
			$rectrou["stableford_brut"] = '';
			$rectrou["coup_nomme"] = '';}
			else
	
			{		if ($rectrou["score_brut"] > 0) {
					$rectrou["stableford"] = - ($rectrou["score_brut"] - $rectrou["par_net"] - 2);
							$rectrou["stableford_brut"] = - ($rectrou["score_brut"] - $rectrou["par"] - 2);
							if ($rectrou["stableford"] < 0) {
							$rectrou["stableford"] = 0;
							}
							if ($rectrou["stableford_brut"] < 0) {
							$rectrou["stableford_brut"] = 0;
							}
							$rectrou["coup_nomme"] = ($rectrou["score_brut"] - $rectrou["par"] + 3);
							if ($rectrou["coup_nomme"] < 1) {
								$rectrou["coup_nomme"] = 1;
							}
							if ($rectrou["coup_nomme"] > 6) {
								$rectrou["coup_nomme"] = 6;
							}
			}
	
			if ($rectrou["score_brut"] == 'X') {
				$rectrou["stableford"] =  $rectrou["par_net"]+2;
				$rectrou["stableford_brut"] = $rectrou["par"]+2;
				$rectrou["coup_nomme"] = 6;
			}
			}
			//			$this->p($rectrou);
			$carte_trou_node->updateDb($rectrou);
			}
	
			// fin pour chaque trou
	
			$select = "select sum(score_brut) as score_brut,
	
			sum(stableford) as stableford,
			sum(stableford_brut) as stableford_brut
			from individu_carte_trou_golf where id_carte=$idcarte";
			$db = & atkGetDb();
			$resultats = $db->getrows($select);
	
			$carte_record["score_brut"] = $resultats[0]["score_brut"];
			$carte_record["stableford"] = $resultats[0]["stableford"];
			$carte_record["stableford_brut"] = $resultats[0]["stableford_brut"];
	
			$select = "select count(coup_nomme) as eagle
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=1 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["eagle_et_moins"] = $coup_nomme[0]["eagle"];
			$select = "select count(coup_nomme) as birdie
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=2 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["birdie"] = $coup_nomme[0]["birdie"];
			$select = "select count(coup_nomme) as pars
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=3 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["pars"] = $coup_nomme[0]["pars"];
			$select = "select count(coup_nomme) as bogey
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=4 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["bogey"] = $coup_nomme[0]["bogey"];
			$select = "select count(coup_nomme) as double_bogey
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=5 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["double_bogey"] = $coup_nomme[0]["double_bogey"];
			$select = "select count(coup_nomme) as triple_bogey
			from individu_carte_trou_golf where id_carte=$idcarte and coup_nomme=6 ";
			$coup_nomme = $db->getrows($select);
			$carte_record["triple_bogey_et_plus"] = $coup_nomme[0]["triple_bogey"];
		}
	
	
		if (($carte_record["id_rencontre"]["id"])!="")
		{$select = 'select ssj
										from organisme_rencontre where id=' . $carte_record["id_rencontre"]["id"] . ' ';
		$db = & atkGetDb();
		$data = $db->getrows($select);
		$carte_record["ssj"] = $data[0]["ssj"];
		}
		if (!isset ($carte_record["ssj"])) {
			echo "Le ssj n\'a pas été renseigné ";
			die();
		}
	
	
		$carte_record["net_corrige"] = $carte_record["stableford"] + $carte_record["ssj"];
		$carte_record["brut_corrige"] = $carte_record["stableford_brut"] + $carte_record["ssj"];
		$select = 'select coefficient_performance, coefficient_contre_performance, zone_tampon from type_categorie_golf
										 where id=' . $carte_record["id_type_categorie_golf"]["id"] . ' ';
		$db = & atkGetDb();
		$data = $db->getrows($select);
		$coefficient_asc = $data[0]["coefficient_performance"];
		$coefficient_desc = $data[0]["coefficient_contre_performance"];
		$zone_tampon = $data[0]["zone_tampon"];
		$stbcorr = $carte_record["stableford"] + $carte_record["ssj"];
		$differentiel = 36 - $stbcorr;
		if ($differentiel < 0) {
			$carte_record["index_apres"] = $carte_record["index_avant"] + ($differentiel * $coefficient_asc);
		}
		if ($differentiel > 0) {
			if ($differentiel > $zone_tampon) {
				$carte_record["index_apres"] = $carte_record["index_avant"] + ($differentiel * $coefficient_desc);
			} else {
				$carte_record["index_apres"] = $carte_record["index_avant"];
			}
		}
		if ($differentiel == 0) {
			$carte_record["index_apres"] = $carte_record["index_avant"];
		}
		if ($carte_record["index_apres"] > 53.5)
			$carte_record["index_apres"] = 53.5;
		$carte_record["atkorgkey"] = $carte_record_org[0]["atkprimkey"];
		$carte_record["atkprimkey"] = $carte_record_org[0]["atkprimkey"];
		$carte_node->updateDb($carte_record);
			
		echo "Résultats calculés<br/>";

	}
	
	function descriptor_def() {
		return "<b>[id_individu.nom] [id_individu.prenom]</b> au <b>[id_organisme_parcours.libelle]</b> du <b>[id_organisme_parcours.id_organisme.nom]</b>";

	}

	function analyse_display($record,$mode)
	{
		$analyse="</b>Départ : <b>".$record["dl_depart"]."<br/>";
		$analyse.="</b>Second coup : <b>".$record["dl_second_coup"]."<br/>";
		$analyse.="</b>Troisième coup : <b>".$record["dl_troisieme_coup"]."<br/>";
		$analyse.="</b>Pitch : <b>".$record["dl_pitch"]."<br/>";
		$analyse.="</b>Chip : <b>".$record["dl_chip"]."<br/>";
		$analyse.="</b>Bunker : <b>".$record["dl_bunker"]."<br/>";
		$analyse.="</b>Puts : <b>".$record["dl_putts"]."<br/>";
		return $analyse;
		/*
		 *  `dl_depart` ,
		 `dl_second_coup`,
		 `dl_troisieme_coup`,
		 `dl_pitch`,
		 `dl_chip`,
		 `dl_bunker` ,
		 `dl_putts`,
		 */
	}
	function descriptor($record, $golf_les_cartes_o_n='n')
	{
		if ($this->m_action!="admin" && $golf_les_cartes_o_n=="n")
		{if (method_exists($this,"descriptor_def"))
		{
			$parser = new atkStringParser($this->descriptor_def());
			return $parser->parse($record);
		}}
		else {
		
			$id_rencontre=$record["id_rencontre"]["id"];
			$rencontre_node = & getNode("organisme.rencontre");
			$recrencontre=array();
			$recs=$rencontre_node->selectDb("organisme_rencontre.id=".$id_rencontre);
			$recrencontre=$recs[0];
			$forcer_couleur_depart_o_n=$recrencontre["forcer_couleur_depart_o_n"];
			$generer_carte_o_n=$recrencontre["generer_carte_o_n"];
			$saisir_score_trou_o_n=$recrencontre["saisir_score_trou_o_n"];

		
			$this->addStyle("recordlist.css");
			$recs = $this->selectDb("individu_carte_golf.id=".$record['id']);
//				$this->p($recs);

			$nombre_trous=count($recs[0]["trous"]);
			$parcoursnode = &atkGetNode("organisme.golf_parcours");
			$records = $parcoursnode->selectDb("organisme_golf_parcours.id=".$recs[0]["id_organisme_parcours"]["id"]);
			if ($golf_les_cartes_o_n=="n")
			{$parcours=$parcoursnode->descriptor($records[0],"n","n");}
			else
			{$parser = new atkStringParser($this->descriptor_def());
			$parcours= $parser->parse($record);
			}
			$record_trous=$records[0]["trous"];

			if ($recs[0]["date_depart"]>0)
			{$datedepart=mktime($recs[0]["heure_depart"]["hours"],$recs[0]["heure_depart"]["minutes"],0,substr($recs[0]["date_depart"], 5,2),substr($recs[0]["date_depart"], 8,2),substr($recs[0]["date_depart"], 0,4));
			}
			($golf_les_cartes_o_n=="n")	? $tableautrous.=$this->descripteur_individu($recs[0]["id_individu"]["id"],null,null,null,null,"n","o")."<br/>"  : null;
			
			($golf_les_cartes_o_n=="n")	? $tableautrous.="</b>Parcours : ".$parcours."<br/>" : 
			$tableautrous.="<p style=\"font-size: 14px;\">".$parcours."</p><br/>";
			
			($recs[0]["trou_depart"]>0) ? $tableautrous.="</b>Départ au trou : <b>".$recs[0]["trou_depart"]." (".$recs[0]["couleur_depart"].")" : null;
			($recs[0]["date_depart"]>0) ? $tableautrous.="</b> le <b>".date("d/m/Y",$datedepart)."</b> à <b>".date("H:i",$datedepart) : null;
	//		($recs[0]["date_depart"]>0) ? $tableautrous.="</b> le <b>".strtolower(text(date("l",$datedepart)))." ".date("d/m/Y",$datedepart)."</b> à <b>".date("H:i",$datedepart) : null;
			($recs[0]["date_depart"]>0 || $recs[0]["trou_depart"]>0) ? $tableautrous.="<br/>" : null;
if ($recs[0]["id_serie"]["id"]>0) 
			{$serie_node = & getNode("organisme.serie_golf");
		$rec=$serie_node->selectDb("organisme_serie.id=".$record['id_serie']['id']);
		$tableautrous.=$serie_node->descripteur($rec[0]);
}
			
			
			if ($generer_carte_o_n=="1")
			{
			$tableautrous.="</b>Index = <b>".$recs[0]["index_avant"]."</b>, Sss = <b>".$recs[0]["sss"]."</b>, Slope = <b>".$recs[0]["slope"]."</b>, Handicap de jeu = <b>".$recs[0]["handicap"];
			($recs[0]["ssj"]!="") ?	$tableautrous.="</b>, Ssj = <b>".$recs[0]["ssj"]."<br/>" : $tableautrous.="<br/>";
			
			if ($golf_les_cartes_o_n=="n")
			{$tableautrous.=" ".href(dispatch_url("individu.carte_golf_trou", "admin", array (
				'atkfilter' => "individu_carte_trou_golf.id_carte='".$record['id']."'"
				), "dispatch.php"), "<b>".text("Saisir les résultats")."</b>", SESSION_NESTED)."<br/>";
			}
					$tableautrous.="<table class=\"golfgg\"><tr>";

			$tableautrous.="<td class=\"golfgg\"></td>";
			for ($i = 0; $i < 9; $i++)
			{ ($record["trou_depart"]==$recs[0]["trous"][$i]["numero_trou"]) ? $tableautrous.="<td class=\"golfgg\" style=\"background: red\">"."<b>".trim($recs[0]["trous"][$i]["numero_trou"])."</b></td>" :
			$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
			$tableautrous.="<td class=\"golfgg\">Aller</td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ ($record["trou_depart"]==$recs[0]["trous"][$i]["numero_trou"]) ? $tableautrous.="<td class=\"golfgg\" style=\"background: red\">"."<b>".trim($recs[0]["trous"][$i]["numero_trou"])."</b></td>" :
			$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
			$tableautrous.="<td class=\"golfgg\">Retour</td>";
			$tableautrous.="<td class=\"golfgg\">A/R</td>";
			$tableautrous.="</tr>";

			($recs[0]["couleur_depart"]=="Blanc") ? $couleur_fond="white" : null;
			($recs[0]["couleur_depart"]=="Jaune") ? $couleur_fond="yellow" : null;
			($recs[0]["couleur_depart"]=="Bleu") ? $couleur_fond="aqua" : null;
			($recs[0]["couleur_depart"]=="Rouge") ? $couleur_fond="red" : null;

			$tableautrous.="<tr style=\"background: ".$couleur_fond."\"><td class=\"golfgg\">Distance (m)</td>";
			for ($i = 0; $i < 9; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance"])."</td>";       	       }
			$tableautrous.="<td class=\"golfgg\"><b>".trim($recs[0]["distance_aller"])."</b></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance"])."</td>";       	       }
			$tableautrous.="<td class=\"golfgg\"><b>".trim($recs[0]["distance_retour"])."</b></td>";
			$tableautrous.="<td class=\"golfgg\"><b>".trim($recs[0]["distance_totale"])."</b></td>";
			$tableautrous.="</tr>";

			$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Par</td>";
			for ($i = 0; $i < 9; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";
			$par_aller+= $recs[0]["trous"][$i]["par"];     	       }
			$tableautrous.="<td class=\"golfgg\"><b>".$par_aller."</b></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";
			$par_retour+= $recs[0]["trous"][$i]["par"];     	    	       }
			$tableautrous.="<td class=\"golfgg\"><b>".$par_retour."</b></td>";
			$tableautrous.="<td class=\"golfgg\"><b>".trim($par_aller+$par_retour)."</b></td>";
			$tableautrous.="</tr>";

			$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Hcp</td>";
			for ($i = 0; $i < 9; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";
			}
			$tableautrous.="<td class=\"golfgg\"></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";
			}
			$tableautrous.="<td class=\"golfgg\"></td>";
			$tableautrous.="<td class=\"golfgg\"></td>";
			$tableautrous.="</tr>";

			$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Coups reçus</td>";
			for ($i = 0; $i < 9; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_donnes"])."</td>";
			$coups_donnes_aller+= $recs[0]["trous"][$i]["coups_donnes"];  }
			$tableautrous.="<td class=\"golfgg\"><b>".$coups_donnes_aller."</b></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ $tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_donnes"])."</td>";
			$coups_donnes_retour+= $recs[0]["trous"][$i]["coups_donnes"]; 	    	       }
			$tableautrous.="<td class=\"golfgg\"><b>".$coups_donnes_retour."</b></td>";
			$tableautrous.="<td class=\"golfgg\"><b>".trim($coups_donnes_aller+$coups_donnes_retour)."</b></td>";
			$tableautrous.="</tr>";

			$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Score joueur</td>";
			for ($i = 0; $i < 9; $i++)
			{

				($recs[0]["trous"][$i]["score_brut"]>0) ? $perf=$recs[0]["trous"][$i]["par"]-$recs[0]["trous"][$i]["score_brut"] : null;
				switch ($perf)
				{
					case 0 :
						$couleur="lime";
						break;
					case 1 :
						$couleur="Pink";
						break;
					case 2 :
						$couleur="orange";
						break;
					case 3 :
						$couleur="red";
						break;
					default :
						$couleur="Aquamarine";
						break;


				}
				($recs[0]["trous"][$i]["score_brut"]=="") ? $couleur="transparent" : null;
				if ($recs[0]["trous"][$i]["score_brut"]=="")
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["score_brut"])."<br/></td>";}
else if ($recs[0]["trous"][$i]["score_brut"]>=$recs[0]["trous"][$i]["par_net"]+2)
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">"."X"."<br/></td>";}
else
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["score_brut"])."</td>";}
				
			}
			$tableautrous.="<td class=\"golfgg\"><b>".trim($score_brut_aller,"0")."</b></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ ($recs[0]["trous"][$i]["score_brut"]>0) ? $perf=$recs[0]["trous"][$i]["par"]-$recs[0]["trous"][$i]["score_brut"] : null;
			switch ($perf)
			{
				case 0 :
					$couleur="lime";
					break;
				case 1 :
					$couleur="Pink";
					break;
				case 2 :
					$couleur="orange";
					break;
				case 3 :
					$couleur="red";
					break;
				default :
					$couleur="Aquamarine";
					break;


			}
							($recs[0]["trous"][$i]["score_brut"]=="") ? $couleur="transparent" : null;
				if ($recs[0]["trous"][$i]["score_brut"]=="")
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["score_brut"])."<br/></td>";}
else if ($recs[0]["trous"][$i]["score_brut"]>=$recs[0]["trous"][$i]["par_net"]+2)
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">"."X"."<br/></td>";}
else
{$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["score_brut"])."</td>";}
			}
			$tableautrous.="<td class=\"golfgg\"><b>".trim($score_brut_retour,"0")."</b></td>";
			$tableautrous.="<td class=\"golfgg\"><b>".trim(($score_brut_aller+$score_brut_retour),"0")."</b></td>";
			$tableautrous.="</tr>";

			$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Stableford net</td>";
			for ($i = 0; $i < 9; $i++)
			{
				($recs[0]["trous"][$i]["score_brut"]>0) ? $perf=$recs[0]["trous"][$i]["par_net"]-$recs[0]["trous"][$i]["score_brut"] : null;
				switch ($perf)
				{
					case 0 :
						$couleur="lime";
						break;
					case 1 :
						$couleur="Pink";
						break;
					case 2 :
						$couleur="orange";
						break;
					case 3 :
						$couleur="red";
						break;

					default :
						$couleur="Aquamarine";
						break;


				}
				($recs[0]["trous"][$i]["stableford"]=="") ? $couleur="transparent" : null;
				$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["stableford"])."</td>";

				$stableford_aller+= $recs[0]["trous"][$i]["stableford"];     	 }
				$tableautrous.="<td class=\"golfgg\"><b>".ltrim($stableford_aller,"0")."</b></td>";
				for ($i = 9; $i < $nombre_trous; $i++)
				{ ($recs[0]["trous"][$i]["score_brut"]>0) ? $perf=$recs[0]["trous"][$i]["par_net"]-$recs[0]["trous"][$i]["score_brut"] : null;
				switch ($perf)
				{
					case 0 :
						$couleur="lime";
						break;
					case 1 :
						$couleur="Pink";
						break;
					case 2 :
						$couleur="orange";
						break;
					case 3 :
						$couleur="red";
						break;

					default :
						$couleur="Aquamarine";
						break;


				}
				($recs[0]["trous"][$i]["stableford"]=="") ? $couleur="transparent" : null;
				$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["stableford"])."</td>";
				$stableford_retour+= $recs[0]["trous"][$i]["stableford"];        	    	       }
				$tableautrous.="<td class=\"golfgg\"><b>".ltrim($stableford_retour,"0")."</b></td>";

				(($stableford_aller+$stableford_retour)>35) ? $couleur="lime" : $couleur="red";
				(($stableford_aller+$stableford_retour)==0) ? $couleur="transparent" : null;
				$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".ltrim(($stableford_aller+$stableford_retour),"0")."</b></td>";
				$tableautrous.="</tr>";

				$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Stableford brut</td>";
				for ($i = 0; $i < 9; $i++)
				{
					($recs[0]["trous"][$i]["score_brut"]>0) ? $perf=$recs[0]["trous"][$i]["par"]-$recs[0]["trous"][$i]["score_brut"] : null;
					switch ($perf)
					{
						case 0 :
							$couleur="lime";
							break;
						case 1 :
							$couleur="Pink";
							break;
						case 2 :
							$couleur="orange";
							break;
						case 3 :
							$couleur="red";
							break;

						default :
							$couleur="Aquamarine";
							break;


					}
					($recs[0]["trous"][$i]["stableford_brut"]=="") ? $couleur="transparent" : null;
					$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["stableford_brut"])."</td>";

					$stableford_brut_aller+= $recs[0]["trous"][$i]["stableford_brut"];     	 }
					$tableautrous.="<td class=\"golfgg\"><b>".ltrim($stableford_brut_aller,"0")."</b></td>";
					for ($i = 9; $i < $nombre_trous; $i++)
					{ ($recs[0]["trous"][$i]["score_brut"]>0) ?  $perf=$recs[0]["trous"][$i]["par"]-$recs[0]["trous"][$i]["score_brut"] :null ;
					switch ($perf)
					{
						case 0 :
							$couleur="lime";
							break;
						case 1 :
							$couleur="Pink";
							break;
						case 2 :
							$couleur="orange";
							break;
						case 3 :
							$couleur="red";
							break;

						default :
							$couleur="Aquamarine";
							break;


					}
					($recs[0]["trous"][$i]["stableford_brut"]=="")  ? $couleur="transparent" : null;
					$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".trim($recs[0]["trous"][$i]["stableford_brut"])."</td>";
					$stableford_brut_retour+= $recs[0]["trous"][$i]["stableford_brut"];        	    	       }
					$tableautrous.="<td class=\"golfgg\"><b>".ltrim($stableford_brut_retour,"0")."</b></td>";

					(($stableford_brut_aller+$stableford_brut_retour)>35) ? $couleur="lime" : $couleur="red";
					(($stableford_brut_aller+$stableford_brut_retour)==0) ? $couleur="transparent" : null;
					$tableautrous.="<td class=\"golfgg\" style=\"background: ".$couleur."\">".ltrim(($stableford_brut_aller+$stableford_brut_retour),"0")."</b></td>";
					$tableautrous.="</tr>";
	if ($golf_les_cartes_o_n=="o")				
					
	{		$tableautrous.="<tr><td class=\"golfgg\">Score marqueur</td>";
			for ($i = 0; $i < 9; $i++)
			{ $tableautrous.="<td class=\"golfgg\"><br/></td>";       	       }
			$tableautrous.="<td class=\"golfgg\"><br/></td>";
			for ($i = 9; $i < $nombre_trous; $i++)
			{ $tableautrous.="<td class=\"golfgg\"><br/></td>";       	       }
			$tableautrous.="<td class=\"golfgg\"><br/></td>";
			$tableautrous.="<td class=\"golfgg\"><br/></td>";
			$tableautrous.="</tr>";
			
		}	
						
					$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Temps</td>";
					for ($i = 0; $i < 9; $i++)
					{ $tableautrous.="<td class=\"golfgg\">".$record_trous[$i]["temps_de_jeu"]["hours"].":".$record_trous[$i]["temps_de_jeu"]["minutes"]."</td>";
					$temps_aller=$this->addtime($temps_aller,$record_trous[$i]["temps_de_jeu"]);
					}
					$tableautrous.="<td class=\"golfgg\"><b>".$temps_aller["hours"].":".$temps_aller["minutes"]."</b></td>";
					for ($i = 9; $i < $nombre_trous; $i++)
					{ $tableautrous.="<td class=\"golfgg\">".$record_trous[$i]["temps_de_jeu"]["hours"].":".$record_trous[$i]["temps_de_jeu"]["minutes"]."</td>";
					$temps_retour=$this->addtime($temps_retour,$record_trous[$i]["temps_de_jeu"]);
					}
					$tableautrous.="<td class=\"golfgg\"><b>".$temps_retour["hours"].":".$temps_retour["minutes"]."</b></td>";
					$temps_aller_retour=$this->addtime($temps_aller, $temps_retour);
					$tableautrous.="<td class=\"golfgg\"><b>".$temps_aller_retour["hours"].":".$temps_aller_retour["minutes"]."</b></td>";
					$tableautrous.="</tr>";

					$record["trou_depart"];
					$heure_depart_trou=$record["heure_depart"];
					for ($i = $record["trou_depart"]-1;$i < $nombre_trous; $i++)
					{
						if ( $i==$record["trou_depart"]-1)
						{	$heure_depart_trou=$heure_depart_trou;
						$tableaudepart[$i]="<td class=\"golfgg\" style=\"background: red\" ><b>".$heure_depart_trou["hours"].":".$heure_depart_trou["minutes"]."</b></td>"
						;}
						else {$heure_depart_trou=$this->addtime($heure_depart_trou, $record_trous[$i-1]["temps_de_jeu"]);
						$tableaudepart[$i]="<td class=\"golfgg\">".$heure_depart_trou["hours"].":".$heure_depart_trou["minutes"]."</td>";}
					}
						
					if ($record["trou_depart"]!="1")
					{
						for ($i = 0;$i < $record["trou_depart"]-1; $i++)
						{
							($i==0) ?  $heure_depart_trou=$this->addtime($heure_depart_trou, $record_trous[$nombre_trous-1]["temps_de_jeu"]) :
							$heure_depart_trou=$this->addtime($heure_depart_trou, $record_trous[$i-1]["temps_de_jeu"]);
							$tableaudepart[$i]="<td class=\"golfgg\">".$heure_depart_trou["hours"].":".$heure_depart_trou["minutes"]."</td>";
						}
					}

					$tableautrous.="<tr style=\"background: transparent\"><td class=\"golfgg\">Heure départ</td>";

					for ($i = 0; $i < 9; $i++)
					{ $tableautrous.=$tableaudepart[$i];       	       }
					$tableautrous.="<td class=\"golfgg\"></td>";
					for ($i = 9; $i < $nombre_trous; $i++)
					{$tableautrous.=$tableaudepart[$i];       	     	       }
					$tableautrous.="<td class=\"golfgg\"></td>";
					$tableautrous.="<td class=\"golfgg\"></td>";
					$tableautrous.="</tr>";

					$tableautrous.="</table>";
					/*

					`index_avant`,
					`handicap`,
					`par`,
					`score_brut`,
					`stableford`,
					`ssj` ,
					`net_corrige`,
					`index_apres`,

					Trou :
					`id`,
					`id_carte`,
					`id_trou`,
					`numero_trou`,
					`couleur`,
					`distance` ,
					`coups_recus` ,
					`coups_donnes`,
					`par`,
					`par_net`,
					`score_brut`,
					`coup_nomme` ,
					`stableford`,

					*/

					$tableautrous.="</b>Index initial = <b>".$recs[0]["index_avant"]."</b>, score brut = <b>".$recs[0]["score_brut"]."</b>, stableford_net = <b>".$recs[0]["stableford"]."</b>, stableford_brut = <b>".$recs[0]["stableford_brut"]."</b>, ssj = <b>".$recs[0]["ssj"]
					."</b>, net corrigé = <b>".$recs[0]["net_corrige"]."</b>, nouvel index = <b>".$recs[0]["index_apres"]."<br/>";


					($recs[0]["eagle_et_moins"]>0) ? $performance.="<b>".$recs[0]["eagle_et_moins"]."</b> eagle, " : null;
					($recs[0]["birdie"]>0) ? $performance.="<b>".$recs[0]["birdie"]."</b> birdy, " : null;
					($recs[0]["pars"]>0) ? $performance.="<b>".$recs[0]["pars"]."</b> par, " : null;
					($recs[0]["bogey"]>0) ? $performance.="<b>".$recs[0]["bogey"]."</b> bogey, " : null;
					($recs[0]["double_bogey"]>0) ? $performance.="<b>".$recs[0]["double_bogey"]."</b> double bogey, " : null;
					($recs[0]["triple_bogey_et_plus"]>0) ? $performance.="<b>".$recs[0]["triple_bogey_et_plus"]."</b> triple bogey, " : null;
					($golf_les_cartes_o_n=="o") ? $tableautrous.="<br/><b>Signature joueur : </b>".
"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;".
 "<b>Signature marqueur : </b><br/><br/>": null;
					if ($performance !="")
					{
						$performance=substr($performance, 0,strlen($performance)-2);

					}

					$tableautrous.=$performance;
					($recs[0]["eagle_et_moins"]>0 || $recs[0]["birdie"]>0 || $recs[0]["pars"]>0 || $recs[0]["bogey"]>0 || $recs[0]["double_bogey"]>0 || $recs[0]["triple_bogey_et_plus"]>0) ? $tableautrous.="<br/>" : null;

			}

					$retour.=$tableautrous;
					
			
					if ($golf_les_cartes_o_n=="n") {$retour.=' '.$this->descripteur_aide('Descripteur_carte_golf','n') ;}
					return $retour;
		}
	}
	function addtime($base,$temps)
	{
		$base["hours"]+=$temps["hours"];
		$base["minutes"]+=$temps["minutes"];
		if ($base["minutes"]>59)
		{$minutes=$base["minutes"];
		$base["minutes"]=$base["minutes"]%60;
		$base["hours"]+=($minutes-$base["minutes"])/60;
		}
		$base["minutes"]=str_pad($base["minutes"], 2, "0", STR_PAD_LEFT);
		return $base;

	}


	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		$categorynode = &atkGetNode("table.categorie_golf");
		$recs = $categorynode->selectDb("type_categorie_golf.id=".$record["id_type_categorie_golf"]["id"]);
		$retour.="<br/>".$categorynode->descriptor($recs[0]);
		return $retour;
	}
	/*function id_organisme_parcours_display($record, $mode) {
	 (!empty($record["id_organisme_parcours"])) ? $retour=$this->descripteur_organisme($record["id_organisme_parcours"]["id"],'n') : $retour="";
	 return $retour;
	 }
	 */
	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);
		$mraactions['maj_index_golf'] = "maj_index_golf";
		$mraactions['delete'] = "delete";
		$mraactions['maj_depart'] = "maj_depart";
		$mraactions['maj_scores_trous'] = "maj_scores_trous";
		
		$mraactions['maj_scores_stableford'] = "maj_scores_stableford";
		


	}



	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_carte_golf
			where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	function action_maj_index_golf()
	{
		$tableau=$this->get_row_selection_information(false);
		$url='http://www.ffgolf.org/ajax/$flashIndex$.aspx?num_lic=';
		$licence="48832192";
		$url.=$licence;
		$result=$this->curlFetchURL($url);
		$this->p($result);

		/*
		 * 	$_url = sprintf('http://%s/maps/geo?&q=%s&output=csv&key=%s', $this->lookup_server['GOOGLE'], rawurlencode($address), $this->api_key);
		 * http://www.ffgolf.org/ajax/$flashIndex$.aspx?num_lic=214541541

		 $_result = false;

		 if ($_result = $this->curlFetchURL($url))) {

		 $_result_parts = explode(',', $_result);
		 if ($_result_parts[0] != 200)
		 return false;
		 $_coords['lat'] = $_result_parts[2];
		 $_coords['lon'] = $_result_parts[3];
		 }

		 */


	}


}
?>
