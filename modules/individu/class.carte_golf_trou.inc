<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");

class carte_golf_trou extends assMetaNode {
	var $table = "individu_carte_trou_golf";
	function meta(& $policy) {
		// $policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function carte_golf_trou() {
		$this->atkMetaNode();
		$this->atkNode("carte_golf_trou",  NF_ADD_LINK | NF_TRACK_CHANGES| NF_ADDAFTERADD| NF_MRA );
		$this->setSecurityAlias("individu.individu");
		$this->m_securityMap["viewprintable"] = "view";

		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_carte",
				"id_trou",
				"numero_trou",
		"score_brut",
				"couleur",
				"distance",
				"coups_recus",
				"coups_donnes",
				"par",
				"par_net",

				"coup_nomme",
				"stableford",
		"stableford_brut"
				),
			"Performances" => array (
				"numero_trou",
				"par",
				"dl_depart",
				"dl_second_coup",
				"dl_troisieme_coup",
				"dl_pitch",
				"dl_chip",
				"dl_bunker",
				"dl_putts",
				"score_brut"
				)
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_carte", "individu.carte_golf", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK),null,150);
				$this->add(new atkManyToOneRelation("id_trou", "organisme.golf_parcours_trou", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK),null,155);
				$this->add(new atkNumberAttribute("numero_trou", AF_SEARCHABLE, 2, 0),null,50);
				$this->add(new atkAttribute("score_brut", AF_SEARCHABLE),null,60);
				$this->add(new atkAttribute("couleur", AF_SEARCHABLE));
				$this->add(new atkNumberAttribute("distance", AF_SEARCHABLE, 4, 0),null,80);
				$this->add(new atkNumberAttribute("coups_recus", AF_SEARCHABLE, 2, 0),null,90);
				$this->add(new atkNumberAttribute("coups_donnes", AF_SEARCHABLE, 2, 0),null,100);
				$this->add(new atkNumberAttribute("par", AF_SEARCHABLE, 2, 0),null,70);
				$this->add(new atkNumberAttribute("par_net", AF_SEARCHABLE, 2, 0));

				$this->add(new atkRadioAttribute("coup_nomme", array (
			"Eagle et -",
			"Birdie",
			"Par",
			"Bogey",
			"Double Bogey",
			"Triple Bogey et +"
			), array (
			'1',
			'2',
			'3',
			'4',
			'5',
			'6'
			), AF_SEARCHABLE));
			$this->add(new atkNumberAttribute("stableford", AF_SEARCHABLE, 2, 0),null,110);
			$this->add(new atkNumberAttribute("stableford_brut", AF_SEARCHABLE, 2, 0),null,120);
			$this->add(new atkAttribute("dl_depart", AF_SEARCHABLE));
			$this->add(new atkAttribute("dl_second_coup", AF_SEARCHABLE));
			$this->add(new atkAttribute("dl_troisieme_coup", AF_SEARCHABLE));
			$this->add(new atkAttribute("dl_pitch", AF_SEARCHABLE));
			$this->add(new atkAttribute("dl_chip", AF_SEARCHABLE));
			$this->add(new atkAttribute("dl_bunker", AF_SEARCHABLE));
			$this->add(new atkNumberAttribute("dl_putts", AF_SEARCHABLE, 1, 0));
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->m_securityMap["maj"] = "view";
			$this->setOrder(" numero_trou ASC ");
			//		$this->setIndex("libelle");
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['maj'] = "maj";
	}
	function action_maj() {
		$db = & atkGetDb();

		foreach ($this->m_postvars["atkselector"] as $value)
		{$idarray=explode("=",$value);
		$id=$idarray[1];
		$id=str_replace("'","",$id);
		$carte_trou_node = & getNode("individu.carte_golf_trou");
		$record=array();
		$recs=$carte_trou_node->selectDb("individu_carte_trou_golf.id=".$id);

		$record=$recs[0];
		$record["score_brut"]=$this->m_postvars["data"][$id]["score_brut"];
		//		$record['atkprimkey']="individu_carte_trou_golf.id=".$id;
		//		$this->p($record);
		($record["score_brut"]=="x" || $record["score_brut"]=="X" )  ? $record["score_brut"]=$record["par_net"]+2 :null;
		($record["score_brut"]=='0') ? $record["score_brut"]="" : null;
		$carte_trou_node->updateDb($record);
		$idcarte=$record["id_carte"]["id"];


		}
		$url=dispatch_url("individu.carte_golf", "resultats", array (
				"id_carte" =>$idcarte,
				"type"=> "détail"), "dispatch.php");
		$this->redirect($url);
//echo "c'est fait";
//die();

			
	}
public function score_brut_validate(&$record, $mode)
{ 
//$this->p($record);
($record["score_brut"]=="x" || $record["score_brut"]=="X" )  ? $record["score_brut"]=$record["par_net"]+2 :null;
    if ($record["score_brut"]!="X" && $record["score_brut"]!="" && $record["score_brut"]<1 ) {
        atkTriggerError($record, $this->getAttribute("score_brut"), "Valeur incorrecte pour un score : numérique ou 'X'");
    }
 
}

	function score_brut_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('score_brut')->display($record, $mode);
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('score_brut')->edit($record, $prefix, 'edit');
	}

/*	function preUpdate(& $record) {
		parent :: preUpdate($record);
		if ($record["score_brut"] > 0) {
			$record["stableford"] = - ($record["score_brut"] - $record["par_net"] - 2);
			$record["stableford_brut"] = - ($record["score_brut"] - $record["par"] - 2);
			if ($record["stableford"] < 0) {
				$record["stableford"] = 0;
			}
			if ($record["stableford_brut"] < 0) {
				$record["stableford_brut"] = 0;
			}
			$record["coup_nomme"] = ($record["score_brut"] - $record["par"] + 3);
			if ($record["coup_nomme"] < 1) {
				$record["coup_nomme"] = 1;
			}
			if ($record["coup_nomme"] > 6) {
				$record["coup_nomme"] = 6;
			}
		}

		if ($record["score_brut"] == 0 || $record["score_brut"] == 'X') {
			$record["stableford"] = '0';
			$record["stableford_brut"] = '0';
			$record["coup_nomme"] = 6;
		}
		// print_r ($record);
		// die();
		return true;
	}
	*/
	function descriptor_def() {
		return " [id] ";
	}


}
?>
