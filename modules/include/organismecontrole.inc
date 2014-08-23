<?php
			$attribute = & $this->getAttribute("id_organisme");
		$original = $attribute->display($record, $mode);
		global $g_sessionManager;
		$g_acces_public_seulement = $g_sessionManager->getValue("atgAccesPublicSeul_o_n", "globals");
		$g_organismes_autorises = $g_sessionManager->getValue("atgOrganismesAutorises", "globals");
		$db = & atkGetDb();
		$sql = "select acces_public_o_n as acces_public_o_n from organisme where id='" . $record["id_organisme"]["id"] . "'";
		$ggrow = $db->getrows($sql);
		if (($ggrow[0]["acces_public_o_n"] == '1') || ($g_acces_public_seulement == '0') || (($g_acces_public_seulement == '1') && ($ggrow[0]["acces_public_o_n"] == '0') && (in_array($record["id_organisme"]["id"], $g_organismes_autorises)))) {
		} else {
			$original = $record["id_organisme"]["nom"] . ' - ' . $record["id_organisme"]["sigle"];
		}
		return $original;	
		
?>