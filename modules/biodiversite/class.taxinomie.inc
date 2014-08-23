<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnomsvernaculairesattribute");
useattrib("development.atgnumberexpressionattribute");

class taxinomie extends assMetaNode {
	var $table = "biodiversite_taxinomie";
	function meta(& $policy) {

		$policy->addFlags("commentaire","id_statut_france_metropole",
			"id_statut_martinique",
			"id_statut_guadeloupe",
			"id_statut_st_martin_st_barthelemy",
			"id_statut_guyane_francaise",
			"id_statut_st_pierre_et_miquelon",
			"id_statut_reunion",
			"id_statut_mayotte",
			"id_statut_terres_australes_et_antartiques_francaises",
		"id_statut_iles_eparses",
		"id_statut_polynesie_francaise",
		"id_statut_nouvelle_caledonie",
		"id_statut_wallis_et_futuna",
		"id_statut_clipperton",
		"nom_anglais",
		"id_rang_taxinomique",
		"auteur",
		"auteur_an",
		"cd_nom" ,
		"cd_ref",
		"cd_taxsup",
		"lb_nom",
		"id_rang_taxinomique",
		"id",
		"id_parent",
		"id_taxon_fauna_europaea",
			"id_taxon_conservation_nature",
			"id_taxon_marine_species",
			"id_taxon_kerguelen",
			"id_bock_kerguelen","etymologie",
		AF_HIDE_LIST);
	}
	function taxinomie() {
		$this->atkMetaNode();
		$this->atkNode("taxinomie", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA | NF_COMPACT );
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id",
				"id_parent",
				"descripteur_taxinomie",
				"url_image",
				"web_info",
		"descripteur_inpn",
		"statuts_inpn",
 
 				"nom_binomial",
 				"nom_francais",
 				"nom_anglais",
		"cd_nom",
		"cd_ref",
 			"ascendance",
		//		"fratrie",
//				"descendance",
 			"id_rang_taxinomique",
 				"auteur",
 			"auteur_an",
"referentiels",
				"etymologie",
	 			"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
				"Inpn"=> array (
				"id_habitat",
				"inpn_nom_complet",
				"inpn_lb_nom",
				"inpn_lb_auteur",
				"inpn_rang",
				"inpn_version",
				"cd_nom",
				"cd_ref",
				"cd_taxsup"
				
				),
				"Statuts_inpn"=> array (
			"id_statut_france_metropole",
			"id_statut_martinique",
			"id_statut_guadeloupe",
			"id_statut_st_martin_st_barthelemy",
			"id_statut_guyane_francaise",
			"id_statut_st_pierre_et_miquelon",
			"id_statut_reunion",
			"id_statut_mayotte",
			"id_statut_terres_australes_et_antartiques_francaises",
		"id_statut_iles_eparses",
		"id_statut_polynesie_francaise",
		"id_statut_nouvelle_caledonie",
		"id_statut_wallis_et_futuna",
		"id_statut_clipperton"
			),
				"Referentiels"=> array (
			"id_taxon_fauna_europaea",
			"id_taxon_conservation_nature",
			"id_taxon_marine_species",
			"id_taxon_kerguelen",
			"id_bock_kerguelen"
			)
			), AF_NO_LABEL));
			$this->add(new atkAttribute("id",AF_HIDE_LIST | AF_FORCE_LOAD ),610);
			$this->add(new atkManyToOneRelation("id_rang_taxinomique", "biodiversite.rang_taxinomique", AF_HIDE_LIST | AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK|AF_FORCE_LOAD), 131);
			$this->add(new atkDummyAttribute("descripteur_taxinomie",0,AF_HIDE_EDIT | AF_COMPACT ),115);
 			$this->add(new atgNumberExpressionAttribute("ascendance", ' 1', 0,AF_HIDE_EDIT | AF_COMPACT),116);
//			$this->add(new atgNumberExpressionAttribute("descendance", ' select count(id) from biodiversite_taxinomie
//	 where id_parent =[table].id 					', 0, 0),132);
			$this->add(new atgTextLibelleAttribute("inpn_nom_complet", AF_SEARCHABLE | AF_OBLIGATORY| AF_COMPACT),130);
			$this->add(new atgTextLibelleAttribute("nom_binomial", AF_SEARCHABLE | AF_OBLIGATORY|AF_FORCE_LOAD),159);
			$this->add(new atgnomsvernaculairesattribute("nom_francais", AF_SEARCHABLE|AF_FORCE_LOAD),160);
			$this->add(new atgnomsvernaculairesattribute("nom_anglais", AF_HIDE_LIST | AF_SEARCHABLE|AF_FORCE_LOAD),170);
			$this->add(new atkManyToOneRelation("id_parent", "biodiversite.taxinomie", AF_HIDE_LIST | AF_SEARCHABLE | AF_OBLIGATORY| AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),810);
			$this->add(new atgTextLibelleAttribute("auteur", AF_HIDE_LIST | AF_SEARCHABLE|AF_FORCE_LOAD),600);
			$this->add(new atkAttribute("auteur_an", AF_HIDE_LIST | AF_SEARCHABLE|AF_FORCE_LOAD),610);
			$this->add(new atkUrlAttribute("url_image", AF_POPUP | AF_SEARCHABLE| AF_COMPACT), 122);
			$this->add(new atkDummyAttribute("web_info",0,AF_HIDE_EDIT | AF_COMPACT ),123);
			$this->add(new atkDummyAttribute("descripteur_inpn",0,AF_HIDE_EDIT | AF_COMPACT),124);
			$this->add(new atkDummyAttribute("statuts_inpn",0 ,AF_HIDE_EDIT| AF_COMPACT),125);
			$this->add(new atkDummyAttribute("referentiels",0,AF_HIDE_EDIT| AF_COMPACT ),126);
			
