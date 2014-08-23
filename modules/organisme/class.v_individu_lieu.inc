<?php
class v_individu_lieu extends assMetaNode
{
	var $table="v_individu_lieu";
function meta(&$policy)
  {

	$policy-> addFlags("nom","courriel","code_postal","ville", AF_SEARCHABLE);

	$policy->setOrder("nom");
}
function v_individu_lieu ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_individu_lieu", NF_EXPORT|NF_IMPORT|NF_ADD_LINK);
	$this->add(new atkRowCounter("#"),NULL,1);
	$this->add(new atkAttribute("id", AF_PRIMARY));
	$this->setExtendedSearchAction('smartsearch');
	$this->setSecurityAlias("individu.individu");
  	$this->m_securityMap["document"] = "view";


      $this->add(new atkEmailAttribute("courriel"));
  
	

	$this->setIndex("nom");
  }
  ///*
  
 
  function assignDocumentVars( &$documentWriter, $selector)
    {
  switch($this->m_postvars["atkcode"])
  {

	case 1:

	
      $records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");

	     $documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");

 	$org=&atkGetNode("organisme.v_organisme_lieu");
 	$orgrecord=$org->selectDb("v_organisme_lieu.id=".$this->m_postvars["id"], "", "", "", "", "view");
 	$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0], $prefix = "o.");
 
	$documentWriter->assignDocumentGenericVars();
    break;
    
    case 2 :
   $records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
   $documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");
   $documentWriter->assignDocumentGenericVars();
    break;
    
      case 3 :
  $org=&atkGetNode("organisme.v_organisme_lieu");
 	$orgrecord=$org->selectDb("v_organisme_lieu.id=".$this->m_postvars["id"], "", "", "", "", "view");
 	$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0], $prefix = "o.");
 
	$documentWriter->assignDocumentGenericVars();
    break;
    
      
    }
    }
//*/
    
function descriptor_def()
  {
    return "[nom]";
  }



}

?>