<?php

class yaquelquun extends assMetaNode {
	var $m_report = array ();
	var $m_cancontinue = true;
	var $m_currentmodule = "";

	function yaquelquun() {
		$this->atkNode("yaquelquun");
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["individus_organisme"] = "view";

	}
	function action_individus_organisme(& $handler) {
	$header_ajax='<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js">
</script>
				<script>
				$(document).ready(function() {
				if (navigator.geolocation) {
				navigator.geolocation.getCurrentPosition(successCallback, errorCallback, , {enableHighAccuracy : true, timeout:10000, maximumAge:600000});
	} else {
				alert(\'GPS not supported\');
	}
	
					
	});
					
				function successCallback(position) {
				alert("Latitude : " + position.coords.latitude + ", longitude : " + position.coords.longitude);
	}
	
				function errorCallback(error){
				switch(error.code){
				case error.PERMISSION_DENIED:
				alert("L\'utilisateur n\'a pas autorisé l\'accès à sa position");
				break;
				case error.POSITION_UNAVAILABLE:
				alert("L\'emplacement de l\'utilisateur n\'a pas pu être déterminé");
				break;
				case error.TIMEOUT:
				alert("Le service n\'a pas répondu à temps");
				break;
	}
					
				</script>
';
			

		$id_organisme = $this->m_postvars["id"];
	//	$this->p($this->m_postvars);
	$res= "<button>Send an HTTP POST request to a page and get the result back</button>";
			
		
		atkimport("atk.ui.atkui");
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		$page->addContent($res);
		// render($title=null, $flags=HTML_STRICT,$extrabodyprops="", $extra_header="")
		$output->output($page->render("Y a-t'il quelqu'un dans le coin ?", true, $header_ajax));
	}
		
	/*		
			
		$this->setupScreen("Recherche des individus d'un organisme", "
				Votre position actuelle :<br/>
				Longitude : <br/>
				Latitude : <br/>
				<br/><br/>
				Choix du rayon en kilomètres :<br/>
				<select id=\"radius\">
				<option value=\"5\" selected>5</option>
				<option value=\"15\">15</option>
				<option value=\"50\">50</option>
				<option value=\"150\">150</option>
				</select>
					
					
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
	*/
		
}
?>