//			$this->add(new atkAttribute("cd_nom", AF_SEARCHABLE),611);
//			$a = & $this->add(new atkOneToManyRelation("descendants", "biodiversite.taxinomie", "id_parent", AF_HIDE_LIST | AF_CASCADE_DELETE), NULL, 1210);
//			$a->setLabel("Sous rang");
			$this->add(new atkAttribute("id_statut_france_metropole", AF_HIDE_LIST ),810);
			$this->add(new atkAttribute("id_statut_martinique", AF_HIDE_LIST   ),820);
			$this->add(new atkAttribute("id_statut_guadeloupe",  AF_HIDE_LIST   ),830);
			$this->add(new atkAttribute("id_statut_st_martin_st_barthelemy",AF_HIDE_LIST ),840);
			$this->add(new atkAttribute("id_statut_guyane_francaise",  AF_HIDE_LIST  ),850);
			$this->add(new atkAttribute("id_statut_st_pierre_et_miquelon",  AF_HIDE_LIST  ),860);
			$this->add(new atkAttribute("id_statut_reunion",  AF_HIDE_LIST  ),870);
			$this->add(new atkAttribute("id_statut_mayotte",  AF_HIDE_LIST ),880);
			$this->add(new atkAttribute("id_statut_terres_australes_et_antartiques_francaises",  AF_HIDE_LIST ),890);
			$this->add(new atkAttribute("id_statut_iles_eparses",  AF_HIDE_LIST ),890);
			$this->add(new atkAttribute("id_statut_polynesie_francaise",  AF_HIDE_LIST ),890);
			$this->add(new atkAttribute("id_statut_nouvelle_caledonie",  AF_HIDE_LIST  ),890);
			$this->add(new atkAttribute("id_statut_wallis_et_futuna", AF_HIDE_LIST  ),890);
			$this->add(new atkAttribute("id_statut_clipperton",  AF_HIDE_LIST ),890);

			$this->add(new atkAttribute("id_habitat", AF_HIDE_LIST | AF_SEARCHABLE),700);	
			$this->add(new atkAttribute("inpn_nom_complet", AF_HIDE_LIST | AF_SEARCHABLE),710);	
			$this->add(new atkAttribute("inpn_lb_nom", AF_HIDE_LIST | AF_SEARCHABLE),720);	
			$this->add(new atkAttribute("inpn_lb_auteur", AF_HIDE_LIST | AF_SEARCHABLE),730);	
			$this->add(new atkAttribute("inpn_rang", AF_HIDE_LIST | AF_SEARCHABLE),740);	
			$this->add(new atkAttribute("inpn_version", AF_HIDE_LIST | AF_SEARCHABLE),750);	
			$this->add(new atkAttribute("cd_nom", AF_HIDE_LIST | AF_SEARCHABLE),760);	
			$this->add(new atkAttribute("cd_ref", AF_HIDE_LIST | AF_SEARCHABLE),770);	
			$this->add(new atkAttribute("cd_taxsup", AF_HIDE_LIST | AF_SEARCHABLE),780);	
			
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL| AF_COMPACT),null,131 );
			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["autocomplete"] = "view";
			$this->m_securityMap["maj"] = "view";
			$this->m_securityMap["biolocalisation"] = "view";
			$this->m_securityMap["mise_a_jour_inpn"] = "view";
			$this->m_securityMap["normalisation"] = "view";
			$this->m_dropdown_width="120";

			//		$this->setOrder("nombre_observations desc");
	}
	function cd_ref_display ($record, $mode)
	{
					$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$record["cd_ref"]."" ;
			return '<b><a href="' . $urlinpn .' " target="_blank" >'.$record["cd_ref"].'</a>';
	}
	function cd_nom_display ($record, $mode)
	{
					$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$record["cd_nom"]."" ;
			return '<b><a href="' . $urlinpn .' " target="_blank" >'.$record["cd_nom"].'</a>';
	}
	function cd_taxsup_display ($record, $mode)
	{
					$urlinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$record["cd_taxsup"]."" ;
			return '<b><a href="' . $urlinpn .' " target="_blank" >'.$record["cd_taxsup"].'</a>';
	}
	function id_habitat_display ($record, $mode)
	{
					$db = & atkGetDb();
					$sql="select habitat from biodiversite_habitat_taxinomie where code_habitat=".$record["id_habitat"];
					$data=$db->getrows($sql);
					return $data[0]["habitat"];
	}
		function action_normalisation() {
			$db = & atkGetDb("association");
			$dbinsert = & atkGetDb();
			$data = $db->query("SELECT id, nom_francais  from biodiversite_taxinomie where nom_francais!=''" );
			if ($db->affected_rows($sql)==0)
			 {
				return true;
			} else {
				while ($db->next_record()) {
					$record = $db->m_record;
					$nom_francais=$record["nom_francais"];
					$nom_francais=$this->normalisation_nom_vernaculaire($nom_francais);
					$nom_francais = escapeSQL($nom_francais);
					$nom_anglais=$record["nom_anglais"];
					$nom_anglais=$this->normalisation_nom_vernaculaire($nom_anglais);
					$nom_anglais = escapeSQL($nom_anglais);
					$id=$record['id'];
					if ($nom_francais!=$record["nom_francais"] || $nom_anglais!=$record["nom_anglais"] )
					{
					$dbinsert->query("UPDATE biodiversite_taxinomie  set nom_francais='$nom_francais', 
					 nom_anglais='$nom_anglais' where id=$id");

					$k++;
					}
				}
			}
			echo "<br> $k nom_francais ont été normalisés .";
			die();
		}
/*
 * 
		function normalisation_nom_vernaculaire($nom="")
		{
						if (substr($nom,0,1)=="'") $nom=substr($nom,1);
					$nom =normalisation_libelle($nom);
					$nom =str_replace(',',';',$nom);
					while (stripos($nom,'  ',0))
					{$nom=str_replace('  ',' ',$nom);}
					$nom=str_replace(' ;',';',$nom);
					$nom=str_replace('; ',';',$nom);
					$nom=str_replace(';',' | ',$nom);
					$nom=trim($nom);
					$pos=0;
					$nom_transforme='';
					while (true)
					{
						$pos=stripos($nom,'|',0);
									
						if ($pos==false) 
						{
							
							$nom=$this->suppression_article_debut_nom($nom)	;	
							$nom=ucfirst($nom);		
							$nom_transforme=$nom_transforme.$nom;
							
	//						echo $nom_transforme;die();
							break;
						}
						$nom_extrait=substr($nom,0,$pos+2);
						$nom_extrait=$this->suppression_article_debut_nom($nom_extrait)	;
						$nom_extrait=ucfirst($nom_extrait);
										
						$nom_transforme=$nom_transforme.$nom_extrait;
						$nom=substr($nom,$pos+2);
					
					}
					return $nom_transforme;
					
		}
function suppression_article_debut_nom($nom="")
		{
								if (substr($nom,0,2)=="L'") $nom=substr($nom,2);
						if (substr($nom,0,3)=="Le ") $nom=substr($nom,3);
						if (substr($nom,0,3)=="La ") $nom=substr($nom,3);
						 return ucfirst($nom);		
		}
 */		
	function action_mise_a_jour_inpn (& $handler)
	{
		global $g_sessionManager;
		$db = & atkGetDb();
		$sql="SELECT MAX(NUM_VERSION_FINAL) as version, MIN(NUM_VERSION_INIT) as version_init FROM `biodiversite_inpn_changes` ";
		$data = $db->getrows($sql);
		$version_inpn=$data[0]["version"] ;
		$version_inpn_precedente=$data[0]["version_init"] ;
		$Administrateur_o_n=$g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$user = getUser();
		$idutilisateur= $user["id"];

		if ($Administrateur_o_n=='0')
		{
			echo 'Il vous faut le privilège administrateur général pour exécuter cette action.';
			die();
		}

		$ordre_mise_a_jour=0;
		$nombreupdate=0;
		$nombreinsert=0;
		$sql="SELECT  count(id) as nombre_final FROM biodiversite_taxinomie where inpn_version='$version_inpn'";
		$data = $db->getrows($sql);
		$nombre_final=$data[0]["nombre_final"];
		$sql="SELECT  count(id) as nombre_init FROM biodiversite_taxinomie where inpn_version='$version_inpn_precedente'";
		$data = $db->getrows($sql);
		$nombre_init=$data[0]["nombre_init"];
		$sql="SELECT  count(CD_NOM) as nombre_init_inpn FROM biodiversite_inpn_taxinomie where ordre_mise_a_jour='0'";
		$data = $db->getrows($sql);
		$nombre_init_inpn=$data[0]["nombre_init_inpn"];
		$sql="SELECT  count(CD_NOM) as nombre_total_inpn FROM biodiversite_inpn_taxinomie ";
		$data = $db->getrows($sql);
		$nombre_total_inpn=$data[0]["nombre_total_inpn"];
		echo "Mise à jour de biodiversite_taxinomie à partir de biodiversite_inpn_taxinomie ( $nombre_init_inpn / $nombre_total_inpn )  : <br />
		- de la version $version_inpn_precedente à la version $version_inpn<br />
		- biodiversite_taxinomie contient $nombre_init taxons en version $version_inpn_precedente<br />
		- biodiversite_taxinomie contient $nombre_final taxons en version $version_inpn<br />";
		
		$sql="SELECT CD_NOM FROM `biodiversite_inpn_changes` WHERE `TYPE_CHANGE`='RETRAIT'";
		$retraits='';
		$nombre='0';
		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++)
		{
			$retraits.=$data[$i]["CD_NOM"].",";
		}
		$retraits=substr($retraits,0,strlen($retraits)-1);
		$sql="SELECT count(id) as nombre FROM biodiversite_taxinomie WHERE cd_nom in (".$retraits.")";
		//	echo $sql;
		//	die();

		$data1 = $db->getrows($sql);
		$nombre=$data1[0]["nombre"];
		for ($i = 0; $i < count($data); $i++)
		{
			$cdnom=$data[$i]['CD_NOM'];
			$sql="DELETE FROM biodiversite_taxinomie WHERE cd_nom =$cdnom ";
			$db->query($sql);
		}
		$sql="SELECT count(id) as nombrefin FROM biodiversite_taxinomie WHERE cd_nom in (".$retraits.")";

		$data1 = $db->getrows($sql);
		$nombrefin=$data1[0]["nombrefin"];
		$nombresupprimes=$nombre-$nombrefin;
		echo 'Suppression terminée : <br />
	Il y avait ' .$nombre. ' taxons à supprimer dans biodiversité_taxinomie.<br />
	'.$nombresupprimes. ' taxons ont été supprimés dans biodiversité_taxinomie.<br />
	'.$nombrefin. ' taxons n\'ont pu être supprimés dans biodiversité_taxinomie.<br />';
		//	die();

		// Get statuts
		$sql='SELECT id, code_statut from biodiversite_statut_taxinomique';
		$statut= $db->getrows($sql);
		for ($i = 0; $i < count($statut); $i++)
		{	$tableau_statuts[$statut[$i]["code_statut"]]=$statut[$i]["id"];
		}

		//get habitat
		$sql='SELECT id, code_habitat from biodiversite_habitat_taxinomie';
		$habitat= $db->getrows($sql);
		for ($i = 0; $i < count($habitat); $i++)
		{$tableau_habitats[$habitat[$i]["code_habitat"]]=$habitat[$i]["id"];
		}

		$sql="SELECT MAX(ordre_mise_a_jour) as nombre  FROM biodiversite_inpn_taxinomie";
		$dataordre= $db->getrows($sql);
		$ordre_mise_a_jour=$dataordre[0]["nombre"];

		// Traiter Rang par rang dans l'ordre hiérarchique

		$sql="SELECT distinct it.RANG as rang, rt.id as id   FROM biodiversite_inpn_taxinomie it, biodiversite_rang_taxinomique rt
	 WHERE it.RANG=rt.rang_inpn order by rt.id_ordre";
		$rang = $db->getrows($sql);
		
		for ($i = 0; $i < count($rang); $i++)
		{
			$sql="SELECT CD_NOM from biodiversite_inpn_taxinomie
	WHERE RANG ='".$rang[$i]["rang"]."' and ordre_mise_a_jour='0'";
		$db2 = &atkGetDb('association');
$db2->query($sql);
		if ($db2->affected_rows($sql)==0)
		{
			continue;
		}
//		echo $db2->affected_rows($sql);
//		die();
		
			
			while ($db2->next_record())
  {
  
		 $record = $db2->m_record;
				$sql2="SELECT
		CD_NOM, 	 	 
		CD_TAXSUP,
		CD_REF,
		RANG,
		LB_NOM,
		LB_AUTEUR, 	 	 
		NOM_COMPLET, 	 	 
		NOM_VERN, 	 	 
		NOM_VERN_EN, 	 	 
		HABITAT, 	 	 
		FR, 	 	 
		GF, 	 	 
		MAR, 	 
		GUA,	 	 
		SMSB, 	 
		SPM,	 	 
		MAY, 	 
		EPA,	 	 
		REU,	 	 
		TAAF,
		PF,	 	 
		NC,	 	 
		WF,	 	 
		CLI 
		FROM biodiversite_inpn_taxinomie 
		WHERE cd_nom='".$record["CD_NOM"]."' ";
				$data2 = $db->getrows($sql2);
  					$sql1="SELECT id, nom_francais
		 			FROM biodiversite_taxinomie 
		 			WHERE cd_nom='".$data2[0]["CD_NOM"]."' and  inpn_version='".$version_inpn_precedente."'";
				$data1 = $db->getrows($sql1);
				if ($data2[0]["CD_TAXSUP"]>'0')
				{	$sql3="SELECT
		t.id as id_taxinomie_sup
		FROM biodiversite_taxinomie t
		WHERE t.cd_nom='".$data2[0]["CD_TAXSUP"]."'";
				$data3= $db->getrows($sql3);
				if (empty($data3))
				{//echo 'Le taxon inpn '.$data2[0]["CD_TAXSUP"].' parent du taxon inpn '.$data2[0]["CD_NOM"].' n\'existe pas ';

					$sql="UPDATE biodiversite_inpn_taxinomie SET ordre_mise_a_jour='-1' WHERE CD_NOM='".$data2[0]["CD_NOM"]."'";
					$db->query($sql);
					continue;
				}
				}
				else
				{
					$data3[0]["id_taxinomie_sup"]='0';
				}

				$tableau_auteur=$this->traiter_lb_auteur($data2[0]["LB_AUTEUR"]);
//				echo 'passage après <br>';
				if (count($data1)>0)
				{
					//Mettre à jour
					
					$sql5="UPDATE biodiversite_taxinomie
					SET
					id_parent='".$data3[0]["id_taxinomie_sup"]."',
					nom_binomial='".escapeSQL($data2[0]["LB_NOM"])."',";
					if (empty($data1[0]["nom_francais"]))
					{$sql5.="nom_francais='".escapeSQL($data2[0]["NOM_VERN"])."',";}
					$sql5.="nom_anglais='".escapeSQL($data2[0]["NOM_VERN_EN"])."',
					id_rang_taxinomique='".$rang[$i]["id"]."',
					auteur='".escapeSQL($tableau_auteur[0])."',
					auteur_an='".$tableau_auteur[1]."',
					id_habitat='".$tableau_habitats[$data2[0]["HABITAT"]]."',
					inpn_nom_complet='".escapeSQL($data2[0]["NOM_COMPLET"])."',
					inpn_lb_nom='".escapeSQL($data2[0]["LB_NOM"])."',
					inpn_lb_auteur='".escapeSQL($data2[0]["LB_AUTEUR"])."',
					inpn_rang='".$data2[0]["RANG"]."',
					inpn_version='".$version_inpn."',
					id_statut_france_metropole='".$tableau_statuts[$data2[0]["FR"]]."',
					id_statut_martinique='".$tableau_statuts[$data2[0]["MAR"]]."',
					id_statut_guadeloupe='".$tableau_statuts[$data2[0]["GUA"]]."',
					id_statut_st_martin_st_barthelemy='".$tableau_statuts[$data2[0]["SMSB"]]."',
					id_statut_guyane_francaise='".$tableau_statuts[$data2[0]["GF"]]."',
					id_statut_st_pierre_et_miquelon='".$tableau_statuts[$data2[0]["SPM"]]."',
					id_statut_reunion='".$tableau_statuts[$data2[0]["REU"]]."',
					id_statut_mayotte='".$tableau_statuts[$data2[0]["MAY"]]."',
					id_statut_terres_australes_et_antartiques_francaises='".$tableau_statuts[$data2[0]["TAAF"]]."',
					id_statut_iles_eparses='".$tableau_statuts[$data2[0]["EPA"]]."',
					id_statut_polynesie_francaise='".$tableau_statuts[$data2[0]["PF"]]."',
					id_statut_nouvelle_caledonie='".$tableau_statuts[$data2[0]["NC"]]."',
					id_statut_wallis_et_futuna='".$tableau_statuts[$data2[0]["WF"]]."',
					id_statut_clipperton='".$tableau_statuts[$data2[0]["CLI"]]."',
					cd_nom='".$data2[0]["CD_NOM"]."',
					cd_taxsup='".$data2[0]["CD_TAXSUP"]."',
					cd_ref='".$data2[0]["CD_REF"]."',
					id_modification='".$idutilisateur."',
					date_modification=UTC_TIMESTAMP() 

			
			WHERE id='".$data1[0]['id']."'";
					$db->query($sql5);
					$nombreupdate++;
				}
				else {
					// Créer
						
					$sql5="INSERT INTO  biodiversite_taxinomie
					(id_parent,
					nom_binomial,
					nom_francais,
			 		nom_anglais,
					id_rang_taxinomique,
					auteur,
					auteur_an,
					id_habitat,
					inpn_nom_complet,
					inpn_lb_nom,
					inpn_lb_auteur,
					inpn_rang,
					inpn_version,
					id_statut_france_metropole,
					id_statut_martinique,
					id_statut_guadeloupe,
					id_statut_st_martin_st_barthelemy,
					id_statut_guyane_francaise,
					id_statut_st_pierre_et_miquelon,
					id_statut_reunion,
					id_statut_mayotte,
					id_statut_terres_australes_et_antartiques_francaises,
					id_statut_iles_eparses,
					id_statut_polynesie_francaise,
					id_statut_nouvelle_caledonie,
					id_statut_wallis_et_futuna,
					id_statut_clipperton,
					cd_nom,
					cd_taxsup,
					cd_ref,
					id_creation,
					date_creation, 
					id_modification,
					date_modification 
					
					)
					VALUES
					(
	
					'".$data3[0]["id_taxinomie_sup"]."',
					'".escapeSQL($data2[0]["LB_NOM"])."',
					'".escapeSQL($data2[0]["NOM_VERN"])."',
					'".escapeSQL($data2[0]["NOM_VERN_EN"])."',
					'".$rang[$i]["id"]."',
					'".escapeSQL($tableau_auteur[0])."',
					'".$tableau_auteur[1]."',
					'".$tableau_habitats[$data2[0]["HABITAT"]]."',
					'".escapeSQL($data2[0]["NOM_COMPLET"])."',
					'".escapeSQL($data2[0]["LB_NOM"])."',
					'".escapeSQL($data2[0]["LB_AUTEUR"])."',
					'".$data2[0]["RANG"]."',
					'".$version_inpn."',
					'".$tableau_statuts[$data2[0]["FR"]]."',
					'".$tableau_statuts[$data2[0]["MAR"]]."',
					'".$tableau_statuts[$data2[0]["GUA"]]."',
					'".$tableau_statuts[$data2[0]["SMSB"]]."',
					'".$tableau_statuts[$data2[0]["GF"]]."',
					'".$tableau_statuts[$data2[0]["SPM"]]."',
					'".$tableau_statuts[$data2[0]["REU"]]."',
					'".$tableau_statuts[$data2[0]["MAY"]]."',
					'".$tableau_statuts[$data2[0]["TAAF"]]."',
					'".$tableau_statuts[$data2[0]["EPA"]]."',
					'".$tableau_statuts[$data2[0]["PF"]]."',
					'".$tableau_statuts[$data2[0]["NC"]]."',
					'".$tableau_statuts[$data2[0]["WF"]]."',
					'".$tableau_statuts[$data2[0]["CLI"]]."',
					'".$data2[0]["CD_NOM"]."',
					'".$data2[0]["CD_TAXSUP"]."',
					'".$data2[0]["CD_REF"]."',
					'".$idutilisateur."',
					UTC_TIMESTAMP(),
					'".$idutilisateur."',
					UTC_TIMESTAMP()
)";
					//		$sql5=escapeSQL($sql5);
					$db->query($sql5);
					$nombreinsert++;
				}
				$ordre_mise_a_jour++;
				$sql="UPDATE biodiversite_inpn_taxinomie SET ordre_mise_a_jour='".$ordre_mise_a_jour."' WHERE CD_NOM='".$data2[0]["CD_NOM"]."'";
				$db->query($sql);
			}
		}
		$sql="SELECT max(id) as maxid , count(id) as nombre FROM biodiversite_taxinomie";
		$data = $db->getrows($sql);
		$nombretotal=$data[0]["nombre"];
		$sql="SELECT  count(id) as nombre_final FROM biodiversite_taxinomie where inpn_version='$version_inpn'";
		$data = $db->getrows($sql);
		$nombre_final=$data[0]["nombre_final"];
		$sql="SELECT  count(id) as nombre_init FROM biodiversite_taxinomie where inpn_version='$version_inpn_precedente'";
		$data = $db->getrows($sql);
		$nombre_init=$data[0]["nombre_init"];
		$sql="UPDATE db_sequence SET nextid='".$data[0]["maxid"]."' WHERE seq_name='seq_biodiversite_taxinomie'";
		$db->query($sql);
		$sql="SELECT count(CD_NOM) AS nombre FROM biodiversite_inpn_taxinomie WHERE ordre_mise_a_jour=-1";
		$data = $db->getrows($sql);
		$nombresansparent=$data[0]["nombre"];

		echo "- $nombreupdate taxons ont été modifiés dans biodiversité_taxinomie.<br />
						- $nombreinsert taxons ont été créés dans biodiversité_taxinomie.<br />
						- biodiversité_taxinomie contient un total de $nombretotal taxons.<br />
						- biodiversite_taxinomie contient $nombre_init taxons en version $version_inpn_precedente<br />
						- biodiversite_taxinomie contient $nombre_final taxons en version $version_inpn<br />
						$nombresansparent taxons sont sans parent et n\'ont pas été traités 
						(voir ordre_mise_a_jour='-1' dans la table biodiversité_inpn_taxinomie).<br />
						";
		die();
	}

	function traiter_lb_auteur($lb_auteur)
	{
		$tableau_auteur=array();
		$lb_auteur=str_replace('(',' ',$lb_auteur);
		$lb_auteur=str_replace(')',' ',$lb_auteur);
		$lb_auteur=str_replace('[',',',$lb_auteur);
		$lb_auteur=str_replace(']','',$lb_auteur);
		$lb_auteur=trim($lb_auteur);
		$tableau_auteur=explode(',',$lb_auteur);
		$tableau_auteur[0]=trim($tableau_auteur[0]);
		$tableau_auteur[1]=trim($tableau_auteur[1]);
		if (count($tableau_auteur)==2 && strlen($tableau_auteur[1])==4)
		{
		}
		else
		{$tableau_auteur=array();
		$tableau_auteur[0]=$lb_auteur;
		}
		return $tableau_auteur;
	}
	function ascendance_display($record, $mode)
	{
	$ascendance=$this->descripteur_biodiversite_ascendance($record["id"], $destination='affichage');
	return $ascendance;
	}
	function descendance_display($record, $mode)
	{
		return $this->biodiversite_descendance($record["id"], $mode);
	}
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
					$result.= "<font color='blue'><b>".$enfant."</b></font><BR />"; // on l'affiche avec le décallage courrant et on recherche ses fils
					$this->recur($enfant,$rang+1); // en rappelant la fonction recur() (+ incrémentation du décallage)
				}
			}
		}
		return ($result);
	}
	function google_en_display($record, $mode)
	{
		$url = "http://www.google.com/search?q=".$record["nom_binomial"] ;
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Google</b></font></a>';
	}
	function google_user_display($record, $mode)
	{
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="SELECT code_iso_639_1 from type_langue tl, app_utilisateur u
		 where u.id=$userutilisateur and u.id_langue_application=tl.id";
		$data=$db->getrows($sql);
		$url = "http://www.google.".$data[0]["code_iso_639_1"]."/search?q=".$record["nom_binomial"] ;
	return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Google ('.$data[0]["code_iso_639_1"].')</b></font></a>';
	}
	function xeno_canto_display($record, $mode)
	{
		$url="http://www.xeno-canto.org/browse.php?query=".$record["nom_binomial"]."&pagenumber=&order=taxonomy&view=4";
		$target=' target="_blank" ';
		return '<center><a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Chants xeno canto</b></font></a></center>';
	}
	function url_image_display($record, $mode)
	{
		$target=' target="_blank" ';

		$url='<center><a href="'.$record["url_image"]. '"' .$target.'"><img src="'.$record["url_image"].'" height="130" alt="'.$record["nom_binomial"].'" title="'.$record["nom_binomial"].'" /></a></center>' ;
		return  $url;
	}
	function wikipedia_en_display($record, $mode)
	{
		$url="http://en.wikipedia.org/wiki/".$record["nom_binomial"] ;
		$target = ' target="_blank"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>wikipedia</b></font></a>';
	}

	function wikipedia_user_display($record, $mode)
	{
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql="SELECT code_iso_639_1 from type_langue tl, app_utilisateur u
		 where u.id=$userutilisateur and u.id_langue_application=tl.id";
		$data=$db->getrows($sql);
		$url="http://".$data[0]["code_iso_639_1"].".wikipedia.org/wiki/".$record["nom_binomial"] ;
		$target = ' target="_blank"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>wikipedia ('.$data[0]["code_iso_639_1"].')</b></font></a>';
	}

	function id_taxon_fauna_europaea_display($record, $mode)
	{
		$id_taxon_fe=$record["id_taxon_fauna_europaea"];
		if (isset($id_taxon_fe))
		{ 	$url="http://www.faunaeur.org/full_results.php?id=".$id_taxon_fe ;
		$target = ' target="_blank"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Fauna europaea</b></font></a>';
		}
		else
		{return "";}
	}
	function oiseaux_net_display($record, $mode)
	{

		$nom=trim($record["nom_francais"]);
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
		$target = '';
		$url="http://www.oiseaux.net/oiseaux/".$nom.".html" ;

		$target = ' target="_blank"';

		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Oiseaux.net</b></font></a>';
	}

	function tela_botanica_display($record, $mode)
	{
		$nom=trim($record["nom_binomial"]);
		$url="http://www.tela-botanica.org/page:eflore?eflore_nom=".$nom."&eflore_referentiel=25&eflore_type_nom=nom_scientifique&module=recherche&action=recherche_nom";
		$target = ' target="_blank"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Tela botanica</b></font></a>';
	}
	function descripteur_taxinomie_display($record, $mode)
	{
				$retour=$this->descripteur_biodiversite_taxinomie($record["id"],null,'affichage');
		return $retour;
	}

	function id_taxon_conservation_nature_display($record, $mode)
	{
		$id_iucn=$record["id_taxon_conservation_nature"];
		if (isset($id_taxon_fe))
		{ 	$url="http://www.iucnredlist.org/details/".$id_iucn ;
		$target = ' target="_new"';
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>IUCN</b></font></a>';
		}
		else
		{return "";}
	}
	function descriptor_def() {
		return "[nom_binomial] - [inpn_nom_complet] - [nom_francais] - [cd_nom]/[cd_ref]";
	}
	function rowColor($record) {
//		$this->p($record);
		$idtaxinomie= $record["id"];
			$db = & atkGetDb();
		$sql="SELECT count(id) as nombre_observations  FROM `biodiversite_observation_detail` WHERE id_taxinomie=$idtaxinomie ";
		$data=$db->getrows($sql);
		if ($data[0]["nombre_observations"] >0)
		return $this->couleurpriorite2;
	}

	function action_admin($handler) {
			
		global $config_recordsperpage;
		$config_recordsperpage = 20;
if  (substr($this->m_postvars["atkfilter"],0,5) =="'%@@@")
		{      
			$view = "tout";
			$searchfields = array("nom_binomial","inpn_nom_complet","nom_francais","cd_nom","cd_ref");
		$searchvalue=$this->m_postvars["atkfilter"];
		$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
		$filter = $this->createSearchFilter($searchfields, $searchvalue,$this->table);

		$this->m_postvars["atkfilter"]=$filter;
		
		$this->addFilter($this->m_postvars["atkfilter"]);
}
		
	else {	
 		$view = $this->getView();
			if ($view == "requete") {
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "tout") {

			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "sans_image") {
//						$this->p($this->m_postvars);
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail
		  ) and ( biodiversite_taxinomie.url_image is null or biodiversite_taxinomie.url_image='' )");
			$this->addFilter($this->m_postvars["atkfilter"]);

		}
		if ($view == "sans_nom_francais") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail
		  ) and ( biodiversite_taxinomie.nom_francais is null or biodiversite_taxinomie.nom_francais='') ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "observees") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail
		  ) ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "observees_protegees") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail bod, biodiversite_taxinomie bt, biodiversite_protection_taxinomie bpt
				 where bod.id_taxinomie=bt.id and bt.cd_nom=bpt.cd_ref
		  ) ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		
			if ($view == "toutes_protegees") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_taxinomie bt, biodiversite_protection_taxinomie bpt
				 where bt.cd_nom=bpt.cd_ref	 
		  ) ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		
		
	}
		
		return $handler->action_admin();
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		//		$mraactions['maj'] = "maj";
		$mraactions['biolocalisation'] = "biolocalisation";
		$actions['biolocalisation'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=biolocalisation&atkselector=[pk]", SESSION_NESTED);


	}

	function adminFooter() {
		$retour=parent::adminfooter();
		$legende = '<b>Légende des couleurs : </b>';
		$legende .= '<font color="'.$this->couleurpriorite2.'"> <b> Espèce déjà observée dans la base utilisée </b></font><br>';
		$view = $this->getView();
		$retour_especes_observees=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=observees', 'Espèces observées')  ;
		$retour_sans_image=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=sans_image', 'Espèces observées sans image')  ;
		$retour_sans_nom_francais= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=sans_nom_francais', 'Espèces observées sans nom français') ;
		$retour_observees_protegees= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=observees_protegees', 'Espèces observées protégées') ;
		$retour_toutes_protegees= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=toutes_protegees', 'Toutes espèces protégées') ;
		$retour_tout= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=tout', 'Tout')  ;
		$db = & atkGetDb();
		$sql='select count(bt.id) as nombre from biodiversite_taxinomie bt ';
		$data=$db->getrows($sql);
		$nombre_tout=$data[0]["nombre"];
		$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od, biodiversite_taxinomie bt where od.id_taxinomie=bt.id
		  and ( bt.url_image is null or bt.url_image="")';
		$data=$db->getrows($sql);
		$nombre_sans_image=$data[0]["nombre"];
		$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od, biodiversite_taxinomie bt where od.id_taxinomie=bt.id
		  and (bt.nom_francais is null or bt.nom_francais="")';
		$data=$db->getrows($sql);
		$nombre_sans_nom_francais=$data[0]["nombre"];
		$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od';
		$data=$db->getrows($sql);
		$nombre_observees=$data[0]["nombre"];
		$sql='select count(distinct bod.id_taxinomie) as nombre from biodiversite_observation_detail bod, biodiversite_taxinomie bt, biodiversite_protection_taxinomie bpt
				 where bod.id_taxinomie=bt.id and bt.cd_nom=bpt.cd_ref ';
		$data=$db->getrows($sql);
		$nombre_observees_protegees=$data[0]["nombre"];
		$sql='select count(distinct bt.id) as nombre from biodiversite_taxinomie bt, biodiversite_protection_taxinomie bpt
				 where bt.cd_nom=bpt.cd_ref	 	 ';
		$data=$db->getrows($sql);
		$nombre_toutes_protegees=$data[0]["nombre"];
		
				$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od';
		$data=$db->getrows($sql);
		$nombre_observees=$data[0]["nombre"];
		
		$retour='<b>Sélections : </b>';
		if ($view == "tout")
		{$retour.= "<b>Tout(".$nombre_tout.")</b>".'|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')';}
		if ($view == "sans_image")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|<b>Espèces observées sans image('.$nombre_sans_image.')</b>|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')';}
		if ($view == "sans_nom_francais")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_image.'('.$nombre_sans_image.')|<b>Espèces observées sans nom français('.$nombre_sans_nom_francais.')</b>|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')';}
		if ($view == "observees")
		{$retour.= $retour_tout.'('.$nombre_tout.')|<b>Espèces observées('.$nombre_observees.')</b>|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')';}
		if ($view == "observees_protegees")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|<b>Espèces observées protégées('.$nombre_observees_protegees.')</b>|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')';}
		if ($view == "requete")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|'.$retour_toutes_protegees.'('.$nombre_toutes_protegees.')</b>';}
		if ($view == "toutes_protegees")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')|'.$retour_observees_protegees.'('.$nombre_observees_protegees.')|<b>Toutes espèces protégées('.$nombre_toutes_protegees.')</b>';}
		
		$retour.='<br>';
		
			global $g_sessionManager;
		$Administrateur_o_n=$g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		if ($Administrateur_o_n=='1')
		{	$retour.="<b>Actions : </b>".'<a href="'.dispatch_url("biodiversite.taxinomie", "mise_a_jour_inpn").'" target="_blank" >Import/Statistiques de biodiversite_inpn_taxinomie vers biodiversite_taxinomie.</a> - ';
$retour.='<a href="'.dispatch_url("biodiversite.taxinomie", "normalisation").'" target="_blank" >Normalisation des noms vernaculaires</a><br>';
		}
		

		return '</b>'.$legende .$retour.'<b>';
	}
