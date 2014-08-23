<?php
useattrib("atknumberattribute");
class scheduler_cyclus_not  extends assMetaNode
{
	function scheduler_cyclus_not()
	{
		$this->atkMetaNode();
		$this->atkNode("scheduler_cyclus_not", NF_ADD_LINK  | NF_MRA );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkManyToOneRelation("id_groupe_travail", "organisme.groupe_travail", AF_SEARCHABLE | AF_RELATION_AUTOLINK ));
		 
		$this->add(new atkDateAttribute("date_exception", "Y-m-d","Y-m-d", 0, 0));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");

		$this->setTable("scheduler_cyclus_not");
		$this->setSecurityAlias("individu.individu");
		 
	}
	function recordActions($rec, & $actions, & $mraactions) {
	$mraactions['sans_courriel'] = "sans_courriel";
	}
	
	function descriptor_def()
	{
		return "[date]";
	}
}
?>