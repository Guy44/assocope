<?php

  class atgNoStorageAttribute extends atkAttribute
  {
    
    function atgNoStorageAttribute($name, $flags=0)
    {
      $this->atkAttribute($name,  $flags = 0, $size = 0);
      
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
  }
 
  

?>