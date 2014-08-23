<?php
useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");

class individu_simple extends assMetaNode {

var $table = "individu";

	function individu_simple() {
		$this->atkMetaNode();
		$this->atkNode("individu_simple", NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"descripteur_individu",
				"id_titre",
				"nom",
				"prenom",
				"sexe",
				"date_naissance",
				"annee_naissance",
		"lieu_naissance",
		"nationalite",
		"profession",
		"courriel_grp",
		"pas_de_courriel_o_n",
		"calendrier_grp",
		"site_internet_grp",
				"telephone_fixe",
				"telephone_mobile",
				"contact_alternatif",
				"date_deces",
				"numero_ss",
				"compte_bancaire",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)

				), AF_NO_LABEL));
			$this->add(new atkDummyAttribute("descripteur_individu",0,AF_HIDE_ADD ),3);
			global $g_sessionManager;
			$g_afficher_portrait_o_n = $g_sessionManager->getValue("afficher_portrait_o_n", "globals");
			
			($g_afficher_portrait_o_n=='1') ?  $this->add(new atkDummyAttribute("portrait",0,AF_HIDE_EDIT | AF_HIDE_ADD ),4) : null;
//						$this->add(new atkDummyAttribute("descripteur_qr_individu",0,AF_HIDE_EDIT ),4);
				$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY ),6);
				
	

			$this->add(new atgTextNomAttribute("prenom", AF_SEARCHABLE), 6);
			$this->addUniqueFieldset(array("nom","prenom"));
			$this->add(new atkManyToOneRelation("id_titre", "table.titre", AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_SEARCHABLE));
			$this->add(new atkEmailAttribute("courriel", false, AF_SEARCHABLE));
			$this->add(new atkUrlAttribute("calendrier", AF_POPUP));
			$this->add(new atkBoolAttribute("pas_de_courriel_o_n"));
			$this->add(new atkUrlAttribute("site_internet", AF_POPUP));
			$this->add(new atkRadioAttribute("sexe", array (
			"Homme",
			"Femme"
			), array (
			"M",
			"F"
			), AF_OBLIGATORY | AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_naissance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
			$this->add(new atkAttribute("lieu_naissance", AF_HIDE_LIST,100 ));
			$this->add(new atkAttribute("nationalite",AF_HIDE_LIST));
			$this->add(new atkAttribute("profession",AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_deces", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));

	
			global $g_sessionManager;
			$id_individu_utilisateur = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
			$this->add(new atkParserAttribute("courriel_go",
			atkHref("?atknodetype=individu.contact_i&atkaction=add&atkfilter=individu_contact.id_individu=[id]&idcontactant=$id_individu_utilisateur&atgemail=[courriel]&"
			, atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->add(new atkParserAttribute("calendrier_go",atkHref("[calendrier]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);
			$this->add(new atkParserAttribute("site_internet_go",atkHref("[site_internet]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->addFieldSet("courriel_grp"," [courriel.field] [courriel_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("calendrier_grp"," [calendrier.field] [calendrier_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("site_internet_grp"," [site_internet.field] [site_internet_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );

			$this->m_securityMap["document"] = "view";
			$this->m_securityMap["autocomplete"] = "view";
			$this->m_securityMap["enveloppe"] = "view";
			$this->m_securityMap["normalisation"] = "view";
			$this->m_securityMap["listeecran"] = "export";
			$this->m_securityMap["fiche"] = "view";
			$this->m_securityMap["liens"] = "view";
			$this->m_securityMap["vcard"] = "view";
			$this->m_securityMap["google"] = "view";
			$this->m_securityMap["googlemap"] = "view";
			$this->m_securityMap["listeecran"] = "view";
			//			$this->m_securityMap["rapport_html"] = "view";
			$this->m_securityMap["inscrire_du_presse_papier"] = "view";
			$this->m_securityMap["rafraichir_calendrier_rencontres"] = "view";
						$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,5);
			$this->setOrder("nom,prenom");
			$this->setIndex("nom");
			// GG deb
			global $ATK_VARS, $g_user;
			if ($ATK_VARS["atknodetype"] == "individu.individu" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
				))) {
					if ($this->getView() == "active") {
						$this->addFilter("individu.date_deces IS NULL");
					}
				}
				// GG fin
	}
	function portrait_display($record, $mode)
	{
		$db = & atkGetDb();
	
	$sql="select id_document_portrait from individu where id=".$record["id"]." ";
		$data=$db->getrows($sql);
		$id_portrait=$data[0]["id_document_portrait"];
		if (!empty($id_portrait))
			{
		$sql="select file_content,file_name, file_size from organisme_document where id=$id_portrait";
		$data=$db->getrows($sql);
		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		$filename=$data[0]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[0]["file_content"]="";
		$retour='<center><a href="'.$url. '" target="_blank" ><img src="'.$url.'" height="100px" alt="Portrait" title="Portrait" /></a></center>' ;
	return $retour;
			}
	}
function descripteur_individu_display($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"n","o");
	}
function descripteur_individu_edit($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"n","o");
	}
/*function descripteur_qr_individu_display($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"o");
	}
	*/
	
	function telephone_fixe_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone_fixe"] . ';">' . $record["telephone_fixe"] . '</a>';
	}
	function telephone_mobile_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone_mobile"] . ';">' . $record["telephone_mobile"] . '</a>';
	}
		function dispatch($postvars, $fullpage = true) {
		/*
		 *
		 if ($postvars['atkaction'] == 'rapport_html') {
			echo 'rapport';
			die();
			}
			*/
		if ($postvars['atkaction'] != 'copier_individus_dans_presse_papier' && $postvars['atkaction'] != 'rafraichir_calendrier_rencontres'  )
		{
			if ($postvars['atkaction'] != 'add' && $postvars['atkaction'] != 'delete' && $postvars['atkaction'] != 'admin') {
				$atkselect = $postvars["atkselector"];
				if (($atkselect != "") && isset ($atkselect)) {
					$individuid = sscanf($atkselect, "individu.id='%d'");
					$individuId = $individuid[0];
					$this->RecentUseProcess('individu', $individuId);
				} else {
					$individuId = 0;
				}
			} else {

				$this->RecentUseRefresh('individu');
			}
		}
		return parent :: dispatch($postvars, $fullpage);
	}


	function nom_display($record, $mode) {
		// Do not return a html link in plain or csv mode or select screen
		//				$this->p($this->m_filters);
		if (($mode == "plain") || ($mode == "csv") || (isset ($this->m_postvars["atkaction"]) && $this->m_postvars["atkaction"] == "select"))
		return $record["nom"];
		// Make all project links clickable
		$defaultaction = $this->allowed("edit") ? "edit" : "view";
		return href(dispatch_url("individu.individu", $defaultaction, array (
			"atkselector" => "individu.id='{$record["id"]}'"
		), "dispatch.php"), $record["nom"], SESSION_NESTED);
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$actions['copier_individus_dans_presse_papier'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=copier_individus_dans_presse_papier&atkselector=[pk]", SESSION_NESTED);

		$mraactions['copier_individus_dans_presse_papier'] = "copier_individus_dans_presse_papier";
		$mraactions['rafraichir_calendrier_rencontres'] = "rafraichir_calendrier_rencontres";
		//		$mraactions['rapport_html'] = "rapport_html";
		//		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
	}
	function courriel_display($record, $mode = "") {
		if ($mode == "csv")
		return parent :: display($record, $mode);
		if ($record["courriel"] != "") {
			return href(dispatch_url("individu.contact_i", "add", array (
				"atgemail" => $record["courriel"],
				"atgtable" => $this->table,
				"atgcle" => 'id',
				"atgvaleur" => $record["id"]
			)), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
		}
	}
	function calendrier_display($record, $mode = "") {
		if (!empty($record["calendrier"]))		return '<a href="'.$record["calendrier"].'">Calendrier</a>';
	}
	function site_internet_display($record, $mode = "") {
		if (!empty($record["site_internet"]))	return '<a href="'.$record["site_internet"].'">Site/Blog</a>';
	}
	// GG deb
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
		function postAdd(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseProcess('individu', $id_entite);
		}
		function preDelete(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseDelete('individu', $id_entite);
		}
		function postUpdate($rec) {
			if ($rec["date_deces"] == NULL) {
				$id_entite = $rec["id"];
				$this->RecentUseRefresh('individu');
				return true;
			}
			$user = getUser();
			$id = $user["id"];
			if (!isset ($id)) {
				$id = "1";
			}
			$idindividu = $rec["id"];
			$db = & atkGetDb();
			$db->query("UPDATE individu_inscription set date_radiation=UTC_DATE(), id_type_radiation='1', id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_attribut set date_fin=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_fonction set date_fin=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_groupe_travail set date_fin_groupe=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			return true;
		}

		function initial_values() {
			return array (
			"date_deces" => null
			);
		}
		function rowColor($record) {
			$date_deces = $record["date_deces"];
			if ($date_deces != "")
			return $this->couleurarchive;
		}
		function validate(& $record, $mode) {
			$record["telephone_fixe"] = normalisation_telephone($record["telephone_fixe"]);
			$record["telephone_mobile"] = normalisation_telephone($record["telephone_mobile"]);

			if (($record["date_deces"]["year"] == '1999') && ($record["date_deces"]["month"] == '12') && ($record["date_deces"]["day"] == '31')) {
				unset ($record["date_deces"]["year"]);
				unset ($record["date_deces"]["month"]);
				unset ($record["date_deces"]["day"]);
			}
			if (($record["date_naissance"]["year"] == '1999') && ($record["date_naissance"]["month"] == '12') && ($record["date_naissance"]["day"] == '31')) {
				unset ($record["date_naissance"]["year"]);
				unset ($record["date_naissance"]["month"]);
				unset ($record["date_naissance"]["day"]);
			}
			parent :: validate($record, $mode);
		}
		function action_normalisation() {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT id, nom , prenom, telephone_fixe, telephone_mobile " . " from individu");
			if (count($data) == 0) {
				return true;
			} else {
				for ($i = 0; $i < count($data); $i++) {
					$data[$i]["nom"] = normalisation_chaine($data[$i]["nom"]);
					$data[$i]["nom"] = addslashes($data[$i]["nom"]);
					$data[$i]["prenom"] = normalisation_chaine($data[$i]["prenom"]);
					$data[$i]["prenom"] = addslashes($data[$i]["prenom"]);
					$data[$i]["telephone_fixe"] = normalisation_telephone($data[$i]["telephone_fixe"]);
					$data[$i]["telephone_fixe"] = addslashes($data[$i]["telephone_fixe"]);
					$data[$i]["telephone_mobile"] = normalisation_telephone($data[$i]["telephone_mobile"]);
					$data[$i]["telephone_mobile"] = addslashes($data[$i]["telephone_mobile"]);
					$db->query("UPDATE individu" . " set nom='" . $data[$i]["nom"] . "'" . " , prenom='" . $data[$i]["prenom"] . "'"
					. " , telephone_fixe='" . $data[$i]["telephone_fixe"] . "'"
					. " , telephone_mobile='" . $data[$i]["telephone_mobile"] . "'"
					. " where id=" . $data[$i]["id"] . "");
				}
			}
			echo "<br> Normalisation des noms, prénoms, téléphones terminée.";
		}
		function descriptor_def() {
			return "[nom] [prenom]";
		}
		function action_admin($handler) {

			if  (substr($this->m_postvars["atkfilter"],0,5) =="'%@@@")
			{
				$searchvalue=$this->m_postvars["atkfilter"];
				$searchfields = array("nom","prenom");
				$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
				$filter = $this->createSearchFilter($searchfields,$searchvalue,$this->table );
				$this->m_postvars["atkfilter"]=$filter;
			}

			$view = $this->getView();

			if ($view == "active") {
				$this->addFilter("individu.date_deces IS NULL");
				$this->addFilter($this->m_postvars["atkfilter"]);
			}

			return $handler->action_admin();
		}
		function adminHeader()
		{
			if (isset($this->m_postvars['atkfilter']))
			{return '</b>Attention filtre actif :  '.$this->m_postvars['atkfilter'].'<b><br />';	}
		}

		function modifyDataGrid($grid,$mode)
		{

			if ($mode==2)
			{

				$grid->setPostvar("atkfilter",'');
				$this->m_postvars['atkfilter']='';
				global $ATK_VARS;
				$ATK_VARS['atkfilter'] = '';
				///  print_r ($this->p($grid->getPostvars()));
				// die();
			}

			return true;
		}


		function adminFooter() {
			$retour=parent::adminfooter();
			$view = $this->getView();
			$legende = 'Légende des couleurs : ';
			$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive ';
			if ($view == "active") {
				return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
			} else {
				return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
			}
		}
}
?>
