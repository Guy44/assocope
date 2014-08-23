<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class scheduler_vacances extends assMetaNode {
	var $table = "scheduler_vacances";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function scheduler_vacances() {
		$this->atkMetaNode();
		$this->atkNode("scheduler_vacances",  NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
					$this->add(new atkBoolAttribute("vacances_scolaires_o_n"));
		$this->add(new atkDateAttribute("date_debut", "d F Y","d F Y", 0, 0));
		$this->add(new atkDateAttribute("date_fin", "d F Y","d F Y", 0, 0));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>