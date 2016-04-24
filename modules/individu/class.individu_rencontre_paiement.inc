<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class individu_rencontre_paiement extends assMetaNode {
	var $table = "individu_rencontre_paiement";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	//	$policy->setOrder("id");
	}
	function individu_rencontre_paiement() {
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id",
				"id_individu_rencontre",
				"libelle",
				"montant_versement",
				"date_reglement",
					"id_compte_financier",
				"id_reglement",
				"id_banque",
				"numero_cheque",
				"ecritures",
				
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)				,
				"Compléments" => array (
				"id_rencontre",
				"id_individu",
				"id_ecriture_participation",
				"id_ecriture_reglement"
								)
			
					
				), AF_NO_LABEL));
				$this->atkMetaNode();
				$this->atkNode("individu_rencontre_paiement", NF_ADD_LINK| NF_MRA| NF_ADDAFTERADD | NF_COMPACT );
				
				//				$this->add(new atkManyToOneRelation("id_rencontre", "organisme.rencontre", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
				$this->add(new atkAttribute("id_rencontre",AF_HIDE | AF_FORCE_LOAD));
				
				$this->add(new atkAttribute("id",AF_HIDE | AF_FORCE_LOAD));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY| AF_FORCE_LOAD));
				$this->setSecurityAlias("organisme.organisme");
