<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
useattrib("development.atgFileManyToOneRelation");
class parcours_observation extends assMetaNode {
	var $table = "biodiversite_parcours_observation";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function parcours_observation() {
		$this->atkMetaNode();
		$this->atkNode("parcours_observation", NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"nom",
				"id_organisme",
				"id_individu_auteur",
		"date_creation_parcours",
				"description",
				"id_document",
		"points",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
						 /*,
				 "Points" => array (
				 "points"
				 )
		,
				 "Groupes_de_travail" => array (
				 "groupe"
				 )
				 */
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("nom", AF_SEARCHABLE),100);
				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				$this->add(new atkManyToOneRelation("id_individu_auteur", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
				$date_modification = & $this->add(new atkDateTimeAttribute("date_creation_parcours", "Y-m-d", "hh:mm:ss",  AF_DATE_STRING | AF_HIDE_VIEW|AF_READONLY| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD));
				$this->add(new atkOneToManyRelation("points", "biodiversite.parcours_point_observation", "id_parcours_observation"),142);
						
				$this->add(new atgFileManyToOneRelation("id_document", "organisme.document",  AF_HIDE_LIST  |AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1400);
				$this->add(new atkfckattribute("description", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '50px'
			)),1300);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
//			$this->setOrder("biodiversite_parcours_observation.nom");
//			$this->setIndex("biodiversite_parcours_observation.nom");
	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function descriptor_def() {
		return "([id_organisme.nom]) [biodiversite_parcours_observation.nom] ";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
	}
function id_individu_auteur_display($record, $mode) {
		(!empty($record["id_individu_auteur"])) ? $retour=$this->descripteur_individu($record["id_individu_auteur"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

}
?>