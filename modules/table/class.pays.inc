<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextnomattribute");
useattrib("development.atgNumberExpressionAttribute");
class pays extends assMetaNode {
	var $table = "type_pays";
	function meta(& $policy) {
		$policy->addFlags("libelle_francais", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function pays() {
		$this->atkMetaNode();
		$this->atkNode("pays", NF_ADD_LINK| NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
							$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"code_iso",
				"libelle_anglais",
				"libelle_francais",
				"indicatif_telephonique",
				"nb_individus",
		"bio_observations",
		"bio_observations_details",
		"bio_especes_observees",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Codes_postaux" => array (
				"codes_postaux"
				),
			"Régions" => array (
				"region"
				)
				), AF_NO_LABEL));
				$this->add(new atkAttribute("code_iso", AF_SEARCHABLE | AF_UNIQUE),100);
				$this->add(new atgTextNomAttribute("libelle_anglais", AF_SEARCHABLE | AF_UNIQUE),150);
				$this->add(new atgTextNomAttribute("libelle_francais", AF_SEARCHABLE | AF_UNIQUE),200);
				$this->add(new atkNumberAttribute("indicatif_telephonique",AF_SEARCHABLE,5,0),250);
				$this->add(new atkOneToManyRelation("codes_postaux", "table.cp_ville_pays", "id_pays", AF_HIDE_LIST));
				$this->add(new atkOneToManyRelation("region", "table.type_region_pays", "id_pays", AF_HIDE_LIST));
				$this->add(new atgNumberExpressionAttribute("nb_individus", "select count(i.id) from
individu i,
individu_lieu il,
lieu l,
type_cp_ville_pays cp,
type_pays p
where
i.id=il.id_individu
and
il.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=p.id
and
p.id=[table].id"), 300);
				$this->add(new atgNumberExpressionAttribute("bio_observations", "select count(o.id) as nombre_observations
from
biodiversite_observation o,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id and
p.id=[table].id"), 350);
				$this->add(new atgNumberExpressionAttribute("bio_observations_details", "select count(od.id) as nombre_observation_detail_pays
from
biodiversite_observation o,
biodiversite_observation_detail od,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id=od.id_observation  and
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id and 
p.id=[table].id"), 400);
				$this->add(new atgNumberExpressionAttribute("bio_especes_observees", "select count(distinct t.id) as nombre_especes_observees_pays
from
biodiversite_observation o,
biodiversite_observation_detail od,
biodiversite_taxinomie t,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id=od.id_observation  and
od.id_taxinomie=t.id and
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id 
and
p.id=[table].id"), 450);
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setOrder("code_iso");

	}
		function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 20;
		

				if ($this->m_postvars["atgordre"]=='nb_individus'  )
				{
					$this->setOrder("nb_individus desc");
				}
				if ($this->m_postvars["atgordre"]=='bio_observations'  )
				{
					$this->setOrder("bio_observations desc");
				}
				return $handler->action_admin();
		}
		

	function bio_observations_display($record, $mode) {
		if ($record["bio_observations"] > 0) {
			return href(dispatch_url("biodiversite.observation", "admin", array (
				'atkfilter' => "biodiversite_observation.id in ( select o.id
from
biodiversite_observation o,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id and
p.id=" . $record['id'] .")" ), "dispatch.php"), text($record["bio_observations"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function bio_observations_details_display($record, $mode) {
		if ($record["bio_observations_details"] > 0) {
			return href(dispatch_url("biodiversite.observation_detail", "admin", array (
				'atkfilter' => "biodiversite_observation_detail.id in ( select od.id
from
biodiversite_observation o,
biodiversite_observation_detail od,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id=od.id_observation  and
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id and 
p.id=" . $record['id'] .")" ), "dispatch.php"), text($record["bio_observations_details"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function bio_especes_observees_display($record, $mode) {
		if ($record["bio_especes_observees"] > 0) {
			return href(dispatch_url("biodiversite.taxinomie", "admin", array (
				'atkfilter' => "biodiversite_taxinomie.id in ( select distinct t.id
from
biodiversite_observation o,
biodiversite_observation_detail od,
biodiversite_taxinomie t,
type_pays p,
type_cp_ville_pays cpv,
lieu l
where
o.id=od.id_observation  and
od.id_taxinomie=t.id and
o.id_lieu is not null and
o.id_lieu=l.id and 
l.id_ville=cpv.id and
cpv.id_pays=p.id 
and
p.id=" . $record['id'] .")" ), "dispatch.php"), text($record["bio_especes_observees"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	

	function nb_individus_display($record, $mode) {
		if ($record["nb_individus"] > 0) {
			return href(dispatch_url("individu.individu", "admin", array (
				'atkfilter' => "individu.id in ( select i.id from
individu i,
individu_lieu il,
lieu l,
type_cp_ville_pays cp,
type_pays p
where
i.id=il.id_individu
and
il.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=p.id
and
p.id=" . $record['id'] ." )"), "dispatch.php"), text($record["nb_individus"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	/*
		function observations_biodiversite_display($record, $mode) {
		return $this->descripteur_biodiversite_observations($record["id"],'pays');
		}

		*/
	function traitement_select($select,&$idorganisme,&$idindividus,&$idfonctions)
	{
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_1 = $id_variable;

			//		$array_organisme = $array_1[0];
			$array_type = explode('=', $id_variable);

			$chaineidfonction .= $array_type[1] . ',';
		}

		//		$array_organisme = str_replace("v_organisme_fonction", "individu_fonction", $array_organisme);
		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 1);
		$idfonctions=$chaineidfonction;
		$sql = 'select distinct i.id as id_individu from individu i
		 where i.id in ( select i.id from
individu i,
individu_lieu il,
lieu l,
type_cp_ville_pays cp,
type_pays p
where
i.id=il.id_individu
and
il.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=p.id
and
p.id in (' . $chaineidfonction . '))';
		$data = $db->getrows($sql);

		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		//		$idorg = explode('=', $array_organisme);
		//		$idorganisme = $idorg[1];

		return true;



	}
	function descriptor_def() {
		return "[libelle_francais]";
	}

}
?>