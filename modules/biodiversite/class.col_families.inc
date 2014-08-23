<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_families extends assMetaNode {
	var $table = "col_families";
	function col_families() {
		$this->atkMetaNode();
		$this->atkNode("col_families", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
  "hierarchy_code" ,
  "kingdom" ,
  "phylum",
  "class",
  "order",
  "family",
  "superfamily" ,
  "family_common_name",
  "database_name",
  "is_accepted_name",
  "database_id" 
  )), AF_NO_LABEL));
  $this->add(new atkAttribute("record_id"),100);
  $this->add(new atgTextLibelleAttribute("hierarchy_code", AF_SEARCHABLE),110);
  $this->add(new atgTextLibelleAttribute("kingdom", AF_SEARCHABLE),120);
  $this->add(new atgTextLibelleAttribute("phylum", AF_SEARCHABLE),130);
  $this->add(new atgTextLibelleAttribute("class", AF_SEARCHABLE),140);
  $this->add(new atgTextLibelleAttribute("order", AF_SEARCHABLE),150);
  $this->add(new atgTextLibelleAttribute("family", AF_SEARCHABLE),160);
  $this->add(new atgTextLibelleAttribute("superfamily", AF_SEARCHABLE),170);
  $this->add(new atgTextLibelleAttribute("family_common_name", AF_SEARCHABLE),180);
  $this->add(new atgTextLibelleAttribute("database_name", AF_SEARCHABLE),190);
  $this->add(new atgTextLibelleAttribute("is_accepted_name", AF_SEARCHABLE),200);
  $this->add(new atkManyToOneRelation("database_id", "biodiversite.col_databases", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),210);

  $this->setExtendedSearchAction('smartsearch');
  $this->addListener(atknew("atk.utils.atkeventlog"));
  $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[family]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>