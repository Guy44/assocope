<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");

class liste_organismes  extends assMetaNode
{
	var $table="app_utilisateur_liste_organismes";
	function meta(&$policy)
	{

		$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

		$policy->setOrder("libelle");
	}
	function liste_organismes()
	{
		$this->atkMetaNode();
		$this->atkNode("liste_organismes",  NF_ADDAFTERADD |NF_ADD_LINK|NF_TRACK_CHANGES|NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));

		$this->m_securityMap["listerpp"] = "view";
		$this->m_securityMap["inscrire_du_presse_papier"] = "view";
		$this->m_securityMap["liste_organismes"] = "view";
		$this->m_securityMap["union"] = "view";
		$this->m_securityMap["intersection"] = "view";
		$this->m_securityMap["difference_1_2"] = "view";
		$this->m_securityMap["difference_2_1"] = "view";
		$this->add(new atgNumberExpressionAttribute("population", ' select count(id)
			 from organisme_liste il
			where il.id_liste=[table].id
			', 0, AF_TOTAL),NULL, 1);
		$this->add(new atkManyToOneRelation("id_type_liste","table.type_liste",AF_OBLIGATORY|AF_SEARCHABLE|AF_RELATION_AUTOLINK));
		// $this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_OBLIGATORY|AF_SEARCHABLE|AF_RELATION_AUTOLINK));
		$this->add(new atkOneToManyRelation("organismes_listes","organisme.organisme_liste","id_liste",AF_HIDE_LIST));
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->setIndex("libelle");
	}
	function population_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select count(id)  as nombre from organisme_liste
	 where  id_liste = ".$record['id']." ";
		$row = $db->getrows($sql);
		$total=	$row[0]["nombre"];


		$ret= href(dispatch_url("organisme.organisme_liste", "admin", array (
				'atkfilter' => "organisme_liste.id_liste='" . $record['id'] . "'"
				), "dispatch.php"), $total, SESSION_NESTED);
				return $ret;


	}


	function descriptor_def()
	{
		return "[libelle]";
	}


	function recordActions($rec, &$actions, &$mraactions)
	{  // parent::recordActions($rec, $actions, $mraactions);
		$actions["listerpp"] = session_url("dispatch.php?atknodetype=".$this->atkNodeType()."&atkaction=listerpp&atkselector=[pk]", SESSION_NESTED);
		$mraactions['union'] = "union";
		$mraactions['intersection'] = "intersection";
		$mraactions['difference_1_2'] = "difference_1_2";
		$mraactions['difference_2_1'] = "difference_2_1";
		$mraactions['liste_organismes'] = "liste_organismes";
		 $mraactions['delete'] = "delete";
	}


	function action_liste_organismes() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idorganismes, $idcotisations);
		$url = dispatch_url("organisme.organisme", "liste_organismes", array (
			
			"idorganismes" => $idorganismes,
			
			"atkcode" => 'liste_organismes',
			"atkexport" => 'n'
			));
			header("Location: $url");
			exit;
	}

	function action_union() {

				if (is_array($this->m_postvars["atkselector"]) && count($this->m_postvars["atkselector"])>1 ) {
			$select = $this->m_postvars["atkselector"];
		} else {
			echo 'Vous devez sélectionner au moins deux listes';
			die();
		}
		$db = & atkGetDb();
				$user = getUser();
		$userid=$user["id"];
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';

		}
		$idlistes = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select libelle from app_utilisateur_liste_organismes
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' union ';
		}
			$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 7);
			
		$data = $db->query("INSERT into app_utilisateur_liste_organismes" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste_organismes where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			$sql = 'select distinct id_organisme from organisme_liste
				 where id_liste in (' . $idlistes . ')';
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
	$db->query("INSERT into organisme_liste" . "
		 (id_liste,id_organisme,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_organisme"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");
	
			}
			$this->redirect();
	}
	
		function action_intersection() {

		if (is_array($this->m_postvars["atkselector"]) && count($this->m_postvars["atkselector"])>1 ) {
			$select = $this->m_postvars["atkselector"];
		} else {
			echo 'Vous devez sélectionner au moins deux listes';
			die();
		}
		$db = & atkGetDb();
		$user = getUser();
		$userid=$user["id"];
		$i=0;
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
$i+=1;
		}
		$idlistes = substr($chaineid, 0, strlen($chaineid) - 1);
		$nblistes=$i;
		$sql = 'select libelle from app_utilisateur_liste_organismes
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' INTERSECTION ';
		}
		$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 14);
			
		$data = $db->query("INSERT into app_utilisateur_liste_organismes" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste_organismes where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql = 'select distinct id_organisme from organisme_liste
				 where id_liste in(' . $idlistes . ')';
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$sql="SELECT count(id_organisme) as compte from organisme_liste
				 where id_organisme='".$data[$i]["id_organisme"]."' and id_liste in ( $idlistes ) ";
				$rang=$db->getrows($sql);
//												echo $sql;
	
				if ($rang[0]["compte"]==$nblistes)
				{	
	
					$sql="INSERT into organisme_liste" . "
		 (id_liste,id_organisme,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_organisme"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()";
								
				$db->query($sql);

				}}
//				die();
				
			$this->redirect();
	}
	
