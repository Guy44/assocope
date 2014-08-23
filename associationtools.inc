<?php

  /**
   * Add a selected project to the session variable.
   * If the session variable is empty, it is filled with
   * the organismes the user has recently booked on.
   */

  global $g_organismenomsize; // must declare global. this piece of code might
                             // be executed somewhere in a local function scope.
  $g_organismenomsize = 50;
  

  function updateSelectedOrganismes()
  {
    global $g_sessionManager, $g_organismenomsize;

    atkdebug("updateSelectedorganisme");
    $org = array();
    //Get current sessionvar
    $session = &atkSessionManager::getSession();
    $org =  $g_sessionManager->getValue("selectedorg","globals");

    //If session var is empty fill with recent organismes
    if (count($org) == 0)
    {
      $org = getRecentorganismes();
      
    }

    //Delete atkselector from global vars, because the stackVar
    //function overwrites the stack val of atkselector
    //when it finds a value in $GLOBALS
    //$_REQUEST['atkselector'] = "";

 //Check if selected organisme already exists in session var
    $atkselect = $g_sessionManager->stackVar("atkselector");

    if (($atkselect != "") && isset($atkselect))
    {
       $organismeid = sscanf($atkselect, "organisme.id='%d'");
       $orgId = $organismeid[0];
    }
    else
    {
        $atkselect = $g_sessionManager->stackVar("selectedorganismeid");
        if (($atkselect != "") && isset($atkselect))
        {
          $orgId = $atkselect;
        }
        else
        {
          $orgId = 0;
        }
    }

    // When no organisme is selected in the dropdown list
    // and the user select's a organisme we need to check
    // if the organisme is in the list. If not
    // we need to get it's nom, so it can be displayed
    // in the dropdown list
    if ($orgId != 0)
    {
       $found = FALSE;
       foreach( $org as $cur)
       {
         if ($cur['organismeid']  == $orgId) $found = TRUE;
       }
       if (!$found)  //add organisme to dropdown list
       {

         $selectedOrg = Array();
         $selectedOrg['organismeid'] = $orgId;

         //Get organisme nom
         $db = &atkGetDb();
         $query = "SELECT nom FROM organisme WHERE id='".$selectedOrg['organismeid']."'";
         $arr = $db->getrows($query);
         $selectedOrg['organismenom'] = $arr[0]['nom'];
         if (strlen($arr[0]['nom']) > $g_organismenomsize)
         {
           $selectedOrg['organismenom'] = substr($arr[0]['nom'],0,$g_organismenomsize-2).".."; //update because of phases
         }
         else
         {
           $selectedOrg['organismenom'] = $arr[0]['nom']; //update because of phases
         }

         //Check maximum number of organismes in session var
         if (count($org) >= atkconfig("numberofrecentorganismes"))
         {
           array_shift($org); // remove the first
           $org[count($org)-1] = $selectedOrg;
         }
         else
         {
           $org[] = $selectedOrg;
         }

       }

       //Reload the menu frame by creating javascript
       $script = "var newlocation=\"menu.php?atkmenutop=organismes&selectedorganisme=".$orgId."\";
                  var oldlocation=parent.menu.location.toString();
                  if (oldlocation.indexOf(newlocation) == -1) {parent.menu.location = newlocation;}";
       $page = &atkinstance("atk.ui.atkpage");
       $page->register_loadScript($script);
     }

     // Copy org to session var
     // Use global session because menu.php uses
     // a different nomspace
     $g_sessionManager->globalVar("selectedorg", $org, true);
    
  }

 /**
  * Get the organismes the user recently booked hours on
  * @return array with recently used organismes
  *
  */

  function getRecentorganismes()
  {
    global $g_user, $g_organismenomsize;

    $db = &atkGetDb();

    $query = "SELECT DISTINCT organisme.nom as organismenom, organisme.id as organismeid FROM organisme ";
  //  $query.= "WHERE phase.id=hours.phaseid AND ".(isset($g_user["id"])?"userid='".$g_user["id"]."' AND ":"")."phase.status='active' AND organisme.status='active' AND phase.organismeid=organisme.id ";
    $query.= "ORDER BY organismenom";

    $arr = $db->getrows($query);

    $newarr = Array();

    // For some reason, the above query returns double results (even though I
    // do a 'select distinct'!)
    // I fail to see why, but I'll work around it by checking for doubles.
    $alreadyhad = array();
    for ($i=0, $_i=count($arr); $i<$_i;$i++)
    {
      if (!in_array($arr[$i]['organismeid'], $alreadyhad))
      {
        $alreadyhad[] = $arr[$i]['organismeid'];
        if (strlen($arr[$i]['organismenom']) > $g_organismenomsize)
        {
          $arr[$i]['organismenom'] = substr($arr[$i]['organismenom'],0,$g_organismenomsize-2).".."; //update because of phases
        }
        $newarr[] = $arr[$i];
      }
    }
    return $newarr;
  }

  /*
   * given a timestamp, this function calculates the weekstamp, which is a concatenation
   * of the year and the ISO week number. (e.g. 200134)
   */
  function weekstamp($timestamp)  // in achievotools.inc
  {
    /*
     * JN 02-06-26: FIX: Time locks based on week numbers not working on win32.
     *                   Reason is PHP: not all strftime functions are working on win32.
     *                   Solution: We have to calculate week of year manually.
     */

    $year = strftime("%Y",$timestamp);
    $yearStart = mktime(0,0,0,1,1,$year);
    $yearEnd = mktime(0,0,0,12,31,$year);

    $daysLost = strftime("%w",$yearStart);
    if ($daysLost > 4) {
      $daysLost -= 9;
    } else {
      $daysLost -= 2;
    }
    // $week = bcdiv(strftime("%j",$timestamp)+$daysLost+7,7,0);
    $week = "".floor((strftime("%j",$timestamp)+$daysLost+7)/7);

    /*
    atkdebug("(weekstamp): date: ".strftime("%a %d %m %Y",$timestamp).
             " week: ".$week.
             " day: ".strftime("%j",$timestamp).
             " jan1: ".strftime("%a",$yearStart).
             " dec31: ".strftime("%a",$yearEnd).
             " w1dLastY: ".($daysLost+1));
    */

    if ($week == 0) {
      //atkdebug("(weekstamp): adjust to previous year");
      return weekstamp(mktime(0,0,0,12,31,($year-1)));
    }

    if ($week == 53)
    {
      if ((strftime("%w", $yearEnd) >= 1) && (strftime("%w", $yearEnd)<= 3))
      {
        //atkdebug("(weekstamp): adjust to following year");
        return ($year+1)."01";
      }
    }

    return $year.sprintf("%02d", $week);
  }

  /*
   * Given a date in the form "2001-03-25", this function returns the date of the first
   * day (monday) of that week.
   * @deprecated use dateUtil::startOfWeek instead (note that it has a slightly different format)
   */
  function startOfWeek($date)
  {
    $viewtime = adodb_mktime(0,0,0,substr($date,5,2),substr($date,8,2),substr($date,0,4));
    $weekday = strftime("%w",$viewtime);
    if ($weekday==0) $weekday=7;
    return date("Y-m-d" ,$viewtime-(86400*($weekday-1)));
  }

  /*
   * Given a date in the form "2001-03-25", this function returns the date of the last
   * day (friday) of that week.
   * @deprecated use dateUtil::endOfWeek instead (note that it has a slightly different format)
   */
  function endOfWeek($date)
  {
    $viewtime = adodb_mktime(0,0,0,substr($date,5,2),substr($date,8,2),substr($date,0,4));
    $weekday = strftime("%w",$viewtime);
    if ($weekday==0) $weekday=7;
    return date("Y-m-d" ,$viewtime-(86400*($weekday-7)));
  }

  /**
   * Generic achievo mail function used when sending mails
   *
   * @param string/array $to Recipients e-mail address(es) (may not be empty, otherwise usermail fails and returns false)
   * @param string $subject Subject to be used when sending the mail (will be prefixed by [achievo notice], but may not be empty, otherwise usermail fails and returns false)
   * @param string $body Mail content
   * @param string $add_header SMTP Mail headers to be added to the mail
   * @return boolean True if succesfull, false if not
   */
  function usermail($to, $subject, $body, $add_header="")
  {
    // Determine the sender's nom by using the mail_sender configuration variable
    $sender = atkconfig("mail_sender", "association");

    // If multiple recipients in array, then convert the recipients array to a comma seperated string
    if (is_array($to) && count($to)>0)
    {
      $to = implode(",", $to);
    }

    // If no recipient or subject found, dont attempt to sent
    if (($to=="") || ($subject==""))
    {
      atkdebug("No mail sent, missing to or subject");
      return false;
    }

    // Attempt to send the mail, and store the result in $result
    $result = mail($to, "[association notice] " . $subject, $body, "From: " . $sender . "\r\n" . $add_header);

    // Show debug info
    atkdebug($result ? "Sent mail to $to" : "Sending of mail to $to failed");

    // Use the mail result as return value
    return $result;
  }

  function time_format($time, $displayzero=false)
  {
    if ($time==0)
    {
      if ($displayzero) return "00:00";
      return "&nbsp;";
    }
    return ($time<0?"-":"").floor(abs($time)/60).":".sprintf("%02d",(abs($time)%60));
  }



?>
