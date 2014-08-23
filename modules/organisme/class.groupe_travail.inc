<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
atkimport("modules.scheduler.utils.schedulertools");
useattrib("scheduler.dummydurationattribute");
class groupe_travail extends assMetaNode {
	var $table = "organisme_groupe_travail";
	var $m_minute_step = 5;
	function meta(& $policy) {
		$policy->addFlags("nom", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function groupe_travail() {

/*	$time = "09:00";
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
*/
		$this->atkMetaNode();
		$this->atkNode("groupe_travail", NF_ADD_LINK | NF_EDITAFTERADD | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"nom",
				"id_organisme",
				"objet",
			"id_type_rencontre",
			
				"id_lieu_rencontre",
				"lieu_reunion",
				"participants",
		"id_type_fonction",
				"rencontres",
				"date_debut_groupe",
				"date_fin_groupe",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				,
				 "Recurrence" => array (
				 "recurrences",
		'end_choice',
		"cyclus_enddate",
		'cyclus_times'

		)
	/*	,
				"Sauf" => array (
				 "exceptions"
				 )
				 */

				 ), AF_NO_LABEL));
				 //			$this->add(new atkOneToManyRelation("membre", "individu.groupe_travail_i", "id_groupe_travail", AF_HIDE_LIST));

		$this->add(new atkDummyAttribute("descripteur_groupe_travail",0,AF_HIDE_EDIT ),3);
		$this->add(new atkOneToManyRelation("recurrences", "organisme.groupe_travail_cyclus", "id_groupe_travail"),4);
				 $this->add(new atgTextLibelleAttribute("nom", AF_SEARCHABLE),200);
				 $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),100);
				 $this->add(new atkfckattribute("objet", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
			)),300);
			$this->add(new atkManyToOneRelation("id_type_rencontre", "table.type_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY), 305);
			$this->add(new atkManyToOneRelation("id_type_fonction", "table.fonction", AF_SEARCHABLE | AF_RELATION_AUTOLINK ), 403);

			$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.lieu_rencontre", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_OBLIGATORY| AF_RELATION_AUTOCOMPLETE ),310);
			$this->add(new atgNumberExpressionAttribute("participants", ' select count(id) from individu_groupe_travail
	 where date_fin_groupe is null and id_groupe_travail =[table].id 					', 0, 0),401);
			$this->add(new atgNumberExpressionAttribute("rencontres", ' select count(id) from organisme_rencontre
	 where id_groupe_travail =[table].id 					', 0, 0),405);
			$this->add(new atkAttribute("lieu_reunion", AF_FORCE_LOAD|AF_HIDE ),408);
			//			$this->add(new atkManyToOneRelation("id_type_frequence", "table.type_frequence",  AF_FORCE_LOAD|AF_HIDE| AF_RELATION_AUTOLINK ),500);
			//			$this->add($recurrent_attr = new atkBoolAttribute("recurrent_o_n"),503);
			//			$recurrent_attr->addOnChangeHandler('change_recurrent_o_n(el)');

			//			$this->add(new atkManyToOneRelation("id_scheduler_cyclus", "scheduler.scheduler_cyclus", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),505);
			
			$this->add(new atkRadioAttribute('end_choice',array(),array(),AF_DISPLAY_VERT|AF_NO_TRANSLATION),510);
			$this->add(new atkDateAttribute("cyclus_enddate", "d F Y","d F Y", 0, 0,AF_HIDE_VIEW|AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),512)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
			$this->add(new atkNumberAttribute('cyclus_times',AF_HIDE_VIEW|AF_HIDE_ADD|AF_HIDE_EDIT|AF_FORCE_LOAD),514)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);
//			$this->add(new atkOneToManyRelation("exceptions","scheduler.scheduler_cyclus_not","id_groupe_travail"),525);

			//			$this->add(new atkTimeAttribute("starttime", 0, 23, $m_arr_minute_step, $default_start_time, AF_TIME_STRING),506);
			//			$this->add(new atkTimeAttribute("endtime", 0, 23, $m_arr_minute_step, $default_end_time, AF_TIME_STRING|AF_FORCE_LOAD|AF_HIDE_VIEW|AF_HIDE_ADD|AF_HIDE_EDIT|AF_HIDE_LIST),535)->addDisabledMode(DISABLED_VIEW|DISABLED_EDIT);

			//			$this->add($duration_attr = new dummydurationattribute('duration'),507);
			//			$duration_attr->addOnChangeHandler('change_duration(newvalue)');

			//			$this->add(new atkBoolAttribute("sauf_vacances_o_n"),538);

			//			$this->add(new atkNumberAttribute("lastdate", AF_HIDE|AF_FORCE_LOAD),540);
			//			$this->add(new atkNumberAttribute("times", AF_HIDE|AF_FORCE_LOAD),545);


			$this->add(new atkDateAttribute("date_debut_groupe", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),600);
			$this->add(new atkDateAttribute("date_fin_groupe", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING),700);


			include_once (atkconfig("atkroot") . "modules/include/association.inc");
					$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,20 );
			$this->m_securityMap["creer_rencontre"] = "view";
			$this->m_securityMap["generer_rencontres"] = "view";
			$this->m_securityMap["liste_detaillee"] = "view";
			$this->m_securityMap["liste_simple"] = "view";
			$this->m_securityMap["liste_des_rencontres"] = "view";
			$this->m_securityMap["inscrire_du_presse_papier"] = "view";

			$this->setOrder("organisme_groupe_travail.nom");

			global $ATK_VARS, $g_user;
			if ($ATK_VARS["atknodetype"] == "organisme.groupe_travail" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
				))) {
					if ($this->getView() == "active") {
						$this->addFilter("( organisme_groupe_travail.date_fin_groupe is null or organisme_groupe_travail.date_fin_groupe > CURDATE() )");
					}
				}
					
	}
	/*
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

		*/
	function id_type_fonction_display($record, $mode)
	{
		$attribute = $this->getAttribute("id_type_fonction");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 55);
	}
	function id_lieu_rencontre_display($record, $mode)
	{
		$attribute = $this->getAttribute("id_lieu_rencontre");
		$original = $attribute->display($record, $mode);
		return $this->decoupe_affichage_colonne($original, 55);
	}
	function recurrences_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select sc.libelle as libelle,
		gtc.sauf_vacances_o_n as sauf_vacances,
		gtc.starttime as starttime,
		gtc.endtime as endtime,
		lr.libelle as libelle_lieu,
		l.latitude as latitude,
		l.longitude as longitude
		 from 
		scheduler_cyclus sc,
		organisme_groupe_travail_cyclus gtc LEFT JOIN 
		organisme_lieu_rencontre lr ON gtc.id_lieu_rencontre=lr.id LEFT JOIN
		lieu l ON lr.id_lieu=l.id
		where gtc.id_groupe_travail=".$record["id"]."
		and gtc.id_scheduler_cyclus=sc.id 
		";
		$row = $db->getrows($sql);
		for ($i = 0, $_i = count($row); $i < $_i; $i++) {
			$ret.=$row[$i]["libelle"]." ";
			if ($row[$i]["sauf_vacances"]==1)
			{$ret.="sauf pendant les vacances"." ";}
			$ret.="de ".$row[$i]["starttime"];
			$ret.=" à ".$row[$i]["endtime"];
			//				$ret.= "<br />";
			if (!empty($row[$i]["latitude"]))
			{
				$carte='<font color="ForestGreen"><b>Carte</b></font>';
				$ret.= href("http://maps.google.com/maps?q=".$row[$i]["latitude"].",".$row[$i]["longitude"], "<br /> à ".$row[$i]["libelle_lieu"]."<br />", SESSION_NEW, false, 'target="_blank"') ;
			}
			else
			{
				$ret.="<br /> à ".$row[$i]["libelle_lieu"]."<br />";
			}

		}
		return $this->decoupe_affichage_colonne($ret, 57);
			
	}

	function participants_display($record, $mode) {
		$db = & atkGetDb();
		$sql="select count(id)  as nombre from individu_groupe_travail
	 where  id_groupe_travail = ".$record['id']." ";
		$row = $db->getrows($sql);
		$total=	$row[0]["nombre"];
		$sql="select count(id)  as nombre from individu_groupe_travail
	 where date_fin_groupe is null and id_groupe_travail = ".$record['id']." ";
		$row = $db->getrows($sql);
		$actifs=	$row[0]["nombre"];

		$ret= href(dispatch_url("individu.groupe_travail_i", "admin", array (
				'atkfilter' => "individu_groupe_travail.id_groupe_travail='" . $record['id'] . "'"
				), "dispatch.php"), text($actifs.'/'.$total), SESSION_NESTED);
				return '<font color="Violet"><b>'.$ret.'</font></b>';


	}



	function rencontres_display($record, $mode) {
		if (isset ($record["rencontres"])) {
			$ret=href(dispatch_url("organisme.rencontre", "admin", array (
				'atkfilter' => "organisme_rencontre.id_groupe_travail='" . $record['id'] . "'"
				), "dispatch.php"), text($record["rencontres"]), SESSION_NESTED);
				if ($record["rencontres"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return '0';
		} else {
			return "";
		}
	}

	/**
	 * Custom end choice edit
	 *
	 * @param array $record Record
	 * @param string $fieldprefix Fieldprefix
	 * @param string $mode Mode
	 * @return string Edit for end choice
	 */

	function end_choice_edit($record="",$fieldprefix="",$mode)
	{
		//		$this->p($record);
		$attrib = &$this->getAttribute("end_choice");
		$attrib->setClickableLabel(false);
			
		$attrib->addOption(atktext("Dans un an et un jour",'scheduler'),1);
			
		$enddate = &$this->getAttribute("cyclus_enddate");
		$attrib->addOption(atktext('Date de fin','scheduler').' '.$enddate->edit($record,$fieldprefix,$mode),2);

		$times = &$this->getAttribute("cyclus_times");
		$attrib->addOption($times->edit($record,$fieldprefix,$mode).' '.atktext('fois','scheduler'),3);
		return $attrib->edit($record,$fieldprefix,$mode);
	}
	function validate(&$record, $mode, $ignoreList = array())
	{
		if($record['end_choice']==2)
		{
			$this->makeObligatory('cyclus_enddate');
		}
		else if($record['end_choice']==3)
		{
			$this->makeObligatory('cyclus_times');
		}
		else
		{
			$record['end_choice']="";
			$record['cyclus_enddate']="";
			$record['cyclus_times']="";
		}
		return parent::validate($record, $mode, $ignoreList);
	}
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

	function preAdd(&$rec)
	{
		if($recurrent_o_n=='0')
		switch($rec['end_choice'])
		{
			case 1: $rec['cyclus_enddate']=null;
			$rec['cyclus_times']=null;
			break;
			case 2: $rec['cyclus_times']=null;
			break;
			case 3: $rec['cyclus_enddate']=null;
			break;
		}
		parent :: preAdd($rec);
		return true;
	}

	function preUpdate(&$rec)
	{
		if($recurrent_o_n=='0')
		switch($rec['end_choice'])
		{
			case 1: $rec['cyclus_enddate']=null;
			$rec['cyclus_times']=null;
			break;
			case 2: $rec['cyclus_times']=null;
			break;
			case 3: $rec['cyclus_enddate']=null;
			break;
		}
		// $this->p(  $rec);
		//		 $this->removeSchedulerDates($record['id'],$record);

		$db = & atkGetDb();
		if(!isset($rec["cyclus_enddate"]))
		{$cyclus_enddate='null';}
		else
		{$cyclus_enddate=$this->dateatktodb($rec["cyclus_enddate"]);}
		if(!isset($rec["cyclus_times"]))
		{$cyclus_times="null";}
		else
		{$cyclus_times=$rec["cyclus_times"];}
		$sql="UPDATE organisme_groupe_travail
		 set cyclus_times='". $cyclus_times."',
				 cyclus_enddate='". $cyclus_enddate."',
				 end_choice='". $rec['end_choice']."'

		 where id=". $rec["id"]." ";
		//	echo $sql;
		//		die();

		$db->query($sql);

		parent :: preUpdate($rec);
		return true;
	}
	/*
	 *
	 function setLastDate(&$rec)
	 {
		if ($rec['date_debut_groupe']==null)
		{$rec['lastdate'] = mktime($rec["starttime"]["hours"],$rec["starttime"]["minutes"],$rec["starttime"]["seconds"],gmdate('m'),gmdate('d'),gmdate('Y'));}
		else
		{$rec['lastdate'] = mktime($rec["starttime"]["hours"],$rec["starttime"]["minutes"],$rec["starttime"]["seconds"],$rec["date_debut_groupe"]["month"],$rec["date_debut_groupe"]["day"],$rec["date_debut_groupe"]["year"]);}
		}
		*/
	/**
	 * Calculate the endddate if the user used the duration dropdown
	 *
	 * @param unknown_type $rec
	 */
	/*	function updateEndDate(&$rec)
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
		*/

	function initial_values()
	{
		$initial=array();
		$initial['end_choice']=1;
		$initial['recurrent_o_n']=1;
		$initial['cyclus_enddate']=array('day'=>date("d"),
                                      'month'=>date("m"),
                                     'year'=>date("Y"));

		return $initial;
	}
	function getEndDateInfo($record,$mode)
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
		$page->register_loadscript("change_recurrent_o_n(); change_duration()");
	}


	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		$view = $this->getView();

		if ($view == "active") {
			$this->addFilter("( organisme_groupe_travail.date_fin_groupe is null or organisme_groupe_travail.date_fin_groupe > CURDATE() )");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}

		return $handler->action_admin();
	}
	function rowColor($record) {
		$date_fin = $record["date_fin_groupe"];
		if ($date_fin != "")
		return $this->couleurarchive;
	}

	function descriptor_def() {
		return "([id_organisme.nom]) [nom] ";
	}
	function action_inscrire_du_presse_papier() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		global $g_sessionManager;
		//		$id_individu_1 = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$requete = "SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$data = $db->getrows($requete);
		//		$this->p($data);
		if (count($data) == 0) {
			$db->commit();
			$this->redirect();
		}
		foreach ($select as $id_variable) {
			$id_groupe_travail = explode('=', $id_variable);
			$id_groupe_travail_1 = $id_groupe_travail[1];

			foreach ($data as $id_individu) {
				$id_individu_1 = $id_individu["id_variable"];
				$requete = "INSERT INTO individu_groupe_travail
										 (  id_individu,id_groupe_travail,id_role_groupe_travail, 
										commentaire, id_creation, date_creation, id_modification, date_modification, date_debut_groupe )  " . "
					VALUES( '$id_individu_1' ,$id_groupe_travail_1,'4',
					'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP(), UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
				$db->query($requete);
				$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_groupe_travail' ");
			}
		}

		$requete = "DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql1 = 'select distinct id_individu from individu_groupe_travail
								 where id_groupe_travail in (' . $idrencontres . ') 
								 and individu_groupe_travail.date_fin_groupe is NULL';
		$sql2 = 'select distinct ifn.id_individu from individu_fonction ifn , organisme_groupe_travail ogt
								 where ogt.id  in (' . $idrencontres . ')
								 and ifn.id_fonction=ogt.id_type_fonction
								 and ifn.id_organisme=ogt.id_organisme
								 and ifn.date_fin is NULL ';
		$sql3 = 'select distinct ifn.id_individu from individu_fonction ifn , organisme_groupe_travail_cyclus ogtc, organisme_groupe_travail ogt
								 where ogtc.id_groupe_travail  in (' . $idrencontres . ')
								 and ifn.id_fonction=ogtc.id_type_fonction
								 and ogt.id=ogtc.id_groupe_travail
								 and ifn.id_organisme=ogt.id_organisme
								 and ifn.date_fin is NULL ';

		$data = $db->getrows($sql1.' UNION '.$sql2.' UNION '.$sql3);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		$sql = 'select distinct id_organisme from organisme_groupe_travail
								 where id in (' . $idrencontres . ')';
		$data = $db->getrows($sql);
		$idorganisme = $data[0]["id_organisme"];
		return true;
	}

	function getCustomMraHtml()
	{
		$list = 'Date (aaaa-mm-jj) : ';
		$list .=  '<input type="text" name="date_rencontre" value=" " size="10" >';
		$list .= ' ';
		$list .= 'Heure (hh:mm) : ';
		$list .= '<input type="text" name="heure_rencontre" value=" " size="6" >';
		$list .= ' ';
		$list .= 'Durée (hh) : ';
		$list .= '<input type="text" name="duree_rencontre" value=" " size="3" >';
		return $list;
	}
	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);

		$mraactions['creer_rencontre'] = "creer_rencontre";
		$actions["generer_rencontres"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=generer_rencontres&atkselector=[pk]", SESSION_NESTED);
		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		$mraactions["inscrire_du_presse_papier"] ="inscrire_du_presse_papier";
		$mraactions['liste_detaillee'] = "liste_detaillee";
		$mraactions['liste_simple'] = "liste_simple";
		$mraactions['liste_des_rencontres'] = "liste_des_rencontres";


	}
	function adminFooter() {
		$retour=parent::adminfooter();
		$view = $this->getView();
		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive ';
		if ($view == "active") {
			return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
		} else {
			return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
		}
	}
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}
	function action_liste_simple()
	{
		return $this->action_liste_detaillee("simple");
	}
	function action_liste_detaillee($mode) {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		//		$db = & atkGetDb();
		$res = "<table border='1'>";
		foreach ($select as $id_variable) {
			$recs = $this->selectDb("$id_variable");
			$record = $recs[0];

			$res .= "<tr><td></td></tr>";
			$res .= "<tr><td></td></tr>";
			$res .= "<tr><td class='styletitre'><b>";
			$res .= "<<< Groupe de travail >>></td></tr><tr><td class='styletitre'><b>".$record["nom"]. "</b></td><td class='styleligne'> (" . $record["id_organisme"]["nom"] . ")</td>";
			$res .= "<td class='styleligne'>Lieu : " . $record["id_lieu_rencontre"]["libelle"] . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Membres permanents : </b></td>";

			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_groupe_travail");
			$query->addJoin("individu", "", "individu_groupe_travail.id_individu = individu.id", true);
			$query->addJoin("organisme", "", "individu_groupe_travail.id_organisme_participant = organisme.id", true);
			$query->addJoin("type_role_groupe_travail", "", "individu_groupe_travail.id_role_groupe_travail = type_role_groupe_travail.id", true);

			$query->addField("organisme.nom as organisme");
			$query->addField("individu.nom as individu_nom");
			$query->addField("individu.prenom as individu_prenom");
			$query->addField("type_role_groupe_travail.libelle as role");
			$query->addField("individu_groupe_travail.date_fin_groupe as date_fin");
			$query->addField("individu_groupe_travail.date_debut_groupe as date_debut");
			$query->addField("individu_groupe_travail.date_echeance_mandat as date_echeance_mandat");
			$query->addCondition("( individu_groupe_travail.date_fin_groupe is null or individu_groupe_travail.date_fin_groupe < CURDATE() )");
			$query->addCondition("individu_groupe_travail.id_groupe_travail =". $record['id']."");
			$query->addOrderBy("individu.nom, individu.prenom ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);

			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				if ($mode=='simple')
				{
					$res .= "<tr><td class='stylesmallcaps'>" . $stuff[$i]["individu_nom"] . " ". $stuff[$i]["individu_prenom"]. "</td><td>".$stuff[$i]["role"]."</td>".
			"<td>".$stuff[$i]["organisme"] ."</td><td>".$stuff[$i]["date_echeance_mandat"] ."</td></tr>";
				}
				else
				{
					$res .= "<tr><td class='stylesmallcaps'>" . $stuff[$i]["individu_nom"] . " ". $stuff[$i]["individu_prenom"]. "</td><td>".$stuff[$i]["role"]."</td>".
			"<td>".$stuff[$i]["organisme"] ."</td><td>".$stuff[$i]["date_echeance_mandat"] ." </td><td>" . $stuff[$i]["date_debut"];
					$res .= " à " . $stuff[$i]["date_fin"]."</td></tr>";
				}
			}
			if (isset($record["id_type_fonction"]))
			{
				$query = & $db->createQuery();
				$query->addTable("individu_fonction");
				$query->addJoin("individu", "", "individu_fonction.id_individu = individu.id", true);
				$query->addField("individu.nom as individu_nom");
				$query->addField("individu.prenom as individu_prenom");
				$query->addCondition("individu_fonction.id_fonction =". $record['id_type_fonction']['id']."");
				$query->addCondition("individu_fonction.id_organisme =". $record['id_organisme']['id']."");
				$query->addOrderBy("individu.nom, individu.prenom ");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$res .= "<tr><td class='stylesmallcaps'>" . $stuff[$i]["individu_nom"] . " ". $stuff[$i]["individu_prenom"]. "</td></tr>";
				}

			}
			if ($mode!='simple')
			{
				$res .= "<tr><td class='styletitre'><b>Rencontres : </b></td>";
				$query = & $db->createQuery();
				$query->addTable("organisme_rencontre");
				$query->addJoin("organisme_lieu_rencontre", "", "organisme_rencontre.id_lieu_rencontre= organisme_lieu_rencontre.id", true);
				$query->addField("organisme_lieu_rencontre.libelle as lieu");
				$query->addField("organisme_rencontre.id as id");
				$query->addField("organisme_rencontre.libelle as rencontre");
				$query->addField("organisme_rencontre.date_debut as date_debut");
				$query->addField("organisme_rencontre.heure_debut as heure_debut");
				$query->addField("organisme_rencontre.date_fin as date_fin");
				$query->addField("organisme_rencontre.heure_fin as heure_fin");

				$query->addCondition("organisme_rencontre.id_groupe_travail =". $record['id']."");

				$query->addOrderBy("organisme_rencontre.date_debut, organisme_rencontre.heure_debut");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);

				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$res .= "<tr><td><b class='stylesmallcaps'>" . $stuff[$i]["rencontre"] . "</b></td><td> le ". $stuff[$i]["date_debut"]. " à ". $stuff[$i]["heure_debut"]."</td><td>".$stuff[$i]["lieu"]."</tr>";
					$query = & $db->createQuery();
					$query->addTable("individu_rencontre");

					$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", true);
					$query->addJoin("organisme", "", "individu_rencontre.id_organisme_participant = organisme.id", true);
					$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);

					$query->addField("individu.nom as individu_nom");
					$query->addField("individu.prenom as individu_prenom");
					$query->addField("type_rencontre_participation.libelle as participation");
					$query->addCondition("type_rencontre_participation.id =individu_rencontre.id_type_rencontre_participation");
					$query->addCondition("individu_rencontre.id_rencontre =".$stuff[$i]["id"]);
					$query->addOrderBy("individu.nom, individu.prenom ");
					$sql = $query->buildSelect();
					$stuff2 = $db->getrows($sql);
					for ($i2 = 0, $_i2 = count($stuff2); $i2 < $_i2; $i2++) {
						$res .= "<tr><td class='stylesmallcaps'>" . $stuff2[$i2]["individu_nom"] . " ". $stuff2[$i2]["individu_prenom"]. "</td><td>". $stuff2[$i2]["participation"]."</td></tr>";
					}

				}
			}
		}
		$res .= "</table>";
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);


	}

	function action_liste_des_rencontres(&$handler) {

		$date_debut = $this->m_postvars["date_rencontre"];

		if (substr_count($date_debut,'-',0)!=2 )
		{ $this->setFeedback("liste_des_rencontres",ACTION_FAILED);
		$location = $this->feedbackUrl("liste_des_rencontres", ACTION_FAILED, "", "La date de début n'est pas correcte.");
		$this->redirect($location);
		}



		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		//		$db = & atkGetDb();
		$res = "<table border='1'>";
		foreach ($select as $id_variable) {
			$recs = $this->selectDb("$id_variable");
			$record = $recs[0];
			$res .= "<tr><td class='styletitre'><b>".$record["nom"]. "</b></td><td class='styleligne'> (" . $record["id_organisme"]["nom"] . ")</td>";
			$res .= "<td class='styleligne'>Lieu : " . $record["id_lieu_rencontre"]["libelle"] . "</td></tr>";

			$db = & atkGetDb();

			$query = & $db->createQuery();
			$query->addTable("organisme_rencontre");
			$query->addJoin("organisme_lieu_rencontre", "", "organisme_rencontre.id_lieu_rencontre= organisme_lieu_rencontre.id", true);
			$query->addField("organisme_lieu_rencontre.libelle as lieu");
			$query->addField("organisme_rencontre.id as id");
			$query->addField("organisme_rencontre.libelle as rencontre");
			$query->addField("organisme_rencontre.date_debut as date_debut");
			$query->addField("organisme_rencontre.heure_debut as heure_debut");
			$query->addField("organisme_rencontre.date_fin as date_fin");
			$query->addField("organisme_rencontre.heure_fin as heure_fin");

			$query->addCondition("organisme_rencontre.id_groupe_travail =". $record['id']."");
			$query->addCondition("organisme_rencontre.date_debut >='". $date_debut."'");

			$query->addOrderBy("organisme_rencontre.date_debut, organisme_rencontre.heure_debut");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);

			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$res .= "<tr><td><b class='stylesmallcaps'>" . $stuff[$i]["rencontre"] . "</b></td><td> le ". $stuff[$i]["date_debut"]. " à ". $stuff[$i]["heure_debut"]."</td><td>".$stuff[$i]["lieu"]."</tr>";
					

			}
				
		}
		$res .= "</table>";
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);


	}

	function action_generer_rencontres(& $handler) {
		$selector = $this->m_postvars["atkselector"];
		$ret=schedulertools::updateRecurringEvents($selector);

		if ( $ret== false)
		{
			$this->setFeedback("generer_rencontres",ACTION_FAILED);
			$location = $this->feedbackUrl("generer_rencontres", ACTION_FAILED, "", "Erreur dans la génération des rencontres : ".$ret);
		}
		else
		{
			$this->setFeedback("generer_rencontres",ACTION_SUCCESS);
			$location = $this->feedbackUrl("generer_rencontres", ACTION_SUCCESS, "", $ret);}
			$this->redirect($location);
	}
	function action_creer_rencontre(& $handler) {
		$date_rencontre = $this->m_postvars["date_rencontre"];
		$heure_rencontre = $this->m_postvars["heure_rencontre"];
		$duree_rencontre = $this->m_postvars["duree_rencontre"];
		// Vérifier une seule ligne sélectionnée

		if (count($this->m_postvars["atkselector"])==1)
		{$pk = $this->m_postvars["atkselector"][0];
		}
		else
		{
			$this->setFeedback("creer_rencontre",ACTION_FAILED);
			$location = $this->feedbackUrl("creer_rencontre", ACTION_FAILED, "", "Vous devez sélectionner une seule ligne");
			$this->redirect($location);
		}

		// Vérifier données reçues

		if (substr_count($date_rencontre,'-',0)!=2 || substr_count($heure_rencontre,':',0)!=1 || $duree_rencontre<'00'|| $duree_rencontre>'99')
		{ $this->setFeedback("creer_rencontre",ACTION_FAILED);
		$location = $this->feedbackUrl("creer_rencontre", ACTION_FAILED, "", "Erreur dans les données fournies");
		$this->redirect($location);
		}

		// Récupérer id_organisme, id_groupe_travail
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		$sql='SELECT id_organisme, id, nom, id_lieu_rencontre,id_type_fonction, id_type_rencontre,lieu_reunion
		from organisme_groupe_travail 
		where '.$pk.'
		';
		$data = $db->getrows($sql);
		$idorganismegroupe=$data[0]["id_organisme"];
		$idlieurencontre=$data[0]["id_lieu_rencontre"];
		$idtyperencontre=$data[0]["id_type_rencontre"];
		$id_type_fonction=$data[0]["id_type_fonction"];
		$idgroupe=$data[0]["id"];
		$nomgroupe=$data[0]["nom"];
		$lieureunion=escapesql($data[0]["lieu_reunion"]);
		$heure_temp=explode(':',$heure_rencontre);
		$heure_fin=	$heure_temp[0] +$duree_rencontre;
		$heure_fin=$heure_fin.':'.$heure_temp[1];
		// Créer organisme_rencontre et récupérer id
		$libelle=escapesql($nomgroupe." (".$date_rencontre.").");
		$idrencontre=$db->nextid("seq_organisme_rencontre");
		$sql="INSERT into organisme_rencontre
	( id, id_organisme, id_groupe_travail, id_type_rencontre,libelle, date_debut, heure_debut, date_fin, heure_fin, id_lieu_rencontre, lieu_texte, id_creation, date_creation, id_modification, date_modification )
	VALUES
	( '".$idrencontre."','". $idorganismegroupe."','".$idgroupe."','".$idtyperencontre."','".$libelle."','".$date_rencontre."','".$heure_rencontre."',' ".$date_rencontre."','".$heure_fin."',' ".$idlieurencontre."','".$lieu_reunion."','"
	. $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   )";
	$db->query($sql);
	// récupérer liste des individus du groupe et leur organisme  hors date_fin_groupe!=null

	if ($id_type_fonction=="")
	{
		$sql='SELECT distinct id_individu, id_organisme_participant
		from individu_groupe_travail 
		where date_fin_groupe is null and id_groupe_travail='.$idgroupe.'
		';	
	}
	else
	{
		$sql='(SELECT distinct id_individu, id_organisme_participant
		from individu_groupe_travail 
		where date_fin_groupe is null and id_groupe_travail='.$idgroupe.'
		) UNION (SELECT id_individu, id_organisme
		from individu_fonction
		where date_fin is null and id_organisme='.$idorganismegroupe.' and id_fonction='.$id_type_fonction.')';	
	}


	$data = $db->getrows($sql);
	// créer individu_rencontre
	for ($i = 0; $i < count($data); $i++) {
		$idindividurencontre=$db->nextid("seq_individu_rencontre");
		if ($data[$i]['id_organisme_participant']=="")
		{
			$sql1="INSERT into individu_rencontre
		( id, id_individu,  id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$idindividurencontre."',' ".$data[$i]['id_individu']."', '".$idrencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		)";
		}
		else
		{
			$sql1="INSERT into individu_rencontre
		( id, id_individu, id_organisme_participant, id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$idindividurencontre."',' ".$data[$i]['id_individu']."', '".$data[$i]['id_organisme_participant']."',' ".$idrencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		)";
		}
		$db->query($sql1);
	}





	$this->redirect();
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
			function descripteur_groupe_travail_display($record, $mode) 
	{
		$id_groupe_travail=trim($record["id"]);

		return $descripteur=$this->decoupe_affichage_colonne($this->descripteur_groupe_travail($id_groupe_travail,"o"), 100);
	}	


}

?>