<?php
atkimport("atk.assmetanode");
class type_langue extends assMetaNode {
	var $table = "type_langue";
	function meta(& $policy) {
		$policy->addFlags("libelle_francais","libelle_anglais", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_langue() {
		$this->atkMetaNode();
		$this->atkNode("type_langue",  NF_ADDAFTERADD |NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->m_securityMap["charger_schema"] = "view";
		$this->m_securityMap["charger_attributs"] = "view";
		$this->m_securityMap["charger_atk"] = "view";
		$this->m_securityMap["charger_application"] = "view";
		$this->setIndex("libelle_francais");
		$this->setOrder("libelle_francais");
	}
	function descriptor_def() {
		return "[libelle_francais]";
	}
	function dispatch($postvars, $fullpage=true)
	{


		if ($postvars['atkaction']=='edit' || $postvars['atkaction']=='view' )
		{        $atkselect = $postvars["atkselector"];
		if (($atkselect != "") && isset($atkselect))
		{
			$langueid = sscanf($atkselect, "type_langue.id='%d'");
			$langueId = $langueid[0];
			$this->RecentUseProcess('langue', $langueId);
		}
		}
		else
		{


			$this->RecentUseRefresh('langue');
		}

		return parent::dispatch($postvars, $fullpage);
	}
	function action_charger_schema() {
		global $g_user;
		$id_langue = $this->m_postvars["id"];
		$dbconfig = atkconfig("db");
		$base_assocope=$dbconfig["default"]["db"];
		$dbschema = & atkGetDb("schema");
		$dbassocope = & atkGetDb();
		$sql="SELECT TABLE_NAME FROM TABLES WHERE TABLE_SCHEMA='$base_assocope'";
		$tablenames = $dbschema->getrows($sql);
		$nombre_tables=0;
		$nombre_champs=0;
		$nombre_champs_traites=0;
		$userid = $g_user["id"];
		$res="";
		if (count($tablenames) == 0) {
			$res="Pas de table.";
		} else {
			$requete = 'DELETE FROM  app_traduction WHERE id_type_traduction="7" ';
			$dbassocope->query($requete);
			for ($i = 0; $i < count($tablenames); $i++) {
				$nomtable = $tablenames[$i]["TABLE_NAME"];
				$sql = "SELECT id from app_traduction where id_type_traduction='8' and nom_table='$nomtable'";
				$data150=$dbassocope->getrows($sql);
				if (count($data150) ==0)
				{$sql = 'INSERT INTO app_traduction
												 ( id, id_type_langue,id_type_traduction,nom_table,nom_noeud,id_creation, date_creation,id_modification, date_modification)   
						  VALUES
						   		( '.$dbassocope->nextid("seq_app_traduction").','.$id_langue .',"8","'.$nomtable.'","'.$nomtable.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',UTC_TIMESTAMP() )
									';
				$dbassocope->query($sql);
				}
					
				$nombre_tables+=1;
				$sql="SELECT COLUMN_NAME, COLUMN_TYPE  FROM COLUMNS WHERE TABLE_SCHEMA='$base_assocope' and TABLE_NAME='$nomtable'
				 ";
				$columnnames = $dbschema->getrows($sql);
				if (count($columnnames) == 0) {

				} else {
					for ($j = 0; $j < count($columnnames); $j++) {
						$nomcolumn = $columnnames[$j]["COLUMN_NAME"];
						$typecolonne = $columnnames[$j]["COLUMN_TYPE"];
						$nombre_champs+=1;
						// Vérifier dans traduction, si absent insérer avec code langue
						$sql='SELECT nom_table FROM app_traduction WHERE id_type_langue='.$id_langue.' and nom_table="'.$nomtable.'" and texte_source="'.$nomcolumn .'"';
						$data = $dbassocope->getrows($sql);
						if (count($data) == 0)
						{

							$requete = 'INSERT INTO app_traduction
												 ( id, id_type_langue,id_type_traduction,nom_table,type_colonne, nom_module,nom_noeud,texte_source,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$dbassocope->nextid("seq_app_traduction").','.$id_langue .',"7","'.$nomtable.'","'.$typecolonne.'",null,"","'.$nomcolumn.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
							$dbassocope->query($requete);
							$nombre_champs_traites+=1;

						}
					}
				}
					
			}
			$res="Nombre de tables : ".$nombre_tables."<br />";
			$res.="Nombre de champs : ".$nombre_champs."<br />";
			$res.="Nombre de champs insérés : ".$nombre_champs_traites."<br />";
			$res.="Chargement du schéma terminé.<br />";
		}
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);


	}

	/*
	 *
	 * Dans chaque module.inc
	 function getGgNodeName()
	 {
	 $res["modulename"]= array("node1", "node2"));
	  
	 }

	 */
	function action_charger_attributs() {
		global $g_user;
		$id_langue = $this->m_postvars["id"];
		$db = & atkGetDb();
		$sql="SELECT traduction_charger_attribut_module_name,
		traduction_charger_attribut_node_name, 
		traduction_charger_attribut_date_dernier_noeud, 
		traduction_charger_attribut_nombre_noeuds_traites, 
		traduction_charger_attribut_termine
		FROM app_globales
		WHERE id=1 ";
		$data = $db->getrows($sql);

		$nombre_champs=0;
		$nombre_actions=0;
		$nombre_attributs=0;
		$nombre_noeuds=0;
		$nombre_champs_traites=0;
		$userid = $g_user["id"];
		$result=atkHarvestModules("getGgNodeName");
		//		$this->p($result);
		$nombre_noeuds_total=count($result);
		$continuer_o_n=false;
		if ($data[0]["traduction_charger_attribut_termine"]=="oui")
		{
			$module_noeud_reprise="";
		}
		else
		{
			$module_noeud_reprise=$data[0]["traduction_charger_attribut_module_name"].".".$data[0]["traduction_charger_attribut_node_name"];
		}
		for($nb =0; $nb<count($result) ; $nb++)
		{
			$nombre_noeuds+=1;
			if ($result[$nb]!=$module_noeud_reprise && $module_noeud_reprise!="" && $continuer_o_n==false)
			{ $nombre_noeuds_traites+=1;
			continue;}
			$continuer_o_n=true;
			$nodetype=explode(".",$result[$nb]);
			$modulename=$nodetype[0];
			$nodename=$nodetype[1];
			$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and nom_module="'.$modulename.'" 
						and nom_noeud="'.$nodename.'" 
				and id_type_traduction="6" 
				and texte_source="'.$nodename.'" ';	
			$data = $db->getrows($sql);
			if (count($data) == 0)
			{
				$requete = 'INSERT INTO app_traduction
			( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source
			,id_creation, date_creation, id_modification, date_modification)   
						  VALUES 		
			( '.$db->nextid("seq_app_traduction").','.$id_langue .',"6","'.$modulename.'","'.$nodename.'","'.$nodename.'",
			'.$userid.',UTC_TIMESTAMP(),'.$userid.',UTC_TIMESTAMP() )

									';
				$db->query($requete);
			}
			$custnode = &getNode($result[$nb]);
			//			echo $nb."<br>";
			//			echo $result[$nb]."<br>";
			//			$this->p($result);
			$attributes = $custnode->getAttributeNames();
			// Attributs

			for ($i = 0; $i < count($attributes); $i++)
			{
				$nombre_champs+=1;
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and nom_module="'.$modulename.'" 
						and nom_noeud="'.$nodename.'" 
				and texte_source="'.$attributes[$i] .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
					$requete = 'INSERT INTO app_traduction
												 ( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"2","'.$modulename.'","'.$nodename.'","'.$attributes[$i].'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
					$db->query($requete);
					$nombre_attributs+=1;
					$nombre_champs_traites+=1;
				}
			}
			// Actions
			$custnode->recordActions(null,$actions,$mraactions);
			// tester si les deux sont bien des tableaux
			$totalactions=array();
			if (is_array($actions) && is_array($mraactions))
			{$totalactions = array_merge($actions, $mraactions);
			}
			elseif (is_array($actions))
			{$totalactions = $actions;}
			elseif (is_array($mraactions))
			{$totalactions = $mraactions;}
			foreach ($totalactions as $k => $v)
			{
				$nombre_champs+=1;
				
				if (stripos($v, "=")!=false)
				{ continue;}
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				
				and id_type_traduction=3
				
				and texte_source="'.$v .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
					$requete = 'INSERT INTO app_traduction
												 ( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_traduit,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"3","","","'.$v.'","'.$v.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
					$db->query($requete);
					$nombre_actions+=1;
					$nombre_champs_traites+=1;
				}
			}
			// pour reprise
			$nombre_noeuds_traites+=1;
			$nombreglobales=$nombre_noeuds_traites.'/'.$nombre_noeuds_total;
			$sql="UPDATE app_globales set traduction_charger_attribut_module_name='$modulename',
		traduction_charger_attribut_node_name='$nodename', 
		traduction_charger_attribut_date_dernier_noeud=UTC_TIMESTAMP(), 
		traduction_charger_attribut_nombre_noeuds_traites='$nombreglobales', 
		traduction_charger_attribut_termine='non' 
		WHERE id=1 ";
			$db->query($sql);
			unset($custnode);
		}
		$sql="UPDATE app_globales set traduction_charger_attribut_module_name='$modulename',
		traduction_charger_attribut_node_name='$nodename', 
		traduction_charger_attribut_date_dernier_noeud=UTC_TIMESTAMP(), 
		traduction_charger_attribut_nombre_noeuds_traites='$nombreglobales', 
		traduction_charger_attribut_termine='oui' 
		WHERE id=1 ";
		$db->query($sql);
		$sql="UPDATE app_traduction
		SET texte_traduit=texte_source
		WHERE (texte_traduit IS NULL OR texte_traduit='') AND (texte_source IS NOT NULL OR texte_source!='' ) AND id_type_traduction in ('2','6') ";
		$db->query($sql);
		$res.="Nombre de champs : ".$nombre_champs."<br />";
		$res.="Nombre de champs insérés : ".$nombre_champs_traites."<br />";
		$res.="Nombre d'attributs : ".$nombre_attributs."<br />";
		$res.="Nombre d'actions : ".$nombre_actions."<br />";
		$res.="Chargement des attributs terminé.<br />";
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);
	}

	function action_charger_atk() {

		global $g_user;
		$id_langue = $this->m_postvars["id"];
		$db = & atkGetDb();
		$sql='SELECT code_iso_639_1 as code_langue FROM type_langue WHERE id='.$id_langue.'';
		$data = $db->getrows($sql);
		$lng=$data[0]["code_langue"];
		$nombre_messages=0;
		$nombre_messages_traites=0;
		$userid = $g_user["id"];
		$path = atkconfig("atkroot")."atk/languages/";
		$file = $path.$lng.".lng";
		if (file_exists($file))
		{
			include($file);
			//			$this->m_cachedlang[$module][$lng] = $$lng;
		}
		else
		{
			echo 'Pas de fichier langue';
			die();
		}
		$key = key($$lng);
		$val = current($$lng);
		reset($$lng);
		while(list ($key, $val) = each ($$lng))
		{
			$nombre_messages+=1;
			$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and id_type_traduction="1" 
				and  texte_source="'.$key .'"';
			$data = $db->getrows($sql);
			if (count($data) == 0)
			{
				$requete = 'INSERT INTO app_traduction
												 ( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_traduit,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"1","","","'.$key.'","'.$val.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
				$db->query($requete);
				$nombre_messages_traites+=1;
			}
		}
		$res.="Nombre de messages : ".$nombre_messages."<br />";
		$res.="Nombre de messages insérés : ".$nombre_messages_traites."<br />";
		$res.="Chargement des messages du noyau Atk terminé.<br />";
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);
	}
	function action_charger_application() {

		global $g_user;
		$id_langue = $this->m_postvars["id"];
		$db = & atkGetDb();
		$sql='SELECT code_iso_639_1 as code_langue FROM type_langue WHERE id='.$id_langue.'';
		$data = $db->getrows($sql);
		$lng=$data[0]["code_langue"];
		$nombre_messages=0;
		$nombre_messages_traites=0;
		$nombre_messages_traites_menu_tooltip=0;
		$nombre_messages_traites_menu=0;
		$nombre_messages_traites_attribut_tooltip=0;
		$nombre_messages_traites_wiki=0;

		$userid = $g_user["id"];
		$path = atkconfig("atkroot")."languages/";
		$file = $path.$lng.".lng";
		if (file_exists($file))
		{
			include($file);
			//			$this->m_cachedlang[$module][$lng] = $$lng;
		}
		else
		{
			echo 'Pas de fichier langue';
			die();
		}
		$key = key($$lng);
		$val = current($$lng);
		reset($$lng);
		while(list ($key, $val) = each ($$lng))
		{
			$nombre_messages+=1;
			if (  substr_count  ( $key , "menu_tooltip_") >0 )

			{
				$key1=str_replace("menu_tooltip_","",$key);
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and id_type_traduction="5" 
				and  texte_source="'.$key1 .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
					$requete = 'INSERT INTO app_traduction
				( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_tt,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"5","","","'.$key1.'","'.$val.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
					$db->query($requete);
					$nombre_messages_traites+=1;
					$nombre_messages_traites_menu_tooltip+=1;
				}
				if (count($data) == 1)
				{			$requete = 'UPDATE   app_traduction
				set texte_tt="'.$val.'",
				id_modification='.$userid.',
				date_modification=UTC_TIMESTAMP()
		WHERE id_type_langue='.$id_langue.'
		 and id_type_traduction="5"
					and  texte_source="'.$key1 .'"
				';

				$db->query($requete);
				$nombre_messages_traites+=1;
				}
			}
			elseif (  substr_count  ( $key , "menu_tooltip_" )==0 && substr_count  ( $key , "menu_" )>0)
			{
				$key2=str_replace("menu_","",$key);
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and id_type_traduction="5" 
				and  texte_source="'.$key2 .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
					$requete = 'INSERT INTO app_traduction
				( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_traduit,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"5","","","'.$key2.'","'.$val.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
					$db->query($requete);
					$nombre_messages_traites+=1;
					$nombre_messages_traites_menu+=1;
				}
				if (count($data) == 1)
				{			$requete = 'UPDATE   app_traduction
				set texte_traduit="'.$val.'",
				id_modification='.$userid.',
				date_modification=UTC_TIMESTAMP()
		WHERE id_type_langue='.$id_langue.'
		 and id_type_traduction="5"
					and  texte_source="'.$key2 .'"
				';

				$db->query($requete);
				$nombre_messages_traites+=1;
				}

			}
			elseif (  substr_count  ( $key , "_tooltip" )>0  && strpos ( $key,"_tooltip") != 5)
			{
				$key3=str_replace("_tooltip","",$key);
				$key3=substr($key3, strpos ( $key3,"_")+1);
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and id_type_traduction="2" 
				and  texte_source="'.$key3 .'"';

				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
				}
				if (count($data)> 0)
				{
					$requete = 'UPDATE   app_traduction
				set texte_tt="'.$val.'",
				id_modification='.$userid.',
				date_modification=UTC_TIMESTAMP()
				WHERE id_type_langue='.$id_langue.'
		 and id_type_traduction="2"
					and  texte_source="'.$key3 .'"
				';
					$db->query($requete);
					$nombre_messages_traites+=1;
					$nombre_messages_traites_attribut_tooltip+=1;
				}
			}
			elseif (  substr_count  ( $key , "wiki_" )>0)
			{
				/* $key4=str_replace("wiki_","",$key);

				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				and id_type_traduction="6"
				and  texte_source="'.$key4 .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
				$requete = 'INSERT INTO app_traduction
				( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_traduit,id_creation, date_creation,
				id_modification, date_modification)
				VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"6","","","'.$key4.'","'.$val.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
				UTC_TIMESTAMP() )
				';
				$db->query($requete);
				$nombre_messages_traites+=1;
				$nombre_messages_traites_wiki+=1;

				}
				*/
			}
			else
			{
				$requete = 'UPDATE   app_traduction
				set texte_traduit="'.$val.'",
				id_modification='.$userid.',
				date_modification=UTC_TIMESTAMP()
		WHERE id_type_langue='.$id_langue.'

					and  texte_source="'.$key .'"
					 and texte_traduit is null
				';
				//		echo $requete;
				//					die();
				$db->query($requete);
				$sql='SELECT id FROM app_traduction WHERE id_type_langue='.$id_langue.'
				
				and  texte_source="'.$key .'"';
				$data = $db->getrows($sql);
				if (count($data) == 0)
				{
					$requete = 'INSERT INTO app_traduction
				( id, id_type_langue,id_type_traduction,nom_module,nom_noeud,texte_source,texte_traduit,id_creation, date_creation,
						 id_modification, date_modification)   
						  VALUES 		( '.$db->nextid("seq_app_traduction").','.$id_langue .',"4","","","'.$key.'","'.$val.'",'.$userid.',UTC_TIMESTAMP(),'.$userid.',
		UTC_TIMESTAMP() )
									';
					$db->query($requete);
				}
				$nombre_messages_traites+=1;
			}
		}
		$res.="Nombre de messages : ".$nombre_messages."<br />";
		$res.="Nombre de messages insérés tooltip menu : ".$nombre_messages_traites_menu_tooltip."<br />";
		$res.="Nombre de messages insérés menu : ".$nombre_messages_traites_menu."<br />";
		$res.="Nombre de messages insérés tooltip attribut : ".$nombre_messages_traites_attribut_tooltip."<br />";
		$res.="Nombre de messages insérés wiki : ".$nombre_messages_traites_wiki."<br />";


		$res.="Nombre de messages insérés : ".$nombre_messages_traites."<br />";
		$res.="Chargement des messages de l\'application.<br />";
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);
	}

}
?>