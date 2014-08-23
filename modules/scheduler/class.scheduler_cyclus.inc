<?php
userelation("atkonetomanyrelation");
useattrib("atkflagattribute");
useattrib("atkdateattribute");
useattrib("atklistattribute");
useattrib("development.atgtextlibelleattribute");

class scheduler_cyclus  extends assMetaNode
{
	function scheduler_cyclus()
	{
		atkimport("modules.utils.dateutil");
		$month_array = dateutil::monthlist();
		$month_arr_value = array_keys($month_array);
		$month_arr_disp = array_values($month_array);

		$day_arr = array();
		for($i=1;$i<32;$i++) $day_arr[]=$i;
		$this->atkMetaNode();
		$this->atkNode("scheduler_cyclus",NF_ADD_LINK);

		//		$this->add(new atkAttribute("id",AF_PRIMARY|AF_HIDE));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE|AF_NO_LABEL));
		$this->add($recur_attr = new atkListAttribute("recur",array("daily","weekly","monthly","yearly"),array(),AF_OBLIGATORY|AF_NO_LABEL));
		$recur_attr->addOnChangeHandler("change_recur(newvalue);");
		$this->add(new atkDummyAttribute('recur_info','',AF_HIDE_ADD|AF_NO_LABEL));
		$this->add(new atkListAttribute("monthly_day",$day_arr,$day_arr,AF_LIST_NO_NULL_ITEM|AF_NO_TRANSLATION|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute("yearly_day",$day_arr,$day_arr,AF_LIST_NO_NULL_ITEM|AF_NO_TRANSLATION|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute("yearly_month",$month_arr_disp,$month_arr_value,AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute("yearly_month2",$month_arr_disp,$month_arr_value,AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkNumberAttribute("daily_every",AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkNumberAttribute("weekly_every",AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkNumberAttribute("monthly_every",AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkNumberAttribute("monthly_every2",AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute("monthly_month_time",array("first","deuxième","third","fourth","last"),array(1,2,3,4,-1),AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute("yearly_month_time",array("first","deuxième","third","fourth","last"),array(1,2,3,4,-1),AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkFlagAttribute("weekly_weekday",array("sunday","monday","tuesday","wednesday","thursday","friday","saturday"),array(1,2,4,8,16,32,64),'',AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute('monthly_weekday_list',array("sunday","monday","tuesday","wednesday","thursday","friday","saturday"),array(1,2,3,4,5,6,7),AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkListAttribute('yearly_weekday_list',array("sunday","monday","tuesday","wednesday","thursday","friday","saturday"),array(1,2,3,4,5,6,7),AF_LIST_NO_NULL_ITEM|AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		$this->add(new atkRadioAttribute('daily_choice',array(),array(),AF_DISPLAY_VERT|AF_NO_LABEL|AF_NO_TRANSLATION|AF_HIDE_VIEW));
		$this->add(new atkDummyAttribute('weekly_choice','',AF_NO_LABEL|AF_HIDE_VIEW));
		$this->add(new atkRadioAttribute('monthly_choice',array(),array(),AF_DISPLAY_VERT|AF_NO_LABEL|AF_NO_TRANSLATION|AF_HIDE_VIEW));
		$this->add(new atkRadioAttribute('yearly_choice',array(),array(),AF_DISPLAY_VERT|AF_NO_LABEL|AF_NO_TRANSLATION|AF_HIDE_VIEW));
		//		$this->add(new atkRadioAttribute('end_choice',array(),array(),AF_DISPLAY_VERT|AF_NO_TRANSLATION|AF_HIDE_VIEW));
		//		$this->add(new atkDateAttribute("cyclus_enddate", "d F Y","d F Y", 0, 0,AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		//		$this->add(new atkNumberAttribute('cyclus_times',AF_HIDE_VIEW))->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
		//		$this->add(new atkOneToManyRelation("exceptions","scheduler.scheduler_cyclus_not","id"));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
$commentaire = &$this->getAttribute("commentaire");
if (is_object($commentaire))
{$commentaire->setFlags(AF_NO_LABEL);}
		$this->setTable("scheduler_cyclus");
		$this->setSecurityAlias("individu.individu");
	}
	function descriptor_def() {
		return "[libelle]";
	}
	
	/**
	 * Register some javascript that are used by the scheduler module
	 */
	function registerFormScripts()
	{
		$page = &$this->getPage();
		$page->register_script(atkConfig("atkroot")."atk/javascript/dhtml_formtools.js");
		$page->register_script(moduleDir("scheduler")."javascript/scheduler.js");
		$page->register_loadscript("change_recur(); change_duration();");
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
	


	/**
	 * Custom yearly choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for yearly choice
	 */
	function yearly_choice_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = &$this->getAttribute("yearly_choice");
		$attrib->setClickableLabel(false);
		$day = &$this->getAttribute("yearly_day");
		$month = &$this->getAttribute("yearly_month");
		$choice = atktext('every','scheduler').' '.$day->edit($record,$fieldprefix,$mode).' '.$month->edit($record,$fieldprefix,$mode).' ';
		$attrib->addOption($choice,1);
		$month_time = &$this->getAttribute("yearly_month_time");
		$weekday_list = &$this->getAttribute("yearly_weekday_list");
		$month = &$this->getAttribute("yearly_month2");
		$choice = atktext('le','scheduler').' '.$month_time->edit($record,$fieldprefix,$mode);
		$choice.= $weekday_list->edit($record,$fieldprefix,$mode).' '.atktext('de','scheduler').' ';
		$choice.= $month->edit($record,$fieldprefix,$mode);
		$attrib->addOption($choice,2);
		return $attrib->edit($record,$fieldprefix,$mode);
	}

	/**
	 * Custom monthly choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for monthly choice
	 */
	function monthly_choice_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = &$this->getAttribute("monthly_choice");
		$attrib->setClickableLabel(false);
		$day = &$this->getAttribute("monthly_day");
		$every = &$this->getAttribute("monthly_every");
		$choice = atktext('le','scheduler').' '.$day->edit($record,$fieldprefix,$mode).' ';
		$choice.= atktext('tous les','scheduler').' '.$every->edit($record,$fieldprefix,$mode).' '.atktext('months','scheduler');
		$attrib->addOption($choice,1);
			
		$month_time = &$this->getAttribute("monthly_month_time");
		$weekday_list = &$this->getAttribute("monthly_weekday_list");
		$month_every = &$this->getAttribute("monthly_every2");
		$choice =atktext('le','scheduler').' '.$month_time->edit($record,$fieldprefix,$mode);
		$choice.= $weekday_list->edit($record,$fieldprefix,$mode).' '.atktext('tous les','scheduler');
		$choice.= $month_every->edit($record,$fieldprefix,$mode).' '.atktext('months','scheduler');
		$attrib->addOption($choice,2);
		return $attrib->edit($record,$fieldprefix,$mode);
	}

	/**
	 * Custom weekly choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for weekly choice
	 */
	function weekly_choice_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = &$this->getAttribute("weekly_choice");
		$every = &$this->getAttribute("weekly_every");
		$weekday = &$this->getAttribute("weekly_weekday");
		$text = atktext('toutes les','scheduler').' '.$every->edit($record,$fieldprefix,$mode).' '.atktext('weeks','scheduler').' '.atktext('le','scheduler');
		$text.= $weekday->edit($record,$fieldprefix,$mode);
		$attrib->setText($text);
		return $attrib->edit($record,$fieldprefix,$mode);
	}

	/**
	 * Custom daily choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for daily choice
	 */
	function daily_choice_edit($record="",$fieldprefix="",$mode)
	{
		$attrib = &$this->getAttribute("daily_choice");
		$attrib->setClickableLabel(false);
		$every = &$this->getAttribute("daily_every");
		$attrib->addOption(atktext('every','scheduler').' '.$every->edit($record,$fieldprefix,$mode).' '.atktext('days','scheduler'),1);
		$attrib->addOption(atktext("every_workday",'scheduler'),2);
		return $attrib->edit($record,$fieldprefix,$mode);
	}

	/**
	 * Custom end choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for end choice
	 */
	/*
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

		*/
	/**
	 * Display the recurring info
	 *
	 * @param mixed $record Record or Scheduler id
	 * @param string $mode Mode
	 * @return string String with the recurring info
	 */
	function recur_info_display($record,$mode)
	{
		$ret='';
		$ret.=$this->getDailyInfo($record,$mode);
		$ret.=$this->getWeeklyInfo($record,$mode);
		$ret.=$this->getMonthlyInfo($record,$mode);
		$ret.=$this->getYearlyInfo($record,$mode);
		return $ret;
	}
function recur_info_edit($record,$mode)
	{
		$ret='';
		$ret.=$this->getDailyInfo($record,$mode);
		$ret.=$this->getWeeklyInfo($record,$mode);
		$ret.=$this->getMonthlyInfo($record,$mode);
		$ret.=$this->getYearlyInfo($record,$mode);
		return $ret;
	}

	/**
	 * Custom validate for all choices
	 *
	 * @param array $record Record
	 * @param string $mode Mode
	 * @param array $ignoreList Ignorelist
	 * @return boolean Validated or not
	 */
	function validate(&$record, $mode, $ignoreList = array())
	{

		// Add extra obligatory flags when recur is not once
		$valid_recur_types = array("daily","weekly","monthly","yearly");
		$recur = $record['recur'];

		if(in_array($recur,$valid_recur_types))
		{
			switch($recur)
			{
				case 'daily':   if($record['daily_choice']==1)
				{
					$this->makeObligatory('daily_every');
				}
				break;
				case 'weekly':  $this->makeObligatory('weekly_weekday','weekly_every');
				break;
				case 'monthly': if($record['monthly_choice']==1)
				{
					$this->makeObligatory(array('monthly_day','monthly_every'));
				}
				else
				{
					$this->makeObligatory('monthly_month_time','monthly_weekday_list','monthly_every2');
				}
				break;
				case 'yearly':  if($record['yearly_choice']==1)
				{
					$this->makeObligatory('yearly_month', 'yearly_day');
				}
				else
				{
					$this->makeObligatory('yearly_month_time','yearly_weekday_list','yearly_month2');
				}
				break;
			}
			/*		if($record['end_choice']==2)
			 {
				$this->makeObligatory('cyclus_enddate');
				}
				else if($record['end_choice']==3)
				{
				$this->makeObligatory('cyclus_times');
				}
				*/
		}
$record["libelle"]=$this->recur_info_display($record,$mode);
		// Call the original validate method
		return parent::validate($record, $mode, $ignoreList);
	}

	/**
	 * Make attribute Obligatory
	 *
	 * @param string $attribname Attribute name
	 */
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


	/**
	 * Pre add function that will clear all the fields that are not used
	 *
	 * @param array $rec Record
	 * @return boolean
	 */
	function preAdd(&$rec)
	{

		$valid_recur_types = array("daily","weekly","monthly","yearly");
		$recur = $rec['recur'];
		if(in_array($recur,$valid_recur_types))
		{
			switch($recur)
			{
				case 'daily':  if($rec['daily_choice']==1)
				{
					// Don't clear: daily_every
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','weekly_every','monthly_every','monthly_every2',
                                                 'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                                 'monthly_choice','yearly_choice');
				}
				else
				{
					// Clear everything
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'monthly_choice','yearly_choice');
				}
				break;
				case 'weekly': // Don't clear: weekly_weekday, weekly_every
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice','yearly_choice');
					break;
				case 'monthly':if($rec['monthly_choice']==1)
				{
					// Don't clear: monthly_day, monthly_every
					$clearfields = array('yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','yearly_choice');
				}
				else
				{
					// Don't clear: monthly_month_time, monthly_weekday_list, monthly_every2
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every',
                                                 'yearly_month_time','weekly_weekday','yearly_weekday_list',
                                                 'daily_choice','yearly_choice');
				}
				break;
				case 'yearly': if($rec['yearly_choice']==1)
				{
					// Don't clear: yearly_month, yearly_day
					$clearfields = array('monthly_day','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice');
				}
				else
				{
					// Don't clear: yearly_month_time, yearly_weekday_list, yearly_month2
					$clearfields = array('monthly_day','yearly_day','yearly_month','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','weekly_weekday','monthly_weekday_list',
                                               'daily_choice','monthly_choice');
				}
				break;
				default :      // Clear everything
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice','yearly_choice');
					break;

			}

			array_shift($valid_recur_types);
			/*		if(in_array($recur,$valid_recur_types))
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
				}
				*/
			$this->emptyFields($rec,$clearfields);
		}
		parent :: preAdd($rec);
		return true;
	}
	function preUpdate(&$rec)
	{

		$valid_recur_types = array("daily","weekly","monthly","yearly");
		$recur = $rec['recur'];
		if(in_array($recur,$valid_recur_types))
		{
			switch($recur)
			{
				case 'daily':  if($rec['daily_choice']==1)
				{
					// Don't clear: daily_every
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','weekly_every','monthly_every','monthly_every2',
                                                 'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                                 'monthly_choice','yearly_choice');
				}
				else
				{
					// Clear everything
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'monthly_choice','yearly_choice');
				}
				break;
				case 'weekly': // Don't clear: weekly_weekday, weekly_every
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice','yearly_choice');
					break;
				case 'monthly':if($rec['monthly_choice']==1)
				{
					// Don't clear: monthly_day, monthly_every
					$clearfields = array('yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','yearly_choice');
				}
				else
				{
					// Don't clear: monthly_month_time, monthly_weekday_list, monthly_every2
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every',
                                                 'yearly_month_time','weekly_weekday','yearly_weekday_list',
                                                 'daily_choice','yearly_choice');
				}
				break;
				case 'yearly': if($rec['yearly_choice']==1)
				{
					// Don't clear: yearly_month, yearly_day
					$clearfields = array('monthly_day','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice');
				}
				else
				{
					// Don't clear: yearly_month_time, yearly_weekday_list, yearly_month2
					$clearfields = array('monthly_day','yearly_day','yearly_month','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','weekly_weekday','monthly_weekday_list',
                                               'daily_choice','monthly_choice');
				}
				break;
				default :      // Clear everything
					$clearfields = array('monthly_day','yearly_day','yearly_month','yearly_month2','daily_every','weekly_every','monthly_every','monthly_every2',
                                               'monthly_month_time','yearly_month_time','weekly_weekday','monthly_weekday_list','yearly_weekday_list',
                                               'daily_choice','monthly_choice','yearly_choice');
					break;

			}

			array_shift($valid_recur_types);
			/*		if(in_array($recur,$valid_recur_types))
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
				}
				*/
			$this->emptyFields($rec,$clearfields);
		}
		parent :: preUpdate($rec);
		return true;
	}

	/**
	 * Empty fields
	 *
	 * @param array $rec Current record
	 * @param array $fields Array with fields to empty
	 */
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

	/**
	 * Initial values
	 *
	 * @return array Array with initial values
	 */
	function initial_values()
	{
		$initial=array();
		$initial["weekly_weekday"]=0;
		$initial['daily_choice']=1;
		$initial['monthly_choice']=1;
		$initial['yearly_choice']=1;
		//		$initial['end_choice']=1;
		//		$initial['cyclus_enddate']=array('day'=>date("d"),
		//                                       'month'=>date("m"),
		//                                       'year'=>date("Y"));
		$initial["recur"]="monthly";
		return $initial;
	}

	/**
	 * Return daily information
	 *
	 * @param array $record Record
	 * @return string daily information
	 */
	function getDailyInfo($record,$mode)
	{
		$ret = "";
		switch($record['daily_choice'])
		{
			case 1: $every = &$this->getAttribute("daily_every");
			if ($every->db2value($record,$mode)==1)
			{
				$ret=atktext('tous les','scheduler').' '.atktext('days','scheduler');
			}
			else
			{
			$ret=atktext('tous les','scheduler').' '.$every->db2value($record,$mode).' '.atktext('days','scheduler');	
			}
			
			break;
			case 2: $ret=atktext("jours travaillés",'scheduler');
			break;
		}
		return $ret;
	}

	/**
	 * Return weekly information
	 *
	 * @param array $record Record
	 * @return string weekly information
	 */
	function getWeeklyInfo($record,$mode)
	{
		$ret = '';
			
		$every = &$this->getAttribute("weekly_every");
		$weekdays = &$this->getAttribute("weekly_weekday");
		if(!$every->isEmpty($record) && !$weekdays->isEmpty($record))
		{
			if ($every->db2value($record,$mode)==1)
			{$ret=atktext('toutes les','scheduler').' '.atktext('weeks','scheduler');			}
			else
			{$ret=atktext('toutes les','scheduler').' '.$every->db2value($record,$mode).' '.atktext('weeks','scheduler');}
		
			$ret.=' '.atktext('le',"scheduler").' '.$weekdays->display($record,$mode);
		}
		return $ret;
	}

	/**
	 * Return monthly information
	 *
	 * @param array $record Record
	 * @return string monthly information
	 */
	function getMonthlyInfo($record,$mode)
	{
		$ret='';
		switch($record['monthly_choice'])
		{
			case 1:  $day = &$this->getAttribute("monthly_day");
			$every = &$this->getAttribute("monthly_every");
			
						$ret = atktext('le','scheduler').' '.$day->display($record).' ';
if ($every->db2value($record,$mode)==1)
{$ret.= atktext('tous les','scheduler').' '.atktext('months','scheduler');}
else
{$ret.= atktext('tous les','scheduler').' '.$every->db2value($record,$mode).' '.atktext('months','scheduler');}
			break;
			case 2:  $month_time = &$this->getAttribute("monthly_month_time");
			$weekday_list = &$this->getAttribute("monthly_weekday_list");
			$month_every = &$this->getAttribute("monthly_every2");
			$ret = atktext('le','scheduler').' '.$month_time->display($record,$mode);
			$ret.= ' '.$weekday_list->display($record,$mode).' '.atktext('tous les','scheduler').' ';
			if ( $month_every->db2value($record,$mode)==1)
			{$ret.= ' '.atktext('months','scheduler');}
			else
		{$ret.= $month_every->db2value($record,$mode).' '.atktext('months','scheduler');}
			break;
		}
		return $ret;
	}

	/**
	 * Return yearly information
	 *
	 * @param array $record Record
	 * @return string yearly information
	 */
	function getYearlyInfo($record,$mode)
	{
		$ret='';
		switch($record['yearly_choice'])
		{
			case 1: $month = &$this->getAttribute("yearly_month");
			$day = &$this->getAttribute("yearly_day");
			if ($day->display($record,$mode)==1)
			{$ret = atktext('tous les','scheduler').' '.$day->display($record,$mode).' '.$month->display($record,$mode).' ';}
			else
				{$ret = atktext('tous les','scheduler').' '.$month->display($record,$mode).' ';}
			//               $ret.= $day->display($record,$mode);
			break;
			case 2: $month_time = &$this->getAttribute("yearly_month_time");
			$weekday_list = &$this->getAttribute("yearly_weekday_list");
			$month = &$this->getAttribute("yearly_month2");
			$ret= atktext('le','scheduler').' '.$month_time->display($record,$mode);
			$ret.= ' '.$weekday_list->display($record,$mode).' '.atktext('de','scheduler').' ';
			$ret.= $month->display($record,$mode);
			break;
		}
		return $ret;
	}

	/**
	 * Return enddate information
	 *
	 * @param array $record Record
	 * @return string enddate information
	 */
	/*
	 *	function getEndDateInfo($record,$mode)
	 {
		$ret="";
		switch($record['end_choice'])
		{
		case 1: $ret=atktext("Pas de date",'scheduler');
		break;
		case 2: $ret=atktext('Date de fin','scheduler').' ';
		$enddate = &$this->getAttribute("cyclus_enddate");
		$ret.=$enddate->display($record,$mode);
		break;
		case 3: $ret=atktext('Nombre de fois','scheduler').' ';
		$times = &$this->getAttribute("cyclus_times");
		$ret.=$times->display($record,$mode).' '.atktext('times','scheduler');
		break;
		default:$ret="-";
		}
		return $ret;
		}
		*/
}

?>
