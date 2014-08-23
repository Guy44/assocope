<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");

class liste  extends assMetaNode
{
	var $table="app_utilisateur_liste";
	function meta(&$policy)
	{

		$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

		$policy->setOrder("libelle");
	}
	function liste()
	{
		$this->atkMetaNode();
		$this->atkNode("liste", NF_ADDAFTERADD | NF_ADD_LINK|NF_TRACK_CHANGES|NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atgNumberExpressionAttribute("population", ' select count(id)
			 from individu_liste il
			where il.id_liste=[table].id
			', 0, AF_TOTAL),NULL, 1);
		$this->add(new atkManyToOneRelation("id_type_liste","table.type_liste",AF_OBLIGATORY|AF_SEARCHABLE|AF_RELATION_AUTOLINK));
		// $this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_OBLIGATORY|AF_SEARCHABLE|AF_RELATION_AUTOLINK));
		$this->add(new atkOneToManyRelation("individus_listes","individu.individu_liste","id_liste",AF_HIDE_LIST));
		$this->m_securityMap["listerpp"] = "view";
		$this->m_securityMap["inscrire_du_presse_papier"] = "view";
		$this->m_securityMap["union"] = "view";
		$this->m_securityMap["intersection"] = "view";
		$this->m_securityMap["difference_1_2"] = "view";
		$this->m_securityMap["difference_2_1"] = "view";
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("date_modification desc ");
	}

	function population_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select count(id)  as nombre from individu_liste
	 where  id_liste = ".$record['id']." ";
		$row = $db->getrows($sql);
		$total=	$row[0]["nombre"];


		$ret= href(dispatch_url("individu.individu_liste", "admin", array (
				'atkfilter' => "individu_liste.id_liste='" . $record['id'] . "'"
				), "dispatch.php"), $total, SESSION_NESTED);
				return $ret;


	}

	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {


		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_individu from individu_liste
				 where id_liste in (select id from app_utilisateur_liste
 where  id in (' . $idrencontres . '))';


		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}

		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
			
		$idorganisme="";
		return true;
	}
	function descriptor_def()
	{
		return "[libelle]";
	}


	function recordActions($rec, &$actions, &$mraactions)
	{  parent::recordActions($rec, $actions, $mraactions);
	$actions["listerpp"] = session_url("dispatch.php?atknodetype=".$this->atkNodeType()."&atkaction=listerpp&atkselector=[pk]", SESSION_NESTED);
	$mraactions['union'] = "union";
	$mraactions['intersection'] = "intersection";
	$mraactions['difference_1_2'] = "difference_1_2";
	$mraactions['difference_2_1'] = "difference_2_1";
	$actions["inscrire_du_presse_papier"]='';
	$mraactions['exportations'] = "exportations";
	 $mraactions['delete'] = "delete";
	}


	function action_exportations() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->traitement_select($select, $idorganisme, $idindividus, $idcotisations);
		$url = dispatch_url("organisme.organisme", "listeecran", array (
			"id" => $idorganisme,
			"idindividus" => $idindividus,
			"idinscriptions" => $idcotisations,
			"atkcode" => '20',
			"atkexport" => 'o'
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
		$sql = 'select libelle from app_utilisateur_liste
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' UNION ';
		}
		$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 7);
			
