<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgNumberExpressionAttribute");
class remise_banque extends assMetaNode {
	var $table = "organisme_remise_banque";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("bordereau_remise",AF_FORCE_LOAD);
		$policy->setOrder("libelle");
	}
	function remise_banque() {
		$this->atkMetaNode();
		$this->atkNode("remise_banque", NF_ADD_LINK | NF_MRA | NF_NO_ADD | NF_NO_DELETE | NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"descripteur_remise_banque",
						"id_organisme",
						"id_remise_organisme",
						"id_releve",
						"id_type_remise_banque",
						"libelle",
						"debit",
						"credit",
						"nombre_cheques",

						"id_compte_banque",
						"id_remise_banque",
						"id_document_remise",
						"date_remise_banque",
						"bordereau_remise",
						"imprimer_remise",

						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Lignes" => array (
						"lignes"
				)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_remise_banque",0,AF_COMPACT),NULL, 6);
		$this->add(new atkNumberAttribute("id_remise_organisme",0,AF_FORCE_LOAD), null, 10);
		$this->add(new atkNumberAttribute("id_releve",0,AF_FORCE_LOAD), null, 15);
		$this->add(new atkManyToOneRelation("id_type_remise_banque", "table.type_remise_banque", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK), null, 20);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE| AF_OBLIGATORY), null, 30);
		$this->add(new atgNumberExpressionAttribute("debit", ' select sum(debit) from organisme_ligne_ecriture_comptable where id_remise = [table].id
				', 0, 0), null, 40);
		$this->add(new atgNumberExpressionAttribute("credit", ' select sum(credit) from organisme_ligne_ecriture_comptable where id_remise = [table].id
				', 0, 0), null, 50);
		$this->add(new atgNumberExpressionAttribute("nombre_cheques", ' select count(distinct numero_piece) from organisme_ligne_ecriture_comptable
				where id_remise = [table].id
				', 0, 0), null, 16);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_FORCE_LOAD | AF_RELATION_AUTOCOMPLETE), null,10);
		$this->add(new atkManyToOneRelation("id_compte_banque", "organisme.compte", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK| AF_FORCE_LOAD | AF_RELATION_AUTOCOMPLETE), null, 80);
		$this->add(new atkNumberAttribute("id_remise_banque",0,AF_FORCE_LOAD), null, 90);
		$this->add(new atkDateAttribute("date_remise_banque", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_FORCE_LOAD), null, 100);
		$this->add(new atgFileManyToOneRelation("id_document_remise", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), null, 110);
		//		$this->add(new atkParserAttribute("endos_cheque", "env", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
		$this->add(new atkfckattribute("bordereau_remise", "", AF_FORCE_LOAD | AF_HIDE_LIST, array (
				'ToolbarSet' => 'Default',
				'Width' => '100%',
				'Height' => '150px'
		) ), null, 111);
		$this->add(new atkParserAttribute("imprimer_remise", "env", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);

		$this->add(new atkOneToManyRelation("lignes", "organisme.ligne_ecriture_comptable", "id_remise", AF_HIDE_LIST));
		$this->m_securityMap["pointer"] = "view";
		$this->m_securityMap["depointer"] = "view";
		$this->m_securityMap["document"] = "view";
		$this->m_securityMap["imprimer"] = "view";
		$this->m_securityMap["clore"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		//			$this->m_securityMap["endoscheque"] = "view";
		$this->m_securityMap["document"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,7 );
		//		$this->setIndex("libelle");
		$this->setOrder("date_creation desc");
	}
	function nombre_cheques_display($record, $mode) {
		if (isset ($record["nombre_cheques"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_remise='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre_cheques"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function libelle_display($record, $mode) {
		return $this->decoupe_affichage_colonne($record["libelle"], 40);
	}
	function descripteur_remise_banque_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_remise_banque($record["id"],'o').'<br />',100);
	}

	function action_admin($handler)
	{
		$id_compte = $this->m_postvars["id_compte"];
		if (!empty($id_compte))
		{
			$db = & atkGetDb();
			$data = $db->getrows("SELECT id_organisme from organisme_compte
					where id =$id_compte");
			$id_organisme = $data[0]["id_organisme"];
			global $g_user;
			$userid = $g_user["id"];
			$sql = "UPDATE organisme_ligne_ecriture_comptable
			set id_remise=null
			where id_compte=$id_compte
			and (
			id_remise in (select distinct id from organisme_remise_banque
			where id_compte_banque=$id_compte
			and  date_remise_banque is null)
			or id_remise not in (select distinct id from organisme_remise_banque
			where id_compte_banque=$id_compte)
			)";
			$db->query($sql);
			$data = $db->getrows("SELECT distinct id , rib
					from organisme_compte
					where id=$id_compte
					and id in (select distinct id_compte
					from organisme_ligne_ecriture_comptable
				 where id_remise is null and id_compte=$id_compte
			)");
			for ($i = 0; $i < count($data); $i++) {
				$id_compte = $data[$i]["id"];
				$rib = $data[$i]["rib"];
				$data1 = $db->getrows("SELECT distinct id_type_reglement
						from organisme_ligne_ecriture_comptable
						where id_compte=$id_compte
						and id_remise is null
						and id_type_reglement in ('1','3')
							
						");
				for ($j = 0; $j < count($data1); $j++) {
					$id_type_reglement = $data1[$j][id_type_reglement];
					if ($id_type_reglement == '1') {
						$id_type_remise_banque = '1';
						$libelle = "Remise de chèques sur le compte " . $rib . ". (" . gmdate(c) . ").";
					}
					if ($id_type_reglement == '3') {
						$id_type_remise_banque = '2';
						$libelle = "Remise d'espèces sur le compte " . $rib . ". (" . gmdate(c) . ").";
					}
					$libelle=escapeSQL($libelle);
					$db->query("INSERT into organisme_remise_banque
							(id_type_remise_banque,
							libelle,
							id_organisme,
							id_compte_banque,
							id_creation,
							date_creation,
							id_modification,
							date_modification)
							VALUES
							(
							'$id_type_remise_banque',
							'$libelle',
							'$id_organisme',
							'$id_compte',
							'$userid',
							UTC_TIMESTAMP(),
							'$userid',
							UTC_TIMESTAMP())
							");
					$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_organisme_remise_banque' ");
					$query = "select max(id) as last_id from organisme_remise_banque where id_organisme=$id_organisme";
					$rows = $db->getrows($query);
					$lastid = $rows[0]["last_id"];
					$db->query("Update organisme_ligne_ecriture_comptable
							set id_remise='$lastid'
							where id_organisme=$id_organisme
							and id_remise is null
							and id_compte=$id_compte
							and id_type_reglement=$id_type_reglement
							and debit>0 ");
				}
			}
			$db->query("DELETE from organisme_remise_banque
					where id_compte_banque=$id_compte
					and id not in (select distinct id_remise from organisme_ligne_ecriture_comptable
				 where id_compte_banque=$id_compte and id_remise is not null)
					");

		}
		return $handler->action_admin();
	}

	function action_clore($handler) {
		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$idremise = $this->m_postvars["atkselector"];
		$this->action_imprimer();
		$record = $db->getrows("SELECT id_organisme, id_remise_organisme
				FROM organisme_remise_banque
				where $idremise");
		$id_remise_organisme = $record[0]["id_remise_organisme"];
		$id_organisme = $record[0]["id_organisme"];
		if (empty ($id_remise_organisme)) {
			$id_organisme = $record[0]["id_organisme"];
			$idremiseorganisme = $this->getProchainIdRemise($id_organisme);
			$db->query("UPDATE  organisme_remise_banque
					set id_remise_organisme='$idremiseorganisme',
					date_remise_banque=UTC_TIMESTAMP(),
					id_modification='$userid',
					date_modification=UTC_TIMESTAMP()
					where $idremise");
			$tableau = explode('=', $idremise);
			$idremise = $tableau[1];
			$db->query("UPDATE  organisme_ligne_ecriture_comptable
					set date_operation=UTC_TIMESTAMP(),
					date_valeur=UTC_TIMESTAMP(),
					id_modification='$userid',
					date_modification=UTC_TIMESTAMP()
					where id_remise= $idremise");
		}
		$this->redirect();
	}
	function imprimer_remise_edit($record, $mode) {
		$url = href(dispatch_url("organisme.remise_banque", "imprimer", array (
				"atkselector" => "organisme_remise_banque.id='" . $record["id"] . "'",
				"atkexport" => 'o',
				"id" => $record["id"]
		)), atktext("Impression de la remise <br>", "core"), SESSION_NESTED);
		return $url;
	}

	/*			function endos_cheque_edit($record, $mode) {

	$url = href(dispatch_url("organisme.remise_banque", "document", array (
			"atkselector" => "organisme_remise_banque.id='" . $record["id"] . "'",
			"id" => $record["id"],
			"atkcode" => "1"
	)), atktext("Impression des endos de chèques <br>", "core"), SESSION_NEW, false, 'target="_blank"');
	return $url;

	}
	*/
	function etat_remise_edit($record, $mode) {
		$idremise = $record["id"];
		$url = href(dispatch_url("organisme.v_organisme_remise_banque", "document", array (
				"atkselector" => "organisme_remise_banque.id='" . $record["id"] . "'",
				"id" => $idremise,
				"atkfilter" => "v_organisme_remise_banque.id_remise='" . $record["id"] . "'",
				"atkdoctpl" => "remise_banque.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "1"
		)), atktext("Impression de la remise en banque (ne marche pas) <br>", "core"), SESSION_NEW, false, 'target="_blank"');
		return $url;
	}
	function action_imprimer() {
		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$idremise = $this->m_postvars["atkselector"];
		$query = & $db->createQuery();
		$query->addTable("organisme_remise_banque");
		$query->addJoin("organisme_ligne_ecriture_comptable", "", "organisme_remise_banque.id = organisme_ligne_ecriture_comptable.id_remise", false);
		$query->addJoin("organisme", "", "organisme_remise_banque.id_organisme = organisme.id", false);
		$query->addJoin("individu", "", "organisme_ligne_ecriture_comptable.id_individu = individu.id", true);
		$query->addJoin("organisme_compte", "", "organisme_remise_banque.id_compte_banque = organisme_compte.id", false);
		//			$query->addJoin("type_banque", "", "organisme_compte.id_banque = type_banque.id", false);
		$query->addJoin("type_remise_banque", "", "organisme_remise_banque.id_type_remise_banque=type_remise_banque.id", false);
		$query->addJoin("type_banque", "", "organisme_ligne_ecriture_comptable.id_type_banque = type_banque.id", true);
		$query->addField("organisme.nom as organisme");
		$query->addField("organisme_compte.rib as rib");
		$query->addField("individu.nom as nom_individu");
		$query->addField("individu.prenom as prenom_individu");
		$query->addField("type_remise_banque.libelle as type_remise");
		$query->addField("organisme_remise_banque.id_remise_organisme as numero_remise_organisme");
		$query->addField("date_format(organisme_remise_banque.date_remise_banque, '%d/%m/%Y') as date_remise_banque");
		$query->addField("organisme_ligne_ecriture_comptable.numero_piece as numero_piece");
		$query->addField("type_banque.libelle as libelle_banque");
		$query->addField("sum(organisme_ligne_ecriture_comptable.debit) as debit");
		$query->addCondition($idremise);
		$query->addGroupBy("organisme_ligne_ecriture_comptable.numero_piece  ");
		$query->addOrderBy("individu.nom, individu.prenom");
		$stuff = $db->getrows($query->buildSelect());

		$data = "<table border='1'>";
		$debittotal = 0;
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {

			if ($i == 0) {
				$data.= '<tr><td>' . "Organisme : " .'</td><td><b>' .$stuff[$i]["organisme"].'</td></tr>';
				$data.=  '<tr><td>'."RIB : ".'</td><td><b>'. $stuff[$i]["rib"].'</td></tr>';
				$data.= '<tr><td>'. "Numéro de remise : ".'</td><td><b>'.$stuff[$i]["numero_remise_organisme"].'</td></tr>';
				$data.= '<tr><td>'."Date de remise : ".'</td><td><b>'. $stuff[$i]["date_remise_banque"].'</td></tr>';
				$data.= '<tr><td>'.'#'.'</td><td>'. 'Nom'.'</td><td>'. 'Banque'.'</td><td>'. 'Numéro chèque'.'</td><td>'. 'Montant</b>'.'</td><td>'.'</td></tr>';
				$data.= '<tr><td>'.($i +1).'</td><td>'.$stuff[$i]["nom_individu"] . ' ' . $stuff[$i]["prenom_individu"].'</td><td>'.$stuff[$i]["libelle_banque"].'</td><td>'.$stuff[$i]["numero_piece"].'</td><td>'. $stuff[$i]["debit"].'</td><td>'." Euro".'</td></tr>';
				$debittotal += $stuff[$i]["debit"];

			} else {
				$data.= '<tr><td>'.($i +1).'</td><td>'.$stuff[$i]["nom_individu"] . ' ' . $stuff[$i]["prenom_individu"].'</td><td>'.$stuff[$i]["libelle_banque"].'</td><td>'.$stuff[$i]["numero_piece"].'</td><td>'.$stuff[$i]["debit"].'</td><td>'." Euro".'</td></tr>';
				$debittotal += $stuff[$i]["debit"];
					
			}
		}
		$data.='<tr><td>' . "Total de la remise : ".'</td><td><b>'.  $debittotal  . " Euro".'</td></tr>';
		$data.= '<tr><td>'."Nombre de chèques : " .'</td><td><b>'. $i.'</td></tr>';
		$data.= '<tr><td>'."<br /> Signature : <br /><br /></td><td><br /></b>".'</td></tr>';
		$data.= "</table >";
		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="UPDATE organisme_remise_banque
				set bordereau_remise='".addcslashes($data,"'")."',
				id_modification= $userutilisateur,
				date_modification=UTC_TIMESTAMP()

				where $idremise and date_remise_banque is null";

		$db->query($sql);
		$page =   &atkinstance("atk.ui.atkpage");
		$page->addContent( $data);

	}

	function preAdd(& $record) {
		parent :: preAdd($record);
	}
	function preDelete(& $record) {
		$idremise = $record["id"];
		if ($record["date_remise_banque"]["year"] > 0) {
			echo "La remise a été effectuée. Il est impossible de la supprimer.";
			die();
		}
		$db = & atkGetDb();
		$db->query("UPDATE  organisme_ligne_ecriture_comptable
				set id_remise=null,
				id_modification='$userid',
				date_modification=UTC_TIMESTAMP()
				where id_remise=$idremise");
	}
	/*function assignDocumentVars(& $documentWriter, $selector) {

	switch ($this->m_postvars["atkcode"]) {
	case 1 :

	$documentWriter->display($template_file, "output.odt", $tplvars);

	$org = & atkGetNode("organisme.organisme");
	$orgrecord = $org->selectDb("organisme.id=" . $this->m_postvars["id"], "", "", "", "", "view");
	$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0], $prefix = "o.");
	$documentWriter->assignDocumentGenericVars();
	break;
	}
	}
	*/
	/*
	 * 		$record["id_remise_organisme"] = $this->getProchainIdRemise($id_organisme);
	*/
	function getProchainIdRemise($id_organisme) {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT prochain_id_remise_en_banque FROM organisme where id='" . $id_organisme . "'");
		$id_remise = $data[0]["prochain_id_remise_en_banque"];
		$db->query("UPDATE organisme set prochain_id_remise_en_banque=prochain_id_remise_en_banque+1 where id=$id_organisme ");
		return $id_remise;
	}
	function recordActions($rec, & $actions, & $mraactions) {
		//		parent :: recordActions($rec, $actions, $mraactions);
		$mraactions['pointer'] = "pointer";
		$mraactions['depointer'] = "depointer";
		$actions["clore"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=clore&atkselector=[pk]", SESSION_NESTED);
		$actions["imprimer"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=imprimer&atkselector=[pk]&id=[pk]", SESSION_NESTED);
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
		$record = $db->getrows("SELECT id_organisme , id_compte_banque
				FROM organisme_remise_banque
				where $select[0]");
		$id_organisme = $record[0]["id_organisme"];
		$id_compte_banque = $record[0]["id_compte_banque"];
		$record = $db->getrows("SELECT max(id) as idmax from organisme_releve_banque where
				id_organisme =$id_organisme and date_cloture_releve is null and id_compte_banque=$id_compte_banque ");
		$id_releve = $record[0]["idmax"];
		if (empty ($id_releve)) {
			return;
		}
		$sql = 'update organisme_remise_banque set id_releve=' . $id_releve . '
				where id in (' . $chaineidfonction . ')';
		$db->query($sql);
		$sql = 'update organisme_ligne_ecriture_comptable set id_releve=' . $id_releve . '
				where id_remise in (' . $chaineidfonction . ')';
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
		$sql = 'update organisme_remise_banque set id_releve=null
				where id in (' . $chaineidfonction . ') and id_releve is not null and id_releve in (select id from organisme_releve_banque where date_cloture_releve is null)';
		$db->query($sql);
		$sql = 'update organisme_ligne_ecriture_comptable set id_releve=null
				where id_remise in (' . $chaineidfonction . ')';
		$db->query($sql);
		$this->redirect();
	}
	function rowColor($record) {
		if (!empty ($record["date_remise_banque"])) {
			return $this->couleurplusmois;
		} else {
			return $this->couleursemaine;
		}
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
		$id_remise_banque=$this->m_postvars["id_remise_banque"];
		$sql="SELECT
		bordereau_remise,
		id_document_remise
		from organisme_remise_banque
		WHERE
		id=$id_remise_banque
		";
		$data=$db->getrows($sql);

		$descripteur="<h2><b>"."Remise en banque : ".$id_remise_banque."</h2><br/>";
		$descripteur.=strip_tags($this->descripteur_remise_banque($id_remise_banque, 'n'),"<b><br><br/><img><div>");
		$descripteur.="<br/><div ".$this->m_styleTitreLigne."<b>"."Lignes d'écritures de la remise en banque : ".$id_remise_banque."</b></div><br/><br/>";
		$node_ligne=newNode("organisme.ligne_ecriture_comptable",true);
		$descripteur.=$node_ligne->action_admin_liste("remise",$id_remise_banque,$id_organisme);
		
		(!empty($data[0]["bordereau_remise"])) ? $descripteur.='<br/><div '.$this->m_styleTitreLigne.'>Bordereau AssoCope : <br/><br/>'.$data[0]["bordereau_remise"]."</div><br/>" : $descripteur.='<br/><div '
				.$this->m_styleTitreLigne.'>Bordereau AssoCope : </div><br/>';
		($data[0]["id_document_remise"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_document_remise"],'n',$lien_recepisse) : $lien_recepisse="";
		$descripteur.='<br/><div '.$this->m_styleTitreLigne.'>Récépissé de la banque : '.$lien_recepisse."</div><br/>";
		unset ($node_ligne);
		$this->page_output($descripteur);


	}
}
?>