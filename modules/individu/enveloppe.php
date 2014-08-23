<?php

 
  include_once("../../atk/document/tbsooo/tbs_class.php");
   include_once("../../atk/document/tbsooo/tbsooo_class.php");

// datas
$x = 'Test enveloppe';

// instantiate a TBS OOo class


$OOo = new clsTinyButStrongOOo;

// setting the object
$OOo->SetZipBinary('zip');
$OOo->SetUnzipBinary('unzip');
$OOo->SetProcessDir('../../atktmp');

// create a new openoffice document from the template with an unique id 
$OOo->NewDocFromTpl('enveloppe.odt');

// merge data with openoffice file named 'content.xml'
$OOo->LoadXmlFromDoc('content.xml');
$OOo->SaveXmlToDoc();

// display
header('Content-type: '.$OOo->GetMimetypeDoc());
header('Content-Length: '.filesize($OOo->GetPathnameDoc()));
$OOo->FlushDoc();
$OOo->RemoveDoc();
?>