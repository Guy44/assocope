<?php

  class mod_todo extends associationModule
  {
    function getNodes()
    {
      // registerNode("todo.todo", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
     
    }
  	function getGgNodeName()
	{
		$res=array();
		$module="todo";
	 $res[]= $module."."."todo";
	 return $res;
	}
    function getMenuItems()
    {
   
  }
     function getPimItems()
    {
      return array("todos"=>"getTodo",
      "blocnotes"=>"getBlocNotes");
    }

    function getTodo()
    {
      include_once(moduleDir("todo")."pim.inc");
      return pimTodos();
    }
    function getBlocNotes()
    {
      include_once(moduleDir("todo")."pim.inc");
      return pimBlocNotes();
    }
}


?>