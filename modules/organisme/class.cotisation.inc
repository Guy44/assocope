<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
require (atkconfig("atkroot")."modules/GChartPhp/gChart.php");
include (atkconfig("atkroot")."modules/GChartPhp/tableExtractor.class.php");
include (atkconfig("atkroot")."modules/GChartPhp/phpDump.class.php");
class NombreDeCotisations extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	//function storageType() {return NOSTORE;}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT COUNT(i.id) as nombredecotisations FROM individu_cotisation i, organisme_cotisation o
		  where o.id='" . $record["id"] . "' and o.id=i.id_cotisation");
		$record["nombre_de_cotisations"]= $rows[0]["nombredecotisations"];

		return $record["nombre_de_cotisations"];
	}

}
class TotalCotisations extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	//function storageType() {return NOSTORE;}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT COUNT(i.id) as nombredecotisations FROM individu_cotisation i, organisme_cotisation o
		  where o.id='" . $record["id"] . "' and o.id=i.id_cotisation");
		$totalcotisations = $rows[0]["nombredecotisations"];
		$rows = $db->getrows("SELECT montant FROM organisme_cotisation o
		  where o.id='" . $record["id"] . "' ");
		$totalcotisations = $totalcotisations * $rows[0]["montant"];
		return $totalcotisations;
	}
}
class TotalVersements extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	//function storageType() {return NOSTORE;}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(i.montant_versement) as totalversements FROM individu_cotisation i, organisme_cotisation o
		  where o.id='" . $record["id"] . "' and o.id=i.id_cotisation");
		return $rows[0]["totalversements"];
	}
}
class TotalDons extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	//function storageType() {return NOSTORE;}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(i.montant_versement) as totalversements FROM individu_cotisation i, organisme_cotisation o
		  where o.id='" . $record["id"] . "' and o.id=i.id_cotisation");
		$versements = $rows[0]["totalversements"];
		$rows = $db->getrows("SELECT COUNT(i.id) as nombredecotisations FROM individu_cotisation i, organisme_cotisation o
		  where o.id='" . $record["id"] . "' and o.id=i.id_cotisation");
		$totalcotisations = $rows[0]["nombredecotisations"];
		$rows = $db->getrows("SELECT montant FROM organisme_cotisation o
		  where o.id='" . $record["id"] . "' ");
		$totalcotisations = $totalcotisations * $rows[0]["montant"];
		$dons = $versements - $totalcotisations;
		return $dons;
	}
}
class cotisation extends assMetaNode {
	var $table = "organisme_cotisation";
	function meta(& $policy) {
		$policy->addFlags("libelle", "code", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function cotisation() {
		$this->atkMetaNode();
		$this->atkNode("cotisation",  NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array ("id",
						"id_organisme",
						"descripteur_cotisation_organisme",
						"descripteur_stats",
						"libelle",
						"annee",
						"montant",
						"montant_1",
						"montant_2",
						"montant_3",
						"nombre_de_cotisations",
						"total_des_cotisations",
						"total_des_versements",
						"total_des_dons",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Cotisants" => array (
						"cotisations"
				),
					
		), AF_NO_LABEL));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE |AF_FORCE_LOAD),null,9);
		$this->add(new atkOneToManyRelation("cotisations", "individu.cotisation_i", "id_cotisation", AF_HIDE_LIST|AF_FORCE_LOAD));
		$this->add(new atkDummyAttribute("descripteur_cotisation_organisme",0,AF_COMPACT),NULL, 6);
		$this->add(new atkDummyAttribute("descripteur_stats",0,AF_COMPACT),NULL, 7);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_FORCE_LOAD));
		$this->add(new atkNumberAttribute("annee" ,AF_FORCE_LOAD), NULL, 9);


		$this->add(new NombreDeCotisations("nombre_de_cotisations",AF_FORCE_LOAD), NULL, 10);
		$this->add(new TotalCotisations("total_des_cotisations", AF_FORCE_LOAD), NULL, 30);
		$this->add(new TotalVersements("total_des_versements",AF_FORCE_LOAD), NULL, 20);
		$this->add(new TotalDons("total_des_dons",AF_FORCE_LOAD), NULL, 40);
		$this->add(new atkDummyAttribute("stats_cotisations", "Statistiques", AF_DUMMY_SHOW_LABEL| AF_COMPACT), NULL, 8);
		$this->add(new atkDummyAttribute("stats_cotisations_graphique", "Graphique", AF_COMPACT), NULL, 9);
		$this->m_securityMap["liste_organismes_cotisants"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,10 );
		$this->setOrder(" annee DESC ");
		//		$this->setIndex("libelle");
	}
	function nombre_de_cotisations_display($record, $mode) {
		//if ($record["nombre_de_cotisations"]>0)
		{        return href(dispatch_url("individu.cotisation_i",
				"admin",
				array('atkfilter'=>"individu_cotisation.id_cotisation=".$record['id'].""), "dispatch.php"),
				text($record["nombre_de_cotisations"]), SESSION_NESTED);
		}
		//    	else
		//    	{    	return "";    }
	}

	function descripteur_stats_display($record, $mode) {
		//if ($record["nombre_de_cotisations"]>0)
		{       $retour.="</b>Nombre de cotisations : <b>".href(dispatch_url("individu.cotisation_i",
				"admin",
				array('atkfilter'=>"individu_cotisation.id_cotisation=".$record['id'].""), "dispatch.php"),
				text($record["nombre_de_cotisations"]), SESSION_NESTED);
			

		$retour.='<br /></b>Total des cotisations (théorique) : <b>'.str_replace(".00", "",$this->total_des_cotisations_display($record, $mode));
		$retour.='<br /></b>Total des versements : <b>'.str_replace(".00", "",$this->total_des_versements_display($record, $mode));
		$retour.='<br /></b>Total des dons : <b>'.str_replace(".00", "",$this->total_des_dons_display($record, $mode));
		return $retour;
		}
		//   	else return '';
	}


	function total_des_cotisations_display($record, $mode) {
		$attr = & $this->getAttribute("total_des_cotisations");
		$val = $attr->display($record, $mode); // call original display
		// now wrap the result in a right-aligned span:
		return '<span style="text-align: right;">' . $val . '</span>';
	}
	function total_des_versements_display($record, $mode) {
		$attr = & $this->getAttribute("total_des_versements");
		$val = $attr->display($record, $mode); // call original display
		// now wrap the result in a right-aligned span:
		return '<span style="text-align: right;">' . $val . '</span>';
	}
	function total_des_dons_display($record, $mode) {
		$attr = & $this->getAttribute("total_des_dons");
		$val = $attr->display($record, $mode); // call original display
		// now wrap the result in a right-aligned span:
		return '<span style="text-align: right;">' . $val . '</span>';
	}
	function descripteur_cotisation_organisme_display($record, $mode) {

		return $this->descripteur_cotisation_organisme($record["id"]);
	}

	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		$mraactions['exportations'] = "exportations";
		$mraactions['liste_organismes_cotisants'] = "liste_organismes_cotisants";

	}

	function action_exportations() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus, $idcotisations);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"idinscriptions" => $idcotisations,
				"atkcode" => '1',
				"atkexport" => 'o'
		));
		header("Location: $url");
		exit;
	}
	function action_liste_organismes_cotisants() {

		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idcotisations = substr($chaineid, 0, strlen($chaineid) - 1);

		$sql = "select distinct id_organisme_cotisant from individu_cotisation
		where id_cotisation in ($idcotisations)";

		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			if ($data[$i]["id_organisme_cotisant"]!="")
			{
				$chaineidorganisme .= $data[$i]["id_organisme_cotisant"] . ',';
			}

		}
		$idorganismes = substr($chaineidorganisme, 0, strlen($chaineidorganisme) - 1);
		if ($idorganismes=="")
		{
			return true;
		}
		$url = dispatch_url("organisme.organisme", "liste_organismes", array (
				"idorganismes" => $idorganismes,
				"atkcode" => 'liste_organismes',
				"atkexport" => 'n'
		));
		header("Location: $url");
		exit;
	}


	function traitement_select($select, & $idorganisme, & $idindividus, & $idcotisations) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_type = explode('=', $id_variable);
			$chaineidfonction .= $array_type[1] . ',';
		}

		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 1);
		$idcotisations = $chaineidfonction;
		$sql = 'select distinct id_individu, id_organisme from individu_cotisation
				where  id_cotisation in (' . $chaineidfonction . ')';

		$data = $db->getrows($sql);


		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
			$idorganisme=$data[$i]["id_organisme"];
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);

		return true;
	}
	function descriptor_def() {
		return " [libelle] ";
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
		function get_cotisation_ans_stats($record,$mode)
	{
		$arrayretour=array();
		$db = & atkGetDb();
		$annee_cotisation=$record["annee"];
		$id_organisme=$record["id_organisme"]["id"];
		$sql="SELECT o.annee, 
				COUNT( i.id ) AS nombredecotisations, 
				SUM( i.montant_versement ) AS montant_versement, 
				SUM( i.`montant_cotisation_organisme` ) AS montant_cotisation_organisme, 
				SUM( i.`montant_don` ) AS montant_don
	FROM individu_cotisation i, organisme_cotisation o
	WHERE o.id_organisme =$id_organisme
	AND o.annee <= $annee_cotisation
	AND o.annee >2006
	AND o.id = i.id_cotisation
	GROUP BY o.annee
	ORDER BY o.annee
				";
		$data = $db->getrows($sql);
		$data=$this->transpose($data);
		return $data;
		}
		/*
	 * 
	*/
	function get_cotisation_stats($record,$mode)
	{
		$arrayretour=array();
		$db = & atkGetDb();
		$id_cotisation=$record["id"];
		$this->getDatesReglements($record,$minimum, $maximum);
		$datecourante=$minimum;
		while ($datecourante<=$maximum)
		{
			$m=substr($datecourante, 4,3);
			$m=str_replace('-0', '-', $m);
			$m=str_replace('-', '', $m);
			$datedb=str_replace('-0', '-', $datecourante);
			$sql="SELECT YEAR(i.date_reglement ) as an, MONTH( i.date_reglement ) As mois, COUNT( i.id ) AS nombredecotisations,  sum(i.montant_versement) as montant_versement,
					sum(i.`montant_cotisation_organisme`) as montant_cotisation_organisme
					FROM individu_cotisation i, organisme_cotisation o
					WHERE CONCAT(YEAR(i.date_reglement),'-',MONTH(i.date_reglement))='".$datedb."'
					AND o.id =$id_cotisation
					AND o.id = i.id_cotisation";
			$data = $db->getrows($sql);
			($data[0]["mois"]=="")? $data[0]["mois"]=$m : null;
			$arrayretour[]=$data[0];
			$datecourante=$this->date_un_mois_add($datecourante);
		}
		$data=$this->transpose($arrayretour);
		return $data;
	}
	function get_titre_graphique($record)
	{
		$id_organisme=$record["id_organisme"]["id"];
		$id_type_cotisation=$record["id"];
		$db = & atkGetDb();
		$data = $db->getrows(" select nom from organisme where id=$id_organisme");

		$retour.= "Cotisations - ".$data[0]["nom"]." - ".$record["annee"];
		return $retour;
	}

	function stats_cotisations_display(&$record, $mode)
	{
		$titre=$this->get_titre_graphique($record);
		$data=$this->get_cotisation_stats($record, $mode);
		$res = $titre."<table border='1'>";
		$res .= "<tr><td class='styletitre'>Mois";
		$count=count($data["mois"]);
		for ($i=0; $i<$count; $i++)
		{
			$res.='</td><td>'.'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">'.$data["mois"][$i].'</p>';
		}
		$res .= "</td></tr><tr><td class='styletitre'>Nombre";
		$count=count($data["nombredecotisations"]);
		$somme=0;
		for ($i=0; $i<$count; $i++)
		{
		//	$somme+=$data["nombredecotisations"][$i];
		//	$res.='</td><td>'.$somme;
			$lien=href(dispatch_url("individu.cotisation_i", "admin", array (
					'atkfilter' => "
				 individu_cotisation.id_cotisation =". $record['id']
					." and YEAR(individu_cotisation.date_reglement)=".$data["an"][$i]
					." and MONTH(individu_cotisation.date_reglement)=".$data["mois"][$i]
			), "dispatch.php"), $this->nombre_format($data["nombredecotisations"][$i],"b") , SESSION_NESTED);
	
			$res.='</td><td>'.$lien;
		}
		$res .= "</td></tr><tr><td class='styletitre'>Cotisations cumulées";
		$count=count($data["montant_cotisation_organisme"]);
		$somme=0;
		for ($i=0; $i<$count; $i++)
		{
			$somme+=$data["montant_cotisation_organisme"][$i];
			$res.='</td><td>'.$this->nombre_format($somme,"b");
		}
		$res .= "</td></tr><tr><td class='styletitre'>Versements cumulés";
		$count=count($data["montant_versement"]);
		$somme=0;
		for ($i=0; $i<$count; $i++)
		{
			$somme+=$data["montant_versement"][$i];
			$res.='</td><td>'.$this->nombre_format($somme,"b");
		}
		$res.='</td></tr></table>';
		
		
		$data_ans=$this->get_cotisation_ans_stats($record,$mode);
	//	$this->p($data_ans);
		$count=count($data_ans["annee"]);
		$titre_ans="Cotisations de ".$data_ans["annee"][0]." à ".$data_ans["annee"][$count-1];
		$res_ans = $titre_ans."<table border='1'>";
		$res_ans .= "<tr><td class='styletitre'>Année";

		for ($i=0; $i<$count; $i++)
		{
		$res_ans.='</td><td>'.'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">'.$data_ans["annee"][$i].'</p>';
		}
		$res_ans .= "</td></tr><tr><td class='styletitre'>Nombre";
		$count=count($data_ans["nombredecotisations"]);
		for ($i=0; $i<$count; $i++)
		{
			$lien=href(dispatch_url("individu.cotisation_i", "admin", array (
					'atkfilter' => "
				 individu_cotisation.id_cotisation =". $record['id']
					." and YEAR(individu_cotisation.date_reglement)=".$data_ans["annee"][$i]
			), "dispatch.php"), $this->nombre_format($data_ans["nombredecotisations"][$i],"b") , SESSION_NESTED);
			$res_ans.='</td><td>'.$lien;
		}
		$res_ans .= "</td></tr><tr><td class='styletitre'>Cotisations";
		$count=count($data_ans["montant_cotisation_organisme"]);
		$somme=0;
				for ($i=0; $i<$count; $i++)
				{
			$res_ans.='</td><td>'.$this->nombre_format($data_ans["montant_cotisation_organisme"][$i],"b");
		}
		$res_ans .= "</td></tr><tr><td class='styletitre'>Versements";
		$count=count($data_ans["montant_versement"]);
		$somme=0;
						for ($i=0; $i<$count; $i++)
						{
			$res_ans.='</td><td>'.$this->nombre_format($data_ans["montant_versement"][$i],"b");
		}
		$res_ans .= "</td></tr><tr><td class='styletitre'>Dons";
		$count=count($data_ans["montant_don"]);
		$somme=0;
		for ($i=0; $i<$count; $i++)
		{
			$res_ans.='</td><td>'.$this->nombre_format($data_ans["montant_don"][$i],"b");
		}
		
				$res_ans.='</td></tr></table>'.$this->getUserStamp('n','o');

		$record["graphique"]=$this->afficheGraphique($res,$titre,2,50);
		$record["graphique"].="<br/>".$this->afficheGraphique($res_ans,$titre_ans,2,20);
		
		return $res."<br/>".$res_ans;

	}

	function getDatesReglements($record,&$minimum, &$maximum)
	{
		// adhésions
		$id_type_cotisation = $record["id"];
		$db = & atkGetDb();
		$data = $db->getrows("select min(date_reglement) as date_reglement_minimum, max(date_reglement) as date_reglement_maximum from individu_cotisation
				where id_cotisation =$id_type_cotisation");
		$minimum=substr($data[0]["date_reglement_minimum"], 0,7);
		$maximum=substr($data[0]["date_reglement_maximum"], 0,7);
		return true;

	}
	function stats_cotisations_graphique_display($record, $mode)
	{
		//					$this->p($record);
		return $record["graphique"];
	}

}
?>