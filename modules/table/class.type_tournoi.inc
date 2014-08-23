<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");

class type_tournoi extends assMetaNode {
	var $table = "type_tournoi";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_tournoi() {
		$this->atkMetaNode();
		$this->atkNode("type_tournoi",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"nombre_par_equipe",
				"formule_de_jeu",
				"type_de_championnat",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE),100);
				$this->add(new atkNumberAttribute("nombre_par_equipe"),120);
				$this->add(new atgTextLibelleAttribute("formule_de_jeu", AF_SEARCHABLE | AF_UNIQUE),130);
				$this->add(new atkListAttribute("type_de_championnat", array ("round_robin","finale"),
				array(0,1)));


				//	$this->add(new atkOneToManyRelation("ecritures", "organisme.ecriture_comptable", "id_type_banque", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");

				$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}
	function preAdd(& $record) {
		if ($record["nombre_par_equipe"<1]) {
			triggerError($record, "", "Ce nombre doit être >0");
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		if ($record["nombre_par_equipe"<1]) {
			triggerError($record, "", "Ce nombre doit être >0");
		}
		parent :: preUpdate($record);
	}
		function initial_values() {
			return array (
			"nombre_par_equipe" => '1'
			);
		}
}
?>