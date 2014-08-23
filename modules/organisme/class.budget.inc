<?php

useattrib("development.atgtextlibelleattribute");

class budget extends assMetaNode
{
	var $table="organisme_budget";

	function meta(&$policy)
	{
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	}
	function budget()
	{
		$this->atkMetaNode();
		$this->atkNode("budget", NF_ADD_LINK |NF_ADDAFTERADD | NF_COMPACT);
		$this->add(new atgTextLibelleAttribute("libelle", AF_OBLIGATORY | AF_FORCE_LOAD));
		$this->add(new atkAttribute("id", AF_HIDE_ADD | AF_HIDE_EDIT  | AF_FORCE_LOAD | AF_COMPACT),null,2);
		$this->add(new atkAttribute("an_budget", AF_OBLIGATORY |AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD));
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,10);
		$this->setSecurityAlias("organisme.organisme");
	}
	function descriptor_def()
	{
		return "[libelle]";
	}

	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_display($record, $mode) {
		$res=$this->descripteur_budget($record["id"],'o');
		$res.=$this->descripteur_organisme_sans_lien($record["id_organisme"]["id"]);
		return $res;
	}
	function validate(&$record, $mode)
	{
		// vérifier qu'un budget n'existe pas déjà pour cette année-là
		$id_organisme = $record["id_organisme"]["id"];
		$an=$record["an_budget"];
		$db = & atkGetDb();
		$sql = "SELECT an_budget  from organisme_budget
						 where id_organisme= $id_organisme  and an_budget=$an";
		$data = $db->getrows($sql);
		if (count($data)>0)
		{
			atkTriggerError($record, $this->getAttribute("an_budget"), "Il existe déjà un budget pour cette année : ".$record["an_budget"]);
		}
		
		if (parent::validate($record, $mode)==true)
		{return true;		}
	}

}

?>