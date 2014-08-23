<?php
	atkimport("atk.assmetanode");

class attribut_i extends assMetaNode
{
	var $table="individu_attribut";

function meta(&$policy)
  {

	//$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
	//$policy->setOrder("libelle");
}
function attribut_i()
{
  	$this->atkMetaNode();
  	$this->atkNode("attribut_i", NF_ADDAFTERADD | NF_ADD_LINK|NF_TRACK_CHANGES);

	$this->add(new atkDateAttribute("date_debut","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING));
	$this->add(new atkDateAttribute("date_fin","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING)); 
	$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE)); 
	$this->add(new atkManyToOneRelation("id_attribut","table.type_attribut",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK)); 

	include_once(atkconfig("atkroot")."modules/include/association.inc");

$this->setSecurityAlias("individu.individu");

global $ATK_VARS,$g_user;
	
	  if ($ATK_VARS["atknodetype"]=="individu.attribut_i"&& in_array($ATK_VARS["atkaction"],array("admin","add","update","edit")))
    {
      if  ($this->getView() == "active") 
           {
     $this->addFilter("(date_fin IS NULL or date_fin='00-00-0000' )" );
     }
     
    }

	//$this->setIndex("libelle");
  }
function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
  
  	// GG deb

	function action_delete() {
			$user = getUser();
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$condition=$this->m_postvars["atkselector"];
		$data=$db->getrows("select date_fin from individu_attribut where $condition");
		if (empty($data[0]["date_fin"]))
		{$sql="update individu_attribut set 
		date_finn= UTC_TIMESTAMP() ,
		id_modification=  $userid,
		date_modification= UTC_TIMESTAMP() where $condition and date_fin is NULL";
		$db->query($sql);
		$db->commit();}
			else 
		{ $db->query("delete from individu_attribut where $condition");
		
		}
		$this->redirect();
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
$date_fin=$record["date_fin"];
if ($date_fin!="")
return $this->couleurarchive;
} 

function descriptor_def()
  {
    return "[id]";
  }

function action_admin($handler)
  {

    $view = $this->getView();
    if ($view=="active")
    {
      $this->addFilter("(date_fin IS NULL or date_fin='00-00-0000' )" );
    }
    return $handler->action_admin();
  }
  
  function adminFooter()
  {
    $retour=parent::adminfooter();
    $view = $this->getView();
    $legende='Légende des couleurs : ';
    $legende.='<font color="'. $this->couleurarchive.'"> <b> Archive </font>';
    if ($view=="active")
    {
      return atktext("onlyactiverecordsareshown")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type))."<br>"
	  .$legende.$retour;
		;
    }
    else
    {
      return $retour.atktext("youareinthearchive")." ".href('dispatch.php?atknodetype='.$this->atkNodeType().'&atkaction='.$this->m_action.
                  '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type))."<br>"
	  .$legende.$retour;
	;
    }
}
}
?>