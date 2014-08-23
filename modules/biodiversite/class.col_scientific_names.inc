<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_scientific_names extends assMetaNode {
	var $table = "col_scientific_names";
	function col_scientific_names() {
		$this->atkMetaNode();
		$this->atkNode("col_scientific_names", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
		"name_code",
		"web_site",
	  "genus" ,
  "species",
  "infraspecies" ,
  "infraspecies_marker",
 "author" ,
  "accepted_name_code",
  "comment" ,
  "scrutiny_date",
  "sp2000_status_id" ,
  "database_id",
  "specialist_id",
  "family_id",
  "is_accepted_name"

  )), AF_NO_LABEL));
  $this->add(new atkAttribute("record_id"),100);
  $this->add(new atgTextLibelleAttribute("name_code", AF_SEARCHABLE),110);
  $this->add(new atkUrlAttribute("web_site", AF_POPUP | AF_SEARCHABLE), 120);
  $this->add(new atgTextLibelleAttribute("genus", AF_SEARCHABLE),150);
  $this->add(new atgTextLibelleAttribute("species", AF_SEARCHABLE),160);
  $this->add(new atgTextLibelleAttribute("infraspecies", AF_SEARCHABLE),170);
  $this->add(new atgTextLibelleAttribute("infraspecies_marker", AF_SEARCHABLE),180);
  $this->add(new atgTextLibelleAttribute("author", AF_SEARCHABLE),190);
  $this->add(new atgTextLibelleAttribute("accepted_name_code", AF_SEARCHABLE),200);
  $this->add(new atgTextLibelleAttribute("comment", AF_SEARCHABLE),210);
  $this->add(new atkAttribute("scrutiny_date"),220);
//  $this->add(new atkAttribute("sp2000_status_id"),230);
     $this->add(new atkManyToOneRelation("sp2000_status_id", "biodiversite.col_sp2000_statuses", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),230);
//  $this->add(new atkAttribute("database_id"),240);
  $this->add(new atkManyToOneRelation("database_id", "biodiversite.col_databases", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),240);
  
//  $this->add(new atkAttribute("specialist_id"),250);
  $this->add(new atkManyToOneRelation("specialist_id", "biodiversite.col_specialists", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),250);
 // $this->add(new atkAttribute("family_id"),260);
    $this->add(new atkManyToOneRelation("family_id", "biodiversite.col_families", AF_SEARCHABLE | AF_RELATION_AUTOLINK ),260);
  
  $this->add(new atkAttribute("is_accepted_name"),270);
  $this->setExtendedSearchAction('smartsearch');
  $this->addListener(atknew("atk.utils.atkeventlog"));
  $this->setSecurityAlias("table.activite");
}
	function descriptor_def() {
		return "[species]";
	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>