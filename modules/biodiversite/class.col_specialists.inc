<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_specialists extends assMetaNode {
	var $table = "col_specialists";
	function col_specialists() {
		$this->atkMetaNode();
		$this->atkNode("col_specialists", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"specialist_name",
   "database_id"
   )), AF_NO_LABEL));
   $this->add(new atkAttribute("record_id"),100);
   $this->add(new atgTextLibelleAttribute("specialist_name", AF_SEARCHABLE),110);
//   $this->add(new atkAttribute("database_id"),150);
    $this->add(new atkManyToOneRelation("database_id", "biodiversite.col_databases", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),150);
   
   $this->setExtendedSearchAction('smartsearch');
   $this->addListener(atknew("atk.utils.atkeventlog"));
   $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[specialist_name]";
	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>