function action_difference_1_2() {

		if (is_array($this->m_postvars["atkselector"]) && count($this->m_postvars["atkselector"])>1 ) {
			$select = $this->m_postvars["atkselector"];
		} else {
			echo 'Vous devez sélectionner au moins deux listes';
			die();
		}
		$db = & atkGetDb();
		$user = getUser();
		$userid=$user["id"];
		$i=0;
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
			if ($i==0)
			{
				$liste1=$array_id[1];
			}
		if ($i==1)
			{
				$liste2=$array_id[1];
			}
$i+=1;
		}
		$idlistes = substr($chaineid, 0, strlen($chaineid) - 1);
		$nblistes=$i;
		if ($nblistes>2)
 {
			echo 'Vous ne devez pas sélectionner plus de deux listes';
			die();
		}
		$sql = 'select libelle from app_utilisateur_liste_organismes
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' MOINS ';
		}
		$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 12);
			
		$data = $db->query("INSERT into app_utilisateur_liste_organismes" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste_organismes where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql ="select distinct id_organisme from organisme_liste
				 where id_liste = $liste1";
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$rang=$db->getrows("SELECT count(id_organisme) as compte from organisme_liste
				 where id_organisme='".$data[$i]["id_organisme"]."' and id_liste in ( $idlistes ) ");
				if ($rang[0]["compte"]==1)
				{	
				$db->query("INSERT into organisme_liste" . "
		 (id_liste,id_organisme,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_organisme"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");

				}}
			$this->redirect();
	}
	
	function action_difference_2_1() {

		if (is_array($this->m_postvars["atkselector"]) && count($this->m_postvars["atkselector"])>1 ) {
			$select = $this->m_postvars["atkselector"];
		} else {
			echo 'Vous devez sélectionner au moins deux listes';
			die();
		}
		$db = & atkGetDb();
		$user = getUser();
		$userid=$user["id"];
		$i=0;
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
			if ($i==0)
			{
				$liste1=$array_id[1];
			}
		if ($i==1)
			{
				$liste2=$array_id[1];
			}
$i+=1;
		}
		$idlistes = substr($chaineid, 0, strlen($chaineid) - 1);
		$nblistes=$i;
		if ($nblistes>2)
 {
			echo 'Vous ne devez pas sélectionner plus de deux listes';
			die();
		}
		$sql = 'select libelle from app_utilisateur_liste_organismes
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
			$libelleunion = $data[1]["libelle"]." MOINS " .$data[0]["libelle"];
		$data = $db->query("INSERT into app_utilisateur_liste_organismes" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste_organismes where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql ="select distinct id_organisme from organisme_liste
				 where id_liste = $liste2";
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$rang=$db->getrows("SELECT count(id_organisme) as compte from organisme_liste
				 where id_organisme='".$data[$i]["id_organisme"]."' and id_liste in ( $idlistes ) ");
				if ($rang[0]["compte"]==1)
				{	
				$db->query("INSERT into organisme_liste" . "
		 (id_liste,id_organisme,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_organisme"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");

				}}
			$this->redirect();
	}
	
		
	

	function traitement_select($select, & $idorganisme, & $idorganismes, & $idrencontres) {


		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_organisme from organisme_liste
				 where id_liste in (select id from app_utilisateur_liste_organismes
 where  id in (' . $idrencontres . '))';


		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_organisme"] . ',';
		}

		$idorganismes = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
			
		$idorganisme="";
		return true;
	}



	function action_listerpp()
	{
		$array_id_liste_organismes=explode('=',$this->m_postvars["atkselector"]);
		$id_liste_organismes=$array_id_liste_organismes[1];
		$user = getUser();
		$userid=$user["id"];
		$nom_variable="id_organisme";
		$db = &atkGetDb();
		$requete="SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_organisme' and id_utilisateur='".$userid."' ";
		$data = $db->getrows($requete);

		if ($db->num_rows==0)
		{
			$db->commit();
			$this->redirect();
		}
		foreach ($data as $id_organisme )
		{
			$id_organisme_1=$id_organisme["id_variable"];
			$requete="DELETE FROM organisme_liste WHERE id_liste=$id_liste_organismes and id_organisme=$id_organisme_1";
			$db->query($requete);
			$requete="INSERT INTO organisme_liste ( id_liste, id_organisme,commentaire, id_creation, date_creation, id_modification, date_modification )  " .
   		"VALUES( $id_liste_organismes,'$id_organisme_1' ,'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())";
			$db->query($requete);
		}
		$db->commit();

		$requete="DELETE  FROM tmp_copier_coller where nom_variable='id_organisme' and id_utilisateur='".$userid."' ";

		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

}

?>