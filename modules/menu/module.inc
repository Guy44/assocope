<?php

  class mod_menu extends associationModule
  {
    function getNodes()
    {
      registerNode("menu.menu", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall","export","import"));
     
    }

  
}


?>