		$data = $db->query("INSERT into app_utilisateur_liste" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			$sql = 'select distinct id_individu from individu_liste
				 where id_liste in (' . $idlistes . ')';
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$db->query("INSERT into individu_liste" . "
		 (id_liste,id_individu,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_individu"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");

			}
			$this->redirect();;
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
		$sql = 'select libelle from app_utilisateur_liste
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' INTERSECTION ';
		}
		$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 14);
			
		$data = $db->query("INSERT into app_utilisateur_liste" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql = 'select distinct id_individu from individu_liste
				 where id_liste in (' . $idlistes . ')';
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$rang=$db->getrows("SELECT count(id_individu) as compte from individu_liste
				 where id_individu='".$data[$i]["id_individu"]."' and id_liste in ( $idlistes ) ");
				if ($rang[0]["compte"]==$nblistes)
				{	
				$db->query("INSERT into individu_liste" . "
		 (id_liste,id_individu,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_individu"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");

				}}
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
		$sql = 'select libelle from app_utilisateur_liste
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
		$libelleunion="";
		for ($i = 0; $i < count($data); $i++) {
			$libelleunion .= $data[$i]["libelle"] . ' MOINS ';
		}
		$libelleunion = substr($libelleunion, 0, strlen($libelleunion) - 12);
			
		$data = $db->query("INSERT into app_utilisateur_liste" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql ="select distinct id_individu from individu_liste
				 where id_liste = $liste1";
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$rang=$db->getrows("SELECT count(id_individu) as compte from individu_liste
				 where id_individu='".$data[$i]["id_individu"]."' and id_liste in ( $idlistes ) ");
				if ($rang[0]["compte"]==1)
				{	
				$db->query("INSERT into individu_liste" . "
		 (id_liste,id_individu,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_individu"].",$userid,$userid,UTC_DATE(),UTC_DATE())
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
		$sql = 'select libelle from app_utilisateur_liste
				  where  id in (' . $idlistes . ')';
		$data = $db->getrows($sql);
			$libelleunion = $data[1]["libelle"]." MOINS " .$data[0]["libelle"];
		$data = $db->query("INSERT into app_utilisateur_liste" . "
		 (libelle,id_type_liste,id_utilisateur,id_creation, id_modification, date_creation, date_modification)" 
		 . "VALUES
		( '".$libelleunion."','1',$userid,$userid,$userid,UTC_DATE(),UTC_DATE())");

			$data = $db->getrows("SELECT max(id) as numero from app_utilisateur_liste where id_modification=$userid ");
			$id_liste=$data[0]["numero"];
			
			$sql ="select distinct id_individu from individu_liste
				 where id_liste = $liste2";
			$data = $db->getrows($sql);
			for ($i = 0; $i < count($data); $i++) {
				$rang=$db->getrows("SELECT count(id_individu) as compte from individu_liste
				 where id_individu='".$data[$i]["id_individu"]."' and id_liste in ( $idlistes ) ");
				if ($rang[0]["compte"]==1)
				{	
				$db->query("INSERT into individu_liste" . "
		 (id_liste,id_individu,id_creation, id_modification, date_creation, date_modification) 
		VALUES
		( $id_liste,".$data[$i]["id_individu"].",$userid,$userid,UTC_DATE(),UTC_DATE())
		 ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()");

				}}
			$this->redirect();
	}
	
	
	function action_listerpp()
	{
		$array_id_liste=explode('=',$this->m_postvars["atkselector"]);
		$id_liste=$array_id_liste[1];
		$user = getUser();
		$userid=$user["id"];
		$nom_variable="id_individu";
		$db = &atkGetDb();
		$requete="SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='".$userid."' ";
		$data = $db->getrows($requete);

		if ($db->num_rows==0)
		{
			$db->commit();
			$this->redirect();
		}
		foreach ($data as $id_individu )
		{
			$id_individu_1=$id_individu["id_variable"];
			$requete="DELETE FROM individu_liste WHERE id_liste=$id_liste and id_individu=$id_individu_1";
			$db->query($requete);
			$requete="INSERT INTO individu_liste ( id_liste, id_individu,commentaire, id_creation, date_creation, id_modification, date_modification )  " .
   		"VALUES( $id_liste,'$id_individu_1' ,'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
   		ON DUPLICATE KEY UPDATE date_creation=UTC_TIMESTAMP()";
			$db->query($requete);
					
		}
		$requete="SELECT MAX(id) as maxid FROM individu_liste ";
		$data=$db->getrows($requete);
		$maxid=$data[0]["maxid"]+1;
		$requete="UPDATE db_sequence set nextid=$maxid WHERE seq_name= 'seq_individu_liste' ";
		$db->query($requete);
		$db->commit();

		$requete="DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='".$userid."' ";

		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

}

?>