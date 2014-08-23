<?php
class atgFileManyToOneRelation extends atkManyToOneRelation {


	function display($record, $mode) {
		$id=$this->m_destInstance->primaryKey($record[$this->fieldName()]);
		$table=$this->m_destInstance->m_table;
		$db = & atkGetDb();
		$data = $db->getrows("SELECT file_extension FROM ".$table." where $id ");
		$extension=$data[0]["file_extension"];

		if ($extension=="")
		{ $result=parent :: display($record, $mode);}
		else
		{ 
		$result=parent :: display($record, $mode).	href(dispatch_url($this->m_destination,"fichier",array("atkselector"=>$id,"atkaction"=>"fichier")),
                       '  <font color="ForestGreen"> <b>Fichier</b>',
		SESSION_NESTED,
		false,'class="atkmanytoonerelation"');
		}
		return $result;
	}
	function edit($record, $fieldprefix="", $mode="edit") {
		$id=$this->m_destInstance->primaryKey($record[$this->fieldName()]);
		$table=$this->m_destInstance->m_table;
		$db = & atkGetDb();
		$data = $db->getrows("SELECT file_extension FROM ".$table." where $id ");
		$extension=$data[0]["file_extension"];
		if ($extension=="")
		{ $result=parent :: edit($record,"", $mode);}
		else
		{
		$result=parent :: edit($record,"", $mode).	href(dispatch_url($this->m_destination,"fichier",array("atkselector"=>$id,"atkaction"=>"fichier")),
                     '  <font color="ForestGreen"> <b>Fichier</b>',
		SESSION_NESTED,
		false,'class="atkmanytoonerelation"');
		}
		return $result;
	}
}
?>
