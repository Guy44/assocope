<?php

class schedulertools
{
	/**
	 * Convert weekday number to flag
	 *
	 * @param int $weekday_number Weekday number (0 sunday, 6 saturday)
	 * @return int Weekday flag
	 */
	function weekdaynumbertoflag($weekday_number)
	{
		if (($weekday_number >=0) && ($weekday_number <= 6))
		$weekday = pow(2,$weekday_number); //2^$weekday_number;
		else
		$weekday = false;

		return $weekday;
	}

	/**
	 * Determine whether or not the passed year is a leap year.
	 *
	 * @param   int     $y      The year as a four digit integer
	 * @return  boolean         True if the year is a leap year, false otherwise
	 */
	function isLeapYear($y)
	{
		return $y % 4 == 0 && ($y % 400 == 0 || $y % 100 != 0);
	}

	/**
	 * Calculate day of week (1=sunday, 2=monday etc...)
	 *
	 * @param int $day Day
	 * @param int $month Month
	 * @param int $year Year
	 * @return int Weekday
	 */
	function dayOfWeek($day,$month,$year)
	{
		return date("w",mktime(12,0,0,$month,$day,$year))+1;
	}


	/**
	 * Calculate the nth day
	 *
	 * @param int $nth 1,2,3,4,5,-1 (last)
	 * @param int $weekday Day number (1=sunday, 2=monday etc...)
	 * @param int $month Month
	 * @param int $year Year
	 * @return int Day number
	 */
	function nthDay($nth,$weekday,$month,$year)
	{
		$daysOfMonthY = array(31,29,31,30,31,30,31,31,30,31,30,31); // Leapyear numbers
		$daysOfMonth =  array(31,28,31,30,31,30,31,31,30,31,30,31); // Non leapyear numbers
		if ($nth > 0) return ($nth-1)*7 + 1 + (7 + $weekday - schedulertools::dayOfWeek(($nth-1)*7 + 1,$month,$year))%7;
		if (schedulertools::isLeapYear($year)) $days = $daysOfMonthY[$month-1];
		else $days = $daysOfMonth[$month-1];
		return $days - (schedulertools::dayOfWeek($days,$month,$year) - $weekday + 7)%7;
	}


	/**
	 * Returns the startdate of the item
	 *
	 * @param Array $item Scheduler item
	 * @return int Timestamp
	 */
	function getItemStartDate($item)
	{
		return mktime(12,0,0,intval($item["startdate"]["month"]),intval($item["startdate"]["day"]),intval($item["startdate"]["year"]));
	}

	/**
	 * Returns the enddate of the item
	 *
	 * @param array $item Scheduler item
	 * @return int Timestamp or NULL
	 */
	function getItemEndDate($item)
	{
		switch($item['end_choice'])
		{
			case 1: $enddate = mktime(12,0,0,12,31,2037); // No enddate, so we use max date
			break;
			case 2: $enddate = mktime(12,0,0,substr($item["cyclus_enddate"],5,2),substr($item["cyclus_enddate"],8,2),substr($item["cyclus_enddate"],0,4));
			break;
			case 3: $enddate=NULL;  // After x times
			break;
		}
		return $enddate;
	}

