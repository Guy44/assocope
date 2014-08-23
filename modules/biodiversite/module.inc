<?php

class mod_biodiversite extends associationModule
{
	function getNodes()
	{
	}
	function getMenuItems()
	{
	}
	function getGgNodeName()
	{
		$res=array();
		$module="biodiversite";
	 $res[]= $module."."."taxinomie";
	 $res[]= $module."."."rang_taxinomique";
	 $res[]= $module."."."statut_taxinomique";
	 $res[]= $module."."."point_observation";

	 $res[]= $module."."."parcours_observation";
	 $res[]= $module."."."parcours_point_observation";
	 $res[]= $module."."."observation";
	 $res[]= $module."."."observation_detail";
	 $res[]= $module."."."bv_lieu_ville";
	 $res[]= $module."."."requete";
	 $res[]= $module."."."requete_detail";
	 $res[]= $module."."."requete_taxinomie";
	 $res[]= $module."."."requete_organisme_commanditaire";
	 $res[]= $module."."."requete_organisme_observateur";
	 $res[]= $module."."."requete_individu_observateur";
	 $res[]= $module."."."requete_pays_observation";
	 $res[]= $module."."."requete_lieu_observation";
	 $res[]= $module."."."requete_date_observation";
	 $res[]= $module."."."protection";
	 $res[]= $module."."."protection_taxinomie";
	 $res[]= $module."."."col_taxa";
	 $res[]= $module."."."col_scientific_names";
	 $res[]= $module."."."col_common_names";
	 $res[]= $module."."."col_distribution";
	 $res[]= $module."."."col_references";
	 $res[]= $module."."."col_specialists";
	 $res[]= $module."."."col_databases";
	 $res[]= $module."."."col_sp2000_statuses";
	 $res[]= $module."."."col_families";
	 $res[]= $module."."."taxinomie_reduite";
	 

	 return $res;
	}
}


?>