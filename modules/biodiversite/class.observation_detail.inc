<?php
atkimport("atk.assmetanode");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");
class observation_detail extends assMetaNode
{
	var $table = "biodiversite_observation_detail";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function observation_detail() {
		$this->atkMetaNode();
		$this->atkNode("observation_detail", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_observation",
		"id",
		"descripteur_observation",
				"id_taxinomie",
"descripteur_taxinomie",
						"web_info",
"descripteur_inpn",
		"a_verifier_o_n"
		,

		"ascendance",

			"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"),

			"Géolocalisation" => array (	
				"longitude",
				"latitude",
				"altitude"),
			"Oiseaux" => array (
				"nombre",
				"oiseau_nicheur",
		"oiseau_migrateur",
				"oiseau_estivant",
				"oiseau_hivernant",
				"id_type_sexe",
				"id_type_physiologie",
				
				"distance_point_metre",
				"en_vol"
				)
				,
				"Protection" => array (
				"protections_toutes",
				"protections",
				"listes_rouges",
				"especes_determinantes",
				)
				,
				
			"Observations" => array (
				"contenu_html"
				)
				), AF_NO_LABEL));
				$this->add(new atkNumberAttribute("id", AF_SEARCHABLE | AF_HIDE_EDIT | AF_HIDE_ADD|AF_FORCE_LOAD, 10, 0),121);
				$this->add(new atkManyToOneRelation("id_observation", "biodiversite.observation", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),123);
				$this->add(new atkDummyAttribute("descripteur_observation",0 , AF_HIDE_EDIT | AF_HIDE_ADD | AF_COMPACT),101);
				$this->add(new atkDummyAttribute("photo",0 , AF_HIDE_EDIT | AF_HIDE_ADD| AF_COMPACT),112);
				$this->add(new atkDummyAttribute("web_info",0 , AF_HIDE_EDIT | AF_HIDE_ADD| AF_COMPACT),116);
				$this->add(new atkDummyAttribute("descripteur_inpn",0 , AF_HIDE_EDIT | AF_HIDE_ADD| AF_COMPACT),117);
				$this->add(new atkDummyAttribute("protections_toutes",0 , AF_HIDE_ADD| AF_COMPACT),118);
				$this->add(new atkBoolAttribute("a_verifier_o_n"),134);
				$this->add(new atkListAttribute("oiseau_nicheur",
				array ('Non_applicable','Accidentel','Rare','Commun' , 'Très commun'),array (null,'A','R','C' , 'CC' )));
				$this->add(new atkListAttribute("oiseau_migrateur",
				array ('Non_applicable','Accidentel','Rare','Commun' , 'Très commun'),array (null,'A','R','C' , 'CC' )));
				$this->add(new atkListAttribute("oiseau_estivant",
				array ('Non_applicable','Accidentel','Rare','Commun' , 'Très commun'),array (null,'A','R','C' , 'CC' )));
				$this->add(new atkListAttribute("oiseau_hivernant",
				array ('Non_applicable','Accidentel','Rare','Commun' , 'Très commun'),array (null,'A','R','C' , 'CC' )));
					
				$this->add(new atkDummyAttribute("ascendance",0 , AF_HIDE_EDIT | AF_HIDE_ADD| AF_COMPACT),114);

				$this->add(new atkManyToOneRelation("id_taxinomie", "biodiversite.taxinomie", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),122);
				$this->add(new atkDummyAttribute("descripteur_taxinomie",0, AF_HIDE_EDIT | AF_HIDE_ADD | AF_COMPACT),111);
				$this->add(new atkListAttribute("id_type_sexe", array("Mâle", "Femelle", "Indifférencié"), array(1,2,3),AF_SEARCHABLE|AF_OBLIGATORY),145);
				$this->add(new atkListAttribute("id_type_physiologie", array("Adulte", "Juvénile","Larve", "Indifférencié"), array(1,2,3,4),AF_SEARCHABLE|AF_OBLIGATORY),146);

				//				$c12->setDestinationFilter("biodiversite_taxinomie.id_rang_taxinomique between 22 and 29");
				$this->add(new atkAttribute("nombre", AF_OBLIGATORY),140);
				$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE, 25, 15),240);
				$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE, 25, 15),242);
				$this->add(new atkNumberAttribute("altitude", AF_SEARCHABLET, 25, 15),244);
				$this->add(new atkNumberAttribute("distance_point_metre",AF_SEARCHABLE, 3,0),260);
				$this->add(new atkBoolAttribute("en_vol"));
				$this->add(new atkfckattribute("contenu_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
			)),270);
			$this->add(new atkDummyAttribute("protections",0, AF_HIDE_ADD ),130);
			$this->add(new atkDummyAttribute("listes_rouges",0 , AF_HIDE_ADD),131);
			$this->add(new atkDummyAttribute("especes_determinantes",0 ,AF_HIDE_ADD),132);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,120 );
			//			$this->setOrder("biodiversite_taxinomie.nom_binomial");
			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["biolocalisation"] = "view";
			$this->m_securityMap["a_verifier"] = "view";
			$this->m_securityMap["verifie"] = "view";
			$this->m_securityMap["mapbiodiversite"] = "view";
			$this->m_securityMap["createMarkerLonLat"] = "view";
			$this->m_securityMap["forcer_cdref"] = "view";
			


	}
	function descripteur_inpn_display($record, $mode)
	{
		$idtaxinomie=trim($record["id_taxinomie"]["id"]);
		return $this->decoupe_affichage_colonne($this->descripteur_biodiversite_taxons_inpn($idtaxinomie,"taxinomie"),50);
	}
		function protections_toutes_display($record, $mode)
	{
		$protections=$this->protections_display($record, $mode);
		$listes_rouges=$this->listes_rouges_display($record, $mode);
		$especes_determinantes=$this->especes_determinantes_display($record, $mode);
		(!empty($protections)) ? $retour.='<b>>> Protections : </b>'.$protections : $retour.='';
		(!empty($retour)) ? $retour.='<br />': $retour.='';
		(!empty($listes_rouges)) ? $retour.='<b>>> Listes rouges : </b>'.$listes_rouges : $retour.='';
		(!empty($retour)) ? $retour.='<br />': $retour.='';
		(!empty($especes_determinantes)) ? $retour.='<b>>> Espèces déterminantes : </b>'.$especes_determinantes : $retour.='';
		return $retour;
	}
	
	function protections_display($record, $mode)
	{

		$db = &atkGetDb();
		$idtaxinomie=$record["id_taxinomie"]["id"];
		$idobservation=$record["id_observation"]["id"];
		$sql="select code_departement_protection from biodiversite_observation where id='$idobservation'";
		$data=$db->getrows($sql);
		$departement=$data[0]["code_departement_protection"];
		$sql="select cd_ref from biodiversite_taxinomie where id='$idtaxinomie'";
		$data=$db->getrows($sql);
		$cdref=$data[0]["cd_ref"];
		$retour=$this->descripteur_biodiversite_protection($idtaxinomie,$idobservation,'détails','protection','affichage',$cdref,$departement);
		return $retour;
	}
	function listes_rouges_display($record, $mode)
	{
		$db = &atkGetDb();
		$idtaxinomie=$record["id_taxinomie"]["id"];
		$idobservation=$record["id_observation"]["id"];
		$sql="select code_departement_protection from biodiversite_observation where id='$idobservation'";
		$data=$db->getrows($sql);
		$departement=$data[0]["code_departement_protection"];
		$sql="select cd_ref from biodiversite_taxinomie where id='$idtaxinomie'";
		$data=$db->getrows($sql);
		$cdref=$data[0]["cd_ref"];
		$retour=$this->descripteur_biodiversite_protection($idtaxinomie,$idobservation,'détails','liste_rouge','affichage',$cdref,$departement);
		return $retour;
	}
	function especes_determinantes_display($record, $mode)
	{
		$db = &atkGetDb();
		$idtaxinomie=$record["id_taxinomie"]["id"];
		$idobservation=$record["id_observation"]["id"];
		$sql="select code_departement_protection from biodiversite_observation where id='$idobservation'";
		$data=$db->getrows($sql);
		$departement=$data[0]["code_departement_protection"];
		$sql="select cd_ref from biodiversite_taxinomie where id='$idtaxinomie'";
		$data=$db->getrows($sql);
		$cdref=$data[0]["cd_ref"];
		$retour=$this->descripteur_biodiversite_protection($idtaxinomie,$idobservation,'détails','espece_determinante','affichage',$cdref,$departement);
		return $retour;
	}

	function descripteur_observation_display($record, $mode)
	{

		$retour=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_observation($record["id_observation"]["id"],"affichage"),50);
		return $retour;
	}
	function descripteur_taxinomie_display($record, $mode)
	{

		$retour=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_taxinomie($record["id_taxinomie"]["id"],$record["id_observation"]["id"],"affichage"),50);
		return $retour;
	}

	function initial_values()
	{
		$initial=array();
		$initial['distance_point_metre']=0;
		$initial['en_vol']=0;
		$initial['id_type_sexe']=3;
		$initial['id_type_physiologie']=4;
		$initial['altitude']=null;
		$initial['nombre']=1;
		return $initial;
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$filtre=$this->m_postvars["atkfilter"];
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="Orange"> <b> A vérifier </b></font>';
		$view = $this->getView();
		$retour_a_verifier=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=a_verifier', 'Observations détails à vérifier'); 
		$retour_verifie=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=verifie', 'Observations détails vérifiées') ;
		$retour_tout=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=tout', 'Tout') ;
		//
		$db = & atkGetDb();
		if ($filtre=='')
		{
			$rows = $db->getrows("select count(distinct id) as nombre from biodiversite_observation_detail where
			 biodiversite_observation_detail.a_verifier_o_n='1' ");
		}
		else
		{
			$rows = $db->getrows("select count(distinct id) as nombre from biodiversite_observation_detail where ".$filtre." and
	
			 biodiversite_observation_detail.a_verifier_o_n='1' ");
		}
		$nombre_a_verifier=$rows[0]["nombre"]	;
		if ($filtre=='')
		{
			$rows = $db->getrows("select count(distinct id) as nombre  from biodiversite_observation_detail where a_verifier_o_n='0'");
		}
		else
		{
			$rows = $db->getrows("select count(distinct id) as nombre from biodiversite_observation_detail where ".$filtre." and  a_verifier_o_n='0'");
		}
		$nombre_verifie=$rows[0]["nombre"]	;
		if ($filtre=='')
		{$rows = $db->getrows("select count(id) as nombre from biodiversite_observation_detail ");

		}
		else
		{$rows = $db->getrows("select count(id) as nombre from biodiversite_observation_detail where ".$filtre."");}
		$nombre_tout=$rows[0]["nombre"]	;
		$retour='Sélection :  ';
		if ($view == "tout")
		{$retour.= "<b>Tout(".$nombre_tout.')</b>|'.$retour_a_verifier.'('.$nombre_a_verifier.')|'.$retour_verifie.'('.$nombre_verifie.')';}
		if ($view == "a_verifier")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.'<b>Observations détails à vérifier('.$nombre_a_verifier.')</b>|'.$retour_verifie.'('.$nombre_verifie.')';}
		if ($view == "verifie")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_a_verifier.'('.$nombre_a_verifier.')|'.'<b>Observations détails vérifiées('.$nombre_verifie.')</b>';}

		$retour.='<br>';

		return '</b>'.$legende .'<br />'.$retour.'<b>';
		return $legende .$retour;

	}
	function adminHeader() {
$retour=parent::adminHeader();
		return $retour.$this->adminFooter();
	}
	function rowColor($record)
	{
		if ($record["a_verifier_o_n"]==1) {
			return "Orange";
		} else {
			return '';
		}
	}


	public function action_a_verifier()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE biodiversite_observation_detail set a_verifier_o_n='1',
			 id_modification='".$userutilisateur."',
			date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_verifie()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE biodiversite_observation_detail set a_verifier_o_n='0',
			 id_modification='".$userutilisateur."',
			date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	
	public function action_forcer_cdref()
	{
		$retour=$this->get_row_selection_information(false);
			$db = & atkGetDb();
			$userid=$retour["userid"];
			$sql="select bt.id as id_bt , bt.cd_ref, bt.cd_nom, bod.id as id_bod
			from biodiversite_observation_detail bod, biodiversite_taxinomie bt 
			where bod.id in ".$retour["in_id_string"]." 
			and bod.id_taxinomie=bt.id";
				$data=$db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["cd_ref"]!= $data[$i]["cd_nom"])
				{
					$sql="select bt.id from biodiversite_taxinomie bt where bt.cd_nom=".$data[$i]["cd_ref"]."
					";
					$row=$db->getrows($sql);
					if (count($row)==0 ) 
					{echo "pas de taxon pour cd_ref = ".$data[$i]["cd_ref"]." de id_taxon = ".$data[$i]["id_bt"];
					die();}
					if (count($row)>1) 
					{echo "plus d\'un taxon pour cd_ref = ".$data[$i]["cd_ref"]." de id_taxon = ".$data[$i]["id_bt"];
					die();}
					$sql="update biodiversite_observation_detail 
					set id_modification=".$retour["userid"]." , date_modification=UTC_TIMESTAMP(), a_verifier_o_n='0', id_taxinomie='".$row[0]["id"]."'
					where id= ".$data[$i]["id_bod"]."
					";
					$db->query($sql);
				}
			
				
			}
			
			$this->redirect();
			
			
	}
	


	function web_info_display($record, $mode)
	{

		$idtaxinomie=trim($record["id_taxinomie"]["id"]);
		return $this->descripteur_biodiversite_web_info($idtaxinomie,"taxinomie");
	}
	/*	$db = & atkGetDb();
		$rows = $db->getrows("select nom_binomial,nom_francais, id_taxon_fauna_europaea, id_taxon_conservation_nature, cd_nom from biodiversite_taxinomie where id ='" . $idtaxinomie . "' ");
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
		$target = ' target="_new"';
		$urloiseaux="http://www.oiseaux.net/oiseaux/".$nom.".html" ;


		$id_taxon_inpn=$rows[0]["cd_nom"];

		if (isset($id_taxon_inpn))
		{
		$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$id_taxon_inpn."" ;
		$retour.='<a href="' . $urlinpn . '"' . $target . '"><font color="ForestGreen"><b>Inpn</b></font></a>';
		$retour.='<br /> ';
		}

		$nom_binomial=trim($rows[0]["nom_binomial"]);
		$urlwikipedia_en="http://en.wikipedia.org/wiki/".$nom_binomial ;
		$retour.='<a href="' . $urlwikipedia_en . '"' . $target . '"><font color="ForestGreen"><b>Wikipedia_en</b></font></a>';
		$retour.='<br /> ';

		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="SELECT code_iso_639_1 from type_langue tl, app_utilisateur u
		where u.id=$userutilisateur and u.id_langue_application=tl.id";
		$data=$db->getrows($sql);
		$urlwikipedia_loc="http://".$data[0]["code_iso_639_1"].".wikipedia.org/wiki/".$nom_binomial ;
		$retour.='<a href="' . $urlwikipedia_loc . '"' . $target . '"><font color="ForestGreen"><b>Wikipedia_loc</b></font></a>';
		$retour.='<br /> ';


		$urlgoogle="http://www.google.fr/search?q=".$nom_binomial ;
		$retour.='<a href="' . $urlgoogle . '"' . $target . '"><font color="ForestGreen"><b>Google</b></font></a>';
		$retour.='<br /> ';


		$id_taxon_fe=$rows[0]["id_taxon_fauna_europaea"];
		if (isset($id_taxon_fe))
		{ 	$urlfauna_europaea="http://www.faunaeur.org/full_results.php?id=".$id_taxon_fe ;
		$retour.='<a href="' . $urlfauna_europaea . '"' . $target . '"><font color="ForestGreen"><b>Fauna_europaea</b></font></a>';
		$retour.='<br /> ';
		}

		$urltela_botanica="http://www.tela-botanica.org/page:eflore?eflore_nom=".$nom_binomial."&eflore_referentiel=25&eflore_type_nom=nom_scientifique&module=recherche&action=recherche_nom";
		$retour.='<a href="' . $urltela_botanica . '"' . $target . '"><font color="ForestGreen"><b>Tela_botanica</b></font></a>';
		$retour.='<br /> ';
		$id_iucn=$rows[0]["id_taxon_conservation_nature"];
		if (isset($id_taxon_fe))
		{ 	$urlconservation_nature="http://www.iucnredlist.org/details/".$id_iucn ;
		$retour.='<a href="' . $urlconservation_nature . '"' . $target . '"><font color="ForestGreen"><b>Conservation_nature</b></font></a>';
		$retour.='<br /> ';	}
		$retour.='<a href="' . $urloiseaux . '"' . $target . '"><font color="ForestGreen"><b>Oiseaux.net</b></font></a>';
		$retour.='<br /> ';
		$urlxenocanto="http://www.xeno-canto.org/browse.php?query=".$nom_binomial."&pagenumber=&order=taxonomy&view=4";
		$retour.='<a href="' . $urlxenocanto . '"' . $target . '"><font color="ForestGreen"><b>Chants xeno canto</b></font></a>';
		$retour.='<br /> ';
		$retour.=$this->etymology_display($record, $mode) ;
		$retour.='<br /> ';
		$nom_binomial_images=str_replace(' ','+',$nom_binomial);
		$url_images="http://www.google.com/images?hl=fr&gbv=2&tbs=isch:1&sa=3&q=".$nom_binomial_images."&btnG=Recherche+d'images";
		$retour.='<a href="' . $url_images . '"' . $target . '"><font color="ForestGreen"><b>Images google</b></font></a>';
		$retour.='<br /> ';

		if (true === $this->m_newWindow) {
		$target = ' target="_new"';
		}
		return $retour;
		}
		*/
	function photo_display($record, $mode)
	{
		$target = ' target="_blank"';
		$idtaxinomie=trim($record["id_taxinomie"]["id"]);
		$db = & atkGetDb();
		$rows = $db->getrows("select url_image ,nom_binomial
		from biodiversite_taxinomie where id ='" . $idtaxinomie . "' ");
		$url='<center><a href="'.$rows[0]["url_image"]. '"' .$target.'"><img src="'.$rows[0]["url_image"].'" height="130" alt="'.$rows[0]["nom_binomial"].'" title="'.$rows[0]["nom_binomial"].'" /></a></center>' ;

		//		$url.='<center><a href="http://www.xeno-canto.org/browse.php?query='.$rows[0]["nom_binomial"].'&pagenumber=&order=taxonomy&view=4" target="_blank"><font color="ForestGreen"><b>Chants xeno canto</b></font></a></center>';
		;


		return $url ;

	}
	/*
	 * 	function etymology_display($record, $mode)
	 {

		$db = & atkGetDb();
		$rows = $db->getrows("select nom_binomial
		from biodiversite_taxinomie where id ='" . $record["id_taxinomie"]["id"] . "' ");
		$nom=trim($rows[0]["nom_binomial"]);
		$target = '';
		if ($nom!="")
		{			$url="http://dictionary.reference.com/search?q=".$nom;
		$target = ' target="_blank"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Etymology</b></font></a>';
		}
		else
		{
		return "";
		}
		}
		*/

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
	function ascendance_display($record, $mode)
	{
		$ascendance=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_ascendance($record["id_taxinomie"]["id"], $destination='affichage'),50);
		return $ascendance;
	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		$view = $this->getView();
		if ($view == "tout") {
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "a_verifier") {
			$this->addFilter(" a_verifier_o_n='1' ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "verifie") {
			$this->addFilter(" a_verifier_o_n='0' ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		return $handler->action_admin();
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "tout";
		}
		return $view;
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
		$mraactions['a_verifier'] = "a_verifier";
		$mraactions['verifie'] = "verifie";
		$mraactions['biolocalisation'] = "biolocalisation";
		$mraactions['forcer_cdref'] = "forcer_cdref";
		$actions['biolocalisation'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=biolocalisation&atkselector=[pk]", SESSION_NESTED);

	
	}
	function traitement_select_biolocalisation($select )
	{
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$taxons .= $array_id[1] . ',';
		}
		$taxons = substr($taxons, 0, strlen($taxons) - 1);
		$taxons=str_replace("'","",$taxons);

		//	$this->p($taxons);
		return array (
			"taxons" => $taxons,
		"taxons_detail"=> $taxons,
			"zones" => 0,
			"date_observation_debut" => 0,
			"date_observation_fin" => 0,
			"heure_observation_debut" => 0,
			"heure_observation_fin" => 0,
			"organismes_commanditaire" => 0,
			"organismes_observateur" => 0,
			"individus_observateur" => 0,
		);
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

		$taxons_detail = $this->m_postvars["taxons_detail"];
		if ($taxons_detail!=0)
		{
			$selectmaptaxons='select
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
		biodiversite_observation_detail od,
		biodiversite_taxinomie t,
		organisme oc,
		organisme oo,
		individu i
		where
		od.id in ('.$taxons_detail.') 
		and od.id_taxinomie=t.id
		and od.id_observation=o.id
		and o.id_organisme=oc.id
		and o.id_organisme_observateur=oo.id
		and o.id_observateur=i.id
		
		';
//		 $this->p($selectmaptaxons);
			return $this->createMarkers($selectmaptaxons, "taxons");

		}
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
		biodiversite_observation_detail od,
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
		biodiversite_observation_detail od,
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
			$html_liens_web=str_replace('<br />','|',$html_liens_web);

			$html=$ascendance.' ';
//			$html .= $html_liens_web.'<br />';
			$html .= 'Observé par : '.$html_individu_observateur.' pour  '. $html_organisme_observateur;
			$html .= 'Le : '.$date_observation. ' à '.$heure_observation.'<br />';
			$html .= 'Organisme : '. $html_organisme_commanditaire.' ';
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
//			$output .= "<font face=\"arial\" size=\"1\" color=\"red\">";
//			$output .= $missing . " : non géolocalisables";
//			$output .= $missingnoms;
//			$output .= "<br />" . $missingadresse . " : sans adresse";
//			$output .= $missingadressenoms;
//			$output .= "</font></body>";
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

}
?>