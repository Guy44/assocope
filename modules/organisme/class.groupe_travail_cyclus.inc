<?php

useattrib("scheduler.dummydurationattribute");
class groupe_travail_cyclus extends assMetaNode {
	var $table = "organisme_groupe_travail_cyclus";
	var $m_minute_step = 5;
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function groupe_travail_cyclus() {

		$time = "09:00";
		$user_eventtime="09";
		for($i=0;$i<60;$i+=$this->m_minute_step)
		{
			$m_arr_minute_step[] = sprintf("%02d",$i);
		}
		if ($time!="")
		{
			$default_start_time = $time; // passed from the url.
			$default_end_time = strftime("%H:%M", mktime(substr($time,0,2), substr($time,3,2)+$user_eventtime)); // endtime is half an hour later than starttime by default
		}
		else
		{
			$default_start_time = strftime("%H:%M");
			$default_end_time = strftime("%H:%M", mktime(substr($default_start_time,0,2),substr($default_start_time,3,2)+$user_eventtime));
		}

		$this->atkMetaNode();
		$this->atkNode("groupe_travail_cyclus", NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id_groupe_travail",
				"id_scheduler_cyclus",
				"id_type_rencontre",
				"id_type_fonction",
				"id_lieu_rencontre",
				'sauf_vacances_o_n',
				'starttime',
				'endtime',
				'duration',
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$gt=$this->add(new atkManyToOneRelation("id_groupe_travail", "organisme.groupe_travail", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),100);
				$this->add(new atkManyToOneRelation("id_scheduler_cyclus", "scheduler.scheduler_cyclus", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_OBLIGATORY ),200);
				$this->add(new atkManyToOneRelation("id_type_rencontre", "table.type_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY), 300);
				$this->add(new atkManyToOneRelation("id_type_fonction", "table.fonction", AF_SEARCHABLE | AF_RELATION_AUTOLINK), 310);
				$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.lieu_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_RELATION_AUTOCOMPLETE),400);
				$this->add(new atkBoolAttribute("sauf_vacances_o_n"),500);
				$this->add(new atkTimeAttribute("starttime", 0, 23, $m_arr_minute_step, $default_start_time, AF_TIME_STRING),600);
				$this->add(new atkTimeAttribute("endtime", 0, 23, $m_arr_minute_step, $default_end_time, AF_TIME_STRING|AF_FORCE_LOAD|AF_HIDE_VIEW|AF_HIDE_ADD|AF_HIDE_EDIT|AF_HIDE_LIST),700)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
				$this->add($duration_attr = new dummydurationattribute('duration'),800);
				$duration_attr->addOnChangeHandler('change_duration(newvalue)');
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setOrder("date_modification");


	}
function updateEndDate(&$rec)
	{
		if($rec['duration']!=-1)
		{
			$enddate = mktime($rec["starttime"]["hours"],$rec["starttime"]["minutes"],$rec["starttime"]["seconds"]);
			$enddate+=$rec['duration']*60;
			$rec['endtime']['hours']=date("H",$enddate);
			$rec['endtime']['minutes']=date("i",$enddate);
			$rec['endtime']['seconds']=date("s",$enddate);

		}
	}
	function initial_values()
	{
		$initial=array();
		$forceList = (isset($this->m_postvars['atkfilter'])) ? decodeKeyValueSet($this->m_postvars['atkfilter']) : array();
//		$this->p($forceList);

		$node = &atkGetNode("organisme.groupe_travail");
		$selector = sprintf("`organisme_groupe_travail`.`id`='%d'", $forceList["id_groupe_travail.id"]);
		$rec = $node->selectDb($selector, "", "", "", array( "id_type_rencontre", "id_type_fonction","id_lieu_rencontre"));
		$initial_values = parent::initial_values();
//		$initial_values["sauf_vacances_o_n"] = $rec[0]['sauf_vacances_o_n'];
		$initial_values["id_type_rencontre"]= $rec[0]['id_type_rencontre'];
		$initial_values["id_type_fonction"] = $rec[0]['id_type_fonction'];
		$initial_values["id_lieu_rencontre"]= $rec[0]['id_lieu_rencontre'];
//		$initial_values["starttime"] = substr($rec[0]['starttime'],0,2);		
//		$initial_values["endtime"] = substr($rec[0]['endtime'],0,2);	
		return $initial_values;
	}



	function duration_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = $this->getAttribute("duration");
		$ret= $attrib->edit($record,$fieldprefix,$mode);
		$ret.='<span id="endtime" style="display: none;">';
		$attrib = $this->getAttribute("endtime");
		$ret.= $attrib->edit($record,$fieldprefix,$mode);
		$ret.='</span>';
		return $ret;
	}

