<?php
  define("DEP_INSTALL", 1);
  define("DEP_RUN"    , 2);
  define("DEP_ALL"    , DEP_INSTALL|DEP_RUN);
  atkimport("recactionlistener");

 class associationModule extends atkModule
  {
    function associationModule($name="")
    {
      $this->atkModule($name);
    }

//function &newNode($node) 
//{ 
 //atkdebug("début redéfinition newnode GUY");
//$instance = &parent::newNode($node); 
//$instance->addListener(new RecActionListener());
//return $instance; 
//} 

    function getPimItems()
    {
      return array();
    }
    function search($expression)
    {
      return array();
    }
    function getDependencies($mode)
    {      
      return array();
    }
    
    function recLinks($recordset, $nodetype)
    {
      $node = &getNode($nodetype);      
      
      $res = array();
      
      for($i=0, $_i=count($recordset); $i<$_i; $i++)
      {
        $item["title"] = $node->descriptor($recordset[$i]);
        $item["url"] = dispatch_url($nodetype, "view", array("atkselector"=>$node->primaryKey($recordset[$i])), "dispatch.php");
        $res[] = $item;
      }
            
      return $res;
    }
  }
?>