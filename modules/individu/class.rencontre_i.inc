<?php
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgtextlibelleattribute");
class rencontre_i extends assMetaNode {
	var $table = "individu_rencontre";
	function meta(& $policy) {
		//$policy-> addFlags("annee",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("id_ecriture_participation", "id_ecriture_reglement", AF_HIDE_EDIT);
		$policy->addFlags("participation_partielle", "participation_complete", "montant_versement", "covoiturage_places_offertes","covoiturage_places_demandees", AF_TOTAL);
	}
	function rencontre_i() {
		$this->atkMetaNode();
		$this->atkNode("rencontre_i", NF_ADD_LINK | NF_TRACK_CHANGES |NF_ADDAFTERADD | NF_MRA  | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id",
						"id_rencontre",
						"descripteur_rencontre",
						"descripteur_participant_rencontre",
						"nom_organisme",
						"date_debut_rencontre",
						"date_fin_rencontre",
						"id_individu",
						"date_inscription",
						"id_type_rencontre_participation",
						//			"option_1",
						//			"participation_partielle",
						"g_participants_1",
						"g_participants_2",
						"g_participants_3",
						"g_participants_4",
						"options",
						"choix",
						/*			"group2",
						 "group3",
		"group4",
		"option_2",
		"participation_complete",
		"option_3",
		"participation_3",
		"option_4",
		"participation_4",
		*/			"id_organisme_participant",

						"id_document_inscription_rencontre",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Participation financière" => array (

						"descripteur_reglement",
						"montant_versement",
						"date_reglement",
						"id_reglement",
						"id_banque",
						"numero_cheque","ecritures",
						"id_ecriture_participation",
						"id_ecriture_reglement",

						"presence_compta"
				),
				"Second règlement" => array (
						"montant_versement_2",
						"date_reglement_2",
						"id_reglement_2",
						"id_banque_2",
						"numero_cheque_2",
						"id_ecriture_participation_2",
						"id_ecriture_reglement_2",
				),
				"Intervenant" => array (

						"intervenant_o_n",
						"theme_intervention",
						"id_document_intervenant"
				),
				"Covoiturage" => array (
						"covoiturage_places_offertes",
						"covoiturage_places_demandees"
				),
				"Rapport activité" => array (
						"id_rapport_activite"
				)

		), AF_NO_LABEL));
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkAttribute("id",0,AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD));
		$attr = $this->add(new atkManyToOneRelation("id_rencontre", "organisme.rencontre", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE |AF_FORCE_LOAD),NULL,115);
		$this->add(new atkParserAttribute("presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST), NULL, 1);
		$this->add(new atkAttribute("id",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,120);
		$this->add(new atkDummyAttribute("descripteur_rencontre","",AF_HIDE_ADD|AF_HIDE_EDIT|AF_COMPACT),NULL,45);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),NULL,111);
		$this->add(new atkManyToOneRelation("id_organisme_participant", "organisme.organisme", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),NULL,100);
		$this->add(new atkDummyAttribute("descripteur_participant_rencontre","", AF_HIDE_ADD|AF_HIDE_EDIT|AF_COMPACT),NULL, 10);
		$this->add(new atkDummyAttribute("descripteur_reglement","",AF_HIDE_ADD|AF_HIDE_EDIT),NULL, 50);
		$this->add(new atkBoolAttribute("intervenant_o_n"),NULL,500);
		$this->add(new atgTextLibelleAttribute("theme_intervention", AF_SEARCHABLE), NULL, 501);
		$this->add(new atkManyToOneRelation("id_type_rencontre_participation", "table.type_rencontre_participation", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY|AF_FORCE_LOAD),NULL,210);
		$this->add(new atkDateAttribute("date_inscription", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),NULL,112);
		$this->add(new atkManyToOneRelation("id_document_inscription_rencontre", "organisme.document", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),NULL,701);
		$this->addFieldSet("g_participants_1","[participation_partielle.field] <b>([option_1.field])</b> ",0,NULL,750 );
		$this->addFieldSet("g_participants_2","[participation_complete.field] <b>([option_2.field])</b> ",0,NULL,750 );
		$this->addFieldSet("g_participants_3","[participation_3.field] <b>([option_3.field])</b> ",0,NULL,750 );
		$this->addFieldSet("g_participants_4","[participation_4.field] <b>([option_4.field])</b> ",0,NULL,750 );
		$this->add(new atgNoStorageAttribute("options",AF_HIDE_ADD|AF_HIDE_EDIT,0),NULL,44);
		$this->add(new atgNoStorageAttribute("choix",AF_HIDE_ADD|AF_HIDE_EDIT|AF_COMPACT,0),NULL,43);

		$this->add(new atkExpressionAttribute("option_1", ' select libelle_participation_1 from organisme_rencontre where id=[table].id_rencontre '),AF_READONLY,749);
		$this->add(new atkAttribute("participation_partielle",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,750);
		$this->add(new atkExpressionAttribute("option_2", ' select libelle_participation_2 from organisme_rencontre where id=[table].id_rencontre '),AF_READONLY,751);
		$this->add(new atkAttribute("participation_complete",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,752);
		$this->add(new atkExpressionAttribute("option_3", ' select libelle_participation_3 from organisme_rencontre where id=[table].id_rencontre '),AF_READONLY,753);
		$this->add(new atkAttribute("participation_3",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,754);
		$this->add(new atkExpressionAttribute("option_4", ' select libelle_participation_4 from organisme_rencontre where id=[table].id_rencontre '),AF_READONLY,755);
		$this->add(new atkAttribute("participation_4",AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),NULL,756);


		$this->add(new atkNumberAttribute("montant_versement", AF_TOTAL, 12, 2), NULL, 899);
		$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),NULL,900);
		$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD),NULL,1000);
		$this->add(new atkManyToOneRelation("id_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK|AF_FORCE_LOAD),NULL,1100);
		$this->add(new atkAttribute("numero_cheque",NULL,20),NULL,1110);
		$this->add(new atkDummyAttribute("ecritures"),NULL,1120);
		$this->add(new atkAttribute("id_ecriture_participation"),NULL,51);
		$this->add(new atkAttribute("id_ecriture_reglement"),NULL,52);

		$this->add(new atkNumberAttribute("montant_versement_2", AF_TOTAL, 12, 2), NULL, 1150);
		$this->add(new atkDateAttribute("date_reglement_2", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),NULL,1160);
		$this->add(new atkManyToOneRelation("id_reglement_2", "table.reglement", AF_SEARCHABLE | AF_RELATION_AUTOLINK),NULL,1170);
		$this->add(new atkManyToOneRelation("id_banque_2", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK),NULL,1180);
		$this->add(new atkAttribute("numero_cheque_2",NULL,20),NULL,1190);
		//	$this->add(new atkDummyAttribute("ecritures"),NULL,1200);
		$this->add(new atkAttribute("id_ecriture_participation_2",0,AF_FORCE_LOAD),NULL,53);
		$this->add(new atkAttribute("id_ecriture_reglement_2",0,AF_FORCE_LOAD),NULL,54);

		$this->add(new atgFileManyToOneRelation("id_document_intervenant", "organisme.document", AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE,0,AF_FORCE_LOAD),NULL,325);
		$rapp=$this->add(new atkOneToManyRelation("id_rapport_activite", "individu.activite_i" ,"id_individu_rencontre", AF_FORCE_LOAD),NULL,800);
		$rapp->setDestinationFilter("[pk]");
		$rapp->setUseFilterForAddLink(true);
		$this->add(new atkExpressionAttribute("date_debut_rencontre", ' select CONCAT(organisme_rencontre.date_debut," ", organisme_rencontre.heure_debut) from organisme_rencontre
				where id=[table].id_rencontre
				', 0, AF_FORCE_LOAD),NULL,310);
		$this->add(new atkExpressionAttribute("nom_organisme", ' select o.id from organisme o , organisme_rencontre ore
				where ore.id=[table].id_rencontre and ore.id_organisme=o.id
				', 0, 0),NULL,110);
		$this->add(new atkExpressionAttribute("date_fin_rencontre", ' select CONCAT(organisme_rencontre.date_fin," ", organisme_rencontre.heure_fin) from organisme_rencontre
				where id=[table].id_rencontre
				', 0, AF_FORCE_LOAD),NULL,320);
		$this->add(new atkNumberAttribute("covoiturage_places_offertes", AF_TOTAL, 3, 0),NULL,321);
		$this->add(new atkNumberAttribute("covoiturage_places_demandees", AF_TOTAL, 3, 0),NULL,322);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,55 );
		//		$this->setOrder("id_rencontre.date_debut desc,id_individu.nom,id_individu.prenom");
		//		$this->setOrder(" organisme_rencontre.date_debut desc ");
		$this->setOrder("individu_rencontre.id_individu asc , date_debut_rencontre desc ");
		//		$this->m_securityMap["participation"] = "participation";
		$this->m_securityMap["inscrit"] = "view";
		$this->m_securityMap["organisme_participant"] = "view";
		$this->m_securityMap["present"] = "view";
		$this->m_securityMap["excuse"] = "view";
		$this->m_securityMap["pouvoir"] = "view";
		$this->m_securityMap["absent"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		$this->m_securityMap["maj"] = "view";

	}
	function option_1_edit($record, $mode)
	{
		return $this->getAttribute('option_1')->display($record,"" ,$mode);
	}
	function option_2_edit($record, $mode)
	{
		return $this->getAttribute('option_2')->display($record,"" ,$mode);
	}
	function option_3_edit($record, $mode)
	{
		return $this->getAttribute('option_3')->display($record,"" ,$mode);
	}
	function option_4_edit($record, $mode)
	{
		return $this->getAttribute('option_4')->display($record,"" ,$mode);
	}

	function initial_values() {
		$init_vals = array ();
		//			$this->p($this->m_postvars);
		$rencontre_i = explode('=', $this->m_postvars['atkfilter']);
		if ($rencontre_i[0] == 'individu_rencontre.id_rencontre') {
			$id_rencontre_i = $rencontre_i[1];
			$db = & atkGetDb();
			$data = $db->getrows("select libelle_participation_1, libelle_participation_2, libelle_participation_3, libelle_participation_4
					from organisme_rencontre where id=$id_rencontre_i");
			$init_vals["option_1"] = $data[0]["libelle_participation_1"];
			$init_vals["option_2"] = $data[0]["libelle_participation_2"];
			$init_vals["option_3"] = $data[0]["libelle_participation_3"];
			$init_vals["option_4"] = $data[0]["libelle_participation_4"];
		} else {
			null;
		}
		return $init_vals;
	}
	function participation_partielle_edit($record,$prefix, $mode)
	{
		if ($record["participation_partielle"]<="0") {
			$record["participation_partielle"]="";
		}
		return $this->getAttribute('participation_partielle')->edit($record,$prefix ,$mode);
	}
	function participation_complete_edit($record,$prefix, $mode)
	{
		if ($record["participation_complete"]<="0") {
			$record["participation_complete"]="";
		}
		return $this->getAttribute('participation_complete')->edit($record,$prefix ,$mode);
	}
	function participation_3_edit($record,$prefix, $mode)
	{
		if ($record["participation_3"]<="0") {
			$record["participation_3"]="";
		}
		return $this->getAttribute('participation_3')->edit($record,$prefix ,$mode);
	}
	function participation_4_edit($record,$prefix, $mode)
	{
		if ($record["participation_4"]<="0") {
			$record["participation_4"]="";
		}
		return $this->getAttribute('participation_4')->edit($record,$prefix ,$mode);
	}
	function options_display($record, $mode='list')
	{
		$db = & atkGetDb();
		$id=$record["id"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		$retour="<table>";
		$retour.="<tr><td>Option</td><td>Nombre</td></tr>";

		$sql="SELECT participation_partielle, participation_complete, participation_3, participation_4
		, libelle_participation_1, libelle_participation_2, libelle_participation_3, libelle_participation_4
		from individu_rencontre ire
		LEFT JOIN organisme_rencontre ON ire.id_rencontre=organisme_rencontre.id
		where ire.id=$id";
		$data=$db->getrows($sql);
		$record["option_1"]=$data[0]["libelle_participation_1"];
		$record["option_2"]=$data[0]["libelle_participation_2"];
		$record["option_3"]=$data[0]["libelle_participation_3"];
		$record["option_4"]=$data[0]["libelle_participation_4"];
		($data[0]["participation_partielle"]<=0)? $record["participation_partielle"]="" : $record["participation_partielle"]=$data[0]["participation_partielle"];
		($data[0]["participation_complete"]<=0)? $record["participation_complete"]="" : $record["participation_complete"]=$data[0]["participation_complete"];
		($data[0]["participation_3"]<=0)? $record["participation_3"]="" : $record["participation_3"]=$data[0]["participation_3"];
		($data[0]["participation_4"]<=0)? $record["participation_4"]="" : $record["participation_4"]=$data[0]["participation_4"];
		$retour.="<tr><td>".$this->getAttribute('option_1')->edit($record, $prefix, 'display')."</td>";
		$retour.="<td>".$this->getAttribute('participation_partielle')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>".$this->getAttribute('option_2')->edit($record, $prefix, 'display')."</td>";
		$retour.="<td>".$this->getAttribute('participation_complete')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>".$this->getAttribute('option_3')->edit($record, $prefix, 'display')."</td>";
		$retour.="<td>".$this->getAttribute('participation_3')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="<tr><td>".$this->getAttribute('option_4')->edit($record, $prefix, 'display')."</td>";
		$retour.="<td>".$this->getAttribute('participation_4')->edit($record, $prefix, 'edit')."</td></tr>";
		$retour.="</table>";

		return $retour;
	}
	function choix_display($record, $mode='list')
	{
		$db = & atkGetDb();
		$id=$record["id"];
		$prefix = "data_AE_".$record["id"]."_AE_";
		$retour="<style>
    .alnright { text-align: right; }
</style>
				<table>";
		$retour.="<tr><td><b>Choix</b></td><td><b>PU</b></td><td><b>Nombre</b></td><td><b>Total</b></td></tr>";
	$id_rencontre=$record["id_rencontre"]["id"];
		$sql="SELECT orc.id, orc.libelle, orc.cout
		from organisme_rencontre_choix orc
		where orc.id_rencontre=$id_rencontre" ;
	//	$this->p($sql);
		$data=$db->getrows($sql);
		$total_total=0;
		foreach ($data as $option)
		{
			
			$id_choix=$option["id"];
			$prefix = "data_AE_".$record["id"]."_AE_choix_AE_".$option["id"]."_AE_";
			$sql1="select irc.quantite
			from individu_rencontre_choix irc
			where irc.id_individu_rencontre = $id and
			irc.id_organisme_rencontre_choix=$id_choix ";
//$this->p($sql1);
			$data1=$db->getrows($sql1);
			(count($data1)>0)? $option["quantite"]=$data1[0]["quantite"] : $option["quantite"]=0;
		
			$option["quantite"]=number_format($option["quantite"],0,",",".");
			$option["cout"]=number_format($option["cout"],2,",",".");
			
			$input_quantite='<input type="text" id='.$prefix.'quantite name='.$prefix.'quantite class="atkNumberAttribute" value="'.$option["quantite"].'" 
					size="7" maxlength="7">';
			$total_ligne=$option["quantite"]*$option["cout"];
			$total_total+=$total_ligne;
			$total_ligne=number_format($total_ligne,2,",",".");
			
			$retour.="<tr><td>".$option["libelle"]."</td><td class='alnright'>".$option["cout"]."</td><td class='alnright'>".$input_quantite."</td><td class='alnright'>".$total_ligne."</td>";
			$retour.="</tr>";
			
		}
		
		$total_total_tmp=number_format($total_total,2,",",".");
		
		$retour.="<tr><td><b>Prestations : </b></td><td></td><td></td><td class='alnright'><b>".$total_total_tmp."</b></td></tr>";
		$sql1="select ir.montant_versement,ir.montant_versement_2 
		from individu_rencontre ir
		where ir.id = $id ";
		//$this->p($sql1);
		$data1=$db->getrows($sql1);
		(count($data1)>0 && $data1[0]["montant_versement"]!='')? $montant_versement=$data1[0]["montant_versement"] : $montant_versement=0;
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
	
	function action_maj() {

		$db = & atkGetDb();
		global $g_user;
		$userid = $g_user["id"];
		$selection=$this->get_row_selection_information(false);
		foreach ($selection["node_ids"] as $id)
		{
			$participation_1=escapeSQL($this->m_postvars["data"][$id]["participation_partielle"]) ;
			$participation_2=escapeSQL($this->m_postvars["data"][$id]["participation_complete"]) ;
			$participation_3=escapeSQL($this->m_postvars["data"][$id]["participation_3"]) ;
			$participation_4=escapeSQL($this->m_postvars["data"][$id]["participation_4"]) ;
			( is_numeric($participation_1) || $participation_1=="") ? null: die ("valeur de option 1 non numérique") ;
			( is_numeric($participation_2) || $participation_2=="") ? null: die ("valeur de option 2 non numérique") ;
			( is_numeric($participation_3) || $participation_3=="") ? null: die ("valeur de option 3 non numérique") ;
			( is_numeric($participation_4) || $participation_4=="") ? null: die ("valeur de option 4 non numérique") ;
			$sql="UPDATE individu_rencontre set
			participation_partielle='$participation_1',
			participation_complete='$participation_2',
			participation_3='$participation_3',
			participation_4='$participation_4',
			id_modification=$userid, date_modification=UTC_TIMESTAMP() where id=$id";
			$db->query($sql);
			$tableaukeys=array_keys($this->m_postvars["data"][$id]["choix"]);
//$this->p($this->m_postvars);
			for ($i=0;$i<count($tableaukeys);$i++)

			{
				$option_id=$tableaukeys[$i];
				$quantite=$this->m_postvars["data"][$id]["choix"][$option_id]["quantite"];
				
				if ($quantite=='') {
					$quantite=0;
				}
				$sql1="INSERT INTO individu_rencontre_choix (
						id_individu_rencontre, 
						id_organisme_rencontre_choix, 
						quantite, 
						id_creation, 
						date_creation,
						id_modification, 
						date_modification  ) 
				VALUES (
						$id, 
						$option_id, 
						$quantite, 
						$userid, 
						UTC_TIMESTAMP(),
						$userid, 
						UTC_TIMESTAMP()	)
				ON DUPLICATE KEY UPDATE  
quantite=$quantite, id_modification=$userid, date_modification=UTC_TIMESTAMP()";
	
				$db->query($sql1);
				

			}
		}
		$this->redirect();
			
	}

	function descripteur_reglement_display($record, $mode) {
		$retour=$this->descripteur_reglement('participant_rencontre',$record["id"]).'<br />';
		$retour.=$this->descripteur_reglement('participant_rencontre_2',$record["id"]).'<br />';
		return $retour;
	}
	function descripteur_participant_rencontre_display($record, $mode) {

		return $this->descripteur_participant_rencontre($record["id"]);
	}
	function descripteur_rencontre_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_rencontre($record["id_rencontre"]["id"]),100);
	}
	/*
	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_reglement"]) || isset ($record["id_ecriture_participation"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_participation'] . "'"
			), "dispatch.php"), text("Ecritures comptables"), SESSION_NESTED)."<br />>";
		} else {
			return "";
		}
	}
	function ecritures_2_display($record, $mode) {
		if (isset ($record["id_ecriture_reglement_2"]) || isset ($record["id_ecriture_participation_2"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement_2'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_participation_2'] . "'"
			), "dispatch.php"), text("Ecritures comptables complément"), SESSION_NESTED)."<br />";
		} else {
			return "";
		}
	}
*/
	function modifyDataGrid($grid,$mode)
	{
		if ($mode=='1')
		{
			$db = & atkGetDb();
			(!empty($this->m_postvars['atkfilter'])) ? $filtre=" and ".$this->m_postvars['atkfilter'] : $filtre="" ;
			$sql1="SELECT count(individu_rencontre.id) as nombre from individu_rencontre , organisme_rencontre ore
					where individu_rencontre.id_rencontre=ore.id ".$filtre." and ore.date_debut > CURDATE()";
			$sql2="SELECT count(individu_rencontre.id) as nombre from individu_rencontre , organisme_rencontre ore
					where individu_rencontre.id_rencontre=ore.id ".$filtre."";
			$data=$db->getrows($sql1);
			$nombreavant=$data[0]["nombre"];
			$data=$db->getrows($sql2);
			$nombretotal=$data[0]["nombre"];

			/*			$nombreavant=$this->countDb(" organisme_rencontre.date_debut > CURDATE() ");
			 $nombretotal=$this->countDb();
			*/
			if ($nombretotal<=50) return true;
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

	function rowColor($record) {
		include_once (moduleDir("utils") . "class.dateutil.inc");
		$db = & atkGetDb();
		$sql='select CONCAT(organisme_rencontre.date_debut," ", organisme_rencontre.heure_debut) as d_debut
				, CONCAT(organisme_rencontre.date_fin," ", organisme_rencontre.heure_fin) as d_fin
				from organisme_rencontre
				where id='.$record["id_rencontre"]["id"];
		$data = $db->getrows($sql);
		$curdate = date("Ymd");
		$datedebut = str_replace(('-'), '', $data[0]["d_debut"]);
		$datefin = str_replace(('-'), '', $data[0]["d_fin"]);
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
	function maj_participation($id_participation) {
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
		$idrencontres = str_replace("'", "", $idrencontres);
		$select = explode(",", $idrencontres);
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$db->query("UPDATE individu_rencontre
					set   	id_type_rencontre_participation=$id_participation,
					id_modification=$userid,
					date_modification= UTC_TIMESTAMP()
					WHERE id=$id_variable");
		}
		$db->commit();
		$this->redirect();
	}


	function action_admin(&$handler) {

		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}




	function action_inscrit($handler) {
		$id_participation = 5;
		$this->maj_participation($id_participation);
	}
	function action_present($handler) {
		$id_participation = 1;
		$this->maj_participation($id_participation);
	}
	function action_excuse($handler) {
		$id_participation = 4;
		$this->maj_participation($id_participation);
	}
	function action_pouvoir($handler) {
		$id_participation = 3;
		$this->maj_participation($id_participation);
	}
	function action_absent($handler) {
		$id_participation = 2;
		$this->maj_participation($id_participation);
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);
		$mraactions['maj'] = "maj";
		$mraactions['delete'] = "delete";
		//		$mraactions['participation'] = "participation";
		$mraactions['inscrit'] = "inscrit";
		$mraactions['present'] = "present";
		$mraactions['excuse'] = "excuse";
		$mraactions['pouvoir'] = "pouvoir";
		$mraactions['absent'] = "absent";
		$mraactions['organisme_participant'] = "organisme_participant";

	}


	public function getCustomMraHtml()
	{
		$list = $this->getAttribute('id_organisme_participant')->edit(null,null,null);
		return $list;
	}

	public function action_organisme_participant()
	{
		$organisme = $this->getAttribute('id_organisme_participant')->fetchValue($this->m_postvars);
		if (empty($organisme)) return;
		$idorganisme=$organisme["id"];
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_rencontre set id_organisme_participant='".$idorganisme."'
					,
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}

	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_rencontre
					where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	/*	function adminHeader()
	 {
	$retour=parent::adminHeader();
	if ($this->m_postvars['atkorigine']=="comptabilite")
	{
	return $retour;
	}
	$db = & atkGetDb();

	$filter=$this->m_postvars['atkfilter'];
	$pos=strpos($filter, " and ");
	($pos>0) ?	$filter=substr($filter,0, $pos) : null;
	$arg=explode("=", $filter);

	if       	(strstr($arg[0],"id_organisme_participant")!=false )
	{
	$sql="SELECT organisme.nom as texte from  organisme
	where  id=".$arg[1]."  ";
	$preface="Organisme participant : ";
	$this->setOrder(" date_debut_rencontre desc, individu_rencontre.id_individu asc ");

	}
	if (strstr($arg[0],"id_individu")!=false )
	{
	$sql="SELECT  CONCAT(individu.prenom ,' ',individu.nom) as texte from   individu
	where  id=".$arg[1]." ";
	$preface="Participations de ";
	}
	if (strstr($arg[0],"id_rencontre")!=false )
	{
	(strpos($arg[1],' ')>0) ? $id_rencontre=substr($arg[1], 0,strpos($arg[1],' ')) : $id_rencontre=$arg[1];
	$sql="SELECT organisme_rencontre.libelle as texte from  organisme_rencontre
	where   id=".$id_rencontre." ";
	$preface="Rencontre : ";
	}

	(!empty($sql)) ? $data=$db->getrows($sql) : null;
	if (count($data)!=0)
	{
	return $retour.$preface.$data[0]["texte"].'<br />';
	}
	else return $retour;
	}
	*/


	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive ou terminée depuis 10 jours ';
		$legende .= '<font color="' . $this->couleursemaine . '"> <b> Déjà commencé ou dans la semaine ';
		$legende .= '<font color="' . $this->couleurmois . '"> <b> Dans le mois';
		$legende .= '<font color="' . $this->couleurplusmois . '"> <b> Au delà du mois';
		if ($view == "active") {
			return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>" . $legende . $retour;
		} else {
			return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>" . $legende . $retour;
		}
	}
	function presence_compta_edit($record, $mode) {
		//		$this->p($record);
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
	function id_ecriture_participation_display($record, $mode) {
	//	$retour=$this-> descripteur_ecriture_comptable($record["id_ecriture_participation"])
	//	.$this-> descripteur_ecriture_comptable($record["id_ecriture_participation_2"]);
		$retour="<b>Premier : </b><br />".$this-> descripteur_ecriture_comptable($record["id_ecriture_participation"],'n')
		."<b>Second : </b><br />".$this-> descripteur_ecriture_comptable($record["id_ecriture_participation_2"],'n');;
		if ($retour=="" && ($record["montant_versement"]>0 || $record["montant_versement_2"]>0) )
		{
			$retour="<span style='color:Red'><b>Pas d'écriture</b></span>";
		}
		return $retour;
	}
	function id_ecriture_reglement_display($record, $mode) {
		$retour="<b>Premier : </b><br />".$this-> descripteur_ecriture_comptable($record["id_ecriture_reglement"],'n')
		."<b>Second : </b><br />".$this-> descripteur_ecriture_comptable($record["id_ecriture_reglement_2"],'n');;
		if ($retour=="" && ($record["montant_versement"]>0 || $record["montant_versement_2"]>0) )
		{
			$retour="<span style='color:Red'><b>Pas d'écriture</b></span>";
		}
		return $retour;
	}
	function id_rapport_activite_display($record, $mode)
	{
		$attribute = &$this->getAttribute("id_rapport_activite");
		$original = $attribute->display($record, $mode);

		if ($original==atktext("none"))
		{
			return "";
			/*return href(dispatch_url("individu.activite_i", "add", array (
				'atkfilter' => "individu_activite.id_individu_rencontre='" . $record['id'] . "'"
			), "dispatch.php"), text("Créer"), SESSION_NESTED);

			*/  }
			else
			{return href(dispatch_url("individu.activite_i", "admin", array (
					'atkfilter' => "individu_activite.id_individu_rencontre='" . $record['id'] . "'"
			), "dispatch.php"), text("Ouvrir"), SESSION_NESTED);
			}
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
		$data=$db->getrows('Select max(id) as id from individu_rencontre');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_participation"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_participation"],$this->type_ecriture_participation_rencontre,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_participation_rencontre,$record["id"]);
		}
		if (!empty($record["id_ecriture_participation_2"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_participation_2"],$this->type_ecriture_participation_rencontre,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement_2"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement_2"],$this->type_ecriture_participation_rencontre,$record["id"]);
		}
		return true;
	}
	function validate(&$record, $mode)
	{
		$id_individu = $record['id_individu']['id'];
		$id_rencontre = $record['id_rencontre']['id'];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_rencontre, id_individu  FROM individu_rencontre
				where id_rencontre = $id_rencontre and id_individu=$id_individu");
		$res = $data[0]["id_individu"];
		if (isset ($res)&& $mode=="add") {
			atkTriggerError($record, $this->getAttribute("id_individu"), "Cette personne est déjà inscrite à la rencontre.");
		}
		if ($record["montant_versement"] > 0 || $record["montant_versement"] < 0) {
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
		}
		if ($record["montant_versement_2"] > 0 || $record["montant_versement_2"] <0) {
			if ($record["id_reglement_2"]["id"]==1 && $record["id_banque_2"]["id"]=="")
			{
				atkTriggerError($record, $this->getAttribute("id_banque_2"), "En cas de règlement par chèque il faut préciser la banque");
			}

			if ($record["id_reglement_2"]["id"]!=1 && $record["numero_cheque_2"]!="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque_2"), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque");
			}
			if ($record["id_reglement_2"]["id"]==1 && $record["numero_cheque_2"]=="")
			{
				atkTriggerError($record, $this->getAttribute("numero_cheque_2"), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque");
			}
		}
		if (parent::validate($record, $mode)==true)
		{

			$changement_versement_1=true;
			$changement_versement_2=true;
			if ($mode=="update")
			{
			//	$this->p($record);
				if ( $record["montant_versement_2"]==$record["atkorgrec"]["montant_versement_2"]
						&& $record["date_reglement_2"]==$record["atkorgrec"]["date_reglement_2"]
						&& $record["id_banque_2"]["id"]==$record["atkorgrec"]["id_banque_2"]["id"]
						&& $record["id_reglement_2"]["id"]==$record["atkorgrec"]["id_reglement_2"]["id"]
						&& $record["numero_cheque_2"]==$record["atkorgrec"]["numero_cheque_2"]
						&& ($record["montant_versement_2"] > 0 || $record["montant_versement_2"] <0)
						&& ($record["id_ecriture_participation_2"] > 0 )
						&& ($record["id_ecriture_reglement_2"] >0)	)
				{
					$changement_versement_2=false;
				}
				if
				( $record["montant_versement"]==$record["atkorgrec"]["montant_versement"]
						&& $record["date_reglement"]==$record["atkorgrec"]["date_reglement"]
						&& $record["id_banque"]["id"]==$record["atkorgrec"]["id_banque"]["id"]
						&& $record["id_reglement"]["id"]==$record["atkorgrec"]["id_reglement"]["id"]
						&& $record["numero_cheque"]==$record["atkorgrec"]["numero_cheque"]
						&& ($record["montant_versement"] > 0 || $record["montant_versement"] <0)
						&& ($record["id_ecriture_participation"] > 0 )
						&& ($record["id_ecriture_reglement"] >0)	)
				{
					$changement_versement_1=false;
				}
				($changement_versement_1==true) ? $this->supprimer_ecritures_1($record) : null;
				($changement_versement_2==true) ? $this->supprimer_ecritures_2($record) : null;
				if ($record["montant_versement"] == 0 || $record["montant_versement"] =="")
				{
					$this->supprimer_ecritures_1($record);
					$record["date_reglement"]=="";
					$record["id_banque"]=="";
					$record["id_reglement"]=="";
					$record["numero_cheque"]=="";
				}
				if ($record["montant_versement_2"] == 0 || $record["montant_versement_2"] =="")
				{
					$this->supprimer_ecritures_2($record);
					$record["date_reglement_2"]=="";
					$record["id_banque_2"]=="";
					$record["id_reglement_2"]=="";
					$record["numero_cheque_2"]=="";
				}
			}
		}
		if (($record["montant_versement"] > 0 || $record["montant_versement"] <0)&& $changement_versement_1==true) {
			$this->creer_ecritures_comptables_1($record);
		}
//		echo "versement 2 : ".$record["montant_versement_2"]."<br/>";
 //if ($changement_versement_2==true) {
 //	echo "Vrai";} else {echo "faux";}
 
//		die();
		if (($record["montant_versement_2"] > 0 || $record["montant_versement_2"] <0) && $changement_versement_2==true) {
			$this->creer_ecritures_comptables_2($record);
		}

	}
	function preDelete(& $record) {

		$this->supprimer_ecritures_2($record);
		$this->supprimer_ecritures_1($record);
		parent :: preDelete($record);
	}

	function supprimer_ecritures_1(& $record) {
		$db = & atkGetDb();
		$id_ecriture_participation = $record["id_ecriture_participation"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "" && $id_ecriture_participation == "") {
			return true;
		} else
		{
			if (isset ($id_ecriture_reglement))
				
			{	$data = $db->getrows("select r.date_remise_banque as date_remise_banque
					from organisme_remise_banque r, organisme_ligne_ecriture_comptable l, individu_rencontre c
					where c.id_ecriture_reglement= $id_ecriture_reglement
					and  l.id_ecriture=c.id_ecriture_reglement
					and r.id=l.id_remise
					and id_type_banque  is not null ");
			if (isset ($data[0]["date_remise_banque"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement 1 a été remis en banque<br>", "critical");
			}
			
			$data = $db->getrows("select l.id_releve
					from organisme_ligne_ecriture_comptable l
					where l.id_ecriture=$id_ecriture_reglement ");
			if (isset ($data[0]["id_releve"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement 1 a été rapproché<br>", "critical");
			}
			}
			if (isset ($id_ecriture_participation)) {
				$this->supprimer_ecriture_comptable($id_ecriture_participation);
				$record["id_ecriture_participation"]="";
			}
			if (isset ($id_ecriture_reglement)) {
				$this->supprimer_ecriture_comptable($id_ecriture_reglement);
				$record["id_ecriture_reglement"]="";
			}
		}
		return true;
	}
	function supprimer_ecritures_2(& $record) {
		$db = & atkGetDb();
		$id_ecriture_participation_2 = $record["id_ecriture_participation_2"];
		$id_ecriture_reglement_2 = $record["id_ecriture_reglement_2"];
		if ($id_ecriture_reglement_2 == "" && $id_ecriture_participation_2 == "") {
			return true;
		} else
		{
			if (isset ($id_ecriture_reglement_2))
					
			{$data = $db->getrows("select r.date_remise_banque as date_remise_banque
					from organisme_remise_banque r, organisme_ligne_ecriture_comptable l, individu_rencontre c
					where c.id_ecriture_reglement_2= $id_ecriture_reglement_2
					and  l.id_ecriture=c.id_ecriture_reglement_2
					and r.id=l.id_remise
					and id_type_banque  is not null ");
			if (isset ($data[0]["date_remise_banque"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement 2 a été remis en banque<br>", "critical");
			}
			$data = $db->getrows("select l.id_releve
					from organisme_ligne_ecriture_comptable l
					where l.id_ecriture=$id_ecriture_reglement_2 ");
			if (isset ($data[0]["id_releve"])) {
				atkhalt("<br><b> Impossible de supprimer, le règlement 2 a été rapproché<br>", "critical");
			}
			}
			if (isset ($id_ecriture_participation_2)) {
				$this->supprimer_ecriture_comptable($id_ecriture_participation_2);
				$record["id_ecriture_participation_2"]="";
			}
			if (isset ($id_ecriture_reglement_2)) {
				$this->supprimer_ecriture_comptable($id_ecriture_reglement_2);
				$record["id_ecriture_reglement_2"]="";
			}

		}
		return true;
	}

	function creer_ecritures_comptables_1(& $record) {
		$id_individu = $record['id_individu']['id'];
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$organisme = $db->getrows("SELECT id_organisme
				from organisme_rencontre where id='" . $record["id_rencontre"]["id"] . "'");
		$id_organisme = $organisme[0]["id_organisme"];
		$rencontre = $db->getrows("SELECT ore.libelle as libelle , ore.date_debut as date_debut ,
				ore.id_type_rencontre as id_type_rencontre, tr.libelle as libelle_type_rencontre
				from organisme_rencontre ore, type_rencontre tr
				where ore.id='" . $record["id_rencontre"]["id"] . "' and ore.id_type_rencontre=tr.id ");
		$individu = $db->getrows("SELECT nom, prenom
				from individu where id='" . $record["id_individu"]["id"] . "'");
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
		$libelle_type_rencontre = $rencontre[0]["libelle_type_rencontre"];
		$id_compte_participation_manifestation = $rang[0]["id_compte_participation_manifestation"];
		$compte = $db->getrows("SELECT code from organisme_compte
				where id='" . $id_compte_participation_manifestation . "'");
		if (strlen($rencontre[0]["id_type_rencontre"])<3)
		{
			$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		}
		else
		{$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 3, "0", STR_PAD_LEFT);
		}
		/*		echo $compte[0]["code"];
		 echo '</br>';
		echo str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		die();
		*/

		$compte = $db->getrows("SELECT id from organisme_compte
				where code=$comptecode and id_organisme='" . $id_organisme . "'");
		if (count($compte) == 0) {
			// Créer le compte
			$libelle_type_rencontre=escapeSQL($libelle_type_rencontre);
			$user = getUser();
			$iduser = $user["id"];
			$sql = "insert into organisme_compte ( id_organisme, code, libelle, usuel, id_creation, date_creation, id_modification,  date_modification)
			values
			( '$id_organisme' ,'$comptecode', '$libelle_type_rencontre', '1',  '$iduser', UTC_TIMESTAMP(),  '$iduser' , UTC_TIMESTAMP() )";
			$data = $db->query($sql);
			$data = $db->getrows("select max(id) as last_id from organisme_compte ");
			$id_compte_participation_manifestation = $data[0]["last_id"];
			$nextid = $data[0]["last_id"] + 1;
			$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_compte' ");
		} else {
			$id_compte_participation_manifestation = $compte[0]["id"];
		}
		$date_reglement = $this->dateatktodb($record["date_reglement"]);
		$libelle = $rencontre[0]["date_debut"] . ' . ' . $rencontre[0]["libelle"] . '. Participation aux frais de ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle,$date_reglement);
		$record["id_ecriture_participation"] = $id_ecriture;
		$id_type_reglement = $record["id_reglement"]["id"];
		$numero_piece = $record["numero_cheque"];
		$id_type_banque = $record["id_banque"]["id"];
		$debit = $record["montant_versement"];
		// montant versement
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$credit = $record["montant_versement"];
		;
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_participation_manifestation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if ($id_type_reglement == 1) {
			// chéque à remettre en banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$credit = $record["montant_versement"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
		} elseif ($id_type_reglement == 3) {
				// epèces reçues en caisse
				$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
				$record["id_ecriture_reglement"] = $id_ecriture;
				$credit = $record["montant_versement"];
				$debit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
				$debit = $record["montant_versement"];
				$credit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement, null);
			}
			elseif ($id_type_reglement == 2) {
				// virement
				$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$credit = $record["montant_versement"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
		}
	
		return;
	}
	function creer_ecritures_comptables_2(& $record) {
		$id_individu = $record['id_individu']['id'];
		global $g_user;
		$userid = $g_user["id"];
		$db = & atkGetDb();
		$organisme = $db->getrows("SELECT id_organisme
				from organisme_rencontre where id='" . $record["id_rencontre"]["id"] . "'");
		$id_organisme = $organisme[0]["id_organisme"];
		$rencontre = $db->getrows("SELECT ore.libelle as libelle , ore.date_debut as date_debut ,
				ore.id_type_rencontre as id_type_rencontre, tr.libelle as libelle_type_rencontre
				from organisme_rencontre ore, type_rencontre tr
				where ore.id='" . $record["id_rencontre"]["id"] . "' and ore.id_type_rencontre=tr.id ");
		$individu = $db->getrows("SELECT nom, prenom
				from individu where id='" . $record["id_individu"]["id"] . "'");
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
		$libelle_type_rencontre = $rencontre[0]["libelle_type_rencontre"];
		$id_compte_participation_manifestation = $rang[0]["id_compte_participation_manifestation"];
		$compte = $db->getrows("SELECT code from organisme_compte
				where id='" . $id_compte_participation_manifestation . "'");
		$comptecode = $compte[0]["code"] . str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		/*		echo $compte[0]["code"];
		 echo '</br>';
		echo str_pad($rencontre[0]["id_type_rencontre"], 2, "0", STR_PAD_LEFT);
		die();
		*/

		$compte = $db->getrows("SELECT id from organisme_compte
				where code=$comptecode and id_organisme='" . $id_organisme . "'");
		if (count($compte) == 0) {
			// Créer le compte
			$user = getUser();
			$iduser = $user["id"];
			$sql = "insert into organisme_compte ( id_organisme, code, libelle, usuel, id_creation, date_creation, id_modification,  date_modification)
			values
			( '$id_organisme' ,'$comptecode', '$libelle_type_rencontre', '1',  '$iduser', UTC_TIMESTAMP(),  '$iduser' , UTC_TIMESTAMP() )";
			$data = $db->query($sql);
			$data = $db->getrows("select max(id) as last_id from organisme_compte ");
			$id_compte_participation_manifestation = $data[0]["last_id"];
			$nextid = $data[0]["last_id"] + 1;
			$data = $db->query("UPDATE db_sequence set nextid='" . $nextid . "' where seq_name='seq_organisme_compte' ");
		} else {
			$id_compte_participation_manifestation = $compte[0]["id"];
		}
		$date_reglement = $this->dateatktodb($record["date_reglement_2"]);
		$libelle = $rencontre[0]["date_debut"] . ' . ' . $rencontre[0]["libelle"] . '. Participation aux frais de ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_recettes, $libelle,$date_reglement);
		$record["id_ecriture_participation_2"] = $id_ecriture;
		$id_type_reglement = $record["id_reglement_2"]["id"];
		$numero_piece = $record["numero_cheque_2"];
		$id_type_banque = $record["id_banque_2"]["id"];
		$debit = $record["montant_versement_2"];
		// montant versement
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		$credit = $record["montant_versement_2"];
		;
		$debit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_recettes, $id_compte_participation_manifestation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if ($id_type_reglement == 1) {
			// chéque à remettre en banque
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement_2"] = $id_ecriture;
			$credit = $record["montant_versement_2"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement_2"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
		} elseif ($id_type_reglement == 3) {
				// epèces reçues en caisse
				$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
				$record["id_ecriture_reglement_2"] = $id_ecriture;
				$credit = $record["montant_versement_2"];
				$debit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
				$debit = $record["montant_versement_2"];
				$credit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement, null);
			}
			elseif ($id_type_reglement == 2)
			// virement
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle,$date_reglement);
			$record["id_ecriture_reglement_2"] = $id_ecriture;
			$credit = $record["montant_versement_2"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement_2"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
				
		return;
	}


	function action_delete(& $handler) {
		$this->setOrder("");
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {


			$requete = "DELETE FROM individu_rencontre
					where ".$id_variable."
							and id_document_intervenant is null
							and id_reglement is null
							and id_rapport_activite is null
							and id_ecriture_participation is null
							and id_ecriture_reglement is null ";
			$db->query($requete);
		}
		$this->redirect();
		//return $handler->action_delete();
	}
	function descriptor_def() {
		return "[id_rencontre.libelle]";
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		(!empty($record["id_organisme_participant"])) ? $retour.='<br />'.$this->descripteur_organisme($record["id_organisme_participant"]["id"],'n') : $retour.="";

		return $retour;
	}
	function nom_organisme_display($record, $mode) {
		(!empty($record["nom_organisme"])) ? $retour=$this->descripteur_organisme($record["nom_organisme"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_participant_display($record, $mode) {
		(!empty($record["id_organisme_participant"])) ? $retour=$this->descripteur_organisme($record["id_organisme_participant"]["id"],'n') : $retour="";
		return $retour;
	}

	/*	 function id_individu_display($record, $mode)
	 {
	$attribute = &$this->getAttribute("id_individu");
	$original = $attribute->display($record, $mode);
	$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone_fixe, telephone_mobile, courriel from individu  where id =" . $record["id_individu"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone_fixe"];
	$telephone_mobile = $data[0]["telephone_mobile"];
	$courriel = $data[0]["courriel"];
	/* if ($courriel != "") {
	$courriel1=href(dispatch_url("individu.contact_i", "add", array (
			"atgemail" => $courriel,
			"atgtable" => $this->table,
			"atgcle" => $record["id_contact"]["id"],
			"atgvaleur" => $record["id_contact"]["id"]
	)), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
	}
	*/
	/*  return $original."<br />".$telephone_fixe."<br />".$telephone_mobile."<br />".$courriel;
	 }
	function id_organisme_participant_display($record, $mode)
	{
	$attribute = &$this->getAttribute("id_organisme_participant");
	$original = $attribute->display($record, $mode);
	if ($record["id_organisme_participant"]["id"]!="")
	{		$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone, courriel from organisme  where id =" . $record["id_organisme_participant"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone"];
	$courriel = $data[0]["courriel"];
	}
	return $original."<br />".$telephone_fixe."<br />".$courriel;
	}
	*/
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$estampille_o_n=$this->m_postvars["estampille_o_n"];
		if ($estampille_o_n=="") $estampille_o_n="n";

		$filtre=str_replace(" individu_rencontre.", " ire.", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		ore.libelle_participation_1,
		ore.libelle_participation_2,
		ore.libelle_participation_3,
		ore.libelle_participation_4,
		ire.id	as id_entite,
		ire.id as id_participant,
		ire.id_document_inscription_rencontre,
		ore.libelle as libelle_rencontre,
		ire.id_individu as id_individu,
		ire.id_rencontre,
		ire.intervenant_o_n,
		ire.theme_intervention,
		ire.id_document_intervenant,
		trp.libelle as libelle_participation,
		ire.participation_partielle,
		ire.participation_complete,
		ire.participation_3,
		ire.participation_4,
		ire.date_inscription,
		ire.id_rapport_activite,
		ire.covoiturage_places_offertes,
		ire.covoiturage_places_demandees
		from
		individu_rencontre ire
		LEFT JOIN individu i ON ire.id_individu=i.id
		LEFT JOIN organisme_rencontre ore ON ire.id_rencontre=ore.id
		LEFT JOIN type_rencontre_participation trp ON ire.id_type_rencontre_participation=trp.id
		where
		$filtre
		order by i.nom, i.prenom, ire.date_inscription	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Rencontre</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Nom</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contact</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Naissance</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Inscription</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Participation</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Intervenant</center></b>';
//		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Choix</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Règlement</center></b>';
//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Décès</center></b>';
			$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';

		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$idindividus.=$data[$i]["id_individu"].",";
			$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
			$res2.= "<tr><td>".($i+1);
			$res2.='</td><td>'.'<b>'.$data[$i]["libelle_rencontre"].'</b>';
			$res2.='</td><td>'.'<b>'.$arrayIndividu["nom"].'</b>';
			$res2.='</td><td>'.$arrayIndividu["contacts"];
			$res2.='</td><td>'.'<b>'.$arrayIndividu["date_naissance"].'</b>';
			$res2.='</td><td>'.'<b>'.$data[$i]["date_inscription"].'</b>'
					."<br/>Document d'inscription : ".$this->descripteur_document_sans_lien("organisme",$data[$i]["id_document_inscription_rencontre"]) ;
			$res2.="<br/></b>Options : <b>";
			(empty($data[$i]["participation_partielle"])) ? $data[$i]["participation_partielle"]='0' : null;
			(empty($data[$i]["participation_complete"])) ? $data[$i]["participation_complete"]='0' : null;
			(empty($data[$i]["participation_3"])) ? $data[$i]["participation_3"]='0' : null;
			(empty($data[$i]["participation_4"])) ? $data[$i]["participation_4"]='0' : null;
			(!empty($data[$i]["libelle_participation_1"])) ? $res2.="<b>".$data[$i]["participation_partielle"]." (".$data[$i]["libelle_participation_1"].")</b>, " : null;
			(!empty($data[$i]["libelle_participation_2"])) ? $res2.="<b>".$data[$i]["participation_complete"]." (".$data[$i]["libelle_participation_2"].")</b>, " : null;
			(!empty($data[$i]["libelle_participation_3"])) ? $res2.="<b>".$data[$i]["participation_3"]." (".$data[$i]["libelle_participation_3"].")</b>, " : null ;
			(!empty($data[$i]["libelle_participation_4"])) ? $res2.="<b>".$data[$i]["participation_4"]." (".$data[$i]["libelle_participation_4"].")</b>, " : null ;
			$res2=substr($res2, 0, strlen($res2)-2);
			$res2.='</td><td>'.'<b>'.$data[$i]["libelle_participation"].'</b>';
			($data[$i]["intervenant_o_n"]==1)?$int="Oui" : $int="Non";
			$res2.='</td><td>'.'<b>'.$int."<br/>".$data[$i]["theme_intervention"].' '.$this->descripteur_document_sans_lien("organisme",$data[$i]["id_document_intervenant"]).'</b>';
//			$res2.='</td><td>'.$this->descripteur_choix reglement("participant_rencontre",$data[$i]["id_participant"],'n')
//			."<br/>";
			$res2.='</td><td>'.$this->descripteur_reglement("participant_rencontre",$data[$i]["id_participant"],'n')
			."<br/>".$this->descripteur_reglement("participant_rencontre_2",$data[$i]["id_participant"],'n');
//				$res2.='</td><td>'.'<b>'.$arrayIndividu["date_deces"].'</b>';
				$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
			$res2.='</td></tr>';
		}

		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Participants à des rencontres"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);

	}

}
?>