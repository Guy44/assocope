<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class individu_rencontre_remboursement extends assMetaNode {
	var $table = "individu_rencontre_remboursement";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
//		$policy->addFlags("id_ecriture_depense", "id_ecriture_reglement", AF_READONLY|AF_FORCE_LOAD);
	//	$policy->setOrder("id");
	}
	function individu_rencontre_remboursement() {
		$this->add(new atkTabbedPane("Pane1", array (
			"G�n�ral" => array (
				"id",
				"id_individu_rencontre",
				"libelle",
				"montant_fourniture",
				"date_reglement",
				"id_compte_financier",
				"id_reglement",
				"numero_cheque",
				"numero_facture",
				"id_document_facture",
				
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)				,
				"Compl�ments" => array (
				"id_rencontre",
				"id_individu",
				"id_ecriture_reglement",
				"id_ecriture_depense",
				)
			
					
				), AF_NO_LABEL));
				$this->atkMetaNode();
				$this->atkNode("individu_rencontre_remboursement", NF_ADD_LINK| NF_MRA| NF_ADDAFTERADD | NF_COMPACT );
				
				
//				$this->add(new atkManyToOneRelation("id_rencontre", "organisme.rencontre", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
				$this->add(new atkAttribute("id_rencontre",AF_HIDE | AF_FORCE_LOAD));
				
				
				$this->add(new atkAttribute("id",AF_HIDE | AF_FORCE_LOAD));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY| AF_FORCE_LOAD));
				$this->setSecurityAlias("organisme.organisme");
 //				$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
 	
			$c50 = & $this->add(new atkManyToOneRelation("id_individu_rencontre", "individu.rencontre_i", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
	$c50->setDestinationFilter(" individu_rencontre.id in (select individu_rencontre.id from individu_rencontre where id_rencontre=[id_rencontre] ) ");
				
				$this->add(new atkNumberAttribute("montant_fourniture", AF_OBLIGATORY, 12, 2));
				$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY));
				$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkDummyAttribute("ecritures"));

$c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK|AF_FORCE_LOAD| AF_OBLIGATORY));
$c12->addDestinationFilter("( code like '51%' or code like '53%') and usuel='1' and id_organisme in (select id_organisme from organisme_rencontre where id ='[id_rencontre]' ) ");

				$this->add(new atgFileManyToOneRelation("id_document_facture", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
				$this->m_securityMap["justificatif"] = "view";
				
				$this->add(new atkDummyAttribute("descripteur_individu_rencontre_remboursement","descripteur_individu_rencontre_remboursement",AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),NULL,5);
			//	$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setOrder(" date_reglement DESC ");
	}
	function descripteur_individu_rencontre_remboursement_display($record, $mode) {
	return $this->decoupe_affichage_colonne($this->descripteur_rencontre_individu_remboursement($record["id"]),120);
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
		if ($record["montant_fourniture"] >0)
		{
			if ($record["date_reglement"]=="")
			{				
				atkTriggerError($record, $this->getAttribute("date_reglement"), "En cas de r�glement vous devez pr�ciser la date");
				return false;
			}
			if ($record["id_compte_financier"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_financier"), "Vous devez choisir un compte de finance");
				return false;
			}
			if ($record["id_reglement"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_reglement"), "Vous devez choisir un type de r�glement");
				return false;
			}
				
			if ($record["id_reglement"]["id"]!=1 && $record["numero_cheque"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Num�ro de ch�que alors que le mode de r�glement pr�cise que ce n'est pas un r�glement par ch�que");
				return false;
			}
			if ($record["id_reglement"]["id"]==1 && $record["numero_cheque"]=="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de num�ro de ch�que alors que le mode de r�glement pr�cise que c'est un r�glement par ch�que");
				return false;
			}
			
		} else 
		{
			atkTriggerError($record, $this->getAttribute("montant_fourniture"), "Pas de montant ?");
			return false;
		}
	
		$record["id_individu"]=$record["id_individu_rencontre"]["id_individu"]["id"];
		if ($mode=="update") $this->supprimer_ecritures($record);
		
		$this->creer_ecritures_comptables($record);
//		$this->p($record);
		return true;
	
	}
	function id_document_facture_display($record, $mode)
	{
		$retour=null;
		if ( $record["id_document_facture"]!=null)
		{$retour .= $this->getAttribute("id_document_facture")->display($record, $mode) ;
		}
		return $retour;
	}
	function id_ecriture_depense_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_depense"]);
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
		$data=$db->getrows('Select max(id) as id from individu_rencontre_remboursement');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{    if (!empty($record["id_ecriture_depense"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_depense"],$this->type_ecriture_rencontre_participant_remboursement,$record["id"]);	}
	if (!empty($record["id_ecriture_reglement"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_rencontre_participant_remboursement,$record["id"]);	}
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
		$id_ecriture_depense = $record["id_ecriture_depense"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "" && $id_ecriture_depense == "") {
			return true;
		}
		if (isset ($id_ecriture_depense)) {
			$this->supprimer_ecriture_comptable($id_ecriture_depense);
		}
		if (isset ($id_ecriture_reglement)) {
			$this->supprimer_ecriture_comptable($id_ecriture_reglement);
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
				from individu where id='" . $record["id_individu"]. "'");
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
		if (strlen($rencontre[0]["id_type_rencontre"])<3)
		{
			$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		}
		else
		{$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 3, "0", STR_PAD_LEFT);
		}
		/*		echo $compte[0]["code"];
		 echo '</br>';
			echo str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
			die();
			*/
	
		$compte = $db->getrows("SELECT id from organisme_compte
				where code=$comptecode and id_organisme='" . $id_organisme . "'");
		if (count($compte) == 0) {
			// Cr�er le compte
			$libelle_type_rencontre=escapeSQL($libelle_type_rencontre);
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
		$libelle = $rencontre[0]["date_debut"] . ' . ' . $rencontre[0]["libelle"] . '. Rembours� � ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle,$date_reglement);
		$record["id_ecriture_depense"] = $id_ecriture;
		$id_type_reglement = $record["id_reglement"]["id"];
		$numero_piece = $record["numero_cheque"];
		$credit = $record["montant_fourniture"];
		// montant remboursement
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$debit = $record["montant_fourniture"];
		;
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_participation_manifestation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
	$id_compte_financier=$record["id_compte_financier"]["id"];
	$sql = "SELECT code
		from organisme_compte where id=$id_compte_financier and id_organisme=$id_organisme";
		$compte = $db->getrows($sql);
		$codecomptefinancier = $compte[0]["code"];
		if (substr($codecomptefinancier, 0, 2) == '53') {
			// ep�ces de la caisse
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement, null);		}
		if (substr($codecomptefinancier, 0, 2) == '51') {
			// banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, null);
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