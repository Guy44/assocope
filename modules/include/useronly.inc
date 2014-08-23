<?php

 
      $user = getUser();
	$id=$user["id"];
	if (isset($id))
	{
	$db = &atkGetDb();
	$data = $db->getrows("SELECT id_individu from app_utilisateur where id=".$id." ");
	$id_individu=$data[0]["id_individu"];   	
    $this->addFilter($this->m_table."."."id_individu",$id_individu);
	}
?>