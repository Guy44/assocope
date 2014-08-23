<?php
atkimport("atk.assmetanode");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");
class requete_detail extends assMetaNode {
	var $table = "biodiversite_requete_detail";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function requete_detail() {
		$this->atkMetaNode();
		$this->atkNode("requete_detail", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_requete", 
  "id_regnum" ,
  "id_phylum" ,
  "id_classis" ,
  "id_ordo" ,
  "id_famille" ,
  "id_species",
  "nombre_individus" ,
  "nombre_observations",
		"longitude",
				"latitude"
				)
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_requete", "biodiversite.requete", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),100);
				$this->add(new atkDummyAttribute("web_info",0 ),185);
//				$this->add(new atkDummyAttribute("ascendance",0 ),135);
				$this->add(new atkAttribute("n_b_regnum"),110);
				$this->add(new atkAttribute("n_b_phylum"),120);
				$this->add(new atkAttribute("n_b_classis"),130);
				$this->add(new atkAttribute("n_b_ordo"),140);
				$this->add(new atkAttribute("n_b_famille"),150);
				$this->add(new atkAttribute("n_b_species"),160);
			$this->add(new atkAttribute("nom_francais"),162);

				
				
				$this->add(new atkManyToOneRelation("id_regnum", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),210);
				$this->add(new atkManyToOneRelation("id_phylum", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),220);
				$this->add(new atkManyToOneRelation("id_classis", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),230);
				$this->add(new atkManyToOneRelation("id_ordo", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),240);
				$this->add(new atkManyToOneRelation("id_famille", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),250);
				$this->add(new atkManyToOneRelation("id_species", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),163);
				$this->add(new atkAttribute("nombre_individus"),170);
				$this->add(new atkAttribute("nombre_observations"),180);
				$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE| AF_HIDE_VIEW, 25, 15),230)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
				$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE| AF_HIDE_VIEW, 25, 15),240)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
						include_once (atkconfig("atkroot") . "modules/include/association.inc");
 $this->setOrder("n_b_regnum","n_b_phylum","n_b_classis","n_b_ordo","n_b_famille","n_b_species");
			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["mapbiodiversite"] = "view";

	}
function web_info_display($record, $mode)
	{

		$idtaxinomie=trim($record["id_species"]["id"]);
		$db = & atkGetDb();
		$rows = $db->getrows("select nom_binomial,nom_francais, id_taxon_fauna_europaea, id_taxon_conservation_nature from biodiversite_taxinomie where id ='" . $idtaxinomie . "' ");
		$nom=trim($rows[0]["nom_francais"]);
		$nom=str_replace(' ','.',$nom);
		$nom=str_replace('é','e',$nom);
		$nom=str_replace('è','e',$nom);
		$nom=str_replace('ê','e',$nom);
		$nom=str_replace('ë','e',$nom);
		$nom=str_replace('à','a',$nom);
		$nom=str_replace('â','a',$nom);
		$nom=str_replace('ç','c',$nom);
		$nom=str_replace('ù','u',$nom);
		$nom=str_replace('î','i',$nom);
		$nom=str_replace('ï','i',$nom);
		$nom=trim(strtolower($nom));
		$nom=str_replace(" ",".",$nom);
		$target = ' target="_blank"';
		$urloiseaux="http://www.oiseaux.net/oiseaux/".$nom.".html" ;


		$nom_binomial=trim($rows[0]["nom_binomial"]);
		$urlwikipedia_en="http://en.wikipedia.org/wiki/".$nom_binomial ;
		$retour='<a href="' . $urlwikipedia_en . '"' . $target . '"><font color="ForestGreen"><b>wikipedia_en</b></font></a>';
		$retour.=' ';
		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="SELECT code_iso_639_1 from type_langue tl, app_utilisateur u
		 where u.id=$userutilisateur and u.id_langue_application=tl.id";
		$data=$db->getrows($sql);
		$urlwikipedia_loc="http://".$data[0]["code_iso_639_1"].".wikipedia.org/wiki/".$nom_binomial ;
		$retour.='<a href="' . $urlwikipedia_loc . '"' . $target . '"><font color="ForestGreen"><b>wikipedia_loc</b></font></a>';
		$retour.=' ';

		$id_taxon_fe=$rows[0]["id_taxon_fauna_europaea"];
		if (isset($id_taxon_fe))
		{ 	$urlfauna_europaea="http://www.faunaeur.org/full_results.php?id=".$id_taxon_fe ;
		$retour.='<a href="' . $urlfauna_europaea . '"' . $target . '"><font color="ForestGreen"><b>fauna_europaea</b></font></a>';
		$retour.=' ';
		}

		$urltela_botanica="http://www.tela-botanica.org/page:eflore?eflore_nom=".$nom_binomial."&eflore_referentiel=25&eflore_type_nom=nom_scientifique&module=recherche&action=recherche_nom";
		$retour.='<a href="' . $urltela_botanica . '"' . $target . '"><font color="ForestGreen"><b>tela_botanica</b></font></a>';
		$retour.=' ';
		$id_iucn=$rows[0]["id_taxon_conservation_nature"];
		if (isset($id_taxon_fe))
		{ 	$urlconservation_nature="http://www.iucnredlist.org/details/".$id_iucn ;
		$retour.='<a href="' . $urlconservation_nature . '"' . $target . '"><font color="ForestGreen"><b>conservation_nature</b></font></a>';
		$retour.=' ';	}
		$retour.='<a href="' . $urloiseaux . '"' . $target . '"><font color="ForestGreen"><b>Oiseaux.net</b></font></a>';
		$retour.=' ';
		if (true === $this->m_newWindow) {
			$target = ' target="_new"';
		}
		return $retour;
	}
