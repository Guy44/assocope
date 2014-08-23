<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgNumberExpressionAttribute");
class releve_banque extends assMetaNode {
	var $table = "organisme_releve_banque";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->setOrder("libelle");
	}
	function releve_banque() {
		$this->atkMetaNode();
		$this->atkNode("releve_banque", NF_ADD_LINK| NF_COMPACT) ;
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"descripteur_releve_banque",
						"id_organisme",
						"libelle",
						"remises_pointees",
						"autres_pointees",
						"detail_pointage",
						"solde_initial_releve",
						"solde_initial_observe",
						"total_debits_releve",
						"total_debits_observe",
						"total_credits_releve",
						"total_credits_observe",
						"solde_final_releve",
						"solde_final_observe",

						"id_compte_banque",
						"id_releve_banque",
						"id_document_releve",
						"date_releve_banque",
						"date_cloture_releve",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Remises_rapprochées" => array (
						"remises"
				),
				"Lignes_rapprochées" => array (
						"lignes"
				)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_releve_banque",0,AF_COMPACT),NULL, 5);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_READONLY | AF_SEARCHABLE| AF_RELATION_AUTOCOMPLETE |AF_FORCE_LOAD),NULL,10);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY), null, 100);
		$this->add(new atgNumberExpressionAttribute("remises_pointees", ' select count(id) from organisme_remise_banque
				where id_releve= [table].id
				', 0, 0), null, 60);
		$this->add(new atgNumberExpressionAttribute("autres_pointees", ' select count(id) from organisme_ligne_ecriture_comptable
				where id_releve= [table].id and id_remise is NULL
				', 0, 0), null, 61);
		$this->add(new atgNumberExpressionAttribute("detail_pointage", ' select count(id) from organisme_ligne_ecriture_comptable
				where id_releve= [table].id
				', 0, 0), null, 62);
		$this->add(new atkNumberAttribute("solde_initial_releve", AF_OBLIGATORY, 10, 2), null, 110);
		$this->add(new atkParserAttribute("solde_initial_observe", "env1"), null, 120);
		$this->add(new atkNumberAttribute("total_debits_releve", AF_OBLIGATORY, 10, 2), null, 130);
		$this->add(new atkParserAttribute("total_debits_observe", "env2"), null, 140);
		$this->add(new atkNumberAttribute("total_credits_releve", AF_OBLIGATORY, 10, 2), null, 150);
		$this->add(new atkParserAttribute("total_credits_observe", "env3"), null, 160);
		$this->add(new atkNumberAttribute("solde_final_releve", AF_OBLIGATORY, 10, 2), null, 170);
		$this->add(new atkParserAttribute("solde_final_observe", "env4"), null, 180);
		//	$this->add(new atkExpressionAttribute("nombre", ' select count(distinct numero_releve) from organisme_ligne_ecriture_comptable		 where id_releve = [table].id ', 0, 0), null, 60);

		$this->add(new atkManyToOneRelation("id_compte_banque", "organisme.compte", AF_SEARCHABLE | AF_READONLY|AF_FORCE_LOAD));
		$this->add(new atkAttribute("id_releve_banque",0,AF_FORCE_LOAD), null, 90);
		$this->add(new atkDateAttribute("date_cloture_releve", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_READONLY | AF_FORCE_LOAD), null, 100);
		$this->add(new atkDateAttribute("date_releve_banque", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY|AF_FORCE_LOAD), null, 100);
		$this->add(new atgFileManyToOneRelation("id_document_releve", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), null, 110);
		$c120 = $this->add(new atkOneToManyRelation("lignes", "organisme.ligne_ecriture_comptable", "id_releve", AF_HIDE_LIST));
		//		$c120= & $this->add(new atkOneToManyRelation("lignesnon", "organisme.ligne_ecriture_comptable", "id_compte", AF_HIDE_LIST));
		$c120->addDestinationFilter(" id_remise is null");
		$this->add(new atkOneToManyRelation("remises", "organisme.remise_banque", "id_releve", AF_HIDE_LIST));
		$this->m_securityMap["clore"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,7);
		//		$this->setIndex("libelle");
		$this->setOrder("date_releve_banque desc");
	}
	function descripteur_releve_banque_display($record, $mode) {
		return $this->descripteur_releve_banque($record["id"],'o').'<br />';
	}
	function libelle_display($record, $mode) {
		return $this->decoupe_affichage_colonne($record["libelle"], 40);
	}

	function detail_pointage_display($record, $mode) {
		if (isset ($record["detail_pointage"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_releve='" . $record['id'] . "' "
			), "dispatch.php"), text($record["detail_pointage"]), SESSION_NESTED);
		} else {
			return "";
		}
	}

	function autres_pointees_display($record, $mode) {
		if (isset ($record["autres_pointees"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_releve='" . $record['id'] . "' and id_remise is null"
			), "dispatch.php"), text($record["autres_pointees"]), SESSION_NESTED);
		} else {
			return "";
		}
	}

	function remises_pointees_display($record, $mode) {
		if (isset ($record["remises_pointees"])) {
			return href(dispatch_url("organisme.remise_banque", "admin", array (
					'atkfilter' => "organisme_remise_banque.id_releve='" . $record['id'] . "'"
			), "dispatch.php"), text($record["remises_pointees"]), SESSION_NESTED);
		} else {
			return "";
		}
	}

	function solde_initial_observe_edit($record, $mode) {
		$idreleve = $record["id"];
		if (empty ($idreleve)) {
			return;
		}
		$idcompte = $record["id_compte_banque"]["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT sum(lec.debit - lec.credit) as solde from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve is not null and lec.id_releve< $idreleve)");
		$solde = $data[0]["solde"];
		if (empty ($solde)) {
			$solde = 0;
		}
		$data = $db->getrows("SELECT (debit_initial - credit_initial) as solde_initial  from organisme_compte
				where   id = $idcompte ");
		$solde = $solde + $data[0]["solde_initial"];
		if (empty ($solde)) {
			$solde = '0,00';
		}
		if ((strlen($solde) - strpos($solde, ".")) == 2) {
			$solde = $solde . '0';
		}
		$solde = str_replace(".", ",", $solde);
		if (strpos($solde, ",") == false) {
			$solde = $solde . ',00';
		}
		return $solde;
	}
	function solde_initial_observe_display($record, $mode) {
		if ($mode == "add") {
			return;
		} else {
			return $this->solde_initial_observe_edit($record, $mode);
		}
	}
	function total_debits_observe_edit($record, $mode) {
		$idreleve = $record["id"];
		if (empty ($idreleve)) {
			return;
		}
		$idcompte = $record["id_compte_banque"]["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT sum(lec.credit) as debit_banque from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve = $idreleve)");
		$debit_banque = $data[0]["debit_banque"];
		if ((strlen($debit_banque) - strpos($debit_banque, ".")) == 2) {
			$debit_banque = $debit_banque . '0';
		}
		$debit_banque = str_replace(".", ",", $debit_banque);
		if (empty ($debit_banque)) {
			$debit_banque = '0,00';
		}
		if (strpos($solde, ",") == false) {
			$solde = $solde . ',00';
		}
		return $debit_banque;
	}
	function total_debits_observe_display($record, $mode) {
		if ($mode == "add") {
			return;
		} else {
			return $this->total_debits_observe_edit($record, $mode);
		}
	}
	function total_credits_observe_edit($record, $mode) {
		$idreleve = $record["id"];
		if (empty ($idreleve)) {
			return;
		}
		$idcompte = $record["id_compte_banque"]["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT sum(lec.debit) as credit_banque from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve = $idreleve)");
		$credit_banque = $data[0]["credit_banque"];
		if ((strlen($credit_banque) - strpos($credit_banque, ".")) == 2) {
			$credit_banque = $credit_banque . '0';
		}
		$credit_banque = str_replace(".", ",", $credit_banque);
		if (empty ($credit_banque)) {
			$credit_banque = '0,00';
		}
		if (strpos($solde, ",") == false) {
			$solde = $solde . ',00';
		}
		return $credit_banque;
	}
	function total_credits_observe_display($record, $mode) {
		if ($mode == "add") {
			return;
		} else {
			return $this->total_credits_observe_edit($record, $mode);
		}
	}
	function solde_final_observe_edit($record, $mode) {
		$idreleve = $record["id"];
		if (empty ($idreleve)) {
			return;
		}
		$idcompte = $record["id_compte_banque"]["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT sum(lec.debit - lec.credit) as solde from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve is not null and lec.id_releve < $idreleve)");
		//		echo "solde ecriture avant".$data[0]["solde"];
		(strlen($data[0]["solde"])>0) ? $solde = $data[0]["solde"] :$solde='0.00' ;
		//		echo "<br/>Solde initial : ".$solde;
		$data = $db->getrows("SELECT (debit_initial - credit_initial) as solde_initial  from organisme_compte
				where   id = $idcompte ");
		//		echo "<br/>Solde initial : ".$data[0]["solde_initial"];
		$solde = $solde + $data[0]["solde_initial"];
		$data = $db->getrows("SELECT sum(lec.credit) as debit_banque from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve = $idreleve)");
		$debit_banque = $data[0]["debit_banque"];
		$data = $db->getrows("SELECT sum(lec.debit) as credit_banque from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte = $idcompte and lec.id_releve = $idreleve)");
		$credit_banque = $data[0]["credit_banque"];
		$solde = $solde + $credit_banque - $debit_banque;

		//		echo "<br/>Crédit banque : ".$credit_banque;
		//		echo "<br/>Débit banque : ".$debit_banque;
		//		echo "<br/>solde : ".$solde;
		//		die();
//		if ((strlen($solde) - strpos($solde, ".")) >3) {
//			$solde = substr($solde, 0,(strpos($solde, ".")+3) );
//		}
		if ((strlen($solde) - strpos($solde, ".")) == 2) {
			$solde = $solde . '0';
		}
		$solde = str_replace(".", ",", $solde);
		if (empty ($solde)) {
			$solde = '0,00';
		}
		if (strpos($solde, ",") == false) {
			$solde = $solde . ',00';
		}
		return $solde;
	}
	function solde_final_observe_display($record, $mode) {
		if ($mode == "add") {
			return;
		} else {
			return $this->solde_final_observe_edit($record, $mode);
		}
	}
	function initial_values() {
		$init_vals = array ();
		$comptebanque = explode('=', $this->m_postvars['atkfilter']);

		if (strchr($comptebanque[0],'organisme_releve_banque.id_compte_banque')!=false){
			//		if ($comptebanque[0] == 'organisme_releve_banque.id_compte_banque' ){
			$id_comptebanque = $comptebanque[1];
			$db = & atkGetDb();
			$data = $db->getrows("SELECT count(id) as count from organisme_releve_banque where id_compte_banque=$id_comptebanque and date_cloture_releve is null ");
			if ($data[0]["count"] > 0) {
				echo "Un relevé est déjà en cours de pointage pour ce compte";
				die();
			}
			$data = $db->getrows("SELECT c.id_organisme as id_organisme FROM organisme_compte c where c.id=$id_comptebanque");
			$init_vals["id_organisme"] = $data[0]["id_organisme"];
		} else {
			echo "L'ajout d'un relevé n'est possible qu'à partir de la sélection d'un compte financier.";
			die();
		}
		$init_vals["debit_initial_releve"] = 0;
		$init_vals["credit_initial_releve"] = 0;
		$init_vals["debit_final_releve"] = 0;
		$init_vals["credit_final_releve"] = 0;
		return $init_vals;
	}
	function preAdd(& $record) {
		$id_compte_banque = $record['id_compte_banque']['id'];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_organisme FROM organisme_compte where id=$id_compte_banque ");
		$id_organisme = $data[0]["id_organisme"];
		$record["id_organisme"] = "$id_organisme";
		parent :: preAdd($record);
	}
	function preDelete(& $record) {
		$idreleve = $record["id"];
		global $g_user;
		$userid = $g_user["id"];
		if ($record["date_cloture_releve"]["year"] > 0) {
			echo "Le relevé a été clôturé. Il est impossible de le supprimer.";
			die();
		}
		$db = & atkGetDb();
		$db->query("UPDATE  organisme_ligne_ecriture_comptable
				set id_releve=null,
				id_modification='$userid',
				date_modification=UTC_TIMESTAMP()
				where id_releve=$idreleve");
		$db->query("UPDATE  organisme_remise_banque
				set id_releve=null,
				id_modification='$userid',
				date_modification=UTC_TIMESTAMP()
				where id_releve=$idreleve");
	}
	function action_clore($handler) {
		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$idreleve = $this->m_postvars["atkselector"];
		$tab = explode("=", $this->m_postvars["atkselector"]);
		$id_releve = $tab[1];
		$record = array ();
		$record["id"] = $id_releve;
		$data = $db->getrows("SELECT id_compte_banque, solde_initial_releve, total_debits_releve, total_credits_releve, solde_final_releve, date_cloture_releve  FROM organisme_releve_banque where id=$id_releve ");
		if (!empty ($data[0]["date_cloture_releve"])) {
			echo "Relevé déjà clos.";
			die();
		}
		$record['id_compte_banque']['id'] = $data[0]["id_compte_banque"];
		$solde_initial_observe = $this->solde_initial_observe_edit($record,null);
		$total_debits_observe = $this->total_debits_observe_edit($record,null);
		$total_credits_observe = $this->total_credits_observe_edit($record,null);
		$solde_final_observe = $this->solde_final_observe_edit($record,null);
/* GG
		$liste=$solde_initial_observe.'<br>'.$total_debits_observe.'<br>'.$total_credits_observe.'<br>'.$solde_final_observe;
			print_r($liste);
			*/
		$data[0]["solde_initial_releve"] = str_replace(".", ",", $data[0]["solde_initial_releve"]);
		$data[0]["total_debits_releve"] = str_replace(".", ",", $data[0]["total_debits_releve"]);
		$data[0]["total_credits_releve"] = str_replace(".", ",", $data[0]["total_credits_releve"]);
		$data[0]["solde_final_releve"] = str_replace(".", ",", $data[0]["solde_final_releve"]);
		//GG				$this->p($data);
		if ($data[0]["solde_initial_releve"] ==	$solde_initial_observe 
				&& $data[0]["total_debits_releve"] == $total_debits_observe 
				&& $data[0]["total_credits_releve"] == $total_credits_observe 
				&& $data[0]["solde_final_releve"] == $solde_final_observe) {
			$db->query("UPDATE  organisme_releve_banque
					set date_cloture_releve=UTC_TIMESTAMP(),
					id_modification='$userid',
					date_modification=UTC_TIMESTAMP()
					where $idreleve");
			$this->redirect();
		} else {
			echo "Pointage incorrect. Vérifier.";
			die();
		}
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$actions["clore"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=clore&atkselector=[pk]", SESSION_NESTED);
	}
	function rowColor($record) {
		if (empty ($record["date_cloture_releve"])) {
			return $this->couleurrouge;
		} else {
			return $this->couleurvert;
		}
	}
	function controle($record) {
		if ($record["solde_initial_releve"] == $record["solde_initial_observe"] && $record["total_debits_releve"] == $record["total_debits_observe"] && $record["total_credits_releve"] == $record["total_credits_observe"] && $record["solde_final_releve"] == $record["solde_final_observe"]) {
			return true;
		}
		return false;
	}
	function descriptor_def() {
		return "[libelle]";
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$id_releve_banque=$this->m_postvars["id_releve_banque"];
		$sql="SELECT
		id_document_releve
		from organisme_releve_banque
		WHERE
		id=$id_releve_banque
		";
		$data=$db->getrows($sql);

		$descripteur="<h2><b>"."Relevé de banque : ".$id_releve_banque."</h2><br/>";
		$descripteur.=strip_tags($this->descripteur_releve_banque($id_releve_banque, 'n'),"<b><br><br/><img><div>");
		$descripteur.="<br/><div ".$this->m_styleTitreLigne."<b>"."Lignes d'écritures concernées par le relevé de banque : ".$id_releve_banque."</b></div><br/><br/>";
		$node_ligne=newNode("organisme.ligne_ecriture_comptable",true);
		$descripteur.=$node_ligne->action_admin_liste("releve",$id_releve_banque,$id_organisme);
		($data[0]["id_document_releve"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_document_releve"],'n',$lien_releve) : $lien_releve="";
		$descripteur.='<br/><div '.$this->m_styleTitreLigne.'>Relevé de la banque : '.$lien_releve."</div><br/>";
		unset ($node_ligne);
		$this->page_output($descripteur);


	}

}
?>