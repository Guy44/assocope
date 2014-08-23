<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");

class type_inscription extends assMetaNode {
	var $table = "type_inscription";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_inscription() {
		$this->atkMetaNode();
		$this->atkNode("type_inscription",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA | NF_COMPACT);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id_organisme",
				"libelle",
				"inscription_organisme_o_n",
				"cotisation_organisme_o_n",
				"tarif",
				"cotisation_federation_o_n",
				"carte_o_n",
				"timbre_o_n",
				"lettre_o_n",
				"infolettre_o_n",
		"flash_info_o_n",
				"delai_radiation_non_cotisation",
				"delai_radiation_non_adhesion",
			"modifiable_o_n",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE |AF_HIDE_LIST |  AF_COMPACT),null,50);
				$this->add(new atkAttribute("id", AF_HIDE_LIST | AF_FORCE_LOAD),null,51);
				$this->add(new atkAttribute("libelle",AF_COMPACT| AF_FORCE_LOAD),null,51);
				$this->add(new atkBoolAttribute("inscription_organisme_o_n"));
				$this->add(new atkBoolAttribute("cotisation_organisme_o_n"));
				$this->add(new atkListAttribute("tarif",
				array ('0','1','2','3' ),array ('0','1','2','3' )));
				$this->add(new atkBoolAttribute("cotisation_federation_o_n"));
				$this->add(new atkBoolAttribute("carte_o_n"));
				$this->add(new atkBoolAttribute("timbre_o_n"));
				$this->add(new atkBoolAttribute("lettre_o_n"));
				$this->add(new atkBoolAttribute("infolettre_o_n"));
								$this->add(new atkBoolAttribute("flash_info_o_n"));
				$this->add(new atkNumberAttribute("delai_radiation_non_cotisation"));
				$this->add(new atkNumberAttribute("delai_radiation_non_adhesion"));
				$this->add(new atkBoolAttribute("modifiable_o_n",AF_READONLY));
				$this->addUniqueFieldset(array("id_organisme","libelle"));
				
//				$this->add(new atkOneToManyRelation("individu", "individu.inscription_i", "id_type_inscription", AF_HIDE_LIST | AF_FORCE_LOAD));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL |AF_COMPACT),null,52 );
//				$this->setIndex("libelle");
				$this->setOrder("libelle");
	}

	function initial_values()
	{
		return array("tarif"=>"0", "modifiable_o_n"=>"1");
	}
/*	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"]["id"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"]) : $retour='';
		return $retour;
	}
	*/
	function libelle_display($record, $mode) {
	//	$this->p($record);
		(!empty($record["libelle"])) ? $retour=$this->descripteur_type_inscription($record["id"],null,$record["id_organisme"]["id"]) : $retour='';
		return $retour;
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