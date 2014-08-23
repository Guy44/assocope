<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextnomattribute");
class cp_ville_pays extends assMetaNode {
	var $table = "type_cp_ville_pays";
	function meta(& $policy) {
		$policy->addFlags("ville", "code_postal", "province_etat", "id_pays", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function cp_ville_pays() {
		$this->atkMetaNode();
		$this->atkNode("cp_ville_pays",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (

		"Général" => array (
				"ville",
				"code_postal",
				"province_etat",
				"id_pays",
				"longitude",
				"latitude",
				"altitude",
				"meteo",
				"normalisation",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
						"Géolocalisations" => array (
				"geolocalise_ville",
				"geolocalise_cp",
				"geolocalise_departement"
			),	
			"Lieux" => array (
				"lieux"
			)
		), AF_NO_LABEL));
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextNomAttribute("ville", AF_SEARCHABLE), 200);
		$this->add(new atgTextNomAttribute("province_etat", AF_SEARCHABLE), 300);
		$this->add(new atkAttribute("code_postal", AF_SEARCHABLE), 100);
		$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE, 25, 5), 500);
		$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE, 25, 5), 600);
		$this->add(new atkNumberAttribute("altitude", AF_SEARCHABLE, 25, 0), 700);
		$this->add(new atkAttribute("commentaire", AF_HIDE_LIST), 800);
		$this->m_securityMap["normalisation"] = "view";
		$this->m_securityMap["geolocalise_ville"] = "view";
		$this->m_securityMap["geolocalise_cp"] = "view";
		$this->m_securityMap["geolocalise_departement"] = "view";
		$this->add(new atkManyToOneRelation("id_pays", "table.pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), 400);
//		$this->add(new atkManyToOneRelation("id_pays", "table.pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ), 400);
		$this->add(new atkOneToManyRelation("lieux", "individu.lieu", "id_ville", AF_HIDE_LIST));
		$this->add(new atkParserAttribute("geolocalise_ville", href("?atkaction=geolocalise_ville&id=[id]", atktext("geolocalise_ville"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD), 250);
		$this->add(new atkParserAttribute("geolocalise_cp", href("?atkaction=geolocalise_cp&id=[id]", atktext("geolocalise_cp"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD), 150);
		$this->add(new atkParserAttribute("geolocalise_departement", href("?atkaction=geolocalise_departement&id=[id]", atktext("geolocalise_departement"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD), 350);
		$this->add(new atkParserAttribute("meteo", "<a href=\"http://www.meteoconsult.fr/moteur_recherches.php?langue=fr&Nom_Recherche=[ville]+[code_postal]&Cible=france\" target=\"_blank\">meteo</a>", AF_NO_LABEL | AF_HIDE_ADD), 260);
		$this->add(new atkParserAttribute("normalisation", href("?atkaction=normalisation&id=[id]", atktext("normalisation des libellés"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_LIST), 260);
		$this->addUniqueFieldset(array("ville","code_postal","id_pays"));
					include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" code_postal ");
	}
	function action_geolocalise_ville() {
		$idville = $this->m_postvars["id"];
		$user = getUser();
		$iduser = $user["id"];
		if ($idville == 0) {
		} else {
			$selectmapville = "Select 
										tv.id as identity, tv.ville, tv.province_etat, tv.code_postal, tv.longitude, tv.latitude, tv.altitude, tp.libelle_anglais as pays
										from type_cp_ville_pays tv, type_pays tp
										 where tv.id=" . $idville . " and tv.id_pays=tp.id";
		}
		return $this->createMarkers($selectmapville, "ville");
	}
	function action_geolocalise_cp() {
		$idville = $this->m_postvars["id"];
		$user = getUser();
		$iduser = $user["id"];
		if ($idville == 0) {
		} else {
			$selectmapville = "Select 
										tv.id as identity, tv.ville, tv.province_etat, tv.code_postal, tv.longitude, tv.latitude, tv.altitude, tp.libelle_anglais as pays
										from type_cp_ville_pays tv, type_pays tp
										 where tv.code_postal in ( select	code_postal from type_cp_ville_pays where id=" . $idville . " ) and 
										  tv.id_pays=tp.id";
		}
		return $this->createMarkers($selectmapville, "ville");
	}
	function action_geolocalise_departement() {
		$idville = $this->m_postvars["id"];
		$user = getUser();
		$iduser = $user["id"];
		if ($idville == 0) {
		} else {
			$selectmapville = "Select 
										tv.id as identity, tv.ville, tv.province_etat, tv.code_postal, tv.longitude, tv.latitude, tv.altitude, tp.libelle_anglais as pays
										from type_cp_ville_pays tv, type_pays tp
										 where 
								tv.province_etat in 
								( select distinct province_etat
								from type_cp_ville_pays where id=" . $idville . " ) and
								tv.id_pays in (select id_pays from type_cp_ville_pays where id=" . $idville . " )
									and 	  tv.id_pays=tp.id";
		}
		// SUBSTRING(str,pos,len)
		return $this->createMarkers($selectmapville, "ville");
	}
	function createMarkers($select, $type) {
		include_once (moduleDir("utils") . "class.googlemapapi.inc");
		$map = new GoogleMapAPI('map', 'association_map');
		$map->setAPIKey($this->get_map_key());
		$map->setHeight("500");
		$map->setWidth("800");
		//$map->disableTypeControls();
		$map->setMapType('hybrid'); // default
		//$map->disableDirections();
		$map->enableZoomEncompass();
		$map->enableOverviewControl();
		$db = & atkGetDb();
		$r = $db->getrows("$select");
		$user = getUser();
		$iduser = $user["id"];
		$selectutilisateur = "SELECT l.id as idlieu, i.id as identity ,i.nom as nom, i.prenom as prenom ,i.courriel as courriel , i.site_internet as site_internet, i.telephone_fixe as telephone_fixe,i.telephone_mobile as telephone_mobile,l.longitude as longitude" . ", l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" . " from " . "individu i left join individu_lieu il on i.id=il.id_individu
							 left join  lieu l on il.id_lieu=l.id
							left join type_cp_ville_pays c on  l.id_ville =c.id
							left join type_pays p on p.id=c.id_pays " . " where  i.id in (select id_individu from app_utilisateur where id=$iduser)" . "";
		$rutilisateur = $db->getrows("$selectutilisateur");
		$i = count($r);
		for ($j = 0; $j < count($rutilisateur); $j++) {
			$r[$i]['code_postal'] = $rutilisateur[$j]['code_postal'];
			$r[$i]['ville'] = $rutilisateur[$j]['ville'];
			$r[$i]['province_etat'] = $rutilisateur[$j]['province_etat'];
			$r[$i]['pays'] = $rutilisateur[$j]['pays'];
			$r[$i]['longitude'] = $rutilisateur[$j]['longitude'];
			$r[$i]['latitude'] = $rutilisateur[$j]['latitude'];
			$r[$i]['nom'] = $rutilisateur[$j]['nom'];
			$r[$i]['prenom'] = $rutilisateur[$j]['prenom'];
		}
		$missing = 0;
		$missingnoms = "";
		$missingadresse = 0;
		$missingadressenoms = "";
		for ($i = 0; $i < count($r); $i++) {
			$address = $r[$i]['code_postal'] . ", " . $r[$i]['ville'] . ", " . $r[$i]['province_etat'] . ", " . $r[$i]['pays'];
			$html = "<a href='dispatch.php?atknodetype=table.cp_ville_pays&atkaction=edit&atkselector=type_cp_ville_pays.id=" . $r[$i]['identity'] . "'>" . $r[$i]['code_postal'] . "<br />" . $r[$i]['ville'] . "<br />" . $r[$i]['province_etat'] . "</a>" . "<br />" . $r[$i]['pays'] . "<br />";
			$title = $r[$i]['prenom'] . " " . $r[$i]['nom'] . " " . $r[$i]['ville'] . " " . $r[$i]['pays'];
			$longitude = $r[$i]['longitude'];
			$latitude = $r[$i]['latitude'];
			$idville = $r[$i]['identity'];
			if (!isset ($r[$i]['code_postal'])) {
				$missingadresse = $missingadresse +1;
				$missingadressenoms .= "<br /><a href='dispatch.php?atknodetype=table.cp_ville_pays&atkaction=edit&atkselector=type_cp_ville_pays.id=" . $r[$i]['identity'] . "'>" . $r[$i]['ville'] . " " . $r[$i]['pays'] . "</a>";
			} else {
				if (!isset ($longitude)) {
					$coords = array ();
					$coords = $map->geoGetCoords($address);
					$map->putCache($idville, $coords["lon"], $coords["lat"], "ville");
					$longitude = $coords["lon"];
					$latitude = $coords["lat"];
				}
				if (!isset ($longitude) or !isset ($latitude)) {
					$missing = $missing +1;
					$missingnoms .= "<br /><a href='dispatch.php?atknodetype=table.cp_ville_pays&atkaction=edit&atkselector=type_cp_ville_pays.id=" . $r[$i]['idlieu'] . "'>" . $r[$i]['ville'] . " " . $r[$i]['pays'] . "</a>";
				} else {
					$map->addMarkerByCoords($longitude, $latitude, $title, $html);
				}
			}
		}
		$output1 = & atkOutput :: getInstance();
		$output = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
		$output .= "<html xmlns=\"http://www.w3.org/1999/xhtml\" xmlns:v=\"urn:schemas-microsoft-com:vml\">";
		$output .= "<head>";
		$output .= $map->printHeaderJS();
		$output .= $map->printMapJS();
		//  <!-- necessary for google maps polyline drawing in IE -->
		$output .= "<style type=\"text/css\">";
		$output .= "v\:* {";
		$output .= "    behavior:url(#default#VML);";
		$output .= "}";
		$output .= "</style>";
		$output .= "</head>";
		$output .= "<body onload=\"onLoad()\">";
		$output .= "<font face=\"arial\" size=\"1\" >";
		$output .= "<table border=1>";
		$output .= "<tr><td>";
		$output .= $map->printMap();
		$output .= "</td><td>";
		$output .= $map->printSidebar();
		$output .= "</td></tr>";
		$output .= "</table>";
		$output .= "<font face=\"arial\" size=\"1\" color=\"red\">";
		$output .= $missing . " : non géolocalisables";
		$output .= $missingnoms;
		$output .= "<br />" . $missingadresse . " : sans adresse";
		$output .= $missingadressenoms;
		$output .= "</font></body>";
		$output .= "</html>";
		$output1->rawoutput($output);
		$output1->outputFlush();
	}
	function action_normalisation() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id, ville , province_etat" . " from type_cp_ville_pays");
		if (count($data) == 0) {
			return true;
		} else {
			for ($i = 0; $i < count($data); $i++) {
				$data[$i]["ville"] = normalisation_chaine($data[$i]["ville"]);
				$data[$i]["ville"] = addslashes($data[$i]["ville"]);
				$data[$i]["province_etat"] = normalisation_chaine($data[$i]["province_etat"]);
				$data[$i]["province_etat"] = addslashes($data[$i]["province_etat"]);
				$db->query("UPDATE type_cp_ville_pays" . " set province_etat='" . $data[$i]["province_etat"] . "'" . " , ville='" . $data[$i]["ville"] . "'" . " where id=" . $data[$i]["id"] . "");
			}
		}
		echo "<br> Normalisation des noms de villes et provinces-etats terminée.";
	}
	function descriptor_def() {
		return "[code_postal] [ville] ";
	}
	function traitement_select($select, & $idorganisme, & $idindividus, & $idfonctions) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_1 = explode('AND', $id_variable);
			$array_organisme = $array_1[0];
			$array_type = explode('=', $array_1[1]);
			$chaineidfonction .= $array_type[1] . ',';
		}
		$array_organisme = str_replace("v_organisme_fonction", "individu_fonction", $array_organisme);
		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 1);
		$idfonctions = $chaineidfonction;
		$sql = 'select distinct id_individu from individu_fonction
				 where ' . $array_organisme . ' and date_fin is null and id_fonction in (' . $chaineidfonction . ')';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		$idorg = explode('=', $array_organisme);
		$idorganisme = $idorg[1];
		return true;
	}
}
?>