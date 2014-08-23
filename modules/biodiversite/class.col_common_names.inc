<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_common_names extends assMetaNode {
	var $table = "col_common_names";
	function col_common_names() {
		$this->atkMetaNode();
		$this->atkNode("col_common_names", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"name_code",
  "common_name" ,
  "language" ,
  "country" ,
  "reference_id",
  "database_id",
  "is_infraspecies"

  )), AF_NO_LABEL));
  $this->add(new atkAttribute("record_id"),100);
  $this->add(new atgTextLibelleAttribute("name_code", AF_SEARCHABLE),110);
  $this->add(new atgTextLibelleAttribute("common_name", AF_SEARCHABLE),120);
  $this->add(new atgTextLibelleAttribute("language", AF_SEARCHABLE),150);
  $this->add(new atgTextLibelleAttribute("country", AF_SEARCHABLE),160);
// $this->add(new atkManyToOneRelation("reference_id", "biodiversite.col_references", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),170);
 $this->add(new atkAttribute("reference_id"),220);
 $this->add(new atkManyToOneRelation("database_id", "biodiversite.col_databases", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),180);
//  $this->add(new atkAttribute("database_id"),230);
  $this->add(new atkAttribute("is_infraspecies"),240);
  $this->setExtendedSearchAction('smartsearch');
  $this->addListener(atknew("atk.utils.atkeventlog"));
  $this->setSecurityAlias("table.activite");


  //		$this->setOrder("nombre_observations desc");
	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}

	function descriptor_def() {
		return "[common_name]";
	}

}
?>