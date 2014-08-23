<?php
class traitement extends atkNode {
	function traitement() {
		$this->atkNode("traitement");
		$this->setSecurityAlias("editeur.editeur");
		$this->m_securityMap["normalisation_libelle"] = "view";
		$this->m_securityMap["normalisation_nom"] = "view";
		$this->m_securityMap["lonlat"] = "view";
		$this->m_securityMap["test_xml2db"] = "view";
	}

	function action_normalisation_libelle(& $handler) {
		global $g_sessionManager;
		$tables_a_ignorer = array (
			"gis_placemark",
			"menu",
			"menu_item",
			"type_normalisation_libelle",
			"type_region_pays",
			"type_symbole_gps",
			"type_zone_region_pays"
		);
		$db = & atkGetDb();
		$user = getUser();
		$id = $user["id"];
		$sql = "select prenom, nom, courriel from app_utilisateur au, individu i " .
		"where au.id=$id and au.id_individu=i.id ";
		$data = $db->getrows($sql);
		$auteur = $data[0]["prenom"] . " " . $data[0]["nom"];
		$emailauteur = $data[0]["courriel"];
		$sql = " show tables";
		$data = $db->getrows($sql);

		for ($i = 0; $i < count($data); $i++) {
			if (in_array($data[$i]["Tables_in_association"], $tables_a_ignorer)) {

			} else {
				$sql = 'show columns from ' . $data[$i]["Tables_in_association"] . ' like "libelle"';
				$data1 = $db->getrows($sql);
				for ($j = 0; $j < count($data1); $j++) {
					print_r($data[$i]["Tables_in_association"]);
					echo "   -   ";
					print_r($data1[$j][Field]);
					echo "<br />";
					$sql = 'select id, libelle from ' . $data[$i]["Tables_in_association"] . '';
					$data2 = $db->getrows($sql);
					for ($k = 0; $k < count($data2); $k++) {
						$libelle = normalisation_libelle($data2[$k]["libelle"]);
						$sql = 'update ' . ($data[$i]["Tables_in_association"]) . ' 
																																								set libelle=\'' . addslashes($libelle) . '\' where id=' . $data2[$k]["id"] . '';
						// echo ($sql);
						// echo "<br />";
						$db->query($sql);

					}

				}
			}
		}
		echo "Normalisation des libellés terminée";
	}
	function action_normalisation_nom(& $handler) {
		global $g_sessionManager;
		$db = & atkGetDb();
		$champs_a_traiter = array (
			array (
				"individu",
				"nom"
			),
			array (
				"individu",
				"prenom"
			),
			array (
				"organisme",
				"nom"
			),
			array (
				"lieu",
				"adresse1"
			),
			array (
				"lieu",
				"adresse2"
			),

			array (
				"type_cp_ville_pays",
				"ville"
			),

			array (
				"type_cp_ville_pays",
				"province_etat"
			),
			array (
				"type_pays",
				"libelle_anglais"
			),
			array (
				"type_pays",
				"libelle_francais"
			),
			array (
				"gis_placemark",
				"libelle"
			),
			array (
				"type_region_pays",
				"libelle"
			),
			array (
				"type_zone_region_pays",
				"libelle"
			)
		);

		for ($i = 0; $i < count($champs_a_traiter); $i++) {
			$table = $champs_a_traiter[$i][0];
			$colonne = $champs_a_traiter[$i][1];
			$sql = 'select id,' . $colonne . ' from ' . $table . '';
			print_r($sql);
			echo ("<br />");
			$data2 = $db->getrows($sql);
			for ($k = 0; $k < count($data2); $k++) {
				$nom = normalisation_chaine($data2[$k]["$colonne"]);
				$sql = 'update ' . $table . ' 
																																set ' . $colonne . '=\'' . addslashes($nom) . '\' where id=' . $data2[$k]["id"] . '';
				$db->query($sql);
			}
		}
		echo "Normalisation des noms terminée";
	}

	function action_lonlat(& $handler) {
		global $g_sessionManager;
		include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
		$db = & atkGetDb();
		$sql = 'select id, longitude, latitude from gis_point_coordinate';

		$data = $db->getrows($sql);
		for ($k = 0; $k < count($data); $k++) {
			$lonlat = decimal2degree($data[$k]["latitude"], 'LAT') . ' ' . decimal2degree($data[$k]["longitude"], 'LON');
			$sql = 'update gis_point_coordinate 
																											set lonlat =\'' . addslashes($lonlat) . '\' where id=' . $data[$k]["id"] . '';
			$db->query($sql);
		}
		echo "Conversion latitude/longitude terminée";
	}

	function action_test_xml2db(& $handler) {
		global $g_sessionManager;
		include_once (atkconfig("atkroot") . "modules/include/xml2db.inc");
		$db = & atkGetDb();
		// GG

		$xml = simplexml_load_file(atkconfig("atkroot") . "modules/include/trajet.kml");
		print "\nDébut<br />\n ";
		foreach ($xml->Document as $document) {
			print "Document name : {$document->name} <br />\n ";
			foreach ($document->Placemark as $placemark) {
				print "Placemark name : {$placemark->name} <br />\n ";
				foreach ($placemark->LineString as $linestring) {
					print "LineString . Tesselate : {$linestring->tesselate} <br />\n ";
					print "LineString . Coordinates : {$linestring->coordinates} <br />\n ";
				
				}
				
				foreach ($placemark->Point as $point) {
					print "Point . Tesselate : {$point->tesselate} <br />\n ";
					print "Point . Coordinates : {$point->coordinates} <br />\n ";
				}

			}

		}
		echo 'Ligne - nom : ' , $xml->Document[0]->Placemark[0]->name , '<br />';
		echo 'Lignes - coordonnées : ' , $xml->Document[0]->Placemark[0]->LineString[0]->coordinates , '<br />';
		echo 'Point - nom : ' , $xml->Document[0]->Placemark[0]->name , '<br />';
		echo 'Point - coordonnées : ' , $xml->Document[0]->Placemark[0]->Point[0]->coordinates , '<br />';
		print "\nFin<br />\n ";
		die();
		// GG FIN

		$xml2db = new xml2db("product");
		$xml2db->setXMLFile(atkconfig("atkroot") . "modules/include/test.xml");
		$xml2db->setTable("cellphones");
		$xml2db->setData(array (
			// 		xml node	type		db field		attr name
			array (
				"",
				"attr",
				"id",
				"id"
			),
			array (
				"brand",
				"node",
				"manufacturer"
			),
			array (
				"brand",
				"attr",
				"type",
				"type"
			),
			array (
				"model",
				"node",
				"name"
			),
			array (
				"price",
				"node",
				"price"
			),

			
		));

		// Just a test printout - you can perfom the queries here
		echo "<pre>";
		print_r($xml2db->getQueries());
		echo "</pre>";
		echo "test xml to db terminée";
	}

}
?>