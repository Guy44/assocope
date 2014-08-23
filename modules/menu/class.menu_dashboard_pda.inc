<?php
class menu_dashboard_pda extends atkNode {
	function menu_dashboard_pda() {
		$this->atkNode("menu_dashboard_pda", NF_MRA);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkDummyAttribute("individu", "individu", AF_NOLABEL), null, 10);
		$this->add(new atkDummyAttribute("organisme", "organisme", AF_NOLABEL), null, 20);
		global $g_sessionManager;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$loggedin = "<b>" . $g_nomutilisateur . "</b>";
		$this->addStyle("guy.css");
		$loggedin .= ' &nbsp; <a href="index.php?atklogout=1" target="_top">' . ucfirst(atktext("logout", "atk")) . '</a> &nbsp;';
		$this->add(new atkDummyAttribute("aide", ">>>>>>>>>> " . $loggedin . " " . nodeHelpUrl($this->atkNodeType()) . " Tutoriel " . nodeDemandeUrl($this->atkNodeType()) . " " . nodeSourceUrl($this->atkNodeType()) . " <<<<<<<<<<", AF_NO_LABEL | AF_HIDE_LIST));
		$this->setTable("");
	}
	function individu_edit() {
			$content = href(dispatch_url("individu.individu_pda", "admin"), atktext("individus", "core"), SESSION_NEW, false) . '&nbsp; ';


		return $content;
	}
		function organisme_edit() {
				$content = href(dispatch_url("organisme.organisme_pda", "admin"), atktext("organismes", "core"), SESSION_NEW, false) . '&nbsp; ';
			return $content;			
				
	}
	function getFormButtons($mode, $record) {
		return array ();
	}
}
?>