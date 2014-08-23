<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
class ligne_ecriture_comptable extends assMetaNode {
	var $table = "organisme_ligne_ecriture_comptable";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("debit", "credit", AF_TOTAL);
	}
	function ligne_ecriture_comptable() {
		$this->atkMetaNode();
		$this->atkNode("ligne_ecriture_comptable", NF_ADD_LINK | NF_MRA |NF_ADDAFTERADD | NF_COMPACT_NULL );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"descripteur_ligne_ecriture_comptable",
						"id_ecriture",
						"debit",
						"credit",
						"date_reglement",
						"date_operation",
						"date_valeur",
						"id_journal",
						"id_organisme",
						"ecriture",
						"id_compte",
						"id_individu",
						"id_type_reglement",
						"numero_piece",

						"id_type_banque",
						"id_remise",
						"id_releve",

						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_ligne_ecriture_comptable",0,AF_COMPACT),NULL, 4);
		$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_SEARCHABLE|AF_FORCE_LOAD),56);
		$this->add(new atkDateAttribute("date_operation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_SEARCHABLE|AF_FORCE_LOAD),57);
		$this->add(new atkDateAttribute("date_valeur", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_SEARCHABLE),58);
		$this->add(new atkNumberAttribute("debit",AF_TOTAL | AF_SEARCHABLE, 10, 2),54);
		$this->add(new atkNumberAttribute("credit", AF_TOTAL | AF_SEARCHABLE, 10, 2),55);
		$this->add(new atkAttribute("numero_piece", AF_SEARCHABLE|AF_FORCE_LOAD));
		$this->add(new atkAttribute("id_remise", AF_SEARCHABLE|AF_FORCE_LOAD));
		$this->add(new atkAttribute("id_releve", AF_SEARCHABLE|AF_FORCE_LOAD));
		$organisme = $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_READONLY | AF_SEARCHABLE|AF_FORCE_LOAD));
		//	$organisme->addDependee("id_compte");
		//	$organisme->addDependee("id_journal");
		$compte = $this->add(new atkManyToOneRelation("id_compte", "organisme.compte", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		$journal = $this->add(new atkManyToOneRelation("id_journal", "organisme.journal_comptable", AF_READONLY | AF_SEARCHABLE|AF_FORCE_LOAD));
		$compte->addDestinationFilter("id_organisme= '[id_organisme.id]' and usuel='1'");
		//		$journal->addDestinationFilter("id_organisme= '[id_organisme.id]' ");
		$this->add(new atkExpressionAttribute("ecriture", ' select libelle from organisme_ecriture_comptable e
				where e.id = [table].id_ecriture
				', 0, 0),50);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));

		$this->m_securityMap["pointer"] = "view";
		$this->m_securityMap["depointer"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
		$this->setOrder("id desc");
	}
	function id_ecriture_display ($record)
	{
		if ($record["id_ecriture"] > 0) {
			$url = href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					"atkfilter" => " organisme_ligne_ecriture_comptable.id_ecriture='" . $record["id_ecriture"] . "'"
			)), atktext($record["id_ecriture"] ."<br>", "core"), SESSION_NEW, false, 'target="_blank"');
		} else {
			$url='';
		}
		return $url;
	}

	function descriptor_def() {
		return "[commentaire]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		return $handler->action_admin();
	}

	function initial_values() {
		$init_vals = array ();
		$ecriture = explode('=', $this->m_postvars['atkfilter']);
		if ($ecriture[0] == 'id_ecriture') {
			$id_ecriture = $ecriture[1];
			$db = & atkGetDb();
			$data = $db->getrows("SELECT e.id_organisme, e.id_journal, DAYOFMONTH(e.date_ecriture) as jour,
			  YEAR(e.date_ecriture) as an,
					MONTH(e.date_ecriture) as mois
					FROM organisme_ecriture_comptable e where e.id=$id_ecriture");
			$init_vals["id_organisme"] = $data[0]["id_organisme"];
			$init_vals["id_journal"] = $data[0]["id_journal"];
			$init_vals["debit"] = 0;
			$init_vals["credit"] = 0;
			$init_vals["date_operation"]["day"] = $data[0]["jour"];
			$init_vals["date_operation"]["month"] = $data[0]["mois"];
			$init_vals["date_operation"]["year"] = $data[0]["an"];
			$init_vals["date_valeur"]["day"] = $data[0]["jour"];
			$init_vals["date_valeur"]["month"] = $data[0]["mois"];
			$init_vals["date_valeur"]["year"] = $data[0]["an"];
			//       print_r ($init_vals);
			//       die();
		} else {
			echo "L'ajout de ligne d'écriture n'est possible qu'à partir de la sélection d'une écriture.";
			die();
		}
		return $init_vals;
	}
	function debit_validate($record) {
		if (empty ($record["debit"])) {
			$record["debit"] = 0;
		}
		if (empty ($record["credit"])) {
			$record["credit"] = 0;
		}
		if (empty ($record["debit"]) and empty ($record["credit"])) {
			triggerError($record, "debit", "erreur_:_débit et crédit ne peuvent pas être nuls");
		}
		return true;
	}
	function preAdd(& $record) {
		// atk_var_dump($record);
		$id_ecriture = $record['id_ecriture'];
		$db = & atkGetDb();

		$data = $db->getrows("SELECT id_organisme, id_journal  FROM organisme_ecriture_comptable where id=$id_ecriture ");
		$id_journal = $data[0]["id_journal"];
		$id_organisme = $data[0]["id_organisme"];
		$record["id_organisme"]["id"] = "$id_organisme";
		$record["id_journal"]["id"] = "$id_journal";
		parent :: preAdd($record);
	}
	function preDelete(& $record) {
		if ($record["id_releve"]>0)
		{
			echo "Suppression impossible. Cette ligne d'écriture a été rapprochée.";
			die();
		}
		if ($record["id_remise"]>0)
		{
			echo "Suppression impossible. Cette ligne d'écriture a été remisée en banque.";
			die();
		}
		parent :: preDelete($record);
	}
	function recordActions($rec, & $actions, & $mraactions) {
		// parent :: recordActions($rec, $actions, $mraactions);
		$mraactions['pointer'] = "pointer";
		$mraactions['depointer'] = "depointer";
	}
	function action_pointer() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		foreach ($select as $id_variable) {
			$array_1 = explode('=', $id_variable);
			$chaineidfonction .= $array_1[1] . ',';
		}
		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 1);
		$db = & atkGetDb();
		$record = $db->getrows("SELECT count(id_remise)as nombre
				FROM organisme_ligne_ecriture_comptable
				where id in (" . $chaineidfonction . ")");
		if($record[0]["nombre"]!=0)
		{
			echo "Une ligne d'écriture fait partie d'une remise. Il faut alors pointer la remise et non la ligne d'écriture";
			die();
		}
		$db = & atkGetDb();
		$record = $db->getrows("SELECT id_organisme, id_compte
				FROM organisme_ligne_ecriture_comptable
				where id in (" . $chaineidfonction . ")");
		$id_organisme = $record[0]["id_organisme"];
		$id_compte_banque = $record[0]["id_compte"];
		$record = $db->getrows("SELECT max(id) as idmax from organisme_releve_banque where
				id_organisme =$id_organisme and date_cloture_releve is null and id_compte_banque=$id_compte_banque");
		$id_releve = $record[0]["idmax"];
		if (empty ($id_releve)) {
			return;
		}
		$sql = 'update organisme_ligne_ecriture_comptable set id_releve=' . $id_releve . '
				where id in (' . $chaineidfonction . ')';
		$db->query($sql);
		$this->redirect();
	}
	function action_depointer() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		foreach ($select as $id_variable) {
			$array_1 = explode('=', $id_variable);
			$chaineidfonction .= $array_1[1] . ',';
		}
		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 1);

		$db = & atkGetDb();
		$sql = 'update organisme_ligne_ecriture_comptable set id_releve=null
				where id in (' . $chaineidfonction . ')and id_releve is not null and id_releve in (select id from organisme_releve_banque where date_cloture_releve is null)';
		$db->query($sql);
		$this->redirect();
	}
	function rowColor($record) {
		$idreleve=$record["id_releve"];
		$idremise=$record["id_remise"];
		$retour='';
		/* if (isset($idremise))
		 {
		$t1=isset($idremise);
		$t2=isset($idreleve);
		$t3=isset($idreleve,$idremise);
		echo 't1'.$t1.'t2'.$t2.'t3'.$t3;
		die();
		}
		*/
		if ($idremise>0)
		{
			$retour="orange";
		}
		if ($idreleve>0)
		{
			$retour="lightgreen";
		}
		if ($idreleve>0 && $idremise>0)
		{
			$retour="green";
		}
		return $retour;
	}


	function adminFooter() {
		$retour=parent::adminfooter();

		$legende = 'Légende des couleurs : 	<b> Ecriture à rapprocher.  ';
		$legende .= '<font color="orange"> <b> Ecriture à rapprocher et ayant été remise en banque. ';
		$legende .= '<font color="lightgreen"> <b> Ecriture rapprochée ne faisant pas partie d\'une remise. ';
		$legende .= '<font color="green"> <b> Ecriture rapprochée et ayant fait partie d\'une remise en banque. ';
			
		return $legende;
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function descripteur_ligne_ecriture_comptable_display($record, $mode) {

		//	return "<b>".$record["ecriture"]."</br>".$this->descripteur_ligne_ecriture_comptable($record["id"],'o');
		return $this->descripteur_ligne_ecriture_comptable($record["id"],'o');
	}
	function action_admin_liste($type="", $id_releve_remise="", $id_organisme="") {
		$db = & atkGetDb();
		if ($type=="remise")
		{
			$filtre=" lec.id_remise= $id_releve_remise";
				
		}
		else if ($type=="releve")
		{
			$filtre=" lec.id_releve= $id_releve_remise";
				
		}
		else
		{
			$type="lignes";
					$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_ligne_ecriture_comptable", "lec", $this->m_postvars["atkfilter"]);
		}

		$sql="SELECT
		lec.id as id_entite,
		oec.id as id_ecriture,
		oec.libelle as libelle_ecriture,
		oj.libelle as libelle_journal,
		oc.code,
		oc.libelle as libelle_compte,
		lec.id_individu,
		lec.id_organisme,
		tr.libelle as libelle_reglement,
		lec.numero_piece,
		lec.date_reglement,
		lec.date_operation,
		lec.date_valeur,
		tb.libelle as libelle_banque,
		lec.id_remise,
		lec.id_releve,
		lec.debit,
		lec.credit,
		o.nom as organisme
		from
		organisme_ligne_ecriture_comptable lec
		LEFT JOIN organisme_compte oc ON lec.id_compte=oc.id
		LEFT JOIN organisme_journal_comptable oj ON lec.id_journal=oj.id
		LEFT JOIN organisme_ecriture_comptable  oec ON lec.id_ecriture=oec.id
		LEFT JOIN type_reglement  tr ON lec.id_type_reglement=tr.id
		LEFT JOIN type_banque  tb ON lec.id_type_banque=tb.id
		LEFT JOIN organisme o ON lec.id_organisme=o.id
		where
		$filtre
		order by lec.date_operation ";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Ligne</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Ecriture</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Opération</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Débit</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Crédit</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Compte</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Individu</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Organisme</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Règlé le</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Règlement</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Banque</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Pièce</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Valeur</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Remise</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Relevé</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			if ($data[$i]["id_individu"]!="")
			{
				$idindividus.=$data[$i]["id_individu"].",";
				$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
			}
			$res2.= "<tr><td>".($i+1);
			$res2.='</td><td>'.$data[$i]["id"];
			$href=dispatch_url("table.type_ecriture", "admin_liste", array(
					"id_ecriture" => $data[$i]["id_ecriture"],
					"id_organisme" => $id_organisme
			)
					, "dispatch.php");
			$lien="<a href=\"".$href."\"> (Voir le contexte)</a>";
			$res2.='</td><td><b>'.$data[$i]["libelle_ecriture"]."</b><br/>
					Ecriture : <b>".$data[$i]["id_ecriture"]."$lien</b><br/>
					Journal : <b>".$data[$i]["libelle_journal"]."</b><br/>";
			$res2.='</td><td><b>'.$data[$i]["date_operation"]."</b>";
			$res2.='</td><td>'.$this->nombre_format($data[$i]["debit"],"b",2);
			$res2.='</td><td>'.$this->nombre_format($data[$i]["credit"],"b",2);
			$res2.='</td><td>'.$data[$i]["code"]." ".$data[$i]["libelle_compte"];
			$res2.='</td><td>'.$this->descripteur_individu_sans_lien($data[$i]["id_individu"]);
			$res2.='</td><td>'.$this->descripteur_organisme_sans_lien($data[$i]["id_organisme"]);
			$res2.='</td><td>'.$data[$i]["date_reglement"];
			$res2.='</td><td>'.$data[$i]["libelle_reglement"];
			$res2.='</td><td>'.$data[$i]["libelle_banque"];
			$res2.='</td><td>'.$data[$i]["numero_piece"];
			$res2.='</td><td>'.$data[$i]["date_valeur"];
			$href=dispatch_url("organisme.remise_banque", "admin_liste", array(
					"id_remise_banque" => $data[$i]["id_remise"],
					"id_organisme" => $id_organisme
			), "dispatch.php");
			$res2.='</td><td>'."<a href=\"".$href."\"><b>". $data[$i]["id_remise"]."</b></a>";
			$href=dispatch_url("organisme.releve_banque", "admin_liste", array(
					"id_releve_banque" => $data[$i]["id_releve"],
					"id_organisme" => $id_organisme
			), "dispatch.php");
			$res2.='</td><td>'."<a href=\"".$href."\"><b>". $data[$i]["id_releve"]."</b></a>";
			$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
			$res2.='</td></tr>';
		}
		
		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
($type=="remise" || $type=="releve") ? $titre="" : null;

		($type=="lignes") ?$titre="<h2><b>"."Lignes d'écritures"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>": null;
		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
	//	echo $type;
	//	die();
		
		if ($type!="lignes") 
		{return $res2;}
		 else 

		{
		$this->page_output($res2);}

	}


}
?>