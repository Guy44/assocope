<?php
useattrib("development.atgomanytoonerelation");
class correspondant extends assMetaNode {
	var $table = "individu_correspondant";
	function meta(& $policy) {
		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function correspondant() {
		$this->atkMetaNode();
		$this->atkNode("correspondant",  NF_ADD_LINK | NF_TRACK_CHANGES  |NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),110);
		$this->add(new atkManyToOneRelation("id_individu_correspondant", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),120);
		$this->add(new atkManyToOneRelation("id_type_correspondant", "table.type_correspondant", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK),130);
//		$this->add(new atkAttribute("identifiant_externe", AF_SEARCHABLE ,200),140);
//		$this->add(new atkAttribute("identifiant_google_court", AF_SEARCHABLE ,200),150);
//		$this->add(new atkAttribute("picasa_o_n", AF_SEARCHABLE ,1),152);
//		$this->add(new atkAttribute("date_synchronisation_google", AF_SEARCHABLE ,200),155);
//		$this->add(new atkAttribute("prenom_google", AF_SEARCHABLE ,200),160);
//		$this->add(new atkAttribute("second_prenom_google", AF_SEARCHABLE ,200),170);
//		$this->add(new atkAttribute("nom_google", AF_SEARCHABLE ,200),180);
//		$this->add(new atkAttribute("courriel", AF_SEARCHABLE ,200),190);
		
//		$this->add(new atkDateAttribute("date_debut", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),150);
//		$this->add(new atkDateAttribute("date_fin", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),160);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("individu_correspondant.id_individu asc, individu_correspondant.id_individu_correspondant asc");
	

		}
	
/*	function id_individu_correspondant_display($record, $mode)
	{
		return $this->descripteur_individu($record["id_individu_correspondant"]["id"],'n');
	}

	function descriptor_def() {
		return "[id]";
	}
*/
		function preDelete(&$record) 
  {
    if ($record["picasa_o_n"]=="o")
    {
    	echo "Suppression impossible car référencé dans Picasa";
    	die();
    	
    }
    else
    {return true;}
  } 
  
	
	function action_admin($handler) {
					global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function adminFooter() {
	  $retour=parent::adminfooter();
	}
	   function recordActions($rec, &$actions, &$mraactions)
  {  parent::recordActions($rec, $actions, $mraactions);
 $mraactions['delete'] = "delete";
 
  }
		function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();
		
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
		$data = $db->getrows("select id_individu_correspondant from individu_correspondant
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu_correspondant"] . ',';
		}
		
		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
	return true;
	}

	
}
?>