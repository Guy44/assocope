<?php
/*
 * 
 class relatedville extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		$rows = $db->getrows("SELECT code_postal, ville from lieu l,type_cp_ville_pays  t where l.id='" . $record["id_lieu"]["id"] . "' and l.id_ville=t.id");
		return $rows[0]["code_postal"] . " " . $rows[0]["ville"];
	}
}
*/
class individu_lieu extends assMetaNode {
	var $table = "individu_lieu";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function individu_lieu() {
		$this->atkMetaNode();
		$this->atkNode("individu_lieu",  NF_ADD_LINK );
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), NULL, 20);
		$this->add(new atkBoolAttribute("adresse_defaut_o_n"));
				$this->add(new atkBoolAttribute("adresse_personnelle_o_n"));
	$this->add(new atkManyToOneRelation("id_lieu", "individu.lieu", AF_SEARCHABLE | AF_OBLIGATORY | AF_PRIMARY | AF_RELATION_AUTOLINK| AF_RELATION_AUTOCOMPLETE), NULL, 50);
// $this->add(new atkOneToOneRelation("id_lieu", "individu.lieu", null, AF_ONETOONE_INTEGRATE));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
function initial_values() {
		$init_vals = array ();
		
		$init_vals["adresse_defaut_o_n"] = 1;
$init_vals["adresse_personnelle_o_n"] = 1;

		return $init_vals;
	}
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	// GG deb
	function preAdd(& $record) {
		$id_individu = $record['id_individu']['id'];
		$adressedefaut = $record['adresse_defaut_o_n'];
		$db = & atkGetDb();
		// en si déjà une 	adresse defaut et celle-ci ausi à défaut mettre cette dernière non défaut et avertir
		// s i aucune à défaut mettre celle-ci à défaut et avertir
		$rows = $db->getrows("select * from individu_lieu where id_individu='" . $id_individu . "' ");
		if (count($rows) == 0) {
		} else {
			if ($record['adresse_defaut_o_n'] == '1')
			{	$db->query("UPDATE individu_lieu set adresse_defaut_o_n='0'   where id_individu='" . $id_individu . "' ");
			}
			if ($record['adresse_personnelle_o_n'] == '1')
			{	$db->query("UPDATE individu_lieu set adresse_personnelle_o_n='0'   where id_individu='" . $id_individu . "' ");
			}
		}
		
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$id_individu = $record['id_individu']['id'];
		$adressedefaut = $record['adresse_defaut_o_n'];
		$db = & atkGetDb();
		// en si déjà une 	adresse defaut et celle-ci ausi à défaut mettre cette dernière non défaut et avertir
		// s i aucune à défaut mettre celle-ci à défaut et avertir
		$rows = $db->getrows("select * from individu_lieu where id_individu='" . $id_individu . "' ");
		if (count($rows) == 0) {
		} else {
			if ($record['adresse_defaut_o_n'] == '1')
			{	$db->query("UPDATE individu_lieu set adresse_defaut_o_n='0'   where id_individu='" . $id_individu . "' ");
			}
			if ($record['adresse_personnelle_o_n'] =='1')
			{	$db->query("UPDATE individu_lieu set adresse_personnelle_o_n='0'   where id_individu='" . $id_individu . "' ");
			}		}

		parent :: preUpdate($record);
	}
	function descriptor_def() {
		return "[id_individu.nom] - [id_lieu.id_ville.ville]";
	}

}
?>