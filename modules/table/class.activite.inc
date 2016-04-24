<?php
atkimport("atk.assmetanode");

useattrib("development.atgtextlibelleattribute");
class activite extends assMetaNode {
	var $table = "type_activite";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function activite() {
		$this->atkMetaNode();
		$this->atkNode("activite",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Individus" => array (
				"individu"
			)
		), AF_NO_LABEL));
	$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));

		$this->add(new atkOneToManyRelation("individu", "individu.activite_i", "id_type_activite", AF_HIDE_LIST));
//		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
	$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		
		$mraactions['delete'] = "delete";
		
	}
/*	function action_delete() {
		if ("GG"=="GG")
		{echo "<pre><br/>";
		echo "Request<br/>";
		print_r($_REQUEST);
		echo "Post<br/>";
		print_r($_POST);
		echo "ATK_VARS<br/>";
		print_r($ATK_VARS);
		echo "atkescape<br/>";
		echo atkurldecode($_REQUEST["atkescape"]);
		echo "atkselector<br/>";
		print_r ($this->m_postvars["atkselector"]);
		echo "</pre><br/>";
		die();}
		
		$condition=$this->m_postvars["atkselector"];
		
		$this->redirect();
	}
	*/
	

}
?>