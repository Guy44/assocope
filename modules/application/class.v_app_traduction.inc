<?php
atkimport("atk.assmetanode");

useattrib("development.atgNumberExpressionAttribute");
class v_app_traduction extends assMetaNode {
	var $table = "v_app_traduction";

	function v_app_traduction() {
		$this->atkMetaNode();
		$this->atkNode("v_app_traduction",  NF_NO_ADD );
		$this->setSecurityAlias("table.activite");

		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_type_langue",
				"id_type_traduction",
				"nombre"
				)), AF_NO_LABEL));


				$this->add(new atkManyToOneRelation("id_type_langue","table.type_langue",AF_SEARCHABLE|AF_RELATION_AUTOLINK),100);
				$this->add(new atkManyToOneRelation("id_type_traduction","table.type_traduction",AF_SEARCHABLE|AF_RELATION_AUTOLINK),200);
				$this->add(new atkNumberAttribute("nombre", 0,12, 0));

				$this->setOrder("id_type_langue, id_type_traduction");
	}
	function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return '<p style="text-align: right;"><b>' . href(dispatch_url("application.traduction", "admin", array (
				'atkfilter' => "app_traduction.id_type_langue='" . $record['id_type_langue']['id'] . "' 
				AND app_traduction.id_type_traduction='" . $record['id_type_traduction']['id'] . "' "
				), "dispatch.php"), text($record["nombre"]), SESSION_NESTED). '</b></p>';;
		} else {
			return "";
		}
	}

	function descriptor_def() {
		return "[id_type_langue][id_type_traduction]";
	}

}
?>