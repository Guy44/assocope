<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class globales extends assMetaNode {
	var $table = "app_globales";
	function meta(& $policy) {

		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function globales() {
		$this->atkMetaNode();
		$this->atkNode("globales",  NF_TRACK_CHANGES);

		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"tracer_mysqldb_query_o_n",
		"en_travaux_o_n",
				"texte_contrat_utilisateur",
				"date_texte_contrat",
		"google_map_key",
		"ubio_keycode",
		"traduction_charger_attribut_module_name", 
		"traduction_charger_attribut_node_name", 
		"traduction_charger_attribut_date_dernier_noeud", 
		"traduction_charger_attribut_nombre_noeuds_traites", 
		"traduction_charger_attribut_termine"
			)
		), AF_NO_LABEL));
			$this->add(new atkfckattribute("texte_contrat_utilisateur","", AF_SEARCHABLE,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'800px',
                 'Height'=>'300px'))); 
			$this->add(new atkAttribute("google_map_key", null,100));
			$this->add(new atkAttribute("ubio_keycode", null,100));
			$this->add(new atkBoolAttribute("tracer_mysqldb_query_o_n"));
			$this->add(new atkBoolAttribute("en_travaux_o_n"));
			$this->add(new atkAttribute("traduction_charger_attribut_module_name", null,100));
			$this->add(new atkAttribute("traduction_charger_attribut_node_name", null,100));
			$this->add(new atkAttribute("traduction_charger_attribut_date_dernier_noeud", null,100));
			$this->add(new atkAttribute("traduction_charger_attribut_nombre_noeuds_traites", null,100));
			$this->add(new atkAttribute("traduction_charger_attribut_termine", null,100));

           $this->add(new atkAttribute("date_texte_contrat", AF_READONLY));
  		$this->setSecurityAlias("application.aide");
  				$this->m_securityMap["confidentialite"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
//		$this->setOrder("module, node");
	}
 function postUpdate($record)
 {

 	if ($record['atkorgrec']['texte_contrat_utilisateur'] != $record['texte_contrat_utilisateur'])
 	{
 		$db = & atkGetDb();
 		$db->query("update app_globales set date_texte_contrat=UTC_TIMESTAMP() ");
 	}
 	parent::postUpdate($record);
 }	
 function action_confidentialite() {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT texte_contrat_utilisateur from  app_globales" );
		$confidentialite = $data[0]["texte_contrat_utilisateur"];
		$res = "<table border='1'>";

		$res .= "<tr><td class='styletitre'><b>";
		$res .= "Règles d'utilisation et de confidentialité</b></td></tr>";
		$res .= "<tr><td class='styleligne'>";

			$res .= $confidentialite;

		$res .= "</td></tr>";
		$res .= "</table>";
	$page =   &atkinstance("atk.ui.atkpage");
	      $theme = atkinstance("atk.ui.atktheme");
       $page->register_style($theme->stylePath("style.css"));
$page->addContent( $res);

	}
}
?>