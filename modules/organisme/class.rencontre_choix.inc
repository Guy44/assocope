<?php
atkimport("atk.assmetanode");
userelation ("atkmanytoonerelation");
useattrib("atkdateattribute");
useattrib("atkrowcounter");
useattrib("atkparserattribute");




class rencontre_choix extends assMetaNode
{
	var $table="organisme_rencontre_choix";
	function meta(&$policy)
	{
		$policy-> addFlags("commentaire","description",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

		$policy->setOrder("libelle");
	}
	function rencontre_choix()
	{
		$this->atkMetaNode();
		$this->atkNode("rencontre_choix", NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA | NF_COMPACT);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkDummyAttribute("descripteur_rencontre_choix",0,AF_HIDE_ADD | AF_COMPACT),10);
		$this->add(new atkDummyAttribute("descripteur_rencontre",0,AF_HIDE_ADD | AF_COMPACT),11);
	//	$this->add(new atkDummyAttribute("descripteur_rencontre",0,AF_HIDE_ADD | AF_COMPACT),15);
$this->add(new atkNumberAttribute("cout", AF_OBLIGATORY, 12, 2), NULL,30);
		$this->add(new atkAttribute("libelle", AF_OBLIGATORY),NULL,20);
		$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
		$this->add(new atkManyToOneRelation("id_rencontre","organisme.rencontre",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK | AF_FORCE_LOAD),NULL,40);
		
		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,50);
	}

	function descriptor_def()
	{
		return "[id_rencontre] - [libelle]";
	}

	function id_organisme_display($record, $mode) {
		
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function descripteur_rencontre_display($record, $mode) {
	//	$this->p($record);
		(!empty($record["id_rencontre"])) ? $retour=$this->decoupe_affichage_colonne($this->descripteur_rencontre($record["id_rencontre"]["id"]),100) : $retour="";
		return $retour;
	}
	function descripteur_rencontre_choix_display($record, $mode)
	{
		$id_choix=trim($record["id"]);
	return $this->descripteur_rencontre_choix($id_choix,"o");
	}
function recordActions($rec, &$actions, &$mraactions)
	{
		
		
		$mraactions['delete'] = "delete";
	}
	function initial_values()
	{
		$db = & atkGetDb();
		$condition=$this->m_postvars["atkfilter"];
		$array_id = explode('=', $condition);
		$id_rencontre = $array_id[1] ;
		$sql="Select id_organisme from organisme_rencontre where id=$id_rencontre";
		$data = $db->getrows($sql);
		$init_vals['id_organisme']=$data[0][id_organisme];
		return $init_vals;
	}

}

?>