<?php
atkimport("atk.assmetanode");
useattrib("development.atgFileManyToOneRelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");
class observation extends assMetaNode {
	var $table = "biodiversite_observation";
	var $filename;
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function observation() {
		$this->atkMetaNode();
		$this->atkNode("observation",  NF_ADD_LINK | NF_EDITAFTERADD | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (

		"descripteur",
		"descripteur_protections",
		"libelle",
		"id_organisme",
				"id_observateur",
				"id_organisme_observateur",
		"album_photos",

				"date_observation",

				"heure_observation",
				"duration",
				"id_type_observation",
			"code_departement_protection",	


				"meteo_vent_m_s",
				"meteo_nebulosite_octats",
				"meteo_temperature_celsius",
				"meteo_hygrometrie",
				"id_type_localisation",
				"id_ville",
				"id_lieu",
				"id_point_observation",
		"id_point_observation_1",
		"id_point_observation_2",
				"longitude",
				"latitude",
		"altitude",
			"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Observations" => array (
				//			"observations"
	"observation_detail"
	)
	,
			"Notes" => array (
				"contenu_html",
				"id_document"
				)
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY|AF_FORCE_LOAD), 95);
				$this->add(new atkDummyAttribute("descripteur",0,AF_HIDE_EDIT | AF_COMPACT ),92);
				$this->add(new atkDummyAttribute("descripteur_protections",0, AF_HIDE_EDIT |AF_COMPACT ),93);
				$this->add(new atkManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),100);
				$this->add(new atkManyToOneRelation("id_observateur", "individu.individu", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),110);
				$this->add(new atkManyToOneRelation("id_organisme_observateur", "organisme.organisme", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),120);
				$this->add(new atkUrlAttribute("album_photos", AF_POPUP | AF_SEARCHABLE ,200),122);

				$this->add(new atgNumberExpressionAttribute("observation_detail", ' select count(id) from biodiversite_observation_detail
	 where id_observation =[table].id 					', 0, 0),140);
				//				$c12->setDestinationFilter("biodiversite_taxinomie.id_rang_taxinomique between 22 and 29");
				//				$this->add(new atkManyToOneTreeRelation("id_taxinomie", "biodiversite.taxinomie", AF_PARENT), NULL);$this->add(new atkAttribute("nombre", AF_OBLIGATORY),140);
				$this->add(new atkDateAttribute("date_observation", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY),150);
				$this->add(new atkTimeAttribute("heure_observation",0,23,$steps=array("00","15","30","45"),"",   AF_OBLIGATORY),151);
				$this->add(new atkListAttribute("id_type_observation", array("Observation", "Photo", "Capture"), array(1,2,3),AF_SEARCHABLE|AF_OBLIGATORY|AF_FORCE_LOAD),155);
				$this->add(new atkNumberAttribute("duration",AF_SEARCHABLE, 5,0),152);
				$this->add(new atkNumberAttribute("code_departement_protection",AF_SEARCHABLE | AF_OBLIGATORY, 5,0),156);
				$this->add(new atkNumberAttribute("meteo_vent_m_s",AF_SEARCHABLE, 2, 2),160);
				$this->add(new atkNumberAttribute("meteo_nebulosite_octats",AF_SEARCHABLE, 1,0),170);
				$this->add(new atkNumberAttribute("meteo_temperature_celsius",AF_SEARCHABLE, 3, 1),180);
				$this->add(new atkNumberAttribute("meteo_hygrometrie",AF_SEARCHABLE, 3,0),190);
				//				$this->add(new atkListAttribute("id_type_localisation", array("Commune", "Lieu","Point d'observation", "Entre points","Coordonnées"), array(1,2,3,4,5),AF_SEARCHABLE|AF_OBLIGATORY));

				//				$this->add($id_type_localisation=new atkRadioDetailsAttribute('id_type_localisation',array("1"=>"id_ville","2"=>"id_lieu","3"=>"id_point_observation"), array("1"=>"id_ville","2"=>"id_lieu","3"=>"id_point_observation"),AF_DISPLAY_VERT|AF_NO_LABEL|AF_NO_TRANSLATION|AF_HIDE_VIEW),203);
				$this->add($id_type_localisation=new atkListAttribute('id_type_localisation',array("ville","lieu","point","points","latlon"), array("1","2","3","4","5"),AF_OBLIGATORY|AF_FORCE_LOAD),203);
				$id_type_localisation->addOnChangeHandler("change_id_type_localisation(newvalue);");
					
				$this->add(new atkManyToOneRelation("id_lieu", "individu.lieu", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_VIEW|AF_FORCE_LOAD),205);
				$this->add(new atkManyToOneRelation("id_ville", "table.cp_ville_pays", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE | AF_HIDE_VIEW|AF_FORCE_LOAD),204);
				$this->add(new atkManyToOneRelation("id_point_observation", "biodiversite.point_observation", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_HIDE_VIEW|AF_FORCE_LOAD),206);
				$this->add(new atkManyToOneRelation("id_point_observation_1", "biodiversite.point_observation", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_HIDE_VIEW|AF_FORCE_LOAD),207);

				$this->add(new atkManyToOneRelation("id_point_observation_2", "biodiversite.point_observation", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_HIDE_VIEW|AF_FORCE_LOAD),208);
				$this->add(new atkNumberAttribute("longitude", AF_SEARCHABLE| AF_HIDE_VIEW, 25, 15),230)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
				$this->add(new atkNumberAttribute("latitude", AF_SEARCHABLE| AF_HIDE_VIEW, 25, 15),240)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
				$this->add(new atkfckattribute("contenu_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
			)),270);
			$this->add(new atgFileManyToOneRelation("id_document", "organisme.document",  AF_HIDE_LIST  |AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE|AF_FORCE_LOAD),280);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,94 );
			//		$this->add(new atkOneToManyRelation("observations", "biodiversite.observation_detail", "id_observation", AF_HIDE_LIST));

			$this->setOrder("biodiversite_observation.date_modification desc");
			$this->setSecurityAlias("organisme.organisme");

			$this->m_securityMap["rapport"] = "view";
			//			$this->m_securityMap["rapport_sans_image_protection"] = "view";
			$this->m_securityMap["rapport_sans_image"] = "view";
			$this->m_securityMap["marquer_a_verifier_cdref"] = "view";
			$this->m_securityMap["forcer_cdref"] = "view";
				