	/**
	 * Get the dates for a recurring item for the given period
	 *
	 * @param array $item
	 * @param string $rangeStartDate
	 * @param string $rangeEndDate
	 * @return array Array with dates for the given item
	 */
	function getDates($item,$rangeStartDate=NULL,$rangeEndDate=NULL)
	{
		$dates = array();
		$datecounter=0;
		$validdates = 0;
		$startdate =  mktime(0,0,0,substr($rangeStartDate,5,2),substr($rangeStartDate,8,2),substr($rangeStartDate,0,4));
		$enddate = schedulertools::getItemEndDate($item);
		//   echo '$rangeStartDate : '.($rangeStartDate).'<br></br>';
		//echo '$rangeEndDate : '.($rangeEndDate).'<br></br>';
		//   echo 'startdate : '.($startdate).'<br></br>';
		// echo 'enddate : '.($enddate).'<br></br>';
		atkdebug("schedulertools::getDates -> RangeStart: $rangeStartDate | RangeEnd: $rangeEndDate | Startdate: ".date('Y-m-d',$startdate)." | Enddate: ".date('Y-m-d',$enddate));

		if($rangeStartDate!=NULL && $rangeEndDate!=NULL)
		{
			if(!is_null($enddate) && $rangeStartDate>date('Y-m-d',$enddate)) return array();
			if($rangeStartDate>date('Y-m-d',$startdate) && $rangeStartDate<=$enddate) $startdate = mktime(12,0,0,substr($rangeStartDate,5,2),substr($rangeStartDate,8,2),substr($rangeStartDate,0,4));
			if(($item['end_choice']==2 && $rangeEndDate<date('Y-m-d',$enddate) && $rangeEndDate>$startdate) || $item['end_choice']!=2) $enddate = mktime(12,0,0,substr($rangeEndDate,5,2),substr($rangeEndDate,8,2),substr($rangeEndDate,0,4));
		}
		atkdebug("schedulertools::getDates -> (AFTER RANGE CHECK) RangeStart: $rangeStartDate | RangeEnd: $rangeEndDate | Startdate: ".date('Y-m-d',$startdate)." | Enddate: ".date('Y-m-d',$enddate));
		//   echo 'startdate : '.($startdate).'<br></br>';
		//echo 'enddate : '.($enddate).'<br></br>';
		while(true)
		{
			$checkdate = $startdate+($datecounter*86400);
			$unix_date = $checkdate;
			if($checkdate>$enddate) break;
			// Skip all months that we don't need for the yearly day/date events
			if($item['recur']=="yearly" && date("n",$checkdate)!=$item["yearly_month"]
			&& date("n",$checkdate)!=$item["yearly_month2"]
			)
			{
				$current_day = (date("d",$checkdate)-1);
				$number_of_days = date("t",$checkdate);
				$datecounter+=($number_of_days-$current_day);
				continue;
			}


			if(schedulertools::showItem($item,$checkdate,$startdate,$enddate))
			{

				$dates[] = date("Y-m-d",$checkdate);
				$validdates++;
			}
			$datecounter++;
			if($item["recur"]=="once" ||
			($item["end_choice"]==3 &&
			($item["cyclus_times"]-intval($item["times"])==$validdates))) break;
		}
		atk_var_dump($item,"schedulertools::getDates() -> SchedulerItem");
		atk_var_dump($dates,"schedulertools::getDates($rangeStartDate,$rangeEndDate)");


		return $dates;
	}

