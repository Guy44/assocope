<?php
atkimport("atk.assmetanode");
useattrib("development.atgNumberExpressionAttribute");

useattrib("development.atgtextlibelleattribute");
class protection_taxinomie extends assMetaNode {
	var $table = "biodiversite_protection_taxinomie";
	function meta(& $policy) {
		$policy->addFlags("commentaire","id", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function protection_taxinomie() {
		$this->atkMetaNode();
		$this->atkNode("protection_taxinomie",  NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id",
		"descripteur_protection",
		//		"descripteur_statuts",
			
		"descripteur_statuts",
		//		"descripteur_statuts_avifaune",
		"photo",
		"descripteur_inpn",
				"cd_protection",
				"cd_ref",
				"nom_complet_valide",
				"nom_cite",
				"nom_francais_cite",
		"nom_initial_liste",
				"precisions",
				"url_inpn",
		"statut_liste_rouge",
		"criteres_liste_rouge",
		"statut_juridique",
		"statut_biologique",
		"statut_presence_determinant",

		"niveau_priorite",
		"directive_habitats_oiseaux","convention_berne","convention_bonn","convention_washington",
"remarques_dreal", "id_dreal", "categorie_statut","note_faune",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
				"Statuts_avifaune" => array (

			"statut_de_nicheur",			
  "statut_biologique_nicheur_region",
  "statut_biologique_hivernant_region",
  "statut_biologique_migrateur_region",
  "statut_spec" ,
  "statut_conservation_nicheur_france" ,
  "statut_conservation_hivernant_france",
  "statut_conservation_nicheur_region",
  "statut_conservation_hivernant_region",
  "espece_determinante_region",
  "espece_prioritaire_nicheur_region",
  "espece_prioritaire_hivernant_region",
  "espece_prioritaire_migrateur_region",

				"statut_regression",
				"statut_rarete",
				"espece_prioritaire_flore"
				)
				//				,
				//			"Taxinomies" => array (
				//				"taxinomie"
				//			)
				), AF_NO_LABEL));
				$this->add(new atkAttribute("id", AF_HIDE_LIST),100);
				$this->add(new atkDummyAttribute("descripteur_protection",0 , AF_HIDE_EDIT),101);
				//				$this->add(new atkDummyAttribute("descripteur_statuts",0 , AF_HIDE_EDIT),102);
				//				$this->add(new atkDummyAttribute("descripteur_statuts_avifaune",0 , AF_HIDE_EDIT),105);
				$this->add(new atkDummyAttribute("descripteur_statuts",0 , AF_HIDE_EDIT),104);
				$this->add(new atkDummyAttribute("photo",0 , AF_HIDE_EDIT),106);
				$this->add(new atkDummyAttribute("descripteur_inpn",0, AF_HIDE_EDIT ),108);
				$this->add(new atkDummyAttribute("recherche_inpn",0, AF_HIDE_EDIT ),109);
				$this->add(new atkAttribute("cd_protection", AF_SEARCHABLE | AF_HIDE_EDIT),110);
				$this->add(new atkAttribute("cd_ref", AF_SEARCHABLE),120);
				$this->add(new atkAttribute("nom_complet_valide", AF_SEARCHABLE),130);
				$this->add(new atkAttribute("nom_cite", AF_SEARCHABLE),140);
				$this->add(new atkAttribute("nom_francais_cite", AF_SEARCHABLE),150);
				$this->add(new atkAttribute("nom_initial_liste", AF_SEARCHABLE),150);
				$this->add(new atkAttribute("precisions", AF_SEARCHABLE | AF_HIDE_LIST),160);
				$this->add(new atkUrlAttribute("url_inpn", AF_POPUP | AF_SEARCHABLE),170);
				$this->add(new atkAttribute("statut_liste_rouge", AF_SEARCHABLE| AF_HIDE_LIST),180);
				$this->add(new atkAttribute("criteres_liste_rouge", AF_SEARCHABLE| AF_HIDE_LIST),190);
				$this->add(new atkAttribute("statut_presence_determinant", AF_SEARCHABLE| AF_HIDE_LIST),195);
				$this->add(new atkAttribute("niveau_priorite", AF_SEARCHABLE| AF_HIDE_LIST),196);
				$this->add(new atkAttribute("directive_habitats_oiseaux", AF_SEARCHABLE| AF_HIDE_LIST),197);
				$this->add(new atkAttribute("convention_berne", AF_SEARCHABLE| AF_HIDE_LIST),198);
				$this->add(new atkAttribute("convention_bonn", AF_SEARCHABLE| AF_HIDE_LIST),199);
				$this->add(new atkAttribute("convention_washington", AF_SEARCHABLE| AF_HIDE_LIST),200);
				$this->add(new atkTextAttribute("remarques_dreal", array ('rows' => '3'), AF_SEARCHABLE),200);
				$this->add(new atkAttribute("id_dreal", AF_SEARCHABLE| AF_HIDE_LIST),202);
				$this->add(new atkAttribute("categorie_statut", AF_SEARCHABLE),203);
					
				$this->add(new atkAttribute("statut_juridique", AF_SEARCHABLE| AF_HIDE_LIST),191);
				$this->add(new atkAttribute("statut_biologique", AF_SEARCHABLE| AF_HIDE_LIST),192);
				$this->add(new atkAttribute("statut_de_nicheur", AF_SEARCHABLE| AF_HIDE_LIST),214);

				$this->add(new atkAttribute("statut_biologique_nicheur_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_biologique_hivernant_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_biologique_migrateur_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_spec", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_conservation_nicheur_france", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_conservation_hivernant_france", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_conservation_nicheur_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_conservation_hivernant_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("espece_determinante_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("espece_prioritaire_nicheur_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("espece_prioritaire_hivernant_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("espece_prioritaire_migrateur_region", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_regression", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("statut_rarete", AF_SEARCHABLE| AF_HIDE_LIST),215);
				$this->add(new atkAttribute("espece_prioritaire_flore", AF_SEARCHABLE| AF_HIDE_LIST),215);

				$this->add(new atkTextAttribute("note_faune", array ('rows' => '3'), AF_SEARCHABLE),220);

				//				$this->add(new atkOneToManyRelation("taxinomie", "biodiversite.taxinomie", "id_protection_taxinomie", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");


				//				$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from biodiversite_taxinomie
				//	 where id_protection_taxinomie =[table].id 					', 0, 0));
				$this->setOrder("date_modification desc");
				$this->setSecurityAlias("organisme.organisme");
				$this->m_securityMap["recuperation_inpn"] = "view";
				$this->m_securityMap["normalisation_pdl"] = "view";
				$this->m_securityMap["affichage_pdl"] = "view";
				$this->m_securityMap["recuperation_noms_francais"] = "view";

				$this->m_securityMap["recherche_nom_binomial_inpn"] = "view";
	}
	function descriptor_def() {
		return "[cd_protection] [cd_ref]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		return $handler->action_admin();
	}
	function recherche_inpn_display($record, $mode)

	{
		$target='target="_blank"';
		$nomcomplet=$record["nom_complet_valide"];
		$pos1=strpos($nomcomplet, ' ');
		$nompartiel=substr($nomcomplet,0,$pos1 );
		$pos2=strpos($nomcomplet, ' ',$pos1+1);
		$nompartiel.=substr($nomcomplet,$pos1, $pos2-$pos1).'%';
		$urlinpncourt="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=12&pageReturn=listEspece.jsp&taxon=".$record["nom_cite"] ;
		//	$urlinpnnompartiel="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=12&pageReturn=listEspece.jsp&taxon=".$nompartiel ;

		$urlinpnnompartiel=dispatch_url("biodiversite.taxinomie", "admin", array (
			"atkfilter" => "biodiversite_taxinomie.nom_binomial LIKE '" . $nompartiel . "'"
			));
				
				
			$urlinpncomplet="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=12&pageReturn=listEspece.jsp&taxon=".$record["nom_complet_valide"] ;
			$retourinpn.='<a href="' . $urlinpncourt . '"' . $target . '"><font color="ForestGreen"><b>Nom binomial</b></font></a>';
			$retourinpn.='<br /><a href="' . $urlinpncomplet . '"' . $target . '"><font color="ForestGreen"><b>Nom complet</b></font></a>';
			$retourinpn.='<br /><a href="' . $urlinpnnompartiel . '"' . $target . '"><font color="ForestGreen"><b>Nom partiel</b></font></a>';
			return $this->decoupe_affichage_colonne($retourinpn, 20);
	}

	function recordActions($rec, & $actions, & $mraactions) {

		$mraactions['delete'] = "delete";


	}
	/*
	 function descripteur_statuts_display($record, $mode)
	 {
	 $cd_ref=trim($record["cd_ref"]);
	 $cd_protection=trim($record["cd_protection"]);
		$retour=$this->descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $cd_protection);
		return $retour;
		}

		function descripteur_statuts_avifaune_display($record, $mode)
		{
		if ($record["categorie_statut"]=='avifaune_prioritaire_pdl')
		{$cd_ref=trim($record["cd_ref"]);
		$cd_protection=trim($record["cd_protection"]);
		$retour=$this->descripteur_biodiversite_protection_taxinomie_statuts_avifaune($cd_ref, $cd_protection);
		}
		else
		{ $retour='';}
		return $retour;
		}
		*/
	function descripteur_statuts_display($record, $mode)
	{
		$cd_ref=trim($record["cd_ref"]);
		$cd_protection=trim($record["cd_protection"]);
		//$retour=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $cd_protection),50);
		$retour=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $cd_protection),40);
		return $retour;
	}

	function photo_display($record, $mode)
	{
		$target = ' target="_blank"';
		$cd_ref=trim($record["cd_ref"]);
		$db = & atkGetDb();
		$rows = $db->getrows("select url_image ,nom_binomial
		from biodiversite_taxinomie where cd_ref ='" . $cd_ref . "' ");
		$url='<center><a href="'.$rows[0]["url_image"]. '"' .$target.'"><img src="'.$rows[0]["url_image"].'" height="130" alt="'.$rows[0]["nom_binomial"].'" title="'.$rows[0]["nom_binomial"].'" /></a></center>' ;

		//		$url.='<center><a href="http://www.xeno-canto.org/browse.php?query='.$rows[0]["nom_binomial"].'&pagenumber=&order=taxonomy&view=4" target="_blank"><font color="ForestGreen"><b>Chants xeno canto</b></font></a></center>';
		;


		return $url ;

	}


	function descripteur_inpn_display($record, $mode)
	{
		$db = & atkGetDb();
		$sql="SELECT id
		FROM biodiversite_taxinomie
		where cd_nom=".$record["cd_ref"];
		$data = $db->getrows($sql);
		$idtaxinomie=$data[0]["id"];

		return $this->descripteur_biodiversite_taxons_inpn($idtaxinomie,"taxinomie");
	}
	function descripteur_protection_display($record, $mode)
	{

		$retour=$this->descripteur_biodiversite_protection_texte($record["cd_protection"]);
		return $retour;
	}



	function cd_ref_display($record, $mode) {
		$ret=href(dispatch_url("biodiversite.taxinomie", "admin", array (
				'atkfilter' => "biodiversite_taxinomie.cd_ref='" . $record['cd_ref'] . "'"
				,'view' => "requete"
				), "dispatch.php"), $record["cd_ref"], SESSION_NESTED);
				return $ret;
	}

	function nom_cite_display($record, $mode) {
		$ret=href(dispatch_url("biodiversite.taxinomie", "edit", array (
				'atkfilter' => "biodiversite_taxinomie.nom_binomial='" . $record['nom_cite'] . "'"
				,'view' => "requete"
				), "dispatch.php"), $record["nom_cite"], SESSION_NESTED);
				return $ret;
	}
	function cd_protection_display($record, $mode) {
		$ret=href(dispatch_url("biodiversite.protection", "edit", array (
				'atkfilter' => "biodiversite_protection.cd_protection='" . $record['cd_protection'] . "'"
				), "dispatch.php"), $record["cd_protection"], SESSION_NESTED);
				return $ret;
	}
	function rowColor($record)
	{
		$db = &atkGetDb();
		$data = $db->getrows(
	"SELECT count(cd_nom) as nombre
	 	from biodiversite_taxinomie
	 where cd_ref=" . $record['cd_ref'] ."") ;

		if ($data[0]["nombre"]==0) {
			return "Orange";
		} else {
			return '';
		}
	}
	function adminFooter() {
		$retour=parent::adminFooter();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="'.$this->couleurmois.'"> <b> Espèce non répertoriée dans la table (taxinomie taxons) </b></font><br>';
		$retour= '</b>'.$legende .$retour.'<b>';

		$retour_especes_non_repertoriees=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkfilter=' . '&atkaction=' . $this->m_action , 'Espèces non répertoriées dans la table des taxons')  ;
		//			$retour_normalisation=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=traduction' , 'Normalisation')  ;
		//		$retour_recuperation_inpn=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=recuperation_inpn' , 'Recupération no inpn');
		//	$retour_recuperation_noms_francais=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=recuperation_noms_francais' , 'Recupération des noms français') ;
		$retour_recherche_nom_binomial_inpn	=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=recherche_nom_binomial_inpn	' , 'recherche_nom_binomial_inpn	') ;



		//		$retour_normalisation_pdl=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=normalisation_pdl' , 'Normalisation pdl')  ;
		// //$retour_affichage_pdl=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=affichage_pdl' , 'Affichage pdl')  ;

		$retour.= $retour_especes_non_repertoriees.'('.')'.'<br />';
		//		$retour.= $retour_normalisation.'('.')'.'<br />';
		//		$retour.= $retour_recuperation_inpn.'('.')'.'<br />';
		// $retour.= $retour_recuperation_noms_francais.'('.')'.'<br />';
		$retour.= $retour_recherche_nom_binomial_inpn.'('.')'.'<br />';

		//		$retour.= $retour_normalisation_pdl.'('.')'.'<br />';
		// $retour.= $retour_affichage_pdl.'('.')'.'<br />';

		return $retour;
			
	}
	function adminHeader() {

		return $this->adminFooter();
	}
	/*
	 function action_traduction ($handler)
	 {
		$db = &atkGetDb();
		$data = $db->getrows(
		"SELECT id, nom_complet_valide
		from biodiversite_protection_taxinomie
	 where  cd_protection LIKE  'LR_%' ") ;

	 if (count($data) > 0)

	 { $j=0;

	 for ($i=0; $i<count($data); $i++)
	 {
	  
	 $id =$data[$i]["id"];
	 $nom_complet_valide =$data[$i]["nom_complet_valide"];

	 $token = strtok($data[$i]["nom_complet_valide"], " ");
	 $pos=stripos($token,".");
	 if ($pos>0)
	 {
	 $nom_complet_valide=substr($nom_complet_valide,$pos+1);
	 $nom_cite=escapeSQL($nom_cite);
	 $sql="update biodiversite_protection_taxinomie
	 set nom_complet_valide='".$nom_complet_valide."'
	 where id=$id";
	 $db->query($sql);
	 $j++;
	 }

	 }
	 echo $j.' enreg normalisés';
	 die();

	 }

	 }
	 */

	function action_recuperation_noms_francais ($handler)
	{
		$db = &atkGetDb();
		$data = $db->getrows(
		"SELECT distinct t.id, t.nom_binomial, t.nom_francais, pt.nom_francais_cite, pt.nom_complet_valide
		from biodiversite_protection_taxinomie pt, biodiversite_taxinomie t
	 where   pt.nom_complet_valide=t.nom_binomial and t.nom_francais is null") ;


		if (count($data) > 0)
	 {
	 	$j=0;
	 	$k=0;
	 	for ($i=0; $i<count($data); $i++)
	 	{
	 		$nom_complet_valide =$data[$i]["nom_complet_valide"];
	 		$nom_complet_valide =trim($nom_complet_valide);
	 		$nom_complet_valide =strtolower($nom_complet_valide);
	 		$nom_complet_valide =ucfirst($nom_complet_valide);

	 		$nom_francais_cite =$data[$i]["nom_francais_cite"];
	 		$nom_francais_cite =trim($nom_francais_cite);
	 		$nom_francais_cite =strtolower($nom_francais_cite);
	 		$nom_francais_cite =ucfirst($nom_francais_cite);

	 		$sql="select id, nom_francais
	 from biodiversite_taxinomie
	 where lcase(nom_binomial)='".strtolower($nom_complet_valide)."' ";

	 		$data1 = $db->getrows($sql);
	 		if (count($data1) >0 && $nom_francais_cite!=''  )
	 		{
	 			$id_taxinomie=$data1[0]["id"];
	 			$j++;
	 			$nom_francais_cite=escapeSQL($nom_francais_cite);
	 			$sql="update biodiversite_taxinomie
	 set nom_francais='".$nom_francais_cite."' 
	 where id=$id_taxinomie";
	 			$this->p($sql);
	 			$db->query($sql);
	 		}
	 		else
	 		{$k++;}

	 	}
	 }
	 echo $j.' mis à jour <br />'.$k.' non mis à jour ';
	 die();


	  
	}
	function createSearchFilterOr ($searchfields,$searchvalue,$searchtable)
	{
		$parts = preg_split('/\s+/', $searchvalue);
		$mainFilter = array();
		$n=0;
		foreach ($parts as $part)
		{
			$filter = array();
			foreach($searchfields as $attribname)
			{
				$tmp = "LOWER(".$searchtable.'.'.$attribname.")";
				if ($n==0)
				{$tmp.= " LIKE LOWER('{$part}%')";}
				else
				{$tmp.= " LIKE LOWER('% {$part}%')";}
				$filter[] = $tmp;
			}
			if (count($filter) > 0)
			$mainFilter[] = "(".implode(") AND (", $filter).")";
			$n++;
			if ($n==2)
			break;
		}
		if (count($mainFilter) > 0)
		{
			$mainFilter= "(".implode(") OR (", $mainFilter).")";
			return $mainFilter;
		}
		else return "";
	}


	function action_recherche_nom_binomial_inpn ($handler)
	{
		$db = &atkGetDb();
		$sql="SELECT cd_ref, nom_complet_valide
FROM biodiversite_protection_taxinomie WHERE cd_protection='IBE3' and NOT EXISTS ( SELECT cd_ref FROM biodiversite_taxinomie 
WHERE biodiversite_protection_taxinomie.cd_ref = biodiversite_taxinomie.cd_nom )";
		$data=$db->getrows($sql);
		$nombre=count(	$data);
		$tableau=array();
		$tbl = & atknew("atk.utils.atktablerenderer");
		$tbl->setRowClass(1, "superbold");
		$row=array();
		$row[]="#";
		$row[]="##";
		$row[]="Nom binomial";
		$row[]="Auteur";
		$row[]="Nom protection";
		$row[]="Id_INPN";
		$row[]="cd_ref protection";
		$sortie= '<table>';
		$tableau[] = $row;

		for ($i=0; $i<count($data); $i++)
		{
			$nom_complet_valide=$data[$i]["nom_complet_valide"];
			$searchstring=$this->createSearchFilterOr(array('nom_binomial'), $nom_complet_valide,'biodiversite_taxinomie');
			// 		$this->p($searchstring);
			$sql1="SELECT id, nom_binomial, cd_nom , auteur from biodiversite_taxinomie where $searchstring";
			//	 		$sql1="SELECT count(id) as nombre from biodiversite_taxinomie where $searchstring";
			//	 		$this->p($sql1);
			$data1 = $db->getrows($sql1);
			//	 				$nombre1=	$data1[0]["nombre"];


			if (count($data1)>0)
			{ 		for ($k=0; $k<count($data1); $k++)
	 	{
	 		$row=array();
				$row[]=$i+1;
				$row[]=$k+1;
				$row[]=$data1[$k]["nom_binomial"];
				$row[]=$data1[$k]["auteur"];
				$row[]=$data[$i]["nom_complet_valide"];
				$row[]=$data1[$k]["cd_nom"];
				$row[]=$data[$i]["cd_ref"];

				$tableau[] = $row;

	 	}}

	 	else
	 	{$row[]=$i+1;
	 	$row[]=$k+1;
	 	$row[]=' ';
	 	$row[]=' ';
	 	$row[]=$data1[$i]["nom_complet_valide"];
	 	$row[]=' ';
	 	$row[]=$data1[$k]["cd_ref"];

	 	$tableau[] = $row;

	 	}
	 		
	 	 

	 	//	$sortie.= '<tr><td>'.$data[$i]["nom_complet_valide"].'</td><td><b>'.$nombre1.'</b></td></tr>';

		}
	 //			 				$this->p($tableau);
		 


		$res = $tableau;
		$res .= $tbl->render($tableau, 0, "recordlist");
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);
			

		/*	$sortie.= '</table>';
		 echo $sortie;
		 die();
		 */
	}

	function action_recuperation_inpn ($handler)
	{
		$db = &atkGetDb();
		$data = $db->getrows(
		"SELECT id, nom_complet_valide, nom_cite
		from biodiversite_protection_taxinomie
	 where  cd_protection='LR_REGION_PDL_FAUNE' and cd_ref='' ") ;
		if (count($data) > 0)
	 {
	 	$j=0;
	 	$k=0;
	 	for ($i=0; $i<count($data); $i++)
	 	{
	 		$id =$data[$i]["id"];

	 		$nom_complet_valide =$data[$i]["nom_complet_valide"];
	 		$nom_complet_valide =trim($nom_complet_valide);
	 		$nom_complet_valide =strtolower($nom_complet_valide);
	 		$nom_complet_valide =ucfirst($nom_complet_valide);

	 		$sql="select cd_nom
	 from biodiversite_taxinomie
	 where lcase(nom_binomial)='".strtolower($nom_complet_valide)."' ";

	 		$data1 = $db->getrows($sql);
	 		if (count($data1) >0)
	 		{
	 			$cd_ref=$data1[0]["cd_nom"];
	 			$j++;
	 			$sql="update biodiversite_protection_taxinomie
	 set cd_ref='".$cd_ref."', nom_complet_valide='".$nom_complet_valide."'
	 ,nom_cite='".$nom_complet_valide."'
	 where id=$id";
	 			$db->query($sql);
	 		}
	 		else
	 		{$k++;}

	 	}
	 }
	 echo $j.' mis à jour <br />'.$k.' non mis à jour ';
	 die();


	  
	}

	function action_normalisation_pdl ($handler)
	{
		$db = &atkGetDb();
		$data = $db->getrows(
		"SELECT id, nom_complet_valide
		from biodiversite_protection_taxinomie
	 where  cd_protection LIKE  'LR_REGION_PAYSDELOIRE%' and cd_ref='' ") ;
		if (count($data) > 0)
	 {
	 	$j=0;

	 	for ($i=0; $i<count($data); $i++)
	 	{
	 		$id =$data[$i]["id"];
	 		$nom_complet_valide =$data[$i]["nom_complet_valide"];
	 		$nom_complet_valide =trim($nom_complet_valide);
	 		$nom_complet_valide =strtolower($nom_complet_valide);
	 		$nom_complet_valide =ucfirst($nom_complet_valide);
	 		$pos=strpos($nom_complet_valide,' -');
	 		if ($pos>0)
	 		{
	 			$nom_complet_valide =substr($nom_complet_valide,0,$pos);
	 			$sql="update biodiversite_protection_taxinomie
	 set nom_complet_valide='".$nom_complet_valide."'
	 where id=$id";
	 			$db->query($sql);
	 			$j++;
	 		}


	 	}
	 }
	 echo $j.' mis à jour <br />';
	 die();


	  
	}
	function action_affichage_pdl ($handler)
	{
		$db = &atkGetDb();
		$data = $db->getrows(
		"SELECT id,cd_ref, nom_complet_valide
		from biodiversite_protection_taxinomie
	 where  cd_protection LIKE  'LR_REGION_PDL%'  order by 3 ") ;

		if (count($data) > 0)
	 {
	 	$j=0;
	 	$affichage='';

	 	for ($i=0; $i<count($data); $i++)
	 	{
	 		$id =$data[$i]["id"];
	 		$cd_ref=$data[$i]["cd_ref"];
	 		$nom_complet_valide =$data[$i]["nom_complet_valide"];
	 		$affichage.= $cd_ref.'<br />';
	 		$j++;
	 	}


	 }
	 echo $affichage;
	 echo $j.' affichés<br />';
	 die();


	  
	}


}
?>