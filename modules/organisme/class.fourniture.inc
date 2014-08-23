<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class fourniture extends assMetaNode {
	var $table = "organisme_fourniture";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("id_ecriture_depense", "id_ecriture_reglement", AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id");
	}
	function fourniture() {
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id",
		"descripteur_depense",
		"libelle",
				"id_organisme",
				"reglement_seul_o_n",
				"id_organisme_tiers",
				"id_individu",
				"description",
				"montant_fourniture",
				"date_reglement",
				"id_compte_charge",
				"id_compte_tiers",
				"id_compte_financier",
				"id_reglement",
				"numero_cheque",
				"numero_facture",
				"id_document_facture",
		"ecritures",
				"id_ecriture_reglement",
				"id_ecriture_depense",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)			/*	,
				"Ventilation" => array (
				"id_ecriture_depense"
				)
				*/
					
				), AF_NO_LABEL));
				$this->atkMetaNode();
				$this->atkNode("fourniture", NF_ADD_LINK| NF_MRA| NF_ADDAFTERADD | NF_COMPACT );
				$this->add(new atkAttribute("id_ecriture_depense",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),null,7);
				$this->add(new atkAttribute("id_ecriture_reglement",AF_HIDE_ADD|AF_HIDE_EDIT| AF_FORCE_LOAD),null,8);
				$this->add(new atkDummyAttribute("descripteur_depense",0,AF_HIDE_ADD|AF_HIDE_EDIT| AF_COMPACT),NULL, 6);
				$this->add(new atkAttribute("id",AF_HIDE | AF_FORCE_LOAD));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY| AF_FORCE_LOAD));
				$this->setSecurityAlias("organisme.organisme");
				$this->add(new atkBoolAttribute("reglement_seul_o_n"));
				$this->add(new atkParserAttribute("presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST), NULL, 1);
				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
				$this->add(new atgOManyToOneRelation("id_organisme_tiers", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
				$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
				$this->add(new atkNumberAttribute("montant_fourniture", AF_OBLIGATORY, 12, 2));
				$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY));
				$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkDummyAttribute("ecritures"));
				$c10 = & $this->add(new atkManyToOneRelation("id_compte_tiers", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY| AF_FORCE_LOAD));
				$c10->setDestinationFilter("organisme_compte.id in ( select organisme_compte.id from organisme_compte where ( code like '4%') and usuel='1' and id_organisme='[id_organisme]') ");
				$c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY| AF_FORCE_LOAD));
				$c12->setDestinationFilter("organisme_compte.id in ( select organisme_compte.id from organisme_compte where ( code like '51%' or code like '53%') and usuel='1' and id_organisme='[id_organisme]') ");
				$c11 = & $this->add(new atkManyToOneRelation("id_compte_charge", "organisme.compte", AF_RELATION_AUTOLINK | AF_FORCE_LOAD));
				$c11->setDestinationFilter(" organisme_compte.id in (select organisme_compte.id from organisme_compte where ( code like '6%' ) and usuel='1' and id_organisme='[id_organisme]') ");
				/*
				 $c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK));
				 $c12->addDestinationFilter("( code like '51%' or code like '53%') and usuel='1' and id_organisme='[id_organisme]' ");
				 $c11 = & $this->add(new atkManyToOneRelation("id_compte_charge", "organisme.compte", AF_RELATION_AUTOLINK));
				 $c11->addDestinationFilter(" ( code like '6%' ) and usuel='1' and id_organisme='[id_organisme]' ");
				 */
				//	$this->add(new atkOneToManyRelation("id_ecriture_depense", "organisme.ligne_ecriture_comptable", "id_ecriture"));
				$this->add(new atgFileManyToOneRelation("id_document_facture", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
				$this->m_securityMap["justificatif"] = "view";
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
				$this->setOrder(" date_reglement DESC ");
	}
	function descripteur_depense_display($record, $mode) {

		return $this->descripteur_depense($record["id"]);
	}
	function action_admin($handler) {

						global $config_recordsperpage;
		$config_recordsperpage = 25;
		return $handler->action_admin();
	}

	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_depense"]) || isset ($record["id_ecriture_reglement"]) ) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_depense'] . "' 
				or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'"
				), "dispatch.php"), text("Voir"), SESSION_NESTED);
		} else {
			return "Pas d'écritures";
		}
	}
	