	/**
	 * Show the current item
	 *
	 * @param array $item Scheduler item
	 * @param int $checkdate Day timestamp
	 * @param int $startdate Startdate timestamp
	 * @param int $enddate Enddate timestamp
	 * @return boolean Show the item or not
	 */
	function showItem($item,$checkdate,$startdate,$enddate)
	{

		$month_time = ceil(date("d",$checkdate)/7);
		$day = date("j",$checkdate);
		$month = date("n",$checkdate);
		$year = date("Y",$checkdate);
		$weekday_number = date("w",mktime(12,0,0,$month,$day,$year));
		$weekday = schedulertools::weekdaynumbertoflag($weekday_number);
		$show_item = true;
		switch($item["recur"])
		{
			case 'once':
				if($checkdate>=$startdate && $checkdate<=$enddate) { $show_item = true; } else { $show_item = false; }
				break;
			case 'daily':
				if($item['daily_choice']==1)
				{
					$every = $item['daily_every'];
					$interval = $checkdate - $startdate;
					$interval_days = floor($interval/(60*60*24));
					$devided = $interval_days/$every;
					$match = (int) $devided;
					if ($devided != $match)
					{
						$show_item = false;
					}
				}
				else
				{
					$workdays = array(2,3,4,5,6);
					if(in_array(schedulertools::dayOfWeek($day,$month,$year),$workdays)) { $show_item=true;} else { $show_item = false; }
				}
				break;
			case 'weekly':
				if(hasFlag(array_sum($item["weekly_weekday"]),$weekday)) { $show_item = true; } else { $show_item = false; }
				//echo '<br></br> somme array'.array_sum($item["weekly_weekday"]);
				//echo '<br></br> item';
				//print_r($item["weekly_weekday"]);

				$every = $item['weekly_every'];
				$interval = $checkdate - $startdate;
				$interval_weeks = floor($interval/(60*60*24*7));
				$devided = $interval_weeks/$every;
				$match = (int) $devided;
				if ($devided != $match)
				{

					$show_item = false;
				}
				// 	    if ($show_item==true)
				// 	    {echo '<br></br>show item true : '.$show_item;}
				break;
			case 'monthly':
				if($item['monthly_choice']==1)
				{
					// Day x of every x months
					if($item["monthly_day"]==$day)  { $show_item = true; } else { $show_item = false; }
					$every = $item['monthly_every'];
				}
				else
				{
					// xth weekday of x months
					$every = $item['monthly_every2'];
					$xth_day = schedulertools::nthDay($item["monthly_month_time"],$item["monthly_weekday_list"],$month,$year);
					if($xth_day==$day) { $show_item = true; } else { $show_item = false; }
				}
				$start_month = $item["startdate"]["month"];
				$this_month = strftime('%m', $checkdate);
				$interval = $this_month - $start_month;
				$devided = $interval/$every;
				$match = (int) $devided;
				if ($devided != $match)
				{
					$show_item= false;
				}
				break;
			case 'yearly':
				if($item['yearly_choice']==1)
				{
					if($item["yearly_day"]==$day && $item["yearly_month"]==$month)  { $show_item = true; } else { $show_item = false; }
				}
				else
				{
					/* xth weekday of month */
					$xth_day = schedulertools::nthDay($item["yearly_month_time"],$item["yearly_weekday_list"],$month,$year);
					if($item["yearly_month2"]==$month && $day==$xth_day) { $show_item = true; } else { $show_item = false; }
				}
				break;
		}
		return $show_item;
	}

	/**
	 * Check for which users the user is an assistant
	 *
	 * @param int $userid
	 * @return array Array with user id's
	 */
	function assistantFor($userid)
	{
		static $assistantFor = null;

		if(is_null($assistantFor))
		{
			$db = &atkGetDb();
			$sql = "SELECT userid FROM scheduler_userassistants WHERE employeeid='{$userid}'";
			$nrows = $db->getrows($sql);
			$assistantFor = array();
			for($i=0;$i<count($nrows);$i++)
			{
				$assistantFor[] = $nrows[$i]["userid"];
			}
		}
		return $assistantFor;
	}

	/**
	 * Check if a user is an attendee for the given item
	 *
	 * @param int $item_id Id of the scheduler item
	 * @param int $userid Id of the user
	 * @return boolean True if it's an attendee
	 */
	function isAttendee($item_id,$userid)
	{
		$db = &atkGetDb();
		$sql = "SELECT person_id FROM scheduler_attendees WHERE scheduler_id='{$item_id}' AND person_id='{$userid}'";
		$nrows = $db->getrows($sql);
		if(count($nrows)==1) return true;
		return false;

	}

