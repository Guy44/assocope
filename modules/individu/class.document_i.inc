<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgblobattribute");
useattrib("development.atgfileblobattribute");
include_once (moduleDir("application")."class.document_proto.inc");
class document_i extends document_proto {
	var $table = "individu_document";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "file_lock_id", "file_lock_date", "file_extension", "file_name", AF_READONLY);
		$policy->addFlags("file_content", "file_lock_date", "file_lock_id", AF_HIDE);
	}
	function document_i() {
		global $ATK_VARS,$g_user;

		$this->document_proto("document_i",null);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (

						"libelle",
						"id_type_document",

						"id_individu",
						"url_document",
						"file_content",
						"file_extension",
						"file_size",
						"file_name"
				),
				"Descripteurs" => array (
						"descripteur_document"
				),
				"Contenu" => array (
						"contenu_html"),
				"Upload" => array (
						"url_upload",
						"date_upload")

		), AF_NO_LABEL));

		$this->add(new atkDummyAttribute("descripteur_document",0,AF_COMPACT),null,10);

		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY ),null,30);
		$this->add(new atkManyToOneRelation("id_type_document", "table.type_document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY|AF_COMPACT),null,19);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),null,50);

		$this->add(new atkfckattribute("contenu_html", "",AF_HIDE_LIST| AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '250px'
		) ),null,30);

		$this->add(new atkUrlAttribute("url_document", AF_POPUP | AF_SEARCHABLE),30);
		$this->add(new atkUrlAttribute("url_upload",AF_POPUP),null,70);
		$this->add(new atkDateAttribute("date_upload","Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING ),null,80);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,20 );

		include_once (atkconfig("atkroot") . "modules/include/useronly.inc");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
			
		$this->setOrder("individu_document.date_modification DESC");
		$this->m_securityMap["display"] = "view";
		$this->m_securityMap["upload"] = "view";
	}
	function descripteur_document_display($record, $mode)
	{
		return $this->decoupe_affichage_colonne($this->descripteur_document('individu',$record["id"], 'o'),150);
	}
	function contenu_html_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["contenu_html"])>0)
		{
			$retour= href(dispatch_url("individu.document","edit",array("atkselector"=>$this->primaryKey($record),


			)),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		return $retour;
	}

	function descriptor_def() {
		return "[date_modification.year]-[date_modification.month]-[date_modification.day] - [id_individu.nom] [id_individu.prenom] - [libelle] ";
	}

	function recordActions($rec, &$actions, &$mraactions)
	{
		$mraactions['delete'] = "delete";
		global $g_sessionManager;
		$uploads_utilisateurs = $g_sessionManager->getValue("uploads_utilisateurs_o_n", "globals");
		($uploads_utilisateurs==1) ? $mraactions['upload'] = "upload" : null;
		($uploads_utilisateurs==1) ? $actions["upload"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=upload&atkselector=[pk]", SESSION_NESTED)
		: null;
	}
	function action_upload() {
		$retour=$this->get_row_selection_information(false);
		//		$this->p($retour);
		for ($i = 0; $i < count($retour["selectors"]); $i++) {
			$id_document_selector=$retour["selectors"][$i];
			$url_upload=$this->getAttribute("file_name")->fichier_upload($id_document_selector,"utilisateur");
			$resultat.=$url_upload.'</br>';
		}
		$resultat=$i." fichier(s) uploadé(s) : </br>".$resultat;
		$this->redirect();
	}

	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>