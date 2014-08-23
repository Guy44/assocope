<?php

  class mod_development extends associationModule
  {
    function getNodes()
    {
  
 registerNode("development.traitement", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
    
    }

}


?>