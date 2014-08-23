<?php

class v_individu_correspondant extends assMetaNode {
	var $table = "v_individu_correspondant";
	var $primary_field = "";
	var $module = "v_individu_correspondant";
	var $node = "v_individu_correspondant";
	var $index_field = "individu";
	var $order_field = "type_correspondant";
	var $descriptor_field = "[organisme]";
	// start constructor
	function v_individu_correspondant() {
		// tabs labels
		// call constructor parent
		$this->atkMetaNode(array (
			"flags" => NF_READONLY | NF_MRA
		));
		//event log
		$this->addListener(atknew("atk.utils.atkeventlog"));
		// node attributes
		$this->add(new atkRowCounter("#"), NULL, 1);
		$this->add(new atkAttribute("individu", AF_SEARCHABLE), NULL, 0);
		$this->add(new atkAttribute("type_correspondant", 0), NULL, 100);
		$this->add(new atkAttribute("nombre", 0), NULL, 200);
		$this->add(new atkNumberAttribute("id_individu", AF_PRIMARY | AF_HIDE_EDIT | AF_HIDE_LIST, 10, 0), NULL, 1100);
		$this->add(new atkNumberAttribute("id_type_correspondant", AF_PRIMARY | AF_HIDE_EDIT | AF_HIDE_LIST, 10, 0), NULL, 1200);
		$this->setExtendedSearchAction('smartsearch');
		$this->setSecurityAlias("organisme.organisme");

		include_once (atkconfig("atkroot") . "modules/include/actions.inc");
		$this->setIndex($this->index_field); // set index attribute
		$this->setOrder($this->order_field); // set order attribute(s)
		$this->setTable($this->table); // set node table
		$this->m_securityMap["inscrire_du_presse_papier"] = "view";
		$this->m_securityMap["export_google"] = "view";


	} // end constructor
	function meta(& $policy) {
	} // end function

	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		$actions["delete"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=delete&atkselector=[pk]", SESSION_NESTED);

		global $g_user;
		$userid = $g_user["id"];

		$mraactions["inscrire_du_presse_papier"] ="inscrire_du_presse_papier";
		//		$mraactions['export_google'] = "export_google";
		$mraactions['delete'] = "delete";
			}
	function action_delete() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
			
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$id_variable=str_replace('v_individu', 'individu', $id_variable);
			$sql="DELETE from individu_correspondant where $id_variable";
			$db->query($sql);
		}
		$this->redirect();
	}

	function action_inscrire_du_presse_papier() {
		if (count($this->m_postvars["atkselector"])==1)
		{$pk = $this->m_postvars["atkselector"][0];
		}
		else
		{
			$this->setFeedback("inscrire_du_presse_papier",ACTION_FAILED);
			$location = $this->feedbackUrl("inscrire_du_presse_papier", ACTION_FAILED, "", "Vous devez sélectionner une seule ligne");
			$this->redirect($location);
		}

		$array_1 = explode('AND', $pk);
		$array_individu = explode('=', $array_1[0]);
		$id_individu= $array_individu[1];

		$array_type = explode('=', $array_1[1]);
		$id_type= $array_type[1];

		$user = getUser();
		$userid = $user["id"];
		global $g_sessionManager;
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$requete = "SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$data = $db->getrows($requete);
		if (count($data) == 0) {
			$db->commit();
			$this->redirect();
		}


		foreach ($data as $id_individu_correspondant) {
			$id_individu_correspondant_1 = $id_individu_correspondant["id_variable"];
			$requete = "INSERT INTO individu_correspondant
										 (  id_individu,id_individu_correspondant,id_type_correspondant, 
										commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
					VALUES( $id_individu ,$id_individu_correspondant_1,$id_type,
					'','$userid', UTC_TIMESTAMP(), '$userid',  UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
			$db->query($requete);
			$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_correspondant' ");
		}

		$requete = "DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

	function traitement_select($select,&$idorganisme,&$idindividus,&$idfonctions)
	{
		$db = & atkGetDb();
		// v_individu_correspondant.id_individu='104' AND v_individu_correspondant.id_type_correspondant='2'

		foreach ($select as $id_variable) {
			$array_1 = explode('AND', $id_variable);
			$array_individu = $array_1[0];
			$array_type = explode('=', $array_1[1]);
			$chaineidtype .= $array_type[1] . ',';
		}
		$array_individu = str_replace("v_individu_correspondant", "individu_correspondant", $array_individu);
		$chaineidtype = substr($chaineidtype, 0, strlen($chaineidtype) - 1);
		$idfonctions=$chaineidtype;
		$sql = 'select distinct id_individu_correspondant from individu_correspondant
		 where ' . $array_individu . '  and id_type_correspondant in (' . $chaineidtype . ')';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu_correspondant"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		$idorg = explode('=', $array_individu);
		$idorganisme = $idorg[1];
		return true;
	}
	function nombre_display($record, $mode) {
		if ($record["nombre"] > 0) {
			return href(dispatch_url("individu.correspondant", "admin", array (
				'atkfilter' => "individu_correspondant.id_individu=" . $record['id_individu']. " and individu_correspondant.id_type_correspondant=" . $record['id_type_correspondant'] . ""
				), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
/*	function getCustomMraHtml()
	{
		$list = 'Mot-de-passe : ';
		$list .=  '<input type="password" name="code_google" value="" size="10" > ';
		return $list;
	}

*/

	

	function descriptor_def() {
		return $this->descriptor_field;
	}


	function action_export_correspondants()
	{
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
			
		$sqlcondition='';
		foreach ($select as $id_variable) {
			$id_variable=str_replace('v_individu', 'individu', $id_variable);
			($sqlcondition=='')?$sqlcondition='('.$id_variable.')' : $sqlcondition.=' OR ('.$id_variable.')';
		}
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
		$query->addCondition("adresse_personnelle_o_n=1");
		$query->addCondition(" individu.id in (SELECT id_individu_correspondant from individu_correspondant where $sqlcondition )");
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
			$row .= '"' . $stuff[$i]["prenom"] . '",,';
			$row .= '"' . $stuff[$i]["nom"] . '",,,,"' . $stuff[$i]["titre"] . '",,,,,,,,';
			$row .= '"' . $stuff[$i]["adresse1"] . '","' . $stuff[$i]["adresse2"] . '",,"' . $stuff[$i]["ville"] . '","' . $stuff[$i]["province"] . '","' . $stuff[$i]["code_postal"] . '","' . $stuff[$i]["pays"] . '",,,,,,,,,,,,,,,,';
			$row .= '"' . $stuff[$i]["telephone_fixe"] . '",,,"' . $stuff[$i]["telephone_mobile"] . '",,,,,,,,';
			$row .= '"' . $stuff[$i]["courriel"] . '",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,""
																														';
			fwrite($fdw, $row);
		}
		fclose($fdw);
		exportFile("contacts", "contacts.csv", "", true);
	}
}
?>