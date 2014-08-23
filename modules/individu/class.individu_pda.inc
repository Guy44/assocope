<?php
useattrib("development.atgtextnomattribute");
class individu_pda extends atkNode {

	function individu_pda() {

		$this->atkNode("individu_pda", NF_READONLY);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY));
		$this->add(new atgTextNomAttribute("prenom", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("telephone_fixe", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("telephone_mobile", AF_SEARCHABLE));
		$this->add(new atkEmailAttribute("courriel", false, AF_SEARCHABLE));
		$this->add(new atkUrlAttribute("site_internet", AF_POPUP));
		$this->setOrder("nom,prenom");
		$this->setIndex("nom");
		$this->setTable("individu");
	}

	function descriptor_def() {
		return "[nom] [prenom]";
	}
	// GG deb

}
?>    
