<?php
class web_i extends assMetaNode {
	var $table = "individu_web";
	function meta(& $policy) {

		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

	}
	function web_i() {
		$this->atkMetaNode();
		$this->atkNode("web_i", NF_ADD_LINK );
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));


		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function descriptor_def() {
		return "[titre]";
	}

}
?>