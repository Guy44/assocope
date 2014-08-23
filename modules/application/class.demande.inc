<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class demande extends assMetaNode {
	var $table = "app_pb_report";

	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function demande() {
		$this->atkMetaNode();
		$this->atkNode("demande",  NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_OBLIGATORY));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"module",
				"node",
				"id_type_demande",
				"id_etat",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
			),
			"Description" => array (
				"description"
			),
			"Réponse" => array (
				"reponse"
			)
		), AF_NO_LABEL));
		$this->add(new atkfckattribute("description", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '1000px',
			'Height' => '600px'
		)));
		$this->add(new atkfckattribute("reponse", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '1000px',
			'Height' => '600px'
		)));
		$this->setSecurityAlias("application.aide");
		$this->add(new atkManyToOneRelation("id_etat", "table.type_etat_todo", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		$this->add(new atkManyToOneRelation("id_type_demande", "table.type_demande", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
		$this->setOrder("date_modification");
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['delete'] = "delete";
	}
	function initial_values() {
		if (isset ($this->m_postvars["module"]) and isset ($this->m_postvars["node"])) {
			return array (
				"module" => $this->m_postvars["module"],
				"node" => $this->m_postvars["node"],
				"id_type_demande" => '1',
				"id_etat" => '2'			);
		}
	}
	
function action_admin($handler)
  {

    $view = $this->getView();
    if ($view=="active")
    {
      $this->addFilter("( id_etat !='1' and id_etat !='3') ");
    }
    return $handler->action_admin();
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
    function adminFooter()
  {
      $retour=parent::adminfooter();
      $view = $this->getView();
    $legende='Légende des couleurs : ';
    $legende.='<font color="'. $this->couleurarchive.'"> <b> Archive ';
$legende.='<font color="'. $this->couleuranomalie.'"> <b> Anomalie ';
$legende.='<font color="'. $this->couleurrequete.'"> <b> Requête ';
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
  function rowColor($record) 
{

if ($record['id_etat']['id']=='1' or $record['id_etat']['id']=='3')
return $this->couleurarchive;
if ($record['id_type_demande']['id']=='1')
return $this->couleuranomalie;
if ($record['id_type_demande']['id']=='2')
return $this->couleurrequete;

}   
	function descriptor_def() {
		return "[libelle]";
	}
	function postAdd($record) {

		$config_maildemande = atkconfig("maildemande");
		$from = atkconfig("mail_sender");
		global $g_sessionManager;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$mailer = atknew('atk.utils.atkmailer');
		$mailer->isHtml(true);
		$mailer->AddAddress($config_maildemande);
		$mailer->FromName = "Webmestre";
		$mailer->From = $from;
		$mailer->Subject = "[".$_SERVER["SERVER_NAME"]."] .".atkconfig("nomapplication") . ". Anomalie/suggestion de " . $g_nomutilisateur . ".";
		$body = "Titre : " . $record[libelle] . "<br>";
		$body .= "Module : ".$record["module"].".Node : ".$record["node"].".Type demande : ".$record["id_type_demande"]["libelle"]."<br>";
		$body .= "Description : <br>";
		$body .= $record[description] . "<br>";
		$body .= "Réponse : <br>";
		$body .= $record[reponse] . "<br>";
		$mailer->Body = nl2br($body);
		$mailer->Send();
	}
}
?>