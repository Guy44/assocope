<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class competence extends assMetaNode {
	var $table = "type_competence";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function competence() {
		$this->atkMetaNode();
		$this->atkNode("competence", NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"nombre",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Individus" => array (
				"individu"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("individu", "individu.competence_i", "id_type_competence", AF_HIDE_LIST));
		$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from individu_competence
 where id_type_competence =[table].id
				', 0, 0));
						include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
				function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("individu.competence_i", "admin", array (
				'atkfilter' => "individu_competence.id_type_competence='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>