<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
useattrib("development.atgFileManyToOneRelation");
class parcours_point_observation extends assMetaNode {
	var $table = "biodiversite_parcours_point_observation";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function parcours_point_observation() {
		$this->atkMetaNode();
		$this->atkNode("parcours_point_observation", NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_parcours_observation",
				"id_point_observation",
				"consignes",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				/*,
				 "Rencontres" => array (
				 "rencontre"
				 )
				 ,
				 "Groupes_de_travail" => array (
				 "groupe"
				 )
				 */
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_parcours_observation", "biodiversite.parcours_observation", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
				$this->add(new atkManyToOneRelation("id_point_observation", "biodiversite.point_observation", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
				

$this->add(new atkfckattribute("consignes", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '50px'
			)),1300);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->setOrder("date_creation desc");

	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function descriptor_def() {
		return "[id] ";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
	}
}
?>