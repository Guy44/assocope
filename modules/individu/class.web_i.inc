<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class web_i extends assMetaNode {
	var $table = "individu_web";
	function meta(& $policy) {

		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	}
	function web_i() {
		$this->atkMetaNode();
		$this->atkNode("web_i", NF_ADD_LINK | NF_EDITAFTERCOPY);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_individu",
				"id_organisme",
				"titre",
				"url",
				"url_admin",
				"code_admin",
				"mdp_admin",
				"cms",
				"version",
				"url_cms",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Hack1" => array (
				"url_stats_1",
				"code_stats_1",
				"loc_stats_1",

				),
			"Hack2" => array (
				"url_stats_2",
				"code_stats_2",
				"loc_stats_2",

				),
			"Hack3" => array (
				"url_stats_3",
				"code_stats_3",
				"loc_stats_3",

				)
				), AF_NO_LABEL));
				$this->setSecurityAlias("individu.individu");
				$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
				$this->add(new atkManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE |  AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),50);
				$this->add(new atgTextLibelleAttribute("titre", AF_SEARCHABLE),100);
				$this->add(new atkUrlAttribute("url",AF_POPUP|AF_SEARCHABLE),200);
				$this->add(new atkUrlAttribute("url_admin",AF_POPUP|AF_SEARCHABLE),300);
				$this->add(new atkAttribute("code_admin", AF_SEARCHABLE),400);
				$this->add(new atkAttribute("mdp_admin", AF_SEARCHABLE),500);
				$this->add(new atgTextLibelleAttribute("cms", AF_SEARCHABLE),600);
				$this->add(new atgTextLibelleAttribute("version", AF_SEARCHABLE),700);
				$this->add(new atkUrlAttribute("url_cms",AF_POPUP|AF_SEARCHABLE),750);
				$this->add(new atkUrlAttribute("url_stats_1",AF_POPUP|AF_SEARCHABLE),800);
				$this->add(new atkTextAttribute("code_stats_1", AF_HIDE_LIST),900);
				$this->add(new atkAttribute("loc_stats_1", AF_HIDE_LIST),1000);
				$this->add(new atkUrlAttribute("url_stats_2",AF_POPUP|AF_SEARCHABLE),1100);
				$this->add(new atkTextAttribute("code_stats_2", AF_HIDE_LIST),1200);
				$this->add(new atkAttribute("loc_stats_2", AF_HIDE_LIST),1300);
				$this->add(new atkUrlAttribute("url_stats_3",AF_POPUP|AF_SEARCHABLE),1400);
				$this->add(new atkTextAttribute("code_stats_3", AF_HIDE_LIST),1500);
				$this->add(new atkAttribute("loc_stats_3", AF_HIDE_LIST),1600);
				$this->setOrder("id_organisme , titre");
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function descriptor_def() {
		return "[titre]";
	}
	function action_admin($handler) {

		global $config_recordsperpage;
		$config_recordsperpage = 100;
		//		$this->p($postvars["atkfilter"]);
		return $handler->action_admin();
	}
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>