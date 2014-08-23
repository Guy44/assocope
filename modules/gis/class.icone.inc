<?php

useattrib("development.atgfileblobattribute");
useattrib("development.atgtextlibelleattribute");
  useattrib("development.atgblobattribute");
include_once (moduleDir("application")."class.document_proto.inc");
class icone extends document_proto {
	var $table = "gis_icone";
	function meta(& $policy) {

		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "file_lock_id", "file_lock_date", "file_extension", "file_name", AF_READONLY);

		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy-> addFlags("file_content","file_lock_date","file_lock_id",AF_HIDE);

	}
	function icone() {
				global $ATK_VARS,$g_user;

    $this->document_proto("icone",null);

		$this->setSecurityAlias("gis.placemark");
$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkManyToOneRelation("id_type_icone", "table.type_icone", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		//	$this->add(new atkManyToOneRelation("id_type_document","table.type_document",AF_SEARCHABLE|AF_RELATION_AUTOLINK|AF_OBLIGATORY));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" libelle ");
		$this->setIndex("libelle");
	}


	function descriptor_def() {
		return " [id] [libelle] ";
	}



}
?>