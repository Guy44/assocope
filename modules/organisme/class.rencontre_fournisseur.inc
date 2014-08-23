<?php
atkimport("atk.assmetanode");
useattrib("development.atgFileManyToOneRelation");
class rencontre_fournisseur extends assMetaNode {
	var $table = "organisme_rencontre_fournisseur";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//				$policy->addFlags("id_ecriture_depense", "id_ecriture_reglement", AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id_rencontre");
	}
	function rencontre_fournisseur() {
		$this->atkMetaNode();
		$this->atkNode("rencontre_fournisseur", NF_ADD_LINK | NF_TRACK_CHANGES | NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkParserAttribute("presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST), NULL, 1);
		$this->add(new atkManyToOneRelation("id_organisme_fournisseur", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atkAttribute("libelle", AF_OBLIGATORY));
		// GG
		$this->add(new atkManyToOneRelation("id_rencontre", "organisme.rencontre", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		$this->add(new atgFileManyToOneRelation("id_document_accord", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkNumberAttribute("montant_prevu", NULL, 12, 2), NULL);
		$this->add(new atkNumberAttribute("montant_fourniture", NULL, 12, 2), NULL);
		$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkAttribute("numero_cheque") );
		$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		//	$this->add(new atkManyToOneRelation("id_banque","table.banque",AF_SEARCHABLE|AF_RELATION_AUTOLINK));
		$this->add(new atkDummyAttribute("ecritures"));
		$c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		$c12->addDestinationFilter("( code like '51%' or code like '53%') and usuel='1' and id_organisme in (select id_organisme from organisme_rencontre where id ='[id_rencontre.id]' ) ");
		$c11 = & $this->add(new atkManyToOneRelation("id_compte_charge", "organisme.compte", AF_RELATION_AUTOLINK|AF_FORCE_LOAD));
		$c11->addDestinationFilter(" ( code like '61%' ) and usuel='1' and id_organisme in (select id_organisme from organisme_rencontre where id ='[id_rencontre.id]' ) ");
		$this->add(new atgFileManyToOneRelation("id_document_facture", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_rencontre_fournisseur","descripteur_rencontre_fournisseur",AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),NULL,5);
		$this->add(new atkDummyAttribute("descripteur_rencontre","descripteur_rencontre",AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),NULL,10);
		$this->add(new atkAttribute("id_ecriture_depense",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),null,20 );
		$this->add(new atkAttribute("id_ecriture_reglement",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),null,30 );
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,40 );
	}
	function descripteur_rencontre_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre($record["id_rencontre"]["id"]),100);
	}
	function descripteur_rencontre_fournisseur_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre_fournisseur($record["id"]),100);
	}

	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_reglement"]) || isset ($record["id_ecriture_depense"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_depense'] . "'"
			), "dispatch.php"), text("Voir"), SESSION_NESTED);
		} else {
			return "Pas d'écritures";
		}
	}
	function descripteur_reglement_display($record, $mode) {
		return $this->descripteur_reglement("rencontre_fournisseur",$record["id"],'o');
	}

	function presence_compta_edit($record, $mode) {
		$id_rencontre = $record["id_rencontre"]["id"];
		$db = & atkGetDb();
		$sql = "SELECT o.nom as nom, date_initialisation_comptabilite  from organisme o
				, organisme_rencontre r where r.id_organisme=o.id and r.id='" . $id_rencontre . "'";
		$data = $db->getrows($sql);
		if ($data[0]["date_initialisation_comptabilite"] != null) {
			return '';
		} else {
			return '<font color="Red"> <b> La comptabilité n\'ayant pas été initialisée pour ' . $data[0]["nom"] . ', la saisie de montant versé ne sera pas prise en compte dans la comptabilité.';
		}
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
		$data=$db->getrows('Select max(id) as id from organisme_rencontre_fournisseur');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_depense"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_depense"],$this->type_ecriture_rencontre_fournisseur,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_rencontre_fournisseur,$record["id"]);
		}
		return true;
	}

	function preDelete(& $record) {
		$this->supprimer_ecritures($record);
		parent :: preDelete($record);
	}
	function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_depense = $record["id_ecriture_depense"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "") {
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
/*	function preAdd(& $record) {
		if ($record["montant_fourniture"] > 0) {
			$this->creer_ecritures_comptables($record);
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$this->supprimer_ecritures($record);
		if ($record["montant_fourniture"] > 0) {
			$this->creer_ecritures_comptables($record);
		}
		parent :: preUpdate($record);
	}
	*/
	function validate(&$record, $mode)
	{
//$this->p($record);
		if ($record["montant_fourniture"] >0)
		{
			if ($record["date_reglement"]=="")
			{				
				atkTriggerError($record, $this->getAttribute("date_reglement"), "En cas de règlement vous devez préciser la date");
			}
			if ($record["id_compte_financier"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_financier"), "Vous devez choisir un compte de finance");
			}
			if ($record["id_reglement"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_reglement"), "Vous devez choisir un type de règlement");
			}
				
			if ($record["id_reglement"]["id"]!=1 && $record["numero_cheque"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque");
			}
			if ($record["id_reglement"]["id"]==1 && $record["numero_cheque"]=="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque");
			}
			if ($record["id_compte_charge"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_charge"), "Vous devez choisir un compte de dépense");
			}
			
			if (count($record['atkerror']) > 0)
			{
			}
			else 
			{
				if ($mode=="update") $this->supprimer_ecritures($record);
				$this->creer_ecritures_comptables($record);
			}
				
				
		} else 
		{
			if ($record["date_reglement"]!="")
			{
				atkTriggerError($record, $this->getAttribute("date_reglement"), "Pas de montant règlé et date de règlement ?");
			}
			if ($record["id_compte_financier"]["id"]!="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_financier"), "Pas de montant règlé et un compte de finance ?");
			}
			if ($record["id_reglement"]["id"]!="")
			{
				atkTriggerError($record, $this->getAttribute("id_reglement"), "Pas de montant règlé et un type de règlement ?");
			}
			
			if ($record["numero_cheque"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de montant règlé et un numéro de chèque ?");
			}
		
			if ($record["id_compte_charge"]["id"]!="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_charge"), "Pas de montant règlé et un compte de dépense ?");
			}		
		}
//		parent::validate($record, $mode);
		
	}

	function creer_ecritures_comptables(& $record) {


		$id_rencontre = $record["id_rencontre"]["id"];
		global $g_user;
		$id_compte_depense = $record["id_compte_charge"]["id"];
		$id_compte_financier = $record["id_compte_financier"]["id"];
		$id_individu = $record["id_individu"]["id"];
		$id_type_reglement = $record["id_reglement"]["id"];
		$numero_cheque = $record["numero_cheque"];
		if (($id_type_reglement==1 && $numero_cheque=="") || ($id_type_reglement!=1 && $numero_cheque!=""))
		{
				
		}
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$organisme = $db->getrows("SELECT id_organisme
				from organisme_rencontre where id='" . $record["id_rencontre"]["id"] . "'");
		$id_organisme = $organisme[0]["id_organisme"];
		$sql = "SELECT code
		from organisme_compte where id=$id_compte_financier and id_organisme=$id_organisme";
		$compte = $db->getrows($sql);
		$codecomptefinancier = $compte[0]["code"];
		$rang = $db->getrows("SELECT libelle from organisme_rencontre where id =$id_rencontre ");
		$libelle = 'Frais rencontre ' . $rang[0]["libelle"] . ' : ' . $record["libelle"] . '. Facture : ' . $record["numero_facture"] . '.';
		$rang = $db->getrows("SELECT
				o.id_compte_dons as id_compte_dons,

				o.id_compte_adherents as id_compte_adherents,
				o.id_compte_caisse as id_compte_caisse,
				o.id_compte_participation_manifestation as id_compte_participation_manifestation,
				o.id_compte_fournisseurs as id_compte_fournisseurs,
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
		$id_compte_fournisseurs = $rang[0]["id_compte_fournisseurs"];
		$date_reglement = $this->dateatktodb($record["date_reglement"]);
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_depenses, $libelle,$date_reglement);

		$record["id_ecriture_depense"] = $id_ecriture;

		$debit = $record["montant_fourniture"];
		// montant dépense
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_depenses, $id_compte_depense, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$credit = $record["montant_fourniture"];
		;
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_depenses, $id_compte_fournisseurs, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if (substr($codecomptefinancier, 0, 2) == '53') {
			// epèces reçues en caisse
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_fournisseurs, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement,null);
		}
		if (substr($codecomptefinancier, 0, 2) == '51') {
			// banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_fournisseurs, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$numero_cheque = $record["numero_cheque"];
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_cheque, $date_reglement,null);
		}
		return;
	}
	function descriptor_def() {
		return "[id_rencontre][id]";
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_fournisseur_display($record, $mode) {
		(!empty($record["id_organisme_fournisseur"])) ? $retour=$this->descripteur_organisme($record["id_organisme_fournisseur"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>