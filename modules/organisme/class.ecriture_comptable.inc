<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class ecriture_comptable extends assMetaNode {
	var $table = "organisme_ecriture_comptable";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function ecriture_comptable() {
		$this->atkMetaNode();
		$this->atkNode("ecriture_comptable", NF_ADD_LINK | NF_EDITAFTERADD);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id",
						"libelle",
						"debit",
						"credit",
						"id_organisme",
						"id_journal",
						//				"id_ecriture_organisme",
						"id_type_ecriture",
						"id_origine_ecriture",
						"date_ecriture",
						"lignes",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				)
		), AF_NO_LABEL));
		$this->add(new atkAttribute("id", AF_SEARCHABLE | AF_FORCE_LOAD), null,4);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE), null, 110);
		$this->add(new atgNumberExpressionAttribute("debit", ' select sum(debit) from organisme_ligne_ecriture_comptable l
				where l.id_ecriture=[table].id
				', 0, 0), null, 120);
		$this->add(new atgNumberExpressionAttribute("credit", ' select sum(credit) from organisme_ligne_ecriture_comptable l
				where l.id_ecriture=[table].id
				', 0, 0), null, 130);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_READONLY | AF_SEARCHABLE),null,200);
		// $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_HIDE_ADD | AF_FORCE_LOAD), null,40);
		$this->add(new atkManyToOneRelation("id_journal", "organisme.journal_comptable", AF_SEARCHABLE | AF_READONLY), null, 160);
		//				$this->add(new atkNumberAttribute("id_ecriture_organisme"), null, 60);
		$this->add(new atkDateAttribute("date_ecriture", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY), null, 115);

		$this->add(new atkManyToOneRelation("id_type_ecriture", "table.type_ecriture", AF_SEARCHABLE | AF_READONLY), null, 140);
		$this->add(new atkAttribute("id_origine_ecriture", AF_SEARCHABLE), null,150);
		$this->add(new atkOneToManyRelation("lignes", "organisme.ligne_ecriture_comptable", "id_ecriture", AF_HIDE_LIST));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,10);
		$this->m_securityMap["insertion_type_ecriture"] = "view";
		$this->setOrder("id desc");
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_origine_ecriture_display($record, $mode)
	{
		switch ($record["id_type_ecriture"]["id"])
		{
			case 1 :
				$module="organisme.journal_comptable";
				$table="organisme_journal_comptable";
				break;
			case 2 :
				$module="individu.cotisation_i";
				$table="individu_cotisation";
				break;
			case 3 :
				$module="individu.rencontre_i";
				$table="individu_rencontre";
				break;
			case 4 :
				$module="organisme.rencontre";
				$table="organisme_rencontre";
				break;
			case 5 :
				$module="organisme.rencontre_fournisseur";
				$table="organisme_rencontre_fournisseur";
				break;
			case 6 :
				$module="organisme.fourniture";
				$table="organisme_fourniture";
				break;
			case 7 :
				$module="organisme.financement";
				$table="organisme_financement";
				break;
			case 8 :
				$module="organisme.virement_comptable";
				$table="organisme_virement_comptable";
				break;
			case 9 :
				$module="individu.activite_i";
				$table="individu_activite";
				break;
			case 10 :
				$module="organisme.abandon_creance";
				$table="organisme_abandon_creance";
				break;
			default :
				$module="";

		}
		return href(dispatch_url($module, "admin", array (
				'atkfilter' => $table.".id='" . $record['id_origine_ecriture']."'" )
				, "dispatch.php"), $record['id_origine_ecriture'], SESSION_NESTED);

	}

	function action_insertion_type_ecriture()
	{
		$db = & atkGetDb("association");
		$dbupdate = & atkGetDb();
		$user = getUser();
		$userid = $user["id"];

		// cotisations
		$type_ecriture=$this->type_ecriture_cotisation;
		$db->query("select
				id,
				id_ecriture_cotisation,
				id_ecriture_cotisation_federation,
				id_ecriture_reglement
				from individu_cotisation
				where date_reglement >'2007-12-31' ");
		$n2=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				if(!empty($record["id_ecriture_cotisation"]));
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_cotisation"]."'
						or  id='".$record["id_ecriture_cotisation_federation"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n2++;
			}
		}
		echo ' cotisations : '.$n2.'<br />';
		// participation rencontre
		$type_ecriture=$this->type_ecriture_participation_rencontre;
		$db->query("select
				id,
				id_ecriture_participation,
				id_ecriture_reglement
				from individu_rencontre ");
		$n3=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_participation"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n3++;
			}
		}
		echo 'participation rencontre : '.$n3.'<br />';
		// rencontre
		$type_ecriture=$this->type_ecriture_rencontre;
		$db->query("select
				id,
				id_ecriture_participation,
				id_ecriture_reglement
				from organisme_rencontre ");
		$n4=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_participation"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n4++;
			}
		}
		echo 'rencontre : '.$n4.'<br />';
		// rencontre fournisseur
		$type_ecriture=$this->type_ecriture_rencontre_fournisseur;
		$db->query("select
				id,
				id_ecriture_depense,
				id_ecriture_reglement
				from organisme_rencontre_fournisseur ");
		$n5=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_depense"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n5++;
			}
		}
		echo 'rencontre fournisseur : '.$n5.'<br />';
		// depense
		$type_ecriture=$this->type_ecriture_depense;
		$db->query("select
				id,
				id_ecriture_depense,
				id_ecriture_reglement
				from organisme_fourniture ");
		$n6=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_depense"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n6++;
			}
		}
		echo 'depense : '.$n6.'<br />';
		// recette
		$type_ecriture=$this->type_ecriture_recette;
		$db->query("select
				id,
				id_ecriture_recette,
				id_ecriture_reglement
				from organisme_financement ");
		$n7=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_recette"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n7++;
			}
		}
		echo 'recette : '.$n7.'<br />';
		// virement
		$type_ecriture=$this->type_ecriture_virement;
		$db->query("select
				id,
				id_ecriture_virement
				from organisme_virement_comptable ");
		$n8=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						id='".$record["id_ecriture_virement"]."'");
				$n8++;
			}
		}
		echo 'virement : '.$n8.'<br />';
		// frais
		$type_ecriture=$this->type_ecriture_frais;
		$db->query("select
				id,
				id_ecriture_frais,
				id_ecriture_benevolat,
				id_ecriture_reglement
				from individu_activite ");
		$n9=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				if(!empty($record["id_ecriture_cotisation"]));
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						(id='".$record["id_ecriture_frais"]."'
						or  id='".$record["id_ecriture_benevolat"]."'
						or  id='".$record["id_ecriture_reglement"]."')");
				$n9++;
			}
		}
		echo 'frais : '.$n9.'<br />';
		// abandon_creance
		$type_ecriture=$this->type_ecriture_abandon_creance;
		$db->query("select
				id,
				id_ecriture_virement
				from organisme_abandon_creance ");
		$n10=0;
		if ($db->affected_rows($sql)==0)
		{
		}
		else {
			while ($db->next_record()) {
				$record = $db->m_record;
				$id=$record["id"];
				$dbupdate->query("UPDATE organisme_ecriture_comptable
						set id_type_ecriture='".$type_ecriture."' ,
						id_origine_ecriture=$id,
					 id_modification=$userid,
						date_modification=UTC_TIMESTAMP()
						where
						id='".$record["id_ecriture_virement"]."'");
				$n10++;

			}
		}
		echo 'abandon_creance : '.$n10.'<br />';
		$data=$db->getrows("select
				id from organisme_ecriture_comptable where id_type_ecriture is null");
		$n11=count($data);
		echo 'ecritures sans origine : '.$n11.'<br />';
		echo 'Traitement terminé';
		atkhalt('Fin de mise à jour des origines écritures','report');
	}
	function preAdd(& $record) {
		// atk_var_dump($record);
		//				print_r ($this->m_postvars);
		//		die ();
		$id_journal = $record['id_journal']['id'];
		// $id_organisme = $record['id_organisme']['id'];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_organisme FROM organisme_journal_comptable where id=$id_journal ");
		$id_organisme = $data[0]["id_organisme"];
		$record["id_organisme"]["id"] = "$id_organisme";
		$data = $db->getrows("SELECT prochain_id_ecriture FROM organisme where id=$id_organisme ");
		$id_ecriture_organisme = $data[0]["prochain_id_ecriture"];
		$db->query("UPDATE organisme set prochain_id_ecriture=prochain_id_ecriture+1 where id=$id_organisme ");
		$record["id_ecriture_organisme"] = "$id_ecriture_organisme";
		if ($record['id_type_ecriture']['id']=="")
		{
			$record['id_type_ecriture']['id']='1';
			$record['id_origine_ecriture']=$id_journal;
				
		}
		parent :: preAdd($record);
	}
	function preDelete(& $record) {
		$idecriture = $record["id"];
		$db = & atkGetDb();
		$data = $db->query("select count(id_releve) as nombre
				from organisme_ligne_ecriture_comptable where id_ecriture = $idecriture and id_releve != null ");
		if ($data[0]["nombre"] > 0) {
			echo "Suppression impossible. Des lignes d'écriture ont été rapprochées.";
			die();
		}
		$data = $db->query("select count(id_remise) as nombre
				from organisme_ligne_ecriture_comptable where id_ecriture = $idecriture and id_remise != null ");
		if ($data[0]["nombre"] > 0) {
			echo "Suppression impossible. Des lignes d'écriture ont été remisées en banque.";
			die();
		}
		parent :: preDelete($record);
	}
	function rowColor($record) {
		if ($record["debit"] != $record["credit"])
			return $this->couleurrouge;
	}
	function initial_values() {
		/*
		 * javascript:atkSubmit("___12Fassociation_12F
		 * dispatch.php_13Fatknodetype_13D
		 * organisme.ecriture_comptable_126
		 * atkaction_13Dadd_126
		 * atkfilter_13Did_journal.id_1253D_1252793_12527_126
		 * atklevel_13D2_126
		 * atkprevlevel_13D1_126
		 * atkstackid_13D526654644337c_126")
		 */
		$init_vals = array ();
//		$this->p( $this->m_postvars);
		$journal = explode('=', $this->m_postvars['atkfilter']);
//		$this->p( $journal);
		if ($journal[0] == 'id_journal.id' || $journal[0] == 'id_journal') {
			if ($journal[0] == 'id_journal.id')
			{$id_journal = $journal[1];}
			else 
			{
				$id_journal =substr($journal[1], 0,stripos($journal[1], ' and '));
			}
			$db = & atkGetDb();
			$data = $db->getrows("SELECT oj.id_organisme, o.nom as nom FROM organisme_journal_comptable oj, organisme o where oj.id=$id_journal and oj.id_organisme=o.id");
			$init_vals["id_organisme"] = $data[0]["id_organisme"];
		} else {
			echo "L'ajout d'écriture n'est possible qu'à partir de la sélection d'un journal";
			die();
		}

		return $init_vals;
	}
	function id_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id"]);
	}
/*	function postUpdate($record)
	{
		$this->mise_a_jour_type_ecriture($record);
		parent::postUpdate($record);
		return true;
	}
	function postAdd($record)
	{
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
	//	$this->p($record);
	$this->ecriture_type_origine_maj($record["id"],$this->type_ecriture_journal,$record["id_journal"]["id"]);
		return true;
	}
	*/
	function descriptor_def() {
		return "[libelle]";
	}
}
?>