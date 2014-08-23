<?php
useattrib("development.atgomanytoonerelation");
class fonction_i extends assMetaNode {
	var $table = "individu_fonction";
	function meta(& $policy) {
		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function fonction_i() {
		$this->atkMetaNode();
		$this->atkNode("fonction_i",  NF_ADD_LINK | NF_TRACK_CHANGES  |NF_ADDAFTERADD | NF_MRA | NF_COMPACT);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkDummyAttribute("descripteur_fonction", "Descripteur fonction", AF_DUMMY_SHOW_LABEL | AF_COMPACT), NULL, 5);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),100);

		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),110);
		$this->add(new atkManyToOneRelation("id_fonction", "table.fonction", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK| AF_FORCE_LOAD),120);
		$this->add(new atgOManyToOneRelation("id_organisme_represente", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),130);
		$this->add(new atkDateAttribute("date_debut", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),140);
		$this->add(new atkDateAttribute("date_echeance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),150);
		$this->add(new atkDateAttribute("date_fin", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_FORCE_LOAD),160);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,6 );
		$this->setOrder("individu_fonction.id_individu asc, individu_fonction.date_creation DESC");
		$this->m_securityMap["liste_organismes_representes"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		global $ATK_VARS, $g_user;
		if ($ATK_VARS["atknodetype"] == "individu.fonction_i" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
		))) {
			if ($this->getView() == "active") {
				$this->addFilter("(date_fin IS NULL or date_fin='00-00-0000' )");
			}
		}
		//$this->setIndex("libelle");
	}
	// GG deb
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
	function descripteur_fonction_display($record, $mode) {
		return $this->descripteur_fonction($record["id"]);
	}

	function rowColor($record) {
		$date_fin = $record["date_fin"];
		if ($date_fin != "")
			return $this->couleurarchive;
	}
	function descriptor_def() {
		return "[id]";
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_represente_display($record, $mode) {
		(!empty($record["id_organisme_represente"])) ? $retour=$this->descripteur_organisme($record["id_organisme_represente"]["id"],'n') : $retour="";
		return $retour;
	}


	function action_delete() {
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$condition=$this->m_postvars["atkselector"];
		$data=$db->getrows("select date_fin from individu_fonction where $condition");
		if (empty($data[0]["date_fin"]))
		{

			$sql="update individu_fonction set
			date_fin= UTC_TIMESTAMP() ,
			id_modification=  $userid,
			date_modification= UTC_TIMESTAMP()
			where $condition and date_fin is NULL ";
			$db->query($sql);
			$db->commit();
		}
		else
		{ $db->query("delete from individu_fonction where $condition");
		}
		$this->redirect();
	}

	function action_admin($handler) {
		$view = $this->getView();
		if ($view == "active") {
			$this->addFilter("(date_fin IS NULL or date_fin='00-00-0000' )");
		}
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende='Légende des couleurs : ';
		$legende.='<font color="'. $this->couleurarchive.'"> <b> Archive ';
		if ($view=="active")
		{
			return atktext("onlyactiverecordsareshown")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
					'&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type))."<br>"
							.$legende.$retour;
			;
		}
		else
		{
			return atktext("youareinthearchive")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
					'&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type))."<br>"
							.$legende.$retour;
			;
		}
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		$mraactions['liste_organismes_representes'] = "liste_organismes_representes";
		$mraactions['delete'] = "delete";
	}
	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_fonction
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	function action_liste_organismes_representes() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);
			$chaineid.=$array_id[1] . ',';

		}
		$idfonctions = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_organisme_represente from individu_fonction
				where  id in (' . $idfonctions . ')';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			if ($data[$i]["id_organisme_represente"]!="")
			{
				$chaineidorganisme .= $data[$i]["id_organisme_represente"] . ',';
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
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("individu_fonction", "ifo", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		ifo.id	as id_entite,
		ifo.id_individu as id_individu,
		tf.libelle as libelle_fonction,
		ifo.date_debut,
		ifo.date_echeance,
		ifo.date_fin,
		o.id as id_organisme,
		o.nom as organisme
		from
		individu_fonction ifo LEFT JOIN individu i ON ifo.id_individu=i.id
		LEFT JOIN type_fonction tf ON ifo.id_fonction=tf.id
		LEFT JOIN organisme o ON ifo.id_organisme=o.id
		where
		$filtre
		order by i.nom, i.prenom, ifo.date_debut	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Nom</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contact</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Naissance</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Début</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Echéance</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Fin</center></b>';
//		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Décès</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$idindividus.=$data[$i]["id_individu"].",";
			$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
			$res2.= "<tr><td>".($i+1);
			$res2.='</td><td>'.$data[$i]["libelle_fonction"];
			$res2.='</td><td>'.$arrayIndividu["nom"];
			$res2.='</td><td>'.$arrayIndividu["contacts"];
			$res2.='</td><td>'.$arrayIndividu["date_naissance"];
			$res2.='</td><td>'.$data[$i]["date_debut"];
			$res2.='</td><td>'.$data[$i]["date_echeance"];
			$res2.='</td><td>'.$data[$i]["date_fin"];
//			$res2.='</td><td>'.$arrayIndividu["date_deces"];
			$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
			$res2.='</td></tr>';
		}
		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Fonctions"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);
		
	}


}
?>