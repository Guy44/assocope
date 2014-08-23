<?php

	useattrib("development.atgprintview1");

class printview extends atkNode
{

function printview()
{
   	$this->atkNode("printview", NF_EXPORT|NF_IMPORT|NF_ADD_LINK|NF_TRACK_CHANGES|NF_MRA);
	$this->setSecurityAlias("organisme.organisme");

	$this->add(new atgPrintView1("attribut_vue","vue",AF_HIDE_LIST|AF_NO_LABEL)); 

  }
    function dispatchPopup($target,$params,$winName,$width,$height,$scroll='no',$resize='no')
    {
      $url = session_url("dispatch.php?".$params, SESSION_NESTED);
      $popupurl ="javascript:NewWindow('".$url."','".$winName."',".$height.",".$width.",'".$scroll."','".$resize."','no','yes')";
      return $popupurl;
    }
        function attribut_vue_display($record)
    {
      $page = &$this->getPage();
      $page->register_script(atkconfig("atkroot")."atk/javascript/newwindow.js");
 
      $newattribute = &$this->getAttribute("attribut_vue");
      $sParams = str_ireplace("atkaction=view", "atkaction=attribut_vue", $_SERVER['QUERY_STRING']);
 
      // this constructs the button HTML.
      $content = $this->dispatchPopup('dispatch.php',$sParams,'printWindow',500,800, 'yes', 'yes');
      $temp = '<input type="button" value="PRINT" onClick="' . $content . '" />';
 
      // return the output.
      $output = $temp.$newattribute->display($record);
      return $output;
    }
       function action_attribut_vue(&$handler)
    {
        $ui = &$this->getUi();
        $newattribute = &$this->getAttribute("attribut_vue");
        $this->addStyle("style.css");
        $this->addStyle("recordlist.css");               
        $sel = $this->m_postvars["atkselector"];
 
        // create 'fake' record to pass to
        $theid = explode("=",$sel);
        $record = array("id"=>$theid[1]);
 
        if (is_object($ui) && is_object($newattribute))
        {
 
            $page = &$this->getPage();
            $page->head('attribut_vue');
            $page->body();
 
            $content_box = $ui->render("mytemplate.tpl",array("title"=>"NEW ATTRIBUTE",
                                                 "content"=>$newattribute->display($record)),
                                       "organisme.printview"
                                          );
 
            $page->addContent($content_box);
 
        }
 
    }// end function
}

?>