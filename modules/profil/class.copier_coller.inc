<?php
class copier_coller extends atkMetaNode {
	function copier_coller() {
		$this->atkMetaNode();
		$this->atkNode("copier_coller", NF_NO_ADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		//	$this->add(new atkOneToManyRelation("ecritures", "organisme.ecriture_comptable", "id_type_banque", AF_HIDE_LIST));
		$this->add(new atkAttribute("id", AF_SEARCHABLE | AF_PRIMARY, 5, 2), 5);
		$this->add(new atkAttribute("id_utilisateur", AF_SEARCHABLE, 5, 2), 45);
		$this->add(new atkAttribute("nom_variable", AF_SEARCHABLE, 5, 2), 30);
		$this->add(new atkAttribute("id_variable", AF_SEARCHABLE, 5, 2), 40);
		$this->add(new atkAttribute("date_creation", AF_SEARCHABLE, 5, 2), 20);
		//		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->m_securityMap["fiche"] = "delete";
		$this->m_securityMap["liens"] = "delete";
			$this->m_securityMap["delete"] = "view";
		$this->setTable("tmp_copier_coller");
		$this->add(new atkDummyAttribute("nom", "nom"), 10);
		$this->setIndex("nom_variable");
		$this->setOrder("nom_variable");
	}
	function descriptor_def() {
		return "[nom_variable]";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['fiche'] = "fiche";
		$mraactions['liens'] = "liens";
		$mraactions['delete'] = "delete";
	}
	function nom_display($record) {
		if ($record["nom_variable"] == 'id_individu') {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT nom, prenom from individu where id=" . $record['id_variable'] . "");
			return $data[0]["nom"] . ' ' . $data[0]["prenom"];
		}
	}
	function action_fiche() {
		$select = $this->m_postvars["atkselector"];
		if (count($select)>1)
		{echo "Vous ne devez sélectionner qu'un seul individu";
		die();}
		$array_id = explode('=', $select[0]);
		$id_copier = $array_id[1];
		$db = & atkGetDb();
			$data = $db->getrows("SELECT id_variable from tmp_copier_coller where id=" . $id_copier . "");		
		$url = dispatch_url("individu.individu", "fiche", array (
				"id" => $data[0]["id_variable"]
			));
		header("Location: $url");
		exit;
	}
		function action_liens() {
		$select = $this->m_postvars["atkselector"];
		if (count($select)!=2)
		{echo "Vous devez sélectionner deux individus";
		die();}
		$array_id = explode('=', $select[0]);
		$id_copier = $array_id[1];
		$db = & atkGetDb();
			$data = $db->getrows("SELECT id_variable from tmp_copier_coller where id=" . $id_copier . "");
			$id_individu1=$data[0]["id_variable"];
		$array_id = explode('=', $select[1]);
		$id_copier = $array_id[1];
		$db = & atkGetDb();
			$data = $db->getrows("SELECT id_variable from tmp_copier_coller where id=" . $id_copier . "");
			$id_individu2=$data[0]["id_variable"];		
		$url = dispatch_url("individu.individu", "liens", array (
				"id1" => $id_individu1,
				"id2" => $id_individu2
			));
		header("Location: $url");
		exit;
	}
}
?>