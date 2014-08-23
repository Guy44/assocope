<?php
atkimport("atk.atkmetanode");
atkimport("atk.utils.atkmessagequeue");
class assMetaNode extends atkMetaNode {
	var $couleuranomalie = "Tomato";
	var $couleurrequete = "MediumSpringGreen";
	var $couleurarchive = "Violet";
	var $couleurrouge = "Tomato";
	var $couleurpriorite1 = "Tomato";
	var $couleurpriorite2 = "Salmon";
	var $couleurpriorite3 = "PapayaWhip";
	var $couleurorganismeaccesprive = "Pink";
	var $couleursemaine = "Tomato";
	var $couleurmois = "Orange";
	var $couleurplusmois = "YellowGreen";
	var $couleurvert = "YellowGreen";
	var $couleuractif = "Tomato";
	var $couleurcompte1 = "#FF6699";
	var $couleurcompte2 = "#FF9966";
	var $couleurcompte3 = "#FFcc33";
	var $couleurcompte4 = "#FFff00";
	var $couleurcompte5 = "#FFff99";
	var $couleurcompte6 = "#FFFFCC";
	var $table = "individu";
	var $type_ecriture_journal=1;
	var $type_ecriture_cotisation=2;
	var $type_ecriture_participation_rencontre=3;
	var $type_ecriture_rencontre=4;
	var $type_ecriture_rencontre_fournisseur=5;
	var $type_ecriture_depense=6;
	var $type_ecriture_recette=7;
	var $type_ecriture_virement=8;
	var $type_ecriture_frais=9;
	var $type_ecriture_abandon_creance=10;
	var $m_styleTitreLigne="style=\"font-variant : small-caps; color: #5A7236;  font-size: 14px !important;\"";
	var $m_styleTitreLigne300px="style=\"font-variant : small-caps; color: #5A7236;  font-size: 12px; width:300px \"";
	var $m_styleTitreLigneEstampille="style=\"font-variant : small-caps; color: #5A7236;  font-size: 12px; width:300px \"";
	var $option_href_tbdebord="SESSION_NESTED, false , 'target=\"_blank\"' ";
	var $target_tbdebord='target=\"_blank\"';

	/**
	 * Minimum number of character a user needs to enter before auto-completion kicks in.
	 *
	 * @access private
	 * @var int
	 */
	var $m_autocomplete_minchars = 2;

	/**
	 * An array with the fieldnames of the destination node in which the autocompletion must search
	 * for results.
	 *
	 * @access private
	 * @var array
	 */
	var $m_autocomplete_searchfields = "";

	/**
	 * The search mode of the autocomplete fields. Can be 'startswith', 'exact' or 'contains'.
	 *
	 * @access private
	 * @var String
	 */
	var $m_autocomplete_searchmode = "contains";

	/**
	 * Value determines wether the search of the autocompletion is case-sensitive.
	 *
	 * @var boolean
	 */
	var $m_autocomplete_search_case_sensitive = false;

	/**
	 * Value determines if select link for autocomplete should use atkSubmit or not (for use in admin screen for example)
	 *
	 * @var boolean
	 */
	var $m_autocomplete_saveform = true;

	/**
	 * Set the minimal number of records for showing the automcomplete. If there are less records
	 * the normal dropdown is shown
	 *
	 * @access private
	 * @var integer
	 */
	var $m_autocomplete_minrecords = -1;

	function ecriture_type_origine_maj($id_ecriture,$type_ecriture,$id_origine)
	{
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$db->query("UPDATE organisme_ecriture_comptable
				set id_type_ecriture=$type_ecriture,
				id_origine_ecriture=$id_origine,
				id_modification=$userid,
				date_modification=UTC_TIMESTAMP()
				where id=$id_ecriture
				");
		$db->commit();
	}

	function get_map_key()
	{
		global $g_sessionManager;
		return  $g_sessionManager->getValue("google_map_key", "globals");
	}
	function get_ubio_keycode()
	{
		global $g_sessionManager;
		return  $g_sessionManager->getValue("ubio_keycode", "globals");
	}

	function createSearchFilter($searchfields,$searchvalue,$searchtable)
	{
		/*	print_r ($searchfields);
		 echo '<br />';
		print_r ($searchvalue);
		echo '<br />';
		print_r ($searchtable);
		die();
		*/

		// $searchfields = array("organisme.nom","organisme.sigle");
		// $searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
		$parts = preg_split('/\s+/', $searchvalue);
		$mainFilter = array();
		foreach ($parts as $part)
		{
			$filter = array();
			foreach($searchfields as $attribname)
			{
				$tmp = "LOWER(".$searchtable.'.'.$attribname.")";
				$tmp.= " LIKE LOWER('%{$part}%')";
				$filter[] = $tmp;
			}
			if (count($filter) > 0)
				$mainFilter[] = "(".implode(") OR (", $filter).")";
		}
		if (count($mainFilter) > 0)
			return "(".implode(") AND (", $mainFilter).")";
		else return "";
	}
	function get_row_selection_information($rang_unique_o_n=false)
	{
		/**
		 * Constructor
		 * @param $rang_unique_o_n
		 * true : sélection doit être monoligne
		 * false : la sélection peut être multilignes
		 * @return array
		 *  Si monoligne :
		 *  $tableau["node_id"]
		 *  $tableau["selector"]
		 *  Dans tous les cas :
		 *  $tableau["userid"]
		 *  $tableau["node_ids"]
		 *  $tableau["in_id_string"]
		 *  $tableau["selectors"]
		 *  $tableau["rows_number"]
		 */
		$tableau=array();
		$user = getUser();
		$tableau["userid"]=$user["id"];
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {			$select[0] = $this->m_postvars["atkselector"];
		}
		if (count($select)>1 && $rang_unique_o_n==true) return false;

		if (count($select)==1 )
		{
			$select_node =$select[0] ;

			$array_id = explode('=', $select_node);
			$node_id = stripQuotes($array_id[1]) ;
			$tableau["node_id"]=$node_id;
			$tableau["selector"]=$select[0];
		}
		$chaine_id_in="(";
		foreach ($select as $selector)
		{
			$array_id = explode('=', $selector);
			$node_id = stripQuotes($array_id[1]) ;
			$tableau["node_ids"][]=$node_id;
			$chaine_id_in.=$node_id.",";
		}
		$chaine_id_in=substr($chaine_id_in, 0,strlen($chaine_id_in)-1).')';
		$tableau["in_id_string"]=$chaine_id_in;

		$tableau["selectors"]=$select;
		$tableau["rows_number"]=count($select);


		return $tableau;


	}

	function date_creation_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->dateatktodb($record["date_creation"]), 12);
	}
	function date_modification_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->dateatktodb($record["date_modification"]),12);
	}

	function descripteur_module_estampillage_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_module_estampillage($record, 'o'), 300);
	}
	function descripteur_module_estampillage_edit($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_module_estampillage($record, 'o'), 300);
	}

	function descripteur_module_estampillage($record_or_id, $aide_o_n)
	{
		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$icones_estampillage_o_n = $g_sessionManager->getValue("icones_estampillage_o_n", "globals");
		$db = & atkGetDb();
		if (is_string($record_or_id)) 
		{$id_entite=$record_or_id;
		$sql="SELECT id, commentaire, id_creation, id_modification, date_creation, date_modification 
				FROM
				".$this->m_table. " WHERE id=".$id_entite;
		$data=$db->getrows($sql);
		$record=$data[0];
		}
		else { $record=$record_or_id ;}
		
		$descripteur="";
		if ($administrateur=="1" && $icones_estampillage_o_n=="1")
		{
			
			

			$source=' '.atkHref(dispatch_url("lesson_utils.sourceviewer", "view", array (
					"module" => $this->m_module,
					"node" => $this->m_type
			)),'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/php-pg-icon.png" alt="Source php" title="Source php du module '.$this->m_module.'.'.$this->m_type.'" ></img>'
					.'</b>', SESSION_NEW, false, 'target="_blank" '  );

			$schema=' '.atkHref(dispatch_url("organisme.organisme", "affiche_table_definition", array (
					"table" => $this->m_table
			)),	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/mysql-icon.png" alt="Schéma" title="Schéma de la table mySql '.$this->m_table.'" target="_blank"></img>'
					 ,SESSION_NEW, false, 'target="_blank"');

			$datarecord=' '.atkHref(dispatch_url("organisme.organisme", "affiche_record", array (
					"table" => $this->m_table,
					"id_table" => $record["id"]
			)),	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Misc-Web-Database-icon.png" alt="Enregistrement sql" title="Enregistrement mySql(#'.$record["id"].') de '.$this->m_table.'" target="_blank"></img>'
					 ,SESSION_NEW, false, 'target="_blank"')  ;

			$editrecord=' '.atkHref(dispatch_url("application.mysql_table", "edit", array (
					"mysql_table" => $this->m_table,
					"atkselector" => $this->m_table.".id=".$record["id"]
			)),	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/database-accept-icon.png" alt="Modification" title="Modification mySql record (#'.$record["id"].') de '.$this->m_table.'" target="_blank"></img>'
					,SESSION_NEW, false, 'target="_blank"')  ;
			
			
			global  $g_sessionManager;
			$g_sessionManager->globalVar("atk_record", $record, true);
			
			$atk_record=atkHref(dispatch_url("organisme.organisme", "affiche_atk_record",array (
					"module" => $this->m_module,
					"node" => $this->m_type
			)),	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/atk.png" alt="Atk record" title="Atk record : '.$this->m_module.'.'.$this->m_type.'" target="_blank"></img>' 
					,SESSION_NEW, false, 'target="_blank"');
			
			$traduction=href(dispatch_url("application.traduction", "admin", array (
					"atkfilter" => "app_traduction.nom_module='" . $this->m_module . "' and app_traduction.nom_noeud='".$this->m_type . "' "
			)), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google-translate-android-app.png" alt="AssoCope wiki" title="Traduction et messages de  '.$this->m_module.'.'.$this->m_type.'" target="_blank"></img>' 
				, SESSION_NEW, false, 'target="_blank" '  ) . "";
			
			$log=href(dispatch_url("organisme.tableaudebord", "tableau_logs", array (
					"type_tableau"=>"logs"
			)), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/log-icon.png" alt="AssoCope wiki" title="Logs" target="_blank"></img>'
					, SESSION_NEW, false, 'target="_blank" '  ) . "";
		$texte="Module ".$this->m_module.'.'.$this->m_type;
			$texte=str_replace(' ', '_', $texte);
			
			$aide=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)), 
			'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Button-Help-icon.png" alt="AssoCope wiki" title="Aide sur '.$this->m_module.'.'.$this->m_type.'" target="_blank"></img>' 
				,	SESSION_NEW,	false,  ' target="_blank"');
			
			
		$descripteur_operations="".$this->table_operations($this->m_module.".".$this->m_type, $this->m_table, $record["id"]);
		$descripteur_operations.= " - ".$source."".$schema."".$datarecord."".$editrecord."".$atk_record."".$traduction."".$log." ".$aide;
		
		// GG ATTENTION shnt des aides
		
	//	$descripteur=$descripteur_operations;
		}
	
		(is_string($record["id_creation"])) ? $id_creation=$record["id_creation"] : $id_creation=$record["id_creation"] ["id"] ;
		(is_string($record["id_modification"])) ? $id_modification=$record["id_modification"] : $id_modification=$record["id_modification"] ["id"] ;
		
		global $g_sessionManager;
		$g_utilisateur_individu = $g_sessionManager->getValue("utilisateur_individu", "globals");
		$id_individu_creation=$g_utilisateur_individu[$id_creation];
		$id_individu_modification=$g_utilisateur_individu[$id_modification];
		if ($this->get_acces_restreint()==true)
		{
			$individu_creation=	$this->descripteur_individu($id_individu_creation,'n','n',150,"sans_lien",'n','n','o','','','o');			
			$individu_modification=	$this->descripteur_individu($id_individu_modification,'n','n',150,"sans_lien",'n','n','o','','','o');
		}
		else 
		{
			$individu_creation=	$this->descripteur_individu($id_individu_creation,'n','n',150,"module_estampillage",'n','n','n','','','o');			
			$individu_modification=	$this->descripteur_individu($id_individu_modification,'n','n',150,"module_estampillage",'n','n','n','','','o');
				}
		if ($this->get_acces_restreint()==false)
		{$edit_link=atkHref(dispatch_url($this->m_module.".".$this->m_type, "edit",array (
				"atkselector" => $this->m_table.".id='" . $record["id"] . "'"))
				,'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/accept-icon.png" alt="Modification de '. $record["id"].'" title="Modification de  '.$this->m_module.'.'.$this->m_type. $record["id"].'" target="_blank"></img>'
				,SESSION_NEW, false, 'target="_blank"');}
		else 
		{$edit_link='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/accept-icon.png" alt="Modifié par" title="Modifié par" target="_blank"></img>';}
		
		
//		($descripteur!="")?$descripteur.='</br>' : null;
		include_once (moduleDir("utils") . "class.dateutil.inc");


	$curdate = date("Ymd");
		$date_modification = $record["date_modification"]["year"].$record["date_modification"]["month"].$record["date_modification"]["day"];
	$diff=dateutil :: date_diff($date_modification, $curdate);
		$couleur="Green";
		if ($diff >365)
		{	$couleur="Violet";}
		if ($diff < 8)
		{	$couleur="Red";}
		if ($diff > 7 and $diff < 31) {
			$couleur="Orange";
		} 
		$date_modification='<span style="color:'.$couleur.'"><b>'.$this->dateatktodb($record["date_modification"]).'</b></span>';
		$descripteur.=$edit_link.' '.$date_modification.' '. $individu_modification .'</b>';
		
			$date_creation = $record["date_creation"]["year"].$record["date_creation"]["month"].$record["date_creation"]["day"];
	$diff=dateutil :: date_diff($date_creation, $curdate);
		$couleur="Green";
		if ($diff >365)
		{	$couleur="Violet";}
		if ($diff < 8)
		{	$couleur="Red";}
		if ($diff > 7 and $diff < 31) {
			$couleur="Orange";
		} 
		$date_creation='<span style="color:'.$couleur.'"><b>'.$this->dateatktodb($record["date_creation"]).'</b></span>';
		
		$descripteur.=' <img class="recordlist" border="0" src="./themes/assocope/icons/assocope/add-icon.png" alt="Création" 
		title="Créé par " target="_blank"></img>'. " " . $date_creation .' '. $individu_creation .'</b>'.'';
//		$descripteur.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/add-icon.png" alt="Création" title="Créé par " target="_blank"></img> ' . $individu_creation . " (" . $this->dateatktodb($record["date_creation"]).')</b>'.'';
//		$descripteur.='</br>'.$edit_link.' '. $individu_modification . " (" . $this->dateatktodb($record["date_modification"]).')</b>';
		if ($administrateur=="1")
		{
			$descripteur.=' '.$descripteur_operations;
		}	
		
		
		(!empty($record["commentaire"])) ? $descripteur.='<br />COMMENTAIRE : '.'<b>'.nl2br($record["commentaire"]).'</b>' : $descripteur.='';

		($aide_o_n=='o') ? $descripteur=$descripteur.'&nbsp;'.$this->descripteur_aide('Descripteur_module_estampillage','n').'<br />' : $descripteur=$descripteur.'<br />';
		return $descripteur;
	}

	function datedb2value($datein)
	{
		if (!isset($datein) || strlen($datein) == 0 || (int)substr($datein, 0, 4) == 0) return "";
		return array("year" =>substr($datein, 0, 4),
				"month"=>substr($datein, 5, 2),
				"day"  =>substr($datein, 8, 2));
	}
	function datetimedb2value($datein)
	{
		if (!isset($datein) || strlen($datein) == 0 || (int)substr($datein, 0, 4) == 0) return "";
		return array("year" =>substr($datein, 0, 4),
				"month"=>substr($datein, 5, 2),
				"day"  =>substr($datein, 8, 2),
				"hours"=>substr($datein, 11, 2),
				"minutes"=>substr($datein, 14, 2),
				"seconds"=>substr($datein, 17, 2));
	}

	function timedb2value($timein)
	{
		return array("hours"=>substr($timein, 0, 2),
				"minutes"=>substr($timein, 3, 2),
				"seconds"=>substr($timein, 6, 2));
	}
	function getCurrentUrl()
	{
		global $_SERVER;

		/**
		 * Filter php_self to avoid a security vulnerability.
		 */
		$php_request_uri = htmlentities(substr($_SERVER['REQUEST_URI'], 0, strcspn($_SERVER['REQUEST_URI'], "\n\r")), ENT_QUOTES);

		if (isset($_SERVER['HTTPS']) && strtolower($_SERVER['HTTPS']) == 'on') {
			$protocol = 'https://';
		} else {
			$protocol = 'http://';
		}
		$host = $_SERVER['HTTP_HOST'];
		if ($_SERVER['SERVER_PORT'] != '' &&
				(($protocol == 'http://' && $_SERVER['SERVER_PORT'] != '80') ||
						($protocol == 'https://' && $_SERVER['SERVER_PORT'] != '443'))) {
			$port = ':' . $_SERVER['SERVER_PORT'];
		} else {
			$port = '';
		}
		return $protocol . $host . $port . $php_request_uri;
	}

	/*
	 *
	function validate(&$record, $mode)
	{
	//set the feedback to be triggered
	$this->setFeedback("save", ACTION_SUCCESS);
	return true;
	}
	function feedbackUrl ($action, $status, $record="", $message="", $levelskip=1)
	{
	 
	if ($action=="save" && $status==ACTION_SUCCESS ) {
	$xxx = href(dispatch_url($this->atknodetype, "admin"),
			"Identifiant:".$record['id_individu']['nom'], SESSION_BACK );
	$message = "Un participant a été ajouté : ".$xxx;
	}
	 
	return atkNode::feedbackUrl ($action, $status, $record, $message,$levelskip);
	}
	*/
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		//		$mraactions['envoi_groupe'] = "envoi_groupe";
		$mraactions['enveloppes'] = "enveloppes";
		$mraactions['enveloppes_sans_courriel_uniquement'] = "enveloppes_sans_courriel_uniquement";
		$mraactions['geolocalisations'] = "geolocalisations";
		$mraactions['itineraires'] = "itineraires";
		$mraactions['courriels'] = "courriels";
		$mraactions['export_google'] = "export_google";
		$mraactions['noms'] = "noms";
		$mraactions['coordonnees'] = "coordonnees";
		$mraactions['vcards'] = "vcards";
		$mraactions['sans_courriel'] = "sans_courriel";
		$mraactions['avec_courriel'] = "avec_courriel";
		$mraactions['sans_adresse_postale'] = "sans_adresse_postale";
		$mraactions['sans_courriel_et_sans_adresse_postale'] = "sans_courriel_et_sans_adresse_postale";
		$mraactions['copier_individus_dans_presse_papier'] = "copier_individus_dans_presse_papier";
		$mraactions['licence_golf'] = "licence_golf";
		$mraactions['competences'] = "competences";
		$mraactions['synchro_google_contacts'] = "synchro_google_contacts";

		//	$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
	}


	function action_copier_individus_dans_presse_papier() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$param4=null;
		//		$this->p($select);
		$this->traitement_select($select, $idorganisme, $idindividus, $param4);
		$select = explode(",", $idindividus);
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$db->query("INSERT INTO tmp_copier_coller (id_utilisateur, nom_variable, id_variable, date_creation)  VALUES( '$userid', '$nom_variable','$id_variable', UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE date_creation= UTC_TIMESTAMP()");
		}
		$db->commit();
		//	 atkMessageQueue::addMessage("Les individus sélectionnés ont été copiés dans le presse papier.");

		$this->redirect();
	}
	function getUserFileName ($nomracine,$extension,&$filename,$directory="")
	{
		(empty($directory)) ? $directory=atkconfig(atkuserdocumenttempdir) : $directory=atkconfig($directory);
		if ($directory=='' || dir($directory)==false)
		{
			echo 'Répertoire des utilisateurs non défini dans config et/ou inexistant';
			die();
		}
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$data=$db->getrows("Select id_individu, identifiant from app_utilisateur where id=$userid");
		$idindividu=$data[0]["id_individu"];
		$identifiant=$data[0]["identifiant"];
		$userdirectory=$directory.$idindividu;


		if (dir($userdirectory)==false)
		{
			if (mkdir($userdirectory,0744)==false)
			{
				echo 'Impossible de créer le répertoire utilisateur';
				die();
			}

		}
		$filename=gmdate('c').'_'.$identifiant.'_'.$nomracine.'.'.$extension;
		$filename=str_replace('-', '_', $filename);
		$filename=str_replace('+', '_', $filename);
		$filename=str_replace(':', '_', $filename);

		return $userdirectory.'/'.$filename;



	}
	function action_envoi_groupe() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$select = explode(",", $idindividus);
		$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$data = $db->getrows("SELECT count(id) as nombre from individu where id in (".$idindividus.")");
		$nombre_individus=$data[0]["nombre"];
		//						$this->p($nombre_individus);
		$data = $db->getrows("SELECT count(id) as nombre from individu where id in (".$idindividus.") and id in (select id_individu from individu_lieu)");
		$nombre_avec_adresse_postale=$data[0]["nombre"];
		$data = $db->getrows("SELECT count(id) as nombre from individu where id in (".$idindividus.") and courriel is not null");
		$nombre_avec_courriel=$data[0]["nombre"];

		global $g_user;
		$userutilisateur = $g_user["id"];
		global $g_sessionManager;
		$id_individu_utilisateur = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$data = $db->query("INSERT into individu_envoi_groupe
				(
				id_type_envoi_groupe,
				id_utilisateur,
				id_individu_emetteur ,
				id_organisme_emetteur ,
				objet,
				contenu_html,
				id_document_organisme ,
				id_document_organisme_1 ,
				id_document_organisme_2 ,
				id_document_individu ,
				id_document_individu_1 ,
				id_document_individu_2,
				nombre_cible,
				nombre_avec_courriel ,
				nombre_avec_adresse_postale ,
				nombre_retours,
				id_gazette ,
				id_infolettre ,
				id_documentorganisme ,
				id_documentindividu ,
				commentaire,
				id_creation ,
				date_creation ,
				id_modification ,
				date_modification
		)
				VALUES (
				'2',
				'$id_individu_utilisateur ',
				'$id_individu_utilisateur ',
				null ,
				'Envoi groupé',
				null ,
				null ,
				null ,
				null ,
				null ,
				null ,
				null ,
				'$nombre_individus ',
				'$nombre_avec_courriel ',
				'$nombre_avec_adresse_postale ',
				'0',
				null ,
				null ,
				null ,
				null ,
				null ,
				'$userutilisateur ',
				UTC_DATE(),
				'$userutilisateur' ,
				UTC_DATE()
		)");
		$data = $db->getrows("SELECT nextid from  db_sequence where seq_name='seq_individu_envoi_groupe' ");
		$id_envoi_groupe=$data[0]["nextid"];
		$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_envoi_groupe' ");


		foreach ($select as $id_variable) {
			$db->query("INSERT INTO individu_contact
					(
					titre ,
					id_type_contact ,
					id_individu ,
					id_contact ,
					id_envoi_groupe ,
					retour_o_n,
					courriel ,
					date_dernier_courriel ,
					commentaire ,
					commentaire_html ,
					id_document_organisme ,
					id_document_organisme_1 ,
					id_document_organisme_2,
					id_document_individu ,
					id_document_individu_1,
					id_document_individu_2 ,
					date_prevue ,
					date_realisee ,
					id_creation ,
					date_creation ,
					id_modification ,
					date_modification

			)

					VALUES (
					'Envoi groupé',
					'4',
					'$id_variable',
					'$id_individu_utilisateur ',
					'$id_envoi_groupe ',
					'0',
					null,
					null ,
					null,
					null ,
					null ,
					null ,
					null ,
					null ,
					null ,
					null ,
					UTC_DATE(),
					null,
					'$userutilisateur ',
					UTC_DATE() ,
					'$userutilisateur',
					UTC_DATE()

			)
					");
			$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_contact' ");
		}
		$db->commit();
		$this->redirect();
	}
	function action_enveloppes() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("individu.v_individu_lieu", "document", array (
				"atkselector" => "organisme.id=" . $idorganisme,
				"id" => $idorganisme,
				"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1' and v_individu_lieu.id in ( " . $idindividus . " )",
				"atkdoctpl" => "enveloppe_individus_organisme.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "1"
		));
		header("Location: $url");
		exit;
	}
	function action_enveloppes_sans_courriel_uniquement() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("individu.v_individu_lieu", "document", array (
				"atkselector" => "organisme.id=" . $idorganisme,
				"id" => $idorganisme,
				"atkfilter" => "( v_individu_lieu.courriel='' or v_individu_lieu.courriel is null )
				and v_individu_lieu.adresse_defaut_o_n='1'
				and v_individu_lieu.id in ( " . $idindividus . " )",
				"atkdoctpl" => "enveloppe_individus_organisme.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "1"
		));
		header("Location: $url");
		exit;
	}
	function action_geolocalisations() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$adresses_actives_o_n=$this->m_postvars["adresses_actives_o_n"];
		
		$url = dispatch_url("organisme.organisme", "mapindividus", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
					"adresses_actives_o_n" => "o"
		));
		header("Location: $url");
		exit;
	}
	
	function action_itineraires() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$adresses_actives_o_n=$this->m_postvars["adresses_actives_o_n"];
		
		$url = dispatch_url("organisme.organisme", "geolocalisation_inscrits", array (
					"type" => "individus",
					"id" =>  $organismeid ,
		"idindividus" => $idindividus,
					"adresses_actives_o_n" => "o"
			));	
		header("Location: $url");
		exit;
	}
	
	function action_biolocalisation() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		/* tableau
		 *
		$taxons=0;
		$zones=0;
		$date_observation_debut=0;
		$date_observation_fin=0;
		$heure_observation_debut=0;
		$heure_observation_fin=0;
		$organismes_commanditaire=0;
		$organismes_observateur=0;
		$individus_observateur=0;
		*/
		$url = dispatch_url("biodiversite.observation_detail", "mapbiodiversite", 	$this->traitement_select_biolocalisation($select));

		header("Location: $url");
		exit;
	}

	function action_courriels() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '9'
		));
		header("Location: $url");
		exit;
	}

	function action_competences() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '107'
		));
		header("Location: $url");
		exit;
	}
function action_synchro_google_contacts() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("individu.google_feed", "synchro_liste", array (
				"idindividus" => $idindividus,
					));
		header("Location: $url");
		exit;
	}

	function action_licence_golf() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '106'
		));
		header("Location: $url");
		exit;
	}


	function action_export_google()
	{
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus, $idrencontres);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '200'
		));
		header("Location: $url");
		exit;

	}
	function action_noms() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '21'
		));
		header("Location: $url");
		exit;
	}

	/*	function action_exportations() {
	 if (is_array($this->m_postvars["atkselector"])) {
	$select = $this->m_postvars["atkselector"];
	} else {
	$select[0] = $this->m_postvars["atkselector"];
	}
	$this->traitement_select($select, $idorganisme, $idindividus, $idrencontres);
	$url = dispatch_url("organisme.organisme", "listeecran", array (
			"id" => $idorganisme,
			"idindividus" => $idindividus,
			"idrencontres" => $idrencontres,
			"atkcode" => '11',
			"atkexport" => 'o'
	));
	header("Location: $url");
	exit;
	}
	*/
	function action_vcards() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '3'
		));
		header("Location: $url");
		exit;
	}
	function action_sans_courriel() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '5'
		));
		header("Location: $url");
		exit;
	}
	function action_coordonnees() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '31'
		));
		header("Location: $url");
		exit;
	}

	function action_avec_courriel() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '6'
		));
		header("Location: $url");
		exit;
	}

	function upload_google_doc($account,$password,$sourcefilename,$targetfilename)
	{
		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_AuthSub');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Gdata_HttpClient');
		Zend_Loader::loadClass('Zend_Gdata_Docs');
		$service = Zend_Gdata_Docs::AUTH_SERVICE_NAME;
		$client = Zend_Gdata_ClientLogin::getHttpClient($account, $password, $service);
		$docs = new Zend_Gdata_Docs($client);
		$fdw = fopen($sourcefilename,"r");
		$res=fread($fdw,filesize($sourcefilename));
		fclose($fdw);
		$res= utf8_encode($res);
		$fdw = fopen($sourcefilename, "w");
		fwrite($fdw, $res);
		fclose($fdw);
		$newDocumentEntry = $docs->uploadFile($sourcefilename, $targetfilename,
				null, Zend_Gdata_Docs::DOCUMENTS_LIST_FEED_URI);
		$alternateLink = '';
		foreach ($newDocumentEntry->link as $link) {
			if ($link->getRel() === 'alternate') {
				$alternateLink = $link->getHref();
			}
		}
		$retour="<a href=\"$alternateLink\" target=\"_blank\">\n";
		$retour.=$newDocumentEntry->title."\n";
		$retour.="</a>\n";
		return $retour;
	}
	function action_datagrid_view() {
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="select datagrid from individu, app_utilisateur where app_utilisateur.id=$userid and individu.id =app_utilisateur.id_individu";
		$data=$db->getrows($sql);
		$res = $data[0]["datagrid"];
		//		$this->p($res);
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		$page->addContent($res);
		$outgg=	$output->output($page->render(atktext('app_title') . ' - ' . atktext('Datagrid'), true));
		/*		$filename = gmdate('c').'_'.$this->atkNodeType()."_datagrid.html";
		 Header("Content-Disposition: attachment; filename=$filename");
		Header("Content-Length: " . strlen($outgg));
		Header("Connection: close");
		Header("Content-Type: text/html; name=$filename");
		*/
	}

	function action_assocope_to_google_export() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$sql="select identifiant, google_docs_courriel, google_docs_code
		from app_utilisateur where app_utilisateur.id=$userid ";
		$data=$db->getrows($sql);
		$user=$data[0]["google_docs_courriel"];
		$pass=$data[0]["google_docs_code"];
		$identifiant=$data[0]["identifiant"];
		$i=0;
		foreach ($select as $id_variable) {
			$data=$db->getrows("SELECT organisme_document.id as id_document ,organisme_document.libelle,organisme_document.file_content, organisme_document.file_extension as file_extension
					, o.nom as nom
					from organisme_document , organisme o
					where ".$id_variable." and organisme_document.id_organisme=o.id");

			$file_content= $data[0]["file_content"];
			$file_extension= $data[0]["file_extension"];
			$nomorganisme=$data[0]["nom"];
			$libelle= $data[0]["libelle"];
			$id_document= $data[0]["id_document"];
			$sourcefilename=$identifiant.'_document_organisme_'.gmdate('c').'_'.$id_document.'.'.$file_extension;
			$sourcefilename=str_replace('+00:00','',$sourcefilename) ;
			$sourcefilename=str_replace(':','_',$sourcefilename) ;
			$sourcefilename="./googledatagrid/".$sourcefilename;
			$fdw = fopen($sourcefilename, "w");
			fwrite($fdw, $file_content);
			fclose($fdw);
			$googlefilename=$this->upload_google_doc($user,$pass,$sourcefilename,$sourcefilename);
			$i++;
			echo $i." - Transféré sur le compte ". $user." : ".$googlefilename.'<br />';
		}
		echo ''.$i.' fichiers ont été transférés sur le compte '. $user.'.';
		$db->commit();
		die();
	}

	function action_datagrid_google_export() {
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="select identifiant, datagrid_csv, google_docs_courriel, google_docs_code
		from  app_utilisateur where app_utilisateur.id=$userid ";
		$data=$db->getrows($sql);
		$user=$data[0]["google_docs_courriel"];

		$pass=$data[0]["google_docs_code"];
		if ($user=="" || $pass=="")
		{
			echo "Vous n'avez pas d'adresse gmail. Cette opération est impossible";
			die();
		}
		$res = $data[0]["datagrid_csv"];
		$res=str_replace('",\n','"',$res);
		$sourcefilename=$data[0]["identifiant"].'_datagrid_'.$this->getModule().'_'.$this->getType().'_'.gmdate('c').".csv";
		$sourcefilename=str_replace('+00:00','',$sourcefilename) ;
		$sourcefilename=str_replace(':','_',$sourcefilename) ;
		$sourcefilename="./googledatagrid/".$sourcefilename;
		$fdw = fopen($sourcefilename, "w");
		fwrite($fdw, $res);
		fclose($fdw);
		$googlefilename=$this->upload_google_doc($user,$pass,$sourcefilename,$sourcefilename);
		echo "Un tableau a été créé sur le compte ". $user." : ".$googlefilename;
		die();
	}

	function action_datagrid_google_texte_export() {
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="select identifiant, datagrid, google_docs_courriel, google_docs_code
		from app_utilisateur where app_utilisateur.id=$userid ";
		$data=$db->getrows($sql);
		$user=$data[0]["google_docs_courriel"];
		$pass=$data[0]["google_docs_code"];
		if ($user=="" || $pass=="")
		{
			echo "Vous n'avez pas d'adresse gmail. Cette opération est impossible";
			die();
		}
		$res = $data[0]["datagrid"];
		$res=str_replace('",\n','"',$res);
		$sourcefilename=$data[0]["identifiant"].'_datagrid_'.$this->getModule().'_'.$this->getType().'_'.gmdate('c').".html";
		$sourcefilename=str_replace('+00:00','',$sourcefilename) ;
		$sourcefilename=str_replace(':','_',$sourcefilename) ;
		$sourcefilename="./googledatagrid/".$sourcefilename;
		$fdw = fopen($sourcefilename, "w");
		fwrite($fdw, $res);
		fclose($fdw);
		$googlefilename=$this->upload_google_doc($user,$pass,$sourcefilename,$sourcefilename);
		echo "Un document texte a été créé sur le compte ". $user." : ".$googlefilename;
		die();
	}


	function action_sans_adresse_postale() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '8'
		));
		header("Location: $url");
		exit;
	}
	function action_sans_courriel_et_sans_adresse_postale() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '7'
		));
		header("Location: $url");
		exit;
	}
	function action_autocomplete($handler)
	{
		global $g_sessionManager;
		$manytoone_autocomplete_minchars = $g_sessionManager->getValue("manytoone_autocomplete_minchars", "globals");
		($manytoone_autocomplete_minchars> 2)? $this->m_autocomplete_minchars=$manytoone_autocomplete_minchars :      $this->m_autocomplete_minchars = atkconfig("manytoone_autocomplete_minchars", 2);
		$this->m_autocomplete_searchmode = atkconfig("manytoone_autocomplete_searchmode", "contains");
		$this->m_autocomplete_search_case_sensitive = atkconfig("manytoone_autocomplete_search_case_sensitive", false);
		$searchvalue=$this->m_postvars["value"];
		if (strlen($searchvalue) < $this->m_autocomplete_minchars)
	 {
	 	$option='<ul><li class="minimum_chars">'.sprintf($this->text('autocomplete_minimum_chars'), $this->m_autocomplete_minchars).'</li></ul>';
	 	$option = atk_iconv( atktext("charset"), "UTF-8",$option);
	 	echo $option;
	 	die();
	 }
		$db_table=$this->getTable();
		$nodetype=$this->atkNodeType();
		$db = & atkGetDb();


		if ($nodetype== 'individu.individu')
		{
			$db_columns = array("nom","prenom");
			$filter = $this->createSearchFilter($db_columns,$searchvalue, $db_table );
			//		$filter="ccc dfd ";
			$sql='SELECT id, nom, prenom from '.$db_table.'
					where '.$filter.'  ';

			//		 	echo "Individu autocomplete";
			//	die();
		}
		/*
		 if ($nodetype== 'organisme.parcours_golf')
		 {$db_columns = array("libelle");
		$filter = $this->createSearchFilter($db_columns,$searchvalue, $db_table );
		$db_columns = array("nom");
		$db_table="organisme";
		$filter.=" and ". $this->createSearchFilter($db_columns,$searchvalue, $db_table );

		$sql='SELECT organisme_parcours_golf.id, organisme_parcours_golf.libelle, organisme.nom from organisme_parcours_golf, organisme
		where organisme_parcours_golf.id_organisme=organisme.id and '.$filter.'  ';}
		*/

		if ($nodetype== 'organisme.organisme')
		{
			$db_columns = array("nom","sigle");
			$filter = $this->createSearchFilter($db_columns,$searchvalue, $db_table );
			$sql='SELECT id, nom, sigle from '.$db_table.'
					where '.$filter.'  ';
		}

		if ($nodetype== 'biodiversite.taxinomie')
		{
			$db_columns = array("nom_binomial","inpn_nom_complet","nom_francais","cd_nom","cd_ref");
			$filter = $this->createSearchFilter($db_columns,$searchvalue, $db_table );
			$sql='SELECT id, nom_binomial,inpn_nom_complet,nom_francais,cd_nom,cd_ref from '.$db_table.'
					where '.$filter.'  ';
		}
		/*
		 $option='<ul><li class="minimum_chars">'.$filter.'</li></ul>';
		$option = atk_iconv( atktext("charset"), "UTF-8",$option);
		echo $option;
		echo die();
		*/


			
		$records=$db->getrows($sql);
		if (count($records) == 0)
		{
			if(in_array($this->m_autocomplete_searchmode,array("exact","startswith","contains")))
				$str = $this->text('autocomplete_no_results_'.$this->m_autocomplete_searchmode);
			else
				$str = $this->text('autocomplete_no_results');
			$option='<ul><li class="no_results">'.$str.'</li></ul>';
			$option = atk_iconv( atktext("charset"), "UTF-8",$option);
			echo $option;
			die();
		}
		$result = '';
		foreach ($records as $rec)
		{
			if ($nodetype== 'individu.individu')
			{
				$option = ($rec["nom"].' '.$rec["prenom"]);
			}
			if ($nodetype== 'organisme.organisme')
			{
				$option = ($rec["nom"].' '.$rec["sigle"]);
			}
			if ($nodetype== 'biodiversite.taxinomie')
			{
				$option = ($rec["nom_binomial"].' - '.$rec["inpn_nom_complet"].' - '.$rec["nom_francais"].' - '.$rec["cd_nom"].'/'.$rec["cd_ref"]);
			}
			$value = $rec["id"];
			$option = atk_iconv( atktext("charset"), "UTF-8",$option);
			if ($nodetype== 'biodiversite.taxinomie')
			{
				$sql="Select count(id) as nombre from biodiversite_observation_detail where id_taxinomie=$value";
				$data=$db->getrows($sql);
				$nombre=$data[0]["nombre"];
				$posslash=strripos("$option","/");
				$cd_ref=substr($option,$posslash+1,strlen($option)-$posslash);
				$posstiret=strripos("$option","-");
				$cd_nom=substr($option,$posstiret+1,$posslash-$posstiret-1);

				if ($cd_ref==$cd_nom)
				{
					$highlightedOption = '<span style="font-weight: bold ; color: Red  ">('.$nombre.') 	</span>'
							.'<span style=" color: Green  ">'.preg_replace('/('.preg_quote($searchvalue).')/i', '<span class="atkmanytoone_highlite">\\1</span>', $option).'</span>';
				}
				else {
					$highlightedOption = '<span style="font-weight: bold ; color: Red  ">('.$nombre.') </span>'
							.preg_replace('/('.preg_quote($searchvalue).')/i', '<span class="atkmanytoone_highlite">\\1</span>', $option);
				}
			}
			else
			{
				$highlightedOption = preg_replace('/('.preg_quote($searchvalue).')/i', '<span class="atkmanytoone_highlite">\\1</span>', $option);
			}






			// si $this->m_table=="biodiversite_taxinomie"
			// voir si id_taxinomie==$value existe dans table biodiversite_observation_detail
			// si oui $highlightedOption="<i>".$highlightedOption."</i>" pour montrer que cette espèce a déjà été observée

			// GG spécial taxinomie


			$result .= '
					<li title="'.$option.'">
							'.$highlightedOption.'
									<span class="selection" style="display: none">'.$option.'</span>
											<span class="value" style="display: none">'.$value.'</span>
													</li>';
		}
		echo "<ul>$result</ul>";
		die();
	}

	function action_node_table_search($handler) {
		$db_table=$this->getTable();
		$nodetype=$this->atkNodeType();
		$db = & atkGetDb();
		require './modules/search/db_search.php';
		// get columns names

	}

	function action_full_base_search($handler) {

	}
	function action_labels_search($handler) {

	}
	function curlFetchURL($url) {
		// create a new curl resource
		$ch = curl_init();

		// set URL and other appropriate options
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		// grab URL and pass it to the browser
		$content = curl_exec($ch);

		// close curl resource, and free up system resources
		curl_close($ch);
		return $content;
	}

	function preAdd(& $record) {
		$user = getUser();
		$id = $user["id"];
		if (!isset ($id)) {
			$id = "1";
		}
		$curdate = date("Y-m-d");
		$record['id_modification'] = "$id";
		$record['date_modification'] = $this->datetimedb2value(gmdate(c));
		$record['id_creation'] = "$id";
		$record['date_creation'] =$this->datetimedb2value(gmdate(c));


		return true;
	}
	function preUpdate(& $record) {
		$user = getUser();
		$id = $user["id"];
		if (!isset ($id)) {
			$id = "1";
		}
		$curdate = date("Y-m-d");
		$record['id_modification'] = "$id";
		$record['date_modification'] = $this->datetimedb2value(gmdate(c));
		return true;
	}
	function adminHeader()
	{
			
		// Si NF_COMPACT et compactage_actif=true Proposer switch vers compactage_actif=false
		// Si NF_COMPACT et compactage_actif=false Proposer switch vers compactage_actif=true
		// Si pas de flag NF_COMPACT rien.

		if ($this->hasFlag(NF_COMPACT))
		{
			global $g_sessionManager;
			$compact = $g_sessionManager->stackVar("compact");
			if ($compact == "") {
				$compact = "actif";
			}
			if ($compact == "actif") {
				$imageadd='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Button-Add-icon.png" alt="Passer en mode étendu" title="Passer en mode étendu"></img>';

				$mescompact= atktext("L'affichage est actuellement en mode compact : ") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&compact=inactif', '==> Etendre '.$imageadd ) ;
			} else {
				$imageminus='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Math-minus-icon.png" alt="Passer en mode compact" title="Passer en mode compact"></img>';

				$mescompact= atktext("L'affichage est actuellement en mode étendu : ") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&compact=actif', '==> Compacter '.$imageminus) ;
			}
			return $mescompact."<br/>";
		}
		else { return "";
		}
	}
	
	function afficheGraphique($res,$titre,$index=null,$multiply=null)
	{
		include_once (atkconfig("atkroot")."modules/GChartPhp/gChart.php");
		include_once (atkconfig("atkroot")."modules/GChartPhp/tableExtractor.class.php");
		$lineChart = new gLineChart(600,160);
		$tx = new tableExtractor;
		$tx->source = $res;
		$tx->anchorWithin = false;
		$tx->anchor = null;
		$tx->stripTags = true;
		$tx->headerRow = false;
		$tableArray = $tx->extractTable();
		if ($index>0)
		{
			$count=count($tableArray[$index]);
			$tableArray[$index][1]=$tableArray[$index][1]."*".$multiply;
			for ($i=2;$i<=$count;$i++)
			{
			$tableArray[$index][$i]=$tableArray[$index][$i]*$multiply;
			}
			}
			//		$this->p($tableArray);
			$titreaxex=array_shift($tableArray[1]);
			$annees=$tableArray[1];
			$start=$tableArray[1][2];
			$count=count($tableArray[1]);
			$end=$tableArray[1][$count];
			$legend=array();
			$min="";
			$max=0;
			$count=count($tableArray);
			for ($i=2;$i<=$count;$i++)
			{
			$count1=count($tableArray[$i]);
			$legend[]=$tableArray[$i][1];
			$dataset=array();
			for ($j=2;$j<=$count1;$j++)
			{
			($tableArray[$i][$j]=="") ? $tableArray[$i][$j]=0 : null;
			($tableArray[$i][$j]>$max) ? $max=$tableArray[$i][$j] : null;
			($min=="" || $tableArray[$i][$j]<$min) ? $min=$tableArray[$i][$j] : null;
			$dataset[]=$tableArray[$i][$j];
			}
			$lineChart->addDataSet($dataset);
			}
			$lineChart->setVisibleAxes(array('y','x'));
			$lineChart->setLegend($legend);
			$lineChart->setDataRange($min,$max);
			$lineChart->addAxisRange(0, $min, $max);
			$lineChart->addAxisLabel(1, $annees);
			$lineChart->setGridLines(20, 10);
			$lineChart->setColors(array("11ff11", "11ffff", "FF00FF", "000000", "ff3344"));
					$lineChart->setTitle($titre);
					$lineChart->setLineStyles(array("3", "3", "3", "3", "3"));
							$url=$lineChart->getUrl();
							$retour.='<img src="'.$url.'" />';
									return $retour;
	
		}
	


	/*
	 *
	function adminFooter()
	{
	$module = getNodeModule($node);
	$type = getNodeType($node);
	return nodeHelpUrl($this->atkNodeType())." Tutoriel Demandes ".nodeSourceUrl($this->atkNodeType());

	}
	*/
	//This is are two little functions that I made to quickly debug my arrays
	//while making php scripts.  You can pass these things any variable (both
	//arrays and non arrays), and it will print out everything that is in it.
	//It will even print out embedded arrays, so if you have arrays in arrays
	//in arrays, it will print all that out in a consice enough format that you
	//will know exactly what is in that variable.
	//
	//You should get output with "key => val", which should look something like
	//the following:
	//
	// admin =>
	//         user           => 1
	//         screwball      => 2
	//         admin          => 4
	//         . . .
	// is    =>
	//         student worker => 1
	//         hacker         => 2
	//         nerd           => 4
	//         admin          => 8
	// . . .
	//
	//call it like the following (where $testVar is a variable of you choice)
	//
	//  print_array($testVar);
	//
	//if your array contains any html code, you may want to call it instead as:
	//
	//  print_array($testVar,"<xmp>","</xmp>");
	//
	//Should be very easy to throw in your code and use...hope you find it useful
	//            Scott Parish <sRparish@bigfoot.com> 1998/02/24
	function p($a, $btag = "", $etag = "") {
		$user=getUser();
		global $g_sessionData;
		$body="<pre><b>Utilisateur : </b>".$user["identifiant"]."\n";
		$body.="<b>Date/heure : </b>".gmdate("c")."\n";
		$e = new Exception;
		$body.="<b>Trace : </b>"."\n".$e->getTraceAsString()."\n\n";
		$body.="<b>Dump : </b>"."\n";
		echo $body;
			
		if (is_array($a)) {
			printf("<table cellpadding=0 cellspacing=0 border='1'> ");
			while (list ($one, $two) = each($a)) {
				/*        printf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
				 "&nbsp;$btag=>$etag</td>".
					 "<td align=right>&nbsp;%s</td></tr>\n"
					 ,$this->sprint_array($two,$btag,$etag));
				*/
				printf("\n<tr valign=baseline><td>$btag$one$etag</td>" . "<td align=right>&nbsp;%s</td></tr>\n", $this->sprint_array($two, $btag, $etag));
			}
			printf("</table>");
		} else {
			printf("%s%s%s", $btag, $a, $etag);
		}
		/*			echo "<br/>Stack : <br/>";
			printf("<table cellpadding=0 cellspacing=0 border='1'> ");
		while (list ($one, $two) = each($g_sessionData)) {
		printf("\n<tr valign=baseline><td>$btag$one$etag</td>" . "<td align=right>&nbsp;%s</td></tr>\n", $this->sprint_array($two, $btag, $etag));
		}
		printf("</table>");
		*/
		die();
	}
	function sprint_array($a, $btag = "", $etag = "") {
		if (is_array($a)) {
			$out = sprintf("<table cellpadding=0 cellspacing=0 border='1'>");
			while (list ($one, $two) = each($a)) {
				/*       $out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
				 "&nbsp;$btag=>$etag</td>".
					 "<td align=right>&nbsp;%s</td></tr>\n"
					 ,$this->sprint_array($two,$btag,$etag));
				*/
				$out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td>" . "<td align=right>&nbsp;%s</td></tr>\n", $this->sprint_array($two, $btag, $etag));
			}
			$out .= "</table>";
			return $out;
		} else {
			return sprintf("%s%s%s", $btag, $a, $etag);
		}
	}

	function string_trim_from_end ($meuledefoin,$aiguille )
	{

		$chercher=true;
		while ($chercher==true)
		{
			$meuledefoin=trim($meuledefoin);
			$pos=strripos($meuledefoin, $aiguille);
			if ($pos==strlen($meuledefoin)-1)
			{
				$meuledefoin=substr($meuledefoin,0,strlen($meuledefoin)-strlen($aiguille));
			}
			else
			{$chercher=false;
			}

		}
		return $meuledefoin;
	}
	/*

	/*
	function p($array) {

	print "<table border='1'>";
	foreach ($array as $key => $val) {
	print "<tr><td><font size=2>" . $key . "</td><td><font size=2>";
	if (is_array($array[$key])) {
	$this->p($array[$key]);
	print "</td></tr>";
	} else
		print $val . "</td></tr>";
	}
	print "</table>";
	die();


	}
	*/
	function getProchainIdEcriture($id_organisme) {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT prochain_id_ecriture FROM organisme where id=$id_organisme ");
		$id_ecriture = $data[0]["prochain_id_ecriture"];
		$db->query("UPDATE organisme set prochain_id_ecriture=prochain_id_ecriture+1 where id=$id_organisme ");
		return $id_ecriture;
	}
	function creer_ecriture_comptable($organisme, $journal, $libelle, $date_ecriture) {
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		if (empty ($date_ecriture)) {
			$date_ecriture = gmdate(c);
		}
		$data = $db->getrows("SELECT date_fin_exercice_comptable FROM organisme where id=$organisme ");
		$date_fin_exercice_comptable = $data[0]["date_fin_exercice_comptable"];
		if ($date_ecriture > $date_fin_exercice_comptable)
			null ;
		else 
		{
			echo '<br><b>Date d\'écriture antérieure à la fin d\'exercice<br> ';
			die();
		}
		$id_ecriture_organisme = $this->getProchainIdEcriture($organisme);
		$libelle=escapeSQL($libelle);
		$requete = "INSERT INTO organisme_ecriture_comptable
				(  id_organisme,
				id_journal,
				id_ecriture_organisme,
				libelle,
				date_ecriture,
				commentaire,
				id_creation,
				date_creation,
				id_modification,
				date_modification)  " . "
				VALUES
				( '$organisme' ,
				'$journal',
				'$id_ecriture_organisme',
				'$libelle',
				'$date_ecriture',
				'',
				'$userid',
				UTC_TIMESTAMP(),
				'$userid',
				UTC_TIMESTAMP())
				";
		$db->query($requete);
		$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_organisme_ecriture_comptable' ");
		$query = "select id as id_ecriture from organisme_ecriture_comptable
		where id_ecriture_organisme=$id_ecriture_organisme and id_organisme=$organisme";
		$rows = $db->getrows($query);
		$id_ecriture = $rows[0]["id_ecriture"];
		return $id_ecriture;
	}
	function creer_ligne_ecriture_comptable($ecriture, $journal, $compte, $organisme, $individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque) {
		if ($debit == 0 && $credit == 0)
			return;
		global $g_user;
		if (empty ($id_type_reglement)) {
			$id_type_reglement = null;
		}
		if (empty ($numero_piece)) {
			$numero_piece = null;
		}
		if (empty ($date_reglement)) {
			$date_reglement = null;
		}
		if (empty ($id_type_banque)) {
			$id_type_banque = null;
		}
		$date_operation = $db = & atkGetDb();
		$userid = $g_user["id"];
		$data = $db->getrows("select date_ecriture from organisme_ecriture_comptable where id=$ecriture");
		$date_ecriture = $data[0]["date_ecriture"];
		$date_operation = $date_ecriture;
		$date_valeur = $date_ecriture;
		$requete = "INSERT INTO organisme_ligne_ecriture_comptable
				(  id_ecriture,id_journal,id_compte,id_individu,id_organisme,debit,credit,commentaire,id_creation, date_creation,
				id_modification, date_modification,id_type_reglement, numero_piece, date_reglement, id_type_banque, date_operation, date_valeur)  " . " VALUES
				( '$ecriture' ,'$journal','$compte',	'$individu','$organisme',				'$debit',		'$credit',				'',			'$userid',UTC_TIMESTAMP(),
				'$userid',
				UTC_TIMESTAMP(),
				'$id_type_reglement', '$numero_piece', '$date_reglement', '$id_type_banque', '$date_operation', '$date_valeur')
				";
		$db->query($requete);
		$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_organisme_ligne_ecriture_comptable' ");
	}
	function supprimer_ecriture_comptable($ecriture) {
		$db = & atkGetDb();
		$data = $db->query("select count(id_releve) as nombre
				from organisme_ligne_ecriture_comptable where id_ecriture = $ecriture and id_releve != null ");
		if ($data[0]["nombre"] > 0) {
			echo "Suppression impossible. Des lignes d'écriture ont été rapprochées.";
			die();
		}
		$data = $db->query("select count(id_remise) as nombre
				from organisme_ligne_ecriture_comptable where id_ecriture = $ecriture and id_remise != null ");
		if ($data[0]["nombre"] > 0) {
			echo "Suppression impossible. Des lignes d'écriture ont été remisées en banque.";
			die();
		}
		$data = $db->query("delete from organisme_ecriture_comptable where id = $ecriture ");
	}
	function dateatktodb($dateatk,$time=true) {
		if ($time==true)
		{
			return ($dateatk["year"] . "-" . $dateatk["month"] . "-" . $dateatk["day"]." ".$dateatk["hours"] . ":" . $dateatk["minutes"] . ":" . $dateatk["seconds"]);
		}
		else
		{return ($dateatk["year"] . "-" . $dateatk["month"] . "-" . $dateatk["day"]);
		}
	}
	function compta_initialisee($id_organisme) {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT date_initialisation_comptabilite  from organisme
				where id ='" . $id_organisme . "'");
		if ($data[0]["date_initialisation_comptabilite"] != null) {
			return true;
		}
		return false;
	}

	function ContexteProcess($menu_top, $url_main) {
		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");

		$session_id = $g_sessionManager->atkStackID();
		$db = & atkGetDb();

		$data = $db->getrows("select id from app_contexte where
				id_individu=$id_individu and session_id=$session_id and menu_top=$menu_top");
		if (count($data) == 0) {
			$db->query("Insert into app_contexte set id_individu=$id_individu, session_id=$session_id, menu_top=$menu_top,
					date_contexte=UTC_TIMESTAMP(), compteur=1");
		} else {
			$id = $data[0]["id"];
			$this->ContexteUpdate($id);
		}

		return true;
	}

	function RecentUseProcess($type_entite, $id_entite) {
		if ($id_entite=='')
		{
			return true;
		}


		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
		$id_individu = $data[0]["id_individu"];
		$data = $db->getrows("select id, id_entite from app_recent_use where
				id_individu=$id_individu and id_entite=$id_entite and type_entite='$type_entite'");
		if (count($data) == 0) {
			$db->query("Insert into app_recent_use set id_individu=$id_individu, type_entite='$type_entite', id_entite=$id_entite, date_recent_use=UTC_TIMESTAMP(), compteur=1");
		} else {
			$id = $data[0]["id"];
			$this->RecentUseUpdate($id);
		}
		$this->RecentUseRefresh($type_entite);
		return true;
	}
	function RecentUseUpdate($id) {
		$db = & atkGetDb();
		$db->query("Update  app_recent_use set date_recent_use=UTC_TIMESTAMP(), compteur=compteur+1 where id=$id");
		return true;
	}
	function RecentUseDelete($type_entite, $id_entite) {
		$db = & atkGetDb();
		$db->query("Delete from  app_recent_use where type_entite='$type_entite' and id_entite=$id_entite");
		$this->RecentUseRefresh($type_entite);
		return true;
	}
	function RecentUseRefresh($type_entite) {
		$top_refresh="";
		if ($type_entite == 'organisme') {
			$menu_url = session_url("menu.php?atkmenutop=Organismes", SESSION_DEFAULT);

		}
		if ($type_entite == 'individu') {
			$menu_url = session_url("menu.php?atkmenutop=Individus", SESSION_DEFAULT);

		}
		if ($type_entite == 'rencontre') {
			$menu_url = session_url("menu.php?atkmenutop=Rencontres", SESSION_DEFAULT);
		}
		if ($type_entite == 'compte') {
			$menu_url = session_url("menu.php?atkmenutop=Comptes", SESSION_DEFAULT);
		}
		if ($type_entite == 'envoi') {
			$menu_url = session_url("menu.php?atkmenutop=Envois", SESSION_DEFAULT);
		}
		if ($type_entite == 'langue') {
			$menu_url = session_url("menu.php?atkmenutop=Langues", SESSION_DEFAULT);
		}
		if ($type_entite == 'taxon') {
			$menu_url = session_url("menu.php?atkmenutop=Taxons", SESSION_DEFAULT);
		}
		/*		parent.f2.location.reload()
		*/
		
		
		$script = "
		var newlocation=\"$menu_url\";
		var oldlocation=parent.menu.location.toString();
		parent.menu.location = newlocation;
		";
		$page = & atkinstance("atk.ui.atkpage");
		$page->register_loadScript($script);
		
		/*		$histo_url = dispatch_url("profil.recent_use", "admin", array (
		 "atkfilter" => "recent_use.type_entite='$type_entite'"
		));

		$script = "var newlocation=\"$histo_url\";
		var oldlocation=parent.menu.location.toString();
		if (oldlocation.indexOf(newlocation) == -1) {parent.menu.location = newlocation;}";
		$page = & atkinstance("atk.ui.atkpage");
		$page->register_loadScript($script);
		*/
		return true;
	}
	function adminFooter(){
		$help_text = $this->footer;
		return $help_text;
	}
	function editPage(&$handler, $record, $locked=false)
	{
		return $this->detailPageFooter($handler, $record, $locked);
	}
	function viewPage(&$handler, $record, $locked=false)
	{
		return $this->detailPageFooter($handler, $record, $locked,"view");
	}
	function addPage(&$handler, $record, $locked=false)
	{
		return $this->detailPageFooter($handler, $record, $locked,"add");
	}
	function detailPageFooter(&$handler, $record, $locked=false, $mode="edit")
	{
		if($mode == "view"){
			$page = $handler->viewPage($record, $locked);
		}elseif($mode == "edit") {// edit
			$page = $handler->editPage($record, $locked);
		} else
			$page = $handler->addPage($record, $locked);
		$page .= $this->footer;

		return $page;
	}       // end function

	function controle_requete_biodiversite_exclure_o_n ($table,$id_requete,  $exclure_o_n)
	{
		$db = & atkGetDb();
		$sql="SELECT count(exclure_o_n) as nombre
				FROM ". $table."
						where exclure_o_n !='".$exclure_o_n ."' and id_biodiversite_requete='".$id_requete ."'
								";
		$data = $db->getrows($sql);
		return $data[0]["nombre"];
	}

	function descripteur_aide ($texte,$texte_o_n="o")
	{
		//	$texte="Descripteur_";
		$texte=str_replace(' ', '_', $texte);
		$duree=$this->GetWikiPageAge($texte);
		$hel_red=
		$image_red='<img class="recordlist" border="0" height="16" width="16" src="./themes/assocope/icons/assocope/helpred.png" alt="Aide mise à jour il y a moins d\'une semaine"
			 title="Aide mise à jour il y a moins d\'une semaine'.$qr_adresse_individu.'"></img>';
		$image_orange='<img class="recordlist" border="0" height="16" width="16" src="./themes/assocope/icons/assocope/helporange.png" alt="Aide mise à jour dans le mois écoulé"
			 title="Aide mise à jour dans le mois écoulé'.$qr_adresse_individu.'"></img>';
		$image_blue='<img class="recordlist" border="0" height="16" width="16" src="./themes/assocope/icons/assocope/helpblue.png" alt="Aide existante et mise à jour il y a plus d\'un mois"
			 title="Aide existante et mise à jour il y a plus d\'un mois'.$qr_adresse_individu.'"></img>';
		$image_black='<img class="recordlist" border="0" height="16" width="16" src="./themes/assocope/icons/assocope/helpblack.png" alt="Aide inexistante : la créer ?"
			 title="Aide inexistante : la créer ?'.$qr_adresse_individu.'"></img>';
		if (empty($duree))
		{
			($texte_o_n=="o")? $aide='Aide' : $aide=$image_black;
		}
		else if ($duree<8)
		{
			($texte_o_n=="o")? $aide='<span style="color:crimson"><b>Aide</b></span>' : $aide=$image_red;
		}
		else if ($duree<32)
		{
			($texte_o_n=="o")? $aide='<span style="color:darkOrange"><b>Aide</b></span>' : $aide=$image_orange;
		}
		else
		{		($texte_o_n=="o")? $aide='<b>Aide</b>' : $aide=$image_blue;
		}
		$retour=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)),    $aide,	SESSION_NEW,	false, ' target="_blank"');
		//			$retour='<a href="http://www.wikistoma.org/wiki/index.php?title='.$texte.'"target="_blank">'.$aide."</a>";
		return $retour;
	}
	function GetWikiPageAge($pagename)
	{
		$dbw = & atkGetDb("assocopewiki");
		$data=$dbw->getrows("select page_touched from mw_page where page_title='". $pagename ."'");
		$page_touched=$data[0]["page_touched"];
		if (empty($page_touched)) return "";
		$hours=substr($page_touched, 8,2);
		$minutes=substr($page_touched, 10,2);
		$seconds=substr($page_touched, 12,2);
		$month=substr($page_touched, 4,2);
		$day=substr($page_touched, 6,2);
		$year=substr($page_touched, 0,4);
		$page_touched= mktime($hours,$minutes,$seconds,$month,$day,$year);
		$time=time();
		return (($time-$page_touched)/3600/24);
	}


	function descripteur_activite_reglement($id_individu_activite, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT
				ir.montant_remboursement,
				ir.id_document_justificatif,
				ir.date_reglement,
				ir.id_ecriture_reglement,
				tr.libelle,
				c.libelle as nom_compte, c.code,
				ir.numero_cheque
				from individu_activite ir LEFT JOIN type_reglement tr ON  tr.id=ir.id_reglement LEFT JOIN organisme_compte c ON ir.id_compte_financier=c.id
				where ir.id=$id_individu_activite");
		(!empty($data[0]["montant_remboursement"])) ? $retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/reglement.png" alt="Règlement" title="Règlement" target="_blank"></img></b> Montant remboursé : <b><font style="font-size:18px;">'.$data[0]["montant_remboursement"].'</font></b><br />': $retour.='';
		(!empty($data[0]["libelle"])) ? $retour.="</b>Par : <b>".$data[0]["libelle"].'<br />': $retour.='';
		(!empty($data[0]["numero_cheque"])) ? $retour.='</b>Numéro : <b>'.$data[0]["numero_cheque"].'<br />': $retour.='';
		(!empty($data[0]["date_reglement"])) ? $retour.='</b>Le : <b>'.$data[0]["date_reglement"].'<br />': $retour.='';
		(!empty($data[0]["nom_compte"])) ? $retour.='</b>Compte : <b>'.$data[0]["code"].'-'.$data[0]["nom_compte"].'<br />': $retour.='';
		(!empty($data[0]["id_ecriture_reglement"])) ? $retour.=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => " organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_reglement'] . "'"
		), "dispatch.php"), "Ecriture règlement", SESSION_NESTED).'<br />': $retour.='';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_activite_reglement','n') : $retour.="";
		return $retour;
	}
	function descripteur_depense($id_organisme_depense, $aide_o_n='o')

	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT
				of.id,
				of.libelle,
				of.id_organisme,
				of.reglement_seul_o_n ,
				of.id_organisme_tiers,
				of.id_individu,
				of.description ,
				of.montant_fourniture,
				of.date_reglement,
				of.id_compte_charge,
				of.id_compte_tiers,
				of.id_compte_financier,
				of.id_reglement,
				of.numero_cheque,
				of.numero_facture,
				of.id_document_facture,
				of.id_ecriture_depense,
				of.id_ecriture_reglement,
				tr.libelle as mode_reglement
				from organisme_fourniture of,
				type_reglement tr

				where of.id=$id_organisme_depense
				 and of.id_reglement=tr.id");
		//		$retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />";
		$href=href(dispatch_url("organisme.fourniture", "edit", array (	'atkselector' => "organisme_fourniture.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shopping-cart-down-icon.png" alt="Dépense" title="Dépense" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		//		(!empty($data[0]["libelle"])) ? $retour.=$data[0]["libelle"].'<br />': $retour.='';
		(!empty($data[0]["id_organisme_tiers"])) ? $retour.="</b>Fournisseur : <b>".$this->descripteur_organisme($data[0]["id_organisme_tiers"],'n','n')."<br />" : $retour.="" ;
		(!empty($data[0]["id_individu"])) ? $retour.=$this->descripteur_individu($data[0]["id_individu"],'n','n',null,"Fourniture",'n')."<br />" : $retour.="" ;
		(!empty($data[0]["montant_fourniture"])) ? $retour.='</b>Montant dépense : <b><font style="font-size:18px;">'.$data[0]["montant_fourniture"].'</font></b><br />': $retour.='';
		$retour.='</b>Mode règlement : <b>'.$data[0]["mode_reglement"].'<br />';
		(!empty($data[0]["numero_cheque"])) ? $retour.='</b>Numéro de chèque : <b>'.$data[0]["numero_cheque"].'<br />': $retour.='';
		(($data[0]["reglement_seul_o_n"])==1) ? $retour.='<b>Réglement seul</b><br />': $retour.='';
		(!empty($data[0]["date_reglement"])) ? $retour.='</b>Le : <b>'.$data[0]["date_reglement"].'<br />': $retour.='';
		(!empty($data[0]["numero_facture"])) ? $retour.='</b>N° facture : <b>'.$data[0]["numero_facture"].'<br />': $retour.='';
		(!empty($data[0]["id_document_facture"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_facture"]).'<br />': $retour.='';
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_depense','n') : $retour.="";
		return $retour;
	}
	function descripteur_abandon_creance($id_abandon_creance, $aide_o_n='o')

	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT
				libelle,
				id_organisme,
				id_individu,
				date_operation,
				montant_virement,
				date_envoi_recu_fiscal,
				id_recu_fiscal,
				id_ecriture_virement
				from organisme_abandon_creance

				where id=$id_abandon_creance");
		$href=href(dispatch_url("organisme.abandon_creance", "edit", array (	'atkselector' => "organisme_abandon_creance.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shopping-cart-remove-icon.png" alt="Abandon de créance" title="Abandon de créance" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		$retour.='<b>'.$this->descripteur_individu($data[0]["id_individu"],'n','n',null,"abandon_creance","n").'</b> <br />';
		(!empty($data[0]["montant_virement"])) ? $retour.='</b>Montant virement : <b><font style="font-size:18px;">'.$data[0]["montant_virement"].'</font></b><br />': $retour.='';
		(!empty($data[0]["date_operation"])) ? $retour.='</b>le : <b>'.$data[0]["date_operation"].'</b><br />': $retour.='';
		(!empty($data[0]["id_recu_fiscal"])) ? $retour.='</b>Reçu fiscal : <b>'.$data[0]["id_recu_fiscal"].'</b><br />': $retour.='';
		(!empty($data[0]["date_envoi_recu_fiscal"])) ? $retour.='</b>Envoyé le  : <b>'.$data[0]["date_envoi_recu_fiscal"].'</b><br />': $retour.='';
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_abandon_creance','n') : $retour.="";
		
		return $retour;
	}
	function descripteur_financement($id_financement, $aide_o_n='o')

	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT
				id,
				libelle,
				id_organisme,
				id_organisme_financeur,
				id_individu,
				date_reglement
				from organisme_financement
				where id=$id_financement");
		//		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		$href=href(dispatch_url("organisme.financement", "edit", array (	'atkselector' => "organisme_financement.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/recette.png" alt="Recette" title="Recette" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		$retour.='</b>Origine : <b>'.$this->descripteur_organisme($data[0]["id_organisme_financeur"],'n','n').'</b> <br />';
		(!empty($data[0]["id_individu"])) ? $retour.='<b>'.$this->descripteur_individu($data[0]["id_individu"],'n','n').'</b> <br />': $retour.='';
//		(!empty($data[0]["date_reglement"])) ? $retour.='</b>le : <b>'.$data[0]["date_reglement"].'<br />': $retour.='';
		$retour.=$this->descripteur_reglement('recette',$data[0]["id"],'n');
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_financement','n') : $retour.="";
		return $retour;
	}
	function descripteur_virement_comptable($id_virement, $aide_o_n='o')

	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT
				ovc.libelle,
				ovc.id_organisme,
				cc.code as code_credit,
				cc.libelle as libelle_credit,
				cd.code as code_debit,
				cd.libelle as libelle_debit,

				ovc.montant_virement,
				ovc.date_operation
				from organisme_virement_comptable ovc, organisme_compte cc, organisme_compte cd
				where ovc.id=$id_virement
				and ovc.id_compte_credit=cc.id
				and ovc.id_compte_debit=cd.id");

		$href=href(dispatch_url("organisme.virement_comptable", "edit", array (	'atkselector' => "organisme_virement_comptable.id='" . $id_virement. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/virement.png" alt="Virement comptable" title="Virement comptable" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;

		//		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		//		(!empty($data[0]["libelle"])) ? $retour.=$data[0]["libelle"].'<br />': $retour.='';
		(!empty($data[0]["montant_virement"])) ? $retour.='</b>Montant : <b><font style="font-size:18px;">'.$data[0]["montant_virement"].'</font></b><br />': $retour.='';
		(!empty($data[0]["date_operation"])) ? $retour.='</b>le : <b>'.$data[0]["date_operation"].'<br />': $retour.='';
		$retour.='</b>de : <b>'.$data[0]["code_credit"].'-'.$data[0]["libelle_credit"].'<br />';
		$retour.='</b>à : <b>'.$data[0]["code_debit"].'-'.$data[0]["libelle_debit"].'<br />';
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_virement_comptable','n') : $retour.="";
		return $retour;
	}


	function descripteur_activite_frais($id_individu_activite, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT ir.libelle as libelle_activite,
				ta.libelle as libelle_type,
				ir.id_individu,
				ir.id_organisme,
				ir.id_rencontre,
				ore.libelle as libelle_rencontre,
				ir.id_contact,
				ic.titre,
				ir.date_debut_periode,
				ir.date_fin_periode,
				ir.nombre_heures,
				ir.montant_indemnite_heure,
				ir.nombre_kilometres,
				ir.montant_indemnite_kilometre,
				ir.montant_peage,
				ir.montant_parking,
				ir.montant_taxi,
				ir.montant_transport_en_commun,
				ir.montant_repas,
				ir.montant_hotel,
				ir.montant_fournitures_diverses,
				ir.montant_frais_divers,
				ir.id_document_justificatif,
				od.libelle as libelle_justificatif,
				od.file_size,
				ir.id_ecriture_frais,
				ir.id_ecriture_benevolat
				from individu_activite ir
				LEFT JOIN type_activite ta ON ta.id=ir.id_type_activite
				LEFT JOIN organisme_document od ON ir.id_document_justificatif=od.id
				LEFT JOIN individu_contact ic ON ir.id_contact=ic.id
				LEFT JOIN organisme_rencontre ore ON ir.id_rencontre=ore.id
				where ir.id=$id_individu_activite ");
		$href=href(dispatch_url("individu.activite_i", "edit", array (	'atkselector' => "individu_activite.id='" . $id_individu_activite. "'"
		), "dispatch.php"), $data[0]["libelle_activite"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/activite.png" alt="Activité/Frais" title="Activité/Frais" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		(!empty($data[0]["libelle_type"])) ? $retour.=" (".$data[0]["libelle_type"].')<br />': $retour.='';
		$retour.='<b>'.$this->descripteur_individu($data[0]["id_individu"],'n','n',null,"activite_frais","n").'</b> <br />';
		//		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
//		(!empty($data[0]["libelle_activite"])) ? $retour.=$data[0]["libelle_activite"].'<br />': $retour.='';
		(!empty($data[0]["id_rencontre"]))? $retour.=href(dispatch_url("organisme.rencontre", "view", array (	'atkselector' => "organisme_rencontre.id='" . $data[0]["id_rencontre"]. "'"
		), "dispatch.php"),'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/rencontre.png" alt="'.$data[0]["libelle_rencontre"].'"
				title="'.$data[0]["libelle_rencontre"].'" ></img> '.$data[0]["libelle_rencontre"]."<br />", SESSION_NESTED) : $retour.="";
		(!empty($data[0]["id_contact"]))? $retour.=href(dispatch_url("individu.contact_i", "view", array (	'atkselector' => "individu_contact.id='" . $data[0]["id_contact"]. "'"
		), "dispatch.php"),'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/contact.png" alt="'.$data[0]["titre"].'"
				title="'.$data[0]["titre"].'" ></img> '.$data[0]["titre"]."<br />", SESSION_NESTED) : $retour.="";
		
		(!empty($data[0]["date_debut_periode"])) ? $retour.='</b>Du : <b>'.$data[0]["date_debut_periode"]: $retour.='';
		(!empty($data[0]["date_fin_periode"])) ? $retour.='</b> au : <b>'.$data[0]["date_fin_periode"].'<br />': $retour.='';
		(!empty($data[0]["nombre_kilometres"])) ? $retour.='</b>Kilomètres : <b>'.$data[0]["nombre_kilometres"].' * '.
				$data[0]["montant_indemnite_kilometre"].' = '.$data[0]["nombre_kilometres"]*$data[0]["montant_indemnite_kilometre"].'<br />': $retour.='';

		($data[0]["montant_peage"]>0) ? $retour.='</b>Péage : <b>'.$data[0]["montant_peage"].'<br />': $retour.='';
		($data[0]["montant_parking"]>0) ? $retour.='</b>Parking : <b>'.$data[0]["montant_parking"].'<br />': $retour.='';
		($data[0]["montant_taxi"]>0) ? $retour.='</b>Taxi : <b>'.$data[0]["montant_taxi"].'<br />': $retour.='';
		($data[0]["montant_transport_en_commun"]>0) ? $retour.='</b>Transports en commun : <b>'.$data[0]["montant_transport_en_commun"].'<br />': $retour.='';
		($data[0]["montant_repas"]>0) ? $retour.='</b>Repas : <b>'.$data[0]["montant_repas"].'<br />': $retour.='';
		($data[0]["montant_hotel"]>0) ? $retour.='</b>Hôtel : <b>'.$data[0]["montant_hotel"].'<br />': $retour.='';
		($data[0]["montant_fournitures_diverses"]>0) ? $retour.='</b>Fournitures : <b>'.$data[0]["montant_fournitures_diverses"].'<br />': $retour.='';
		($data[0]["montant_frais_divers"]>0) ? $retour.='</b>Frais divers : <b>'.$data[0]["montant_frais_divers"].'<br />': $retour.='';
		$montant=$data[0]["montant_frais_divers"]+$data[0]["montant_fournitures_diverses"]+$data[0]["montant_hotel"]+$data[0]["montant_repas"]+$data[0]["montant_transport_en_commun"]+$data[0]["montant_taxi"]+$data[0]["montant_parking"]+$data[0]["montant_peage"]+($data[0]["nombre_kilometres"]*$data[0]["montant_indemnite_kilometre"]);
		($montant>0) ? $retour.='</b>Remboursable : <b><font style="font-size:18px;">'.$montant.'</font></b><br />' : $retour.='';
		/*		(!empty($data[0]["id_ecriture_frais"])) ? $retour.=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
		 'atkfilter' => " organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_frais'] . "'"
		), "dispatch.php"), "Ecriture frais", SESSION_NESTED).'<br />': $retour.='';
		*/
		($data[0]["nombre_heures"]>0) ? $retour.='</b>Heures : <b>'.$data[0]["nombre_heures"].' * '.
				$data[0]["montant_indemnite_heure"].' = '.$data[0]["nombre_heures"]*$data[0]["montant_indemnite_heure"].'<br />': $retour.='';
		/*				(!empty($data[0]["id_ecriture_benevolat"])) ? $retour.=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
		 'atkfilter' => " organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_benevolat'] . "'"
		), "dispatch.php"), "Ecriture bénévolat", SESSION_NESTED).'<br />': $retour.='';
		*/
		(!empty($data[0]["id_document_justificatif"])) ? $retour.='</b>Justificatif : <b>'.href(dispatch_url("organisme.document", "view", array (
				'atkselector' => " organisme_document.id='" . $data[0]['id_document_justificatif'] . "'"
		), "dispatch.php"), $data[0]['libelle_justificatif'], SESSION_NESTED).' ': $retour.='';
		(!empty($data[0]["file_size"])) ? $retour.=href(dispatch_url("organisme.document", "fichier", array (
				'atkselector' => " organisme_document.id='" . $data[0]['id_document_justificatif'] . "'"
		), "dispatch.php"), '<font color="ForestGreen"> <b>Fichier</b></font>', SESSION_NESTED).'<br />': $retour.='';
		$retour.=$this->descripteur_activite_reglement($id_individu_activite,'n');
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_activite_frais','n') : $retour.="";
		return $this->decoupe_affichage_colonne($retour,100);
	}


	function descripteur_participant_rencontre($id_rencontre_i, $aide_o_n='o')
	{
		$db = & atkGetDb();

		$sql="select 
		ro.id_organisme,
		ro.libelle_participation_1,
		ro.libelle_participation_2,
		ro.libelle_participation_3,
		ro.libelle_participation_4,
		tt.titre_long,
		 i.id as idindividu,
		  i.nom, i.prenom,
		   ire.id_type_rencontre_participation,
		    ire.date_inscription,
		    ire.id_document_inscription_rencontre,
		    ire.montant_versement,
		    ire.montant_versement_2,
		ire.intervenant_o_n,
		 ire.theme_intervention,
		  ire.id_document_intervenant,
		  ire.id_organisme_participant,
		ire.participation_partielle,
		 ire.participation_complete , 
		 ire.participation_3 ,
		 ire.participation_4 ,
		 ire.covoiturage_places_offertes, ire.covoiturage_places_demandees, trp.libelle
		from 
		individu_rencontre ire ,
		 type_titre tt,
		  individu i,
		   type_rencontre_participation trp,
		   organisme_rencontre ro
		where ro.id=ire.id_rencontre
		and ire.id=$id_rencontre_i
		and ire.id_type_rencontre_participation=trp.id
		and ire.id_individu=i.id
		and i.id_titre=tt.id";
		$data = $db->getrows($sql);
		//		(!empty($data[0]["titre_long"])) ? $retour="<b>".$data[0]["titre_long"]." ".$data[0]["nom"]." ".$data[0]["prenom"]."</b><br />" : $retour="" ;
		$retour.=$this->descripteur_individu($data[0]["idindividu"],'n','n',null,null,"n").'<br />';

		(!empty($data[0]["id_organisme_participant"])) ? $retour.="</b>de : <b> ".$this->descripteur_organisme($data[0]["id_organisme_participant"],'n','n')."<br />" : $retour.="" ;
		(!empty($data[0]["libelle"])) ? $retour.='<b>'.$data[0]["libelle"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["date_inscription"])) ? $retour.='</b>Inscrit le : <b>'.$data[0]["date_inscription"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["id_document_inscription_rencontre"])) ? $retour.="</b>Document d'inscription : <b>".$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_inscription_rencontre"])."<br />" : $retour.="" ;
		($data[0]["intervenant_o_n"]==1) ? $retour.="</b>Intervenant.<b><br />" : $retour.="" ;
		(!empty($data[0]["theme_intervention"])) ? $retour.="</b>Thème :  ".$data[0]["theme_intervention"]."<br />" : $retour.="" ;
		$href=dispatch_url("organisme.document", "edit", array ("atkselector" => "organisme_document.id='" . $data[0]["id_document_intervenant"] . "'"));
		(!empty($data[0]["id_document_intervenant"])) ? $retour.='<a href="'.$href.'" > Document <br />' : $retour.="" ;
		(empty($data[0]["participation_partielle"])) ? $data[0]["participation_partielle"]='0' : null;
		(empty($data[0]["participation_complete"])) ? $data[0]["participation_complete"]='0' : null;
		(empty($data[0]["participation_3"])) ? $data[0]["participation_3"]='0' : null;
		(empty($data[0]["participation_4"])) ? $data[0]["participation_4"]='0' : null;
		if (!empty($data[0]["libelle_participation_1"])
		||!empty($data[0]["libelle_participation_2"])
		||!empty($data[0]["libelle_participation_3"])
		||!empty($data[0]["libelle_participation_4"])
		) 
		{$retour.='</b>Options : <b>';}
		(!empty($data[0]["libelle_participation_1"])) ? $retour.="<b>".$data[0]["participation_partielle"]." (".$data[0]["libelle_participation_1"].")</b>, " : $retour.="" ;
		(!empty($data[0]["libelle_participation_2"])) ? $retour.="<b>".$data[0]["participation_complete"]." (".$data[0]["libelle_participation_2"].")</b>, " : $retour.="" ;
		(!empty($data[0]["libelle_participation_3"])) ? $retour.="<b>".$data[0]["participation_3"]." (".$data[0]["libelle_participation_3"].")</b>, " : $retour.="" ;
		(!empty($data[0]["libelle_participation_4"])) ? $retour.="<b>".$data[0]["participation_4"]." (".$data[0]["libelle_participation_4"].")</b>, " : $retour.="" ;
//		$retour=substr($retour, 0, strlen($retour)-2)."<br/>";
		(!empty($data[0]["covoiturage_places_offertes"])) ? $retour.="</b>Covoiturage proposé : <b>".$data[0]["covoiturage_places_offertes"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["covoiturage_places_demandees"])) ? $retour.="</b>Covoiturage demandé : <b>".$data[0]["covoiturage_places_demandees"]."</b><br />" : $retour.="" ;
		(!empty ($data[0]["montant_versement"])) ? $retour.=$this->descripteur_reglement('participant_rencontre',$id_rencontre_i,'n'):null;
		(!empty ($data[0]["montant_versement_2"])) ? $retour.=$this->descripteur_reglement('participant_rencontre_2',$id_rencontre_i,'n') : null;
		$retour.='<b>'.$this->descripteur_organisme($data[0]["id_organisme"],'n','n').'</b> <br />';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_participant_rencontre','n') : $retour.="";
		
		return $this->decoupe_affichage_colonne($retour,100);
	}


	function descripteur_tournoi($id_tournoi, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		t.id,
		t.id_organisme,
		t.libelle,
		t.id_type_tournoi,
		t.nombre_d_equipes,
		t.nombre_de_participants_individuels,
		t.id_lieu_rencontre,
		t.date_debut_tournoi,
		t.date_fin_tournoi,
		t.blocage_generation_o_n
		from organisme_tournoi t
		where t.id=$id_tournoi";
		$data = $db->getrows($sql);
		$type_tournoi=$data[0]["id_type_tournoi"];
		$sql="select libelle from type_tournoi
	 where id =$type_tournoi";
		$data1 = $db->getrows($sql);
		$libelle_type_tournoi=$data1[0]["libelle"];

		$sql="select count(id) as inscrits from individu_tournoi
	 where id_tournoi =$id_tournoi";
		$data1 = $db->getrows($sql);
		$nombre_inscrits=$data1[0]["inscrits"];
		$sql="select count(id) as nombre from tournoi_equipe
	 where id_tournoi =$id_tournoi";
		$data1 = $db->getrows($sql);
		$nombre_equipes=$data1[0]["nombre"];
		$sql="select count(id) as nombre from tournoi_rencontre
	 where id_tournoi =$id_tournoi";
		$data1 = $db->getrows($sql);
		$nombre_rencontres=$data1[0]["nombre"];

		$sql="select count(trm.id)  as nombre from tournoi_rencontre_match trm , tournoi_rencontre tr
	 where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre";
		$row = $db->getrows($sql);
		$matchs=	$row[0]["nombre"];
		$sql="select count(trm.id)  as nombre from tournoi_rencontre_match trm , tournoi_rencontre tr
	 where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre and trm.date_rencontre_effective is not null";
		$row = $db->getrows($sql);
		$matchsjoues=	$row[0]["nombre"];
		$sql="select count(trm.id)  as nombre from tournoi_rencontre_match trm , tournoi_rencontre tr
	 where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre and trm.date_rencontre_effective is null";
		$row = $db->getrows($sql);
		$matchsajouer=	$row[0]["nombre"];
		$descripteur_matches= '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Love-Football-icon.png" alt="Matchs"
				title="Matchs"  ></img>Matchs (tous/joués/à jouer): <b>'.href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select trm.id from tournoi_rencontre_match trm , tournoi_rencontre tr
						where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre) "
				), "dispatch.php"), text($matchs), SESSION_NESTED,null," alt=\"matchs\" title=\"matchs\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select trm.id from tournoi_rencontre_match trm , tournoi_rencontre tr
						where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre and trm.date_rencontre_effective is not null) "
				), "dispatch.php"),text($matchsjoues), SESSION_NESTED,null," alt=\"matchs joués\" title=\"matchs joués\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select trm.id from tournoi_rencontre_match trm , tournoi_rencontre tr
						where  tr.id_tournoi =$id_tournoi and  tr.id=trm.id_tournoi_rencontre and trm.date_rencontre_effective is null) "
				), "dispatch.php"),text($matchsajouer), SESSION_NESTED,null," alt=\"matchs à jouer\" title=\"matchs à jouer\"");



				$inscrits= href(dispatch_url("tournoi.individu_tournoi", "admin", array (
						'atkfilter' => "individu_tournoi.id_tournoi='" . $id_tournoi . "'"
				), "dispatch.php"),$nombre_inscrits, SESSION_NESTED);
				$equipes= href(dispatch_url("tournoi.tournoi_equipe", "admin", array (
						'atkfilter' => "tournoi_equipe.id_tournoi='" . $id_tournoi . "'"
				), "dispatch.php"), text($nombre_equipes), SESSION_NESTED);
				$rencontres= href(dispatch_url("tournoi.tournoi_rencontre", "admin", array (
						'atkfilter' => "tournoi_rencontre.id_tournoi='" . $id_tournoi . "'"
				), "dispatch.php"), text($nombre_rencontres), SESSION_NESTED);
				$href=atkHref(dispatch_url("tournoi.organisme_tournoi", "edit", array ("atkselector" => "organisme_tournoi.id='" . $id_tournoi . "'" )),
						$data[0]["libelle"],SESSION_NESTED, false, 'target="main"') ;
				$descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/tournoi.png" alt="Tournoi" title="Tournoi" target="_blank"></img>'.
						"<b>".$href."</b> <br />" ;

				//		$descripteur='<b>'.$data[0]["libelle"].'</b><br />';
				$descripteur.="(".$libelle_type_tournoi.')<br />';
				$descripteur.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />";
				(!empty($data[0]["date_debut_tournoi"])) ? $descripteur.="Du <b>".$data[0]["date_debut_tournoi"]."</b><br />" : $descripteur.="" ;
				(!empty($data[0]["date_fin_tournoi"])) ? $descripteur.="</b>au <b>".$data[0]["date_fin_tournoi"]."</b><br />" : $descripteur.="" ;
				(!empty($data[0]["id_lieu_rencontre"])) ? $descripteur.=$this->descripteur_golf_parcours($data[0]["id_lieu_rencontre"],'n','n')."<br />" : $descripteur.="" ;
				(!empty($data[0]["nombre_d_equipes"]) || !empty($data[0]["nombre_de_participants_individuels"])) ? $descripteur.="Prévu (équipes/participants) : (".$data[0]["nombre_d_equipes"]."/".$data[0]["nombre_de_participants_individuels"].")<br />" : $descripteur.="" ;

				$descripteur.= '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/individu.png" alt="Inscrits"
						title="Inscrits"  ></img>'."Inscrits : <b>".$inscrits."</b>";
				($data[0]["blocage_generation_o_n"]==1) ? $descripteur.=" (<b>Clos</b>)<br />" : $descripteur.="</b><br />" ;
				$descripteur.= '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/equipe.png" alt="Equipes"
						title="Equipes"  ></img>'."Equipes : <b>".$equipes."</b><br />";
				$descripteur.= '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/calendrier.png" alt="Rencontres"
						title="Rencontres"  ></img>'."Rencontres : <b>".$rencontres."</b><br />";
				$descripteur.=$descripteur_matches."<br />";

				($aide_o_n=='o') ? $descripteur.=$this->descripteur_aide('Descripteur_tournoi','n') : $descripteur.="";
				return $descripteur;

	}


	function descripteur_tournoi_equipe($id_equipe, $aide_o_n) {
		$db = & atkGetDb();
		$sql="select nom_d_equipe, numero_d_equipe, jour_rattrapage_o_n   from tournoi_equipe
				where  id = ".$id_equipe." ";
		$row = $db->getrows($sql);
		($row[0]["jour_rattrapage_o_n"]=='1') ? $equipe_texte.="<br />Jour de rattrapage  : <b>oui"."</b>" : null;
		$sql="select count(id)  as nombre from tournoi_rencontre_equipe
	 where  id_tournoi_equipe =$id_equipe ";
		$row = $db->getrows($sql);
		$matchs=$row[0]["nombre"];
		$sql="select count(tre.id)  as nombre from tournoi_rencontre_equipe tre, tournoi_rencontre_match trm
	 where  tre.id_tournoi_equipe = $id_equipe and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is not null";
		$row = $db->getrows($sql);
		$matchsjoues=$row[0]["nombre"];
		$sql="select count(tre.id)  as nombre from tournoi_rencontre_equipe tre, tournoi_rencontre_match trm
	 where  tre.id_tournoi_equipe = $id_equipe and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is  null";
		$row = $db->getrows($sql);
		$matchsajouer=$row[0]["nombre"];

		$equipe_texte.= '</br><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Love-Football-icon.png" alt="Matchs"
				title="Matchs"  ></img>Matchs (tous/joués/à jouer): <b>'.href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select id_tournoi_match from tournoi_rencontre_equipe
						where  id_tournoi_equipe =$id_equipe) "
				), "dispatch.php"), text($matchs), SESSION_NESTED,null," alt=\"matchs\" title=\"matchs\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select tre.id_tournoi_match from tournoi_rencontre_equipe tre, tournoi_rencontre_match trm
						where  tre.id_tournoi_equipe = $id_equipe and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is not null) "
				), "dispatch.php"),text($matchsjoues), SESSION_NESTED,null," alt=\"matchs joués\" title=\"matchs joués\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in (select tre.id_tournoi_match from tournoi_rencontre_equipe tre, tournoi_rencontre_match trm
						where  tre.id_tournoi_equipe = $id_equipe and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is null) "
				), "dispatch.php"),text($matchsajouer), SESSION_NESTED,null," alt=\"matchs à jouer\" title=\"matchs à jouer\"");
				$ret= $this->descripteur_tournoi_equipe_participants($id_equipe,'o');
				$ret.="<b>".$equipe_texte."</b>";
				($aide_o_n=='o') ? $ret.="</br>".$this->descripteur_aide('Descripteur_tournoi_equipe','n') : $ret.="";
				return $ret;
	}

	function descripteur_tournoi_equipe_participants($id_equipe, $aide_o_n) {
		$db = & atkGetDb();
		$sql="select nom_d_equipe, numero_d_equipe, jour_rattrapage_o_n   from tournoi_equipe
				where  id = ".$id_equipe." ";
		$row = $db->getrows($sql);
		$href=atkHref(dispatch_url("tournoi.tournoi_equipe", "edit", array ("atkselector" => "tournoi_equipe.id='" . $id_equipe . "'" )),
				$row[0]["nom_d_equipe"]." (".$row[0]["numero_d_equipe"].")",SESSION_NESTED, false, 'target="main"') ;
		$equipe_texte='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/equipe.png" alt="Equipe" title="Equipe" target="_blank"></img>'.
				"<b>".$href."</b> " ;
		$numero_equipe=($row[0]["numero_d_equipe"]);
		$nom_equipe=($row[0]["nom_d_equipe"]);
		$sql="select i.id as individu from individu i, individu_tournoi it, tournoi_equipe_participant tep
				where tep.id_tournoi_equipe=".$id_equipe." and tep.id_individu_tournoi=it.id and it.id_individu=i.id
						order by i.nom, i.prenom  ";;
		$row1= $db->getrows($sql);
		$joueurs="";
		for ($j = 0; $j < count($row1); $j++) {
			$joueurs.=	$this->descripteur_individu($row1[$j]["individu"],'n','n', 100, "tournoi_match","n","n")."</br>";
		}
			
		$descripteur="</br></br>".$equipe_texte ."</b></br>".substr($joueurs, 0,strlen($joueurs)-5);
		return $descripteur;
	}

	function descripteur_tournoi_rencontre($id_rencontre, $aide_o_n) {
		$db = & atkGetDb();
		$sql="select numero_de_rencontre, date_rencontre, date_rattrapage_rencontre, date_limite_rencontre, id_lieu_rencontre from tournoi_rencontre
				where  id = ".$id_rencontre." ";
		$row = $db->getrows($sql);
		$href=atkHref(dispatch_url("tournoi.tournoi_rencontre", "edit", array ("atkselector" => "tournoi_rencontre.id='" . $id_rencontre . "'" )),
				"Rencontre ".$row[0]["numero_de_rencontre"],SESSION_NESTED, false, 'target="main"') ;
		$descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/calendrier.png" alt="Rencontre" title="Rencontre" target="_blank"></img>'.
				"<b>".$href."</b> " ;
		$descripteur.="<br /></b>Date : <b>".$row[0]["date_rencontre"]."</b>";
		$descripteur.="<br /></b>Rattrapage : <b>".$row[0]["date_rattrapage_rencontre"]."</b>";
		$descripteur.="<br /></b>Date limite : <b>".$row[0]["date_limite_rencontre"]."</b>";
		(!empty($row[0]["id_lieu_rencontre"])) ? $descripteur.="</br>".$this->descripteur_golf_parcours($row[0]["id_lieu_rencontre"],'n','n') : $descripteur.="" ;
		$sql="select count(id)  as nombre from tournoi_rencontre_match
				where  id_tournoi_rencontre = ".$id_rencontre." ";
		$row = $db->getrows($sql);
		$matchs=	$row[0]["nombre"];
		$sql="select count(id)  as nombre from tournoi_rencontre_match
				where  id_tournoi_rencontre = ".$id_rencontre." and date_rencontre_effective is not null";
		$row = $db->getrows($sql);
		$matchsjoues=	$row[0]["nombre"];
		$sql="select count(id)  as nombre from tournoi_rencontre_match
				where  id_tournoi_rencontre = ".$id_rencontre." and date_rencontre_effective is null";
		$row = $db->getrows($sql);
		$matchsajouer=	$row[0]["nombre"];
		$descripteur.= '</br><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Love-Football-icon.png" alt="Matchs"
				title="Matchs"  ></img>Matchs (tous/joués/à jouer): <b>'.href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in ( select id from tournoi_rencontre_match	 where  id_tournoi_rencontre =$id_rencontre )"
				), "dispatch.php"), text($matchs), SESSION_NESTED,null," alt=\"matchs\" title=\"matchs\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id in ( select id from tournoi_rencontre_match	 where  id_tournoi_rencontre =$id_rencontre and date_rencontre_effective is not null)"
				), "dispatch.php"), text($matchsjoues), SESSION_NESTED,null," alt=\"matchs joués\" title=\"matchs joués\"").'/'.
				href(dispatch_url("tournoi.tournoi_rencontre_match", "admin", array (
						'atkfilter' => "tournoi_rencontre_match.id  in ( select id from tournoi_rencontre_match	 where  id_tournoi_rencontre =$id_rencontre and date_rencontre_effective is null)"
				), "dispatch.php"), text($matchsajouer), SESSION_NESTED,null," alt=\"matchs à jouer\" title=\"matchs à jouer\"");
				($aide_o_n=='o') ? $descripteur.="</br>".$this->descripteur_aide('Descripteur_tournoi_rencontre','n') : $descripteur.="";
				return $descripteur;
	}

	function descripteur_tournoi_rencontre_match($id_match, $aide_o_n) {
		$db = & atkGetDb();
		$sql="select numero_de_match,id_lieu_match, date_rencontre_effective  from tournoi_rencontre_match
				where  id = ".$id_match." ";
		$row = $db->getrows($sql);
		$href=atkHref(dispatch_url("tournoi.tournoi_rencontre_match", "edit", array ("atkselector" => "tournoi_rencontre_match.id='" . $id_match . "'" )),
				"Match ".$row[0]["numero_de_match"],SESSION_NESTED, false, 'target="main"') ;
		$descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Love-Football-icon.png" alt="Match" title="Match" target="_blank"></img>'.
				"<b>".$href."</b> " ;
		(!empty($row[0]["id_lieu_match"])) ? $descripteur.="</br>".$this->descripteur_golf_parcours($row[0]["id_lieu_match"],'n','n') : $descripteur.="" ;
		$date_match=$row[0]["date_rencontre_effective"];
		(!empty($date_match)) ? $descripteur.="<br />Joué le : <b>$date_match"."</b>" : null;
		$sql="select count(id)  as nombre from tournoi_rencontre_equipe
				where  id_tournoi_match = ".$id_match." ";
		$row = $db->getrows($sql);
		$actifs=	$row[0]["nombre"];
		$descripteur.="</br>Equipes : <b>".href(dispatch_url("tournoi.tournoi_rencontre_equipe", "admin", array (
				'atkfilter' => "tournoi_rencontre_equipe.id_tournoi_match='" . $id_match . "'"
		), "dispatch.php"), text($actifs), SESSION_NESTED)."</b>";

			
		$sql="select tre.id_tournoi_equipe, tre.score, tre.remarque ,te.numero_d_equipe, te.nom_d_equipe from tournoi_rencontre_equipe tre, tournoi_equipe te
				where  tre.id_tournoi_match = ".$id_match."
						and  te.id=tre.id_tournoi_equipe";
		$row = $db->getrows($sql);
		for ($i = 0; $i < count($row); $i++) {
			$id_equipe=($row[$i]["id_tournoi_equipe"]);
			$descripteur.=$this->descripteur_tournoi_equipe_participants($id_equipe, 'o');
			$href=atkHref(dispatch_url("tournoi.tournoi_rencontre_equipe", "edit",
					array ("atkselector" => "tournoi_rencontre_equipe.id_tournoi_match='" . $id_match . "' and tournoi_rencontre_equipe.id_tournoi_equipe='".$id_equipe. "'",

					)),
					"</br>Score : <b>",SESSION_NESTED, false, 'target="main"') ;
			$descripteur.=$href.($row[$i]["score"])."</b>" ;
			(!empty($row[$i]["remarque"])) ? $descripteur.="</br>Remarque : <b>".($row[$i]["remarque"])."</b>" : null;
		}

		return $descripteur;
	}
	function table_operations ($nodename,$tablebase, $id_entity, $target="main")
	{
		$target=' target="'.$target.'" ';
		$nodename=atktext($nodename);
		if ($id_entity>0)
		{
			$href="".href(dispatch_url($nodename, "edit", array ("atkselector" => "$tablebase.id='" . $id_entity."'" ),"dispatch.php"),
					'<img class="recordlist" style="border-style:solid;border-width:3px 0px;border-color:transparent;" src="./themes/assocope/icons/assocope/table-edit-icon.png"
					alt="Modification" title="Modification : '.$nodename.'" ></img>',SESSION_NESTED, null,$target);
			$href.=href(dispatch_url($nodename, "admin", array ("atkfilter" => "$tablebase.id='" . $id_entity."'" ,
					"compact"=>"actif"),"dispatch.php"),
					'<img class="recordlist" style="border-style:solid;border-width:3px 0px;border-color:transparent;" src="./themes/assocope/icons/assocope/table-icon.png"
					alt="Administration" title="Administration/Recherche : '.$nodename.'" ></img>',SESSION_NESTED, null,$target);
			$href.=href(dispatch_url($nodename, "delete", array ("atkselector" => "$tablebase.id='" . $id_entity."'" ),"dispatch.php"),
					'<img class="recordlist" style="border-style:solid;border-width:3px 0px;border-color:transparent;" src="./themes/assocope/icons/assocope/table-delete-icon.png"
					alt="Suppression" title="Suppression : '.$nodename.'" ></img>',SESSION_NESTED, null,$target);
		}
		$href.=href(dispatch_url($nodename, "add",array(),"dispatch.php"),
				'<img class="recordlist" style="border-style:solid;border-width:3px 0px;border-color:transparent;" src="./themes/assocope/icons/assocope/table-add-icon.png"
				alt="Création" title="Création : '.$nodename.'" ></img>',SESSION_NESTED, null,$target);
		return $href;
	}
	function descripteur_tournoi_rencontre_equipe($id_rencontre_equipe, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select tre.id_tournoi_equipe, tre.score, tre.remarque from tournoi_rencontre_equipe tre
				where  tre.id = ".$id_rencontre_equipe."";
		$data = $db->getrows($sql);
		$id_equipe=($data[0]["id_tournoi_equipe"]);
		$descripteur=$this->descripteur_tournoi_equipe_participants($id_equipe, 'o');
		$descripteur.="</br>Score : <b>".($data[0]["score"])."</b>" ;
		(!empty($data[0]["remarque"])) ? $descripteur.="</br>Remarque : <b>".($data[0]["remarque"])."</b>" : null;
		return $descripteur;
	}

	function descripteur_tournoi_listes_web($tournoi_id, $upload_dir, $aide_o_n='o')
	{
		$liste_equipes=$upload_dir."organisme_tournoi_".$tournoi_id.'_equipes.html';
		$liste_equipes_et_adresses=$upload_dir."organisme_tournoi_".$tournoi_id.'_equipes_et_adresses.html';
		$liste_rencontres=$upload_dir."organisme_tournoi_".$tournoi_id.'_rencontres.html';
		$liste_rencontres_par_equipe=$upload_dir."organisme_tournoi_".$tournoi_id.'_rencontres_par_equipe.html';
		$descripteur.='<a href="'.$liste_equipes.'" target="_blank" >Equipes</a><br/>';
		$descripteur.='<a href="'.$liste_equipes_et_adresses.'" target="_blank" >Equipes avec coordonnées</a><br/>';
		$descripteur.='<a href="'.$liste_rencontres.'" target="_blank" >Rencontres</a><br/>';
		$descripteur.='<a href="'.$liste_rencontres_par_equipe.'" target="_blank" >Rencontres par equipe</a><br/>';
		($aide_o_n=='o') ? $descripteur.=$this->descripteur_aide('Descripteur_listes_web','n') : $descripteur.="";
			
		return $descripteur;
	}

	function descripteur_rencontre($id_rencontre, $aide_o_n='o',$long_o_n='o', $icones_table_o_n="n")
	{
		$db = & atkGetDb();
		$sql="select ore.id, ore.libelle, o.nom as organisme, o.id as id_organisme, tr.libelle as type_rencontre, date_debut, heure_debut, date_fin, heure_fin, id_lieu_rencontre, lieu_texte, montant_participation_adherent,
		montant_participation_accompagnant, ore.id_organisme_parcours as parcours,
		ore.libelle_participation_1,
		ore.libelle_participation_2,
		ore.libelle_participation_3,
		ore.libelle_participation_4
		
		from organisme_rencontre ore, organisme o, type_rencontre tr
		where ore.id=$id_rencontre
		and ore.id_organisme=o.id
		and ore.id_type_rencontre=tr.id";
		$data = $db->getrows($sql);
		$libelle_participation_1=$data[0]["libelle_participation_1"];
		$libelle_participation_2=$data[0]["libelle_participation_2"];
		$libelle_participation_3=$data[0]["libelle_participation_3"];
		$libelle_participation_4=$data[0]["libelle_participation_4"];
		$sql="select count(id) as inscrits, sum(participation_complete) as nombre,
		 sum(participation_partielle) as nombre_partiel,
		 sum(participation_3) as nombre_3,
		 sum(participation_4) as nombre_4,
		  sum(intervenant_o_n) as nombre_intervenants,
		sum(montant_versement) as montant_versement , sum(montant_versement_2) as montant_versement_2,
		sum( covoiturage_places_offertes) as covoiturage_places_offertes ,
		sum(covoiturage_places_demandees) as covoiturage_places_demandees
		from individu_rencontre
	 where id_rencontre =$id_rencontre";
		$data1 = $db->getrows($sql);
		$covoiturage_places_offertes=$data1[0]["covoiturage_places_offertes"];
		$covoiturage_places_demandees=$data1[0]["covoiturage_places_demandees"];
		$nombre_intervenants=$data1[0]["nombre_intervenants"];
		($nombre_intervenants>0) ? null : $nombre_intervenants=0;
		$nombre_inscrits=$data1[0]["inscrits"];
		($nombre_inscrits>0) ? null : $nombre_inscrits=0;
		$nombre_participants=$data1[0]["nombre"];
		($nombre_participants>0) ? null : $nombre_participants=0 ;
		$nombre_participants_partiels=$data1[0]["nombre_partiel"];
		($nombre_participants_partiels>0) ? null : $nombre_participants_partiels=0 ;
		$nombre_participants_3=$data1[0]["nombre_3"];
		($nombre_participants_3>0) ? null : $nombre_participants_3=0 ;
		$nombre_participants_4=$data1[0]["nombre_4"];
		($nombre_participants_4>0) ? null : $nombre_participants_4=0 ;
		$total_montant_versement=$data1[0]["montant_versement"];
		$total_montant_versement_2=$data1[0]["montant_versement_2"];
		$sql="select count(id) as joueurs from individu_carte_golf
	 where id_rencontre =$id_rencontre";
		$data2 = $db->getrows($sql);
		$nombre_joueurs=$data2[0]["joueurs"];
//
		$href_rencontre=href(dispatch_url("organisme.rencontre", "edit", array (
				'atkfilter' => "organisme_rencontre.id=$id_rencontre"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED, false, ' target="main"');
		
		$href_intervenants=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and intervenant_o_n>0 "
		), "dispatch.php"), $nombre_intervenants, SESSION_NESTED);
		$href_participants=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and participation_complete>0 "
		), "dispatch.php"), $nombre_participants, SESSION_NESTED);
		$href_participants_partiels=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and participation_partielle>0"
		), "dispatch.php"),$nombre_participants_partiels, SESSION_NESTED);
		$href_participants_3=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and participation_3>0"
		), "dispatch.php"),$nombre_participants_3, SESSION_NESTED);
		$href_participants_4=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and participation_4>0"
		), "dispatch.php"),$nombre_participants_4, SESSION_NESTED);
		
		$href_inscrits=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre "
		), "dispatch.php"), $nombre_inscrits, SESSION_NESTED);
		$href_montant_versement=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and montant_versement>0"
		), "dispatch.php"),'<font style="font-size:18px;">'.$total_montant_versement.'</font>', SESSION_NESTED);
		$href_montant_versement_2=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and montant_versement_2>0"
		), "dispatch.php"),'<font style="font-size:18px;">'.$total_montant_versement_2.'</font>', SESSION_NESTED);
		$href_joueurs=href(dispatch_url("individu.carte_golf", "admin", array (
				'atkfilter' => "individu_carte_golf.id_rencontre=$id_rencontre "
		), "dispatch.php"), $nombre_joueurs, SESSION_NESTED);


		$sql="select count(id) as nombre from individu_rencontre
	 where id_rencontre =$id_rencontre and intervenant_o_n='1' ";
		$data1 = $db->getrows($sql);
		$nombre_intervenants=$data1[0]["nombre"];
		$href_intervenants=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => "individu_rencontre.id_rencontre=$id_rencontre and individu_rencontre.intervenant_o_n='1'"
		), "dispatch.php"), $nombre_intervenants, SESSION_NESTED);
		$href_liste_participants=href(dispatch_url("organisme.rencontre", "liste_participants", array(
				"atkselector" => "organisme_rencontre.id=$id_rencontre" ), "dispatch.php"),'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/rencontre.png" alt="Tableau des participants" title="Tableau des participants" target="_blank"></img>',SESSION_NESTED)." ";

		($icones_table_o_n=='o') ? $tablemodifiers=$this->table_operations("organisme.rencontre","organisme_rencontre",$id_rencontre ) : $tablemodifiers="";
		(!empty($data[0]["libelle"])) ? $retour=$href_liste_participants.
		'<b>'.$href_rencontre.' '.$tablemodifiers.'</b><br />' : $retour="" ;
//		'<b>'.$data[0]["libelle"].' '.$tablemodifiers.'</b><br />' : $retour="" ;
		
		(!empty($data[0]["type_rencontre"])) ? $retour.=" (".$data[0]["type_rencontre"].")<br />" : $retour.="" ;
		//		$href=dispatch_url("organisme.organisme", "edit", array ("atkselector" => "organisme.id='" . $data[0]["id_organisme"] . "'"));
		(!empty($data[0]["organisme"])) ? $retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />" : $retour.="" ;
		if ($long_o_n=='o')
		{
			(!empty($data[0]["date_debut"])) ? $retour.="</b>Du <b>".$data[0]["date_debut"]."</b> à <b>".$data[0]["heure_debut"]."<br />" : $retour.="" ;
			(!empty($data[0]["date_fin"])) ? $retour.="</b>Au <b>".$data[0]["date_fin"]."</b> à <b>".$data[0]["heure_fin"]."<br />" : $retour.="" ;
			(!empty($data[0]["id_lieu_rencontre"])) ? $retour.=$this->descripteur_lieu_rencontre($data[0]["id"],'n','n')."<br />" : $retour.="" ;
			(!empty($data[0]["montant_participation_adherent"])) ? $retour.="</b>Tarif adhérent / accompagnant : <b>".$data[0]["montant_participation_adherent"]." / ".$data[0]["montant_participation_accompagnant"]."<br />" : $retour.="" ;
			$retour.='<b>'.$href_inscrits.'</b></b> Participants dont <b>'.$href_intervenants.'</b></b> Intervenants<br/>';

	
		$sql="select
		count(ire.id_individu) as nombre_individus,
		trp.libelle as libelle_rencontre_participation,
		ire.id_type_rencontre_participation as id_type_rencontre_participation
		from type_rencontre_participation trp
		LEFT JOIN individu_rencontre ire ON trp.id=ire.id_type_rencontre_participation
		where ire.id_rencontre=$id_rencontre
		
		GROUP BY trp.id
		ORDER BY trp.libelle
		";
		$data3 = $db->getrows($sql);
		for ($i=0;$i<count($data3);$i++)
		{
			$lien="";
			$lien=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.id_type_rencontre_participation=".$data3[$i]["id_type_rencontre_participation"]
				), "dispatch.php"), $data3[$i]["nombre_individus"] , SESSION_NESTED,null,' title="'.$data3[$i]["libelle_rencontre_participation"].'"');
				$res2.='<b>'.$lien." (".$data3[$i]["libelle_rencontre_participation"].")</b>, ";
		}
		
			$retour.='</b>Participation : <b>';
			$res2=substr($res2, 0, strlen($res2)-2)."<br/>";
			$retour.=$res2.'</b>';
			
			$retour.='</b>Options : ';
			(!empty($libelle_participation_1)) ? $retour.='<b>'.$href_participants_partiels.' ('.$libelle_participation_1."), " : null;
			(!empty($libelle_participation_2)) ? $retour.='<b>'.$href_participants.' ('.$libelle_participation_2."), ": null;
			(!empty($libelle_participation_3)) ? $retour.='<b>'.$href_participants_3.' ('.$libelle_participation_3."), ": null;
			(!empty($libelle_participation_4)) ? $retour.='<b>'.$href_participants_4.' ('.$libelle_participation_4."), ": null;
			$retour=substr($retour, 0, strlen($retour)-2)."<br/>";
			
			if ($data[0]["parcours"]>0)
			{
				$parcoursnode = &atkGetNode("organisme.golf_parcours");
				$records = $parcoursnode->selectDb("organisme_golf_parcours.id=".$data[0]["parcours"]);
				$retour.="</b>Parcours : <b>".$parcoursnode->descriptor($records[0],"n","n").'</b>'.'<br />';
				$retour.='</b>Joueurs : <b>'.$href_joueurs.'</b>'.'<br />' ;
			}

			if ($total_montant_versement>0 || $total_montant_versement_2>0 )
			{
				$retour.='</b></b>Versements (premier/second): <b>';
				($total_montant_versement>0 ) ? $retour.=$href_montant_versement.'</b>' : $retour.='<b>0</b>';
				($total_montant_versement_2>0 ) ? $retour.=' | '.$href_montant_versement_2.'</b>' : $retour.='<b>/0</b>';
				$retour.='<br />';
			}
			($covoiturage_places_offertes>0 || $covoiturage_places_demandees>0 ) ?
			$retour.="Covoiturage : <b>".$covoiturage_places_offertes."/".$covoiturage_places_demandees. "</b> (places offertes/demandées)<br />" : $retour.="" ;
		}

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_rencontre','n') : $retour.="";
		return $retour;
	}
	function descripteur_log($id_log, $aide_o_n='o')
	{
		$db = & atkGetDb();
		// `user_agent`,
		//  `accept_language`,
		// `referer`,
		// `query_string`,
		// `error_message` ,
		//  `parametres`,
		$sql="select
		`userid`,
		`stamp`,
		`origine` ,
		`node`,
		`action`,
		`dispatch_ms_time`,
		`dispatch_ms_elapsed_time`,
		`html_page_output_ms_time`,
		`html_page_output_size`,
		`query_count`,
		`selector`,
		`user_agent`,
		`accept_language`,
		`referer`,
		`host`,
		`remote_address`,
		error_message,
		query_string,
		parametres,
		au.id_individu as id_individu
		from atkeventlog l,app_utilisateur au
		where l.id=$id_log AND l.userid=au.id
		";
		$data = $db->getrows($sql);
		$individu=	$this->descripteur_individu($data[0]["id_individu"],'n','n', null, "log","n");
		$descripteur.="<b>" . $individu . " (" . $data[0]["stamp"].')</b>'.'';
		$descripteur.="<br/></b> Origine / Node / Action : <b>".$data[0]["origine"]." / ".$data[0]["node"]." / ".$data[0]["action"];
		($data[0]["selector"]!="") ? $descripteur.="<br/></b> Selector : <b>".$data[0]["selector"] : $descripteur.="";
		($data[0]["query_count"]!="") ? $descripteur.="<br/></b> Elapsed / Process / Output / Queries / Size : <b>".$data[0]["dispatch_ms_elapsed_time"]." / ".$data[0]["dispatch_ms_time"]." / ".$data[0]["html_page_output_ms_time"]
		." / ".$data[0]["query_count"]." / ".$data[0]["html_page_output_size"] : $descripteur.="";
		$descripteur.="<br/></b> Host / Remote / Referer : <b>".$data[0]["host"]." / "
				.'<a href="http://geomaplookup.net/?ip='.$data[0]["remote_address"].'"  target="_blank" >'.$data[0]["remote_address"]."</a> / ".$data[0]["referer"];
		if (!empty($data[0]["query_string"]) || !empty($data[0]["parametres"]) || !empty($data[0]["error_message"]))
		{
			$descripteur.="<br/></b> Query / Paramètres / Erreur : <b>";
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=query_string','Requête sql',650,650,'yes','no');
			(!empty($data[0]["query_string"])) ? $descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Query string"
					title="Query string" ></img></a>('.strlen($data[0]["query_string"]).') / ' : $descripteur.=' / ';
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=parametres','Paramètres',650,650,'yes','no');
			(!empty($data[0]["parametres"])) ? $descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Paramètres"
					title="Paramètres" ></img></a>('.strlen($data[0]["parametres"]).') / ' : $descripteur.=' / ';
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=error_message','Error message',650,650,'yes','no');
			(!empty($data[0]["error_message"])) ? $descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Error message"
					title="Error message" ></img></a>('.strlen($data[0]["error_message"]).')'  : $descripteur.='';

		}
		$descripteur.="<br/></b> Language / User_agent : <b>".$data[0]["accept_language"]." / ".$data[0]["user_agent"];
		($aide_o_n=='o') ? $descripteur.="<br/>".$this->descripteur_aide('Descripteur_log','n') : $descripteur.="";
		return $descripteur;
			
	}
	function descripteur_rencontre_documents($id_rencontre, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		ta.libelle as libelle_audience,
		ore.audience,
		ore.id_document_inscription,
		ore.id_document_programme,
		ore.programme,
		ore.id_document_preparation,
		ore.preparation,
		ore.id_document_communication,
		ore.communique_presse,
		ore.id_compte_rendu,
		ore.conclusion,
		ore.url_inscription,
		ore.url_programme,
		ore.url_preparation,
		ore.url_communication,
		ore.url_compte_rendu,
		id_document_emargement
		from organisme_rencontre ore
		LEFT JOIN type_audience ta ON ore.id_type_audience=ta.id
		where ore.id=$id_rencontre
		";
		$data = $db->getrows($sql);
//		(strlen($data[0]["preparation"])>0 || ($data[0]["id_document_preparation"])>0) ? $retour='Préparation : ' : $retour='';
		$retour='</b>Préparation : <b>';
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre&id='.$id_rencontre.'&field=preparation','Préparation',650,650,'yes','no');
		(strlen($data[0]["preparation"])>0 ) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Préparation"
				title="Préparation" ></img></a>' : $retour.='';
//		(($data[0]["id_document_preparation"])>0) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_preparation"],'n').'' : $retour.="" ;
		(($data[0]["id_document_preparation"])>0) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_preparation"]).'' : $retour.="" ;
		(($data[0]["url_preparation"])!="") ? $retour.=' '.$this->affiche_url($data[0]["url_preparation"]).'' : $retour.="" ;
//		(strlen($data[0]["preparation"])>0|| ($data[0]["id_document_preparation"])>0) ? $retour.='<br />' : $retour.='';

//		(!empty($data[0]["libelle_audience"]) || !empty($data[0]["audience"])) ? $retour.='Audience : ' : $retour.='';
		$retour.='</b><br/>Audience : <b>';
		(!empty($data[0]["libelle_audience"])) ? $retour.='('.$data[0]["libelle_audience"].')' : $retour.="" ;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre&id='.$id_rencontre.'&field=audience','Audience',650,650,'yes','no');
		(!empty($data[0]["audience"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Audience"
				title="Audience" ></img> </a>' : $retour.='';
//		(!empty($data[0]["libelle_audience"]) || !empty($data[0]["audience"])) ? $retour.='<br />' : $retour.='';

//		(!empty($data[0]["programme"]) || !empty($data[0]["id_document_programme"])) ? $retour.='Programme : ' : $retour.='';
		$retour.='</b><br/>Programme : <b>';
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre&id='.$id_rencontre.'&field=programme','Programme',650,650,'yes','no');
		(!empty($data[0]["programme"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Programme"
				title="Programme" ></img></a>' : $retour.='';
//		(!empty($data[0]["id_document_programme"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_programme"],'n').'' : $retour.="" ;
		(!empty($data[0]["id_document_programme"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_programme"]).'' : $retour.="" ;
		(($data[0]["url_programme"])!="") ? $retour.=' '.$this->affiche_url($data[0]["url_programme"]).'' : $retour.="" ;
//		(!empty($data[0]["programme"]) || !empty($data[0]["id_document_programme"])) ? $retour.='<br />' : $retour.='';
		$retour.='</b><br/>Inscription : <b>';
//		(!empty($data[0]["id_document_inscription"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_inscription"],'n') : $retour.="" ;
		(!empty($data[0]["id_document_inscription"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_inscription"]) : $retour.="" ;
		(($data[0]["url_inscription"])!="") ? $retour.=' '.$this->affiche_url($data[0]["url_inscription"]).'' : $retour.="" ;
		$retour.='</b><br/>Communique de presse : <b>';
//		(!empty($data[0]["communique_presse"]) || !empty($data[0]["id_document_communication"])) ? $retour.='Communiqué : ' : $retour.='';
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre&id='.$id_rencontre.'&field=communique_presse','Communication',650,650,'yes','no');
		(!empty($data[0]["communique_presse"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Communiqué de presse"
				title="Communiqué de presse" ></img></a>' : $retour.='';
//		(!empty($data[0]["id_document_communication"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_communication"],'n').'' : $retour.="" ;
		(!empty($data[0]["id_document_communication"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_communication"]).'' : $retour.="" ;
		(($data[0]["url_communication"])!="") ? $retour.=' '.$this->affiche_url($data[0]["url_communication"]).'' : $retour.="" ;
//		(!empty($data[0]["communique_presse"]) || !empty($data[0]["id_document_communication"])) ? $retour.='<br />' : $retour.='';
		$retour.='</b><br/>Compte rendu : <b>';
//		(!empty($data[0]["conclusion"]) || !empty($data[0]["id_compte_rendu"])) ? $retour.='Compte rendu : ' : $retour.='';
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre&id='.$id_rencontre.'&field=conclusion','Conclusion',650,650,'yes','no');
		(!empty($data[0]["conclusion"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Conclusion"
				title="Conclusion" ></img></a> ' : $retour.='';
//		(!empty($data[0]["id_compte_rendu"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_compte_rendu"],'n').'' : $retour.="" ;
		(!empty($data[0]["id_compte_rendu"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_compte_rendu"]).'' : $retour.="" ;
		(($data[0]["url_compte_rendu"])!="") ? $retour.=' '.$this->affiche_url($data[0]["url_compte_rendu"]).'' : $retour.="" ;
//		(!empty($data[0]["conclusion"]) || !empty($data[0]["id_compte_rendu"])) ? $retour.='<br />' : $retour.='';
		$retour.='</b><br/>Emargement : <b>';
//		(!empty($data[0]["id_document_emargement"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_emargement"],'n').'<br />' : $retour.="" ;
		(!empty($data[0]["id_document_emargement"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_emargement"]).'<br />' : $retour.="" ;

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_rencontre_documents','n') : $retour.="";
		return $retour;
	}
	function descripteur_rencontre_participation($id_rencontre)
	{
		$db = & atkGetDb();
		$sql="SELECT libelle_participation_1,
				libelle_participation_2,
				libelle_participation_3,
				libelle_participation_4
				FROM organisme_rencontre 
								WHERE  id=$id_rencontre";
		$data = $db->getrows($sql);
		$libelle_participation_1=$data[0]["libelle_participation_1"];
		$libelle_participation_2=$data[0]["libelle_participation_2"];
		$libelle_participation_3=$data[0]["libelle_participation_3"];
		$libelle_participation_4=$data[0]["libelle_participation_4"];
		$sql="select
		count(id_individu) as nombre_individus,
		SUM(participation_partielle) as nombre_participation_1,
		SUM(participation_complete) as nombre_participation_2,
		SUM(participation_3) as nombre_participation_3,
		SUM(participation_4) as nombre_participation_4,
		SUM(intervenant_o_n) as nombre_intervenants,
		SUM(montant_versement) as montant_versement_total,
		SUM(montant_versement_2) as montant_versement_2_total
		from individu_rencontre ire
		where ire.id_rencontre=$id_rencontre
		";
		$data1 = $db->getrows($sql);
		$sql="select count(id) as nombre from individu_rencontre
		where id_rencontre =$id_rencontre and intervenant_o_n='1' ";
		$data2 = $db->getrows($sql);
		$nombre_intervenants=$data2[0]["nombre"];
		$lien_individus="";
		$lien_participation_complete="";
		$lien_participation_partielle="";
		$lien_intervenants="";
		$lien_montant_versement_total="";
		$lien_montant_versement_2_total="";
		
		$lien_individus=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre
				 "	), "dispatch.php"), $data1[0]["nombre_individus"] , SESSION_NESTED,null,' title="Nombres de rencontres"');
		($data1[0]["nombre_participation_1"]>0) ? null:$data1[0]["nombre_participation_1"]=0;
		($data1[0]["nombre_participation_2"]>0) ? null:$data1[0]["nombre_participation_2"]=0;
		($data1[0]["nombre_participation_3"]>0) ? null:$data1[0]["nombre_participation_3"]=0;
		($data1[0]["nombre_participation_4"]>0) ? null:$data1[0]["nombre_participation_4"]=0;
		$lien_participation_1=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.participation_partielle>0
				"	), "dispatch.php"), $data1[0]["nombre_participation_1"] , SESSION_NESTED,null," title=$libelle_participation_1");
		$lien_participation_2=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.participation_complete>0
				"	), "dispatch.php"), $data1[0]["nombre_participation_2"] , SESSION_NESTED,null," title=$libelle_participation_2 ");
		$lien_participation_3=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.participation_3>0
				"	), "dispatch.php"), $data1[0]["nombre_participation_3"] , SESSION_NESTED,null," title=$libelle_participation_3");
		$lien_participation_4=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.participation_4>0
				"	), "dispatch.php"), $data1[0]["nombre_participation_4"] , SESSION_NESTED,null," title=$libelle_participation_4");
		$lien_intervenants=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.intervenant_o_n='1'
				"	), "dispatch.php"), $nombre_intervenants , SESSION_NESTED,null,' title="Intervenants"');
		$lien_montant_versement_total=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.montant_versement>0
				"	), "dispatch.php"), "<font style=\"font-size:18px;\">".$data1[0]["montant_versement_total"]."</font>" , SESSION_NESTED,null,' title="Total montant versement 1"');
		$lien_montant_versement_2_total=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.montant_versement_2>0
				"	), "dispatch.php"), "<font style=\"font-size:18px;\">".$data1[0]["montant_versement_2_total"]."</font>" , SESSION_NESTED,null,' title="Total montant versement 2"');
		
		$res2.="</b>Individus : <b>".$lien_individus."</b><br/>";
		$res2.="</b>Options : <b>";
		(!empty($libelle_participation_1)) ? $res2.="<b>".$lien_participation_1." (".$libelle_participation_1.")</b>, " : null;
		(!empty($libelle_participation_2)) ? $res2.="<b>".$lien_participation_2." (".$libelle_participation_2.")</b>, " : null;
		(!empty($libelle_participation_3)) ? $res2.="<b>".$lien_participation_3." (".$libelle_participation_3.")</b>, " : null;
		(!empty($libelle_participation_4)) ? $res2.="<b>".$lien_participation_4." (".$libelle_participation_4.")</b>, " : null;
		$res2=substr($res2, 0, strlen($res2)-2)."<br/>";
		$res2.="</b>Intervenants : <b>".$lien_intervenants."<br/>";
		
		$sql="select
		count(ire.id_individu) as nombre_individus,
		trp.libelle as libelle_rencontre_participation,
		ire.id_type_rencontre_participation as id_type_rencontre_participation
		from type_rencontre_participation trp
		LEFT JOIN individu_rencontre ire ON trp.id=ire.id_type_rencontre_participation
		where ire.id_rencontre=$id_rencontre
		
		GROUP BY trp.id
		ORDER BY trp.libelle
		";
		$res2.="</b>Participation : <b>";
		$data2 = $db->getrows($sql);
		for ($i=0;$i<count($data2);$i++)
		{
			$lien="";
			$lien=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
				'atkfilter' => " individu_rencontre.id_rencontre = $id_rencontre AND individu_rencontre.id_type_rencontre_participation=".$data2[$i]["id_type_rencontre_participation"]
				), "dispatch.php"), $data2[$i]["nombre_individus"] , SESSION_NESTED,null,' title="'.$data2[$i]["libelle_rencontre_participation"].'"');
				$res2.='<b>'.$lien." <b>(".$data2[$i]["libelle_rencontre_participation"].")</b>, ";
		}
		$res2=substr($res2, 0, strlen($res2)-2);
		$res2.="</b><br/></b> Versements 1 : <b><font style=\"font-size:18px;\">".$lien_montant_versement_total."</font>";
		$res2.="</b><br/></b> Versements 2 : <b><font style=\"font-size:18px;\">".$lien_montant_versement_2_total."</font>";
		
		return $res2;
	}
	
	function descripteur_rencontre_balance_carree($id_rencontre)
	{
	
		$db = & atkGetDb();
		$descripteur_rencontre=$res.=$this->descripteur_rencontre($id_rencontre,'n','n')."<br />";
		// Créer la ligne titre border:1px solid red;
		$retour_debut="<style> .alnright { text-align: right; }</style>
				<style> .alncenter{ text-align: center; }</style>
				<style> td {
 border-width:1px;
 border-style:solid;
 border-color:black;
	
 }</style><table class=\"toc  sortable\">";
				$retour="<tr><td><b>#</td><td><b>Nom</td>";
		$sql="SELECT orc.libelle, orc.cout
		from organisme_rencontre_choix orc
		where orc.id_rencontre=$id_rencontre
		order by orc.id" ;
		$data=$db->getrows($sql);
		for ($i=0;$i<count($data);$i++)
		{
		$cout=number_format($data[$i]["cout"],0,",",".");
		$retour.="<td  class='alncenter'><b>".$data[$i]["libelle"]."<br/>".$cout." Euro</td>";
		}
		$retour.="<td class='alncenter'><b>Total des prestations</td><td class='alncenter'><b>Total des règlements</td><td><b>Solde</td>";
		$retour.="</tr>";
		$sql="SELECT i.id, i.nom, i.prenom
		from individu i
		where i.id in
		(select id_individu from individu_rencontre where id_rencontre=$id_rencontre )
		order by i.nom, i.prenom
		" ;
		$data_individu=$db->getrows($sql);
		$retour.="<tr>";
		$ligne_bas=$retour;
		$retour=$descripteur_rencontre.$retour_debut.$retour;
			$total_choix=array();
			$total_choix_nombre=array();
			$total_total_prestations_individu=0;
			$total_solde_individu=0;
			$total_versements_individu=0;
			for ($i=0;$i<count($data_individu);$i++)
			{
			$nom= $data_individu[$i]["nom"].' '.$data_individu[$i]["prenom"];
			$retour.="<td><b>".($i+1)."</td><td><b>".$nom."</td>";
			$id_individu=$data_individu[$i]["id"];
			$sql="SELECT
			orc.id, orc.cout, irc.quantite
			from organisme_rencontre_choix orc LEFT JOIN  individu_rencontre_choix irc  ON orc.id=irc.id_organisme_rencontre_choix , individu_rencontre ir
			where
			ir.id_rencontre=$id_rencontre and
			ir.id_individu=$id_individu and
			ir.id=irc.id_individu_rencontre
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
			($quantite==0)? $retour.="<td></td>" : $retour.="<td class='alncenter' >".$total_choix_individu." (".$quantite_display.")"."</td>";
		//		$retour.="<td>".$total_choix_individu." (".$quantite.")"."</td>";
			$total_prestations_individu+=$total_choix_individu;
			$total_choix[$j]+=$total_choix_individu;
			$total_choix_nombre[$j]+=$quantite;
			}
			$retour.="<td class='alnright'><b>$total_prestations_individu</td>";
			$total_total_prestations_individu+=$total_prestations_individu;
			$sql1="select ir.montant_versement,ir.montant_versement_2
			from individu_rencontre ir
			where ir.id_individu=$id_individu and ir.id_rencontre = $id_rencontre ";
			//$this->p($sql1);
			$data1=$db->getrows($sql1);
			(count($data1)>0 && $data1[0]["montant_versement"]!='')? $montant_versement=$data1[0]["montant_versement"] : $montant_versement=0;
			(count($data1)>0 && $data1[0]["montant_versement_2"]!='')? $montant_versement+=$data1[0]["montant_versement_2"] : null;
		$total_versements_individu+=$montant_versement;
		$solde=$total_prestations_individu-$montant_versement;
			$montant_versement=number_format($montant_versement,0,",",".");
			$retour.="<td class='alnright'><b>$montant_versement</td>";
	
			$total_solde_individu+=$solde;
			$solde=number_format($solde,0,",",".");
			$retour.="<td class='alnright'><b>$solde</td>";
			$retour.="</tr>";
	
			}
			$retour.="<tr><td><b>$i</td><td><b>Total</td>";
			$total_ligne=0;
			for ($k=0;$k<count($total_choix);$k++)
		{
		$retour.="<td class='alncenter'><b>".$total_choix[$k]." (".$total_choix_nombre[$k].")"."</td>";
		$total_ligne+=$total_choix[$k];
			}
					$retour.="<td class='alnright'><b>".$total_ligne." / ".$total_total_prestations_individu."</td>";
		$retour.="<td class='alnright'><b>".$total_versements_individu."</td>";
			$retour.="<td class='alnright'><b>".$total_solde_individu."</td>";
		$retour.="</tr>";
		$retour.=$ligne_bas;
			$retour.="</table>";
	return $retour;
	
	}
	function descripteur_rencontre_renseignements_voyage($id_rencontre)
	{
			$db = & atkGetDb();
		$descripteur_rencontre=$res.=$this->descripteur_rencontre($id_rencontre,'n','n')."<br />";
		// Créer la ligne titre border:1px solid red;
		$retour_debut="<style> .alnright { text-align: right; }</style>
				<style> .alncenter{ text-align: center; }</style>
				<style> td {
 border-width:1px;
 border-style:solid;
 border-color:black;
	
 }</style><table class=\"toc  sortable\">";
				$retour="<tr><td><b>#</td><td><b>Nom</td>";
				$retour.="<td><b>Prénom</td>";
				$retour.="<td><b>Nom-prénom passeport</td>";
				$retour.="<td><b>Date de naissance</td>";
				$retour.="<td><b>Nationalité</td>";
				$retour.="<td><b>Numéro de passeport</td>";
				$retour.="<td><b>Date d'expiration</td>";
				$retour.="<td><b>Numéro de SS</td>";
				$retour.="<td><b>Compte bancaire</td>";
				$retour.="<td><b>Licence de golf</td>";
				$retour.="<td><b>Index de golf</td>";
				
			$retour.="</tr>";
		$sql="SELECT i.id, i.nom, i.prenom, i.date_naissance, i.nationalite,  i.passeport_nom_prenom,i.passeport_numero, i.passeport_date_expiration, i.numero_ss, i.compte_bancaire, i.golf_licence, i.golf_index
		from individu i
		where i.id in
		(select id_individu from individu_rencontre where id_rencontre=$id_rencontre )
		order by i.nom, i.prenom
		" ;
		$data_individu=$db->getrows($sql);
		$retour.="<tr>";
		$ligne_bas=$retour;
		$retour=$descripteur_rencontre.$retour_debut.$retour;
			
			for ($i=0;$i<count($data_individu);$i++)
			{
				$retour.="<td><b>".($i+1)."</td>";
			$retour.="<td>".$data_individu[$i]["nom"]."</td>";
			( $data_individu[$i]["prenom"]!="") ? $retour.="<td>".$data_individu[$i]["prenom"]."</td>" : $retour.="<td><b>????????</td>" ;
			( $data_individu[$i]["passeport_nom_prenom"]!="") ? $retour.="<td>".$data_individu[$i]["passeport_nom_prenom"]."</td>" : $retour.="<td><b>????????</td>" ;
			( $data_individu[$i]["date_naissance"]!="") ? $retour.="<td>".$data_individu[$i]["date_naissance"]."</td>" : $retour.="<td><b>????????</td>" ;
			( $data_individu[$i]["nationalite"]!="") ? $retour.="<td>".$data_individu[$i]["nationalite"]."</td>" : $retour.="<td><b>????????</td>" ;
			( $data_individu[$i]["passeport_numero"]!="") ? $retour.="<td>".$data_individu[$i]["passeport_numero"]."</td>" : $retour.="<td><b>????????</td>" ;
			( $data_individu[$i]["passeport_date_expiration"]!="") ? $retour.="<td>".$data_individu[$i]["passeport_date_expiration"]."</td>" : $retour.="<td><b>????????</td>" ;
			$retour.="<td>".$data_individu[$i]["numero_ss"]."</td>";
			$retour.="<td>".$data_individu[$i]["compte_bancaire"]."</td>";
			$retour.="<td>".$data_individu[$i]["golf_licence"]."</td>";
			$retour.="<td>".$data_individu[$i]["golf_index"]."</td>";
			
		
			$retour.="</tr>";
	
			}
			
		$retour.=$ligne_bas;
			$retour.="</table>";
	return $retour;
	}
	
	
	function descripteur_rencontre_recettes_depenses($id_rencontre)
	{
		$db = & atkGetDb();
		
		$retour="<style>  .alnright { text-align: right; }</style><style>  .alncenter { text-align: center ; }</style><style> td {
 border-width:1px;
 border-style:solid;
 border-color:black;
	
 }</style><table class=\"toc  sortable\" >";
		$retour.="<tr><td class='alncenter'><b>RECETTES</td><td><b></td><td><b></td><td class='alncenter'><b>Prévues</td><td class='alncenter'><b>Réalisées</td><td class='alncenter'><b>Prévues<br/>-<br/>Réalisées</td></tr>";
		$retour.="<tr><td><b>Choix</td><td><b>PU</td><td><b>Nombre</td><td><b>Total</td><td><b></td><td><b></td></tr>";
		$sql="SELECT orc.id, orc.libelle, orc.cout
		from organisme_rencontre_choix orc
		where orc.id_rencontre=$id_rencontre" ;

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
			
			$lien_choix=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
					'atkfilter' => " individu_rencontre.id in (select id_individu_rencontre from individu_rencontre_choix where id_organisme_rencontre_choix=$id_choix   and quantite>0)
					"	), "dispatch.php"), $option["quantite"] , SESSION_NESTED,null," title=\"individus rencontres \"");
			
			
			$retour.="<tr><td>".$this->decoupe_affichage_colonne($option["libelle"], 50)."</td><td class='alnright'>".$option["cout"]."</td><td class='alnright'>".$lien_choix."</td><td class='alnright'>".$total_ligne."</td><td><b></td><td><b></td>";
			$retour.="</tr>";
			
		}
		$total_total_tmp=number_format($total_total,2,",",".");
		
		
		$sql1="select sum(ir.montant_versement) as montant_versement,sum(ir.montant_versement_2) as montant_versement_2
		from individu_rencontre ir
		where ir.id in ( select id from individu_rencontre where id_rencontre=$id_rencontre ) ";
		$data1=$db->getrows($sql1);
		(count($data1)>0 && $data1[0]["montant_versement"]!='')? $montant_versement=$data1[0]["montant_versement"] : $montant=0;
		(count($data1)>0 && $data1[0]["montant_versement_2"]!='')? $montant_versement+=$data1[0]["montant_versement_2"] : null;
		$solde=$total_total-$montant_versement;
		$recettes=$montant_versement;
		$montant_versement=number_format($montant_versement,2,",",".");
		($solde>0)? $texte="A percevoir :" : null;
		($solde<0)? $texte="Trop perçu :" : null;
		($solde==0)? $texte="Equilibré :" : null;
		$solde=number_format($solde,2,",",".");
			$retour.="<tr><td><b></td><td><b></td><td><b></td><td class='alnright'><b>$total_total_tmp</td><td class='alnright'><b>$montant_versement</td><td class='alnright'><b>$solde</td></tr>";
			$sql1="select sum(orf.montant_prevu) as montant_prevu,sum(orf.montant_fourniture) as montant_fourniture
			from organisme_rencontre_fournisseur orf
			where orf.id_rencontre =$id_rencontre  ";
			$data1=$db->getrows($sql1);
			$solde=$data1[0]["montant_fourniture"]-$data1[0]["montant_prevu"];
			$depenses=$data1[0]["montant_fourniture"];
			($solde>0)? $texte="Dépassement :" : null;
			($solde<0)? $texte="Mieux :" : null;
			($solde==0)? $texte="Equilibré :" : null;
			$solde=number_format($solde,2,",",".");
			$retour.="<tr><td class='alncenter'><b>DEPENSES</td><td><b></td><td><b></td><td class='alncenter'><b>Prévues</td><td class='alncenter'><b>Réalisées</td><td class='alncenter'><b>Prévues<br/>-<br/>Réalisées</td></tr>";
			$retour_total="<tr><td><b></td><td><b></td><td><b></td><td class='alnright'><b>".
					number_format($data1[0]["montant_prevu"],2,",",".")
			."</td><td class='alnright'><b>".
			number_format($data1[0]["montant_fourniture"],2,",",".")
		."</td><td class='alnright'><b>".
			$solde."</td></tr>";
			$sql1="select orf.id_organisme_fournisseur, orf.libelle as libelle, orf.montant_prevu as montant_prevu,orf.montant_fourniture as montant_fourniture
			from organisme_rencontre_fournisseur orf
			where orf.id_rencontre =$id_rencontre ";
			$data1=$db->getrows($sql1);
			for ($i=0;$i<count($data1);$i++)
					
			{
			$retour.="<tr><td>".$data1[$i]["libelle"]."<br/>".
				$this->descripteur_organisme($data1[$i]["id_organisme_fournisseur"],'n','n')
									."</td><td></td><td></td><td class='alnright'>".
									number_format($data1[$i]["montant_prevu"],2,",",".")
									."</td><td class='alnright'>".
									number_format($data1[$i]["montant_fourniture"],2,",",".")
								."</td>
				<td class='alnright'>".
				number_format(($data1[$i]["montant_fourniture"] - $data1[$i]["montant_prevu"]),2,",",".")
			."</td></tr>";
			}
			$retour.=$retour_total;				
$solde=$recettes -$depenses; 
$solde=number_format($solde,2,",",".");
$retour.="<tr><td class='alncenter'><b>RECETTES - DEPENSES</td><td><b></td><td><b></td><td><b></td><td class='alnright'><b>".$solde."</td><td><b></td></tr>";

		$retour.="</table>";
	
		return $retour;
				
		}
		
	function descripteur_rencontre_fournisseurs($id_rencontre, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		rf.id,
		rf.libelle,
		rf.id_organisme_fournisseur,
		rf.id_individu,
		rf.id_document_accord,
		rf.description,
		rf.montant_prevu,
		rf.montant_fourniture
		from organisme_rencontre_fournisseur rf

		where rf.id_rencontre=$id_rencontre
		";
		$data = $db->getrows($sql);
		$retour='';
		for ($i = 0; $i < count($data); $i++) {
			($i>0) ? $retour.="<br /><b><i>Fourniture ".($i+1)." : </i></b><br />" : $retour='<b><i>Fourniture '.($i+1)." : </i></b><br />";
			$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shopping-cart-down-icon.png" alt="Fourniture"
				title="Fourniture" ></img> ';
			(!empty($data[$i]["libelle"])) ? $retour.="<b>".href(dispatch_url("organisme.rencontre_fournisseur", "edit", array (	'atkselector' => "organisme_rencontre_fournisseur.id='" . $data[$i]["id"]. "'"
			), "dispatch.php"),$data[$i]["libelle"].'<br />', SESSION_NESTED)."</b>" : $retour.="";
			(!empty($data[$i]["id_organisme_fournisseur"])) ? $retour.=$this->descripteur_organisme($data[$i]["id_organisme_fournisseur"],'n','n')."<br />" : $retour.="" ;
			(!empty($data[$i]["id_individu"])) ? $retour.=$this->descripteur_individu($data[$i]["id_individu"],'n','n').'<br />' : $retour.="" ;
			(!empty($data[$i]["id_document_accord"])) ? $retour.=$this->descripteur_document("organisme",$data[$i]["id_document_accord"],'n').'<br />' : $retour.="" ;
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre_fournisseur&id='.$data[$i]["id"].'&field=description','Description',650,650,'yes','no');
			(!empty($data[$i]["description"])) ? $retour.='</b>Description : <b><a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Description"
					title="Description" ></img></a>'.'<br />' : $retour.='';
			(!empty($data[$i]["montant_prevu"])) ? $retour.='</b>Dépense prévue : <b>'.$data[$i]["montant_prevu"]."" : $retour.="" ;
			(!empty($data[$i]["montant_fourniture"])) ? $retour.='. </b>Dépense effective : <b><font style=\"font-size:18px;\">'.$data[$i]["montant_fourniture"]."</font>" : $retour.="" ;
			(!empty($data[$i]["montant_prevu"]) || !empty($data[$i]["montant_fourniture"]))? $retour.='<br />' : $retour.="" ;
			($data[$i]["montant_fourniture"]) ?	$retour.=$this->descripteur_reglement("rencontre_fournisseur",$data[$i]["id"],'n') : $retour.="";

		}
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_rencontre_fournisseurs','n') : $retour.="";
		return $retour;
	}
	function descripteur_rencontre_fournisseurs_sans_lien($id_rencontre)
	{
		$db = & atkGetDb();
		$sql="select
		rf.id,
		rf.libelle,
		rf.id_organisme_fournisseur,
		rf.id_individu,
		rf.id_document_accord,
		rf.description,
		rf.montant_prevu,
		rf.montant_fourniture
		from organisme_rencontre_fournisseur rf
		where rf.id_rencontre=$id_rencontre
		";
		$data = $db->getrows($sql);
		$retour='';
		for ($i = 0; $i < count($data); $i++) {
		($i>0) ? $retour.="<br /><b><i>Fourniture ".($i+1)." : </i></b><br />" : $retour='<b><i>Fourniture '.($i+1)." : </i></b><br />";
				$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shopping-cart-down-icon.png" alt="Fourniture"
				title="Fourniture" ></img> ';
						(!empty($data[$i]["libelle"])) ? $retour.="<b>".$data[$i]["libelle"]." " : null;
						(!empty($data[$i]["id_organisme_fournisseur"])) ? $retour.=$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_fournisseur"])." " : $retour.="" ;
						(!empty($data[$i]["id_individu"])) ? $retour.=$this->descripteur_individu_sans_lien($data[$i]["id_individu"]).' ' : $retour.="" ;
						$retour.='</b><br/>Dépense prévue : <b>'.$data[$i]["montant_prevu"];
						$retour.="</b>. Devis : <b>".$this->descripteur_document_sans_lien("organisme",$data[$i]["id_document_accord"])  ;
						(!empty($data[$i]["description"])) ? $retour.='<br/></b>Description : <b>'.$data[$i]["description"] : $retour.="";
						($data[$i]["montant_fourniture"]) ?	$retour.="<br/></b><b>".$this->descripteur_reglement("rencontre_fournisseur",$data[$i]["id"],'n') : $retour.="";
	
	}
	
			return $retour;
		}

	function descripteur_rencontre_fournisseur($id_rencontre_fournisseur, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		rf.id,
		rf.libelle,
		ro.id_organisme,
		rf.id_organisme_fournisseur,
		rf.id_individu,
		rf.id_document_accord,
		rf.description,
		rf.montant_prevu,
		rf.montant_fourniture
		from organisme_rencontre_fournisseur rf, organisme_rencontre ro

		where rf.id=$id_rencontre_fournisseur
		and rf.id_rencontre=ro.id
		";
		$data = $db->getrows($sql);
		$retour='';
		$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shopping-cart-down-icon.png" alt="Fourniture"
				title="Fourniture" ></img> ';

		(!empty($data[0]["libelle"])) ? $retour.=href(dispatch_url("organisme.rencontre_fournisseur", "edit", array (	'atkselector' => "organisme_rencontre_fournisseur.id='" . $data[0]["id"]. "'"
		), "dispatch.php"),"<b>".$data[0]["libelle"].'</b><br />', SESSION_NESTED) : $retour.="";
		(!empty($data[0]["id_organisme_fournisseur"])) ? $retour.="</b>Fournisseur : <b>".$this->descripteur_organisme($data[0]["id_organisme_fournisseur"],'n','n')."<br />" : $retour.="" ;
		(!empty($data[0]["id_individu"])) ? $retour.=$this->descripteur_individu($data[0]["id_individu"],'n','n',null,"rencontre_fournisseur",'n').'<br />' : $retour.="" ;
		(!empty($data[0]["id_document_accord"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_accord"],'n').'<br />' : $retour.="" ;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_rencontre_fournisseur&id='.$data[0]["id"].'&field=description','Description',650,650,'yes','no');
		(!empty($data[0]["description"])) ? $retour.='Description : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Description"
				title="Description" ></img></a>'.'<br />' : $retour.='';
		(!empty($data[0]["montant_prevu"])) ? $retour.='</b>Dépense prévue/effective : <b>'.$data[0]["montant_prevu"]."</b>/<b>".$data[0]["montant_fourniture"]."</b>" : $retour.="" ;
	//	(!empty($data[0]["montant_fourniture"])) ? $retour.='</b> Dépense effective : '.$data[0]["montant_fourniture"]."" : $retour.="" ;
		(!empty($data[0]["montant_prevu"]) || !empty($data[0]["montant_fourniture"]))? $retour.='<br />' : $retour.="" ;
		$retour.=$this->descripteur_reglement("rencontre_fournisseur",$data[0]["id"],'n');
		$retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_rencontre_fournisseur','n') : $retour.="";
		return $retour;
	}
	function descripteur_rencontre_choix($id_rencontre_choix, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql1="select sum(quantite) as nombre
		from individu_rencontre_choix
		where 
		id_organisme_rencontre_choix =$id_rencontre_choix  and quantite>0
		";
		$data1 = $db->getrows($sql1);
		$nombre=$data1[0]["nombre"];
		$lien_choix=href(dispatch_url("individu.rencontre_i", "admin", array (
				'atkfilter' => " individu_rencontre.id in (select id_individu_rencontre from individu_rencontre_choix where id_organisme_rencontre_choix=$id_rencontre_choix   and quantite>0)
				"	), "dispatch.php"), $nombre , SESSION_NESTED,null," title=\"individus rencontres \"");
		
		$sql="select
		rc.id,
		rc.libelle,
		rc.cout
				from organisme_rencontre_choix rc
	
		where rc.id=$id_rencontre_choix
				";
		$data = $db->getrows($sql);
		$retour='';
		$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/choix.png" alt="Choix"
		title="Choix" ></img> ';
		$retour.=href(dispatch_url("organisme.rencontre_choix", "edit", array (	'atkselector' => "organisme_rencontre_choix.id='" 
				. $data[0]["id"]. "'"
		), "dispatch.php"),"<b>".$data[0]["libelle"].'</b><br />', SESSION_NESTED) ;
	$retour.='</b>Prix : <b>'.$data[0]["cout"]."</b><br />".
	'</b>Nombre : <b>'.$lien_choix."</b><br />" ;
	
					($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_rencontre_choix','n') : $retour.="";
					return $retour;
	}


	function descripteur_adresse_individu($id_individu, $qr_o_n='n',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT il.id_lieu
				from individu_lieu il
				where il.id_individu=$id_individu and il.adresse_defaut_o_n='1'
				");
		(!empty($data[0]["id_lieu"] )) ? $retour=$this->descripteur_lieu($data[0]["id_lieu"],$qr_o_n,'n') : $retour='';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_adresse_individu','n') : $retour.="";
		return $retour;
	}
	
function descripteur_itineraire_individu($id_individu, $lat="", $long="")
	{
		if ($lat=="" || $long=="")
		{return;}
		
			$db = & atkGetDb();
		
		$data = $db->getrows("SELECT il.id_lieu, l.latitude, l.longitude 
				from individu_lieu il, lieu l
				where il.id_individu=$id_individu and il.id_lieu=l.id and il.adresse_defaut_o_n='1'
				");
		if (!empty($data[0]["id_lieu"] )) 
		{
		$lat_ind=$data[0]["latitude"];
		$long_ind=$data[0]["longitude"];
		$lat_centre=($lat-$lat_ind)+$lat;
		$long_centre=($long-$long_ind)+$long;
		
					$retour='<a href="http://www.google.fr/maps/dir/'.$lat.','.$long.'/'.$data[0]["latitude"].','.$data[0]["longitude"].'/@'.$lat_centre.','.$long_centre.'z/data=!3m1!4b1!4m4!4m3!1m0!1m0!3e0 " target="_blank">'.
					'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/covoiturage.png" alt="Itinéraire depuis ma position"
							title="Itinéraire depuis ma position"  ></img></a>';
		}
		else {
			$retour="";
		}
		return $retour;
	}

	function descripteur_adresse_organisme($id_organisme, $qr_o_n='n',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT il.id_lieu
				from organisme_lieu il
				where il.id_organisme=$id_organisme and il.adresse_defaut_o_n='1'
				");
		(!empty($data[0]["id_lieu"] )) ? $retour=$this->descripteur_lieu($data[0]["id_lieu"],$qr_o_n,'n') : $retour='';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_adresse_organisme','n') : $retour.="";
		return $retour;
	}

	function descripteur_lieu_rencontre($id_rencontre, $qr_o_n='n',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT  lr.id, lr.libelle, lr.id_lieu from organisme_rencontre ore, organisme_lieu_rencontre lr
				where ore.id_lieu_rencontre=lr.id and 	ore.id=$id_rencontre");
		$href=href(dispatch_url("organisme.lieu_rencontre", "edit", array (	'atkselector' => "organisme_lieu_rencontre.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		(!empty($data[0]["libelle"])) ? $retour.='</b>Lieu : <b>'.$href."<br />": $retour.='';
		(!empty($data[0]["id_lieu"])) ? $retour.=$this->descripteur_lieu($data[0]["id_lieu"], 'n','n')." ".$this->descripteur_lieu($data[0]["id_lieu"], 'o','n') : $retour.='';

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_lieu_rencontre','n') : $retour.="";
		return $retour;
	}

	function descripteur_lieu_rencontre_lieu($id_lieu_rencontre,$aide_o_n='o',$abrege_o_n='n')
	{
		$db = & atkGetDb();
		/*
		 *
		*
		*/
		$data = $db->getrows("SELECT olr.id,
				olr.id_organisme,
				olr.id_individu_correspondant,
				olr.libelle,
				olr.id_lieu,
				olr.horaires,
				olr.capacite,
				olr.cout_location,
				olr.telephone,
				olr.wifi,
				olr.sonorisation,
				olr.projection,
				olr.consignes,
				o.nom as nom_organisme
				from organisme_lieu_rencontre olr, organisme o
				where olr.id=$id_lieu_rencontre
				and olr.id_organisme=o.id");
		$href=href(dispatch_url("organisme.lieu_rencontre", "edit", array (	'atkselector' => "organisme_lieu_rencontre.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		($abrege_o_n=='n') ? $retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/lieu_rencontre.png" alt="Lieu de rencontre" title="Lieu de rencontre" target="_blank"></img>'.' <b>'
				.$href."<br />" : $retour=$data[0]["nom_organisme"]."<br />" ;
		(!empty($data[0]["id_lieu"])) ? $retour.=$this->descripteur_lieu($data[0]["id_lieu"], 'n','n')." ".$this->descripteur_lieu($data[0]["id_lieu"], 'o','n')."<br />" : $retour.='';
if ($abrege_o_n=='n')
{	(!empty($data[0]["id_organisme"])) ? $retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />" : $retour.="" ;
		(!empty($data[0]["id_individu_correspondant"])) ? $retour.=$this->descripteur_organisme($data[0]["id_individu_correspondant"],'n','n')."<br />" : $retour.="" ;
		(!empty($data[0]["horaires"])) ? $retour.="</b>Horaires : <b>".$data[0]["horaires"]."<br />" : $retour.='';
		(!empty($data[0]["capacite"])) ? $retour.="</b>Capacité : <b>".$data[0]["capacite"]."<br />" : $retour.='';
		(!empty($data[0]["cout_location"])) ? $retour.="</b>Coût de location : <b>".$data[0]["cout_location"]."<br />" : $retour.='';
		(!empty($data[0]["telephone"])) ? $retour.="</b>Téléphone : <b>".$data[0]["telephone"]."<br />" : $retour.='';
		(!empty($data[0]["wifi"])) ? $retour.="</b>Wifi : <b>".$data[0]["wifi"]."<br />" : $retour.='';
		(!empty($data[0]["sonorisation"])) ? $retour.="</b>Sonorisation : <b>".$data[0]["sonorisation"]."<br />" : $retour.='';
		(!empty($data[0]["projection"])) ? $retour.="</b>Videoprojecteur : <b>".$data[0]["projection"]."<br />" : $retour.='';
		(!empty($data[0]["consignes"])) ? $retour.="</b>Consignes : <b>".filter_var($data[0]["consignes"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';


		$row = $db->getrows("select count(id) as nombre from organisme_contrat
				where id_lieu_rencontre =$id_lieu_rencontre and ( date_echeance is null or date_echeance > CURDATE() or date_resiliation is null or date_resiliation > CURDATE() )	");
		$contrats=$row[0]["nombre"];
		$row = $db->getrows(" select count(id) as nombre  from organisme_rencontre
				where id_lieu_rencontre =$id_lieu_rencontre and ( date_fin > CURDATE()) ");
		$rencontres=$row[0]["nombre"];
		$row = $db->getrows(" select count(id)  as nombre from organisme_groupe_travail
				where id_lieu_rencontre =$id_lieu_rencontre and ( date_fin_groupe is null or date_fin_groupe > CURDATE()) ");
		$groupes=$row[0]["nombre"];
		$retour.= "</b>Contrats : <b>".href(dispatch_url("organisme.contrat", "admin", array (
				'atkfilter' => "organisme_contrat.id_lieu_rencontre='" . $id_lieu_rencontre . "' and ( date_echeance is null or date_echeance > CURDATE() or date_resiliation is null or date_resiliation > CURDATE() )"
		), "dispatch.php"), $contrats, SESSION_NESTED)."<br />";
		$retour.="</b>Rencontres : <b>".href(dispatch_url("organisme.rencontre", "admin", array (
				'atkfilter' => "organisme_rencontre.id_lieu_rencontre='" . $id_lieu_rencontre . "' and date_fin > CURDATE()"
		), "dispatch.php"), $rencontres, SESSION_NESTED)."<br />";
		$retour.="</b>Groupes de travail : <b>".href(dispatch_url("organisme.groupe_travail", "admin", array (
				'atkfilter' => "organisme_groupe_travail.id_lieu_rencontre='" . $id_lieu_rencontre . "' and ( date_fin_groupe is null or date_fin_groupe > CURDATE())"
		), "dispatch.php"), $groupes, SESSION_NESTED)."<br />";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_lieu_rencontre_lieu','n') : $retour.="";
}
		return $retour;
	}


	function descripteur_organisme_lieu_rencontre($id_lieu_rencontre, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT lr.id, lr.id_organisme, lr.libelle, lr.id_lieu from  organisme_lieu_rencontre lr
				where lr.id=$id_lieu_rencontre");
		(!empty($data[0]["id_lieu"])) ? $retour=$this->descripteur_lieu($data[0]["id_lieu"], 'n','n') : $retour.='';
		$href=href(dispatch_url("organisme.lieu_rencontre", "edit", array (	'atkselector' => "organisme_lieu_rencontre.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		(!empty($data[0]["libelle"])) ? $retour.=$href." (".$this->descripteur_organisme($data[0]["id_organisme"],'n','n').")<br />": $retour.='';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_organisme_lieu_rencontre','n') : $retour.="";
		return $retour;
	}
	function descripteur_golf_parcours($id_parcours, $aide_o_n='o')
	{
		$parcoursnode = &atkGetNode("organisme.golf_parcours");

		return $parcoursnode->descriptor($id_parcours,$aide_o_n);
	}


	/*		function descripteur_golf_parcours($id_parcours, $aide_o_n='o')
		{$db = & atkGetDb();
	$data = $db->getrows("SELECT  op.id, op.libelle, op.latitude, op.longitude, op.altitude, op.url_meteo, op.id_organisme,
			op.sss_blanc, op.sss_jaune, op.sss_bleu, op.sss_rouge,
			op.slope_blanc, op.slope_jaune, op.slope_bleu, op.slope_rouge, op.green_fee_haute_saison, op.green_fee_basse_saison
			from organisme_golf_parcours op
			where op.id=$id_parcours");
	$href=href(dispatch_url("organisme.golf_parcours", "edit", array (	'atkselector' => "organisme_golf_parcours.id='" . $data[0]["id"]. "'"
	), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
	$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/golf_tee.png" alt="Parcours"
	title="Parcours"  ></img>'.' <b>'.$href." ";
	if ($data[0]["latitude"]=="")
	{}
	else
	{
	$retour.=' <a href="'.'http://maps.google.com/maps?q='.$data[0]["latitude"].','.$data[0]["longitude"].'&iwloc=A&hl=fr" target="_blank">'.
	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/maps.png" alt="Parcours"
	title="Parcours"  ></img></a>';
	}
	if ($data[0]["url_meteo"]=="")
	{}
	else
	{
	$retour.=' <a href="'.$data[0]["url_meteo"].'" target="_blank">'.
	'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/meteo.png" alt="Météo"
	title="Météo"  ></img></a>';
	}

	if ($data[0]["green_fee_basse_saison"]=="" && $data[0]["green_fee_haute_saison"]=="" )
	{
	$retour.="";
	}
	else {
	$retour.=" Green fee : ";
	($data[0]["green_fee_basse_saison"]!="" ) ? $retour.=$data[0]["green_fee_basse_saison"] : $retour.="";
	($data[0]["green_fee_haute_saison"]!="" ) ? $retour.="/".$data[0]["green_fee_haute_saison"] : $retour.="";
	}
	$retour.="<br />".$this->descripteur_organisme($data[0]["id_organisme"],'n','n',null);

	$this->addStyle("titi.css");
	$parcoursnode = &atkGetNode("organisme.golf_parcours");
	$recs = $parcoursnode->selectDb("organisme_golf_parcours.id='$id_parcours'");
	$nombre_trous=count($recs[0]["trous"]);

	$tableautrous="<table class=\"golfgg\"><tr>";
	$tableautrous.="<tr><td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\">Sss</td>";
	$tableautrous.="<td class=\"golfgg\">Slope</td>";
	$tableautrous.="<td class=\"golfgg\">Aller</td>";
	$tableautrous.="<td class=\"golfgg\">Retour</td>";
	$tableautrous.="<td class=\"golfgg\">A/R</td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: white\"><td class=\"golfgg\">Blanc</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_blanc']."</td>";
	 
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_blanc"])."</td>";       	       }

	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: yellow\"><td class=\"golfgg\">Jaune</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_jaune']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_jaune"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: aqua\"><td class=\"golfgg\">Bleu</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_bleu']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_bleu"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: red\"><td class=\"golfgg\">Rouge</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_rouge']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_rouge"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr><td class=\"golfgg\">Par</td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_aller']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_retour']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_total']."</td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";       	       }

	$tableautrous.="</tr>";
	$tableautrous.="<tr><td class=\"golfgg\">Handicap</td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";       	       }
	$tableautrous.="</tr></table>";
	$retour.=$tableautrous;
	($aide_o_n=='o') ? $retour.=' '.$this->descripteur_aide('Descripteur_golf_parcours','n') : $retour.="";
	return $retour;
	}
	*/
	/*function descripteur_carte_golf($id_carte_golf, $aide_o_n='o')
		{$db = & atkGetDb();
	$data = $db->getrows("SELECT  id, id_individu, id_rencontre, id_organisme_parcours, date_depart, heure_depart,
			trou_depart,
			couleur_depart,
			sss,
			slope,
			distance_aller,
			distance_retour,
			distance_totale,
			id_type_categorie_golf,
			index_avant,
			handicap,
			par,
			score_brut,
			eagle_et_moins,
			birdie,
			pars,
			bogey,
			double_bogey,
			triple_bogey_et_plus,
			stableford,
			ssj,
			net_corrige,
			index_apres
			from individu_carte_golf
			where id=$id_carte_golf");
	//($data[0]["id_rencontre"]!="") ? $retour.=$this->descripteur_rencontre($data[0]["id_rencontre"],'o')."<br/>" : null;

	//		$retour.="<br />".$this->descripteur_organisme($data[0]["id_organisme"],'n','n',null);

	$this->addStyle("titi.css");
	$parcoursnode = &atkGetNode("individu.carte_golf");
	$recs = $parcoursnode->selectDb("individu_carte_golf.id='$id_carte_golf'");
	//      $this->p($recs);
	return true;
	$nombre_trous=count($recs[0]["trous"]);

	$tableautrous="<table class=\"golfgg\"><tr>";
	$tableautrous.="<tr><td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\">Sss</td>";
	$tableautrous.="<td class=\"golfgg\">Slope</td>";
	$tableautrous.="<td class=\"golfgg\">Aller</td>";
	$tableautrous.="<td class=\"golfgg\">Retour</td>";
	$tableautrous.="<td class=\"golfgg\">A/R</td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: white\"><td class=\"golfgg\">Blanc</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_blanc']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_blanc']."</td>";
	 
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_blanc"])."</td>";       	       }

	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: yellow\"><td class=\"golfgg\">Jaune</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_jaune']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_jaune']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_jaune"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: aqua\"><td class=\"golfgg\">Bleu</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_bleu']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_bleu']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_bleu"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr style=\"background: red\"><td class=\"golfgg\">Rouge</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_rouge']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_rouge']."</td>";

	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_rouge"])."</td>";       	       }
	 
	$tableautrous.="</tr>";
	$tableautrous.="<tr><td class=\"golfgg\">Par</td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_aller']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_retour']."</td>";
	$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_total']."</td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";       	       }

	$tableautrous.="</tr>";
	$tableautrous.="<tr><td class=\"golfgg\">Handicap</td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	$tableautrous.="<td class=\"golfgg\"></td>";
	for ($i = 0; $i < $nombre_trous; $i++)
	{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";       	       }
	$tableautrous.="</tr></table>";
	$retour.=$tableautrous;
	($aide_o_n=='o') ? $retour.=' '.$this->descripteur_aide('Descripteur_golf_parcours','n') : $retour.="";
	return $retour;
	}
	*/
	function descripteur_google_photo($id_photo, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT  gp.id, gp.titre, gp.url_thumbnail, gp.url_image, gp.date_prise_de_vue, gp.geo_rss, gp.size , gp.heigth, gp.width,gp.tags,  gp.date_synchronisation_google
				from individu_google_photo gp
				where gp.id=$id_photo");
		$url_thumbnail=$data[0]["url_thumbnail"]; 
		$url_image=$data[0]["url_image"];
		$title=$data[0]["titre"];

		$href=href(dispatch_url("individu.google_photos", "edit", array (	'atkselector' => "individu_google_photo.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["titre"], SESSION_NESTED);
		$hrefpicasa='<a href="'.$url_image.'" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/picasa-icone.png" alt="Album"
				title="Photo Picasa"  ></img></a>';

		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/photo-icone.png" alt="Photo"
				title="Photo"  ></img>'.' <b>'.$href." ".$hrefpicasa;

		$retour.="<br /><a href=\"".$url_image."\" target=\"_blank\" title=\"$title\"><img src=\"" .
		$url_thumbnail . "\"/></a>";
		$hauteur=number_format($data[0]["heigth"],0,"",".");
		$largeur=number_format($data[0]["width"],0,"",".");
		$taille=number_format($data[0]["size"],0,"",".");
		$retour.="<br />Taille (h*w) : ".$hauteur." x ".$largeur." ( ".$taille." )";
		$retour.="<br />Cliché du : ".$data[0]["date_prise_de_vue"];
		$retour.="<br />Localisation : ".$data[0]["geo_rss"];
		$retour.="<br />Tags : ".$data[0]["tags"];
		$retour.="<br />Synchronisée le : ".$data[0]["date_synchronisation_google"];

		($aide_o_n=='o') ? $retour.=' '.$this->descripteur_aide('Descripteur_google_photo','n') : $retour.="";
		return $retour;
	}

	function descripteur_google_feed_album($id_album, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT  gf.id, gf.album, gf.lien_album, gf.date_publication_album, gf.nombre_de_photos, gf.taille_octets, gf.url_google , gf.date_synchronisation_google
				from individu_google_feed gf
				where gf.id=$id_album");
		$href=href(dispatch_url("individu.google_feed", "edit", array (	'atkselector' => "individu_google_feed.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["album"], SESSION_NESTED);
		$hrefpicasa='<a href="'.$data[0]["lien_album"].'" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/picasa-icone.png" alt="Album"
				title="Album Picasa"  ></img></a>';
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/photos_album.png" alt="Album"
				title="Album AssoCope"  ></img>'.' <b>'.$href." ".$hrefpicasa." ";
		/*
		 * http://www.wikistoma.org/association/dispatch.php?atknodetype=individu.google_photos&atkaction=admin&atkfilter=individu_google_photo.id_album%3D5131%20&atklevel=1&atkprevlevel=0&atkstackid=4f490f47b8e2e&
		*/
		$nombre_de_photos=number_format($data[0]["nombre_de_photos"],0,"",".");
		$taille=number_format($data[0]["taille_octets"],0,"",".");
		$href=href(dispatch_url("individu.google_photos", "admin", array (
				'atkfilter' => "individu_google_photo.id_album=$id_album "
		), "dispatch.php"),$nombre_de_photos, SESSION_NESTED,null,' title="Photos AssoCope"');
		$retour.='<br /><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/photo-icone.png" alt="Photo"
				title="Photo"  ></img> Photos : '.$href;
		$retour.="<br />Taille : ".$taille;
		$retour.="<br />Publié le : ".$data[0]["date_publication_album"];
		$retour.="<br />Synchronisé le : ".$data[0]["date_synchronisation_google"];

		($aide_o_n=='o') ? $retour.=' '.$this->descripteur_aide('Descripteur_google_feed_album','n') : $retour.="";
		return $retour;
	}


	function descripteur_lieu_tournoi($id_lieu_rencontre, $qr_o_n='n',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT  lr.libelle, lr.id_lieu , ore.nom from  organisme ore,organisme_lieu_rencontre lr
				where lr.id=$id_lieu_rencontre and lr.id_organisme=ore.id");
		(!empty($data[0]["id_lieu"])) ? $retour=$this->descripteur_lieu($data[0]["id_lieu"], 'n','n') : $retour='';
		(!empty($data[0]["libelle"])) ? $retour.='<b>'.$data[0]["libelle"].' ('.$data[0]["nom"].')</b>': $retour.='';

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_lieu_tournoi','n') : $retour.="";
		return $retour;
	}


	function descripteur_lieu($id_lieu, $qr_o_n='n',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT l.latitude, l.longitude, bus_metro_tram, adresse1, adresse2, code_postal, ville, code_iso, libelle_francais from  lieu l, type_cp_ville_pays cp, type_pays p where l.id='$id_lieu' and l.id_ville=cp.id and cp.id_pays=p.id ");
		if (!empty($data[0]["ville"] ))
		{
			$qr_adresse_organisme=$data[0]["adresse1"];
			$coordonnees=$qr_adresse_organisme;
			(!empty($data[0]["adresse2"])) ? $qr_adresse_organisme.=' , '.$data[0]["adresse2"] : $qr_adresse_organisme.="";
			(!empty($data[0]["adresse2"])) ? $coordonnees.='<br />'.$data[0]["adresse2"] : null;
			$qr_adresse_organisme.= ' , '  . $data[0]["code_postal"] . ' , ' . $data[0]["ville"] . ' , ' . $data[0]["code_iso"];
			$coordonnees.= '<br />'  . $data[0]["code_postal"] . ' ' . $data[0]["ville"] . '<br />' . $data[0]["libelle_francais"];
		}
		else {$adresse_organisme="";
		$qr_adresse_organisme="";
		}
			
		if ($data[0]["latitude"]=="")
		{
		}
		else
		{
			// (!empty($data[0]["adresse1"])) ? $adresse_organisme.=$data[0]["adresse1"].'<br />' : $adresse_organisme.="";
			// (!empty($data[0]["adresse2"])) ? $adresse_organisme.=$data[0]["adresse2"].'<br />' : $adresse_organisme.="";
			// $adresse_organisme.=$data[0]["code_postal"] . ' ' . $data[0]["ville"] . ' (' . $data[0]["code_iso"].')';
			$adresse_organisme.='<a href="'.'http://maps.google.com/maps?q='.$data[0]["latitude"].','.$data[0]["longitude"].'&iwloc=A&hl=fr" target="_blank">'.
					'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/maps.png" alt="Maps : '.$qr_adresse_organisme.'"
							title="Maps : '.$qr_adresse_organisme.'"  ></img></a>';
			$coordonnees.= '<br />Lat/Lon : '  . $data[0]["latitude"] . '/' . $data[0]["longitude"] ;


		}
		(!empty($data[0]["bus_metro_tram"])) ? $adresse_organisme.='<br />Station : '.$data[0]["bus_metro_tram"].'' : $adresse_organisme.="";
		(!empty($data[0]["bus_metro_tram"])) ? $coordonnees.= '<br />' . $data[0]["bus_metro_tram"] : null ;
			
		($aide_o_n=='o') ? $adresse_organisme.=$this->descripteur_aide('Descripteur_lieu','n') : $adresse_organisme.="";
		($qr_o_n=='o') ? $retour=$qr_adresse_organisme : null ;
		($qr_o_n=='n' || $qr_o_n=='') ? $retour=$adresse_organisme : null;
		($qr_o_n=='c') ? $retour=$coordonnees : null;
			
		return $retour;
	}
	function action_html_popup()
	{
		$table = $this->m_postvars["table"];
		$id = $this->m_postvars["id"];
		$field = $this->m_postvars["field"];

		$popup=atkPopup('atk/popups/htmlpopup.inc','table="'.$table.'"&id='.$id.'&field="'.$field.'"','Contenu html',650,650,'yes','no');
		//			$this->p($popup);
		return $popup;

	}

	function descripteur_document($type='organisme',$id_document, $aide_o_n='o',&$lien=null)
	{
		
		$db = & atkGetDb();
		if ($type=='organisme')
		{
			$sql="select od.libelle as titre , od.file_size, od.contenu_html, td.libelle as type, od.file_extension as extension,
			od.url_upload, od.date_upload, od.id_upload, i.nom, i.prenom, od.id_individu_auteur, od.id_organisme, od.url_document
			from organisme_document od LEFT JOIN type_document td ON od.id_type_document=td.id
			LEFT JOIN individu i ON od.id_upload=i.id
			Where od.id=$id_document";
			$table="organisme_document";
			$id=$id_document;
			$field="contenu_html";
		}
		if ($type=='individu')
		{
			$sql="select od.libelle as titre , od.file_size, od.contenu_html, td.libelle as type, od.file_extension as extension,
			od.url_upload, od.date_upload, od.id_individu, od.url_document
			from individu_document od LEFT JOIN type_document td ON od.id_type_document=td.id
			Where od.id=$id_document";
			$table="individu_document";
			$id=$id_document;
			$field="contenu_html";
		}
		$data = $db->getrows($sql);
		$nom=$data[0]["nom"];
		$prenom=$data[0]["prenom"];
		$file_size=$data[0]["file_size"];
		$id_individu=$data[0]["id_individu"];
		$id_organisme=$data[0]["id_organisme"];
		$temp_size="";
	while (strlen($file_size)>0) 
		{
			if (strlen($file_size)>3)
			{
				$temp_size=".".substr($file_size,(strlen($file_size)-3),3).$temp_size;
				$file_size=substr($file_size,0,(strlen($file_size)-3));
			}
			else
			{$temp_size=$file_size.$temp_size;
			$file_size="";
			}
		}
			$file_size=$temp_size;
			

//			($type=='individu') ?	$retour.=$this->descripteur_individu($id_individu)."<br/>" : $retour.="";
			($type=='individu')? $retour.=''.href(dispatch_url("individu.document_i", "view", array ('atkselector' => " individu_document.id='" . $id_document . "'"
			), "dispatch.php"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/label.png" alt="Document individu AssoCope"
				title="Document individu AssoCope" ></img>', SESSION_NESTED) : $retour.='' ;
//			($type=='organisme') ? $retour.=$this->descripteur_organisme($id_organisme,'n')."<br/>" : $retour.="";
			($type=='organisme')? $retour.=''.href(dispatch_url("organisme.document", "view", array ('atkselector' => " organisme_document.id='" . $id_document . "'"
			), "dispatch.php"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/label.png" alt="Document organisme AssoCope"
				title="Document organisme AssoCope" ></img>', SESSION_NESTED) : $retour.='' ;
			
				
		
		($type=='individu')? $retour.=" ".atkHref(		dispatch_url("individu.document_i", "edit", array ("atkselector" => "individu_document.id='" . $id_document . "'" )),
				"<b>".$data[0]["titre"]."</b> ".$aide."<br /> (".$data[0]["type"].") ",SESSION_NESTED, false, 'target="main"') : $retour.='';
		($type=='organisme')? $retour.=" ".atkHref(		dispatch_url("organisme.document", "edit", array ("atkselector" => "organisme_document.id='" . $id_document . "'" )),
				"<b>".$data[0]["titre"]."</b> ".$aide."<br /> (".$data[0]["type"].") ",SESSION_NESTED, false, 'target="main"') : $retour.='';
		$icon="down.png";
		if (strstr("doc, odt, txt, rtf", $data[0]["extension"])!=false) $icon="ttexte.gif";
		if (strstr(" html, htm", $data[0]["extension"])!=false) $icon="html.png";
		if (strstr("xls, ods", $data[0]["extension"])!=false) $icon="tableur.gif";
		if (strstr("pdf", $data[0]["extension"])!=false) $icon="pdf.png";
		if (strstr("odp, pps, ppt", $data[0]["extension"])!=false) $icon="diaporama.png";
		if (strstr("gif, jpeg, jpg, jpe, , svg, png", $data[0]["extension"])!=false) $icon="image.png";
		if (strstr("aac, mp3, oga, ogg, flac, wav, ra", $data[0]["extension"])!=false) $icon="audio.png";
		if (strstr("avi, mkv, ogm, mov", $data[0]["extension"])!=false) $icon="video.png";
		if (strstr("gz, tar, zip, 7z, rar", $data[0]["extension"])!=false) $icon="archive.png";
		if (strstr("csv", $data[0]["extension"])!=false) $icon="csv.png";
		if (strstr("kml, kmz ", $data[0]["extension"])!=false) $icon="earth.png";
		if ($type=='organisme')
		{
			(!empty($data[0]["file_size"])) ? $lien=''.href(dispatch_url("organisme.document", "fichier", array (
					'atkselector' => " organisme_document.id='" . $id_document . "'"
			), "dispatch.php"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icon.'"
					alt="Ouvrir fichier : '.$data[0]["extension"].' ('.$data[0]["file_size"].')"
					title="Ouvrir fichier : '.$data[0]["extension"].' ('.$data[0]["file_size"].')" ></img>', SESSION_NESTED, null, ' target="_blank" ') : $lien='';
			$retour.=$lien;
	//		$lien="<b>".$data[0]["titre"]."</b> ".$lien."<br/>".$this->descripteur_organisme_sans_lien($data[0]["id_organisme"]);
			$lien="<b>".$data[0]["titre"]."</b> ".$lien;
		}
		if ($type=='individu')
		{
			(!empty($data[0]["file_size"])) ? $lien=''.href(dispatch_url("individu.document_i", "fichier", array (
					'atkselector' => " individu_document.id='" . $id_document . "'"
			), "dispatch.php"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icon.'"
					alt="Ouvrir fichier : '.$data[0]["extension"].' ('.$data[0]["file_size"].')"
					title="Ouvrir fichier : '.$data[0]["extension"].' ('.$data[0]["file_size"].')" ></img>', SESSION_NESTED, null, ' target="_blank" ')  : $lien='';
			$retour.=$lien;
	//		$lien="<b>".$data[0]["titre"]."</b> ".$lien."<br/>".$this->descripteur_individu_sans_lien($data[0]["id_individu"]);
			$lien="<b>".$data[0]["titre"]."</b> ".$lien ;
		}
		if ($type=='organisme')
		{
			(!empty($data[0]["file_size"])) ? $retour.=''.href(dispatch_url($this->atkNodeType,"assocope_to_google_export",array("atkselector"=>" organisme_document.id='" . $id_document . "'"
					,"atkaction"=>"assocope_to_google_export")),
					'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google_icon.png" alt="Exporter vers Google" title="Exporter vers Google" target="_blank">',
					SESSION_NESTED,	false, ' target="_blank"') : $retour.='';
		}
		if ($type=='individu')
		{
			(!empty($data[0]["file_size"])) ? $retour.=''.href(dispatch_url($this->atkNodeType,"assocope_to_google_export",array("atkselector"=>" individu_document.id='" . $id_document . "'"
					,"atkaction"=>"assocope_to_google_export")),
					'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google_icon.png" alt="Exporter vers Google" title="Exporter vers Google" target="_blank">',
					SESSION_NESTED,	false, ' target="_blank"') : $retour.='';
		}
		($data[0]["file_size"]>0) ? $retour.=" (<b>".$file_size."</b> octets)" :null;
		// texte
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table='.$table.'&id='.$id.'&field='.$field,'Contenu html',650,650,'yes','no');
		(!empty($data[0]["contenu_html"])) ? $retourtexte='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Texte riche"
				title="Texte riche" ></img></a>' : $retourtexte='';
		$retour.=$retourtexte;
		$lien.=$retourtexte;
		(!empty($data[0]["url_document"])) ? $retoururl=' '.$this->affiche_url($data[0]["url_document"],"Network-Download-icon.png") : $retoururl=' ';
		$retour.=$retoururl;
		$lien.=$retoururl;
		(!empty($data[0]["id_individu_auteur"])) ? $retour.='</br>Auteur : '.$this->descripteur_individu_sans_lien($data[0]["id_individu_auteur"]) : null;
		if	(!empty($data[0]["url_upload"]))
		{
			$retour.='</br><img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/upload.gif" alt="Uploadé"
					title="a été uploadé" ></img> <b><a href="'.$data[0]["url_upload"].'" target="_blank">'.$data[0]["url_upload"].'</a>';
			$retour.='</br></b>Le : <b>'.$data[0]["date_upload"].'</b>' ;
			if ($type=='organisme')
			{
				$retour.='</br>Par : '.$this->descripteur_individu($data[0]["id_upload"],'n');
			}
		}
		

		($type=='individu') ?	$retour.="<br/>".$this->descripteur_individu($id_individu,'n','n') : $retour.="";
		($type=='organisme') ? $retour.="<br/>".$this->descripteur_organisme($id_organisme,'n','n'): $retour.="";
		
		($aide_o_n=='o' ) ? $aide=$this->descripteur_aide('Descripteur_document','n') : $aide="";
	
		
		return $retour;
	}
	
	function descripteur_contact($id_contact, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		ic.id_individu,
		ic.id_organisme_contactant,
		ic.id_contact,
		ic.id_organisme_contacte,
		ic.titre as titre,
		tc.libelle as type,
		ic.date_prevue,
		ic.date_realisee,
		ic.attente_reponse_o_n,
		ic.courriel,
		ic.date_dernier_courriel,
		ic.retour_o_n,
		ic.id_envoi_groupe
		from individu_contact ic LEFT JOIN type_contact tc ON ic.id_type_contact=tc.id
		Where ic.id=$id_contact";
		$data = $db->getrows($sql);
		$href=atkHref(dispatch_url("individu.contact_i", "edit", array ("atkselector" => "individu_contact.id='" . $id_contact . "'" )),
				$data[0]["titre"],SESSION_NESTED, false, 'target="main"') ;
		(!empty($data[0]["titre"])) ? $retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/contact.png" alt="Contact" title="Contact" target="_blank"></img>'.
				"<b>".$href."</b><br /> (".$data[0]["type"].")<br />" : $retour="" ;
		(!empty($data[0]["id_contact"])) ? $retour.=$this->descripteur_individu($data[0]["id_contact"],'n','n',null,null,'n') : null;
		(!empty($data[0]["id_organisme_contactant"])) ? $retour.=' ('.$this->descripteur_organisme($data[0]["id_organisme_contactant"],'n','n').")" : null;
		(!empty($data[0]["id_individu"])) ? $retour.='<br/><b>===></b><br/>'.$this->descripteur_individu($data[0]["id_individu"],'n','n',null,null,'n') : null;
		(!empty($data[0]["id_organisme_contacte"])) ? $retour.=' ('.$this->descripteur_organisme($data[0]["id_organisme_contacte"],'n','n').")" : null;

		$retour.="<br/>";
		(!empty($data[0]["date_prevue"])) ? $retour.="</b>Prévu le <b>".$data[0]["date_prevue"]." " : $retour.="" ;
		(!empty($data[0]["date_realisee"])) ? $retour.="</b>fait le <b>".$data[0]["date_realisee"]."<br />" : $retour.="<br />" ;
		(!empty($data[0]["courriel"])) ? $retour.="</b>Envoyé à <b>".$data[0]["courriel"]."</b> le <b>".$data[0]["date_dernier_courriel"]."<br />" : $retour.="" ;
		($data[0]["attente_reponse_o_n"]==1) ? $retour.="</b>En attente de réponse<b><br />" : $retour.="" ;
		(!empty($data[0]["id_envoi_groupe"])) ? $retour.="</b>id_envoi : <b>".$data[0]["id_envoi_groupe"]."" : $retour.="" ;
		($data[0]["retour_o_n"]==1) ? $retour.="</b>Non distribué (retour)<b><br />" : $retour.="" ;
		$desc=$this->descripteur_contenu_contact($id_contact, 'n');
		(!empty($desc)) ? $retour.="</b>Contenu : ".$desc : null;

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_contact','n') : $retour.="";
		return $retour;
	}

	function descripteur_contenu_contact($id_contact, $aide_o_n='o',$sans_lien_o_n='n')
	{
		$db = & atkGetDb();
		$sql="select
		ic.commentaire_html,
		ic.id_document_organisme,
		ic.id_document_organisme_1,
		ic.id_document_organisme_2,
		ic.id_document_individu,
		ic.id_document_individu_1,
		ic.id_document_individu_2
			
		from individu_contact ic
		Where ic.id=$id_contact";
		$table="individu_contact";
		$id=$id_contact;
		$field="commentaire_html";
		$data = $db->getrows($sql);

		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table='.$table.'&id='.$id.'&field='.$field,'Contenu html',650,650,'yes','no');
		(!empty($data[0]["commentaire_html"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Texte riche"
				title="Texte riche" ></img><br /></a>' : $retour.='';
		$retour2="";
		(!empty($data[0]["id_document_organisme"])) ? $retour2=$this->descripteur_document("organisme",$data[0]["id_document_organisme"],'o',$lien1).'<br />' : $retour2="" ;
		(!empty($data[0]["id_document_organisme_1"])) ? $retour2.=$this->descripteur_document("organisme",$data[0]["id_document_organisme_1"],'o',$lien2).'<br />' : $retour2.="" ;
		(!empty($data[0]["id_document_organisme_2"])) ? $retour2.=$this->descripteur_document("organisme",$data[0]["id_document_organisme_2"],'o',$lien3).'<br />' : $retour2.="" ;
		(!empty($data[0]["id_document_individu"])) ? $retour2.=$this->descripteur_document("individu",$data[0]["id_document_individu"],'o',$lien4).'<br />' : $retour2.="" ;
		(!empty($data[0]["id_document_individu_1"])) ? $retour2.=$this->descripteur_document("individu",$data[0]["id_document_individu_1"],'o',$lien5).'<br />' : $retour2.="" ;
		(!empty($data[0]["id_document_individu_2"])) ? $retour2.=$this->descripteur_document("individu",$data[0]["id_document_individu_2"],'o',$lien6).'<br />' : $retour2.="" ;

		if ($sans_lien_o_n=='o')
		{
			$retour2="";
			($lien1!="")? $retour2.=$lien2."<br/>" : $retour2.="";
			($lien3!="")? $retour2.=$lien3."<br/>" : $retour2.="";
			($lien4!="")? $retour2.=$lien4."<br/>" : $retour2.="";
			($lien5!="")? $retour2.=$lien5."<br/>" : $retour2.="";
			($lien6!="")? $retour2.=$lien6 : $retour2.="";
			$aide="";
		}
else
{($aide_o_n=='o') ? $aide=$this->descripteur_aide('Descripteur_contenu_contact','n') : $aide="";}

		return $retour.$retour2.$aide;
	}

	function descripteur_organisme_contrat($id_contrat, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		organisme_contrat.id,
		id_organisme,
		id_organisme_contrat,
		id_interlocuteur,
		id_individu_conventionne,
		organisme_contrat.libelle as libelle,
		type_contrat.libelle as type,
		reference_contrat,
		avenant,
		id_lieu_rencontre,
		id_document,
		date_souscription,
		motif_souscription,
		montant,
		periodicite,
		date_echeance,
		date_resiliation,
		motif_resiliation
			
		from organisme_contrat, type_contrat
		Where organisme_contrat.id=$id_contrat and organisme_contrat.id_type_contrat=type_contrat.id";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.contrat", "edit", array (	'atkselector' => "organisme_contrat.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/contrat.png" alt="Contrat" title="Contrat" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		$retour.="(".$data[0]["type"].")</b> <br />";
		(!empty($data[0]["id_organisme"])) ? $retour.="</b>Souscrit par : <b>".$this->descripteur_organisme($data[0]["id_organisme"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["id_individu_conventionne"])) ? $retour.=$this->descripteur_individu($data[0]["id_individu_conventionne"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["id_organisme_contrat"])) ? $retour.="</b>Auprès de : <b>".$this->descripteur_organisme($data[0]["id_organisme_contrat"],'n','n','50')."<br />" : $retour.='';

		(!empty($data[0]["id_interlocuteur"])) ? $retour.=$this->descripteur_individu($data[0]["id_interlocuteur"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["id_document"])) ? $retour.="</b>Document : <b>".$this->descripteur_document('organisme',$data[0]["id_document"], 'o')."</b><br />" : $retour.="" ;
		$url=$data[0]["url"];
		(!empty($data[0]["date_souscription"])) ? $retour.="</b>Souscrit le : <b>".$data[0]["date_souscription"]."<br />" : $retour.='';
		(!empty($data[0]["montant"])) ? $retour.="</b>Montant : <b>".$data[0]["montant"]."<br />" : $retour.='';
		(!empty($data[0]["periodicite"])) ? $retour.="</b>Périodicité : <b>".$data[0]["periodicite"]."<br />" : $retour.='';
		(!empty($data[0]["date_echeance"])) ? $retour.="</b>Prochaine échéance : <b>".$data[0]["date_echeance"]."<br />" : $retour.='';
		(!empty($data[0]["date_resiliation"])) ? $retour.="</b>Résilié le : <b>".$data[0]["date_resiliation"]."<br />" : $retour.='';

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_organisme_contrat','n')."<br />" : $retour.="<br />";

		return $retour;
	}

	function descripteur_patrimoine($id_patrimoine, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		id,
		id_organisme,
		libelle,
		date_acquisition,
		montant_acquisition,
		motif_acquisition,
		date_cession,
		montant_cession,
		motif_cession
		from organisme_patrimoine
		Where organisme_patrimoine.id=$id_patrimoine";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.programme", "edit", array (	'atkselector' => "organisme_programme.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/patrimoine.png" alt="Patrimoine" title="Patrimoine" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		(!empty($data[0]["date_acquisition"])) ? $retour.="</b>Acquis le : <b>".$data[0]["date_acquisition"]."<br />" : $retour.='';
		(!empty($data[0]["montant_acquisition"])) ? $retour.="</b>Montant : <b>".$data[0]["montant_acquisition"]."<br />" : $retour.='';
		(!empty($data[0]["motif_acquisition"])) ? $retour.="</b>Motif : <b>".$data[0]["motif_acquisition"]."<br />" : $retour.='';
		(!empty($data[0]["date_cession"])) ? $retour.="</b>Cédé le : <b>".$data[0]["date_cession"]."<br />" : $retour.='';
		(!empty($data[0]["montant_cession"])) ? $retour.="</b>Montant : <b>".$data[0]["montant_cession"]."<br />" : $retour.='';
		(!empty($data[0]["motif_cession"])) ? $retour.="</b>Motif : <b>".$data[0]["motif_cession"]."<br />" : $retour.='';

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_patrimoine','n')."<br />" : $retour.="<br />";

		return $retour;
	}
	
	function descripteur_referencement($id_referencement, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		organisme_referencement.id,
		id_organisme,
		id_organisme_referencement,
		id_interlocuteur,
		organisme_referencement.libelle,

		tr.libelle as type_referencement,
		date_inscription,
		url,
		date_verification,

		ter.libelle as etat_referencement,
		contenu,
		date_echeance,
		date_resiliation,
		motif_resiliation
		from organisme_referencement, type_referencement tr, type_etat_referencement ter
		Where organisme_referencement.id=$id_referencement
		and organisme_referencement.id_type_referencement=tr.id and organisme_referencement.id_type_etat_referencement=ter.id";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.referencement", "edit", array (	'atkselector' => "organisme_referencement.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/referencement.png" alt="Référencement" title="Référencement" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		$retour.="(".$data[0]["type_referencement"].")</b> <br />";

		(!empty($data[0]["id_organisme_referencement"])) ? $retour.="</b>Référenceur : <b>".$this->descripteur_organisme($data[0]["id_organisme_referencement"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["id_interlocuteur"])) ? $retour.="</b>Interlocuteur : <b>".$this->descripteur_individu($data[0]["id_interlocuteur"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["date_inscription"])) ? $retour.="</b>Référencé le : <b>".$data[0]["date_inscription"]."<br />" : $retour.='';
		$url=$data[0]["url"];
		(!empty($data[0]["url"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["date_verification"])) ? $retour.="</b>Vérifié le : <b>".$data[0]["date_verification"]."<br />" : $retour.='';
		(!empty($data[0]["etat_referencement"])) ? $retour.="</b>Etat : <b>".$data[0]["etat_referencement"]."<br />" : $retour.='';
		(!empty($data[0]["contenu"])) ? $retour.="</b>Contenu : <b>".$data[0]["contenu"]."<br />" : $retour.='';
		(!empty($data[0]["date_echeance"])) ? $retour.="</b>Echéance le : <b>".$data[0]["date_echeance"]."<br />" : $retour.='';
		(!empty($data[0]["date_resiliation"])) ? $retour.="</b>Résilié le : <b>".$data[0]["date_resiliation"]."<br />" : $retour.='';
		(!empty($data[0]["motif_resiliation"])) ? $retour.="</b>Motif : <b>".$data[0]["motif_resiliation"]."<br />" : $retour.='';

		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_referencement','n')."<br />" : $retour.="<br />";

		return $retour;
	}
		
	function descripteur_domaine_internet($id_domaine, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select

		id,
		id_organisme,
		libelle,
		nom_domaine,
		google_apps_o_n,
		id_organisme_registrar,
		date_registrar_debut,
		date_registrar_fin,
		url_administration_registrar,
		identifiant_registrar,
		mot_de_passe_registrar,
		cout_registrar,
		commentaire_registrar,
		id_organisme_hebergement,
		date_contrat_debut_hebergement,
		date_contrat_fin_hebergement,
		caracteristiques_hebergement,
		url_administration_hebergement,
		identifiant_hebergement,
		mot_de_passe_hebergement,
		cout_hebergement,
		commentaire_hebergement,
		url_administration_mysql,
		serveur_mysql,
		identifiant_mysql,
		mot_de_passe_mysql,
		commentaire_mysql,
		url_administration_ftp,
		serveur_ftp,
		identifiant_ftp,
		mot_de_passe_ftp,
		commentaire_ftp,
		url_administration_mail,
		serveur_mail,
		identifiant_mail,
		mot_de_passe_mail,
		commentaire_mail
		from organisme_domaine
		Where organisme_domaine.id=$id_domaine
		";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.domaine", "edit", array (	'atkselector' => "organisme_domaine.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/domaine_internet.png" alt="Domaine internet" title="Domaine internet" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		(!empty($data[0]["nom_domaine"])) ? $retour.="</b>Nom de domaine : <b>".$data[0]["nom_domaine"]."<br />" : $retour.='';
			
		(!empty($data[0]["id_organisme_registrar"])) ? $retour.="<br /></b>Registrar : <b>".$this->descripteur_organisme($data[0]["id_organisme_registrar"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["date_registrar_debut"])) ? $retour.="</b>Début : <b>".$data[0]["date_registrar_debut"]."<br />" : $retour.='';
		(!empty($data[0]["date_registrar_fin"])) ? $retour.="</b>Fin : <b>".$data[0]["date_registrar_fin"]."<br />" : $retour.='';
		$url=$data[0]["url_administration_registrar"];
		(!empty($data[0]["url_administration_registrar"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["identifiant_registrar"])) ? $retour.="</b>Identifiant : <b>".$data[0]["identifiant_registrar"]."/".$data[0]["mot_de_passe_registrar"]."<br />" : $retour.='';
		(!empty($data[0]["cout_registrar"])) ? $retour.='</b>Coût : <b><font style="font-size:18px;">'.$data[0]["cout_registrar"]."</font><br />" : $retour.='';
		//					(!empty($data[0]["commentaire_registrar"])) ? $retour.="</b>Commentaire : <b>".filter_var($data[0]["commentaire_registrar"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';

		(!empty($data[0]["id_organisme_hebergement"])) ? $retour.="<br /></b>Hébergeur : <b>".$this->descripteur_organisme($data[0]["id_organisme_hebergement"],'n','n','50')."<br />" : $retour.='';
		(!empty($data[0]["date_contrat_debut_hebergement"])) ? $retour.="</b>Début : <b>".$data[0]["date_contrat_debut_hebergement"]."<br />" : $retour.='';
		(!empty($data[0]["date_contrat_fin_hebergement"])) ? $retour.="</b>Fin : <b>".$data[0]["date_contrat_fin_hebergement"]."<br />" : $retour.='';
		$url=$data[0]["url_administration_hebergement"];
		(!empty($data[0]["url_administration_hebergement"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["identifiant_hebergement"])) ? $retour.="</b>Identifiant : <b>".$data[0]["identifiant_hebergement"]."/".$data[0]["mot_de_passe_hebergement"]."<br />" : $retour.='';
		(!empty($data[0]["cout_hebergement"])) ? $retour.='</b>Coût : <b><font style="font-size:18px;">'.$data[0]["cout_hebergement"]."</font><br />" : $retour.='';
		//					(!empty($data[0]["commentaire_hebergement"])) ? $retour.="</b>Commentaire : <b>".filter_var($data[0]["commentaire_hebergement"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';
			
		$retour.="<br />MySql : <br /></b>";
		$url=$data[0]["url_administration_mysql"];
		(!empty($data[0]["url_administration_mysql"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["serveur_mysql"])) ? $retour.="</b>Serveur : <b>".$data[0]["serveur_mysql"]."<br />" : $retour.='';
		(!empty($data[0]["identifiant_mysql"])) ? $retour.="</b>Identifiant : <b>".$data[0]["identifiant_mysql"]."/".$data[0]["mot_de_passe_mysql"]."<br />" : $retour.='';
		//					(!empty($data[0]["commentaire_mysql"])) ? $retour.="</b>Commentaire : <b>".filter_var($data[0]["commentaire_mysql"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';
			
		$retour.="<br />Ftp : <br /></b>";
		$url=$data[0]["url_administration_ftp"];
		(!empty($data[0]["url_administration_ftp"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["serveur_ftp"])) ? $retour.="</b>Serveur : <b>".$data[0]["serveur_ftp"]."<br />" : $retour.='';
		(!empty($data[0]["identifiant_ftp"])) ? $retour.="</b>Identifiant : <b>".$data[0]["identifiant_ftp"]."/".$data[0]["mot_de_passe_ftp"]."<br />" : $retour.='';
		//					(!empty($data[0]["commentaire_ftp"])) ? $retour.="</b>Commentaire : <b>".filter_var($data[0]["commentaire_ftp"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';

		$retour.="<br />Mail : <br /></b>";
		$url=$data[0]["url_administration_mail"];
		(!empty($data[0]["url_administration_mail"])) ? $retour.="</b>Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		(!empty($data[0]["serveur_mail"])) ? $retour.="</b>Serveur : <b>".$data[0]["serveur_mail"]."<br />" : $retour.='';
		(!empty($data[0]["identifiant_mail"])) ? $retour.="</b>Identifiant : <b>".$data[0]["identifiant_mail"]."/".$data[0]["mot_de_passe_mail"]."<br />" : $retour.='';
		//					(!empty($data[0]["commentaire_mail"])) ? $retour.="</b>Commentaire : <b>".filter_var($data[0]["commentaire_mail"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';
			
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_domaine_internet','n')."<br />" : $retour.="<br />";

		return $retour;
	}
		

	function descripteur_groupe_travail($id_groupe_travail, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		organisme_groupe_travail.id as id_groupe_travail,
		id_organisme,
		nom,
		objet,
		tr.libelle as type_rencontre,
		tf.libelle as type_fonction,
		id_lieu_rencontre,
		lieu_reunion,
		end_choice,
		cyclus_enddate,
		cyclus_times,
		date_debut_groupe,
		date_fin_groupe
		from organisme_groupe_travail, type_rencontre tr, type_fonction tf
		Where organisme_groupe_travail.id=$id_groupe_travail
		and organisme_groupe_travail.id_type_rencontre=tr.id and organisme_groupe_travail.id_type_fonction=tf.id";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.groupe_travail", "edit", array (	'atkselector' => "organisme_groupe_travail.id='" . $data[0]["id_groupe_travail"]. "'"
		), "dispatch.php"), $data[0]["nom"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/groupe_travail.png" alt="Groupe de travail" title="Groupe de travail" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		(!empty($data[0]["objet"])) ? $retour.="</b>Objet : <b>".filter_var($data[0]["objet"], FILTER_SANITIZE_STRING)."<br />" : $retour.='';
		(!empty($data[0]["type_rencontre"])) ? $retour.="</b>Type rencontre : <b>".$data[0]["type_rencontre"]."<br />" : $retour.='';
		(!empty($data[0]["type_fonction"])) ? $retour.="</b>Type fonction : <b>".$data[0]["type_fonction"]."<br />" : $retour.='';
		$id_lieu_rencontre=$data[0]["id_lieu_rencontre"];
		(!empty($data[0]["id_lieu_rencontre"])) ? $retour.="</b>Lieu rencontre : <b>".$this->descripteur_organisme_lieu_rencontre($id_lieu_rencontre,'n') : $retour.='';
		//		(!empty($data[0]["end_choice"])) ? $retour.="</b>End choice : <b>".$data[0]["end_choice"]."<br />" : $retour.='';
		//		(!empty($data[0]["cyclus_enddate"])) ? $retour.="</b>cyclus_enddate : <b>".$data[0]["cyclus_enddate"]."<br />" : $retour.='';
		//		(!empty($data[0]["cyclus_times"])) ? $retour.="</b>cyclus_times : <b>".$data[0]["cyclus_times"]."<br />" : $retour.='';
		(!empty($data[0]["date_debut_groupe"])) ? $retour.="</b>Début le : <b>".$data[0]["date_debut_groupe"]."<br />" : $retour.='';
		(!empty($data[0]["date_fin_groupe"])) ? $retour.="</b>Fin le : <b>".$data[0]["date_fin_groupe"]."<br />" : $retour.='';

		$sql="select count(id)  as nombre from individu_groupe_travail
				where  id_groupe_travail = ".$id_groupe_travail." ";
		$row = $db->getrows($sql);
		$total=	$row[0]["nombre"];
		$sql="select count(id)  as nombre from individu_groupe_travail
				where date_fin_groupe is null and id_groupe_travail = ".$id_groupe_travail." ";
		$row = $db->getrows($sql);
		$actifs=	$row[0]["nombre"];

		$retour.= "</b>Participants : <b>".href(dispatch_url("individu.groupe_travail_i", "admin", array (
				'atkfilter' => "individu_groupe_travail.id_groupe_travail='" . $id_groupe_travail . "'"
		), "dispatch.php"), text($actifs.'/'.$total), SESSION_NESTED)."<br />";
		$sql="select count(id) as nombre from organisme_rencontre
				where id_groupe_travail = ".$id_groupe_travail." " 	;
		$row = $db->getrows($sql);
		$nombre=	$row[0]["nombre"];
		$sql="select count(id) as nombre from organisme_rencontre
				where date_debut > CURDATE() and id_groupe_travail = ".$id_groupe_travail." " 	;
		$row = $db->getrows($sql);
		$nombre_a_venir=	$row[0]["nombre"];
		$retour.="</b>Rencontres : <b>".href(dispatch_url("organisme.rencontre", "admin", array (
				'atkfilter' => "organisme_rencontre.id_groupe_travail='" . $id_groupe_travail . "'"
		), "dispatch.php"), text($nombre)."/".$nombre_a_venir, SESSION_NESTED)."<br />";
			
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_groupe_travail','n')."<br />" : $retour.="<br />";

		return $retour;
	}

	function descripteur_fonction($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();

		$sql="select
		id_fonction,
		id_individu,
		id_organisme,
		id_organisme_represente,
		tf.libelle,
		date_debut,
		date_echeance,
		date_fin
		from individu_fonction , type_fonction tf
		where individu_fonction.id=$id_entite and id_fonction=tf.id";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("table.fonction", "edit", array (	'atkselector' => "type_fonction.id='" . $data[0]["id_fonction"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour.=$this->descripteur_individu($data[0]["id_individu"],'n','n','50')."<br />";
		$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/function_icon.png" alt="Fonction" title="Fonction" target="_blank"></img> <b>'.$href."</b><br />";
		(!empty($data[0]["id_organisme_represente"])) ? $retour.="</b>Organisme représenté : <b>".$this->descripteur_organisme($data[0]["id_organisme_represente"],'n','n','50')."<br />" : $retour.='';
		
		$retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n','50')."<br />";


			
		(!empty($data[0]["date_debut"])) ? $retour.="</b>Début : <b>".$data[0]["date_debut"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_echeance"])) ? $retour.="</b>Echéance : <b>".$data[0]["date_echeance"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_fin"])) ? $retour.="</b>Fin : <b>".$data[0]["date_fin"]."<br />" : $retour.="" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_fonction','n') : $retour.="";
		return $retour;

	}
	function descripteur_inscription($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();

		$sql="select
		ti.libelle as inscription,
		ii.id_individu,
		ii.id_organisme,
		ii.id_organisme_inscrit,
		ii.id_type_inscription,
		ii.id_inscription,
		ii.date_inscription,
		ii.date_adhesion,
		ii.id_document_adhesion,
		ii.date_envoi_carte,
		ii.date_derniere_cotisation,
		ii.date_radiation,
		tr.libelle as radiation,
		ii.origine,
		tori.libelle as libelle_origine
		from individu_inscription ii
		LEFT JOIN type_inscription ti  ON ii.id_type_inscription=ti.id
		LEFT JOIN type_radiation tr ON ii.id_type_radiation=tr.id
		LEFT JOIN type_origine tori ON ii.id_type_origine=tori.id

		where ii.id=$id_entite";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("table.type_inscription", "view", array (	'atkselector' => "type_inscription.id='" . $data[0]["id_type_inscription"]. "'"
		), "dispatch.php"), "</b>Type : <b>".$data[0]["inscription"], SESSION_NESTED);
		//	(!empty($data[0]["inscription"])) ? $retour="<b>".$href."</b><br />" : $retour="" ;
		

		$retour.=$this->descripteur_individu($data[0]["id_individu"],'n','n','50')."<br />";
		(!empty($data[0]["id_organisme_inscrit"])) ? $retour.=" (".$this->descripteur_organisme($data[0]["id_organisme_inscrit"],'n','n','50').")<br />" : $retour.='';


		$retour.="<b>".$href."</b><br />";
		(!empty($data[0]["id_inscription"])) ? $retour.="</b>Numéro : <b>".$data[0]["id_inscription"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["date_inscription"])) ? $retour.="</b>Inscrit le : <b>".$data[0]["date_inscription"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_adhesion"])) ? $retour.="</b>Adhésion le : <b>".$data[0]["date_adhesion"]."<br />" : $retour.="" ;
		(!empty($data[0]["id_document_adhesion"])) ? $retour.="</b>Document d\'adhésion : <b>".$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_adhesion"])."<br />" : $retour.="" ;
		(!empty($data[0]["date_envoi_carte"])) ? $retour.="</b>Carte envoyée le : <b>".$data[0]["date_envoi_carte"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_derniere_cotisation"])) ? $retour.="</b>Dernière cotisation : <b>".$data[0]["date_derniere_cotisation"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_radiation"])) ? $retour.="</b>Radiation le : <b>".$data[0]["date_radiation"]."<br />" : $retour.="" ;
		(!empty($data[0]["radiation"])) ? $retour.="</b>Motif : <b>".$data[0]["radiation"]."<br />" : $retour.="" ;
		(!empty($data[0]["origine"])) ? $retour.="</b>Origine : <b>".$data[0]["origine"]."<br />" : $retour.="" ;
		(!empty($data[0]["libelle_origine"])) ? $retour.="</b>Origine : <b>".$data[0]["libelle_origine"]."<br />" : $retour.="" ;
		$retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n','50')."<br />";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_inscription','n') : $retour.="";
		return $retour;

	}


	function descripteur_type_inscription($id_entite, $aide_o_n='o', $id_organisme_appel=null)
	{
		$db = & atkGetDb();

		if ($id_organisme_appel>0)
		{
			$sql="select count(id) as nombre from individu_inscription ii where ii.id_type_inscription=$id_entite and ii.id_organisme=$id_organisme_appel and ii.date_radiation IS  NULL";
		}
		else
		{
			$sql="select count(id) as nombre from individu_inscription ii where ii.id_type_inscription=$id_entite and ii.date_radiation IS  NULL";
		}
		$data = $db->getrows($sql);

		$lien_inscrits=href(dispatch_url("individu.inscription_i", "admin", array (
				'atkfilter' => "individu_inscription.id_type_inscription=$id_entite"
		), "dispatch.php"), $data[0]["nombre"], SESSION_NESTED);

		$sql="select

		libelle,
		inscription_organisme_o_n,
		cotisation_organisme_o_n,
		tarif,
		cotisation_federation_o_n,
		carte_o_n,
		timbre_o_n,
		lettre_o_n,
		infolettre_o_n,
		flash_info_o_n,
		delai_radiation_non_cotisation,
		delai_radiation_non_adhesion,
		modifiable_o_n,
		id_organisme
		from  type_inscription
		where id=$id_entite";
		$data = $db->getrows($sql);
		// iconeInscription.png
		$href=href(dispatch_url("table.type_inscription", "edit", array (	'atkselector' => "type_inscription.id='" . $id_entite. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$id_organisme=$data[0]["id_organisme"];

		$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/iconeInscription.png" alt="Type d\'inscription" title="Type d\'inscription" target="_blank"></img>'." <b>".$href."</b><br />";
		($id_organisme>0) ? $retour.="( Propre à ".$this->descripteur_organisme($id_organisme)." )<br />": $retour.="";
		($data[0]["inscription_organisme_o_n"]=='1') ? $retour.="-> Inscription d'organisme"."<br />" : $retour.="" ;
		($data[0]["cotisation_organisme_o_n"]=='1') ? $retour.="-> Cotisation"."<br />" : $retour.="" ;
		(!empty($data[0]["tarif"])) ? $retour.="-> Tarif : ".$data[0]["tarif"]. "<br />" : $retour.="" ;
		($data[0]["cotisation_federation_o_n"]=='1') ? $retour.="-> Cotisation fédération"."<br />" : $retour.="" ;
		($data[0]["carte_o_n"]=='1') ? $retour.="-> Carte d'adhérent"."<br />" : $retour.="" ;
		($data[0]["timbre_o_n"]=='1') ? $retour.="-> Timbre cotisation"."<br />" : $retour.="" ;
		($data[0]["lettre_o_n"]=='1') ? $retour.="-> Lettre"."<br />" : $retour.="" ;
		($data[0]["infolettre_o_n"]=='1') ? $retour.="-> Infolettre"."<br />" : $retour.="" ;
		($data[0]["flash_info_o_n"]=='1') ? $retour.="-> Flash info"."<br />" : $retour.="" ;
		(!empty($data[0]["delai_radiation_non_cotisation"])) ? $retour.="-> Délai radiation non cotisation : ".$data[0]["delai_radiation_non_cotisation"]." an(s)<br />" : $retour.="" ;
		(!empty($data[0]["delai_radiation_non_adhesion"])) ? $retour.="-> Délai radiation non adhésion : ".$data[0]["delai_radiation_non_adhesion"]." an(s)<br />" : $retour.="" ;
		//			($data[0]["modifiable_o_n"]=='1') ? $retour.="Modifiable"."</b><br />" : $retour.="" ;
		($id_organisme_appel>0) ?	$retour.="</b>Inscriptions : <b>".$lien_inscrits."</b><br />" : null;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_type_inscription','n') : $retour.="";
		return $retour;

	}
	function descripteur_type_fonction($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		libelle
		from  type_fonction
		where id=$id_entite";
		$data = $db->getrows($sql);
		
		$href=href(dispatch_url("table.type_fonction", "edit", array (	'atkselector' => "type_fonction.id='" . $id_entite. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
	
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/function_icon.png" alt="Type de fonction" title="Type de fonction" target="_blank"></img>'." <b>".$href."</b> ";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_type_fonction','n') : null;
		return $retour;
	
	}
	

	function descripteur_type_rencontre($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		libelle,
		routine_o_n
		from  type_rencontre
		where id=$id_entite";
		$data = $db->getrows($sql);
		// iconerencontre.png
		$href=href(dispatch_url("table.type_rencontre", "edit", array (	'atkselector' => "type_rencontre.id='" . $id_entite. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
	
		$retour.='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/type_rencontre.png" alt="Type de rencontre" title="Type de rencontre" target="_blank"></img>'." <b>".$href."</b><br />";
		$retour.="</b>Routine : ";
		($data[0]["routine_o_n"]=='1') ? $retour.="<b>oui</b> " : $retour.="" ;
		($data[0]["routine_o_n"]=='0') ? $retour.="<b>non</b> " : $retour.="" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_type_rencontre','n') : $retour.="";
		return $retour;
	
	}
	function descripteur_cotisation_organisme($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();

		$sql="select
		libelle,
		id_organisme,
		annee,
		montant,
		montant_1,
		montant_2,
		montant_3
		from  organisme_cotisation
		where id=$id_entite";
		$data = $db->getrows($sql);
		$retour=$this->descripteur_organisme($data[0]["id_organisme"],'n')."<br/>";
		$href=href(dispatch_url("organisme.cotisation", "edit", array (	'atkselector' => "organisme.cotisation.id='" . $id_entite. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour.="</b>Cotisation : <b>".$href."</b><br />";
		(!empty($data[0]["annee"])) ? $retour.="</b>Année :  <b>".$data[0]["annee"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["montant"])) ? $retour.="</b>Tarif 1 :  <b>".$data[0]["montant"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["montant_1"])) ? $retour.="</b>Tarif 2 :  <b>".$data[0]["montant_1"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["montant_2"])) ? $retour.="</b>Tarif 3 :  <b>".$data[0]["montant_2"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["montant_3"])) ? $retour.="</b>Tarif 4 :  <b>".$data[0]["montant_3"]."</b><br />" : $retour.="" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_cotisation_organisme','n') : $retour.="";
		return $retour;

	}


	function descripteur_remise_banque($id_entite, $aide_o_n='o', $court='n')
	{
		$db = & atkGetDb();
		$sql="select count(distinct numero_piece) as nombre_cheques, sum(debit) as debit, sum(credit) as credit  from organisme_ligne_ecriture_comptable
		where id_remise = $id_entite";
		$data = $db->getrows($sql);
		$nombre_cheques=$data[0]["nombre_cheques"];
		$total=$data[0]["debit"]-$data[0]["credit"];
		$sql="select
		orb.id,
		orb.libelle,
		trb.libelle as libelle_type,
		oc.code, oc.id as id_compte,
		oc.libelle as libelle_compte,
		orb.id_remise_banque,
		orb.date_remise_banque,
		orb.id_remise_organisme,
		orb.id_releve,
		orb.id_document_remise,
		orb.id_compte_banque,
		orb.bordereau_remise
		from organisme_remise_banque orb
		LEFT JOIN type_remise_banque trb ON orb.id_type_remise_banque=trb.id
		LEFT JOIN organisme_compte oc ON oc.id=orb.id_compte_banque
		where orb.id=$id_entite";
		$data = $db->getrows($sql);
		$href_compte=href(dispatch_url("organisme.compte", "view", array (
				'atkfilter' => "organisme_compte.id='" . $data[0]["id_compte_banque"] . "'"
		), "dispatch.php"), $data[0]["code"]." - ".$data[0]["libelle_compte"], SESSION_NESTED);
		if ($court=='n')
		{
			//				(!empty($data[0]["libelle"])) ? $retour="<b>".$data[0]["libelle"]."(".$data[0]["id_remise_organisme"].")</b><br />" : $retour="" ;
			$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/remise-banque.png" alt="Remise en banque" title="Remise en banque" ></img>'.
					"<b> ".$data[0]["libelle"]."(".$data[0]["id_remise_organisme"].")</b><br />" ;

			$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_remise='" . $id_entite . "'"
			), "dispatch.php"), $nombre_cheques, SESSION_NESTED);
			$urlprint = href(dispatch_url("organisme.remise_banque", "imprimer", array (
					"atkselector" => "organisme_remise_banque.id='" . $id_entite . "'",
					"atkexport" => 'o',
					"id" => $id_entite
			)),
					'<img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/print.gif" alt="Imprimer la remise en banque dans une page séparée" title="Imprimer la remise en banque dans une page séparée" ></img>', SESSION_NEW,null," target=\"_blank\" ");
			//		$retour.=$url;
			(!empty($data[0]["libelle_type"])) ? $retour.="Montant : <b><font style=\"font-size:18px;\">".$total. "</font></b> euro "."</b>(<b> ".$href."</b> ".strtolower($data[0]["libelle_type"]).") ".$urlprint."<br />" : $retour.=$urlprint."<br />" ;

			//			(!empty($data[0]["code"])) ? $retour.="</b> sur le compte : <b>".$href_compte."<br />" : $retour.="" ;
			(!empty($data[0]["id_compte"])) ? $retour.=$this->descripteur_compte_comptable($data[0]["id_compte"], 'n')."</b>" : $retour.="" ;
			(!empty($data[0]["id_remise_banque"])) ? $retour.="</b>Remise banque : <b>".$data[0]["id_remise_banque"]."<br />" : $retour.="" ;
			(!empty($data[0]["date_remise_banque"])) ? $retour.="</b>le : <b>".$data[0]["date_remise_banque"]."<br />" : $retour.="" ;
			$href=href(dispatch_url("organisme.releve_banque", "view", array (
					'atkfilter' => "organisme_releve_banque.id='" . $data[0]["id_releve"] . "'"
			), "dispatch.php"), $data[0]["id_releve"], SESSION_NESTED);
			(!empty($data[0]["id_releve"])) ? $retour.="</b>Relevé : <b>".$href."<br />" : $retour.="" ;

			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=organisme_remise_banque&id='.$id_entite.'&field=bordereau_remise','Bordereau',650,650,'yes','no');
			(!empty($data[0]["bordereau_remise"])) ? $retour.='<a href="'.$popup.'"><font color="ForestGreen"><b>Bordereau</b></font><br /></a>' : $retour.='';

			/*			$href=href(dispatch_url("organisme.document", "edit", array (
				'atkselector' => "organisme_document.id='" . $data[0]["id_document_remise"]. "'"
			), "dispatch.php"), "Bordereau de remise", SESSION_NESTED);

			$retour.="Bordereau de remise : ".$this->descripteur_document("organisme",$data[0]["id_document_remise"],'n').'';
			*/
				
			(!empty($data[0]["id_document_remise"])) ? $retour.="</b>Bordereau de remise : <b>".$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_remise"])."<br />" : $retour.="" ;


		}
		else {
			$href_id=href(dispatch_url("organisme.remise_banque", "edit", array (
					'atkfilter' => "organisme_remise_banque.id='" . $data[0]["id"] . "'"
			), "dispatch.php"), $data[0]["id"], SESSION_NESTED);
			$retour.=" ".$href_id;
			(!empty($data[0]["date_remise_banque"])) ? $retour.="</b> du <b>".$data[0]["date_remise_banque"] : $retour.="" ;
			(!empty($data[0]["code"])) ? $retour.="</b> sur <b>".$href_compte."<br />" : $retour.="" ;
		}
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_remise_banque','n') : $retour.="";
		return $retour;

	}

	function descripteur_releve_banque($id_entite, $aide_o_n='o', $court='n')
	{
		$db = & atkGetDb();
		$sql="select count(id) as nombre from organisme_remise_banque
		where id_releve=$id_entite";
		$data = $db->getrows($sql);
		$nombre_remises_pointees=$data[0]["nombre"];
		$href_remises_pointees=href(dispatch_url("organisme.remise_banque", "admin", array (
				'atkfilter' => "organisme_remise_banque.id_releve='" . $id_entite . "'"
		), "dispatch.php"), $nombre_remises_pointees, SESSION_NESTED);
		$sql="select count(id) as nombre from organisme_ligne_ecriture_comptable
		where id_releve= $id_entite and id_remise is NULL";
		$data = $db->getrows($sql);
		$nombre_autres_pointees=$data[0]["nombre"];
		$href_autres_pointees=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => "organisme_ligne_ecriture_comptable.id_releve='" . $id_entite . "' and id_remise is null"
		), "dispatch.php"), $nombre_autres_pointees, SESSION_NESTED);
		$sql="select count(id) as nombre from organisme_ligne_ecriture_comptable
		where id_releve= $id_entite ";
		$data = $db->getrows($sql);
		$nombre_detail_pointees=$data[0]["nombre"];
		$href_detail_pointees=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
				'atkfilter' => "organisme_ligne_ecriture_comptable.id_releve='" . $id_entite . "' "
		), "dispatch.php"), $nombre_detail_pointees, SESSION_NESTED);

		$sql="select
		orb.id,
		orb.libelle,
		orb.id_compte_banque,
		oc.code,
		oc.libelle as libelle_compte,
		oc.id as id_compte,
		orb.id_releve_banque,
		orb.id_document_releve,
		orb.date_releve_banque,
		orb.solde_initial_releve,
		orb.total_debits_releve,
		orb.total_credits_releve,
		orb.solde_final_releve,
		orb.date_cloture_releve

		from organisme_releve_banque orb
		LEFT JOIN organisme_compte oc ON oc.id=orb.id_compte_banque

		where orb.id=$id_entite";
		$data = $db->getrows($sql);
		$datalec = $db->getrows("SELECT sum(lec.credit) as credit_banque ,
				sum(lec.debit) as debit_banque
				from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte =".$data[0]['id_compte_banque']." and lec.id_releve = $id_entite)");
		$credit_banque = $datalec[0]["credit_banque"];
		$debit_banque = $datalec[0]["debit_banque"];
		$solde=0;
		$datalec = $db->getrows("SELECT sum(lec.debit - lec.credit) as solde from organisme_ligne_ecriture_comptable lec
				where  ( lec.id_compte =". $data[0]['id_compte_banque']." and lec.id_releve is not null and lec.id_releve< $id_entite)");
		$solde = $datalec[0]["solde"];
		$datalec= $db->getrows("SELECT (debit_initial - credit_initial) as solde_initial  from organisme_compte
				where   id =". $data[0]['id_compte_banque']." ");
		$solde = $solde + $datalec[0]["solde_initial"];
		($solde=="0")?$solde="0.00": null;
		$href_compte=href(dispatch_url("organisme.compte", "view", array (
				'atkfilter' => "organisme_compte.id='" . $data[0]["id_compte_banque"] . "'"
		), "dispatch.php"), $data[0]["code"]." - ".$data[0]["libelle_compte"], SESSION_NESTED);
		if ($court=='n')
		{
			//			(!empty($data[0]["libelle"])) ? $retour="<b>".$data[0]["libelle"]." (".$data[0]["id_releve_banque"].") </b>clos le <b>".$data[0]["date_cloture_releve"]."</b><br />" : $retour="" ;
			($data[0]["date_cloture_releve"]!="") ? $clos="Clos le " : $clos="Non clos";
					$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/releve-banque.png" alt="Relevé de compte bancaire" title="Relevé de compte bancaire" ></img>'.
					"<b> ".$data[0]["libelle"]." (".$data[0]["id_releve_banque"].") </b>".$clos."<b>".$data[0]["date_cloture_releve"]."</b><br />" ;
			//			(!empty($data[0]["code"])) ? $retour.="</b>du compte : <b>".$href_compte."</b><br />" : $retour.="" ;
			(!empty($data[0]["id_compte"])) ? $retour.=$this->descripteur_compte_comptable($data[0]["id_compte"], 'n')."</b>" : $retour.="" ;


			(!empty($data[0]["id_releve_banque"])) ? $retour.="</b>Relevé banque : <b>".$data[0]["id_releve_banque"]."" : $retour.="" ;
			(!empty($data[0]["date_releve_banque"])) ? $retour.="</b> du : <b>".$data[0]["date_releve_banque"]."<br />" : $retour.="" ;
			(!empty($data[0]["id_document_releve"])) ? $retour.="</b>Document relevé : <b>".$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_releve"])."<br />" : $retour.="" ;
			/*		$href=href(dispatch_url("organisme.document", "edit", array (
				'atkselector' => "organisme_document.id='" . $data[0]["id_document_releve"]. "'"
			), "dispatch.php"), "<b>(Document relevé de banque)</b>", SESSION_NESTED);
			(!empty($data[0]["id_document_releve"])) ? $retour.=$href."<br />" : $retour.="<br />" ;
			*/
			$solde_calcule=$solde-$credit_banque+$debit_banque;
	//GG		if ((strlen($solde_calcule) - strpos($solde_calcule, ".")) >3) {
	//GG			$solde_calcule = substr($solde_calcule, 0,(strpos($solde_calcule, ".")+3) );
	//GG		}
			$retour.="<table ><tr><th style=\"width:100px;\"></th><th style=\"width:100px;\"><center>Relevé de compte</th><th style=\"width:100px;\"><center>Calculé</th></tr>";
			$retour.="<tr><td style=\"width:100px;\">Solde final</td><td style=\"width:100px;;font-size:16px\">".$this->nombre_format($data[0]["solde_final_releve"],"b",2,"n")."</td>";
			($solde_calcule!=$data[0]["solde_final_releve"])? $retour.="<td>".$this->nombre_format($solde_calcule,"b",2,"n")."</td></tr>" : $retour.="<td>".$this->nombre_format($solde_calcule,"b",2)."</td></tr>";
			$retour.="<tr><td style=\"width:100px;\">Débits</td><td style=\"width:100px;\">".$this->nombre_format($data[0]["total_debits_releve"],"b",2,"n")."</td>";
			($credit_banque!=$data[0]["total_debits_releve"])? $retour.="<td>".$this->nombre_format($credit_banque,"b",2,"n")."</td></tr>" : $retour.="<td>".$this->nombre_format($credit_banque,"b",2)."</td></tr>";
			$retour.="<tr><td style=\"width:100px;\">Crédits</td><td style=\"width:100px;\">".$this->nombre_format($data[0]["total_credits_releve"],"b",2,"n")."</td>";
			($debit_banque!=$data[0]["total_credits_releve"])? $retour.="<td>".$this->nombre_format($debit_banque,"b",2,"n")."</td></tr>" : $retour.="<td>".$this->nombre_format($debit_banque,"b",2)."</td></tr>";
			$retour.="<tr><td style=\"width:100px;\">Solde initial</td><td style=\"width:100px;font-size:16px\">".$this->nombre_format($data[0]["solde_initial_releve"],"b",2,"n")."</td>";
			($solde!=$data[0]["solde_initial_releve"])? $retour.="<td>".$this->nombre_format($solde,"b",2,"n")."</td></tr></table>" : $retour.="<td>".$this->nombre_format($solde,"b",2,"n")."</td></tr></table>";
				
		/*	 
			(!empty($data[0]["solde_initial_releve"])) ? $retour.='</b>Solde initial. <b>'.$data[0]["solde_initial_releve"].' </b>(relevé) <b>'.$solde."</b> (calculé)<br />" : $retour.="" ;
			(!empty($data[0]["total_debits_releve"])) ? $retour.='</b>Débits. <b>'.$data[0]["total_debits_releve"].' </b>(relevé) <b>'.$credit_banque."</b> (calculé)<br />" : $retour.="" ;
			(!empty($data[0]["total_credits_releve"])) ? $retour.='</b>Crédits. <b>'.$data[0]["total_credits_releve"].' </b>(relevé) <b>'.$debit_banque."</b> (calculé)<br />" : $retour.="" ;
			(!empty($data[0]["solde_final_releve"])) ? $retour.='</b>Solde final. <b>'.$data[0]["solde_final_releve"].' </b>(relevé) <b>'.$solde_calcule."</b> (calculé)<br />" : $retour.="" ;
	*/
				(!empty($href_detail_pointees)) ? $retour.="</b>Eléments pointés : <b>".$href_remises_pointees." remises, <b>".$href_autres_pointees." autres, <b>".$href_detail_pointees. " détails <br />" : $retour.="" ;
	
			}
		else {
			$href_id=href(dispatch_url("organisme.releve_banque", "edit", array (
					'atkfilter' => "organisme_releve_banque.id='" . $data[0]["id"] . "'"
			), "dispatch.php"), $data[0]["id"], SESSION_NESTED);
			$retour.=" ".$href_id;
			(!empty($data[0]["date_releve_banque"])) ? $retour.="</b> du <b>".$data[0]["date_releve_banque"] : $retour.="" ;
			(!empty($data[0]["code"])) ? $retour.="</b> de <b>".$href_compte."<br />" : $retour.="" ;
		}
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_releve_banque','n') : $retour.="";

		return $retour;

	}

	function descripteur_reglement($type='cotisation',$id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();
		if ($type=='recette')
		{
			$sql="select of.id_ecriture_recette as id_ecriture_recette, of.id_ecriture_reglement as id_ecriture_reglement , of.montant_financement as montant_versement, of.date_reglement, tr.libelle as reglement, tb.libelle as banque, of.numero_cheque
			from organisme_financement of LEFT JOIN type_reglement tr ON of.id_reglement=tr.id LEFT JOIN type_banque tb ON of.id_banque=tb.id
			Where of.id=$id_entite";
		}
		if ($type=='participant_rencontre')
		{
			$sql="select ir.id_ecriture_participation as id_ecriture_participation,ir.id_ecriture_reglement as id_ecriture_reglement ,ir.montant_versement, ir.date_reglement, tr.libelle as reglement, tb.libelle as banque, ir.numero_cheque
			from individu_rencontre ir LEFT JOIN type_reglement tr ON ir.id_reglement=tr.id LEFT JOIN type_banque tb ON ir.id_banque=tb.id
			Where ir.id=$id_entite";
		}
		if ($type=='participant_rencontre_2')
		{
			$sql="select ir.id_ecriture_participation_2 as id_ecriture_participation,ir.id_ecriture_reglement_2 as id_ecriture_reglement ,ir.montant_versement_2 as montant_versement, ir.date_reglement_2 as date_reglement, tr.libelle as reglement, tb.libelle as banque, ir.numero_cheque_2 as numero_cheque
			from individu_rencontre ir LEFT JOIN type_reglement tr ON ir.id_reglement_2=tr.id LEFT JOIN type_banque tb ON ir.id_banque_2=tb.id
			Where ir.id=$id_entite";
		}
		if ($type=='cotisation')
		{
			$sql="select ic.id_cotisation, ic.montant_versement, ic.date_reglement, tr.libelle as reglement, tb.libelle as banque, ic.numero_cheque,
			ic.id_recu_fiscal, ic.date_envoi_recu_fiscal, ic.date_envoi_timbre,oc.libelle as libelle_cotisation, oc.montant
			from individu_cotisation ic LEFT JOIN type_reglement tr ON ic.id_reglement=tr.id LEFT JOIN type_banque tb ON ic.id_banque=tb.id LEFT JOIN organisme_cotisation oc
			ON ic.id_cotisation=oc.id
			Where ic.id=$id_entite";
		}
		if ($type=='rencontre_fournisseur')
		{
			$sql="select
			rf.montant_fourniture as montant_versement,
			rf.date_reglement,
			c.libelle as nom_compte, c.code,
			tr.libelle as reglement,
			rf.numero_cheque,
				
			numero_facture ,
			id_document_facture
				
			from organisme_rencontre_fournisseur rf
			LEFT JOIN organisme_compte c ON rf.id_compte_financier=c.id
			LEFT JOIN type_reglement tr ON rf.id_reglement=tr.id
			Where rf.id=$id_entite";
		}

		$data = $db->getrows($sql);
		
		($id_entite>0 && strlen($data[0]["date_reglement"])>0 ) ? $retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/reglement.png" alt="Règlement" title="Règlement" target="_blank"></img>'.
				"</b> " : $retour="" ;
		$href=href(dispatch_url("organisme.cotisation", "view", array (	'atkselector' => "organisme_cotisation.id='" . $data[0]["id_cotisation"]. "'"
		), "dispatch.php"), $data[0]["libelle_cotisation"], SESSION_NESTED);
		(!empty($data[0]["libelle_cotisation"])) ? $retour.="<b>".$href." (".$data[0]["montant"].")</b><br />" : $retour.="" ;
		(!empty($data[0]["montant_versement"])) ? $retour.="</b><b><font style=\"font-size:18px;\">".$data[0]["montant_versement"]."</font> euro </b>" : $retour.="" ;
		(!empty($data[0]["date_reglement"])) ? $retour.="</b> le <b>".$data[0]["date_reglement"]  : $retour.="" ;
		(!empty($data[0]["reglement"])) ? $retour.='</b> <b>'.$data[0]["reglement"]." </b>" : $retour.="" ;
		(!empty($data[0]["numero_cheque"])) ? $retour.="<b>".$data[0]["numero_cheque"]."</b> " : $retour.=" " ;
		(!empty($data[0]["nom_compte"])) ? $retour.='</b> sur <b>'.$data[0]["code"].'-'.$data[0]["nom_compte"].'<br />': $retour.='';
		(!empty($data[0]["banque"])) ? $retour.="</b>Banque : <b>".$data[0]["banque"] : $retour.="" ;
				
		if (($type=='participant_rencontre' || $type=='participant_rencontre_2') && (isset ($data[0]["id_ecriture_reglement"]) || isset ($data[0]["id_ecriture_participation"]))) {
			$retour.=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_reglement'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_participation'] . "'"
			), "dispatch.php"), text(" (=> Ecritures)"), SESSION_NESTED)."<br />";
		}
			else {
				$retour.="";
			}
			
		if ($type=='recette' && (isset ($data[0]["id_ecriture_reglement"]) || isset ($data[0]["id_ecriture_recette"]))) {
				$retour.=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
						'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_reglement'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $data[0]['id_ecriture_recette'] . "'"
				), "dispatch.php"), text(" (=> Ecritures)"), SESSION_NESTED)."<br />";
			}
		else {
				$retour.="";
			}
			

		(!empty($data[0]["id_recu_fiscal"])) ? $retour.="</b><br/>Reçu fiscal : <b>".$data[0]["id_recu_fiscal"] : $retour.="" ;
		(!empty($data[0]["date_envoi_recu_fiscal"])) ? $retour.="</b>Envoyé le : <b>".$data[0]["date_envoi_recu_fiscal"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_envoi_timbre"])) ? $retour.="</b><br/>Timbre envoyé le : <b>".$data[0]["date_envoi_timbre"]."<br />" : $retour.="" ;

		(!empty($data[0]["numero_facture"]) || !empty($data[0]["id_document_facture"])) ? $retour.='</b><br/>Facture : <b>' : $retour.='';
		(!empty($data[0]["numero_facture"])) ? $retour.= $data[0]["numero_facture"]." " : $retour.="" ;
		(!empty($data[0]["id_document_facture"])) ? $retour.=$this->descripteur_document_sans_lien("organisme",$data[0]["id_document_facture"]).'' : $retour.="" ;
		(!empty($data[0]["numero_facture"]) || !empty($data[0]["id_document_facture"])) ?  $retour.='<br />' : $retour.='';
		/*
		 * ($id_entite>0 && strlen($data[0]["date_reglement"])>0 ) ? $retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/reglement.png" alt="Règlement" title="Règlement" target="_blank"></img>'.
				"</b> " : $retour="" ;
		$href=href(dispatch_url("organisme.cotisation", "view", array (	'atkselector' => "organisme_cotisation.id='" . $data[0]["id_cotisation"]. "'"
		), "dispatch.php"), $data[0]["libelle_cotisation"], SESSION_NESTED);
		(!empty($data[0]["libelle_cotisation"])) ? $retour.="<b>".$href." (".$data[0]["montant"].")</b><br />" : $retour.="" ;
		(!empty($data[0]["montant_versement"])) ? $retour.="</b>Montant : <b>".$data[0]["montant_versement"]."</b><br />" : $retour.="" ;
		(!empty($data[0]["date_reglement"])) ? $retour.="</b>Réglé le : <b>".$data[0]["date_reglement"]."<br />" : $retour.="" ;
		(!empty($data[0]["reglement"])) ? $retour.='</b>Mode : <b>'.$data[0]["reglement"]." </b>" : $retour.="" ;
		(!empty($data[0]["numero_cheque"])) ? $retour.="<b>".$data[0]["numero_cheque"]."</b><br />" : $retour.="<br />" ;
		(!empty($data[0]["nom_compte"])) ? $retour.='</b>Compte : <b>'.$data[0]["code"].'-'.$data[0]["nom_compte"].'<br />': $retour.='';
		(!empty($data[0]["banque"])) ? $retour.="</b>Banque : <b>".$data[0]["banque"]."<br />" : $retour.="" ;

		(!empty($data[0]["id_recu_fiscal"])) ? $retour.="</b>Reçu fiscal : <b>".$data[0]["id_recu_fiscal"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_envoi_recu_fiscal"])) ? $retour.="</b>Envoyé le : <b>".$data[0]["date_envoi_recu_fiscal"]."<br />" : $retour.="" ;
		(!empty($data[0]["date_envoi_timbre"])) ? $retour.="</b>Timbre envoyé le : <b>".$data[0]["date_envoi_timbre"]."<br />" : $retour.="" ;

		(!empty($data[0]["numero_facture"]) || !empty($data[0]["id_document_facture"])) ? $retour.='</b>Facture : <b>' : $retour.='';
		(!empty($data[0]["numero_facture"])) ? $retour.= $data[0]["numero_facture"]." " : $retour.="" ;
		(!empty($data[0]["id_document_facture"])) ? $retour.=$this->descripteur_document("organisme",$data[0]["id_document_facture"],'n').'' : $retour.="" ;
		(!empty($data[0]["numero_facture"]) || !empty($data[0]["id_document_facture"])) ?  $retour.='<br />' : $retour.='';
		 */

		($aide_o_n=='o'  ) ? $retour.=$this->descripteur_aide('Descripteur_reglement','n') : $retour.="";
		return $retour;

	}
	function descripteur_organisme($id_organisme,$qr_o_n='n',$aide_o_n='o',$size=50, $origine_appel='commune', $sans_lien_o_n='n')

	{
		if (!($id_organisme>0)) return false ;
		$db = & atkGetDb();
		global $g_sessionManager;
		$g_icones_detaillees_o_n = $g_sessionManager->getValue("icones_detaillees_o_n", "globals");
		$pos=strpos($id_organisme, " and ");
		if ($pos>0) {
			$id_organisme=substr($id_organisme, 0,$pos);
		}
		$toutes_icones='non';
		if ($g_icones_detaillees_o_n==1 || $origine_appel=='menu' ||  $origine_appel=='popup') {
			$toutes_icones='oui';
		}
		$sql="select nom , sigle, siret, courriel, site_internet, calendrier, calendrier_contacts_url, calendrier_contacts_refresh,
		calendrier_rencontres_url, calendrier_rencontres_refresh, telephone  from organisme where id=$id_organisme";
		//				$this->p($id_organisme);
		$data = $db->getrows($sql);
		$nom_organisme = $data[0]["nom"];
		$courriel_organisme = $data[0]["courriel"];
		$sigle_organisme = $data[0]["sigle"];
		$siret_organisme = $data[0]["siret"];
		$calendrier_organisme = $data[0]["calendrier"];
		$calendrier_contacts_url_organisme = $data[0]["calendrier_contacts_url"];
		$calendrier_contacts_refresh_organisme = $data[0]["calendrier_contacts_refresh"];
		$calendrier_rencontres_url_organisme = $data[0]["calendrier_rencontres_url"];
		$calendrier_rencontres_refresh_organisme = $data[0]["calendrier_rencontres_refresh"];
		$site_internet_organisme = $data[0]["site_internet"];
		$telephone_organisme = $data[0]["telephone"];

		$adresse_organisme=$this->descripteur_adresse_organisme($id_organisme,'n','n');
		$qr_adresse_organisme=$this->descripteur_adresse_organisme($id_organisme,'o','n');


		$data = $db->getrows("SELECT od.nom_domaine as domaine from organisme_domaine od
				where od.id_organisme=$id_organisme and od.google_apps_o_n='1'
				");
		$google_apps='';
		if (!empty($data[0]["domaine"] ))
		{
			//			$google_apps='http://docs.google.com/a/'.$data[0]["domaine"].'#';
			$google_apps='http://docs.google.com/a/'.$data[0]["domaine"];
		}

		$popup=atkPopup(atkconfig("atkroot").'atk/popups/qrpopup.inc','type=organisme&id='.$id_organisme,'Coordonnées organisme',700,300,'yes','no');
		$descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/organisme.png" alt="Coordonnées organisme" title="Coordonnées organisme" target="_blank"></img></a>'.'' ;

		//				$descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/organisme.png" alt="Organisme" title="Organisme" target="_blank"></img>';
	if ($sans_lien_o_n=='n')
	{	$descripteur.=" ".atkHref(		dispatch_url("organisme.organisme", "edit", array ("atkselector" => "organisme.id='" . $id_organisme . "'" )),
				'<b>'.$nom_organisme.'</b>',SESSION_NESTED, false, 'target="main"')." ";
	}
	else 
	{
		$descripteur.=" ".'<b>'.$nom_organisme.'</b>';
	}
		if ($toutes_icones!='oui' && $site_internet_organisme!="")
		{
			$href=" ".$site_internet_organisme."";
			$descripteur.=' <a href="'.$href.'" target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/blog.png" alt="Accès à : '.$site_internet_organisme.'"
					title="Accès à : '.$site_internet_organisme.'" ></img></a>';

			//			$descripteur.='<br /> '.$site_internet_organisme;
		}
		$href="http://www.google.fr/search?q=".$nom_organisme."&ie=utf-8&oe=utf-8&aq=t&";
			$descripteur.='<a href="'.$href.'"  target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/notoriete.png" alt="Chercher avec Google"
					title="Chercher avec Google" ></img></a>';


		$coordonnees='<b>'.$nom_organisme.'</b>';
		(!empty($sigle_organisme)) ? ($coordonnees.='<br >'.$sigle_organisme) : null;
		(!empty($siret_organisme)) ? ($coordonnees.='<br >Siret : '.$siret_organisme) : null;


		($aide_o_n=='o') ? $descripteur.=' '.$this->descripteur_aide('Descripteur_organisme','n').'' : $descripteur=$descripteur.'';
		if ($toutes_icones=='oui') {
			$descripteur.='<br />';
		}
		$qr_nom_organisme=$nom_organisme;
		//			(!empty($sigle_organisme)) ? $descripteur.=$sigle_organisme.'<br />' :  $descripteur.='';

		if (!empty($qr_adresse_organisme))
		{
			if ($toutes_icones=='oui')
			{
				$descripteur.=$adresse_organisme;
				$descripteur.=atkHref(dispatch_url("organisme.organisme", "googlemap", array ("id" => "$id_organisme"	)),
						'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/geolocalisation.png" alt="Où est-ce ? : '.$qr_organisme.'"
						title="Où est-ce ? : '.$qr_organisme.'"  ></img>',SESSION_NESTED, false, 'target="_blank"');
				$href="http:./dispatch.php?atknodetype=organisme.v_organisme_lieu&atkaction=document&atkselector=organisme.id=".$id_organisme."&id=&atkfilter=v_organisme_lieu.id=".$id_organisme."&atkdoctpl=enveloppe_organisme.odt&atkdoctpl_prefix_id=1&atkcode=2&atklevel=-1&atkprevlevel=0&";
				$descripteur.='<a href="'.$href.'"  target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/courrier.png" alt="Enveloppe : '.$qr_organisme.'"
						title="Enveloppe : '.$qr_organisme.'" ></img></a>';
			}
			$coordonnees.='<br />'.$this->descripteur_adresse_organisme($id_organisme,'c','n');
		}
			
			
		if (!empty($telephone_organisme))
		{
			if ($toutes_icones=='oui')
			{
				$href=" tel:".$telephone_organisme;
				$descripteur.='<a href="'.$href.'" target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/telephonefixe.png" alt="Appeler le : '.$telephone_organisme.'"
						title="Appeler le : '.$telephone_organisme.'" ></img></a>';
			}
			$coordonnees.='<br />'.$telephone_organisme;
		}
		if (!empty($courriel_organisme))
		{
			if ($toutes_icones=='oui')
			{
				$href="mailto:".$courriel_organisme."";
				$descripteur.='<a href="'.$href.'" target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/courriel.png" alt="Courriel à : '.$courriel_organisme.'"
						title="Courriel à : '.$courriel_organisme.'" ></img></a>';
			}
			$coordonnees.='<br />'.$courriel_organisme;
		}
		if (!empty($site_internet_organisme))
		{
			if ($toutes_icones=='oui')
			{
				$href=" ".$site_internet_organisme."";
				$descripteur.='<a href="'.$href.'" target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/blog.png" alt="Accès à : '.$site_internet_organisme.'"
						title="Accès à : '.$site_internet_organisme.'" ></img></a>';
			}
			$coordonnees.='<br />'.$site_internet_organisme;
		}
		if (!empty ($calendrier_organisme)) {
			if ($toutes_icones=='oui')
			{
				$href=" ".$calendrier_organisme;
				$descripteur.='<a href="'.$href.'" target="_blank" >'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/calendrier.png" alt="Calendrier : '.$calendrier_organisme.'"
						title="Calendrier : '.$calendrier_organisme.'" ></img></a>';
			}
		}
		if (!empty ($google_apps)) {
			if ($toutes_icones=='oui')
			{
				$href=" ".$google_apps;
				$descripteur.='<a href="'.$href.'" target="_blank" ><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/docs.png" alt="Google documents :'.$google_apps.'"
						title="Google documents :'.$google_apps.'" ></img></a>';
			}
		}
		if ($toutes_icones=='oui')
		{

			
			$href="http:./dispatch.php?atknodetype=organisme.organisme&atkaction=geolocalisation_inscrits&type=organisme&id=".$id_organisme."";
			$descripteur.='<a href="'.$href.'"  target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/app-map-icon.png" alt="Qui y-at\'il dans les parages ?"
				title="Y a-t\'il quelqu\'un dans le coin ?" ></img></a>';
		}

	


		$qr_organisme="MECARD:N:".$qr_nom_organisme.";TEL:".$telephone_organisme.";URL:".$site_internet_organisme.
		";EMAIL:".$courriel_organisme.";ADR:".$qr_adresse_organisme.";;";
		$qr_organisme=str_replace(' ', '+', $qr_organisme);
		$qr_organisme=str_replace("'", "/'", $qr_organisme);
		$qr_organisme=utf8_encode($qr_organisme);
		$qr_organisme = href("index.php", '<img src="http://chart.apis.google.com/chart?cht=qr&chs=150x150&chl='.$qr_organisme.'" class="gwt-Image" style="">', SESSION_DEFAULT, false, 'target="_top"');
		//				if ($size>0) $descripteur=$this->decoupe_affichage_colonne($descripteur, $size);
		//				if (empty($size)) $descripteur=$this->decoupe_affichage_colonne($descripteur, 50);
			
		($qr_o_n=='o')? $retour=$qr_organisme : $retour.='';
		($qr_o_n=='n' || $qr_o_n=='')? $retour=$descripteur : $retour.='';
		($qr_o_n=='c')? $retour=$coordonnees.'<br /><br />'.$qr_organisme : $retour.='';

		return $retour;

	}
	function descripteur_organisme_immatriculation($id_entite, $aide_o_n='o')
	{
		$db = & atkGetDb();

		$sql="select
		id,
		id_organisme,
		immatriculation,
		libelle,
		url
		from organisme_immatriculation
		where organisme_immatriculation.id=$id_entite";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.organisme_immatriculation", "edit", array (	'atkselector' => "organisme_immatriculation.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/immatriculation.png" alt="Immatriculation" title="Immatriculation" target="_blank"></img>'.
				"<b>".$href."</b> <br />" ;
		(!empty($data[0]["immatriculation"])) ? $retour.="Immatriculation : <b>".$data[0]["immatriculation"]."</b><br />" : $retour.="" ;
		$url=$data[0]["url"];
		(!empty($data[0]["url"])) ? $retour.="Url : <b>"."<a href=\"$url\" target=\"_blank\">".$url."</a></b><br />" : $retour.="" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_organisme_immatriculation','n')."<br />" : $retour.="<br />";

		return $retour;

	}
	function descripteur_individu_utilisateur($id_utilisateur,$sans_lien_o_n='n')
	{
		$db = & atkGetDb();
		$data = $db->getrows("select i.id from individu i, app_utilisateur au 
				where au.id=$id_utilisateur and au.id_individu=i.id ");
		$id_individu=$data[0]["id"];
		return $this->descripteur_individu($id_individu,'n','n',$size=100,"utilisateur", 'n', 'n',$sans_lien_o_n);
	}

	function descripteur_individu($id_individu,$qr_o_n='n',$aide_o_n='o',$size=50,$origine_appel='commune', $long_o_n='o', $licence_golf_o_n='n', $sans_lien_o_n='n', $lat="", $long="", $sans_nom_o_n='n')
	{
		if (!($id_individu>0)) return false ;
		global $g_sessionManager;
		$g_icones_detaillees_o_n = $g_sessionManager->getValue("icones_detaillees_o_n", "globals");
		$toutes_icones='non';
		$pos=strpos($id_individu, " and ");
		if ($pos>0) {
			$id_individu=substr($id_individu, 0,$pos);
		}
		if ($g_icones_detaillees_o_n==1 || $origine_appel=='menu' ||  $origine_appel=='popup') {
			$toutes_icones='oui';
		}
		if ($long_o_n=='n') {
			$toutes_icones='non';
		}
		$db = & atkGetDb();
		$data = $db->getrows("select golf_licence, golf_index, nom, prenom,sexe,
				id_document_portrait, id_document_signature,courriel, calendrier, calendrier_contacts_url, calendrier_contacts_refresh,
				calendrier_rencontres_url, calendrier_rencontres_refresh, telephone_fixe, telephone_mobile, date_naissance,site_internet, date_deces  from individu where id=$id_individu");
		$nomindividu=$data[0]["nom"];
		$golflicence=$data[0]["golf_licence"];
		$golfindex=$data[0]["golf_index"];
		$prenomindividu=$data[0]["prenom"];
		$calendrier_individu = $data[0]["calendrier"];
		$calendrier_contacts_url_individu = $data[0]["calendrier_contacts_url"];
		$calendrier_contacts_refresh_individu = $data[0]["calendrier_contacts_refresh"];
		$calendrier_rencontres_url_individu = $data[0]["calendrier_rencontres_url"];
		$calendrier_rencontres_refresh_individu = $data[0]["calendrier_rencontres_refresh"];
		$date_deces=$data[0]["date_deces"];
		
		$qr_nom_individu=$data[0]["nom"] . ' , '. $data[0]["prenom"];
		$qr_anniversaire=substr($data[0]["date_naissance"], 0,10);
		$qr_anniversaire_individu=str_replace('-', '', $qr_anniversaire);

		$nom_individu="";

		$nom_individu = $nomindividu ;
		if (!empty($prenomindividu)) $nom_individu .= " ".$prenomindividu ;
		$courriel_individu = $data[0]["courriel"];
		$site_internet_individu = $data[0]["site_internet"];
		$telephone_fixe_individu = $data[0]["telephone_fixe"];
		$telephone_mobile_individu = $data[0]["telephone_mobile"];
		if ($long_o_n=='o')
		{
			$adresse_individu=$this->descripteur_adresse_individu($id_individu,'n','n');
			$qr_adresse_individu=$this->descripteur_adresse_individu($id_individu,'o','n');
		}
		($data[0]["sexe"]=='F') ? $icon='individu_elle.png' : $icon='individu.png';
		
		

		$popup=atkPopup(atkconfig("atkroot").'atk/popups/qrpopup.inc','type=individu&id='.$id_individu,'Coordonnées de '.$nom_individu,700,350,'yes','no');
		$descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icon.'" alt="Coordonnées de '.$nom_individu.'" title="Coordonnées de '.$nom_individu.'" target="_blank"></img></a>'.'' ;
		($date_deces!="") ? $descripteur.=" (".$date_deces.") " : null;
		if ($sans_nom_o_n=='o')
		{}
		else 
		{
		if ($sans_lien_o_n=='n')
		{$descripteur.=" ".atkHref(		dispatch_url("individu.individu", "edit", array ("atkselector" => "individu.id='" . $id_individu . "'" )),
				'<b>'.$nom_individu.'</b>',
				SESSION_NESTED,
				false,
				'target="main"');}
		else {
			$descripteur.='<b>'.$nom_individu.'</b>';
		}
		}
		$coordonnees='<b>'.$nom_individu.'</b><br />';
		($aide_o_n=='o') ? $descripteur.=' '.$this->descripteur_aide('Descripteur_individu','n').'' : $descripteur=$descripteur.'';
		if ($long_o_n=='o')
		{
			if ($toutes_icones=='oui') {
				$descripteur.='<br />';
			}
			if (!empty($qr_adresse_individu))
			{
				if ($toutes_icones=='oui')
				{
					$descripteur.=$adresse_individu;
					$descripteur.=atkHref(		dispatch_url("individu.individu", "googlemap", array ("id" => "$id_individu"	)),
							'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/geolocalisation.png" alt="Où est-ce ? : '.$qr_adresse_individu.'"
							title="Où est-ce ? : '.$qr_adresse_individu.'"  ></img>',SESSION_NESTED, false,
							'target="_blank"');

					/*		 $href=dispatch_url("individu.individu", "googlemap", array ("id" => "$id_individu"	));
					 $descripteur.='<a href="'.$href.'">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/geolocalisation.png" alt="Où est-ce ? : '.$qr_adresse_individu.'"
					title="Où est-ce ? : '.$qr_adresse_individu.'"  ></img></a>';
					*/
					$href="http:./dispatch.php?atknodetype=individu.v_individu_lieu&atkaction=document&atkselector=individu.id=".$id_individu."&id=&atkfilter=v_individu_lieu.id=".$id_individu."&atkdoctpl=enveloppe_individu.odt&atkdoctpl_prefix_id=0&atkcode=2&atklevel=-1&atkprevlevel=0&".
							' target="_blank"';
					$descripteur.='<a href="'.$href.'">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/courrier.png" alt="Enveloppe : '.$qr_adresse_individu.'"
							title="Enveloppe : '.$qr_adresse_individu.'" ></img></a>';
					($lat!="" && $long!="") ? $descripteur.=$this->descripteur_itineraire_individu($id_individu, $lat, $long) : null;
				}
				else {
					$descripteur.="<br />".$qr_adresse_individu;
				}
				$coordonnees.=$this->descripteur_adresse_individu($id_individu,'c','n').'<br />';
			}
			if (!empty($telephone_fixe_individu))
			{
				if ($toutes_icones=='oui')
				{
					$href=" tel:".$telephone_fixe_individu;
					$descripteur.='<a href="'.$href.'">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/telephonefixe.png" alt="Appeler le : '.$telephone_fixe_individu.'"
							title="Appeler le : '.$telephone_fixe_individu.'" ></img></a>';
				}
				$coordonnees.=$telephone_fixe_individu.'<br />';
			}
			if (!empty($telephone_mobile_individu))
			{
				if ($toutes_icones=='oui')
				{
					$href=" tel:".$telephone_mobile_individu;
					$descripteur.='<a href="'.$href.'">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/telephonemobile.png" alt="Appeler le : '.$telephone_mobile_individu.'"
							title="Appeler le : '.$telephone_mobile_individu.'" ></img></a>';
				}
				$coordonnees.=$telephone_mobile_individu.'<br />';
			}
			if (!empty($courriel_individu))
			{
				if ($toutes_icones=='oui')
				{
					$href="mailto:".$courriel_individu."";
					$descripteur.='<a href="'.$href.'">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/courriel.png" alt="Courriel à : '.$courriel_individu.'"
							title="Courriel à : '.$courriel_individu.'" ></img></a>';
				}
				$coordonnees.=$courriel_individu.'<br />';
			}

			if (!empty($site_internet_individu))
			{
				if ($toutes_icones=='oui')
				{
					$href=" ".$site_internet_individu."";
					$descripteur.='<a href="'.$href.'"  target="_blank" >'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/blog.png" alt="Accès à : '.$site_internet_individu.'"
							title="Accès à : '.$site_internet_individu.'" ></img></a>';
				}
				$coordonnees.=$site_internet_individu.'<br />';
			}
			if (!empty ($calendrier_individu)) {
				if ($toutes_icones=='oui')
				{
					$href=" ".$calendrier_individu;
					$descripteur.='<a href="'.$href.'"  target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/calendrier.png" alt="Calendrier : '.$calendrier_individu.'"
							title="Calendrier : '.$calendrier_individu.'" ></img></a>';
				}
			}
			
		
			if ($toutes_icones=='oui' )
			{
			

			}
				$href="http://www.google.fr/search?q=".$nom_individu."&ie=utf-8&oe=utf-8&aq=t&";
				$descripteur.='<a href="'.$href.'"  target="_blank">'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/notoriete.png" alt="Chercher avec Google"
						title="Chercher avec Google" ></img></a>';

			$qr_individu="MECARD:N:".$qr_nom_individu.";TEL:".$telephone_fixe_individu.";TEL:".$telephone_mobile_individu.";BDAY:".$qr_anniversaire_individu.";URL:".$site_internet_individu.
			";EMAIL:".$courriel_individu.";ADR:".$qr_adresse_individu.";;";
			$qr_individu=str_replace(' ', '+', $qr_individu);
			$qr_individu=str_replace("'", "/'", $qr_individu);
			$qr_individu=utf8_encode($qr_individu);
			$qr_individu = href("index.php", '<img src="http://chart.apis.google.com/chart?cht=qr&chs=150x150&chl='.$qr_individu.'" class="gwt-Image" style="">', SESSION_DEFAULT, false, 'target="_top"');



			//				http://www.wikistoma.org/association/dispatch.php?atknodetype=individu.individu&atkaction=fiche&id=104&atklevel=-1&atkprevlevel=0&
			global $g_sessionManager;
			$g_acces_restreint_o_n=$g_sessionManager->getValue("acces_restreint_o_n", "globals");
			if ($toutes_icones=='oui' && $g_acces_restreint_o_n="0")
			{
				$popup=atkPopup(atkconfig("atkroot").'dispatch.php','atknodetype=individu.individu&atkaction=fiche&id='.$id_individu.'&atklevel=-1&atkprevlevel=0&','Récapitulatif individu',400,250,'yes','no');
				$descripteur.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/fiche.png" alt="Récapitulatif"
						title="Récapitulatif" ></img></a>' ;
			}

			if ($size>0) $descripteur=$this->decoupe_affichage_colonne($descripteur, $size);
			if (empty($size)) $descripteur=$this->decoupe_affichage_colonne($descripteur, 50);

			($qr_o_n=='o')? $retour=$qr_individu : $retour.='';
			($qr_o_n=='n' || $qr_o_n=='' )? $retour=$descripteur : $retour.='';
			($qr_o_n=='c')? $retour=$coordonnees.'<br /><br />'.$qr_individu : $retour.='';
		}
		else
		{
			$retour=$descripteur;
		}
		($licence_golf_o_n=='o') ? $retour.="</b><br/> (Licence golf : <b>".$golflicence. "</b>. Index : <b>".$golfindex. "</b>)" : null;
			
		return $retour;
	}

	function descripteur_biodiversite_protection_texte($cd_protection,$aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="SELECT
				type_liste,valide_o_n,article,intitule,arrete,niveau,ss_niveau_1,cd_arrete,url,date_arrete,url_inpn
				FROM biodiversite_protection
				where cd_protection='".$cd_protection ."'
						";
		$dat = $db->getrows($sql);
		if ($dat[0]["valide_o_n"]!=1)
		{
			$validite='(<s>Valide</s>)';
		}
		else {
			$validite='(Valide)';
		}

		$href=atkHref(dispatch_url("biodiversite.protection", "edit", array ("atkselector" => "biodiversite_protection.cd_protection='" . $cd_protection . "'" )),
				$dat[0]["intitule"],SESSION_NESTED, false, 'target="main"') ;
		(!empty($dat[0]["intitule"])) ? $retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/protection.png" alt="Protection" title="Protection" target="_blank"></img>'.
				"<b>".$href."</b>" :  $retour="" ;
		$retour.=' '.$this->descripteur_aide('Descripteur_biodiversite_protection_texte','n')."<br />";
		$retour.="(".$dat[0]["type_liste"].")<br />" ;

		//		$retour="Type : <b>".ucfirst($dat[0]["type_liste"]).$validite.'</b><br />';
		//			$retour.="Intitulé : <b>".$dat[0]["intitule"].'</b><br />';
		(!empty($dat[0]["article"])) ? $retour.="Article : <b>".$dat[0]["article"].'</b><br />' :  $retour.="" ;
		(!empty($dat[0]["date_arrete"])) ? $retour.="Date : <b>".$dat[0]["date_arrete"].'</b><br />' :  $retour.="" ;
		($dat[0]["arrete"]=="")? $r=$dat[0]["url"] : $r=$dat[0]["arrete"] ;
		if (strlen($dat[0]["url"])>0)
		{
			$hrefurl='<a href="'.$dat[0]["url"].'">'.$r.'</a> ';
		}
		else
		{$hrefurl=$dat[0]["arrete"];
		}

		if (strlen($dat[0]["url_inpn"])>0)
		{
			$hrefurlinpn=' / <a href="'.$dat[0]["url_inpn"].'">Liste INPN</a> ';
		}
		else
		{$hrefurlinpn="";
		}

		($hrefurl=='' && $hrefurlinpn=='') ? $retour.="" : $retour.="Arrêté : <b>".$hrefurl.$hrefurlinpn.'</b><br />' ;
		$hrefprotection=dispatch_url("biodiversite.protection", "edit", array (
				"atkselector" => "cd_protection='" . $cd_protection . "'"
		));
		(!empty($dat[0]["$cd_protection"])) ?	$retour.="Cd_protection : <b>".'<a href="'.$hrefprotection.'">'.$cd_protection.'</a></b><br />' :  $retour.="" ;
		(!empty($dat[0]["niveau"])) ?		$retour.="Niveau : <b>".$dat[0]["niveau"].'</b><br />' :  $retour.="" ;
		(!empty($dat[0]["ss_niveau_1"])) ?	$retour.="Département(s) : <b>".$dat[0]["ss_niveau_1"].'</b><br />' :  $retour.="" ;
		$sql="SELECT count(id) as nombre from biodiversite_protection_taxinomie where cd_protection='".$cd_protection."'";
		$datanombre = $db->getrows($sql);
		$nombretaxons=$datanombre[0]["nombre"];
		if ($nombretaxons > 0) {
			$hrefnombretaxons=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
					'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $cd_protection . "'"
			), "dispatch.php"),$nombretaxons, SESSION_NESTED);
		}

		/*		$sql="SELECT count(id) as nombre from biodiversite_protection_taxinomie where cd_protection='".$cd_protection."'
		 and biodiversite_protection_taxinomie.cd_ref  in
		(SELECT cd_ref FROM biodiversite_protection_taxinomie WHERE cd_protection='".$cd_protection."'
				and NOT EXISTS (  SELECT cd_ref FROM biodiversite_taxinomie
					 WHERE biodiversite_protection_taxinomie.cd_ref = biodiversite_taxinomie.cd_ref 			)) ";
		*/
		$sql="SELECT count(id) as nombre from biodiversite_protection_taxinomie where cd_protection='".$cd_protection."'
				and biodiversite_protection_taxinomie.cd_ref='99999999' ";
		$datanombre = $db->getrows($sql);
		$nombretaxonsnonrepertories=$datanombre[0]["nombre"];
		if ($nombretaxonsnonrepertories > 0) {
			/*		$hrefnombretaxonsnonrepertories=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
			 'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $cd_protection . "' and
					biodiversite_protection_taxinomie.cd_ref  in (SELECT cd_ref
						 FROM biodiversite_protection_taxinomie WHERE cd_protection='" . $cd_protection . "' and NOT EXISTS (
						 		SELECT cd_ref FROM biodiversite_taxinomie
						 		WHERE biodiversite_protection_taxinomie.cd_ref = biodiversite_taxinomie.cd_ref 		  ))	"
			), "dispatch.php"), $nombretaxonsnonrepertories, SESSION_NESTED);
			*/
			$hrefnombretaxonsnonrepertories=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
					'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $cd_protection . "' and
					biodiversite_protection_taxinomie.cd_ref='99999999'	"
			), "dispatch.php"), $nombretaxonsnonrepertories, SESSION_NESTED);
		}

		$sql="select od.id as id_detail
				from
				biodiversite_protection bp,	biodiversite_protection_taxinomie pt,	biodiversite_observation_detail od,	biodiversite_taxinomie t,	biodiversite_observation o
				where
				pt.cd_protection='".$cd_protection."' and bp.cd_protection=pt.cd_protection	and pt.cd_ref=t.cd_nom	and t.id=od.id_taxinomie	and od.id_observation=o.id
						and (
						bp.ss_niveau_1 like concat("."'%#'".",o.code_departement_protection,"."'#%'"." )
								or
								bp.ss_niveau_1 is null)
								";
		$data= $db->getrows($sql);
		$nombre_taxons_observes=count($data);

		if ($nombre_taxons_observes > 0) {
			$in='(';
			for ($i = 0; $i < count($data); $i++) {
				$in.=$data[$i]["id_detail"].',';
			}
			$in=substr($in,0,strlen($in)-1).')';
			$hrefnombre_taxons_observes= href(dispatch_url("biodiversite.observation_detail", "admin", array (
					'atkfilter' => " biodiversite_observation_detail.id in $in "
			), "dispatch.php"),'<b>'. $nombre_taxons_observes.'</b>', SESSION_NESTED);

				
		}


		$retour.="Taxons(<b>".$hrefnombretaxons."</b>)/Non-répertoriés(<b>".$hrefnombretaxonsnonrepertories."</b>)/Observations(<b>".$hrefnombre_taxons_observes."</b>) ";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_biodiversite_protection_texte','n') : $retour.="";

		return $this->decoupe_affichage_colonne($retour,atkconfig("decoupe_colonne"));
	}
	function descripteur_biodiversite_protection($id_taxinomie,$id_observation,$details_o_n='détails',  $type='protection', $destination='affichage', $cd_ref, $departement_observation,$aide_o_n='o')
	{
		//				if ($details_o_n=='détails' && $destination=='rapport') return array();
		//		if (($id_observation=='' || $id_taxinomie=='' ) and $details_o_n=='détails') return;
		if ($id_taxinomie==''  and $details_o_n=='nombre') return;
		if ($id_observation==''  and $details_o_n=='observation') return;
		$db = &atkGetDb();
		$sql='';
		$select_nombre_affichage_taxinomie=" SELECT distinct
				bp.id  as id_protection , bp.ss_niveau_1 as departements ";
		$select_nombre_affichage_observation=" SELECT distinct
				bp.id  as id_protection, bp.ss_niveau_1 as departements  ";
		$select_details_affichage=" SELECT distinct
				bp.id as id_protection,
				bp.cd_protection as cd_protection,
				bp.ss_niveau_1 as departements,
				bp.intitule as intitule,
				bp.article as article,
				bp.url as url,
				bp.date_arrete as an,
				pt.statut_liste_rouge as statut ";
		$select_details_rapport=" SELECT distinct
				bp.id as id_protection
				, bp.type_liste as type_liste
				, bp.cd_protection as cd_protection
				, bp.url_inpn as url_inpn
				, bp.url as url
				, bp.ss_niveau_1 as departements
				, bp.intitule as intitule
				, bp.article as article
				, bp.date_arrete as an
				, pt.statut_liste_rouge as statut
			 ";
		$select_observation_affichage=" SELECT distinct
				t.id as id_taxinomie,
				bp.id as id_protection,
				bp.cd_protection as cd_protection,

				bp.ss_niveau_1 as departements,
				bp.intitule as intitule,
				bp.article as article,
				bp.url as url,
				bp.date_arrete as an,
				pt.statut_liste_rouge as statut ";

		$condition_protection=	" bp.type_liste='protection' ";
		$condition_liste_rouge=	" bp.type_liste='liste rouge' ";
		$condition_espece_determinante=	" bp.type_liste='espèce déterminante' ";
		$condition_validite_protection=" and bp.valide_o_n='1' ";
		$from_observation_affichage=" biodiversite_protection bp,
				biodiversite_protection_taxinomie pt,
				biodiversite_observation o,
				biodiversite_observation_detail od,
				biodiversite_taxinomie t ";
		$from_nombre_affichage_observation=" biodiversite_protection bp,
				biodiversite_protection_taxinomie pt";
		$from_nombre_affichage_taxinomie="biodiversite_protection bp,
				biodiversite_protection_taxinomie pt";
		$from_details_rapport=" biodiversite_protection bp,
				biodiversite_protection_taxinomie pt";
		$from_details_affichage=" biodiversite_protection bp,
				biodiversite_protection_taxinomie pt ";

		// construction sql
		if ($details_o_n=='observation' && $destination=='affichage') $sql.=$select_observation_affichage;
		if ($details_o_n=='détails' && $destination=='rapport') $sql.=$select_details_rapport;
		if ($details_o_n=='détails' && $destination=='affichage') $sql.=$select_details_affichage;
		if ($details_o_n=='nombre' && $id_observation!="" && $destination=='affichage') $sql.=$select_nombre_affichage_observation;
		if ($details_o_n=='nombre' && $id_observation=="" && $destination=='affichage') $sql.=$select_nombre_affichage_taxinomie;

		$sql.=" from ";
		if ($details_o_n=='observation' && $destination=='affichage') $sql.=$from_observation_affichage;
		if ($details_o_n=='détails' && $destination=='rapport') $sql.=$from_details_rapport;
		if ($details_o_n=='détails' && $destination=='affichage') $sql.=$from_details_affichage;
		if ($details_o_n=='nombre' && $id_observation!="" && $destination=='affichage') $sql.=$from_nombre_affichage_observation;
		if ($details_o_n=='nombre' && $id_observation=="" && $destination=='affichage') $sql.=$from_nombre_affichage_taxinomie;

		$sql.=" where ";
		if ($details_o_n=='observation' && $destination=='affichage') $sql.=" t.id=od.id_taxinomie and
		pt.cd_ref=t.cd_nom
		and o.id=od.id_observation  and o.id= $id_observation ";
		if ($details_o_n=='détails' && $destination=='rapport') $sql.=" pt.cd_ref='$cd_ref'";
		if ($details_o_n=='détails' && $destination=='affichage') $sql.=" pt.cd_ref='$cd_ref' ";
		if ($details_o_n=='nombre' && $id_observation!="" && $destination=='affichage') $sql.=" pt.cd_ref='$cd_ref'";
		if ($details_o_n=='nombre' && $id_observation=="" && $destination=='affichage') $sql.=" pt.cd_ref='$cd_ref'";
		$sql.=" and pt.cd_protection=bp.cd_protection ";

		if ($type=='tout') $sql.=" ";
		if ($type=='protection') $sql.=" and ".$condition_protection;
		if ($type=='liste_rouge') $sql.=" and ".$condition_liste_rouge;
		if ($type=='espece_determinante') $sql.=" and ".$condition_espece_determinante;
		$sql.=$condition_validite_protection;
		if ($details_o_n=='nombre' && $id_observation=="" && $destination=='affichage')
		{
			$sql.=" ";
		}
		else {
			$sql.="and (
			bp.ss_niveau_1 is null
			or
			bp.ss_niveau_1 like '%#$departement_observation#%'
			) ";
		}

		//				if ($details_o_n=='observation' && $destination=='affichage') $this->p($sql);

		$data = $db->getrows($sql);
		$departements=$data[$i]["departements"];
		$retour='';
		$tableau_retour=array();

		// nombre  et affichage
		/*
		* appelé par
		* - taxinomie
		* - observation_detail
		* - observation
		* au travers de la fonction descripteur_biodiversite_taxinomie.
		*/

		if ( $details_o_n=='nombre' && $destination=='affichage' && count($data)>0 )
		{
			$nombre_protections=count($data);
			$in='(';
			for ($i = 0; $i < count($data); $i++) {
				$in.=$data[$i]["id_protection"].',';
			}
			$in=substr($in,0,strlen($in)-1).')';

			if ($id_observation=="")
			{
				$protections='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/protection.png" alt="Protections" title="Protections" target="_blank"></img>Protections';
				($aide_o_n=='o') ? $protections.=$this->descripteur_aide('Descripteur_biodiversite_protection','n') : $protections.="";

				$protections.= href(dispatch_url("biodiversite.protection", "admin", array (
						'atkfilter' => " biodiversite_protection.id in $in "
				), "dispatch.php"),'<b>listes('.$nombre_protections.')</b>', SESSION_NESTED, false, 'target="main"');
				$protections.= '&nbsp;'.href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
						'atkfilter' => " biodiversite_protection_taxinomie.cd_ref =$cd_ref and  biodiversite_protection_taxinomie.cd_protection in ( select cd_protection
						from  biodiversite_protection  where biodiversite_protection.id in $in )"
				), "dispatch.php"),'<b>statuts</b>', SESSION_NESTED, false, 'target="main"');
			}
			else
			{
					
				if ($type=='protection') $condition="bp.type_liste='protection'";
				if ($type=='liste_rouge') $condition="bp.type_liste='liste rouge'";
				if ($type=='espece_determinante') $condition="bp.type_liste='espèce déterminante'";
				$select_id_taxinomie='';
				if ($id_taxinomie!='') $select_id_taxinomie=" and t.id=$id_taxinomie ";
				$inin=" from biodiversite_protection bp, biodiversite_protection_taxinomie pt, biodiversite_observation o, biodiversite_observation_detail od, biodiversite_taxinomie t
						where t.id=od.id_taxinomie "
						.$select_id_taxinomie
						."	and pt.cd_ref=t.cd_nom
						and o.id=od.id_observation
						and o.id= $id_observation
						and pt.cd_protection=bp.cd_protection
						and $condition
						and bp.valide_o_n='1'
						and ( bp.ss_niveau_1 is null or bp.ss_niveau_1 like '%#$departement_observation#%' )
						)";
				$protections= href(dispatch_url("biodiversite.protection", "admin", array (
						'atkfilter' => " biodiversite_protection.cd_protection in (SELECT distinct pt.cd_protection ".$inin
				), "dispatch.php"),'<b>listes('.$nombre_protections.')</b>', SESSION_NESTED, false, 'target="main"');
				$protections.= '&nbsp;'.href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
						'atkfilter' => " biodiversite_protection_taxinomie.cd_ref in (SELECT distinct pt.cd_ref ".$inin ." and  biodiversite_protection_taxinomie.cd_protection in ( select cd_protection
						from  biodiversite_protection  where biodiversite_protection.id in $in )"
				) , "dispatch.php"),'<b>statuts</b>', SESSION_NESTED, false, 'target="main"');
			}
			$retour=$protections;
		}

		// Détails  et rapport
		/*
		* appelé par
		* - observation
		* au travers de l'action rapport.
		*/

		if (count($data)>0 && $details_o_n=='détails' && $destination=='rapport')
		{
			for ($i = 0; $i < count($data); $i++) {
				$substring_departement='#'.$departement_observation.'#';
				if ($data[$i]["departements"]!='' && strchr($data[$i]["departements"],$substring_departement)!=false)
				{
					$rapport_departement=$departement_observation;
				}
				else
				{	$rapport_departement=null;
				}

				if ($data[$i]["url_inpn"]!="")
				{
					$urlcdprotectioninpn=$data[$i]["url_inpn"];
				}
				else if  ($data[$i]["url"]!="")
				{
					$urlcdprotectioninpn=$data[$i]["url"];
				}
				else
				{$urlcdprotectioninpn="";
				}
				if ($urlcdprotectioninpn=="")
				{
					$retourcdprotectioninpn='<b>'.$data[$i]["intitule"].'</b>';
				}
				else
				{$retourcdprotectioninpn='<b><a href="' . $urlcdprotectioninpn .'" target="main" >'.$data[$i]["intitule"].'</a></b>';
				}

					
					

				//$tableau_retour[]=$retourcdprotectioninpn.'('.$data[$i]["an"].') | '.$data[$i]["article"].' | ' .$this->descripteur_biodiversite_traduction_code($data[$i]["statut"]).
				//    ' | '.$rapport_departement;
				$tableau_retour[$i][0]=$retourcdprotectioninpn.(empty($data[$i]["an"]) ? '' : '('.$data[$i]["an"].')').
				(empty($data[$i]["article"]) ? ' | ' : ' | '.$data[$i]["article"]);
				$statutuicn=$this->get_biodiversite_statut('',$data[$i]["statut"],'statut_uicn',false);
				if (empty($statutuicn))
				{
					$tableau_retour[$i][0].=' | ';
				}
				else {$tableau_retour[$i][0].=' | '.$statutuicn;
				}
				$tableau_retour[$i][0].=' | '.$rapport_departement;
				$tableau_retour[$i][1]=$retourcdprotectioninpn;
				$tableau_retour[$i][2]=$this->descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $data[$i]["cd_protection"],"n");

				$tableau_retour[$i][3]=$data[$i]["article"];
			}

		}

		// Détails  et affichage
		/*
		* appelé par
		* - observation_detail
		*
		* 				 */

		if (count($data)>0 && $details_o_n=='détails' && $destination=='affichage')
		{
			$nombre_protections=count($data);
			$in='(';
			for ($i = 0; $i < count($data); $i++) {
				$in.=$data[$i]["id_protection"].',';
			}
			$in=substr($in,0,strlen($in)-1).')';
			$retour="";
			for ($i = 0; $i < count($data); $i++) {

				$substring_departement='#'.$departement_observation.'#';
				if ($data[$i]["departements"]!='' && strchr($data[$i]["departements"],$substring_departement)!=false)
				{
					$rapport_departement=' | '.$departement_observation;
				}
				else
				{ $rapport_departement=null;
				}
				$ret=href(dispatch_url("biodiversite.protection", "admin", array (
						'atkfilter' => " biodiversite_protection.id = ".$data[$i]["id_protection"].""
				), "dispatch.php"), $data[$i]["intitule"].'('.$data[$i]["an"].') | '.$data[$i]["article"].' | <b>' .$this->get_biodiversite_statut('<b>',$data[$i]["statut"],'statut_uicn',false).$rapport_departement.'</b>', SESSION_NESTED, false, 'target="main"');
				$ret=str_replace(' ','&nbsp;',$ret);
				$ret=str_replace('<a&nbsp;href=','<a href=',$ret);
				$retour.='<br />'.$ret;
			}
		}

		// Observation et affichage
		if (count($data)>0 && $details_o_n=='observation' && $destination=='affichage')
		{
			$nombre_protections=count($data);
			$in='(';
			for ($i = 0; $i < count($data); $i++) {
				$in.=$data[$i]["id_taxinomie"].',';
			}
			$in=substr($in,0,strlen($in)-1).')';

			if ($type=='protection') $condition="bp.type_liste='protection'";
			if ($type=='liste_rouge') $condition="bp.type_liste='liste rouge'";
			if ($type=='espece_determinante') $condition="bp.type_liste='espèce déterminante'";
			$inin=" from biodiversite_protection bp, biodiversite_protection_taxinomie pt, biodiversite_observation o, biodiversite_observation_detail od, biodiversite_taxinomie t
			where t.id=od.id_taxinomie
			and pt.cd_ref=t.cd_nom
			and o.id=od.id_observation
			and o.id= $id_observation
			and pt.cd_protection=bp.cd_protection
			and $condition
			and bp.valide_o_n='1'
			and ( bp.ss_niveau_1 is null or bp.ss_niveau_1 like '%#$departement_observation#%' )
			";
			$sqls="SELECT count(distinct pt.cd_protection) as nombre ".$inin;
			$datas = $db->getrows($sqls);
			$nombre=$datas[0]["nombre"];
			$protections= href(dispatch_url("biodiversite.protection", "admin", array (
					'atkfilter' => " biodiversite_protection.cd_protection in (SELECT distinct pt.cd_protection ".$inin.")"
			), "dispatch.php"),'<b>listes('.$nombre.')</b>', SESSION_NESTED, false, 'target="main"');
				
			//				$chaine=" biodiversite_protection.cd_protection in (SELECT distinct pt.cd_protection ".$inin.'<br /><br />'.$sql;
			//				if ($type=='liste_rouge' and $protections!='') $this->p($chaine);
			$sqls="SELECT count(distinct t.id) as nombre ".$inin;
			$datas = $db->getrows($sqls);
			$nombre=$datas[0]["nombre"];
			$protections.= '&nbsp;'.href(dispatch_url("biodiversite.taxinomie", "admin", array (
					'atkfilter' => " biodiversite_taxinomie.id in (SELECT distinct t.id ".$inin.")"
			), "dispatch.php"),'<b>taxons('.$nombre.')</b>', SESSION_NESTED, false, 'target="main"');
			$sqls="SELECT count(distinct pt.id) as nombre ".$inin;
			$datas = $db->getrows($sqls);
			$nombre=$datas[0]["nombre"];
			$protections.= '&nbsp;'.href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
					'atkfilter' => " biodiversite_protection_taxinomie.id in (SELECT distinct pt.id			".$inin.")"
			), "dispatch.php"),'<b>statuts('.$nombre.')</b>', SESSION_NESTED, false, 'target="main"');
			$retour=$protections;

		}


		if ($destination=='affichage')			return $this->decoupe_affichage_colonne($retour,atkconfig("decoupe_colonne"));
		if ($destination=='rapport')			return $tableau_retour;
	}
	function report_writer($tableau,$first_col,$last_col)
	{
		if (count($tableau) ==1) return $tableau;
		//	$this->p($tableau);
		foreach ($tableau as $num=>$row)
		{
			$row_out=array();
			$i++;
			if ($i>1)
			{
				for ($c=0; $c<count($row); $c++)
				{
					if ($c<$first_col || $c>$last_col)
					{
						$row_out[]=$row[$c];
					}
					else
					{if ($preceding_row[$c]==$row[$c])
					{
						$row_out[]=' ';
					}
					else
					{	$row_out[]=$row[$c];
					}
					}
				}
			}
			else
			{
				$row_out=$row;
			}
			$preceding_row=$row;
			$tableau_out[]=$row_out;



		}
		return $tableau_out;
	}
	function get_biodiversite_statut($libelle,$code,$type,$cr=false)
	{
		$br='';
		if ($cr==true) $br='<br />';
		if ($code=='') return ''.$br;
		if (trim($type)=='') return '</b>'.$libelle.'<b>'.$code.'</b>'.$br;
		$db = &atkGetDb();
		$data = $db->getrows("SELECT statut, couleur from biodiversite_statut_taxinomique
				where code_statut='$code' and type_statut='$type' ");
		if ($data[0]["statut"]!='')
		{
			return '<span style="color:'.$data[0]["couleur"].'">'.'</b>'.$libelle.'<b>'.$data[0]["statut"].'</b></span>'.$br;
		}

		else
		{
			return '</b>'.$libelle.'<b>'.$code.'</b>'.$br;
		}
	}
	function descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $cd_protection,$aide_o_n='o') {
		// pas bon pour rapport
		//			$aide_o_n="n";
		if ($cd_ref=='') return;
		$db = &atkGetDb();
		$statut='';
		$data = $db->getrows(
				"SELECT
				categorie_statut,
				statut_liste_rouge,
				criteres_liste_rouge,
				statut_presence_determinant,
				statut_juridique,
				statut_biologique ,
				statut_de_nicheur,
				note_faune,
					
				`statut_biologique_nicheur_region`,
				`statut_biologique_hivernant_region`,
				`statut_biologique_migrateur_region`,
				`statut_SPEC` ,
				`statut_conservation_nicheur_france` ,
				`statut_conservation_hivernant_france`,
				`statut_conservation_nicheur_region`,
				`statut_conservation_hivernant_region`,
				`espece_determinante_region`,
				`espece_prioritaire_nicheur_region`,
				`espece_prioritaire_hivernant_region`,
				`espece_prioritaire_migrateur_region`,


				niveau_priorite,
				directive_habitats_oiseaux,
				convention_berne,
				convention_bonn,
				convention_washington,
					
				remarques_dreal,
				statut_orhoptere_france,
				statut_orhoptere_nemoral,
				statut_orhoptere_massif_central,
				statut_orhoptere_pyreneen,
				statut_orhoptere_alpien,
				statut_orhoptere_languedocien,
				statut_orhoptere_aquitain,
				statut_orhoptere_mediterraneen,
				statut_orhoptere_corse,
					
				statut_regression,
				statut_rarete,
				espece_prioritaire_flore
					

			 from biodiversite_protection_taxinomie
				where cd_ref= $cd_ref and cd_protection='$cd_protection'");


		if ($data[0]["statut_liste_rouge"]!='')  $statut.=$this->get_biodiversite_statut('Statut de conservation : <b>',$data[0]["statut_liste_rouge"],'statut_uicn',true);
		if ($data[0]["criteres_liste_rouge"]!='') $statut.='Critères de conservation : <b>'.$data[0]["criteres_liste_rouge"].'<br />'.'</b>';
		if ($data[0]["statut_presence_determinant"]!='') $statut.=$this->get_biodiversite_statut('Présence déterminante : ',$data[0]["statut_presence_determinant"],' ',true);
		if ($data[0]["statut_juridique"]!='') $statut.=$this->get_biodiversite_statut('Statut juridique : ',$data[0]["statut_juridique"],'statut_juridique',true);
		if ($data[0]["statut_biologique"]!='') $statut.=$this->get_biodiversite_statut('Statut biologique : ',$data[0]["statut_biologique"],' ',true);
		if ($data[0]["statut_de_nicheur"]!='') $statut.=$this->get_biodiversite_statut('Statut nicheur : ',$data[0]["statut_de_nicheur"],' ',true);
		if ($data[0]["note_faune"]!='') $statut.=$this->get_biodiversite_statut('Note faune : ',$data[0]["note_faune"],' ',true);
		// dreal
		//		if ($data[0]["statut_liste_rouge"]!='')  $statut.=$this->get_biodiversite_statut('Statut de conservation : <b>',$data[0]["statut_liste_rouge"],'statut_uicn').'</b>';
		//		if ($data[0]["criteres_liste_rouge"]!='') $statut.='Critères de conservation : <b>'.$data[0]["criteres_liste_rouge"].'<br />'.'</b>';
		if ($data[0]["niveau_priorite"]!='') $statut.=$this->get_biodiversite_statut('Statut espèce prioritaire : ',$data[0]["niveau_priorite"],'espece_prioritaire',true);
		if ($data[0]["directive_habitats_oiseaux"]!='') $statut.='Directive Habitats/Oiseaux : <b>'.$data[0]["directive_habitats_oiseaux"].'<br />'.'</b>';
		if ($data[0]["convention_berne"]!='') $statut.='Convention de Berne : <b>'.$data[0]["convention_berne"].'<br />'.'</b>';
		if ($data[0]["convention_bonn"]!='') $statut.='Convention de Bonn : <b>'.$data[0]["convention_bonn"].'<br />'.'</b>';
		if ($data[0]["convention_washington"]!='') $statut.='Convention de Washington : <b>'.$data[0]["convention_washington"].'<br />'.'</b>';
		//			if ($data[0]["statut_juridique"]!='') $statut.=$this->get_biodiversite_statut('Statut juridique : <b>',$data[0]["statut_juridique"],'statut_juridique').'</b>';
		//			if ($data[0]["statut_biologique"]!='') $statut.='Statut biologique : <b>'.$data[0]["statut_biologique"].'<br />'.'</b>';
		if ($data[0]["remarques_dreal"]!='') $statut.='Remarques : <b>'.$data[0]["remarques_dreal"].'<br />'.'</b>';
		// avifaune

		if ($data[0]["statut_biologique_nicheur_region"]!='')  $statut.=$this->get_biodiversite_statut('Statut biologique nicheur région : ',$data[0]["statut_biologique_nicheur_region"],'statut_biologique',true);
		if ($data[0]["statut_biologique_hivernant_region"]!='')  $statut.=$this->get_biodiversite_statut('Statut biologique hivernant région : ',$data[0]["statut_biologique_hivernant_region"],'statut_biologique',true);
		if ($data[0]["statut_biologique_migrateur_region"]!='')  $statut.=$this->get_biodiversite_statut('Statut biologique migrateur région : ',$data[0]["statut_biologique_migrateur_region"],'statut_biologique',true);
		if ($data[0]["statut_spec"]!='')  $statut.=$this->get_biodiversite_statut('Statut conservation SPEC : ',$data[0]["statut_spec"],'statut_spec',true);
		if ($data[0]["statut_conservation_nicheur_france"]!='')  $statut.=$this->get_biodiversite_statut('Statut conservation nicheur france : ',$data[0]["statut_conservation_nicheur_france"],'statut_conservation_liste_rouge',true);
		if ($data[0]["statut_conservation_hivernant_france"]!='')  $statut.=$this->get_biodiversite_statut('Statut conservation hivernant france : ',$data[0]["statut_conservation_hivernant_france"],'statut_conservation_liste_rouge',true);
		if ($data[0]["statut_conservation_nicheur_region"]!='')  $statut.=$this->get_biodiversite_statut('Statut conservation nicheur région : ',$data[0]["statut_conservation_nicheur_region"],'statut_conservation_liste_rouge',true);
		if ($data[0]["statut_conservation_hivernant_region"]!='')  $statut.=$this->get_biodiversite_statut('Statut conservation hivernant région : ',$data[0]["statut_conservation_hivernant_region"],'statut_conservation_liste_rouge',true);
		if ($data[0]["espece_determinante_region"]!='')  $statut.=$this->get_biodiversite_statut('Espèce déterminante région : ',$data[0]["espece_determinante_region"],'espece_determinante',true);
		if ($data[0]["espece_prioritaire_nicheur_region"]!='')  $statut.=$this->get_biodiversite_statut('Espèce prioritaire nicheur région : ',$data[0]["espece_prioritaire_nicheur_region"],'espece_prioritaire',true);
		if ($data[0]["espece_prioritaire_hivernant_region"]!='')  $statut.=$this->get_biodiversite_statut('Espèce prioritaire hivernant région : ',$data[0]["espece_prioritaire_hivernant_region"],'espece_prioritaire',true);
		if ($data[0]["espece_prioritaire_migrateur_region"]!='')  $statut.=$this->get_biodiversite_statut('Espèce prioritaire migrateur région : ',$data[0]["espece_prioritaire_migrateur_region"],'espece_prioritaire',true);

		if ($data[0]["statut_orhoptere_france"]!='')  $statut.=$this->get_biodiversite_statut('Statut France : ',$data[0]["statut_orhoptere_france"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_nemoral"]!='')  $statut.=$this->get_biodiversite_statut('Statut némoral : ',$data[0]["statut_orhoptere_nemoral"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_massif_central"]!='')  $statut.=$this->get_biodiversite_statut('Statut Massif Central : ',$data[0]["statut_orhoptere_massif_central"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_pyreneen"]!='')  $statut.=$this->get_biodiversite_statut('Statut Pyrénéen : ',$data[0]["statut_orhoptere_pyreneen"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_alpien"]!='')  $statut.=$this->get_biodiversite_statut('Statut Alpien : ',$data[0]["statut_orhoptere_alpien"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_languedocien"]!='')  $statut.=$this->get_biodiversite_statut('Statut Languedocien : ',$data[0]["statut_orhoptere_languedocien"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_aquitain"]!='')  $statut.=$this->get_biodiversite_statut('Statut Aquitain : ',$data[0]["statut_orhoptere_aquitain"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_mediterraneen"]!='')  $statut.=$this->get_biodiversite_statut('Statut Méditerranéen : ',$data[0]["statut_orhoptere_mediterraneen"],'orthoptères',true);
		if ($data[0]["statut_orhoptere_corse"]!='')  $statut.=$this->get_biodiversite_statut('Statut Corse : ',$data[0]["statut_orhoptere_corse"],'orthoptères',true);

		if ($data[0]["statut_regression"]!='')  $statut.=$this->get_biodiversite_statut('Statut régression : ',$data[0]["statut_regression"],'regression_flore_vasculaire',true);
		if ($data[0]["statut_rarete"]!='')  $statut.=$this->get_biodiversite_statut('Statut de rareté : ',$data[0]["statut_rarete"],'rarete_flore_vasculaire',true);
		if ($data[0]["espece_prioritaire_flore"]!='')  $statut.=$this->get_biodiversite_statut('Espèce prioritaire : ',$data[0]["espece_prioritaire_flore"],'priorité_flore_vasculaire',true);
		if ($statut=='')
		{
		}
		else
		{$statut.='</b>'.$this->document_aide_biodiversite_symboles_protection();
		}
		($aide_o_n=='o') ? $statut.=' '.$this->descripteur_aide('Descripteur_biodiversite_protection_taxinomie_statuts','n').'' : $statut.='';
 
		return $statut;
	}
	function fratrie_display($id_parent)
	{
		$db = & atkGetDb();

		$sql="SELECT count(id) as nombre from biodiversite_taxinomie where id_parent='".$id_parent."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];

		if ($nombre>0) {
			$ret= href(dispatch_url("biodiversite.taxinomie", "admin", array (
					'atkfilter' => "biodiversite_taxinomie.id_parent='" . $id_parent . "'",
					'view'=>'tout'
			), "dispatch.php"), '<b>'.$nombre.'</b>', SESSION_NESTED, false, 'target="main"');
			//				$this->p($record);

			if ($nombre!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
			else return $ret;
		} else {
			return "";
		}
	}
	function descripteur_biodiversite_observations($id_localisation,$type='pays') {
		if ($id_localisation=='') return;
		$ret='';
		$db = &atkGetDb();
		if ($type=='pays')
		{
			$sql_observations="select count(o.id) as nombre_observations
			from
			biodiversite_observation o,
			type_pays p,
			type_cp_ville_pays cpv,
			lieu l
			where
			o.id_lieu is not null and
			o.id_lieu=l.id and
			l.id_ville=cpv.id and
			cpv.id_pays=p.id and
			p.id=$id_localisation";
		}
		$data = $db->getrows($sql_observations);
		$nombre_observations=$data[0]["nombre_observations"];

		$ret='observations : '.$nombre_observations;
		return $ret;
	}
	function descripteur_biodiversite_premiere_derniere_observation($id_taxinomie,$id_observations) {
		if ($id_taxinomie=='' || $id_observations=='') return;
		$tableau_retour=array();
		$db = &atkGetDb();
		$sql="SELECT
				max(bo.date_observation) as date_observation
				from
				biodiversite_observation bo,
				biodiversite_observation_detail bod
				where
				bod.id_observation in ( " . $id_observations . ")
				and bod.id_taxinomie='$id_taxinomie'
				and bod.id_observation=bo.id
				";
		$data = $db->getrows($sql);
		$date_max=$data[0]["date_observation"];
		$sql="SELECT
				bo.id_observateur,
				i.nom,
				i.prenom,
				year(bo.date_observation) as annee
				from
				biodiversite_observation bo,
				biodiversite_observation_detail bod,
				individu i
				where
				bod.id_observation in ( " . $id_observations . ")
				and bo.date_observation='$date_max'
				and bod.id_taxinomie='$id_taxinomie'
				and bod.id_observation=bo.id
				and bo.id_observateur=i.id";
		$data = $db->getrows($sql);
		$tableau_retour[]=$data[0]["nom"].' '.substr($data[0]["prenom"],0,1).'.'.' '.$data[0]["annee"];
		$sql="SELECT
				min(bo.date_observation) as date_observation
				from
				biodiversite_observation bo,
				biodiversite_observation_detail bod
				where
				bod.id_observation in ( " . $id_observations . ")
				and bod.id_taxinomie='$id_taxinomie'
				and bod.id_observation=bo.id
				";
		$data = $db->getrows($sql);
		$date_min=$data[0]["date_observation"];
		$sql="SELECT
				bo.id_observateur,
				i.nom,
				i.prenom,
				year(bo.date_observation) as annee
				from
				biodiversite_observation bo,
				biodiversite_observation_detail bod,
				individu i
				where
				bod.id_observation in ( " . $id_observations . ")
				and bo.date_observation='$date_min'
				and bod.id_taxinomie='$id_taxinomie'
				and bod.id_observation=bo.id
				and bo.id_observateur=i.id";
		$data = $db->getrows($sql);
		$tableau_retour[]=$data[0]["nom"].' '.substr($data[0]["prenom"],0,1).'.'.' '.$data[0]["annee"];
		return $tableau_retour;
	}

	function descripteur_biodiversite_taxons_inpn($id_taxinomie,$id_observation,$destination='affichage',$aide_o_n='o') {
		if ($id_taxinomie=='' || !isset($id_taxinomie)) return;

		$db = &atkGetDb();
		$data = $db->getrows(
				"SELECT
				t.inpn_nom_complet,
				t.inpn_lb_nom,
				t.inpn_lb_auteur,
				t.inpn_rang,
				t.inpn_version,
				t.cd_nom,
				t.cd_taxsup,
				t.cd_ref,
				t.nom_francais,
				t.nom_anglais,
				h.habitat
					
				from biodiversite_taxinomie t LEFT JOIN
				biodiversite_habitat_taxinomie h
				ON  t.id_habitat=h.code_habitat
					
				where t.id=$id_taxinomie
				");
		// 			and t.id_habitat=h.code_habitat
		$nom_complet=$data[0]["inpn_nom_complet"];
		$lb_nom=$data[0]["inpn_lb_nom"];
		$lb_auteur=$data[0]["inpn_lb_auteur"];
		$rang=$data[0]["inpn_rang"];
		$version=$data[0]["inpn_version"];
		$cd_nom=$data[0]["cd_nom"];
		$cd_taxsup=$data[0]["cd_taxsup"];
		$cd_ref=$data[0]["cd_ref"];
		$nom_vern=$data[0]["nom_francais"];
		$nom_vern_en=$data[0]["nom_anglais"];

		$habitat=$data[0]["habitat"];
		$descripteur='';


		$descripteur.='Nom complet : <b>'.$nom_complet ;
		$descripteur.='</b><br />';
		$descripteur.='Lb nom : <b>'.$lb_nom ;
		$descripteur.='</b><br />';
		$descripteur.='Nom vern : <b>'.$nom_vern;
		$descripteur.='</b><br />';
		$descripteur.='Nom vern en : <b>'.$nom_vern_en;
		$descripteur.='</b><br />';
		$descripteur.='Lb auteur : <b>'.$lb_auteur;
		$descripteur.='</b><br />';
		$descripteur.='Rang : <b>'.$rang;
		$descripteur.='</b><br />';
		//			$descripteur=str_replace(' ','&nbsp;',$descripteur );
		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$cd_nom."" ;
		$descripteur.='Cd nom (<b>'.$cd_nom.'</b>) : <b><a href="' . $urlinpn .' " target="_blank" >Inpn</a>';
		$descripteur.='</b><br />';

		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$cd_ref."" ;
		if ($cd_nom==$cd_ref)
		{
			$descripteur.='Cd ref (<b>'.$cd_ref.'</b>) : <b><a href="' . $urlinpn .' " target="_blank" >Inpn</a>';
		}
		else
		{$descripteur.='<b>Cd ref </b>(<b>'.$cd_ref.'</b></font>) : <b><a href="' . $urlinpn .' " target="_blank" >Inpn</a>';
		}
		$urlassocope='<b><a href="dispatch.php?atknodetype=biodiversite.taxinomie&view=requete&
				atkaction=admin&atkfilter=biodiversite_taxinomie.cd_nom='.$cd_ref. '&" target="_blank" >AssoCope</a></b>';
		$descripteur.=' '.$urlassocope;
		if ($cd_ref=='')
		{
			echo $id_observation;
			echo '<br>';
			echo "Aucun cd_ref n'a été trouvé pour";
			echo '<br>';


			echo 'id_taxinomie : '.$id_taxinomie;
			echo '<br>';
			$this->p($data);
			die();

		}

		$data = $db->getrows(	"SELECT count(id) as nombre from  biodiversite_taxinomie where cd_ref= $cd_ref");
		$nombretaxref=$data[0]["nombre"];
		$urlassocope='<b><a href="dispatch.php?atknodetype=biodiversite.taxinomie&view=requete&
				atkaction=admin&atkfilter=biodiversite_taxinomie.cd_ref='.$cd_ref. '&" target="_blank" >'.$nombretaxref.'&nbsp;synonymes</a></b>';
		$descripteur.=' '.$urlassocope;
		$descripteur.='</b><br />';
		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$cd_taxsup."" ;
		$descripteur.='Cd taxsup (<b>'.$cd_taxsup.'</b>) : <b><a href="'. $urlinpn .'" target="_blank" >Inpn</a>';
		$urlassocope='<b><a href="dispatch.php?atknodetype=biodiversite.taxinomie&view=requete&
				atkaction=admin&atkfilter=biodiversite_taxinomie.cd_nom='.$cd_taxsup. '&" target="_blank" >AssoCope</a></b>';
		$descripteur.=' '.$urlassocope;
		$descripteur.='</b><br />';
		$descripteur.='Habitat : <b>'.$habitat;
		$descripteur.='</b><br />';
		$descripteur.='Version : <b>'.$version;
		$descripteur.='</b><br />';
		//	$descripteur=str_replace(' ','&nbsp;',$descripteur);
		//	$descripteur=str_replace('<br&nbsp;/>','<br />',$descripteur);
		//	$descripteur=str_replace('<a&nbsp;href=','<a href=',$descripteur);
		($aide_o_n=='o') ? $descripteur.=$this->descripteur_aide('Descripteur_biodiversite_taxons_inpn','n') : $descripteur.="";

		return $descripteur;


	}
	function descripteur_biodiversite_referentiels($id_taxinomie,$id_observation,$destination='affichage',$aide_o_n='o') {
		if ($id_taxinomie=='') return;
		$db = &atkGetDb();
		$ref='';
		$data = $db->getrows(
				"SELECT count(ta.record_id) as nombre from
				biodiversite_taxinomie tox,
				col_taxa ta
				where tox.id=$id_taxinomie
				and LOWER(tox.nom_binomial)=LOWER(ta.name)
				");
		$nombre_taxa=$data[0]["nombre"];
		$data = $db->getrows(
				"SELECT	t.id_taxon_fauna_europaea,
				t.id_taxon_conservation_nature,
				t.id_taxon_marine_species,
				t.id_taxon_kerguelen,
				t.id_bock_kerguelen
				, t.nom_binomial
				from biodiversite_taxinomie t
				where t.id= $id_taxinomie 				");
		$nom_binomial_brut=$data[0]["nom_binomial"];

		$id_taxon_fe=$data[0]["id_taxon_fauna_europaea"];
		if (isset($id_taxon_fe))
		{
			$url="http://www.faunaeur.org/full_results.php?id=".$id_taxon_fe ;
			$target = ' target="_blank"';
			$anchor='<a href="' . $url . '"' . $target . '" ><b>'.$id_taxon_fe.'</b></a>';
		}
		else
		{$anchor="";
		}
		$nom_binomial_brut=str_replace(' ','&nbsp;',$nom_binomial_brut );

		if ($nombre_taxa>0)
		{
			$ref='<a target="_blank" href="dispatch.php?atknodetype=biodiversite.col_taxa&
					atkaction=admin&atkfilter=col_taxa.name=\''.$nom_binomial_brut.'\'"><b>Catalogue of life local('.$nombre_taxa.')</b></a> <br /> ';
		}
		else
		{$ref='<a target="_blank" href="dispatch.php?atknodetype=biodiversite.col_taxa&
				atkaction=admin&atkfilter=col_taxa.name=\''.$nom_binomial_brut.'\'">Catalogue of life local(0)</a> <br /> ';
		}

		$ref.='Taxon&nbsp;fauna&nbsp;europaea&nbsp;:&nbsp;<b>';
		//			$ref.=str_replace(' ','&nbsp;',$ref );
		$ref.=$anchor.'</b><br />';
		$ref1='Taxon conservation nature : <b>'.$data[0]["id_taxon_conservation_nature"].'</b><br />';
		$ref1.='Taxon marine species : <b>'.$data[0]["id_taxon_marine_species"].'</b><br />';
		$ref1.='Taxon kerguelen : <b>'.$data[0]["id_taxon_kerguelen"].'</b><br />';
		$ref1.='Bock kerguelen : <b>'.$data[0]["id_bock_kerguelen"].'</b><br />';
		($aide_o_n=='o') ? $ref1.=$this->descripteur_aide('Descripteur_biodiversite_referentiels','n') : $ref1.="";
		//$ref1=str_replace(' ','&nbsp;',$ref1 );
		//$ref1=str_replace('<br&nbsp;/>','<br />',$ref1 );
		return $ref.$ref1;

	}

	function descripteur_biodiversite_statuts_inpn($id_taxinomie,$id_observation,$destination='affichage',$aide_o_n='o') {
		if ($id_taxinomie=='') return;
		$db = &atkGetDb();
		$statut='';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_france_metropole=s.id	and type_statut='statut_inpn'					");
		$statut.='France métropolitaine : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_martinique=s.id and type_statut='statut_inpn'							");
		$statut.='Martinique : <b>'.$data[0]["statut"].'</b> ';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_guadeloupe=s.id	and type_statut='statut_inpn'						");
		$statut.='Guadeloupe : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_st_martin_st_barthelemy=s.id		and type_statut='statut_inpn'					");
		$statut.='St Martin St Barthélémy : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_guyane_francaise=s.id			and type_statut='statut_inpn'				");
		$statut.='Guyane francaise : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_st_pierre_et_miquelon=s.id	and type_statut='statut_inpn'						");
		$statut.='St Pierre et Miquelon : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_reunion=s.id		and type_statut='statut_inpn'					");
		$statut.='Réunion : <b>'.$data[0]["statut"].'</b> ';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_mayotte=s.id		and type_statut='statut_inpn'					");
		$statut.='Mayotte : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_terres_australes_et_antartiques_francaises	=s.id			and type_statut='statut_inpn'				");
		$statut.='Terres australes et antarctiques francaises : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_iles_eparses=s.id		and type_statut='statut_inpn'					");
		$statut.='Iles éparses : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_polynesie_francaise=s.id						");
		$statut.='Polynesie francaise : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_nouvelle_caledonie=s.id	and type_statut='statut_inpn'						");
		$statut.='Nouvelle Calédonie : <b>'.$data[0]["statut"].'</b><br />';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_wallis_et_futuna=s.id		and type_statut='statut_inpn'					");
		$statut.='Wallis et Futuna : <b>'.$data[0]["statut"].'</b> ';
		$data = $db->getrows(
				"SELECT	s.statut from biodiversite_taxinomie t,	biodiversite_statut_taxinomique s
				where t.id= $id_taxinomie and t.id_statut_clipperton=s.id			and type_statut='statut_inpn'				");

		$statut.='Clipperton : <b>'.$data[0]["statut"].'</b><br />';
		($aide_o_n=='o') ? $statut.=$this->descripteur_aide('Descripteur_biodiversite_statuts_inpn','n') : $statut.="";
		return $statut;
	}


	function descripteur_biodiversite_taxinomie($id_taxinomie,$id_observation,$destination='affichage',$aide_o_n='o',$image_o_n='n') {
		if ($id_taxinomie=='') return;

		$db = &atkGetDb();
		$data = $db->getrows(
				"SELECT t.nom_binomial as nom_binomial,
				t.inpn_nom_complet,
				t.url_image,
				t.cd_nom as cd_nom,
				t.cd_ref as cd_ref,
				t.id_parent as id_parent,
				t.nom_francais as nom_francais,
				t.nom_anglais as nom_anglais,
				t.auteur as auteur,
				t.auteur_an as auteur_an,
				t.id_statut_france_metropole,
				rt.nom_francais as rang_francais
				from biodiversite_taxinomie t,
				biodiversite_rang_taxinomique rt
					
				where t.id= $id_taxinomie
				and t.id_rang_taxinomique=rt.id
				");
		$cd_ref=$data[0]["cd_ref"];
		$id_parent=$data[0]["id_parent"];
		$nom_francais=$data[0]["nom_francais"];
		$nom_binomial=$data[0]["nom_binomial"];
		$nom_binomial_brut=$data[0]["nom_binomial"];
		$url_image=$data[0]["url_image"];
		$target=' target="main" ';
		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$data[0]["cd_nom"] ;
		$retourinpnnom.='<a href="' . $urlinpn . '"' . $target . '"><b>'.$data[0]["cd_nom"].'</b></a>';
		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=" .$data[0]["cd_ref"];
		$retourinpnref.='<a href="' . $urlinpn . '"' . $target . '"><b>'.$data[0]["cd_ref"].'</b></a>';
		if ($data[0]["cd_nom"]==$data[0]["cd_ref"])
		{
			$inpn_nom_complet=$data[0]["inpn_nom_complet"].'<br /><span style="color:Green">(CD&nbsp;NOM=CD&nbsp;REF='.$retourinpnnom.')</span>';
		}
		else
		{
			$inpn_nom_complet=$data[0]["inpn_nom_complet"].'<br /><span style="color:Red">(CD&nbsp;NOM='.$retourinpnnom.')'.'<br />(CD&nbsp;REF='.$retourinpnref.')</span>';
		}
		$inpn_nom_complet_sans_cd=$data[0]["inpn_nom_complet"];
		$nom_anglais=$data[0]["nom_anglais"];
		$auteur=$data[0]["auteur"];
		$auteur_an=$data[0]["auteur_an"];
		$rang_francais=$data[0]["rang_francais"];
		$statut=$data[0]["id_statut_france_metropole"];
		if ($nom_binomial=='') {
			echo 'id : '.$id_taxinomie.' '; die();
		}
		if ($destination=='affichage')
		{
			$data = $db->getrows("select count(id) as compte from biodiversite_observation_detail
					where id_taxinomie =$id_taxinomie ");
			$nombre_observations=$data[0]["compte"];
			if ($nombre_observations >0 ) {
				$observations= href(dispatch_url("biodiversite.observation_detail", "admin", array (
						'atkfilter' => "biodiversite_observation_detail.id_taxinomie='" . $id_taxinomie . "'"
				), "dispatch.php"), $nombre_observations, SESSION_NESTED, false, 'target="main"');
				if ($nombre_observations!=0)			$observations='<font color="red"><b>'.$observations.'</font></b>';
				$data = $db->getrows("select id from biodiversite_observation_detail
						where id_taxinomie =$id_taxinomie ");
				for ($l = 0; $l < count($data); $l++) {
					$taxons .= $data[$l]["id"] . ',';
				}
				$taxons = substr($taxons, 0, strlen($taxons) - 1);
				$taxons=str_replace("'","",$taxons);
				$observations.=atkHref(		dispatch_url("biodiversite.observation_detail", "mapbiodiversite",array (
						"taxons" => $taxons,
						"taxons_detail"=> $taxons,
						"zones" => 0,
						"date_observation_debut" => 0,
						"date_observation_fin" => 0,
						"heure_observation_debut" => 0,
						"heure_observation_fin" => 0,
						"organismes_commanditaire" => 0,
						"organismes_observateur" => 0,
						"individus_observateur" => 0
				)),
						'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/earth.png" alt="Géolocalisation des observations"
						title="Géolocalisation des observations"  ></img>',SESSION_NESTED, false,
						'target="_blank"');

			} else {
				$observations="";
			}
			if ($id_observation!="")
			{
				$data = $db->getrows("SELECT code_departement_protection from biodiversite_observation where id=$id_observation			");
				$code_departement_protection=$data[0]["code_departement_protection"];
			}
			else $code_departement_protection="";

			$protections=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,'nombre','protection','affichage',$cd_ref,$code_departement_protection);
			$listes_rouges=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,'nombre','liste_rouge','affichage',$cd_ref,$code_departement_protection);
			$listes_espece_determinante=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,'nombre','espece_determinante','affichage',$cd_ref,$code_departement_protection);
			$fratrie=$this->fratrie_display($id_parent);
			$descendance=$this->biodiversite_descendance($id_taxinomie, $mode);

			$href=atkHref(dispatch_url("biodiversite.taxinomie", "edit", array ("atkselector" => "biodiversite_taxinomie.id='" . $id_taxinomie . "'" )),
					$nom_binomial,SESSION_NESTED, false, 'target="main"') ;
			(!empty($nom_binomial)) ? $descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/taxinomie.png" alt="Taxon" title="Taxon" target="main"></img>'.
					"<b>".$href."</b> " : $descripteur="" ;
			($aide_o_n=='o') ? $descripteur.=$this->descripteur_aide('Descripteur_taxinomie','n').'<br />' : $descripteur.='<br />';
			$data = $db->getrows(	"SELECT count(id) as nombre from  biodiversite_taxinomie where cd_ref= $cd_ref");
			$nombre_synonymes=$data[0]["nombre"];
			$synonymes='<a href="dispatch.php?atknodetype=biodiversite.taxinomie&view=requete&
					atkaction=admin&atkfilter=biodiversite_taxinomie.cd_ref='.$cd_ref. '&" target="main" >'.$nombre_synonymes.'</a>';
			(!empty($inpn_nom_complet))	? $descripteur.='Nom complet : <b>'.$inpn_nom_complet.'</b><br />' : $descripteur.='';
			(!empty($nom_francais))	? $descripteur.='Nom francais : <b>'.$nom_francais.'</b><br />' : $descripteur.='';
			(!empty($nom_anglais))	? $descripteur.='Nom anglais : <b>'.$nom_anglais.'</b><br />' : $descripteur.='';
			(!empty($auteur))	? $descripteur.='Auteur : <b>'.$auteur.'-'.$auteur_an.'</b><br />' : $descripteur.='';
			(!empty($fratrie))	? $descripteur.='Fratrie : <b>'.$fratrie.'</b><br />' : $descripteur.='';
			(!empty($descendance))	? $descripteur.='Descendance : <b>'.$descendance.'</b><br />' : $descripteur.='';
			$descripteur.='Synonymes : <b>'.$synonymes.'</b><br />';
			(!empty($observations))	? $descripteur.='Observations : <b>'.$observations.'</b><br />' : $descripteur.='';
			(!empty($protections))	? $descripteur.='Protections : <b>'.$protections.'</b><br />' : $descripteur.='';
			(!empty($listes_rouges))	? $descripteur.='Listes rouges : <b>'.$listes_rouges.'</b><br />' : $descripteur.='';
			(!empty($listes_espece_determinante))	? $descripteur.='Espèces déterminantes : <b>'.$listes_espece_determinante.'</b><br />' : $descripteur.='';
			$descripteur.= $this->document_aide_biodiversite_symboles_protection();
				
			$descripteur=$this->decoupe_affichage_colonne($descripteur,atkconfig("decoupe_colonne"));
			if ($image_o_n=='o')
			{
				(strlen($url_image) >0 ) ? $descripteur.= '</br><a href="'.$url_image.'" target="_blank" ><img  border="0" src="'.$url_image.'" height="100"  alt="Taxon" title="Taxon" ></img></a>' : null;
			}
		}
		if ($destination=='rapport')
		{
			if ($data[0]["t.id_statut_france_metropole"]!='0')
			{
				$datastatut = $db->getrows(
						"SELECT statut
						from biodiversite_statut_taxinomique
						where id=$statut");
				$statut=$datastatut[0]["statut"];
			}
			else
			{
				$statut='';
			}
			$descripteur=array();
			$descripteur["cd_ref"]=$cd_ref;

			$descripteur["inpn_nom_complet"]=$inpn_nom_complet ;
			$descripteur["nom_binomial"]=str_replace('_',' ',$nom_binomial );
			$descripteur["nom_francais"]=str_replace('_',' ',$nom_francais );
			$descripteur["auteur"]=str_replace('_',' ',$auteur );
			$descripteur["auteur_an"]=$auteur_an;
			$descripteur["statut_inpn"]=str_replace('_',' ',$statut );
		}
		return $descripteur;
	}
	function document_aide_biodiversite_symboles_protection()
	{
		$hrefdoc=dispatch_url("organisme.document", "fichier", array (
				"atkselector" => "organisme_document.id='1491'"
		));
		return'<a href="'.$hrefdoc.'" target="main">Explications</a>';
	}
	function descripteur_biodiversite_ascendance($idtaxinomie, $destination='affichage',$aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="SELECT t.id,  id_parent, nom_binomial, nom_latin
				from biodiversite_taxinomie t , biodiversite_rang_taxinomique r
				where t.id='".$idtaxinomie."' and t.id_rang_taxinomique=r.id";
		$rows = $db->getrows($sql);
		$id_parent=$rows[0]["id_parent"];
		$nom_binomial=$rows[0]["nom_binomial"];
		$ascendance="";
		$tableau_ascendance=array();
		if ($destination=='affichage')
		{
			$nombi=str_replace(' ','&nbsp;',$rows[0]["nom_binomial"]);
			$nomlatin=str_replace(' ','&nbsp;',$rows[0]["nom_latin"]);
			$ascendance= $nomlatin.'&nbsp;:&nbsp;<b><a target="_blank" href="dispatch.php?atknodetype=biodiversite.taxinomie&
					atkaction=view&atkselector=biodiversite_taxinomie.id='.$rows[0]["id"]. '&">'.$nombi.'</a> <br /></b>'.$ascendance;

		}
		if ($destination=='rapport')
		{
			$tableau_ascendance[$rows[0]["nom_latin"]]=$rows[0]["nom_binomial"];
		}
		while ($id_parent!=0)
		{
			$sql="SELECT t.id,  id_parent, nom_binomial, nom_latin
					from biodiversite_taxinomie t , biodiversite_rang_taxinomique r
					where t.id='".$id_parent."' and t.id_rang_taxinomique=r.id";
			$data=$db->getrows($sql);
			$id_parent=$data[0]["id_parent"];
			if ($destination=='affichage')
			{
				$nombi=str_replace(' ','&nbsp;',$data[0]["nom_binomial"]);
				$nomlatin=str_replace(' ','&nbsp;',$data[0]["nom_latin"]);
				$ascendance=$nomlatin.'&nbsp;:&nbsp;<b><a target="_blank" href="dispatch.php?atknodetype=biodiversite.taxinomie&
						atkaction=view&atkselector=biodiversite_taxinomie.id='.$data[0]["id"]. '&">'.$nombi.'</a><br /></b> '.$ascendance;

			}
			if ($destination=='rapport')
			{
				$tableau_ascendance[$data[0]["nom_latin"]]=$data[0]["nom_binomial"];
				//			$tableau_ascendance["nom_binomial"][]=$data[0]["nom_binomial"];
			}
		}
		if ($destination=='rapport') return $tableau_ascendance;
		if ($destination=='affichage')
		{
			($aide_o_n=='o') ? $ascendance.=' '.$this->descripteur_aide('Descripteur_biodiversite_ascendance','n').'<br />' : $ascendance.='';
			return $ascendance;
		}
	}

	function descripteur_biodiversite_observation($id_observation,$destination='affichage',$aide_o_n='o')
	{
		if ($id_observation=='') return;
		$db = &atkGetDb();
		$data = $db->getrows(
				"SELECT  bo.id_organisme,
				bo.id_organisme_observateur,
				bo.id_observateur,
				bo.date_observation,
				bo.id_type_localisation,
				bo.libelle,
				bo.latitude,
				bo.longitude,
				bo.id_ville,
				bo.id_lieu,
				bo.id_point_observation ,
				bo.code_departement_protection
				from biodiversite_observation bo
				where bo.id=$id_observation " ) ;
		$id_organisme_commanditaire=$data[0]["id_organisme"];
		$id_organisme_observateur=$data[0]["id_organisme_observateur"];
		$id_observateur=$data[0]["id_observateur"];
		$date_observation=$data[0]["date_observation"];
		$id_ville=$data[0]["id_ville"];
		$id_lieu=$data[0]["id_lieu"];
		$id_point_observation=$data[0]["id_point_observation"];
		$ob_latitude=$data[0]["latitude"];
		$ob_latitude=$data[0]["longitude"];
		$libelle=$data[0]["libelle"];
		$code_departement_protection=$data[0]["code_departement_protection"];
		$especes_observees=$data[0]["especes_observees"];

		$data = $db->getrows(
				"SELECT  count(id) as compte
				from biodiversite_observation_detail
				where id_observation=$id_observation") ;
		$nb_observations=$data[0]["compte"];

		if ( $id_organisme_observateur>0	)
		{
			$data = $db->getrows(
					"SELECT  nom
					from organisme
					where id=$id_organisme_observateur") ;
			$nom_organisme_observateur_rapport=$data[0]["nom"];
			$nom_organisme_observateur= href(dispatch_url("organisme.organisme", "edit", array (
					'atkfilter' => "organisme.id='" . $id_organisme_observateur . "'"
			), "dispatch.php"), $nom_organisme_observateur_rapport, SESSION_NESTED);
				
		}
		$data = $db->getrows("SELECT  nom
				from organisme
				where id=$id_organisme_commanditaire") ;
		$nom_organisme_commanditaire_rapport=$data[0]["nom"];
		$nom_organisme_commanditaire= href(dispatch_url("organisme.organisme", "edit", array (
				'atkfilter' => "organisme.id='" . $id_organisme_commanditaire . "'"
		), "dispatch.php"), $nom_organisme_commanditaire_rapport, SESSION_NESTED);
		$data = $db->getrows(
				"SELECT  nom , prenom
				from individu
				where id=$id_observateur") ;
		$nom_observateur=$data[0]["nom"];
		$prenom_observateur=$data[0]["prenom"];
		$nom_observateur_rapport=$nom_observateur.' '.$prenom_observateur;
		$nom_observateur= href(dispatch_url("individu.individu", "edit", array (
				'atkfilter' => "individu.id='" . $id_observateur . "'"
		), "dispatch.php"), $nom_observateur_rapport, SESSION_NESTED);

		if ( isset($id_ville)	)
		{
			$data = $db->getrows(
					"SELECT  ville, code_postal, tp.code_iso, longitude, latitude
					from type_cp_ville_pays cp, type_pays tp
					where cp.id=$id_ville and id_pays=tp.id") ;
			$longitude=$data[0]["longitude"];
			$latitude=$data[0]["latitude"];
			$nom_ville=$data[0]["ville"];
			$code_postal=$data[0]["code_postal"];
			$code_pays=$data[0]["code_iso"];
			$lieu=$code_postal.' '.$nom_ville.' '.$code_pays;
			$href_lieu_observation=atkHref(dispatch_url("table.cp_ville_pays", "edit", array ("atkselector" => "type_cp_ville_pays.id='" . $id_ville . "'" )),
					$lieu,SESSION_NESTED, false, 'target="main"') ;
		}
		if ( isset($id_lieu)	)
		{
			$data = $db->getrows(
					"SELECT  l.adresse1, l.adresse2, l.longitude, l.latitude, cp.ville, cp.code_postal,tp.code_iso
					from lieu l, type_cp_ville_pays cp, type_pays tp
					where l.id=$id_lieu
					and l.id_ville=cp.id
					and cp.id_pays=tp.id") ;
			$longitude=$data[0]["longitude"];
			$latitude=$data[0]["latitude"];
			$adresse1=$data[0]["adresse1"];
			$adresse2=$data[0]["adresse2"];
			$nom_ville=$data[0]["ville"];
			$code_postal=$data[0]["code_postal"];
			$code_pays=$data[0]["code_iso"];
			$lieu=$adresse1.' '.$code_postal.' '.$nom_ville.' '.$code_pays;
			$href_lieu_observation=atkHref(dispatch_url("individu.lieu", "edit", array ("atkselector" => "lieu.id='" . $id_lieu . "'" )),
					$lieu,SESSION_NESTED, false, 'target="main"') ;
		}

		if ( isset($id_point_observation)	)
		{
			$data = $db->getrows(
					"SELECT po.libelle, l.adresse1, l.adresse2, l.longitude, l.latitude, cp.ville, cp.code_postal,tp.code_iso
					from biodiversite_point_observation po, lieu l, type_cp_ville_pays cp, type_pays tp
					where po.id=$id_point_observation
					and po.id_lieu=l.id
					and l.id_ville=cp.id
					and cp.id_pays=tp.id") ;

			$longitude=$data[0]["longitude"];
			$latitude=$data[0]["latitude"];
			$libelle_point_observation=$data[0]["libelle"];
			$adresse1=$data[0]["adresse1"];
			$adresse2=$data[0]["adresse2"];
			$nom_ville=$data[0]["ville"];
			$code_postal=$data[0]["code_postal"];
			$code_pays=$data[0]["code_iso"];
			$lieu=$libelle_point_observation.' '.$adresse1.' '.$code_postal.' '.$nom_ville.' '.$code_pays;
			$href_lieu_observation=atkHref(dispatch_url("biodiversite.point_observation", "edit", array ("atkselector" => "biodiversite_point_observation.id='" . $id_point_observation . "'" )),
					$lieu,SESSION_NESTED, false, 'target="main"') ;
		}

		if ( isset($ob_latitude)	)
		{
			$latitude=$ob_latitude;
			$lieu=$latitude;
		}

		if ( isset($ob_longitude)	)
		{
			$longitude=$ob_longitude;
			$lieu.=' '.$longitude;
		}

		if (isset ($nb_observations)) {
			$observations= href(dispatch_url("biodiversite.observation_detail", "admin", array (
					'atkfilter' => "biodiversite_observation_detail.id_observation='" . $id_observation . "'"
			), "dispatch.php"), '<b>'.text($nb_observations).'</b>', SESSION_NESTED);
		} else {
			$observations='';
		}

		if ($destination=='affichage')
		{

			$href=atkHref(dispatch_url("biodiversite.observation", "edit", array ("atkselector" => "biodiversite_observation.id='" . $id_observation . "'" )),
					$libelle,SESSION_NESTED, false, 'target="main"') ;
			(!empty($libelle)) ? $descripteur='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/observation.png" alt="Observation de la biodiversité" title="Observation de la biodiversité" target="_blank"></img>'.
					"<b>".$href."</b> " : $descripteur="" ;
			($aide_o_n=='o') ? $descripteur.=$this->descripteur_aide('Descripteur_biodiversite_observation','n').'<br />' : $descripteur.='<br />';

			//							$descripteur="Libellé : <b>".$libelle;
			//					$descripteur.="</b><br />";
			$descripteur.="Date : <b>".$date_observation.'</b><br />';


			$descripteur.='Observé par : '.$this->descripteur_individu($id_observateur,'n','n',50) ;

			(!empty($id_organisme_observateur)) ? $descripteur.="<br />De : <b>".$this->descripteur_organisme($id_organisme_observateur,'n','n',50).'</b>' : $descripteur.='' ;

			(!empty($id_organisme_commanditaire)) ? $descripteur.="<br />Pour : <b>".$this->descripteur_organisme($id_organisme_commanditaire,'n','n',50).'</b>' : $descripteur.='' ;


			$lieu= href(dispatch_url("biodiversite.observation_detail", "createMarkerLonLat", array (
					'longitude' => $longitude,
					'latitude' => $latitude,
					'titre' => $libelle
			), "dispatch.php"), '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/earth.png" alt="Coordonnées observation" title="Coordonnées observation" target="_blank"></img>', SESSION_NESTED,null,'target="_blank"');
			$descripteur.="<br />Lieu : <b>".$lieu.$href_lieu_observation;
			$descripteur.="</b><br />";
			$descripteur.="Espèces observées : <b>".$observations."</b>";
			/*					$descripteur=str_replace(' ','&nbsp;',$descripteur);
			 $descripteur=str_replace('<br&nbsp;/>','<br />',$descripteur);
			$descripteur=str_replace('<a&nbsp;href=','<a href=',$descripteur);
			*/
		}
		if ($destination=='rapport')
		{
			$descripteur=array();
			$descripteur["libelle"]=$libelle;
			$descripteur["date_observation"]=$date_observation;
			$descripteur["organisme_observateur"]=$nom_organisme_observateur_rapport;
			$descripteur["organisme_commanditaire"]=$nom_organisme_commanditaire_rapport;
			$descripteur["observateur"]=$nom_observateur_rapport;

			$descripteur["lieu"]='<a href="http://maps.google.com/maps/api/staticmap?&size=1024x1024&maptype=hybrid&zoom=14
					&markers=color:red|color:red|label:A|'.$latitude.','.$longitude.'&sensor=false">'.$lieu.'</a>';
			//					http://maps.google.com/maps/api/staticmap?&size=1024x1024&maptype=hybrid&zoom=14&markers=color:red|color:red|label:C|47.038635,-1.510491&sensor=false
			$descripteur["longitude"]=$longitude;
			$descripteur["latitude"]=$latitude;
			$descripteur["code_departement_protection"]=$code_departement_protection;
			$descripteur["observation_libelle"]=$libelle;



		}

		return  $descripteur;

	}
	function descripteur_biodiversite_web_info($idtaxinomie,$origine="taxinomie",$aide_o_n='o')
	{
		$db = & atkGetDb();
		$rows = $db->getrows("select nom_binomial,nom_francais,nom_anglais, id_taxon_fauna_europaea, id_taxon_conservation_nature, cd_nom from biodiversite_taxinomie where id ='" . $idtaxinomie . "' ");
		$nom=trim($rows[0]["nom_francais"]);
		$nom=str_replace(' ','.',$nom);
		$nom=str_replace('é','e',$nom);
		$nom=str_replace('è','e',$nom);
		$nom=str_replace('ê','e',$nom);
		$nom=str_replace('ë','e',$nom);
		$nom=str_replace('à','a',$nom);
		$nom=str_replace('â','a',$nom);
		$nom=str_replace('ç','c',$nom);
		$nom=str_replace('ù','u',$nom);
		$nom=str_replace('î','i',$nom);
		$nom=str_replace('ï','i',$nom);
		$nom=trim(strtolower($nom));
		$nom=str_replace(" ",".",$nom);
		$target = ' target="_new"';
		$urloiseaux="http://www.oiseaux.net/oiseaux/".$nom.".html" ;
		$retouroiseaux.='<a href="' . $urloiseaux . '"' . $target . '"><font color="ForestGreen"><b>Oiseaux.net</b></font></a>';
		$retouroiseaux.='...';

		$id_taxon_inpn=$rows[0]["cd_nom"];
		if (isset($id_taxon_inpn))
		{
			$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$id_taxon_inpn."" ;
			$retourinpn.='<a href="' . $urlinpn . '"' . $target . '"><font color="ForestGreen"><b>Inventaire_National_du_Patrimoine_Naturel</b></font></a>';
			$retourinpn.='<br /> ';
		}

		$nom_binomial=trim($rows[0]["nom_binomial"]);
		$nom_francais=trim($rows[0]["nom_francais"]);
		$nom_anglais=trim($rows[0]["nom_anglais"]);
		$nom_binomial_plus=str_replace(' ','+',$nom_binomial);
		$nom_binomial_moins=str_replace(' ','_',$nom_binomial);
		$urlwikipedia_en="http://en.wikipedia.org/wiki/".$nom_binomial ;
		$retourwikipedia_en.='<a href="' . $urlwikipedia_en . '"' . $target . '"><font color="ForestGreen"><b>Wikipedia_en</b></font></a>';
		$retourwikipedia_en.='... ';


		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="SELECT code_iso_639_1 from type_langue tl, app_utilisateur u
		where u.id=$userutilisateur and u.id_langue_application=tl.id";
		$data=$db->getrows($sql);
		$urlwikipedia_loc="http://".$data[0]["code_iso_639_1"].".wikipedia.org/wiki/".$nom_binomial ;
		$retourwikipedia_loc.='<a href="' . $urlwikipedia_loc . '"' . $target . '"><font color="ForestGreen"><b>Wikipedia_loc</b></font></a>';
		$retourwikipedia_loc.='<br /> ';


		$nom_wikiwix_en='('.$nom_binomial.") OR ".'('.$nom_anglais.')';
		$urlwikiwix_en="http://fr.wikiwix.com/index.php?lang=en&art=true&disp=article&action=".$nom_wikiwix_en ;
		$retourwikiwix_en.='<a href="' . $urlwikiwix_en . '"' . $target . '"><font color="ForestGreen"><b>wikiwix_en</b></font></a>';
		$retourwikiwix_en.='...';

		$nom_wikiwix_loc='('.$nom_binomial.") OR ".'('.$nom_francais.')';
		$urlwikiwix_loc="http://fr.wikiwix.com/index.php?lang=".$data[0]["code_iso_639_1"]."&art=true&disp=article&action=".$nom_wikiwix_loc;
		$retourwikiwix_loc.='<a href="' . $urlwikiwix_loc . '"' . $target . '"><font color="ForestGreen"><b>wikiwix_loc</b></font></a>';
		$retourwikiwix_loc.='...';

		$nom_wikispecies=$nom_binomial_moins;
		$urlwikispecies="http://species.wikimedia.org/wiki/".$nom_wikispecies;

		$retourwikispecies='<a href="' . $urlwikispecies . '"' . $target . '"><font color="ForestGreen"><b>Wikispecies</b></font></a>';

		$retourwikispecies.='<br />';
		//			$this->p($retourwikispecies);


		$urlgoogle="http://www.google.fr/search?q=".$nom_binomial ;
		$retourgoogle.='<a href="' . $urlgoogle . '"' . $target . '"><font color="ForestGreen"><b>Google</b></font></a>';
		$retourgoogle.='...';

		$urlcola="http://www.catalogueoflife.org/annual-checklist/2010/search/all/key/".$nom_binomial_plus."/match/1" ;
		$retourcola.='<a href="' . $urlcola . '"' . $target . '"><font color="ForestGreen"><b>Catalog_Of_life : annual</b></font></a>';
		$retourcola.='...';

		$urlcold="http://www.catalogueoflife.org/dynamic-checklist/search_results.php?search_string=".$nom_binomial_plus."&hub=GlobalHub" ;
		$retourcold.='<a href="' . $urlcold . '"' . $target . '"><font color="ForestGreen"><b>dynamic</b></font></a>';
		$retourcold.='<br /> ';

		$urlgbif="http://data.gbif.org/ws/rest/taxon/list?scientificname=".$nom_binomial_plus."&hub=GlobalHub" ;
		$retourgbif.='<a href="' . $urlgbif . '"' . $target . '"><font color="ForestGreen"><b>Global_Biodiversity_Information_Facility</b></font></a>';
		$retourgbif.='<br /> ';


		$urleol="http://www.eol.org/search?q=".$nom_binomial_plus ;
		$retoureol.='<a href="' . $urleol . '"' . $target . '"><font color="ForestGreen"><b>Encyclopedy_of_life</b></font></a>';
		$retoureol.='<br /> ';


		$urlbiopix="http://www.biopix.com/Species.asp?Searchtext=".$nom_binomial_plus ;
		$retourbiopix.='<a href="' . $urlbiopix . '"' . $target . '"><font color="ForestGreen"><b>Images_Biopix</b></font></a>';
		$retourbiopix.='...';
		/*
		 $urlbold="http://www.boldsystems.org/views/taxbrowser.php?taxon=".$nom_binomial_plus ;
		$retourbold.='<a href="' . $urlbold . '"' . $target . '"><font color="ForestGreen"><b>Barcode_of_Life_Data_Systems</b></font></a>';
		$retourbold.='<br /> ';
		*/

		$id_taxon_fe=$rows[0]["id_taxon_fauna_europaea"];
		if (isset($id_taxon_fe))
		{
			$urlfauna_europaea="http://www.faunaeur.org/full_results.php?id=".$id_taxon_fe ;
			$retourfauna_europaea.='<a href="' . $urlfauna_europaea . '"' . $target . '"><font color="ForestGreen"><b>Fauna_europaea</b></font></a>';
			$retourfauna_europaea.='...';
		}

		$urltela_botanica="http://www.tela-botanica.org/page:eflore?eflore_nom=".$nom_binomial."&eflore_referentiel=25&eflore_type_nom=nom_scientifique&module=recherche&action=recherche_nom";
		$retourtela_botanica.='<a href="' . $urltela_botanica . '"' . $target . '"><font color="ForestGreen"><b>Tela_botanica</b></font></a>';
		$retourtela_botanica.='<br /> ';
		$id_iucn=$rows[0]["id_taxon_conservation_nature"];
		if (isset($id_taxon_fe))
		{
			$urlconservation_nature="http://www.iucnredlist.org/details/".$id_iucn ;
			$retouriucn.='<a href="' . $urlconservation_nature . '"' . $target . '"><font color="ForestGreen"><b>International_Union_for_Conservation_of_Nature</b></font></a>';
			$retouriucn.='<br /> ';
		}

		$urlxenocanto="http://www.xeno-canto.org/browse.php?query=".$nom_binomial."&pagenumber=&order=taxonomy&view=4";
		$retourxenocantho.='<a href="' . $urlxenocanto . '"' . $target . '"><font color="ForestGreen"><b>Chants_xeno-canto.org</b></font></a>';
		$retourxenocantho.='<br />';
		$urletymology="http://dictionary.reference.com/search?q=".$nom_binomial;
		$retouretymology.='<a href="' . $urletymology . '"' . $target . '"><font color="ForestGreen"><b>Etymology</b></font></a>';
		$retouretymology.='<br /> ';
		$nom_binomial_images=str_replace(' ','+',$nom_binomial);
		$url_imagesgoogle="http://www.google.com/images?hl=fr&gbv=2&tbs=isch:1&sa=3&q=".$nom_binomial_images."&btnG=Recherche+d'images";
		$retourimagesgoogle.='<a href="' . $url_imagesgoogle . '"' . $target . '"><font color="ForestGreen"><b>Images_google</b></font></a>';
		$retourimagesgoogle.='<br /> ';
		if (true === $this->m_newWindow) {
			$target = ' target="_new"';
		}

		//		http://www.boldsystems.org/views/taxbrowser.php?taxon=meles+meles

		$retour=$retourinpn;
		$retour.=$retoureol;
		//			$retour.=$retourbold;
		$retour.=$retourwikispecies;
		$retour.=$retourcola;
		$retour.=$retourcold;
		$retour.=$retourgbif;
		$retour.=$retourfauna_europaea;
		$retour.=$retourtela_botanica;
		$retour.=$retouroiseaux;
		$retour.=$retourxenocantho;
		$retour.=$retourgoogle;
		$retour.=$retourwikipedia_en;
		$retour.=$retourwikipedia_loc;
		$retour.=$retourwikiwix_en;
		$retour.=$retourwikiwix_loc;
		//			$retour.=$retourscholar_en;
		$retour.=$retourbiopix;
		$retour.=$retourimagesgoogle;
		$retour.=$retouretymology;
		($aide_o_n=='o') ? $retour.=' '.$this->descripteur_aide('Descripteur_biodiversite_web_info','n').'<br />' : $retour.='';
		return $retour;
	}

	function decoupe_affichage_colonne($descripteur,$largeur_colonne)
	{
	$descripteur=str_replace(' ','&nbsp;',$descripteur);
		$descripteur=str_replace('<br/>','<br />',$descripteur);
		$descripteur=str_replace('<br>','<br />',$descripteur);
		$descripteur=str_replace('<br&nbsp;/>','<br />',$descripteur);
		$descripteur=str_replace('<a&nbsp;href=','<a href=',$descripteur);
		$descripteur=str_replace('<div&nbsp;','<div ',$descripteur);
		$descripteur=str_replace('<span&nbsp;','<span ',$descripteur);
		$descripteur=str_replace('<p&nbsp;','<p ',$descripteur);
		$descripteur=str_replace('<td&nbsp;','<td ',$descripteur);
		$descripteur=str_replace('<font&nbsp;','<font ',$descripteur);
		$descripteur=str_replace('<img&nbsp;','<img ',$descripteur);
		//			$descripteur=str_replace('-','&#x2011;',$descripteur);
		$chaine='';
		$taillesansbalise=0;
		$tailleavecbalise=0;
		$offset=0;
		$dernieroffsetnbsp=0;
		$dernieroffset_=0;
		$dernieroffsetbr=0;
		$offsetfin=0;
		$comptage=true;
		while (true)
		{
			$car=substr($descripteur,$offset, 1);
			if ($car=='' )
			{
				if ($offset==0)
				{
					break;
				}
				else
				{$offsetfin=$offset;
				}
			}
			if ($car=='<' )
			{
				$comptage=false;
				if (substr($descripteur,$offset, 6)=='<br />' || substr($descripteur,$offset, 6)=='</div>')
				{
					$dernieroffsetbr=$offset;
					$offset+=5;
					$comptage=true;
				}
				if (substr($descripteur,$offset, 7)=='</span>' )
				{
					$dernieroffsetbr=$offset;
					$offset+=6;
					$comptage=true;
				}
			}
			if ($car=='&' && $comptage==true)
			{
				if (substr($descripteur,$offset, 6)=='&nbsp;')
				{
					$dernieroffsetnbsp=$offset;
					$offset+=5;
				}
				//					else
				//						{$comptage=false;}
			}

			if ($car=='&' && $comptage==false)
			{
				if (substr($descripteur,$offset, 6)=='&nbsp;')
				{
					$descripteur=substr($descripteur, 0,$offset).' '.substr($descripteur,$offset+6);
					//					echo $offset;
					//					echo '<br />';
					//					echo $descripteur;
					//					die();
				}

			}



			if (($car=='|' || $car=='_' ) && $comptage==true)
			{
				$dernieroffset_=$offset;
			}
			//			if ($car=='>' || $car==';') $comptage=true;

			if (($comptage==false && $car=='>')) $comptage=true;
			if ($comptage==true) $taillesansbalise++;
			$offset++;


			//		if ($comptage==false) continue;

			if ($offsetfin!=0)
			{
				$chaine.=substr($descripteur,0,$offsetfin);
				$chaineremplie=true;
			}
			elseif ( $comptage==true && $taillesansbalise > $largeur_colonne)
			{
				if( $dernieroffset_ > $dernieroffsetnbsp)
				{
					$chaine.=substr($descripteur,0,$dernieroffset_ ).'<br /> ';
					$offset=$dernieroffset_;
				}
				elseif ($dernieroffset_ < $dernieroffsetnbsp)
				{
					$chaine.=substr($descripteur,0,$dernieroffsetnbsp ).'<br /> ';
					$offset=$dernieroffsetnbsp;
				}
				elseif ($dernieroffset_==$dernieroffsetnbsp && $dernieroffsetnbsp==0)
				{
					$chaine.=substr($descripteur,0,$offset).'<br /> ';
				}
				elseif ($dernieroffset_==$dernieroffsetnbsp && $dernieroffsetnbsp!=0)
				{
					$chaine.=substr($descripteur,0,$dernieroffsetnbsp ).'<br /> ';
					$offset=$dernieroffsetnbsp;
				}
				$chaineremplie=true;
			}
			elseif ($dernieroffsetbr!=0)
			{
				$chaine.=substr($descripteur,0,$offset);
				$chaineremplie=true;
			}
			else
			{$chaineremplie=false;
			}
			if ($chaineremplie==true)
			{
				$descripteur=substr($descripteur,$offset);
				$taillesansbalise=0;
				$dernieroffsetbr=0;
				$dernieroffsetnbsp=0;
				$dernieroffset_=0;
				$offset=0;
			}
		}
		return $chaine;	
		
	}
	function decoupe_div($descripteur, $largeur)
	{
		return '<div style="width:'.($largeur).'px;margin:auto 0;">'.$descripteur."</div>";
	}

	function biodiversite_descendance($idtaxinomie, $mode)
	{
		$db = & atkGetDb();
		$sql="SELECT count(id) as nombre from biodiversite_taxinomie where id_parent='".$idtaxinomie."' ";
		$data=$db->getrows($sql);
		$nombre_descendance=$data[0]["nombre"];
		if (isset ($nombre_descendance)) {
			$ret= href(dispatch_url("biodiversite.taxinomie", "admin", array (
					'atkfilter' => "biodiversite_taxinomie.id_parent='" . $idtaxinomie . "'",
					'view'=> "tout"
			), "dispatch.php"), $nombre_descendance, SESSION_NESTED, false, 'target="main"');
			if ($nombre_descendance!=0)			return '<b>'.$ret.'</b>';
			else return $ret;
		} else {
			return "";
		}
	}
	function action_createMarkerLonLat() {
		$longitude= $this->m_postvars["longitude"];
		$latitude= $this->m_postvars["latitude"];
		$titre= $this->m_postvars["titre"];
		$html= $this->m_postvars["html"];
		include_once (moduleDir("utils") . "class.googlemapapi.inc");
		$map = new GoogleMapAPI('map', 'association_map');
		$map->setAPIKey($this->google_map_key);
		$map->setHeight("800");
		$map->setWidth("1500");
		//$map->disableTypeControls();
		$map->setMapType('hybrid'); // default
		//$map->disableDirections();
		$map->enableZoomEncompass();
		$map->enableOverviewControl();
		$map->addMarkerByCoords($longitude, $latitude, $titre, $html);
		$output1 = & atkOutput :: getInstance();
		$output = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
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
		$output .= "<body onload=\"onLoad()\">";
		$output .= "<font face=\"arial\" size=\"1\" >";
		$output .= "<table border=1>";
		$output .= "<tr><td>";
		$output .= $map->printMap();
		$output .= "</td><td>";
		$output .= $map->printSidebar();
		$output .= "</td></tr>";
		$output .= "</table>";
		$output .= "<font face=\"arial\" size=\"1\" color=\"red\">";
		//		$output .= $missing . " : non géolocalisables";
		//		$output .= $missingnoms;
		//		$output .= "<br />" . $missingadresse . " : sans adresse";
		//		$output .= $missingadressenoms;
		$output .= "</font></body>";
		$output .= "</html>";
		$output1->rawoutput($output);
		$output1->outputFlush();
	}



	/* START NODE MESSAGING */

	/*         // this function is automatically called after a record has been updated
	 function postUpdate($record){
	// notify the user that the record has been updated
	$this->printMessage("L'enregistrement ".$record[$this->primaryKey]." a été modifié");
	return true;
	}

	// this function is automatically called after a record has been deleted
	function postDelete($record){
	// notify the user that the record has been deleted
	$this->printMessage("L'enregistrement ".$record[$this->primaryKey]." a été supprimé");
	return true;
	}

	// this function is automatically called after a record has been added
	function postAdd(&$record){
	$this->getMyLastId($record);
	// notify the user that the record has been created
	$this->printMessage("L'enregistrement ".$record[$this->primaryKey]." a été créé");
	return true;
	}

	/*
	Jorge Garifuna - info@garidigital.com
	created: 9/12/06

	this function obtains the last inserted id of specified table
	*/
	/*        function getMyLastId(&$record){

	$db = &atkGetDb();
	// get the id of the last record that was inserted
	$query = "select max(id) as last_id from ".$this->table;
	$rows = $db->getrows($query);

	if(count($rows)>0){
	$id = $rows[0]["last_id"];
	$record[$this->primary_field] = $id;


	$record["indexkeygg"] = $this->primaryKey."='$id'";
	}
	}
	function printMessage($message, $background_color='#6787B0', $text_color='white'){
	atkMessageQueue::addMessage("<div style='background-color: ".$background_color.";'><b><font color='".$text_color."'>".$message."</font></b></div>"); //     FFAB35
	}
	*/

	function descripteur_ecriture_comptable($id_ecriture, $aide='o')
	{
		$retour="";
		if ($id_ecriture > 0)
		{
			$ecriture_presente_o_n='n';
			$ligne_presente_o_n='n';
			$lien_ecriture="";
			$db = & atkGetDb();
			$data = $db->getrows("SELECT id, id_journal, libelle, id_type_ecriture, id_origine_ecriture FROM organisme_ecriture_comptable where id=" . $id_ecriture);
			$id_journal=$data[0]["id_journal"];
			$libelle=$data[0]["libelle"];
			$id_type_ecriture=$data[0]["id_type_ecriture"];
			$id_origine_ecriture=$data[0]["id_origine_ecriture"];
			if (count($data)>0) {
				$ecriture_presente_o_n='o';
			}
			$data = $db->getrows("SELECT id FROM organisme_ligne_ecriture_comptable where id_ecriture=" . $id_ecriture);
			if (count($data)>0) {
				$ligne_presente_o_n='o';
			}
			if ($ligne_presente_o_n=='o')
			{
				$data = $db->getrows("SELECT sum(debit) as debit, sum(credit) as credit FROM organisme_ligne_ecriture_comptable where id_ecriture=" . $id_ecriture);
				$debit=$data[0]["debit"];
				$credit=$data[0]["credit"];
			}
			if ($ligne_presente_o_n=='o')
			{
				$lien_lignes= href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
						'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $id_ecriture . "'"
				), "dispatch.php"), "Lignes", SESSION_NESTED);

			}
			else
			{$lien_lignes="<span style='color:Red'><b>Pas de lignes</b><br/></span>";
			}
			if ($ecriture_presente_o_n=='o')
			{
				$lien_ecriture= href(dispatch_url("organisme.ecriture_comptable", "admin", array (
						'atkfilter' => "organisme_ecriture_comptable.id='" . $id_ecriture . "'"
				), "dispatch.php"), $libelle." ($id_ecriture)", SESSION_NESTED);
			}
			else
			{$lien_ecriture="<span style='color:Red'><b>Pas d'écriture</b></span>";
			}
			//			 $retour=$id_ecriture.'<br />';
			switch ($id_type_ecriture)
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
			if (!empty($id_origine_ecriture))
			{
				$href_origine=href(dispatch_url($module, "admin", array (
						'atkfilter' => $table.".id='" . $id_origine_ecriture."'" )
						, "dispatch.php"), $module." (".$id_origine_ecriture.")", SESSION_NESTED);
			}
			else {$href_origine='<span style="color:Red"><b>Pas d\'origine ???</b>';
			}

			$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/ecriture.png" alt="Ecriture comptable" title="Ecriture comptable" target="_blank"></img>' ;
			$retour.=" <b>".$lien_ecriture;
			$retour.="<br />".$lien_lignes;
			$debit_credit=' </b>/ Débit = <span style="color:Red"><b>'.$debit.'</span> /</b> Crédit <span style="color:Green">= <b>'.$credit.'</span>';
			if (($debit != $credit) || $debit=="")
			{
				$debit_credit='<span style="color:Red"><b>Débit = '.$debit.'<br />Crédit = '.$credit.'</span></b>';
			}
			$retour.=$debit_credit."</br>";
			$retour.="</b>Origine : <b>".$href_origine."<br />";
			(!empty($id_journal)) ? $retour.="<b>".$this->descripteur_journal_comptable($id_journal,'n') : $retour.='';
			$ligne = $db->getrows("SELECT id FROM organisme_ligne_ecriture_comptable where id_ecriture=" . $id_ecriture);
			for ($i = 0; $i < count($ligne); $i++) {
			 $retour.='<br />'.$this->descripteur_ligne_ecriture_comptable($ligne[$i]["id"],'n');
			}
			//			 $retour=$this->decoupe_affichage_colonne($retour, 20);
			($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_ecriture_comptable','n')."<br />" : $retour.="<br />";

		}
		return $retour;

	}
	function descripteur_ligne_ecriture_comptable($id_ligne_ecriture, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		lec.id,
		lec.id_ecriture,
		lec.id_journal,
		lec.id_compte,
		lec.id_individu,
		lec.id_organisme,
		lec.id_type_reglement,
		lec.numero_piece,
		lec.date_reglement,
		lec.date_operation,
		lec.date_valeur,
		lec.id_type_banque,
		lec.id_remise,
		lec.id_releve,
		lec.debit,
		lec.credit,
		ec.libelle
		from organisme_ligne_ecriture_comptable lec , organisme_ecriture_comptable ec
		Where lec.id_ecriture =ec.id and lec.id=$id_ligne_ecriture";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "edit", array (	'atkselector' => "organisme_ligne_ecriture_comptable.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["id"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/ligne_ecriture.png" alt="Ligne écriture" title="Ligne écriture" target="_blank"></img>'.
				" <b>".$data[0]["libelle"]."<br/></b>Ligne écriture : <b>".$href."</b> <br />" ;
		//					(!empty($data[0]["id_ecriture"])) ? $retour.="</b>Ecriture : <b>".$this->descripteur_ecriture_comptable($data[0]["id_ecriture"],'n')."<br />" : $retour.='';
		//					(!empty($data[0]["id_journal"])) ? $retour.="</b>Journal : <b>".$this->descripteur_journal_comptable($data[0]["id_journal"],'n') : $retour.='';
		(!empty($data[0]["id_compte"])) ? $retour.="</b>Compte : <b>".$this->descripteur_compte_comptable($data[0]["id_compte"],'n') : $retour.='';
		(!empty($data[0]["id_individu"])) ? $retour.="</b>Individu : <b>".$this->descripteur_individu($data[0]["id_individu"],'n','n',100,"commune",'n')."<br />" : $retour.='';

		//					(!empty($data[0]["id_organisme"])) ? $retour.="</b>Organisme : <b>".$this->descripteur_organisme($data[0]["id_organisme"],'n')."<br />" : $retour.='';
		(!empty($data[0]["id_type_reglement"])) ? $retour.="</b>Type règlement : <b>".$this->descripteur_type_reglement($data[0]["id_type_reglement"],'n') : $retour.='';
		(!empty($data[0]["id_type_banque"])) ? $retour.="</b>Banque : <b>".$this->descripteur_type_banque($data[0]["id_type_banque"],'n') : $retour.='';
		(!empty($data[0]["numero_piece"])) ? $retour.="</b>Numéro pièce : <b>".$data[0]["numero_piece"]."<br />" : $retour.='';
		(!empty($data[0]["date_reglement"]) && $data[0]["date_reglement"]!="0000-00-00") ? $retour.="</b>Date réglement : <b>".$data[0]["date_reglement"]."<br />" : $retour.='';
		(!empty($data[0]["date_operation"])) ? $retour.="</b>Date opération : <b>".$data[0]["date_operation"]."<br />" : $retour.='';
		//					(!empty($data[0]["date_valeur"])) ? $retour.="</b>Date valeur : <b>".$data[0]["date_valeur"]."<br />" : $retour.='';
		(!empty($data[0]["id_remise"])) ? $retour.="</b>Remise en banque : <b>".$this->descripteur_remise_banque($data[0]["id_remise"],'n','o') : $retour.='';
		(!empty($data[0]["id_releve"])) ? $retour.="</b>Relevé de banque : <b>".$this->descripteur_releve_banque($data[0]["id_releve"],'n','o') : $retour.='';
		(!empty($data[0]["debit"]) && $data[0]["debit"]!="0.00") ? $retour.="</b>Débit : <b><span style=\"color: red ; font-size:18px;\">".$data[0]["debit"]."<br /></span>" : $retour.='';
		(!empty($data[0]["credit"]) && $data[0]["credit"]!="0.00") ? $retour.="</b>Crédit : <b><span style=\"color: green ; font-size:18px;\">".$data[0]["credit"]."<br /></span>" : $retour.='';
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_ligne_ecriture_comptable','n')."<br />" : $retour.="";

		return $retour;
	}
	/*
	 * function stats_inscriptions_display(&$record, $mode)
	{
		$titre=$this->get_titre_graphique($record);
		$AnMinimum=$this->getAnMinimum($record);

		if ($AnMinimum>0)
		{

			$res = $titre."<table border='1'>";
			$res.= $this->getEnTete($AnMinimum);
			$AnDepart=date("Y");
			// inscriptions
			$res .= "<tr><td class='styletitre'>Inscriptions";
			for($i=$AnMinimum; $i<=$AnDepart; $i++)
			{
		//		$res.='</td><td>'.$this->nombre_format($this->calcul_inscription($record,$i,$mode),"b");
				$res.='</td><td>'.$this->calcul_inscription($record,$i,$mode);
			}
			$res.='</td></tr>';
			// adhésions
			$res .= "<tr><td class='styletitre'>Adhésions";
			for($i=$AnMinimum; $i<=$AnDepart; $i++)

			{
	//			$res.='</td><td>'.$this->nombre_format($this->calcul_adhesion($record,$i,$mode),"b");
				$res.='</td><td>'.$this->calcul_adhesion($record,$i,$mode);
			}
			$res.='</td></tr>';
			// cotisations
			$res .= "<tr><td class='styletitre'>Cotisations";
			for($i=$AnMinimum; $i<=$AnDepart; $i++)
			{
	//			$res.='</td><td>'.$this->nombre_format($this->calcul_cotisation($record,$i,$mode),"b");
				$res.='</td><td>'.$this->calcul_cotisation($record,$i,$mode);
			}
			$res.='</td></tr>';
			// cotisations_federation
			$res .= "<tr><td class='styletitre'>Cotisations Fédération";
			for($i=$AnMinimum; $i<=$AnDepart; $i++)
			{
	//			$res.='</td><td>'.$this->nombre_format($this->calcul_cotisation_federation($record,$i,$mode),"b");
				$res.='</td><td>'.$this->calcul_cotisation_federation($record,$i,$mode);
			}
			$res.='</td></tr>';

			// radiations
			$res .= "<tr><td class='styletitre'>Radiations";
			for($i=$AnMinimum; $i<=$AnDepart; $i++)
			{
	//			$res.='</td><td>'.$this->nombre_format($this->calcul_radiation($record,$i,$mode),"b");
				$res.='</td><td>'.$this->calcul_radiation($record,$i,$mode);
				
			}
			$res.='</td></tr></table>'.$this->getUserStamp('n','o');
			
			
			$record["graphique"]=$this->afficheGraphique($res,$titre);
			
				return $res;
		}
	}

	 */
		
	function descripteur_journal_comptable($id_journal, $aide='o', $long='n')
	{
		$db = & atkGetDb();
//		Rechercher année d'écriture minimum
if ($long=='o')
{
		$sql=" select min(year(e.date_ecriture)) as an_minimum, year( UTC_TIMESTAMP()) as an_exercice from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
where e.id_journal = $id_journal";
		$data = $db->getrows($sql);
		$an_minimum=$data[0]["an_minimum"];
		$an_exercice=$data[0]["an_exercice"];

		($an_minimum >0) ? $difference=$an_exercice-$an_minimum : $difference=0;
		$res = "<table border='1'>";
		$res.="
				<tr>
				<td class='styletitre'>Année</td>
				<td class='styletitre'>Débit</td>
				<td class='styletitre'>Crédit</td>
				<td class='styletitre'>Ecart</td>
				<td class='styletitre'>Ecritures</td>
				<td class='styletitre'>Lignes</td>
				</tr>";
//		if ($an_minimum>0)
//		{
		
			
		for ($i=0;$i<=$difference;$i++)
		{
			$an_exercice_courant=$an_exercice-$i;
			$sql=" select sum(debit) as debit,  sum(credit) as credit  
					 from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
where e.id_journal = $id_journal and l.id_ecriture=e.id and year(e.date_ecriture)=$an_exercice_courant";
		$data = $db->getrows($sql);
		
		$credit=$data[0]["credit"];
		$debit=$data[0]["debit"];
		$ecart=$credit-$debit;
		($ecart!=0)? $couleur=' style="color: red ;"' : $couleur=' style="color: black ;"';
		if ($ecart!=0)
			$ecart="<b>$ecart</b>";
		$an_exercice_courant=$an_exercice-$i;

		
		$sql=" select  count(l.id) as nombre_ligne_ecriture
					 from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
where e.id_journal = $id_journal and l.id_ecriture=e.id and year(e.date_ecriture)=$an_exercice_courant";	
		$data = $db->getrows($sql);
		$nombre_ligne_ecriture=$data[0]["nombre_ligne_ecriture"];
		
		$sql=" select  count(e.id) as nombre_ecriture
		from  organisme_ecriture_comptable e
		where e.id_journal = $id_journal  and year(e.date_ecriture)=$an_exercice_courant";
		$data = $db->getrows($sql);
	//	$nombre_ecriture=$data[0]["nombre_ecriture"];
		$nombre_ecriture=href(dispatch_url("organisme.ecriture_comptable", "admin", array (
		
				'atkfilter' => "id_journal='" . $id_journal. "'  and year(date_ecriture)='" .$an_exercice_courant." '"
		), "dispatch.php"), $data[0]["nombre_ecriture"], SESSION_NESTED, null, ' alt="Ecritures" ');
// $nombre,$options="b",$decimales=0,$blanc_si_zero='o'		
		$res.="<tr>
		<td class='styletitre'>$an_exercice_courant</td>
		<td".$couleur.">".$this->nombre_format ($debit, "b", 2)."</td>
		<td".$couleur.">".$this->nombre_format ($credit, "b", 2)."</td>
		<td".$couleur.">".$this->nombre_format ($ecart, "b", 2)."</td>
		<td>$nombre_ecriture</td>
		<td>$nombre_ligne_ecriture</td>
		</tr>";
		}
		
//		http://www.wikistoma.org/association/dispatch.php?atknodetype=organisme.ecriture_comptable&atkaction=add&atklevel=2&atkprevlevel=1&atkstackid=526cbe86c0d92&
	
//		}
		$res.="</table>";
		$res.="*** Cliquer sur le nombre d'écritures pour voir/créer<br /> des écritures directement dans le journal.<br />";
		
}
else {$res="";}


		$sql="select
		id,id_organisme, id_compte_banque,
		libelle
		from organisme_journal_comptable
		Where organisme_journal_comptable.id=$id_journal";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.journal_comptable", "edit", array (	'atkselector' => "organisme_journal_comptable.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/journal_comptable.png" alt="Journal comptable" title="Journal comptable" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		($data[0]["id_compte_banque"]> 0) ? $retour.="" : $retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />"."<br />";
		($data[0]["id_compte_banque"]> 0) ? $retour.=$this->descripteur_compte_comptable($data[0]["id_compte_banque"],'n','n')."<br />" : $retour.="";
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_journal_comptable','n')."<br />" : $retour.="";
		
		
	//	return $retour."(".$id_journal.")".$tableau;
		return $retour.$res;
	}

	function descripteur_compte_comptable($id_compte, $aide_o_n='o', $long_o_n='n')
	{
		$db = & atkGetDb();
		$sql="select
		oc.id, 
		oc.code,
		oc.id_organisme,
		oc.libelle,
		oc.credit_initial,
		oc.debit_initial,
		oc.usuel,
		tb.libelle as banque,
		oc.rib,
		oc.url_banque,
		oc.code_acces
		from organisme_compte oc LEFT JOIN type_banque tb ON oc.id_banque=tb.id
		Where oc.id=$id_compte
		";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.compte", "edit", array (	'atkselector' => "organisme_compte.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), "<b>".$data[0]["code"]." ". $data[0]["libelle"]."</b>", SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/compte_comptable.png" alt="Compte comptable" title="Compte comptable" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		if ($long_o_n=='o')
		{
		($data[0]["credit_initial"]>0) ?  $retour.=	"</b>Crédit initial : <b>".$data[0]["credit_initial"]."<br/>" : null;
		($data[0]["debit_initial"]>0) ?  $retour.=	"</b>Débit initial : <b>".$data[0]["debit_initial"]."<br/>" : null;
		($data[0]["usuel"]==1) ?  null : $retour.=	"<br/></b>Usuel : <b>Non"."<br/>";
		($data[0]["banque"]=="") ?  null : $retour.=	"</b>Banque : <b>".$data[0]["banque"]."<br/>";
		($data[0]["rib"]=="") ?  null : $retour.=	"</b>Rib : <b>".$data[0]["rib"]."<br/>";
		$url_banque=$data[0]["url_banque"];
		($data[0]["url_banque"]=="") ?  null : $retour.=	"</b>Url banque : <b><a target=\"_blank\" href=\"$url_banque\" >Site internet</a>"."<br/>";
		($data[0]["code_acces"]=="") ?  null : $retour.=	"</b>+url : <b>".$data[0]["code_acces"]."<br/>";
		}
		$retour.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n')."<br />";
			
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_compte_comptable','n')."<br />" : $retour.="";
		return $retour;
	}
	function descripteur_budget($id_budget, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select count(id) as nombre from organisme_budget_ligne
		where id_budget=$id_budget";
		$data = $db->getrows($sql);
		$nombre_budget_ligne=$data[0]["nombre"];
		$href_budget_lignes=href(dispatch_url("organisme.budget_ligne", "admin", array (
				'atkfilter' => "organisme_budget_ligne.id_budget='" . $id_budget . "'"
		), "dispatch.php"), $nombre_budget_ligne, SESSION_NESTED);
		$sql="select
		b.id,
		b.id_organisme,
		b.libelle,
		b.an_budget
		from organisme_budget b 
		Where b.id=$id_budget
		";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.budget", "edit", array (	'atkselector' => "organisme_budget.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), "<b>".$data[0]["libelle"]." (".$data[0]["an_budget"].")</b>", SESSION_NESTED);
			$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/budget-icon.png" alt="Budget" title="Budget" target="_blank"></img>'.
			"<b> ".$href."</b> <br />" ;
			$retour.=	"</b>Détails : <b>".$href_budget_lignes." ";
					($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_budget','n')."<br />" : $retour.="";
					return $retour;
	}
	function descripteur_budget_ligne($id_budget_ligne, $aide_o_n='o')
	{
		$db = & atkGetDb();
		$sql="select
		bl.id,
		bl.id_organisme,
		bl.libelle,
		bl.id_budget,
		bl.id_compte,
		bl.date_budget,
		bl.credit,
		bl.debit,
		bl.motif
		from organisme_budget_ligne bl
		Where bl.id=$id_budget_ligne
		";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("organisme.budget_ligne", "edit", array (	'atkselector' => "organisme_budget_ligne.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), "<b>".$data[0]["libelle"]."</b>", SESSION_NESTED);
			$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/budget-ligne-icon.png" alt="Ligne budget" title="Ligne budget" target="_blank"></img>'.
					"<b> ".$href."</b> <br />" ;
			$retour.="</b>Budget : <b>".$this->descripteur_budget($data[0]["id_budget"],"n");
			$retour.="</b>Compte : <b>".$this->descripteur_compte_comptable($data[0]["id_compte"],"n","n");
			$retour.="</b>Date : <b>".$data[0]["date_budget"];
			$retour.="</b>Crédit : <b>".$data[0]["credit"]." / Décit : ".$data[0]["debit"];
			$table="organisme_budget_ligne";
			$field="</b>motif<b>";
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table='.$table.'&id='.$id.'&field='.$field,'Contenu html',650,650,'yes','no');
		(!empty($data[0]["commentaire_html"])) ? $retour.='<a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Motif"
				title="Motif" ></img><br /></a>' : $retour.='';
			
			($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_budget_ligne','n')."<br />" : $retour.="";
						return $retour;
	}
	

	function descripteur_type_reglement($id_type_reglement, $aide='o')
	{
		$db = & atkGetDb();
		$sql="select
		id,
		libelle
		from type_reglement
		Where type_reglement.id=$id_type_reglement";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("table.type_reglement", "edit", array (	'atkselector' => "type_reglement.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour="<b>".$href."</b> <br />" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_type_reglement','n')."<br />" : $retour.="";
		return $retour;
	}

	function descripteur_type_banque($id_type_banque, $aide='o')
	{
		$db = & atkGetDb();
		$sql="select
		id,
		libelle
		from type_banque
		Where type_banque.id=$id_type_banque";
		$data = $db->getrows($sql);
		$href=href(dispatch_url("table.type_banque", "edit", array (	'atkselector' => "type_banque.id='" . $data[0]["id"]. "'"
		), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/banque.png" alt="Banque" title="Banque" target="_blank"></img>'.
				"<b> ".$href."</b> <br />" ;
		($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_type_banque','n')."<br />" : $retour.="";
		return $retour;
	}

	/*function descripteur_remise_banque($id_remise_banque, $aide='o')
	 {
	$db = & atkGetDb();
	$sql="select
	id,
	libelle
	from organisme_remise_banque
	Where organisme_remise_banque.id=$id_remise_banque";
	$data = $db->getrows($sql);
	$href=href(dispatch_url("organisme.remise_banque", "edit", array (	'atkselector' => "organisme_remise_banque.id='" . $data[0]["id"]. "'"
	), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
	$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/remise_banque.png" alt="Remise en banque" title="Remise en banque" target="_blank"></img>'.
	"<b>".$href."</b> <br />" ;
	($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_remise_banque','n')."<br />" : $retour.="<br />";
	return $retour;		}

	function descripteur_releve_banque($id_releve_banque, $aide='o')
	{
	$db = & atkGetDb();
	$sql="select
	id,
	libelle
	from organisme_releve_banque
	Where organisme_releve_banque.id=$id_remise_banque";
	$data = $db->getrows($sql);
	$href=href(dispatch_url("organisme.releve_banque", "edit", array (	'atkselector' => "organisme_releve_banque.id='" . $data[0]["id"]. "'"
	), "dispatch.php"), $data[0]["libelle"], SESSION_NESTED);
	$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/releve_banque.png" alt="Relevé de banque" title="Relevé de banque" target="_blank"></img>'.
	"<b>".$href."</b> <br />" ;
	($aide_o_n=='o') ? $retour.=$this->descripteur_aide('Descripteur_releve_banque','n')."<br />" : $retour.="<br />";
	return $retour;		}

	*/


	function xmlStringToObject($xmlString) {

		// création du nouvel objet document
		$dom = new DomDocument();

		// chargement à partir du fichier
		//    $dom->load($fileName);
		$dom->loadXML($xmlString);

		// validation à partir de la DTD référencée dans le document.
		// En cas d'erreur, on ne va pas plus loin
		if (!@$dom->validate()) {
			return false;
		}

		// création de l'objet résultat
		$object = new stdClass();

		// on référence l'adresse du fichier source
		$object->source = $fileName;

		// on récupère l'élément racine, on le met dans un membre
		// de l'objet nommé "root"
		$root = $dom->documentElement;
		$object->root = new stdClass();

		// appel d'une fonction récursive qui traduit l'élément XML
		// et passe la main à ses enfants, en parcourant tout l'arbre XML.
		getElement($root, $object->root);

		return $object;
	}
	function xmlgetElement($dom_element, $object_element) {

		// récupération du nom de l'élément
		$object_element->name = $dom_element->nodeName;

		// récupération de la valeur CDATA,
		// en supprimant les espaces de formatage.
		$object_element->textValue = trim($dom_element->firstChild->nodeValue);

		// Récupération des attributs
		if ($dom_element->hasAttributes()) {
			$object_element->attributes = array();
			foreach($dom_element->attributes as $attName=>$dom_attribute) {
				$object_element->attributes[$attName] = $dom_attribute->value;
			}
		}

		// Récupération des éléments fils, et parcours de l'arbre XML
		// on veut length >1 parce que le premier fils est toujours
		// le noeud texte
		if ($dom_element->childNodes->length > 1) {
			$object_element->children = array();
			foreach($dom_element->childNodes as $dom_child) {
				if ($dom_child->nodeType == XML_ELEMENT_NODE) {
					$child_object = new stdClass();
					getElement($dom_child, $child_object);
					array_push($object_element->children, $child_object);
				}
			}
		}
	}


	function utf8_strlen($str) {
		return preg_match_all('/[\x00-\x7F\xC0-\xFD]/', $str, $dummy);
	}
	function transpose($array) {
		if (!is_array($array) || empty($array)) {
			return array();
		}
		else {
			foreach ($array as $row_key => $row) {
				if (is_array($row) && !empty($row)) { //check to see if there is a second dimension
					foreach ($row as $column_key => $element) {
						$transposed_array[$column_key][$row_key] = $element;
					}
				}
				else {
					$transposed_array[0][$row_key] = $row;
				}
			}
			return $transposed_array;
		}
	}
	function date_un_mois_add($date_YYYY_MM)
	{
		$an=substr($date_YYYY_MM, 0,4);
		$mois=substr($date_YYYY_MM, 5,2);
		$mois++;
		if ($mois==13)
		{
			$an++;
			$mois=1;
		}
		return $an."-".str_pad($mois, 2,"0",STR_PAD_LEFT);
	
	}
	function getIndividuCoordinates($id_individu)
	{
		$db = & atkGetDb();
		$sql="SELECT
				nom,
				prenom,
				date_naissance,
				date_deces,
				courriel,
				telephone_fixe,
				telephone_mobile,
				site_internet
				FROM
				individu
				WHERE id=$id_individu
				";
		$data=$db->getrows($sql);
		$arrayIndividu=array();
		$arrayIndividu["nom"]=$this->descripteur_individu($id_individu,'n','n',150,"tableaudebord",'n','n','o');
	//	$arrayIndividu["prenom"]=$data[0]["prenom"];
		$arrayIndividu["date_naissance"]=$data[0]["date_naissance"];
		$arrayIndividu["date_deces"]=$data[0]["date_deces"];
		($data[0]["date_deces"]!="") ? $arrayIndividu["date_naissance"].= '<br>-<br>(<b>'.$data[0]["date_deces"].'</b>)' : null;
		
		($data[0]["telephone_fixe"]!="") ? $arrayIndividu["contacts"].=" ".$this->affiche_telephone_fixe($data[0]["telephone_fixe"]): null;
		($data[0]["telephone_mobile"]!="") ? $arrayIndividu["contacts"].=" ".$this->affiche_telephone_mobile($data[0]["telephone_mobile"]) : null;
		($data[0]["courriel"]!="") ? $arrayIndividu["contacts"].=" ".$this->affiche_courriel($data[0]["courriel"]) : null;
		($data[0]["site_internet"]!="") ? $arrayIndividu["contacts"].=" ".$this->affiche_url($data[0]["site_internet"],"blog.png", "Site personnel : ".$data[0]["site_internet"]) : null;
		$sql="SELECT
				individu_lieu.adresse_defaut_o_n,
				individu_lieu.adresse_personnelle_o_n,
				lieu.adresse1 as adresse1,
				lieu.adresse2 as adresse2,
				lieu.longitude as longitude,
				lieu.latitude as latitude,
				type_cp_ville_pays.code_postal as code_postal,
				type_cp_ville_pays.ville as ville,
				type_cp_ville_pays.province_etat as province,
				type_pays.libelle_anglais as pays
				FROM
				individu_lieu LEFT JOIN lieu ON individu_lieu.id_lieu=lieu.id
				LEFT JOIN type_cp_ville_pays ON lieu.id_ville=type_cp_ville_pays.id
				LEFT JOIN type_pays ON type_cp_ville_pays.id_pays=type_pays.id
				WHERE
				individu_lieu.id_individu=$id_individu
				and (individu_lieu.adresse_defaut_o_n='1' OR individu_lieu.adresse_personnelle_o_n='1')
				";
		$data=$db->getrows($sql);
		for ($i=0;$i<count($data);$i++)
		{
			$arrayIndividu["adresses"]="";
						
			($data[$i]["adresse1"]!="") ? $arrayIndividu["adresses"].=$data[$i]["adresse1"]." - " : null;
			($data[$i]["adresse2"]!="") ? $arrayIndividu["adresses"].=$data[$i]["adresse2"]." - " : null;

			($data[$i]["code_postal"]!="") ? $arrayIndividu["adresses"].=$data[$i]["code_postal"]." " : null;
			($data[$i]["ville"]!="") ? $arrayIndividu["adresses"].=$data[$i]["ville"]." " : null;
			($data[$i]["province"]!="") ? $arrayIndividu["adresses"].=$data[$i]["province"]." " : null;
			($data[$i]["pays"]!="") ? $arrayIndividu["adresses"].=$data[$i]["pays"]." " : null;
			($data[$i]["longitude"]!="") ? $arrayIndividu["contacts"].=' '.$this->affiche_maps_coordonnees($data[$i]["longitude"], $data[$i]["latitude"],$arrayIndividu["adresses"]): null;
	
		}
		return $arrayIndividu;
	}
	function descripteur_individu_sans_lien($id_individu)
	{
//		return "";
		return $this->descripteur_individu($id_individu,'n','n',150,"sans_lien",'n','n','o');
	}
	function descripteur_organisme_sans_lien($id_organisme)
	{
	return $this->descripteur_organisme($id_organisme,'n','n',150,"sans_lien",'o');
	}
	
	function getUserStamp($stampseul_o_n="o",$confidentiel_o_n="n")
	{
				global $g_sessionManager;
				($confidentiel_o_n=='o') ? $confidentiel="<b>CONFIDENTIEL </b>- " : $confidentiel="";
		($stampseul_o_n!='o') ? $g_nom_utilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals") : $g_nom_utilisateur="";
		$date=gmdate('c');
		$date=str_replace("T", " ", $date);
		$date=str_replace("+00:00", " TU", $date);
		$retour=$confidentiel.$g_nom_utilisateur." ".$date;
		return $retour;
	}
	function nombre_format($nombre,$options="b",$decimales=0,$blanc_si_zero='o')
	{
		$nombre=number_format($nombre,$decimales,","," ");
		($nombre==0 && $blanc_si_zero =='o' )?$nombre="" :null;
		if ($options=="b") {$option1="<b>";$finoption1="</b>";}
		if ($options=="i") {$option2="<i>";$finoption2="</i>";}
		if ($options=="u") {$option2="<i>";$finoption2="</u>";}
		if ($options=="bi") {$option1="<b>";$finoption1="</b>";$option2="<i>";$finoption2="</i>";}
		if ($options=="") {$option1="";$finoption1="";$option2="";$finoption2="";}
		$nombre= '<p style="text-align: right; padding-right:3px;padding-left:5px; margin-top:0px; margin-bottom:0px">'.$option1.$option2 . $nombre .$finoption1.$finoption2. "</p>";
		return str_replace("&nbsp;", " ", $nombre);
	}
	
	function sautDePage ()
	{
return '<p style="page-break-after:always;" ></p>';
	}
	function curPageURL() {
		$pageURL = 'http';
		if ($_SERVER["HTTPS"] == "on") {$pageURL .= "s";}
		$pageURL .= "://";
		if ($_SERVER["SERVER_PORT"] != "80") {
			$pageURL .= $_SERVER["SERVER_NAME"].":".$_SERVER["SERVER_PORT"].$_SERVER["REQUEST_URI"];
		} else {
			$pageURL .= $_SERVER["SERVER_NAME"].$_SERVER["REQUEST_URI"];
		}
		return $pageURL;
	}
	function curPageName() {
		return substr($_SERVER["SCRIPT_NAME"],strrpos($_SERVER["SCRIPT_NAME"],"/")+1);
	}
	function admin_liste_operations ($id_organisme, $idindividus)
	{
		$retour.="</b>Opérations sur les individus de la liste<b><br/>";
		$retour.="<ol>";
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '9'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Adresses de courriel</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $idorganisme,
				"idindividus" => $idindividus,
				"atkcode" => '31'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Adresses postales</b></a></li>';
		$url = dispatch_url("organisme.organisme", "mapindividus", array (
				"adresses_actives_o_n" => "o",
				"id" => $id_organisme,
				"idindividus" => $idindividus));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Géolocaliser</b></a></li>';
		$url = dispatch_url("individu.v_individu_lieu", "document", array (
				"atkselector" => "organisme.id=" . $id_organisme,
				"id" => $id_organisme,
				"atkfilter" => "v_individu_lieu.adresse_defaut_o_n='1' and v_individu_lieu.id in ( " . $idindividus . " )",
				"atkdoctpl" => "enveloppe_individus_organisme.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "1"
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Enveloppes</b></a></li>';
		$url = dispatch_url("individu.v_individu_lieu", "document", array (
				"atkselector" => "organisme.id=" . $id_organisme,
				"id" => $id_organisme,
				"atkfilter" => "( v_individu_lieu.courriel='' or v_individu_lieu.courriel is null )
				and v_individu_lieu.adresse_defaut_o_n='1'
				and v_individu_lieu.id in ( " . $idindividus . " )",
				"atkdoctpl" => "enveloppe_individus_organisme.odt",
				"atkdoctpl_prefix_id" => "1",
				"atkcode" => "1"
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Enveloppes pour ceux qui n\'ont pas d\'adresse de courriel</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '106'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Licences golf</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '21'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Noms</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '8'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Ceux qui n\'ont pas d\'adresse postale</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '5'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Ceux qui n\'ont pas d\'adresse de courriel</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '6'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Ceux qui ont une adresse de courriel</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '7'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Ceux qui n\'ont ni d\'adresse de courriel, ni d\'adresse postale</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '200'
		));
		$retour.='<li><a href="'.$url.'" target="_blank" ><b>Exportation des contacts au format Google</b></a></li>';
		$url = dispatch_url("organisme.organisme", "listeecran", array (
				"id" => $id_organisme,
				"idindividus" => $idindividus,
				"atkcode" => '3'
		));
		$retour.='<li><a href="'.$url.'" ><b>Exportation des contacts au format vcard</b></a></li>';
		
		$retour.="</ol>";
		
		return $retour;
		
	}
	function page_output($content, $title=null, $flags=null, $extra_body=null, $extra_header=null)
	{
	$page = & atknew("atk.ui.atkpage");
	$ui = & atkinstance("atk.ui.atkui");
	$output = & atkOutput :: getInstance();
	$page->register_style($ui->stylePath("recordlist.css"));
	$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
	$page->addContent($content);
	($title==null)? $title=atktext('app_title') . ' - ' . atktext('help') : null;
	$output->output($page->render($title, true,$extra_body,$extra_header));
	}
	function affiche_url($url,$icone="blog.png",$titre="")
	{
		($titre=="")? $titre=$url : null;
		if ($url!="")
		{$url='<a href="'.$url.'" target="_blank" >'.'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/'.$icone.'" alt="Contact" title="'.$titre.'" target="_blank"></img></a>';
		}
		else 
		{$url="";
		}
			return $url;
	}
	function affiche_courriel($courriel, $titre="")
	{
		($titre=="")? $titre="Envoyer un courriel à : ".$courriel : null;
		$url='mailto:'.$courriel;
		return $this->affiche_url($url,"courriel.png",$titre);
	}
	function affiche_telephone($telephone, $titre="")
	{
		($titre=="")? $titre="Appeler le téléphone : ".$telephone : null;
		$url='tel:'.$telephone;
		return $this->affiche_url($url,"telephonefixe.png",$titre);
	}
	function affiche_telephone_fixe($telephone, $titre="")
	{
		($titre=="")? $titre="Appeler le fixe : ".$telephone : null;
		$url='tel:'.$telephone;
		return $this->affiche_url($url,"telephonefixe.png",$titre);
	}
	function affiche_telephone_mobile($telephone, $titre="")
	{
		($titre=="")? $titre="Appeler le mobile : ".$telephone : null;
		$url='tel:'.$telephone;
		return $this->affiche_url($url,"telephonemobile.png",$titre);
	}
	
	function affiche_calendrier($calendrier, $titre="")
	{
		($titre=="")? $titre="Afficher le calendrier :".$calendrier : null;
		$url=$calendrier;
		return $this->affiche_url($url,"calendrier.png",$titre);
	}
	
	function affiche_maps_coordonnees($longitude,$latitude,$titre)
	{
		($titre=="")? $titre="Aller sur google maps :".$longitude."/".$latitude : null;
		$url="http://maps.google.fr/maps?hl=fr&q=".$latitude.",".$longitude."&ie=UTF-8";
		return $this->affiche_url($url,"Google-Maps-icon.png", $titre);
	}
	function descripteur_document_sans_lien($type="organisme",$id_document)
	{
		if ($id_document>0) 
		{$this->descripteur_document($type,$id_document,'n',$lien);
		return $lien;
		}
		else { 
			return "";
		}
	}
	function get_acces_restreint ()
	{
		global $g_sessionManager;
		$g_acces_restreint_o_n=$g_sessionManager->getValue("acces_restreint_o_n", "globals");
		if ($g_acces_restreint_o_n=="1")
		{return true;}
		else 
		{ return false;}
	}
	function get_record_info($id_entite)
	{
		$recs=$this->selectDb($this->m_table.".id=".$id_entite);
	return $recs[0];
	}
	// http://www.localiser-IP.com/?ip=90.59.225.43 
	function ip_geolocalisation($ip)
	{
		$url="http://www.localiser-IP.com/?ip=";
		return '<a href="'.$url.$ip.'" target="_blank" >'.$ip.'</a>';
		
	}
	function get_textes_logs($id_log)
	{
		$db = & atkGetDb();
		$sql="SELECT
	node,
   selector,
   parametres,
   referer,
   query_string,
   error_message
		from
		atkeventlog 
		where
		id=$id_log
		";
		$data=$db->getrows($sql);
		$node=$data[0]["node"];
		$parametres=str_replace("''", "'", $data[0]["parametres"]);
		$array_params=$this->print_r_reverse($parametres);
		(is_array($array_params)) ? $url=dispatch_url($node, "edit", $array_params, "dispatch.php") : $url="";
		$retourtexte='';
		
		($url!="") ? $retourtexte="</b>Lien : <b>".href($url, '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/assocope.ico" alt="Lien"
				title="Lien" ></img>', SESSION_NEW, null, ' target="_blank" ') : null;
			$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=selector','Contenu html',650,650,'yes','no');
		(!empty($data[0]["selector"])) ? $retourtexte.='<br/>Selector : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="Selector"
				title="Selector" ></img></a>' : null;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=parametres','Contenu html',650,650,'yes','no');
		(!empty($data[0]["parametres"])) ? $retourtexte.='<br/>Paramètres : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="parametres"
				title="Paramètres" ></img></a>' : null;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=referer','Contenu html',650,650,'yes','no');
		(!empty($data[0]["referer"])) ? $retourtexte.='<br/>Referer : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="referer"
				title="Referer" ></img></a>' : null;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=query_string','Contenu html',650,650,'yes','no');
		(!empty($data[0]["query_string"])) ? $retourtexte.='<br/>Query string : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="query_string"
				title="Query string" ></img></a>' : null;
		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','table=atkeventlog&id='.$id_log.'&field=error_message','Contenu html',650,650,'yes','no');
		(!empty($data[0]["error_message"])) ? $retourtexte.='<br/>Error message : <a href="'.$popup.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt="error_message"
				title="Error message" ></img></a>' : null;
		return $retourtexte;
	}
	function print_r_reverse($in) {
		$lines = explode("\n", trim($in));
		if (trim($lines[0]) != 'Array') {
			// bottomed out to something that isn't an array
			return $in;
		} else {
			// this is an array, lets parse it
				if (preg_match("/(\s{5,})\(/", $lines[1], $match)) {
				// this is a tested array/recursive call to this function
					// take a set of spaces off the beginning
					$spaces = $match[1];
					$spaces_length = strlen($spaces);
					$lines_total = count($lines);
					for ($i = 0; $i < $lines_total; $i++) {
					if (substr($lines[$i], 0, $spaces_length) == $spaces) {
					$lines[$i] = substr($lines[$i], $spaces_length);
				}
				}
				}
					array_shift($lines); // Array
					array_shift($lines); // (
					array_pop($lines); // )
					$in = implode("\n", $lines);
					// make sure we only match stuff with 4 preceding spaces (stuff for this array and not a nested one)
					preg_match_all("/^\s{4}\[(.+?)\] \=\> /m", $in, $matches, PREG_OFFSET_CAPTURE | PREG_SET_ORDER);
					$pos = array();
					$previous_key = '';
					$in_length = strlen($in);
							// store the following in $pos:
							// array with key = key of the parsed array's item
							// value = array(start position in $in, $end position in $in)
							foreach ($matches as $match) {
							$key = $match[1][0];
							$start = $match[0][1] + strlen($match[0][0]);
					$pos[$key] = array($start, $in_length);
							if ($previous_key != '') $pos[$previous_key][1] = $match[0][1] - 1;
							$previous_key = $key;
							}
							$ret = array();
							foreach ($pos as $key => $where) {
							// recursively see if the parsed out value is an array too
							$ret[$key] =$this->print_r_reverse(substr($in, $where[0], $where[1] - $where[0]));
	}
	return $ret;
	}
	}
	
}

?>