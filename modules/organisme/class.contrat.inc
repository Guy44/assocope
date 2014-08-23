<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgFileManyToOneRelation");
class contrat extends assMetaNode {
	var $table = "organisme_contrat";
	function meta(& $policy) {
		$policy->addFlags("libelle", "reference_contrat", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "motif_souscription", AF_HIDE_LIST);
	}
	function contrat() {
		$this->atkMetaNode();
		$this->atkNode("contrat", NF_MRA | NF_ADD_LINK |NF_ADDAFTERADD );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkDummyAttribute("descripteur_contrat",0,AF_HIDE_EDIT ),3);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
		$this->add(new atkManyToOneRelation("id_individu_conventionne", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),210);

		$this->add(new atgOManyToOneRelation("id_organisme_contrat", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),220);
		$this->add(new atkManyToOneRelation("id_interlocuteur", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),230);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),240);
		$this->add(new atkManyToOneRelation("id_type_contrat", "table.type_contrat", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY ),250);
		$this->add(new atkAttribute("reference_contrat", AF_SEARCHABLE),260);
		$this->add(new atkAttribute("avenant", AF_SEARCHABLE),261);
		$this->add(new atgFileManyToOneRelation("id_document", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),262);
		$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.lieu_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_RELATION_AUTOCOMPLETE ),265);

		$this->add(new atkDateAttribute("date_souscription", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),270);
		$this->add(new atkDateAttribute("date_echeance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),280);
		$this->add(new atkDateAttribute("date_resiliation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),290);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,20 );
		$this->m_securityMap["liste_organismes_souscripteurs"] = "view";
		$this->m_securityMap["liste_organismes_contractants"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		$this->setOrder(" date_echeance ASC ");

	}
	function descriptor_def() {
		return " [libelle] [reference_contrat]";
	}
	function rowColor($record) {
		if (
				($record["date_echeance"]!="" &&  $this->dateatktodb($record["date_echeance"],false) < gmdate('Y-m-d'))
				|| ($record["date_resiliation"]!="" && $this->dateatktodb($record["date_resiliation"],false) < gmdate('Y-m-d'))
		)
		{
			return $this->couleurarchive;
		}
	}

	function id_individu_conventionne_display($record, $mode) {
		(!empty($record["id_individu_conventionne"])) ? $retour=$this->descripteur_individu($record["id_individu_conventionne"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_interlocuteur_display($record, $mode) {
		(!empty($record["id_interlocuteur"])) ? $retour=$this->descripteur_individu($record["id_interlocuteur"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_contrat_display($record, $mode) {
		(!empty($record["id_organisme_contrat"])) ? $retour=$this->descripteur_organisme($record["id_organisme_contrat"]["id"],'n') : $retour="";
		return $retour;
	}


	function validate(&$record, $mode)
	{
		//	$this->p($record);
		if ($record["id_type_contrat"]["id"]=='6' && $record["id_lieu_rencontre"]=="" )
		{
			triggerError($record, "id_lieu_rencontre", "Le local est obligatoire pour une réservation de local");
				
		}
		else
		{
			parent::validate($record,$mode);
		}
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Résilié ou échu ';
		return $legende.$retour;

	}

	function recordActions($rec, &$actions, &$mraactions)
	{
		$mraactions['liste_organismes_contractants'] = "liste_organismes_contractants";
		$mraactions['liste_organismes_souscripteurs'] = "liste_organismes_souscripteurs";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}

	function action_liste_organismes_contractants() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
		}
		$idcontrats = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_organisme_contrat from organisme_contrat
				where  id in (' . $idcontrats . ')';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidorganisme .= $data[$i]["id_organisme_contrat"] . ',';
		}
		$idorganismes = substr($chaineidorganisme, 0, strlen($chaineidorganisme) - 1);
		$url = dispatch_url("organisme.organisme", "liste_organismes", array (
				"idorganismes" => $idorganismes,
				"atkcode" => 'liste_organismes',
				"atkexport" => 'n'
		));
		header("Location: $url");
		exit;
	}
	function action_liste_organismes_souscripteurs() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
		}
		$idcontrats = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_organisme from organisme_contrat
				where  id in (' . $idcontrats . ')';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidorganisme .= $data[$i]["id_organisme"] . ',';
		}
		$idorganismes = substr($chaineidorganisme, 0, strlen($chaineidorganisme) - 1);
		$url = dispatch_url("organisme.organisme", "liste_organismes", array (
				"idorganismes" => $idorganismes,
				"atkcode" => 'liste_organismes',
				"atkexport" => 'n'
		));
		header("Location: $url");
		exit;
	}

	function descripteur_contrat_display($record, $mode)
	{
		$id_contrat=trim($record["id"]);

		return $this->descripteur_organisme_contrat($id_contrat,"o");
	}
	function action_admin_liste() {
	
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_contrat", "c", $this->m_postvars["atkfilter"]);
		
		$sql=" SELECT
		c.id as id_entite,
		c.libelle,
		tc.libelle as type_contrat,
		c.id_organisme_contrat,
		c.id_interlocuteur,
		c.id_individu_conventionne,
		c.reference_contrat,
		c.avenant,
		c.date_souscription,
		c.motif_souscription,
		c.montant,
		c.periodicite,
		c.date_echeance,
		c.date_resiliation,
		c.motif_resiliation,
		c.id_document,
		c.id_lieu_rencontre
		from organisme_contrat c
		LEFT JOIN type_contrat tc ON c.id_type_contrat=tc.id
		where  $filtre
		order by c.date_souscription desc, c.date_creation desc";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$tbl = & atknew("atk.utils.atktablerenderer");
		$datatableau = array ();
		$tbl->setRowClass(1, "superbold");
		$row[] = "#";
		
		$row[] ="Libellé";
		$row[] ="Type";
		$row[] = "Référence";
		$row[] = "Organisme";
		$row[] = "Interlocuteur";
		$row[] ="Conventionné";
		$row[]="Avenant";
		$row[] ="Souscrit le";
		$row[] ="Motif";
		$row[] = "Montant";
		$row[] = "Périodicité";
		$row[] = "Echéance";
		$row[] ="Résilié le";
		$row[]="Motif";
		$row[] = "Document";
		$row[] = "Lieu";
		$row[] ="Estampille";
		$datatableau[] = $row;
		for ($i=0; $i<count($data); $i++) {
			($data[$i]["id_document"]>0) ? $this->descripteur_document($type='organisme',$data[$i]["id_document"],'n',$lien_document) : $lien_document="";
			($data[$i]["id_lieu_rencontre"]>0) ? $lien_lieu=$this->descripteur_lieu_rencontre_lieu($data[$i]["id_lieu_rencontre"],'n','o') : $lien_lieu="";
			$row = array ();
			$row[] =$i+1;
			
			$row[] ="<b>".$this->decoupe_affichage_colonne($data[$i]["libelle"],50)."</b>";
			$row[] =$data[$i]["type_contrat"];
			$row[] =$data[$i]["reference_contrat"];
			$row[] =$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_contrat"]);
			$row[] =$this->descripteur_individu_sans_lien($data[$i]["id_interlocuteur"]);
			$row[] =$this->descripteur_individu_sans_lien($data[$i]["id_individu_conventionne"]);
			$row[] =$data[$i]["avenant"];
			$row[] ="<b>".$this->decoupe_affichage_colonne($data[$i]["date_souscription"], 15)."</b>";
			$row[] =nl2br($data[$i]["motif_souscription"]);
			$row[] ="<b>".$data[$i]["montant"]."</b>";
			$row[] ="<b>".$data[$i]["periodicite"]."</b>";
			$row[] ="<b>".$data[$i]["date_echeance"]."</b>";
			$row[] ="<b>".$data[$i]["date_resiliation"]."</b>";
			$row[] =$data[$i]["motif_resiliation"];
			$row[] =$lien_document;
			$row[] =$lien_lieu;
			$row[] =$this->descripteur_module_estampillage($data[$i]["id_entite"], 'n');
			$datatableau[] = $row;
		}
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Contrats"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res= $titre.$tbl->render($datatableau,TBL_HEADER, "toc sortable ");
		$res.=$this->getUserStamp('n','o');
		$this->page_output($res);
	}
}

?>