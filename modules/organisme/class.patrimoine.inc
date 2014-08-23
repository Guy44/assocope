<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class patrimoine extends assMetaNode {
	var $table = "organisme_patrimoine";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("motif_acquisition", "motif_cession", "commentaire", AF_HIDE_LIST);
	}
	function patrimoine() {
		$this->atkMetaNode();
		$this->atkNode("patrimoine",  NF_ADD_LINK  );
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["admin_liste"] = "view";
		$this->add(new atkDummyAttribute("descripteur_patrimoine",0,AF_HIDE_EDIT ),3);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkDateAttribute("date_acquisition", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_cession", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,20 );
		$this->setOrder(" date_acquisition DESC ");
		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle]";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function descripteur_patrimoine_display($record, $mode) 
	{
		$id_patrimoine=trim($record["id"]);

		return $descripteur=$this->decoupe_affichage_colonne($this->descripteur_patrimoine($id_patrimoine,"o"), 50);
	}	
	function action_admin_liste() {

		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_patrimoine", "p", $this->m_postvars["atkfilter"]);
		$sql=" SELECT
		p.id as id_entite,
		p.libelle,
		p.date_acquisition,
		p.montant_acquisition,
		p.motif_acquisition,
		p.date_cession,
		p.montant_cession,
		p.motif_cession
		from organisme_patrimoine p
		where $filtre
		order by p.date_acquisition";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$tbl = & atknew("atk.utils.atktablerenderer");
		$datatableau = array ();
		$tbl->setRowClass(1, "superbold");
		$row[] = "#";
		$row[] = "Libellé";
		$row[] = "Acquis le";
		$row[] = "Motif";
		$row[] = "Montant";
		$row[] = "Cédé le";
		$row[] = "Motif";
		$row[] = "Montant";
		$row[] ="Estampille";
		$datatableau[] = $row;
		for ($i=0; $i<count($data); $i++) {
			($data[$i]["url"]!="") ? $lien_reference=$this->affiche_url($data[$i]["url"]) : $lien_reference="";
			$row = array ();
			$row[] =$i+1;
			$row[] ="<b>".$data[$i]["libelle"]."</b>";
			$row[] ="<b>".$this->decoupe_affichage_colonne($data[$i]["date_acquisition"],15)."</b>";
			$row[] =$this->decoupe_affichage_colonne($data[$i]["motif_acquisition"],60);
			$row[] ="<b>".$data[$i]["montant_acquisition"]."</b>";
			$row[] ="<b>".$data[$i]["date_cession"]."</b>";
			$row[] =$data[$i]["motif_cession"];
			$row[] ="<b>".$data[$i]["montant_cession"]."</b>";
			$row[] =$this->descripteur_module_estampillage($data[$i]["id_entite"], 'n');
			$datatableau[] = $row;
		}
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Patrimoine"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res= $titre.$tbl->render($datatableau,TBL_HEADER, "toc sortable ");
		$res.=$this->getUserStamp('n','o');
		$this->page_output($res);
	}
}
?>