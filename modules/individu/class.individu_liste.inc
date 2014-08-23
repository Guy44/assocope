<?php

class individu_liste extends assMetaNode
{
	var $table="individu_liste";


function meta(&$policy)
  {

	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

	// $policy->setOrder("nom");
}
function individu_liste ()
{
  	$this->atkMetaNode();
  	$this->atkNode("individu_liste", NF_ADD_LINK|NF_MRA |NF_ADDAFTERADD);

	$this->setSecurityAlias("individu.individu");



	$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_liste","profil.liste",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 
	include_once(atkconfig("atkroot")."modules/include/association.inc");	
  }
    function recordActions($rec, &$actions, &$mraactions)
  {  parent::recordActions($rec, $actions, $mraactions);

 $mraactions['delete'] = "delete";
  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
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


}

?>