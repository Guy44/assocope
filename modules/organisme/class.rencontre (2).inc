<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgNumberExpressionAttribute");
atkimport("modules.scheduler.utils.schedulertools");
useattrib("scheduler.dummydurationfattribute");
class rencontre extends assMetaNode {
	var $table = "organisme_rencontre";
	var $m_minute_step = 5;
	var $m_resultats_suppression="";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("preparation", "audience", "programme", "communique_presse", "imprime_inscription", "conclusion", "lieu_texte", "commentaire", AF_HIDE_LIST);
		$policy->addFlags("conclusion","preparation", "communique_presse" , "programme","audience",AF_FORCE_LOAD);
	}
	function rencontre() {
		$time = "09:00";
		$user_eventtime="09";
		for($i=0;$i<60;$i+=$this->m_minute_step)
		{
			$m_arr_minute_step[] = sprintf("%02d",$i);
		}
		if ($time!="")
		{
			$default_start_time = $time; // passed from the url.
			$default_end_time = strftime("%H:%M", mktime(substr($time,0,2), substr($time,3,2)+$user_eventtime)); // endtime is half an hour later than starttime by default
		}
		else
		{
			$default_start_time = strftime("%H:%M");
			$default_end_time = strftime("%H:%M", mktime(substr($default_start_time,0,2),substr($default_start_time,3,2)+$user_eventtime));
		}

		$this->atkMetaNode();
		$this->atkNode("rencontre", NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA | NF_COMPACT );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array ("id",
						"id_organisme",
						"id_groupe_travail",
						"libelle",
						"descripteur_rencontre",
						"descripteur_rencontre_documents",
						"descripteur_rencontre_fournisseurs",
						"id_type_rencontre",
						"date_debut",
						"heure_debut",
						//		"duration",
						"date_fin",
						"heure_fin",
						"date_cloture",
						"id_lieu_rencontre",
						"lieu_texte",
						"libelle_participation_1",
						"libelle_participation_2",
						"libelle_participation_3",
						"libelle_participation_4",
						"options",
						"tous_les_choix",
						"nombre",
						"montant_participation_adherent",
						"montant_participation_accompagnant",
						"montant_depense_totale",
						"montant_recette_non_nominative",
						"ecritures",

						"id_ecriture_participation",
						"id_ecriture_reglement",
		//				"participations_partielles",
		//				"participations_completes",
		//				"total_versements",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Audience" => array (
						"audience",
						"id_type_audience"
				),
				"Communication" => array (
						"communique_presse",
						"id_document_communication",
						"url_communication",
						"communications"
				),

				"Conclusion" => array (
						"conclusion",
						"id_compte_rendu",
						"url_compte_rendu"
				),
				/*				"Covoiturage" => array (
				 "places_offertes",
						"places_demandees"
				),
		*/

				"Emargement" => array (
						"id_document_emargement"
				),
				"Formulaire_inscription" => array (
						"id_document_inscription",
						"url_inscription"
				),
		"Choix" => array (
				 "choix"
				),
				/*			"Fournisseurs" => array (
				 "fournisseurs"
				),
				


		"Participants" => array (
				"inscrire_rencontre",
				"participants"
		),
		*/
				"Golf_Competition" => array (
						"id_organisme_parcours",
						"an_championnat" ,
						"numero_rencontre_championnat" ,
						"forcer_couleur_depart_o_n",
						"generer_carte_o_n",
						"saisir_score_trou_o_n",
						"cheque_1_motif",
						"cheque_1_montant",
						"cheque_1_ordre",
						"cheque_2_motif",
						"cheque_2_montant",
						"cheque_2_ordre",
						"frais_de_jeu",
						"ssj"	),
				"Préparation" => array (
						"preparation",
						"id_document_preparation",
						"url_preparation"
				),
				"Programme" => array (
						"programme",
						"id_document_programme"
						,"url_programme"
				)
		), AF_NO_LABEL));
		$this->add(new atkAttribute("id",0,AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD));
		$this->add(new atkDummyAttribute("descripteur_rencontre","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD|AF_COMPACT),NULL,10);
		$this->add(new atkDummyAttribute("descripteur_rencontre_documents","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD|AF_COMPACT),NULL,14);
		$this->add(new atkDummyAttribute("descripteur_rencontre_fournisseurs","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD|AF_COMPACT),NULL,15);

		/*		$this->add(new atkDummyAttribute("descripteur_rencontre",0,AF_COMPACT),NULL,10);
		 $this->add(new atkDummyAttribute("descripteur_rencontre_documents",0,AF_COMPACT),NULL,11);
		$this->add(new atkDummyAttribute("descripteur_rencontre_fournisseurs",0,AF_COMPACT),NULL,12);
		*/
		$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from individu_rencontre
				where id_rencontre =[table].id
				', 0, 0),201);
		$this->add(new atkDummyAttribute("ecritures"));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY), null, 95);
		$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.lieu_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD), null,96);

		$this->add(new atgTextLibelleAttribute("lieu_texte",0,100),null,97);
		$this->add(new atgTextLibelleAttribute("libelle_participation_1",0,20),null,98);
		$this->add(new atgTextLibelleAttribute("libelle_participation_2",0,20),null,99);
		$this->add(new atgTextLibelleAttribute("libelle_participation_3",0,20),null,100);
		$this->add(new atgTextLibelleAttribute("libelle_participation_4",0,20),null,101);
		$this->add(new atgNoStorageAttribute("options",AF_COMPACT,0),NULL,12);
		$this->add(new atgNoStorageAttribute("tous_les_choix",AF_COMPACT,0),NULL,11);
/*
		$this->add(new atgNumberExpressionAttribute("participations_partielles", ' select sum(participation_partielle) from individu_rencontre
				where id_rencontre =[table].id
				', null, 102));
		$this->add(new atgNumberExpressionAttribute("participations_completes", ' select sum(participation_complete) from individu_rencontre
				where id_rencontre =[table].id
				', null, 103));
		$this->add(new atgNumberExpressionAttribute("total_versements", ' select sum(montant_versement) from individu_rencontre
				where id_rencontre =[table].id
				', null, 104));
				*/
		/*
		 * 			$this->add(new atgNumberExpressionAttribute("places_offertes", ' select sum(covoiturage_places_offertes) from individu_rencontre
		 		where id_rencontre =[table].id
					', null, 100));
		$this->add(new atgNumberExpressionAttribute("places_demandees", ' select sum(covoiturage_places_demandees) from individu_rencontre
				where id_rencontre =[table].id
				', null, 101));
		*/

		$this->add(new atkNumberAttribute("montant_participation_adherent", AF_SEARCHABLE, 10, 2));
		$this->add(new atkNumberAttribute("montant_participation_accompagnant", AF_SEARCHABLE, 10, 2));
		$this->add(new atkNumberAttribute("montant_depense_totale", AF_SEARCHABLE, 10, 2));
		$this->add(new atkNumberAttribute("montant_recette_non_nominative", AF_SEARCHABLE, 10, 2));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null, 300);
		$this->add(new atkManyToOneRelation("id_groupe_travail", "organisme.groupe_travail", AF_READONLY| AF_FORCE_LOAD), null, 301);
		$this->add(new atgFileManyToOneRelation("id_compte_rendu", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,410);

		$this->add(new atkManyToOneRelation("id_type_rencontre", "table.type_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY| AF_FORCE_LOAD), null, 200);
		$this->add(new atgFileManyToOneRelation("id_document_inscription", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,420);
		$this->add(new atgFileManyToOneRelation("id_document_programme", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,430);
		$this->add(new atgFileManyToOneRelation("id_document_emargement", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,620);
		$this->add(new atgFileManyToOneRelation("id_document_preparation", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,400);
		$this->add(new atgFileManyToOneRelation("id_document_communication", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null,610);
		$this->add(new atkManyToOneRelation("id_type_audience", "table.audience", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_FORCE_LOAD), null, 600);

		$this->add(new atkDateAttribute("date_debut", "d F Y","d F Y", 0, 0, AF_FORCE_LOAD),205);
		$this->add(new atkDateAttribute("date_fin", "d F Y","d F Y", 0, 0,AF_FORCE_LOAD),210);
		$this->add(new atkTimeAttribute("heure_debut", 0, 23, $m_arr_minute_step, $default_start_time, AF_TIME_STRING|AF_FORCE_LOAD|AF_HIDE_VIEW|AF_HIDE_LIST), null,225);
		$this->add(new atkTimeAttribute("heure_fin", 0, 23, $m_arr_minute_step, $default_end_time,  AF_TIME_STRING|AF_FORCE_LOAD|AF_HIDE_VIEW|AF_HIDE_LIST), null,230);
		$this->add(new atkDateAttribute("date_cloture", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));

		$this->add(new atkManyToOneRelation("id_organisme_parcours", "organisme.golf_parcours", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD), null, 800);
		$this->add(new atkNumberAttribute("an_championnat", AF_SEARCHABLE, 4,0), null, 811);
		$this->add(new atkNumberAttribute("numero_rencontre_championnat", AF_SEARCHABLE, 4,0), null,813);
		$this->add(new atkBoolAttribute("forcer_couleur_depart_o_n"), null,814);
		$this->add(new atkBoolAttribute("generer_carte_o_n"), null,815);
		$this->add(new atkBoolAttribute("saisir_score_trou_o_n"), null,816);
		$this->add(new atkTextAttribute("cheque_1_motif", 1,AF_SEARCHABLE), null,817);
		$this->add(new atkNumberAttribute("cheque_1_montant", AF_SEARCHABLE, 5, 2), null,817);
		$this->add(new atkTextAttribute("cheque_1_ordre", 1,AF_SEARCHABLE), null,819);
		$this->add(new atkTextAttribute("cheque_2_motif", 1,AF_SEARCHABLE), null,820);
		$this->add(new atkNumberAttribute("cheque_2_montant", AF_SEARCHABLE, 5, 2), null,821);
		$this->add(new atkTextAttribute("cheque_2_ordre", 1,AF_SEARCHABLE), null,822);
		$this->add(new atkNumberAttribute("frais_de_jeu", AF_SEARCHABLE, 2,0), null,823);
		//				$this->add(new atkOneToManyRelation("competiteurs", "individu.carte_golf", "id_rencontre", AF_HIDE_LIST), null, 824);
		$this->add(new atkNumberAttribute("ssj", AF_SEARCHABLE, 2, 0));
		//		$this->add(new atkOneToManyRelation("fournisseurs", "organisme.rencontre_fournisseur", "id_rencontre", AF_HIDE_LIST));
		$this->add(new atkOneToManyRelation("choix", "organisme.rencontre_choix", "id_rencontre", AF_HIDE_LIST));
		$this->add(new atkfckattribute("communique_presse", "", AF_HIDE_LIST| AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '500px'
		)));
		$this->add(new atkfckattribute("preparation", "", AF_HIDE_LIST| AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '500px'
		)));
		$this->add(new atkfckattribute("programme", "", AF_HIDE_LIST| AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '500px'
		)));
		$this->add(new atkfckattribute("conclusion", "", AF_HIDE_LIST| AF_FORCE_LOAD , array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '500px'
		)));
		$this->add(new atkfckattribute("audience", "", AF_HIDE_LIST| AF_FORCE_LOAD , array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '500px'
		)));
		$this->add(new atkUrlAttribute("url_inscription", AF_POPUP | AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_programme", AF_POPUP | AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_preparation", AF_POPUP | AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_communication", AF_POPUP | AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("url_compte_rendu", AF_POPUP | AF_SEARCHABLE));


		$this->add(new atkOneToManyRelation("communications", "organisme.rencontre_communication", "id_rencontre", AF_HIDE_LIST));
		//			$this->add(new atkDummyAttribute("inscrits1", "Courriel", AF_NO_LABEL | AF_HIDE_LIST));
		//			$this->add(new atkParserAttribute("inscrits2", href("?atkaction=listeecran&id=[id]&atkcode=1", atktext("Inscrits : tous"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_LIST), NULL, 10000);
		//		$this->add(new atkDummyAttribute("inscrire_rencontre", "Courriel", AF_NO_LABEL | AF_HIDE_LIST));
		$this->m_securityMap["admin_liste"] = "view";
		$this->m_securityMap["maj"] = "view";
		$this->m_securityMap["liste_participants"] = "view";
		$this->m_securityMap["inscrire_participants_du_presse_papier"] = "view";
		$this->m_securityMap["inscrire_joueurs_du_presse_papier"] = "view";
		$this->m_securityMap["listeecran"] = "view";
		$this->m_securityMap["document"] = "view";
		$this->m_securityMap["m_inscrire"] = "view";
		$this->m_securityMap["compte_rendu"] = "view";
		$this->m_securityMap["individus_supprimer"] = "view";
		$this->m_securityMap["joueurs_supprimer"] = "view";
		$this->m_securityMap["rencontres_supprimer"] = "view";
		$this->m_securityMap["liste_organismes_participants"] = "view";
		$this->m_securityMap["golf_tous_les_documents"] = "view";
		$this->m_securityMap["golf_les_departs"] = "view";
		$this->m_securityMap["golf_les_cartes"] = "view";
		$this->m_securityMap["golf_le_classement_net"] = "view";
		$this->m_securityMap["golf_le_classement_brut"] = "view";
		$this->m_securityMap["balance_carree"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,17 );
		$this->setOrder("organisme_rencontre.date_debut desc");
		//			$this->setIndex("libelle");
		// GG deb
		global $ATK_VARS, $g_user;
		if ($ATK_VARS["atknodetype"] == "organisme.rencontre" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
		))) {
			if ($this->getView() == "active") {
				$this->addFilter("ADDDATE(organisme_rencontre.date_fin,365) > UTC_DATE");
			}
		}
		// GG fin
	}
	function tous_les_choix_display($record, $mode='list')
	{
		$db = & atkGetDb();
		$id=$record["id"];
		$retour="<style>
    .alnright { text-align: right; }
</style>
				<table>";
		$retour.="<tr><td><b>Choix</td><td><b>PU</td><td><b>Nombre</td><td><b>Total</td></tr>";
		$id_rencontre=$record["id"];
		$sql="SELECT orc.id, orc.libelle, orc.cout
		from organisme_rencontre_choix orc
		where orc.id_rencontre=$id_rencontre" ;
		//	$this->p($sql);
		$data=$db->getrows($sql);
		$total_total=0;
		foreach ($data as $option)
		{
				
			$id_choix=$option["id"];
			$sql1="select sum(irc.quantite) as quantite
			from individu_rencontre_choix irc
			where 
			irc.id_organisme_rencontre_choix=$id_choix
			and irc.id_individu_rencontre in ( select id from individu_rencontre where id_rencontre=$id_rencontre )";
			$data1=$db->getrows($sql1);
			(count($data1)>0)? $option["quantite"]=$data1[0]["quantite"] : $option["quantite"]=0;
	
			$total_ligne=$option["quantite"]*$option["cout"];
			$total_total+=$total_ligne;
			$option["quantite"]=number_format($option["quantite"],0,",",".");
			$option["cout"]=number_format($option["cout"],2,",",".");
			$total_ligne=number_format($total_ligne,2,",",".");
			$retour.="<tr><td>".$option["libelle"]."</td><td class='alnright'>".$option["cout"]."</td><td class='alnright'>".$option["quantite"]."</td><td class='alnright'>".$total_ligne."</td>";
			$retour.="</tr>";
			
		}
		$total_total_tmp=number_format($total_total,2,",",".");
		$retour.="<tr><td><b>Prestations : </b></td><td></td><td></td><td class='alnright'><b>".$total_total_tmp."</b></td></tr>";
		$sql1="select sum(ir.montant_versement) as montant_versement,sum(ir.montant_versement_2) as montant_versement_2
		from individu_rencontre ir
		where ir.id in ( select id from individu_rencontre where id_rencontre=$id_rencontre ) ";
		//$this->p($sql1);
		$data1=$db->getrows($sql1);
		(count($data1)>0 && $data1[0]["montant_versement"]!='')? $montant_versement=$data1[0]["montant_versement"] : $montant=0;
		(count($data1)>0 && $data1[0]["montant_versement_2"]!='')? $montant_versement+=$data1[0]["montant_versement_2"] : null;
		$solde=$total_total-$montant_versement;
		$montant_versement=number_format($montant_versement,2,",",".");
		$retour.="<tr><td><b>Versements : </b></td><td></td><td></td><td class='alnright'><b>".$montant_versement."</b></td></tr>";
		
		($solde>0)? $texte="A percevoir :" : null;
		($solde<0)? $texte="Trop perçu :" : null;
		($solde==0)? $texte="Equilibré :" : null;
		$solde=number_format($solde,2,",",".");
		
			$retour.="<tr><td><b>$texte</b></td><td></td><td></td><td class='alnright'><b>".$solde."</b></td></tr>";
		$retour.="</table>";
	
		return $retour;
	}
	function action_balance_carree()
	{
				(!empty($this->m_postvars['atkfilter']))? $rencontre=$this->m_postvars['atkfilter'] : null;
		(!empty($this->m_postvars['atkselector']))? $rencontre=$this->m_postvars['atkselector'] : null;
	
		$array_id = explode('=', $rencontre);
//$this->p($array_id);
		$id_rencontre=$array_id[1];
		$db = & atkGetDb();
		
		// Créer la ligne titre border:1px solid red;
		$retour="<style> .alnright { text-align: right; }</style>
				<style> td { 
 border-width:1px;
 border-style:solid; 
 border-color:black;

 }</style><table>";
		$retour.="<tr><td>Nom</td>";
		$sql="SELECT orc.libelle, orc.cout
		from organisme_rencontre_choix orc
		where orc.id_rencontre=$id_rencontre
		 order by orc.id" ;
		$data=$db->getrows($sql);
		for ($i=0;$i<count($data);$i++)
				{
					$cout=number_format($data[$i]["cout"],0,",",".");
					$retour.="<td>".$data[$i]["libelle"]."<br/>".$cout."</td>";
				}
		$retour.="<td>Total des prestations</td><td>Total des règlements</td><td>Solde</td>";
		$retour.="</tr>";
		$sql="SELECT i.id, i.nom, i.prenom
		from individu i
		where i.id in 
		(select id_individu from individu_rencontre where id_rencontre=$id_rencontre )
		order by i.nom, i.prenom
		" ;
		$data_individu=$db->getrows($sql);
		$retour.="<tr>";
		$total_choix=array();
		$total_choix_nombre=array();
		$total_total_prestations_individu=0;
		$total_solde_individu=0;
		$total_versements_individu=0;
		for ($i=0;$i<count($data_individu);$i++)
		{
			$nom= $data_individu[$i]["nom"].' '.$data_individu[$i]["prenom"];
			$retour.="<td>$nom</td>";
			$id_individu=$data_individu[$i]["id"];
			$sql="SELECT 
			orc.id, orc.cout, irc.quantite
			from organisme_rencontre_choix orc, individu_rencontre_choix irc, individu_rencontre ir
			where 
			ir.id_rencontre=$id_rencontre and 
			ir.id_individu=$id_individu and
			ir.id=irc.id_individu_rencontre and
			irc.id_organisme_rencontre_choix=orc.id
						 order by orc.id
			" ;
			$data_choix=$db->getrows($sql);
			$total_prestations_individu=0;
	
			for ($j=0;$j<count($data_choix);$j++)
			{
				$cout=$data_choix[$j]["cout"];
				$quantite=$data_choix[$j]["quantite"];
				$total_choix_individu=$cout*$quantite;
				$quantite_display=number_format($quantite,0,",",".");
			($quantite==0)? $retour.="<td></td>" : $retour.="<td>".$total_choix_individu." (".$quantite_display.")"."</td>";
		//		$retour.="<td>".$total_choix_individu." (".$quantite.")"."</td>";
				$total_prestations_individu+=$total_choix_individu;
				$total_choix[$j]+=$total_choix_individu;
				$total_choix_nombre[$j]+=$quantite;
			}
			$retour.="<td class='alnright'>$total_prestations_individu</td>";
			$total_total_prestations_individu+=$total_prestations_individu;
			$sql1="select ir.montant_versement,ir.montant_versement_2 
		from individu_rencontre ir
		where ir.id_individu=$id_individu and ir.id_rencontre = $id_rencontre ";
		//$this->p($sql1);
		$data1=$db->getrows($sql1);
		(count($data1)>0 && $data1[0]["montant_versement"]!='')? $montant_versement=$data1[0]["montant_versement"] : $montant=0;
		(count($data1)>0 && $data1[0]["montant_versement_2"]!='')? $montant_versement+=$data1[0]["montant_versement_2"] : null;
		$total_versements_individu+=$montant_versement;
		$solde=$total_prestations_individu-$montant_versement;
		$montant_versement=number_format($montant_versement,0,",",".");
		$retour.="<td class='alnright'>$montant_versement</td>";
		
		$total_solde_individu+=$solde;
		$solde=number_format($solde,0,",",".");
		$retour.="<td class='alnright'>$solde</td>";
			$retour.="</tr>";
			
		}
		$retour.="<tr><td>Total</td>";
		$total_ligne=0;
		for ($k=0;$k<count($total_choix);$k++)
		{
		$retour.="<td>".$total_choix[$k]." (".$total_choix_nombre[$k].")"."</td>";
		$total_ligne+=$total_choix[$k];
		}
		$retour.="<td>".$total_ligne." / ".$total_total_prestations_individu."</td>";
		$retour.="<td class='alnright'>".$total_versements_individu."</td>";
		$retour.="<td class='alnright'>".$total_solde_individu."</td>";
		$retour.="</tr>";
		$retour.="</table>";
	//	return $retour;
		// render table.
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$res= "Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle<br /><br />";
//		$res.=$this->descripteur_rencontre($stuff[0]["id_rencontre_organisme"],'n')."<br />";
		$res .= $retour;
		$res.= "<br / >Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle";
		
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
		$page->addContent($retour);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		
	}
	
	
	function options_display($record, $mode='list')
	{
		$db = & atkGetDb();
		$id=$record["id"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		$retour.="<table>";
		$retour.="<tr><td>Option</td><td>Libellé</td></tr>";
	
		$sql="SELECT libelle_participation_1, libelle_participation_2, libelle_participation_3, libelle_participation_4
		from organisme_rencontre 
		where id=$id";
		$data=$db->getrows($sql);
		$record["libelle_participation_1"]=$data[0]["libelle_participation_1"];
		$record["libelle_participation_2"]=$data[0]["libelle_participation_2"];
		$record["libelle_participation_3"]=$data[0]["libelle_participation_3"];
		$record["libelle_participation_4"]=$data[0]["libelle_participation_4"];
		$retour.="<tr><td>Option 1</td>";
		$retour.="<td>".$this->getAttribute('libelle_participation_1')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>Option 2</td>";
		$retour.="<td>".$this->getAttribute('libelle_participation_2')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>Option 3</td>";
		$retour.="<td>".$this->getAttribute('libelle_participation_3')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>Option 4</td>";
		$retour.="<td>".$this->getAttribute('libelle_participation_4')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="</table>";
	
		return $retour;
	}
	function action_maj() {
	
		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$selection=$this->get_row_selection_information(false);
		foreach ($selection["node_ids"] as $id)
		{
			$participation_1=escapeSQL($this->m_postvars["data"][$id]["libelle_participation_1"]) ;
			$participation_2=escapeSQL($this->m_postvars["data"][$id]["libelle_participation_2"]) ;
			$participation_3=escapeSQL($this->m_postvars["data"][$id]["libelle_participation_3"]) ;
			$participation_4=escapeSQL($this->m_postvars["data"][$id]["libelle_participation_4"]) ;
			$sql="UPDATE organisme_rencontre set
			libelle_participation_1='$participation_1',
			libelle_participation_2='$participation_2',
			libelle_participation_3='$participation_3',
			libelle_participation_4='$participation_4',
			id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=$id";
			$db->query($sql);
		}
		$this->redirect();
			
	}
	function descripteur_rencontre_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre($record["id"]),100);
	}
	function descripteur_rencontre_documents_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre_documents($record["id"]),100);
	}
	function descripteur_rencontre_fournisseurs_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre_fournisseurs($record["id"]),100);
	}
	function ecritures_display($record, $mode) {
		$db = & atkGetDb();
		$idrencontre=$record["id"];
		$inrencontre='';
		$inrencontre = (empty($record["id_ecriture_participation"]) ? '' : $record["id_ecriture_participation"].',')
		.(empty($record["id_ecriture_reglement"]) ? '' : $record["id_ecriture_reglement"].',');
		if (substr($inrencontre, strlen($inrencontre),1)==',')
		{
			$inrencontre=substr($inrencontre,0 ,strlen($inrencontre)-1);
		}
		$sqlparticipants ="select id_ecriture_participation from individu_rencontre where id_rencontre = $idrencontre
		and  id_ecriture_participation is not null
		UNION
		select id_ecriture_reglement from individu_rencontre where id_rencontre = $idrencontre
		and id_ecriture_reglement is not null";
		$sqlfournisseurs ="select id_ecriture_depense from organisme_rencontre_fournisseur where id_rencontre = $idrencontre
		and  id_ecriture_depense is not null
		UNION
		select id_ecriture_reglement from organisme_rencontre_fournisseur where id_rencontre = $idrencontre
		and  id_ecriture_reglement is not null
		";
		if (strlen($inrencontre)>0)
		{
			$retourrencontre=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture IN (".$inrencontre.") "
			), "dispatch.php"), text("Rencontre"), SESSION_NESTED);
		}

		$data=$db->getrows("$sqlparticipants");
		if (count($data)>0)
		{
			$retourparticipants=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture IN (".$sqlparticipants.") "
			), "dispatch.php"), text("Participants"), SESSION_NESTED);
		}

		$data=$db->getrows("$sqlfournisseurs");
		if (count($data)>0)
		{
			$retourfournisseurs=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture IN (".$sqlfournisseurs.") "
			), "dispatch.php"), text("Fournisseurs"), SESSION_NESTED);
		}

		$retour=(empty($retourrencontre) ? '' : $retourrencontre.'<br />')
		.(empty($retourparticipants) ? '' : $retourparticipants.'<br />')
		.(empty($retourfournisseurs) ? '' : $retourfournisseurs);

		if (isset ($retour))
		{
			return $retour;
		}
		else {
			return "Pas d'écritures";
		}
	}

	function id_document_preparation_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["preparation"])>0)
		{
			$retour= href(dispatch_url("organisme.rencontre","edit",array("atkselector"=>$this->primaryKey($record))),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		if ( $record["id_document_preparation"]!=null)
		{
			$retour .= $this->getAttribute("id_document_preparation")->display($record, $mode) ;
		}
		return $retour;

	}

	function id_document_programme_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["programme"])>0)
		{
			$retour= href(dispatch_url("organisme.rencontre","edit",array("atkselector"=>$this->primaryKey($record))),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		if ( $record["id_document_programme"]!=null)
		{
			$retour .= $this->getAttribute("id_document_programme")->display($record, $mode) ;
		}
		return $retour;
	}
	function id_document_communication_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["communique_presse"])>0)
		{
			$retour= href(dispatch_url("organisme.rencontre","edit",array("atkselector"=>$this->primaryKey($record))),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		if ( $record["id_document_communication"]!=null)
		{
			$retour .= $this->getAttribute("id_document_communication")->display($record, $mode) ;
		}
		return $retour;
	}

	function id_type_audience_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["audience"])>0)
		{
			$retour= href(dispatch_url("organisme.rencontre","edit",array("atkselector"=>$this->primaryKey($record))),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		if ( $record["id_type_audience"]!=null)
		{
			$retour .= $this->getAttribute("id_type_audience")->display($record, $mode) ;
		}
		return $retour;
	}

	function id_compte_rendu_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["conclusion"])>0)
		{
			$retour= href(dispatch_url("organisme.rencontre","edit",array("atkselector"=>$this->primaryKey($record)
					,
					"atktab"=>"Conclusion"
			)),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		if ( $record["id_compte_rendu"]!=null)
		{
			$retour .= $this->getAttribute("id_compte_rendu")->display($record, $mode) ;
		}


		return $retour;
	}

	function modifyDataGrid($grid,$mode)
	{
		if ($mode=='1'&& isset($this->m_postvars['atkfilter']))
		{
			/*		$db = & atkGetDb();
			 $sql1="SELECT count(organisme_rencontre.id) as nombre from organisme_rencontre
			where  ".$this->m_postvars['atkfilter']." and date_debut > CURDATE()";
			$sql2="SELECT count(organisme_rencontre.id) as nombre from organisme_rencontre
			where  ".$this->m_postvars['atkfilter']." ";
			$data=$db->getrows($sql1);
			$nombreavant=$data[0]["nombre"];

			$data=$db->getrows($sql2);
			$nombretotal=$data[0]["nombre"];
			*/
			$nombreavant=$this->countDb("organisme_rencontre.date_debut > CURDATE() ");
			$nombretotal=$this->countDb();
			if ($nombretotal<20) return true;
			if ($nombreavant<10)
			{
				$startat=0;
			}
			else
			{
				$startat=$nombreavant-10;
			}

			$grid->setPostvar('atklimit', '20');
			$grid->setPostvar('atkstartat', $startat);
		}
		return true;
	}

	/*
	 function duration_edit($record="",$fieldprefix="",$mode)
	 {
	$attrib = $this->getAttribute("duration");
	$ret= $attrib->edit($record,$fieldprefix,$mode);
	$ret.='&nbsp;&nbsp;&nbsp;<span id="date_fin" style="display: none;">';
	$attrib = $this->getAttribute("date_fin");
	$ret.= $attrib->edit($record,$fieldprefix,$mode);
	$ret.='</span>&nbsp;&nbsp;&nbsp;<span id="heure_fin" style="display: none;">';
	$attrib = $this->getAttribute("heure_fin");
	$ret.= $attrib->edit($record,$fieldprefix,$mode);
	$ret.='</span>';
	return $ret;
	}

	function duration_display($record,$mode)
	{

	$attrib = $this->getAttribute("duration");
	$ret.= $attrib->display($record,$mode);
	if($record['duration']==-1)
	{
	$ret.='&nbsp;&nbsp;&nbsp;';
	$attrib = $this->getAttribute("date_fin");
	$ret.= $attrib->display($record,$mode);

	$ret.='&nbsp;&nbsp;&nbsp;';
	$attrib = $this->getAttribute("heure_fin");
	$ret.= $attrib->display($record,$mode);
	}


	return $ret;
	}
	*/
	/**
	 * Validate date_fin
	 *
	 * @param unknown_type $record
	* @param unknown_type $mode
	*/
	function date_fin_validate(&$record, $mode)
	{
		if ($record["date_fin"]["year"] < $record["date_debut"]["year"])
		{
			triggerError($record, "date_fin", "error_date");
		}
		elseif ($record["date_fin"]["year"] == $record["date_debut"]["year"])
		{
			if ($record["date_fin"]["month"] < $record["date_debut"]["month"])
			{
				triggerError($record, "date_fin", "error_date");
			}
			elseif ($record["date_fin"]["month"] == $record["date_debut"]["month"])
			{
				if ($record["date_fin"]["day"] < $record["date_debut"]["day"])
				{
					triggerError($record, "date_fin", "error_date");
				}
			}
		}
	}

	function heure_fin_validate(&$record, $mode)
	{
		// check if start and date_fin are the same else don't validate
		$date_debut = $record["date_debut"]["year"].$record["date_debut"]["month"].$record["date_debut"]["day"];
		$date_fin = $record["date_fin"]["year"].$record["date_fin"]["month"].$record["date_fin"]["day"];

		if($date_debut==$date_fin )
		{
			if ($record["heure_fin"]["hours"] < $record["heure_debut"]["hours"])
			{
				triggerError($record, "heure_fin", "error_time");
			}
			elseif ($record["heure_fin"]["hours"] == $record["heure_debut"]["hours"])
			{
				if ($record["heure_fin"]["minutes"] <= $record["heure_debut"]["minutes"])
				{
					triggerError($record, "heure_fin", "error_time");
				}
			}
		}
	}
	/*
	 function date_debut_edit($record="", $fieldprefix="",$mode)
	 {
	$attrib = $this->getAttribute("date_debut");
	$ret = $attrib->edit($record,$fieldprefix,$mode);
	$ret.='&nbsp;&nbsp;&nbsp;<span id="heure_debut" style="display: inline;">';
	$attrib = $this->getAttribute("heure_debut");
	$ret.= $attrib->edit($record,$fieldprefix,$mode)."</span>";
	return $ret;
	}
	*/
	function date_debut_display($record,$mode)
	{
		$attrib = $this->getAttribute("date_debut");
		$ret = $attrib->display($record,$mode);

		$ret.='&nbsp;&nbsp;&nbsp;';
		$attrib = $this->getAttribute("heure_debut");
		$ret.= $attrib->display($record)."</span>";

		return $ret;
	}
	/*	function date_fin_edit($record="", $fieldprefix="",$mode)
	 {
	$attrib = $this->getAttribute("date_fin");
	$ret = $attrib->edit($record,$fieldprefix,$mode);
	$ret.='&nbsp;&nbsp;&nbsp;<span id="heure_fin" style="display: inline;">';
	$attrib = $this->getAttribute("heure_fin");
	$ret.= $attrib->edit($record,$fieldprefix,$mode)."</span>";
	return $ret;
	}
	*/
	function date_fin_display($record,$mode)
	{
		$attrib = $this->getAttribute("date_fin");
		$ret = $attrib->display($record,$mode);

		$ret.='&nbsp;&nbsp;&nbsp;';
		$attrib = $this->getAttribute("heure_fin");
		$ret.= $attrib->display($record)."</span>";

		return $ret;
	}

	/**
	 * Calculate the endddate if the user used the duration dropdown
	 *
	 * @param unknown_type $rec

	 function updatedate_fin(&$rec)
	 {
		if($rec['duration']!=-1)
		{
		$date_fin = mktime($rec["heure_debut"]["hours"],$rec["heure_debut"]["minutes"],$rec["heure_debut"]["seconds"],$rec['date_debut']['month'],$rec['date_debut']['day'],$rec['date_debut']['year']);
		$date_fin+=$rec['duration']*60;
		$rec['heure_fin']['hours']=date("H",$date_fin);
		$rec['heure_fin']['minutes']=date("i",$date_fin);
		$rec['heure_fin']['seconds']=date("s",$date_fin);
		$rec['date_fin']['day']=date("d",$date_fin);
		$rec['date_fin']['month']=date("m",$date_fin);
		$rec['date_fin']['year']=date("Y",$date_fin);
		}
		}

	 */



	function dispatch($postvars, $fullpage=true)
	{
		if ($postvars['atkaction']=='edit' || $postvars['atkaction']=='view' )
		{
			$atkselect = $postvars["atkselector"];
			if (($atkselect != "") && isset($atkselect))
			{
				$rencontreid = sscanf($atkselect, "organisme_rencontre.id='%d'");
				$rencontreId = $rencontreid[0];
				$this->RecentUseProcess('rencontre', $rencontreId);
			}
		}
		else
		{
			$this->RecentUseRefresh('rencontre');
		}
		return parent::dispatch($postvars, $fullpage);
	}
	function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("individu.rencontre_i", "admin", array (
					'atkfilter' => "individu_rencontre.id_rencontre='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function id_ecriture_participation_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_participation"]);
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
		$data=$db->getrows('Select max(id) as id from organisme_rencontre');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_participation"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_participation"],$this->type_ecriture_rencontre,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_rencontre,$record["id"]);
		}
		$id_entite=$record["id"];
		$this->RecentUseProcess('rencontre', $id_entite);

		return true;
	}

	function preAdd(& $record) {
		if ($record["montant_recette_non_nominative"] > 0) {
			$this->creer_ecritures_comptables($record);
		}

		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
	//$this->p($record);
		$this->supprimer_ecritures($record);
		if ($record["montant_recette_non_nominative"] > 0) {
			$this->creer_ecritures_comptables($record);
		}
		parent :: preUpdate($record);
	}
	function preDelete(& $record) {
		$this->supprimer_ecritures($record);
		parent :: preDelete($record);
	}
	function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_participation = $record["id_ecriture_participation"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "") {
			return true;
		}
		if (isset ($id_ecriture_participation)) {
			$this->supprimer_ecriture_comptable($id_ecriture_participation);
		}
		if (isset ($id_ecriture_reglement)) {
			$this->supprimer_ecriture_comptable($id_ecriture_reglement);
		}
		return true;
	}
	function creer_ecritures_comptables(& $record) {
		$id_organisme = $record['id_organisme']['id'];
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
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
		$id_compte_participation_manifestation = $rang[0]["id_compte_participation_manifestation"];
		$date_reglement = $this>dateatktodb($record["date_debut"]);
		$libelle = 'Participation aux frais non nominative à ' . $record["libelle"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle, $date_reglement);
		$record["id_ecriture_participation"] = $id_ecriture;

		$debit = $record["montant_recette_non_nominative"];
		// montant recette
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_adherents, $id_organisme, null, $debit, $credit, null, null, null, null);
		$credit = $record["montant_recette_non_nominative"];
		;
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_participation_manifestation, $id_organisme, null, $debit, $credit, null, null, null, null);
		// epèces reçues en caisse
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle, $date_reglement);
		$record["id_ecriture_reglement"] = $id_ecriture;
		$credit = $record["montant_recette_non_nominative"];
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, null, $debit, $credit, null, null, null, null);
		$debit = $record["montant_recette_non_nominative"];
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, null, $debit, $credit, '3', null, $date_reglement, null);
		return;
	}
	function action_liste_organismes_participants() {

		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_organisme_participant from individu_rencontre
				where id_rencontre in (select id from organisme_rencontre
				where  id in (' . $idrencontres . '))';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			if ($data[$i]["id_organisme_participant"]!="")
			{
				$chaineidorganisme .= $data[$i]["id_organisme_participant"] . ',';
			}

		}
		$idorganismes = substr($chaineidorganisme, 0, strlen($chaineidorganisme) - 1);
		if ($idorganismes=="")
		{
			return true;
		}
		$url = dispatch_url("organisme.organisme", "liste_organismes", array (
				"idorganismes" => $idorganismes,
				"atkcode" => 'liste_organismes',
				"atkexport" => 'n'
		));
		header("Location: $url");
		exit;
	}


	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$andpos=strpos($id_variable, "AND");

			if ($andpos>0 )
			{
				$id_variable=substr($id_variable, 0,$andpos);
			}
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_individu from individu_rencontre
				where id_rencontre in (select id from organisme_rencontre
				where  id in (' . $idrencontres . '))';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		$sql = 'select distinct id_organisme from organisme_rencontre
				where id in (' . $idrencontres . ')';
		$data = $db->getrows($sql);
		$idorganisme = $data[0]["id_organisme"];
		return true;
	}
	/*
	 *
	function inscrits1_edit($record, $mode) {
	$original = href(dispatch_url("individu.v_individu_lieu", "document", array (
			'atkfilter' => ' v_individu_lieu.id in
			( select distinct id_individu from individu_rencontre where id_rencontre=' . $record["id"] . ' ) ',
			'atkselector' => 'organisme.id=' . $record["id_organisme"]["id"] . '',
			'id' => $record["id_organisme"]["id"],
			'atkdoctpl' => 'enveloppe_individus_organisme.odt',
			'atkcode' => '1'
	)), atktext("Enveloppes"), SESSION_NESTED);
	return $original;
	}
	*/
	function inscrire_rencontre_edit($record, $mode) {
		$inscrire_rencontre = 'En visualisant les fonctions à partir de organisme/stats_inscrits on peut inscrire à des rencontres ';
		return $inscrire_rencontre;
	}
	function action_liste_participants() {

		(!empty($this->m_postvars['atkfilter']))? $rencontre=$this->m_postvars['atkfilter'] : null;
		(!empty($this->m_postvars['atkselector']))? $rencontre=$this->m_postvars['atkselector'] : null;
		//		$this->p($rencontre);
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu_rencontre");
		$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
		$query->addJoin("organisme_rencontre", "", "individu_rencontre.id_rencontre = organisme_rencontre.id", false);
		$query->addJoin("organisme", "", "organisme_rencontre.id_organisme = organisme.id", true);
		$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);
		$query->addJoin("individu_lieu", "", "individu_rencontre.id_individu = individu_lieu.id_individu", true);
		$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addField("organisme.nom as organisme");
		$query->addField("individu_rencontre.id as id_rencontre");
		$query->addField("organisme_rencontre.id as id_rencontre_organisme");
		$query->addField("individu_rencontre.participation_complete as participation_complete");
		$query->addField("individu_rencontre.participation_partielle as participation_partielle");
		$query->addField("individu_rencontre.montant_versement as montant_versement");
		$query->addField("individu_rencontre.montant_versement_2 as montant_versement_2");


		$query->addField("individu_rencontre.id_individu as id_individu");
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
		$query->addField("type_rencontre_participation.libelle as participation");
		$query->addField("individu_rencontre.commentaire as commentaire");
		$query->addCondition($rencontre);
		$query->addCondition("individu_lieu.adresse_defaut_o_n='1'or individu_lieu.adresse_defaut_o_n is null");
		$query->addOrderBy(" individu.nom, individu.prenom");

		$sql = $query->buildSelect();
		//		$this->p($sql);
		$stuff = $db->getrows($sql);
		$tbl = & atknew("atk.utils.atktablerenderer");
		$data = array ();
		// Develop a table however you'd like it to display
		// Use cascading style sheets to alter the appearance.
		$tbl->setRowClass(1, "superbold");
		// ....
		// Create data
		$row = array ();
		$row[] ='<b>#</b>';
		$row[] = "<b>Organisme</b>";
		$row[] = "<b>Participation</b>";
		$row[] = "<b>Nom</b>";
		$row[] = "<b>Prénom</b>";
		$row[] = "<b>Participants (complet)</b>";
		$row[] = "<b>Participants (partiel)</b>";
		$row[] = "<b>Versement</b>";
		$row[] = "<b>Second versement</b>";
		$row[] = "<b>Commentaire</b>";
		$row[] = "<b>Courriel</b>";
		$row[] = "<b>Téléphone</b>";
		$row[] = "<b>Mobile</b>";
		$row[] = "<b>Adresse</b>";
		$row[] = "<b>CP</b>";
		$row[] = "<b>Ville</b>";
		//		$row[] = "<b>Province</b>";
		//		$row[] = "<b>Pays</b>";
		$data[] = $row;
		for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
			$row = array ();
			$f=$i+1;
			$row[] ='<b>'. $f.'</b>';
			$row[] = $stuff[$i]["organisme"];
			$row[] = $stuff[$i]["participation"];
			$row[] = $stuff[$i]["nom"];
			$row[] = $stuff[$i]["prenom"];
			$row[] = $stuff[$i]["participation_complete"];
			$total_participation_complete+=$stuff[$i]["participation_complete"];
			$row[] = $stuff[$i]["participation_partielle"];
			$total_participation_partielle+=$stuff[$i]["participation_partielle"];
			$row[] = $stuff[$i]["montant_versement"];
			$total_montant_versement+=$stuff[$i]["montant_versement"];
			$row[] = $stuff[$i]["montant_versement_2"];
			$total_montant_versement_2+=$stuff[$i]["montant_versement_2"];
			$row[] = $stuff[$i]["commentaire"];
			$row[] = $stuff[$i]["courriel"];
			$row[] = $stuff[$i]["telephone_fixe"];
			$row[] = $stuff[$i]["telephone_mobile"];
			$row[] = $stuff[$i]["adresse1"];
			$row[] = $stuff[$i]["code_postal"];
			$row[] = $stuff[$i]["ville"];
			//			$row[] = $stuff[$i]["province"];
			//			$row[] = $stuff[$i]["pays"];
			$data[] = $row;
		}
		$row = array ();
		$f=$i+1;
		$row[] ='<b>Totaux : </b>';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '<b>'.$total_participation_complete.'</b>';
		$row[] = '<b>'.$total_participation_partielle.'</b>';
		$row[] = '<b>'.$total_montant_versement.'</b>';
		$row[] = '<b>'.$total_montant_versement_2.'</b>';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		$row[] = '';
		//		$row[] = '';
		//		$row[] = '';
		$data[] = $row;
			
		// render table.
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$res= "Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle<br /><br />";
		$res.=$this->descripteur_rencontre($stuff[0]["id_rencontre_organisme"],'n')."<br />";
		$res .= $tbl->render($data, 0, "recordlist");
		$res.= "<br / >Cette liste valable au " . gmdate(c) . " et imprimée par " . $g_nomutilisateur . " est strictement confidentielle";
		/*		$id_document=$this->stocker_document_individu('Participants_rencontre', $res, '148');

		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=individu_document&id='.$id_document.'&field=file_content','Document',650,650,'yes','no');
		$this->p($popup);
		header("Location: $popup");
		*/

		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

	}
	function action_golf_tous_les_documents() {
		$this->action_golf_les_departs();
		$this->action_golf_les_cartes();
		$this->action_golf_le_classement_net();
		$this->action_golf_le_classement_brut();
		$this->action_golf_le_classement_general_net();
		$this->action_golf_le_classement_general_brut();

	}
	function action_golf_les_departs()
	{
		$tableau_selection=$this->get_row_selection_information(false);
		$idrencontres=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");

		foreach ($idrencontres as $idrencontre)
		{
			$j=0;
			$k=0;
			$tbl = & atknew("atk.utils.atktablerenderer");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$db = & atkGetDb();
			$sql=" select
			c.trou_depart,
			c.heure_depart,
			i.nom as nom_joueur,
			i.prenom as prenom_joueur,
			c.index_avant,
			cat.libelle as libelle_categorie,
			c.couleur_depart,
			r.libelle as libelle_rencontre,
			p.libelle as libelle_parcours,
			o.nom as nom_organisme,
			op.nom as nom_organisme_parcours,
			c.date_depart
			from individu i,
			organisme o,
			individu_carte_golf c,
			organisme_rencontre r,
			organisme_golf_parcours p,
			type_categorie_golf cat,
			organisme op
			where
			r.id=$idrencontre
			and r.id=c.id_rencontre
			and c.id_individu=i.id
			and c.id_organisme_parcours=p.id
			and p.id_organisme=op.id
			and c.id_type_categorie_golf=cat.id
			and r.id_organisme=o.id

			order by
			c.trou_depart,
			c.heure_depart,
			c.index_avant
			";
			$stuff=$db->getrows($sql);
			//logo
			//nom golf et date
			// titre rencontre

			$row = array ();
			$row[]="<b>#";
			$row[]="<b>Equipe";
			$row[]="<b>Tee";
			$row[] = "<b>Heure";
			$row[] = "<b>Nom";
			$row[] = "<b>Prénom";
			$row[] = "<b>Index";
			$row[] = "<b>Catégorie";
			$row[] = "<b>Repère";

			$data=array();
			$data[]= $row;
			for ($i = 0; $i < count($stuff); $i++)
			{
				$row = array();
				$row[]=++$k;
				if ($i>0 && $stuff[$i]["trou_depart"]==$stuff[$i-1]["trou_depart"] && $stuff[$i]["heure_depart"]==$stuff[$i-1]["heure_depart"]  )
				{
					$row[]="";
					$row[] ="";
					$row[] ="";
				}
				else
				{
					$row[]=++$j;
					$row[]=$stuff[$i]["trou_depart"];
					$row[] =substr($stuff[$i]["heure_depart"], 0, strlen($stuff[$i]["heure_depart"])-3);
				}
				$row[] =$stuff[$i]["nom_joueur"];
				$row[] =$stuff[$i]["prenom_joueur"];
				$row[] =$stuff[$i]["index_avant"];
				$row[] =$stuff[$i]["libelle_categorie"];
				$row[] =$stuff[$i]["couleur_depart"];
				$data[]= $row;
			}
			$tbl = & atknew("atk.utils.atktablerenderer");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$haut=array();
			$row=array();
			$haut[]=$this->ligne_de_haut_de_tableau($idrencontre, "Départs");
			$res=$tbl->render($haut,null,"hautlistegg");
			$res.= $tbl->render($data, TBL_ALTERNATE, "recordlistgg");
			$pied=array();
			$row=array();
			$row[]=$this->ligne_de_bas_de_tableau($idrencontre);
			$pied[]=$row;
			$res.=$tbl->render($pied,null,"baslistegg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			if ($g_uploads_organismes_o_n=='1' )
			{
				$filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$idrencontre.'_departs.html' ;
				$file =@fopen($filename,"w");
				$filecontent =($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				@fwrite($file,$filecontent,strlen($filecontent));
				@fclose($file);
				echo "Fichier html mis à disposition : <b>$filename</b> </br></br>";
			}

			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

		}
	}


	function action_golf_les_cartes()
	{
		$tableau_selection=$this->get_row_selection_information(false);
		$idrencontres=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");
		$carte_node = & getNode("individu.carte_golf");

		foreach ($idrencontres as $idrencontre)
		{
			$cartes="";

			$db = & atkGetDb();
			$sql=" select
			r.libelle as libelle_rencontre,
			r.date_debut,
			o.nom as nom_organisme,
			orr.nom as nom_organisme_orr,
			orr.id as id_organisme_orr,
			orr.logo,
			p.id_document_photo,
			od.file_extension,
			p.libelle,
			o.nom
			from
			organisme_document od,
			organisme_golf_parcours p,
			organisme_rencontre r,
			organisme o,
			organisme orr
			where
			r.id=$idrencontre
			and r.id_organisme_parcours=p.id
			and p.id_document_photo=od.id
			and p.id_organisme=o.id
			and r.id_organisme=orr.id
			";
			$row=$db->getrows($sql);
			$id_organisme_rencontre=$row[0]["id_organisme_orr"];
			$cartes.="<table class=\"hautlistegg\" style=\"page-break-after:always; table-layout:fixed;  width:1000px; \" >";
			$cartes.="<tr style=\"border:0px;\">";
			$cartes.="<td align=\"center\" style=\"vertical-align:middle;height:750px;\" ><p class=\"hautlistegg\">";
			$cartes.='<img   border="0"  src="documents/organisme_document_'.$row[0]["id_document_photo"].".".$row[0]["file_extension"].'"></img>';
			$cartes.="</td>";
			$cartes.="<td align=\"center\" style=\"vertical-align:middle;height:750px;\"><p class=\"hautlistegg\" >";

			$sql="select od.libelle, ti.libelle as type, od.file_content,od.file_name, od.file_size
			from organisme_image od , type_image ti
			where
			od.id_entite=$id_organisme_rencontre
			and id_type_entite=1
			and od.id_type_image=ti.id
			and od.actif_o_n='1'";
			$data=$db->getrows($sql);
			$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
			$filename=$data[0]["file_name"];
			$url="./documents/".$filename;
			$file =@fopen($url,"w");
			@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
			@fclose($file);
			$data[$i]["file_content"]="";
			$legende=$data[0]["type"]." : ".$data[0]["libelle"];
			$cartes.=$row[0]["nom_organisme_orr"]."<br/><br/><br/>";
			$cartes.='<img  border="0" src="'.$url.'" alt="'.$legende.'"
					title="'.$legende.'"  width="350" ></img>'."<br/><br/>";
			$cartes.=$row[0]["libelle_rencontre"]."<br/>";
			$cartes.=$row[0]["date_debut"]."<br/>";
			$cartes.="</p>";
			$cartes.="</td>";
			$cartes.="</tr>";
			$cartes.="</table>";
			$record=array();
			$recs=$carte_node->selectDb("individu_carte_golf.id_rencontre=".$idrencontre);
			foreach ($recs as $record_joueur)
			{
				$cartes.="<table class=\"recordlistgg\" style=\"page-break-after:always\" >";
				$cartes.="<tr style=\"border:0px;\"><td>";
				$cartes.=$carte_node->descriptor($record_joueur,"o");
				$cartes.="</td></tr>";
				$cartes.="</table>";
			}
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($cartes);
			if ($g_uploads_organismes_o_n=='1' )
			{
				$filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$idrencontre.'_cartes.html' ;
				$file =@fopen($filename,"w");
				$filecontent =($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				@fwrite($file,$filecontent,strlen($filecontent));
				@fclose($file);
				echo "Fichier html mis à disposition : <b>$filename</b> </br></br>";
			}

		}

		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));


	}
	function action_golf_le_classement_net()
	{
		$this->action_golf_le_classement('net');
	}
	function action_golf_le_classement($type='net')
	{
		$tableau_selection=$this->get_row_selection_information(false);
		$idrencontres=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");

		foreach ($idrencontres as $idrencontre)
		{
			$j=0;
			$k=0;
			$tbl = & atknew("atk.utils.atktablerenderer");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$db = & atkGetDb();
			$sql="		SELECT i.nom, i.prenom, c.index_avant, c.handicap, c.stableford, c.stableford_brut, c.index_apres
			from
			organisme_rencontre r,
			individu i,
			individu_carte_golf c
			where
			r.id=$idrencontre
			and r.id=c.id_rencontre
			and i.id=c.id_individu ";
			($type=='net') ? ($sql.=" order by c.stableford desc, c.index_avant") : ($sql.=" order by c.stableford_brut desc, c.index_avant ");
			$stuff=$db->getrows($sql);
			//logo
			//nom golf et date
			// titre rencontre

			$row = array ();
			$row[]="<b>#";
			$row[]="<b>Nom";
			$row[]="<b>Prénom";
			$row[] = "<b>Index initial";
			$row[] = "<b>Handicap";
			$row[] = "<b>Stableford net";
			$row[] = "<b>Stableford brut";
			$row[] = "<b>Nouvel index";

			$data=array();
			$data[]= $row;
			for ($i = 0; $i < count($stuff); $i++)
			{
				$row = array();
				$row[]=++$j;
				$row[]=$stuff[$i]["nom"];
				$row[] =$stuff[$i]["prenom"];
				$row[] =$stuff[$i]["index_avant"];
				$row[] =$stuff[$i]["handicap"];
				($type=='net') ? $row[] ="<b>".$stuff[$i]["stableford"]."</b>" : $row[] ="</b>".$stuff[$i]["stableford"];
				($type!='net') ? $row[] ="<b>".$stuff[$i]["stableford_brut"]."</b>" : $row[] ="</b>".$stuff[$i]["stableford_brut"];
				//				$row[] =$stuff[$i]["stableford"];
				//				$row[] =$stuff[$i]["stableford_brut"];
				$row[] =$stuff[$i]["index_apres"];
				$data[]= $row;
			}
			$tbl = & atknew("atk.utils.atktablerenderer");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$haut=array();
			$row=array();
			($type=='net') ? 	$haut[]=$this->ligne_de_haut_de_tableau($idrencontre, "Classement en net") : $haut[]=$this->ligne_de_haut_de_tableau($idrencontre, "Classement en brut");
			$res=$tbl->render($haut,null,"hautlistegg");
			$res.= $tbl->render($data, TBL_ALTERNATE, "recordlistgg");
			$pied=array();
			$row=array();
			$row[]=$this->ligne_de_bas_de_tableau($idrencontre);
			$pied[]=$row;
			$res.=$tbl->render($pied,null,"baslistegg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			if ($g_uploads_organismes_o_n=='1' )
			{
				($type=='net') ? ($filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$idrencontre.'_classement_net.html')
				: ($filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$idrencontre.'_classement_brut.html') ;
				$file =@fopen($filename,"w");
				$filecontent =($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				@fwrite($file,$filecontent,strlen($filecontent));
				@fclose($file);
				echo "Fichier html mis à disposition : <b>$filename</b> </br></br>";
			}

			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

		}
	}
	function action_golf_le_classement_general_net()
	{
		$this->action_golf_le_classement_general('net');
	}
	function action_golf_le_classement_general_brut()
	{
		$this->action_golf_le_classement_general('brut');
	}
	function action_golf_le_classement_general($type='net')
	{
		$tableau_selection=$this->get_row_selection_information(false);
		$idrencontresin=$tableau_selection["in_id_string"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");
		$tbl = & atknew("atk.utils.atktablerenderer");
		$tbl->setRowClass(1, "superbold");
		$res="";
		$db = & atkGetDb();
		$sql="SELECT i.nom, i.prenom, i.golf_index as index_avant , sum(c.stableford)as stableford_net , sum(c.stableford_brut) as stableford_brut
				from individu_carte_golf c, individu i
				where id_rencontre in ".$idrencontresin."
						and i.id=c.id_individu group by id_individu ";
		($type=='net') ? ($sql.=" order by stableford_net desc, i.golf_index") : ($sql.=" order by stableford_brut desc, i.golf_index ");
		$stuff=$db->getrows($sql);
		$row = array ();
		$row[]="<b>#</b>";
		$row[]="<b>Nom</b>";
		$row[]="<b>Prénom</b>";
		$row[] = "<b>Index initial</b>";
		$row[] = "<b>Stableford net</b>";
		$row[] = "<b>Stableford brut</b>";
			
		$data=array();
		$data[]= $row;
		for ($i = 0; $i < count($stuff); $i++)
		{
			$row = array();
			$row[]=++$j;
			$row[]=$stuff[$i]["nom"];
			$row[] =$stuff[$i]["prenom"];
			$row[] =$stuff[$i]["index_avant"];
			($type=='net') ? $row[] ="<b>".$stuff[$i]["stableford_net"]."</b>" : $row[] ="</b>".$stuff[$i]["stableford_net"];
			($type!='net') ? $row[] ="<b>".$stuff[$i]["stableford_brut"]."</b>" : $row[] ="</b>".$stuff[$i]["stableford_brut"];
			$data[]= $row;
		}
		$sql="SELECT r.id, r.libelle, r.date_debut
				from organisme_rencontre r
				where id in ".$idrencontresin." order by r.date_debut";
		$lignes=$db->getrows($sql);
		for ($i = 0; $i < count($lignes); $i++)
		{
			$rencontreslibelle .="<b>".$lignes[$i]["libelle"]."</b> le <b>". $lignes[$i]["date_debut"]."</b><br/>";
			$identification_rencontres.=$lignes[$i]["id"]."_";
			($i==0) ? $idrencontre=$lignes[$i]["id"] : null;
		}
		$identification_rencontres=substr($identification_rencontres, 0, strlen($identification_rencontres)-1);

		$tbl = & atknew("atk.utils.atktablerenderer");
		$tbl->setRowClass(1, "superbold");
		$res="";
		$haut=array();
		$row=array();
		($type=='net') ? 	$haut[]=$this->ligne_de_haut_de_tableau($idrencontre, "Classement général net",true,$rencontreslibelle ) : $haut[]=$this->ligne_de_haut_de_tableau($idrencontre, "Classement général brut",true,$rencontreslibelle );
		$res=$tbl->render($haut,null,"hautlistegg");

		//			$res.="<br/>Compétitions : <br/>".$rencontreslibelle;
		$res.= $tbl->render($data, TBL_ALTERNATE, "recordlistgg");
		$pied=array();
		$row=array();
		$row[]=$this->ligne_de_bas_de_tableau($idrencontre);
		$pied[]=$row;
		$res.=$tbl->render($pied,null,"baslistegg");
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
		$page->addContent($res);
			
		if ($g_uploads_organismes_o_n=='1' )
		{
			($type=='net') ? ($filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$identification_rencontres.'_classement_general_net.html')
			: ($filename=$this->get_upload_dir($idrencontre)."organisme_rencontre_".$identification_rencontres.'_classement_general_brut.html') ;
			$file =@fopen($filename,"w");
			$filecontent =($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
			@fwrite($file,$filecontent,strlen($filecontent));
			@fclose($file);
			echo "Fichier html mis à disposition : <b>$filename</b> </br></br>";
		}
			

		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

	}
	function action_golf_le_classement_brut()
	{
		$this->action_golf_le_classement('brut');
	}
	function ligne_de_bas_de_tableau($id_rencontre)
	{
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$data ="Liste imprimée par " . $g_nomutilisateur.", valable au " . gmdate(c) ;
		return $data;
	}
	function ligne_de_haut_de_tableau($id_rencontre,$sujet,$general_o_n=false, $libelle_general="")
	{

		$db = & atkGetDb();
		$sql=" select
		r.libelle as libelle_rencontre,
		r.date_debut,
		o.nom as nom_organisme,
		o.logo
		from
		organisme o,
		organisme_rencontre r
		where
		r.id=$id_rencontre
		and r.id_organisme=o.id
		";
		$row=$db->getrows($sql);
		$ligne=array();
		$ligne[]='<img  border="0" src="./logos/'.$row[0]["logo"].'" alt="Logo" title="Logo" ></img>';
		($general_o_n==true) ?  $libelle=$libelle_general."<br/>" : $libelle=""  ;
		($general_o_n==false) ?
		$ligne[]="<b>".$row[0]["nom_organisme"]."</br>".$row[0]["libelle_rencontre"] ."</br>(".$row[0]["date_debut"] .")</br></br>$sujet" :
		$ligne[]="<b>".$row[0]["nom_organisme"]."</br></br>$sujet</br>$libelle"
		;


		return $ligne;
	}
	function get_upload_dir($idrencontre)
	{
		$db = &atkGetDb();
		$sql="select o.id from organisme o, organisme_rencontre r  where r.id=$idrencontre and r.id_organisme=o.id";
		$data=$db->getrows($sql);
		$uploaddir = atkconfig("uploads_organismes_dir").$data[0]["id"]."/";
		if (!file_exists($uploaddir))
		{
			mkdir($uploaddir);
		}
		return $uploaddir;
	}

	function stocker_document_individu($titre, &$res, $type)
	{
		$filename=$this->getUserFileName($titre,'html',$filenameshort,null);
		$filecontent = base64_encode($res);
		$size=strlen($filecontent);
		$fileextension = strtolower(substr($filename, strrpos($filename, '.') + 1, strlen($filename)));
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$data1=$db->getrows("Select id_individu from app_utilisateur where id=$userid");
		$idindividu=$data1[0]["id_individu"];
		$id_record=$db->nextid('seq_individu_document');
		$db->query("INSERT into individu_document
				(id,
				id_individu,
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
				'$idindividu',
				'$filenameshort',
				'$type' ,
				'$filenameshort',
				'$fileextension',
				'$size',
				'$filecontent',
				'$userid',
				'$userid'
				,UTC_TIMESTAMP(),
				UTC_TIMESTAMP())");
		return $id_record;
	}
	function action_compte_rendu() {
		$cle=$this->m_postvars['atkfilter'];

		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("organisme_rencontre");
		$query->addJoin("organisme", "", "organisme_rencontre.id_organisme = organisme.id", false);
		$query->addJoin("type_rencontre", "", "organisme_rencontre.id_type_rencontre = type_rencontre.id", false);
		$query->addJoin("organisme_groupe_travail", "", "organisme_rencontre.id_groupe_travail = organisme_groupe_travail.id", true);
		$query->addJoin("organisme_lieu_rencontre", "", "organisme_rencontre.id_lieu_rencontre = organisme_lieu_rencontre.id", true);
		$query->addJoin("lieu", "", "organisme_lieu_rencontre.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addField("organisme.nom as organisme");
		$query->addField("type_rencontre.libelle as type_rencontre");
		$query->addField("organisme_groupe_travail.nom as groupe_travail");
		$query->addField("organisme_lieu_rencontre.libelle as lieu_rencontre");
		$query->addField("organisme_lieu_rencontre.telephone as lieu_telephone");
		$query->addField("organisme_rencontre.libelle as rencontre");
		$query->addField("organisme_rencontre.date_debut as date_debut");
		$query->addField("organisme_rencontre.heure_debut as heure_debut");
		$query->addField("organisme_rencontre.date_fin as date_fin");
		$query->addField("organisme_rencontre.heure_fin as heure_fin");
		$query->addField("organisme_rencontre.preparation");
		$query->addField("organisme_rencontre.conclusion");
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("lieu.adresse2 as adresse2");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_cp_ville_pays.province_etat as province");
		$query->addField("type_pays.libelle_anglais as pays");


		$query->addCondition($cle);
		$sql = $query->buildSelect();
		$stufforganisme = $db->getrows($sql);




		$res="Compte rendu ".'<br />';
		$res.="Rencontre : ".$stufforganisme[0]["rencontre"].'<br />';
		if ($stufforganisme[0]["groupe_travail"]!="")
		{
			$res.="Groupe de travail : ".$stufforganisme[0]["groupe_travail"].'<br />';
		}
		$res.="Type réunion : ".$stufforganisme[0]["type_rencontre"].'<br />';
		$res.="Organisme : ".$stufforganisme[0]["organisme"].'<br />';
		if ($stufforganisme[0]["lieu_rencontre"]!="")
		{
			$res.="Lieu : ".$stufforganisme[0]["lieu_rencontre"].'<br />';
			$res.="".$stufforganisme[0]["adresse1"].'<br />';
			if ($stufforganisme[0]["adresse2"]!="")
			{
				$res.="".$stufforganisme[0]["adresse2"].'<br />';
			}
			$res.="".$stufforganisme[0]["code_postal"].' '.$stufforganisme[0]["ville"].'<br />';
			if ($stufforganisme[0]["lieu_telephone"]!="")
			{
				$res.="".$stufforganisme[0]["lieu_telephone"].'<br />';
			}
		}
		$res.="Date : ".$stufforganisme[0]["date_debut"]." à ".$stufforganisme[0]["heure_debut"].'<br />';
		//	$res.="Fin : ".$stufforganisme[0]["date_fin"]." à ".$stufforganisme[0]["heure_fin"].'<br />';
		$res.="Participants : ".'<br />';
		$id_rencontre = explode('=', $cle);
		$id_rencontre = $id_rencontre[1];

		$query = & $db->createQuery();
		$query->addTable("individu_rencontre");
		$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
		$query->addJoin("organisme", "", "individu_rencontre.id_organisme_participant = organisme.id", true);
		$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("organisme.nom as organisme_participant");
		$query->addField("type_rencontre_participation.libelle as participation");
		$query->addField("individu_rencontre.commentaire as commentaire");
		$query->addCondition("individu_rencontre.id_rencontre=".$id_rencontre);
		$query->addOrderBy(" type_rencontre_participation.libelle, individu.nom, individu.prenom");
		$sql = $query->buildSelect();
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

			$row[] = $stuff[$i]["participation"];
			$row[] = $stuff[$i]["nom"];
			$row[] = $stuff[$i]["prenom"];
			$row[] = $stuff[$i]["organisme_participant"];
			$row[] = $stuff[$i]["commentaire"];
			$data[] = $row;
		}
		// render table.
		$res .= $tbl->render($data, 0, "recordlist");
		$res.="<br />";
		if ($stufforganisme[0]["preparation"]!="")
		{
			$res.="<b>PREPARATION DEBUT</b><br />";
			$res.=$stufforganisme[0]["preparation"];
			$res.="<b>PREPARATION FIN</b><br />";
		}
		if ($stufforganisme[0]["conclusion"]!="")
		{
			$res.="<b>CONCLUSION DEBUT</b><br />";

			$res.=$stufforganisme[0]["conclusion"];
			$res.="<b>CONCLUSION FIN</b><br />";
		}
		$res.="le ".gmdate('d/m/Y')."<br />";

		global $g_user;
		$userutilisateur = $g_user["id"];

		$db->getrows("UPDATE organisme_rencontre set conclusion='".escapeSQL($res)."'
				,  id_modification=".$userutilisateur." where ".$cle);

		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		//				$res .= '<br><div align="right"><a href="javascript:window.close();">' . atktext("close") . '</a></div>';
		$page->addContent($res);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		// $output->outputFlush();
		// hf

	}

	function action_m_inscrire() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		global $g_sessionManager;
		$id_individu_1 = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");

		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$id_rencontre = explode('=', $id_variable);
			$id_rencontre1 = $id_rencontre[1];
			$requete = "INSERT INTO individu_rencontre
					(  id_individu,id_rencontre,id_type_rencontre_participation,
					commentaire, id_creation, date_creation, id_modification, date_modification, date_inscription )  " . "
					VALUES( '$id_individu_1' ,$id_rencontre1,'5',
					'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP(), UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
			$db->query($requete);
			$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_rencontre' ");


		}
		//			$this->redirect();

	}

	function action_individus_supprimer() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$resultat="";


		foreach ($select as $id_variable) {
			$id_rencontre = explode('=', $id_variable);
			$id_rencontre1 = $id_rencontre[1];
			$db = & atkGetDb();
			$sql='SELECT libelle as libelle from organisme_rencontre
					where id='.$id_rencontre1.' ';
			$data=$db->getrows($sql);
			$rencontre=$data[0]["libelle"];
			$this->m_resultats_suppression.="Rencontre : ".$rencontre."<br />";

			$this->individus_supprimer($id_rencontre1);
		}
		echo $this->m_resultats_suppression;
		die();


	}
	function action_joueurs_supprimer() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$id_rencontre = explode('=', $id_variable);
			$id_rencontre1 = $id_rencontre[1];
			$requete = "DELETE FROM individu_carte_golf
					where id_rencontre=".$id_rencontre1."";
			$db->query($requete);
		}
		echo "Suppression joueurs effectuée.";
		die();


	}


	function individus_supprimer($idrencontre)
	{
		$db = & atkGetDb();
		$sql='SELECT count(id) as nombre_total from individu_rencontre
				where id_rencontre='.$idrencontre.' ';
		$data=$db->getrows($sql);
		$nombre_total=$data[0]["nombre_total"];
		$sql='SELECT count(id) as nombre_suppression from individu_rencontre
				where id_rencontre='.$idrencontre.'
						and id_document_intervenant is null
						and id_reglement is null
						and id_rapport_activite is null
						and id_ecriture_participation is null
						and id_ecriture_reglement is null ';
		$data=$db->getrows($sql);
		$nombre_suppression=$data[0]["nombre_suppression"];

		$requete = "DELETE FROM individu_rencontre
				where id_rencontre=".$idrencontre."
						and id_document_intervenant is null
						and id_reglement is null
						and id_rapport_activite is null
						and id_ecriture_participation is null
						and id_ecriture_reglement is null ";
		$db->query($requete);
		$this->m_resultats_suppression.=$nombre_suppression." Participants supprimés <br />";
		$this->m_resultats_suppression.=$nombre_total-$nombre_suppression." Participants non supprimés (données ) <br />";

		return true ;
	}
	function action_rencontres_supprimer() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}

		foreach ($select as $id_variable) {
			$id_rencontre = explode('=', $id_variable);
			$id_rencontre1 = $id_rencontre[1];

			$db = & atkGetDb();
			$sql='SELECT libelle as libelle from organisme_rencontre
					where id='.$id_rencontre1.'';
			$data=$db->getrows($sql);

			$rencontre=$data[0]["libelle"];
			$this->m_resultats_suppression.=" Rencontre : ".$rencontre.'<br />';

			$this->individus_supprimer($id_rencontre1);
			if ($this->rencontre_supprimer($id_rencontre1)==true)
			{
				$this->m_resultats_suppression.=" Rencontre : supprimée <br />";
			}

		}
		$messagefin="Suppression de rencontres : <br />".$this->m_resultats_suppression;
		$messagefin.="<br />ATTENTION : Il faudra peut-être regénérer des calendriers externes".

				$this->setFeedback("rencontres_supprimer",ACTION_SUCCESS);
		$location = $this->feedbackUrl("rencontres_supprimer", ACTION_SUCCESS, "", $messagefin);
		$this->redirect($location);


	}
	function rencontre_supprimer($idrencontre)
	{
		$db = & atkGetDb();
		$sql="SELECT count(id) as nombre , date_debut , id_groupe_travail FROM organisme_rencontre
				where id=".$idrencontre."
						and id not in (select id_rencontre from individu_rencontre )";
		$data=$db->getrows($sql);


		$nombre=$data[0]["nombre"];
		$idgroupetravail=$data[0]["id_groupe_travail"];
		$datedebut=$data[0]["date_debut"];
		if ($nombre==0)
		{
			return false;
		}

		$requete = "DELETE FROM organisme_calendrier_element
				where id_rencontre=".$idrencontre."
						and id_rencontre not in (select id_rencontre from individu_rencontre ) ";
		$db->query($requete);

		$requete = "DELETE FROM organisme_rencontre
				where id=".$idrencontre."
						and id not in (select id_rencontre from individu_rencontre ) ";
		$db->query($requete);
		global $g_user;
		$userid = $g_user["id"];
		if ($idgroupetravail>0)
		{
			$sql="INSERT

			INTO
			scheduler_cyclus_not
			( id_groupe_travail, date_exception, commentaire, id_creation, date_creation, id_modification, date_modification)
			VALUES
			( $idgroupetravail,
			'$datedebut',

			'',
			'$userid',
			UTC_TIMESTAMP(),
			'$userid',
			UTC_TIMESTAMP())
			";
			$db->query($sql);
		}
		return true;
	}

	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}

	function getViewPlusMois() {
		global $g_sessionManager;
		$viewplusmois = $g_sessionManager->stackVar("viewplusmois");
		if ($viewplusmois == "") {
			$viewplusmois = "nonactive";
		}
		return $viewplusmois;
	}

	function getViewRoutine() {
		global $g_sessionManager;
		$viewroutine = $g_sessionManager->stackVar("viewroutine");
		if ($viewroutine == "") {
			$viewroutine = "active";
		}
		return $viewroutine;
	}

	// GG fin
	function descriptor_def() {
		//		return "[date_debut.year]-[date_debut.month]-[date_debut.day] - [id_organisme.nom] - [libelle] ";
		return "[libelle]";
	}
	function rowColor($record) {
		include_once (moduleDir("utils") . "class.dateutil.inc");
		$curdate = date("Ymd");
		$datedebut = $record['date_debut']["year"] . $record['date_debut']["month"] . $record['date_debut']["day"];
		$datefin = $record['date_fin']["year"] . $record['date_fin']["month"] . $record['date_fin']["day"];
		/*
		 print_r($record);
		print($curdate);
		print($datedebut);
		print($datefin);
		print(dateutil::date_diff( $datedebut,$curdate));
		die();
		*/
		if ($curdate > $datefin)
			return $this->couleurarchive;
		if (dateutil :: date_diff($curdate, $datedebut) < 8)
			return $this->couleursemaine;
		if (dateutil :: date_diff($curdate, $datedebut) > 7 and dateutil :: date_diff($curdate, $datedebut) < 31) {
			return $this->couleurmois;
		} else {
			return $this->couleurplusmois;
		}
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		$view = $this->getView();
		if ($view == "active") {
			$this->addFilter("ADDDATE(organisme_rencontre.date_fin,365) > UTC_DATE");
		}
		$viewroutine = $this->getViewRoutine();
		if ($viewroutine == "active") {
			$this->addFilter(" organisme_rencontre.id_type_rencontre not in ( select id from type_rencontre where routine_o_n ='1') ");
		}

		/*
		 *
		$viewplusmois = $this->getViewPlusMois();
		if ($viewplusmois == "nonactive") {
		$this->addFilter("SUBDATE(organisme_rencontre.date_fin,30) < UTC_DATE");
		}
		*/
		return $handler->action_admin();
	}

	function adminHeader()
	{
		$retour=parent::adminHeader();
		if ($this->m_postvars['atkorigine']=="liste_organismes_participants" || $this->m_postvars['atkorigine']=="comptabilite")
		{
			return $retour;
		}
		$db = & atkGetDb();
		$filter=$this->m_postvars['atkfilter'];
		$pos=strpos($filter, " and ");
		($pos>0) ?	$filter=substr($filter,0, $pos) : null;
		$filter=substr($filter,0, $pos);
		$arg=explode("=", $filter);
		if (strstr($arg[0],"id_organisme_parcours")==true || $filter=="" )
		{
			return $retour;
		}
		if       	(strstr($arg[0],"id_organisme")!=false )
		{
			$sql="SELECT organisme.nom as texte from  organisme
					where  id=".$arg[1]."  ";
			$preface="Rencontres de ";

		}
		else if (strstr($arg[0],"id_groupe_travail")!=false )
		{
			$sql="SELECT  CONCAT('Rencontres du groupe de travail : ',organisme_groupe_travail.nom, ' de ',organisme.nom) as texte from   organisme_groupe_travail , organisme
					where  organisme_groupe_travail.id=".$arg[1]."  and organisme_groupe_travail.id_organisme=organisme.id" ;
			$preface="";
		}
		else if (strlen($arg[1])<400)
		{
			$sql="SELECT organisme_rencontre.libelle as texte from  organisme_rencontre
					where   id=".$arg[1]." ";
			$preface="Rencontre : ";
		}


		$data=$db->getrows($sql);
		if (count($data)!=0 &&strlen($arg[1])<400)
		{
			return $retour.$preface.$data[0]["texte"].'<br />';
		}
		else return $retour;
	}

	function adminFooter() {
		$retour=parent::adminFooter();
		$view = $this->getView();
		$viewplusmois = $this->getViewPlusMois();
		$viewroutine = $this->getViewRoutine();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive ou terminée depuis un an ';
		$legende .= '<font color="' . $this->couleursemaine . '"> <b> Déjà commencé ou dans la semaine ';
		$legende .= '<font color="' . $this->couleurmois . '"> <b> Dans le mois';
		$legende .= '<font color="' . $this->couleurplusmois . '"> <b> Au delà du mois';
		$texte="<b>";
		/*
		 *
		if ($viewplusmois == "active")
		{
		$texte.=  " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&viewplusmois=nonactive', atktext('Cacher les rencontres au delà du mois', $this->m_module, $this->m_type));
		}
		else {
		$texte.=" " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&viewplusmois=active', atktext('Montrer les rencontres au delà du mois', $this->m_module, $this->m_type));
		}
		$texte.="<br>";
		*/
		if ($viewroutine == "active")
		{
			$texte.=  " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&viewroutine=nonactive', atktext('Montrer les rencontres de routine', $this->m_module, $this->m_type));
		}
		else {
			$texte.=" " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&viewroutine=active', atktext('Cacher les rencontres de routine', $this->m_module, $this->m_type));
		}
		$texte.="<br>";

		if ($view == "active") {
			$texte.=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('Montrer les archives (finies depuis plus d\'un an)', $this->m_module, $this->m_type)) ;
		} else {
			$texte.=  href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('Cacher les archives (finies depuis plus d\'un an)', $this->m_module, $this->m_type))  ;
		}

		$texte.="<br>" . $legende . $retour;
		$texte.="</b>";
		return $texte;
	}
	function initial_values() {
		$init_vals = array ();
		$init_vals["date_debut"]["day"]= gmdate('d');
		$init_vals["date_debut"]["month"]= gmdate('m');
		$init_vals["date_debut"]["year"]= gmdate('Y');
		$init_vals["date_fin"]["day"]= gmdate('d');
		$init_vals["date_fin"]["month"]= gmdate('m');
		$init_vals["date_fin"]["year"]= gmdate('Y');
		$init_vals["heure_debut"]["hours"] = "09";
		$init_vals["heure_debut"]["minutes"] = "00";
		$init_vals["heure_fin"]["hours"] = "20";
		$init_vals["heure_fin"]["minutes"] = "00";
		$init_vals['duration']="60";
		return $init_vals;
	}

	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		$actions["delete"] ="";
		$actions["m_inscrire"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=m_inscrire&atkselector=[pk]", SESSION_NESTED);
		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		$actions["liste_participants"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=liste_participants&atkselector=[pk]", SESSION_NESTED);
		$actions["balance_carree"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=balance_carree&atkselector=[pk]", SESSION_NESTED);
		
		//		$mraactions['compte_rendu'] = "compte_rendu";
		$mraactions['maj'] = "maj";
		$mraactions['m_inscrire'] = "m_inscrire";
		$mraactions["inscrire_participants_du_presse_papier"] ="inscrire_participants_du_presse_papier";
		$mraactions["individus_supprimer"] ="individus_supprimer";
		$mraactions["rencontres_supprimer"] ="rencontres_supprimer";
		if ($rec["id_organisme_parcours"]["id"]!="")
		{
			$mraactions["inscrire_joueurs_du_presse_papier"] ="inscrire_joueurs_du_presse_papier";
			$mraactions["joueurs_supprimer"] ="joueurs_supprimer";
			$mraactions["golf_tous_les_documents"] ="golf_tous_les_documents";
			$mraactions["golf_les_departs"] ="golf_les_departs";
			$mraactions["golf_les_cartes"] ="golf_les_cartes";
			$mraactions["golf_le_classement_net"] ="golf_le_classement_net";
			$mraactions["golf_le_classement_brut"] ="golf_le_classement_brut";
		}

		$mraactions['liste_organismes_participants'] = "liste_organismes_participants";

	}

	function action_inscrire_joueurs_du_presse_papier()
	{
		$this->inscrire_du_presse_papier("joueur");
	}
	function action_inscrire_participants_du_presse_papier()
	{
		$this->inscrire_du_presse_papier("participant");
	}

	function inscrire_du_presse_papier($type="participant") {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		global $g_sessionManager;
		//		$id_individu_1 = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$requete = "SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$data = $db->getrows($requete);
		//		$this->p($data);
		if (count($data) == 0) {
			$db->commit();
			$this->redirect();
		}
		foreach ($select as $id_variable) {
			$id_rencontre = explode('=', $id_variable);
			$id_rencontre_1 = $id_rencontre[1];
			$id_rencontre_1 =str_replace("'", "", $id_rencontre_1);

			foreach ($data as $id_individu) {
				$id_individu_1 = $id_individu["id_variable"];
				if ($type=="participant")
				{
					$requete = "INSERT INTO individu_rencontre
							(  id_individu,id_rencontre,id_type_rencontre_participation,
							commentaire, id_creation, date_creation, id_modification, date_modification, date_inscription )  " . "
							VALUES( '$id_individu_1' ,$id_rencontre_1,'5',
							'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP(), UTC_TIMESTAMP())
							ON DUPLICATE KEY UPDATE id_modification=id_modification ";
					$db->query($requete);
					$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_rencontre' ");
				}
				if ($type=="joueur")
				{
					$carte_node = & getNode("individu.carte_golf");
					$record=array();
					$sql="select id_organisme_parcours, date_debut, heure_debut from organisme_rencontre where id=$id_rencontre_1";
					$dbrencontre = & atkGetDb();
					$rencrec=$dbrencontre->getrows($sql);
					$id_organisme_parcours=$rencrec[0]['id_organisme_parcours'];
					$date_debut=$rencrec[0]['date_debut'];
					$heure_debut=$rencrec[0]['heure_debut'];
					$record["id_individu"]["id"]=$id_individu_1;
					$record["id_rencontre"]["id"]=$id_rencontre_1;
					$record["id_organisme_parcours"]["id"]=$id_organisme_parcours;
					$record["date_depart"]=$date_debut;
					$record["heure_depart"]=$heure_debut;
					//					$this->p($record);
					$carte_node->addDb($record);

					/*

					$requete = "INSERT INTO individu_carte_golf
					(  id_individu,id_rencontre,id_organisme_parcours, date_depart, heure_depart,
							commentaire, id_creation, date_creation, id_modification, date_modification )  " . "
					VALUES( '$id_individu_1' ,$id_rencontre_1,'$id_organisme_parcours','$date_debut', '$heure_debut',
							'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
					$db->query($requete);
					$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_carte_golf' ");
					*/
				}

			}
		}

		$requete = "DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

	/*
	 function recordActions($rec, &$actions, &$mraactions)
	 {  parent::recordActions($rec, $actions, $mraactions);

	$actions["liste_participants"] = session_url("dispatch.php?atknodetype=".$this->atkNodeType()."&atkaction=liste_participants&atkselector=[pk]", SESSION_NESTED);
	}
	*/

	function validate(&$record, $mode)
	{
		$debut=$record["date_debut"]["year"].$record["date_debut"]["monh"].$record["date_debut"]["day"].
		$record["heure_debut"]["hour"].$record["heure_debut"]["min"];
		$fin=$record["date_fin"]["year"].$record["date_fin"]["monh"].$record["date_fin"]["day"].
		$record["heure_fin"]["hour"].$record["heure_fin"]["min"];
		if ($fin<$debut)
		{
			triggerError($record, "date_fin", "Date de fin antérieure à la date de début");
		}
		if (parent::validate($record, $mode)==true)
		{return true;}
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	/*		function id_organisme_parcours_display($record, $mode) {
	 (!empty($record["id_organisme_parcours"])) ? $retour=$this->descripteur_organisme($record["id_organisme_parcours"]["id"],'n') : $retour="";
	return $retour;
	}
	*/
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_rencontre", "ore", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		ore.id as id_entite,
		ore.id as id_rencontre,
		ore.libelle,
		tr.libelle as type_rencontre,
		ore.date_debut,
		TIME_FORMAT(ore.heure_debut,'%k:%i') as heure_debut,
		ore.date_fin,
		TIME_FORMAT(ore.heure_fin,'%k:%i') as heure_fin,
		DATE(ore.date_cloture) as date_cloture,
		ore.id_lieu_rencontre,
		ore.lieu_texte,
		ore.libelle_participation_1,
		ore.libelle_participation_2,
		ore.libelle_participation_3,
		ore.libelle_participation_4,
			
		o.id as id_organisme,
		o.nom as organisme
		from
		organisme_rencontre ore
		LEFT JOIN type_rencontre tr ON ore.id_type_rencontre=tr.id
		LEFT JOIN organisme o ON ore.id_organisme=o.id
		where
		$filtre
		order by ore.date_debut desc	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Rencontre</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Dates/Lieu</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Documents</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Participation</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Dépenses</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$res2.= "<tr><td>".($i+1);
			
			$res2.='</td><td><b>'.$data[$i]["libelle"];
			$res2.='</td><td><b>'.$data[$i]["type_rencontre"];
			$res2.='</td><td></b>Du : <b>'.$data[$i]["date_debut"]." ".$data[$i]["heure_debut"]."<br/>"
					.'</b>Au : <b>'.$data[$i]["date_fin"]." ".$data[$i]["heure_fin"].'<br/>'
							.'</b>Clôture : <b>'.$data[$i]["date_cloture"].'<br/>';

			if ($data[$i]["id_lieu_rencontre"]>0)
			{
				$res2.='</b>Lieu : <b>'.$data[$i]["lieu_texte"]."<br/>".$this->descripteur_lieu_rencontre_lieu($data[$i]["id_lieu_rencontre"],'n','o');
			}
			else
			{
				$res2.='</b>Lieu : <b>'.$data[$i]["lieu_texte"];
			}
			$res2.='</td><td>'.$this->descripteur_rencontre_documents($data[$i]["id_rencontre"],"n")."<br/>";
			$res2.='</td><td>'.$this->descripteur_rencontre_participation($data[$i]["id_rencontre"]);
			$res2.='</td><td>'.$this->descripteur_rencontre_fournisseurs_sans_lien($data[$i]["id_rencontre"])."<br/>";
			$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');

			$res2.='</td></tr>';
		}
		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');

		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Rencontres"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/>";

		$res2=$titre.$res2;
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
		$page->addContent($res2);
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
	}


}
?>
