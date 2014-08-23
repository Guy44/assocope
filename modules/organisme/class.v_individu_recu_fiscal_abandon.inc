<?php
class v_individu_recu_fiscal_abandon extends assMetaNode
{
	var $table="v_individu_recu_fiscal_abandon";
function meta(&$policy)
  {

	// $policy-> addFlags("nom","courriel","code_postal","ville", AF_SEARCHABLE);

	$policy->setOrder("nom");
}
function v_individu_recu_fiscal_abandon ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_individu_recu_fiscal_abandon", NF_ADD_LINK);
	$this->add(new atkRowCounter("#"),NULL,1);
		$this->add(new atkDateAttribute("date_reglement","d/m/Y","d/m/Y", 0, 0, AF_DATE_STRING));
	//$this->add(new atkAttribute("id", AF_PRIMARY));
	//$this->add(new atkAttribute("id_lieu", AF_PRIMARY));
	$this->setExtendedSearchAction('smartsearch');
			$this->m_securityMap["recu_maj"] = "view";
	$this->m_securityMap["document"] = "view";
		$this->setSecurityAlias("organisme.organisme");


  

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
	function action_recu_maj(& $handler) {
		$db = & atkGetDb();
		$sql="update organisme_abandon_creance
				 set date_envoi_recu_fiscal='".gmdate(c)."'  
				where date_operation is not null and date_envoi_recu_fiscal is null 
				and id_organisme=" . $this->m_postvars["id"] . "";
				global $g_user;
		$userutilisateur = $g_user["id"];
		$db->query("UPDATE organisme
		set id_recu_abandon_creance= " . $userutilisateur. " , date_recu_abandon_creance=UTC_TIMESTAMP(), id_modification=" . $userutilisateur . ", date_modification=UTC_TIMESTAMP()
		where id=" . $this->m_postvars["id"] . "");

		$nombre = $db->query($sql);
		echo "La date envoi des reçus pour abandon de créance a été mise à jour : " . $nombre;
		echo "<br />";
		die();
	}
//*/
    
function descriptor_def()
  {
    return "[nom]";
  }

}

?>