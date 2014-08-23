<?php
useattrib("development.atgfileblobattribute");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgblobattribute");
useattrib("development.atgomanytoonerelation");
include_once (moduleDir("application")."class.document_proto.inc");
class document extends document_proto {
	var $table = "organisme_document";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "file_lock_id", "file_lock_date", "file_extension", "file_name", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("file_content", "file_lock_date", "file_lock_id", AF_HIDE);
			
	}
	function document() {
		global $ATK_VARS,$g_user;

		$this->document_proto("document",null);

		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (

						"libelle",
						"id_type_document",
						"id_individu_auteur",
						"id_organisme",
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
						"date_upload",
						"id_upload")

		), AF_NO_LABEL));

		// $this->add(new atkAttribute("id",AF_SEARCHABLE),null,21);
		$this->add(new atkDummyAttribute("descripteur_document","",AF_COMPACT),null,10);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE| AF_OBLIGATORY ));
		$this->add(new atkUrlAttribute("url_document", AF_POPUP | AF_SEARCHABLE),30);
		$this->add(new atkfckattribute("contenu_html", "",AF_HIDE_LIST| AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '750px',
				'Height' => '250px'
		) ),null,30);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),null,40);
		$this->add(new atkManyToOneRelation("id_type_document", "table.type_document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY| AF_COMPACT),null,19);
		$this->add(new atkManyToOneRelation("id_individu_auteur", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD ),null,60);
		$this->add(new atkUrlAttribute("url_upload",AF_POPUP),null,70);
		$this->add(new atkDateAttribute("date_upload","Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING ),null,80);
		$this->add(new atkManyToOneRelation("id_upload", "individu.individu", AF_SEARCHABLE| AF_FORCE_LOAD),null,90 );

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,20 );
		$this->setOrder(" organisme_document.date_modification DESC ");
		$this->m_securityMap["upload"] = "view";
		$this->m_securityMap["admin_liste"] = "view";

	}
	function descripteur_document_display($record, $mode)
	{
		return $this->decoupe_affichage_colonne($this->descripteur_document('organisme',$record["id"], 'o'),150);
	}

	function descriptor_def() {
		return "[libelle] - [id_organisme.nom]";
	}
	function id_individu_auteur_display($record, $mode) {
		(!empty($record["id_individu_auteur"])) ? $retour=$this->descripteur_individu($record["id_individu_auteur"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function contenu_html_display($record, $mode)
	{
		$retour=null;
		if ( strlen($record["contenu_html"])>0)
		{
			$retour= href(dispatch_url("organisme.document","edit",array("atkselector"=>$this->primaryKey($record),


			)),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);
		}
		return $retour;
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		$mraactions['delete'] = "delete";
		global $g_sessionManager;
		$uploads_organismes= $g_sessionManager->getValue("uploads_organismes_o_n", "globals");
		// 		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		($uploads_organismes==1) ? $mraactions['upload'] = "upload" : null;
		($uploads_organismes==1) ? $actions["upload"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=upload&atkselector=[pk]", SESSION_NESTED)
		: null;
	}
	function action_upload() {
		$retour=$this->get_row_selection_information(false);
		//		$this->p($retour);
		for ($i = 0; $i < count($retour["selectors"]); $i++) {
			$id_document_selector=$retour["selectors"][$i];
			$url_upload=$this->getAttribute("file_name")->fichier_upload($id_document_selector,"organisme");
			$resultat.=$url_upload.'</br>';
		}
		$resultat=$i." fichier(s) uploadé(s) : </br>".$resultat;
		$this->redirect();
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];

		$filtre=str_replace("organisme_document", "od", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		od.id as id_entite,
		od.id_organisme as id_organisme,
		o.nom as organisme,
		od.libelle,
		td.libelle as libelle_type ,
		od.file_name,
		od.file_extension,
		od.file_size,
		od.url_document,
		od.url_upload,
		od.date_upload,
		od.id_upload,
		od.id_individu_auteur,
		od.date_creation
		from
		organisme_document od
		LEFT JOIN type_document td ON od.id_type_document=td.id
		LEFT JOIN organisme o ON od.id_organisme=o.id
		where		$filtre
		order by od.date_creation 	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Titre</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Fichier</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Url</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Téléchargé</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Auteur</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Date</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$idindividus.=$data[$i]["id_individu_auteur"].",";
			$res2.= "<tr><td>".($i+1);
			$res2.='</td><td>'.$data[$i]["libelle_type"];
			$res2.='</td><td>'.$this->descripteur_document_sans_lien("organisme",$data[$i]["id_entite"]);
			$fichier="</b>Nom : <b>".$data[$i]["file_name"]."<br/></b>Extension : <b>".$data[$i]["file_extension"]."<br/></b>Taille : <b>".$data[$i]["file_size"];
			$res2.='</td><td>'.$fichier;
			$res2.='</td><td>'.$this->affiche_url($data[$i]["url_document"],"Network-Download-icon.png");
			$upload="</b><br/>à : <b>".$this->affiche_url($data[$i]["url_upload"])."<br/></b>le : <b>".$data[$i]["date_upload"]."<br/></b>par : <b>".$this->descripteur_individu_sans_lien($data[$i]["id_upload"]);
			$res2.='</td><td>'.$upload;
			$res2.='</td><td>'.$this->descripteur_individu_sans_lien($data[$i]["id_individu_auteur"]);
			$res2.='</td><td>'.$data[$i]["date_creation"];
			$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
			$res2.='</td></tr>';
		}

		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Documents de l'organisme "." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);

	}

}
?>