<?php

  class atgNoStorageAttribute extends atkAttribute
  {
    
    function atgNoStorageAttribute($name, $flags, $size)
    {
      $this->atkAttribute($name,  $flags, $size);
      
    }
  function loadType()
   {
     // this makes sure this attribute does not partake in the query that loads
     // data. Since we aren't a real relationship, we don't have anything to load.
     return NOLOAD;
   }
 
   function storageType()
   {
      return NOSTORE;
   }
   function display($record, $mode="")
   {
   	// the next if-statement is a workaround for derived attributes which do
   	// not override the display() method properly. This will not give them a
   	// working display() functionality but at least it will not give error messages.
   	if ($mode=="list" && $this->hasFlag(AF_POPUP) && $record[$this->fieldName()]!="")
   	{		$popup=atkPopup(atkconfig("atkroot").'atk/popups/htmlpopup.inc','type=attribut_af_popup&field='.$record[$this->fieldName()],$this->fieldName(),1000,800,'yes','yes');
   	return '<a href="'.$popup.'">'.nl2br(substr($record[$this->fieldName()],0,100)).'<br/><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/txt.png" alt='.$this->fieldName().
   	' title=' .$this->fieldName().' ></img></a>'. " ( ".strlen($record[$this->fieldName()])." caractères)";
   	}
   	if (!is_array($record[$this->fieldName()]))
   	{
   		// default behaviour is that we display a value 'as is'.
   		if (($mode=="csv")||($mode=="plain")) return $record[$this->fieldName()];
   		return nl2br(htmlspecialchars($record[$this->fieldName()]));
   	}
   }
    
  }
 
  

?>