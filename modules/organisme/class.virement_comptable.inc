<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class virement_comptable extends assMetaNode {
	var $table = "organisme_virement_comptable";
	function meta(& $policy) {
		$policy->addFlags("commentaire", "description", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("id_ecriture_virement", AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id");
	}
	function virement_comptable() {
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"descripteur_virement_comptable",
		"libelle",
				"id_organisme",
				"montant_virement",
				"date_operation",
				"id_compte_debit",
				"id_compte_credit",
		"ecritures",
				"id_ecriture_virement",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)		
			
		), AF_NO_LABEL));
		$this->atkMetaNode();
		$this->atkNode("virement_comptable", NF_ADD_LINK | NF_COMPACT );
		$this->add(new atkDummyAttribute("descripteur_virement_comptable",0,AF_COMPACT),null,5);
		$this->add(new atkAttribute("id_ecriture_virement",AF_FORCE_LOAD),null,6);
		$this->add(new atgTextLibelleAttribute("libelle",AF_FORCE_LOAD| AF_SEARCHABLE | AF_OBLIGATORY));
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme",AF_FORCE_LOAD | AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkNumberAttribute("montant_virement", AF_OBLIGATORY, 12, 2));
		$this->add(new atkDummyAttribute("ecritures"));
		$this->add(new atkDateAttribute("date_operation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_OBLIGATORY));
		$c12 = & $this->add(new atkManyToOneRelation("id_compte_debit", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		$c12->setDestinationFilter("organisme_compte.id in ( select id from organisme_compte where  usuel='1' and id_organisme='[id_organisme]') ");
		$c13 = & $this->add(new atkManyToOneRelation("id_compte_credit", "organisme.compte", AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		$c13->setDestinationFilter("organisme_compte.id in ( select id from organisme_compte where  usuel='1' and id_organisme='[id_organisme]') ");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
				$this->setOrder(" date_operation DESC ");
	}
	function descripteur_virement_comptable_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_virement_comptable($record["id"],'o'),100);
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
	function id_ecriture_virement_display($record, $mode) {
return $this-> descripteur_ecriture_comptable($record["id_ecriture_virement"]);	}
function postUpdate($record)
    {
    $this->mise_a_jour_type_ecriture($record);  
    parent::postUpdate($record);
    return true;       
    }
  function postAdd($record)
    { $db = & atkGetDb();
$data=$db->getrows('Select max(id) as id from organisme_virement_comptable');
$record["id"]=$data[0]["id"];
   	$this->mise_a_jour_type_ecriture($record);  
    parent::postAdd($record);
    return true;       
    }
    function mise_a_jour_type_ecriture($record)
    {    if (!empty($record["id_ecriture_virement"]))
    {$this->ecriture_type_origine_maj($record["id_ecriture_virement"],$this->type_ecriture_virement,$record["id"]);	}
    return true;
    }
    	
	function preAdd(& $record) {
				$this->RazDestinationFilters();
		if ($record["montant_virement"] == 0) {
			triggerError($record, "montant_virement", 'Valeurs', atktext("Montant à zéro", "atk"));
		}
		$this->creer_ecritures_comptables($record);
		parent :: preAdd($record);

		return true;
	}
	function preUpdate(& $record) {
				$this->RazDestinationFilters();
		if ($record["montant_virement"] == 0) {
			triggerError($record, "montant_virement", 'Valeurs', atktext("Montant à zéro", "atk"));
		}
		$this->supprimer_ecritures($record);
		$this->creer_ecritures_comptables($record);
		parent :: preUpdate($record);
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
		$id_ecriture_virement = $record["id_ecriture_virement"];

		if (isset ($id_ecriture_virement)) {
			$this->supprimer_ecriture_comptable($id_ecriture_virement);
		}
	
		return true;
	}

	function creer_ecritures_comptables(& $record) {
		$id_organisme = $record['id_organisme']['id'];
		$id_compte_debit = $record['id_compte_debit']['id'];
		$id_compte_credit = $record['id_compte_credit']['id'];
		$date_reglement = $this->dateatktodb($record['date_operation']);
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$rang = $db->getrows("SELECT
								id_journal_operations_diverses
									 FROM organisme where id=$id_organisme ");
	
		$id_journal_operations_diverses = $rang[0]["id_journal_operations_diverses"];
		if (!isset ($id_journal_operations_diverses)) {
			echo '<br><b>Journal des opérations diverses non initialisé<br> ';
			die();
		}
		
		$libelle = 'Virement : ' . $record["libelle"] ;
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_operations_diverses, $libelle, $date_reglement);
		$record["id_ecriture_virement"] = $id_ecriture;
		$debit = $record["montant_virement"];
		$credit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_operations_diverses, $id_compte_debit, $id_organisme, null, $debit, $credit, '2', null,$date_reglement,null);
		$credit = $record["montant_virement"];
		$debit = 0;
		$this->creer_ligne_ecriture_comptable($id_ecriture, $id_journal_operations_diverses, $id_compte_credit, $id_organisme, null, $debit, $credit, '2', null,$date_reglement,null);

		return true;
	}
			function RazDestinationFilters()
	{
		$attrib=$this->getAttribute("id_compte_debit")	;
	$attrib->setDestinationFilter("");
	$attrib=$this->getAttribute("id_compte_credit")	;
	$attrib->setDestinationFilter("");
	
	return true;	
		
	}
	function descriptor_def() {
		return "[id]";
	}
}
?>