			//			$this->m_securityMap["rapport_variante_protection_sans_image"] = "view";
			//			$this->m_securityMap["mise_a_jour_inpn"] = "view";



	}
	function descripteur_protections_display($record, $mode)
	{
		$id_observation=$record["id"];
		$departement_observation=$record["code_departement_protection"];
		$protections=$this->descripteur_biodiversite_protection(null,$id_observation,'observation','protection','affichage',null,$departement_observation);
		$listes_rouges=$this->descripteur_biodiversite_protection(null,$id_observation,'observation','liste_rouge','affichage',null,$departement_observation);
		$listes_espece_determinante=$this->descripteur_biodiversite_protection(null,$id_observation,'observation','espece_determinante','affichage',null,$departement_observation);
		if (strlen($protections)>0)
		{$descripteur.='Protections&nbsp;:&nbsp;'.$protections;
		$descripteur.='<br />';}
		if (strlen($listes_rouges)>0)
		{$descripteur.='Listes&nbsp;rouges&nbsp;:&nbsp;'.$listes_rouges;
		$descripteur.='<br />';}
		if (strlen($listes_espece_determinante)>0)
		{$descripteur.='Espèces&nbsp;déterminantes&nbsp:&nbsp;'.$listes_espece_determinante;
		$descripteur.='<br />';
		}
		$descripteur.=$this->document_aide_biodiversite_symboles_protection();
		$descripteur.=" ".$this->descripteur_aide('Descripteur_especes_protegees','n');
		return  $descripteur;

	}


	function descripteur_display($record, $mode)
	{
		if (isset ($record["id"]))
		{
			$retour=$this->decoupe_affichage_colonne($this->descripteur_biodiversite_observation($record["id"],'affichage'),50);
			return $retour;
		}
		else		return;
	}
	function descriptor_def()
	{
		return "[libelle]";
	}

	function initial_values()
	{
		$initial=array();
		$initial["id_type_localisation"]=1;
		$initial['id_type_observation']=1;


		return $initial;
	}
	function makeObligatory($attrs)
	{
			
		if (func_num_args() > 1)
		{
			$attrs = func_get_args();
		}
		else if (!is_array($attrs))
		$attrs = array($attrs);
		foreach ($attrs as $attr)
		$this->getAttribute($attr)->addFlag(AF_OBLIGATORY);
	}
	function observation_detail_display($record, $mode) {
		if (isset ($record["observation_detail"])) {
			$ret= href(dispatch_url("biodiversite.observation_detail", "admin", array (
				'atkfilter' => "biodiversite_observation_detail.id_observation='" . $record['id'] . "'"
				), "dispatch.php"), text($record["observation_detail"]), SESSION_NESTED);
				if ($record["observation_detail"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			$ret= href(dispatch_url("biodiversite.observation_detail", "admin", array (
				'atkfilter' => "biodiversite_observation_detail.id_observation='" . $record['id'] . "'"
				), "dispatch.php"), "0", SESSION_NESTED);
				return $ret;
		}
	}


	function emptyFields(&$rec,$fields)
	{
		foreach($fields as $field)
		{
			if(array_key_exists($field,$rec))
			{
				$rec[$field]=null;
			}
		}
	}


	function validate(&$record, $mode, $ignoreList = array())
	{
		switch($record["id_type_localisation"])
		{
			case '1':
				{
					$this->makeObligatory('id_ville');
				}
				break;
			case '2':
				{
					$this->makeObligatory('id_lieu');
				}
				break;
			case '3':
				{
					$this->makeObligatory('id_point_observation');
				}
				break;
			case '4':
				{
					$this->makeObligatory('id_point_observation_1');
					$this->makeObligatory('id_point_observation_2');
				}
				break;
			case '5':
				{
					$this->makeObligatory('latitude');
					$this->makeObligatory('longitude');
				}
				break;
		}
		return parent::validate($record, $mode, $ignoreList);
	}
	function preAdd(&$rec)
	{
		$db = & atkGetDb();
		//			$this->p($rec);
		switch($rec["id_type_localisation"])
		{
			case '1':
				{
					$clearfields = array('id_lieu','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre','latitude','longitude');
					$sql="select latitude, longitude from type_cp_ville_pays where id=".$rec["id_ville"]["id"]." ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_ville", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '2':
				{
					$clearfields = array('id_ville','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre','latitude','longitude');
					$sql="select latitude, longitude from lieu where id=".$rec["id_lieu"]["id"]." ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_lieu", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '3':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation_1','id_point_observation_2','latitude','longitude');
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '4':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation','distance_point_metre','latitude','longitude');
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation_1"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation_1", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$latitude_1=$data[0]["latitude"];
						$longitude_1=$data[0]["longitude"];
					}
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation_2"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation_2", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$latitude_2=$data[0]["latitude"];
						$longitude_2=$data[0]["longitude"];
					}
					if (($latitude_1>0 and $latitude_2>0) || ($latitude_1<0 and $latitude_2<0))
					{
						if ($latitude_1 < $latitude_2)
						{
							$latitude_3=$latitude_1 + ($latitude_2 - $latitude_1)/2;
						}
						else
						{
							$latitude_3=$latitude_2 + ($latitude_1 - $latitude_2)/2;
						}
					}
					else
					{$latitude_3=($latitude_1 + $latitude_2)/2;}

					if (($longitude_1>0 and $longitude_2>0) || ($longitude_1<0 and $longitude_2<0))
					{
						if ($longitude_1 < $longitude_2)
						{
							$longitude_3=$longitude_1 + ($longitude_2 - $longitude_1)/2;
						}
						else
						{
							$longitude_3=$longitude_2 + ($longitude_1 - $longitude_2)/2;
						}
					}
					else
					{$longitude_3=($longitude_1 + $longitude_2)/2;}
					$rec["latitude"]=$latitude_3;
					$rec["longitude"]=$longitude_3;

				}
				break;
			case '5':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre');
				}
				break;

		}
		$this->emptyFields($rec,$clearfields);
		parent :: preAdd($rec);
		return true;
	}

	function preUpdate(&$rec)
	{
		$db = & atkGetDb();
		//		$this->p($this->m_postvars);
		switch($rec["id_type_localisation"])
		{
			case '1':
				{
					$clearfields = array('id_lieu','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre','latitude','longitude');
					$sql="select latitude, longitude from type_cp_ville_pays where id=".$rec["id_ville"]["id"]." ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_ville", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '2':
				{
					$clearfields = array('id_ville','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre','latitude','longitude');
					$sql="select latitude, longitude from lieu where id=".$rec["id_lieu"]["id"]." ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_lieu", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '3':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation_1','id_point_observation_2','latitude','longitude');
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$rec["latitude"]=$data[0]["latitude"];
						$rec["longitude"]=$data[0]["longitude"];
					}
				}
				break;
			case '4':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation','distance_point_metre','latitude','longitude');
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation_1"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation_1", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$latitude_1=$data[0]["latitude"];
						$longitude_1=$data[0]["longitude"];
					}
					$sql="select l.latitude, l.longitude from biodiversite_point_observation po, lieu l where po.id=".$rec["id_point_observation_2"]["id"]." and po.id_lieu=l.id ";
					$data=$db->getrows($sql);
					if (!isset($data[0]["latitude"]) || !isset($data[0]["longitude"]))
					{triggerError($rec, "id_point_observation_2", 'Valeurs', atktext("longitude et latitude non initialisées", "atk"));}
					else
					{
						$latitude_2=$data[0]["latitude"];
						$longitude_2=$data[0]["longitude"];
					}
					if (($latitude_1>0 and $latitude_2>0) || ($latitude_1<0 and $latitude_2<0))
					{
						if ($latitude_1 < $latitude_2)
						{
							$latitude_3=$latitude_1 + ($latitude_2 - $latitude_1)/2;
						}
						else
						{
							$latitude_3=$latitude_2 + ($latitude_1 - $latitude_2)/2;
						}
					}
					else
					{$latitude_3=($latitude_1 + $latitude_2)/2;}

					if (($longitude_1>0 and $longitude_2>0) || ($longitude_1<0 and $longitude_2<0))
					{
						if ($longitude_1 < $longitude_2)
						{
							$longitude_3=$longitude_1 + ($longitude_2 - $longitude_1)/2;
						}
						else
						{
							$longitude_3=$longitude_2 + ($longitude_1 - $longitude_2)/2;
						}
					}
					else
					{$longitude_3=($longitude_1 + $longitude_2)/2;}
					$rec["latitude"]=$latitude_3;
					$rec["longitude"]=$longitude_3;

				}
				break;
			case '5':
				{
					$clearfields = array('id_ville','id_lieu','id_point_observation','id_point_observation_1','id_point_observation_2','distance_point_metre');
				}
				break;

		}
		$this->emptyFields($rec,$clearfields);
		parent :: preUpdate($rec);
		return true;
	}
	// suppression des lignes de biodiversite_taxinomie signalées par 'RETRAIT' dans biodiversite_inpn_changes

	/*	function action_rapport_variante_protection(&$handler)
	 {
		$this->action_rapport($handler,'oui','oui');
		}
		function action_rapport_variante_protection_sans_image(&$handler)
		{
		$this->action_rapport($handler,'oui','non');
		}


		function action_rapport_sans_image_protection(&$handler)
		{
		$this->action_rapport($handler,'non','non');
		}
		*/

	function action_marquer_a_verifier_cdref(&$handler)
	{
		$retour=$this->get_row_selection_information(false);
		$db = & atkGetDb();
		$userid=$retour["userid"];
		$sql="select bod.id
			from biodiversite_observation_detail bod, biodiversite_taxinomie bt 
			where bod.id_observation in ".$retour["in_id_string"]." 
			and bod.id_taxinomie=bt.id
			and bt.cd_ref!=bt.cd_nom";
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$sql="update biodiversite_observation_detail
			 set id_modification=$userid , date_modification=UTC_TIMESTAMP(),a_verifier_o_n='1' where id =".$data[$i]["id"]." ";
			$db->query($sql);
		}
			
		$this->redirect();
	}
	public function action_forcer_cdref()
	{
		$retour=$this->get_row_selection_information(false);
		$db = & atkGetDb();
		
		$sql="select bt.id as id_bt , bt.cd_ref, bt.cd_nom, bod.id as id_bod
			from biodiversite_observation_detail bod, biodiversite_taxinomie bt 
			where bod.id_observation in ".$retour["in_id_string"]." 
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

	function action_rapport_sans_image(&$handler)
	{
		$this->action_rapport($handler,'non','non');
	}


	function action_rapport(&$handler,$nombre_protections_o_n='non',$image_o_n='oui')
	{

		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$lc_regnum=20;
		$lc_phylum=20;
		$lc_classis=20;
		$lc_ordo=20;
		$lc_familia=20;
		$lc_nom_binomial=15;
		$lc_nom_complet=27;
		$lc_image=20;
		$lc_nom_francais=15;
		$lc_protection_intitule=50;
		$lc_protections=20;
		$lc_liste_rouge=20;
		$lc_espece_determinante=20;
		$lc_article=20;
		$lc_statuts=20;
		$lc_taxon_ref=7;
		$lc_staut_inpn=20;
		$lc_premiere_observation=20;
		$lc_derniere_observation=20;
		$lc_departement=20;
		$lc_nombre_especes_observees=20;
		$lc_id_observation=20;
		$lc_libelle_observation=20;
		$lc_organisme_commanditaire=20;
		$lc_organisme_observateur=20;
		$lc_observateur=20;
		$lc_lieu=20;
		$lc_latitude=20;
		$lc_longitude=20;
		$lc_niveau_geographique=20;
		$lc_date_observation=20;
		$lc_observation_protections=12;


		$message_ordre_manquant=array();
		$db = & atkGetDb();
		$sql="SELECT MAX(NUM_VERSION_FINAL) as version, MIN(NUM_VERSION_INIT) as version_init FROM `biodiversite_inpn_changes` ";
		$data = $db->getrows($sql);
		$version_inpn=$data[0]["version"] ;

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';

			$idobservations= substr($chaineid, 0, strlen($chaineid) - 1);
			$idobservations = str_replace("'", "", $idobservations);
		}
		$sql="select distinct code_departement_protection as code_departement_protection from biodiversite_observation where biodiversite_observation.id in ( " . $idobservations . ")";
		$data= $db->getrows($sql);
		if (count($data) >1)
		{ echo 'impossible : plusieurs départements';
		die();
		}
		$departement_observation=$data[0]["code_departement_protection"];
		$tbl = & atknew("atk.utils.atktablerenderer");
		$tbl->setRowClass(1, "superbold");

		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$data=$db->getrows("Select individu.prenom as prenom, individu.nom as nom from app_utilisateur, individu where app_utilisateur.id=$userid and app_utilisateur.id_individu=individu.id");
		$filename=$this->getUserFileName('biodiversite_rapport','csv',$filenameshort);
		$dataentete=array();
		$row=array();
		$row[]="Vous pouvez retrouver ce tableau au format csv dans vos documents (utilisateur/documents personnels/<b>$filenameshort</b>) ";
		$dataentete[] = $row;
		$row=array();
		$filename2=substr($filenameshort,0, strlen($filenameshort)-4).'.html';
		$row[]="Vous pouvez retrouver ce tableau au format html dans vos documents (utilisateur/documents personnels/<b>$filename2</b>) ";
		$dataentete[] = $row;
		$row=array();
		$row[]="Ce rapport a été créé par ".$data[0]["prenom"]." ".$data[0]["nom"]." le ".gmdate( 'd/m/Y ')." à ".gmdate("H:i:s")." TU.";
		$dataentete[] = $row;

		// Liste observations
		$data_observations=array();
		$row=array();
		$row[]="<b>#</b>";
		$row[]="<b>Id</b>";
		$row[]="<b>Observation</b>";
		$row[]="<b>Commanditaire</b>";
		$row[]="<b>Organisme<br />observateur</b>";
		$row[]="<b>Observateur</b>";
		$row[]="<b>Lieu</b>";
		//		$row[]="<b>Latitude</b>";
		//		$row[]="<b>Longitude</b>";
		//		$row[]="<b>Dépt</b>";
		$row[]="<b>Date<br />observation</b>";
		$row[]="<b>Espèces<br />observées</b>";
		$row[]="<b>Listes</b>";
		//		$row[]="<b>LR</b>";
		//		$row[]="<b>LED</b>";
		$data_observations[] = $row;
		$arrayobservations=explode(",",$idobservations);

		for ($i = 0; $i < count($arrayobservations); $i++) {
			$tableau_observation=$this->descripteur_biodiversite_observation($arrayobservations[$i],"rapport");
			$protections=$this->descripteur_biodiversite_protection(null,$arrayobservations[$i],'observation','protection','affichage',null,$departement_observation);
			$listes_rouges=$this->descripteur_biodiversite_protection(null,$arrayobservations[$i],'observation','liste_rouge','affichage',null,$departement_observation);
			$listes_espece_determinante=$this->descripteur_biodiversite_protection(null,$arrayobservations[$i],'observation','espece_determinante','affichage',null,$departement_observation);
			$sql="select count(distinct id_taxinomie) as especes_observees from biodiversite_observation_detail
			 where biodiversite_observation_detail.id_observation =$arrayobservations[$i]";
			$data1= $db->getrows($sql);
			$especes_observees=$data1[0]["especes_observees"];
			$row=array();
			$row[]=$i+1;
			$row[]=$arrayobservations[$i];
			$row[]=$this->decoupe_affichage_colonne($tableau_observation["observation_libelle"],$lc_libelle_observation);
			$row[]=$this->decoupe_affichage_colonne($tableau_observation["organisme_commanditaire"],$lc_organisme_commanditaire);
			$row[]=$this->decoupe_affichage_colonne($tableau_observation["organisme_observateur"],$lc_organisme_observateur);
			$row[]=$this->decoupe_affichage_colonne($tableau_observation["observateur"],$lc_observateur);
			$row[]=$this->decoupe_affichage_colonne($tableau_observation["lieu"].'<br />Lat : '
			.$tableau_observation["latitude"].'<br />Lon : '
			.$tableau_observation["longitude"].'<br />Dépt : '
			.$tableau_observation["code_departement_protection"],$lc_lieu);
			//			$row[]=$tableau_observation["latitude"];
			//			$row[]=$tableau_observation["longitude"];
			//			$row[]=$tableau_observation["code_departement_protection"];
			$row[]=$tableau_observation["date_observation"];
			$row[]=$especes_observees;
			if ($image_o_n=='non')
			{$row[]=	(empty($protections) ? '' : 'Protections : '.'<br />'.$this->decoupe_affichage_colonne(strip_tags($protections),$lc_protection_intitule).'<br />')
			.(empty($listes_rouges) ? '' : 'Listes rouges : '.'<br />'.$this->decoupe_affichage_colonne(strip_tags($listes_rouges),$lc_protection_intitule).'<br />')
			.(empty($especes_determinantes) ? '' : 'Espèces déterminantes : '.'<br />'.$this->decoupe_affichage_colonne(strip_tags($especes_determinantes),$lc_protection_intitule));
			}
			else
			{$row[]=	(empty($protections) ? '' : 'Protections : '.'<br />'.$this->decoupe_affichage_colonne($protections,$lc_protection_intitule).'<br />')
			.(empty($listes_rouges) ? '' : 'Listes rouges : '.'<br />'.$this->decoupe_affichage_colonne($listes_rouges,$lc_protection_intitule).'<br />')
			.(empty($especes_determinantes) ? '' : 'Espèces déterminantes : '.'<br />'.$this->decoupe_affichage_colonne($especes_determinantes,$lc_protection_intitule));
			}
			$data_observations[] = $row;




		}

		$data=array();
		$datagroupes=array();
		$dataprotections=array();
		$datalistesrouges=array();
		$dataespecesdeterminantes=array();
		$dataprotections_especes=array();
		$datalistesrouges_especes=array();
		$dataespecesdeterminantes_especes=array();
		// Liste espèces observées
		$row=array();
		$row[]="<b>#</b>";
		$row[]="<b>Nom<br />binomial</b>";
		$row[]="<b>Nom<br />complet</b>";
		if ($image_o_n=='oui') $row[]="<b>Image";
		$row[]="<b>Nom<br />francais</b>";
		$row[]="<b>Règne</b>";
		//	$row[]="<b>Phylum</b>";
		$row[]="<b>Classe</b>";
		$row[]="<b>Ordre</b>";
		$row[]="<b>Famille</b>";
		//	$row[]="<b>CD_REF</b>";
		//	$row[]="<b>Statut INPN</b>";
		$row[]="<b>Observations<br />(première)<br />(dernière)</b>";
		//	$row[]="<b>Dernière obs.</b>";
		$row[]="<b>Dépt</b>";
		$row[]="<b>Listes</b>";
		//		$row[]="<b>LR</b>";
		//		$row[]="<b>LED</b>";
		$data[] = $row;

		$sql="SELECT distinct
biodiversite_taxinomie.id as id_taxinomie,
biodiversite_taxinomie.url_image as url_image,  
biodiversite_taxinomie.id_parent as id_parent, 
biodiversite_taxinomie.cd_ref as cd_ref 
FROM
 `biodiversite_observation` 
 JOIN biodiversite_observation_detail 
 JOIN biodiversite_taxinomie 
 WHERE
  ( biodiversite_observation.id = biodiversite_observation_detail.id_observation)
   AND ( biodiversite_taxinomie.id = biodiversite_observation_detail.id_taxinomie)
    AND (biodiversite_observation.id in ( " . $idobservations . ")) 
    ORDER BY biodiversite_taxinomie.nom_binomial";

		$stuff = $db->getrows($sql);
		$tableau="description_html";
		if (count($stuff)>0 )
		{
			for ($i = 0; $i < count($stuff); $i++) {
				$id_observation=$stuff[$i]["id_observation"];
				$id_taxinomie=$stuff[$i]["id_taxinomie"];
				$url_image=$stuff[$i]["url_image"];
				$id_parent=$stuff[$i]["id_parent"];
				$cd_ref=$stuff[$i]["cd_ref"];
				$tableau_premiere_derniere_observation=$this->descripteur_biodiversite_premiere_derniere_observation($id_taxinomie,$idobservations);
				$tableau_ascendance=$this->descripteur_biodiversite_ascendance($id_taxinomie, $destination='rapport');

				//>>>>>>>>>>>>>>>
				$tableau_protection=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,$details_o_n='détails',  $type='protection','rapport',$cd_ref,$departement_observation);
				/*
				 * 						$tableau_retour[$i][0]=$retourcdprotectioninpn.'('.$data[$i]["an"].') | '.$data[$i]["article"].' | ' .$this->descripteur_biodiversite_traduction_code($data[$i]["statut"]).' | '.$rapport_departement;
				 $tableau_retour[$i][1]=$retourcdprotectioninpn;
				 $tableau_retour[$i][2]=descripteur_biodiversite_protection_taxinomie_statuts($cd_ref, $data[$i]["cd_protection"]);
				 */
				$protections=null;
				$protections_nombre=count($tableau_protection);
				for ($k = 0; $k < count($tableau_protection); $k++)
				{						$protections.=($k+1).'- '.$this->string_trim_from_end($tableau_protection[$k][0],'|').'<br />';
				if (isset($dataprotections[$tableau_protection[$k][0]]))
				{	++$dataprotections[$tableau_protection[$k][0]]; }
				else
				{$dataprotections[$tableau_protection[$k][0]]=1;}
				}
				$protections=substr($protections,0,strlen($protections)-6);
				//$protections=$this->decoupe_affichage_colonne($protections, $lc_protections);

				//>>>>>>>>>>>>>>>
				$tableau_liste_rouge=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,$details_o_n='détails',  $type='liste_rouge','rapport',$cd_ref,$departement_observation);
				$listes_rouges=null;
				$listes_rouges_nombre=count($tableau_liste_rouge);
				for ($k = 0; $k < count($tableau_liste_rouge); $k++)
				{						$listes_rouges.=($k+1).'- '.$this->string_trim_from_end($tableau_liste_rouge[$k][0],'|').'<br />';
				if (isset($datalistesrouges[$tableau_liste_rouge[$k][0]]))
				{
					++$datalistesrouges[$tableau_liste_rouge[$k][0]];
				}
				else {
					$datalistesrouges[$tableau_liste_rouge[$k][0]]=1;
				}			}
				$listes_rouges=substr($listes_rouges,0,strlen($listes_rouges)-6);
				//$listes_rouges=$this->decoupe_affichage_colonne($listes_rouges,$lc_liste_rouge);
				//>>>>>>>>>>>>>>>
				$tableau_espece_determinante=$this->descripteur_biodiversite_protection($id_taxinomie,$id_observation,$details_o_n='détails',  $type='espece_determinante','rapport',$cd_ref,$departement_observation);
				$especes_determinantes=null;
				$especes_determinantes_nombre=count($tableau_espece_determinante);
				for ($k = 0; $k < count($tableau_espece_determinante); $k++)
				{						$especes_determinantes.=($k+1).'- '.$this->string_trim_from_end($tableau_espece_determinante[$k][0],'|').'<br />';
				if (isset($dataespecesdeterminantes[$tableau_espece_determinante[$k][0]]))
				{
					++$dataespecesdeterminantes[$tableau_espece_determinante[$k][0]];
				}
				else {
					$dataespecesdeterminantes[$tableau_espece_determinante[$k][0]]=1;
				}
				}
				$especes_determinantes=substr($especes_determinantes,0,strlen($especes_determinantes)-6);
				//$especes_determinantes=$this->decoupe_affichage_colonne($especes_determinantes,$lc_espece_determinante);



				$tableau_taxinomie=$this->descripteur_biodiversite_taxinomie($id_taxinomie,$id_observation,'rapport');
				//				$this->p($tableau_taxinomie);
				$target=' target="_blank" ';
				$tableau_taxinomie["image"]='<center><a href="'.$url_image. '"' .$target.'"><img src="'.$url_image.'" height="50" alt="'.$tableau_taxinomie["nom_binomial"].'" title="'.$tableau_taxinomie["nom_binomial"].'" /></a></center>' ;
				$concatenation=(empty($tableau_ascendance["Regnum"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_ascendance["Regnum"], $lc_regnum)) .'@'
				//				.(empty($tableau_ascendance["Phylum"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_ascendance["Phylum"], $lc_phylum)) .'@'
				.(empty($tableau_ascendance["Classis"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_ascendance["Classis"], $lc_classis)).'@'
				.(empty($tableau_ascendance["Ordo"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_ascendance["Ordo"], $lc_ordo)).'@'
				.(empty($tableau_ascendance["Familia"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_ascendance["Familia"], $lc_familia)).'@'
				.(empty($tableau_taxinomie["nom_binomial"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_taxinomie["nom_binomial"], $lc_nom_binomial)).'@'
				.(empty($tableau_taxinomie["inpn_nom_complet"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_taxinomie["inpn_nom_complet"], $lc_nom_complet)).'@' ;
				if ($image_o_n=='oui') $concatenation.=(empty($tableau_taxinomie["image"]) ? ' ' : $tableau_taxinomie["image"]).'@';
				$concatenation.=(empty($tableau_taxinomie["nom_francais"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_taxinomie["nom_francais"], $lc_nom_francais));
				if ($protections!=null)
				{
					//					$dataprotections_especes[$concatenation]=$protections;
					$dataprotections_especes[$concatenation]=$tableau_protection;
					//		if (count($tableau_protection)>1) $this->p($dataprotections_especes);

				}
				if ($listes_rouges!=null)
				{
					//$datalistesrouges_especes[$concatenation]=$listes_rouges;
					$datalistesrouges_especes[$concatenation]=$tableau_liste_rouge;
				}
				if ($especes_determinantes!=null)
				{
					//$dataespecesdeterminantes_especes[$concatenation]=$especes_determinantes;
					$dataespecesdeterminantes_especes[$concatenation]=$tableau_espece_determinante;
				}
				if ( $nombre_protections_o_n=='oui')
				{$protections=$protections_nombre=='0' ? ' ' : $protections_nombre;
				$listes_rouges=$listes_rouges_nombre=='0' ? ' ' : $listes_rouges_nombre;
				$especes_determinantes=$especes_determinantes_nombre=='0' ? ' ' : $especes_determinantes_nombre;
				}

				$urlcdrefinpn="http://inpn.mnhn.fr/isb/servlet/ISBServlet?action=Espece&typeAction=10&pageReturn=ficheEspeceDescription.jsp&numero_taxon=".$tableau_taxinomie["cd_ref"]."" ;
				$tableau_taxinomie["cd_ref"]='<b><a href="' . $urlcdrefinpn .' " target="_blank" >'.$tableau_taxinomie["cd_ref"].'</a>';
				$colllistes=(empty($protections) ? '' : 'Protections : '.'<br />'.$this->decoupe_affichage_colonne($protections,$lc_protection_intitule).'<br />')
				.(empty($listes_rouges) ? '' : 'Listes rouges : '.'<br />'.$this->decoupe_affichage_colonne($listes_rouges,$lc_protection_intitule).'<br />')
				.(empty($especes_determinantes) ? '' : 'Espèces déterminantes : '.'<br />'.$this->decoupe_affichage_colonne($especes_determinantes,$lc_protection_intitule));

				$data2[$concatenation]=
				//		(empty($tableau_taxinomie["cd_ref"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_taxinomie["cd_ref"], $lc_taxon_ref)).'@'
				//		.(empty($tableau_taxinomie["statut_inpn"]) ? ' ' : $this->decoupe_affichage_colonne($tableau_taxinomie["statut_inpn"],$lc_staut_inpn)).'@'
				(empty($tableau_premiere_derniere_observation[1]) ? ' ' : $tableau_premiere_derniere_observation[1]).'<br />'
				.(empty($tableau_premiere_derniere_observation[0]) ? ' ' : $tableau_premiere_derniere_observation[0]).'@'
				.(empty($departement_observation) ? ' ' : $departement_observation).'@'
				.$colllistes;

					
					
				$row=array();
				$row[]=$i+1;
				$row[]=$this->decoupe_affichage_colonne($tableau_taxinomie["nom_binomial"],$lc_nom_binomial);
				$row[]=$this->decoupe_affichage_colonne($tableau_taxinomie["inpn_nom_complet"],$lc_nom_complet);
				if ($image_o_n=='oui') $row[]=$tableau_taxinomie["image"];
				//			$row[]=$tableau_taxinomie["auteur_an"];
				$row[]=$this->decoupe_affichage_colonne($tableau_taxinomie["nom_francais"],$lc_nom_francais);
				//			$row[]=$this->decoupe_affichage_colonne($tableau_ascendance["Regnum"], $lc_regnum);
				$row[]=$this->decoupe_affichage_colonne($tableau_ascendance["Phylum"], $lc_phylum);
				$row[]=$this->decoupe_affichage_colonne($tableau_ascendance["Classis"], $lc_classis);
				$row[]=$this->decoupe_affichage_colonne($tableau_ascendance["Ordo"], $lc_ordo);
				$row[]=$this->decoupe_affichage_colonne($tableau_ascendance["Familia"], $lc_familia);
				//			$row[]=$this->decoupe_affichage_colonne($tableau_taxinomie["cd_ref"],$lc_taxon_ref);

				//			$row[]=$this->decoupe_affichage_colonne($tableau_taxinomie["statut_inpn"],$lc_staut_inpn);
				$row[]=$tableau_premiere_derniere_observation[1].'<br />'.$tableau_premiere_derniere_observation[0];
				$row[]=$this->decoupe_affichage_colonne($departement_observation,$lc_departement);
				$row[]=$colllistes;
				$data[] = $row;
				if ($tableau_ascendance["Ordo"]=='')
				{
					$message_ordre_manquant[]=$tableau_taxinomie["nom_binomial"];
					// die();
				}

				if (isset($datagroupes[$tableau_ascendance["Regnum"].'@'.$tableau_ascendance["Phylum"].'@'.$tableau_ascendance["Classis"].'@'.$tableau_ascendance["Ordo"] ]))
				{
					++$datagroupes[$tableau_ascendance["Regnum"].'@'.$tableau_ascendance["Phylum"].'@'.$tableau_ascendance["Classis"].'@'.$tableau_ascendance["Ordo"]];
				}
				else {
					$datagroupes[$tableau_ascendance["Regnum"].'@'.$tableau_ascendance["Phylum"].'@'.$tableau_ascendance["Classis"].'@'.$tableau_ascendance["Ordo"]]=1;
				}

			}

			$tableaudata2=array();
			ksort($data2);
			// Liste espèces observées triées par classification
			$row2=array();
			$row2[]="<b>#</b>";

			$row2[]="<b>Règne</b>";
			//			$row2[]="<b>Phylum</b>";
			$row2[]="<b>Classe</b>";
			$row2[]="<b>Ordre</b>";
			$row2[]="<b>Famille</b>";
			$row2[]="<b>Nom<br />binomial</b>";
			$row2[]="<b>Nom<br />complet</b>";
			if ($image_o_n=='oui') $row2[]="<b>Image</b>";
			//			$row2[]="<b>Année</b>";
			$row2[]="<b>Nom<br />francais</b>";
			//			$row2[]="<b>CD_REF</b>";
			//			$row2[]="<b>Statut INPN</b>";
			$row2[]="<b>Observations<br />(première)<br />(dernière)</b>";
			//		$row2[]="<b>Dernière obs.</b>";
			$row2[]="<b>Dépt</b>";
			$row2[]="<b>Listes</b>";
			//			$row2[]="<b>LR</b>";
			//			$row2[]="<b>LED</b>";
			$tableaudata2[]=$row2;
			$compteur=0;
			foreach ($data2 as $k=>$v)
			{
				$ligne=$k.'@'.$v;
				$ligne=str_replace('@@','@ @',$ligne);
				$row2=array();
				++$compteur;
				$row2[]=$compteur;
				$token = strtok($ligne, "@");
				while ($token != false)
				{
					$row2[]=$token;
					$token = strtok("@");
				}
				$tableaudata2[]=$row2;
			}



			$tableaugroupes=array();
			ksort($datagroupes);
			// Liste des nombres observés par Ordre
			$rang=array();
			$rang[]="<b>#</b>";
			$rang[]="<b>Règne</b>";
			$rang[]="<b>Phylum</b>";
			$rang[]="<b>Classe</b>";
			$rang[]="<b>Ordre</b>";
			$rang[]="<b>Espèces<br />observées</b>";
			$tableaugroupes[]=$rang;
			$compteur=0;
			foreach ($datagroupes as $k=>$v)
			{

				$ligne=$k.'@'.$v;
				$ligne=str_replace('@@','@ @',$ligne);
				$rang=array();
				++$compteur;
				$rang[]=$compteur;
				$token = strtok($ligne, "@");
				while ($token != false)
				{
					$rang[]=$token;
					$token = strtok("@");
				}
				$tableaugroupes[]=$rang;
			}
			$tableau_retour=$this->traitement_tableau_protection($type='Protection',$dataprotections, $dataprotections_especes, $image_o_n);
			$tableauprotections=$tableau_retour["type"];
			$tableauprotections_especes=$tableau_retour["especes"];
			$tableau_retour=$this->traitement_tableau_protection($type='Listes rouges',$datalistesrouges, $datalistesrouges_especes, $image_o_n);
			$tableaulistesrouges=$tableau_retour["type"];
			$tableaulistesrouges_especes=$tableau_retour["especes"];
			//			$this->p($tableaulistesrouges_especes);
			$tableau_retour=$this->traitement_tableau_protection($type='Espèces déterminantes',$dataespecesdeterminantes, $dataespecesdeterminantes_especes, $image_o_n);
			$tableauespecesdeterminantes=$tableau_retour["type"];
			$tableauespecesdeterminantes_especes=$tableau_retour["especes"];

			$datalegendes=array();
			$row=array();
			$row[]='<b>Liste des annexes </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 1 : Liste des espèces observées. </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Triée par nom complet INPN.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Triée selon la classification classique.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 2 : Nombre d\'espèces observées par Ordre. </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 3 : Liste des observations effectuées.</b> ';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 4 : Protections. </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Listes.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Espèces.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 5 : Listes rouges. </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Listes.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Espèces.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>Annexe 6 : Espèces déterminantes. </b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Listes.</b>';
			$datalegendes[]=$row;
			$row=array();
			$row[]='<b>&nbsp;&nbsp;Espèces.</b>';
			$datalegendes[]=$row;

			$row=array();
			$row[]='<b>Légende des principaux symboles utilisés.</b>';
			$datalegendes[]=$row;



			// ouvrir fichier

			$file=fopen($filename, "w");

			// en-tete (fichier généré par le )
			$this->file_write_tableau($file, $dataentete);
			$res_en_tete = $tbl->render($dataentete, 0, "recordlist");
			// legendes
			$this->file_write_tableau($file, $datalegendes);
			$res_legendes = $tbl->render($datalegendes, 0, "recordlist");
			// especes observees
			$datatitre=array();
			$datatitre[]=array('Annexe 1 : Liste des espèces observées. ');
			$this->file_write_tableau($file, $datatitre);
			$res_especes = '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';
			$datatitre=array();
			$datatitre[]=array('Triée par nom complet INPN.');
			$this->file_write_tableau($file, $datatitre);
			$res_especes .= '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';

			$this->file_write_tableau($file, $data);
			$res_especes .= $tbl->render($data, 0, "recordlist");

			$datatitre=array();
			$datatitre[]=array('Triée selon la classification classique.');
			$this->file_write_tableau($file, $datatitre);
			$res_especes .= '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';

			$this->file_write_tableau($file, $tableaudata2);
			$tableaudata2=$this->report_writer($tableaudata2,1,6);
			$res_especes .= $tbl->render($tableaudata2, 0, "recordlist");
			// ordres
			$datatitre=array();

			$datatitre[]=array('Annexe 2 : Nombre d\'espèces observées par Ordre. ');
			$this->file_write_tableau($file, $datatitre);
			$res_cumul =  '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableaugroupes);
			$tableaugroupes=$this->report_writer($tableaugroupes,1,3);
			$res_cumul.=$tbl->render($tableaugroupes,0,"recordlist");
			// observations
			$datatitre=array();

			$datatitre[]=array('Annexe 3 : Liste des observations effectuées. ');
			$this->file_write_tableau($file, $datatitre);
			$res_observations = '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $data_observations);
			$res_observations.= $tbl->render($data_observations, 0, "recordlist");
			// protections
			$datatitre=array();
			$datatitre[]=array('Annexe 4 : Protections. ');
			$this->file_write_tableau($file, $datatitre);
			$res_protections = '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$datatitre=array();
			$datatitre[]=array('Listes.');
			$this->file_write_tableau($file, $datatitre);
			$res_protections .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableauprotections);
			//		$tableauprotections=$this->report_writer($tableauprotections,1,1);
			$res_protections.=$tbl->render($tableauprotections,0,"recordlist");
			$datatitre=array();
			$datatitre[]=array('Espèces. ');
			$this->file_write_tableau($file, $datatitre);
			$res_protections .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableauprotections_especes);
			//		$tableauprotections_especes=$this->report_writer($tableauprotections_especes,0,9);
			$res_protections.=$tbl->render($tableauprotections_especes,0,"recordlist");
			// listes rouges
			$datatitre=array();

			$datatitre[]=array('Annexe 5 : Listes rouges. ');
			$this->file_write_tableau($file, $datatitre);
			$res_listesrouges =  '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';
			$datatitre=array();
			$datatitre[]=array('Listes.');
			$this->file_write_tableau($file, $datatitre);
			$res_listesrouges .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableaulistesrouges);
			//		$tableaulistesrouges=$this->report_writer($tableaulistesrouges,1,1);
			$res_listesrouges.=$tbl->render($tableaulistesrouges,0,"recordlist");
			$datatitre=array();
			$datatitre[]=array('Espèces. ');
			$this->file_write_tableau($file, $datatitre);
			$res_listesrouges .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableaulistesrouges_especes);
			//		$tableaulistesrouges_especes=$this->report_writer($tableaulistesrouges_especes,0,9);
			$res_listesrouges.=$tbl->render($tableaulistesrouges_especes,0,"recordlist");

			// especes déterminantes
			$datatitre=array();

			$datatitre[]=array('Annexe 6 : Espèces déterminantes. ');
			$this->file_write_tableau($file, $datatitre);
			$res_especesdeterminantes =  '<br /><b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';
			$datatitre=array();
			$datatitre[]=array('Listes.');
			$this->file_write_tableau($file, $datatitre);
			$res_especesdeterminantes .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableauespecesdeterminantes);
			//		$tableauespecesdeterminantes=$this->report_writer($tableauespecesdeterminantes,1,1);
			$res_especesdeterminantes.=$tbl->render($tableauespecesdeterminantes,0,"recordlist");
			$datatitre=array();
			$datatitre[]=array('Espèces. ');
			$this->file_write_tableau($file, $datatitre);
			$res_especesdeterminantes .= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$this->file_write_tableau($file, $tableauespecesdeterminantes_especes);
			//		$tableauespecesdeterminantes_especes=$this->report_writer($tableauespecesdeterminantes_especes,0,9);
			$res_especesdeterminantes.=$tbl->render($tableauespecesdeterminantes_especes,0,"recordlist");

			$datatitre=array();
			$datatitre[]=array('Légende des principaux symboles utilisés.');
			$this->file_write_tableau($file, $datatitre);
			$res_legende= '<br /><b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';
			$datatitre=array();
			$datatitre[]=array( "Dépt : Département français.<br />
			Prot. : Protections des espèces.<br />
			LR : Listes rouges.<br />
			LED : Listes d'espèces déterminantes.<br />
			CD_NOM : Code taxon INPN.<br />
			CD_REF : Code taxon de référence INPN.<br />
			LB_NOM :nom binomial INPN.<br />
			Les informations sur les espèces sont celles fournies par l'Inventaire National du Patrimoine Naturel (http://inpn.mnhn.fr/) : la dernière version utilisée est la version 
			TAXREF $version_inpn  <br /> <br />
				Profitez pleinement de cette version de l'annexe du rapport :<br>
			- les liens CD_NOM et CD_REF affichent directement les taxons concernés sur le site de l'INPN <br>
			- les liens sur les images vous les montrent en taille maximum.<br>
			- les liens sur les noms des listes vous ouvrent les textes officiels en ligne
			
		");
				
			/*			$hrefdoc=dispatch_url("organisme.document", "fichier", array (
			 "atkselector" => "organisme_document.id='1491'"
			 ));
			 */
			$hrefdoc="https://sites.google.com/a/lescailleries.org/www/legendes_biodiversite.pdf?attredirects=0";
			$datatitre[]=array( '<a href="'.$hrefdoc.'"><b>Télécharger la légende des symboles au format pdf</b></a><br />');
				
			if ($image_o_n=='oui')
			{$hrefdoc="https://sites.google.com/a/lescailleries.org/www/annexe_rapport_biodiversite.html?attredirects=0";
			$datatitre[]=array( '<a href="'.$hrefdoc.'"><b>Consulter la version html de cette annexe (avec images)</b></a><br />');}
			else
			{$hrefdoc="https://sites.google.com/a/lescailleries.org/www/annexe_rapport_biodiversite_sans_images.html?attredirects=0";
			$datatitre[]=array( '<a href="'.$hrefdoc.'"><b>Consulter la version html de cette annexe (sans images)</b></a><br />');}

			$hrefdoc="http://www.lescailleries.org";
			$datatitre[]=array( '<a href="'.$hrefdoc.'"><b>Visiter le site web public des Cailleries</b></a><br />');
			$this->file_write_tableau($file, $datatitre);
			$res_legende.= '<b>'. $tbl->render($datatitre, 0, "recordlist").'</b>';

			/*
			 if (!empty($message_ordre_manquant))
			 {
			 $datatitre=array();
			 $datatitre[]=array('Espèces non rattachées à un Ordre : ');
			 $this->file_write_tableau($file, $datatitre);
			 $res_message_ordre_manquant =  '<b>'.$tbl->render($datatitre, 0, "recordlist").'</b>';
			 $this->p($message_ordre_manquant);
			 $this->file_write_tableau($file, $message_ordre_manquant);
			 $res_message_ordre_manquant.=$tbl->render($message_ordre_manquant,0,"recordlist");
			 }

			 */

			fclose($file);
			$size=filesize($filename);
			$file = @ fopen($filename, "rb");
			$filecontent = @ fread($file, $size);
			@ fclose($file);
			$filecontent = base64_encode($filecontent);
			$fileextension = strtolower(substr($filename, strrpos($filename, '.') + 1, strlen($filename)));
			$user = getUser();
			$userid = $user["id"];
			$db = & atkGetDb();
			$data1=$db->getrows("Select id_individu from app_utilisateur where id=$userid");
			$idindividu=$data1[0]["id_individu"];
			$id_record=$db->nextid('seq_individu_document');
			$db->query("INSERT into individu_document
		(id,
						 id_individu,
						 libelle,
						 id_type_document ,
						 file_name,
						 file_extension,
						 file_size,
						 file_content,
						 id_creation,
						 id_modification,
						 date_creation,
						 date_modification)
						  VALUES ( $id_record,
							'$idindividu',
						 '$filenameshort', 
						 '142' ,
						 '$filenameshort',
						 '$fileextension',
						 '$size',
						'$filecontent',
						'$userid',
						'$userid'
						,UTC_TIMESTAMP(),
						 UTC_TIMESTAMP())");

			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("style.css"));
			$page->addContent($res_en_tete);
			$page->addContent($res_legendes);
			$page->addContent($res_especes);
			$page->addContent($res_cumul);
			$page->addContent($res_observations);
			$page->addContent($res_protections);
			$page->addContent($res_listesrouges);
			$page->addContent($res_especesdeterminantes);
			$page->addContent($res_legende);
			$id_record=$db->nextid('seq_individu_document');
			$filecontent = base64_encode($page->render(atktext('rapport biodiversité'), true,'', '<base target="_blank">'));
			$size=strlen($filecontent);
			$filenameshort='annexe_rapport_biodiversite';
			$db->query("INSERT into individu_document
		(id,
						 id_individu,
						 libelle,
						 id_type_document ,
						 file_name,
						 file_extension,
						 file_size,
						 file_content,
						 id_creation,
						 id_modification,
						 date_creation,
						 date_modification)
						  VALUES ( $id_record,
							'$idindividu',
						 '$filename2', 
						 '142' ,
						 '$filename2',
						 'html',
						 '$size',
						'$filecontent',
						'$userid',
						'$userid'
						,UTC_TIMESTAMP(),
						 UTC_TIMESTAMP())");

			//			$page->addContent($res_message_ordre_manquant);
			// render($title=null, $flags=HTML_STRICT,$extrabodyprops="", $extra_header="")
			$output->output($page->render(atktext('rapport biodiversité'), true,'', '<base target="_blank">'));
			//			return;

		}

	}

	function traitement_tableau_protection($type='Protection',$dataprotections, $dataprotections_especes,$image_o_n)
	{
		$col_regne=1;
		$col_classe=2;
		$col_ordre=3;
		$col_famille=4;
		$col_nom_complet=5;
		if ($image_o_n=='oui')
		{$col_image=6;
		$col_nom_francais=7;
		$col_listes=8;
		$col_descripteur_statuts=9;}
		else
		{
			$col_nom_francais=6;
			$col_listes=7;
			$col_descripteur_statuts=8;}
			$tableauprotections=array();
			ksort($dataprotections);
			//			$this->p($dataprotections);
			// Listes des protections
			$rang=array();
			$rang[]="<b>#</b>";
			$rang[]="<b>".$type."</b>";
			$rang[]="<b>Article</b>";
			$rang[]="<b>Statut</b>";
			$rang[]="<b>Dépt.</b>";
			$rang[]="<b>Espèces<br />observées</b>";
			$tableauprotections[]=$rang;
			$compteur=0;
			foreach ($dataprotections as $k=>$v)
			{
				$ligne=str_replace('|', '@', $k).'@'.$v;
				$rang=array();
				++$compteur;
				$rang[]=$compteur;
				$token = strtok($ligne, "@");
				while ($token != false)
				{
					$rang[]=str_replace('()','',$token);
					$token = strtok("@");
				}
				$tableauprotections[]=$rang;
			}
				
			//									if (count($tableauprotections)>0) $this->p($dataprotections);
				
			// Listes des espèces ayant une protection
			$tableauprotections_especes=array();
			ksort($dataprotections_especes);
			$rang=array();
			$rang[]="<b>#</b>";
			$rang[]="<b>Règne</b>";
			//			$rang[]="<b>Phylum</b>";
			$rang[]="<b>Classe</b>";
			$rang[]="<b>Ordre</b>";
			$rang[]="<b>Famille</b>";
			//			$rang[]="<b>Nom binomial</b>";
			$rang[]="<b>Nom<br />complet</b>";
			if ($image_o_n=='oui') $rang[]="<b>Image</b>";
			$rang[]="<b>Nom<br />francais</b>";
			$rang[]="<b>Protections</b>";
			//			$rang[]="<b>Article</b>";
			$rang[]="<b>Descripteur<br />statuts</b>";
			//$this->p($dataprotections_especes);
			$tableauprotections_especes[]=$rang;
			$compteur=0;
			foreach ($dataprotections_especes as $k=>$v)
			{
				++$compteur;

				foreach ($v as $numprot=>$statut)
				{
					$champ=0;
					$ligne=$k.'@'.$statut[1].'@'.$statut[3].'@'.$statut[2];
					$ligne=str_replace('@@', '@ @', $ligne);
					//					$this->p($ligne);
					$rang=array();
					$rang[]=$compteur;
					$token = strtok($ligne, "@");
					while ($token != false)
					{
						$champ++;
						if (($champ==8 && $image_o_n!='oui') || ($champ==9 && $image_o_n=='oui') )
						{
							$tokenplusun=strtok("@");
							$tokenplusun=trim($tokenplusun);
							if ($tokenplusun=='' )
							{$token=$token;}
							else
							{$token=$token.'<br />'.$tokenplusun;}
							$champ++;
						}
						if ($champ==5)
						{}
						else
						{	$rang[]=$token;}
						$token = strtok("@");
					}
					//				$this->p($rang);
					$rang[$col_listes]=$this->decoupe_affichage_colonne($rang[$col_listes], 40);
					$rang[$col_descripteur_statuts]=$this->decoupe_affichage_colonne($rang[$col_descripteur_statuts], 50);
					$rang[$col_nom_complet]=$this->decoupe_affichage_colonne($rang[$col_nom_complet], 40);

					$tableauprotections_especes[]=$rang;
				}

			}
			$retour_tableau=array();
			$retour_tableau["type"]=$this->report_writer($tableauprotections,1,1);
			if ($image_o_n=='oui')
			{$retour_tableau["especes"]=$this->report_writer($tableauprotections_especes,0,7);}
			else
			{$retour_tableau["especes"]=$this->report_writer($tableauprotections_especes,0,6);}
			return $retour_tableau;
	}



	function timeinfo($texte, $file)
	{
		return true;
		$texte='"'.'TIME - '.$texte.' : '.gmdate('c').'";
			';
		//			$this->p($texte);
		fwrite( $file,$texte);
	}

	function file_write_tableau($file, $tableau)
	{
		for ($i = 0; $i < count($tableau); $i++)
		{
			$this->file_write_row($file, $tableau[$i]);
		}
		$this->file_write_row($file,'
');
	}

	function file_write_row($file, $row)
	{		for ($i = 0; $i < count($row); $i++)
	{
		$enreg.= '"' . $row[$i] . '"';
		$enreg.= ',' ;
	}
	$enreg=substr($enreg,0,strlen($enreg)-1).';
	';
	$enreg=str_replace('<br />','
',$enreg);
	$enreg=str_replace('	','',$enreg);
	$enreg=str_replace('&nbsp;',' ',$enreg);

	fwrite($file, $enreg);
	}

	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		$view = $this->getView();
		if ($view == "tout") {
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "a_verifier") {
			$this->addFilter("biodiversite_observation.id in (select distinct id_observation from biodiversite_observation_detail where a_verifier_o_n='1')");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "verifie") {
			$this->addFilter("biodiversite_observation.id not in (select distinct id_observation from biodiversite_observation_detail where a_verifier_o_n='1')");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		return $handler->action_admin();
	}

	/**
	 * Register some javascript that are used by the scheduler module
	 */
	function registerFormScripts()
	{
		return true;
		$page = &$this->getPage();
		//		$page->register_script(atkConfig("atkroot")."atk/javascript/dhtml_formtools.js");
		$page->register_script(moduleDir("biodiversite")."javascript/biodiversite.js");
		$page->register_loadscript("change_id_type_localisation();");
	}

	/**
	 * Customer edit action to register the javascripts
	 *
	 * @param object $handler
	 * @return string Edit apge
	 */
	function action_edit(&$handler)
	{
		$this->registerFormScripts();
		return $handler->action_edit();
	}

	/**
	 * Customer add action to register the javascripts
	 *
	 * @param object $handler
	 * @return string add page
	 */
	function action_add(&$handler)
	{
		$this->registerFormScripts();
		return $handler->action_add();
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
		$mraactions['rapport'] = "rapport";
		$mraactions['rapport_sans_image'] = "rapport_sans_image";
		$mraactions['marquer_a_verifier_cdref'] = "marquer_a_verifier_cdref";
		$mraactions['forcer_cdref'] = "forcer_cdref";
		//				$mraactions['rapport_sans_image_protection'] = "rapport_sans_image_protection";
		//		$mraactions['rapport_variante_protection'] ="rapport_variante_protection";
		//		$mraactions['rapport_variante_protection_sans_image'] ="rapport_variante_protection_sans_image";
		//		$mraactions['mise_a_jour_inpn'] ="mise_a_jour_inpn";
	}
	function rowColor($record)
	{		$db = & atkGetDb();
	$rows = $db->getrows("select count(a_verifier_o_n) as nombre from biodiversite_observation_detail
			 where a_verifier_o_n='1' and id_observation ='" . $record["id"] . "' ");
	if ($rows[0]["nombre"]>0) {
		return "Orange";
	} else {
		return '';
	}
	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$filtre=$this->m_postvars["atkfilter"];
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="Orange"> <b> A vérifier </b></font>';
		$view = $this->getView();
		$retour_a_verifier=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=a_verifier', 'Observations à vérifier') ;
		$retour_verifie= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=verifie', 'Observations vérifiées') ;
		$retour_tout= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=tout', 'Tout')  ;
		$db = & atkGetDb();
		if ($filtre=='')
		{
			$rows = $db->getrows("select count(distinct id_observation) as nombre from biodiversite_observation_detail where
			 biodiversite_observation_detail.a_verifier_o_n='1' ");
		}
		else
		{
			$rows = $db->getrows("select count(distinct id_observation) as nombre from biodiversite_observation_detail, biodiversite_observation where ".$filtre." and
	biodiversite_observation.id=biodiversite_observation_detail.id_observation and 
			 biodiversite_observation_detail.a_verifier_o_n='1' ");
		}
		$nombre_a_verifier=$rows[0]["nombre"]	;
		if ($filtre=='')
		{
			$rows = $db->getrows("select count(distinct id) as nombre from biodiversite_observation where
		biodiversite_observation.id not in (select distinct id_observation from biodiversite_observation_detail where a_verifier_o_n='1')");
		}
		else
		{
			$rows = $db->getrows("select count(distinct id) as nombre from biodiversite_observation where ".$filtre." and
		biodiversite_observation.id not in (select distinct id_observation from biodiversite_observation_detail where a_verifier_o_n='1')");
		}
		$nombre_verifie=$rows[0]["nombre"]	;
		if ($filtre=='')
		{$rows = $db->getrows("select count(id) as nombre from biodiversite_observation ");

		}
		else
		{$rows = $db->getrows("select count(id) as nombre from biodiversite_observation where ".$filtre."");}
		$nombre_tout=$rows[0]["nombre"]	;
		$retour='Sélection :  ';
		if ($view == "tout")
		{$retour.= "<b>Tout(".$nombre_tout.')</b>|'.$retour_a_verifier.'('.$nombre_a_verifier.')|'.$retour_verifie.'('.$nombre_verifie.')';}
		if ($view == "a_verifier")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.'<b>Observations à vérifier('.$nombre_a_verifier.')</b>|'.$retour_verifie.'('.$nombre_verifie.')';}
		if ($view == "verifie")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_a_verifier.'('.$nombre_a_verifier.')|'.'<b>Observations vérifiées('.$nombre_verifie.')</b>';}

		$retour.='<br>';

		return '</b>'.$legende .'<br />'.$retour.'<b>';
		return $legende .$retour;
	}
	function adminHeader() {
	$retour=parent::adminHeader();
		return $retour.$this->adminFooter();
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "tout";
		}
		return $view;
	}
	function id_observateur_display($record, $mode) {
		(!empty($record["id_observateur"])) ? $retour=$this->descripteur_individu($record["id_observateur"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function album_photos_display($record, $mode) {
		return $this->decoupe_affichage_colonne($record["album_photos"], 50);
	}


	function id_organisme_observateur_display($record, $mode) {
		(!empty($record["id_organisme_observateur"])) ? $retour=$this->descripteur_organisme($record["id_organisme_observateur"]["id"],'n') : $retour="";
		return $retour;
	}}
	?>