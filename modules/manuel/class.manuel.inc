<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class manuel extends assMetaNode {
	var $table = "organisme_regle";
	var $m_count = 0;
	function countDb($selector = "", $excludeList = "", $includeList = "", $mode = "") {
		$this->m_count = parent :: countDb($selector, $excludeList, $includeList, $mode);
		return $this->m_count;
	}
	function meta(& $policy) {
		$policy->addFlags("titre", AF_SEARCHABLE);
		$policy->addFlags("definition", "mise_en_oeuvre", "commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setTabs("definition","definition_html","définition");
		//		$policy->setTabs("mise_en_oeuvre", "mise en oeuvre");
		//		$policy->setTabs("commentaire", "commentaire");
		//$policy->setOrder("titre");
	}
	function manuel() {
		$this->atkMetaNode();
		$this->atkNode("manuel",  NF_ADD_LINK  );
		$this->setOrder("titre");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_organisme",
				"titre",
				"definition",
				"definition_html",
				"id_document",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Mise en oeuvre" => array (
				"mise_en_oeuvre"
			)
		), AF_NO_LABEL));
		$this->add(new atgTextLibelleAttribute("titre", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("definition", array (
			'autoadjust' => 'yes',
			'rows' => '2'
		)));
		$this->add(new atkTextAttribute("mise_en_oeuvre", array (
			'autoadjust' => 'yes',
			'rows' => '2'
		)));
		$this->add(new atkfckattribute("definition_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '750px',
			'Height' => '150px'
		)));
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atgFileManyToOneRelation("id_document", "organisme.document", AF_SEARCHABLE | AF_RELATION_AUTOCOMPLETE));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" date_modification DESC ");
		$this->setIndex("titre");
	}
	function descriptor_def() {
		return "[titre] ";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}	
}
?>