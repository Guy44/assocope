<?php
 function pimBlocNotes()
  {
    global $g_user;

    $userutilisateur = $g_user["id"];
    
    $db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu FROM app_utilisateur where id=$userutilisateur ");
	$userindividu=$data[0]["id_individu"];


    $rl = &atknew("atk.recordlist.atkrecordlist");
    $todonode = &atkGetNode("todo.todo");
    $todonode->m_flags |= NF_NO_SEARCH;
    $todonode->m_action="admin";
    $actions = array();
    $actions["edit"] = "dispatch.php?atknodetype=todo.todo&atkaction=edit&atkselector=[pk]";

    $recs = $todonode->selectDb("todo.id_individu_a_faire='$userindividu' and todo.blocnotes_o_n='1'","","","","description");

    if (count($recs)>0)
    {
      $todo_assignedtome.= $rl->render($todonode,$recs,$actions,RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedtoyou",array(),"todoassignedtoyou");
    }
    else
    {
      $todo_assignedtome.= atktext("pim_todo_empty")."<br>";
    }
 

    $res = '<table border="0">';
    $res.= '<tr>';
    $res.= '<td valign="top">'.$todo_assignedtome.'</td>';

    $res.= '</tr></table>';
    return $res;
  }




  function pimTodos()
  {
    global $g_user;

    $userutilisateur = $g_user["id"];
    
    $db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu FROM app_utilisateur where id=$userutilisateur ");
	$userindividu=$data[0]["id_individu"];


    $rl = &atknew("atk.recordlist.atkrecordlist");
    $todonode = &atkGetNode("todo.todo");
    $todonode->m_flags |= NF_NO_SEARCH;
    $todonode->m_action="admin";
    $todonode->addFilter("todo.id_type_etat_todo IN (2,4)");
    $actions = array();
    $actions["edit"] = "dispatch.php?atknodetype=todo.todo&atkaction=edit&atkselector=[pk]";
       $actions["delete"] = "dispatch.php?atknodetype=todo.todo&atkaction=delete&atkselector=[pk]";
    

    $recs = $todonode->selectDb("todo.id_individu_a_faire='$userindividu' AND todo.id_individu_a_faire <> 0");
    $todo_assignedtome = atktext("pim_assignedtoyou").":<br>";
    if (count($recs)>0)
    {
      $todo_assignedtome.= $rl->render($todonode,$recs,$actions,RL_MRA|RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedtoyou",array(),"todoassignedtoyou");
    }
    else
    {
      $todo_assignedtome.= atktext("pim_todo_empty")."<br>";
    }
    $todo_assignedtome.= '<br>'.href("dispatch.php?atknodetype=todo.todo&atkaction=add&atkfilter=".rawurlencode("id_individu_a_faire='$userutilisateur'"),atktext('add'),SESSION_NESTED);

    $todo_assignedbyme = atktext("pim_assignedbyyou").":<br>";
    $recs = $todonode->selectDb("todo.id_modification='$userutilisateur' AND todo.id_individu_a_faire<>'$userindividu'");
    if (count($recs)>0)
    {
      $todo_assignedbyme.= $rl->render($todonode,$recs,$actions,RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedbyyou",array(),"todoassignedbyyou");
    }
    else
    {
      $todo_assignedbyme.= atktext("pim_todo_empty")."<br>";
    }
    $todo_assignedbyme.= '<br>'.href("dispatch.php?atknodetype=todo.todo&atkaction=add",atktext('add'),SESSION_NESTED);

    $res = '<table border="0">';
    $res.= '<tr>';
    $res.= '<td valign="top">'.$todo_assignedtome.'</td>';
    $res.= '</tr><tr><td>&nbsp;</td></tr><tr>';
    $res.= '<td valign="top">'.$todo_assignedbyme.'</td>';
    $res.= '</tr></table>';
    return $res;
  }

?>