<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");
class compte extends assMetaNode {
	var $table = "organisme_compte";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function compte() {
		global $ATK_VARS;
		//		print_r ($ATK_VARS);
		//		die();
		if ($ATK_VARS['atkaction'] == "edit") {
			$ATK_VARS['atkfilter'] = '';
		}
		$this->atkMetaNode();
		$this->atkNode("compte", NF_ADDAFTERADD | NF_ADD_LINK| NF_MRA |NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"code",
						"libelle",
						"debit_initial",
						"credit_initial",
	/*					"debit_total",
						"credit_total",
						"solde_total",
						"solde_courant",
						"debit_2",
						"credit_2",
						"solde_2",
						"debit_1",
						"credit_1",
						"solde_1",
						"debit",
						"credit",
						"solde",
	*/
						"id_organisme",
						"usuel",
						"id_banque",
						"rib",
						"url_banque",
						"code_acces",
						"stats_comptes",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				)

		), AF_NO_LABEL));
		//		$this->add(new atkNumberAttribute("id", AF_PRIMARY | AF_HIDE | AF_FORCE_LOAD));
		$this->add(new atkAttribute("code", AF_SEARCHABLE| AF_FORCE_LOAD), NULL, 10);
		$this->add(new atkParserAttribute("endos_cheque", "env", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE|AF_OBLIGATORY|AF_COMPACT | AF_FORCE_LOAD), NULL, 2);
		$this->add(new atkNumberAttribute("debit_initial", AF_FORCE_LOAD, 12, 2), NULL, 30);
		$this->add(new atkNumberAttribute("credit_initial", AF_FORCE_LOAD, 12, 2), NULL, 40);
/*		$this->add(new atgNumberExpressionAttribute("debit_total", ' select sum(debit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id
				', AF_TOTAL, AF_TOTAL), NULL, 41);
		$this->add(new atgNumberExpressionAttribute("credit_total", ' select sum(credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id
				', AF_TOTAL, AF_TOTAL), NULL, 42);
		$this->add(new atgNumberExpressionAttribute("solde_total", ' select sum(debit-credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id
				', AF_TOTAL, AF_TOTAL), NULL, 43);
		$this->add(new atkDummyAttribute("solde_courant", "solde courant", AF_NOLABEL), NULL, 44);
		$this->add(new atgNumberExpressionAttribute("debit_2", ' select sum(debit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-2
				', AF_TOTAL, AF_TOTAL), NULL, 50);
		$this->add(new atgNumberExpressionAttribute("credit_2", ' select sum(credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-2
				', AF_TOTAL, AF_TOTAL), NULL, 60);
		$this->add(new atgNumberExpressionAttribute("solde_2", ' select sum(debit-credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-2
				', AF_TOTAL, AF_TOTAL), NULL, 61);
		$this->add(new atgNumberExpressionAttribute("debit_1", ' select sum(debit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-1
				', AF_TOTAL, AF_TOTAL), NULL, 70);
		$this->add(new atgNumberExpressionAttribute("credit_1", ' select sum(credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-1
				', AF_TOTAL, AF_TOTAL), NULL, 80);
		$this->add(new atgNumberExpressionAttribute("solde_1", ' select sum(debit-credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())-1
				', AF_TOTAL, AF_TOTAL), NULL, 81);
		$this->add(new atgNumberExpressionAttribute("debit", ' select sum(debit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())
				', AF_TOTAL, AF_TOTAL), NULL, 90);
		$this->add(new atgNumberExpressionAttribute("credit", ' select sum(credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())
				', AF_TOTAL, AF_TOTAL), NULL, 100);
		$this->add(new atgNumberExpressionAttribute("solde", ' select sum(debit-credit) from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = [table].id and l.id_ecriture=e.id and year(e.date_ecriture)=year( UTC_TIMESTAMP())
				', AF_TOTAL, AF_TOTAL), NULL, 101);
				*/
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
		$this->add(new atkBoolAttribute("usuel",AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
		$this->add(new atkAttribute("rib", AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_banque", AF_POPUP | AF_SEARCHABLE));
		$this->add(new atkAttribute("code_acces", AF_SEARCHABLE));

		$this->add(new atkDummyAttribute("stats_comptes", "Statistiques", AF_DUMMY_SHOW_LABEL|AF_COMPACT), NULL, 5);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,10 );
		$this->m_securityMap["document"] = "view";
		$this->m_securityMap["preparation_remise_banque"] = "delete";
		$this->m_securityMap["mettre_au_budget"] = "delete";
		$this->m_securityMap["admin_liste"] = "view";
		$this->setOrder(" RPAD(code,7,'0')");
		$an_exercice=$this->m_postvars["an_exercice_comptable"];
		if (!isset($an_exercice))
		{
			$ancours=gmdate('Y');
		}
/*
		$this->getAttribute("debit_2")->setLabel("D-".($ancours-2));
		$this->getAttribute("debit_1")->setLabel("D-".($ancours-1));
		$this->getAttribute("debit")->setLabel("D-".($ancours));
		$this->getAttribute("credit_2")->setLabel("C-".($ancours-2));
		$this->getAttribute("credit_1")->setLabel("C-".($ancours-1));
		$this->getAttribute("credit")->setLabel("C-".($ancours));
		$this->getAttribute("solde_2")->setLabel("S-".($ancours-2));
		$this->getAttribute("solde_1")->setLabel("S-".($ancours-1));
		$this->getAttribute("solde")->setLabel("S-".($ancours));
*/
		global $ATK_VARS, $g_user;
		if ($ATK_VARS["atknodetype"] == "individu.individu" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
		))) {
			if ($this->getView() == "active") {
				$this->addFilter("organisme_compte.usuel='1'");
			}
		}
	}
	function dispatch($postvars, $fullpage=true)
	{
		if ($postvars['atkaction']!='add' && $postvars['atkaction']!='delete' && $postvars['atkaction']!='admin')
		{
			$atkselect = $postvars["atkselector"];
			if (($atkselect != "") && isset($atkselect))
			{
				$compteid = sscanf($atkselect, "organisme_compte.id='%d'");
				$compteId = $compteid[0];
				$this->RecentUseProcess('compte', $compteId);
			} else
			{ $compteId = 0;
			}
			$this->RecentUseRefresh('compte');
		}
		 


		if ($postvars['atkaction'] != 'admin') {
			$filtre = $postvars["atkfilter"];
			if (stristr($filtre, ' and ') != false) {
				unset ($postvars["atkfilter"]);
			}
				

		}


		return parent::dispatch($postvars, $fullpage);
	}
