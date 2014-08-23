<?php
class v_organisme_lieu extends assMetaNode
{
	var $table="v_organisme_lieu";
function meta(&$policy)
  {

	$policy-> addFlags("nom","courriel","code_postal","ville", AF_SEARCHABLE);

	$policy->setOrder("nom");
}
function v_organisme_lieu ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_organisme_lieu",NF_ADD_LINK);
	$this->add(new atkRowCounter("#"),NULL,1);
	$this->add(new atkAttribute("id", AF_PRIMARY));
	$this->add(new atkAttribute("id_lieu", AF_PRIMARY));
	$this->setExtendedSearchAction('smartsearch');
	$this->setSecurityAlias("organisme.organisme");
	  	$this->m_securityMap["document"] = "view";


      $this->add(new atkEmailAttribute("courriel"));
  

	$this->setIndex("nom");
  }

 function assignDocumentVars( &$documentWriter, $selector)
    {
  switch($this->m_postvars["atkcode"])
  {

	case 1:

    break;
    
    case 2 :
   $records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
   $documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");
   //$documentWriter->assignDocumentGenericVars();
    break;
    
      case 3 :
  
    break;
    }
    }
    
function descriptor_def()
  {
    return "[nom]";
  }

}

?>