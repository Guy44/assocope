<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
class calendrier extends assMetaNode {
	var $table = "organisme_calendrier";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function calendrier() {
		$this->atkMetaNode();
		$this->atkNode("calendrier", NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"nom",
				"id_organisme",
				"uri",
		"url",
		"nb_lieux",
		"nb_groupes",
		"nb_rencontres",
		"nb_elements",
				"date_refresh_google",
		"refresh_en_cours",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
				 "Lieux" => array (
				 "lieu"
				 )
				 ,
				 "Groupes" => array (
				 "groupe"
				 )

				 ,
				 "Rencontres" => array (
				 "rencontre"
				 )

				 ,
				 "Eléments" => array (
				 "element"
				 )


				 ), AF_NO_LABEL));

				 $this->add(new atgTextLibelleAttribute("nom", AF_SEARCHABLE),100);
				 $this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				 $this->add(new atkAttribute("uri", AF_HIDE_LIST),205);
				 $this->add(new atkUrlAttribute("url", AF_POPUP | AF_SEARCHABLE), 150);

				 $this->add(new atkDateTimeAttribute("date_refresh_google", "Y-m-d", "hh:mm:ss",  AF_DATE_STRING ),300);
				 				$this->add(new atkBoolAttribute("refresh_en_cours"),301);

				 $this->add(new atgNumberExpressionAttribute("nb_lieux", ' select count(id) from organisme_calendrier_lieu_rencontre
	 where id_calendrier =[table].id 
					', 0, 0),400);
				 $this->add(new atgNumberExpressionAttribute("nb_groupes", ' select count(id) from organisme_calendrier_groupe_travail
	 where id_calendrier =[table].id 
					', 0, 0),500);
				 $this->add(new atgNumberExpressionAttribute("nb_rencontres", ' select count(id) from organisme_calendrier_rencontre
	 where id_calendrier =[table].id 
					', 0, 0),600);	
				 $this->add(new atgNumberExpressionAttribute("nb_elements", ' select count(id) from organisme_calendrier_element
	 where id_calendrier =[table].id 
					', 0, 0),605);
				 $this->add(new atkOneToManyRelation("lieu", "organisme.calendrier_lieu_rencontre", "id_calendrier", AF_HIDE_LIST));
				 $this->add(new atkOneToManyRelation("groupe", "organisme.calendrier_groupe_travail", "id_calendrier", AF_HIDE_LIST));
				 $this->add(new atkOneToManyRelation("rencontre", "organisme.calendrier_rencontre", "id_calendrier", AF_HIDE_LIST));
					$this->add(new atkOneToManyRelation("element", "organisme.calendrier_element", "id_calendrier", AF_HIDE_LIST));

					include_once (atkconfig("atkroot") . "modules/include/association.inc");
					$this->m_securityMap["rafraichir_calendrier"] = "view";
					$this->m_securityMap["rafraichir_calendrier_avec_participants"] = "view";
					$this->setOrder("nom");
					$this->setIndex("nom");
	}
	function rowColor($record) {
		
		if ($record["refresh_en_cours"]==1)
		return $this->couleurrouge;
	}
	
	function date_refresh_google_display($record, $mode) {
		return $this->dateatktodb($record["date_refresh_google"]);
	}
	function url_display($record, $mode)
	{
		$url = $record["url"];
		$target = '';
		if (true === $this->m_newWindow) {
			$target = ' target="_new"';
		}
		return '<a href="' . $url . '"' . $target . '"><font color="ForestGreen"><b>Calendrier Google</b></font></a>';

	}
	function nb_lieux_display($record, $mode) {
		if (isset ($record["nb_lieux"])) {
			$ret= href(dispatch_url("organisme.calendrier_lieu_rencontre", "admin", array (
				'atkfilter' => "organisme_calendrier_lieu_rencontre.id_calendrier='" . $record['id'] . "'  "
				), "dispatch.php"), text($record["nb_lieux"]), SESSION_NESTED);
				if ($record["nb_lieux"]!=0)			return '<font color="Red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_groupes_display($record, $mode) {
		if (isset ($record["nb_groupes"])) {
			$ret= href(dispatch_url("organisme.calendrier_groupe_travail", "admin", array (
				'atkfilter' => "organisme_calendrier_groupe_travail.id_calendrier='" . $record['id'] . "'  "
				), "dispatch.php"), text($record["nb_groupes"]), SESSION_NESTED);
				if ($record["nb_groupes"]!=0)			return '<font color="Red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_rencontres_display($record, $mode) {
		if (isset ($record["nb_rencontres"])) {
			$ret= href(dispatch_url("organisme.calendrier_rencontre", "admin", array (
				'atkfilter' => "organisme_calendrier_rencontre.id_calendrier='" . $record['id'] . "'  "
				), "dispatch.php"), text($record["nb_rencontres"]), SESSION_NESTED);
				if ($record["nb_rencontres"]!=0)			return '<font color="Red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_elements_display($record, $mode) {
		if (isset ($record["nb_elements"])) {
			$ret= href(dispatch_url("organisme.calendrier_element", "admin", array (
				'atkfilter' => "organisme_calendrier_element.id_calendrier='" . $record['id'] . "'  "
				), "dispatch.php"), text($record["nb_elements"]), SESSION_NESTED);
				if ($record["nb_elements"]!=0)			return '<font color="Red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}


	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function descriptor_def() {
		return "([id_organisme.nom]) [nom] ";
	}

	function recordActions($rec, & $actions, & $mraactions) {
		//		parent::recordActions($rec, $actions, $mraactions);
		$mraactions['rafraichir_calendrier'] = "rafraichir_calendrier";
		$mraactions['rafraichir_calendrier_avec_participants'] = "rafraichir_calendrier_avec_participants";

	}
	function action_rafraichir_calendrier_avec_participants ()
	{
		$this->action_rafraichir(true);
	}
	function action_rafraichir_calendrier ($participants_o_n=false)
	{
		$this->action_rafraichir(false);
	}
	function action_rafraichir ($participants_o_n)
	{
		$code_google = $this->m_postvars["code_google"];
	if (strlen($code_google)<5)
		{ $this->setFeedback("rafraichir",ACTION_FAILED);
		$location = $this->feedbackUrl("rafraichir", ACTION_FAILED, "", "Mot de passe vide ou de longueur trop faible");
		$this->redirect($location);
		}
		
		$messagecalendrier='';
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_AuthSub');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Gdata_HttpClient');
		Zend_Loader::loadClass('Zend_Gdata_Calendar');
		$_authSubKeyFile = null; // Example value for secure use: 'mykey.pem'
		$_authSubKeyFilePassphrase = null;
		$service = Zend_Gdata_Calendar::AUTH_SERVICE_NAME;

		foreach ($select as $id_variable) {
			$nombreevents=0;
			$nombredelete=0;
			$id_calendrier = explode('=', $id_variable);
			$id_calendrier1 = $id_calendrier[1];
			$sql='SELECT oc.nom, identifiant_google, code_google, tz_offset_google, uri, date_refresh_google
			from organisme o, organisme_calendrier oc
		where oc.id='.$id_calendrier1.' and oc.id_organisme=o.id';
			$data=$db->getrows($sql);
			$user=$data[0]["identifiant_google"];
			$nomcalendrier=$data[0]["nom"];
			$daterefreshgoogle=$data[0]["date_refresh_google"];
			
//			$pass=$data[0]["code_google"];

			$pass=$code_google;
//			$tzOffset=$data[0]["tz_offset_google"];
			$tzOffset=substr($data[0]["tz_offset_google"],0,strlen($data[0]["tz_offset_google"])-2); 
				if (strlen($tzOffset)!=3) 
			{
				echo 'Time Zone organisme non correct';
				die();
			}
			$uri=$data[0]["uri"];
			$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);
			$sql='UPDATE organisme_calendrier
		set refresh_en_cours="1" where
		id='.$id_calendrier1.' ';
			$db->query($sql);
			
			if ($daterefreshgoogle!=null)
			{
			

			// supprimer les éléments
			$maxresults=20;
			$gdataCal = new Zend_Gdata_Calendar($client);
			$query = $gdataCal->newEventQuery();
			$query->setUser($uri);
			$query->setVisibility('private');
			$query->setProjection('full');
			$query->setOrderby('starttime');
			$query->setFutureevents(false);
			$query->setMaxResults($maxresults);
			$rdv=true	;
			
			while ($rdv==true)
			{$eventFeed = $gdataCal->getCalendarEventFeed($query);
			$nbevents=0;
			foreach ($eventFeed as $event) {
					
				$event->delete();
				$nombredelete+=1;
				$nbevents+=1;
			}
			if ($nbevents<$maxresults)
			{
				$rdv=false;
			}
			}
			
			$sql='DELETE FROM organisme_calendrier_element
		where id_calendrier='.$id_calendrier1.' ';
			$db->query($sql);
			$sql='UPDATE organisme_calendrier
		set date_refresh_google= null where
		id='.$id_calendrier1.' ';

			
			$db->query($sql);
			
			}
			
						$sql='select count(id) as nombre FROM organisme_calendrier_element
		where id_calendrier='.$id_calendrier1.' ';
			$data=$db->getrows($sql);
			$nombrederdv=$data[0]["nombre"];
			
			
			$sql="
			 ( SELECT id_rencontre as id from organisme_calendrier_rencontre WHERE id_calendrier=".$id_calendrier1.")
			  UNION 
			 ( SELECT id  as id FROM organisme_rencontre WHERE id_groupe_travail 
			    IN  
			   (SELECT id_groupe_travail FROM organisme_calendrier_groupe_travail WHERE id_calendrier=".$id_calendrier1.")
			   )
			   			  UNION 
			 ( SELECT id as id FROM organisme_rencontre WHERE id_lieu_rencontre 
			    IN  
			   (SELECT id_lieu_rencontre FROM organisme_calendrier_lieu_rencontre WHERE id_calendrier=".$id_calendrier1.")
			   )
			   
			   ";
		$debut=date("Y-m-d", mktime(0,0,0,date("m")-9,date("d"),date("Y")));
			$data=$db->getrows($sql);
							// Create a new entry using the calendar service's magic factory method
				$service = new Zend_Gdata_Calendar($client);
			for ($i = 0; $i < count($data); $i++) {
				$sql="SELECT
						ore.libelle,
						ore.id_organisme,
						o.nom,
						o.telephone,
						o.site_internet,
						ore.id_lieu_rencontre,
						ore.id_groupe_travail,
						ore.date_debut,
						ore.heure_debut,
						ore.date_fin, 
						ore.heure_fin,
						ore.commentaire
						FROM 
						organisme_rencontre ore, organisme o
						where ore.id=".$data[$i]["id"]." and ore.date_debut>'".$debut."' and ore.id_organisme=o.id 
						and ore.id not in (select id_rencontre from organisme_calendrier_element where id_calendrier=".$id_calendrier1.")
						";

				$rencontre=$db->getrows($sql);
				if (count($rencontre)==0)	{ continue;}

				
				
				
				$event= $service->newEventEntry();
				// Populate the event with the desired information
				// Note that each attribute is crated as an instance of a matching class
				//				   $value = atk_iconv(atktext("charset"),"UTF-8",$rencontre[0]["libelle"]);
				$adresse="";
				$lieu_latlon="";
				if ($rencontre[0]["id_lieu_rencontre"]!="")
				{

					$query = & $db->createQuery();
					$query->addTable("organisme_lieu_rencontre");
					$query->addJoin("lieu", "", "organisme_lieu_rencontre.id_lieu = lieu.id", false);
					$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
					$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
					$query->addField("organisme_lieu_rencontre.libelle as libelle");
					$query->addField("lieu.adresse1 as adresse1");
					$query->addField("lieu.longitude as longitude");
					$query->addField("lieu.latitude as latitude");
					$query->addField("type_cp_ville_pays.code_postal as code_postal");
					$query->addField("type_cp_ville_pays.ville as ville");
					$query->addField("type_cp_ville_pays.province_etat as province");
					$query->addField("type_pays.libelle_anglais as pays");
					$query->addCondition("organisme_lieu_rencontre.id=".$rencontre[0]["id_lieu_rencontre"]);
					$sql = $query->buildSelect();
					$stuff = $db->getrows($sql);
					if ($stuff[0]["latitude"]!="");
					{
//					$stuff[0]["latitude"]=substr($stuff[0]["latitude"],0, strlen($stuff[0]["latitude"])-6).'.'.substr($stuff[0]["latitude"],strlen($stuff[0]["latitude"])-6,6);
//					$stuff[0]["longitude"]=substr($stuff[0]["longitude"],0, strlen($stuff[0]["longitude"])-6).'.'.substr($stuff[0]["longitude"],strlen($stuff[0]["longitude"])-6,6);
					$lieu_latlon=$stuff[0]["latitude"].",".$stuff[0]["longitude"];

					
					}
					$adresse="<b>Lieu de la rencontre : </b>".$stuff[0]["libelle"]."<br />".$stuff[0]["adresse1"]." - ".$stuff[0]["code_postal"]." - ".$stuff[0]["ville"]." - ".$stuff[0]["province"]." - ".$stuff[0]["pays"];
				}
					
				if ($participants_o_n==true)	
				{
				$query = & $db->createQuery();
				$query->addTable("individu_rencontre");
				$query->addJoin("individu", "", "individu_rencontre.id_individu = individu.id", false);
				$query->addJoin("organisme", "", "individu_rencontre.id_organisme_participant = organisme.id", true);
				$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.telephone_fixe as telephone");
				$query->addField("organisme.nom as organisme_participant");
				$query->addField("type_rencontre_participation.libelle as participation");
				$query->addField("individu_rencontre.commentaire as commentaire");
				$query->addCondition("individu_rencontre.id_rencontre=".$data[$i]["id"]);
				$query->addOrderBy(" type_rencontre_participation.libelle, individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				$stuff = $db->getrows($sql);

				$datatbl = array ();

				for ($j = 0; $j< count($stuff); $j++) {
					$row = array ();
					$row[] = $j +1;


					$row[] = $stuff[$j]["nom"];
					$row[] = $stuff[$j]["prenom"];
					$row[] = $stuff[$j]["telephone"];
					$row[] = $stuff[$j]["organisme_participant"];
					$row[] = $stuff[$j]["commentaire"];
					$row[] = $stuff[$j]["participation"];
					$datatbl[] = $row;
				}
				$tbl = & atknew("atk.utils.atktablerenderer");
				$res = $tbl->render($datatbl, 0, "recordlist");
				}
				else
				{$res=""; }
				

					
					
				$event->title = $service->newTitle(atk_iconv(atktext("charset"),"UTF-8",$rencontre[0]["libelle"]));
				if ($lieu_latlon!="")
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$lieu_latlon)));}
				else
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$adresse)));}
				if ($rencontre[0]["site_internet"]=="")
				{$event->content =$service->newContent(atk_iconv(atktext("charset"),"UTF-8",'<b>Organisme : </b>'.$rencontre[0]["nom"].' '.$rencontre[0]["telephone"].'<br />'.$adresse.'<br />'.'<b>Participants : </b>'.'<br />'.$res));
					}
					else
					{
				$event->content =$service->newContent(atk_iconv(atktext("charset"),"UTF-8",'<b>Organisme : </b><a href="'.$rencontre[0]["site_internet"].'">'.$rencontre[0]["nom"].'</a> '.$rencontre[0]["telephone"].'<br />'.$adresse.'<br />'.'<b>Participants : </b>'.'<br />'.$res));
					}
				// Set the date using RFC 3339 format.
				$startDate = $rencontre[0]["date_debut"];
				$startTime = substr($rencontre[0]["heure_debut"], 0,5);
				$endDate = $rencontre[0]["date_fin"];
				$endTime = substr($rencontre[0]["heure_fin"],0,5);
				$when = $service->newWhen();
/*	//			$tzOffset='+00';
	echo "<br />startdate : ".$startDate;
		echo "<br />startTime : ".$startTime;
			echo "<br />endDate : ".$endDate;
				echo "<br />endTime : ".$endTime;
				die();
*/	


				$when->startTime = "{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				$when->endTime = "{$endDate}T{$endTime}:00.000{$tzOffset}:00";
				$event->when = array($when);
				// Upload the event to the calendar server
				// A copy of the event as it is recorded on the server is returned
				$caluri='http://www.google.com/calendar/feeds/'.$uri.'/private/full';
				/*
				 echo "{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				 die();

				 */
				$newEvent = $service->insertEvent($event, $caluri);

				$nombreevents+=1;

				$idrencontre=$data[$i]["id"];
				$sql="INSERT
						INTO
						organisme_calendrier_element
						( id_calendrier, id_google, id_rencontre,commentaire, id_creation, date_creation, id_modification, date_modification)
						VALUES
						( $id_calendrier1,
						'$idgoogle',
						'$idrencontre',				
						'',
						'$userid',
						UTC_TIMESTAMP(),
						'$userid',
						UTC_TIMESTAMP())
						";
				$db->query($sql);
				//				echo $newEvent;
				//				echo '<br />';


			}
			$sql="UPDATE organisme_calendrier
		SET id_modification='$userid', date_modification=UTC_TIMESTAMP(), date_refresh_google=UTC_TIMESTAMP() where id=$id_calendrier1
						";
			$db->query($sql);
					$sql='UPDATE organisme_calendrier
		set refresh_en_cours="0" where
		id='.$id_calendrier1.' ';
			$db->query($sql);
			$messagecalendrier.=' Calendrier : '.$nomcalendrier.' mis à jour. '.$nombreevents.' évènements ont été créés. '.$nombredelete.' évènements ont été supprimés. ';

		}
		$messagefin=" Mises à jour effectuées<br />".$messagecalendrier;
		//        echo $messagefin;
		//        die();
			
		$this->setFeedback("rafraichir_calendrier",ACTION_SUCCESS);
		$location = $this->feedbackUrl("rafraichir_calendrier", ACTION_SUCCESS, "", $messagefin);
		$this->redirect($location);
			

	}
	function getCustomMraHtml()
	{
		$list = 'Mot-de-passe : ';
		$list .=  '<input type="text" name="code_google" value=" " size="10" > ';
				return $list;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>