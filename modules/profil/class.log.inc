<?php
atkimport("atk.assmetanode");

class log  extends assMetaNode
{
	var $table="atkeventlog";
	function meta(&$policy)
	{

		$policy-> addFlags("node","action","userid","utilisateur", "ptr",AF_SEARCHABLE);


	}
	function log()
	{
		$this->atkMetaNode();
		$this->atkNode("log", NF_NO_ADD|NF_MRA | NF_COMPACT );
		$this->add(new atkRowCounter("#"),NULL,1);
		$this->setExtendedSearchAction('smartsearch');
		$this->setSecurityAlias("profil.profil");
//		$this->add(new atkOneToManyRelation("utilisateurs","profil.utilisateur","id",AF_HIDE_LIST));
		$this->add(new atkRowCounter("#", AF_COMPACT), NULL, 1);
		$this->add(new atkDummyAttribute("descripteur_log",0,AF_COMPACT),NULL,10);
		$this->add(new atkManyToOneRelation("userid","profil.utilisateur",AF_SEARCHABLE),100);
		$this->add(new atkAttribute("stamp",AF_SEARCHABLE | AF_FORCE_LOAD),150);
		$this->add(new atkAttribute("origine",AF_SEARCHABLE),155);
		$this->add(new atkAttribute("action",AF_SEARCHABLE),200);
		$this->add(new atkNumberAttribute("query_count",AF_SEARCHABLE,12,0),201);
		$this->add(new atkNumberAttribute("dispatch_ms_elapsed_time",AF_SEARCHABLE,12,3),202);
		$this->add(new atkNumberAttribute("dispatch_ms_time",AF_SEARCHABLE,12,3),203);
		$this->add(new atkNumberAttribute("html_page_output_ms_time",AF_SEARCHABLE,12,3),204);	
		$this->add(new atkNumberAttribute("html_page_output_size",AF_SEARCHABLE,12,3),205);	
		$this->add(new atkAttribute("selector",AF_SEARCHABLE),210);
		$this->add(new atkAttribute("node",AF_SEARCHABLE),205);
		$this->add(new atkAttribute("parametres",AF_POPUP),400);
		$this->add(new atkAttribute("host",AF_HIDE_LIST),410);
		$this->add(new atkTextAttribute("remote_address",AF_SEARCHABLE),420);
		$this->add(new atkTextAttribute("user_agent",5,AF_HIDE_LIST),430);
		$this->add(new atkAttribute("accept_language",AF_HIDE_LIST),440);
		$this->add(new atkTextAttribute("referer",5,AF_HIDE_LIST),450);
		$this->add(new atkTextAttribute("query_string",5,AF_HIDE_LIST),460);
		$this->add(new atkParserAttribute("ptr",href("?atknodetype=[node]&atkaction=view&atkselector=[parametres]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_ADD), NULL, 10000);
//	$this->add(new atkDummyAttribute("ptr"), NULL, 10000);
		$this->add(new atkfckattribute("error_message", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '150px'
		)));
		$this->m_securityMap["admin_liste"] = "view";
		$this->addListener(atknew("atk.utils.atkeventlog"));
		$this->setOrder("stamp DESC");

	}
	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	
	function ptr_display($record, $mode) {
		$node=$record["node"];
		$pk=$record["parametres"];
		if (substr($record["action"],0,7)!="action_")
		{ 
		return href(dispatch_url($node, "view", array (
		"atkselector" => "" . $pk . ""
		), "dispatch.php"), text("..."), SESSION_NESTED);}
		else
		{return href(dispatch_url($node, "view", array (
		"atkselector" => "" . $pk . ""
		), "dispatch.php"), text("..."), SESSION_NESTED);
		}

	}
	
	function descripteur_log_display ($record, $mode)
	{
				return $this->decoupe_affichage_colonne($this->descripteur_log($record["id"]),100);
	}
	
	function query_string_display($record, $mode) {
		return $this->decoupe_affichage_colonne($record["query_string"], 100);
		

	}
	
/*function parametres_display($record, $mode) {
		return $this->decoupe_affichage_colonne($record["parametres"], 50);
		

	}
*/	

	function descriptor_def()
	{
		return "[node]";
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$filtre=$this->m_postvars["atkfilter"];
		$sql="SELECT
		atkeventlog.id as id,
	individu.id as id_individu,
  userid,
   stamp,
   origine,
   node,
   action,
   dispatch_ms_time,
   dispatch_ms_elapsed_time,
   html_page_output_ms_time,
   html_page_output_size,
   query_count,
   selector,
   parametres,
   host,
   remote_address,
   user_agent,
   accept_language,
   referer,
   query_string,
   error_message
		from
		atkeventlog 
		LEFT JOIN app_utilisateur ON atkeventlog.userid=app_utilisateur.id
		LEFT JOIN individu ON app_utilisateur.id_individu=individu.id
		where
		$filtre
		order by stamp desc	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
				$res2.='<thead>';
				$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Utilisateur</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Date-heure</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Node</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Action</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Ip</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Performance</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>selector</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Détails</center></b>';
	//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>parametres</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>host</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>user_agent</center></b>';
				$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>accept_language</center></b>';

	//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>query_string</center></b>';
	//			$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>error_message</center></b>';
		
				$res2.='</th></tr>';
				$res2.='</thead>';
				$res2.='<tbody>';
				for ($i=0;$i<count($data);$i++)
				{
					$idindividus.=$data[$i]["id_individu"].",";
					$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
					$res2.= "<tr><td>".($i+1);
					$res2.='</th><th>'.$this->descripteur_individu_sans_lien($data[$i]["id_individu"]).'</center></b>';
					$res2.='</td><td>'.$data[$i]["stamp"];
					$res2.='</td><td>'.$data[$i]["node"];
					$res2.='</td><td>'.$data[$i]["action"];
					$res2.='</td><td>'.$this->ip_geolocalisation($data[$i]["remote_address"]);
					$res2.='</td><td>Dispatch : '.$data[$i]["dispatch_ms_time"].' s . Elapsed : '.$data[$i]["dispatch_ms_elapsed_time"].' s'
					.'<br/>Html output : '. $data[$i]["html_page_output_ms_time"].' s . Taille : '.$data[$i]["html_page_output_size"].' o.'
					.'<br/>Requêtes Sql : '.$data[$i]["query_count"];
					$res2.='</td><td>'.$data[$i]["selector"];
					$res2.='</td><td>'.$this->get_textes_logs($data[$i]["id"]);
	//				$res2.='</td><td>'.$data[$i]["parametres"];
					$res2.='</td><td>'.$data[$i]["host"];
					$res2.='</td><td>'.$data[$i]["user_agent"];
					$res2.='</td><td>'.$data[$i]["accept_language"];
	
	//				$res2.='</td><td>'.$data[$i]["query_string"];
	//				$res2.='</td><td>'.$data[$i]["error_message"];

			$res2.='</td></tr>';
	}
	
	$res2.='</tbody>';
	$res2.='</table>'.$this->getUserStamp('n','o');
	$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
	$criteres=$this->m_postvars["atkfiltre"];
	$titre="<h2><b>"."Logs"." </b>- "."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
	$res2=$titre.$res2;
	$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
	$this->page_output($res2);
	
	}

}

?>