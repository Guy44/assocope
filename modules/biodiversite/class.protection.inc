<?php
atkimport("atk.assmetanode");
useattrib("development.atgNumberExpressionAttribute");

useattrib("development.atgtextlibelleattribute");
class protection extends assMetaNode {
	var $table = "biodiversite_protection";
	function meta(& $policy) {
		$policy->addFlags("commentaire","id", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function protection() {
		$this->atkMetaNode();
		$this->atkNode("protection", NF_COPY | NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id",
		"descripteur_protection",
		"type_liste",
		"cd_protection",
		"valide_o_n",
		"nombre_de_taxons",
		"taxons_observes",
		"taxons_non_repertories",
		"article",
		"intitule",
		"arrete",
				"niveau",
		"ss_niveau_1",
				"cd_arrete",
				"url",
		"date_arrete",
		"url_inpn",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				//				,
				//			"Taxinomies" => array (
				//				"taxinomie"
				//			)
				), AF_NO_LABEL));
				$this->add(new atkAttribute("id", AF_HIDE_LIST),100);
				$this->add(new atkDummyAttribute("descripteur_protection",0 , AF_HIDE_EDIT),101);
				$this->add(new atkAttribute("type_liste",AF_SEARCHABLE),102);
				$this->add(new atkAttribute("cd_protection", AF_SEARCHABLE),110);
				$this->add(new atkBoolAttribute("valide_o_n"),103);
				$this->add(new atgNumberExpressionAttribute("nombre_de_taxons", ' select count(id) from biodiversite_protection_taxinomie
	 where cd_protection =[table].cd_protection 					', 0, 0),120);
				$this->add(new atgNumberExpressionAttribute("taxons_observes", ' select count(id) from biodiversite_protection_taxinomie
	 where cd_protection =[table].cd_protection 					', 0, 0),121);
				/*				$this->add(new atgNumberExpressionAttribute("taxons_non_repertories", ' SELECT count(cd_ref ) as nombre
				 FROM biodiversite_protection_taxinomie WHERE cd_protection=[table].cd_protection and NOT EXISTS ( SELECT cd_ref FROM biodiversite_taxinomie
				 WHERE biodiversite_protection_taxinomie.cd_ref = biodiversite_taxinomie.cd_ref 			)		', 0, 0),122);
				 */
				$this->add(new atgNumberExpressionAttribute("taxons_non_repertories", ' SELECT count(cd_ref ) as nombre
FROM biodiversite_protection_taxinomie WHERE cd_protection=[table].cd_protection and biodiversite_protection_taxinomie.cd_ref ="99999999"				', 0, 0),122);
				$this->add(new atkTextAttribute("article", array ('rows' => '2'), AF_SEARCHABLE),130);
				$this->add(new atkTextAttribute("intitule", array ('rows' => '2'), AF_SEARCHABLE),140);
				$this->add(new atkTextAttribute("arrete", array ('rows' => '3'), AF_SEARCHABLE),150);
				$this->add(new atkAttribute("cd_arrete", AF_SEARCHABLE),160);
				$this->add(new atkAttribute("niveau", AF_SEARCHABLE,50),104);
				$this->add(new atkAttribute("ss_niveau_1", AF_SEARCHABLE),105);
				$this->add(new atkUrlAttribute("url", AF_POPUP | AF_SEARCHABLE ,200) ,190);
				$this->add(new atkAttribute("date_arrete", AF_SEARCHABLE,20),106);
				$this->add(new atkUrlAttribute("url_inpn", AF_POPUP | AF_SEARCHABLE ,200),210);

				//				$this->add(new atkOneToManyRelation("taxinomie", "biodiversite.taxinomie", "id_protection", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setSecurityAlias("organisme.organisme");
				$this->m_securityMap["recherche_cd_ref"] = "view";
				$this->m_securityMap["recherche_cd_ref_nom_cite_nom_binomial"] = "view";

				$this->m_securityMap["valider"] = "view";
				$this->m_securityMap["invalider"] = "view";
				$this->setOrder("date_modification desc");
	}
	function descriptor_def() {
		return "[cd_protection]";
	}
	function action_valider() {
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$condition=$this->m_postvars["atkselector"];
		foreach ($condition as $valeur)
		{$sql="update biodiversite_protection set
		valide_o_n='1' ,
		id_modification=  $userid,
		date_modification= UTC_TIMESTAMP() 
		  where $valeur ";
		$db->query($sql);}
		$db->commit();
		$this->redirect();
	}
	function action_invalider() {
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$condition=$this->m_postvars["atkselector"];
		//		$this->p($condition);
		foreach ($condition as $valeur)
		{$sql="update biodiversite_protection set
		valide_o_n='0' ,
		id_modification=  $userid,
		date_modification= UTC_TIMESTAMP() 
		  where $valeur ";
		$db->query($sql);
		}
		$db->commit();
		$this->redirect();
	}

	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		$view = $this->getView();
		if ($view == "valide" || $view=="") {
			$this->addFilter(" valide_o_n='1' ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}

		return $handler->action_admin();
	}
	function rowColor($record) {
		if ($record["valide_o_n"] == "0")
		return $this->couleurarchive;
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "valide";
		}
		return $view;
	}

	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive<br /> ';
		if ($view == "valide") {
			return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonvalide', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
		} else {
			return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=valide', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
		}
	}
	function adminHeader() {

		return $this->adminFooter();
	}

	function action_recherche_cd_ref($handler) {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb("association");
		$dbupdate = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id_variable = explode('=', $id_variable);
			$array_id_variable[1] = str_replace("''", "", $array_id_variable[1]);
				
			$db->query("select id, nom_complet_valide from biodiversite_protection_taxinomie
			where (cd_ref='' or cd_ref='99999999') and cd_protection in (select cd_protection from biodiversite_protection where id=" . $array_id_variable[1] . ")");
			if ($db->affected_rows($sql)==0)
			{
				return true;
			} else {
				while ($db->next_record()) {
					$record = $db->m_record;
					$nom_complet=escapeSQL($record["nom_complet_valide"]);

					$nom_complet =trim($nom_complet);
					$nom_complet =strtolower($nom_complet);
					$id=$record["id"];
					$data=$dbupdate->getrows("SELECT distinct t.cd_ref from biodiversite_taxinomie t where lower(inpn_nom_complet)='$nom_complet'");
					if (count($data)>0)
					{
						$cd_ref=$data[0]['cd_ref'] ;
						$dbupdate->query("UPDATE biodiversite_protection_taxinomie
					set cd_ref=$cd_ref, id_modification=$userid, date_modification=UTC_TIMESTAMP()
					  where id=$id ");
					}
					else
					{
						$dbupdate->query("UPDATE biodiversite_protection_taxinomie
					set cd_ref='99999999', id_modification=$userid, date_modification=UTC_TIMESTAMP()  where id=$id ");
						$liste.='Liste : '.$array_id_variable[1].' . Nom complet : '.$nom_complet.'<br />';
					}
				}
					
			}
		}
		$liste.='Opération terminée sur nom complet <br />';
		$liste.=$this->action_recherche_cd_ref_nom_cite_nom_binomial($handler);
		echo $liste;
		die();
	}


	function action_recherche_cd_ref_nom_cite_nom_binomial($handler) {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb("association");
		$dbupdate = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id_variable = explode('=', $id_variable);
			$array_id_variable[1] = str_replace("''", "", $array_id_variable[1]);
			$db->query("select id, nom_cite, nom_complet_valide,  nom_francais_cite from biodiversite_protection_taxinomie
			where (cd_ref='' or cd_ref='99999999') and cd_protection in (select cd_protection from biodiversite_protection where id=" . $array_id_variable[1] . ")");
			if ($db->affected_rows($sql)==0)
			{
				return true;
			} else {
				while ($db->next_record()) {
					$record = $db->m_record;
					$id=$record["id"];
					$nom_binomial=escapeSQL($record["nom_cite"]);
					$nom_binomial =trim($nom_binomial);
					$nom_binomial =strtolower($nom_binomial);
					$nom_complet=escapeSQL($record["nom_complet_valide"]);
					$nom_complet=trim($nom_complet);
					$nom_complet =strtolower($nom_complet);
					if ($nom_binomial!='')
					{
						
						$data=$dbupdate->getrows("SELECT distinct t.cd_ref, t.inpn_nom_complet from biodiversite_taxinomie t where lower(nom_binomial)='$nom_binomial'");
						if (count($data)>0)
						{
							$cd_ref=$data[0]['cd_ref'] ;
							$nom_complet=escapeSQL($data[0]['inpn_nom_complet']) ;
							$dbupdate->query("UPDATE biodiversite_protection_taxinomie
					set cd_ref=$cd_ref,nom_complet_valide='$nom_complet', id_modification=$userid, date_modification=UTC_TIMESTAMP()
					  where id=$id ");
							$miseajourfaite=1;
						}
						else
						{$miseajourfaite=0;}
					}
					else 
				{$miseajourfaite=0;}
							
												if ($miseajourfaite==0)
						 {

						 $pos1=strpos($nom_complet, ' ');
						 $nompartiel=substr($nom_complet,0,$pos1 );
						 $pos2=strpos($nom_complet, ' ',$pos1+1);
						 $nompartiel.=substr($nom_complet,$pos1, $pos2-$pos1);
						 $nom_binomial=ucfirst($nompartiel);
						$dbupdate->query("UPDATE biodiversite_protection_taxinomie
					set cd_ref='99999999', nom_cite='$nom_binomial', id_modification=$userid, date_modification=UTC_TIMESTAMP()  where id=$id ");
						$liste.='Liste : '.$array_id_variable[1].' . Nom binomial : '.$nom_binomial.'<br />';
					}
				}
					
			}
		}
		$liste.='Opération terminée sur nom_binomial<br />';
		return $liste;


	}



	function recordActions($rec, & $actions, & $mraactions) {

		$mraactions['delete'] = "delete";
		$mraactions['valider'] = "valider";
		$mraactions['invalider'] = "invalider";

		global $g_sessionManager;
		$Administrateur_o_n=$g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		if ($Administrateur_o_n=='1')
		{$mraactions['recherche_cd_ref'] = "recherche_cd_ref";
		}
	}
	function nombre_de_taxons_display($record, $mode) {
		if (isset ($record["nombre_de_taxons"])) {
			$ret=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
				'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $record['cd_protection'] . "'"
				), "dispatch.php"), $record["nombre_de_taxons"], SESSION_NESTED);
				if ($record["nombre_de_taxons"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return '0';
		} else {
			return "";
		}
	}
	function taxons_non_repertories_display($record, $mode) {
		if (isset ($record["taxons_non_repertories"])) {
			/*			$ret=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
				'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $record['cd_protection'] . "' and
				biodiversite_protection_taxinomie.cd_ref  in (SELECT cd_ref
				FROM biodiversite_protection_taxinomie WHERE cd_protection='" . $record['cd_protection'] . "' and NOT EXISTS (
				SELECT cd_ref FROM biodiversite_taxinomie
				WHERE biodiversite_protection_taxinomie.cd_ref = biodiversite_taxinomie.cd_ref 			  ))	"
				), "dispatch.php"), $record["taxons_non_repertories"], SESSION_NESTED);
				*/
			$ret=href(dispatch_url("biodiversite.protection_taxinomie", "admin", array (
				'atkfilter' => "biodiversite_protection_taxinomie.cd_protection='" . $record['cd_protection'] . "' and 
biodiversite_protection_taxinomie.cd_ref='99999999'	"
			), "dispatch.php"), $record["taxons_non_repertories"], SESSION_NESTED);
			if ($record["taxons_non_repertories"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
			else return '0';
		} else {
			return "";
		}

	}
	function descripteur_protection_display($record, $mode)
	{

		$retour=$this->descripteur_biodiversite_protection_texte($record["cd_protection"]);
		return $retour;
	}

	function taxons_observes_display($record, $mode) {
		$db = &atkGetDb();
		$id_protection=$record["id"];
		$sql="select od.id as id_detail
	from
	biodiversite_protection bp,
	biodiversite_protection_taxinomie pt,
	biodiversite_observation_detail od,
	biodiversite_taxinomie t,
	biodiversite_observation o
	where
	bp.id=$id_protection
	and bp.cd_protection=pt.cd_protection
	and pt.cd_ref=t.cd_nom
	and t.id=od.id_taxinomie
	and od.id_observation=o.id
	and (
	bp.ss_niveau_1 like concat("."'%#'".",o.code_departement_protection,"."'#%'"." )
	or
	bp.ss_niveau_1 is null)
				";
		$data = $db->getrows($sql);
		$nombre_taxons_observes=count($data);
		if ($nombre_taxons_observes > 0) {
			$in='(';
			for ($i = 0; $i < count($data); $i++) {
				$in.=$data[$i]["id_detail"].',';
			}
			$in=substr($in,0,strlen($in)-1).')';
			$protections= href(dispatch_url("biodiversite.observation_detail", "admin", array (
				'atkfilter' => " biodiversite_observation_detail.id in $in "
			), "dispatch.php"),'<b>'. $nombre_taxons_observes.'</b>', SESSION_NESTED);

			return $protections;
		}
	}

}
?>