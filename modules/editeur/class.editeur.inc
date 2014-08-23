<?php
atkimport("atk.assmetanode");
useattrib("atkdateattribute");
useattrib("atkrowcounter");
atkimport("atk.atkfileeditor");

class editeur  extends atkFileEditor
{



	function editeur()
	{

		$this->atkFileEditor("editeur","./modules/","\..*");
		$this->atkFileEditor("editeur","./modules/table/","\..*");
		$this->atkFileEditor("editeur","./","\..*");
		$this->m_securityMap["dirchange"] = "view";
		//	$this->add(new atkFileEditor("association", "./modules/" ));
		/* this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 $this->add(new atkFileEditor("association/modules", $dir="", $filter="", $flags=0));
		 */
		$this->setSecurityAlias("table.activite");
	}
	function descriptor_def()
	{

	}




}

?>