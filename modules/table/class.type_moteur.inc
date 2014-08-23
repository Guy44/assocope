<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_moteur extends assMetaNode {
	var $table = "type_moteur";
	function meta(& $policy) {
		$policy->addFlags("sujet","moteur", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_moteur() {
		$this->atkMetaNode();
		$this->atkNode("type_moteur",  NF_ADD_LINK| NF_ADDAFTERADD  | NF_MRA);
  	$this->add(new atkattribute("nombre_acces",AF_READONLY),45);
		$this->add(new atgTextLibelleAttribute("moteur",AF_SEARCHABLE |AF_OBLIGATORY),100);
		$this->add(new atgTextLibelleAttribute("sujet",AF_SEARCHABLE |AF_OBLIGATORY),200);
		$this->add(new atgTextLibelleAttribute("sujet_anglais",AF_SEARCHABLE |AF_OBLIGATORY),300);
		$this->add(new atkTextAttribute("url_recherche", array (
	'autoadjust' => 'yes',
	'rows' => '6'
),AF_SEARCHABLE |AF_OBLIGATORY),400);
		$this->add(new atkTextAttribute("url_site",AF_SEARCHABLE |AF_OBLIGATORY),450);
		$this->add(new atkTextAttribute("url_english",AF_SEARCHABLE |AF_OBLIGATORY),500);
$this->add(new atkDummyAttribute("explication",'[string] sera remplacé par le texte recherché<br />
[lang] sera remplacé par le code langue choisi
[assocope] sera remplacé par url racine',AF_HIDE_LIST),420);
		$this->setSecurityAlias("table.activite");


		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("sujet");
		$this->setOrder("moteur, sujet");
	}
	function descriptor_def() {
		return "[moteur] [sujet]";
	}
	function preAdd(& $record) {
		$record["nombre_acces"]=0;
	parent :: preAdd($record);
	}

}
?>