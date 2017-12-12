<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class type_golf_abonnement extends assMetaNode {
	var $table = "type_golf_abonnement";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_golf_abonnement() {
		$this->atkMetaNode();
		$this->atkNode("type_golf_abonnement",  NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
//		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE ));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));

			
						include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	
	
	function descriptor_def() {
		return "[libelle]";
	}

}
?>