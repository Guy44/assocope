<?php

  class mod_editeur extends associationModule
  {
    function getNodes()
    {
  
 registerNode("editeur.editeur", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
    
    }

}


?>