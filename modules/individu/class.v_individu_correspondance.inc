<?php
atkimport("atk.utils.atkmessagequeue");
class v_individu_correspondance extends atkMetaNode {
	var $table = "v_individu_correspondance";
	var $primary_field = "";
	var $module = "v_individu_correspondance";
	var $node = "v_individu_correspondance";
	var $index_field = "nom_organisme";
	var $order_field = "nom,prenom";
	var $descriptor_field = "[nom_organisme]";
	// start constructor
	function v_individu_correspondance() {
		// tabs labels
		// call constructor parent
		$this->atkMetaNode(array (
			"flags" => NF_ADD_LINK  | NF_ADDAFTERADD
		));
		//event log
		$this->addListener(atknew("atk.utils.atkeventlog"));
		// node attributes
		$this->add(new atkRowCounter("#"), NULL, 1);
		$this->add(new atkNumberAttribute("id_organisme", 0, 10, 0), NULL, 0);
		$this->add(new atkAttribute("nom_organisme", AF_SEARCHABLE), NULL, 100);
		$this->add(new atkNumberAttribute("id_individu", 0, 10, 0), NULL, 200);
		$this->add(new atkAttribute("titre", 0), NULL, 300);
		$this->add(new atkAttribute("nom", 0), NULL, 400);
		$this->add(new atkAttribute("prenom", 0), NULL, 500);
		$this->add(new atkTextAttribute("p1"), NULL, 600);
		$this->add(new atkTextAttribute("e1", AF_HIDE_LIST), NULL, 700);
		$this->add(new atkTextAttribute("p2"), NULL, 800);
		$this->add(new atkTextAttribute("e2", AF_HIDE_LIST), NULL, 900);
		$this->add(new atkTextAttribute("p3"), NULL, 1000);
		$this->add(new atkTextAttribute("e3", AF_HIDE_LIST), NULL, 1100);
		$this->add(new atkTextAttribute("p4"), NULL, 1200);
		$this->add(new atkTextAttribute("e4", AF_HIDE_LIST), NULL, 1300);
		$this->add(new atkTextAttribute("p5"), NULL, 1400);
		$this->add(new atkTextAttribute("e5", AF_HIDE_LIST), NULL, 1500);
		$this->add(new atkTextAttribute("p6"), NULL, 1600);
		$this->add(new atkTextAttribute("e6", AF_HIDE_LIST), NULL, 1700);
		//smart search
		$this->setExtendedSearchAction('smartsearch');
		$this->setSecurityAlias("individu.individu");
		// index, order and table setups
		$this->setIndex($this->index_field); // set index attribute
		$this->setOrder($this->order_field); // set order attribute(s)
		$this->setTable($this->table); // set node table
		$this->m_securityMap["document"] = "view";
	} // end constructor
	function meta(& $policy) {
	} // end function
	function id_individu_display($record, $mode) {
		return href(dispatch_url("individu.individu", "edit", array (
			'atkselector' => "individu.id=" . $record['id_individu']
		), "dispatch.php"), text($record['id_individu']), SESSION_NESTED);
	}
	function id_organisme_display($record, $mode) {
		return href(dispatch_url("organisme.organisme", "edit", array (
			'atkselector' => "organisme.id=" . $record['id_organisme']
		), "dispatch.php"), text($record['id_organisme']), SESSION_NESTED);
	}
	function assignDocumentVars(& $documentWriter, $selector) {

		$records = $this->selectDb($this->m_postvars["atkfilter"], "", "", $this->m_viewExcludes, "", "document");
//		print_r ($records[0]);
//		die();
		$documentWriter->assignDocumentMultiRecord($this, $records, $prefix = "");
	}
	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function action_save(& $handler) {
		$attr = & $this->getAttribute($this->primary_field);
		$attr->removeFlag(AF_PRIMARY);
		return $handler->action_save();
	} // end function 
	function nom_organisme_display($record, $mode) {
		$attr = & $this->getAttribute("nom_organisme");
		$original = $attr->display($record, $mode);
		$pparams[$this->primary_field] = $record[$this->primary_field];
		$pparams["atkselector"] = $this->node . "." . $this->primary_field . "='" . $record[$this->primary_field] . "'";
		// link name
		$original = href(dispatch_url($this->module . "." . $this->node, "view", $pparams, "dispatch.php"), $original, SESSION_NESTED);
		return $original;
	} // end function
	/* START NODE MESSAGING */
	// this function is automatically called after a record has been updated
	function postUpdate($record) {
		// notify the user that the record has been updated
		$this->printMessage("Record, " . $record[$this->index_field] . ", Updated Successfully");
		return true;
	}
	// this function is automatically called after a record has been deleted			
	function postDelete($record) {
		// notify the user that the record has been deleted
		$this->printMessage("Record, " . $record[$this->index_field] . ", Deleted Successfully");
		return true;
	}
	// this function is automatically called after a record has been added
	function postAdd(& $record) {
		$this->getMyLastId($record);
		// notify the user that the record has been created
		$this->printMessage("Record, " . $record[$this->index_field] . ", Created Successfully");
		return true;
	}
	/*
	     Jorge Garifuna - info@garidigital.com
	     created: 9/12/06
	     
	     this function obtains the last inserted id of specified table 
	*/
	function getMyLastId(& $record) {
		$db = & atkGetDb();
		// get the id of the last record that was inserted
		$query = "select max(" . $this->primary_field . ") as last_id from " . $this->table;
		$rows = $db->getrows($query);
		if (count($rows) > 0) {
			$id = $rows[0]["last_id"];
			$record[$this->primary_field] = $id;
			$record["atkprimkey"] = $this->node . "." . $this->primary_field . "='$id'";
		}
	}
	/*
	     This function is a wrapper to print messages to the top of the screen
	     Author: Jorge Garifuna (GariDigital.com) <info@GariDigital.com>
	     Created Date: 6/27/06
	
	     @param $message               The actual message to be printed
	     @param $background_color      The background color of the bar to show message
	     @param $text_color            The color of the text to be printed
	     
	     Note:
	     - If your visual creativity is bad like mine, you can find nice colors at the following site:
	          http://www.colorcombos.com/index.html
	          
	     - Make sure to include "atkimport("atk.utils.atkmessagequeue");" at the top of your node 
	
	*/
	function printMessage($message, $background_color = '#6787B0', $text_color = 'white') {
		atkMessageQueue :: addMessage("<div style='background-color: " . $background_color . ";'><b><font color='" . $text_color . "'>" . $message . "</font></b></div>"); //     FFAB35          
	}
	/* END NODE MESSAGING */
	function descriptor_def() {
		return $this->descriptor_field;
	}
	// used for header section of list view page
	function adminHeader() {
		// get messages from the queue
		$msgs = atkMessageQueue :: getMessages();
		if (count($msgs) > 0) {
			$msgs = implode("<br>", $msgs);
		} else {
			$msgs = "";
		}
		$help_text = $msgs . "
		                    
				          <!-- h1><font color=#FF6347>v_individu_correspondance</font></h1 -->
				     ";
		return $help_text;
	} // end function
	// used for footer section of list view page
// end function
	// this function is called when editing an individual record
	// any information here will be displayed on the footer section of the edited record page
	function editPage(& $handler, $record, $locked = false) {
		return $this->detailPageFooter($handler, $record, $locked);
	}
	// this function is called when viewing an individual record
	// any information here will be displayed on the footer section of the viewed record page
	function viewPage(& $handler, $record, $locked = false) {
		return $this->detailPageFooter($handler, $record, $locked, "view");
	}
	// this is a custom helper function for editPage and viewPage
	// you can consolidate operations here unless you need to display different information
	// when editing and viewing the record
	// the information will be displayed on the footer page when editing or viewing an individual record	
	function detailPageFooter(& $handler, $record, $locked = false, $mode = "edit") {
		if ($mode == "view") {
			$page = $handler->viewPage($record, $locked);
		} else { // edit
			$page = $handler->editPage($record, $locked);
		}
		$data_info = "";
		$page .= $data_info;
		return $page;
	} // end function    
} // end node v_individu_correspondance
?>