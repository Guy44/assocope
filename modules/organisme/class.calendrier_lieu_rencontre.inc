<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
class calendrier_lieu_rencontre extends assMetaNode {
	var $table = "organisme_calendrier_lieu_rencontre";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function calendrier_lieu_rencontre() {
		$this->atkMetaNode();
		$this->atkNode("calendrier_lieu_rencontre",NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_calendrier",
				"id_lieu_rencontre",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				/*,
				 "Rencontres" => array (
				 "lieu_rencontre"
				 )
				 ,
				 "Groupes_de_travail" => array (
				 "groupe"
				 )
				 */
				), AF_NO_LABEL));

				$this->add(new atkManyToOneRelation("id_calendrier", "organisme.calendrier", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.lieu_rencontre", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),210);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");

				$this->setOrder("id_lieu_rencontre");

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