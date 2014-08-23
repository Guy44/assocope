<?php
atkimport("atk.assmetanode");

class debug  extends assMetaNode
{
	var $table="atkdebug";
	function meta(&$policy)
	{}
	function debug()
	{
		$this->atkMetaNode();

		$this->atkNode("debug", NF_ADD_LINK | NF_MRA);
		$this->add(new atkRowCounter("#"),NULL,1);
		$this->setExtendedSearchAction('smartsearch');
		$this->setSecurityAlias("profil.profil");
		$this->add(new atkManyToOneRelation("userid","profil.utilisateur",AF_SEARCHABLE),100);
		$this->add(new atkAttribute("stamp",AF_SEARCHABLE),150);
//$this->add(new atkAttribute("debug_message",AF_SEARCHABLE),155);
	$this->add(new atkTextAttribute("debug_message",array(
	'rows' => 5,
			'cols' => null,
			'autoadjust' => true),AF_SEARCHABLE),155);
	$this->add(new atkfckattribute("contexte", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '500px'
		)),200);

		$this->addListener(atknew("atk.utils.atkeventlog"));
		$this->setOrder("stamp DESC");
//		atkdebug_gg('test',true);

	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
function recordActions($rec, & $actions, & $mraactions) {
		
		$mraactions['delete'] = "delete";
		


	}


	function descriptor_def()
	{
		return "[id] [stamp]";
	}

}

?>