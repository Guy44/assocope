<?php



// Same as listattribute, but then without save

class dummydurationfattribute extends atkListAttribute 
{

  function dummydurationfattribute($name)
  {
    $flags = AF_HIDE_SEARCH | AF_NO_SORT | AF_LIST_NO_NULL_ITEM;
    $optionArray = array('0:15','0:30','0:45','1:00','1:30','2:00','2:30','3:00','3:30','4:00','4:30','5:00','5:30','6:00','6:30','7:00','7:30','8:00','9:00','10:00','11:00','12:00','13:00','14:00','15:00','16:00','17:00','date fin');
    $valueArray = array(15,30,45,60,90,120,150,180,210,240,270,300,330,360,390,420,450,480, 540,600,660,720,780,840,900,960,1020,-1);
        parent::atkListAttribute($name,$optionArray,$valueArray,$flags,$size); 
  }
  
  function search($record="", $size=0, $maxsize=0)
  {
    return "&nbsp;";
  }
  
 /**
  * No function, but is neccesary
  */
  function store($a, $b)
  {
    return true;
  }

  function db2value($record)
  {
    atk_var_dump($record,"DURATION RECORD");
    $tmp_startdate = explode('-',$record['date_debut']);
    $tmp_enddate   = explode('-',$record['date_fin']);
    $tmp_starttime = explode(':',$record['heure_debut']);
    $tmp_endtime   = explode(':',$record['heure_fin']);
    
    
    $startdate = mktime(intval($tmp_starttime[0]),intval($tmp_starttime[1]),intval($tmp_starttime[2]),intval($tmp_startdate[1]),intval($tmp_startdate[2]),intval($tmp_startdate[0]));
    $enddate   = mktime(intval($tmp_endtime[0]),intval($tmp_endtime[1]),intval($tmp_endtime[2]),intval($tmp_enddate[1]),intval($tmp_enddate[2]),intval($tmp_enddate[0]));
    $diff = ($enddate-$startdate)/60;
    $valueArray = array(15,30,45,60,90,120,150,180,210,240,270,300,330,360,390,420,450,480, 540,600,660,720,780,840,900,960,1020);
    atkdebug("DURATION: DifF: $diff");
    if(in_array($diff,$valueArray)) return $diff;
    return -1;    
  }

  /**
  * No function, but is neccesary
  */
  function addToQuery(&$query, $tablename="", $fieldaliasprefix="",$level)
  {
  }

  function getSearchModes()
  {
    // exact match and substring search should be supported by any database.
    // (the LIKE function is ANSI standard SQL, and both substring and wildcard
    // searches can be implemented using LIKE)
    // Possible values
    //"regexp","exact","substring", "wildcard","greaterthan","greaterthanequal","lessthan","lessthanequal"
    return array();
  }

  function dbFieldType()
  {
    return "";
  }
  
  function needsUpdate()
  {
    return false;
  }
  
  
  
}


?>