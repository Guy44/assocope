<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextnomattribute");
useattrib("development.atgNumberExpressionAttribute");
class bv_lieu_ville extends assMetaNode {
	var $table = "v_lieu_ville";
	function meta(& $policy) {

	}
	function bv_lieu_ville() {

		$this->atkMetaNode(array (
			"flags" => NF_NO_ADD | NF_MRA
		));
		$this->atkNode("bv_lieu_ville", NF_NO_ADD | NF_MRA);
		$this->setSecurityAlias("table.activite");

		$this->add(new atkTextAttribute("code_postal", AF_SEARCHABLE),900);

		$this->add(new atkTextAttribute("ville", AF_SEARCHABLE | AF_PRIMARY),910);
		$this->add(new atkTextAttribute("province", AF_SEARCHABLE | AF_PRIMARY),920);
		$this->add(new atkTextAttribute("libelle_francais", AF_SEARCHABLE),930);
		$this->add(new atkTextAttribute("id_pays", AF_SEARCHABLE | AF_PRIMARY),1000);
		$this->add(new atkTextAttribute("libelle_anglais", AF_SEARCHABLE),1010);
		$this->add(new atkTextAttribute("code_iso", AF_SEARCHABLE),1020);

		$this->add(new atgNumberExpressionAttribute("nb_observations_points",
		"select count(bo.id) from
biodiversite_observation bo,
biodiversite_point_observation po,
lieu l,
type_cp_ville_pays cp
where
bo.id_point_observation=po.id
and
po.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=[table].id_pays
and cp.province_etat=[table].province
and cp.ville=[table].ville"
), 30);
$this->add(new atgNumberExpressionAttribute("nb_observations_lieux",

"select count(bo.id) from
biodiversite_observation bo,

lieu l,
type_cp_ville_pays cp
where

bo.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=[table].id_pays
and cp.province_etat=[table].province
and cp.ville=[table].ville"	

), 40);
$this->add(new atgNumberExpressionAttribute("nb_observations_commune",

"select count(bo.id) from
biodiversite_observation bo,

type_cp_ville_pays cp
where
bo.id_ville=cp.id
and
cp.id_pays=[table].id_pays
and cp.province_etat=[table].province
and cp.ville=[table].ville"

), 50);
$this->add(	new atkCalculatorAttribute("nb_observations", "[nb_observations_points]+[nb_observations_lieux]+[nb_observations_commune]"),60);
	
include_once (atkconfig("atkroot") . "modules/include/actions.inc");
$this->m_securityMap["biolocalisation"] = "view";
$this->setOrder("(nb_observations_commune + nb_observations_lieux + nb_observations_points) desc");
$this->setTable($this->table); // set node table
	}
	/*	function nb_individus_display($record, $mode) {
		if ($record["nb_individus"] > 0) {
		return href(dispatch_url("individu.individu", "admin", array (
		'atkfilter' => "individu.id in ( select il.id_individu from

		individu_lieu il,
		lieu l,
		type_cp_ville_pays cp
		where
		il.id_lieu=l.id
		and
		l.id_ville=cp.id
		and
		cp.province_etat='" . $record['province'] ." '
		and
		cp.ville='" . $record['ville'] ." '
		and
		cp.id_pays=" . $record['id_pays'] ." )"), "dispatch.php"), text($record["nb_individus"]), SESSION_NESTED);
		} else {
		return "";
		}
		}
		*/
	function traitement_select_biolocalisation($select)
	{
		//		$this->p($select);
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$chaine = '('.$id_variable.')';


			$chainecondition .= $chaine . ' or ';
		}

		$chainecondition = str_replace("v_lieu_ville", "cp", $chainecondition);
		$chainecondition = str_replace("cp.province", "cp.province_etat", $chainecondition);
		$chainecondition = substr($chainecondition, 0, strlen($chainecondition) - 3);
		$chainecondition;

		return array (
			"taxons" => 0,
			"zones" => $chainecondition,
			"date_observation_debut" => 0,
			"date_observation_fin" => 0,
			"heure_observation_debut" => 0,
			"heure_observation_fin" => 0,
			"organismes_commanditaire" => 0,
			"organismes_observateur" => 0,
			"individus_observateur" => 0,
		);



	}
	function descriptor_def() {
		return "[libelle_francais]";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['biolocalisation'] = "biolocalisation";

	}
	

}
?>