/*
	function ascendance_display($record, $mode)
	{
//		
		$idtaxinomie=trim($record["id_taxinomie"]["id"]);
		$db = & atkGetDb();
		$rows = $db->getrows("select id_parent from biodiversite_taxinomie where id ='" . $idtaxinomie . "' ");
		$id_parent=$rows[0]["id_parent"];
		$ascendance="";
		while (isset($id_parent))
		{
			$sql="SELECT t.id,  id_parent, nom_binomial, nom_latin from biodiversite_taxinomie t , biodiversite_rang_taxinomique r where t.id='".$id_parent."' and t.id_rang_taxinomique=r.id";
			$data=$db->getrows($sql);
			//		http://www.wikistoma.org/association/dispatch.php?atknodetype=biodiversite.taxinomie&atkaction=view&atkselector=biodiversite_taxinomie.id%3D%2782568%27&atklevel=1&atkprevlevel=0&atkstackid=4a1107623cb41&
			// <a target="main"  href="dispatch.php?atknodetype=table.type_placemark&atkaction=admin&atklevel=-1&atkprevlevel=0&">Types Repères</a>
			$id_parent=$data[0]["id_parent"];
			$ascendance='<a target="main" href="dispatch.php?atknodetype=biodiversite.taxinomie&atkaction=view&atkselector=biodiversite_taxinomie.id='.$data[0]["id"]. '&">'.$data[0]["nom_binomial"].'</a>'.'('.$data[0]["nom_latin"].') <br />'.$ascendance;
		}

		return $ascendance;

	}
*/

	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";

	}
	function action_mapbiodiversite() {
/*		echo 'Taxons : '.$this->m_postvars["taxons"].'<br />';
		echo 'Zones : '.$this->m_postvars["zones"].'<br />';
		echo 'date_observation_debut : '.$this->m_postvars["date_observation_debut"].'<br />';
		echo 'date_observation_fin : '.$this->m_postvars["date_observation_fin"].'<br />';
		echo 'heure_observation_debut : '.$this->m_postvars["heure_observation_debut"].'<br />';
		echo 'heure_observation_fin : '.$this->m_postvars["heure_observation_fin"].'<br />';
		echo 'organismes_commanditaire : '.$this->m_postvars["organismes_commanditaire"].'<br />';
		echo 'organismes_observateur : '.$this->m_postvars["organismes_observateur"].'<br />';
		echo 'individus_observateur : '.$this->m_postvars["individus_observateur"].'<br />';
		die();
		*/
		$taxons = $this->m_postvars["taxons"];
		if ($taxons!=0)
		{
			$selectmaptaxons ='select
		o.latitude as latitude,
		o.longitude as longitude,
		o.id_type_localisation,
		o.id_point_observation,
		o.id_lieu,
		o.id_ville,
		oc.nom as organisme_commanditaire,
		oc.id as id_organisme_commanditaire,

		oo.nom as organisme_observateur,
				oo.id as id_organisme_observateur,

		i.nom as nom_observateur, i.prenom as prenom_observateur,
		i.id as id_individu_observateur,

		o.date_observation,
		o.heure_observation,
		t.nom_binomial as nom_binomial,
		t.id as id_taxinomie,
		t.id_parent as id_parent
		
		from 
		biodiversite_observation o,
		biodiversite_requete_detail od,
		biodiversite_taxinomie t,
		organisme oc,
		organisme oo,
		individu i
		where
		od.id_taxinomie in ('.$taxons.') 
		and od.id_taxinomie=t.id
		and od.id_observation=o.id
		and o.id_organisme=oc.id
		and o.id_organisme_observateur=oo.id
		and o.id_observateur=i.id
		
		';

			/*
		 	"taxons" => $taxons,
		 	"zones" => $zones,
		 	"date_observation_debut" => $date_observation_debut,
		 	"date_observation_fin" => $date_observation_fin,
		 	"heure_observation_debut" => $heure_observation_debut,
		 	"heure_observation_fin" => $heure_observation_fin,
		 	"organismes_commanditaire" => $organismes_commanditaire,
		 	"organismes_observateur" => $organismes_observateur,
		 	"individus_observateur" => $individus_observateur,
		 	*/

			return $this->createMarkers($selectmaptaxons, "taxons");
		}
		$zones = $this->m_postvars["zones"];
		if ($zones!='0')
		{
//						echo 'zones';
//			die ();
			$db = & atkGetDb();
			$sql="SELECT distinct bo.id as id_observation
			from
			biodiversite_observation bo,
			biodiversite_point_observation po,
			lieu l,
			type_cp_ville_pays cp
			where
			".$zones."
			and
			(
			(cp.id=bo.id_ville)
			or
			(cp.id=l.id_ville
			and
			l.id=bo.id_lieu)
			or
			(cp.id=l.id_ville
			and
			l.id=po.id_lieu
			and
			po.id=bo.id_point_observation)
			)
			";
			$idobservations="";
			$rows = $db->getrows($sql);
			for ($i = 0; $i < count($rows); $i++) {
				$idobservations.=$rows[$i]["id_observation"].',';
			}
			$idobservations = substr($idobservations, 0, strlen($idobservations) - 1);
			$selectmapzones ='select
		o.latitude as latitude,
		o.longitude as longitude,
		o.id_type_localisation,
		o.id_point_observation,
		o.id_lieu,
		o.id_ville,
		oc.nom as organisme_commanditaire,
		oc.id as id_organisme_commanditaire,

		oo.nom as organisme_observateur,
				oo.id as id_organisme_observateur,

		i.nom as nom_observateur, i.prenom as prenom_observateur,
		i.id as id_individu_observateur,

		o.date_observation,
		o.heure_observation,
		t.nom_binomial as nom_binomial,
		t.nom_francais as nom_francais,
		t.id as id_taxinomie,
		t.id_parent as id_parent
		
		from 
		biodiversite_observation o,
		biodiversite_requete_detail od,
		biodiversite_taxinomie t,
		organisme oc,
		organisme oo,
		individu i
		where
		o.id in ('.$idobservations.') 
		and od.id_taxinomie=t.id
		and od.id_observation=o.id
		and o.id_organisme=oc.id
		and o.id_organisme_observateur=oo.id
		and o.id_observateur=i.id
		order by t.nom_binomial, o.date_observation, o.heure_observation
		
		';	

			return $this->createMarkers($selectmapzones, "zones");
				
		}

	}
	function createMarkers($select, $type) {
		include_once (moduleDir("utils") . "class.googlemapapi.inc");
		$map = new GoogleMapAPI('map', 'association_map');
		$map->setAPIKey($this->get_map_key());
		$map->setHeight("800");
		$map->setWidth("1500");
		//$map->disableTypeControls();
		$map->setMapType('hybrid'); // default
		//$map->disableDirections();
		$map->enableZoomEncompass();
		$map->enableOverviewControl();
		$db = & atkGetDb();
		$r = $db->getrows("$select");
		$site = atkHost();
		$urlsite = 'http://' . $site;
		$sitesanswww = substr_replace($site, '', 0, 4);
		for ($i = 0; $i < count($r); $i++) {
			$title=$r[$i]['nom_binomial'].' ('.$r[$i]['nom_francais'].') ('.$r[$i]['date_observation'].' '.$r[$i]['heure_observation'].')';
			$html_individu_observateur="<a href='dispatch.php?atknodetype=individu.individu&atkaction=edit&atkselector=individu.id="
			. $r[$i]['id_individu_observateur'] . "'>" . $r[$i]['nom_observateur'] . " " . $r[$i]['prenom_observateur'] . "</a>" . "<br />"
			;
			$html_organisme_observateur="<a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id="
			. $r[$i]['id_organisme_observateur'] . "'>" . $r[$i]['organisme_observateur']  . "</a>" . "<br />"
			;
			$html_organisme_commanditaire="<a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id="
			. $r[$i]['id_organisme_commanditaire'] . "'>" . $r[$i]['organisme_commanditaire']  . "</a>" . "<br />"
			;
			// ville
			if ($r[$i]['id_type_localisation']==1)
			{
				$sql="SELECT latitude, longitude from type_cp_ville_pays
				where id='".$r[$i]['id_ville']."'";
				$data=$db->getrows($sql);

			}
			//lieu
			if ($r[$i]['id_type_localisation']==2)
			{
				$sql="SELECT latitude, longitude from lieu
				where id='".$r[$i]['id_lieu']."'";
				$data=$db->getrows($sql);

			}
			// point observation
			if ($r[$i]['id_type_localisation']==3)
			{
				$sql="SELECT l.latitude, l.longitude from biodiversite_point_observation po, lieu l
				where po.id='".$r[$i]['id_point_observation']."' and po.id_lieu=l.id";
				$data=$db->getrows($sql);

			}
			$longitude=$data[0]["longitude"];
			$latitude=$data[0]["latitude"];
			$date_observation = $r[$i]['date_observation'];
			$heure_observation = $r[$i]['heure_observation'];


			$id_taxinomique=$r[$i]['id_taxinomie'];
			$id_parent=$r[$i]['id_parent'];
			$ascendance="";
			$sql="SELECT t.id,  id_parent, nom_binomial , t.nom_francais as nom_francais, nom_latin from biodiversite_taxinomie t , biodiversite_rang_taxinomique r where t.id='".$id_taxinomique."' and t.id_rang_taxinomique=r.id";
			$data=$db->getrows($sql);
			$id_parent=$data[0]["id_parent"];
			$ascendance='<a target="main" href="dispatch.php?atknodetype=biodiversite.taxinomie&atkaction=view&atkselector=biodiversite_taxinomie.id='.$data[0]["id"]. '&">'.$data[0]["nom_binomial"].'</a>'.'('.$data[0]["nom_francais"].')('.$data[0]["nom_latin"].') <br /> '.$ascendance;

			while (isset($id_parent))
			{
				$sql="SELECT t.id,  id_parent, nom_binomial, nom_latin from biodiversite_taxinomie t , biodiversite_rang_taxinomique r where t.id='".$id_parent."' and t.id_rang_taxinomique=r.id";
				$data=$db->getrows($sql);
				$id_parent=$data[0]["id_parent"];
				$ascendance='<a target="main" href="dispatch.php?atknodetype=biodiversite.taxinomie&atkaction=view&atkselector=biodiversite_taxinomie.id='.$data[0]["id"]. '&">'.$data[0]["nom_binomial"].'</a>'.'('.$data[0]["nom_latin"].')  '.$ascendance;
			}

			$record["id_taxinomie"]["id"]=$r[$i]['id_taxinomie'];
			$html_liens_web=$this->web_info_display($record, $mode);
				
			$html=$ascendance.' ';
			$html .= $html_liens_web.'<br />';
			$html .= 'Observé par : '.$html_individu_observateur.' pour  '. $html_organisme_observateur;
			$html .= 'Le : '.$date_observation. ' à '.$heure_observation.'<br />';
			$html .= 'Organisme : '. $html_organisme_commanditaire.' ';
			/*echo $html;
			 echo 'lon : '.$longitude ;
			 echo ' lat : '.$latitude ;
			 die();
			 */

			$map->addMarkerByCoords($longitude, $latitude, $title, $html);

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
		//		$output .= $missing . " : non géolocalisables";
		//		$output .= $missingnoms;
		//		$output .= "<br />" . $missingadresse . " : sans adresse";
		//		$output .= $missingadressenoms;
		$output .= "</font></body>";
		$output .= "</html>";
		$output1->rawoutput($output);
		$output1->outputFlush();
	}
/*
	 * #  
# FUNCTION recur($pere,$rang,$conn)
# fonction récursive d'affichage de l'arbre
# $pere :Element courant
# $rang :Décallage de l'element
# $conn :Index de la connexion a utiliser
# 
*/
	

 function recur($pere,$rang=0)
 {
 		$db = & atkGetDb();
 $sql="select id_parent,id from biodiversite_taxinomie where id_parent='$pere'";
 $r=$db->getrows($sql);
$nblignes=count($r);
 if($nblignes > 0)// si il y a au moins 1 resultat
 {
 for($i=0 ;$i<$nblignes ;$i++)// tant qu'il y a des lignes on affiche les enfants
 {
 $parent=$r[$i]["id_parent"];
 $enfant=$r[$i]["id"];

 if ($parent==$pere)// si un élément a pour père : $pere
 {
 $result.= espace($rang)."<font color='blue'><b>".$enfant."</b></font><BR />"; // on l'affiche avec le décallage courrant et on recherche ses fils
 recur($enfant,$rang+1,$conn); // en rappelant la fonction recur() (+ incrémentation du décallage)
 }
 }
 }
 return ($result);
 // /echo"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color='red'><b>$recherche</b></font><br>";
 //recur($recherche,1,$conn); 
 }

}
?>