	/**
	 * Update recurring events for a given period
	 *
	 * @param string $startdate Start date
	 * @param string $enddate End date
	 */
	function updateRecurringEvents($selector)
	{
		$res="";
		$id_gt = explode('=', $selector);
		$id_gt1 = $id_gt[1];
		global $g_user;
		$userutilisateur = $g_user["id"];
		$db = &atkGetDb();
		$sql="select
     gt.end_choice,
    gt.cyclus_enddate,
    gt.cyclus_times,
    gt.date_debut_groupe,
    gt.date_fin_groupe,
    gt.id_organisme,
    gt.nom,
    gt.lieu_reunion,
    gtc.id_groupe_travail,
    gtc.sauf_vacances_o_n,
    gtc.id_scheduler_cyclus,
    gtc.id_type_fonction,
    gtc.id_type_rencontre,
    gtc.id_lieu_rencontre,
    gtc.starttime,
    gtc.endtime,
     sc.id,
    sc.recur,
    sc.yearly_choice,
    sc.yearly_day
    ,sc.yearly_month,
    sc.yearly_month_time,
    sc.yearly_weekday_list,
    sc.yearly_month2,
    sc.monthly_choice,
    sc.monthly_day,
    sc.monthly_every,
    sc.monthly_month_time,
    sc.monthly_weekday_list,
    sc.monthly_every2,
    sc.weekly_every,
    sc.weekly_weekday,
    sc.daily_choice,
    sc.daily_every
    from organisme_groupe_travail gt, organisme_groupe_travail_cyclus gtc, scheduler_cyclus sc
    where gt.id=".$id_gt1." 
    and gt.id=gtc.id_groupe_travail
     and gtc.id_scheduler_cyclus=sc.id "
     ;
     $data=$db->getrows($sql);
     for ($i = 0; $i < count($data); $i++) {
     	$rec = $data[$i];
     	$scheduler = &atkGetNode("scheduler.scheduler_cyclus");
     	$condition = "scheduler_cyclus.id='".$rec["id"]."'";
     	$nrows = $scheduler->selectDb($condition,"","","",array('weekly_weekday'));
     	$rec["weekly_weekday"]=$nrows[0][weekly_weekday];
     	if ($rec["recur"]=="once")  {return false;}
     	//    	if ($rec["end_choice"]=="1")  {return false;}
     	if ($rec["date_debut_groupe"]=="")
     	{$startdate = date("Y-m-d",mktime(0,0,0,gmdate('m'),gmdate('d'),gmdate('Y')));}
     	else
     	{$startdate = date("Y-m-d",mktime(0,0,0,substr($rec["date_debut_groupe"],5,2),substr($rec["date_debut_groupe"],8,2),substr($rec["date_debut_groupe"],0,4)));}
/*echo $rec["cyclus_enddate"];
echo '<br></br>';
echo $startdate;
die();
*/
     	if ($rec["end_choice"]=="2"&& $rec["cyclus_enddate"] <$startdate) {return false;}

     	if ($rec["date_fin_groupe"]=="")
     	{$enddate = date("Y-m-d",mktime(0,0,0,gmdate('m'),gmdate('d')+1,gmdate('Y')+1));}
     	else
     	{$enddate = date("Y-m-d",mktime(0,0,0,substr($rec["date_fin_groupe"],5,2),substr($rec["date_fin_groupe"],8,2),substr($rec["date_fin_groupe"],0,4)));}

     	$tmp_startdate = mktime(0,0,0,substr($startdate,5,2),substr($startdate,8,2),substr($startdate,0,4));
     	$tmp_enddate = mktime(0,0,0,substr($enddate,5,2),substr($enddate,8,2),substr($enddate,0,4));
     	$dates = schedulertools::getDates($rec,$startdate,$enddate);
     	$nombre_rencontres_creees=0;
     	$nombre_rencontres_deja_creees=0;
     	$nombre_rencontres_non_creees_vacances=0;
     	$nombre_participants_créés=0;
     	foreach($dates as $date)
     	{
     		$idgt=$id_gt1;
     		$tmp_start = mktime($rec["starttime"]["hours"],$rec["starttime"]["minutes"],$rec["starttime"]["seconds"],$rec["startdate"]["month"],$rec["startdate"]["day"],$rec["startdate"]["year"]);
     		$tmp_end = mktime($rec["endtime"]["hours"],$rec["endtime"]["minutes"],$rec["endtime"]["seconds"],$rec["enddate"]["month"],$rec["enddate"]["day"],$rec["enddate"]["year"]);
     		$duration = $tmp_end-$tmp_start;

     		$date_rencontre = $date;
     		$sql="select count(id) as nombre from scheduler_cyclus_not where date_exception='".$date_rencontre."' and id_groupe_travail=".$idgt." ";
     		$data3=$db->getrows($sql);
     		if ($data3[0]["nombre"]>0 ) {continue;}

     		$heure_rencontre=$rec["starttime"];
     		$heure_fin=$rec["endtime"];
     		
     		$sql="SELECT count(id) as nombre from organisme_rencontre where id_groupe_travail=".$idgt." and date_debut='".$date."' ";
     		//  	$this->p($sql);

     		$data1=$db->getrows($sql);


     		if ($data1[0]["nombre"]==0)

     		{ // la rencontre n'existe pas encore
     			 


     			if ($rec["sauf_vacances_o_n"]=='1')
     			{$sql="select count(id) as nombre from scheduler_vacances where date_debut<='".$date."' and    date_fin>='".$date. "'  ";	}
     			else
     			{$sql="select count(id) as nombre from scheduler_vacances where date_debut<='".$date."' and    date_fin>='".$date. "'  and vacances_scolaires_o_n='0'";	}

     			$data2=$db->getrows($sql);

     			if ($data2[0]["nombre"]==0 )
     			{
     				// La rencontre ne tombe ni un jour férié ni un jour de vacance

     				$idorganismegroupe=$rec["id_organisme"];
     				$idlieurencontre=$rec["id_lieu_rencontre"];
     				$idtyperencontre=$rec["id_type_rencontre"];
     				$idgroupe=$idgt;
     				$nomgroupe=$rec["nom"];
     				$lieureunion=escapesql($rec["lieu_reunion"]);
     				// Créer organisme_rencontre et récupérer id
     				$libelle=escapesql($nomgroupe." (".$date_rencontre.").");
     				$idrencontre=$db->nextid("seq_organisme_rencontre");
     				$sql="INSERT into organisme_rencontre
	( id, id_organisme, id_groupe_travail, id_type_rencontre,libelle, date_debut, heure_debut, date_fin, heure_fin, id_lieu_rencontre, lieu_texte, id_creation, date_creation, id_modification, date_modification )
	VALUES
	( '".$idrencontre."','". $idorganismegroupe."',".$idgroupe.",'".$idtyperencontre."','".$libelle."','".$date_rencontre."','".$heure_rencontre."',' ".$date_rencontre."','".$heure_fin."',' ".$idlieurencontre."','".$lieu_reunion."','"
	. $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   )";
	$db->query($sql);
	{$nombre_rencontres_creees+=1;}

	// récupérer liste des individus du groupe et leur organisme  hors date_fin_groupe!=null

	if ($rec["id_type_fonction"]=="")
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
		where date_fin is null and id_organisme='.$rec["id_organisme"].' and id_fonction='.$rec["id_type_fonction"].')';	
	}
	$data3 = $db->getrows($sql);
	// créer individu_rencontre
	for ($i3 = 0; $i3 < count($data3); $i3++) {
		$i3dindividurencontre=$db->nextid("seq_individu_rencontre");
		if ($data3[$i3]['id_organisme_participant']=="")
		{
			$sql1="INSERT into individu_rencontre
		( id, id_individu,  id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$i3dindividurencontre."',' ".$data3[$i3]['id_individu']."', '".$idrencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		)
		ON DUPLICATE KEY UPDATE date_modification=UTC_TIMESTAMP()
		";
		}
		else
		{
			$sql1="INSERT into individu_rencontre
		( id, id_individu, id_organisme_participant, id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$i3dindividurencontre."',' ".$data3[$i3]['id_individu']."', '".$data3[$i3]['id_organisme_participant']."',' ".$idrencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		)
		ON DUPLICATE KEY UPDATE date_modification=UTC_TIMESTAMP()";
		}
		$db->query($sql1);
	}
     			}
     			else
     			{
     				// la rencontre n'est pas créée pour cause de jour férié ou de vacances
     				$nombre_rencontres_non_creees_vacances+=1;}
     		}
     		else
     		{
     			// la rencontre a déjà été créée
     			$nombre_rencontres_deja_creees+=1;
     			$sql="SELECT id  from organisme_rencontre where id_groupe_travail=".$idgt." and date_debut='".$date."' ";
     			$dataid= $db->getrows($sql);
     			$idrencontre=$dataid[0]["id"];
     			if ($rec["id_type_fonction"]=="")
     			{ 			$sql="SELECT distinct id_individu, id_organisme_participant
		from individu_groupe_travail 
		where date_fin_groupe is null and id_groupe_travail=".$idgt." 
		and id_individu not in (select ir.id_individu from individu_rencontre ir, organisme_rencontre ore  where ore.id=ir.id_rencontre and ore.id_groupe_travail=".$idgt." and ore.date_debut='".$date."' )
		";
     			}
     			else
     			{ 			$sql="(SELECT distinct id_individu, id_organisme_participant
		from individu_groupe_travail 
		where date_fin_groupe is null and id_groupe_travail=".$idgt." 
		and id_individu not in (select ir.id_individu from individu_rencontre ir, organisme_rencontre ore  where ore.id=ir.id_rencontre and ore.id_groupe_travail=".$idgt." and ore.date_debut='".$date."' )
		) UNION (SELECT distinct id_individu, id_organisme
		from individu_fonction
		where date_fin is null and id_fonction='".$rec["id_type_fonction"]."' and id_organisme=".$rec["id_organisme"]." 
		and id_individu not in (select ir.id_individu from individu_rencontre ir, organisme_rencontre ore  where ore.id=ir.id_rencontre and ore.id_groupe_travail=".$idgt." and ore.date_debut='".$date."' )
		)";
     			}
     			$data4 = $db->getrows($sql);
     			// créer individu_rencontre qui sont nouveaux
     			for ($i4 = 0; $i4 < count($data4); $i4++) {
     				$idindividurencontre=$db->nextid("seq_individu_rencontre");
     				if ($data4[$i4]['id_organisme_participant']=="")
     				{
     					$sql1="INSERT into individu_rencontre
		( id, id_individu,  id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$idindividurencontre."',' ".$data4[$i4]['id_individu']."', '".$idrencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		)
		 ON DUPLICATE KEY UPDATE date_modification=UTC_TIMESTAMP() ";
     				}
     				else
     				{
     					$sql1="INSERT into individu_rencontre
		( id, id_individu, id_organisme_participant, id_rencontre, date_inscription,  	id_type_rencontre_participation,  id_creation, date_creation, id_modification, date_modification )
		VALUES
		('".$idindividurencontre."',' ".$data4[$i4]['id_individu']."', '".$data4[$i4]['id_organisme_participant']."',' ".$i4rencontre."', UTC_DATE(),'5', '" . $userutilisateur."',UTC_TIMESTAMP(),'". $userutilisateur."',UTC_TIMESTAMP()   
		) 
		ON DUPLICATE KEY UPDATE date_modification=UTC_TIMESTAMP() ";
     				}
     				$db->query($sql1);
     				$nombre_participants_créés+=1;
     			}

     		}

     	}


     	/* atkdebug("schedulertools::updateRecurringEvents -> update scheduler item lastdate: $endstamp = ".date("Y-m-d",$endstamp));
     	 $sql = "UPDATE scheduler_scheduler SET lastdate = '$endstamp', times =  COALESCE(times,0)+".count($dates)." WHERE id='$id'";
     	 $db->query($sql);
     	 */
     	$db->commit();
     	if ($nombre_rencontres_non_creees_vacances==0 && $nombre_rencontres_deja_creees==0)
     	{}
     	else
     	{ $res.= "nombre de rencontres non créées à cause des vacances : ".$nombre_rencontres_non_creees_vacances."<br></br>";
     	$res.=  "nombre de rencontres non créées car déjà existantes : ".$nombre_rencontres_deja_creees."<br></br>";}

     	$res.=  "nombre de rencontres créées : ".$nombre_rencontres_creees."<br></br>";
     	$res.=  "nombre de nouvelles participations créées : ".$nombre_participants_créés."<br></br>";

     }
     return $res;
	}




}

?>