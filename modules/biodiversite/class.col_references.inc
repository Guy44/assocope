<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_references extends assMetaNode {
	var $table = "col_references";
	function col_references() {
		$this->atkMetaNode();
		$this->atkNode("col_references", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"author",
   "year",
  "title" ,
  "source",
  "database_id"
  )), AF_NO_LABEL));
  $this->add(new atkAttribute("record_id"),100);
  $this->add(new atgTextLibelleAttribute("author", AF_SEARCHABLE),110);
  $this->add(new atgTextLibelleAttribute("year", AF_SEARCHABLE),120);
  $this->add(new atgTextLibelleAttribute("title", AF_SEARCHABLE),130);
  $this->add(new atgTextLibelleAttribute("source", AF_SEARCHABLE),140);
//  $this->add(new atkAttribute("database_id"),150);
    $this->add(new atkManyToOneRelation("database_id", "biodiversite.col_databases", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),150);
  
  $this->setExtendedSearchAction('smartsearch');
  $this->addListener(atknew("atk.utils.atkeventlog"));
  $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[title]";
	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>