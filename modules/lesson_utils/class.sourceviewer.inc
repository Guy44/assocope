<?php

  class sourceviewer extends atkNode
  {
    function sourceviewer()
    {
      $this->atkNode("sourceviewer");
    }

    function action_view()
    {
      global $g_sessionManager;

      $module = $g_sessionManager->pageVar("module");
      $node = $g_sessionManager->pageVar("node");

      if ($node=="")
      {
        $filename = moduleDir($module)."module.inc";
      }
      else
      {
        $filename = moduleDir($module)."class.".$node.".inc";
      }
      if (atkLevel()>0)
      {
 //       $content= '<br><br>'.atkButton(text("back"), "", SESSION_BACK, false);
      }
      $content = '<div align="left" style="font-size: 10pt">';

      if (strpos($filename, "..")===false)
      {

        $content.= '<br>Sourcecode of <b>'.$filename.'</b>:<br><br>';

        $content.= highlight_file($filename, true).'</div>';

      }
      else
      {
        $content = "Invalid path for source viewer.";
      }

      if (atkLevel()>0)
      {
        $content.= '<br><br>'.atkButton(text("back"), "", SESSION_BACK, false);
      }

      $ui = &$this->getUi();
      $output = $ui->renderBox(array("title"=>text("view_source"),
                                     "content"=>$content));

      $actionpage = $this->renderActionPage("view", $output);

      $page = &$this->getPage();
      $theme = &atkTheme::getInstance();
      $page->register_style($theme->stylePath("style.css"));
      $page->addContent($actionpage);
    }

  }

?>