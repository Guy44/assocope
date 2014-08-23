<?php
class userprefs extends atkNode {
	function userprefs() {
		$this->atkNode("userprefs", NF_NO_ADD | NF_NO_DELETE);
		/*$this->add(new atkTabbedPane("Pane1",
			array(
			"Général"=>	array("passwordexplanation","mot_de_passe","theme","commentaire",
		 "id_creation","date_creation","id_modification","date_modification")
			),AF_NO_LABEL));
			*/
		$this->add(new atkNumberAttribute("id", AF_PRIMARY | AF_HIDE));
		$this->add(new atkAttribute("identifiant", AF_HIDE));
		if (atkconfig("authentication") == "db") {
			$this->add(new atkDummyAttribute("passwordexplanation", atktext("password_leaveblankifunchanged"), AF_HIDE_ADD | AF_HIDE_LIST));
			$this->add(new atkPasswordAttribute("mot_de_passe", AF_OBLIGATORY));
		}
		$this->add(new atkManyToOneRelation("id_langue_application", "table.type_langue", AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_SEARCHABLE));
		$this->add(new atkEmailAttribute("courriel", false, AF_SEARCHABLE));
		$this->add(new atkBoolAttribute("tt_o_n"));
		$this->add(new atkBoolAttribute("sticky_tt_o_n"));
		$this->add(new atkBoolAttribute("biodiversite_o_n"));
		$this->add(new atkBoolAttribute("golf_o_n"));
		$this->add(new atkNumberAttribute("manytoone_autocomplete_minchars",null,2,0));
		$this->add(new atkBoolAttribute("table_des_matieres_wiki_o_n"));
		$this->add(new atkBoolAttribute("stats_page_o_n"));
		$this->add(new atkBoolAttribute("icones_detaillees_o_n"));
		$this->add(new atkBoolAttribute("icones_estampillage_o_n"));
		$this->add(new atkBoolAttribute("afficher_portrait_o_n"));
		$this->add(new atkBoolAttribute("copie_courriel_o_n"));
		$this->add(new atkEmailAttribute("courriel_copie", false, AF_SEARCHABLE));
		$this->add(new atkEmailAttribute("google_docs_courriel", false, AF_SEARCHABLE));
		$this->add(new atkPasswordAttribute("google_docs_code", false,  AF_PASSWORD_NO_ENCODE | AF_HIDE_LIST));
		
//		$this->add(new atkColorPickerAttribute("tooltip_couleur_bg","",AF_OBLIGATORY|AF_HIDE_LIST|AF_FORCE_LOAD|AF_POPUP));

	$this->add(new atkAttribute("tt_couleur_bg"));

		$themes = getThemes();
		$this->add(new atkListAttribute("theme", $themes, $themes, AF_HIDE_ADD | AF_NO_TRANSLATION));
		$this->setTable("app_utilisateur", "app_utilisateur");
		$this->setSecurityAlias("individu.individu");
	}
	function initial_values() {
		$init_vals = array ();
		$init_vals ["tooltip_color"]='#E2E7FF';
		return $init_vals;
	}
	function descriptor_def() {
		return "[identifiant]";
	}
	function postUpdate($record) {
		global $g_user, $g_sessionManager, $g_securityManager;
		if ($record["id"] == $g_user["id"]) {
			// If the theme was updated, we must change it in the session (or you won't
			// see the update.
			$g_sessionManager->globalVar("atkTheme", $record["theme"], true);
			// Also, if we edited userpreferences, then the current record
			// should be stored in the session as user record, so Achievo
			// will immediately start to use the new settings.
			$g_securityManager->reloadUser();
			// Also, we must refresh the screen.
			echo '<script language="javascript">';
			echo 'parent.location = "index.php"';
			echo '</script>';
			exit;
		}
	}
}
?>