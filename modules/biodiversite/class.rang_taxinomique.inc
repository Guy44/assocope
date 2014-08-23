<?php
atkimport("atk.assmetanode");
useattrib("development.atgNumberExpressionAttribute");

useattrib("development.atgtextlibelleattribute");
class rang_taxinomique extends assMetaNode {
	var $table = "biodiversite_rang_taxinomique";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function rang_taxinomique() {
		$this->atkMetaNode();
		$this->atkNode("rang_taxinomique", NF_ADDAFTERADD | NF_ADD_LINK  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"id",
				"id_ordre",
		"rang_inpn",
		"nombre",
		"statut_inpn",
				"nom_latin",
				"nom_francais",
				"nom_anglais",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Taxinomies" => array (
				"taxinomie"
			)
				), AF_NO_LABEL));
				$this->add(new atkAttribute("id"));
				$this->add(new atkAttribute("rang_inpn"));
				$this->add(new atkAttribute("statut_inpn"));
				$this->add(new atgTextLibelleAttribute("nom_latin", AF_SEARCHABLE));
				$this->add(new atgTextLibelleAttribute("nom_francais", AF_SEARCHABLE));
				$this->add(new atgTextLibelleAttribute("nom_anglais", AF_SEARCHABLE));
				$this->add(new atkOneToManyRelation("taxinomie", "biodiversite.taxinomie", "id_rang_taxinomique", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setIndex("nom_latin");
				$this->setOrder("id_ordre");
				
				$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from biodiversite_taxinomie
	 where id_rang_taxinomique =[table].id 					', 0, 0));
							
				$this->setSecurityAlias("organisme.organisme");
	}
	function descriptor_def() {
		return "[nom_latin]-[nom_francais]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	function recordActions($rec, & $actions, & $mraactions) {
	
		$mraactions['delete'] = "delete";
		}
	function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			$ret=href(dispatch_url("biodiversite.taxinomie", "admin", array (
				'atkfilter' => "biodiversite_taxinomie.id_rang_taxinomique='" . $record['id'] . "'"
					,'view' => "requete"
				), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
				if ($record["nombre"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return '0';
		} else {
			return "";
		}
	}
	
}
?>