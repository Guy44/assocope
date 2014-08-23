<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class abandon_creance extends assMetaNode {
	var $table = "organisme_abandon_creance";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("id_ecriture_virement", AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id");
	}
	function abandon_creance() {
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"descripteur_abandon_creance",
						"libelle",
						"id_organisme",
						"id_individu",
						"montant_virement",
						"date_operation",
						"id_recu_fiscal",
						"date_envoi_recu_fiscal",
						"id_ecriture_virement",
						"ecritures",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				)
					
		), AF_NO_LABEL));
		$this->atkMetaNode();
		$this->atkNode("abandon_creance", NF_ADD_LINK | NF_COMPACT );
		$this->add(new atkDummyAttribute("descripteur_abandon_creance","",AF_COMPACT),NULL,6);
		$this->add(new atkAttribute("id_ecriture_virement","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),null,7);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY |AF_FORCE_LOAD));
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atgOManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atkNumberAttribute("montant_virement", AF_OBLIGATORY, 12, 2));
		$this->add(new atkDummyAttribute("ecritures"));
		$this->add(new atkDateAttribute("date_operation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY));
		$this->add(new atkDateAttribute("date_envoi_recu_fiscal", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING|AF_READONLY));

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10 );
		$this->setOrder(" date_operation DESC ");
	}
	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_virement"]) ) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_virement']  . "'"
			), "dispatch.php"), text("Voir"), SESSION_NESTED);
		} else {
			return "Pas d'écritures";
		}
	}
	function descripteur_abandon_creance_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_abandon_creance($record["id"],'o'),60);
	}

	function id_ecriture_virement_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_virement"]);
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
		$data=$db->getrows('Select max(id) as id from organisme_abandon_creance');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_virement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_virement"],$this->type_ecriture_abandon_creance,$record["id"]);
		}
		return true;
	}

	function preAdd(& $record) {

		if ($record["montant_virement"] == 0) {
			triggerError($record, "montant_virement", 'Valeurs', atktext("Montant à zéro", "atk"));
		}
		$this->creer_ecritures_comptables($record);
		$id_organisme = $record['id_organisme']['id'];
		$record["id_recu_fiscal"] = $this->getProchainIdRecuFiscal($id_organisme);
		parent :: preAdd($record);
		return true;
	}
	function preUpdate(& $record) {

		if ($record["montant_virement"] == 0) {
			triggerError($record, "montant_virement", 'Valeurs', atktext("Montant à zéro", "atk"));
		}
		$this->supprimer_ecritures($record);
		$this->creer_ecritures_comptables($record);
		parent :: preUpdate($record);
		return true;
	}
	function preDelete(& $record) {

		$this->supprimer_ecritures($record);
		parent :: preDelete($record);
		return true;
	}
	function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_virement = $record["id_ecriture_virement"];

		if (isset ($id_ecriture_virement)) {
			$this->supprimer_ecriture_comptable($id_ecriture_virement);
		}

		return true;
	}

	function creer_ecritures_comptables(& $record) {
		$db = & atkGetDb();
		$id_organisme = $record['id_organisme']['id'];
		$id_individu = $record['id_individu']['id'];
		$sql="select CONCAT( prenom,' ', nom) as nom_individu from individu where id='".$id_individu."'";
		$data = $db->getrows($sql);
		$nom_individu=$data[0]["nom_individu"];
		$sql="select id as id_compte_credit from organisme_compte where id_organisme='".$id_organisme."' and code='77133'";
		$data = $db->getrows($sql);
		$id_compte_credit=$data[0]["id_compte_credit"];
		$sql="select id as id_compte_debit from organisme_compte where id_organisme='".$id_organisme."' and code='411'";
		$data = $db->getrows($sql);
		$id_compte_debit=$data[0]["id_compte_debit"];
		$date_reglement = $this->dateatktodb($record['date_operation']);
		global $g_user;
		$userid = $g_user["id"];

		$rang = $db->getrows("SELECT
				id_journal_operations_diverses
				FROM organisme where id=$id_organisme ");

		$id_journal_operations_diverses = $rang[0]["id_journal_operations_diverses"];
		if (!isset ($id_journal_operations_diverses)) {
			echo '<br><b>Journal des opérations diverses non initialisé<br> ';
			die();
		}

		$libelle = 'Abandon de créance : ' . $record["libelle"] ." (".$nom_individu.")";
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_operations_diverses, $libelle, $date_reglement);
		$record["id_ecriture_virement"] = $id_ecriture;
		$debit = $record["montant_virement"];
		$credit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_operations_diverses, $id_compte_debit, $id_organisme, $id_individu, $debit, $credit, '2', null,$date_reglement,null);
		$credit = $record["montant_virement"];
		$debit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_operations_diverses, $id_compte_credit, $id_organisme, null, $debit, $credit, '2', null,$date_reglement,null);

		return true;
	}

	function getProchainIdRecuFiscal($id_organisme) {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT prochain_id_recu_fiscal FROM organisme where id=$id_organisme ");
		$id_recu_fiscal = $data[0]["prochain_id_recu_fiscal"];
		$db->query("UPDATE organisme set prochain_id_recu_fiscal=prochain_id_recu_fiscal+1 where id=$id_organisme ");
		return $id_recu_fiscal;
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
}
?>