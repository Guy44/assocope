<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_distribution extends assMetaNode {
	var $table = "col_distribution";
	function col_distribution() {
		$this->atkMetaNode();
		$this->atkNode("col_distribution", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"name_code",
   "distribution"

   )), AF_NO_LABEL));
   $this->add(new atkAttribute("record_id"),100);
   $this->add(new atgTextLibelleAttribute("name_code", AF_SEARCHABLE),110);

   $this->add(new atkTextAttribute("distribution", array (	'rows' => '2'),Null),120);
   $this->setExtendedSearchAction('smartsearch');
   $this->addListener(atknew("atk.utils.atkeventlog"));
   $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[distribution]";
	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>