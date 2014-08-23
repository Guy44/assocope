<?php
class v_organisme_remise_banque extends assMetaNode
{
	var $table="v_organisme_remise_banque";
function meta(&$policy)
  {

}
function v_organisme_remise_banque ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_organisme_remise_banque",NF_ADD_LINK);
	$this->add(new atkRowCounter("#"),NULL,1);
	$this->setIndex("nom");
			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["document"] = "view";
  }
 
  function assignDocumentVars(&$documentWriter, $selector)
    {
  
	
	$db = &atkGetDb();
     $records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
      $documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");

 	$org=&atkGetNode("organisme.remise_banque");
  	$orgrecord=$org->selectDb("organisme_remise_banque.id=".$this->m_postvars["id"], "", "", "", "", "view");
 	$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0]);
 
	$documentWriter->assignDocumentGenericVars();
   
    }
//*/
    
function descriptor_def()
  {
    return "[nom]";
  }

}

?>