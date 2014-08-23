<?php
useattrib("development.atgtextnomattribute");
class lieu extends assMetaNode {
	var $table = "lieu";
	function meta(& $policy) {
		$policy->addFlags("adresse1", "id_ville", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function lieu() {
		$this->atkMetaNode();
		$this->atkNode("lieu",  NF_ADD_LINK  );
		$this->setSecurityAlias("individu.individu");
		$this->m_securityMap["normalisation"] = "view";
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"adresse1",
				"adresse2",
				"id_ville",
			"bus_metro_tram",
						
				"normalisation",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Coordonnées" => array (
				"latitude",
				"longitude",
				"altitude",
			"google_earth"
			),
			"Individus" => array (
				"individus_lieux",
			"nb_individus"
			),
			"Organismes" => array (
				"organismes_lieux",
			"nb_organismes"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextNomAttribute("adresse1", AF_SEARCHABLE| AF_OBLIGATORY));
		$this->add(new atgTextNomAttribute("adresse2", AF_SEARCHABLE));
		$this->add(new atkManyToOneRelation("id_ville", "table.cp_ville_pays", AF_LARGE | AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));

		$this->add(new atkTextAttribute("bus_metro_tram", array (
	
	'rows' => '2'
)));
		$this->add(new atkOneToManyRelation("individus_lieux", "individu.individu_lieu", "id_lieu", AF_HIDE_LIST));
		$this->add(new atkOneToManyRelation("organismes_lieux", "organisme.organisme_lieu", "id_lieu", AF_HIDE_LIST));
/*		$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE, 25, 6));
		$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE, 25, 6));
		$this->add(new atkNumberAttribute("altitude", AF_SEARCHABLE, 25, 6));
		*/
				$this->add(new atkAttribute("longitude", AF_SEARCHABLE));
		$this->add(new atkAttribute("latitude", AF_SEARCHABLE));
		$this->add(new atkAttribute("altitude", AF_SEARCHABLE));
		$this->add(new atkParserAttribute("normalisation", href("?atkaction=normalisation", atktext("normalisation des libellés"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_LIST), 260);
		$this->add(new atkDummyAttribute("nb_individus", "nombre individus", AF_NOLABEL), NULL);
				$this->add(new atkDummyAttribute("google_earth", "google_earth",AF_DUMMY_SHOW_LABEL), NULL);
				
/*		$this->add(new atkExpressionAttribute("nb_individus", "select count(il.id_individu) from 
individu_lieu il
where

il.id_lieu=[table].id"), NULL);
*/
		$this->add(new atkDummyAttribute("nb_organismes", "nombre organismes", AF_NOLABEL), NULL);
/*		$this->add(new atkExpressionAttribute("nb_organismes", "select count(ol.id_organisme) from 
organisme_lieu ol
where
ol.id_lieu=[table].id"), NULL);
*/
include_once (atkconfig("atkroot") . "modules/include/association.inc");
//		$this->setOrder("lieu.id_ville");
//		$this->setIndex("lieu.id_ville");
$this->m_securityMap["geolocalisation"] = "view";
	}
	function nb_individus_display($record, $mode)
	{
		$id_lieu = $record["id"];
		$db = & atkGetDb();
		$data = $db->getrows("select count(il.id_individu)as nombre_i from 
individu_lieu il
where

il.id_lieu=$id_lieu");

return '<p style="text-align: right;"><b>' . $data[0]['nombre_i']. '</b></p>';
		
	}
		function nb_organismes_display($record, $mode)
	{
		$id_lieu = $record["id"];
		$db = & atkGetDb();
		$data = $db->getrows("select count(ol.id_organisme)as nombre_i from 
organisme_lieu ol
where
ol.id_lieu=$id_lieu");
return '<p style="text-align: right;"><b>' .$data[0]['nombre_i']. '</b></p>';
		
	}
		function google_earth_display($record, $mode)
	{
		$lat_lon = $record["latitude"].' '.$record["longitude"];
		$lat_lon=str_replace(',','.',$lat_lon);
		
return $lat_lon;
		
	}
	
	function action_normalisation() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id, adresse1 , adresse2" . " from lieu");
		if (count($data) == 0) {
			return true;
		} else {
			for ($i = 0; $i < count($data); $i++) {
				$data[$i]["adresse1"] = normalisation_chaine($data[$i]["adresse1"]);
				$data[$i]["adresse1"] = addslashes($data[$i]["adresse1"]);
				$data[$i]["adresse2"] = normalisation_chaine($data[$i]["adresse2"]);
				$data[$i]["adresse2"] = addslashes($data[$i]["adresse2"]);
				$db->query("UPDATE lieu" . " set adresse2='" . $data[$i]["adresse2"] . "'" . " , adresse1='" . $data[$i]["adresse1"] . "'" . " where id=" . $data[$i]["id"] . "");
			}
		}
		echo "<br> Normalisation des adresses terminée.";
	}

	function descriptor_def() {
		return "[adresse1] [adresse2] - [id_ville.code_postal] - [id_ville.ville]";
	}
	   function recordActions($rec, &$actions, &$mraactions)
  {  

 $mraactions['delete'] = "delete";

		$actions['geolocalisation'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=geolocalisation&atkselector=[pk]", SESSION_NESTED);


	}
  

	function validate(& $record, $mode) {
		// latitude : ^-?([1-8]?[1-9]|[1-9]0)\.{1}\d{1,6}
		// longitude : ^-?([1]?[1-7][1-9]|[1]?[1-8][0]|[1-9]?[0-9])\.{1}\d{1,6}
		//compass direction N90.00.00 E180.00.00 | S34.59.33 W179.59.59 | N00.00.00 W000.00.00 :  ^[NS]([0-8][0-9](\.[0-5]\d){2}|90(\.00){2})\040[EW]((0\d\d|1[0-7]\d)(\.[0-5]\d){2}|180(\.00){2})$
		// Vérifier s'il s'agit d'un collé depuis maps
		// vrai s'il y a un point, une virgule, un point
		$record["latitude"]=str_replace(' ', '', $record["latitude"]);
		$comptage=count_chars($record["latitude"],1);
		if ($comptage[44]==1 &&  $comptage[46]==2)
		{$pos=strpos($record["latitude"], ",");
			$latitude=substr($record["latitude"], 0,$pos);
			$longitude=substr($record["latitude"],$pos+1);
			$record["latitude"]=$latitude;
			$record["longitude"]=$longitude;
	}
	$record["latitude"]=str_replace(',', '.', $record["latitude"]);
	$record["longitude"]=str_replace(',', '.', $record["longitude"]);
	
		$latitude_regexp='#^-?([1-8]?[1-9]|[1-9]0)\.{1}\d{1,8}#';
		$longitude_regexp='#^-?([1]?[1-7][1-9]|[1]?[1-8][0]|[1-9]?[0-9])\.{1}\d{1,8}#';

		if ($record["latitude"]!="" && preg_match($latitude_regexp, $record["latitude"])==false)
		{
			echo atkTriggerError($record,  $this->getAttribute("latitude"), "latitude incorrecte");
		}
	if ($record["longitude"]!="" && $record["latitude"]!="" && preg_match($longitude_regexp, $record["longitude"])==false)
		{
			atkTriggerError($record,  $this->getAttribute("longitude"), "longitude incorrecte");
		}
	if ($record["longitude"]==""	&& $record["latitude"]=="")
	{
/*		include_once (moduleDir("utils") . "class.googlemapapi.inc");
		$map = new GoogleMapAPI('map', 'association_map');
		$map->setAPIKey($this->get_map_key());
		*/

		include_once(moduleDir("utils") ."GoogleMap.php");
//include_once(moduleDir("utils") ."JSmin.php");
		$map = new GoogleMapAPI('map', 'association_map');

		$id_ville=$record["id_ville"]["id"];
		$db = & atkGetDb();
		$select = "SELECT c.code_postal as code_postal, c.ville as ville, p.libelle_anglais as pays 
		from type_cp_ville_pays c 
		left join type_pays p on p.id=c.id_pays 
		where c.id= $id_ville ";
		$r = $db->getrows("$select");
		$address = $record['adresse1'] . ", " . $record['adresse2'] . ", " .$r[0]['code_postal'] . ", " . $r[0]['ville'] . ", " . $r[0]['pays'];
		$coords = $map->geoGetCoords($address);
					
					$record["longitude"] = $coords["lon"];
					$record["latitude"] = $coords["lat"];
	}
		
		parent::validate($record, $mode);

	}
	
function action_geolocalisation() 
{		$select = $this->m_postvars["atkselector"];
	$db = & atkGetDb();
		$select = "SELECT latitude, longitude from lieu where $select ";
		$r = $db->getrows("$select");
		$url = "http://maps.google.com/maps?q=".$r[0]["latitude"].",".$r[0]["longitude"];
		header("Location: $url");
		exit;
	}
	
}
?>