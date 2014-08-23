<?php
useattrib ( "development.atgomanytoonerelation" );
useattrib ( "development.atgtextlibelleattribute" );
useattrib ( "development.atgFileManyToOneRelation" );
useattrib ( "development.atgNumberExpressionAttribute" );
class activite_i extends assMetaNode {
	var $table = "individu_activite";
	function meta(& $policy) {
		$policy->addFlags ( "commentaire", AF_HIDE_LIST );
		$policy->addFlags ( "id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY );
		$policy->addFlags ( "id_ecriture_frais", "id_ecriture_benevolat", "id_ecriture_reglement", AF_READONLY | AF_FORCE_LOAD );
		$policy->addFlags ( "nombre_heures", AF_TOTAL );
	}
	function activite_i() {
		$this->atkMetaNode ();
		$this->atkNode ( "activite_i", NF_ADD_LINK | NF_ADDAFTERADD | NF_TRACK_CHANGES | NF_COMPACT );
		$this->setSecurityAlias ( "individu.individu" );
		$this->add ( new atkDummyAttribute ( "descripteur_activite_frais", 0, AF_COMPACT ), NULL, 1 );
		$this->add ( new atkDummyAttribute ( "descripteur_activite_reglement" ), NULL, 2 );
		$this->add ( new atgTextLibelleAttribute ( "libelle", AF_SEARCHABLE | AF_OBLIGATORY ), null, 140 );
		
		$this->add ( new atkParserAttribute ( "presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST ), NULL, 1 );
		$this->add ( new atkManyToOneRelation ( "id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ), null, 50 );
		$this->add ( new atkManyToOneRelation ( "id_type_activite", "table.activite", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ), null, 150 );
		$organisme = &$this->add ( new atgOManyToOneRelation ( "id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE ), null, 20 );
		$organisme->addDependee ( "id_compte_financier" );
		$this->add ( new atkAttribute ( "id_ecriture_frais", AF_HIDE_ADD ), null, 3 );
		$this->add ( new atkAttribute ( "id_ecriture_reglement", AF_HIDE_ADD ), null, 4 );
		$this->add ( new atkAttribute ( "id_ecriture_benevolat", AF_HIDE_ADD ), null, 5 );
		$this->add ( new atgOManyToOneRelation ( "id_rencontre", "organisme.rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE ), null, 115 );
		// TODO $this->add(new atgOManyToOneRelation("id_contact", "individu.contact_i", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),null,116);
		$this->add ( new atkAttribute ( "id_contact", 0 ), null, 116 );
		$this->add ( new atkDateAttribute ( "date_debut_periode", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY | AF_FORCE_LOAD ) );
		$this->add ( new atkDateAttribute ( "date_fin_periode", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY ) );
		$this->add ( new atkNumberAttribute ( "nombre_heures", NULL, 12, 0 ), null, 200 );
		$this->add ( new atkNumberAttribute ( "montant_indemnite_heure", AF_HIDE_ADD, 12, 3 ), null, 210 );
		$this->add ( new atgNumberExpressionAttribute ( "total_indemnite_heures", ' select nombre_heures*montant_indemnite_heure
			 from individu_activite ia
			where ia.id=[table].id
			', 0, AF_TOTAL ), NULL, 220 );
		$this->add ( new atkNumberAttribute ( "nombre_kilometres", NULL, 12, 0 ), NULL, 230 );
		$this->add ( new atkNumberAttribute ( "montant_indemnite_kilometre", AF_HIDE_ADD, 12, 3 ), NULL, 240 );
		$this->add ( new atgNumberExpressionAttribute ( "total_indemnite_kilometres", ' select nombre_kilometres*montant_indemnite_kilometre
			 from individu_activite ia
			where ia.id=[table].id
			', 0, AF_TOTAL ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_peage", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_parking", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_taxi", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_transport_en_commun", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_repas", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_hotel", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_fournitures_diverses", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atkNumberAttribute ( "montant_frais_divers", NULL, 12, 2 ), NULL, 250 );
		$this->add ( new atgNumberExpressionAttribute ( "total_note", ' select (nombre_kilometres*montant_indemnite_kilometre)
			
			+ montant_peage + montant_parking + montant_transport_en_commun + montant_repas + montant_hotel + montant_fournitures_diverses + montant_frais_divers
			 from individu_activite ia
			where ia.id=[table].id
			', 0, AF_TOTAL ), NULL, 260 );
		$this->add ( new atgFileManyToOneRelation ( "id_document_justificatif", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE ), NULL, 138 );
		$this->add ( new atkNumberAttribute ( "montant_remboursement", NULL, 12, 2 ), NULL, 139 );
		$this->add ( new atkDateAttribute ( "date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING ), NULL, 139 );
		$this->add ( new atkManyToOneRelation ( "id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK ), NULL, 139 );
		$this->add ( new atkDummyAttribute ( "ecritures" ), NULL, 139 );
		$c12 = & $this->add ( new atkManyToOneRelation ( "id_compte_financier", "organisme.compte", AF_RELATION_AUTOLINK ), NULL, 139 );
		$c12->setDestinationFilter ( "organisme_compte.id in ( select id from organisme_compte where ( code like '51%' or code like '53%') and usuel='1' and id_organisme='[id_organisme.id]') " );
		// $this->add(new atkManyToOneRelation("id_individu_rencontre", "individu.rencontre_i", AF_RELATION_AUTOLINK));
		// $this->add(new atkManyToOneRelation("id_individu_contact", "individu.contact_i", AF_RELATION_AUTOLINK));
		$this->add ( new atkAttribute ( "id_individu_rencontre", AF_HIDE_ADD ), NULL, 250 );
		$this->add ( new atkAttribute ( "id_individu_contact", AF_HIDE_ADD ), NULL, 250 );
		include_once (atkconfig ( "atkroot" ) . "modules/include/association.inc");
		$this->add ( new atkDummyAttribute ( "descripteur_module_estampillage", 'text', AF_HIDE_ADD | AF_HIDE_EDIT | AF_NO_LABEL | AF_COMPACT ), null, 8 );
		$this->setOrder ( " date_debut_periode DESC " );
	}
	function id_rencontre_display($record, $mode) {
		$attribute = $this->getAttribute ( "id_rencontre" );
		$original = $attribute->display ( $record, $mode );
		return $this->decoupe_affichage_colonne ( $original, 40 );
	}
	function id_contact_display($record, $mode) {
		$attribute = $this->getAttribute ( "id_contact" );
		$original = $attribute->display ( $record, $mode );
		return $this->decoupe_affichage_colonne ( $original, 40 );
	}
	function id_individu_display($record, $mode) {
		(! empty ( $record ["id_individu"] )) ? $retour = $this->decoupe_affichage_colonne ( $this->descripteur_individu ( $record ["id_individu"] ["id"], 'n' ), 30 ) : $retour = "";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(! empty ( $record ["id_organisme"] )) ? $retour = $this->decoupe_affichage_colonne ( $this->descripteur_organisme ( $record ["id_organisme"] ["id"], 'n' ), 30 ) : $retour = "";
		return $retour;
	}
	function ecritures_display($record, $mode) {
		if (isset ( $record ["id_ecriture_frais"] ) || isset ( $record ["id_ecriture_benevolat"] ) || isset ( $record ["id_ecriture_reglement"] )) {
			return href ( dispatch_url ( "organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record ['id_ecriture_frais'] . "' 
				or organisme_ligne_ecriture_comptable.id_ecriture='" . $record ['id_ecriture_benevolat'] . "'
				or organisme_ligne_ecriture_comptable.id_ecriture='" . $record ['id_ecriture_reglement'] . "'" 
			), "dispatch.php" ), text ( "Voir" ), SESSION_NESTED );
		} else {
			return "Pas d'écritures";
		}
	}
	function descripteur_activite_frais_display($record, $mode) {
		return $this->decoupe_affichage_colonne ( $this->descripteur_activite_frais ( $record ["id"], 'o' ), 100 );
	}
	function descripteur_activite_reglement_display($record, $mode) {
		return $this->decoupe_affichage_colonne ( $this->descripteur_activite_reglement ( $record ["id"], 'o' ), 100 );
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		return $handler->action_admin ();
	}
	function initial_values() {
		$init_vals = array ();
		$filter = atkArrayNvl ( $this->m_postvars, "atkfilter", null );
		$select = strstr ( $filter, "id_individu_rencontre=" );
		$db = & atkGetDb ();
		if ($select != false) {
			$idindividurencontre = str_replace ( "id_individu_rencontre=", "", $select );
			$idindividurencontre = str_replace ( "AND", "", $idindividurencontre );
			$sql = "SELECT
			ire.id_individu,
			ire.id_rencontre,
			ore.id_organisme,
			ore.date_debut,
			ore.heure_debut,
			ore.date_fin,
			ore.heure_fin,
			ore.libelle,
			o.nom
			FROM individu_rencontre ire,
			organisme_rencontre ore,
			organisme o
			WHERE ire.id=$idindividurencontre AND
			ire.id_rencontre=ore.id AND
			ore.id_organisme=o.id
		";
			$stuff = $db->getrows ( $sql );
			$init_vals ["id_individu"] ["id"] = $stuff [0] ["id_individu"];
			$init_vals ["id_organisme"] ["id"] = $stuff [0] ["id_organisme"];
			$init_vals ["libelle"] = $stuff [0] ["nom"] . " : " . $stuff [0] ["libelle"];
			$init_vals ["date_debut_periode"] = $this->datedb2value ( $stuff [0] ["date_debut"] );
			$init_vals ["date_fin_periode"] = $this->datedb2value ( $stuff [0] ["date_fin"] );
			$hd = $this->timedb2value ( $stuff [0] ["heure_debut"] );
			$hf = $this->timedb2value ( $stuff [0] ["heure_fin"] );
			$df = mktime ( $hf ["hours"], $hf ["minutes"], $hf ["seconds"], $init_vals ["date_fin_periode"] ["month"], $init_vals ["date_fin_periode"] ["day"], $init_vals ["date_fin_periode"] ["year"] );
			$dd = mktime ( $hd ["hours"], $hd ["minutes"], $hd ["seconds"], $init_vals ["date_debut_periode"] ["month"], $init_vals ["date_debut_periode"] ["day"], $init_vals ["date_debut_periode"] ["year"] );
			$init_vals ["nombre_heures"] = DateDiff ( "h", $dd, $df, true );
			$init_vals ["id_type_activite"] ["id"] = 20;
			$init_vals ["id_rencontre"] ["id"] = $stuff [0] ["id_rencontre"];
		}
		$select = strstr ( $filter, "id_individu_contact=" );
		if ($select != false) {
			$idindividucontact = str_replace ( "id_individu_contact=", "", $select );
			$idindividucontact = str_replace ( "AND", "", $idindividucontact );
			$sql = "SELECT
			ic.id_contact,
			ic.id,
			i1.nom as nom_contactant,
			i1.prenom as prenom_contactant,
			ic.id_individu,
			i2.nom as nom_contacte,
			i2.prenom as prenom_contacte,
			ic.titre,
			ic.date_realisee
			FROM individu_contact ic,
			individu i1, individu i2
			WHERE ic.id=$idindividucontact AND
			ic.id_contact=i1.id AND
				ic.id_individu=i2.id
		";
			$stuff = $db->getrows ( $sql );
			$init_vals ["id_individu"] ["id"] = $stuff [0] ["id_contact"];
			$init_vals ["id_contact"] ["id"] = $stuff [0] ["id"];
			$init_vals ["libelle"] = $stuff [0] ["titre"] . ". De " . $stuff [0] ["prenom_contactant"] . " " . $stuff [0] ["nom_contactant"] . " à " . $stuff [0] ["prenom_contacte"] . " " . $stuff [0] ["nom_contacte"];
			$init_vals ["date_debut_periode"] = $this->datedb2value ( $stuff [0] ["date_realisee"] );
			$init_vals ["date_fin_periode"] = $this->datedb2value ( $stuff [0] ["date_realisee"] );
			$init_vals ["id_type_activite"] ["id"] = 20;
			$init_vals ["id_rencontre"] ["id"] = $stuff [0] ["id_rencontre"];
			$init_vals ["nombre_heures"] = '1';
		} else {
			$user = getUser ();
			$id = $user ["id"];
			$db = & atkGetDb ();
			$data = $db->getrows ( "SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " " );
			$idutilisateur = $data [0] ["idutilisateur"];
			$init_vals ["id_individu"] ["id"] = $idutilisateur;
			$init_vals ["nombre_heures"] = 0;
		}
		$init_vals ["nombre_kilometres"] = 0;
		
		$init_vals ["montant_peage"] = 0;
		$init_vals ["montant_parking"] = 0;
		$init_vals ["montant_taxi"] = 0;
		$init_vals ["montant_transport_en_commun"] = 0;
		$init_vals ["montant_repas"] = 0;
		$init_vals ["montant_hotel"] = 0;
		$init_vals ["montant_fournitures_diverses"] = 0;
		$init_vals ["montant_frais_divers"] = 0;
		
		return $init_vals;
	}
	function presence_compta_edit($record, $mode) {
		$id_organisme = $record ["id_organisme"] ["id"];
		$db = & atkGetDb ();
		$sql = "SELECT nom as nom, date_initialisation_comptabilite  from organisme
									 where id='" . $id_organisme . "'";
		$data = $db->getrows ( $sql );
		if ($data [0] ["date_initialisation_comptabilite"] != null) {
			return 'La comptabilité a été initialisée pour ' . $data [0] ["nom"] . ' le ' . $data [0] ["date_initialisation_comptabilite"];
		} else {
			return '<font color="Red"> <b> La comptabilité n\'ayant pas été initialisée pour ' . $data [0] ["nom"] . ', la saisie de montant versé ne sera pas prise en compte dans la comptabilité.';
		}
	}
	function id_ecriture_reglement_display($record, $mode) {
		return $this->descripteur_ecriture_comptable ( $record ["id_ecriture_reglement"] );
	}
	function id_ecriture_frais_display($record, $mode) {
		return $this->descripteur_ecriture_comptable ( $record ["id_ecriture_frais"] );
	}
	function id_ecriture_benevolat_display($record, $mode) {
		return $this->descripteur_ecriture_comptable ( $record ["id_ecriture_benevolat"] );
	}
	function postUpdate($record) {
		$this->mise_a_jour_type_ecriture ( $record );
		parent::postUpdate ( $record );
		return true;
	}
	function postAdd($record) {
		$db = & atkGetDb ();
		$data = $db->getrows ( 'Select max(id) as id from individu_activite' );
		$record ["id"] = $data [0] ["id"];
		$this->mise_a_jour_type_ecriture ( $record );
		parent::postAdd ( $record );
		return true;
	}
	function mise_a_jour_type_ecriture($record) {
		if (! empty ( $record ["id_ecriture_frais"] )) {
			$this->ecriture_type_origine_maj ( $record ["id_ecriture_frais"], $this->type_ecriture_frais, $record ["id"] );
		}
		if (! empty ( $record ["id_ecriture_reglement"] )) {
			$this->ecriture_type_origine_maj ( $record ["id_ecriture_reglement"], $this->type_ecriture_frais, $record ["id"] );
		}
		if (! empty ( $record ["id_ecriture_benevolat"] )) {
			$this->ecriture_type_origine_maj ( $record ["id_ecriture_benevolat"], $this->type_ecriture_frais, $record ["id"] );
		}
		return true;
	}
	function validate(&$record, $mode) {
		// $this->p($record);
		$this->RazDestinationFilters ();
		if (($record ["nombre_heures"] + $record ["nombre_kilometres"] + $record ["montant_peage"] + $record ["montant_parking"] + $record ["montant_transport_en_commun"] + $record ["montant_repas"] + $record ["montant_hotel"] + $record ["montant_fournitures_diverses"] + $record ["montant_frais_divers"] + $record ["montant_remboursement"]) == 0) {
			triggerError ( $record, "nombre_heures", 'Valeurs', atktext ( "Toutes les valeurs sont à zéro", "atk" ) );
		}
		if (empty ( $record ["id_organisme"] ["id"] )) {
			triggerError ( $record, "id_organisme", 'Valeurs', atktext ( "L'organisme n'est pas renseigné", "atk" ) );
		}
		
		if ($record ["montant_remboursement"] > 0) {
			if ($record ["date_reglement"] == "") {
				atkTriggerError ( $record, $this->getAttribute ( "date_reglement" ), "En cas de règlement vous devez préciser la date" );
			}
			if ($record ["id_compte_financier"] ["id"] == "") {
				atkTriggerError ( $record, $this->getAttribute ( "id_compte_financier" ), "Vous devez choisir un compte de finance" );
			}
			if ($record ["id_reglement"] ["id"] == "") {
				atkTriggerError ( $record, $this->getAttribute ( "id_reglement" ), "Vous devez choisir un type de règlement" );
			}
			
			if ($record ["id_reglement"] ["id"] != 1 && $record ["numero_cheque"] != "") {
				atkTriggerError ( $record, $this->getAttribute ( "numero_cheque" ), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque" );
			}
			if ($record ["id_reglement"] ["id"] == 1 && $record ["numero_cheque"] == "") {
				atkTriggerError ( $record, $this->getAttribute ( "numero_cheque" ), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque" );
			}
		} else {
			if ($record ["date_reglement"] != "") {
				atkTriggerError ( $record, $this->getAttribute ( "date_reglement" ), "Pas de montant règlé et date de règlement ?" );
			}
			if ($record ["id_compte_financier"] ["id"] != "") {
				atkTriggerError ( $record, $this->getAttribute ( "id_compte_financier" ), "Pas de montant règlé et un compte de finance ?" );
			}
			if ($record ["id_reglement"] ["id"] != "") {
				atkTriggerError ( $record, $this->getAttribute ( "id_reglement" ), "Pas de montant règlé et un type de règlement ?" );
			}
			
			if ($record ["numero_cheque"] != "") {
				atkTriggerError ( $record, $this->getAttribute ( "numero_cheque" ), "Pas de montant règlé et un numéro de chèque ?" );
			}
		}
		if (parent::validate ( $record, $mode ) == true) {
			if ($mode == "update")
				$this->supprimer_ecritures ( $record );
			$this->creer_ecritures_comptables ( $record );
		}
	}
	function preDelete(& $record) {
		$this->RazDestinationFilters ();
		$this->supprimer_ecritures ( $record );
		parent::preDelete ( $record );
	}
	function supprimer_ecritures(& $record) {
		$db = & atkGetDb ();
		$id_ecriture_frais = $record ["id_ecriture_frais"];
		$id_ecriture_benevolat = $record ["id_ecriture_benevolat"];
		$id_ecriture_reglement = $record ["id_ecriture_reglement"];
		if ($id_ecriture_frais == "" && $id_ecriture_benevolat == "") {
			return true;
		}
		if (isset ( $id_ecriture_frais )) {
			$this->supprimer_ecriture_comptable ( $id_ecriture_frais );
		}
		if (isset ( $id_ecriture_benevolat )) {
			$this->supprimer_ecriture_comptable ( $id_ecriture_benevolat );
		}
		if (isset ( $id_ecriture_reglement )) {
			$this->supprimer_ecriture_comptable ( $id_ecriture_reglement );
		}
		return true;
	}
	function creer_ecritures_comptables(& $record) {
		// print_r ($record);
		// die();
		$id_organisme = $record ['id_organisme'] ['id'];
		$id_individu = $record ['id_individu'] ['id'];
		global $g_user;
		$userid = $g_user ["id"];
		$db = & atkGetDb ();
		$rang = $db->getrows ( "SELECT
		id_compte_adherents ,
		id_journal_frais ,
		id_journal_benevolat ,
		id_journal_caisse,
		id_journal_banque_courant,
		id_compte_kilometres,
		id_compte_peage,
		id_compte_parking,
		id_compte_transport_en_commun,
		id_compte_repas,
		id_compte_hotel,
		id_compte_fournitures_diverses,
		id_compte_frais_divers,
		id_compte_benevolat,
		id_compte_personnel_benevole,
		montant_indemnite_kilometre,
		montant_indemnite_heure_benevolat
		FROM organisme where id=$id_organisme " );
		$id_journal_frais = $rang [0] ["id_journal_frais"];
		
		$date_reglement = $this->dateatktodb ( $record ["date_reglement"] );
		$date_ecriture = $this->dateatktodb ( $record ["date_fin_periode"] );
		$id_journal_caisse = $rang [0] ["id_journal_caisse"];
		if (! isset ( $id_journal_caisse )) {
			echo '<br><b>Journal caisse non initialisé<br> ';
			die ();
		}
		$id_journal_banque_courant = $rang [0] ["id_journal_banque_courant"];
		if (! isset ( $id_journal_banque_courant )) {
			echo '<br><b>Journal banque courant non initialisé<br> ';
			die ();
		}
		if (! isset ( $id_journal_frais )) {
			echo '<br><b>Journal frais non initialisé<br> ';
			die ();
		}
		$id_journal_benevolat = $rang [0] ["id_journal_benevolat"];
		if (! isset ( $id_journal_benevolat )) {
			echo '<br><b>Journal bénévolat non initialisé<br> ';
			die ();
		}
		$id_compte_adherents = $rang [0] ["id_compte_adherents"];
		if (! isset ( $id_compte_adherents )) {
			echo '<br><b>Compte adhérents non initialisé<br> ';
			die ();
		}
		$id_compte_kilometres = $rang [0] ["id_compte_kilometres"];
		if (! isset ( $id_compte_kilometres )) {
			echo '<br><b>Compte indemnités kilométriques non initialisé<br> ';
			die ();
		}
		$id_compte_peage = $rang [0] ["id_compte_peage"];
		if (! isset ( $id_compte_peage )) {
			echo '<br><b>Compte péage non initialisé<br> ';
			die ();
		}
		$id_compte_parking = $rang [0] ["id_compte_parking"];
		if (! isset ( $id_compte_parking )) {
			echo '<br><b>Compte parking non initialisé<br> ';
			die ();
		}
		$id_compte_transport_en_commun = $rang [0] ["id_compte_transport_en_commun"];
		if (! isset ( $id_compte_transport_en_commun )) {
			echo '<br><b>Compte transport en commun non initialisé<br> ';
			die ();
		}
		$id_compte_repas = $rang [0] ["id_compte_repas"];
		if (! isset ( $id_compte_repas )) {
			echo '<br><b>Compte repas non initialisé<br> ';
			die ();
		}
		$id_compte_hotel = $rang [0] ["id_compte_hotel"];
		if (! isset ( $id_compte_hotel )) {
			echo '<br><b>Compte frais hôtel non initialisé<br> ';
			die ();
		}
		$id_compte_fournitures_diverses = $rang [0] ["id_compte_fournitures_diverses"];
		if (! isset ( $id_compte_fournitures_diverses )) {
			echo '<br><b>Compte fournitures diverses non initialisé<br> ';
			die ();
		}
		$id_compte_frais_divers = $rang [0] ["id_compte_frais_divers"];
		if (! isset ( $id_compte_frais_divers )) {
			echo '<br><b>Compte frais divers non initialisé<br> ';
			die ();
		}
		$id_compte_benevolat = $rang [0] ["id_compte_benevolat"];
		if (! isset ( $id_compte_benevolat )) {
			echo '<br><b>Compte bénévolat non initialisé<br> ';
			die ();
		}
		$id_compte_personnel_benevole = $rang [0] ["id_compte_personnel_benevole"];
		if (! isset ( $id_compte_personnel_benevole )) {
			echo '<br><b>Compte personnel bénévole non initialisé<br> ';
			die ();
		}
		$id_individu = $record ["id_individu"] ["id"];
		$record ["montant_indemnite_heure"] = $rang [0] ["montant_indemnite_heure_benevolat"];
		if (! isset ( $rang [0] ["montant_indemnite_heure_benevolat"] )) {
			echo '<br><b>Montant indemnité horaire non initialisé<br> ';
			die ();
		}
		$record ["montant_indemnite_kilometre"] = $rang [0] ["montant_indemnite_kilometre"];
		if (! isset ( $rang [0] ["montant_indemnite_kilometre"] )) {
			echo '<br><b>Montant indemnité kilométrique non initialisé<br> ';
			die ();
		}
		$individu = $db->getrows ( "SELECT nom, prenom
																	from individu where id='" . $id_individu . "'" );
		$libelle = $individu [0] ["nom"] . ' ' . $individu [0] ["prenom"] . ' : frais de déplacement (' . $record ["libelle"] . '.)';
		if (($record ["nombre_kilometres"] + $record ["montant_peage"] + $record ["montant_parking"] + $record ["montant_transport_en_commun"] + $record ["montant_repas"] + $record ["montant_hotel"] + $record ["montant_fournitures_diverses"] + $record ["montant_frais_divers"]) > 0) {
			$id_ecriture = $this->creer_ecriture_comptable ( $id_organisme, $id_journal_frais, $libelle, $date_ecriture );
			$record ["id_ecriture_frais"] = $id_ecriture;
			$debit = 0;
			$credit = ($record ["nombre_kilometres"] * $record ["montant_indemnite_kilometre"]) + $record ["montant_peage"] + $record ["montant_parking"] + $record ["montant_transport_en_commun"] + $record ["montant_repas"] + $record ["montant_hotel"] + $record ["montant_fournitures_diverses"] + $record ["montant_frais_divers"];
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = ($record ["nombre_kilometres"] * $record ["montant_indemnite_kilometre"]);
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_kilometres, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_peage"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_peage, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_parking"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_parking, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_transport_en_commun"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_transport_en_commun, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_repas"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_repas, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_hotel"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_hotel, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_fournitures_diverses"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_fournitures_diverses, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$debit = $record ["montant_frais_divers"];
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_frais, $id_compte_frais_divers, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
		}
		if (($record ["nombre_heures"]) > 0) {
			$libelle = $individu [0] ["nom"] . ' ' . $individu [0] ["prenom"] . ' : temps de bénévolat (' . $record ["libelle"] . '.)';
			$id_ecriture = $this->creer_ecriture_comptable ( $id_organisme, $id_journal_benevolat, $libelle, $date_ecriture );
			$record ["id_ecriture_benevolat"] = $id_ecriture;
			$debit = ($record ["nombre_heures"] * $record ["montant_indemnite_heure"]);
			$credit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_benevolat, $id_compte_benevolat, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
			$credit = ($record ["nombre_heures"] * $record ["montant_indemnite_heure"]);
			$debit = 0;
			$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_benevolat, $id_compte_personnel_benevole, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
		}
		if (($record ["montant_remboursement"]) > 0) {
			$id_compte_financier = $record ["id_compte_financier"] ["id"];
			
			if (empty ( $id_compte_financier )) {
				$this->supprimer_ecritures ( $record );
				;
				triggerError ( $record, "id_compte_financier", 'Valeurs', atktext ( "Vous n'avez pas sélectionné de compte de banque", "atk" ) );
				;
				return false;
			}
			$sql = "SELECT code	from organisme_compte where id=$id_compte_financier and id_organisme=$id_organisme";
			$compte = $db->getrows ( $sql );
			$codecomptefinancier = $compte [0] ["code"];
			
			$libelle = $individu [0] ["nom"] . ' ' . $individu [0] ["prenom"] . ' : remboursement frais (' . $record ["libelle"] . '.)';
			
			if (substr ( $codecomptefinancier, 0, 2 ) == '53') {
				// epèces reçues en caisse
				$id_ecriture = $this->creer_ecriture_comptable ( $id_organisme, $id_journal_caisse, $libelle, $date_reglement );
				$record ["id_ecriture_reglement"] = $id_ecriture;
				$debit = $record ["montant_remboursement"];
				$credit = 0;
				$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
				$credit = $record ["montant_remboursement"];
				$debit = 0;
				$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_caisse, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_typereglement, null, $date_reglement, null );
			}
			if (substr ( $codecomptefinancier, 0, 2 ) == '51') {
				// banque
				$id_ecriture = $this->creer_ecriture_comptable ( $id_organisme, $id_journal_banque_courant, $libelle, $date_reglement );
				$record ["id_ecriture_reglement"] = $id_ecriture;
				$debit = $record ["montant_remboursement"];
				$credit = 0;
				$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null );
				$numero_cheque = $record ["numero_cheque"];
				$credit = $record ["montant_remboursement"];
				$debit = 0;
				$this->creer_ligne_ecriture_comptable ( $id_ecriture, $id_journal_banque_courant, $id_compte_financier, $id_organisme, $id_individu, $debit, $credit, $id_typereglement, $numero_cheque, $date_reglement, null );
			}
		}
	}
	function RazDestinationFilters() {
		$attrib = $this->getAttribute ( "id_compte_financier" );
		$attrib->setDestinationFilter ( "" );
		
		return true;
	}
	function descriptor_def() {
		return "[id]";
	}
}
?>