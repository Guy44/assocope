<?php

  include_once($config_atkroot."atk.inc");

  atksession();
  atksecure();

//  Renders the help screen
//print_r ($_GET);
//die();
$type=$_GET["type"];
if ($type=="attribut_af_popup")
{
	$data = $_GET["field"];
}
else {
  $table = $_GET["table"];
  $id = $_GET["id"];
  $field = $_GET["field"];
$db = & atkGetDb();
$sql="SELECT $field from $table where id=$id";
$row=$db->getrows($sql);
   $data = '<div align="left">';
  $data .= $row[0]["$field"];
  $data .='</div>';
}
  $page = &atknew("atk.ui.atkpage");
  $ui = &atkinstance("atk.ui.atkui");

  $output = &atkOutput::getInstance();

  $page->register_style($ui->stylePath("style.css"));
  $res='<div align="right"><a href="javascript:window.close();">'.atktext("close").'</a></div><br />';

  $res .= $ui->renderBox(array("title"=>$title,
                                 "content"=>$data));
  $res.='<br><div align="right"><a href="javascript:window.close();">'.atktext("close").'</a></div>';

  $page->addContent($res);

  $output->output($page->render(atktext('app_title').' - '.atktext('html-popup'), true));

  $output->outputFlush();

?>