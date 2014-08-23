<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_envoi_groupe extends assMetaNode {
	var $table = "type_envoi_groupe";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_envoi_groupe() {
		$this->atkMetaNode();
		$this->atkNode("type_envoi_groupe",  NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
//				"nombre",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
			// ,
	//		"Envois groupe" => array (
//				"individu"
//			)
		), AF_NO_LABEL));

/*			$this->add(new atkOneToManyRelation("individu", "individu.envoi_groupe_i", "id_envoi_groupe", AF_HIDE_LIST));
				$this->add(new atkExpressionenvoi_groupee("nombre", ' select count(id) from individu_envoi_groupe
 where id_envoi_groupe =[table].id
				', 0, 0));
*/
						include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
/*			function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("individu.envoi_groupe_i", "admin", array (
				'atkfilter' => "individu_envoi_groupe.id_envoi_groupe='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
*/
	
	function descriptor_def() {
		return "[libelle]";
	}

}
?>