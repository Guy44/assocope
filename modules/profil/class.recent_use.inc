<?php
class recent_use extends assMetaNode {
	var $table = "app_recent_use";
	function recent_use() {
		$this->atkMetaNode();
		$this->atkNode("recent_use", NF_NO_ADD | NF_MRA);
		$this->add(new atkNumberAttribute("id", AF_PRIMARY | AF_HIDE | AF_FORCE_LOAD));
/*		if ($IdTypeEntite == 1) {
			$this->add(new atgOManyToOneRelation("id_entite", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));
		} else {
			$this->add(new atkManyToOneRelation("id_entite", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));
		}
		*/
//		$this->p($this->m_postvars);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_HIDE| AF_FORCE_LOAD));
		$this->add(new atkParserAttribute("description", "env26", AF_NO_LABEL), NULL);
		$this->add(new atkNumberAttribute("id_entite", NULL));
//		$this->add(new atkManyToOneRelation("id_entite", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkAttribute("date_recent_use", null));
		$this->add(new atkAttribute("type_entite",null));
		$this->add(new atkNumberAttribute("compteur", null));
		include_once (atkconfig("atkroot") . "modules/include/actions.inc");
	$this->add(new atkRowCounter("#"), NULL, 1);
		$this->setOrder("date_recent_use desc");
		$this->setSecurityAlias("individu.individu");
		$this->m_securityMap["selectionner"] = "view";
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);
		$actions =array();
		$mraactions['delete'] = "delete";

	}
	function dispatch($postvars, $fullpage = true) {
		//	$this->p($postvars["atkfilter"]);
		if (substr_count($postvars["atkfilter"], "app_recent_use.type_entite='organisme'") == 1) {
			$this->RecentUseRefresh('organisme');
		}
		if (substr_count($postvars["atkfilter"], "app_recent_use.type_entite='individu'") == 1) {
			$this->RecentUseRefresh('individu');
		}
		if (substr_count($postvars["atkfilter"], "app_recent_use.type_entite='rencontre'") == 1) {
			$this->RecentUseRefresh('rencontre');
		}
		if (substr_count($postvars["atkfilter"], "app_recent_use.type_entite='compte'") == 1) {
			$this->RecentUseRefresh('compte');
		}
	if (substr_count($postvars["atkfilter"], "app_recent_use.type_entite='taxon'") == 1) {
			$this->RecentUseRefresh('taxon');
		}
		return parent :: dispatch($postvars, $fullpage);
	}
	function description_display($record, $prefix = "") {

		$type_entite = $record["type_entite"];
		if ($type_entite == 'organisme') {
			$id_organisme = $record["id_entite"];
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("organisme");
			$query->addJoin("organisme_lieu", "", "organisme.id = organisme_lieu.id_organisme", true);
			$query->addJoin("lieu", "", "organisme_lieu.id_lieu = lieu.id", true);
			$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
			$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
			$query->addField("organisme.nom as nom");
			$query->addField("organisme.sigle as sigle");
			$query->addField("organisme.courriel as courriel");
			$query->addField("organisme.calendrier as calendrier");
			$query->addField("organisme.site_internet as site_internet");
			$query->addField("organisme.telephone as telephone");
			$query->addField("organisme.acces_public_o_n as acces_public_o_n");
			$query->addField("lieu.adresse1 as adresse1");
			$query->addField("type_cp_ville_pays.code_postal as code_postal");
			$query->addField("type_cp_ville_pays.ville as ville");
			$query->addField("type_cp_ville_pays.province_etat as province");
			$query->addField("type_pays.libelle_anglais as pays");
			$query->addCondition("organisme.id='" . $id_organisme . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			$i = 0;
			$identification = $stuff[$i]["nom"];
			if (isset ($stuff[$i]["sigle"]) || $stuff[$i]["sigle"] == "") {
				$identification .= ' - ' . atk_htmlentities($stuff[$i]["sigle"]);
			}
			$description = '<b>' . atk_htmlentities($identification) . '</b>';
			$description = href(dispatch_url("organisme.organisme", "edit", array (
				"atkselector" => "organisme.id='$id_organisme'"
			)), atktext($description, "core"), SESSION_NEW, false, 'target="main"');
			$description .= '&nbsp';
			if (isset ($stuff[$i]["telephone"])) {
				$description .= ' ' . $stuff[$i]["telephone"];
			}
			if (isset ($stuff[$i]["courriel"])) {
				$description .= ' ' . '<a href="mailto:' . $stuff[$i]["courriel"] . '" target="main">  ' . $stuff[$i]["courriel"] . '</a>';
			}
			if (isset ($stuff[$i]["calendrier"])) {
				$description .= ' <a href="' . $stuff[$i]["calendrier"] . '" target="main">  ' . 'calendrier' . '</a>';
			}
			if (isset ($stuff[$i]["site_internet"])) {
				$description .= ' ' . '<a href="' . $stuff[$i]["site_internet"] . '" target="main">  ' . $stuff[$i]["site_internet"] . '</a>';
			}
			if (isset ($stuff[$i]["ville"])) {
				$adresse = ' ' . atk_htmlentities($stuff[$i]["adresse1"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["code_postal"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["ville"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["province"]);
				$adresse .= ' ' . $stuff[$i]["pays"];
				$googlemap = href(dispatch_url("organisme.organisme", "googlemap", array (
					"id" => "" . $id_organisme . ""
				)), atktext($adresse, "core"), SESSION_NEW, false, 'target="main"');
				$description .= ' ' . $googlemap;
				$enveloppe = href(dispatch_url("organisme.v_organisme_lieu", "document", array (
					"atkselector" => "organisme.id='" . $id_organisme . "'",
					"id" => "'" . $id_organisme . "'",
					"atkfilter" => "v_organisme_lieu.id='" . $id_organisme . "'",
					"atkdoctpl" => "enveloppe_organisme.odt",
					"atkdoctpl_prefix_id" => "1",
					"atkcode" => "2"
				)), atktext("enveloppe", "core"), SESSION_NEW, false, 'target="main"');
				$description .= ' ' . $enveloppe;
			}
			$vcard = href(dispatch_url("organisme.organisme", "vcard", array (
				"id" => "" . $id_organisme . ""
			)), atktext("vcard", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $vcard;
			$google = href("http://www.google.fr/search?q=" . $stuff[$i]["nom"] . "&ie=utf-8&oe=utf-8&aq=t", atktext("Google", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $google;
			return $description;
		}
		if ($type_entite == 'individu') {
			$id_individu = $record["id_entite"];
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu");
			$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
			$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
			$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
			$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
			$query->addField("individu.nom as nom");
			$query->addField("individu.prenom as prenom");
			$query->addField("individu.courriel as courriel");
			$query->addField("individu.date_deces as date_deces");
			$query->addField("individu.calendrier as calendrier");
			$query->addField("individu.site_internet as site_internet");
			$query->addField("individu.telephone_fixe as telephone_fixe");
			$query->addField("individu.telephone_mobile as telephone_mobile");
			$query->addField("lieu.adresse1 as adresse1");
			$query->addField("type_cp_ville_pays.code_postal as code_postal");
			$query->addField("type_cp_ville_pays.ville as ville");
			$query->addField("type_cp_ville_pays.province_etat as province");
			$query->addField("type_pays.libelle_anglais as pays");
			$query->addCondition("individu.id='" . $id_individu . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			$i = 0;
			$description = '<b>' . atk_htmlentities($stuff[$i]["prenom"] . ' ' . $stuff[$i]["nom"]) . '</b>';
			$description = href(dispatch_url("individu.individu", "edit", array (
				"atkselector" => "individu.id='$id_individu'"
			)), atktext($description, "core"), SESSION_NEW, false, 'target="main"');
			$description .= '&nbsp';
			if (!empty ($stuff[$i]["date_deces"])) {
				$description .= '<b> dcd le ' . $stuff[$i]["date_deces"] . '</b>';
			}
			$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
				"idcontacte" => "$id_individu",
				"idcontactant" => $record["id_individu"]["id"]
							)), atktext(atk_htmlentities('Contacté'), "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
				"idcontacte" => $record["id_individu"]["id"],
				"idcontactant" => "$id_individu"
			)), atktext(atk_htmlentities('Contactant'), "core"), SESSION_NEW, false, 'target="main"');
			if (isset ($stuff[$i]["telephone_fixe"])) {
				$description .= ' ' . $stuff[$i]["telephone_fixe"] . ' -';
			}
			if (isset ($stuff[$i]["telephone_mobile"])) {
				$description .= ' ' . $stuff[$i]["telephone_mobile"];
			}
			//		$description = atk_htmlentities($description);
			if (isset ($stuff[$i]["courriel"])) {
				$description .= ' ' . href(dispatch_url("individu.contact_i", "add", array (
								"idcontacte" => "$id_individu",
				"idcontactant" => $record["id_individu"]["id"],
					"atgemail" => $stuff[$i]["courriel"]
				)), atktext($stuff[$i]["courriel"], "core"), SESSION_NEW, false, 'target="main"');
			}
			if (isset ($stuff[$i]["calendrier"])) {
				$description .= ' <a href="' . $stuff[$i]["calendrier"] . '" target="main">  ' . 'calendrier' . '</a>';
			}
			if (isset ($stuff[$i]["site_internet"])) {
				$description .= ' <a href="' . $stuff[$i]["site_internet"] . '" target="main">  ' . $stuff[$i]["site_internet"] . '</a>';
			}
			if (isset ($stuff[$i]["ville"])) {
				$adresse = ' ' . atk_htmlentities($stuff[$i]["adresse1"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["code_postal"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["ville"]);
				$adresse .= ' ' . atk_htmlentities($stuff[$i]["province"]);
				$adresse .= ' ' . $stuff[$i]["pays"];
				$googlemap = href(dispatch_url("individu.individu", "googlemap", array (
					"id" => "" . $id_individu . ""
				)), atktext($adresse, "core"), SESSION_NEW, false, 'target="main"');
				$description .= ' ' . $googlemap;
				$enveloppe = href(dispatch_url("individu.v_individu_lieu", "document", array (
					"atkselector" => "individu.id='" . $id_individu . "'",
					"id" => $id_organisme,
					"atkfilter" => "v_individu_lieu.id='" . $id_individu . "'",
					"atkdoctpl" => "enveloppe_individu.odt",
					"atkdoctpl_prefix_id" => "0",
					"atkcode" => "2"
				)), atktext("enveloppe", "core"), SESSION_NEW, false, 'target="main"');
				$description .= ' ' . $enveloppe;
			}
			$fiche = href(dispatch_url("individu.individu", "fiche", array (
				"id" => $id_individu
			)), atktext("fiche", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $fiche;
			$vcard = href(dispatch_url("individu.individu", "vcard", array (
				"id" => $id_individu
			)), atktext("vcard", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $vcard;
			$google = href("http://www.google.fr/search?q=" . $stuff[$i]["nom"] . "+" . $stuff[$i]["prenom"] . "&ie=utf-8&oe=utf-8&aq=t", atktext("Google", "core"), SESSION_NEW, false, 'target="main"');
			$description .= ' ' . $google;
			return $description;
		}
		if ($type_entite == 'rencontre') {
			$id_rencontre = $record["id_entite"];
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("organisme_rencontre");
			$query->addJoin("organisme", "", "organisme.id = organisme_rencontre.id_organisme", true);
			$query->addJoin("type_rencontre", "", "type_rencontre.id = organisme_rencontre.id_type_rencontre", true);
			$query->addField("organisme.nom as nom");
			$query->addField("type_rencontre.libelle as type_renconre");
			$query->addField("organisme_rencontre.libelle as libelle");
			$query->addField("organisme_rencontre.date_debut as date_debut");
			$query->addField("organisme_rencontre.date_fin as date_fin");
			$query->addField("organisme_rencontre.heure_debut as heure_debut");
			$query->addField("organisme_rencontre.heure_fin as heure_fin");
			$query->addField("organisme_rencontre.lieu_texte as lieu");
			$query->addCondition("organisme_rencontre.id='" . $id_rencontre . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			$i = 0;

			
			$identification = $stuff[$i]["nom"];
			$description ="<b>".atk_htmlentities($identification)."</b><br />";
			$description .= " " . $stuff[$i]["libelle"];
			$description .= " (" . $stuff[$i]["type_renconre"] . ")"."<br />";
			$description .= " du " . $stuff[$i]["date_debut"];
			$description .= " à " . $stuff[$i]["heure_debut"];
			$description .= " au " . $stuff[$i]["date_fin"];
			$description .= " à " . $stuff[$i]["heure_fin"]."<br />";
			$description .= " à " . $stuff[$i]["lieu"];
			$description = href(dispatch_url("organisme.rencontre", "edit", array (
				"atkselector" => "organisme_rencontre.id='$id_rencontre'"
			)), atktext($description, "core"), SESSION_NEW, false, 'target="main"');
			$description .= '&nbsp';
			return $description;
		}
		if ($type_entite == 'compte') {
			$id_compte = $record["id_entite"];
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("organisme_compte");
			$query->addJoin("organisme", "", "organisme.id = organisme_compte.id_organisme", true);
			$query->addField("organisme.nom as nom");
			$query->addField("organisme_compte.code as code");
			$query->addField("organisme_compte.libelle as libelle");
			$query->addCondition("organisme_compte.id='" . $id_compte . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			$i = 0;
			$identification = $stuff[$i]["nom"];
			$identification .= " " . $stuff[$i]["code"];
			$identification .= " (" . $stuff[$i]["libelle"] . ")";
			$description = '<b>' . atk_htmlentities($identification) . '</b>';
			$description = href(dispatch_url("organisme.compte", "edit", array (
				"atkselector" => "organisme_compte.id='$id_compte'"
			)), atktext($description, "core"), SESSION_NEW, false, 'target="main"');
			$description .= '&nbsp';
			return $description;
		}
		
	if ($type_entite == 'taxon') {
			$id_taxon = $record["id_entite"];
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("biodiversite_taxinomie");
			$query->addField("inpn_nom_complet as nom");
			$query->addField("nom_binomial as nom_binomial");
			$query->addField("nom_francais as nom_francais");
			$query->addCondition("id='" . $id_taxon . "'");
			$sql = ($query->buildSelect());
			$stuff = $db->getrows($sql);
			$i = 0;
			$identification = $stuff[$i]["nom_binomial"];
			$identification .= " " . $stuff[$i]["nom_francais"];
			$identification .= " (" . $stuff[$i]["inpn_nom_complet"] . ")";
			$description = '<b>' . atk_htmlentities($identification) . '</b>';
			$description = href(dispatch_url("biodiversite.taxinomie", "edit", array (
				"atkselector" => "biodiversite_taxinomie='$id_taxon'"
			)), atktext($description, "core"), SESSION_NEW, false, 'target="main"');
			$description .= '&nbsp';
			return $description;
		}
	}
function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();
	//	$this->p($select);
		foreach ($select as $id_variable) {
			$sql="select id_entite from app_recent_use
				 where $id_variable and type_entite='individu' ";
	//		$this->p($sql);
		$data = $db->getrows($sql);
			$idindividus .= $data[0]["id_entite"] . ',';
		}
		
		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		
		$idorganisme = "";
	return true;
	}
	
	
}
?>