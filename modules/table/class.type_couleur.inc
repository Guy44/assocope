<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgtextnomattribute");
class type_couleur extends assMetaNode {
	var $table = "type_couleur";

	function meta(& $policy) {
		$policy->addFlags("nom", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_couleur() {
		$this->atkMetaNode();
		$this->atkNode("type_couleur", NF_ADD_LINK| NF_ADDAFTERADD | NF_EXT_SORT);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"nom",
				"exemple",
		"exemple2","exemple3",
		"code_rgb", "red", "green","blue",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
		$this->add(new atkAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY | AF_UNIQUE),100);
		$this->add(new atkAttribute("exemple", AF_SEARCHABLE),105);
		$this->add(new atkDummyAttribute("exemple2",0 , AF_HIDE_EDIT),110);
		$this->add(new atkDummyAttribute("exemple3",0 , AF_HIDE_EDIT),111);
		$this->add(new atkAttribute("code_rgb", AF_SEARCHABLE),115);
		$this->add(new atkAttribute("red", AF_SEARCHABLE|AF_OBLIGATORY),120);
		$this->add(new atkAttribute("green", AF_SEARCHABLE|AF_OBLIGATORY),125);
		$this->add(new atkAttribute("blue", AF_SEARCHABLE|AF_OBLIGATORY),130);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("nom");
	}
	function exemple_display($record, $mode) {
	return '<div style="background-color:'.$record["nom"].'; font-size: 20px;">'.$record["nom"] .'</div>'	;
	}
	function exemple2_display($record, $mode) {
	return '<div style="color:'.$record["nom"].'; font-size: 20px;">'.$record["nom"] .'</div>'	;
	}
	function exemple3_display($record, $mode) {
	return '<div style="background-color:'.$record["code_rgb"].'; font-size: 20px;">'.$record["nom"] .'</div>'	;
	}
	function descriptor_def() {
		return "[nom] [code_rgb]";
	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 150;
		return $handler->action_admin();
	}
function validate(&$record, $mode)
{
    if ($record["red"]<'00' ) {
        atkhalt ("Red doit être compris entre '00' et 'FF' ",'critical');
    } 
     if ($record["green"]<'00' || $record["green"] >'FF' ) {
        atkhalt ("Green doit être compris entre '00' et 'FF' ",'warning');
    } 
     if ($record["blue"] <'00' || $record["blue"] >'FF' ) {
        atkhalt ("Blue doit être compris entre '00' et 'FF' ",'warning');
    } 
   $record["code_rgb"]='#'.$record["red"].$record["green"].$record["blue"];
        parent::validate($record, $mode);
    
  }
  

}
?>