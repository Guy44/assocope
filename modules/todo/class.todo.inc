<?php
	useattrib("development.atgtextlibelleattribute");
class todo  extends assMetaNode
{
	var $table="todo";
function meta(&$policy)
  {
	$policy-> addFlags("libelle","id_type_etat_todo",AF_SEARCHABLE);
	$policy-> addFlags("description","commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
 }
function todo()
{
  	$this->atkMetaNode();
  	$this->atkNode("todo",NF_ADD_LINK|NF_TRACK_CHANGES); 
	$this->setSecurityAlias("table.activite");
			$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"id_individu_a_faire",
				"priorite",
				"blocnotes_o_n",
				"date_echeance",
				"id_type_etat_todo",
				"description",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			)
		), AF_NO_LABEL));
	$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY));
	$this->add(new atkManyToOneRelation("id_individu_a_faire","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOCOMPLETE)); 
   	$this->add(new atkListAttribute("priorite", array("A", "B", "C"), array(1,2,3),AF_SEARCHABLE|AF_OBLIGATORY));
		$this->add(new atkBoolAttribute("blocnotes_o_n"));
		 	$this->add(new atkManyToOneRelation("id_type_etat_todo","table.type_etat_todo",AF_SEARCHABLE|AF_RELATION_AUTOLINK|AF_OBLIGATORY)); 
 		$this->add(new atkfckattribute("description", "", "", array (
			'ToolbarSet' => 'Default',
			'Width' => '750px',
			'Height' => '600px'
		)));
/*
		$this->add(new atkfckattribute("description", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Basic',
			'Width' => '100%',
			'Height' => '300px'
		)));
		*/
$this->add(new atkDateAttribute("date_echeance","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING|AF_OBLIGATORY));
		$this->setOrder(" priorite ASC, date_echeance ASC ");
	include_once(atkconfig("atkroot")."modules/include/association.inc");		  
  global $ATK_VARS,$g_user;
	  if ($ATK_VARS["atknodetype"]=="node.node"&& in_array($ATK_VARS["atkaction"],array("admin","add","update","edit")))
    {
      if  ($this->getView() == "active") 
           {
     $this->addFilter("( id_type_etat_todo !='1' and id_type_etat_todo !='3' )" );
     }
    }
	$this->setIndex("libelle");
  }
  
  	function preAdd(& $record) {
		$id_individu = $record['id_individu_a_faire']['id'];
		$defaut = $record['blocnotes_o_n'];
		if ($defaut=='1')
		{
		$db = & atkGetDb();
		$db->query("UPDATE todo set blocnotes_o_n='0'   where id_individu_a_faire='" . $id_individu . "' ");
		}
		parent :: preAdd($record);
	}
	  	function preUpdate(& $record) {
		$id_individu = $record['id_individu_a_faire']['id'];
		$defaut = $record['blocnotes_o_n'];
		if ($defaut=='1')
		{
		$db = & atkGetDb();
		$db->query("UPDATE todo set blocnotes_o_n='0'   where id_individu_a_faire='" . $id_individu . "' ");
		}
		parent :: preUpdate($record);
	}
	
	 function getView()
  {
    global $g_sessionManager;
    $view = $g_sessionManager->stackVar("view");
    if ($view=="")
    {
      $view = "active";
    }
    return $view;
  }
  
  
   function rowColor($record) 
{
//print_r($record);
//die();
if ($record['id_type_etat_todo']['id']=='1' or $record['id_type_etat_todo']['id']=='3')
return $this->couleurarchive;
if ($record['priorite']=='1')
return $this->couleurpriorite1;
if ($record['priorite']=='2')
return $this->couleurpriorite2;
if ($record['priorite']=='3')
return $this->couleurpriorite3;

} 

function descriptor_def()
  {
    return "[libelle] ";
  }

function action_admin($handler)
  {

    $view = $this->getView();
    if ($view=="active")
    {
      $this->addFilter("( id_type_etat_todo !='1' and id_type_etat_todo !='3') ");
    }
    return $handler->action_admin();
  }
  
 
  function adminFooter()
  {
      $retour=parent::adminfooter();
      $view = $this->getView();
    $legende='Légende des couleurs : ';
    $legende.='<font color="'. $this->couleurarchive.'"> <b> Archive ';
$legende.='<font color="'. $this->couleurpriorite1.'"> <b> Priorité A ';
$legende.='<font color="'. $this->couleurpriorite2.'"> <b> Priorité B';
$legende.='<font color="'. $this->couleurpriorite3.'"> <b> Priorité C';
    if ($view=="active")
    {
      return atktext("onlyactiverecordsareshown")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type))."<br>"
		  .$legende.$retour;
    }
    else
    {
      return atktext("youareinthearchive")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type))."<br>"
		  .$legende.$retour;
    }

}
    
}
?>