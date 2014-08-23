<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class referencement extends assMetaNode {
	var $table = "organisme_referencement";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "contenu", AF_HIDE_LIST);
	}
	function referencement() {
		$this->atkMetaNode();
		$this->atkNode("referencement",  NF_ADD_LINK | NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["admin_liste"] = "view";
		$this->add(new atkDummyAttribute("descripteur_referencement",0,AF_HIDE_EDIT | AF_COMPACT),3);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE| AF_FORCE_LOAD));
		$this->add(new atkUrlAttribute("url", AF_POPUP| AF_FORCE_LOAD));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_FORCE_LOAD),100);
		$this->add(new atgOManyToOneRelation("id_organisme_referencement", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),110);
		$this->add(new atkManyToOneRelation("id_type_etat_referencement", "table.type_etat_referencement", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_FORCE_LOAD),120);
				$this->add(new atkManyToOneRelation("id_interlocuteur", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_referencement", "table.type_referencement", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_FORCE_LOAD));

		$this->add(new atkDateAttribute("date_inscription", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_verification", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_echeance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_resiliation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,20 );
		$this->setOrder("  date_verification ASC ");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_referencement_display($record, $mode) {
		(!empty($record["id_organisme_referencement"])) ? $retour=$this->descripteur_organisme($record["id_organisme_referencement"]["id"],'n') : $retour="";
		return $retour;
	}
		function descripteur_referencement_display($record, $mode) 
	{
		$id_referencement=trim($record["id"]);

		return $descripteur=$this->decoupe_affichage_colonne($this->descripteur_referencement($id_referencement,"o"), 100);
	}	
	function action_admin_liste() {
	
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_referencement", "orf", $this->m_postvars["atkfilter"]);
		$sql=" SELECT
		orf.id as id_entite,
		orf.id_organisme_referencement,
		orf.id_interlocuteur,
		orf.libelle,
		tr.libelle as type_referencement,
		orf.date_inscription,
		orf.url,
		orf.date_verification,
		ter.libelle as etat_referencement,
		orf.contenu,
		orf.date_echeance,
		orf.date_resiliation,
		orf.motif_resiliation,
		DATE(orf.date_modification) as date_modification,
		orf.id_modification
		from organisme_referencement orf
		LEFT JOIN type_referencement tr ON orf.id_type_referencement=tr.id
		LEFT JOIN type_etat_referencement ter ON orf.id_type_etat_referencement=ter.id
		where $filtre
		order by orf.date_inscription desc, orf.date_creation desc ";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
				$tbl = & atknew("atk.utils.atktablerenderer");
				$datatableau = array ();
				$tbl->setRowClass(1, "superbold");
				$row[] = "#";
				$row[] = "Libellé";
				$row[] = "Type";
				$row[] = "Organisme";
				$row[] = "Interlocuteur";
				$row[] = "Inscription";
				$row[] = "Url";
				$row[] = "Vérification";
				$row[] = "Etat";
				$row[] = "Contenu";
				$row[] = "Echéance";
				$row[] = "Résiliation";
				$row[] = "Motif";
				$row[] = "Mis à jour";
				$row[] = "Par";
				$row[] ="Estampille";
				$datatableau[] = $row;
				for ($i=0; $i<count($data); $i++) {
					($data[$i]["url"]!="") ? $lien_reference=$this->affiche_url($data[$i]["url"]) : $lien_reference="";
					$row = array ();
					$row[] =$i+1;
					$row[] =$data[$i]["libelle"];
					$row[] =$data[$i]["type_referencement"];
					$row[] =$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_referencement"]);
					$row[] =$this->descripteur_individu_sans_lien($data[$i]["id_interlocuteur"]);
					$row[] =$data[$i]["date_inscription"];
					$row[] =$lien_reference;
					$row[] =$data[$i]["date_verification"];
					$row[] =$data[$i]["etat_referencement"];
					$row[] =$data[$i]["contenu"];
					$row[] =$data[$i]["date_echeance"];
					$row[] =$data[$i]["date_resiliation"];
					$row[] =$data[$i]["motif_resiliation"];
					$row[] =$data[$i]["date_modification"];
					$row[] =$this->descripteur_individu_utilisateur($data[$i]["id_modification"],'o');
					$row[] =$this->descripteur_module_estampillage($data[$i]["id_entite"], 'n');
					$datatableau[] = $row;
				}
				$criteres=$this->m_postvars["atkfiltre"];
				$titre="<h2><b>"."Référencements"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
				$res= $titre.$tbl->render($datatableau,TBL_HEADER, "toc sortable ");
				$res.=$this->getUserStamp('n','o');
				$this->page_output($res);
	}
}
?>