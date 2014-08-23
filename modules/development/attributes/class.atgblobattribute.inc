<?php

  useattrib("atkattribute");
   
  class atgBlobAttribute extends atkAttribute
  {
   
    /**
     * Constructor
     *
     * @param String $name Unique name of this attribute within the node.
     * @param String $calculation The calculation to perform. Must be a valid php expression.
     * @param int $flags Flags of the attribute.
     */
    function atgBlobAttribute($name, $flags = 0, $size = 0)
    {
      $this->atkAttribute($name, $flags);
    }
     function loadType($mode)
     { 
 	 return NOLOAD; }
   
 
  
  }

?>