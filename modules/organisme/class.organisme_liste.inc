<?php

class organisme_liste extends assMetaNode
{
	var $table="organisme_liste";


function meta(&$policy)
  {

	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

	// $policy->setOrder("nom");
}
function organisme_liste ()
{
  	$this->atkMetaNode();
  	$this->atkNode("organisme_liste", NF_ADD_LINK|NF_MRA |NF_ADDAFTERADD);

	$this->setSecurityAlias("organisme.organisme");



	$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_liste","profil.liste_organismes",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 
	include_once(atkconfig("atkroot")."modules/include/association.inc");	
  }
    function recordActions($rec, &$actions, &$mraactions)
  {  

 $mraactions['delete'] = "delete";
  }
  
    	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {


		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id= explode('=', $id_variable);

			$chaineid.=$array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql = 'select distinct id_individu from individu_liste
				 where id in (' . $idrencontres . ')';


		$data = $db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}

		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
/*			$sql = 'select distinct id_organisme from organisme_liste
				 where id in (' . $idrencontres . ')';
				$data = $db->getrows($sql);
				$idorganisme=$data[0]["id_organisme"];	
				*/	 
		return true;
	}
	
function descriptor_def()
  {
    return "[id_individu]";
  }
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}

?>