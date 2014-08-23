<?php

useattrib("development.atgNumberExpressionAttribute");
class utilisateur extends assMetaNode {
	var $table = "app_utilisateur";
	function meta(& $policy) {
		$policy->addFlags("id_individu", "identifiant", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("nombre_de_logins",  AF_READONLY|AF_FORCE_LOAD);
		$policy->setOrder("id_individu");
	}
	function utilisateur() {
		$this->atkMetaNode();
		$this->atkNode("utilisateur",  NF_ADD_LINK | NF_MRA| NF_ADDAFTERADD );

		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"identifiant",
				"id_individu",
				"id_profil",
				"mot_de_passe",
			"id_langue_application",
				"role",
				"courriel",
					"acces_restreint_o_n",
					"url_acces_restreint",
				"log_o_n",
		"debug_o_n",
				"tt_o_n",
		"sticky_tt_o_n",
				"tt_couleur_bg",
		"manytoone_autocomplete_minchars",
		"table_des_matieres_wiki_o_n",
					"stats_page_o_n",
		"trace_db_o_n",
		"contexte_o_n",
		"biodiversite_o_n",
		"golf_o_n",
		"uploads_utilisateurs_o_n",
		"uploads_organismes_o_n",
		"icones_detaillees_o_n",
		"icones_estampillage_o_n",
		"copie_courriel_o_n",
		"courriel_copie",
				"etat",
				"date_dernier_login",
				"nombre_de_logins",
				"theme",
		"google_album_checkpoint",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Logs" => array (
				"log"
				),
			"Contrat" => array (
				"texte_contrat_utilisateur",
				"date_signature_contrat"
				)
				), AF_NO_LABEL));

	//			$this->add(new atkOneToManyRelation("log", "profil.log", "userid", AF_HIDE_LIST));

				$this->add(new atgNumberExpressionAttribute("log", ' select count(id) from atkeventlog
	 where userid =[table].id
					', 0, 0));
				$this->setSecurityAlias("profil.profil");
				$this->add(new atkManyToOneRelation("id_profil", "profil.profil", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
				$this->add(new atkPasswordAttribute("mot_de_passe", true, AF_HIDE_LIST | AF_PASSWORD_NOVALIDATE));
	//			$this->add(new atkPasswordAttribute("google_docs_code", false,  AF_PASSWORD_NO_ENCODE | AF_HIDE_LIST));
				$this->add(new atkManyToOneRelation("id_langue_application", "table.type_langue", AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_SEARCHABLE));
				$this->add(new atkEmailAttribute("courriel",false, AF_SEARCHABLE));
				$this->add(new atkBoolAttribute("acces_restreint_o_n"));
				$this->add(new atkUrlAttribute("url_acces_restreint"));
				$this->add(new atkBoolAttribute("log_o_n"));
				$this->add(new atkBoolAttribute("debug_o_n"));
				$this->add(new atkBoolAttribute("tt_o_n"));
				$this->add(new atkBoolAttribute("sticky_tt_o_n"));
				$this->add(new atkAttribute("tt_couleur_bg"));
				$this->add(new atkBoolAttribute("trace_db_o_n"));
					$this->add(new atkNumberAttribute("manytoone_autocomplete_minchars",null,2,0));
				
				$this->add(new atkBoolAttribute("table_des_matieres_wiki_o_n"));	
				$this->add(new atkBoolAttribute("stats_page_o_n"));
				$this->add(new atkBoolAttribute("contexte_o_n"));
				$this->add(new atkBoolAttribute("biodiversite_o_n"));
				$this->add(new atkBoolAttribute("golf_o_n"));
				$this->add(new atkBoolAttribute("uploads_utilisateurs_o_n"));
				$this->add(new atkBoolAttribute("uploads_organismes_o_n"));
				$this->add(new atkBoolAttribute("icones_detaillees_o_n"));
				$this->add(new atkBoolAttribute("icones_estampillage_o_n"));
				$this->add(new atkBoolAttribute("afficher_portrait_o_n"));
				$this->add(new atkBoolAttribute("copie_courriel_o_n"));
				$this->add(new atkEmailAttribute("courriel_copie", false, AF_SEARCHABLE));
				$this->add(new atkListAttribute("etat", array (
			"actif",
			"inactif"
			), array (), AF_OBLIGATORY));
			$this->add(new atkDateTimeAttribute("date_dernier_login","", "", AF_DATE_STRING | AF_READONLY));
			$themes = getThemes();
			$this->add(new atkListAttribute("theme",$themes,$themes,AF_HIDE_ADD|AF_NO_TRANSLATION));
			$this->add(new atkAttribute("google_album_checkpoint", AF_READONLY));
			$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_SEARCHABLE));
			$this->add(new atkfckattribute("texte_contrat_utilisateur","", AF_SEARCHABLE| AF_READONLY | AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'800px',
                 'Height'=>'300px')));
			$this->add(new atkAttribute("date_signature_contrat", AF_READONLY));
					$this->add(new atkPasswordAttribute("google_docs_code", false,  AF_PASSWORD_NO_ENCODE | AF_HIDE_LIST));

			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->setIndex("id_individu");
			$this->setOrder("app_utilisateur.date_dernier_login desc");
			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["activer"] = "view";
			$this->m_securityMap["desactiver"] = "view";
	}
	function log_display($record, $mode) {
		if (isset ($record["log"])) {
			$ret= href(dispatch_url("profil.log", "admin", array (
				'atkfilter' => "atkeventlog.userid='" . $record['id'] . "'"
				), "dispatch.php"), text($record["log"]), SESSION_NESTED);
				if ($record["log"]!=0)			return '<b>'.$ret.'</b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function validate($record, $mode)
	{
		if ($record["acces_restreint_o_n"]==1 && $record["url_acces_restreint"]=="")
		{		atkTriggerError($record, $this->getAttribute("url_acces_restreint"), "En cas d\'accès restreint vous devez préciser l\'url à lancer");}
		
		if (parent::validate($record, $mode)==true)
		{
						return true;
		}
	}
	function id_individu_display ($record, $mode)
	{
		return $this->descripteur_individu($record["id_individu"]["id"],"n","o",40,"utilisateur");
	}
		
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}

	public function action_activer()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE app_utilisateur set etat='actif',
			 id_modification='".$userutilisateur."',
			date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_desactiver()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE app_utilisateur set etat='inactif',
			 id_modification='".$userutilisateur."',
			date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}

	function courriel_display($record, $mode="")
	{
		if ($mode == "csv")
		return parent::display($record, $mode);

		if ($record["courriel"]!="")
		{

			return href(dispatch_url("individu.contact_i", "add", array (
			"atgemail" => $record["courriel"],
			"atgtable" => 'individu',
			"atgcle" => 'id',
			"atgvaleur" => $record["id_individu"]["id"]
			)), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
		}
		//   return parent::display($record, $mode);
	}

	function rowColor($record) {
		if ($record["etat"] == "actif") {
			return $this->couleuractif;
		}
	}
	function adminFooter()
	{
		$retour=parent::adminfooter();
		$legende='Légende des couleurs : ';
		$legende.='<font color="'. $this->couleuractif.'"> <b> Utilisateur actif '.$retour;

		return $legende;


	}
	function descriptor_def() {
		return "[identifiant]";
	}
	function initial_values() {
		$init_vals = array ();
		$init_vals ["nombre_de_logins"]='0';
		return $init_vals;
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['activer'] = "activer";
		$mraactions['desactiver'] = "desactiver";


	}
}
?>