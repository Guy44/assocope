<?php
useattrib("development.atgomanytoonerelation");
class groupe_travail_i extends assMetaNode {
	var $table = "individu_groupe_travail";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function groupe_travail_i() {
		$this->atkMetaNode();
		$this->atkNode("groupe_travail_i",  NF_ADD_LINK | NF_TRACK_CHANGES  |NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_groupe_travail", "organisme.groupe_travail", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),100);
		$this->add(new atkExpressionAttribute("organisme_groupe", ' select o.nom from organisme o, organisme_groupe_travail ogt 
		where  ogt.id=[table].id_groupe_travail and ogt.id_organisme=o.id 
					', 0, 0),110);
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
		$this->add(new atgOManyToOneRelation("id_organisme_participant", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
		$this->add(new atkManyToOneRelation("id_role_groupe_travail", "table.type_role_groupe_travail", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ),400);
		$this->add(new atkDateAttribute("date_debut_groupe", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),500);
		$this->add(new atkDateAttribute("date_fin_groupe", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),600);
		$this->add(new atkDateAttribute("date_echeance_mandat", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),550);

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("individu_groupe_travail.id_individu asc, individu_groupe_travail.date_creation DESC");
		global $ATK_VARS, $g_user;
		if ($ATK_VARS["atknodetype"] == "individu.groupe_travail_i" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
			))) {
			if ($this->getView() == "active") {
				$this->addFilter("(individu_groupe_travail.date_fin_groupe IS NULL or individu_groupe_travail.date_fin_groupe='00-00-0000' )");
			}
		}
		//$this->setIndex("libelle");
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}

function id_organisme_participant_display($record, $mode) {
		(!empty($record["id_organisme_participant"])) ? $retour=$this->descripteur_organisme($record["id_organisme_participant"]["id"],'n') : $retour="";
		return $retour;
	}
	
	function organisme_groupe_display($record, $mode) {
		$sql=' select o.id as id_organisme from organisme o, organisme_groupe_travail ogt 
		where  ogt.id="'.$record["id_groupe_travail"]["id"].'" and ogt.id_organisme=o.id';
		$db = & atkGetDb();
		$data = $db->getrows($sql);
		
		(!empty($data["id_organisme_inscrit"])) ? $retour=$this->descripteur_organisme($data["id_organisme_inscrit"],'n') : $retour="";
		return $retour;
/*		if (isset ($record["organisme_groupe"])) {
			$ret= href(dispatch_url("organisme.organisme", "admin", array (
				'atkfilter' => "organisme.nom='" . str_replace("'","\'",$record['organisme_groupe']) . "'"
				), "dispatch.php"), text($record["organisme_groupe"]), SESSION_NESTED);
				return $ret;
		} else {
			return "";
		}
		*/
	}
	
	// GG deb
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
	function rowColor($record) {
		$date_fin = $record["date_fin_groupe"];
		if ($date_fin != "")
return $this->couleurarchive;
	}
	function descriptor_def() {
		return "[id]";
	}
	function action_admin($handler) {
		$view = $this->getView();
		if ($view == "active") {
			$this->addFilter("(individu_groupe_travail.date_fin_groupe IS NULL or individu_groupe_travail.date_fin_groupe='00-00-0000' )");
		}
					global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function adminFooter() {
	  $retour=parent::adminfooter();
	  	$view = $this->getView();
		    $legende='Légende des couleurs : ';
    $legende.='<font color="'. $this->couleurarchive.'"> <b> Archive ';
    if ($view=="active")
    {
      return atktext("onlyactiverecordsareshown")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type))."<br>"
	  .$legende.$retour;
		;
    }
    else
    {
      return atktext("youareinthearchive")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type))."<br>"
	  .$legende.$retour;
	;
    }
	}
/*	   function recordActions($rec, &$actions, &$mraactions)
  {  parent::recordActions($rec, $actions, $mraactions);

 $mraactions['delete'] = "delete";
  }
  */
		function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();
		
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
		$data = $db->getrows("select id_individu from individu_groupe_travail
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}
		
		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
	return true;
	}
		function recordActions($rec, & $actions, & $mraactions) {

		$mraactions['delete'] = "delete";
		}
		
}
?>