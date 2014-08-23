<?php
class cotorep_i extends assMetaNode {
	var $table = "individu_cotorep";
	function meta(& $policy) {
		$policy->addFlags("numero_dossier", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->setOrder("numero_dossier");
	}
	function cotorep_i() {
		$this->atkMetaNode();
		$this->atkNode("cotorep_i",  NF_ADD_LINK  );
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkDateAttribute("date_depot", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));

		$this->add(new atkDateAttribute("date_carte_invalidite", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkBoolAttribute("carte_stationnement_o_n"));
		$this->add(new atkDateAttribute("date_carte_stationnement", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_echeance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
	$this->add(new atkBoolAttribute("en_cours"));
						$this->add(new atkDateAttribute("date_dernier_contact_mdph", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function descriptor_def() {
		return "[numero_dossier]";
	}
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>