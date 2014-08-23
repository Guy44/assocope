<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class inscription_i extends assMetaNode {
	var $table = "individu_inscription";
	function meta(& $policy) {
		//$policy-> addFlags("annee",AF_SEARCHABLE);
		$policy->addFlags("commentaire", "origine", "p1", "e1", "p2", "e2", "p3", "e3", "p4", "e4", "p5", "e5", "p6", "e6", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "creer_adresse_postale_o_n", "inscrire_federation_o_n", "creer_cotisation_federation_o_n", "reporter_inscription_federation_o_n", "reporter_radiation_federation_o_n", "regler_cotisation_federation_o_n", "imprimer_adresse_o_n", "envoyer_recu_fiscal_o_n", "envoyer_timbre_o_n", "envoyer_carte_adherent_o_n", "an_derniere_cotisation", "reclamer_cotisation_o_n", "an_radiation_cotisation_prevue", "avertir_radiation_cotisation_o_n", "effectuer_radiation_cotisation_o_n", "an_adhesion_prevue", "avertir_radiation_adhesion_o_n", "effectuer_radiation_adhesion_o_n", AF_READONLY);
		/*	$policy->setTab("creer_adresse_postale_o_n", "inscrire_federation_o_n",
		 "creer_cotisation_federation_o_n", "reporter_inscription_federation_o_n","reporter_radiation_federation_o_n",
				"regler_cotisation_federation_o_n", "imprimer_adresse_o_n","envoyer_recu_fiscal_o_n","envoyer_timbre_o_n","envoyer_carte_adherent_o_n"
				,"an_derniere_cotisation","reclamer_cotisation_o_n","an_radiation_cotisation_prevue","avertir_radiation_cotisation_o_n"
				,"effectuer_radiation_cotisation_o_n","an_adhesion_prevue","avertir_radiation_adhesion_o_n","effectuer_radiation_adhesion_o_n","adhesion_et_pas_de_cotisation_o_n","traitement");
			
		//$policy->setTab("p1", "e1",
				"p2", "e2","p3",
				"e3", "p4","e4","p5","e5"
				,"p6","e6","complément_correspondance");
		*/
	}
	function inscription_i() {
		$this->atkMetaNode();
		$this->atkNode("inscription_i",  NF_ADD_LINK | NF_TRACK_CHANGES| NF_ADDAFTERADD | NF_MRA | NF_COMPACT );
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id_individu",
						"id_organisme",
						"descripteur_inscription",
						"id_inscription",
						"id_type_inscription",
						"id_organisme_inscrit",
						"date_inscription",
						"date_adhesion",
						"id_document_adhesion",
						"date_envoi_carte",
						"date_derniere_cotisation",
						"date_radiation",
						"id_type_radiation",
						"origine",
						"id_type_origine",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),

				"Traitements" => array (
						"creer_adresse_postale_o_n",
						"inscrire_federation_o_n",
						"creer_cotisation_federation_o_n",
						"reporter_inscription_federation_o_n",
						"reporter_radiation_federation_o_n",
						"regler_cotisation_federation_o_n",
						"imprimer_adresse_o_n",
						"envoyer_recu_fiscal_o_n",
						"envoyer_timbre_o_n",
						"envoyer_carte_adherent_o_n",
						"an_derniere_cotisation",
						"reclamer_cotisation_o_n",
						"an_radiation_cotisation_prevue",
						"avertir_radiation_cotisation_o_n",
						"effectuer_radiation_cotisation_o_n",
						"an_adhesion_prevue",
						"avertir_radiation_adhesion_o_n",
						"effectuer_radiation_adhesion_o_n",
						"adhesion_et_pas_de_cotisation_o_n"
				),
				"Compléments correspondance" => array (
						"p1",
						"e1",
						"p2",
						"e2",
						"p3",
						"e3",
						"p4",
						"e4",
						"p5",
						"e5",
						"p6",
						"e6"
				)
		), AF_NO_LABEL));
		$this->add(new atkTextAttribute("p1", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e1", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("p2", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e2", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("p3", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e3", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("p4", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e4", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("p5", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e5", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("p6", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkTextAttribute("e6", array (
				'autoadjust' => 'yes',
				'rows' => '2'
		)));
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),NULL,110);
		$this->add(new atkDummyAttribute("descripteur_inscription",0,AF_COMPACT),NULL, 100);
		$organisme = & $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),NULL,120);
		$organisme->addDependee("id_type_inscription");


		//		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_type_origine", "table.origine", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_FORCE_LOAD));
		$inscription = & $this->add(new atkManyToOneRelation("id_type_inscription", "table.type_inscription", AF_SEARCHABLE | AF_OBLIGATORY | AF_FORCE_LOAD));
		$inscription->addDestinationFilter("id_organisme= '[id_organisme.id]' OR id_organisme is null");



		$this->add(new atgOManyToOneRelation("id_organisme_inscrit", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_radiation", "table.type_radiation", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
		$this->add(new atkDateAttribute("date_inscription", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY));
		$this->add(new atkDateAttribute("date_adhesion", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkManyToOneRelation("id_document_adhesion", "organisme.document", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD));
		$this->add(new atkDateAttribute("date_envoi_carte", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_derniere_cotisation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_radiation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_FORCE_LOAD));
		$this->add(new atkBoolAttribute("creer_adresse_postale_o_n"));
		$this->add(new atkBoolAttribute("inscrire_federation_o_n"));
		$this->add(new atkBoolAttribute("creer_cotisation_federation_o_n"));
		$this->add(new atkBoolAttribute("reporter_inscription_federation_o_n"));
		$this->add(new atkBoolAttribute("reporter_radiation_federation_o_n"));
		$this->add(new atkBoolAttribute("regler_cotisation_federation_o_n"));
		$this->add(new atkBoolAttribute("imprimer_adresse_o_n"));
		$this->add(new atkBoolAttribute("envoyer_recu_fiscal_o_n"));
		$this->add(new atkBoolAttribute("envoyer_timbre_o_n"));
		$this->add(new atkBoolAttribute("envoyer_carte_adherent_o_n"));
		$this->add(new atkNumberAttribute("an_derniere_cotisation"));
		$this->add(new atkBoolAttribute("reclamer_cotisation_o_n"));
		$this->add(new atkNumberAttribute("an_radiation_cotisation_prevue"));
		$this->add(new atkBoolAttribute("avertir_radiation_cotisation_o_n"));
		$this->add(new atkBoolAttribute("effectuer_radiation_cotisation_o_n"));
		$this->add(new atkNumberAttribute("an_adhesion_prevue"));
		$this->add(new atkBoolAttribute("avertir_radiation_adhesion_o_n"));
		$this->add(new atkBoolAttribute("effectuer_radiation_adhesion_o_n"));
		$this->add(new atkBoolAttribute("adhesion_et_pas_de_cotisation_o_n"));
		/*		$this->add(new atkDummyAttribute("courriel", "Courriel", AF_SEARCHABLE));
		 $this->add(new atkDummyAttribute("telephone_fixe", "Telephone_fixe", AF_SEARCHABLE));
		$this->add(new atkDummyAttribute("telephone_mobile", "Telephone_mobile", AF_SEARCHABLE));
		*/
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,101 );
		$this->m_securityMap["admin_liste"] = "view";
		$this->setOrder("individu_inscription.id_individu");

		global $ATK_VARS, $g_user;
		if ($ATK_VARS["atknodetype"] == "individu.inscription_i" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
		))) {
			if ($this->getView() == "active") {
				$this->addFilter("individu_inscription.date_radiation IS NULL");
			}
		}
		//$this->setIndex("annee");
	}
	function descripteur_inscription_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_inscription($record["id"],'o').'<br />',60);
	}
	/*
	 function action_edit(&$handler)
	 {
	$page = &$this->getPage();
	$page->register_stylecode("#ar_e1 TD.field { overflow:scroll; }");
	$page->register_stylecode("#ar_e2 TD.field { overflow:scroll; }");
	$page->register_stylecode("#ar_e3 TD.field { overflow:scroll; }");
	$page->register_stylecode("#ar_e4 TD.field { overflow:scroll; }");
	$page->register_stylecode("#ar_e5 TD.field { overflow:scroll; }");
	$page->register_stylecode("#ar_e6 TD.field { overflow:scroll; }");

	return $handler->action_edit();
	}
	*/
	/*
	 *
	function recordActions($rec, & $actions, & $mraactions) {
	$actions["lister"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=lister&atkselector=[pk]", SESSION_NESTED);
	unset ($mraactions["delete"]);
	$mraactions[] = "lister";
	//unset($mraactions[0]);
	}
	*/
	/*	function id_organisme_display($record, $mode) {
		include_once(atkconfig("atkroot")."modules/include/organismecontrole.inc");

	}
	*/
	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_inscription
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_inscrit_display($record, $mode) {
		(!empty($record["id_organisme_inscrit"])) ? $retour=$this->descripteur_organisme($record["id_organisme_inscrit"]["id"],'n') : $retour="";
		return $retour;
	}

	/*	function courriel_display($record, $mode) {
		$db = & atkGetDb();
	$query = "SELECT courriel from individu where id=" . $record["id_individu"]["id"] . " ";
	$row = $db->getrows($query);
	return $row[0]["courriel"];
	}
	function telephone_fixe_display($record, $mode) {
	$db = & atkGetDb();
	$query = "SELECT telephone_fixe from individu where id=" . $record["id_individu"]["id"] . " ";
	$row = $db->getrows($query);
	return $row[0]["telephone_fixe"];
	}
	function telephone_mobile_display($record, $mode) {
	$db = & atkGetDb();
	$query = "SELECT telephone_mobile from individu where id=" . $record["id_individu"]["id"] . " ";
	$row = $db->getrows($query);
	return $row[0]["telephone_mobile"];
	}
	*/
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}

	function preAdd(& $record) {
		// atk_var_dump($record);
		$id_organisme = $record['id_organisme']['id'];
		$id_individu = $record['id_individu']['id'];
		$id_type_inscription = $record['id_type_inscription']['id'];
		$date_inscription=$record['date_inscription']['year'].$record['date_inscription']['month'].$record['date_inscription']['day'];
		$db = & atkGetDb();
		// Vérifier si déjà inscrit
		$data = $db->getrows("SELECT id FROM individu_inscription where id_organisme=$id_organisme and id_individu=$id_individu
				and ( date_radiation is null or date_radiation > $date_inscription ) ");
		if (count($data) > 0) {
			triggerError($record, "", "erreur_:_deja_inscrit_organisme");
		}
		$record["id_inscription"]=$this->getProchainIdInscription($id_organisme) ;


		global $g_user;
		$userutilisateur = $g_user["id"];
		$db = & atkGetDb();
		// doit on payer une cotisation fédération
		$data = $db->getrows("SELECT ti.inscription_organisme_o_n, ti.cotisation_federation_o_n, ti.cotisation_organisme_o_n from  type_inscription ti" . " where ti.id=$id_type_inscription ");
		$cotisation_federation_o_n = $data[0]["cotisation_federation_o_n"];
		$cotisation_organisme_o_n = $data[0]["cotisation_organisme_o_n"];
		$inscription_organisme_o_n = $data[0]["inscription_organisme_o_n"];
		//$this->p($record);
		if ($inscription_organisme_o_n=='1' and !isset($record["id_organisme_inscrit"]["id"]))
		{
			triggerError($record, "id_organisme_inscrit", "erreur_:_inscription_organisme_obligatoire");
		}
		// L'inscription à fédération doit exister et vérifier si pas déjà inscription existante
		if ($cotisation_federation_o_n == '1') {
			$data = $db->getrows("SELECT o.id_organisme_federation from organisme o where id=$id_organisme");
			$id_organisme_federation = $data[0]["id_organisme_federation"];

			if (empty($id_organisme_federation))
			{
				triggerError($record, "id_type_inscription", "erreur_:_inscription_federation_obligatoire_et_pas_de_federation");
			}
			else
			{
				$data = $db->getrows("SELECT ii.id from individu_inscription ii" . " where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme_federation ");
				if (count($data) == 0) {
					$data = $db->getrows("SELECT prochain_id_inscription FROM organisme where id=$id_organisme_federation ");
					$id_inscription = $data[0]["prochain_id_inscription"];
					$db->query("UPDATE organisme set prochain_id_inscription=prochain_id_inscription+1 where id=$id_organisme_federation ");
					$data = $db->query("INSERT into individu_inscription" . " (id_individu, id_organisme,id_inscription ,id_type_inscription,id_creation, id_modification, date_creation, date_modification, date_inscription)" . " VALUES ( $id_individu,$id_organisme_federation,$id_inscription,'13',$userutilisateur,$userutilisateur,UTC_DATE(),UTC_TIMESTAMP(), UTC_TIMESTAMP())");
					$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_inscription' ");
				}
			}
		}

		parent :: preAdd($record);
	}


	function getProchainIdInscription($id_organisme)
	{
		$db = &atkGetDb();
		$data = $db->getrows("SELECT prochain_id_inscription FROM organisme where id=$id_organisme ");
		$id_inscription=$data[0]["prochain_id_inscription"];
		$db->query("UPDATE organisme set prochain_id_inscription=prochain_id_inscription+1 where id=$id_organisme ");
		return $id_inscription;


	}


	function preUpdate(& $record) {
		// atk_var_dump($record);
		$id_organisme = $record['id_organisme']['id'];
		$id_individu = $record['id_individu']['id'];
		$id_type_inscription = $record['id_type_inscription']['id'];
		$date_radiation = $record['date_radiation']['year'] . '-' . $record['date_radiation']['month'] . '-' . $record['date_radiation']['day'];
		if ($date_radiation == "--") {
			$date_radiation = null;
		}
		$motif_radiation = $record['id_type_radiation']['id'];

		($date_radiation!=null && $motif_radiation==null ) ? triggerError($record, "id_type_radiation", "erreur_:_pour_une_radiation_vous_devez_saisir_le_motif") : null ;
		(empty($date_radiation) && !empty($motif_radiation)) ? triggerError($record, "date_radiation", "erreur_:_pour_une_radiation_vous_devez_saisir_la_date") : null ;
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		$db = & atkGetDb();
		// doit on payer une cotisation fédération
		$data = $db->getrows("SELECT ti.inscription_organisme_o_n, ti.cotisation_federation_o_n, ti.cotisation_organisme_o_n from  type_inscription ti" . " where ti.id=$id_type_inscription ");
		$cotisation_federation_o_n = $data[0]["cotisation_federation_o_n"];
		$cotisation_organisme_o_n = $data[0]["cotisation_organisme_o_n"];
		$inscription_organisme_o_n = $data[0]["inscription_organisme_o_n"];
		//$this->p($record);
		if ($inscription_organisme_o_n=='1' and !isset($record["id_organisme_inscrit"]["id"]))
		{
			triggerError($record, "id_organisme_inscrit", "erreur_:_inscription_organisme_obligatoire");
		}
		// L'inscription à fédération doit exister et vérifier si pas déjà inscription existante
		if ($cotisation_federation_o_n == '1') {
			$data = $db->getrows("SELECT o.id_organisme_federation from organisme o where id=$id_organisme");
			$id_organisme_federation = $data[0]["id_organisme_federation"];
			if (empty($id_organisme_federation))
			{
				triggerError($record, "id_type_inscription", "erreur_:_inscription_federation_obligatoire_et_pas_de_federation");
			}
			else
			{
				$data = $db->getrows("SELECT ii.id from individu_inscription ii" . " where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme_federation ");
				if (count($data) == 0) {
					$data = $db->getrows("SELECT prochain_id_inscription FROM organisme where id=$id_organisme_federation ");
					$id_inscription = $data[0]["prochain_id_inscription"];
					$db->query("UPDATE organisme set prochain_id_inscription=prochain_id_inscription+1 where id=$id_organisme_federation ");
					$data = $db->query("INSERT into individu_inscription" . " (id_individu, id_organisme,id_inscription ,id_type_inscription,id_creation, id_modification, date_creation, date_modification, date_inscription)" . "VALUES ( $id_individu ,$id_organisme_federation,$id_inscription,'13',$userutilisateur,$userutilisateur,UTC_DATE(),UTC_DATE(), UTC_DATE())");
					$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_inscription' ");
				} else {
					if ($date_radiation != null) {
						$data = $db->query("UPDATE individu_inscription set date_radiation='$date_radiation', id_type_radiation=$motif_radiation, date_modification=CURDATE(), id_modification=$userutilisateur " . "where id_individu='$id_individu'   and id_organisme='$id_organisme_federation' ");
					}
				}
			}
		}
		parent :: preUpdate($record);

	}
	function rowColor($record) {
		$date_radiation = $record["date_radiation"];
		if ($date_radiation != "")
			return $this->couleurarchive;
	}
	function descriptor_def() {
		return "[id_inscription]";
	}
	function action_admin($handler) {
		//		$this->p($this->m_postvars["atkfilter"]);
		$view = $this->getView();
		if ($view == "active") {
			$this->addFilter("individu_inscription.date_radiation IS NULL");
		}
		global $config_recordsperpage;
		$config_recordsperpage = 100;

		return $handler->action_admin();
	}
	function dispatch(& $postvars, $fullpage = true) {

		if ($postvars['atkaction'] != 'admin') {

			$filtre = $postvars["atkfilter"];
			if (stristr($filtre, ' or ') != false) {
				unset ($postvars["atkfilter"]);
			}

			if (stristr($filtre, '%09or%20') != false) {
				unset ($postvars["atkfilter"]);
			}
		}
		if ($postvars['atkaction'] == 'edit' || $postvars['atkaction'] == 'view' )
		{
			unset ($postvars["atkfilter"]);
		}

		$this->addFilter($postvars["atkfilter"]);
		//	unset ($postvars["atkfilter"]);

		return parent :: dispatch($postvars, $fullpage);
	}



	function action_lister() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		//  atk_var_dump($this->m_postvars["atkselector"], 'selected records');
		// print_r($this->m_postvars["atkselector"]);
		//print_r($select);
		//die();
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id_variable = explode('=', $id_variable);
			$array_id_variable[1] = str_replace("''", "", $array_id_variable[1]);
			$r = $db->getrows("select id_individu from individu_inscription where id=" . $array_id_variable[1] . " ");
			$db->query("INSERT INTO tmp_copier_coller (id_utilisateur, nom_variable, id_variable, date_creation)  VALUES( '$userid', '$nom_variable'," . $r[0][id_individu] . ", UTC_TIMESTAMP())");
		}
		$db->commit();
		$this->redirect();
	}


	function action_delete() {

		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}

		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		foreach ($select as $condition) {
			//		$condition=$this->m_postvars["atkselector"];
			$data=$db->getrows("select date_radiation from individu_inscription where $condition");
			//		$this->p($data);
			if (empty($data[0]["date_radiation"]))
			{
				$sql="update individu_inscription set
				date_radiation= UTC_TIMESTAMP() ,
				id_modification=  $userid,
				date_modification= UTC_TIMESTAMP() ,
				id_type_radiation= 3
		  where $condition and date_radiation is NULL";
				$db->query($sql);
				$db->commit();
			}
			else
			{ $db->query("delete from individu_inscription where $condition");

			}
			$this->redirect();
		}
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende='Légende des couleurs : ';
		$legende.='<font color="'. $this->couleurarchive.'"> <b> Archive ';
		if ($view == "active") {
			return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>"
					.$legende.$retour;
		} else {
			return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>"
					.$legende.$retour;
		}
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		//	$mraactions['liste_organismes_representes'] = "liste_organismes_representes";
		$mraactions['delete'] = "delete";
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("individu_inscription", "ii", $this->m_postvars["atkfilter"]);
		$type=$this->m_postvars["type"];
		if ($type=="inscription")
		{
			$sql="SELECT
			ii.id	as id_entite,
			i.id as id_individu,
			ti.libelle as libelle_inscription,
			ii.date_inscription,
			ii.date_adhesion,
			ii.id_document_adhesion,
			ii.date_envoi_carte,
			ii.date_derniere_cotisation,
			ii.date_radiation,
			tr.libelle as libelle_radiation,
			ii.origine as origine,
			tor.libelle as libelle_origine,
			o.id as id_organisme,
			o.nom as organisme
			from
			individu_inscription ii LEFT JOIN individu i ON ii.id_individu=i.id
			LEFT JOIN type_inscription ti ON ii.id_type_inscription=ti.id
			LEFT JOIN type_radiation tr ON ii.id_type_radiation=tr.id
			LEFT JOIN type_origine tor ON ii.id_type_origine=tor.id
			LEFT JOIN organisme o ON ii.id_organisme=o.id
			where
			$filtre
			order by i.nom, i.prenom, ii.date_inscription 	";
//			$this->p($sql);
			$data=$db->getrows($sql);
			$res2= '<table class="toc  sortable">';
			$res2.='<thead>';
			$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Nom</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contact</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Naissance</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Inscription</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Adhésion</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Envoi carte</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Radiation</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Motif</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Origine</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type origine</center></b>';
//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Décès</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
			$res2.='</th></tr>';
			$res2.='</thead>';
			$res2.='<tbody>';
			for ($i=0;$i<count($data);$i++)
			{
				($data[$i]["origine"]=="NULL")? $data[$i]["origine"]="" : null;
				$idindividus.=$data[$i]["id_individu"].",";
				$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
				$res2.= "<tr><td>".($i+1);
				$res2.='</td><td>'.$data[$i]["libelle_inscription"];
				$res2.='</td><td>'.$arrayIndividu["nom"];
				$res2.='</td><td>'.$arrayIndividu["contacts"];
				$res2.='</td><td>'.$arrayIndividu["date_naissance"];
				$res2.='</td><td>'.$data[$i]["date_inscription"];
				$res2.='</td><td>'.$data[$i]["date_adhesion"]."<br/> Document d'adhésion : ".$this->descripteur_document_sans_lien("organisme",$data[$i]["id_document_adhesion"]);
				$res2.='</td><td>'.$data[$i]["date_envoi_carte"];
				$res2.='</td><td>'.$data[$i]["date_radiation"];
				$res2.='</td><td>'.$data[$i]["libelle_radiation"];
				$res2.='</td><td>'.$data[$i]["origine"];
				$res2.='</td><td>'.$data[$i]["libelle_origine"];
//				$res2.='</td><td>'.$arrayIndividu["date_deces"];
				$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
				$res2.='</td></tr>';
			}
			$res2.='</tbody>';
			$res2.='</table>'.$this->getUserStamp('n','o');
			$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
			$criteres=$this->m_postvars["atkfiltre"];
			$titre="<h2><b>"."Inscriptions"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
				

		}
		if ($type=="adhesion")
		{
			$sql="SELECT
			ii.id	as id_entite,
			i.id as id_individu,
			ti.libelle as libelle_inscription,
			ii.date_inscription,
			ii.date_adhesion,
			ii.date_envoi_carte,
			ii.date_derniere_cotisation,
			ii.date_radiation,
			tr.libelle as libelle_radiation,
			ii.origine as origine,
			tor.libelle as libelle_origine,
			o.id as id_organisme,
			o.nom as organisme
			from
			individu_inscription ii LEFT JOIN individu i ON ii.id_individu=i.id
			LEFT JOIN type_inscription ti ON ii.id_type_inscription=ti.id
			LEFT JOIN type_radiation tr ON ii.id_type_radiation=tr.id
			LEFT JOIN type_origine tor ON ii.id_type_origine=tor.id
			LEFT JOIN organisme o ON ii.id_organisme=o.id
			where
			$filtre
			order by i.nom, i.prenom, ii.date_adhesion 	";
			$data=$db->getrows($sql);
			$res2= '<table class="toc  sortable">';
			$res2.='<thead>';

			$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Nom</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contact</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Naissance</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Inscription</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Adhésion</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Envoi carte</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Radiation</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Motif</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Origine</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type origine</center></b>';
//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Décès</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
			$res2.='</th></tr>';
			$res2.='</thead>';
			$res2.='<tbody>';
				
			for ($i=0;$i<count($data);$i++)
			{
				$idindividus.=$data[$i]["id_individu"].",";
				$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
				$res2.= "<tr><td>".($i+1);
				$res2.='</td><td>'.$data[$i]["libelle_inscription"];
				$res2.='</td><td>'.$arrayIndividu["nom"];
				$res2.='</td><td>'.$arrayIndividu["contacts"];
				$res2.='</td><td>'.$arrayIndividu["date_naissance"];
				$res2.='</td><td>'.$data[$i]["date_inscription"];
				$res2.='</td><td>'.$data[$i]["date_adhesion"];
				$res2.='</td><td>'.$data[$i]["date_envoi_carte"];
				$res2.='</td><td>'.$data[$i]["date_radiation"];
				$res2.='</td><td>'.$data[$i]["libelle_radiation"];
				$res2.='</td><td>'.$data[$i]["origine"];
				$res2.='</td><td>'.$data[$i]["libelle_origine"];
	//			$res2.='</td><td>'.$arrayIndividu["date_deces"];
				$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
				
				$res2.='</td></tr>';
			}
			$res2.='</tbody>';
			$res2.='</table>'.$this->getUserStamp('n','o');
			$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
			$criteres=$this->m_postvars["atkfiltre"];
			$titre="<h2><b>"."Adhésions"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		}
		if ($type=="radiation")
		{
			$sql="SELECT
			ii.id as id_entite,
			i.id as id_individu,
			ti.libelle as libelle_inscription,
			ii.date_inscription,
			ii.date_adhesion,
			ii.date_envoi_carte,
			ii.date_derniere_cotisation,
			ii.date_radiation,
			tr.libelle as libelle_radiation,
			ii.origine as origine,
			tor.libelle as libelle_origine,
			o.id as id_organisme,
			o.nom as organisme
			from
			individu_inscription ii LEFT JOIN individu i ON ii.id_individu=i.id
			LEFT JOIN type_inscription ti ON ii.id_type_inscription=ti.id
			LEFT JOIN type_radiation tr ON ii.id_type_radiation=tr.id
			LEFT JOIN type_origine tor ON ii.id_type_origine=tor.id
			LEFT JOIN organisme o ON ii.id_organisme=o.id
			where
			$filtre
			order by i.nom, i.prenom, ii.date_radiation	";
			$data=$db->getrows($sql);
			$res2= "<table class=\"toc\">";
			$res2.='<thead>';
			$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Nom</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contact</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Naissance</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Inscription</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Adhésion</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Envoi carte</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Radiation</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Motif</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Origine</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type origine</center></b>';
//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Décès</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
			$res2.='</th></tr>';
			$res2.='</thead>';
			$res2.='<tbody>';
			for ($i=0;$i<count($data);$i++)
			{
				$idindividus.=$data[$i]["id_individu"].",";
				$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
				$res2.= "<tr><td>".($i+1);
				$res2.='</td><td>'.$data[$i]["libelle_inscription"];
				$res2.='</td><td>'.$arrayIndividu["nom"];
				$res2.='</td><td>'.$arrayIndividu["contacts"];
				$res2.='</td><td>'.$arrayIndividu["date_naissance"];
				$res2.='</td><td>'.$data[$i]["date_inscription"];
				$res2.='</td><td>'.$data[$i]["date_adhesion"];
				$res2.='</td><td>'.$data[$i]["date_envoi_carte"];
				$res2.='</td><td>'.$data[$i]["date_radiation"];
				$res2.='</td><td>'.$data[$i]["libelle_radiation"];
				$res2.='</td><td>'.$data[$i]["origine"];
				$res2.='</td><td>'.$data[$i]["libelle_origine"];
//				$res2.='</td><td>'.$arrayIndividu["date_deces"];
				$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
				
				$res2.='</td></tr>';
			}
			$res2.='</tbody>';
			$res2.='</table>'.$this->getUserStamp('n','o');
			$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
			$criteres=$this->m_postvars["atkfiltre"];
			$titre="<h2><b>"."Radiations"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		}

		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);

	}

}
?>