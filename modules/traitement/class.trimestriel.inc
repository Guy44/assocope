<?php
/**
 * You might have noticed, that the module.inc file for the setup module
 * does not contain any nodes. This means, that you can not grant anyone
 * any rights to use the setup node.
 * This ensures, that only the administrator user can make use of the
 * stuff presented here
 */
class trimestriel extends atkNode {
	var $m_report = array ();
	var $m_cancontinue = true;
	var $m_currentmodule = "";
	var $m_resultmsg = array (
		"ok" => "Installation completed",
		"n/a" => "No installation required",
		"failed" => "Installation failed",
		"faileddep" => "Not installed (dependencies could not be resolved)",
		"cyclicdep" => "Not installed (Cyclic dependency detected)",
		"alreadyinstalled" => "Module was already installed and up to date",
		"notfound" => "Not installed (Module could not be found)",
		"patched" => "Patch applied succesfully"
		);
		function trimestriel() {
			$this->atkNode("trimestriel");
			$this->m_securityMap["avertissement"] = "view";
			$this->m_securityMap["adhesion"] = "view";
			$this->m_securityMap["adresse"] = "view";
			$this->m_securityMap["carte"] = "view";
			$this->m_securityMap["carte_maj"] = "view";
			$this->m_securityMap["cotisation"] = "view";
			$this->m_securityMap["cotisation_federation_seule"] = "view";
			$this->m_securityMap["cotisation_federation"] = "view";
			$this->m_securityMap["reporter_inscription_federation"] = "view";
			$this->m_securityMap["reporter_radiation_federation"] = "view";
			$this->m_securityMap["impressioncomplement"] = "view";
			$this->m_securityMap["impressionenveloppe"] = "view";
			$this->m_securityMap["impressionrecufiscal"] = "view";
			$this->m_securityMap["inscription_federation"] = "view";
			$this->m_securityMap["intro"] = "view";
			$this->m_securityMap["miseajourenvois"] = "view";
			$this->m_securityMap["recu"] = "view";
			$this->m_securityMap["recu_maj"] = "view";
			$this->m_securityMap["timbre"] = "view";
			$this->m_securityMap["timbre_maj"] = "view";
			$this->m_securityMap["complement_correspondance"] = "view";
			$this->m_securityMap["adhesion_et_pas_de_cotisation"] = "view";
		}
		function action_avertissement(& $handler) {
			$organismeid=$this->m_postvars["id"];
			$db = & atkGetDb();
			$data = $db->getrows("SELECT o.date_derniere_preparation, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_derniere_preparation=au.id where o.id= $organismeid ");
			$nombre_prepa = $data[0]["identifiant"]." le ".$data[0]["date_derniere_preparation"];
			$date_debut=$data[0]["date_derniere_preparation"];
			$data = $db->getrows("SELECT o.date_derniere_preparation_fin, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_derniere_preparation_fin=au.id where o.id= $organismeid ");
			$nombre_prepa_fin = $data[0]["identifiant"]." le ".$data[0]["date_derniere_preparation_fin"];
			$date_fin=$data[0]["date_derniere_preparation_fin"];
			($date_debut > $date_fin)?  $alerte=" <b>ATTENTION LA DERNIERE PREPARATION A ETE INTERROMPUE.</b> " : $alerte="";
			$data = $db->getrows("SELECT o.date_envoi_recu_fiscal, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_envoi_recu_fiscal=au.id where o.id=$organismeid");
			$nombre_recu_fiscal = $data[0]["identifiant"]." le ".$data[0]["date_envoi_recu_fiscal"];
			$data = $db->getrows("SELECT o.date_envoi_timbre, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_envoi_timbre=au.id where o.id=$organismeid");
			$nombre_timbre = $data[0]["identifiant"]." le ".$data[0]["date_envoi_timbre"];
			$data = $db->getrows("SELECT o.date_envoi_carte, au.identifiant
			from organisme o LEFT JOIN app_utilisateur  au ON o.id_envoi_carte=au.id where o.id=$organismeid");
			$nombre_carte = $data[0]["identifiant"]." le ".$data[0]["date_envoi_carte"];
			$data = $db->getrows("SELECT o.date_recu_abandon_creance, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_recu_abandon_creance=au.id where o.id=$organismeid");
			$nombre_abandon_creance = $data[0]["identifiant"]." le ".$data[0]["date_recu_abandon_creance"];
			$data = $db->getrows("SELECT o.date_synchronisation_federation, au.identifiant
			from organisme o LEFT JOIN app_utilisateur au  ON o.id_synchronisation_federation=au.id where o.id=$organismeid");
			$nombre_synchro_federation =$data[0]["identifiant"]." le ".$data[0]["date_synchronisation_federation"];

			$this->setupScreen("Avertissement", "Récapitulatif du dernier traitement :
				                          <ul>
				                            <li>Dernière préparation:</li>
				                            <li>====> <b>DEBUT : $nombre_prepa .</b></li>
				                            <li>====> <b>FIN : $nombre_prepa_fin .</b></li>
				                            <li>$alerte</li>
				                            <li>Mise à jour des envois des reçus fiscaux : <b>$nombre_recu_fiscal </b>.</li>
				                            <li>Mise à jour des envois des timbres : <b>$nombre_timbre </b>.</li>
				                            <li>Mise à jour des envois des cartes : <b>$nombre_carte </b>.</li>
				                            <li>Synchronisation avec la fédération : <b>$nombre_synchro_federation </b>.</li>
				                            <li>Mise à jour des envois des reçus fiscaux pour abandon de créance : <b>$nombre_abandon_creance </b>.</li>
				                            <li><b>VERIFIEZ</b> : que les mises à jour et synchronisation ont bien été faites après la préparation : </li>	
				                            <li>====><b> SI OUI : vous pouvez poursuivre en cliquant sur 'Continuer' </b></li>	
				                            <li>====><b> SI NON : quittez ce traitement et faîtes les mises à jour nécessaires</b></li>		                            
				                          </ul>
				                          <br>
				                          <br>
				                          ", "intro", array (
			id => $this->m_postvars["id"]
			));
		}

		function action_intro(& $handler) {
			$this->setupScreen("Introduction", "Ce traitement a lieu chaque trimestre pour un organisme lors de l'envoi de la lettre trimestrielle aux membres et consiste à :
				                          <ul>
				                            <li><b>Vérifier</b> que des <b>adresses postales existent bien pour tous les inscrits</b> à la lettre.
				                            <li><b>Vérifier</b> que les <b>inscrits le sont aussi à la fédération si spécifié dans le type inscription</b>.
				                            <li>Rechercher si la cotisation a été créée pour un inscrit qui ne cotise qu'à la fédération.
				                            <li>Rechercher les notifications des nouvelles inscriptions à faire à la fédération.
				                            <li>Rechercher les notifications des radiations à faire à la fédération.
				                            <li>Rechercher les cotisations dues à la fédération.
				                            <li>Rechercher si la cotisation de l'année en cours est dûe.
				                           <li>Rechercher les recus fiscaux à envoyer.
				                            <li>Rechercher les cartes à envoyer.
				                            <li>Rechercher les timbres à envoyer.
				                            <li>Rechercher les avertissements de radiation.
				                            <li>Créer le fichier open office des adresses pour imprimer les adresses sur les enveloppes.
				                            <li>Créer le fichier open office des reçus fiscaux.
				                            <li>Créer le fichier open office des compléments explicatifs.
				                            <li>Mettre à jour avec la date du jour.
				                            
				                          </ul>
				                          <br>
				                          <br>
				                          ", "adresse", array (
			id => $this->m_postvars["id"]
			));
			$db = & atkGetDb();
			global  $g_sessionManager;
			$userutilisateur = $g_user["id"];
			$user = getUser();
			$id = $user["id"];
			$sql="Update organisme set date_derniere_preparation=UTC_TIMESTAMP(), id_derniere_preparation=".$id." where id=".$this->m_postvars["id"]."";
			$db->query($sql);
			$db->query("UPDATE individu_inscription" . " set imprimer_adresse_o_n='0', " . " envoyer_recu_fiscal_o_n='0'," . " envoyer_timbre_o_n='0'," . " envoyer_carte_adherent_o_n='0'," . " an_radiation_cotisation_prevue=null, " . " an_derniere_cotisation=null, " . " an_adhesion_prevue=null, " . " avertir_radiation_cotisation_o_n='0', " . " reclamer_cotisation_o_n='0', " . " effectuer_radiation_cotisation_o_n='0', " . " avertir_radiation_adhesion_o_n='0', " . " effectuer_radiation_adhesion_o_n='0', " . " inscrire_federation_o_n='0'," . " creer_cotisation_federation_o_n='0'," . " inscrire_federation_o_n='0'," . " reporter_inscription_federation_o_n='0'," . " reporter_radiation_federation_o_n='0'," . " regler_cotisation_federation_o_n='0'," . " creer_adresse_postale_o_n='0'," . " adhesion_et_pas_de_cotisation_o_n='0'," . " p1=NULL," . "e1=NULL," . "p2=NULL," . "e2=NULL," . "p3=NULL," . "e3=NULL," . "p4=NULL," . "e4=NULL," . "p5=NULL," . "e5=NULL," . "p6=NULL," . "e6=NULL" . " where id_organisme=" . $this->m_postvars["id"] . "");
		}
		function action_adresse(& $handler) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT i.id, i.nom, i.prenom" . " from individu i" . " where i.date_deces is null" . " and i.id not in (select id_individu  from individu_lieu where adresse_defaut_o_n='1')" . " and i.id in " . " (select ii.id_individu " . " from individu_inscription ii," . " type_inscription ti" . " where ii.id_organisme=" . $this->m_postvars["id"] . " and ii.date_radiation is null" . " and ii.id_type_inscription=ti.id" . " and ti.lettre_o_n=1)");
			if (count($data) == 0) {
				$db->query("UPDATE individu_inscription" . " set imprimer_adresse_o_n='1'" . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_type_inscription in " . " (select id from type_inscription where lettre_o_n=1)");
			} else {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set creer_adresse_postale_o_n='1' " . " where date_radiation is null " . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
			$data1 = $db->getrows("SELECT count(id) as enveloppes" . " from individu_inscription " . " where imprimer_adresse_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Vérification des adresses postales pour les membres abonnés à la lettre aux membres", "Le traitement vérifie qu'une adresse postale existe bien :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les types d'inscription comportant un abonnement à la lettre.
				                           </ul>
				                          <br>il y a <b>" . count($data) . " individus sans adresse postale (si ce nombre est positif il faut d'abord compléter ces adresses).</b>
				                          <br>il y a <b>" . $data1[0]["enveloppes"] . " lettres (enveloppes, timbres postaux, gazette, plaquette) à prévoir, préparer et à envoyer.</b>
				                          <br>il y aura aussi <b>les compléments à insérer et éventuellemnt ce qui est spécifié dans les compléments (carte, timbre, reçu fiscal)</b>", "inscription_federation", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_inscription_federation(& $handler) {
			$db = & atkGetDb();
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT o.id_organisme_federation" . " from organisme o" . " where o.id=" . $this->m_postvars["id"] . " ");
			$id_federation = $data[0]["id_organisme_federation"];
			if (!isset ($id_federation))
			return false;
			$data = $db->getrows("SELECT o.nom " . " from organisme o" . " where o.id=" . $id_federation . " ");
			$nom_federation = $data[0]["nom"];
			$data = $db->getrows("SELECT i.id " . " from individu i" . " where i.date_deces is null" . " and i.id in " . " (select ii.id_individu " . " from individu_inscription ii," . " type_inscription ti" . " where ii.id_organisme=" . $this->m_postvars["id"] . " and ii.date_radiation is null" . " and ii.id_type_inscription=ti.id" . " and ti.cotisation_federation_o_n=1)" . " and i.id not in " . " (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $id_federation . " )");
			$this->setupScreen("Vérification que les inscrits avec type cotisation fédération sont bien inscrits à la fédération", "Le traitement vérifie qu'une inscription à la fédération existe bien :
				                          <ul>
				                            <li>Pour l'organisme mentionné et étant rattaché à la fédération <b>" . $nom_federation . ".</b>
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les types d'inscription comportant une cotisation à la fédération.
				                           </ul>
				                          <br>il y a <b>" . count($data) . " individus non inscrits à la fédération et devant l'être. </b>
				                          <br>", "cotisation_federation_seule", array (
			id => $this->m_postvars["id"]
			));
			if (count($data) != 0) {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set inscrire_federation_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
		}
		function action_cotisation_federation_seule(& $handler) {
			$db = & atkGetDb();
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT o.id_organisme_federation" . " from organisme o" . " where o.id=" . $this->m_postvars["id"] . " ");
			$id_federation = $data[0]["id_organisme_federation"];
			if (!isset ($id_federation))
			return false;
			$data = $db->getrows("SELECT o.nom " . " from organisme o" . " where o.id=" . $id_federation . " ");
			$nom_federation = $data[0]["nom"];
			$data = $db->getrows("SELECT i.id " . " from individu i" . " where i.date_deces is null" . " and i.id in " . " (select ii.id_individu " . " from individu_inscription ii," . " type_inscription ti" . " where ii.id_organisme=" . $this->m_postvars["id"] . " and ii.date_radiation is null" . " and ii.id_type_inscription=ti.id" . " and ti.cotisation_federation_o_n=1" . " and ti.cotisation_organisme_o_n=0)" . " and i.id not in " . " (select ic.id_individu " . " from individu_cotisation ic," . " organisme_cotisation oc " . " where ic.id_cotisation=oc.id" . " and oc.id_organisme=" . $id_federation . " and oc.annee=year(UTC_DATE()))");
			$this->setupScreen("Recherche des appels à cotisation pour ceux pour qui seule la cotisation à la fédération est reversée", "Le traitement recherche les individus :
				                          <ul>
				                            <li>Pour l'organisme mentionné et étant rattaché à la fédération <b>" . $nom_federation . ".</b>
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les types d'inscription comportant une cotisation à la fédération et non à l'organisme.
				                            <li>Pour lesquels il n'y a pas eu de cotisation pour la fédération pour l'année en cours.
				                           </ul>
				                          <br>il y a <b>" . count($data) . " individus cotisants seulement à la fédération et pour qui la cotisation fédération n'a pas été créée.</b>
				                          <br>", "reporter_inscription_federation", array (
			id => $this->m_postvars["id"]
			));
			if (count($data) != 0) {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set creer_cotisation_federation_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
		}
		function action_reporter_inscription_federation(& $handler) {
			$db = & atkGetDb();
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT o.id_organisme_federation, o.date_synchronisation_federation " . " from organisme o" . " where o.id=" . $this->m_postvars["id"] . " ");
			$id_federation = $data[0]["id_organisme_federation"];
			if (!isset ($id_federation))
			return false;
			$date_synchro_federation = $data[0]["date_synchronisation_federation"];
			$data = $db->getrows("SELECT o.nom " . " from organisme o" . " where o.id=" . $id_federation . " ");
			$nom_federation = $data[0]["nom"];
			$data = $db->getrows("SELECT i.id " . " from individu i" . " where i.date_deces is null" . " and i.id in " . " (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $id_federation . " and ii.date_radiation is null" . " and ii.date_inscription is not null" . " and ii.date_inscription>'" . $date_synchro_federation . "')" . " and i.id in  (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $this->m_postvars["id"] . " and ii.date_radiation is null )");
			$this->setupScreen("Recherche des nouvelles inscriptions à la fédération enregistrées depuis la dernière synchronisation avec la fédération", "Le traitement recherche les individus :
				                          <ul>
				                            <li>Pour l'organisme mentionné et étant rattaché à la fédération <b>" . $nom_federation . ".</b>
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les inscriptions à la fédération ayant eu lieu depuis la dernière date de synchronisation avec la fédération.
				                           </ul>
				                          <br>il y a <b>" . count($data) . " nouvelles inscriptions à reporter à la fédération.</b>
				                          <br>", "reporter_radiation_federation", array (
			id => $this->m_postvars["id"]
			));
			if (count($data) != 0) {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set reporter_inscription_federation_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
		}
		function action_reporter_radiation_federation(& $handler) {
			$db = & atkGetDb();
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT o.id_organisme_federation, o.date_synchronisation_federation " . " from organisme o" . " where o.id=" . $this->m_postvars["id"] . " ");
			$id_federation = $data[0]["id_organisme_federation"];
			$date_synchro_federation = $data[0]["date_synchronisation_federation"];
			if (!isset ($id_federation))
			return false;
			$data = $db->getrows("SELECT o.nom " . " from organisme o" . " where o.id=" . $id_federation . " ");
			$nom_federation = $data[0]["nom"];
			$data = $db->getrows("SELECT i.id " . " from individu i" . " where  i.id in " . " (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $id_federation . " and ii.date_radiation is not null" . " and ii.date_radiation>'" . $date_synchro_federation . "')" . " and i.id in  (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $this->m_postvars["id"] . "  )");
			$this->setupScreen("Recherche des radiations à la fédération enregistrées depuis la dernière synchronisation avec la fédération", "Le traitement recherche les individus :
				                          <ul>
				                            <li>Pour l'organisme mentionné et étant rattaché à la fédération <b>" . $nom_federation . ".</b>
				                            <li>Pour les inscrits à l'organisme.
				                            <li>Pour les inscriptions à la fédération dont la radiation a eu lieu depuis la dernière date de synchronisation avec la fédération.
				                           </ul>
				                          <br>il y a <b>" . count($data) . " nouvelles radiations à reporter à la fédération.</b>
				                          <br>", "cotisation_federation", array (
			id => $this->m_postvars["id"]
			));
			if (count($data) != 0) {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set reporter_radiation_federation_o_n='1' " . " where id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
		}
		function action_cotisation_federation(& $handler) {
			$db = & atkGetDb();
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT o.id_organisme_federation, o.date_synchronisation_federation " . " from organisme o" . " where o.id=" . $this->m_postvars["id"] . " ");
			$id_federation = $data[0]["id_organisme_federation"];
			$date_synchro_federation = $data[0]["date_synchronisation_federation"];
			if (!isset ($id_federation))
			return false;
			$data = $db->getrows("SELECT o.nom " . " from organisme o" . " where o.id=" . $id_federation . " ");
			$nom_federation = $data[0]["nom"];
			$data = $db->getrows("SELECT i.id " . " from individu i" . " where i.date_deces is null" . " and i.id in " . " (select ic.id_individu " . " from individu_cotisation ic, organisme_cotisation oc " . " where ic.date_reglement is null " . " and ic.id_cotisation=oc.id " . " and oc.id_organisme=" . $id_federation . ")" . " and i.id in  (select ii.id_individu " . " from individu_inscription ii" . " where ii.id_organisme=" . $this->m_postvars["id"] . "  )");
			$this->setupScreen("Recherche des cotisations non réglées  à la fédération", "Le traitement recherche les individus :
				                          <ul>
				                            <li>Pour l'organisme mentionné et étant rattaché à la fédération <b>" . $nom_federation . ".</b>
				                            <li>Pour les inscrits à l'organisme.
				                            <li>Pour les cotisations à la fédération où la date de règlement est nulle
				                           </ul>
				                          <br>il y a <b>" . count($data) . " cotisations à règler à la fédération.</b>
				                          <br>", "cotisation", array (
			id => $this->m_postvars["id"]
			));
			if (count($data) != 0) {
				for ($i = 0; $i < count($data); $i++) {
					$db->query("UPDATE individu_inscription" . " set regler_cotisation_federation_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu=" . $data[$i]["id"] . " ");
				}
			}
		}
		function action_cotisation(& $handler) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT
					ic.id_individu as IdIndividu,
					max(oc.annee) as  DerniereCotisation,
					ti.delai_radiation_non_cotisation as DelaiRadiation
					from individu_cotisation ic ,
					organisme_cotisation oc, 
					individu_inscription ii,
					type_inscription ti 
					where 
					ic.id_cotisation = oc.id 
					and oc.id_organisme=" . $this->m_postvars["id"] . " 
					and ic.date_reglement is not null  
					and ic.id_individu=ii.id_individu " . " and ii.date_radiation is null 
					and ii.id_type_inscription=ti.id
				        and ti.delai_radiation_non_cotisation
				and ti.cotisation_organisme_o_n=1
					and ii.id_organisme=" . $this->m_postvars["id"] . " 
				group by ic.id_individu
				");
			for ($i = 0; $i < count($data); $i++) {
				$anradiation = $data[$i]["DerniereCotisation"] + $data[$i]["DelaiRadiation"];
				$cotisAPayer = 0;
				if ($data[$i]["DerniereCotisation"] < gmdate("Y")) {
					$cotisAPayer = 1;
				}
				$avertirradiation = 0;
				if ($anradiation < gmdate("Y")) {
					$avertirradiation = 1;
				}
				if ($avertirradiation == '1') {
					$cotisAPayer = 0;
				}
				$effectuerradiation = 0;
				if ($anradiation < gmdate("Y") - 1) {
					$effectuerradiation = 1;
				}
				if ($effectuerradiation == '1') {
					$avertirradiation = 0;
					$cotisAPayer = 0;
				}
				$db->query("update individu_inscription " . " set an_radiation_cotisation_prevue=" . $anradiation . "," . " an_derniere_cotisation=" . $data[$i]["DerniereCotisation"] . " , reclamer_cotisation_o_n=" . $cotisAPayer . " , avertir_radiation_cotisation_o_n=" . $avertirradiation . " , effectuer_radiation_cotisation_o_n=" . $effectuerradiation . " where id_individu=" . $data[$i]["IdIndividu"] . " and id_organisme=" . $this->m_postvars["id"] . "");
			}
			$data1 = $db->getrows("SELECT count(id) as avertir" . " from individu_inscription " . " where avertir_radiation_cotisation_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$data2 = $db->getrows("SELECT count(id) as effectuer" . " from individu_inscription " . " where effectuer_radiation_cotisation_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$data3 = $db->getrows("SELECT count(id) as reclamer" . " from individu_inscription " . " where reclamer_cotisation_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des dernières cotisations et des radiations prévues", "Le traitement recherche :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les adhérents ayant au moins réglé une cotisation.
				                            <li>L'année de la dernière cotisation payée et la durée en années avant radiation
				                           </ul>
				                          <br>Il écrit dans l'inscription :
				                            <li> L'année de la dernière cotisation
				                            <li> L'année de la radiation en cas de non paiement
				                            <li> L'indicateur de cotisation dûe. 
				                            <br><br>il y a <b>" . $data3[0]["reclamer"] . " rappels de cotisations.</b>
				                           	<br>il y a <b>" . $data1[0]["avertir"] . " avertissements pour non cotisation.</b>
				                          	<br>il y a <b>" . $data2[0]["effectuer"] . " radiations à faire pour non réponse à relance.</b>", "carte", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_carte(& $handler) {
			$db = & atkGetDb();
			$db->query("update individu_inscription set envoyer_carte_adherent_o_n='1'
		 where date_radiation is null  and id_organisme=" . $this->m_postvars["id"] . " 
		and date_adhesion is not null  and date_envoi_carte is null ");
			$data1 = $db->getrows("SELECT count(id) as cartes" . " from individu_inscription " . " where envoyer_carte_adherent_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des nouvelles cartes d'adhérents à établir", "Le traitement recherche les inscriptions où :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>La date d'adhésion n'est pas nulle et dont la date de l'envoi de la carte est nulle
				                            </ul>
				                          <br>il y a <b>" . $data1[0]["cartes"] . " cartes à prévoir et à envoyer.</b>
				                          		<br>
				                          ", "timbre", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_carte_maj(& $handler) {
			$db = & atkGetDb();
			$db->query("update individu_inscription
				 set date_envoi_carte=UTC_TIMESTAMP()
				where  envoyer_carte_adherent_o_n='1' and id_organisme=" . $this->m_postvars["id"] . " ");
			$nombre = $db->affected_rows();
	 	global $g_user;
	 	$userutilisateur = $g_user["id"];
	 	$db->query("UPDATE organisme
		set id_envoi_carte= " . $userutilisateur. " , date_envoi_carte=UTC_TIMESTAMP(), id_modification=" . $userutilisateur . ", date_modification=UTC_TIMESTAMP()
		where id=" . $this->m_postvars["id"] . "");
		echo "La date d'envoi de <b>".$nombre." cartes</b> a été mise à jour au " . gmdate("c");
	 	echo "<br />";
	 	die();
		}
		function action_timbre(& $handler) {
			$db = & atkGetDb();
			$db->query("update individu_inscription" . " set envoyer_timbre_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu in " . " ( select ic.id_individu" . " from " . " individu_cotisation ic," . " organisme_cotisation oc" . " where " . " date_envoi_timbre is null" . " and date_reglement is not null" . " and ic.id_cotisation=oc.id" . " and oc.id_organisme=" . $this->m_postvars["id"] . ")");
			$data1 = $db->getrows("SELECT count(id) as timbres" . " from individu_inscription " . " where envoyer_timbre_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des timbres à envoyer", "Le traitement recherche les cotisations où :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>La date de règlement n'est pas nulle et la date d'envoi du timbre est nulle
				                           </ul>
				                          <br>il y a <b>" . $data1[0]["timbres"] . " timbres à prévoir et à envoyer.</b><br>
				                          <br>", "recu", array (
			id => $this->m_postvars["id"]
			));
			$db = & atkGetDb();
		}
		function action_timbre_maj(& $handler) {
			$db = & atkGetDb();

			$db->query("update individu_cotisation
				 set date_envoi_timbre=UTC_TIMESTAMP()
				where id_cotisation in (select id from organisme_cotisation where  id_organisme=" . $this->m_postvars["id"] . ") 
				 and date_reglement is not null and date_envoi_timbre is null 
				and id_individu in ( select distinct id_individu from individu_inscription 
				where envoyer_timbre_o_n='1' and id_organisme=" . $this->m_postvars["id"] . ")");
			$nombre = $db->affected_rows();
	 	global $g_user;
	 	$userutilisateur = $g_user["id"];
	 	$db->query("UPDATE organisme
		set id_envoi_timbre= " . $userutilisateur. " , date_envoi_timbre=UTC_TIMESTAMP(), id_modification=" . $userutilisateur . ", date_modification=UTC_TIMESTAMP()
		where id=" . $this->m_postvars["id"] . "");

	 	echo "La date d'envoi de <b>".$nombre." timbres</b> a été mise à jour au " . gmdate("c");
	 	echo "<br />";
	 	die();
		}
		function action_recu(& $handler) {
			$db = & atkGetDb();
			$db->query("update individu_inscription" . " set envoyer_recu_fiscal_o_n='1' " . " where date_radiation is null" . " and id_organisme=" . $this->m_postvars["id"] . " and id_individu in " . " ( select ic.id_individu" . " from " . " individu_cotisation ic," . " organisme_cotisation oc" . " where " . " date_envoi_recu_fiscal is null" . " and date_reglement is not null" . " and ic.id_cotisation=oc.id" . " and oc.id_organisme=" . $this->m_postvars["id"] . ")");
			$data1 = $db->getrows("SELECT count(id) as recu" . " from individu_inscription " . " where envoyer_recu_fiscal_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des reçus fiscaux à envoyer", "Le traitement recherche les cotisations où :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>La date de règlement n'est pas nulle et la date d'envoi du reçu fiscal est nulle
				                           </ul>
				                          <br>il y a <b>" . $data1[0]["recu"] . " reçus fiscaux à établir et à envoyer.</b><br><br>
				                          <br>", "adhesion", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_recu_maj(& $handler) {
			$db = & atkGetDb();
			$sql="update individu_cotisation
				 set date_envoi_recu_fiscal=UTC_TIMESTAMP()  
				where id_cotisation in (select id from organisme_cotisation where  id_organisme=" . $this->m_postvars["id"] . ") 
				 and date_reglement is not null and date_envoi_recu_fiscal is null 
				and id_individu in ( select distinct id_individu from individu_inscription 
				where envoyer_recu_fiscal_o_n=1 and id_organisme=" . $this->m_postvars["id"] . ")";

			$db->query($sql);
			$nombre = $db->affected_rows();
			global $g_user;
			$userutilisateur = $g_user["id"];
			$db->query("UPDATE organisme
		set id_envoi_recu_fiscal= " . $userutilisateur. " , date_envoi_recu_fiscal=UTC_TIMESTAMP(), id_modification=" . $userutilisateur . ", date_modification=UTC_TIMESTAMP()
		where id=" . $this->m_postvars["id"] . "");
			echo "La date d'envoi de <b>".$nombre." reçus fiscaux</b> a été mise à jour au " . gmdate("c");
			echo "<br />";
			die();
		}
		function action_adhesion(& $handler) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT
					ii.id_individu as IdIndividu,
					year(ii.date_inscription) as  AnInscription,
					ti.delai_radiation_non_adhesion as DelaiRadiation 
					from 
					individu_inscription ii,
					type_inscription ti 
					where " . " ii.date_adhesion is null " . " and ii.date_radiation is null 
					 and ii.id_type_inscription=ti.id
				        and ti.delai_radiation_non_adhesion is not null
					and ii.id_organisme=" . $this->m_postvars["id"] . " 
				");
			for ($i = 0; $i < count($data); $i++) {
				$anadhesionprevue = $data[$i]["AnInscription"] + $data[$i]["DelaiRadiation"];
				$avertir = 0;
				if ($anadhesionprevue < gmdate("Y")) {
					$avertir = 1;
				}
				$effectuer = 0;
				if ($anadhesionprevue < gmdate("Y") + 1) {
					$effectuer = 1;
				}
				if ($effectuer == '1') {
					$avertir = 0;
				}
				$db->query("update individu_inscription " . " set an_adhesion_prevue=" . $anadhesionprevue . " , avertir_radiation_adhesion_o_n=" . $avertir . " , effectuer_radiation_adhesion_o_n=" . $effectuer . " where id_individu=" . $data[$i]["IdIndividu"] . " and id_organisme=" . $this->m_postvars["id"] . "");
			}
			$data1 = $db->getrows("SELECT count(id) as avertir" . " from individu_inscription " . " where avertir_radiation_adhesion_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$data2 = $db->getrows("SELECT count(id) as effectuer" . " from individu_inscription " . " where effectuer_radiation_adhesion_o_n='1'" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des radiations pour non adhésion", "Le traitement recherche :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour le délai mentionné dans le type d'inscription
				                           </ul>
				                          <br>Calcule l'année de radiation prévue et positionne la demande de cotisation en conséquence 
				                          <br>il y a <b>" . $data1[0]["avertir"] . " avertissements que la période initiale, libre de cotisation, est terminée.</b>" . "<br>il y a <b>" . $data2[0]["effectuer"] . " radiations à effectuer suite à non réponse.</b>" . "<br>", "adhesion_et_pas_de_cotisation", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_adhesion_et_pas_de_cotisation(& $handler) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT
					ii.id_individu as IdIndividu 
						from 
					individu_inscription ii,
					type_inscription ti " . " where " . " ii.date_adhesion is not null " . " and ii.date_radiation is null 
					 and ii.id_type_inscription=ti.id
				        and ti.cotisation_organisme_o_n='1'
					and ii.id_organisme=" . $this->m_postvars["id"] . " and ii.id_individu not in " . "( select ic.id_individu " . " from individu_cotisation ic," . " organisme_cotisation oc" . " where ic.id_cotisation=oc.id " . " and oc.id_organisme=" . $this->m_postvars["id"] . " )
				");
			for ($i = 0; $i < count($data); $i++) {
				$db->query("update individu_inscription " . " set  adhesion_et_pas_de_cotisation_o_n=1 " . " where id_individu=" . $data[$i]["IdIndividu"] . " and id_organisme=" . $this->m_postvars["id"] . "");
			}
			$data1 = $db->getrows("SELECT count(id) as pasdecot" . " from individu_inscription " . " where adhesion_et_pas_de_cotisation_o_n=1" . " and id_organisme=" . $this->m_postvars["id"] . " ");
			$this->setupScreen("Recherche des adhésions sans cotisation", "Le traitement recherche :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les adhésions avec inscription de type cotisation à l'organisme.
				                           </ul>
				                          <br>Recherche les adhésions qui n'ont pas eu de cotisation versée 
				                          <br>il y a <b>" . $data1[0]["pasdecot"] . " adhésions pour lesquelles il n'y a pas eu de cotisation.</b>" . "<br>", "complement_correspondance", array (
			id => $this->m_postvars["id"]
			));
		}
		function action_complement_correspondance(& $handler) {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT
					ii.id_individu ,
					ii.envoyer_carte_adherent_o_n,
				 ii.envoyer_timbre_o_n,
				 ii.envoyer_recu_fiscal_o_n,
				 ii.reclamer_cotisation_o_n,
				 ii.avertir_radiation_cotisation_o_n,
				  ii.avertir_radiation_cotisation_o_n," . "ii.adhesion_et_pas_de_cotisation_o_n," . " ii.an_derniere_cotisation," . " ii.an_radiation_cotisation_prevue," . " year(ii.date_inscription)as annee_inscription," . " ii.an_adhesion_prevue
					from 
					individu_inscription ii " . " where " . " ii.id_organisme=" . $this->m_postvars["id"] . " and (ii.envoyer_carte_adherent_o_n=1
				or ii.envoyer_timbre_o_n=1
				or ii.envoyer_recu_fiscal_o_n=1
				or ii.reclamer_cotisation_o_n=1
				or ii.avertir_radiation_cotisation_o_n=1
				or ii.avertir_radiation_adhesion_o_n=1
				or ii.adhesion_et_pas_de_cotisation_o_n=1
				) 	and ii.date_radiation is null 
				");
			if (count($data) > 0) {
				$data2 = $db->getrows(" select p_texte_carte, p_explication_carte," . " p_texte_timbre, p_explication_timbre," . " p_texte_recu_fiscal, p_explication_recu_fiscal," . " p_texte_rappel_cotisation, p_explication_rappel_cotisation," . " p_texte_radiation_non_cotisation, p_explication_radiation_non_cotisation," . " p_texte_radiation_non_adhesion, p_explication_radiation_non_adhesion " . " from organisme " . " where id=" . $this->m_postvars["id"] . " ");
				$p_organisme = array (
				"p_texte_carte" => $data2[0]["p_texte_carte"],
				"p_texte_timbre" => $data2[0]["p_texte_timbre"],
				"p_texte_recu_fiscal" => $data2[0]["p_texte_recu_fiscal"],
				"p_texte_rappel_cotisation" => $data2[0]["p_texte_rappel_cotisation"],
				"p_texte_radiation_non_cotisation" => $data2[0]["p_texte_radiation_non_cotisation"],
				"p_texte_radiation_non_adhesion" => $data2[0]["p_texte_radiation_non_adhesion"],
				"p_explication_carte" => $data2[0]["p_explication_carte"],
				"p_explication_timbre" => $data2[0]["p_explication_timbre"],
				"p_explication_recu_fiscal" => $data2[0]["p_explication_recu_fiscal"],
				"p_explication_rappel_cotisation" => $data2[0]["p_explication_rappel_cotisation"],
				"p_explication_radiation_non_cotisation" => $data2[0]["p_explication_radiation_non_cotisation"],
				"p_explication_radiation_non_adhesion" => $data2[0]["p_explication_radiation_non_adhesion"]
				);
				for ($i = 0; $i < count($data); $i++) {
					$p = array ();
					$e = array ();
					$j = 0;
					if ($data[$i]["envoyer_carte_adherent_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_carte"];
						// $p[$j]=str_replace("(ID)", "'".$valeur."'",$atkfilter);
						$e[$j] = $p_organisme["p_explication_carte"];
						$j++;
					}
					if ($data[$i]["envoyer_timbre_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_timbre"];
						$p[$j] = str_replace("(ID)", $data[$i]["an_derniere_cotisation"], $p[$j]);
						$e[$j] = $p_organisme["p_explication_timbre"];
						$j++;
					}
					if ($data[$i]["envoyer_recu_fiscal_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_recu_fiscal"];
						$p[$j] = str_replace("(ID)", $data[$i]["an_derniere_cotisation"], $p[$j]);
						$e[$j] = $p_organisme["p_explication_recu_fiscal"];
						$j++;
					}
					if ($data[$i]["reclamer_cotisation_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_rappel_cotisation"];
						$p[$j] = str_replace("(ID)", $data[$i]["an_derniere_cotisation"] + 1, $p[$j]);
						$e[$j] = $p_organisme["p_explication_rappel_cotisation"];
						$j++;
					}
					if ($data[$i]["avertir_radiation_cotisation_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_radiation_non_cotisation"];
						$p[$j] = str_replace("(ID)", $data[$i]["an_derniere_cotisation"], $p[$j]);
						$e[$j] = $p_organisme["p_explication_radiation_non_cotisation"];
						$j++;
					}
					if ($data[$i]["avertir_radiation_adhesion_o_n"] == true or $data[$i]["adhesion_et_pas_de_cotisation_o_n"] == true) {
						$p[$j] = $p_organisme["p_texte_radiation_non_adhesion"];
						$p[$j] = str_replace("(ID)", $data[$i]["annee_inscription"], $p[$j]);
						$e[$j] = $p_organisme["p_explication_radiation_non_adhesion"];
						$j++;
					}
					for ($j = 0; $j < 6; $j++) {
						$p[$j] = str_replace("\r\n", "\n", $p[$j]);
						$e[$j] = str_replace("\r\n", "\n", $e[$j]);
					}
					$db->query("update individu_inscription " . " set p1='" . addslashes($p[0]) . "'," . "e1='" . addslashes($e[0]) . "'," . "p2='" . addslashes($p[1]) . "'," . "e2='" . addslashes($e[1]) . "'," . "p3='" . addslashes($p[2]) . "'," . "e3='" . addslashes($e[2]) . "'," . "p4='" . addslashes($p[3]) . "'," . "e4='" . addslashes($e[3]) . "'," . "p5='" . addslashes($p[4]) . "'," . "e5='" . addslashes($e[4]) . "'," . "p6='" . addslashes($p[5]) . "'," . "e6='" . addslashes($e[5]) . "' where id_individu=" . $data[$i]["id_individu"] . " and id_organisme=" . $this->m_postvars["id"] . "");
					//				$db->query("update individu_inscription " . " set p1='" . escapeSQL($p[0]) . "'," . "e1='" . escapeSQL($e[0]) . "'," . "p2='" . escapeSQL($p[1]) . "'," . "e2='" . escapeSQL($e[1]) . "'," . "p3='" . escapeSQL($p[2]) . "'," . "e3='" . escapeSQL($e[2]) . "'," . "p4='" . escapeSQL($p[3]) . "'," . "e4='" . escapeSQL($e[3]) . "'," . "p5='" . escapeSQL($p[4]) . "'," . "e5='" . escapeSQL($e[4]) . "'," . "p6='" . escapeSQL($p[5]) . "'," . "e6='" . escapeSQL($e[5]) . "' where id_individu=" . $data[$i]["id_individu"] . " and id_organisme=" . $this->m_postvars["id"] . "");
				}
			}
			$user = getUser();
			$id = $user["id"];
			$sql="Update organisme set date_derniere_preparation_fin=UTC_TIMESTAMP(), id_derniere_preparation_fin=".$id." where id=".$this->m_postvars["id"]."";
			$db->query($sql);

			$this->setupScreen("Confection des messages de complément (carte, timbre, reçu ...)", "Le traitement recherche :
				                          <ul>
				                            <li>Pour l'organisme mentionné.
				                            <li>Pour les inscrits non radiés.
				                            <li>Pour les inscrits ayant des indicateurs de complément de correspondance.
				                           </ul>
				                          <br>Traite les indicateurs et compose les textes qui seront imprimés en complément à envoyer lors de la correspondance.
				                          <br>il y a <b>" . count($data) . " compléments à éditer et à envoyer.</b>" . "<br><br> <b>Le traitement périodique est terminé</b>", "", array (
			id => $this->m_postvars["id"]
			));
		}
		function setupScreen($title, $output, $nextaction = "", $params = array ()) {
			atkimport("atk.ui.atkui");
			$ui = & atkUI :: getInstance();
			$db = & atkGetDb();
			$id_organisme = $this->m_postvars["id"];
			$data = $db->getrows("SELECT nom FROM organisme where id=" . $id_organisme . " ");
			$nom_organisme = $data[0]["nom"];
			$title = $nom_organisme . " - " . $title;
			$form = '<div align="left"><b>' . $title . '</b><br><br>';
			$form .= '<form action="dispatch.php">' . session_form(SESSION_NEW) . '<input type="hidden" name="atknodetype" value="traitement.trimestriel">' . '<input type="hidden" name="atkaction" value="' . $nextaction . '">' . $output;
			if (count($params)) {
				foreach ($params as $key => $value) {
					$form .= '<input type="hidden" name="' . $key . '" value="' . $value . '">';
				}
			}
			if ($nextaction != "") {
				if ($nextaction == "achievostart") {
					$btn = "Start using Achievo";
				} else
				if ($nextaction == $this->m_action) {
					$btn = "Retry";
				} else {
					$btn = "Continuer";
				}
				$form .= '<br><br><input type="submit" value="' . $btn . '"><br><br>';
			}
			$form .= '</form></div>';
			$page = & atkPage :: getInstance();
			$theme = & atkTheme :: getInstance();
			$page->register_style($theme->stylePath("style.css"));
			$page->addContent($ui->renderBox(array (
			"content" => $form,
			"title" => $title
			)));
		}
}
?>