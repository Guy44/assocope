<?php
class editeur_fr_lng  extends atkFileEditor
{
	function editeur_fr_lng()
	{
		$this->atkFileEditor("editeur_fr_lng","./languages/",".lng");
		$this->m_securityMap["dirchange"] = "view";
		$this->setSecurityAlias("table.activite");
	}
}

?>