/*
	function solde_courant_display($record, $mode) {
		$id_compte = $record["id"];
		$db = & atkGetDb();
		$data = $db->getrows(" select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				where l.id_compte = $id_compte and l.id_ecriture=e.id ");
		if (empty ($data[0]["solde"])) {
			$data[0]["solde"] = 0;
		}
		return '<p style="text-align: right;"><font color="Tomato"><b>' . ($data[0]["solde"] + $record["debit_initial"] - $record["credit_initial"]) . "</b></font></p>";
	}
	function solde_1_display($record, $mode) {
		$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array(
				"atkfilter" => " id_compte=".$record['id']." and
				year(date_operation)=year( UTC_TIMESTAMP())-1 ")
				, "dispatch.php"), '<p style="text-align: right;"><b>' . ($record["solde_1"]) . '</b></p>', SESSION_NESTED);
		return $href;
	}
	function solde_2_display($record, $mode) {
		$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array(
				"atkfilter" => " id_compte=".$record['id']." and
				year(date_operation)=year( UTC_TIMESTAMP())-2 ")
				, "dispatch.php"), '<p style="text-align: right;"><b>' . ($record["solde_2"]) . '</b></p>', SESSION_NESTED);
		return $href;

	}
	function solde_display($record, $mode) {
		$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array(
				"atkfilter" => " id_compte=".$record['id']." and
				year(date_operation)=year( UTC_TIMESTAMP())-0 ")
				, "dispatch.php"), '<p style="text-align: right;"><b>' . ($record["solde"]) . '</b></p>', SESSION_NESTED);
		return $href;
	}
	*/

	function action_document($handler) {
		switch ($this->m_postvars["atkcode"]) {
			// endos de cheque
			case 1 :
				$select = $this->m_postvars["id"];
				$db = & atkGetDb();
				$data = $db->getrows("SELECT o.id as id_organisme
						, o.nom as nom , c.rib as rib, tb.libelle as banque
						FROM organisme o, organisme_compte c, type_banque tb
						where c.id=" . $select . "
						and o.id=c.id_organisme
						and c.id_banque=tb.id
						");
				$id_organisme = $data[0]["id_organisme"];
				$template_filename = "endos_cheque.odt";
				$this->m_postvars["id"] = $id_organisme;
				$this->m_postvars["atkdoctpl_prefix_id"] = '1';
				$template_file = & $handler->getFilenameForTemplate($template_filename);
				$tplvars["nom"] = $data[0]["nom"];
				$tplvars["rib"] = $data[0]["rib"];
				$tplvars["banque"] = $data[0]["banque"];
				$dw = & atkOpenDocumentWriter :: getInstance("opendocument");
				$dw->display($template_file, "endos_cheque.odt", $tplvars);
				die();
				break;
		}
	}
	function code_display($record, $mode) {
		return str_pad($record["code"], 7, '.', STR_PAD_RIGHT);
	}
	function libelle_display($record, $mode) {
		return $this->descripteur_compte_comptable($record["id"],'o','o');
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
	function action_admin($handler) {
		$view = $this->getView();
		if ($view == "active") {
			$this->addFilter("organisme_compte.usuel='1'
					or organisme_compte.id in (select distinct id_compte from organisme_ligne_ecriture_comptable)");
		}
		global $config_recordsperpage;
		$config_recordsperpage = 1000;
		return $handler->action_admin();
	}
	function rowColor($record) {
		$usuel = $record["usuel"];
		if (strlen($record["code"]) == 1 && $usuel == "1")
			return $this->couleurcompte1;
		if (strlen($record["code"]) == 2 && $usuel == "1")
			return $this->couleurcompte2;
		if (strlen($record["code"]) == 3 && $usuel == "1")
			return $this->couleurcompte3;
		if (strlen($record["code"]) > 3 && $usuel == "1")
			return $this->couleurcompte4;
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurcompte1 . '"> <b> Classe ' .		'<font color="' . $this->couleurcompte2 . '"> <b> Sous Classe ' .		'<font color="' . $this->couleurcompte3 . '"> <b> Compte 3 chiffres' .		'<font color="' . $this->couleurcompte4 . '"> <b> compte >= 4 chiffres ' .		'<font color="Black"> <b> compte non usuel ';
		;
		$legende .= '<br /> Classes : 1=capitaux, 2=immobilisations, 3=stocks, 4=tiers, 5=financiers, 6=charges, 7=produits, 8=contributions volontaires ';
		if ($view == "active") {
			return atktext("Consultation des comptes usuels.") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('Cliquer ici pour visualiser tous les comptes.', $this->m_module, $this->m_type)) . "<br>" .			$legende . $retour;
		} else {
			return atktext("Consultation de tous les comptes.") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('Cliquer ici pour ne visualiser que les comptes usuels.', $this->m_module, $this->m_type)) . "<br>" .			$legende .$retour;
		}
	}
	function initial_values() {
		$init_vals = array ();
		$init_vals["debit_initial"] = 0;
		$init_vals["credit_initial"] = 0;


		return $init_vals;
	}
	function descriptor_def() {
		return "[code] - [libelle]";
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		$mraactions['delete'] = "delete";
		$mraactions['mettre_au_budget'] = "mettre_au_budget";
	}
	function get_titre_graphique($record)
	{
		$id_compte=$record["id"];
		$db = & atkGetDb();
		$data = $db->getrows(" select oc.code, oc.libelle, o.nom from organisme_compte oc LEFT JOIN organisme o ON oc.id_organisme=o.id  where oc.id=$id_compte");
		$retour.=$data[0]["nom"]." - Compte ".$data[0]["code"]." ".$data[0]["libelle"];
		return $retour;
	}

	function stats_comptes_display(&$record, $mode)
	{

		$titre=$this->get_titre_graphique($record);
		$id_compte=$record["id"];
		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();

		//Déterminer date min
		$sql="SELECT min(YEAR( date_operation )) AS an_min
		FROM  `organisme_ligne_ecriture_comptable`
		WHERE id_compte=$id_compte
		";
		$data = $db->getrows($sql);
		
		$min=$data[0]["an_min"];
		if ($min=="") return;
		$max=date("Y");
		$res = $titre."<table border='1'>";
		$res .= "<tr><td class='styletitre'>Année";
		$res.='</td><td><p style="text-align: center;  margin-top:0px; margin-bottom:0px">Initial</p>';
		for($i=$min; $i<=$max ; $i++)
		{
			$res.='</td><td>'.'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">'.$i.'</p>';
		}

		$res.='</td><td><p style="text-align: center;  margin-top:0px; margin-bottom:0px">Total solde</p>';
		$res .= "<tr><td class='styletitre'>Crédit";
		$res.='</td><td>'.$this->nombre_format ($record["credit_initial"]);
		for ($i=$min; $i<=$max;$i++)
		{

			$sql="select sum(credit) as credit from organisme_ligne_ecriture_comptable
			where id_compte=$id_compte
			AND YEAR(date_operation)=$i
			";

			$data = $db->getrows($sql);
			$lien=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_compte =$id_compte
					 AND YEAR(date_operation)= $i
					" )
					, "dispatch.php"), $this->nombre_format ($data[0]["credit"]) , SESSION_NESTED);
			$res.='</td><td>'.$lien;

		}
		$res.='</td><td></td></tr>';
		
		$res .= "<tr><td class='styletitre'>Débit";
		$res.='</td><td>'.$this->nombre_format ($record["debit_initial"]);
		
		for ($i=$min; $i<=$max;$i++)
		{
		
		$sql="select sum(debit) as debit from organisme_ligne_ecriture_comptable
		where id_compte=$id_compte
		AND YEAR(date_operation)=$i
		";
		
		$data = $db->getrows($sql);
		$lien=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => "organisme_ligne_ecriture_comptable.id_compte =$id_compte
				AND YEAR(date_operation)= $i
				" )
				, "dispatch.php"), $this->nombre_format($data[0]["debit"]) , SESSION_NESTED);
				$res.='</td><td>'.$lien;
		
		}
		$res.='</td><td></td></tr>';
		$res .= "<tr><td class='styletitre'>Solde (D-C)";
		$total_solde=0;
		$res.='</td><td>'.$this->nombre_format($record["debit_initial"]-$record["credit_initial"]);
		$total_solde+=($record["debit_initial"]-$record["credit_initial"]);
		for ($i=$min; $i<=$max;$i++)
		{
		
		$sql="select (sum(debit)-sum(credit)) as solde from organisme_ligne_ecriture_comptable
		where id_compte=$id_compte
		AND YEAR(date_operation)=$i
		";
		
		$data = $db->getrows($sql);
		$lien=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => "organisme_ligne_ecriture_comptable.id_compte =$id_compte
				AND YEAR(date_operation)= $i
				" )
				, "dispatch.php"),  $this->nombre_format($data[0]["solde"]) , SESSION_NESTED);
				$res.='</td><td>'.$lien;
				$total_solde+=$data[0]["solde"];
		}
		$res.='</td><td>'.$this->nombre_format($total_solde).'</td></tr>';
		$res.='</td></tr></table>'.$this->getUserStamp('n','o');;

		//		$record["graphique"]=$this->afficheGraphique($res,$titre);

		return $res;
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=$this->m_postvars["atkfilter"];
		$sql="SELECT
		organisme_compte.id as id_entite,
  
  o.nom as organisme,
  organisme_compte.code,
  organisme_compte.libelle,
  organisme_compte.debit_initial,
  organisme_compte.credit_initial,
  organisme_compte.usuel,
  tb.libelle as banque,
  organisme_compte.rib,
  organisme_compte.url_banque
		from
		organisme_compte
		 LEFT JOIN type_banque tb ON organisme_compte.id_banque=tb.id
		 LEFT JOIN organisme o ON organisme_compte.id_organisme=o.id
		where
		$filtre
		order by RPAD(code,7,'0')";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
				$res2.='<thead>';
				$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Code</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Libellé</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Débit initial</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Crédit initial</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Usuel</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Banque</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Rib</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Url Banque</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
				$res2.='</th></tr>';
				$res2.='</thead>';
				$res2.='<tbody>';
				for ($i=0;$i<count($data);$i++)
				{($data[$i]["usuel"]==1) ? $usuel="Oui" : $usuel="Non";
					$res2.= "<tr><td>".($i+1);
					$res2.='</td><td><b>'.$data[$i]["code"]."</b>";
					$res2.='</td><td><b>'.$data[$i]["libelle"]."</b>";
					$res2.='</td><td>'.$this->nombre_format($data[$i]["debit_initial"],"b",2);
					$res2.='</td><td>'.$this->nombre_format($data[$i]["credit_initial"],"b",2);
					$res2.='</td><td>'.$data[$i]["usuel"];
					$res2.='</td><td>'.$data[$i]["banque"];
					$res2.='</td><td>'.$data[$i]["rib"];
					$res2.='</td><td>'.$data[$i]["url_banque"];
					$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
						
					$res2.='</td></tr>';
	}
	$res2.='</tbody>';
	$res2.='</table>'.$this->getUserStamp('n','o');
					$criteres=$this->m_postvars["atkfiltre"];
					$titre="<h2><b>"."Comptes"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
					$res2=$titre.$res2;
					
			$this->page_output($res2);
	
		}
		public function getCustomMraHtml()
		{
			/*$list = $this->getAttribute('id_document_facture')->edit(null, null, null);
			return $list;
			*/
			/*
			 *  $this->add(new atkManyToOneRelation("memo_id","lesson6.personnel_memo", AF_OBLIGATORY)); 
        return 'Send memo #:' . $this->getAttribute('memo_id')->edit($record, $mode); 
			 */
			$list = "<input type='text' name='qty' value='20'></input>";
			return $list;
		}
		public function action_mettre_au_budget()
		{
		$this->p($this->m_postvars);
			$justificatif= $this->getAttribute('id_document_facture')->fetchValue($this->m_postvars);
			if (empty($justificatif)) return;
			$idjustificatif=$justificatif["id"];
			$db = & atkGetDb();
			global $g_user;
			$userutilisateur = $g_user["id"];
			foreach ($this->m_postvars['atkselector'] as $pk)
			{
				$sql="UPDATE organisme_fourniture
			set id_document_facture='".$idjustificatif."',
			id_modification='".$userutilisateur."',
			date_modification= UTC_TIMESTAMP()
			 where ".$pk."";
				$db->query($sql);
			}
			$this->redirect();
		}
}
?>