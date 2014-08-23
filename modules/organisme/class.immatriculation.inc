<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class immatriculation extends assMetaNode {
	var $table = "organisme_immatriculation";
	function meta(& $policy) {
		$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function immatriculation() {
		$this->atkMetaNode();
		$this->atkNode("immatriculation",  NF_ADD_LINK  );
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["admin_liste"] = "view";
		$this->add(new atkDummyAttribute("descripteur_immatriculation",0,AF_HIDE_EDIT ),3);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),200);
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), 400);
		$this->add(new atkattribute("immatriculation"), 1000);
		$this->add(new atkUrlAttribute("url", AF_POPUP), 350);
		/*		$this->add(new atkfckattribute("commentaire", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
				'Width' => '100%',
				'Height' => '150px'
		)), 400);
		*/
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,20 );
		$this->setOrder("libelle");
		//		$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
	function descripteur_immatriculation_display($record, $mode)
	{
		$id_immatriculation=trim($record["id"]);

		return $this->descripteur_organisme_immatriculation($id_immatriculation,"o");
	}

	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function action_admin_liste() {

		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("organisme_immatriculation", "i", $this->m_postvars["atkfilter"]);
		$sql=" SELECT i.id as id_entite, i.libelle, i.immatriculation, i.url
		from organisme_immatriculation i
		where $filtre
		order by i.libelle";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$tbl = & atknew("atk.utils.atktablerenderer");
		$datatableau = array ();
		$tbl->setRowClass(1, "superbold");
		$row[] = "#";
		$res .= "<tr><th>#</th><th>Libellé</th><th>Immatriculation</th><th>Url</th><th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";
		$row[] = "Libellé";
		$row[] = "Immatriculation";
		$row[] = "Url";
		$row[] ="Estampille";
		$datatableau[] = $row;
		for ($i=0; $i<count($data); $i++) {
			($data[$i]["url"]!="") ? $lien_reference=$this->affiche_url($data[$i]["url"]) : $lien_reference="";
			$row = array ();
			$row[] =$i+1;
			$row[] ="<b>".$data[$i]["libelle"]."</b>";
			$row[] ="<b>".$this->decoupe_affichage_colonne($data[$i]["immatriculation"], 60	)."</b>";
			$row[] =$lien_reference;
			$row[] =$this->descripteur_module_estampillage($data[$i]["id_entite"], 'n');
			$datatableau[] = $row;
		}
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Immatriculations"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res= $titre.$tbl->render($datatableau,TBL_HEADER, "toc sortable ");
		$res.=$this->getUserStamp('n','o');
		$this->page_output($res);
	}

}
?>