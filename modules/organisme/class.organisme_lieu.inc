<?php
atkimport("atk.assmetanode");
useattrib("development.atgomanytoonerelation");
class relatedville1 extends atkAttribute {
	function loadType() {
		return POSTLOAD;
	}
	function storageType() {
		return NOSTORE;
	}
	function load(& $db, $record, $mode) {
		//print_r($record);
		//die();
		$rows = $db->getrows("SELECT code_postal, ville from lieu l,type_cp_ville_pays  t where l.id='" . $record["id_lieu"]["id"] . "' and l.id_ville=t.id");
		return $rows[0]["code_postal"] . " " . $rows[0]["ville"];
	}
}
class organisme_lieu extends assMetaNode {
	var $table = "organisme_lieu";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function organisme_lieu() {
		$this->atkMetaNode();
		$this->atkNode("organisme_lieu",  NF_ADD_LINK );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), NULL, 20);
		$this->add(new atkBoolAttribute("adresse_defaut_o_n"));
		$this->add(new atkBoolAttribute("adresse_siege_social_o_n"));
		$this->add(new atkManyToOneRelation("id_lieu", "individu.lieu", AF_SEARCHABLE | AF_OBLIGATORY | AF_PRIMARY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE), NULL, 50);
		$this->add(new relatedville1("Ville", AF_READONLY), NULL, 60);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function initial_values() {
		$init_vals = array ();
		
		$init_vals["adresse_defaut_o_n"] = 1;

$init_vals["adresse_siege_social_o_n"] = 1;
		return $init_vals;
	}
	/*function descriptor_def()
	  {
	    return "[id_organisme.nom] - [id_lieu.id_ville.ville]";
	  }
	*/
	function preAdd(& $record) {
		$id_organisme = $record['id_organisme']['id'];
		$adressedefaut = $record['adresse_defaut_o_n'];
		$db = & atkGetDb();
		// en si déjà une 	adresse defaut et celle-ci ausi à défaut mettre cette dernière non défaut et avertir
		// s i aucune à défaut mettre celle-ci à défaut et avertir
		$rows = $db->getrows("select * from organisme_lieu where id_organisme='" . $id_organisme . "' ");
		if (count($rows) == 0) {
		} else {
			if ($record['adresse_defaut_o_n'] =='1')
			{$db->query("UPDATE organisme_lieu set adresse_defaut_o_n='0'   where id_organisme='" . $id_organisme . "' ");
			}
		if ($record['adresse_siege_social_o_n'] =='1')
			{$db->query("UPDATE organisme_lieu set adresse_siege_social_o_n='0'   where id_organisme='" . $id_organisme . "' ");
			}}

		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		$id_organisme = $record['id_organisme']['id'];
		$adressedefaut = $record['adresse_defaut_o_n'];
		$db = & atkGetDb();
		// en si déjà une 	adresse defaut et celle-ci ausi à défaut mettre cette dernière non défaut et avertir
		// s i aucune à défaut mettre celle-ci à défaut et avertir
		$rows = $db->getrows("select * from organisme_lieu where id_organisme='" . $id_organisme . "' ");
		if (count($rows) == 0) {
		} else {if ($record['adresse_defaut_o_n'] =='1')
			{$db->query("UPDATE organisme_lieu set adresse_defaut_o_n='0'   where id_organisme='" . $id_organisme . "' ");
			}
		if ($record['adresse_siege_social_o_n'] =='1')
			{$db->query("UPDATE organisme_lieu set adresse_siege_social_o_n='0'   where id_organisme='" . $id_organisme . "' ");
			}}

		parent :: preUpdate($record);
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>