function adminHeader() {
$retour=parent::adminHeader();
		return $retour.$this->adminFooter();
	}

	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "observees";
		}

		return $view;
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
	function web_info_display($record, $mode)
	{
		$idtaxinomie=trim($record["id"]);
		return $this->descripteur_biodiversite_web_info($idtaxinomie,"taxinomie");
	}
	function descripteur_inpn_display($record, $mode)
	{
		$idtaxinomie=trim($record["id"]);

		return $this->descripteur_biodiversite_taxons_inpn($idtaxinomie,"taxinomie");
	}
	function statuts_inpn_display($record, $mode)
	{
		$idtaxinomie=trim($record["id"]);
		return $this->descripteur_biodiversite_statuts_inpn($idtaxinomie,"taxinomie");
	}
	function referentiels_display($record, $mode)
	{
		$idtaxinomie=trim($record["id"]);
		return $this->descripteur_biodiversite_referentiels($idtaxinomie,"taxinomie");
	}
		function postAdd(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseProcess('taxon', $id_entite);
		}
		function preDelete(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseDelete('taxon', $id_entite);
		}
		function postUpdate($rec) {
			
				$id_entite = $rec["id"];
				$this->RecentUseRefresh('taxon');
				return true;
			
		}
function dispatch($postvars, $fullpage = true) {

			if ($postvars['atkaction'] != 'add' && $postvars['atkaction'] != 'delete' && $postvars['atkaction'] != 'admin') {
				$atkselect = $postvars["atkselector"];
				if (($atkselect != "") && isset ($atkselect)) {
					$taxinomieid = sscanf($atkselect, "biodiversite_taxinomie.id='%d'");
					$taxinomieId = $taxinomieid[0];
					$this->RecentUseProcess('taxon', $taxinomieId);
				} else {
					$taxinomieId = 0;
				}
			} else {

				$this->RecentUseRefresh('taxon');
			}
		return parent :: dispatch($postvars, $fullpage);
}
	
	
}
?>