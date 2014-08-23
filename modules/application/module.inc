<?php

class mod_application extends associationModule
{
	function getNodes()
	{

		registerNode("application.aide", array("admin", "add", "edit", "delete" ,"view" ,"view_all", "grantall"));
		 registerNode("application.v_atkeventlog_heure", array("admin", "view", "stats_jour"));

	}

	function getGgNodeName()
	{
		$res=array();
		$module="application";
	 $res[]= $module."."."aide_mot_cle";
	 $res[]= $module."."."aide";
	 $res[]= $module."."."demande";
	 $res[]= $module."."."document_proto";
	 $res[]= $module."."."globales";
	 $res[]= $module."."."image_a";
	 $res[]= $module."."."sauvegarde";
	 $res[]= $module."."."traduction";
	 $res[]= $module."."."v_atkeventlog";
	 $res[]= $module."."."mysql_table";

	 return $res;
	}
		
			function getMenuItems($topmenu) {
				// Dernier langue sélectionné
if ($topmenu=="Langues")

		{
				$langueid = 0;
		$user = getUser();
		$id = $user["id"];
		if (isset ($id)) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
			$id_individu = $data[0]["id_individu"];
			$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='langue' order by date_recent_use desc");
			if (count($data) > 0) {
				$langueid = $data[0]["id_entite"];
				$data = $db->getrows("select libelle_francais from type_langue where id=$langueid");
				$nom_langue = $data[0]["libelle_francais"];

				$fiche_langue = '<font color="Tomato"> <b>' . $nom_langue . '</b>';
			}
		}
						// TOP LANGUES
			// Nom Langue
			$this->menuitem("@fiche_langue_lng@".$fiche_langue, dispatch_url("table.type_langue", "edit", array (
			"atkselector" => "type_langue.id='" . $langueid . "'"
			)), "Langues", true);
			// Rechercher
			$this->menuitem("Rechercher_lng", dispatch_url("table.type_langue", "admin"), "Langues", true);
			// Récents

			$data = $db->getrows("SELECT count(id) as nombre from app_recent_use where type_entite='langue' and id_individu='" . $id_individu . "'");
			$nombre = $data[0]["nombre"];
			$this->menuitem("Récents_lng"."#".$nombre, dispatch_url("profil.recent_use", "admin", array( 
			"atkfilter" => "app_recent_use.type_entite='langue' and app_recent_use.id_individu='" . $id_individu . "'"
			)), "Langues", true);
			// Créer
			$this->menuitem("Créer_lng", dispatch_url("table.type_langue", "add"), "Langues", true);
			//
			$this->menuitem("-", null, "Langues", true);

			$data = $db->getrows("SELECT count(id_type_langue) as nombre from v_app_traduction where  id_type_langue=" . $langueid . " ");
			$nombre_traduction = $data[0]["nombre"];

			// Traductions
			$this->menuitem("Traductions_lng"."#".$nombre_traduction, dispatch_url("application.v_app_traduction", "admin", array (
			"atkfilter" => "app_traduction.id_type_langue ='" . $langueid . "'"
			)), "Langues", true);
			$data = $db->getrows("SELECT count(id) as nombre from app_traduction where  id_type_langue=" . $langueid . " ");
			$nombre_traduction = $data[0]["nombre"];
			// Traductions
			$this->menuitem("Traductions_detail_lng"."#".$nombre_traduction, dispatch_url("application.traduction", "admin", array (
			"atkfilter" => "app_traduction.id_type_langue ='" . $langueid . "'"
			)), "Langues", true);

			$this->menuitem("-", null, "Langues", true);

			// Chargement schéma
			$this->menuitem("Chargement_schema_lng", dispatch_url("table.type_langue", "charger_schema", array (
			"id" => "'". $langueid . "'"
			)), "Langues", true);
			// Chargement attributs
			$this->menuitem("Chargement_attributs_lng", dispatch_url("table.type_langue", "charger_attributs", array (
			"id" => "'". $langueid . "'"
			)), "Langues", true);
			// Chargement mesages atk
			$this->menuitem("Chargement_atk_lng", dispatch_url("table.type_langue", "charger_atk", array (
			"id" => "'". $langueid . "'"
			)), "Langues", true);
			// Chargement mesages atk
			$this->menuitem("Chargement_application_lng", dispatch_url("table.type_langue", "charger_application", array (
			"id" => "'". $langueid . "'"
			)), "Langues", true);
			$this->menuitem("-", null, "Langues", true);
			
		}
			}
}


?>