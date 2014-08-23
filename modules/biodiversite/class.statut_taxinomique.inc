<?php
atkimport("atk.assmetanode");

useattrib("development.atgtextlibelleattribute");
class statut_taxinomique extends assMetaNode {
	var $table = "biodiversite_statut_taxinomique";
	function meta(& $policy) {
//		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function statut_taxinomique() {
		$this->atkMetaNode();
		$this->atkNode("statut_taxinomique", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id",
		"type_statut",
		"code_statut",
		"statut","couleur",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Taxinomies" => array (
				"taxinomie"
			)
				), AF_NO_LABEL));
				$this->add(new atkAttribute("id"));
				$this->add(new atkAttribute("type_statut"));
				$this->add(new atkAttribute("code_statut"));
				$this->add(new atkAttribute("statut"));
				$this->add(new atkAttribute("couleur"));
//				$this->add(new atkAttribute("commentaire"));
				$this->add(new atkOneToManyRelation("taxinomie", "biodiversite.taxinomie", "id_statut_france_metropole", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
$this->add($commentaire = new atkTextAttribute("commentaire", array (

	'rows' => '2'
), AF_HIDE_LIST),10000);
				$this->setOrder("type_statut, statut");
				$this->setSecurityAlias("organisme.organisme");
	}
	function descriptor_def() {
		return "[statut]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	function statut_display($record, $mode)
	{
		$couleur=$record["couleur"];
	
		return '<div style="background-color:'.$couleur.'">'.$record["statut"].'</div>';
	}
	function recordActions($rec, & $actions, & $mraactions) {
	
		$mraactions['delete'] = "delete";
		

	}
}
?>