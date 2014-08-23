<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
class domaine extends assMetaNode {
	var $table = "organisme_domaine";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "identifiant_registrar", "mot_de_passe_registrar", "caracteristiques_hebergement", "identifiant_hebergement", "mot_de_passe_hebergement", "serveur_mysql", "identifiant_mysql", "mot_de_passe_mysql", "serveur_ftp", "identifiant_ftp", "mot_de_passe_ftp", "serveur_mail", "identifiant_mail", "mot_de_passe_mail", "commentaire_registrar", "commentaire_hebergement", "commentaire_mysql", "commentaire_ftp", "commentaire_mail", AF_HIDE_LIST);
	}
	function domaine() {
		$this->atkMetaNode();
		$this->atkNode("domaine",  NF_ADD_LINK | NF_TRACK_CHANGES | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id_organisme",
						"libelle",
						"nom_domaine",
						"google_apps_o_n",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Registrar" => array (
						"id_organisme_registrar",
						"date_registrar_debut",
						"date_registrar_fin",
						"url_administration_registrar",
						"identifiant_registrar",
						"mot_de_passe_registrar",
						"cout_registrar",
						"commentaire_registrar"
				),
				"Hébergement" => array (
						"id_organisme_hebergement",
						"date_contrat_debut_hebergement",
						"date_contrat_fin_hebergement",
						"caracteristiques_hebergement",
						"url_administration_hebergement",
						"identifiant_hebergement",
						"mot_de_passe_hebergement",
						"cout_hebergement",
						"commentaire_hebergement"
				),
				"Base de données" => array (
						"serveur_mysql",
						"url_administration_mysql",
						"identifiant_mysql",
						"mot_de_passe_mysql",
						"commentaire_mysql"
				),
				"Ftp" => array (
						"serveur_ftp",
						"url_administration_ftp",
						"identifiant_ftp",
						"mot_de_passe_ftp",
						"commentaire_ftp"
				),
				"Mail" => array (
						"serveur_mail",
						"url_administration_mail",
						"identifiant_mail",
						"mot_de_passe_mail",
						"commentaire_mail"
				)
		), AF_NO_LABEL));
		//	$this->setSecurityAlias("profil.profil");
		$this->add(new atkDummyAttribute("descripteur_domaine_internet",0,AF_HIDE_EDIT | AF_COMPACT ),3);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE|AF_FORCE_LOAD));
		$this->add(new atkBoolAttribute("google_apps_o_n"));
		$this->add(new atkDateAttribute("date_creation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_READONLY|AF_FORCE_LOAD));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atgOManyToOneRelation("id_organisme_registrar", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new 		atgOManyToOneRelation		("id_organisme_hebergement", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD));
		$this->add(new atkUrlAttribute("url_administration_registrar", AF_POPUP));
		$this->add(new atkUrlAttribute("url_administration_hebergement", AF_POPUP));
		$this->add(new atkUrlAttribute("url_administration_mysql", AF_POPUP));
		$this->add(new atkUrlAttribute("url_administration_ftp", AF_POPUP));
		$this->add(new atkUrlAttribute("url_administration_mail", AF_POPUP));
		$this->add(new atkfckattribute("caracteristiques_hebergement", "", AF_HIDE_LIST, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '150px'
		)));
		$this->add(new atkDateAttribute("date_registrar_debut", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING|AF_FORCE_LOAD));
		$this->add(new atkDateAttribute("date_registrar_fin", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING|AF_FORCE_LOAD));
		$this->add(new atkDateAttribute("date_contrat_debut_hebergement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_contrat_fin_hebergement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkNumberAttribute("cout_registrar", AF_SEARCHABLE, 10, 2));
		$this->add(new atkNumberAttribute("cout_hebergement", AF_SEARCHABLE, 10, 2));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,4 );
		$this->setOrder(" organisme_domaine.date_creation DESC ");
		//		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_registrar_display($record, $mode) {
		(!empty($record["id_organisme_registrar"])) ? $retour=$this->descripteur_organisme($record["id_organisme_registrar"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_hebergement_display($record, $mode) {
		(!empty($record["id_organisme_hebergement_registrar"])) ? $retour=$this->descripteur_organisme($record["id_organisme_hebergement"]["id"],'n') : $retour="";
		return $retour;
	}
	function descripteur_domaine_internet_display($record, $mode)
	{
		$id_domaine=trim($record["id"]);

		return $descripteur=$this->decoupe_affichage_colonne($this->descripteur_domaine_internet($id_domaine,"o"), 100);
	}

}
?>