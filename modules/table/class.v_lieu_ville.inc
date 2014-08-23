<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextnomattribute");
useattrib("development.atgNumberExpressionAttribute");
class v_lieu_ville extends assMetaNode {
	var $table = "v_lieu_ville";
	function meta(& $policy) {

	}
	function v_lieu_ville() {

		$this->atkMetaNode(array (
			"flags" => NF_NO_ADD | NF_MRA
		));
		$this->atkNode("v_lieu_ville", NF_NO_ADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTextAttribute("id_pays", AF_SEARCHABLE | AF_PRIMARY));
		$this->add(new atkTextAttribute("libelle_anglais", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("code_iso", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("libelle_francais", AF_SEARCHABLE));
		$this->add(new atkTextAttribute("province", AF_SEARCHABLE | AF_PRIMARY));
		$this->add(new atkTextAttribute("ville", AF_SEARCHABLE | AF_PRIMARY),20);
		$this->add(new atgNumberExpressionAttribute("nb_individus", "select count(il.id_individu) from

individu_lieu il,
lieu l,
type_cp_ville_pays cp
where

il.id_lieu=l.id
and
l.id_ville=cp.id
and
cp.id_pays=[table].id_pays
and cp.province_etat=[table].province
and cp.ville=[table].ville"), NULL);
		include_once (atkconfig("atkroot") . "modules/include/actions.inc");
		$this->setOrder("nb_individus desc");
		$this->setTable($this->table); // set node table
	}
	function nb_individus_display($record, $mode) {
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

	function traitement_select($select,&$idorganisme,&$idindividus,&$idfonctions)
	{
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$chaine = '('.$id_variable.')';


			$chaineidfonction .= $chaine . ' or ';
		}

		$chaineidfonction = str_replace("v_lieu_ville", "cp", $chaineidfonction);
		$chaineidfonction = str_replace("cp.province", "cp.province_etat", $chaineidfonction);
		$chaineidfonction = substr($chaineidfonction, 0, strlen($chaineidfonction) - 3);
		$idfonctions=$chaineidfonction;
		$sql = 'select distinct i.id as id_individu from individu i
		 where i.id in ( select il.id_individu from

individu_lieu il,
lieu l,
type_cp_ville_pays cp
where

il.id_lieu=l.id
and
l.id_ville=cp.id
and (' . $chaineidfonction .'))';
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