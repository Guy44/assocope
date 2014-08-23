<?php

  function pimContacts()
  {
    global $g_user;

  $userutilisateur = $g_user["id"];
//    $userutilisateur=32;
    $db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu FROM app_utilisateur where id=$userutilisateur ");
	$userindividu=$data[0]["id_individu"];


    $rl = &atknew("atk.recordlist.atkrecordlist");
    $contactnode = &atkGetNode("individu.contact_i");
    $contactnode->m_flags |= NF_NO_SEARCH;
    $contactnode->m_action="admin";
    $contactnode->addFilter("date_realisee IS NULL");
    $actions = array();
    $actions["edit"] = "dispatch.php?atknodetype=individu.contact_i&atkaction=edit&atkselector=[pk]";
    $actions["delete"] = "dispatch.php?atknodetype=individu.contact_i&atkaction=delete&atkselector=[pk]";
    $recs = $contactnode->selectDb("(individu_contact.id_individu='$userindividu' OR individu_contact.id_contact='$userindividu')");
          $contact_assignedtome = atktext("contact_vous_concernant").":<br>";
    if (count($recs)>0)
    {
      $contact_assignedtome.= $rl->render($contactnode,$recs,$actions,RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedtoyou",array(),"todoassignedtoyou");
      
    }
    else
    {
      $contact_assignedtome.= atktext("pas_de_contact")."<br>";
    }
    $contact_assignedtome.= '<br>'.href("dispatch.php?atknodetype=individu.contact_i&atkaction=add&atkfilter=".rawurlencode("id_individu='$userindividu'"),atktext('add'),SESSION_NESTED);

    $contact_assignedbyme = atktext("contacts_crees_par_vous_et_ne_vous_concernant_pas").":<br>";
    $recs = $contactnode->selectDb("individu_contact.id_modification='$userutilisateur' AND individu_contact.id_individu!='$userindividu' AND individu_contact.id_contact!='$userindividu' ");
    if (count($recs)>0)
    {
      $contact_assignedbyme.= $rl->render($contactnode,$recs,$actions,RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedbyyou",array(),"todoassignedbyyou");
    }
    else
    {
      $contact_assignedbyme.= atktext("pas_de_contact")."<br>";
    }
    $contact_assignedbyme.= '<br>'.href("dispatch.php?atknodetype=todo.todo&atkaction=add",atktext('add'),SESSION_NESTED);

    $res = '<table border="0">';
    $res.= '<tr>';
    $res.= '<td valign="top">'.$contact_assignedtome.'</td>';
    $res.= '</tr><tr><td>&nbsp;</td></tr><tr>';
    $res.= '<td valign="top">'.$contact_assignedbyme.'</td>';
    $res.= '</tr></table>';
    return $res;
  }
  
    function pimRencontres()
  {
    global $g_user;

    $userutilisateur = $g_user["id"];
    
    $db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu FROM app_utilisateur where id=$userutilisateur ");
	$userindividu=$data[0]["id_individu"];


    $rl = &atknew("atk.recordlist.atkrecordlist");
    $rencontrenode = &atkGetNode("individu.rencontre_i");
    $rencontrenode->m_flags |= NF_NO_SEARCH;
    $rencontrenode->m_action="admin";
     $actions = array();
    $actions["edit"] = "dispatch.php?atknodetype=individu.rencontre_i&atkaction=edit&atkselector=[pk]";
$ilyaunesemaine = mktime(0,0,0,date("m")+1,date("d"),date("Y"));
$ilyaunesemaine=date("Y-md", $ilyaunesemaine);
    $recs = $rencontrenode->selectDb("individu_rencontre.id_individu='$userindividu' AND" .
    		" individu_rencontre.id_rencontre IN " .
    		" (SELECT id from organisme_rencontre where date_debut >= UTC_DATE() and date_debut < '".$ilyaunesemaine."')");
    $rencontre_assignedtome = atktext("rencontre_ou_vous_etes_inscrit").":<br>";
    if (count($recs)>0)
    {
      $rencontre_assignedtome.= $rl->render($rencontrenode,$recs,$actions,RL_NO_EXTENDED_SEARCH|RL_NO_SEARCH|RL_NO_SORT, array(),"todoassignedtoyou",array(),"todoassignedtoyou");
    }
    else
    {
      $rencontre_assignedtome.= atktext("pas_de_rencontre")."<br>";
    }
    
    $res = '<table border="0">';
    $res.= '<tr>';
    $res.= '<td valign="top">'.$rencontre_assignedtome.'</td>';
    $res.= '</tr><tr><td>&nbsp;</td></tr><tr>';
     $res.= '</tr></table>';
    return $res;
  }
  
  function pimActivite()
  {
  	// GG
 //   return; 
    global $g_user;
    $activitesnode = &getNode("individu.activite_i");
/*
    $pda = browserInfo::detectPDA();
    if ($pda) $nodetype = "timereg.hourspda";
    else $nodetype = "timereg.hours";
*/


	$nodetype = "individu.activite_i";
    $actions = array();
//    if(!$pda)
      $actions["edit"] = "dispatch.php?atknodetype=$nodetype&atkaction=edit&atkselector=[pk]";


    $userutilisateur = $g_user["id"];
    
    $db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu FROM app_utilisateur where id=$userutilisateur ");
	$userindividu=$data[0]["id_individu"];
	
    // Show only todays bookings, and only your own.
    $activitesnode->addFilter("date_debut_periode",strftime("%Y-%m-%d"));
    $activitesnode->addFilter("individu_activite.id_individu",$userindividu);

    $recs = $activitesnode->selectDb();

    if (count($recs)>0)
    {
      $recordlist = &atknew("atk.recordlist.atkrecordlist");
      $todayhours = $recordlist->render($activitesnode, $recs, $actions);
    }
    else
    {
      $todayhours = atktext('activite_pas_d_activite_aujourdhui').'<br>';
    }
  //  if ($pda) $nodetype = "timereg.hourspda";
//    else $nodetype = "timereg.hours";
	$nodetype = "individu.activite_i";
    $todayhours.= '<br>'.href("dispatch.php?atknodetype=$nodetype&atkaction=add",atktext('add'),SESSION_NESTED);
 
  //  if (!$pda) $todayhours.= ' &nbsp; '.href("dispatch.php?atknodetype=$nodetype&atkaction=admin",atktext('activite_enregistrer_des_activites'),SESSION_NESTED);
	
	$todayhours.= ' &nbsp; '.href("dispatch.php?atknodetype=$nodetype&atkaction=admin",atktext('activite_enregistrer_des_activites'),SESSION_NESTED);
    $res = '<table border="0">';
    $res.= '<tr>';
   //  if (!$pda) 
   //  $res.= '<td width="15">&nbsp;</td>'; // spacer
    $res.= '<td valign="top">'.$todayhours.'</td>';
     $res.= '</tr><tr><td>&nbsp;</td></tr><tr>';
    $res.= '</tr></table>';

    return $res;
  }
  

?>