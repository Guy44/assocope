<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class col_taxa extends assMetaNode {
	var $table = "col_taxa";
	function col_taxa() {
		$this->atkMetaNode();
		$this->atkNode("col_taxa", NF_READONLY );
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"record_id",
				"name",
				"taxon",
				"ascendance",
				"descendance",
				"fratrie",
				"name_code",
				"lsid",
				"complements",
				"parent_id",
				"sp2000_status_id",
				"database_id",
				"is_accepted_name",
				"is_species_or_nonsynonymic_higher_taxon",
				"name_with_italics"

				)), AF_NO_LABEL));
				$this->add(new atkAttribute("record_id"),100);
				$this->add(new atgTextLibelleAttribute("name", AF_SEARCHABLE),110);
				$this->add(new atgTextLibelleAttribute("taxon", AF_SEARCHABLE),120);
				$this->add(new atgNumberExpressionAttribute("ascendance", ' 1', 0, 0),130);
				$this->add(new atgNumberExpressionAttribute("descendance", ' 1', 0, 0),140);
				$this->add(new atgNumberExpressionAttribute("fratrie", ' 1', 0, 0),145);
				$this->add(new atgTextLibelleAttribute("name_code", AF_SEARCHABLE),150);
				$this->add(new atgTextLibelleAttribute("lsid", AF_SEARCHABLE),160);
				$this->add(new atgNumberExpressionAttribute("complements", ' 1', 0, 0),165);
				$this->add(new atkAttribute("parent_id"),170);
				$this->add(new atkAttribute("sp2000_status_id"),180);
				$this->add(new atkAttribute("database_id"),190);
				$this->add(new atkAttribute("is_accepted_name"),200);
				$this->add(new atkAttribute("is_species_or_nonsynonymic_higher_taxon"),210);
				$this->add(new atkAttribute("name_with_italics"),220);
				$this->setExtendedSearchAction('smartsearch');
				$this->addListener(atknew("atk.utils.atkeventlog"));
				$this->setSecurityAlias("table.activite");

				//		$this->setOrder("nombre_observations desc");
	}
	function descriptor_def() {
		return "[name]";
	}
	function ascendance_display($record,$mode)
	{
		$record_id=$record["record_id"];
		$db = & atkGetDb();
		$rows = $db->getrows("select parent_id from col_taxa where record_id ='" . $record_id . "' ");
		$id_parent=$rows[0]["parent_id"];

		$ascendance="";
		$tableau_ascendance=array();
		while (isset($id_parent))
		{
			$sql="SELECT record_id,  parent_id, name, taxon
				from col_taxa
				where record_id='".$id_parent."' ";
			$data=$db->getrows($sql);
			$id_parent=$data[0]["parent_id"];
			$ascendance='<a target="_blank" href="dispatch.php?atknodetype=biodiversite.col_taxa&
				atkaction=view&atkselector=col_taxa.record_id='.$data[0]["record_id"]. '&">'.$data[0]["name"].'</a>'.'('.$data[0]["taxon"].') <br /> '.$ascendance;
		}
		return $ascendance;
	}
	function descendance_display($record, $mode)
	{
		$recordid=$record["record_id"];
		$db = & atkGetDb();
		$sql="SELECT count(record_id) as nombre from col_taxa where parent_id='".$recordid."' ";
		$data=$db->getrows($sql);
		$nombre_descendance=$data[0]["nombre"];
		if (isset ($nombre_descendance)) {
			$ret= href(dispatch_url("biodiversite.col_taxa", "admin", array (
				'atkfilter' => "col_taxa.parent_id='" . $recordid . "'"
				), "dispatch.php"), $nombre_descendance, SESSION_NESTED);
				if ($nombre_descendance!=0)			return '<b>'.$ret.'</b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function fratrie_display($record,$mode)
	{
		$id_parent=$record["parent_id"];
			
		$db = & atkGetDb();

		$sql="SELECT count(record_id) as nombre from col_taxa where parent_id='".$id_parent."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];

		if ($nombre>0) {
			$ret= href(dispatch_url("biodiversite.col_taxa", "admin", array (
				'atkfilter' => "col_taxa.parent_id='" . $id_parent . "'"
				), "dispatch.php"), '<b>'.$nombre.'</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function complements_display($record,$mode)
	{
		$name_code=$record["name_code"];
		$database_id=$record["database_id"];
		$db = & atkGetDb();
		$sql="SELECT count(record_id) as nombre from col_scientific_names where name_code='".$name_code."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_scientific_names= href(dispatch_url("biodiversite.col_scientific_names", "admin", array (
				'atkfilter' => "col_scientific_names.name_code='" . $name_code . "'"
				), "dispatch.php"), '<b>Scientific_names('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_scientific_names='<font color="red"><b>'.$ret_scientific_names.'</font></b>';
		} else {
			$ret_scientific_names= '<b>Scientific_names(0)</b>';
		}
		$sql="SELECT count(record_id) as nombre from col_common_names where name_code='".$name_code."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_common_names= href(dispatch_url("biodiversite.col_common_names", "admin", array (
				'atkfilter' => "col_common_names.name_code='" . $name_code . "'"
				), "dispatch.php"), '<b>Common_names('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_common_names='<font color="red"><b>'.$ret_common_names.'</font></b>';
		} else {
			$ret_common_names= '<b>Common_names(0)</b>';
		}
		$sql="SELECT count(record_id) as nombre from col_distribution where name_code='".$name_code."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_distribution= href(dispatch_url("biodiversite.col_distribution", "admin", array (
				'atkfilter' => "col_distribution.name_code='" . $name_code . "'"
				), "dispatch.php"), '<b>Distribution('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_distribution='<font color="red"><b>'.$ret_distribution.'</font></b>';
		} else {
			$ret_distribution= '<b>Distribution(0)</b>';
		}
		$sql="SELECT count(distinct reference_id) as nombre from col_scientific_name_references where name_code='".$name_code."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_references= href(dispatch_url("biodiversite.col_references", "admin", array (
				'atkfilter' => "col_references.record_id in (select distinct reference_id from col_scientific_name_references where name_code='" . $name_code . "')"
				), "dispatch.php"), '<b>Références('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_references='<font color="red"><b>'.$ret_references.'</font></b>';
		} else {
			$ret_references= '<b>Références(0)</b>';
		}
		$sql="SELECT count(distinct specialist_id) as nombre from col_scientific_names where name_code='".$name_code."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_specialists= href(dispatch_url("biodiversite.col_specialists", "admin", array (
				'atkfilter' => "col_specialists.record_id in (select distinct specialist_id from col_scientific_names where name_code='" . $name_code . "')"
				), "dispatch.php"), '<b>Spécialistes('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_specialists='<font color="red"><b>'.$ret_specialists.'</font></b>';
		} else {
			$ret_specialists= '<b>Spécialistes(0)</b>';
		}
		$sql="SELECT count(distinct record_id) as nombre from col_databases where record_id='".$database_id."' ";
		$data=$db->getrows($sql);
		$nombre=$data[0]["nombre"];
		if ($nombre>0) {
			$ret_databases= href(dispatch_url("biodiversite.col_databases", "admin", array (
				'atkfilter' => "col_databases.record_id ='" . $database_id . "'"
				), "dispatch.php"), '<b>Bases_de_données('.$nombre.')</b>', SESSION_NESTED);
				//				$this->p($record);

				if ($nombre!=0)			$ret_databases='<font color="red"><b>'.$ret_databases.'</font></b>';
		} else {
			$ret_databases= '<b>Bases_de_données(0)</b>';
		}

		$ret=$ret_scientific_names;
		$ret.='<br />';
		$ret.=$ret_common_names;
		$ret.='<br />';
		$ret.=$ret_distribution;
		$ret.='<br />';
		$ret.=$ret_references;
		$ret.='<br />';
		$ret.=$ret_specialists;
		$ret.='<br />';
		$ret.=$ret_databases;
		return $ret;



	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;

		return $handler->action_admin();
	}



}
?>