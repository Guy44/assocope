<?php

  class pim extends atkNode
  {
    function pim()
    {
      $this->atkNode("pim",NF_NO_SECURITY);
    }

    function action_pim(&$handler)
    {
      if (atkconfig('pim_redirect_to') != "")
      {
        header("Location: " . atkconfig('pim_redirect_to'));
        return;
      }
      
      $pimItems = atkHarvestModules("getPimItems","",true);
      $userpimitems = &atknew("module.pim.userpimitems");
      $user = getuser();
      $userDbItems = $userpimitems->selectDb("app_pimitem.id_utilisateur='".$user["id"]."'","ordre","",array("id","id_utilisateur"));
      $disallowedpimitems = atkConfig("disallowedpimitems", array());
      $res = array();

      
      if(count($userDbItems)==0)
      {
        $res[atktext("title_pim","pim")] = '<br>'.atkText("pim_nopimitems","pim").'<br><br>';
      }
      else
      {
        $userItems = array();
        foreach($userDbItems as $key => $item)
        {
            $userItems[] = $item["pimitem"];
        }

        $res = "";
        foreach($pimItems as $modname => $item)
        {
          foreach($item as $itemName => $itemContent)
          {
            $pimitemid = $modname.'_'.$itemName;
            atkdebug("Check: ".$pimitemid);
            if(in_array($pimitemid, $userItems) && !in_array($pimitemid, $disallowedpimitems))
            {
              $module = &getModule($modname);
              if (is_object($module))
              {
                if (method_exists($module, $itemContent))
                {
                  $itemContent = $module->$itemContent();
                }
                $res[atktext(array("pim_$itemName", $itemName), $modname)] = $itemContent;
              }
            }
           }
        }
      }
       $page = &$this->getPage();
      $content = $this->renderContent(atktext("title_pim"),$res);
 
 
      $page->addContent($content);
   //                      print_r($content);
//      die();   
     }

    function getAdminPimContent()
    {
      // Generate the content
      $employeeadminlink = href(dispatch_url("employee.employee", "admin"), $this->text("clickhere", "pim"), SESSION_NESTED);
      $content = '<br><div align="left" style="width: 400px;">';
      $content.= '<b>' . $this->text("welcome") . '</b><br>';
      $content.= $this->text("loggedinasadmin") . '<br><br>';
      $content.= '<b>' . $this->text("setuppurposesonly") . '</b><br>';
      $content.= $this->text("notarealaccount") . '<br><br>';
      $content.= '<b>' . $this->text("firsttimeusage") . '</b><br>';
      $content.= sprintf($this->text("createfirstrealuseraccount"), $employeeadminlink) . '<br><br>';
      $content.= '<b>' . $this->text("upgradesandinstallations") . '</b><br>';
      $content.= $this->text("usesetuplink") . '<br><br>';
      $content.= '<b>' . $this->text("donations") . '</b><br>';
      $content.= $this->text("becomeasponsor") . '<br><br>';
      $content.= '<a href="http://www.achievo.org/support/donate" target="_new">';
      $content.= '<img border="0" src="modules/pim/paypal_donate.gif" alt="' . $this->text("donate") . '">';
      $content.= '</a>';
      $content.= '</div><br>';

      // Return the generated content
      return $content;
    }

    function action_adminpim(&$handler)
    {
      // Initialize the title and content
      $title = $this->text("title_pim_adminpim");
      $content = $this->getAdminPimContent();

      // Render the page
      $page = &$this->getPage();
      
      $content = $this->renderContent($title,$content);
      $page->addContent($content);
    }
    
     function action_acceptecontrat(&$handler)
    {
      // Initialize the title and content
      $session = &atkSessionManager::getSession();
      $session["contrat_accepte"]=0;
      $title = $this->text("Clause de confidentialité");
      $content = $this->getacceptecontrat();

      // Render the page
      $page = &$this->getPage();
      
      $content = $this->renderContent($title,$content);
      $page->addContent($content);
    }
    
       function action_reponseutilisateur(&$handler)
    {
  		global $g_sessionManager;
		$positif = strip_tags($g_sessionManager->stackVar("positif"));
		$negatif = strip_tags($g_sessionManager->stackVar("negatif"));
  	 $session = &atkSessionManager::getSession();
		if (!empty($positif))
		{
			$title = $this->text("Clauses de confidentialité acceptées");
			$content='Bienvenue dans AssoCope';
			$session["contrat_accepte"]=1;
			$destination = session_url(dispatch_url("pim.pim", "pim"),SESSION_NEW);
			$db = & atkGetDb();
			$user = getuser();
			$idut=$user["id"];
					$db = & atkGetDb();
		$data = $db->getrows("SELECT texte_contrat_utilisateur from app_globales ");
		$texte_contrat=$db->escapeSQL($data[0]["texte_contrat_utilisateur"]);
		
			$db->query("update app_utilisateur set date_signature_contrat=UTC_TIMESTAMP()
			, texte_contrat_utilisateur='".$texte_contrat."'
			
			where id='".$idut."'");
    				
		}
		else 
		{
			$destination = 'index.php?atklogout=1'.' target="_top"';
		}
header("Location: " . $destination);   
				return ;
    }
    
  	function getacceptecontrat() 
  	{
		$db = & atkGetDb();
		$data = $db->getrows("SELECT texte_contrat_utilisateur, date_texte_contrat from app_globales ");
		$texte_contrat=$data[0]["texte_contrat_utilisateur"];
		$date_texte_contrat=$data[0]["date_texte_contrat"];
		$res = '<td align="left"><form name="contrat" action="dispatch.php"' . ($targetframe != "" ? 'target="' . $targetframe . '"' : '') . '>';

		$res .= '<input type="hidden" name="atknodetype" value="pim.pim">';
		$res .= '<input type="hidden" name="atkaction" value="reponseutilisateur">';
		$res .= session_form(SESSION_NESTED);
		$res .= '<b>Clauses d\'utilisation de l\'application (version du '.$date_texte_contrat.') : &nbsp;</b><br />' . $texte_contrat . '<br />';
		$res .= '&nbsp;<input type="submit" name="positif" value="' . atktext("J'accepte") . '">';
		$res .= '&nbsp;<input type="submit" name="negatif" value="' . atktext("Je refuse") . '">';
		$res .= '</form></td>';
		return $res;
	}
    
    function renderContent($title,$content)
    {
      $theme = &atkinstance('atk.ui.atktheme');
      if ($theme->getAttribute('useframes',true))
      {
         $renderd_content = $this->genericPage($title, $content);        
      }
      else 
      {
         $ui = &$this->getUi();
         
          if (!is_array($content)) $content = array($title=>$content);
          $renderd_content="";
          foreach($content as $itemtitle => $itemcontent)
           $renderd_content.= $ui->renderBox(array("title"=>$itemtitle, "content"=>$itemcontent));
      }
      return $renderd_content;
    }
  }

?>