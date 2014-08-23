<?php
useattrib("development.atgtextnomattribute");
class organisme_pda extends atkNode {
	var $table = "organisme";

	function organisme_pda() {
				$this->atkNode("organisme_pda", NF_READONLY);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY));
		$this->add(new atkTextAttribute("telephone", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("courriel", AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("site_internet", AF_POPUP));
		$this->setOrder("nom");
		$this->setIndex("nom");
		$this->setTable("organisme");
				
}
	function descriptor_def() {
		return "[nom]";
	}
}
?>