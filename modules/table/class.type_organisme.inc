<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class type_organisme extends assMetaNode {
	var $table = "type_organisme";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_organisme() {
		$this->atkMetaNode();
		$this->atkNode("type_organisme", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
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
			"Organismes" => array (
				"organismes"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("organismes", "organisme.organisme", "id_type_organisme", AF_HIDE_LIST));
						$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from organisme
 where id_type_organisme =[table].id
				', 0, 0));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}
			function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("organisme.organisme", "admin", array (
				'atkfilter' => "organisme.id_type_organisme='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}

}
?>