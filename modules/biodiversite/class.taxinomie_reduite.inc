<?php

atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgnumberexpressionattribute");

class taxinomie_reduite extends assMetaNode {
	var $table = "biodiversite_taxinomie";
	function meta(& $policy) {

		$policy->addFlags("commentaire", AF_HIDE_LIST);

      $policy->setFlags("id_rang_taxinomique",
				"etymologie",
      "id_statut_france_metropole",
			"id_statut_martinique",
			"id_statut_guadeloupe",
			"id_statut_st_martin_st_barthelemy",
			"id_statut_guyane_francaise",
			"id_statut_st_pierre_et_miquelon",
			"id_statut_reunion",
			"id_statut_mayotte",
			"id_statut_terres_australes_et_antartiques_francaises",
      "cd_nom",
			"cd_ref",
			"id_taxon_fauna_europaea",
			"id_taxon_conservation_nature",
			"id_taxon_marine_species",
			"id_taxon_kerguelen",
			"id_bock_kerguelen",  "url_image",
       AF_HIDE);

	}
	function taxinomie_reduite() {
		$this->atkMetaNode();
		$this->atkNode("taxinomie_reduite",NF_ADD_LINK |  NF_MRA | NF_EXT_SORT );
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
	"id",
				"id_parent",
				"nom_binomial",
				"nom_francais",
				"nom_anglais",
				"auteur",
				"auteur_an",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
			), AF_NO_LABEL));
			$this->add(new atkAttribute("id"),155);
			$this->add(new atgTextLibelleAttribute("nom_binomial", AF_SEARCHABLE | AF_OBLIGATORY),156);

						$this->add(new atkExpressionAttribute("observations", 'select count(*) from biodiversite_observation_detail 
						where id_taxinomie=[table].id', 0, AF_SEARCHABLE),157);
			$this->add(new atgTextLibelleAttribute("nom_francais", AF_SEARCHABLE),160);
			$this->add(new atgTextLibelleAttribute("nom_anglais", AF_SEARCHABLE),170);
			$this->add(new atkManyToOneRelation("id_parent", "biodiversite.taxinomie", AF_SEARCHABLE | AF_OBLIGATORY| AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),810);
						$this->add(new atgTextLibelleAttribute("auteur", AF_SEARCHABLE),820);
			$this->add(new atkAttribute("auteur_an", AF_SEARCHABLE),830);

			include_once (atkconfig("atkroot") . "modules/include/association.inc");
//	$this->setOrder("observations desc, nom_binomial asc ");
	        $this->setIndex("nom_binomial");
	}

	function descriptor_def() {
		return "[nom_binomial] - [nom_francais]";
	}
	function rowColor($record) {
//		$this->p($record);
		$idtaxinomie= $record["id"];
			$db = & atkGetDb();
		$sql="SELECT count(id) as nombre_observations  FROM `biodiversite_observation_detail` WHERE id_taxinomie=$idtaxinomie ";
		$data=$db->getrows($sql);
		if ($data[0]["nombre_observations"] >0)
		return $this->couleurpriorite2;
	}
function observations_display ($record,$mode)
{
		$idtaxinomie= $record["id"];
		$db = & atkGetDb();
		$data = $db->getrows("select count(id) as compte from biodiversite_observation_detail
	 where id_taxinomie =$idtaxinomie ");
			$nombre_observations=$data[0]["compte"];
			if ($nombre_observations >0 ) {
				$observations= href(dispatch_url("biodiversite.observation_detail", "admin", array (
				'atkfilter' => "biodiversite_observation_detail.id_taxinomie='" . $idtaxinomie . "'"
				), "dispatch.php"), $nombre_observations, SESSION_NESTED);
				if ($nombre_observations!=0)			$observations='<font color="red"><b>'.$observations.'</font></b>';

			} else {
				$observations="";
			}
			return $observations;
}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 200;
		$view = $this->getView();

		if ($view == "tout") {

			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "observees_sans_nom_francais") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail
		  ) and biodiversite_taxinomie.nom_francais is null");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}
		if ($view == "observees") {
			$this->addFilter("biodiversite_taxinomie.id in (select distinct id_taxinomie from biodiversite_observation_detail
		  ) ");
			$this->addFilter($this->m_postvars["atkfilter"]);
		}

		
		return $handler->action_admin();
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
/*		//		$mraactions['maj'] = "maj";
		$mraactions['biolocalisation'] = "biolocalisation";
		$actions['biolocalisation'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=biolocalisation&atkselector=[pk]", SESSION_NESTED);
*/

	}

	function adminFooter() {
		$retour=parent::adminfooter();
 		$legende = 'Légende des couleurs : ';
		$legende .= '<font color="'.$this->couleurpriorite2.'"> <b> Espèce déjà observée dans la base utilisée </b></font><br>';
		$view = $this->getView();
		$retour_especes_observees=href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=observees', 'Espèces observées')  ;
		$retour_sans_nom_francais= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=observees_sans_nom_francais', 'Espèces observées sans nom français') ;
		$retour_tout= href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=tout', 'Tout')  ;
		$db = & atkGetDb();
		$sql='select count(bt.id) as nombre from biodiversite_taxinomie bt ';
		$data=$db->getrows($sql);
		$nombre_tout=$data[0]["nombre"];
		$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od, biodiversite_taxinomie bt where od.id_taxinomie=bt.id
		  and bt.nom_francais is null';
		$data=$db->getrows($sql);
		$nombre_sans_nom_francais=$data[0]["nombre"];
		$sql='select count(distinct od.id_taxinomie) as nombre from biodiversite_observation_detail od';
		$data=$db->getrows($sql);
		$nombre_observees=$data[0]["nombre"];

		
		$retour='Sélection : ';
		if ($view == "tout")
		{$retour.= "<b>Tout(".$nombre_tout.")</b>".'|'.$retour_especes_observees.'('.$nombre_observees.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')';}
		if ($view == "observees_sans_nom_francais")
		{$retour.= $retour_tout.'('.$nombre_tout.')|'.$retour_especes_observees.'('.$nombre_observees.')|<b>Espèces observées sans nom français('.$nombre_sans_nom_francais.')</b>)';}
		if ($view == "observees")
		{$retour.= $retour_tout.'('.$nombre_tout.')|<b>Espèces observées('.$nombre_observees.')</b>|'.$retour_sans_image.'('.$nombre_sans_image.')|'.$retour_sans_nom_francais.'('.$nombre_sans_nom_francais.')';}
		$retour.='<br>';

		return '</b>'.$legende .$retour.'<b>';
	}
	function adminHeader() {

		return $this->adminFooter();
	}

	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "observees";
		}
		return $view;
	}

	/*
	 *
	 function action_maj() {
		$db = & atkGetDb();
		foreach ($this->m_postvars["atkselector"] as $value)
		{$idarray=explode("=",$value);
		$id=$idarray[1];
		$id=str_replace("'","",$id);

		$nom_francais=str_replace("'","\'",$this->m_postvars["data"][$id]["nom_francais"]) ;
		$nom_anglais=str_replace("'","\'",$this->m_postvars["data"][$id]["nom_anglais"]) ;
		$sql="UPDATE biodiversite_taxinomie set nom_francais='". $nom_francais."', nom_anglais='". $nom_anglais."'
		where id=".$id."";
		$db->query($sql);

		}
		$this->redirect();
			
		}
	 */


}
?>