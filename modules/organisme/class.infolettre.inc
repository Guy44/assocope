<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgtextlibelleattribute");
class infolettre extends assMetaNode {
	var $table = "organisme_infolettre";
	function meta(& $policy) {

		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", "preparation", "contenu_html", AF_HIDE_LIST);
	}
	function infolettre() {
		$this->atkMetaNode();
		$this->atkNode("infolettre",  NF_ADD_LINK | NF_TRACK_CHANGES );
		$this->setSecurityAlias("organisme.organisme");
	$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY));

		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkfckattribute("contenu_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '600px'
		)), "contenu");
		$this->add(new atkDateAttribute("date_prevue", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkDateAttribute("date_envoi", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
		$this->add(new atkManyToOneRelation("id_type_audience", "table.audience", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" date_prevue DESC ");
		$this->setIndex("libelle");
	}
		function initial_values() {
			return array (
				"id_type_audience" => '7'			);
	
	}
	function descriptor_def() {
		return " [libelle] ";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>