<?php
useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgNumberExpressionAttribute");
class organisme extends assMetaNode {
	var $table = "organisme";
	function meta(& $policy) {
		$policy->addFlags("nom", "sigle", "site_internet", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "objectifs", "p_texte_carte", "p_explication_carte", "p_texte_timbre", "p_explication_timbre", "p_texte_recu_fiscal", "p_explication_recu_fiscal", "p_texte_rappel_cotisation", "p_explication_rappel_cotisation", "p_texte_radiation_non_cotisation", "p_explication_radiation_non_cotisation", "p_texte_radiation_non_adhesion", "p_explication_radiation_non_adhesion", AF_HIDE_LIST);
	}
	function organisme() {
		$this->atkMetaNode();
		$this->atkNode("organisme", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"descripteur_organisme",
				"nom",
				"sigle",
		"siret",
		"siret_recepisse_prefecture",
				"objectif_concis",
				"id_type_organisme",
	
				"telephone",
		"courriel_grp",
		"calendrier_grp",
		"site_internet_grp",
				"acces_public_o_n",
				"objectifs",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Projet" => array (
					"id_logo",
					"id_icone",
				"id_plaquette",
				"id_statuts",
				"id_reglement_interieur",
				"id_projet_associatif",

				"id_organigramme_du_personnel",
				"numero_association",
				"date_declaration_association",
				"date_publication_jo"
				),
					
			"Paramètres" => array (
				"Pane12"
				),
			"Comptabilité" => array (
				"compta_init",
				"date_initialisation_comptabilite",
				"date_fin_exercice_comptable",
				"date_cloture_comptabilite"
					
				),
			"Logo" => array (
				"logo"
				),
			"Fédération" => array (
				"id_organisme_federation",
				"id_contact_federation",
				"id_association_dans_federation"
				),
			"Traitements" => array (

				"date_derniere_preparation",
				"id_derniere_preparation",
					"date_derniere_preparation_fin",
					"id_derniere_preparation_fin",
			  "date_envoi_recu_fiscal",
  "id_envoi_recu_fiscal",
  "date_envoi_timbre",
  "id_envoi_timbre",
  "date_envoi_carte",
 "id_envoi_carte",
  "date_recu_abandon_creance",
  "id_recu_abandon_creance",
 "date_synchronisation_federation",
  "id_synchronisation_federation",
				"creation_cotisation_federation_seule",
				"trim_1",
				"trim_2",
				"trim_3",
				"trim_4",
				"trim_5",
				"trim_6",
				"trim_66",
				"trim_7",
				"trim_8",
				"trim_9",
				"inscription_federation",
				"radiation_federation",
				"cotisation_federation",
				"maj_cotisation_federation"
				
				)
				), AF_NO_LABEL));
				$this->add(new atkTabbedPane("Pane12", array (
			"Notifications" => array (
				"p_texte_carte",
				"p_explication_carte",
				"p_texte_timbre",
				"p_explication_timbre",
				"p_texte_recu_fiscal",
				"p_explication_recu_fiscal",
				"p_texte_rappel_cotisation",
				"p_explication_rappel_cotisation",
				"p_texte_radiation_non_cotisation",
				"p_explication_radiation_non_cotisation",
				"p_texte_radiation_non_adhesion",
				"p_explication_radiation_non_adhesion"
				),
			"Compteurs" => array (
				"prochain_id_ecriture",
				"prochain_id_remise_en_banque",
				"prochain_id_recu_fiscal",
				"prochain_id_inscription"
				),
			"Comptes automatiques" => array (
				"id_compte_dons",
				"id_compte_cotisation_organisme_an_prec",
				"id_compte_cotisation_organisme_an",
				"id_compte_cotisation_organisme_an_suiv",
				"id_compte_cotisation_federation_an_prec",
				"id_compte_cotisation_federation_an",
				"id_compte_cotisation_federation_an_suiv",
				"id_compte_adherents",
				"id_compte_financeurs",
				"id_compte_fournisseurs",
				"id_compte_federation",
				"id_compte_banque_courant",
				"id_compte_banque_epargne",
				"id_compte_caisse",
				"id_compte_participation_manifestation",
				"id_compte_kilometres",
				"id_compte_peage",
				"id_compte_parking",
				"id_compte_transport_en_commun",
				"id_compte_repas",
				"id_compte_hotel",
				"id_compte_fournitures_diverses",
				"id_compte_frais_divers",
				"id_compte_benevolat",
				"id_compte_personnel_benevole"
				),
			"Journaux" => array (
				"id_journal_cotisations_organisme",
				"id_journal_cotisations_federation",
				"id_journal_depenses",
				"id_journal_recettes",
				"id_journal_banque_courant",
				"id_journal_banque_epargne",
				"id_journal_caisse",
				"id_journal_frais",
				"id_journal_benevolat",
				"id_journal_operations_diverses",
				"eclater_cotisations_dons_o_n"
				),
			"Indemnités de base" => array (
				"montant_indemnite_kilometre",
				"site_montant_indemnite_kilometre",
				"montant_indemnite_heure_benevolat",
				"site_montant_indemnite_heure_benevolat"
				),
				"Google" => array (
				"identifiant_google",
				"code_google",
				"tz_offset_google",
				"calendrier_rencontres_nom",
				"calendrier_rencontres_url",
				"calendrier_rencontres_uri",
				"calendrier_rencontres_refresh",
				"calendrier_contacts_nom",
				"calendrier_contacts_url",
				"calendrier_contacts_uri",
				"calendrier_contacts_refresh"
				)
				), AF_NO_LABEL));
				$this->add(new atkDummyAttribute("descripteur_organisme",0,AF_HIDE_EDIT | AF_COMPACT ),3);
				$this->add(new atkAttribute("identifiant_google", AF_HIDE_LIST), 1005);
				$this->add(new atkPasswordAttribute("code_google", false,  AF_PASSWORD_NO_ENCODE | AF_HIDE_LIST), 1010);
				$this->add(new atkTimeZoneAttribute("tz_offset_google",  AF_HIDE_LIST),1020);
				$this->add(new atkAttribute("calendrier_rencontres_nom", AF_HIDE_LIST), 1025);
				$this->add(new atkAttribute("calendrier_rencontres_url", AF_HIDE_LIST), 1030);
				$this->add(new atkAttribute("calendrier_rencontres_uri",  AF_HIDE_LIST),1035);
				$this->add(new atkDateAttribute("calendrier_rencontres_refresh", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_DATE_STRING ),1036);
				$this->add(new atkAttribute("calendrier_contacts_nom", AF_HIDE_LIST), 1040);
				$this->add(new atkAttribute("calendrier_contacts_url", AF_HIDE_LIST), 1045);
				$this->add(new atkAttribute("calendrier_contacts_uri",  AF_HIDE_LIST),1050);
				$this->add(new atkDateAttribute("calendrier_contacts_refresh", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_DATE_STRING ),1055);
					
				$this->add(new atkBoolAttribute("acces_public_o_n"));
				$this->add(new atkBoolAttribute("eclater_cotisations_dons_o_n",AF_HIDE_LIST));
				$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY | AF_UNIQUE), 100);
				$this->add(new atkAttribute("sigle", AF_SEARCHABLE), 108);
				$this->add(new atkAttribute("siret", AF_HIDE_LIST), 109);
				$this->add(new atkAttribute("siret_recepisse_prefecture", AF_HIDE_LIST), 110);
				$this->add(new atkAttribute("objectif_concis", AF_SEARCHABLE), 7);
				$this->add(new atkAttribute("id_association_dans_federation", AF_HIDE_LIST), 112);
				$this->add(new atkManyToOneRelation("id_type_organisme", "table.type_organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK), 5);
				$this->add(new atkAttribute("telephone", AF_SEARCHABLE), 130);
				$this->add(new atkEmailAttribute("courriel", true, AF_SEARCHABLE), 140);
				$this->add(new atkUrlAttribute("calendrier", AF_POPUP | AF_SEARCHABLE), 145);
				$this->add(new atkUrlAttribute("site_internet", AF_POPUP | AF_SEARCHABLE), 150);
/*				$this->add(new atgNumberExpressionAttribute("fonctions", ' select count(id) from individu_fonction
	 where id_organisme =[table].id and date_fin is null
					', 0, 0),121);
				$this->add(new atgNumberExpressionAttribute("inscriptions", ' select count(id) from individu_inscription
	 where id_organisme =[table].id and date_radiation is null
					', 0, 0),122);
					*/
				$this->add(new atkNumberAttribute("montant_indemnite_kilometre",  AF_HIDE_LIST, 10, 3));
				$this->add(new atkNumberAttribute("montant_indemnite_heure_benevolat",  AF_HIDE_LIST, 10, 3));
				$this->add(new atkfckattribute("objectifs", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Basic',
			'Width' => '750px',
			'Height' => '150px'
			)), 170);
			$this->add(new atkTextAttribute("p_explication_carte", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_explication_timbre", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_explication_recu_fiscal", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_explication_rappel_cotisation", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_explication_radiation_non_cotisation", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_explication_radiation_non_adhesion", array (
			'autoadjust' => 'yes',
			'rows' => '2'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_carte", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_timbre", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_recu_fiscal", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_rappel_cotisation", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_radiation_non_cotisation", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));
			$this->add(new atkTextAttribute("p_texte_radiation_non_adhesion", array (
			'autoadjust' => 'yes',
			'rows' => '1'
			), AF_HIDE_LIST));

			$this->add(new atkParserAttribute("courriel_go",
			atkHref("?atknodetype=individu.contact_i&atkaction=add&atkfilter=individu_contact.id_individu=$id_individu_utilisateur&idcontactant=$id_individu_utilisateur&atgemail=[courriel]&"
			, atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->add(new atkParserAttribute("calendrier_go",atkHref("[calendrier]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);
			$this->add(new atkParserAttribute("site_internet_go",atkHref("[site_internet]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->addFieldSet("courriel_grp"," [courriel.field] [courriel_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("calendrier_grp"," [calendrier.field] [calendrier_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("site_internet_grp"," [site_internet.field] [site_internet_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );


			$this->add(new atkManyToOneRelation("id_organisme_federation", "organisme.organisme", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), "fédération");
			$this->add(new atkManyToOneRelation("id_contact_federation", "individu.individu", AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE), "fédération");
//			$this->add(new atkDateAttribute("date_synchronisation_federation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_READONLY| AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_initialisation_comptabilite", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_READONLY| AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_fin_exercice_comptable", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING |  AF_HIDE_LIST));
			
			$this->add(new atkDateAttribute("date_cloture_comptabilite", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_READONLY| AF_HIDE_LIST));
			$this->add(new atkFileAttribute("logo", "./logos", AF_HIDE_LIST));
			$this->add(new atkNumberAttribute("prochain_id_ecriture", AF_HIDE_LIST));
			$this->add(new atkNumberAttribute("prochain_id_remise_en_banque", AF_HIDE_LIST));
			$this->add(new atkNumberAttribute("prochain_id_recu_fiscal", AF_HIDE_LIST));
			$this->add(new atkNumberAttribute("prochain_id_inscription", AF_HIDE_LIST));
			$d110 = & $this->add(new atgFileManyToOneRelation("id_logo", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST ));
			$d110->addDestinationFilter("id_organisme= '[id]'");
			$d120 = & $this->add(new atgFileManyToOneRelation("id_icone", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST ));
			$d120->addDestinationFilter("id_organisme= '[id]'");
			
			$d101 = & $this->add(new atgFileManyToOneRelation("id_plaquette", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST ));
			$d101->addDestinationFilter("id_organisme= '[id]'");

			$d100 = & $this->add(new atgFileManyToOneRelation("id_statuts", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST ));
			$d100->addDestinationFilter("id_organisme= '[id]'");
			$d200 = & $this->add(new atgFileManyToOneRelation("id_reglement_interieur", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST));
			$d200->addDestinationFilter("id_organisme= '[id]'");
			$d300 = & $this->add(new atgFileManyToOneRelation("id_projet_associatif", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST));
			$d300->addDestinationFilter("id_organisme= '[id]'");
			//						$d400 = & $this->add(new atgFileManyToOneRelation("id_certification", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST));
			//			$d400->addDestinationFilter("id_organisme= '[id]'");
			/*			$d400 = & $this->add(new atkManyToOneRelation("id_organigramme_vie_statutaire", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST));
			$d400->addDestinationFilter("id_organisme= '[id]'");
			*/
			$d500 = & $this->add(new atgFileManyToOneRelation("id_organigramme_du_personnel", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST));
			$d500->addDestinationFilter("id_organisme= '[id]'");
			$this->add(new atkAttribute("numero_association", AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_declaration_association", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_publication_jo", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_HIDE_LIST));
/*
			$c1 = & $this->add(new atkManyToOneRelation("id_compte_dons", "organisme.compte", AF_LARGE | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c1->addDestinationFilter("id_organisme= '[id]'");
			$c2 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_organisme_an_prec", "organisme.compte", AF_LARGE | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c2->addDestinationFilter("id_organisme= '[id]'");
			$c3 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_organisme_an", "organisme.compte", AF_LARGE | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c3->addDestinationFilter("id_organisme= '[id]'");
			$c4 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_organisme_an_suiv", "organisme.compte", AF_LARGE | AF_RELATION_AUTOCOMPLETE | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c4->addDestinationFilter("id_organisme= '[id]'");
			$c5 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_federation_an_prec", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c5->addDestinationFilter("id_organisme= '[id]'");
			$c6 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_federation_an", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c6->addDestinationFilter("id_organisme= '[id]'");
			$c7 = & $this->add(new atkManyToOneRelation("id_compte_cotisation_federation_an_suiv", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c7->addDestinationFilter("id_organisme= '[id]'");
			$c8 = & $this->add(new atkManyToOneRelation("id_compte_adherents", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c8->addDestinationFilter("id_organisme= '[id]'");
			$c80 = & $this->add(new atkManyToOneRelation("id_compte_fournisseurs", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c80->addDestinationFilter("id_organisme= '[id]'");
			$c81 = & $this->add(new atkManyToOneRelation("id_compte_financeurs", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c81->addDestinationFilter("id_organisme= '[id]'");
			$c9 = & $this->add(new atkManyToOneRelation("id_compte_federation", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c9->addDestinationFilter("id_organisme= '[id]'");
			$c10 = & $this->add(new atkManyToOneRelation("id_compte_banque_courant", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c10->addDestinationFilter("id_organisme= '[id]'");
			$c11 = & $this->add(new atkManyToOneRelation("id_compte_banque_epargne", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c11->addDestinationFilter("id_organisme= '[id]'");
			$c110 = & $this->add(new atkManyToOneRelation("id_compte_caisse", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c110->addDestinationFilter("id_organisme= '[id]'");
			$c111 = & $this->add(new atkManyToOneRelation("id_compte_participation_manifestation", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c111->addDestinationFilter("id_organisme= '[id]'");
			$c112 = & $this->add(new atkManyToOneRelation("id_compte_kilometres", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c112->addDestinationFilter("id_organisme= '[id]'");
			$c113 = & $this->add(new atkManyToOneRelation("id_compte_peage", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c113->addDestinationFilter("id_organisme= '[id]'");
			$c114 = & $this->add(new atkManyToOneRelation("id_compte_parking", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c114->addDestinationFilter("id_organisme= '[id]'");
			$c115 = & $this->add(new atkManyToOneRelation("id_compte_transport_en_commun", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c115->addDestinationFilter("id_organisme= '[id]'");
			$c116 = & $this->add(new atkManyToOneRelation("id_compte_repas", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c116->addDestinationFilter("id_organisme= '[id]'");
			$c117 = & $this->add(new atkManyToOneRelation("id_compte_hotel", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c117->addDestinationFilter("id_organisme= '[id]'");
			$c118 = & $this->add(new atkManyToOneRelation("id_compte_fournitures_diverses", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c118->addDestinationFilter("id_organisme= '[id]'");
			$c119 = & $this->add(new atkManyToOneRelation("id_compte_frais_divers", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c119->addDestinationFilter("id_organisme= '[id]'");
			$c120 = & $this->add(new atkManyToOneRelation("id_compte_benevolat", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c120->addDestinationFilter("id_organisme= '[id]'");
			$c130 = & $this->add(new atkManyToOneRelation("id_compte_personnel_benevole", "organisme.compte", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c130->addDestinationFilter("id_organisme= '[id]'");
			$c12 = & $this->add(new atkManyToOneRelation("id_journal_cotisations_organisme", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c12->addDestinationFilter("id_organisme= '[id]'");
			$c13 = & $this->add(new atkManyToOneRelation("id_journal_cotisations_federation", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c13->addDestinationFilter("id_organisme= '[id]'");
			$c14 = & $this->add(new atkManyToOneRelation("id_journal_depenses", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c14->addDestinationFilter("id_organisme= '[id]'");
			$c15 = & $this->add(new atkManyToOneRelation("id_journal_recettes", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c15->addDestinationFilter("id_organisme= '[id]'");
			$c16 = & $this->add(new atkManyToOneRelation("id_journal_banque_courant", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c16->addDestinationFilter("id_organisme= '[id]'");
			$c17 = & $this->add(new atkManyToOneRelation("id_journal_banque_epargne", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c17->addDestinationFilter("id_organisme= '[id]'");
			$c170 = & $this->add(new atkManyToOneRelation("id_journal_caisse", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c170->addDestinationFilter("id_organisme= '[id]'");
			$c180 = & $this->add(new atkManyToOneRelation("id_journal_frais", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c180->addDestinationFilter("id_organisme= '[id]'");
			$c181 = & $this->add(new atkManyToOneRelation("id_journal_benevolat", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c181->addDestinationFilter("id_organisme= '[id]'");
			$c182 = & $this->add(new atkManyToOneRelation("id_journal_operations_diverses", "organisme.journal_comptable", AF_LARGE | AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$c182->addDestinationFilter("id_organisme= '[id]'");
*/			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,5);
			$this->m_securityMap["googlemap"] = "view";
			$this->m_securityMap["google"] = "view";
			$this->add(new atkParserAttribute("inscription_federation", "Inscriptions à reporter à la fédération --> " . href("?atkaction=traitement&id=[id]&atkcode=8", atktext("Voir"), SESSION_NESTED) . " " . href("?atkaction=listeecran&id=[id]&atkcode=8&atkexport='o'", atktext("Exporter"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("radiation_federation", "Radiations à reporter à la fédération --> " . href("?atkaction=traitement&id=[id]&atkcode=9", atktext("Voir"), SESSION_NESTED) . " " . href("?atkaction=listeecran&id=[id]&atkcode=9&atkexport='o'", atktext("Exporter"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("cotisation_federation", "Cotisations à règler à la fédération --> " . href("?atkaction=traitement&id=[id]&atkcode=10", atktext("Voir"), SESSION_NESTED) . " " . href("?atkaction=listeecran&id=[id]&atkcode=10&atkexport='o'", atktext("Exporter"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("maj_cotisation_federation", href("?atkaction=traitement&id=[id]&atkcode=11", atktext("<br><br>
										Mise à jour cotisations à la fédération"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
				
			$this->add(new atkDateAttribute("date_derniere_preparation", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY),22500);
			$this->add(new atkAttribute("id_derniere_preparation", AF_READONLY),22510);
			$this->add(new atkDateAttribute("date_derniere_preparation_fin", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY),22511);
			$this->add(new atkAttribute("id_derniere_preparation_fin", AF_READONLY),22512);
			$this->add(new atkDateAttribute("date_envoi_recu_fiscal", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY ),22520);
			$this->add(new atkAttribute("id_envoi_recu_fiscal", AF_READONLY),22530);
			$this->add(new atkDateAttribute("date_envoi_timbre", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY ),22540);
			$this->add(new atkAttribute("id_envoi_timbre", AF_READONLY),22550);
			$this->add(new atkDateAttribute("date_envoi_carte", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY ),22560);
			$this->add(new atkAttribute("id_envoi_carte", AF_READONLY),22570);
			$this->add(new atkDateAttribute("date_recu_abandon_creance", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY ),22580);
			$this->add(new atkAttribute("id_recu_abandon_creance", AF_READONLY),22590);
			$this->add(new atkDateAttribute("date_synchronisation_federation", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_READONLY ),22600);
			$this->add(new atkAttribute("id_synchronisation_federation", AF_READONLY),22610);
				
			$this->add(new atkParserAttribute("creation_cotisation_federation_seule", href("?atkaction=traitement&id=[id]&atkcode=100", atktext("<br><br>
										Création des cotisations payés à la fédération pour les membres non cotisants.<br>"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("compta_init", "env1", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("site_montant_indemnite_kilometre", "env155", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("site_montant_indemnite_heure_benevolat", "env156", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_1", "env2", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_2", "env3", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_3", "env4", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_4", "env5", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_5", "env6", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_6", "env7", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_66", "Etablir les cartes d'adhésion à la main<br><br>", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_7", "env8", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_8", "env9", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->add(new atkParserAttribute("trim_9", "env10", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), NULL, 10000);
			$this->m_securityMap["rafraichir_calendrier_rencontres"] = "view";
			$this->m_securityMap["mapindividus"] = "view";
			$this->m_securityMap["autocomplete"] = "view";
			$this->m_securityMap["googlemap"] = "view";
			$this->m_securityMap["appel_cotisation"] = "view";
			$this->m_securityMap["document"] = "view";
			$this->m_securityMap["normalisation"] = "view";
			$this->m_securityMap["vcard"] = "view";
			$this->m_securityMap["listeecran"] = "view";
			$this->m_securityMap["traitement"] = "delete";
			$this->m_securityMap["init_compta"] = "delete";
			$this->m_securityMap["liste_organismes"] = "view";
			$this->m_securityMap["affiche_record"] = "view";
			$this->m_securityMap["affiche_table_definition"] = "view";
			$this->m_securityMap["affiche_atk_record"] = "view";
			$this->m_securityMap["travaux"] = "view";
			$this->m_securityMap["tracer_mysqldb"] = "view";
			$this->m_securityMap["debugging"] = "view";
			$this->m_securityMap["geolocalisation_inscrits"] = "view";
//			$this->setIndex("nom");
			$this->setOrder("nom");
			$this->m_dropdown_width="100";
	}
	function descripteur_organisme_display($record, $mode)
	{
		$id_organisme=trim($record["id"]);

		return $this->descripteur_organisme($id_organisme,"n","o");
	}
	function nom_display($record, $mode)
	{
		$attribute = $this->getAttribute("nom");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}
	function objectif_concis_display($record, $mode)
	{
		$attribute = $this->getAttribute("objectif_concis");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}
	function site_internet_display($record, $mode)
	{
		$attribute = $this->getAttribute("site_internet");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}

	function telephone_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone"] . ';">' . $record["telephone"] . '</a>';
	}


	function fonctions_display($record, $mode) {
		if (isset ($record["fonctions"])) {
			$ret= href(dispatch_url("organisme.v_organisme_fonction", "admin", array (
				'atkfilter' => "v_organisme_fonction.id_organisme='" . $record['id'] . "'"
				), "dispatch.php"), text($record["fonctions"]), SESSION_NESTED);
				if ($record["fonctions"]!=0)			return '<b>'.$ret.'</b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function inscriptions_display($record, $mode) {
		if (isset ($record["inscriptions"])) {
			$ret= href(dispatch_url("organisme.v_organisme_inscription", "admin", array (
				'atkfilter' => "v_organisme_inscription.id_organisme='" . $record['id'] . "'"
				), "dispatch.php"), text($record["inscriptions"]), SESSION_NESTED);
				if ($record["inscriptions"]!=0)			return '<b>'.$ret.'</b>';
				else return $ret;
		} else {
			return "";
		}
	}
function id_derniere_preparation_display($record, $mode) {
		if (!empty ($record["id_derniere_preparation"])) {
					$db = & atkGetDb();
//					$id=$record["id_derniere_preparation"]["id"];
					$id=$record["id_derniere_preparation"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}
	function id_derniere_preparation_fin_display($record, $mode) {
		if (!empty ($record["id_derniere_preparation_fin"])) {
			$db = & atkGetDb();
			//					$id=$record["id_derniere_preparation"]["id"];
			$id=$record["id_derniere_preparation_fin"];
			$sql="SELECT identifiant from app_utilisateur where id=$id";
			$data=$db->getrows($sql);
			return $data[0]["identifiant"];
				
		} else {
			return "";
		}
	}
function id_envoi_recu_fiscal_display($record, $mode) {
		if (!empty ($record["id_envoi_recu_fiscal"])) {
					$db = & atkGetDb();
//					$id=$record["id_envoi_recu_fiscal"]["id"];
					$id=$record["id_envoi_recu_fiscal"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}
function id_envoi_timbre_display($record, $mode) {
		if (!empty ($record["id_envoi_timbre"])) {
					$db = & atkGetDb();
//					$id=$record["id_envoi_timbre"]["id"];
					$id=$record["id_envoi_timbre"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}


function id_envoi_carte_display($record, $mode) {
		if (!empty ($record["id_envoi_carte"])) {
					$db = & atkGetDb();
//					$id=$record["id_envoi_carte"]["id"];
					$id=$record["id_envoi_carte"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}
function id_recu_abandon_creance_display($record, $mode) {
		if (!empty ($record["id_recu_abandon_creance"])) {
					$db = & atkGetDb();
//					$id=$record["id_recu_abandon_creance"]["id"];
					$id=$record["id_recu_abandon_creance"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}
	
function id_synchronisation_federation_display($record, $mode)
 {
		if (!empty ($record["id_synchronisation_federation"])) {
					$db = & atkGetDb();
//					$id=$record["id_synchronisation_federation"]["id"];
					$id=$record["id_synchronisation_federation"];
					$sql="SELECT identifiant from app_utilisateur where id=$id";
					$data=$db->getrows($sql);
					return $data[0]["identifiant"];
					
		} else {
			return "";
		}
	}
	
	function dispatch($postvars, $fullpage=true)
	{
		if ($postvars['atkaction']!='add' && $postvars['atkaction']!='delete' && $postvars['atkaction']!='admin')
		{        $atkselect = $postvars["atkselector"];
		if (count($atkselect)==1)
		{
			$organismeid = sscanf($atkselect, "organisme.id='%d'");
			$organismeId = $organismeid[0];
			$this->RecentUseProcess('organisme', $organismeId);
		} else
		{ $organismeId = 0;}
		}
		else
		{
			$this->RecentUseRefresh('organisme');
		}

		return parent::dispatch($postvars, $fullpage);
	}

	function initial_values() {
		$init_vals = array ();
		$init_vals["prochain_id_ecriture"] = 0;
		$init_vals["prochain_id_recu_fiscal"] = 0;
		$init_vals["prochain_id_inscription"] = 0;
		$init_vals["prochain_id_remise_en_banque"] = 0;
		$init_vals["acces_public_o_n"] = 1;
		return $init_vals;
	}
	function rowColor($record) {
		if ($record["acces_public_o_n"]== "0")
		return $this->couleurorganismeaccesprive;
	}

	function adminHeader()
	{
		$retour=parent::adminHeader();
		if (isset($this->m_postvars['atkfilter']))
		{return $retour.'</b>Attention filtre actif :  '.$this->m_postvars['atkfilter'].'<b><br />';	}
		return $retour;
	}

	function modifyDataGrid($grid,$mode)
	{

		if ($mode==2)
		{

			$grid->setPostvar("atkfilter",'');
			$this->m_postvars['atkfilter']='';
			// $this->p($grid->getPostvars());
		}

		return true;
	}

	function adminFooter() {
		$retour=parent::adminfooter();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurorganismeaccesprive . '"> <b> Accès privé ';
		return $legende . $retour;
	}

	function compta_init_edit($record, $mode) {
		if (!isset ($record["date_initialisation_comptabilite"]["year"])) {
			$url = href(dispatch_url("organisme.organisme", "init_compta", array (
				"atkselector" => "organisme.id='" . $record["id"] . "'",
				"id" => $record["id"]
			)), atktext("<b>Cliquer ici pour initialiser la comptabilité </b><br><br>", "core"), SESSION_NEW, false, 'target="main"');
			return "<font color=\"Red\"><b>La comptabilité n'a pas été initialisée</b><br>" . $url;
		} else {
			return "La comptabilité a été initialisée le " . $record["date_initialisation_comptabilite"]["year"] . "-" . $record["date_initialisation_comptabilite"]["month"] . "-" . $record["date_initialisation_comptabilite"]["day"];
		}
	}
	function site_montant_indemnite_kilometre_edit($record, $mode) {
		$url = href("http://www11.minefi.gouv.fr/boi/boi2008/5fppub/textes/5f208/5f208.pdf", atktext("Voir site du ministère des finances.", "core"), SESSION_NEW, false, 'target="_blank"');
		return $url;
	}
	function site_montant_indemnite_heure_benevolat_edit($record, $mode) {
		$url = href("http://www.travail-solidarite.gouv.fr/spip.php?page=article&id_article=1027", atktext("Voir site du ministère du travail.", "core"), SESSION_NEW, false, 'target="_blank"');
		return $url;
	}
	function trim_1_edit($record, $mode) {
		$url = href(dispatch_url("traitement.trimestriel", "intro", array (
			"atkselector" => "organisme.id='" . $record["id"] . "'",
			"id" => $record["id"]
		)), atktext("Préparation <br><br>", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_2_edit($record, $mode) {
		$url = href(dispatch_url("organisme.v_organisme_inscription_controle", "edit", array (
			"atkselector" => "v_organisme_inscription_controle.id_organisme='" . $record["id"] . "'",
			"atkfilter" => "v_organisme_inscription_controle.id_organisme='" . $record["id"] . "'",
			"id" => $record["id"],
			
		)), atktext("Vérification globale", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_3_edit($record, $mode) {
		$url = href(dispatch_url("individu.v_individu_correspondance", "admin", array (
			"atkfilter" => "v_individu_correspondance.id_organisme='" . $record["id"] . "'",
			"id" => $record["id"],
			
		)), atktext("Vérification des compléments au courrier<br><br>", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_4_edit($record, $mode) {
		$url = href(dispatch_url("individu.v_individu_lieu", "document", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1'  
																					and v_individu_lieu.id in 
																					(select distinct ii.id_individu
																					 from individu_inscription ii 
																					 where  ii.imprimer_adresse_o_n=1 
																					and ii.id_organisme='" . $record["id"] . "')",
			"atkdoctpl" => "enveloppe_individus_organisme.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $record["id"],
			
		)), atktext("Impression des enveloppes", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_5_edit($record, $mode) {
		$url = href(dispatch_url("organisme.v_individu_recu_fiscal", "document", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"atkfilter" => "v_individu_recu_fiscal.id_organisme='" . $record["id"] . "'",
			"atkdoctpl" => "recu_fiscal.odt",
			"atkdoctpl_prefix_id" => "1",
			"atkcode" => "1",
			"id" => $record["id"],
			
		)), atktext("Impression des reçus fiscaux", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_6_edit($record, $mode) {
		$url = href(dispatch_url("individu.v_individu_correspondance", "document", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"atkfilter" => "v_individu_correspondance.id_organisme='" . $record["id"] . "'",
			"atkdoctpl" => "complement_gazette.odt",
			"atkdoctpl_prefix_id" => "1",
			"id" => $record["id"],
			
		)), atktext("Impression des notifications individuelles", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_7_edit($record, $mode) {
		$url = href(dispatch_url("traitement.trimestriel", "recu_maj", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"id" => $record["id"],
			
		)), atktext("Mise à jour de la date d'envoi des reçus fiscaux", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_8_edit($record, $mode) {
		$url = href(dispatch_url("traitement.trimestriel", "timbre_maj", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"id" => $record["id"],
			
		)), atktext("Mise à jour de la date d'envoi des timbres de cotisation", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function trim_9_edit($record, $mode) {
		$url = href(dispatch_url("traitement.trimestriel", "carte_maj", array (
			"atkselector" => "organisme_id='" . $record["id"] . "'",
			"id" => $record["id"],
			
		)), atktext("Mise à jour de la date d'envoi des cartes d'adhésion<br><br>", "core"), SESSION_NEW, false, 'target="main"');
		return $url;
	}
	function case_8($id_organisme)
	{
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu_inscription");
		$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
		$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
		$query->addJoin("type_titre", "", "individu.id_titre= type_titre.id", false);
		$query->addJoin("individu_lieu", "", "individu_inscription.id_individu = individu_lieu.id_individu", true);
		$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
		$query->addField("organisme.nom as organisme");
		$query->addField("individu.id as id");
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("DATE_FORMAT(individu.date_naissance, '%d/%m/%Y') as naissance");
		$query->addField("DATE_FORMAT(individu_inscription.date_adhesion, '%d/%m/%Y') as adhesion");
		$query->addField("individu.telephone_fixe as telephone");
		$query->addField("type_inscription.libelle as type_inscription");
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_titre.titre_long as titre");
		$query->addCondition("individu_inscription.id_organisme = " . $id_organisme);
		$query->addCondition("individu_inscription.date_radiation is null ");
		$query->addCondition("individu.date_deces is null");
		$query->addCondition("individu_inscription.reporter_inscription_federation_o_n ='1'");
		$query->addCondition("individu_lieu.adresse_personnelle_o_n ='1'");
		$query->addOrderBy("type_inscription.libelle,individu.nom, individu.prenom");
		$stuff = $db->getrows($query->buildSelect());

		$data = array ();
		$db1 = & atkGetDb();
		$row1 = & $db1->getrows("select DATE_FORMAT(date_synchronisation_federation, '%d/%m/%Y') as date_fede from organisme where id=" . $id_organisme);
		$title= "<b>Adhésions enregistrées entre le " . $row1[0]["date_fede"] . " et le " . gmdate('d/m/Y') . "</b><br />";
		$row1 = array ();
		$row1[] = "#";
		$row1[] = "Organisme";
		$row1[] = "Type-adhésion";
		$row1[] = "Titre";
		$row1[] = "Nom";
		$row1[] = "Prénom";
		$row1[] = "Téléphone";
		$row1[] = "Type-stomie";
		$row1[] = "Né(e) le";
		$row1[] = "Adhésion";
		$row1[] = "Rue";
		$row1[] = "Code-postal";
		$row1[] = "Ville</b>";
		$data[] = $row1;

		// ....
		// Create data
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
			$db1 = & atkGetDb();
			$query1 = & $db1->createQuery();
			$query1->addTable("individu_attribut");
			$query1->addJoin("type_attribut", "", "individu_attribut.id_attribut = type_attribut.id", false);
			$query1->addCondition("individu_attribut.id_individu =" . $stuff[$i]["id"]);
			$query1->addCondition("type_attribut.libelle like '%stom%'");
			$query1->addField("distinct type_attribut.libelle as type");
			$sql1 = $query1->buildSelect();
			//					echo $sql1;
			$stuff1 = $db1->getrows($sql1);
			$c1 = '';
			for ($j = 0, $_j = count($stuff1); $j < $_j; $j++) {
				$c1 .= $stuff1[$j]["type"] . ' ';
			}
			$row = array ();
			$row[] = $i +1;
			$row[] = $stuff[$i]["organisme"];
			$row[] = $stuff[$i]["type_inscription"];
			$row[] = $stuff[$i]["titre"];
			$row[] = $stuff[$i]["nom"];
			$row[] = $stuff[$i]["prenom"];
			$row[] = $stuff[$i]["telephone"];
			$row[] = $c1;
			$row[] = $stuff[$i]["naissance"];
			$row[] = $stuff[$i]["adhesion"];
			$row[] = $stuff[$i]["adresse1"];
			$row[] = $stuff[$i]["code_postal"];
			$row[] = $stuff[$i]["ville"];
			$data[] = $row;

		}
		$tableau=array();
		$tableau[0]=$title;
		$tableau[1]=$data;
		return $tableau;
	}
	function case_9($id_organisme)
	{
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu_inscription");
		$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
		$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
		$query->addJoin("type_titre", "", "individu.id_titre= type_titre.id", false);
		$query->addJoin("individu_lieu", "", "individu_inscription.id_individu = individu_lieu.id_individu", true);
		$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addJoin("type_radiation", "", "individu_inscription.id_type_radiation = type_radiation.id", true);
		$query->addField("organisme.nom as organisme");
		$query->addField("individu.id as id");
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("individu.annee_naissance as naissance");
		$query->addField("individu.telephone_fixe as telephone_fixe");
		$query->addField("type_radiation.libelle as type_radiation");
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_titre.titre_long as titre");
		$query->addCondition("individu_inscription.id_organisme = " . $id_organisme);
		$query->addCondition("individu_inscription.reporter_radiation_federation_o_n ='1'");
		$query->addCondition("individu_lieu.adresse_personnelle_o_n ='1'");
		$query->addOrderBy(" individu.nom, individu.prenom");
		$stuff = $db->getrows($query->buildSelect());

		$data = array ();
		$db1 = & atkGetDb();
		$row1 = & $db1->getrows("select DATE_FORMAT(date_synchronisation_federation, '%d/%m/%Y') as date_fede from organisme where id=" . $id_organisme);
		$title="<b>Radiations enregistrées entre le " . $row1[0]["date_fede"] . " et le " . gmdate('d/m/Y') . "</b><br />";
		$row1 = array ();
		$row1[] = "#";
		$row1[] = "Organisme";
		$row1[] = "Type-radiation";
		$row1[] = "Titre";
		$row1[] = "Nom";
		$row1[] = "Prénom";
		$row1[] = "Naissance";
		//				$row1[]="Téléphone";
		$row1[] = "Rue";
		$row1[] = "Code-postal";
		$row1[] = "Ville</b>";
		$data[] = $row1;
		// Create data
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
			$row = array ();
			$row[] = $i +1;
			$row[] = $stuff[$i]["organisme"];
			$row[] = $stuff[$i]["type_radiation"];
			$row[] = $stuff[$i]["titre"];
			$row[] = $stuff[$i]["nom"];
			$row[] = $stuff[$i]["prenom"];
			$row[] = $stuff[$i]["naissance"];
			//					$row[] = $stuff[$i]["telephone_fixe"];
			$row[] = $stuff[$i]["adresse1"];
			$row[] = $stuff[$i]["code_postal"];
			$row[] = $stuff[$i]["ville"];
			$data[] = $row;
		}
		$tableau=array();
		$tableau[0]=$title;
		$tableau[1]=$data;
		return $tableau;
	}
	function case_10($id_organisme)
	{
		$db1 = & atkGetDb();
		$row1 = & $db1->getrows("select id_organisme_federation as id_federation ,DATE_FORMAT(date_synchronisation_federation, '%d/%m/%Y') as date_fede from organisme where id=" . $id_organisme);
		$id_fede = $row1[0]["id_federation"];
		$date_fede = $row1[0]["date_fede"];
		$row1 = & $db1->getrows("select nom as nom_fede from organisme where id=" . $id_fede);
		$nom_fede = $row1[0]["nom_fede"];
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu_inscription");
		$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
		$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
		$query->addJoin("type_titre", "", "individu.id_titre= type_titre.id", false);
		$query->addJoin("individu_cotisation", "", "individu_inscription.id_individu = individu_cotisation.id_individu", false);
		$query->addJoin("organisme_cotisation", "", "individu_cotisation.id_cotisation = organisme_cotisation.id", false);
		$query->addField("organisme.nom as organisme");
		$query->addField("organisme_cotisation.annee as annee");
		$query->addField("organisme_cotisation.montant as montant");
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("type_titre.titre_long as titre");
		$query->addCondition("individu_inscription.id_organisme = " . $id_organisme);
		$query->addCondition("individu_inscription.regler_cotisation_federation_o_n ='1'");
		$query->addCondition("individu_cotisation.date_reglement is null");
		$query->addCondition("organisme_cotisation.id_organisme=" . $id_fede);
		$query->addOrderBy(" organisme_cotisation.annee, individu.nom, individu.prenom ");
		$sql = $query->buildSelect();
		$stuff = $db->getrows($sql);

		$data = array ();
		$title="<b>Cotisations versées à la fédération entre le " . $date_fede . " et le " . gmdate('d/m/Y') . "</b><br />";
		$row1 = array ();
		$row1[] = "#";
		$row1[] = "Organisme";
		$row1[] = "Fédération";
		$row1[] = "Titre";
		$row1[] = "Nom";
		$row1[] = "Prénom";
		$row1[] = "Année";
		$row1[] = "Montant";
		$data[] = $row1;

		// Create data
		$total = 0;
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
			$row = array ();
			$row[] = $i +1;
			$row[] = $stuff[$i]["organisme"];
			$row[] = $nom_fede;
			$row[] = $stuff[$i]["titre"];
			$row[] = $stuff[$i]["nom"];
			$row[] = $stuff[$i]["prenom"];
			$row[] = $stuff[$i]["annee"];
			$row[] = $stuff[$i]["montant"];
			$total += $stuff[$i]["montant"];
			$data[] = $row;
		}
		$tableau=array();
		$tableau[0]=$title;
		$tableau[1]=$data;
		return $tableau;
	}
	function action_traitement() {
		switch ($this->m_postvars["atkcode"]) {
			case 80 :
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setRowClass(1, "superbold");
				$id_organisme=$this->m_postvars["id"];
				$data=$this->case_8($id_organisme);
				$res=$data[0].$tbl->render($data[1],0, "recordlist");
				$data=$this->case_9($id_organisme);
				$res.=$data[0].$tbl->render($data[1],0, "recordlist");
				$data=$this->case_10($id_organisme);
				$res.=$data[0].$tbl->render($data[1],0, "recordlist");
				
				

				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('Synchronisation fédération'), true));


				break;

			case 8 :
				// render table.
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setRowClass(1, "superbold");
				$data=$this->case_8($this->m_postvars["id"]);
				$res=$data[0].$tbl->render($data[1],0, "recordlist");
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscriptions_federation.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 9 :

				// render table.
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setRowClass(1, "superbold");
				$data=$this->case_9($this->m_postvars["id"]);
				$res=$data[0].$tbl->render($data[1],0, "recordlist");
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_radiations_federation.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 10 :

				// render table.
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setRowClass(1, "superbold");
				$data=$this->case_10($this->m_postvars["id"]);
				$res=$data[0].$tbl->render($data[1],0, "recordlist");
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$page->addContent("<b>Total des cotisations : " . $total . " Euro.</b>");
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_cotisations_federation.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 11 :
				
				
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setRowClass(1, "superbold");
				$id_organisme=$this->m_postvars["id"];
				$data=$this->case_8($id_organisme);
				$res=$data[0].$tbl->render($data[1],0, "recordlist");
				$data=$this->case_9($id_organisme);
				$res.=$data[0].$tbl->render($data[1],0, "recordlist");
				$data=$this->case_10($id_organisme);
				$res.=$data[0].$tbl->render($data[1],0, "recordlist");
				$filename=$this->getUserFileName('synchronisation_federation','html',$filenameshort,null);
				$file=fopen($filename, "w");
				fwrite($file, $res);
				fclose($file);
				$size=filesize($filename);
				$file = @ fopen($filename, "rb");
				$filecontent = @ fread($file, $size);
				@ fclose($file);
				$filecontent = base64_encode($filecontent);
				$fileextension = strtolower(substr($filename, strrpos($filename, '.') + 1, strlen($filename)));
				$user = getUser();
				$userid = $user["id"];
				$db = & atkGetDb();
				
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				$page->addContent($res);
				$res=$page->render(atktext('app_title') . ' - ' . atktext('Synchronisation fédération'), true);
				
				$id_record=$db->nextid('seq_organisme_document');
				$db->query("INSERT into organisme_document
		(id,
						 id_organisme,
						 libelle,
						 id_type_document ,
						 file_name,
						 file_extension,
						 file_size,
						 file_content,
						 id_creation,
						 id_modification,
						 date_creation,
						 date_modification)
						  VALUES ( $id_record,
							'$id_organisme',
						 '$filenameshort', 
						 '42' ,
						 '$filenameshort',
						 '$fileextension',
						 '$size',
						'$filecontent',
						'$userid',
						'$userid'
						,UTC_TIMESTAMP(),
						 UTC_TIMESTAMP())");
			
				$db1 = & atkGetDb();
				$row1 = & $db1->getrows("select id_organisme_federation as id_federation,   	id_contact_federation as   	id_contact_federation ,DATE_FORMAT(date_synchronisation_federation, '%d/%m/%Y') as date_fede from organisme where id=" . $this->m_postvars["id"]);
				$id_fede = $row1[0]["id_federation"];
				$id_contact_federation = $row1[0]["id_contact_federation"];
				$date_fede = $row1[0]["date_fede"];
				$row1 = & $db1->getrows("select nom as nom_fede from organisme where id=" . $id_fede);
				$nom_fede = $row1[0]["nom_fede"];
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_inscription");
				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("type_titre", "", "individu.id_titre= type_titre.id", false);
				$query->addJoin("individu_cotisation", "", "individu_inscription.id_individu = individu_cotisation.id_individu", false);
				$query->addJoin("organisme_cotisation", "", "individu_cotisation.id_cotisation = organisme_cotisation.id", false);
				$query->addField("organisme.nom as organisme");
				$query->addField("organisme_cotisation.annee as annee");
				$query->addField("organisme_cotisation.montant as montant");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu_cotisation.id as id_ind_cot");
				$query->addField("type_titre.titre_long as titre");
				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("individu_inscription.regler_cotisation_federation_o_n ='1'");
				$query->addCondition("individu_cotisation.date_reglement is null");
				$query->addCondition("organisme_cotisation.id_organisme=" . $id_fede);
				$query->addOrderBy(" organisme_cotisation.annee, individu.nom, individu.prenom ");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				//				echo $sql;
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				echo "</BR><b>Cotisations versées à la fédération entre le " . $date_fede . " et le " . gmdate('d/m/Y') . ".</BR>";
				$row1 = array ();
				$row1[] = "#";
				$row1[] = "Organisme";
				$row1[] = "Fédération";
				$row1[] = "id_ind_cot";
				$row1[] = "Titre";
				$row1[] = "Nom";
				$row1[] = "Prénom";
				$row1[] = "Année";
				$row1[] = "Montant";
				$data[] = $row1;
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$total = 0;
				global $g_user;
				$userutilisateur = $g_user["id"];
				if (count($stuff) > 0) {
					for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
						$row = array ();
						$row[] = $i +1;
						$row[] = $stuff[$i]["organisme"];
						$row[] = $nom_fede;
						$row[] = $stuff[$i]["id_ind_cot"];
						$row[] = $stuff[$i]["titre"];
						$row[] = $stuff[$i]["nom"];
						$row[] = $stuff[$i]["prenom"];
						$row[] = $stuff[$i]["annee"];
						$row[] = $stuff[$i]["montant"];
						$total += $stuff[$i]["montant"];
						$data[] = $row;
						$sql = "UPDATE individu_cotisation
					  set date_reglement='" . gmdate(c) . "', id_banque='7' , id_reglement='1', montant_versement='" . $stuff[$i]['montant'] . "'
				 , id_modification='" . $userutilisateur . "', date_modification='" . gmdate(c) . "'
				 where id='" . $stuff[$i]['id_ind_cot'] . "'";
						$r = $db->query($sql);
					}
					$r = $db->query("UPDATE organisme
					 set id_synchronisation_federation= " . $userutilisateur. " , date_synchronisation_federation=UTC_TIMESTAMP(), id_modification=" . $userutilisateur . ", date_modification=UTC_TIMESTAMP()
					 where id=" . $this->m_postvars["id"] . "");
					// render table.
					$res = $tbl->render($data, 0, "recordlist");
					// h// h
					$page = & atknew("atk.ui.atkpage");
					$ui = & atkinstance("atk.ui.atkui");
					$output = & atkOutput :: getInstance();
					$page->register_style($ui->stylePath("style.css"));
					//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
					$page->addContent($res);
					$page->addContent("<b>Total des cotisations : " . $total . " Euro.</b></BR>");
					$page->addContent("La liste a été stockée dans un document de l'organisme : " .$filenameshort."<br />");
					$page->addContent(href(dispatch_url("organisme.fourniture", "admin", array (
						"atkfilter" => "organisme_fourniture.id_organisme='" . $this->m_postvars["id"] . "'"
						)), atktext("Créer un règlement, faire le chèque et noter son numéro", "core"), SESSION_NEW, false, 'target="main"') . '&nbsp; ');
					
					$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
					
						
				} else {
					echo "Pas de cotisation à règler à la fédération";
					die();
				}
				break;
			case 100 :
				{
					// créer cotisation fédération seule
					global $g_user;
					$userutilisateur = $g_user["id"];
					$id_organisme = $this->m_postvars["id"];
					$annee_cotisation_organisme = gmdate('Y');
					// Recherche des inscriptions pour lesquelles il faut payer une cotisation à la fédération
					$db = & atkGetDb();
					$id_inscriptions = $db->getrows("SELECT ii.id,ii.id_individu, i.nom, i.prenom
					from individu_inscription ii, individu i where ii.creer_cotisation_federation_o_n='1'
					and ii.id_organisme=$id_organisme
					and ii.date_radiation is null and ii.id_individu=i.id");
					// rechercher le montant de la cotisation fédération pour la même année
					if (count($id_inscriptions) > 0) {
						$rang = $db->getrows("SELECT

						o.id_compte_cotisation_federation_an as id_compte_cotisation_federation_an,

						o.id_compte_federation as id_compte_federation,

						o.id_journal_cotisations_federation as id_journal_cotisations_federation
							
						FROM organisme o
						where o.id=$id_organisme  ");
						$id_journal_cotisations_federation = $rang[0]["id_journal_cotisations_federation"];
						$id_compte_federation = $rang[0]["id_compte_federation"];
						$id_compte_cotisation_federation = $rang[0]["id_compte_cotisation_federation_an"];
						$data = $db->getrows("SELECT o.id_organisme_federation, oc.montant, oc.id
						from organisme o, organisme_cotisation oc
						where o.id=$id_organisme and o.id_organisme_federation=oc.id_organisme
						and oc.annee=$annee_cotisation_organisme ");
						$montant_cotisation_federation = $data[0]["montant"];
						$id_cotisation_federation = $data[0]["id"];
						$id_organisme_federation = $data[0]["id_organisme_federation"];

						if (!isset ($montant_cotisation_federation)) {
							atkhalt("La cotisation fédération n'a pas été créée", "critical");
						}
						for ($i = 0, $_i = count($id_inscriptions); $i < $_i; $i++) {
							$id_individu = $id_inscriptions[$i]["id_individu"];
							$id_inscription = $id_inscriptions[$i]["id"];
							// L'inscription à fédération doit exister et vérifier si pas déjà cotistaion existante
							$data = $db->getrows("SELECT ii.id from individu_inscription ii" . "
							where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme_federation ");
							if (count($data) == 0) {
								atkhalt("erreur_:_non_inscrit_federation", "critical");
							}
							$data = $db->getrows("SELECT ic.id from individu_cotisation ic" . " where ic.id_individu=$id_individu and ic.id_cotisation=$id_cotisation_federation ");
							if (count($data) == 0) {
								// Créer la cotisation à la fédération
							}
							$data = $db->query("INSERT into individu_cotisation" . " (id_organisme, id_individu, id_cotisation, montant_versement, montant_cotisation_organisme,id_creation, id_modification, date_creation, date_modification)" . "VALUES ( $id_organisme_federation, $id_individu,$id_cotisation_federation,$montant_cotisation_federation,$montant_cotisation_federation,$userutilisateur,$userutilisateur,UTC_DATE(),UTC_DATE())");
							$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_cotisation' ");
							$sql = "SELECT id as id from individu_cotisation where id_individu=$id_individu and  id_cotisation=$id_cotisation_federation ";
							$data = $db->getrows($sql);
							$id_cotisation_federation_id = $data[0]["id"];

							//Céer l'écriture comptable
							$libelle = 'Cotisation fédération ' . gmdate('Y') . ' ' . $id_inscriptions[$i]["nom"] . ' ' . $id_inscriptions[$i]["prenom"];
							$date_reglement = gmdate('c');
							$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_cotisations_federation, $libelle, $date_reglement);
							$id_ecriture_cotisation_federation = $id_ecriture;
							$debit = 0;
							$credit = $montant_cotisation_federation;
							$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_federation, $id_compte_federation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
							$credit = 0;
							$debit = $montant_cotisation_federation;
							$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_federation, $id_compte_cotisation_federation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
							$data = $db->query("Update individu_cotisation set id_ecriture_cotisation_federation=$id_ecriture_cotisation_federation
							where id=$id_cotisation_federation_id");
							$data = $db->query("Update individu_inscription set creer_cotisation_federation_o_n='1'
							where id=$id_inscription");
						}
					}
				}

				break;
		}
	}
	function action_liste_organismes ()
	{
		if ($this->m_postvars["atkcode"] == "liste_organismes")
		{
			$idorganismes=	$this->m_postvars["idorganismes"];
		}
		else
		{
			if (is_array($this->m_postvars["atkselector"])) {
				$select = $this->m_postvars["atkselector"];
			} else {
				$select[0] = $this->m_postvars["atkselector"];
			}
			foreach ($select as $id_variable) {
				$array_id = explode('=', $id_variable);
				$chaineid .= $array_id[1] . ',';
			}
			$idorganismes= substr($chaineid, 0, strlen($chaineid) - 1);
			$idorganismes = str_replace("'", "", $idorganismes);
		}
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("organisme");
		$query->addField("organisme.id as id");
		$query->addField("organisme.nom as nom");
		$query->addField("organisme.sigle as sigle");
		$query->addField("organisme.objectif_concis as objectif_concis");
		$query->addField("organisme.site_internet as site_internet");//objectif_concis
		$query->addCondition("organisme.id in ( " . $idorganismes . ")");
		$query->addOrderBy("organisme.nom");
		$sql = $query->buildSelect();
		$stuff = $db->getrows($sql);
		$tbl = & atknew("atk.utils.atktablerenderer");
		$data = array ();
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_organisme";

		$nombreavant=$db->getrows("select count(id) as nombre from  tmp_copier_coller where id_utilisateur=$userid  and nom_variable='".$nom_variable."'");
		$tbl->setRowClass(1, "superbold");
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
			$row = array ();
			$db->query("INSERT INTO tmp_copier_coller (id_utilisateur, nom_variable, id_variable, date_creation)
					 VALUES( '$userid', '$nom_variable'," . $stuff[$i]["id"] . ", UTC_TIMESTAMP())
					 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP() ");

			if ($i==0)
			{
				$row[] = '<td>#</td><td>Organisme</td><td>Sigle</td><td>Mission</td><td>Site internet</td>';
				$data[] = $row;
				$row = array ();
			}


			if ($stuff[$i]["site_internet"]=="")
			{
				$row[] = '<td>'.($i+1).'</td><td width=200px ><a href="http://www.google.fr/search?q=' . $stuff[$i]["nom"] . '">'.$stuff[$i]["nom"] .'</a></td><td width=100px >' . $stuff[$i]["sigle"] .
					 '</td><td width=200px >' . $stuff[$i]["objectif_concis"] .'</td><td></td>';}
				else
				{
					{$row[] = '<td>'.($i+1).'</td><td width=200px ><a href="http://www.google.fr/search?q=' . $stuff[$i]["nom"] . '">'.$stuff[$i]["nom"] .'</a></td><td width=100px >' . $stuff[$i]["sigle"] .
					 '</td><td width=200px >' . $stuff[$i]["objectif_concis"] .'</td><td><a href="' . $stuff[$i]["site_internet"] . '">Site internet</a></td>';}
				}
				$data[] = $row;
		}
		$nombreapres=$db->getrows("select count(id) as nombre from  tmp_copier_coller where id_utilisateur=$userid  and nom_variable='".$nom_variable."'");
		$row = array ();
		$row[] =  '<td colspan=4>Les '.$i.' organismes ont été ajoutés ( ou mis à jour) dans votre presse-papier. (Avant : '.$nombreavant[0]["nombre"].' . Après : '.$nombreapres[0]["nombre"].').</td>';
		$data[] = $row;
		$row = array ();
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$row[] = "<td colspan=4>Cette liste valable au " . gmdate(c) . " et sortie par " . $g_nomutilisateur . " est strictement confidentielle.</td>";


		$data[] = $row;
		// render table.
		$res = $tbl->render($data, 0, "recordlist");
		// h// h
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		if ($this->m_postvars["atkexport"] == 'o') {
			$filename = $this->m_postvars["id"] . "_liste_organismes_nom_sigle_site_internet.html";
			Header("Content-Disposition: attachment; filename=$filename");
			Header("Content-Length: " . strlen($output));
			Header("Connection: close");
			Header("Content-Type: text/html; name=$filename");
		}
	}
	function action_listeecran() {
		switch ($this->m_postvars["atkcode"]) {
							
				
			case 1 : // inscriptions
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_inscription");
				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("organisme", "organisme_inscrit", "individu_inscription.id_organisme_inscrit = organisme_inscrit.id", true);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("individu_attribut", "", "individu.id = individu_attribut.id_individu", true);
				$query->addJoin("type_attribut", "", "type_attribut.id = individu_attribut.id_attribut", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);

				//			$query->addJoin("individu_cotisation", "", "individu_inscription.id_individu = individu_cotisation.id_individu and individu_inscription.id_organisme = individu_cotisation.id_organisme", true);
				//			$query->addJoin("organisme_cotisation", "", "individu_cotisation.id_cotisation = organisme_cotisation.id ", true);

				$query->addField("organisme.nom as organisme");
				$query->addField("organisme.id as id_organisme");
				$query->addField("organisme_inscrit.nom as nom_organisme_inscrit");
				$query->addField("organisme_inscrit.sigle as sigle_organisme_inscrit");
				$query->addField("organisme_inscrit.site_internet as site_internet");
				$query->addField("organisme_inscrit.objectif_concis as objectif_concis_organisme_inscrit");
				$query->addField("organisme_inscrit.courriel as courriel_organisme_inscrit");
				$query->addField("organisme_inscrit.telephone as telephone_inscrit");
				$query->addField("individu_inscription.id as id_inscription");
				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.id as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("individu_inscription.date_inscription as date_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addField("individu.annee_naissance as annee_naissance ");
				$query->addField("individu_attribut.date_debut as date_debut_attribut");
				$query->addField("type_attribut.libelle as libelle_attribut");


				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu_inscription.id_type_inscription in ( " . $this->m_postvars["idinscriptions"] . ")");
				//				$query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				// 		$query->addCondition(" individu.id not in (select id_individu from individu_lieu) ");


				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				global $g_sessionManager;
				global $g_nomutilisateur;
				$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$row = array ();
				$row[] = "Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle";
				$data[] = $row;
				$row[] = "organisme";
				$row[] = "nom_organisme_inscrit";

				$row[] = "sigle_organisme_inscrit";
				$row[] = "objectif_concis_organisme_inscrit";
				$row[] = "site_internet";
				$row[] = "telephone_inscrit";
				$row[] = "courriel_organisme_inscrit";
				$row[] = "type_inscription";
				$row[] = "date_inscription";
				$row[] = "an_cotisation";
				$row[] = "nom";
				$row[] = "prenom";
				$row[] = "annee_naissance";
				$row[] = "libelle_attribut";
				$row[] = "date_debut_attribut";
				$row[] = "courriel";
				$row[] = "telephone_fixe";
				$row[] = "telephone_mobile";
				$row[] = "adresse1";
				$row[] = "code_postal";
				$row[] = "ville";
				$row[] = "province";
				$row[] = "pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$sql="Select max(annee) as an_cotisation from organisme_cotisation oc
					where oc.id_organisme =". $stuff[$i]['id_organisme']."
					and oc.id in ( select id_cotisation from individu_cotisation
					where id_individu=".$stuff[$i]['id_individu'].")
					";
					$cotisation = $db->getrows($sql);

					$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom_organisme_inscrit"];

					$row[] = $stuff[$i]["sigle_organisme_inscrit"];
					$row[] = $stuff[$i]["objectif_concis_organisme_inscrit"];
					$row[] = $stuff[$i]["site_internet"];
					$row[] = $stuff[$i]["telephone_inscrit"];
					$row[] = $stuff[$i]["courriel_organisme_inscrit"];
					$row[] = $stuff[$i]["type_inscription"];
					$row[] = $stuff[$i]["date_inscription"];
					$row[] = $cotisation[0]["an_cotisation"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["annee_naissance"];
					$row[] = $stuff[$i]["libelle_attribut"];
					$row[] = $stuff[$i]["date_debut_attribut"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "recordlist");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				/*				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel_et_sans_adresse_postale.html";
					Header("Content-Disposition: attachment; filename=$filename");
					//					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
					}
					break;
					*/
				break;
			case 30 : // inscriptions
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_inscription");
				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("organisme", "organisme_inscrit", "individu_inscription.id_organisme_inscrit = organisme_inscrit.id", true);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				//				$query->addJoin("individu_attribut", "", "individu.id = individu_attribut.id_individu", true);
				//				$query->addJoin("type_attribut", "", "type_attribut.id = individu_attribut.id_attribut", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);

				//			$query->addJoin("individu_cotisation", "", "individu_inscription.id_individu = individu_cotisation.id_individu and individu_inscription.id_organisme = individu_cotisation.id_organisme", true);
				//			$query->addJoin("organisme_cotisation", "", "individu_cotisation.id_cotisation = organisme_cotisation.id ", true);

				$query->addField("organisme.nom as organisme");
				$query->addField("organisme.id as id_organisme");
				/*				$query->addField("organisme_inscrit.nom as nom_organisme_inscrit");
				 $query->addField("organisme_inscrit.sigle as sigle_organisme_inscrit");
				 $query->addField("organisme_inscrit.site_internet as site_internet");
				 $query->addField("organisme_inscrit.objectif_concis as objectif_concis_organisme_inscrit");
				 $query->addField("organisme_inscrit.courriel as courriel_organisme_inscrit");
				 $query->addField("organisme_inscrit.telephone as telephone_inscrit");
				 */
				$query->addField("individu_inscription.id as id_inscription");
				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.id as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("individu_inscription.date_inscription as date_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addField("individu.annee_naissance as annee_naissance ");
				//				$query->addField("individu_attribut.date_debut as date_debut_attribut");
				//				$query->addField("type_attribut.libelle as libelle_attribut");


				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
			
				$query->addCondition("adresse_defaut_o_n ='1' ");
				$query->addCondition("individu_inscription.id_type_inscription in ( " . $this->m_postvars["idinscriptions"] . ")");
				//				$query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				// 		$query->addCondition(" individu.id not in (select id_individu from individu_lieu) ");


				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				global $g_sessionManager;
				global $g_nomutilisateur;
				$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data

				$row = array ();
				$row[] ="<b>#";
				$row[] = "<b>Organisme";
				/*			$row[] = "nom_organisme_inscrit";

				$row[] = "sigle_organisme_inscrit";
				$row[] = "objectif_concis_organisme_inscrit";
				$row[] = "site_internet";
				$row[] = "telephone_inscrit";
				$row[] = "courriel_organisme_inscrit";
				*/
				$row[] = "<b>Type inscription";
				$row[] = "<b>Date inscription";
				$row[] = "<b>Cotisation";
				$row[] = "<b>Nom";
				$row[] = "<b>Prénom";
				//				$row[] = "annee_naissance";
				//				$row[] = "libelle_attribut";
				//				$row[] = "date_debut_attribut";
				$row[] = "<b>Courriel";
				$row[] = "<b>Téléphone";
				$row[] = "<b>Mobile";
				$row[] = "<b>Adresse";
				$row[] = "<b>CP";
				$row[] = "<b>Ville";
				//				$row[] = "<b>Province";
				//				$row[] = "<b>Pays</b>";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$f=$i+1;
					$row[] = "<b>".$f."</b>";
					$sql="Select max(annee) as an_cotisation from organisme_cotisation oc
					where oc.id_organisme =". $stuff[$i]['id_organisme']."
					and oc.id in ( select id_cotisation from individu_cotisation
					where id_individu=".$stuff[$i]['id_individu'].")
					";
					$cotisation = $db->getrows($sql);

					$row[] = $stuff[$i]["organisme"];
					/*					$row[] = $stuff[$i]["nom_organisme_inscrit"];
					 	
					$row[] = $stuff[$i]["sigle_organisme_inscrit"];
					$row[] = $stuff[$i]["objectif_concis_organisme_inscrit"];
					$row[] = $stuff[$i]["site_internet"];
					$row[] = $stuff[$i]["telephone_inscrit"];
					$row[] = $stuff[$i]["courriel_organisme_inscrit"];
					*/
					$row[] = $stuff[$i]["type_inscription"];
					$row[] = $stuff[$i]["date_inscription"];
					$row[] = $cotisation[0]["an_cotisation"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					//					$row[] = $stuff[$i]["annee_naissance"];
					//					$row[] = $stuff[$i]["libelle_attribut"];
					//					$row[] = $stuff[$i]["date_debut_attribut"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					//					$row[] = $stuff[$i]["province"];
					//					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res= "Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle<br /><br />";
				$res .= $tbl->render($data, 0, "recordlist");
				$res.= "<br / >Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle";
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				/*				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel_et_sans_adresse_postale.html";
					Header("Content-Disposition: attachment; filename=$filename");
					//					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
					}
					break;
					*/
				break;
				
				
			case  31 : // coordonnees
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("(individu_lieu.adresse_defaut_o_n='1' or individu_lieu.adresse_defaut_o_n is null ) ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$tbl->setRowClass(1, "superbold");
				$tbl->setTableStyle("toc sortable");
				$row = array ();
				$row[] = "#";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Courriel";
				$row[] = "Téléphone fixe";
				$row[] = "Téléphone mobile";
				$row[] = "Adresse(1)";
				$row[] = "Code Postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 2 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_fonction");
				$query->addJoin("individu", "", "individu_fonction.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_fonction.id_organisme = organisme.id", false);
				$query->addJoin("type_fonction", "", "individu_fonction.id_fonction = type_fonction.id", false);
				$query->addJoin("individu_lieu", "", "individu_fonction.id_individu = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addField("organisme.nom as organisme");

				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.date_naissance as date_naissance");
				$query->addField("individu.lieu_naissance as lieu_naissance");
				$query->addField("individu.nationalite as nationalite");
				$query->addField("individu.profession as profession");

				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("type_fonction.libelle as type_fonction");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("individu_fonction.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("individu_fonction.id_fonction in ( " . $this->m_postvars["idfonctions"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu_lieu.adresse_personnelle_o_n='1' ");
				$query->addCondition("individu_fonction.date_fin is null");
				$query->addOrderBy("type_fonction.libelle,individu.nom, individu.prenom");
				$stuff = $db->getrows($query->buildSelect());

				$query = & $db->createQuery();
				$query->addTable("organisme");
				$query->addJoin("organisme_lieu", "", "organisme_lieu.id_organisme=organisme.id", true);
				$query->addJoin("lieu", "", "organisme_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addField("organisme.nom as nom_organisme");
				$query->addField("organisme.numero_association as numero_association");
				$query->addField("organisme.date_declaration_association as date_declaration_association");
				$query->addField("organisme.date_publication_jo as date_publication_jo");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("lieu.adresse2 as adresse2");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("organisme.id=".$this->m_postvars["id"]."");
				$query->addCondition("organisme_lieu.adresse_siege_social_o_n='1' ");
				$stufforganisme = $db->getrows($query->buildSelect());

				$res="Monsieur le préfet
<br /><br />
Nous avons l'honneur, de vous faire connaître, 
conformément aux dispositions de l'article 5 de la loi du 1er juillet 1901 que, 
lors de son assemblée générale du ?????? ,
 l'association <br /><b>".$stufforganisme[0]["nom_organisme"]."</b><br /> déclarée en préfecture sous le numéro <b>".$stufforganisme[0]["numero_association"]."</b> et dont le siège est à <br /><b>"
 .$stufforganisme[0]["adresse1"];
 (!empty($stufforganisme[0]["adresse2"]))? $res.='<br /><b>'.$stufforganisme[0]["adresse2"].'</b>' : $res=$res;
 $res.="<br />".$stufforganisme[0]["code_postal"]
 ." ".$stufforganisme[0]["ville"]
 ."<br />".$stufforganisme[0]["pays"]
 ."</b><br /> a procédé au changement de ses dirigeants."
 ."<br /><br />Les personnes en charge de son administration sont :"
 ."<br /><br />";

 $tbl = & atknew("atk.utils.atktablerenderer");
 $data = array ();
 // Develop a table however you'd like it to display
 // Use cascading style sheets to alter the appearance.
 $tbl->setRowClass(1, "superbold");
 // ....
 // Create data
 $row = array ();
 //				$row[] = "";

 $row[] = "Fonction";
 $row[] ="Nom";
 $row[] = "Prénom";
 $row[] = "Né(e) le";
 $row[] = "à";
 $row[] = "Nationalité";
 $row[] = "Profession";
 $row[] = "Courriel";
 $row[] = "Tél fixe";
 $row[] = "Tél mobile";
 $row[] = "Rue";
 $row[] = "Code postal";
 $row[] = "Ville";
 //				$row[] = "Province";
 $row[] = "Pays";
 $data[] = $row;
 for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
 	$row = array ();
 	//					$row[] = $i +1;
 	//					$row[] = $stuff[$i]["organisme"];
 	$stuff[$i]["type_fonction"]=str_replace("Association - bureau - ","",$stuff[$i]["type_fonction"]);
 	$stuff[$i]["type_fonction"]=str_replace("Association - ","",$stuff[$i]["type_fonction"]);
 	$stuff[$i]["type_fonction"]=str_replace("- membre","",$stuff[$i]["type_fonction"]);
 	$stuff[$i]["type_fonction"]=ucfirst($stuff[$i]["type_fonction"]);


 	$row[] = $stuff[$i]["type_fonction"];
 		
 	$row[] = $stuff[$i]["nom"];
 	$row[] = $stuff[$i]["prenom"];
 	$row[] = $stuff[$i]["date_naissance"];
 	$row[] = $stuff[$i]["lieu_naissance"];
 	$row[] = $stuff[$i]["nationalite"];
 	$row[] = $stuff[$i]["profession"];
 	$row[] = $stuff[$i]["courriel"];
 	$row[] = $stuff[$i]["telephone_fixe"];
 	$row[] = $stuff[$i]["telephone_mobile"];
 	$row[] = $stuff[$i]["adresse1"];
 	$row[] = $stuff[$i]["code_postal"];
 	$row[] = $stuff[$i]["ville"];
 	//	$row[] = $stuff[$i]["province"];
 	$row[] = $stuff[$i]["pays"];
 	$data[] = $row;
 }
 // render table.

 $res .= $tbl->render($data, 0, "navpers");
 $res.="<br />Nous vous demandons de bien vouloir nous délivrer récépissé de la présente déclaration.
<br /><br />
Veuillez agréer, Monsieur le ?????? préfet (ou sous-préfet), l'assurance de notre considération distinguée.
<br /><br />
Fait à "
 .$stufforganisme[0]["ville"]." le ".gmdate('d/m/Y')
 ."<br /> <br />
Signatures (de deux membres du bureau) 
<br />
Le président, <br /><br />                                    Le secrétaire,";

 $page = & atknew("atk.ui.atkpage");
 $ui = & atkinstance("atk.ui.atkui");
 $output = & atkOutput :: getInstance();
 $page->register_style($ui->stylePath("style.css"));
 //				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
 $page->addContent($res);
 $outgg=$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
 if ($this->m_postvars["atkexport"] == 'o') {
 	$filename = $this->m_postvars["id"] . "_fonctions.html";
 	Header("Content-Disposition: attachment; filename=$filename");
 	Header("Content-Length: " . strlen($outgg));
 	Header("Connection: close");
 	Header("Content-Type: text/html; name=$filename");
 }
 break;
			case 3 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", false);
				$query->addJoin("type_titre", "", "individu.id_titre = type_titre.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addField("organisme.nom as organisme");
				$query->addField("type_titre.titre_long as titre");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("lieu.adresse2 as adresse2");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme =' " . $this->m_postvars["id"] . "'");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				//		$query->addCondition("individu_lieu.adresse_defaut_o_n='1'");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//		print_r ($sql);
				//		die();
				$stuff = $db->getrows($sql);
				$fdw = fopen("contacts", "w");
				$row = '"Titre","Prénom","Deuxième prénom","Nom","Suffixe","Société ","Service ","Titre","Rue (bureau)","Rue (bureau) 2","Rue (bureau) 3","Ville (bureau)","Dép/Région (bureau)","Code postal (bureau)","Pays (bureau)","Rue (domicile)","Rue (domicile) 2","Rue (domicile) 3","Ville (domicile)","Dép/Région (domicile)","Code postal (domicile)","Pays (domicile)","Rue (autre)","Rue (autre) 2","Rue (autre) 3","Ville (autre)","Dép/Région (autre)","Code postal (autre)","Pays (autre)","Téléphone de l\'assistant(e)","Télécopie (bureau)","Téléphone (bureau)","Téléphone 2 (bureau)","Rappel","Téléphone (voiture)","Téléphone société","Télécopie (domicile)","Téléphone (domicile)","Téléphone 2 (domicile)","RNIS","Tél. mobile","Télécopie (autre)","Téléphone (autre)","Récepteur de radiomessagerie","Téléphone principal","Radio téléphone","Téléphone TDD/TTY","Télex","Adresse de messagerie","Type de messagerie","Nom complet de l\'adresse de messagerie","Adresse de messagerie 2","Type de messagerie 2","Nom complet de l\'adresse de messagerie 2","Adresse de messagerie 3","Type de messagerie 3","Nom complet de l\'adresse de messagerie 3","Anniversaire","Anniversaire de mariage ou fête","Autre boîte postale","B.P. professionnelle","Boîte postale du domicile","Bureau","Catégories","Code gouvernement","Compte","Conjoint(e)","Critère de diffusion","Disponibilité Internet","Emplacement","Enfants","Informations facturation","Initiales","Kilométrage","Langue","Mots clés","Nom de l\'assistant(e)","Notes","Numéro d\'identification de l\'organisation","Page Web","Passe-temps","Priorité","Privé","Profession","Recommandé par","Responsable","Serveur d\'annuaire","Sexe","Utilisateur 1","Utilisateur 2","Utilisateur 3","Utilisateur 4"
																																							';
				fwrite($fdw, $row);
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = '"",';
					$row .= '"' . $stuff[$i]["nom"] . '",,';
					$row .= '"' . $stuff[$i]["prenom"] . '","","","","","","' . $stuff[$i]["titre"] . '",,,,,,,,';
					$row .= '"' . $stuff[$i]["adresse1"] . '","' . $stuff[$i]["adresse2"] . '",,"' . $stuff[$i]["ville"] . '","' . $stuff[$i]["province"] . '","' . $stuff[$i]["code_postal"] . '","' . $stuff[$i]["pays"] . '",,,,,,,,,,,,,,,,';
					$row .= '"' . $stuff[$i]["telephone_fixe"] . '",,,"' . $stuff[$i]["telephone_mobile"] . '",,,,,,,,';
					$row .= '"' . $stuff[$i]["courriel"] . '",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,""
																																																	';
					fwrite($fdw, $row);
				}
				fclose($fdw);
				exportFile("contacts", "contacts.csv", "", true);
				exit;
				break;
			case 200 :
				$sep=',';
				$env='"';
				$cr=chr(13).chr(10);
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addJoin("type_titre", "", "individu.id_titre = type_titre.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addField("type_titre.titre_long as titre");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("lieu.adresse2 as adresse2");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition(" adresse_personnelle_o_n='1' OR adresse_personnelle_o_n IS NULL ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//			$this->p($sql);
				$stuff = $db->getrows($sql);
				//				$this->p($stuff);
				$fdw = fopen("contacts", "w");
				//		$row = '"Given Name","Family Name","Name Prefix","Address 1 - Type","Address 1 - Street","Address 1 - City","Address 1 - Region","Address 1 - Postal Code","Address 1 - Country","Phone 1 - Type","Phone 1 - Value","Phone 2 - Type","Phone 2 - Value","E-mail 1 - Type","E-mail 1 - Value"'.chr(13).chr(10);
				$row = '"First Name","Last Name","E-mail Address","Home Address","Mobile Phone","Home Phone"'.chr(13).chr(10);
				fwrite($fdw, $row);
				for ($i = 0;$i<count($stuff);$i++) {
					$row='';
					$row = '"' . $stuff[$i]["prenom"] . '",';
					$row .= '"' . $stuff[$i]["nom"] . '",' ;
					$row .= '"' . $stuff[$i]["courriel"] . '",' ;
					$row .= '"' . $stuff[$i]["adresse1"] . ' , ';
					(!empty($stuff[$i]["adresse2"])) ? $row.= $stuff[$i]["adresse2"] . ' , ' : null;
					$row.=$stuff[$i]["ville"] . ' , '
							. $stuff[$i]["province"] . ' , '
									. $stuff[$i]["code_postal"] . ' , '
											. $stuff[$i]["pays"] . '",';
					$row .= '"' . $stuff[$i]["telephone_mobile"] . '",' ;
					$row .= '"' . $stuff[$i]["telephone_fixe"] . '"' ;
					$row .=  chr(13).chr(10);
					fwrite($fdw, $row);
				}
				
				fclose($fdw);
				exportFile("contacts", "contacts.csv", "", true);
				exit;
				break;
			case 4 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("type_cp_ville_pays");
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", false);
				$query->addField("type_cp_ville_pays.ville");
				$query->addField("type_cp_ville_pays.code_postal");
				$query->addField("type_pays.libelle_anglais");
				$query->addCondition("type_cp_ville_pays.ville like '%ang%' ");
				$query->addOrderBy("type_cp_ville_pays.code_postal, type_cp_ville_pays.ville ");
				$sql = $query->buildSelect();
				$user = getUser();
				$id = $user["id"];
				echo "début<br>" . gmdate("c") . '<br>';
				$deb1 = time();
				$stuff = $db->getrows($sql);
				echo "fin<br>" . gmdate("c") . '<br>';
				$fin1 = time();
				usleep(3000000);
				echo "début<br>" . gmdate("c") . '<br>';
				$deb2 = time();
				$stuff = $db->getrows($sql);
				echo "fin<br>" . gmdate("c") . '<br>';
				$fin2 = time();
				usleep(3000000);
				echo "début<br>" . gmdate("c") . '<br>';
				$deb3 = time();
				$stuff = $db->getrows($sql);
				echo "fin<br>" . gmdate("c") . '<br>';
				$fin3 = time();
				usleep(3000000);
				echo "début<br>" . gmdate("c") . '<br>';
				$deb4 = time();
				$stuff = $db->getrows($sql);
				echo "fin<br>" . gmdate("c") . '<br>';
				$fin4 = time();
				echo "Doit durer à peu près 12 secondes<br>";
				$elapsed1 = $fin1 - $deb1;
				$elapsed2 = $fin2 - $deb2;
				$elapsed3 = $fin3 - $deb3;
				$elapsed4 = $fin4 - $deb4;
				$elapsedtotal = $fin4 - $deb1;
				$deb1 = gmdate('c', $deb1);
				$fin1 = gmdate('c', $fin1);
				$deb2 = gmdate('c', $deb2);
				$fin2 = gmdate('c', $fin2);
				$deb3 = gmdate('c', $deb3);
				$fin3 = gmdate('c', $fin3);
				$deb4 = gmdate('c', $deb4);
				$fin4 = gmdate('c', $fin4);
				$data = $db->query("insert into performance_serveur (
				id_test,
				date_debut_1,
				date_fin_1,
				elapsed_1 ,
				date_debut_2 ,
				date_fin_2 ,
				elapsed_2,
				date_debut_3,
				date_fin_3 ,
				elapsed_3,
				date_debut_4 ,
				date_fin_4 ,
				elapsed_4 ,
				elapsed_total,
				id_creation,
				date_creation) VALUES (
				'1',
				'$deb1',
				'$fin1',
				'$elapsed1',
				'$deb2',
				'$fin2',
				'$elapsed2',
				'$deb3',
				'$fin3',
				'$elapsed3',
				'$deb4',
				'$fin4',
				'$elapsed4',
				'$elapsedtotal',
				$id,'" . gmdate(c) . "'
																																							) ");
				break;
			case 5 :
				// Inscrits sans courriel
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//				$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$row = array ();
				$row[] = "#";
				$row[] = "Organisme";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Courriel";
				$row[] = "Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse(1)";
				$row[] = "Code Postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 6 :
				// avec courriel
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//			$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition(" individu.courriel is not null ");
				$query->addCondition(" individu.courriel !='' ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				$row = array ();
				$row[] = "#";
				$row[] = "Organisme";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Courriel";
				$row[] = "Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse(1)";
				$row[] = "Code Postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				// ....
				// Create data
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_avec_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 7 :
				//sans courriel et sans adresse
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//			$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//				$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				$query->addCondition(" individu.id not in (select id_individu from individu_lieu) ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$row = array ();
				$row[] = "#";
				$row[] = "Organisme";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Courriel";
				$row[] = "Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse(1)";
				$row[] = "Code Postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel_et_sans_adresse_postale.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 8 :
				// sans adresse postale
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//			$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//				$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				//				$query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				$query->addCondition(" individu.id not in (select id_individu from individu_lieu where adresse_defaut_o_n='1') ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				
				// ....
				// Create data
				$row = array ();
				$row[] = "#";
				$row[] = "Organisme";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Courriel";
				$row[] = "Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse(1)";
				$row[] = "Code Postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel_et_sans_adresse_postale.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 9 :
				// courriels
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition(" individu.courriel is not null ");
				$query->addCondition(" individu.courriel !='' ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$row = array ();
				$row[] = "Courriel";
				$data[] = $row;
				$tbl->setRowClass(1, "superbold");
				$tbl->setTableStyle("toc sortable");
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = htmlentities('"' . $stuff[$i]["nom"] . ' ' . $stuff[$i]["prenom"] . '" <' . $stuff[$i]["courriel"] . '>,');
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel_et_sans_adresse_postale.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 10 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_rencontre");
				$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
				$query->addJoin("organisme_rencontre", "", "individu_rencontre.id_rencontre = organisme_rencontre.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu_rencontre.id_individu = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addJoin("type_rencontre", "", "organisme_rencontre.id_type_rencontre = type_rencontre.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("type_rencontre.libelle as type_rencontre");
				$query->addField("organisme_rencontre.libelle as libelle_rencontre");
				$query->addField("organisme_rencontre.date_debut as date_debut");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition("organisme_rencontre.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("organisme_rencontre.id_type_rencontre in ( " . $this->m_postvars["idtypes"] . ")");
				$query->addCondition("year(organisme_rencontre.date_debut) in ( " . $this->m_postvars["idans"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addOrderBy("individu.nom, individu.prenom");
				$stuff = $db->getrows($query->buildSelect());
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["type_rencontre"];
					$row[] = $stuff[$i]["date_debut"];
					$row[] = $stuff[$i]["libelle_rencontre"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "toc");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				// $output->outputFlush();
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_tous.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 11 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_rencontre");
				$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
				$query->addJoin("organisme_rencontre", "", "individu_rencontre.id_rencontre = organisme_rencontre.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu_rencontre.id_individu = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addJoin("type_rencontre", "", "organisme_rencontre.id_type_rencontre = type_rencontre.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("type_rencontre.libelle as type_rencontre");
				$query->addField("organisme_rencontre.libelle as libelle_rencontre");
				$query->addField("organisme_rencontre.date_debut as date_debut");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition("organisme_rencontre.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("organisme_rencontre.id in ( " . $this->m_postvars["idrencontres"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addOrderBy("individu.nom, individu.prenom");
				$stuff = $db->getrows($query->buildSelect());
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["type_rencontre"];
					$row[] = $stuff[$i]["date_debut"];
					$row[] = $stuff[$i]["libelle_rencontre"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "toc");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				// $output->outputFlush();
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_tous.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 12 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("organisme");
				$query->addJoin("individu_inscription", "ii", "organisme.id=ii.id_organisme", false);
				$query->addJoin("individu", "i", "ii.id_individu=i.id", false);
				$query->addJoin("type_inscription", "ti", "ii.id_type_inscription = ti.id", false);
				$query->addJoin("individu_cotisation", "ic", "ii.id_individu = ic.id_individu", true);
				$query->addJoin("organisme_cotisation", "oc", "ic.id_cotisation = oc.id", true);
				$query->addField("organisme.nom as organisme");
				$query->addField("i.nom as nom");
				$query->addField("i.prenom as prenom");
				$query->addField("ii.id_inscription as numero_inscription");
				$query->addField("ii.date_radiation as radiation");
				$query->addField(" max(ic.date_reglement) as derniere_cotisation");
				$query->addCondition("organisme.id= " . $this->m_postvars["id"]);
				$query->addCondition("oc.id_organisme= " . $this->m_postvars["id"]);
				$query->addCondition(" ti.cotisation_organisme_o_n ='1' ");
				$query->addGroupBy("ii.id_inscription");
				$query->addOrderBy("ii.date_radiation desc, max(ic.date_reglement), organisme.nom,i.nom, i.prenom, ii.id_inscription");
				$stuff = $db->getrows($query->buildSelect());
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$row1 = array ();
				$row1[] = "#";
				$row1[] = "Organisme";
				$row1[] = "Nom";
				$row1[] = "Prénom";
				$row1[] = "Numéro_inscription";
				$row1[] = "Dernière_cotisation";
				$row1[] = "Radiation";
				$data[] = $row1;
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["numero_inscription"];
					$row[] = $stuff[$i]["derniere_cotisation"];
					$row[] = $stuff[$i]["radiation"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "navpers");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_cotisations.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 20 :
				// Individus
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//				$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				// $query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "toc");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 21 :
				// Individus
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.sexe as sexe");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$tbl->setTableStyle("toc sortable");
				$data = array ();
				$tbl->setRowClass(1, "superbold");
				$row = array ();
				$row[] = "#";
				$row[] = "Nom";
				$row[] = "Prénom";
				$row[] = "Sexe";
				
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["sexe"];

					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, TBL_HEADER, "toc sortable");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
				case 107 :
				// competences individus
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addJoin("individu_competence", "", "individu.id = individu_competence.id_individu", false);
				$query->addJoin("type_competence", "", "individu_competence.id_type_competence= type_competence.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("type_competence.libelle as competence");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu.date_deces is null");
				$query->addOrderBy("individu.nom, individu.prenom, competence");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$tbl->setRowClass(1, "superbold");
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["competence"];

					$data[] = $row;
				}
				// render table.
				$res = $tbl->render($data, 0, "toc");
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_sans_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
			case 22 :
				// Listes fonctions avec organisme mandatant
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu_fonction");
				$query->addJoin("individu", "", "individu_fonction.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_fonction.id_organisme = organisme.id", false);
				$query->addJoin("organisme", "organisme_represente", "individu_fonction.id_organisme_represente = organisme_represente.id", true);
				$query->addJoin("type_fonction", "", "individu_fonction.id_fonction = type_fonction.id", false);
				$query->addField("organisme.nom as organisme");
				$query->addField("organisme.site_internet as site_internet");
				$query->addField("organisme_represente.nom as organisme_represente");
				$query->addField("organisme_represente.site_internet as organisme_represente_site_internet");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("type_fonction.libelle as type_fonction");
				$query->addCondition("individu_fonction.id_organisme = " . $this->m_postvars["id"]);
				$query->addCondition("individu_fonction.id_fonction in ( " . $this->m_postvars["idfonctions"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("individu_fonction.date_fin is null");
				$query->addOrderBy("type_fonction.libelle,individu.nom, individu.prenom");
				$stuff = $db->getrows($query->buildSelect());

				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$row = array ();
				//				$row[] = "";

				$row[] = "Organisme";
				$row[] = "Fonction";
				$row[] ="Nom";
				$row[] = "Prénom";
				$row[] = "Organisme représenté";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					//					$row[] = $i +1;
					//					$row[] = $stuff[$i]["organisme"];
					$stuff[$i]["type_fonction"]=str_replace("Association - bureau - ","",$stuff[$i]["type_fonction"]);
					$stuff[$i]["type_fonction"]=str_replace("Association - ","",$stuff[$i]["type_fonction"]);
					$stuff[$i]["type_fonction"]=str_replace("- membre","",$stuff[$i]["type_fonction"]);
					$stuff[$i]["type_fonction"]=ucfirst($stuff[$i]["type_fonction"]);
					if ($stuff[$i]["site_internet"]=="")
					{$row[] = $stuff[$i]["organisme"];}
					else
					{
						$row[] = '<a href="'.$stuff[$i]["site_internet"].'">'.$stuff[$i]["organisme"].'</a>';
					}
					$row[] = $stuff[$i]["type_fonction"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					if ($stuff[$i]["organisme_represente_site_internet"]=="")
					{$row[] = $stuff[$i]["organisme_represente"];}
					else
					{
						$row[] = '<a href="'.$stuff[$i]["organisme_represente_site_internet"].'">'.$stuff[$i]["organisme_represente"].'</a>';

					}

					$data[] = $row;
				}
				// render table.

				$res .= $tbl->render($data, 0, "navpers");

				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$outgg=$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_fonctions.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($outgg));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
				case 106 :
				// licence golf
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//			$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("individu.golf_index as golf_index");
				$query->addField("individu.golf_licence as golf_licence");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition(" individu.golf_licence is not null ");
				$query->addCondition(" individu.golf_licence !='' ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$titre='Avec index de golf';
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				$tbl->setTableStyle("toc sortable");
				// ....
				// Create data
				$row = array ();
				$row[] = "#";
				//			$row[] = $stuff[$i]["organisme"];
				$row[] ="Nom";
				$row[] = "Prénom";
				$row[] = "Index golf";
				$row[] = "Licence golf";
				$row[] = "Courriel";
				$row[] ="Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse (1)";
				$row[] = "Code postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
		//			$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["golf_index"];
					$row[] = $stuff[$i]["golf_licence"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res = $titre.'</br>';
				$res .= $tbl->render($data, TBL_HEADER, "toc sortable");
				
								$query = & $db->createQuery();
				$query->addTable("individu");
				//				$query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
				//				$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				//				$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
				//				$query->addField("organisme.nom as organisme");
				//			$query->addField("individu_inscription.id as id_inscription");
				//				$query->addField("individu_inscription.id_individu as id_individu");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("individu.golf_index as golf_index");
				$query->addField("individu.golf_licence as golf_licence");
				//				$query->addField("type_inscription.libelle as type_inscription");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_pays.libelle_anglais as pays");
				//				$query->addCondition("individu_inscription.id_organisme = " . $this->m_postvars["id"]);
				//				$query->addCondition("individu_inscription.date_radiation is null ");
				$query->addCondition("individu_lieu.adresse_defaut_o_n='1' ");
				$query->addCondition("individu.id in ( " . $this->m_postvars["idindividus"] . ")");
				$query->addCondition("individu.date_deces is null");
				$query->addCondition("( individu.golf_licence is null or individu.golf_licence ='0' )");
		//		$query->addCondition(" individu.golf_index ='0' ");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//					print_r ($sql);
				//				die();
				$stuff = $db->getrows($sql);
//				$this->p($sql);
				$tbl = & atknew("atk.utils.atktablerenderer");
				$data = array ();
				$row = array ();
				// Develop a table however you'd like it to display
				// Use cascading style sheets to alter the appearance.
				$tbl->setRowClass(1, "superbold");
				// ....
				// Create data
				$row[] = "#";
				//			$row[] = $stuff[$i]["organisme"];
				$row[] ="Nom";
				$row[] = "Prénom";
				$row[] = "Index golf";
				$row[] = "Licence golf";
				$row[] = "Courriel";
				$row[] ="Fixe";
				$row[] = "Mobile";
				$row[] = "Adresse (1)";
				$row[] = "Code postal";
				$row[] = "Ville";
				$row[] = "Province/Etat";
				$row[] = "Pays";
				$data[] = $row;
				$titre='Sans index de golf';
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = array ();
					$row[] = $i +1;
		//			$row[] = $stuff[$i]["organisme"];
					$row[] = $stuff[$i]["nom"];
					$row[] = $stuff[$i]["prenom"];
					$row[] = $stuff[$i]["golf_index"];
					$row[] = $stuff[$i]["golf_licence"];
					$row[] = $stuff[$i]["courriel"];
					$row[] = $stuff[$i]["telephone_fixe"];
					$row[] = $stuff[$i]["telephone_mobile"];
					$row[] = $stuff[$i]["adresse1"];
					$row[] = $stuff[$i]["code_postal"];
					$row[] = $stuff[$i]["ville"];
					$row[] = $stuff[$i]["province"];
					$row[] = $stuff[$i]["pays"];
					$data[] = $row;
				}
				// render table.
				$res .= $titre.'</br>';
				$res .= $tbl->render($data,TBL_HEADER, "toc sortable ");
				
				
				// h// h
				$page = & atknew("atk.ui.atkpage");
				$ui = & atkinstance("atk.ui.atkui");
				$output = & atkOutput :: getInstance();
				$page->register_style($ui->stylePath("style.css"));
				//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
				$page->addContent($res);
				$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				if ($this->m_postvars["atkexport"] == 'o') {
					$filename = $this->m_postvars["id"] . "_inscrits_avec_courriel.html";
					Header("Content-Disposition: attachment; filename=$filename");
					Header("Content-Length: " . strlen($output));
					Header("Connection: close");
					Header("Content-Type: text/html; name=$filename");
				}
				break;
		}
	}
	/*	function nom_display($record, $mode) {
		// Do not return a html link in plain or csv mode or select screen
		if (($mode == "plain") || ($mode == "csv") || (isset ($this->m_postvars["atkaction"]) && $this->m_postvars["atkaction"] == "select"))
		return $record["nom"];
		// Make all project links clickable
		$defaultaction = $this->allowed("edit") ? "edit" : "view";
		return href(dispatch_url("organisme.organisme", $defaultaction, array (
		"atkselector" => "organisme.id='{$record["id"]}'"
		), "dispatch.php"), $record["nom"], SESSION_NESTED);
		}
		*/
	function recordActions($rec, & $actions, & $mraactions) {
		$actions["lister"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=lister&atkselector=[pk]", SESSION_NESTED);
		//		$actions["liste_organismes"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=liste_organismes&atkselector=[pk]", SESSION_NESTED);
		unset ($mraactions["delete"]);
		$mraactions["lister"] = "lister";
		$mraactions['rafraichir_calendrier_rencontres'] = "rafraichir_calendrier_rencontres";
		$mraactions['liste_organismes'] = "liste_organismes";
		global $g_acces_public_seulement;
		global $g_organismes_autorises;
		global $g_sessionManager;
		$g_acces_public_seulement = $g_sessionManager->getValue("atgAccesPublicSeul_o_n", "globals");
		$g_organismes_autorises = $g_sessionManager->getValue("atgOrganismesAutorises", "globals");
		if (($g_acces_public_seulement == '1') && ($rec["acces_public_o_n"] == '0') && (in_array($rec["id"], $g_organismes_autorises) == false)) {
			unset ($actions["edit"]);
			unset ($actions["view"]);
			unset ($actions["delete"]);
			unset ($mraactions["lister"]);
			unset ($actions["lister"]);
		}
	}
	function action_lister() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {			$select[0] = $this->m_postvars["atkselector"];		}
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_organisme";
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id_variable = explode('=', $id_variable);
			$array_id_variable[1] = str_replace("''", "", $array_id_variable[1]);
			$db->query("INSERT INTO tmp_copier_coller (id_utilisateur, nom_variable, id_variable, date_creation)  VALUES( '$userid', '$nom_variable'," . $array_id_variable[1] . ", UTC_TIMESTAMP())");
		}
		$db->commit();
		$this->redirect();
	}
	function assignDocumentVars(& $documentWriter, $selector) {
		switch ($this->m_postvars["atkcode"]) {
			case 1 :
				// Impression endos de chèque
				/*
				$records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
				print_r($records);
				die();

				$documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");
				*/
				$org = & atkGetNode("organisme.organisme");
				$orgrecord = $org->selectDb("organisme.id=" . $this->m_postvars["id"], "", "", "", "", "view");
				$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0], $prefix = "o.");
				$documentWriter->assignDocumentGenericVars();
				break;
		}
	}
	function action_normalisation() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id, nom , telephone " . " from organisme");
		if (count($data) == 0) {
			return true;
		} else {
			for ($i = 0; $i < count($data); $i++) {
				$data[$i]["nom"] = normalisation_chaine($data[$i]["nom"]);
				$data[$i]["nom"] = addslashes($data[$i]["nom"]);
				$data[$i]["telephone"] = normalisation_telephone($data[$i]["telephone"]);
				$data[$i]["telephone"] = addslashes($data[$i]["telephone"]);
				$db->query("UPDATE organisme" . " set nom='" . $data[$i]["nom"] . "'" . ", telephone='" . $data[$i]["telephone"] . "' where id=" . $data[$i]["id"] . "");
			}
		}
		echo "<br> Normalisation des noms et téléphones terminée.";
	}
	function action_init_compta() {
		$id_organisme = $this->m_postvars["id"];
		$user = getUser();
		$iduser = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT date_initialisation_comptabilite  from organisme
					 where id ='" . $id_organisme . "'");
		if ($data[0]["date_initialisation_comptabilite"] != null) {
			echo "<b>La comptabilité a déjà été initialisée<br></b>";
			die();
		}
		$sql = "insert into organisme_compte ( id_organisme, code, libelle, usuel, id_creation, date_creation, id_modification,  date_modification)
					select '" . $id_organisme . "' ,code, libelle, usuel, '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() from modele_compte ";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_compte ");
		$nextid = $data[0]["last_id"] + 1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_compte' ");
		$data = $db->getrows("select id as id_compte_dons
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='77131'");
		$id_compte_dons = $data[0]["id_compte_dons"];
		$data = $db->getrows("select id as id_compte_cotisation_organisme_an_prec
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='7561'");
		$id_compte_cotisation_organisme_an_prec = $data[0]["id_compte_cotisation_organisme_an_prec"];
		$data = $db->getrows("select id as id_compte_cotisation_organisme_an
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='7562'");
		$id_compte_cotisation_organisme_an = $data[0]["id_compte_cotisation_organisme_an"];
		$data = $db->getrows("select id as id_compte_cotisation_organisme_an_suiv
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='7563'");
		$id_compte_cotisation_organisme_an_suiv = $data[0]["id_compte_cotisation_organisme_an_suiv"];
		$data = $db->getrows("select id as id_compte_cotisation_federation_an_prec
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='628111'");
		$id_compte_cotisation_federation_an_prec = $data[0]["id_compte_cotisation_federation_an_prec"];
		$data = $db->getrows("select id as id_compte_cotisation_federation_an
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='628112'");
		$id_compte_cotisation_federation_an = $data[0]["id_compte_cotisation_federation_an"];
		$data = $db->getrows("select id as id_compte_cotisation_federation_an_suiv
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='628113'");
		$id_compte_cotisation_federation_an_suiv = $data[0]["id_compte_cotisation_federation_an_suiv"];
		$data = $db->getrows("select id as id_compte_adherents
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='411'");
		$id_compte_adherents = $data[0]["id_compte_adherents"];
		$data = $db->getrows("select id as id_compte_financeurs
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='412'");
		$id_compte_financeurs = $data[0]["id_compte_financeurs"];
		$data = $db->getrows("select id as id_compte_fournisseurs
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='401'");
		$id_compte_fournisseurs = $data[0]["id_compte_fournisseurs"];
		$data = $db->getrows("select id as id_compte_federation
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='4511'");
		$id_compte_federation = $data[0]["id_compte_federation"];
		$data = $db->getrows("select id as id_compte_banque_courant
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='51211'");
		$id_compte_banque_courant = $data[0]["id_compte_banque_courant"];
		$data = $db->getrows("select id as id_compte_banque_epargne
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='51212'");
		$id_compte_banque_epargne = $data[0]["id_compte_banque_epargne"];
		$data = $db->getrows("select id as id_compte_caisse
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='531'");
		$id_compte_caisse = $data[0]["id_compte_caisse"];
		$data = $db->getrows("select id as id_compte_participation_manifestation
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='7581'");
		$id_compte_participation_manifestation = $data[0]["id_compte_participation_manifestation"];
		$data = $db->getrows("select id as id_compte_kilometres
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62511'");
		$id_compte_kilometres = $data[0]["id_compte_kilometres"];
		$data = $db->getrows("select id as id_compte_peage
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62512'");
		$id_compte_peage = $data[0]["id_compte_peage"];
		$data = $db->getrows("select id as id_compte_parking
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62513'");
		$id_compte_parking = $data[0]["id_compte_parking"];
		$data = $db->getrows("select id as id_compte_transport_en_commun
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62514'");
		$id_compte_transport_en_commun = $data[0]["id_compte_transport_en_commun"];
		$data = $db->getrows("select id as id_compte_repas
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62515'");
		$id_compte_repas = $data[0]["id_compte_repas"];
		$data = $db->getrows("select id as id_compte_hotel
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62516'");
		$id_compte_hotel = $data[0]["id_compte_hotel"];
		$data = $db->getrows("select id as id_compte_fournitures_diverses
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62517'");
		$id_compte_fournitures_diverses = $data[0]["id_compte_fournitures_diverses"];
		$data = $db->getrows("select id as id_compte_frais_divers
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='62518'");
		$id_compte_frais_divers = $data[0]["id_compte_frais_divers"];
		$data = $db->getrows("select id as id_compte_benevolat
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='8701'");
		$id_compte_benevolat = $data[0]["id_compte_benevolat"];
		$data = $db->getrows("select id as id_compte_personnel_benevole
					from organisme_compte
					 where id_organisme='" . $id_organisme . "'
					and code='864'");
		$id_compte_personnel_benevole = $data[0]["id_compte_personnel_benevole"];
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des cotisations organisme',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idcotisationsorganisme = $data[0]["last_id"];
		$nextid = $idcotisationsorganisme +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des cotisations fédération',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idcotisationsfederation = $data[0]["last_id"];
		$nextid = $idcotisationsfederation +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,id_compte_banque,   id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal de banque courant', '$id_compte_banque_courant', '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idbanquecourant = $data[0]["last_id"];
		$nextid = $idbanquecourant +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle, id_compte_banque, id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal de banque épargne','$id_compte_banque_epargne',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idbanqueepargne = $data[0]["last_id"];
		$nextid = $idbanqueepargne +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des dépenses',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$iddepenses = $data[0]["last_id"];
		$nextid = $iddepenses +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des recettes',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idrecettes = $data[0]["last_id"];
		$nextid = $idrecettes +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal de caisse',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idcaisse = $data[0]["last_id"];
		$nextid = $idcaisse +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des frais de déplacement',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idfrais = $data[0]["last_id"];
		$nextid = $idcaisse +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal du bénévolat',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idbenevolat = $data[0]["last_id"];
		$nextid = $idcaisse +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$sql = "insert into organisme_journal_comptable
					 ( id_organisme,libelle,  id_creation, date_creation, id_modification,  date_modification)
					values ( '" . $id_organisme . "' ,'Journal des opérations diverses',  '" . $iduser . "', UTC_TIMESTAMP(), '" . $iduser . "', UTC_TIMESTAMP() )";
		$data = $db->query($sql);
		$data = $db->getrows("select max(id) as last_id from organisme_journal_comptable
					 where id_organisme='" . $id_organisme . "' ");
		$idod = $data[0]["last_id"];
		$nextid = $idcaisse +1;
		$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_journal_comptable' ");
		$data = $db->query("update organisme
		set id_compte_banque_epargne='$id_compte_banque_epargne',
		id_compte_banque_courant='$id_compte_banque_courant',
		id_compte_federation='$id_compte_federation',
		id_compte_adherents='$id_compte_adherents',
		id_compte_financeurs='$id_compte_financeurs',
		id_compte_fournisseurs='$id_compte_fournisseurs',
		id_compte_cotisation_federation_an_suiv='$id_compte_cotisation_federation_an_suiv',
		id_compte_cotisation_federation_an='$id_compte_cotisation_federation_an',
		id_compte_cotisation_federation_an_prec='$id_compte_cotisation_federation_an_prec',
		id_compte_cotisation_organisme_an_suiv='$id_compte_cotisation_organisme_an_suiv',
		id_compte_cotisation_organisme_an='$id_compte_cotisation_organisme_an',
		id_compte_cotisation_organisme_an_prec='$id_compte_cotisation_organisme_an_prec',
		id_compte_caisse='$id_compte_caisse',
		id_compte_dons='$id_compte_dons',
		id_compte_participation_manifestation='$id_compte_participation_manifestation',
		id_compte_kilometres='$id_compte_kilometres',
		id_compte_peage='$id_compte_peage',
		id_compte_parking='$id_compte_parking',
		id_compte_transport_en_commun='$id_compte_transport_en_commun',
		id_compte_repas='$id_compte_repas',
		id_compte_hotel='$id_compte_hotel',
		id_compte_fournitures_diverses='$id_compte_fournitures_diverses',
		id_compte_frais_divers='$id_compte_frais_divers',
		id_compte_benevolat='$id_compte_benevolat',
		id_compte_personnel_benevole='$id_compte_personnel_benevole',
		prochain_id_ecriture='1',
		prochain_id_remise_en_banque='1',
		eclater_cotisations_dons_o_n='1',
		id_journal_cotisations_organisme='$idcotisationsorganisme',
		id_journal_cotisations_federation='$idcotisationsfederation',
		id_journal_recettes='$idrecettes',
		id_journal_depenses='$iddepenses',
		id_journal_caisse='$idcaisse',
		id_journal_banque_courant='$idbanquecourant',
		id_journal_banque_epargne='$idbanqueepargne',
		id_journal_frais='$idfrais',
		id_journal_benevolat='$idbenevolat',
		id_journal_operations_diverses='$idod',
		id_modification='$iduser',
		date_modification=UTC_TIMESTAMP(),
		date_initialisation_comptabilite=UTC_TIMESTAMP()
		where id='" . $id_organisme . "'
					");
		echo '<b> La comptabilité a été initialisée avec succès.<br>
	Ne pas oublier de renseigner dans Organisme/Paramètres/Indemnités de base <br>
	les champs \'Montant indemnite kilometre\' et \'Montant indemnite heure benevolat\'.';
		die();
	}
	function descriptor_def() {

		return "[nom] ([sigle])";
	}
	function action_vcard(& $handler) {
		return $this->createVCard($this->m_postvars["organisme.id"]);
	}
	function createVCard($id) {
		include_once (moduleDir("utils") . "vcard.php");
		$v = new vCard();
		$recs = $this->selectDb("organisme.id='" . $id . "'", "", "", "", array (
		"courriel",
		"telephone",
		"site_internet",
		"nom"
		));
		$record = $recs[0];
		$v->setName($record["nom"], "", "", "");
		$v->setURL($record["site_internet"]);
		// GG  début
		$id_organisme = $record['id'];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT adresse1, adresse2,  code_postal, ville, province_etat,libelle_francais
		from organisme_lieu ol, lieu l, type_cp_ville_pays v , type_pays p where ol.id_organisme='" . $id . "' 
and ol.id_lieu=l.id and l.id_ville=v.id and v.id_pays=p.id");
		$pays = strtolower($data[0]["libelle_francais"]);
		$pays = ucwords($pays);
		$v->setAddress("", "", $data[0]["adresse1"], $data[0]["ville"], $data[0]["province_etat"], $data[0]["code_postal"], $pays);
		$v->setAddress("", "", $data[0]["adresse1"], $data[0]["ville"], $data[0]["province_etat"], $data[0]["code_postal"], $pays, "POSTAL");
		$v->setPhoneNumber($record["telephone"], "PREF;WORK;VOICE");
		$v->setEmail($record["courriel"]);
		// GG Fin
		$output = $v->getVCard();
		//$filename = $v->getFileName();
		//Remove spaces that would break the vcard filename
		$name = str_replace(" ", "_", $record['name']);
		$filename = $name . ".vcf";
		Header("Content-Disposition: attachment; filename=$filename");
		Header("Content-Length: " . strlen($output));
		Header("Connection: close");
		Header("Content-Type: text/x-vCard; name=$filename");
		echo $output;
		exit;
	}
function action_affiche_record() {
		$table=$this->m_postvars["table"];
		$id_table=$this->m_postvars["id_table"];
		$db = & atkGetDb();
		$sql="Select * from $table where id=$id_table";
		$rows=$db->getRows($sql);
//		$this->p($rows[0]);
		$data = array ();
		$row = array ();
		$row[]="<b>Field";
		$row[] = "<b>Value";
		$data[] = $row;
while (list($key, $val) = each($rows[0] ))
  {		$row = array ();
		$row[]=$key;
		$row[] = $val;
		$data[] = $row;
		}
		$tbl = & atknew("atk.utils.atktablerenderergrouped");
		$res="Table : ".$table."</br>";
		$res .= $tbl->render($data, TBL_HEADER | TBL_ALTERNATE, "recordlistgg");
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
/*
		echo "Table : ".$table."</br>";
		$this->p($rows[0]);
		*/
}
function action_affiche_table_definition() {
		$table=$this->m_postvars["table"];
		$db = & atkGetDb();		
		$data = array ();
		$sql="explain $table";
		$stuff=$db->getrows($sql);
		$row = array ();
		$row[]="<b>Field";
		$row[] = "<b>Type";
		$row[] = "<b>Null";
		$row[] = "<b>Key";
		$row[] = "<b>Default";
		$row[] = "<b>Extra";
		$data[] = $row;
		for ($i = 0; $i < count($stuff); $i++) {
		$row = array ();
		$row[]=$stuff[$i]["Field"];
		$row[] = $stuff[$i]["Type"];
		$row[] = $stuff[$i]["Null"];
		$row[] = $stuff[$i]["Key"];
		$row[] = $stuff[$i]["Default"];
		$row[] = $stuff[$i]["Extra"];
		$data[] = $row;		
		}
		$tbl = & atknew("atk.utils.atktablerenderergrouped");
		$res="Table : ".$table."</br>";
		$res .= $tbl->render($data, TBL_HEADER | TBL_ALTERNATE, "recordlistgg");
		$page = & atknew("atk.ui.atkpage"); 
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
}
function action_affiche_atk_record() {
	global $g_sessionManager;
	$record = $g_sessionManager->getValue("atk_record", "globals");
	$module=$this->m_postvars["module"];
		$node=$this->m_postvars["node"];
		echo "Module : ".$module.'.'.$node."</br>";
			$this->p($record);
/*			$tbl = & atknew("atk.utils.atktablerenderergrouped");
		$res="xModule : ".$module.'.'.$node."</br>";
		$res .= $tbl->render($record,  TBL_ALTERNATE, "recordlistgg");
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		*/
}
function action_geolocalisation_inscrits() {
$id_organisme = $this->m_postvars["id"];
$origine = $this->m_postvars["origine"];
$type = $this->m_postvars["type"];
if ($origine!="geolocalisation")
{
/*	$html='<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
	
	<meta name="generator" content="Andy Moore: http://locationdetection.mobi/">
	<title>Location Detection Example</title>
	</head>';
*/	
	if (	$type =="organisme")
	{$url=dispatch_url("organisme.organisme", "geolocalisation_inscrits", array (
			"id" => "" . $id_organisme . "",
		"origine" => "geolocalisation",
			"type" => $type
			));}
	else 
		{$url=dispatch_url("organisme.organisme", "geolocalisation_inscrits", array (
				"origine" => "geolocalisation",
				"type" => $type
		));}
$html='<script type="text/javaScript">
		function GEOprocess(position) {
  document.getElementById("geo").innerHTML = "Latitude: " + position.coords.latitude + " Longitude: " + position.coords.longitude;
	GEOajax("'.$url.'&accuracy=" + position.coords.accuracy + "&latlng=" + position.coords.latitude + "," + position.coords.longitude +"&altitude="+position.coords.altitude+"&altitude_accuracy="+position.coords.altitudeAccuracy+"&heading="+position.coords.heading+"&speed="+position.coords.speed+"");
}
function GEOdeclined(error) {
  document.getElementById("geo").innerHTML = "Erreurr: " + error.message;
}
if (navigator.geolocation) {
	navigator.geolocation.getCurrentPosition(GEOprocess, GEOdeclined);
}else{
  document.getElementById("geo").innerHTML = "Mettre à jour votre navigateur";
}
if (window.XMLHttpRequest) {
 xmlHttp = new XMLHttpRequest();
}else if(window.ActiveXObject){
 xmlHttp = new ActiveXObject("Microsoft.XMLHTTP");
}
function GEOajax(url) {
 xmlHttp.open("GET", url, true);
 xmlHttp.onreadystatechange = updatePage;
 xmlHttp.send(null);
}
function updatePage() {
 if (xmlHttp.readyState == 4) {
  var response = xmlHttp.responseText;
  document.getElementById("geo").innerHTML = "" + response;
 }
			}</script>
';

if (	$type =="organisme")
{$html.='<h1>Géolocalisation des adhérents et animateurs : <br/>'.$this->descripteur_organisme($id_organisme,'n','n','0','menu') .' </h1>
		<div id="geo" class="geolocation_data"></div>';}
else
{
	$html.='<h1>Géolocalisation des individus < 50km : <br/> </h1>
		<div id="geo" class="geolocation_data"></div>';
}
$this->page_output($html);
// echo $html;
}
else
{
	$geo = 'http://maps.google.com/maps/api/geocode/xml?latlng='.htmlentities(htmlspecialchars(strip_tags($_GET['latlng']))).'&sensor=true';
	$xml = simplexml_load_file($geo);
		
	foreach($xml->result->address_component as $component){
		if($component->type=='street_address'){
			$geodata['precise_address'] = $component->long_name;
		}
		if($component->type=='natural_feature'){
			$geodata['natural_feature'] = $component->long_name;
		}
		if($component->type=='airport'){
			$geodata['airport'] = $component->long_name;
		}
		if($component->type=='park'){
			$geodata['park'] = $component->long_name;
		}
		if($component->type=='point_of_interest'){
			$geodata['point_of_interest'] = $component->long_name;
		}
		if($component->type=='premise'){
			$geodata['named_location'] = $component->long_name;
		}
		if($component->type=='street_number'){
			$geodata['house_number'] = $component->long_name;
		}
		if($component->type=='route'){
			$geodata['street'] = $component->long_name;
		}
		if($component->type=='locality'){
			$geodata['town_city'] = $component->long_name;
		}
		if($component->type=='administrative_area_level_3'){
			$geodata['district_region'] = $component->long_name;
		}
		if($component->type=='neighborhood'){
			$geodata['neighborhood'] = $component->long_name;
		}
		if($component->type=='colloquial_area'){
			$geodata['locally_known_as'] = $component->long_name;
		}
		if($component->type=='administrative_area_level_2'){
			$geodata['county_state'] = $component->long_name;
		}
		if($component->type=='postal_code'){
			$geodata['postcode'] = $component->long_name;
		}
		if($component->type=='country'){
			$geodata['country'] = $component->long_name;
		}
	}

	list($lat,$long) = explode(',',htmlentities(htmlspecialchars(strip_tags($_GET['latlng']))));
	$geodata['latitude'] = $lat;
	$geodata['longitude'] = $long;
	$geodata['formatted_address'] = $xml->result->formatted_address;
	$geodata['accuracy'] = htmlentities(htmlspecialchars(strip_tags($_GET['accuracy'])));
	$geodata['altitude'] = htmlentities(htmlspecialchars(strip_tags($_GET['altitude'])));
	$geodata['altitude_accuracy'] = htmlentities(htmlspecialchars(strip_tags($_GET['altitude_accuracy'])));
	$geodata['directional_heading'] = htmlentities(htmlspecialchars(strip_tags($_GET['heading'])));
	$geodata['speed'] = htmlentities(htmlspecialchars(strip_tags($_GET['speed'])));
	$geodata['google_api_src'] = $geo;

	$res2= '<table class="toc  sortable">';
	$res2.='<thead>';
	$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Titre</center></b>';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Valeur</center></b>';
	$res2.='</th></tr>';
	$res2.='</thead>';
	$res2.='<tbody>';
	$res2.= "<tr><td>".(++$i);
	$res2.='</td><td>Latitude';
	$res2.='</td><td>'.$lat;
	$res2.='</td></tr>';
	$res2.= "<tr><td>".(++$i);
	$res2.='</td><td>Longitude';
	$res2.='</td><td>'.$long;
	foreach($geodata as $name => $value){
		$res2.= "<tr><td>".(++$i);
		$res2.='</td><td>'.$name;
		$res2.='</td><td>'.str_replace('&','&amp;',$value);
		$res2.='</td></tr>';
	//	echo ''.$name.': '.str_replace('&','&amp;',$value).'<br />';
	}
	$res2.='</tbody>';
	$res2.='</table>';
	$db = & atkGetDb();
	if ($type=="organisme")
	{
	$sql="
select il.id_individu,
FORMAT(ACOS( SIN( RADIANS( l.latitude ) ) * SIN( RADIANS( $lat ) ) + COS( RADIANS(l.latitude) )
* COS( RADIANS( $lat )) * COS( RADIANS( l.longitude ) - RADIANS( $long )) ) * 6380 , 3) AS distance, 
FORMAT(l.longitude ,7) AS longitude,
FORMAT( l.latitude,7) AS latitude

FROM lieu l, individu_lieu il 
WHERE il.id_individu in (select distinct id_individu from individu_fonction where id_organisme=$id_organisme and date_fin is null
UNION select distinct id_individu from individu_inscription  where id_organisme=$id_organisme and date_radiation is null)

and l.longitude is not null
and l.id = il.id_lieu 
			and il.adresse_defaut_o_n='1'
ORDER BY ACOS( SIN( RADIANS( l.latitude ) ) * SIN( RADIANS( $lat ) ) + COS( RADIANS(l.latitude) )
* COS( RADIANS( $lat )) * COS( RADIANS( l.longitude ) - RADIANS( $long )) ) * 6380 
	";}
	else 
		{
			$sql="
			select il.id_individu,
			FORMAT(ACOS( SIN( RADIANS( l.latitude ) ) * SIN( RADIANS( $lat ) ) + COS( RADIANS(l.latitude) )
			* COS( RADIANS( $lat )) * COS( RADIANS( l.longitude ) - RADIANS( $long )) ) * 6380 , 3) AS distance,
			FORMAT(l.longitude ,7) AS longitude,
			FORMAT( l.latitude,7) AS latitude
		
			FROM lieu l, individu_lieu il
			WHERE
			 ACOS( SIN( RADIANS( l.latitude ) ) * SIN( RADIANS( $lat ) ) + COS( RADIANS(l.latitude) )
			* COS( RADIANS( $lat )) * COS( RADIANS( l.longitude ) - RADIANS( $long )) ) * 6380 < 50
			and  l.longitude is not null
			and l.id = il.id_lieu
			and il.adresse_defaut_o_n='1'
			ORDER BY ACOS( SIN( RADIANS( l.latitude ) ) * SIN( RADIANS( $lat ) ) + COS( RADIANS(l.latitude) )
			* COS( RADIANS( $lat )) * COS( RADIANS( l.longitude ) - RADIANS( $long )) ) * 6380
			";}
//	$this->p($sql);
	$data = $db->getrows($sql);
	$res2.= '<br/>';
	$res2.= '<table class="toc  sortable">';
	$res2.='<thead>';
	$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
	// <img src="http://maps.googleapis.com/maps/api/staticmap?center=-15.800513,-47.91378&zoom=11&size=200x200&sensor=false">
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Individu</center></b>';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Distance</center></b>';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Localisation</center></b>';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Zoom</center></b>';
	$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Street view</center></b>';
	$res2.='</th></tr>';
	$res2.='</thead>';
	$res2.='<tbody>';
	$res1='<img src="http://maps.google.com/maps/api/staticmap?center='.$lat.','.$long.'&zoom=14&size=500x500&maptype=hybrid
			';
	$idindividus="";
	for ($i = 0; $i < count($data); $i++) {

		$res2.= "<tr><td>".(++$i);
		$res2.='</td><td>'.$this->descripteur_individu($data[$i]["id_individu"],'n','n','0','menu');
		$res2.='</td><td style="text-align:right;"><b>'.$data[$i]["distance"].'</b>';
		$res2.='</td><td>';
		$res2.='</td><td>';
		$res2.='</td><td>';
/*		$res2.='</td><td><img src="http://maps.googleapis.com/maps/api/staticmap?center='.$data[$i]["latitude"].','.$data[$i]["longitude"].'&zoom=10&size=200x200
				&maptype=hybrid&markers=color:red%7Ccolor:red%7Clabel:S%7C'.$data[$i]["latitude"].','.$data[$i]["longitude"].'&key='.$this->get_map_key().'&sensor=false">';
		$res2.='</td><td><img src="http://maps.googleapis.com/maps/api/staticmap?center='.$data[$i]["latitude"].','.$data[$i]["longitude"].'&zoom=16&size=200x200
				&maptype=hybrid&markers=color:red%7Ccolor:red%7Clabel:S%7C'.$data[$i]["latitude"].','.$data[$i]["longitude"].'&key='.$this->get_map_key().'&sensor=false">';
		$res2.='</td><td><img src="http://maps.googleapis.com/maps/api/streetview?size=200x200&location='.$data[$i]["latitude"].','.$data[$i]["longitude"].'&heading=235&key='.$this->get_map_key().'&sensor=false">';
*/
				$res2.='</td></tr>';
		$idindividus .= $data[$i]["id_individu"] . ',';
		
//		$res1.='&markers=color:red%7Ccolor:red%7Clabel:S%7C'.$data[$i]["latitude"].','.$data[$i]["longitude"];
	}

	$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
	$idindividus=str_replace("'","",$idindividus);
	$this->m_postvars["idindividus"]=$idindividus;
	$this->m_postvars["adresses_actives_o_n"]="o";
	$this->m_postvars["renvoi_resultat_o_n"]="o";
//	$res3="<br/>".$this->action_mapindividus();



	$res1.='&markers=color:red%7Ccolor:red%7Clabel:S%7C'.$lat.','.$long;
	$res1.='&key='.$this->get_map_key().'&sensor=true" width="500" height="500" alt="'.$geodata['formatted_address'].'" \/><br /><br />';
	$res1.= '<br/>';

	$res2.='</tbody>';
	$res2.='</table>';
	$title=null;
	$flags=null;
	$extra_body=null;
	$extra_header=null;
	$this->page_output($res1.$res2,$title,$flags,$extra_body,$extra_header);
	
}
	
}

	function action_googlemap() {
		$idorganisme = $this->m_postvars["id"];
		$user = getUser();
		$iduser = $user["id"];
		if ($idorganisme == 0) {
			$selectmaporganisme = "SELECT o.id as identity, l.id as idlieu, o.nom as nom, ' ' as prenom ,o.courriel as courriel,o.site_internet as site_internet, o.telephone as telephone_fixe,l.longitude as longitude
																																																								   		, l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, 
																																																								   		p.libelle_anglais as pays 
																																																								   		 from 
																																																								organisme o 
																																																								left join organisme_lieu ol on o.id=ol.id_organisme
																																																								 left join  lieu l on ol.id_lieu=l.id
																																																								left join type_cp_ville_pays c on  l.id_ville =c.id
																																																								left join type_pays p on p.id=c.id_pays 
																																																								
																																																								   		 
																																																								   		order by nom, prenom";
		} else {
			$selectmaporganisme = "SELECT o.id as identity, l.id as idlieu, o.nom as nom, ' ' as prenom ,o.courriel as courriel,o.site_internet as site_internet, o.telephone as telephone_fixe,l.longitude as longitude" . ", l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" . " from organisme o
																																																								left join organisme_lieu ol on o.id=ol.id_organisme
																																																								 left join  lieu l on ol.id_lieu=l.id
																																																								left join type_cp_ville_pays c on  l.id_ville =c.id
																																																								left join type_pays p on p.id=c.id_pays " . " where  o.id=" . $idorganisme . " " . "order by nom, prenom";
		}
		return $this->createMarkers($selectmaporganisme, "organisme");
	}
	function action_mapindividus() {
		$idindividus = $this->m_postvars["idindividus"];
		$adresses_actives_o_n=$this->m_postvars["adresses_actives_o_n"];
		$user = getUser();
		$iduser = $user["id"];
		$selectmapinscrits = "SELECT l.id as idlieu, i.id as identity, i.nom as nom, i.prenom as prenom , i.id_document_portrait as id_document_portrait, 
		i.courriel as courriel,i.site_internet as site_internet, i.telephone_fixe as telephone_fixe,i.telephone_mobile as telephone_mobile, l.longitude as longitude" . ", 
		l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" .
		 " from " . "individu i left join individu_lieu il on i.id=il.id_individu
			 left join  lieu l on il.id_lieu=l.id
			left join type_cp_ville_pays c on  l.id_ville =c.id
			left join type_pays p on p.id=c.id_pays " . " 
			where";
		if ($adresses_actives_o_n=='o')
		{
			$selectmapinscrits.="	(il.adresse_defaut_o_n='1' or il.adresse_personnelle_o_n='1') AND (i.id in ( " . $idindividus . " ) )" . "order by nom, prenom";
		}
		else
		{
			$selectmapinscrits.="	 (i.id in ( " . $idindividus . " ) or i.id in (select id_individu from app_utilisateur where id=$iduser))" . "order by nom, prenom";
		}
//		$this->p($selectmapinscrits);
		return $this->createMarkers($selectmapinscrits, "individu");
	}
	function createMarkers($select, $type) {
		/*
		 * <?php
include_once(moduleDir("utils") ."GoogleMap.php");
include_once(moduleDir("utils") ."JSMin.php");

$map = new GoogleMapAPI(); 
$map->_minify_js = isset($_REQUEST["min"])?FALSE:TRUE;
$map->setDSN("mysql://user:password@localhost/db_name");
$map->addMarkerByAddress("Denver, CO","Marker Title", "Marker Description");
$map->addMarkerByAddress("Los Angeles, CA","Marker2 Title", "Marker2 Description");
?>
<html>
<head>
<?=$map->getHeaderJS();?>
<?=$map->getMapJS();?>
</head>
<body>
<?=$map->printOnLoad();?> 
<?=$map->printMap();?>
<?=$map->printSidebar();?>
</body>
</html>
		 */
//		include_once (moduleDir("utils") . "class.googlemapapi.inc");
include_once(moduleDir("utils") ."GoogleMap.php");
include_once(moduleDir("utils") ."JSMin.php");
		$map = new GoogleMapAPI('map', 'association_map');
		 $map->_minify_js = isset($_REQUEST["min"])?FALSE:TRUE;
$map->setDSN("mysql://user:password@localhost/db_name");
//		$map->setAPIKey($this->get_map_key());
		$map->setHeight("800");
		$map->setWidth("1500");
		//$map->disableTypeControls();
		$map->setMapType('hybrid'); // default
		//$map->disableDirections();
		$map->enableZoomEncompass();
		$map->enableOverviewControl();
		$db = & atkGetDb();
		$r = $db->getrows("$select");
		$user = getUser();
		$iduser = $user["id"];
		/*
		$selectutilisateur = "SELECT l.id as idlieu, i.id as identity ,i.nom as nom, i.prenom as prenom ,i.courriel as courriel , i.site_internet as site_internet,
		 i.telephone_fixe as telephone_fixe,i.telephone_mobile as telephone_mobile, l.longitude as longitude" . ", l.latitude as latitude, l.adresse1 as adresse1 ,
		  l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" . " 
		  from " . "individu i left join individu_lieu il on i.id=il.id_individu
		left join  lieu l on il.id_lieu=l.id
				left join type_cp_ville_pays c on  l.id_ville =c.id
			left join type_pays p on p.id=c.id_pays " . " 
			where  il.adresse_defaut_o_n='1' and i.id in (select id_individu from app_utilisateur where id=$iduser)" . "";
		$rutilisateur = $db->getrows("$selectutilisateur");
		// TODO:  Traiter la photo;
		$site = atkHost();
		$urlsite = 'http://' . $site;
		$sitesanswww = substr_replace($site, '', 0, 4);
		$photosdir = atkconfig("photosdir");
		$i = count($r);
		for ($j = 0; $j < count($rutilisateur); $j++) {
			$r[$i]['code_postal'] = $rutilisateur[$j]['code_postal'];
			$r[$i]['ville'] = $rutilisateur[$j]['ville'];
			$r[$i]['province_etat'] = $rutilisateur[$j]['province_etat'];
			$r[$i]['pays'] = $rutilisateur[$j]['pays'];
			$r[$i]['longitude'] = $rutilisateur[$j]['longitude'];
			$r[$i]['latitude'] = $rutilisateur[$j]['latitude'];
			$r[$i]['adresse1'] = $rutilisateur[$j]['adresse1'];
			$r[$i]['nom'] = $rutilisateur[$j]['nom'];
			$r[$i]['prenom'] = $rutilisateur[$j]['prenom'];
		}
		*/
		$missing = 0;
		$missingnoms = "";
		$missingadresse = 0;
		$missingadressenoms = "";
		for ($i = 0; $i < count($r); $i++) {
			$address = $r[$i]['adresse1'] . ", " . $r[$i]['code_postal'] . ", " . $r[$i]['ville'] . ", " . $r[$i]['pays'];
			if ($type == "organisme") {
				$html = "<a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>" . "<br />" . $r[$i]['adresse1'] . "<br />" . $r[$i]['code_postal'] . " " . $r[$i]['ville'] . "<br />" . $r[$i]['pays'] . "<br /><a href=\"mailto:" . $r[$i]['courriel'] . "\">" . $r[$i]['courriel'] . "</a><br /><a href=\"" . $r[$i]['site_internet'] . "\">" . $r[$i]['site_internet'] . "</a><br />" . $r[$i]['telephone_fixe'];
			} else {
				$idportrait = $r[$i]['id_document_portrait'];
				if (isset ($idportrait) || $idportrait != 0) {
					$sqlp = "select id, file_extension,file_content, file_size from organisme_document
																					 where id=" . $idportrait . "";
					$dataphoto = $db->getrows($sqlp);
					$filename = ".." . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'];
					$file = @ fopen($filename, "w");
					@ fwrite($file, base64_decode($dataphoto[0]["file_content"]));
					@ fclose($file);
					$urlphotozone = "http://" . $sitesanswww . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'] . "";
					//				$htmlphoto = '<b><a href="' . $urlsite . '"> <img src="' . $urlphotozone . '"></a> </b><br />';
	//				$htmlphoto = '<b><a href=""> <img src="' . $urlphotozone . '"></a> </b><br />';
					$htmlphoto = '';
				} else {
					$htmlphoto = '';
				}
				$html = "<a href='dispatch.php?atknodetype=individu.individu&atkaction=edit&atkselector=individu.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>" . "<br />" . $r[$i]['adresse1'] . "<br />" . $r[$i]['code_postal'] . " " . $r[$i]['ville'] . "<br />" . $r[$i]['pays'] . "<br /><a href=\"mailto:" . $r[$i]['courriel'] . "\">" . $r[$i]['courriel'] . "</a><br /><a href=\"" . $r[$i]['site_internet'] . "\">" . $r[$i]['site_internet'] . "</a><br />" . $r[$i]['telephone_fixe'] . "</a><br />" . $r[$i]['telephone_mobile'] . "</a><br />" . $htmlphoto;
			}
			$title = $r[$i]['nom'] . " " . $r[$i]['prenom']."<br/>";
			$longitude = $r[$i]['longitude'];
			$latitude = $r[$i]['latitude'];
			$idlieu = $r[$i]['idlieu'];
			if (!isset ($r[$i]['code_postal'])) {
				$missingadresse = $missingadresse +1;
				if ($type == "organisme") {
					$missingadressenoms .= "<br /><a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
				} else {
					$missingadressenoms .= "<br /><a href='dispatch.php?atknodetype=individu.individu&atkaction=edit&atkselector=individu.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
				}
			} else {
				if (!isset ($longitude)) {
					$coords = array ();
					$coords = $map->geoGetCoords($address);
					$map->putCache($idlieu, $coords["lon"], $coords["lat"]);
					$longitude = $coords["lon"];
					$latitude = $coords["lat"];
				}
				if (!isset ($longitude) or !isset ($latitude)) {
					$missing = $missing +1;
					$missingnoms .= "<br /><a href='dispatch.php?atknodetype=individu.lieu&atkaction=edit&atkselector=lieu.id=" . $r[$i]['idlieu'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
				} else {
				
					$map->addMarkerByCoords($longitude, $latitude, $title, $html);
				}
			}
		}
		
/*		$output = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
		$output .= "<html xmlns=\"http://www.w3.org/1999/xhtml\" xmlns:v=\"urn:schemas-microsoft-com:vml\">";
		$output .= "<head>";
		$output .= $map->printHeaderJS();
		$output .= $map->printMapJS();
		//  <!-- necessary for google maps polyline drawing in IE -->
		$output .= "<style type=\"text/css\">";
		$output .= "v\:* {";
		$output .= "    behavior:url(#default#VML);";
		$output .= "}";
		$output .= "</style>";
		$output .= "</head>";
		*/
		$output .= "<head>";
		$output .= $map->printHeaderJS();
		$output .= $map->printMapJS();
		$output .= "</head>";


		$output_body= $map->printOnLoad();
		$output_body .= $map->printMap();
		$output_body .= $map->printSidebar();
		$output_body .= "<font face=\"arial\" size=\"1\" color=\"red\">";
		$output_body .= $missing . " : non géolocalisables";
		$output_body .= $missingnoms;
		$output_body .= "<br />" . $missingadresse . " : sans adresse";
		$output_body .= $missingadressenoms."</font>";
		$output .= $output_body;
		
		if ($this->m_postvars["renvoi_resultat_o_n"]=="o")
		{ return $output_body;}
		else {
			$output1 = & atkOutput :: getInstance();
		$output1->rawoutput($output);
		$output1->outputFlush();}
	}
	function postAdd(&$record)
	{
		$id_entite=$record["id"];
		$this->RecentUseProcess('organisme', $id_entite);

	}

	function preDelete(&$record)

	{
		$id_entite=$record["id"];
		$this->RecentUseDelete('organisme', $id_entite);
		return true;
	}
	function validate(& $record, $mode) {
		$record["telephone"] = normalisation_telephone($record["telephone"]);
		parent::validate($record, $mode);

	}
	function action_admin($handler) {
		if  (substr($this->m_postvars["atkfilter"],0,5) =="'%@@@")
		{      $searchfields = array("nom","sigle");
		$searchvalue=$this->m_postvars["atkfilter"];
		$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
		$filter = $this->createSearchFilter($searchfields, $searchvalue,$this->table);

		$this->m_postvars["atkfilter"]=$filter;
		}
		$this->addFilter($this->m_postvars["atkfilter"]);
		return $handler->action_admin();
	}
function action_travaux($handler) {
	$db = & atkGetDb();
	global  $g_sessionManager;
	
		if  ( $this->m_postvars["atktravaux"]=="debut")
		{
			$sql="UPDATE app_globales set en_travaux_o_n='1' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("en_travaux_o_n", '1', true);
			$mes="Le signal travaux a été activé";
		}
		if  ( $this->m_postvars["atktravaux"]=="fin")
		{
			$sql="UPDATE app_globales set en_travaux_o_n='0' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("en_travaux_o_n", '0', true);
			$mes="Le signal travaux a été désactivé";
		}
		$href='menu.php?atkmenutop='.$this->m_postvars["atkmenutop"];
		header("Location: $href");
		exit;
		
	}
	function action_debugging($handler) {
		$db = & atkGetDb();
		global $g_sessionManager;
//	$this->p(m_postvars);
		if  ( $this->m_postvars["atkdebugging"]=="debut")
		{
			$sql="UPDATE app_globales set debug_o_n='1' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("debug_o_n", "1", true);
/*				
			$GLOBALS["debuglevel"]='3';
			$mes="Le debugging niveau 3 a été activé";
			*/
		}
		if  ( $this->m_postvars["atkdebugging"]=="fin")
		{
			$sql="UPDATE app_globales set debug_o_n='0' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("debug_o_n", "0", true);
			/*
			$GLOBALS["debuglevel"]='-1';
			$mes="Le debugging niveau 3 a été désactivé";
			*/
		}
		$href='menu.php?atkmenutop='.$this->m_postvars["atkmenutop"];
		header("Location: $href");
		exit;
	//	echo $mes;
	//	die();
	
	}
	
	// global $g_debug_level;
//	$g_debug_level=-1;
	
	
function action_tracer_mysqldb($handler) {
	$db = & atkGetDb();
	global  $g_sessionManager;
	
		if  ( $this->m_postvars["atktracer_mysqldb"]=="debut")
		{
			$sql="UPDATE app_globales set tracer_mysqldb_query_o_n='1' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("tracer_mysqldb_query_o_n", '1', true);
			$mes="La trace des appels Sql a été activée";
		}
		if  ( $this->m_postvars["atktracer_mysqldb"]=="fin")
		{
			$sql="UPDATE app_globales set tracer_mysqldb_query_o_n='0' where id =1";
			$db->query($sql);
			$g_sessionManager->globalVar("tracer_mysqldb_query_o_n", '0', true);
			$mes="La trace des appels Sql a été désactivée";
		}
		$href='menu.php?atkmenutop='.$this->m_postvars["atkmenutop"];
		header("Location: $href");
		exit;
	}
	
	function action_rafraichir_calendrier_rencontres ()
	{
		$messagecalendrier='';
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_AuthSub');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Gdata_HttpClient');
		Zend_Loader::loadClass('Zend_Gdata_Calendar');
		$_authSubKeyFile = null; // Example value for secure use: 'mykey.pem'
		$_authSubKeyFilePassphrase = null;
		$service = Zend_Gdata_Calendar::AUTH_SERVICE_NAME;

		foreach ($select as $id_variable) {
			$nombreevents=0;
			$nombredelete=0;
			$id_organisme = explode('=', $id_variable);
			$id_organisme1 = $id_organisme[1];
			$sql='SELECT calendrier_rencontres_nom, identifiant_google, code_google, tz_offset_google, calendrier_rencontres_uri
			from organisme
		where id='.$id_organisme1.'  ';
			$data=$db->getrows($sql);
			$user=$data[0]["identifiant_google"];
			$nomcalendrier=$data[0]["calendrier_rencontres_nom"];
			$pass=$data[0]["code_google"];
			//			$tzOffset=$data[0]["tz_offset_google"];
			$tzOffset=substr($data[0]["tz_offset_google"],0,strlen($data[0]["tz_offset_google"])-2);
			if (strlen($tzOffset)!=3)
			{
				echo 'Time Zone organisme non correct';
				die();
			}
			$uri=$data[0]["calendrier_rencontres_uri"];
			$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);

			// supprimer les éléments
			$maxresults=20;
			$gdataCal = new Zend_Gdata_Calendar($client);
			$query = $gdataCal->newEventQuery();
			$query->setUser($uri);
			$query->setVisibility('private');
			$query->setProjection('full');
			$query->setOrderby('starttime');
			$query->setFutureevents(false);
			$query->setMaxResults($maxresults);
			$eventFeed = $gdataCal->getCalendarEventFeed($query);
			$nbevents=0;
			$rdv=true	;
			while ($rdv==true)
			{$eventFeed = $gdataCal->getCalendarEventFeed($query);
			$nbevents=0;

			foreach ($eventFeed as $event) {
					
				$event->delete();
				$nombredelete+=1;
				$nbevents+=1;}


				if ($nbevents<$maxresults)
				{
					$rdv=false;
				}
			}


			/*				 echo "<ul>\n";
			 foreach ($eventFeed as $event) {
			 echo "\t<li>" . $event->title->text .  " (" . $event->id->text . ")\n";
			 // Zend_Gdata_App_Extensions_Title->__toString() is defined, so the
			 // following will also work on PHP >= 5.2.0
			 //echo "\t<li>" . $event->title .  " (" . $event->id . ")\n";
			 echo "\t\t<ul>\n";
			 foreach ($event->when as $when) {
			 echo "\t\t\t<li>Starts: " . $when->startTime . "</li>\n";
			 }
			 echo "\t\t</ul>\n";
			 echo "\t</li>\n";
			 }
			 */


			$debut=date("Y-m-d", mktime(0,0,0,date("m")-3,date("d"),date("Y")));
			$sql="
			  SELECT id from  organisme_rencontre ore WHERE ore.id_organisme=".$id_organisme1." 
			    and ore.date_debut>='".$debut."'  ORDER by ore.date_debut ";
			$data=$db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$sql="SELECT
						ore.libelle,
						ore.id_organisme,
						o.nom,
						o.telephone,
						ore.id_lieu_rencontre,
						ore.id_groupe_travail,
						ore.date_debut,
						ore.heure_debut,
						ore.date_fin, 
						ore.heure_fin,
						ore.commentaire
						FROM 
						organisme_rencontre ore, organisme o
						where ore.id=".$data[$i]["id"]." and ore.id_organisme=o.id
						";	
				$rencontre=$db->getrows($sql);
				// Create a new entry using the calendar service's magic factory method
				$service = new Zend_Gdata_Calendar($client);
				$event= $service->newEventEntry();
				// Populate the event with the desired information
				// Note that each attribute is crated as an instance of a matching class
				//				   $value = atk_iconv(atktext("charset"),"UTF-8",$rencontre[0]["libelle"]);
				$adresse="";
				$lieu_latlon="";
				if ($rencontre[0]["id_lieu_rencontre"]!="")
				{

					$query = & $db->createQuery();
					$query->addTable("organisme_lieu_rencontre");
					$query->addJoin("lieu", "", "organisme_lieu_rencontre.id_lieu = lieu.id", false);
					$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
					$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
					$query->addField("organisme_lieu_rencontre.libelle as libelle");
					$query->addField("lieu.adresse1 as adresse1");
					$query->addField("lieu.longitude as longitude");
					$query->addField("lieu.latitude as latitude");
					$query->addField("type_cp_ville_pays.code_postal as code_postal");
					$query->addField("type_cp_ville_pays.ville as ville");
					$query->addField("type_cp_ville_pays.province_etat as province");
					$query->addField("type_pays.libelle_anglais as pays");
					$query->addCondition("organisme_lieu_rencontre.id=".$rencontre[0]["id_lieu_rencontre"]);
					$sql = $query->buildSelect();
					$stuff = $db->getrows($sql);
					if ($stuff[0]["latitude"]!="");
					{
						//				$stuff[0]["latitude"]=substr($stuff[0]["latitude"],0, strlen($stuff[0]["latitude"])-6).'.'.substr($stuff[0]["latitude"],strlen($stuff[0]["latitude"])-6,6);
						//					$stuff[0]["longitude"]=substr($stuff[0]["longitude"],0, strlen($stuff[0]["longitude"])-6).'.'.substr($stuff[0]["longitude"],strlen($stuff[0]["longitude"])-6,6);
						$lieu_latlon=$stuff[0]["latitude"].",".$stuff[0]["longitude"];
					}
					$adresse="<b>Lieu de la rencontre : </b>".$stuff[0]["libelle"]."<br />".$stuff[0]["adresse1"]." - ".$stuff[0]["code_postal"]." - ".$stuff[0]["ville"]." - ".$stuff[0]["province"]." - ".$stuff[0]["pays"];
				}
					
					
				$query = & $db->createQuery();
				$query->addTable("individu_rencontre");
				$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_rencontre.id_organisme_participant = organisme.id", true);
				$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.telephone_fixe as telephone");
				$query->addField("organisme.nom as organisme_participant");
				$query->addField("type_rencontre_participation.libelle as participation");
				$query->addField("individu_rencontre.commentaire as commentaire");
				$query->addCondition("individu_rencontre.id_rencontre=".$data[$i]["id"]);
				$query->addOrderBy(" type_rencontre_participation.libelle, individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);

				$datatbl = array ();

				for ($j = 0; $j< count($stuff); $j++) {
					$row = array ();
					$row[] = $j +1;


					$row[] = $stuff[$j]["nom"];
					$row[] = $stuff[$j]["prenom"];
					$row[] = $stuff[$j]["telephone"];
					$row[] = $stuff[$j]["organisme_participant"];
					$row[] = $stuff[$j]["commentaire"];
					$row[] = $stuff[$j]["participation"];
					$datatbl[] = $row;
				}
				$tbl = & atknew("atk.utils.atktablerenderer");
				$res = $tbl->render($datatbl, 0, "recordlist");


					
					
				$event->title = $service->newTitle(atk_iconv(atktext("charset"),"UTF-8",$rencontre[0]["libelle"]));
				if ($lieu_latlon!="")
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$lieu_latlon)));}
				else
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$adresse)));}

				$event->content =$service->newContent(atk_iconv(atktext("charset"),"UTF-8",'<b>Organisme : </b>'.$rencontre[0]["nom"].' '.$rencontre[0]["telephone"].'<br />'.$adresse.'<br />'.'<b>Participants : </b>'.'<br />'.$res));
				// Set the date using RFC 3339 format.
				$startDate = $rencontre[0]["date_debut"];
				$startTime = substr($rencontre[0]["heure_debut"], 0,5);
				$endDate = $rencontre[0]["date_fin"];
				$endTime = substr($rencontre[0]["heure_fin"],0,5);
				$when = $service->newWhen();
				$when->startTime = "{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				$when->endTime = "{$endDate}T{$endTime}:00.000{$tzOffset}:00";
				$event->when = array($when);
				// Upload the event to the calendar server
				// A copy of the event as it is recorded on the server is returned
				$caluri='http://www.google.com/calendar/feeds/'.$uri.'/private/full';

				//				 echo "{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				//			 die();

					
				$newEvent = $service->insertEvent($event, $caluri);
				$nombreevents+=1;

				/*		$idrencontre=$data[$i]["id"];
				 $sql="INSERT
				 INTO
				 organisme_calendrier_element
				 ( id_calendrier, id_google, id_rencontre,commentaire, id_creation, date_creation, id_modification, date_modification)
				 VALUES
				 ( $id_calendrier1,
				 '$idgoogle',
				 '$idrencontre',
				 '',
				 '$userid',
				 UTC_TIMESTAMP(),
				 '$userid',
				 UTC_TIMESTAMP())
				 ";
				 $db->query($sql);
				 */
				//				echo $newEvent;
				//				echo '<br />';


			}
			$sql="UPDATE organisme
		SET id_modification='$userid', date_modification=UTC_TIMESTAMP(), calendrier_rencontres_refresh=UTC_TIMESTAMP() where id=$id_organisme1
						";
			$db->query($sql);
			$messagecalendrier.=' Calendrier : '.$nomcalendrier.' mis à jour. '.$nombreevents.' évènements ont été créés. '.$nombredelete.' évènements ont été supprimés. ';

		}
		$messagefin=" Mises à jour effectuées<br />".$messagecalendrier;
		//        echo $messagefin;
		//        die();
			
		$this->setFeedback("rafraichir_calendrier_rencontres",ACTION_SUCCESS);
		$location = $this->feedbackUrl("rafraichir_calendrier_rencontres", ACTION_SUCCESS, "", $messagefin);
		$this->redirect($location);
			

	}
	function getGolfIndex($licence,$index,$datValidite)
	{
		
	}
}
?>