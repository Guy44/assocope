<?php

  class mod_divers extends associationModule
  {
    function getNodes()
    {
   
      registerNode("divers.mailinglist", array("admin", "report" ,"view" ,"view_all", "grantall"));
     

    
    }

}


?>