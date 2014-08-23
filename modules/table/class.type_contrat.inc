<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class type_contrat extends assMetaNode {
	var $table = "type_contrat";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_contrat() {
		$this->atkMetaNode();
		$this->atkNode("type_contrat", NF_ADD_LINK| NF_ADDAFTERADD  );
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE),50);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
		"nombre",
		"modifiable_o_n",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"contrats" => array (
				"contrat"
				)
				), AF_NO_LABEL));
				$this->add(new atkOneToManyRelation("contrat", "organisme.contrat", "id_type_contrat", AF_HIDE_LIST));

				$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from organisme_contrat
 where id_type_contrat =[table].id
				', 0, 0),60);
				$this->add(new atkBoolAttribute("modifiable_o_n",AF_READONLY),70);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");

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
	
	function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("organisme.contrat", "admin", array (
				'atkfilter' => "organisme_contrat.id_type_contrat='" . $record['id'] . "'"
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