//			$this->add(new atkManyToOneRelation("id_individu", "individu.individu_simple", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
			
				$c50 = & $this->add(new atkManyToOneRelation("id_individu_rencontre", "individu.rencontre_i", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$c50->setDestinationFilter(" individu_rencontre.id in (select individu_rencontre.id from individu_rencontre 
						where id_rencontre=[id_rencontre] ) ");
				
				$this->add(new atkNumberAttribute("montant_versement", AF_OBLIGATORY, 12, 2));
				$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY));
				$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkManyToOneRelation("id_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkAttribute("numero_cheque",NULL,20),NULL,1190);
				
				$this->add(new atkDummyAttribute("ecritures"));
		$c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK|AF_FORCE_LOAD| AF_OBLIGATORY));
		$c12->addDestinationFilter("( code like '51%' or code like '53%') and usuel='1' and id_organisme in (select id_organisme from organisme_rencontre where id ='[id_rencontre]' ) ");

					
				$this->add(new atkDummyAttribute("descripteur_individu_rencontre_paiement","descripteur_individu_rencontre_paiement",AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),NULL,5);
		//		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setOrder(" date_reglement DESC ");

				
	}
	function descripteur_individu_rencontre_paiement_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre_individu_paiement($record["id"]),120);
	}
	function action_admin($handler) {

						global $config_recordsperpage;
		$config_recordsperpage = 200;
		return $handler->action_admin();
	}

	
	function validate(&$record, $mode)
	{
//$this->p($record);
		$this->RazDestinationFilters();
		if ($record["montant_versement"] >0)
		{
			if ($record["date_reglement"]=="")
			{				
				atkTriggerError($record, $this->getAttribute("date_reglement"), "En cas de règlement vous devez préciser la date");
				return false;
			}
			if ($record["id_compte_financier"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_financier"), "Vous devez choisir un compte de finance");
				return false;
			}
			if ($record["id_reglement"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_reglement"), "Vous devez choisir un type de règlement");
				return false;
			}
				
			if ($record["id_reglement"]["id"]!=1 && $record["numero_cheque"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque");
				return false;
			}
			if ($record["id_reglement"]["id"]==1 && $record["numero_cheque"]=="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque");
				return false;
			}
			
		} else 
		{
			atkTriggerError($record, $this->getAttribute("montant_versement"), "Pas de montant ?");
			return false;
		}
	
		$record["id_individu"]=$record["id_individu_rencontre"]["id_individu"]["id"];
		if ($mode=="update") $this->supprimer_ecritures($record);
		
		$this->creer_ecritures_comptables($record);
//		$this->p($record);
		return true;
	
	}
	
	function id_ecriture_participation_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_participation"]);
	}
	function id_ecriture_reglement_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_reglement"]);
	}
	function postUpdate($record)
	{
		$this->mise_a_jour_type_ecriture($record);
		parent::postUpdate($record);
		return true;
	}
	function postAdd($record)
	{
		$db = & atkGetDb();
		$data=$db->getrows('Select max(id) as id from individu_rencontre_paiement');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{    if (!empty($record["id_ecriture_participation"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_participation"],$this->type_ecriture_rencontre_participant_paiement			,$record["id"]);	}
	if (!empty($record["id_ecriture_reglement"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_rencontre_participant_paiement,$record["id"]);	}
	return true;
	}
		
	function preDelete(& $record) {
		$this->RazDestinationFilters();
		$this->supprimer_ecritures($record);
		parent :: preDelete($record);
		return true;
	}
function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_participation = $record["id_ecriture_participation"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
	
		if ($id_ecriture_reglement == "" && $id_ecriture_participation == "") {
			return true;
		} else
		{
			if (isset ($id_ecriture_reglement))
					
			{$data = $db->getrows("select r.date_remise_banque as date_remise_banque
					from organisme_remise_banque r, organisme_ligne_ecriture_comptable l, individu_rencontre c
					where c.id_ecriture_reglement= $id_ecriture_reglement
					and  l.id_ecriture=c.id_ecriture_reglement
					and r.id=l.id_remise
					and id_type_banque  is not null ");
			if (isset ($data[0]["date_remise_banque"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement a été remis en banque<br>", "critical");
			}
			$data = $db->getrows("select l.id_releve
					from organisme_ligne_ecriture_comptable l
					where l.id_ecriture=$id_ecriture_reglement ");
			if (isset ($data[0]["id_releve"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement a été rapproché<br>", "critical");
			}
			}
			if (isset ($id_ecriture_participation)) {
				$this->supprimer_ecriture_comptable($id_ecriture_participation);
				$record["id_ecriture_participation"]="";
			}
			if (isset ($id_ecriture_reglement)) {
				$this->supprimer_ecriture_comptable($id_ecriture_reglement);
				$record["id_ecriture_reglement"]="";
			}

		}
		return true;
	}

	
function creer_ecritures_comptables(& $record) {
	$db = & atkGetDb();
		$id_individu_rencontre=$record["id_individu_rencontre"]["id"];
		$data=$db->getrows("select id_individu from individu_rencontre where id=$id_individu_rencontre");
		$record["id_individu"]=$data[0]["id_individu"];
		$id_individu = $record['id_individu'];
		
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
				$organisme = $db->getrows("SELECT id_organisme
				from organisme_rencontre where id='" . $record["id_rencontre"] . "'");
		$id_organisme = $organisme[0]["id_organisme"];
		$rencontre = $db->getrows("SELECT ore.libelle as libelle , ore.date_debut as date_debut ,
				ore.id_type_rencontre as id_type_rencontre, tr.libelle as libelle_type_rencontre
				from organisme_rencontre ore, type_rencontre tr
				where ore.id='" . $record["id_rencontre"] . "' and ore.id_type_rencontre=tr.id ");
		
		$individu = $db->getrows("SELECT nom, prenom
				from individu where id='" . $record["id_individu"] . "'");
		$rang = $db->getrows("SELECT
				o.id_compte_dons as id_compte_dons,

				o.id_compte_adherents as id_compte_adherents,
				o.id_compte_caisse as id_compte_caisse,
				o.id_compte_participation_manifestation as id_compte_participation_manifestation,

				o.id_journal_depenses as id_journal_depenses,
				o.id_journal_recettes as id_journal_recettes,
				o.id_journal_banque_courant as id_journal_banque_courant,
				o.id_journal_caisse as id_journal_caisse,
				jc.id_compte_banque as id_compte_banque
				FROM organisme o, organisme_journal_comptable jc
				where o.id=$id_organisme and o.id_journal_banque_courant=jc.id ");
		$id_journal_depenses = $rang[0]["id_journal_depenses"];
		$id_journal_recettes = $rang[0]["id_journal_recettes"];
		$id_journal_caisse = $rang[0]["id_journal_caisse"];
		$id_journal_banque_courant = $rang[0]["id_journal_banque_courant"];
		$id_compte_banque = $rang[0]["id_compte_banque"];
		$id_compte_caisse = $rang[0]["id_compte_caisse"];
		$id_compte_adherents = $rang[0]["id_compte_adherents"];
		$libelle_type_rencontre = $rencontre[0]["libelle_type_rencontre"];
		$id_compte_participation_manifestation = $rang[0]["id_compte_participation_manifestation"];
		$compte = $db->getrows("SELECT code from organisme_compte
				where id='" . $id_compte_participation_manifestation . "'");
		$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		/*		echo $compte[0]["code"];
		 echo '</br>';
		echo str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		die();
		*/

		$compte = $db->getrows("SELECT id from organisme_compte
				where code=$comptecode and id_organisme='" . $id_organisme . "'");
		if (count($compte) == 0) {
			// Créer le compte
			$user = getUser();
			$iduser = $user["id"];
			$sql = "insert into organisme_compte ( id_organisme, code, libelle, usuel, id_creation, date_creation, id_modification,  date_modification)
			values
			( '$id_organisme' ,'$comptecode', '$libelle_type_rencontre', '1',  '$iduser', UTC_TIMESTAMP(),  '$iduser' , UTC_TIMESTAMP() )";
			$data = $db->query($sql);
			$data = $db->getrows("select max(id) as last_id from organisme_compte ");
			$id_compte_participation_manifestation = $data[0]["last_id"];
			$nextid = $data[0]["last_id"] + 1;
			$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_compte' ");
		} else {
			$id_compte_participation_manifestation = $compte[0]["id"];
		}
		$date_reglement = $this->dateatktodb($record["date_reglement"]);
		$libelle = $rencontre[0]["date_debut"] . ' . ' . $rencontre[0]["libelle"] . '. Participation aux frais de ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle,$date_reglement);
		$record["id_ecriture_participation"] = $id_ecriture;
		$id_type_reglement = $record["id_reglement"]["id"];
		$numero_piece = $record["numero_cheque"];
		$id_type_banque = $record["id_banque"]["id"];
		$debit = $record["montant_versement"];
		// montant versement
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$credit = $record["montant_versement"];
		;
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_participation_manifestation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if ($id_type_reglement == 1) {
			// chéque à remettre en banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$credit = $record["montant_versement"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
		} elseif ($id_type_reglement == 3) {
				// epèces reçues en caisse
				$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
				$record["id_ecriture_reglement"] = $id_ecriture;
				$credit = $record["montant_versement"];
				$debit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
				$debit = $record["montant_versement"];
				$credit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement, null);
			}
			elseif ($id_type_reglement == 2)
			{
			// virement
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$credit = $record["montant_versement"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
			}		
		return;
	}
	
	
	function RazDestinationFilters()
	{
	
		$attrib=$this->getAttribute("id_compte_financier")	;
		$attrib->setDestinationFilter("");
		$attrib=$this->getAttribute("id_individu_rencontre")	;
		$attrib->setDestinationFilter("");

		return true;

	}
	function descriptor_def() {
		return "[id]";
	}
/*	public function getCustomMraHtml()
	{
		$list = $this->getAttribute('id_document_facture')->edit(null, null, null);
		return $list;
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['justificatif'] = "justificatif";
	}
	public function action_justificatif()
	{

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
	*/
	
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

}
?>