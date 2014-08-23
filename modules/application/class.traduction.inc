<?php
atkimport("atk.assmetanode");

class traduction extends assMetaNode
{
	var $table="app_traduction";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function traduction()
	{
		$this->atkMetaNode();
		$this->atkNode("traduction",NF_MULTI_RECORD_PRIORITY_ACTIONS|  NF_EXTENDED_SORT|NF_MRA | NF_ADD_LINK|NF_COPY| NF_ADDAFTERADD);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_type_langue",
"id_type_traduction",
				"nom_table",
		"type_colonne",
				"nom_module",
				"nom_noeud",
				"texte_source",
				"texte_traduit",
				"texte_tt",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_type_langue","table.type_langue",AF_OBLIGATORY |AF_SEARCHABLE|AF_RELATION_AUTOLINK),900);
				$this->add(new atkManyToOneRelation("id_type_traduction","table.type_traduction",AF_OBLIGATORY | AF_SEARCHABLE|AF_RELATION_AUTOLINK),200);
				$this->add(new atkAttribute("nom_table", AF_SEARCHABLE| AF_READONLY_EDIT),910);
				$this->add(new atkAttribute("type_colonne", AF_SEARCHABLE| AF_READONLY_EDIT),920);
				$this->add(new atkAttribute("nom_module", AF_SEARCHABLE | AF_READONLY_EDIT),500);
				$this->add(new atkAttribute("nom_noeud", AF_SEARCHABLE| AF_READONLY_EDIT),600);
				$this->add(new atkAttribute("texte_source", AF_OBLIGATORY | AF_SEARCHABLE),700);
				$this->add(new atkTextAttribute("texte_traduit",1, AF_SEARCHABLE),800);
//				$this->add(new atkTextAttribute("texte_tt",5, AF_SEARCHABLE),801);
						$this->add(new atkfckattribute("texte_tt", "", 0, array (
				 'ToolbarSet' => 'Default',
				 'Width' => '100%',
				 'Height' => '300px'
				 )),801);
		
				include_once(atkconfig("atkroot")."modules/include/association.inc");

				$this->setSecurityAlias("profil.profil");
				$this->m_securityMap["maj"] = "view";
				$this->setOrder(" id_type_langue,nom_module ,nom_noeud,nom_table ");
	}

	function texte_traduit_display($record, $mode='list')
	{
		if ($mode != 'list')
		return $this->getAttribute('texte_traduit')->display($record, $mode);
		$prefix = "data_AE_".$record["id"]."_AE_";
		return $this->getAttribute('texte_traduit')->edit($record, $prefix, 'edit');
	}

	function descriptor_def()
	{
		return "[texte_source]";
	}
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['delete'] = "delete";
		$mraactions['maj'] = "maj";
	}
	function action_maj() {
		$db = & atkGetDb();
		foreach ($this->m_postvars["atkselector"] as $value)
		{$idarray=explode("=",$value);
		$id=$idarray[1];
		$id=str_replace("'","",$id);

		$texte=str_replace("'","\'",$this->m_postvars["data"][$id]["texte_traduit"]) ;

				$sql="UPDATE app_traduction set texte_traduit='". $texte."' where id=".$id."";
/*
 * 
	$tt=str_replace("'","\'",$this->m_postvars["data"][$id]["texte_tt"]) ;
		$sql="UPDATE app_traduction set texte_traduit='". $texte."', texte_tt='". $tt."'
		where id=".$id."";
 */			
		$db->query($sql);
	
		}
		$this->redirect();
			
	}

}
?>