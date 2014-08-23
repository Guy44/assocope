<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
class calendrier_groupe_travail extends assMetaNode {
	var $table = "organisme_calendrier_groupe_travail";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function calendrier_groupe_travail() {
		$this->atkMetaNode();
		$this->atkNode("calendrier_groupe_travail", NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_calendrier",
				"id_groupe_travail",
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

				$this->add(new atkManyToOneRelation("id_calendrier", "organisme.calendrier", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				$this->add(new atkManyToOneRelation("id_groupe_travail", "organisme.groupe_travail", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),210);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");

				$this->setOrder("id_groupe_travail");

	}

	
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	/*
	 * 
	function descriptor_def() {
		return "([id_organisme.nom]) [nom] ";
	}
	 */

	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);

	}

}
?>