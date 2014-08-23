<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class reglement extends assMetaNode {
	var $table = "type_reglement";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function reglement() {
		$this->atkMetaNode();
		$this->atkNode("reglement",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
		"modifiable_o_n",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Ecritures" => array (
				"ecritures"
			)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("ecritures", "organisme.ligne_ecriture_comptable", "id_type_reglement", AF_HIDE_LIST));
						$this->add(new atkBoolAttribute("modifiable_o_n",AF_READONLY));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function initial_values()
	{
		return array("modifiable_o_n"=>"1");
	}
	function preUpdate(& $record) {
		if ($record["modifiable_o_n"]==0)
		{
			triggerError($record, "modifiable_o_n", "Cet enregistrement n'est pas modifiable");
			
		}
		else
		{
			parent::preUpdate($record);
		}
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>