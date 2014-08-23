<?php
class v_individu_recu_fiscal extends assMetaNode
{
	var $table="v_individu_recu_fiscal";
function meta(&$policy)
  {

	// $policy-> addFlags("nom","courriel","code_postal","ville", AF_SEARCHABLE);

	$policy->setOrder("nom");
}
function v_individu_recu_fiscal ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_individu_recu_fiscal", NF_ADD_LINK);
	$this->add(new atkRowCounter("#"),NULL,1);
		$this->add(new atkDateAttribute("date_reglement","d/m/Y","d/m/Y", 0, 0, AF_DATE_STRING));
	//$this->add(new atkAttribute("id", AF_PRIMARY));
	//$this->add(new atkAttribute("id_lieu", AF_PRIMARY));
	$this->setExtendedSearchAction('smartsearch');
	



  

	$this->setIndex("nom");
  }
 
  function assignDocumentVars(&$documentWriter, $selector)
    {
  
	
	$db = &atkGetDb();

   	

      $records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
      $documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");

 	$org=&atkGetNode("organisme.v_organisme_lieu");
 	$orgrecord=$org->selectDb("v_organisme_lieu.id=".$this->m_postvars["id"], "", "", "", "", "view");
 	$documentWriter->assignDocumentSingleRecord($org, $orgrecord[0], $prefix = "o.");
 
	$documentWriter->assignDocumentGenericVars();
   
    }
//*/
    
function descriptor_def()
  {
    return "[nom]";
  }

}

?>