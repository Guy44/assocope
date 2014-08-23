<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class aide extends assMetaNode {
	var $table = "app_aide";
	function meta(& $policy) {
		$policy->addFlags("libelle","module", "node", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function aide() {
		$this->atkMetaNode();
		$this->atkNode("aide",  NF_MRA);

		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"module",
				"node",
				"mots_cles",
				"description",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Mots-Clés"=> array (
				"mots_cles"
			)
		), AF_NO_LABEL));
			$this->add(new atkfckattribute("description","", AF_SEARCHABLE,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'800px',
                 'Height'=>'150px')), "contenu"); 
        $this->add(new atkOneToManyRelation("mots_cles", "application.aide_mot_cle", "id_aide", AF_HIDE_LIST));
  
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("module, node");
	}
	  function initial_values()
  {
  	if (isset($this->m_postvars["module"]) and isset($this->m_postvars["node"]))
  {
     return array("module"=>$this->m_postvars["module"],
                  "node"=>$this->m_postvars["node"]);
  }
  }
  
	function descriptor_def() {
		return "[libelle]";
	}

}
?>