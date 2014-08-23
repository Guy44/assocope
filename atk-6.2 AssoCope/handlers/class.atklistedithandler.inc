<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage handlers
 *
 * @copyright (c)2000-2004 Ivo Jansch
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 5996 $
 * $Id: class.atkdeletehandler.inc 5996 2008-07-04 09:02:22Z peter $
 */

/**
 * Handler for the 'Editable List' action of a node. 
 *
 * @author Guy Gourmellet
 * @package atk
 * @subpackage handlers
 *
 */
class atkListEditHandler extends atkActionHandler
{
	/**
	 * The action handler.
	 */
	function action_listedit()
	{
		echo 'Oui';
		die();
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}

		$node = &atkGetNode($this->m_postvars["atknodetype"]);
	
		$descripteur.=$node_ligne->action_admin_liste("releve",$id_releve_banque,$id_organisme);
		($data[0]["id_document_releve"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_document_releve"],'n',$lien_releve) : $lien_releve="";
		$descripteur.='<br/><div '.$this->m_styleTitreLigne.'>Relevé de la banque : '.$lien_releve."</div><br/>";
		unset ($node);
		
		
		
		foreach ($select as $id_variable) {
			$record = $this->getRecord();
		$this->handleProcess($record);
		}
		$this->redirect();
		
	}
function handleProcess($record)
    {
      // load original record if needed
      $this->getNode()->trackChangesIfNeeded($record);

      // just before we validate the record we call the preUpdate() to check if the record needs to be modified
      $this->m_node->executeTrigger("preUpdate", $record);

      $this->m_node->validate($record, "update");

      $error = $this->hasError($record);

      if ($error)
      {
        $this->handleError($record);
        return;
      }

      $db = &$this->m_node->getDb();
      if(!$this->m_node->updateDb($record))
      {
        $this->handleUpdateError($db, $record);
      }
      else
      {
        $this->handleUpdateSuccess($db, $record);
      }
    }
 function handleError($record)
    {
      $this->setRejectInfo($record);
      $location = session_url(dispatch_url($this->m_node->atknodetype(),"edit",array("atkselector"=>$this->m_node->primaryKey($record))),SESSION_REPLACE);
      $this->m_node->redirect($location);
    }
 function handleUpdateError(&$db, $record)
    {
      $db->rollback();
      if($db->getErrorType()=="user")
      {
        triggerError($record, 'Error', $db->getErrorMsg(), '', '');
        $this->m_node->m_action="edit";
        global $ATK_VARS; $ATK_VARS["atkaction"]="edit";
        $page = &$this->getPage();
        $edithandler = $this->m_node->getHandler("edit");
        $page->addContent($edithandler->invoke("editPage", $record));
      }
      else
      {
        $location = $this->m_node->feedbackUrl("update",ACTION_FAILED, $record, $db->getErrorMsg());
        $this->m_node->redirect($location, $record);
      }
    }
  function handleUpdateSuccess(&$db, $record)
    {
      $db->commit();
      $this->notify("update", $record);

      $this->clearCache();
      if (!isset($this->m_postvars['atknoclose']))
      {
        // 'save and close' was clicked
        $location = $this->m_node->feedbackUrl("update", ACTION_SUCCESS, $record, "");
      }
      else
      {
        // 'save' was clicked
        $location = session_url(dispatch_url($this->m_node->atknodetype(),"edit", array("atkselector"=>$this->m_node->primaryKey($record),"atktab"=>$this->m_node->getActiveTab())), SESSION_REPLACE);
      }
      $this->m_node->redirect($location);
    }
    

	/* Checks with each of the attributes of the node whose record is about to be deleted
	 * if they allow the deletion
	 * @return bool wether or not the attributes have allowed deletion
	 */
	function checkAttributes()
	{
		for ($counter=0; $counter<count($this->m_node->m_attribIndexList); $counter++)
		{
			// Check with every attribute
			$p_attrib = &$this->m_node->m_attribList[$this->m_node->m_attribIndexList[$counter]["name"]];
			$allowed= $p_attrib->deleteAllowed();

			// If allowed !=== true, then it returned an error message
			if ($allowed!==true)
			{
				$db = &$this->m_node->getDb();
				$db->rollback();
				$location = $this->m_node->feedbackUrl("delete",ACTION_FAILED,null,sprintf(atktext("attrib_delete_not_allowed"),atktext($this->m_node->m_attribIndexList[$counter]["name"],$this->m_node->m_module,$this->m_node->m_type),$allowed));
				$this->m_node->redirect($location);
				return;
			}
		}
		return true;
	}
}
?>
