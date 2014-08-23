<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
class financement extends assMetaNode {
	var $table = "organisme_financement";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("id_ecriture_recette", "id_ecriture_reglement", AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id");
	}
	function financement() {
		$this->atkMetaNode();
		$this->atkNode("financement",  NF_ADD_LINK | NF_ADDAFTERADD | NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkAttribute("libelle",AF_SEARCHABLE | AF_OBLIGATORY),NULL,4);
		$this->add(new atkDummyAttribute("descripteur_financement",0,AF_HIDE_ADD|AF_COMPACT),NULL,5);
//		$this->add(new atkDummyAttribute("descripteur_reglement",0,AF_COMPACT),NULL,6);
		$this->add(new atkAttribute("id_ecriture_recette",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,7);
		$this->add(new atkAttribute("id_ecriture_reglement",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,7);
		$this->add(new atkParserAttribute("presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST), NULL, 1);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD), NULL, 100);
		$this->add(new atgOManyToOneRelation("id_organisme_financeur", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD), NULL, 110);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD), NULL, 115);
		
		$this->add(new atkNumberAttribute("montant_financement", AF_OBLIGATORY, 12, 2), NULL, 120);
		$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY), NULL, 130);
		$this->add(new atkDummyAttribute("ecritures"), NULL, 300);
		
		$c10 = & $this->add(new atkManyToOneRelation("id_compte_tiers", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY|AF_FORCE_LOAD), NULL, 139);
		$c10->setDestinationFilter(" organisme_compte.id in ( select id from organisme_compte where ( code like '4%') and usuel='1' and id_organisme='[id_organisme]') ");
		
		
		$c12 = & $this->add(new atkManyToOneRelation("id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY|AF_FORCE_LOAD), NULL, 140);
		$c12->setDestinationFilter(" organisme_compte.id in ( select id from organisme_compte where ( code like '5%') and usuel='1' and id_organisme='[id_organisme]') ");
		$c11 = & $this->add(new atkManyToOneRelation("id_compte_produit", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY|AF_FORCE_LOAD), NULL, 150);
		$c11->setDestinationFilter(" organisme_compte.id in (select id from organisme_compte where ( code like '7%' ) and usuel='1' and id_organisme='[id_organisme]') ");
		$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD| AF_OBLIGATORY), NULL, 160);
				$this->add(new atkManyToOneRelation("id_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD), NULL, 170);
				$this->add(new atkAttribute("numero_cheque"), NULL, 180);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
		$this->setOrder(" date_reglement DESC ");
	}
/*	function preAdd(& $record) {
		$this->RazDestinationFilters();
		if ($record["montant_financement"] > 0) {
			$this->creer_ecritures_comptables($record);
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$this->RazDestinationFilters();
	
		$this->supprimer_ecritures($record);
		if ($record["montant_financement"] > 0) {
			$this->creer_ecritures_comptables($record);
		}
		parent :: preUpdate($record);
	}
	*/
	function validate(&$record, $mode)
	{
		//$this->p($record);
		$this->RazDestinationFilters();
		if ($record["montant_financement"] >0)
		{
			if ($record["id_reglement"]["id"]==1 && $record["id_banque"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_banque"), "En cas de règlement par chèque il faut préciser la banque");
			}
			
			if ($record["id_reglement"]["id"]!=1 && $record["numero_cheque"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque");
			}
			if ($record["id_reglement"]["id"]==1 && $record["numero_cheque"]=="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque");
			}
			
			if (count($record['atkerror']) > 0)
			{
			}
			
		} else
		{
		
			atkTriggerError($record, $this->getAttribute("montant_financement"), "Pas de montant ou montant nul ?");
		}
		if (parent::validate($record, $mode)==true)
		{
			if ($mode=="update") $this->supprimer_ecritures($record);
			$this->creer_ecritures_comptables($record);
		}
	
	}
	
	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_recette"]) || isset ($record["id_ecriture_reglement"]) ) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_recette'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'"
			), "dispatch.php"),"Ecritures", SESSION_NESTED);
		} else {
			return "Pas d'écritures";
		}
	}
	function descripteur_reglement_display($record, $mode) {
		return $this->decoupe_affichage_colonne('<b>'.$this->descripteur_reglement('recette',$record["id"],'o').'<br />',100);
	}
	function descripteur_financement_display($record, $mode) {
		$retour=$this->decoupe_affichage_colonne($this->descripteur_financement($record["id"],'o'),100);
//		$retour.="<br/>".$this->decoupe_affichage_colonne('<b>'.$this->descripteur_reglement('recette',$record["id"],'o').'<br />',100);
		return $retour;
	}

	function presence_compta_edit($record, $mode) {
		//		$this->p($record);
		$id_organisme = $record["id_organisme"];
		$db = & atkGetDb();
		$sql = "SELECT o.nom as nom, date_initialisation_comptabilite  from organisme o
				where o.id ='" . $id_organisme . "'";
		$data = $db->getrows($sql);
		if ($data[0]["date_initialisation_comptabilite"] != null) {
			return '';
		} else {
			return '<font color="Red"> <b> La comptabilité n\'ayant pas été initialisée pour ' . $data[0]["nom"] . ', la saisie de montant versé ne sera pas prise en compte dans la comptabilité.';
		}
	}

	function id_ecriture_recette_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_recette"]);
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
		$data=$db->getrows('Select max(id) as id from organisme_financement');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_recette"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_recette"],$this->type_ecriture_recette,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_recette,$record["id"]);
		}
		return true;
	}
	 

	function preDelete(& $record) {
		$this->RazDestinationFilters();

		$this->supprimer_ecritures($record);
		parent :: preDelete($record);
	}
	function creer_ecritures_comptables(& $record) {
		//		print_r ($record);
		//		die();
		$id_organisme = $record['id_organisme']['id'];
		$id_individu = $record['id_individu']['id'];
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$rang = $db->getrows("SELECT
				id_compte_financeurs ,
				id_journal_recettes ,
				id_journal_caisse,
				id_journal_banque_courant
				FROM organisme where id=$id_organisme ");
		$numero_cheque = $record["numero_cheque"];
		$id_typereglement = $record["id_reglement"]["id"];
		$id_banque = $record["id_banque"]["id"];
		$id_compte_produit = $record["id_compte_produit"]["id"];
		$id_compte_financier = $record["id_compte_financier"]["id"];
		$date_reglement = $this->dateatktodb($record["date_reglement"]);
		$sql = "SELECT code	from organisme_compte where id=$id_compte_financier and id_organisme=$id_organisme";
		$compte = $db->getrows($sql);
		$codecomptefinancier = $compte[0]["code"];
		$id_journal_recettes = $rang[0]["id_journal_recettes"];
		if (!isset ($id_journal_recettes)) {
			echo '<br><b>Journal recettes non initialisé<br> ';
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
		$id_compte_financeurs = $rang[0]["id_compte_financeurs"];
		if ($record["id_compte_tiers"]["id"]>0)
		{$id_compte_financeurs=$record["id_compte_tiers"]["id"];}
		else
		{
		if (!isset ($id_compte_financeurs)) {
			echo '<br><b>Compte financeurs non initialisé<br> ';
			die();
		}}
//		$this->p($record);
		$libelle = 'Recette : ' . $record["libelle"] . '.';

		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle, $date_reglement);
		$record["id_ecriture_recette"] = $id_ecriture;
		$debit = $record["montant_financement"];
		$credit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_financeurs, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$credit = $record["montant_financement"];
		$debit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_produit, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if (substr($codecomptefinancier, 0, 2) == '53') {
			// epèces reçues en caisse
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$debit = $record["montant_financement"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_typereglement, null, $date_reglement, $id_banque);
			$credit = $record["montant_financement"];
			$debit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_financeurs, $id_organisme, $id_individu, $debit, $credit,  null, null, null, null);
		}
		if (substr($codecomptefinancier, 0, 2) == '51') {
			// banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$numero_cheque = $record["numero_cheque"];
			$debit = $record["montant_financement"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit,$id_typereglement, $numero_cheque, $date_reglement, $id_banque);
				
			$credit = $record["montant_financement"];
			$debit = 0;
			$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_financeurs, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);

		}
		return true;
	}

	function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_recette = $record["id_ecriture_recette"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "") {
			return true;
		} else {
			$data = $db->getrows("select r.date_remise_banque as date_remise_banque from organisme_remise_banque r, organisme_ligne_ecriture_comptable l, organisme_financement c
					where c.id_ecriture_reglement= $id_ecriture_reglement
					and  l.id_ecriture=c.id_ecriture_reglement
					and r.id=l.id_remise
					and id_type_banque  is not null ");
			if (isset ($data[0]["date_remise_banque"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement a été remis en banque<br>", "critical");
			} else {
				if (isset ($id_ecriture_recette)) {
					$this->supprimer_ecriture_comptable($id_ecriture_recette);
				}
				if (isset ($id_ecriture_reglement)) {
					$this->supprimer_ecriture_comptable($id_ecriture_reglement);
				}
			}
		}
		return true;
	}
	function RazDestinationFilters()
	{
		$attrib=$this->getAttribute("id_compte_financier")	;
		$attrib->setDestinationFilter("");
		$attrib=$this->getAttribute("id_compte_produit")	;
		$attrib->setDestinationFilter("");
		$attrib=$this->getAttribute("id_compte_tiers")	;
		$attrib->setDestinationFilter("");
		return true;

	}
	function descriptor_def() {
		return "[id]";
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->decoupe_affichage_colonne($this->descripteur_organisme($record["id_organisme"]["id"],'n'),40) : $retour="";
		return $retour;
	}
	function id_organisme_financeur_display($record, $mode) {
		(!empty($record["id_organisme_financeur"])) ? $retour=$this->decoupe_affichage_colonne($this->descripteur_organisme($record["id_organisme_financeur"]["id"],'n'),40) : $retour="";
		return $retour;
	}
}
?>