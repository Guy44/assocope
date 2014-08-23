<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class Distance_Aller_Blanc extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_blanc) as distance_aller_blanc
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou<10 ");
		return $rows[0]["distance_aller_blanc"];
	}
}
class Distance_Aller_Jaune extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_jaune) as distance_aller_jaune
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou<10 ");
		return $rows[0]["distance_aller_jaune"];
	}
}
class Distance_Aller_Bleu extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_bleu) as distance_aller_bleu
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou<10 ");
		return $rows[0]["distance_aller_bleu"];
	}
}
class Distance_Aller_Rouge extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_rouge) as distance_aller_rouge
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou<10 ");
		return $rows[0]["distance_aller_rouge"];
	}
}
class Distance_Retour_Blanc extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_blanc) as distance_retour_blanc
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou>9 ");
		return $rows[0]["distance_retour_blanc"];
	}
}
class Distance_Retour_Jaune extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_jaune) as distance_retour_jaune
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou>9 ");
		return $rows[0]["distance_retour_jaune"];
	}
}
class Distance_Retour_Bleu extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_bleu) as distance_retour_bleu
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou>9 ");
		return $rows[0]["distance_retour_bleu"];
	}
}
class Distance_Retour_Rouge extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_rouge) as distance_retour_rouge
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou>9 ");
		return $rows[0]["distance_retour_rouge"];
	}
}
class Distance_Aller_Retour_Blanc extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_blanc) as distance_aller_retour_blanc
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours  ");
		return $rows[0]["distance_aller_retour_blanc"];
	}
}
class Distance_Aller_Retour_Jaune extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_jaune) as distance_aller_retour_jaune
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours  ");
		return $rows[0]["distance_aller_retour_jaune"];
	}
}
class Distance_Aller_Retour_Bleu extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_bleu) as distance_aller_retour_bleu
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours  ");
		return $rows[0]["distance_aller_retour_bleu"];
	}
}
class Distance_Aller_Retour_Rouge extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.distance_rouge) as distance_aller_retour_rouge
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours ");
		return $rows[0]["distance_aller_retour_rouge"];
	}
}
class Par_Aller extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.par) as par_aller
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou<10 ");
		return $rows[0]["par_aller"];
	}
}
class Par_Retour extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.par) as par_retour
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours and t.numero_trou>9 ");
		return $rows[0]["par_retour"];
	}
}
class Par_Total extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT SUM(t.par) as par_total
				 FROM organisme_golf_parcours_trou t, organisme_golf_parcours p
				  where p.id='" . $record["id"] . "' and p.id=t.id_organisme_parcours  ");
		return $rows[0]["par_total"];
	}
}
class golf_parcours extends assMetaNode {
	var $table = "organisme_golf_parcours";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "regles_locales", AF_HIDE_LIST);
	}
	function golf_parcours() {
		$this->atkMetaNode();
		$this->atkNode("golf_parcours",  NF_MRA | NF_ADD_LINK | NF_TRACK_CHANGES| NF_ADDAFTERADD );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (

				"descripteur_parcours",
		"id_organisme",
				"libelle","Sss","Slope", 
					"latitude",
		"longitude",
		"altitude",
				"url_meteo",
				"consulter_meteo",
				"id_document_photo",
				"green_fee_haute_saison",
				"green_fee_basse_saison","regles_locales",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
				"Suite" => array (
				"distance_aller_blanc",
				"distance_retour_blanc",
				"distance_aller_retour_blanc",
				"sss_blanc",
				"slope_blanc",
				"distance_aller_jaune",
				"distance_retour_jaune",
				"distance_aller_retour_jaune",
				"sss_jaune",
				"slope_jaune",
				"distance_aller_bleu",
				"distance_retour_bleu",
				"distance_aller_retour_bleu",
				"sss_bleu",
				"slope_bleu",
				"distance_aller_rouge",
				"distance_retour_rouge",
				"distance_aller_retour_rouge",
				"sss_rouge",
				"slope_rouge",
				"Aller","Retour","Aller_Retour",
				"par_aller",
				"par_retour",
				"par_total"
				),
			"Trous" => array (
				"trous"
				)
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE), 100);
				$this->add(new atkDummyAttribute("descripteur_parcours"),NULL, 5);

				$this->add(new atkNumberAttribute("green_fee_haute_saison", AF_SEARCHABLE, 5, 0));
				$this->add(new atkNumberAttribute("green_fee_basse_saison", AF_SEARCHABLE, 5, 0));