	function duration_display($record,$mode)
	{
		$attrib = $this->getAttribute("duration");
		$ret= $attrib->display($record,$mode);
		if($record['duration']==-1)
		{
			$attrib = $this->getAttribute("endtime");
			$ret.= $attrib->display($record,$mode);
		}
		return $ret;
	}
	function endtime_validate(&$record, $mode)
	{

		if ($record["endtime"]["hours"] < $record["starttime"]["hours"])
		{
			triggerError($record, "endtime", "error_time");
		}
		elseif ($record["endtime"]["hours"] == $record["starttime"]["hours"])
		{
			if ($record["endtime"]["minutes"] <= $record["starttime"]["minutes"])
			{
				triggerError($record, "endtime", "error_time");
			}
		}

	}

	function end_choice_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = &$this->getAttribute("end_choice");
		$attrib->setClickableLabel(false);
			
		$attrib->addOption(atktext("Sans fin",'scheduler'),1);
			
		$enddate = &$this->getAttribute("cyclus_enddate");
		$attrib->addOption(atktext('Date de fin','scheduler').' '.$enddate->edit($record,$fieldprefix,$mode),2);

		$times = &$this->getAttribute("cyclus_times");
		$attrib->addOption($times->edit($record,$fieldprefix,$mode).' '.atktext('fois','scheduler'),3);
		return $attrib->edit($record,$fieldprefix,$mode);
	}
	function preAdd(&$rec)
	{


			switch($rec['end_choice'])
			{
				case 1: $clearfields[]='cyclus_enddate';
				$clearfields[]='cyclus_times';
				break;
				case 2: $clearfields[]='cyclus_times';
				break;
				case 3: $clearfields[]='cyclus_enddate';
				break;
			}


			$this->emptyFields($rec,$clearfields);
		$this->updateEndDate($rec);
//			$this->setLastDate($rec);
			parent :: preAdd($rec);
			return true;
	}
	function preUpdate(&$rec)
	{
		$db = & atkGetDb();
		$this->updateEndDate($rec);
		$endtime=$rec["endtime"]["hours"].':'.$rec["endtime"]["minutes"];
	$id_scheduler_cyclus=$rec["id_scheduler_cyclus"]["id"];
		$data = $db->query("UPDATE organisme_groupe_travail_cyclus
		 set 
		 endtime='". $endtime."',
		  id_scheduler_cyclus='". $id_scheduler_cyclus."'
		 where id=". $rec["id"]." ");
		parent :: preUpdate($rec);
		return true;
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

	function action_add(&$handler)
	{
		$this->registerFormScripts();
		return $handler->action_add();
	}
	function action_edit(&$handler)
	{
		$this->registerFormScripts();
		return $handler->action_edit();
	}
	function registerFormScripts()
	{
		$page = &$this->getPage();
		$page->register_script(atkConfig("atkroot")."atk/javascript/dhtml_formtools.js");
		$page->register_script(moduleDir("scheduler")."javascript/scheduler.js");
		$page->register_loadscript(" change_duration()");
	}


	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}


}

?>