/*	function preAdd(& $record) {
		
		$this->creer_ecritures_comptables($record);
		parent :: preAdd($record);
		return true;
	}
	function preUpdate(& $record) {
		$this->supprimer_ecritures($record);
		$this->creer_ecritures_comptables($record);
		parent :: preUpdate($record);
		return true;
	}
	
	*/	
	function validate(&$record, $mode)
	{
//$this->p($record);
		$this->RazDestinationFilters();
		if ($record["reglement_seul_o_n"] == false && $record["id_compte_charge"]["id"]=="") {
			triggerError($record, "id_compte_charge", 'Valeurs', atktext("Le compte de dépense doit être renseigné, s'il ne s'agit pas d'un règlement seul", "atk"));
		}
		if ($record["reglement_seul_o_n"] == true && $record["id_compte_charge"]["id"]!="") {
			triggerError($record, "id_compte_charge", 'Valeurs', atktext("S'il s'agit d'un règlement seul : il ne doit pas y avoir de compte de dépense", "atk"));
		}
		
		
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
/*			if ($record["id_compte_charge"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_charge"), "Vous devez choisir un compte de dépense");
			}
			*/
			if ($record["id_compte_tiers"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_compte_tiers"), "Vous devez choisir un compte tiers");
			}
		} else 
		{
			atkTriggerError($record, $this->getAttribute("montant_fourniture"), "Pas de montant ?");
		}
		if (parent::validate($record, $mode)==true)
		{
			if ($mode=="update") $this->supprimer_ecritures($record);
				$this->creer_ecritures_comptables($record);
				return true;
		}
		
		
		
	}
	function presence_compta_edit($record, $mode) {
		$id_organisme = $record["id_organisme"];
		$db = & atkGetDb();
		$sql = "SELECT o.nom as nom, date_initialisation_comptabilite  from organisme o
						 where o.id='" . $id_organisme . "'";
		$data = $db->getrows($sql);
		if ($data[0]["date_initialisation_comptabilite"] != null) {
			return '';
		} else {
			return '<font color="Red"> <b> La comptabilité n\'ayant pas été initialisée pour ' . $data[0]["nom"] . ', la saisie de montant versé ne sera pas prise en compte dans la comptabilité.';
		}
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
		$data=$db->getrows('Select max(id) as id from organisme_fourniture');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{    if (!empty($record["id_ecriture_depense"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_depense"],$this->type_ecriture_depense,$record["id"]);	}
	if (!empty($record["id_ecriture_reglement"]))
	{$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_depense,$record["id"]);	}
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

	function creer_ecritures_comptables(& $record) {
		//		print_r ($record);
		//		die();
		$id_organisme = $record['id_organisme']['id'];
		$id_individu = $record['id_individu']['id'];
		$reglement_seul_o_n = $record['reglement_seul_o_n'];
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$rang = $db->getrows("SELECT
									id_journal_depenses ,
								id_journal_caisse,
								id_journal_banque_courant
									 FROM organisme where id=$id_organisme ");
		$numero_cheque = $record["numero_cheque"];
		$id_typereglement = $record["id_reglement"]["id"];
		$id_compte_depense = $record["id_compte_charge"]["id"];
		$id_compte_financier = $record["id_compte_financier"]["id"];
		$id_compte_tiers= $record["id_compte_tiers"]["id"];
		$date_reglement = $this->dateatktodb($record["date_reglement"]);

		$sql = "SELECT code	from organisme_compte where id=$id_compte_financier and id_organisme=$id_organisme";
		$compte = $db->getrows($sql);
		$codecomptefinancier = $compte[0]["code"];
		$id_journal_depenses = $rang[0]["id_journal_depenses"];
		if (!isset ($id_journal_depenses)) {
			echo '<br><b>Journal dépenses non initialisé<br> ';
			die();
		}
		$id_journal_caisse = $rang[0]["id_journal_caisse"];
		if (!isset ($id_journal_caisse)) {
			echo '<br><b>Journal caisse non initialisé<br> ';
			die();
		}
		$id_journal_banque_courant = $rang[0]["id_journal_banque_courant"];
		if (!isset ($id_journal_banque_courant)) {
			echo '<br><b>Journal banque courant non initialisé<br> ';
			die();
		}

		$libelle = 'Dépense : ' . $record["libelle"] . '. Facture : ' . $record["numero_facture"] . '.';
		if ($reglement_seul_o_n==0)
		{
				

			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_depenses, $libelle, $date_reglement);
			$record["id_ecriture_depense"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_depenses, $id_compte_depense, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_depenses, $id_compte_tiers, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		}
		else {
			//$record["id_compte_charge"]["id"]=null;
		}
		if (substr($codecomptefinancier, 0, 2) == '53') {
			// epèces reçues en caisse
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_tiers, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_typereglement, null,$date_reglement, null);
		}
		if (substr($codecomptefinancier, 0, 2) == '51') {
			// banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_fourniture"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_tiers, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$numero_cheque = $record["numero_cheque"];
			$credit = $record["montant_fourniture"];
			$debit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_typereglement,$numero_cheque, $date_reglement,null );
		}
		return true;
	}
	function RazDestinationFilters()
	{
		$attrib=$this->getAttribute("id_compte_tiers")	;
		$attrib->setDestinationFilter("");
		$attrib=$this->getAttribute("id_compte_financier")	;
		$attrib->setDestinationFilter("");
		$attrib=$this->getAttribute("id_compte_charge")	;
		$attrib->setDestinationFilter("");
		return true;

	}
	function descriptor_def() {
		return "[id]";
	}
	public function getCustomMraHtml()
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
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_tiers_display($record, $mode) {
		(!empty($record["id_organisme_tiers"])) ? $retour=$this->descripteur_organisme($record["id_organisme_tiers"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>