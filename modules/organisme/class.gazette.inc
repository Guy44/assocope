<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgFileManyToOneRelation");
class gazette extends assMetaNode {
	var $table = "organisme_gazette";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "preparation", AF_HIDE_LIST);
	}
	function gazette() {
		$this->atkMetaNode();
		$this->atkNode("gazette",  NF_ADD_LINK  );
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["admin_liste"] = "view";
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atgFileManyToOneRelation("id_document", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkDateAttribute("date_prevue", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_envoi", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkManyToOneRelation("id_type_audience", "table.audience", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" date_prevue DESC ");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_gazette", "og", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		og.id	as id_entite,
		og.libelle as libelle_gazette,
		og.preparation,
		og.id_document,
		og.date_prevue,
		og.date_envoi,
		ta.libelle as libelle_audience,
		o.id as id_organisme,
		o.nom as organisme
		from
		organisme_gazette og
		LEFT JOIN type_audience ta ON og.id_type_audience=ta.id
		LEFT JOIN organisme o ON og.id_organisme=o.id
		where
		$filtre
		order by date_prevue desc  ";
		$data1=$db->getrows($sql);
		$tbl = & atknew("atk.utils.atktablerenderer");
		$data = array ();
		$tbl->setRowClass(1, "superbold");
		$row[] = "#";
		$row[] ="Libellé";
		$row[] ="Audience";
		$row[] = "Préparation";
		$row[] = "Gazette";
		$row[] = "Prévu le";
		$row[] ="Envoyé le";
		$row[]="Estampille";
		$data[] = $row;
		$titre='Gazette';
		for ($i=0; $i<count($data1); $i++) {
			$row = array ();
			$row[] = $i +1;
			$row[] = '<b>'.$this->decoupe_affichage_colonne($data1[$i]["libelle_gazette"], 50).'</b>';
			$row[] = $data1[$i]["libelle_audience"];
			$row[] = $this->decoupe_affichage_colonne(nl2br($data1[$i]["preparation"]), 60);
			$row[] = $this->decoupe_affichage_colonne($this->descripteur_document_sans_lien("organisme",$data1[$i]["id_document"]), 50);
			$row[] = '<b>'.$data1[$i]["date_prevue"].'</b>';
			$row[] = '<b>'.$data1[$i]["date_envoi"].'</b>';
			$row[] =$this->descripteur_module_estampillage($data1[$i]["id_entite"],'n');
			$data[] = $row;
		}
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Gazettes"." </b>- ".$data1[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res= $titre.$tbl->render($data,TBL_HEADER, "toc sortable ");
		$res.=$this->getUserStamp('n','o');
		$this->page_output($res);
	}
}
?>