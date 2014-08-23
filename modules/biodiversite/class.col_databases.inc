<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_databases extends assMetaNode {
	var $table = "col_databases";
	function col_databases() {
		$this->atkMetaNode();
		$this->atkNode("col_databases", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
  "database_name_displayed" ,
  "record_id" ,
  "database_name"  ,
  "database_full_name" ,
  "web_site" ,
  "organization"  ,
  "contact_person" ,
  "taxa"  ,
  "taxonomic_coverage" ,
  "abstract"  ,
  "version"  ,
  "release_date"  ,
  "SpeciesCount" ,
  "SpeciesEst" ,
  "authors_editors"  ,
  "accepted_species_names" ,
  "accepted_infraspecies_names" ,
  "species_synonyms" ,
  "infraspecies_synonyms"  ,
  "common_names"  ,
  "total_names" ,
  "is_new" 
  )), AF_NO_LABEL));
  $this->add(new atkAttribute("record_id"),100);
  $this->add(new atgTextLibelleAttribute("database_name_displayed", AF_SEARCHABLE),110);
  $this->add(new atgTextLibelleAttribute("database_name", AF_SEARCHABLE),120);
  $this->add(new atgTextLibelleAttribute("database_full_name", AF_SEARCHABLE),130);
  $this->add(new atkUrlAttribute("web_site", AF_POPUP | AF_SEARCHABLE), 140);
  $this->add(new atgTextLibelleAttribute("organization", AF_SEARCHABLE),150);
  $this->add(new atgTextLibelleAttribute("contact_person", AF_SEARCHABLE),160);
  $this->add(new atgTextLibelleAttribute("taxa", AF_SEARCHABLE),170);
  $this->add(new atgTextLibelleAttribute("taxa", AF_SEARCHABLE),180);

  $this->add(new atgTextLibelleAttribute("taxonomic_coverage", AF_SEARCHABLE),190);
  $this->add(new atgTextLibelleAttribute("abstract", AF_SEARCHABLE),200);
  $this->add(new atgTextLibelleAttribute("version", AF_SEARCHABLE),210);
  $this->add(new atgTextLibelleAttribute("release_date", AF_SEARCHABLE),220);
  $this->add(new atgTextLibelleAttribute("SpeciesCount", AF_SEARCHABLE),230);
  $this->add(new atgTextLibelleAttribute("SpeciesEst", AF_SEARCHABLE),240);
  $this->add(new atgTextLibelleAttribute("authors_editors", AF_SEARCHABLE),250);
  $this->add(new atgTextLibelleAttribute("accepted_species_names", AF_SEARCHABLE),260);
  $this->add(new atgTextLibelleAttribute("accepted_infraspecies_names", AF_SEARCHABLE),270);
  $this->add(new atgTextLibelleAttribute("species_synonyms", AF_SEARCHABLE),280);
  $this->add(new atgTextLibelleAttribute("infraspecies_synonyms", AF_SEARCHABLE),290);
  $this->add(new atgTextLibelleAttribute("common_names", AF_SEARCHABLE),300);
  $this->add(new atgTextLibelleAttribute("total_names", AF_SEARCHABLE),310);
  $this->add(new atgTextLibelleAttribute("is_new", AF_SEARCHABLE),320);
  $this->setExtendedSearchAction('smartsearch');
  $this->addListener(atknew("atk.utils.atkeventlog"));
  $this->setSecurityAlias("table.activite");
	}
	function descriptor_def() {
		return "[database_name_displayed]";
	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>