//				$this->addFieldSet("Titre","[slope_blanc.label] [slope_jaune.label] [slope_bleu.label] [slope_rouge.label]",AF_BLANK_LABEL|AF_HIDE_SEARCH,NULL,849 );
				$this->addFieldSet("Aller","[distance_aller_blanc.field] [distance_aller_bleu.field] [distance_aller_bleu.field] [distance_aller_rouge.field]",AF_HIDE_SEARCH,NULL,850 );
				$this->addFieldSet("Retour","[distance_retour_blanc.field] [distance_retour_bleu.field] [distance_retour_bleu.field] [distance_retour_rouge.field]",AF_HIDE_SEARCH,NULL,851 );
				$this->addFieldSet("Aller_Retour","[distance_aller_retour_blanc.field] [distance_aller_retour_bleu.field] [distance_aller_retour_bleu.field] [distance_aller_retour_rouge.field]",AF_HIDE_SEARCH,NULL,851 );
				$this->addFieldSet("Sss","[sss_blanc.field] [sss_bleu.field] [sss_bleu.field] [sss_rouge.field]",AF_HIDE_SEARCH,NULL,852 );
				$this->addFieldSet("Slope","[slope_blanc.field] [slope_bleu.field] [slope_bleu.field] [slope_rouge.field]",AF_HIDE_SEARCH,NULL,853 );

				$this->add(new Distance_Aller_Blanc("distance_aller_blanc", AF_HIDE_LIST |AF_READONLY), 110);
				$this->add(new Distance_Retour_Blanc("distance_retour_blanc", AF_HIDE_LIST |AF_READONLY), 115);
				$this->add(new Distance_Aller_Retour_Blanc("distance_aller_retour_blanc", AF_HIDE_LIST |AF_READONLY), 120);
				$this->add(new atkAttribute("sss_blanc",AF_HIDE_LIST), 125);
				$this->add(new atkAttribute("slope_blanc", AF_HIDE_LIST),130);
				$this->add(new Distance_Aller_Jaune("distance_aller_jaune", AF_HIDE_LIST |AF_READONLY), 140);
				$this->add(new Distance_Retour_Jaune("distance_retour_jaune", AF_HIDE_LIST |AF_READONLY), 145);
				$this->add(new Distance_Aller_Retour_Jaune("distance_aller_retour_jaune", AF_HIDE_LIST |AF_READONLY), 150);
				$this->add(new atkAttribute("sss_jaune",AF_HIDE_LIST), 155);
				$this->add(new atkAttribute("slope_jaune",AF_HIDE_LIST), 160);
				$this->add(new Distance_Aller_Bleu("distance_aller_bleu", AF_HIDE_LIST |AF_READONLY), 170);
				$this->add(new Distance_Retour_Bleu("distance_retour_bleu", AF_HIDE_LIST |AF_READONLY), 175);
				$this->add(new Distance_Aller_Retour_Bleu("distance_aller_retour_bleu", AF_HIDE_LIST |AF_READONLY), 180);
				$this->add(new atkAttribute("sss_bleu", AF_HIDE_LIST),185);
				$this->add(new atkAttribute("slope_bleu", AF_HIDE_LIST),190);
				$this->add(new Distance_Aller_Rouge("distance_aller_rouge", AF_HIDE_LIST |AF_READONLY), 200);
				$this->add(new Distance_Retour_Rouge("distance_retour_rouge", AF_HIDE_LIST |AF_READONLY), 205);
				$this->add(new Distance_Aller_Retour_Rouge("distance_aller_retour_rouge", AF_HIDE_LIST |AF_READONLY), 210);
				$this->add(new atkAttribute("sss_rouge", AF_HIDE_LIST),215);
				$this->add(new atkAttribute("slope_rouge", AF_HIDE_LIST),220);
				$this->add(new Par_Aller("par_aller", AF_READONLY), 240);
				$this->add(new Par_Retour("par_retour", AF_READONLY), 245);
				$this->add(new Par_Total("par_total", AF_READONLY), 250);
				$this->add(new atkfckattribute("regles_locales", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '750px',
			'Height' => '150px'
			)));
			$this->add(new atkAttribute("latitude",null),280);
			$this->add(new atkAttribute("longitude", null),285);
			$this->add(new atkAttribute("altitude", null),290);
			$this->add(new atkUrlAttribute("url_meteo", AF_POPUP), 300);
			$this->add(new atkParserAttribute("consulter_meteo", "<a href=\"[url_meteo]\" target=\"_blank\">meteo</a>", AF_NO_LABEL | AF_HIDE_ADD | AF_HIDE_LIST), 305);
			$this->add(new atgFileManyToOneRelation("id_document_photo", "organisme.document",  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), 310);
			//				$this->add(new atkParserAttribute("vcard", href("?atkaction=vcard&id=[id]", atktext("vcard"), SESSION_NESTED), AF_NO_LABEL | AF_HIDE_ADD), NULL, 10000);
			$this->add(new atkOneToManyRelation("trous", "organisme.golf_parcours_trou", "id_organisme_parcours", AF_HIDE_LIST));
			//				$this->add(new atkExpressionAttribute("distance_aller",'SELECT SUM(distance_blanc) FROM organisme_golf_parcours_trou  WHERE id_organisme_parcours = [table].id'));
			$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), 51);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,6 );
			$this->setOrder(" libelle ");
			//			$this->setIndex("libelle");
			$this->m_securityMap["autocomplete"] = "view";
	}
	function descriptor_def() {
		return "([id_organisme.nom]) [libelle]";
		//		return "[libelle]";
		}

	function descriptorFields()
	{
		return array("id", "libelle", "latitude", "longitude", "altitude", "url_meteo", "id_organisme",
		"sss_blanc", "sss_jaune", "sss_bleu", "sss_rouge",
		"slope_blanc", "slope_jaune", "slope_bleu", "slope_rouge", "green_fee_haute_saison", "green_fee_basse_saison", "trous");
	}


	function descriptor($record,$long_o_n="o",$atk_o_n="o")
	{ 
		if ($this->m_action!="admin" && $atk_o_n=="o") 
		{if (method_exists($this,"descriptor_def"))
		{
			atkimport("atk.utils.atkstringparser");
			$parser = new atkStringParser($this->descriptor_def());
			return $parser->parse($record);
		}}
		else {
		if ($record['id']=="") return true;
		$href=href(dispatch_url("organisme.golf_parcours", "admin", array (	'atkfilter' => "organisme_golf_parcours.id='" .$record["id"]. "'"
		), "dispatch.php"), $record["libelle"], SESSION_NESTED, null, " title=\"Parcours\" ");
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/golf_tee.png" alt="Parcours"
			title="Parcours"  ></img>'.' <b>'.$href." ";
/*		$nombre_trous=count($record["trous"]);

		*/
		$db = & atkGetDb();
					$sql="select count(id) as nombre_trous from organisme_golf_parcours_trou  where id_organisme_parcours=".$record['id'];
  					$data = $db->getrows($sql);

					$href=href(dispatch_url("organisme.golf_parcours_trou", "admin", array (	'atkfilter' => "organisme_golf_parcours_trou.id_organisme_parcours=".$record["id"]
		), "dispatch.php"), " (<b><font color=\"Coral\">".$data[0]["nombre_trous"]."</font></b>)", SESSION_NESTED, null, " title=\"Trous\" ");
		$retour.=$href;
					
		if ($record["latitude"]=="")
		{}
		else
		{
			$retour.=' <a href="'.'http://maps.google.com/maps?q='.$record["latitude"].','.$record["longitude"].'&iwloc=A&hl=fr" target="_blank">'.
			'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/maps.png" alt="Parcours" 
			title="Maps"  ></img></a></b>';
		}
		if ($record["url_meteo"]=="")
		{}
		else
		{
			$retour.=' <a href="'.$record["url_meteo"].'" target="_blank">'.
			'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/meteo.png" alt="Météo" 
			title="Météo"  ></img></a></b>';
		}
	//	http://www.wikistoma.org/association/dispatch.php?
	// atknodetype=organisme.document&
	//atkaction=fichier&
	//atkselector=organisme_document.id%3D%271564%27
	//&atklevel=2&atkprevlevel=1&atkstackid=4fa385a041cd7&
		if ($record["id_document_photo"]!='')
		{
		$retour.=href(dispatch_url("organisme.document", "fichier", array (	'atkselector' => "organisme_document.id='" .$record["id_document_photo"]["id"]. "'"
		), "dispatch.php"), ' <img class="recordlist" border="0" src="./themes/assocope/icons/assocope/photo-icone.png" alt="Photo parcours"	title="Photo parcours"  ></img>', SESSION_NESTED, null, " title=\"Photo parcours\" target=\"_blank\"");
		}
				

		if ($record["green_fee_basse_saison"]=="" && $record["green_fee_haute_saison"]=="" )
		{
			$retour.="";
		}
		else {
			$retour.="</b> Green fee : <b>";
			($record["green_fee_basse_saison"]!="" ) ? $retour.=$record["green_fee_basse_saison"] : $retour.="";
			($record["green_fee_haute_saison"]!="" ) ? $retour.="/".$record["green_fee_haute_saison"] : $retour.="";
		}

		
		($record["id_organisme"]["id"]!="") ? $retour.="<br/>".$this->descripteur_organisme($record["id_organisme"]["id"],'n','n',null) : null;

		if ($long_o_n=="o")
		{
$this->addStyle("recordlist.css");
		$recs = $this->selectDb("organisme_golf_parcours.id=".$record['id']);
		$nombre_trous=count($recs[0]["trous"]);
		//      $this->p($recs);

		$tableautrous="<table class=\"golfgg\"><tr>";
		$tableautrous.="<tr><td class=\"golfgg\"></td>";
		$tableautrous.="<td class=\"golfgg\">Sss</td>";
		$tableautrous.="<td class=\"golfgg\">Slope</td>";
			
			
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">Aller</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["numero_trou"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">Retour</td>";
		$tableautrous.="<td class=\"golfgg\">A/R</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr style=\"background: white\"><td class=\"golfgg\">Blanc</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_blanc']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_blanc']."</td>";
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_blanc"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_blanc']."</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_blanc"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_blanc']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_blanc']."</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr style=\"background: yellow\"><td class=\"golfgg\">Jaune</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_jaune']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_jaune']."</td>";
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_jaune"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_jaune']."</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_jaune"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_jaune']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_jaune']."</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr style=\"background: aqua\"><td class=\"golfgg\">Bleu</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_bleu']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_bleu']."</td>";
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_bleu"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_bleu']."</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_bleu"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_bleu']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_bleu']."</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr style=\"background: red\"><td class=\"golfgg\">Rouge</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['sss_rouge']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['slope_rouge']."</td>";
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_rouge"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_rouge']."</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["distance_rouge"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_retour_rouge']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['distance_aller_retour_rouge']."</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr><td class=\"golfgg\">Par</td>";
		$tableautrous.="<td class=\"golfgg\"></td>";
		$tableautrous.="<td class=\"golfgg\"></td>";


		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_aller']."</td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["par"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_retour']."</td>";
		$tableautrous.="<td class=\"golfgg\">".$recs[0]['par_total']."</td>";
		$tableautrous.="</tr>";

		$tableautrous.="<tr><td class=\"golfgg\">Handicap</td>";
		$tableautrous.="<td class=\"golfgg\"></td>";
		$tableautrous.="<td class=\"golfgg\"></td>";
		for ($i = 0; $i < 9; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\"></td>";
		for ($i = 9; $i < $nombre_trous; $i++)
		{       	$tableautrous.="<td class=\"golfgg\">".trim($recs[0]["trous"][$i]["coups_recus"])."</td>";       	       }
		$tableautrous.="<td class=\"golfgg\"></td>";
		$tableautrous.="<td class=\"golfgg\"></td>";

		$tableautrous.="</tr></table>";
		}
		$retour.=$tableautrous;
		$this->descripteur_aide('Descripteur_golf_parcours','n');
		return $retour;
		}
	}
	function descripteur_parcours_display($record, $mode) {
		return $this->descriptor($record);
	}
	function descripteur_parcours_edit($record, $mode) {
		return $this->descriptor($record);
	}

	/*
	 function descripteur_parcours_display($record, $mode) {
		return $this->descripteur_golf_parcours($record["id"],'o').'<br />';
		}
		function descripteur_parcours_edit($record, $mode) {
		return $this->descripteur_golf_parcours($record["id"],'o').'<br />';
		}
		*/
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

	function validate(& $record, $mode) {
		// latitude : ^-?([1-8]?[1-9]|[1-9]0)\.{1}\d{1,6}
		// longitude : ^-?([1]?[1-7][1-9]|[1]?[1-8][0]|[1-9]?[0-9])\.{1}\d{1,6}
		//compass direction N90.00.00 E180.00.00 | S34.59.33 W179.59.59 | N00.00.00 W000.00.00 :  ^[NS]([0-8][0-9](\.[0-5]\d){2}|90(\.00){2})\040[EW]((0\d\d|1[0-7]\d)(\.[0-5]\d){2}|180(\.00){2})$
		// Vérifier s'il s'agit d'un collé depuis maps
		// vrai s'il y a un point, une virgule, un point
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

		parent::validate($record, $mode);

	}

	function recordActions($rec, &$actions, &$mraactions)
	{
		$mraactions['delete'] = "delete";

	}

}
?>