<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class type_attribut extends assMetaNode {
	var $table = "type_attribut";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_attribut() {
		$this->atkMetaNode();
		$this->atkNode("type_attribut",  NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
//		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE ));
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

				$this->add(new atkOneToManyRelation("individu", "individu.attribut_i", "id_attribut", AF_HIDE_LIST));
				$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from individu_attribut
 where id_attribut =[table].id
				', 0, 0));
						include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
			function nombre_display($record, $mode) {
//				$this->p($record);
		if (isset ($record["nombre"])) {
			return href(dispatch_url("individu.attribut_i", "admin", array (
				'atkfilter' => "individu_attribut.id_attribut='" . $record['id'] . "'"
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