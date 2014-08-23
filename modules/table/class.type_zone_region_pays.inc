<?php
useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");
class type_zone_region_pays extends assMetaNode {
	var $table = "type_zone_region_pays";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", "lookat_longitude", "lookat_longitude", "lookat_latitude", "lookat_altitude", "lookat_range", "lookat_tilt", "lookat_heading", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_zone_region_pays() {
		$this->atkMetaNode();
		$this->atkNode("type_zone_region_pays",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"id_region_pays","id_maree_meteo","id_photo",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Lookat" => array (
				"lookat_longitude",
				"lookat_latitude","lookat_altitude","lookat_range","lookat_tilt","lookat_heading"
			),
			"Box" => array (
				"box_north","box_south","box_east","box_west","box_minalt","box_maxalt",
"box_minlod","box_maxlod","box_minfade","box_maxfade"
			),
			"Repères" => array (
				"placemark"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextNomAttribute("libelle", AF_SEARCHABLE));
		$this->m_securityMap["export_kml"] = "view";
		$this->m_securityMap["import_kml"] = "view";
		$this->add(new atkManyToOneRelation("id_region_pays", "table.type_region_pays", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_maree_meteo", "table.maree_meteo", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_HIDE_LIST|AF_RELATION_AUTOCOMPLETE), 130);
		$this->add(new atgFileManyToOneRelation("id_photo", "individu.document_i", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_HIDE_LIST|AF_RELATION_AUTOCOMPLETE), 132);
		$this->add(new atkOneToManyRelation("placemark", "gis.placemark", "id_zone_region_pays", AF_HIDE_LIST));
		$this->add(new atkNumberAttribute("lookat_longitude", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("lookat_latitude", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("lookat_altitude", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("lookat_range", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("lookat_tilt", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("lookat_heading", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_north", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_south", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_east", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_west", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_minalt", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_maxalt", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_minlod", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_maxlod", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_minfade", AF_SEARCHABLE, 25, 0));
		$this->add(new atkNumberAttribute("box_maxfade", AF_SEARCHABLE, 25, 0));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
		function initial_values() {
		$init_vals = array ();
		$init_vals["lookat_longitude"] = 0;
		$init_vals["lookat_latitude"] = 0;
		$init_vals["lookat_altitude"] = 0;
		$init_vals["lookat_range"] = 0;
		$init_vals["lookat_tilt"] = 0;
		$init_vals["lookat_heading"] = 0;
		$init_vals["box_north"] = 50;
		$init_vals["box_south"] = 45;
		$init_vals["box_east"] = 2;
		$init_vals["box_west"] = -5;
		$init_vals["box_minalt"] = 0;
		$init_vals["box_maxalt"] = 10000;
		$init_vals["box_minlod"] = 120;
		$init_vals["box_maxlod"] = -1;
		$init_vals["box_minfade"] = 128;
		$init_vals["box_maxfade"] = 128;
		return $init_vals;
	}
	function action_export_kml() {
		// nom du site sur lequel ext l'appli
		$site = atkHost();
		$urlsite = 'http://' . $site;
		$sitesanswww = substr_replace($site, '', 0, 4);
		// nom du répertoire des icones
		$imagesdir = atkconfig("imagesdir");
		// nom du répertoire des fichiers exportés en kml
		$kmldir = atkconfig("kmldir");
		// nom du répertoire des fichiers exportés en gpx
		$gpxdir = atkconfig("gpxdir");
		// nom du répertoire des fichiers exportés en gpx
		$photosdir = atkconfig("photosdir");
		$application = atkconfig("identifier");
		$db = & atkGetDb();
		$user = getUser();
		$id = $user["id"];
		$sql = "select prenom, nom, courriel from app_utilisateur au, individu i " . "where au.id=$id and au.id_individu=i.id ";
		$data = $db->getrows($sql);
		$auteur = $data[0]["prenom"] . " " . $data[0]["nom"];
		$emailauteur = $data[0]["courriel"];
		$gpx_output = '<?xml version="1.0" encoding="utf-8" ?>';
		$gpx_output .= '<gpx xmlns="http://www.topografix.com/GPX/1/0" ';
		$gpx_output .= ' creator="appli:' . $application . ' - http://' . $site . '" >';
		$kml_output = '<?xml version="1.0" encoding="UTF-8"?>';
		$kml_output .= '<kml xmlns="http://earth.google.com/kml/2.1" ';
		$kml_output .= ' creator="' . $application . ' - http://' . $site . '" >';
		$sql = " SELECT " . "distinct " . "tzrp.libelle as zone, 
						trp.libelle as region , 
						tp.libelle_anglais as pays,
						tzrp.lookat_longitude,
						tzrp.lookat_latitude,
						tzrp.lookat_altitude,
						tzrp.lookat_range,
						tzrp.lookat_tilt,
						tzrp.lookat_heading,
						 tzrp.id_photo,
						tzrp.id_maree_meteo " . "from" . " type_zone_region_pays tzrp ," . " type_region_pays trp, " . " type_pays tp " . " where tzrp.id=" . $this->m_postvars["id"] . " and   tzrp.id_region_pays=trp.id " . "  and trp.id_pays=tp.id ";
		$data = $db->getrows($sql);
		if (isset ($data[0]["id_photo"]) && ($data[0]["id_photo"]) != 0) {
			$sqlp = "select id, file_extension,file_content, file_size from individu_document
									 where id=" . $data[0]["id_photo"] . "";
			$dataphoto = $db->getrows($sqlp);
			$filename = ".." . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'];
			$file = @ fopen($filename, "w");
			@ fwrite($file, base64_decode($dataphoto[0]["file_content"]));
			@ fclose($file);
			$urlphotozone = "http://" . $sitesanswww . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'] . "";
		} else {
			$urlphotozone = null;
		}
		if (isset ($data[0]["id_maree_meteo"]) && $data[0]["id_maree_meteo"] != 0) {
			$sqlp = "select tmm.url_meteo, tmm.url_maree " . " FROM (type_zone_region_pays tzrp  left join
									type_maree_meteo tmm on tzrp.id_maree_meteo=tmm.id) 
									where tzrp.id=" . $this->m_postvars["id"] . " ";
			$datamm = $db->getrows($sqlp);
			$url_maree = $datamm[0]['url_maree'];
			$url_meteo = $datamm[0]['url_meteo'];
		} else {
			$url_maree = null;
			$url_meteo = null;
		}
		$gpx_output .= '<desc>Phares et balises de la zone:' . $data[0]["zone"] . '</desc> 
						<author>' . $auteur . '</author>
						<email>' . $emailauteur . '</email> 
						<time>' . gmdate(c) . '</time> 
						<desc>Phares et balises de la zone:' . $data[0]["zone"] . '</desc> 
						<author>' . $auteur . '</author>
						<email>' . $emailauteur . '</email> 
						<time>' . gmdate(c) . '</time> ';
		$kml_output .= '<Document>
						<description>Phares et balises <br />
						<table style="font: 12px Arial; ">
						<tr><td><b>Pays:</b> ' . $data[0]["pays"] . '<br />
						  <b>Region:</b> ' . $data[0]["region"] . '<br />
						<b>Zone:</b> ' . $data[0]["zone"] . '<br />';
		if (isset ($url_maree) && $url_maree != '') {
			$kml_output .= '
									<b><a href="' . $url_maree . '"> Marées</a> </b><br />';
		}
		if (isset ($url_meteo) && $url_meteo != '') {
			$kml_output .= '
									<b><a href="' . $url_meteo . '"> Météo</a> </b><br />';
		}
		if (isset ($urlphotozone) && $urlphotozone != '') {
			$kml_output .= '<b><a href="' . $urlsite . '"> <img src="' . $urlphotozone . '" /></a> </b><br />';
		}
		$kml_output .= '
						<div style="width:325px; padding: 2px; border: 1px solid #000; "><br />
						<br /></div>
						</td></tr>
						</table>
						</description>
						<name>' . $data[0]["zone"] . '</name>
						<visibility>1</visibility>
						<LookAt>
						<longitude> ' . $data[0]["lookat_longitude"] . '</longitude>
						<latitude> ' . $data[0]["lookat_latitude"] . '</latitude>
						<altitude> ' . $data[0]["lookat_altitude"] . '</altitude>
						<range> ' . $data[0]["lookat_range"] . '</range>
						<tilt> ' . $data[0]["lookat_tilt"] . '</tilt>
						<heading> ' . $data[0]["lookat_heading"] . '</heading>
						</LookAt>';
		// traiter et sortir les icones
		$sql = " SELECT  
						distinct tp.id_icone as id_icone, tp.id_seconde_icone as id_seconde_icone, gi.file_content as icone, gi2.file_content as icone2 
						from
						 type_placemark tp ,
						gis_placemark gp, 
						 gis_icone gi, 
						 gis_icone gi2 
						 where gp.id_zone_region_pays=" . $this->m_postvars["id"] . "  and gp.geometry=\"Point\" and gp.id_type_placemark=tp.id 
						and tp.id_icone=gi.id 
						 and tp.id_seconde_icone=gi2.id 
						order by tp.id_icone ";
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$kml_output .= '
									<StyleMap id="msn_icon' . $data[$i]["id_icone"] . '">
									<Pair> 
									<key>normal</key> 
									<styleUrl>#sn_icon' . $data[$i]["id_icone"] . '</styleUrl> 
									</Pair> 
									<Pair> 
									<key>highlight</key> 
									<styleUrl>#sh_icon' . $data[$i]["id_seconde_icone"] . '</styleUrl> 
									</Pair> 
									</StyleMap> 
									<Style id="sh_icon' . $data[$i]["id_seconde_icone"] . '">
									<IconStyle> 
									<scale>1.1</scale> 
									<Icon> 
									<x>0.5</x>
									<y>0.5</y>
									<href>http://' . $sitesanswww . $imagesdir . 'gis_icone_' . $data[$i]['id_seconde_icone'] . '.png </href> 
									</Icon>
									</IconStyle> 
									<LabelStyle>
									<color>ff00ffff</color>
									<scale>0.7</scale>
									</LabelStyle>
									<ListStyle> 
									</ListStyle> 
									</Style> 
									<Style id="sn_icon' . $data[$i]["id_icone"] . '"> 
									<IconStyle> 
									<scale>1</scale> 
									<Icon> 
									<x>0.5</x>
									<y>0.5</y>
									<href>http://' . $sitesanswww . $imagesdir . 'gis_icone_' . $data[$i]['id_icone'] . '.png </href> 
									</Icon>
									</IconStyle> 
									<LabelStyle>
									<color>ff00ffff</color>
									<scale>0.7</scale>
									</LabelStyle>
									<ListStyle> 
									</ListStyle> 
									</Style> ';
			// enregistrer les icones.
			$filename = ".." . $imagesdir . "gis_icone_" . $data[$i]['id_icone'] . ".png";
			$file = @ fopen($filename, "w");
			$record["file_content"] = base64_decode($record["file_content"]);
			@ fwrite($file, base64_decode($data[$i]['icone']));
			@ fclose($file);
			$filename = ".." . $imagesdir . "gis_icone_" . $data[$i]['id_seconde_icone'] . ".png";
			$file = @ fopen($filename, "w");
			@ fwrite($file, base64_decode($data[$i]['icone2']));
			@ fclose($file);
		}
		$sql = "SELECT " . " p.libelle as libelle_placemark," . "p.etiquette, p.id," . "p.description,
						p.id_photo,
						p.geometry,
						p.extrude,
						p.tesselate,
						p.altitudemode, " . "tps.libelle_anglais," . "trp.libelle as libelle_region," . "tzrp.libelle as libelle_zone," . "tp.id_icone as id_icone," . "tsg.libelle as symbole_visualgps," . "tp.libelle as libelle_type_placemark,
						tmm.url_meteo, tmm.url_maree " . " FROM (gis_placemark p left join
						type_maree_meteo tmm on p.id_maree_meteo=tmm.id) ,
						  " . "type_symbole_gps tsg,type_pays tps,type_region_pays trp,
				 type_zone_region_pays tzrp, type_placemark tp   
				 WHERE p.id_zone_region_pays=" . $this->m_postvars["id"] . "
				 and p.id_zone_region_pays=tzrp.id   and tzrp.id_region_pays=trp.id  
				 and trp.id_pays=tps.id   and p.id_type_placemark=tp.id  
				   and tp.id_symbole_gps=tsg.id  ";
		$data = $db->getrows($sql);
		$kml_output .= '
						<Folder>
						<name>Phares et balises de la zone</name>';
		for ($i = 0; $i < count($data); $i++) {
			$id = $data[$i]['id'];
			$id_placemark = $data[$i]['id'];
			$libelle = $data[$i]['libelle_placemark'];
			$geometry = $data[$i]['geometry'];
			$extrude = $data[$i]['extrude'];
			$tesselate = $data[$i]['tesselate'];
			$altitudemode = $data[$i]['altitudemode'];
			$etiquette = $data[$i]['etiquette'];
			$description = $data[$i]['description'];
			//$longitude = $data[$i]['longitude'];
			//$latitude = $data[$i]['latitude'];
			//$altitude = $data[$i]['altitude'];
			$zone = $data[$i]['libelle_region'];
			$region = $data[$i]['libelle_zone'];
			$pays = $data[$i]['libelle_anglais'];
			$url_maree = $data[$i]['url_maree'];
			$url_meteo = $data[$i]['url_meteo'];
			$id_photo = $data[$i]['id_photo'];
			$symbole_visualgps = $data[$i]['symbole_visualgps'];
			$sql = "SELECT " . " tap.libelle as attribut,
									gpa.valeur as valeur 
									from
									gis_placemark_attribut gpa,
									type_attribut_placemark tap
									where 
									gpa.id_placemark=" . $data[$i]['id'] . "
									and gpa.id_type_attribut_placemark=tap.id
									 order by tap.libelle ";
			$kml_attributs = '';
			$data2 = $db->getrows($sql);
			for ($j = 0; $j < count($data2); $j++) {
				$kml_attributs .= '<b><font color="#0000ff">' . $data2[$j]["attribut"] . ':</font></b> ' . $data2[$j]["valeur"] . '<br />
												';
			}
			$kml_lonlat = '';
			if ($geometry == 'Point') {
				$kml_output_item .= '<Point>
												<extrude>' . $extrude . '</extrude>
												<tesselate>' . $tesselate . '</tesselate>
												<altitudemode>' . $altitudemode . '</altitudemode>';
				$sql = "SELECT pc.longitude, pc.latitude, pc.altitude, pc.lonlat
												from gis_point_coordinate pc where 
												pc.id_placemark=" . $id . " order by pc.id";
				$datall = $db->getrows($sql);
				$kml_lonlat = '<b>Coordonnées GPS (DMS): </b>' . $datall[0]['lonlat'] . ' <br />';
				$kml_coordinates = $datall[0]["longitude"] . ',' . $datall[0]["latitude"] . ',' . $datall[0]["altitude"];
				$kml_output_item .= '<coordinates>' . $kml_coordinates . '</coordinates>
												</Point>';
				$gpx_output .= '
										<wpt lat="' . $datall[0]["latitude"] . '" lon="' . $datall[0]["longitude"] . '" >
										<ele> ' . $datall[0]["altitude"] . '</ele>
										<name><![CDATA[' . utf8_encode($etiquette) . ']]></name>
										<sym><![CDATA[' . utf8_encode($symbole_visualgps) . ']]></sym>
										</wpt>';
			}
			if ($geometry == 'LineString') {
				$kml_output_item .= '<LineString>
												<extrude>' . $extrude . '</extrude>
												<tesselate>' . $tesselate . '</tesselate>
												<altitudemode>' . $altitudemode . '</altitudemode>';
				$sql = "SELECT pc.longitude, pc.latitude, pc.altitude, pc.lonlat,
								pc.distance_next, pc.heading_next, pc.distance_previous, pc.heading_previous
												from gis_ligne_coordinate pc where 
												pc.id_placemark=" . $id . " order by pc.id";
				$kml_coordinates = '';
				$datall = $db->getrows($sql);
				$kml_lonlat = '<table border="1">
								<tr>
								<th>Coordonnées</th>
								<th>Distsuivant</th>
								<th>Cumul</th>
								<th>CapSuivant</th>
								<th>DisPréc</th>
								<th>CapPréc</th>
								</tr>';
				$cumul = 0;
				$gpx_output .= '
											<rte>';
				for ($k = 0; $k < count($datall); $k++) {
					$kml_coordinates .= $datall[$k]["longitude"] . ',' . $datall[$k]["latitude"] . ',' . $datall[$k]["altitude"];
					$kml_coordinates .= ' ';
					$cumul += $datall[$k]["distance_next"];
					$kml_lonlat .= '<tr><td>' . $datall[$k]["lonlat"] . '</td><td>' . $datall[$k]["distance_next"] . '</td><td>' . $cumul . '</td><td>' . $datall[$k]["heading_next"] . '</td><td>' . $datall[$k]["distance_previous"] . '</td><td>' . $datall[$k]["heading_previous"] . '</td></tr>';
					$gpx_output .= '
												<rtept lat="' . $datall[$k]["latitude"] . '" lon="' . $datall[$k]["longitude"] . '" >
												<ele> ' . $datall[$k]["altitude"] . '</ele>
												</rtept>';
				}
				$kml_lonlat .= '</table>';
				$kml_output_item .= '<coordinates>' . $kml_coordinates . '</coordinates>
												</LineString>';
				$gpx_output .= '
											</rte>';
			}
			if ($geometry == 'LinearRing') {
				$kml_output_item .= '<LinearRing>
												<extrude>' . $extrude . '</extrude>
												<tesselate>' . $tesselate . '</tesselate>
												<altitudemode>' . $altitudemode . '</altitudemode>';
				$sql = "SELECT pc.longitude, pc.latitude, pc.altitude, pc.lonlat,
								pc.distance_next, pc.heading_next, pc.distance_previous, pc.heading_previous
												from gis_ligne_coordinate pc where 
												pc.id_placemark=" . $id . " order by pc.id";
				$kml_coordinates = '';
				$gpx_output .= '
											<trk>
								<trkseg>';
				$datall = $db->getrows($sql);
				for ($k = 0; $k < count($datall); $k++) {
					$kml_coordinates .= $datall[$k]["longitude"] . ',' . $datall[$k]["latitude"] . ',' . $datall[$k]["altitude"];
					$kml_coordinates .= ' ';
					$gpx_output .= '
												<trkpt lat="' . $datall[$k]["latitude"] . '" lon="' . $datall[$k]["longitude"] . '" >
												<ele> ' . $datall[$k]["altitude"] . '</ele>
												</trkpt>';
				}
				$kml_output_item .= '<coordinates>' . $kml_coordinates . '</coordinates>
												</LinearRing>';
				$gpx_output .= '
											</trkseg>
								</trk>';
			}
			if ($geometry == 'Polygon') {
				$kml_output_item .= '<Polygon>
											<extrude>' . $extrude . '</extrude>
											<tesselate>' . $tesselate . '</tesselate>
											<altitudemode>' . $altitudemode . '</altitudemode>
											  <outerBoundaryIs>
											    <LinearRing>
											';
				$sql = "SELECT pc.longitude, pc.latitude, pc.altitude, pc.lonlat,
								pc.distance_next, pc.heading_next, pc.distance_previous, pc.heading_previous
											from gis_ligne_coordinate pc where 
											pc.id_placemark=" . $id . " order by pc.id";
				$kml_coordinates = '';
				$gpx_output .= '
											<trk>
								<trkseg>';
				$datall = $db->getrows($sql);
				for ($k = 0; $k < count($datall); $k++) {
					$kml_coordinates .= $datall[$k]["longitude"] . ',' . $datall[$k]["latitude"] . ',' . $datall[$k]["altitude"];
					$kml_coordinates .= ' ';
					$gpx_output .= '
												<trkpt lat="' . $datall[$k]["latitude"] . '" lon="' . $datall[$k]["longitude"] . '" >
												<ele> ' . $datall[$k]["altitude"] . '</ele>
												</trkpt>';
				}
				$kml_output_item .= '<coordinates>' . $kml_coordinates . '</coordinates>
											  </LinearRing>
											  </outerBoundaryIs>
											</Polygon>';
				$gpx_output .= '
											</trkseg>
								</trk>';
			}
			$kml_description = '
									<b>Region:</b> ' . $region . '<br />
									<b>Zone:</b> ' . $zone . '<br />
									<b>Pays:</b> ' . $pays . '<br />
									<b>Repère :</b> ' . $etiquette . '<br />
									' . $kml_lonlat . '
									<b>Description:</b> ' . $description . '<br />';
			if (isset ($url_maree)) {
				$kml_description .= '
												<b><a href="' . $url_maree . '"> Marées</a> </b><br />';
			}
			if (isset ($url_meteo)) {
				$kml_description .= '
												<b><a href="' . $url_meteo . '"> Météo</a> </b><br />';
			}
			if (isset ($id_photo) || $id_photo != 0) {
				$sqlp = "select id, file_extension,file_content, file_size from individu_document
												 where id=" . $id_photo . "";
				$dataphoto = $db->getrows($sqlp);
				$filename = ".." . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'];
				$file = @ fopen($filename, "w");
				@ fwrite($file, base64_decode($dataphoto[0]["file_content"]));
				@ fclose($file);
				$urlphotozone = "http://" . $sitesanswww . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'] . "";
				$kml_description .= '<b><a href="' . $urlsite . '"> <img src="' . $urlphotozone . '"></a> </b><br />';
			}
			$kml_description .= '<b>Attributs:</b><br />';
			$kml_description = '<![CDATA[' . $kml_description . ' ]]>';
			$kml_attributs = '<![CDATA[' . $kml_attributs . ' ]]>';
			/*
			 * ajouter traitement export ligne, polygone
			 */
			$kml_output .= '
									<Placemark>
									<description>' . $kml_description . $kml_attributs . '</description>
									<name>' . $etiquette . '</name>
									<styleUrl>#msn_icon' . $data[$i]["id_icone"] . '</styleUrl>
									' . $kml_output_item;
			$kml_output .= '</Placemark>';
		}
		// end the document structure
		$kml_output .= '
					</Folder>
					</Document>
					</kml>';
		$gpx_output .= '</gpx>';
		$basefilename = ".." . $kmldir . "kml_zone_" . $this->m_postvars['id'];
		$filename = ".." . $kmldir . "kml_zone_" . $this->m_postvars['id'] . ".kml";
		$link = "http://" . $site . $kmldir . "kml_zone_" . $this->m_postvars["id"] . ".kml";
		$linkz = "http://" . $site . $kmldir . "kml_zone_" . $this->m_postvars["id"] . ".kmz";
		$file = @ fopen($filename, "w");
		@ fwrite($file, $kml_output);
		@ fclose($file);
		if (strlen(shell_exec('zip -h')) == 0) {
			echo ("Ne peut executer zip");
		} else {
			exec('rm -r ..' . $kmldir . 'doc');
			exec('mkdir ..' . $kmldir . 'doc');
			exec('cp ' . $filename . ' ..' . $kmldir . 'doc/doc.kml');
			exec('zip  -j  ' . $basefilename . '.kmz  ..' . $kmldir . 'doc/doc.kml  ');
		}
		echo "<br> Exportation du fichier " . $filename . " terminée.";
		echo "<br><a href=" . $link . " target=\"_blank\"><u><b>'Résultat en kml'</b></u></a>";
		echo "<br><a href=" . $linkz . " target=\"_blank\"><u><b>'Résultat en kmz'</b></u></a>";
		$filename = ".." . $gpxdir . "gpx_zone_" . $this->m_postvars['id'] . ".gpx";
		$link = "http://" . $site . $gpxdir . "gpx_zone_" . $this->m_postvars["id"] . ".gpx";
		$file = @ fopen($filename, "w");
		@ fwrite($file, $gpx_output);
		@ fclose($file);
		echo "<br> Exportation du fichier " . $filename . " terminée.";
		echo "<br><a href=" . $link . " target=\"_blank\"><u><b>'Résultat en gpx.'</b></u></a>";
	}
	function action_import_kml() {
		include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
		if (array_key_exists('action', $_POST)) {
			@ copy($_FILES["my_field"]["tmp_name"], atkconfig("atkroot") . "gis/import/" . $_FILES["my_field"]["name"]);
			$xml = simplexml_load_file(atkconfig("atkroot") . "gis/import/" . $_FILES["my_field"]["name"]);
			$db = & atkGetDb();
			$user = getUser();
			$id = $user["id"];
			$sql = "select prenom, nom, courriel from app_utilisateur au, individu i " . "where au.id=$id and au.id_individu=i.id ";
			$data = $db->getrows($sql);
			$auteur = $data[0]["prenom"] . " " . $data[0]["nom"];
			$emailauteur = $data[0]["courriel"];
			foreach ($xml->Document as $document) {
				foreach ($document->Placemark as $placemark) {
					$placemark_node = & getNode("gis.placemark");
					$placemark_record = array ();
					$placemark_record["libelle"] = utf8_decode($placemark->name);
					$placemark_record["etiquette"] = utf8_decode($placemark->name);
					$placemark_record["id_zone_region_pays"] = $this->m_postvars["id"];
					$placemark_record["id_type_placemark"]["id"] = '47';
					$placemark_record["description"] = utf8_decode($placemark->description);
					foreach ($placemark->LookAt as $lookat) {
					}
					foreach ($placemark->LineString as $linestring) {
						if (!isset ($linestring->extrude)) {
							$linestring->extrude = 0;
							$linestring->tesselate = 0;
							$linestring->altitudemode = "clampToGround";
						}
						$placemark_record["geometry"] = "LineString";
						$placemark_record["extrude"] = $linestring->extrude;
						$placemark_record["tesselate"] = $linestring->tesselate;
						$placemark_record["altitudemode"] = $linestring->altitudemode;
						$placemark_node->addDb($placemark_record);
						$primkey = explode("=", $placemark_node->primaryKey($placemark_record));
						$primkey[1] = str_ireplace("'", "", $primkey[1]);
						$token = explode(" ", trim($linestring->coordinates));
						$distnexttotal = 0;
						$distprevtotal = 0;
						for ($i = 0; $i < (count($token)); $i++) {
							$token1 = explode(",", trim($token[$i]));
							$distnext = null;
							$distprev = null;
							$dist1 = null;
							$dist2 = null;
							$headnext = null;
							$headprev = null;
							if ($i < (count($token) - 1)) {
								$token2 = explode(",", trim($token[$i +1]));
								$distnext = decimal_distance($token1[1], $token1[0], $token2[1], $token2[0]);
								$headnext = compute_heading($token1[1], $token1[0], $token2[1], $token2[0]);
								$distnexttotal = $distnexttotal + $distnext;
							}
							if ($i > 0) {
								$token3 = explode(",", trim($token[$i -1]));
								$distprev = decimal_distance($token1[1], $token1[0], $token3[1], $token3[0]);
								$headprev = compute_heading($token1[1], $token1[0], $token3[1], $token3[0]);
								//						$distprevtotal=$distprevtotal+$distprev;
							}
							$ligne_coordinate_node = & getNode("gis.ligne_coordinate");
							$ligne_coordinate_record = array ();
							$ligne_coordinate_record["id_placemark"]["id"] = $primkey[1];
							$ligne_coordinate_record["longitude"] = $token1[0];
							$ligne_coordinate_record["latitude"] = $token1[1];
							$ligne_coordinate_record["altitude"] = $token1[2];
							$ligne_coordinate_record["distance_next"] = $distnext;
							$ligne_coordinate_record["distance_next_total"] = $distnexttotal;
							$ligne_coordinate_record["heading_next"] = $headnext;
							$ligne_coordinate_record["distance_previous"] = $distprev;
							$ligne_coordinate_record["distance_previous_total"] = $distprevtotal;
							$ligne_coordinate_record["heading_previous"] = $headprev;
							include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
							$ligne_coordinate_record["lonlat"] = decimal2degree($ligne_coordinate_record["longitude"], 'LON') . ' ' . decimal2degree($ligne_coordinate_record["latitude"], 'LAT');
							$ligne_coordinate_node->addDb($ligne_coordinate_record);
						}
					}
					foreach ($placemark->LinearRing as $linearring) {
						$token = explode(" ", $linearring->coordinates);
						for ($i = 0; $i < count($token); $i++) {
						}
					}
					foreach ($placemark->Point as $point) {
						if (!isset ($point->extrude)) {
							$point->extrude = 0;
							$point->tesselate = 0;
							$point->altitudemode = "clampToGround";
						}
						$placemark_record["geometry"] = "Point";
						$placemark_record["extrude"] = $point->extrude;
						$placemark_record["tesselate"] = $point->tesselate;
						$placemark_record["altitudemode"] = $point->altitudemode;
						$placemark_node->addDb($placemark_record);
						$primkey = explode("=", $placemark_node->primaryKey($placemark_record));
						$primkey[1] = str_ireplace("'", "", $primkey[1]);
						$point_coordinate_node = & getNode("gis.point_coordinate");
						$point_coordinate_record = array ();
						$point_coordinate_record["id_placemark"]["id"] = $primkey[1];
						$token = explode(",", trim($point->coordinates));
						$point_coordinate_record["longitude"] = $token[0];
						$point_coordinate_record["latitude"] = $token[1];
						$point_coordinate_record["altitude"] = $token[2];
						include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
						$point_coordinate_record["lonlat"] = decimal2degree($point_coordinate_record["longitude"], 'LON') . ' ' . decimal2degree($point_coordinate_record["latitude"], 'LAT');
						$point_coordinate_node->addDb($point_coordinate_record);
					}
					foreach ($placemark->Polygon as $polygone) {
						foreach ($polygone->outerBoundaryIs as $outerboundaryis) {
							foreach ($outerboundaryis->LinearRing as $linearring) {
								if (!isset ($linearring->extrude)) {
									$linearring->extrude = 0;
									$linearring->tesselate = 0;
									$linearring->altitudemode = "clampToGround";
								}
								$placemark_record["geometry"] = "Polygon";
								$placemark_record["extrude"] = $linearring->extrude;
								$placemark_record["tesselate"] = $linearring->tesselate;
								$placemark_record["altitudemode"] = $linearring->altitudemode;
								$placemark_node->addDb($placemark_record);
								$primkey = explode("=", $placemark_node->primaryKey($placemark_record));
								$primkey[1] = str_ireplace("'", "", $primkey[1]);
								$token = explode(" ", trim($linearring->coordinates));
								for ($i = 0; $i < (count($token)); $i++) {
									$token1 = explode(",", trim($token[$i]));
									$distnext = null;
									$distprev = null;
									$dist1 = null;
									$dist2 = null;
									$headnext = null;
									$headprev = null;
									if ($i < (count($token) - 1)) {
										$token2 = explode(",", trim($token[$i +1]));
										$distnext = decimal_distance($token1[1], $token1[0], $token2[1], $token2[0]);
										$headnext = compute_heading($token1[1], $token1[0], $token2[1], $token2[0]);
									}
									if ($i > 0) {
										$token3 = explode(",", trim($token[$i -1]));
										$distprev = decimal_distance($token1[1], $token1[0], $token3[1], $token3[0]);
										$headprev = compute_heading($token1[1], $token1[0], $token3[1], $token3[0]);
									}
									$ligne_coordinate_node = & getNode("gis.ligne_coordinate");
									$ligne_coordinate_record = array ();
									$ligne_coordinate_record["id_placemark"]["id"] = $primkey[1];
									$ligne_coordinate_record["longitude"] = $token1[0];
									$ligne_coordinate_record["latitude"] = $token1[1];
									$ligne_coordinate_record["altitude"] = $token1[2];
									$ligne_coordinate_record["distance_next"] = $distnext;
									$ligne_coordinate_record["heading_next"] = $headnext;
									$ligne_coordinate_record["distance_previous"] = $distprev;
									$ligne_coordinate_record["heading_previous"] = $headprev;
									include_once (atkconfig("atkroot") . "modules/include/greatcircle.inc");
									$ligne_coordinate_record["lonlat"] = decimal2degree($ligne_coordinate_record["longitude"], 'LON') . ' ' . decimal2degree($ligne_coordinate_record["latitude"], 'LAT');
									$ligne_coordinate_node->addDb($ligne_coordinate_record);
								}
							}
							foreach ($polygone->innerBoundaryIs as $innerboundaryis) {
								print "Polygone : InnerBoundary <br />\n ";
								foreach ($innerboundaryis->LinearRing as $linearring) {
									print "Innerboundary ne sont pas importés dans ce programme <br />\n ";
								}
							}
						}
					}
				}
			}
			print "\nImport terminé<br />\n ";
		} else {
			$urlaction = "dispatch.php?atknodetype=table.type_zone_region_pays&atkaction=import_kml";
			$content = '<form name="form" enctype="multipart/form-data" method="post" action="' . $urlaction . '" /> &nbsp;
								            <p><input type="file" size="32" name="my_field" value="" /> <br />&nbsp;
								Pour un polygone seule la linearring de l\'outboundary sera importée</p> &nbsp;
								            <p class="button"><input type="hidden" name="action" value="simple" /> &nbsp;
								            <input type="submit" name="Submit" value="Importer" /></p> &nbsp;
								<input type="hidden" name="id" value="' . $this->m_postvars["id"] . '">
								        </form>';
			echo ($content);
		}
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>