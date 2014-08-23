<?php
useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgNumberExpressionAttribute");
class organisme_simple extends assMetaNode {
	var $table = "organisme";

	function organisme_simple() {
		$this->atkMetaNode();
		$this->atkNode("organisme", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"descripteur_organisme",
				"nom",
				"sigle",
		"siret",
		"siret_recepisse_prefecture",
				"objectif_concis",
				"id_type_organisme",
		
				"telephone",
		"courriel_grp",
		"calendrier_grp",
		"site_internet_grp",
				"acces_public_o_n"
				)
), AF_NO_LABEL));
				$this->add(new atkDummyAttribute("descripteur_organisme",0,AF_HIDE_EDIT ),3);
					
				$this->add(new atkBoolAttribute("acces_public_o_n"));

				$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY | AF_UNIQUE), 100);
				$this->add(new atkAttribute("sigle", AF_SEARCHABLE), 108);
				$this->add(new atkAttribute("siret", AF_HIDE_LIST), 109);
				$this->add(new atkAttribute("siret_recepisse_prefecture", AF_HIDE_LIST), 110);
				$this->add(new atkAttribute("objectif_concis", AF_SEARCHABLE), 7);

				$this->add(new atkManyToOneRelation("id_type_organisme", "table.type_organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK), 5);
				$this->add(new atkAttribute("telephone", AF_SEARCHABLE), 130);
				$this->add(new atkEmailAttribute("courriel", true, AF_SEARCHABLE), 140);
				$this->add(new atkUrlAttribute("calendrier", AF_POPUP | AF_SEARCHABLE), 145);
				$this->add(new atkUrlAttribute("site_internet", AF_POPUP | AF_SEARCHABLE), 150);
			$this->add(new atkParserAttribute("courriel_go",
			atkHref("?atknodetype=individu.contact_i&atkaction=add&atkfilter=individu_contact.id_individu=$id_individu_utilisateur&idcontactant=$id_individu_utilisateur&atgemail=[courriel]&"
			, atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->add(new atkParserAttribute("calendrier_go",atkHref("[calendrier]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);
			$this->add(new atkParserAttribute("site_internet_go",atkHref("[site_internet]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->addFieldSet("courriel_grp"," [courriel.field] [courriel_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("calendrier_grp"," [calendrier.field] [calendrier_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("site_internet_grp"," [site_internet.field] [site_internet_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
//							include_once (atkconfig("atkroot") . "modules/include/association.inc");

			$this->setIndex("nom");
			$this->setOrder("nom");
	}
	function descripteur_organisme_display($record, $mode)
	{
		$id_organisme=trim($record["id"]);

		return $this->descripteur_organisme($id_organisme,"n","o");
	}
	function nom_display($record, $mode)
	{
		$attribute = $this->getAttribute("nom");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}
	function objectif_concis_display($record, $mode)
	{
		$attribute = $this->getAttribute("objectif_concis");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}
	function site_internet_display($record, $mode)
	{
		$attribute = $this->getAttribute("site_internet");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 30);
	}

	function telephone_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone"] . ';">' . $record["telephone"] . '</a>';
	}



	
	function dispatch($postvars, $fullpage=true)
	{
		if ($postvars['atkaction']!='add' && $postvars['atkaction']!='delete' && $postvars['atkaction']!='admin')
		{        $atkselect = $postvars["atkselector"];
		if (count($atkselect)==1)
		{
			$organismeid = sscanf($atkselect, "organisme.id='%d'");
			$organismeId = $organismeid[0];
			$this->RecentUseProcess('organisme', $organismeId);
		} else
		{ $organismeId = 0;}
		}
		else
		{
			$this->RecentUseRefresh('organisme');
		}

		return parent::dispatch($postvars, $fullpage);
	}

	function initial_values() {
		$init_vals = array ();
		$init_vals["prochain_id_ecriture"] = 0;
		$init_vals["prochain_id_recu_fiscal"] = 0;
		$init_vals["prochain_id_inscription"] = 0;
		$init_vals["prochain_id_remise_en_banque"] = 0;
		$init_vals["acces_public_o_n"] = 1;
		return $init_vals;
	}
	function rowColor($record) {
		if ($record["acces_public_o_n"]== "0")
		return $this->couleurorganismeaccesprive;
	}

	function adminHeader()
	{
		$retour=parent::adminHeader();
		if (isset($this->m_postvars['atkfilter']))
		{return '</b>Attention filtre actif :  '.$this->m_postvars['atkfilter'].'<b><br />';	}
	}

	function modifyDataGrid($grid,$mode)
	{

		if ($mode==2)
		{

			$grid->setPostvar("atkfilter",'');
			$this->m_postvars['atkfilter']='';
			// $this->p($grid->getPostvars());
		}

		return true;
	}

	function adminFooter() {
		$retour=parent::adminfooter();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurorganismeaccesprive . '"> <b> Accès privé ';
		return $legende . $retour;
	}


	function action_normalisation() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id, nom , telephone " . " from organisme");
		if (count($data) == 0) {
			return true;
		} else {
			for ($i = 0; $i < count($data); $i++) {
				$data[$i]["nom"] = normalisation_chaine($data[$i]["nom"]);
				$data[$i]["nom"] = addslashes($data[$i]["nom"]);
				$data[$i]["telephone"] = normalisation_telephone($data[$i]["telephone"]);
				$data[$i]["telephone"] = addslashes($data[$i]["telephone"]);
				$db->query("UPDATE organisme" . " set nom='" . $data[$i]["nom"] . "'" . ", telephone='" . $data[$i]["telephone"] . "' where id=" . $data[$i]["id"] . "");
			}
		}
		echo "<br> Normalisation des noms et téléphones terminée.";
	}

	function descriptor_def() {

		return "[nom] ([sigle])";
	}

	function postAdd(&$record)
	{
		$id_entite=$record["id"];
		$this->RecentUseProcess('organisme', $id_entite);

	}
	function postUpdate(&$record)
	{
		$id_entite=$record["id"];
		$this->RecentUseRefresh('organisme');

	}
	function preDelete(&$record)

	{
		$id_entite=$record["id"];
		$this->RecentUseDelete('organisme', $id_entite);
		return true;
	}
	function validate(& $record, $mode) {
		$record["telephone"] = normalisation_telephone($record["telephone"]);
		parent::validate($record, $mode);

	}
	function action_admin($handler) {
		if  (substr($this->m_postvars["atkfilter"],0,5) =="'%@@@")
		{      $searchfields = array("nom","sigle");
		$searchvalue=$this->m_postvars["atkfilter"];
		$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
		$filter = $this->createSearchFilter($searchfields, $searchvalue,$this->table);

		$this->m_postvars["atkfilter"]=$filter;
		}
		$this->addFilter($this->m_postvars["atkfilter"]);
		return $handler->action_admin();
	}

}
?>