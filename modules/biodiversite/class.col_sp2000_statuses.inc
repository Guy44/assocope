<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_sp2000_statuses extends assMetaNode {
	var $table = "col_sp2000_statuses";
	function col_sp2000_statuses() {
		$this->atkMetaNode();
		$this->atkNode("col_sp_2000_statuses", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"sp2000_status"
   )), AF_NO_LABEL));
   $this->add(new atkAttribute("record_id"),100);
   $this->add(new atgTextLibelleAttribute("sp2000_status", AF_SEARCHABLE),110);
   $this->setExtendedSearchAction('smartsearch');
   $this->addListener(atknew("atk.utils.atkeventlog"));
   $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[sp2000_status]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>