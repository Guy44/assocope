<?php
useattrib("development.atgtextnomattribute");
useattrib("development.atgFileManyToOneRelation");

class individu extends assMetaNode {

var $table = "individu";

	function meta(& $policy) {
		$policy->addFlags("nom", "prenom", "site_internet", "telephone_fixe", "telephone_mobile", "courriel", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("taille",
				"poids",
				"pointure",
				"tour_de_cou",
				"tour_de_poitrine",
				"tour_de_taille",
				"tour_de_bassin","entree_college",
				"sortie_college",
				"date_mesure","commentaire", "contact_alternatif", "sexe","annee_naissance", "compte_bancaire", "numero_ss", "commentaire_portrait", "Fusion_OpenOffice", AF_HIDE_LIST);
	}
	function individu() {
		$this->atkMetaNode();
//		$this->atkNode("individu",  NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA | NF_COMPACT_NULL);
			$this->atkNode("individu",  NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
		"descripteur_individu",
//		"descripteur_qr_individu",
				"id_titre",
				"nom",
				"prenom",
				"sexe",
				"date_naissance",
				"annee_naissance",
		"lieu_naissance",
					
		"nationalite",
		"profession",
		//				"courriel",
		//		"courriel_go",
		"courriel_grp",
		"pas_de_courriel_o_n",
		"calendrier_grp",
		//				"calendrier",
		//		"calendrier_go",
		"site_internet_grp",
		//				"site_internet",
		//		"site_internet_go",

				"id_document_signature",
				"telephone_fixe",
				"telephone_mobile",
				"contact_alternatif",
				"date_deces",
				"numero_ss",
				"compte_bancaire",
					"passeport_nom_prenom",
		"passeport_numero", "passeport_date_expiration",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
							"Descripteurs" => array (
		"descripteur_individu",
//		"descripteur_qr_individu",
				"descripteur_module_estampillage"
				
			),
			"Compléments" => array (
				"Pane2"
				)
					
					
				), AF_NO_LABEL));
				$this->add(new atkTabbedPane("Pane2", array (
		"Mensurations" => array (
				"taille",
				"poids",
				"pointure",
				"tour_de_cou",
				"tour_de_poitrine",
				"tour_de_taille",
				"tour_de_bassin",
				"date_mesure"), 

					"Etp" => array (
				"etp_poids_kg",
				"etp_pulses_per_minute",
				"etp_systole_mm_hg"
				),
									"Sport" => array (
				"golf_licence",
				"golf_index",
				"golf_url_federation",
				"lien"
				),
			"Etudes" => array (
				"entree_college",
				"sortie_college"
				),
			"Portrait" => array (
				"id_document_portrait",
				"commentaire_portrait"
				),
			"Signature_courriel" => array (
				"signature_courriel"
				),
				"Google" => array (
				"identifiant_google",
				"code_google",
				"tz_offset_google",
				"calendrier_rencontres_nom",
				"calendrier_rencontres_url",
				"calendrier_rencontres_uri",
				"calendrier_rencontres_refresh",
				"google_calendar_entries",
				"calendrier_contacts_nom",
				"calendrier_contacts_url",
				"calendrier_contacts_uri",
				"calendrier_contacts_refresh"
				)

				), AF_NO_LABEL));
			$this->add(new atkDummyAttribute("descripteur_individu",0,AF_HIDE_ADD | AF_COMPACT),3);
			global $g_sessionManager;
			$g_afficher_portrait_o_n = $g_sessionManager->getValue("afficher_portrait_o_n", "globals");
			
			($g_afficher_portrait_o_n=='1') ?  $this->add(new atkDummyAttribute("portrait",0,AF_HIDE_EDIT | AF_HIDE_ADD ),4) : null;
//						$this->add(new atkDummyAttribute("descripteur_qr_individu",0,AF_HIDE_EDIT ),4);
				$this->add(new atgTextNomAttribute("nom", AF_SEARCHABLE | AF_OBLIGATORY ),6);
				
	
				$this->add(new atkfckattribute("signature_courriel", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '600px',
			'Height' => '300px'
			)));
			$this->add(new atkAttribute("identifiant_google", AF_HIDE_LIST,50), 1005);
			$this->add(new atkPasswordAttribute("code_google", false,  AF_PASSWORD_NO_ENCODE | AF_HIDE_LIST), 1010);
			$this->add(new atkTimeZoneAttribute("tz_offset_google",  AF_HIDE_LIST),1020);
			$this->add(new atkAttribute("calendrier_rencontres_nom", AF_HIDE_LIST), 1025);
			$this->add(new atkAttribute("calendrier_rencontres_url", AF_HIDE_LIST), 1030);
			$this->add(new atkAttribute("calendrier_rencontres_uri",  AF_HIDE_LIST),1035);
			$this->add(new atkDateAttribute("calendrier_rencontres_refresh", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_DATE_STRING| AF_HIDE_LIST ),1036);
			$this->add(new atkAttribute("google_calendar_entries",  AF_HIDE_LIST),1037);
			$this->add(new atkAttribute("calendrier_contacts_nom", AF_HIDE_LIST), 1040);
			$this->add(new atkAttribute("calendrier_contacts_url", AF_HIDE_LIST), 1045);
			$this->add(new atkAttribute("calendrier_contacts_uri",  AF_HIDE_LIST),1050);
			$this->add(new atkDateAttribute("calendrier_contacts_refresh", "Y-m-d hh:mm", "Y-m-d hh:mm", 0, 0, AF_DATE_STRING | AF_HIDE_LIST),1055);

			$this->add(new atgTextNomAttribute("prenom", AF_SEARCHABLE), 6);
			$this->addUniqueFieldset(array("nom","prenom"));
			$this->add(new atkManyToOneRelation("id_titre", "table.titre", AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_SEARCHABLE));
			$this->add(new atkEmailAttribute("courriel", false, AF_SEARCHABLE));
			$this->add(new atkUrlAttribute("calendrier", AF_POPUP));
			$this->add(new atkBoolAttribute("pas_de_courriel_o_n"));
			$this->add(new atkUrlAttribute("site_internet", AF_POPUP));
			$this->add(new atkRadioAttribute("sexe", array (
			"Homme",
			"Femme"
			), array (
			"M",
			"F"
			), AF_OBLIGATORY | AF_HIDE_LIST));
			$this->add(new atkAttribute("passeport_numero",AF_HIDE_LIST));
			$this->add(new atkAttribute("passeport_nom_prenom",AF_HIDE_LIST,100));
			$this->add(new atkAttribute("compte_bancaire",AF_HIDE_LIST,50));
			$this->add(new atkDateAttribute("passeport_date_expiration", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
			
			$this->add(new atkDateAttribute("date_naissance", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
			$this->add(new atkAttribute("lieu_naissance", AF_HIDE_LIST,100 ));
			$this->add(new atkAttribute("nationalite",AF_HIDE_LIST));
			$this->add(new atkAttribute("profession",AF_HIDE_LIST));
			$this->add(new atkDateAttribute("date_deces", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING));
			$this->add(new atkDateAttribute("date_mesure", "Y-m-d", "Y-m-d", 0, 0,AF_HIDE_LIST| AF_DATE_STRING));
			$this->add(new atkAttribute("taille",AF_HIDE_LIST));
			$this->add(new atkAttribute("poids",AF_HIDE_LIST));
			$this->add(new atkAttribute("pointure",AF_HIDE_LIST));
			$this->add(new atkAttribute("tour_de_cou",AF_HIDE_LIST));
			$this->add(new atkAttribute("tour_de_poitrine",AF_HIDE_LIST));
			$this->add(new atkAttribute("tour_de_taille",AF_HIDE_LIST));
			$this->add(new atkAttribute("tour_de_bassin",AF_HIDE_LIST));
			$this->add(new atkAttribute("etp_poids_kg",AF_HIDE_LIST));
			$this->add(new atkAttribute("etp_pulses_per_minute",AF_HIDE_LIST));
			$this->add(new atkAttribute("etp_systole_mm_hg",AF_HIDE_LIST));
			global $g_sessionManager;
			$id_individu_utilisateur = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
			$this->add(new atkParserAttribute("courriel_go",
			atkHref("?atknodetype=individu.contact_i&atkaction=add&atkfilter=individu_contact.id_individu=[id]&idcontactant=$id_individu_utilisateur&atgemail=[courriel]&"
			, atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->add(new atkParserAttribute("calendrier_go",atkHref("[calendrier]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);
			$this->add(new atkParserAttribute("site_internet_go",atkHref("[site_internet]", atktext("..."), SESSION_NESTED), AF_NO_LABEL|AF_HIDE_LIST), NULL);

			$this->addFieldSet("courriel_grp"," [courriel.field] [courriel_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("calendrier_grp"," [calendrier.field] [calendrier_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );
			$this->addFieldSet("site_internet_grp"," [site_internet.field] [site_internet_go.field] ",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL );


			//
			$this->add(new atkAttribute("golf_licence", AF_SEARCHABLE | AF_HIDE_LIST), null, 110);
			$this->add(new atkNumberAttribute("golf_index", AF_SEARCHABLE | AF_HIDE_LIST, 5, 2), null, 120);
			$this->add(new atkUrlAttribute("golf_url_federation", AF_POPUP | AF_HIDE_LIST), null, 130);
			$this->add(new atkParserAttribute("lien", "<a href=\"[golf_url_federation]\" target=\"_blank\">Consulter</a>", AF_NO_LABEL | AF_HIDE_LIST), null, 130);
			$this->m_securityMap["document"] = "view";
			$this->m_securityMap["autocomplete"] = "view";
			$this->m_securityMap["enveloppe"] = "view";
			$this->m_securityMap["normalisation"] = "view";
			$this->m_securityMap["listeecran"] = "export";
			$this->m_securityMap["fiche"] = "view";
			$this->m_securityMap["liens"] = "view";
			$this->m_securityMap["vcard"] = "view";
			$this->m_securityMap["google"] = "view";
			$this->m_securityMap["googlemap"] = "view";
			$this->m_securityMap["listeecran"] = "view";
			//			$this->m_securityMap["rapport_html"] = "view";
			$this->m_securityMap["inscrire_du_presse_papier"] = "view";
			$this->m_securityMap["rafraichir_calendrier_rencontres"] = "view";
			$this->add(new atgFileManyToOneRelation("id_document_portrait", "organisme.document", AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			$this->add(new atgFileManyToOneRelation("id_document_signature", "individu.document_i", AF_RELATION_AUTOLINK | AF_HIDE_LIST | AF_RELATION_AUTOCOMPLETE));
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
						$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,5);
			$this->setOrder("nom,prenom");
			$this->setIndex("nom");
			$this->m_dropdown_width="100";
			// GG deb
			global $ATK_VARS, $g_user;
			if ($ATK_VARS["atknodetype"] == "individu.individu" && in_array($ATK_VARS["atkaction"], array (
				"admin",
				"add",
				"update",
				"edit"
				))) {
					if ($this->getView() == "active") {
						$this->addFilter("individu.date_deces IS NULL");
					}
				}
				// GG fin
	}
	function portrait_display($record, $mode)
	{
		$db = & atkGetDb();
	
	$sql="select id_document_portrait from individu where id=".$record["id"]." ";
		$data=$db->getrows($sql);
		$id_portrait=$data[0]["id_document_portrait"];
		if (!empty($id_portrait))
			{
		$sql="select file_content,file_name, file_size from organisme_document where id=$id_portrait";
		$data=$db->getrows($sql);
		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		$filename=$data[0]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[0]["file_content"]="";
		$retour='<center><a href="'.$url. '" target="_blank" ><img src="'.$url.'" height="100px" alt="Portrait" title="Portrait" /></a></center>' ;
	return $retour;
			}
	}
function descripteur_individu_display($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"n","o");
	}
function descripteur_individu_edit($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"n","o");
	}
/*function descripteur_qr_individu_display($record, $mode)
	{
		$id_individu=trim($record["id"]);

		return $this->descripteur_individu($id_individu,"o");
	}
	*/
	
	function telephone_fixe_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone_fixe"] . ';">' . $record["telephone_fixe"] . '</a>';
	}
	function telephone_mobile_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone_mobile"] . ';">' . $record["telephone_mobile"] . '</a>';
	}
	function action_rafraichir_calendrier_rencontres ()
	{
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

			$nombredelete=0;
			$id_individu = explode('=', $id_variable);
			$id_individu1 = $id_individu[1];
			$sql='SELECT calendrier_rencontres_nom, identifiant_google, code_google, tz_offset_google,
			 google_calendar_entries, calendrier_rencontres_uri
			, calendrier_rencontres_refresh from individu
		where id='.$id_individu1.'  ';
			$data=$db->getrows($sql);
			$user=$data[0]["identifiant_google"];
			$nomcalendrier=$data[0]["calendrier_rencontres_nom"];
			$nombrerdv=$data[0]["google_calendar_entries"];
			$pass=$data[0]["code_google"];
			//			$tzOffset=$data[0]["tz_offset_google"];
			$tzOffset=substr($data[0]["tz_offset_google"],0,strlen($data[0]["tz_offset_google"])-2);
			if (strlen($tzOffset)!=3)
			{
				echo 'Time Zone Individu non correct';
				die();
			}
			$uri=$data[0]["calendrier_rencontres_uri"];
			$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);

			if ($data[0]["calendrier_rencontres_refresh"]!=null)
			// supprimer les éléments

			{		$sql="UPDATE individu
		SET id_modification='$userid', date_modification=UTC_TIMESTAMP(),calendrier_rencontres_refresh=null ,
		  google_calendar_entries='0' where id=$id_individu1
						";


			$db->query($sql);
			}
			$sql='SELECT
			 google_calendar_entries from individu
		where id='.$id_individu1.'  ';
			$data=$db->getrows($sql);
			if ($data[0]["google_calendar_entries"]==0)
			{
				$maxresults=20;
				$gdataCal = new Zend_Gdata_Calendar($client);
				$query = $gdataCal->newEventQuery();
				$query->setUser($uri);
				$query->setVisibility('private');
				$query->setProjection('full');
				$query->setOrderby('starttime');
				$query->setFutureevents(false);
				$query->setMaxResults($maxresults);
				$eventFeed = $gdataCal->getCalendarEventFeed($query);
				$nbevents=0;
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
			}
			$debut=date("Y-m-d", mktime(0,0,0,date("m")-1,date("d"),date("Y")));

			$sql="
			  SELECT id_rencontre from individu_rencontre ir , organisme_rencontre ore WHERE ir.id_individu=".$id_individu1." 
			    and ir.id_rencontre=ore.id and ore.date_debut>='".$debut."'  ORDER by ore.date_debut ";
			$data=$db->getrows($sql);
			$sql='SELECT  google_calendar_entries
		from individu
		where id='.$id_individu1.'  ';
			$datanbr=$db->getrows($sql);
			$nbrrdv=$datanbr[0]["google_calendar_entries"];
			$nombreevents=$nbrrdv;
			for ($i =$nbrrdv ; $i < count($data); $i++) {
				$sql="SELECT
						ore.libelle,
						ore.id_organisme,
						o.nom,
						o.telephone,
						ore.id_lieu_rencontre,
						ore.id_groupe_travail,
						ore.date_debut,
						ore.heure_debut,
						ore.date_fin, 
						ore.heure_fin,
						ore.commentaire
						FROM 
						organisme_rencontre ore, organisme o
						where ore.id=".$data[$i]["id_rencontre"]." and ore.id_organisme=o.id
						";	
				$rencontre=$db->getrows($sql);
				// Create a new entry using the calendar service's magic factory method
				$service = new Zend_Gdata_Calendar($client);
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
				$query->addCondition("individu_rencontre.id_rencontre=".$data[$i]["id_rencontre"]);
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


					
					
				$event->title = $service->newTitle(atk_iconv(atktext("charset"),"UTF-8",$rencontre[0]["libelle"]));
				if ($lieu_latlon!="")
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$lieu_latlon)));}
				else
				{$event->where = array($service->newWhere(atk_iconv(atktext("charset"),"UTF-8",$adresse)));}

				$event->content =$service->newContent(atk_iconv(atktext("charset"),"UTF-8",'<b>Organisme : </b>'.$rencontre[0]["nom"].' '.$rencontre[0]["telephone"].'<br />'.$adresse.'<br />'.'<b>Participants : </b>'.'<br />'.$res));
				// Set the date using RFC 3339 format.
				$startDate = $rencontre[0]["date_debut"];
				$startTime = substr($rencontre[0]["heure_debut"], 0,5);
				$endDate = $rencontre[0]["date_fin"];
				$endTime = substr($rencontre[0]["heure_fin"],0,5);
				$when = $service->newWhen();
				$when->startTime = "{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				$when->endTime = "{$endDate}T{$endTime}:00.000{$tzOffset}:00";
				$event->when = array($when);
				// Upload the event to the calendar server
				// A copy of the event as it is recorded on the server is returned
				$caluri='http://www.google.com/calendar/feeds/'.$uri.'/private/full';

				//							 echo "<br />{$startDate}T{$startTime}:00.000{$tzOffset}:00";
				//						 die();

					
				$newEvent = $service->insertEvent($event, $caluri);
				$nombreevents+=1;
				$sql="UPDATE individu
		SET id_modification='$userid', date_modification=UTC_TIMESTAMP(), google_calendar_entries='$nombreevents' where id=$id_individu1
						";
				$db->query($sql);
					
			}
			$sql="UPDATE individu
		SET id_modification='$userid', date_modification=UTC_TIMESTAMP(), calendrier_rencontres_refresh=UTC_TIMESTAMP(), google_calendar_entries=0 where id=$id_individu1
						";
			$db->query($sql);
			$messagecalendrier.=' Calendrier : '.$nomcalendrier.' mis à jour. '.$nombreevents.' évènements ont été créés. '.$nombredelete.' évènements ont été supprimés. ';

		}
		$messagefin=" Mises à jour effectuées<br />".$messagecalendrier;
		//        echo $messagefin;
		//     die();
			
		$this->setFeedback("rafraichir_calendrier_rencontres",ACTION_SUCCESS);
		$location = $this->feedbackUrl("rafraichir_calendrier_rencontres", ACTION_SUCCESS, "", $messagefin);
		$this->redirect($location);
			

	}

	function dispatch($postvars, $fullpage = true) {
		/*
		 *
		 if ($postvars['atkaction'] == 'rapport_html') {
			echo 'rapport';
			die();
			}
			*/
		if ($postvars['atkaction'] != 'copier_individus_dans_presse_papier' && $postvars['atkaction'] != 'rafraichir_calendrier_rencontres'  )
		{
			if ($postvars['atkaction'] != 'add' && $postvars['atkaction'] != 'delete' && $postvars['atkaction'] != 'admin') {
				$atkselect = $postvars["atkselector"];
				if (($atkselect != "") && isset ($atkselect)) {
					$individuid = sscanf($atkselect, "individu.id='%d'");
					$individuId = $individuid[0];
					$this->RecentUseProcess('individu', $individuId);
				} else {
					$individuId = 0;
				}
			} else {

				$this->RecentUseRefresh('individu');
			}
		}
		return parent :: dispatch($postvars, $fullpage);
	}

	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idindividus = substr($chaineid, 0, strlen($chaineid) - 1);
		$idindividus = str_replace("'", "", $idindividus);
		$idorganisme = "";
		return true;
	}
	function nom_display($record, $mode) {
		// Do not return a html link in plain or csv mode or select screen
		//				$this->p($this->m_filters);
		if (($mode == "plain") || ($mode == "csv") || (isset ($this->m_postvars["atkaction"]) && $this->m_postvars["atkaction"] == "select"))
		return $record["nom"];
		// Make all project links clickable
		$defaultaction = $this->allowed("edit") ? "edit" : "view";
		return href(dispatch_url("individu.individu", $defaultaction, array (
			"atkselector" => "individu.id='{$record["id"]}'"
		), "dispatch.php"), $record["nom"], SESSION_NESTED);
	}
	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);
		$actions['copier_individus_dans_presse_papier'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=copier_individus_dans_presse_papier&atkselector=[pk]", SESSION_NESTED);

		$mraactions['copier_individus_dans_presse_papier'] = "copier_individus_dans_presse_papier";
		$mraactions['rafraichir_calendrier_rencontres'] = "rafraichir_calendrier_rencontres";
		//		$mraactions['rapport_html'] = "rapport_html";
		//		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
	}
	function courriel_display($record, $mode = "") {
		if ($mode == "csv")
		return parent :: display($record, $mode);
		if ($record["courriel"] != "") {
			return href(dispatch_url("individu.contact_i", "add", array (
				"atgemail" => $record["courriel"],
				"atgtable" => $this->table,
				"atgcle" => 'id',
				"atgvaleur" => $record["id"]
			)), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
		}
	}
	function calendrier_display($record, $mode = "") {
		if (!empty($record["calendrier"]))		return '<a href="'.$record["calendrier"].'">Calendrier</a>';
	}
	function site_internet_display($record, $mode = "") {
		if (!empty($record["site_internet"]))	return '<a href="'.$record["site_internet"].'">Site/Blog</a>';
	}
	// GG deb
	function getView() {
		global $g_sessionManager;
		$view = $g_sessionManager->stackVar("view");
		if ($view == "") {
			$view = "active";
		}
		return $view;
	}

	function action_listeecran() {
		switch ($this->m_postvars["atkcode"]) {
			case 1 :
				$db = & atkGetDb();
				$query = & $db->createQuery();
				$query->addTable("individu");
				$query->addJoin("type_titre", "", "individu.id_titre = type_titre.id", false);
				$query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
				$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
				$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
				$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
				$query->addField("type_titre.titre_long as titre");
				$query->addField("individu.nom as nom");
				$query->addField("individu.prenom as prenom");
				$query->addField("individu.courriel as courriel");
				$query->addField("individu.telephone_fixe as telephone_fixe");
				$query->addField("individu.telephone_mobile as telephone_mobile");
				$query->addField("lieu.adresse1 as adresse1");
				$query->addField("lieu.adresse2 as adresse2");
				$query->addField("type_cp_ville_pays.code_postal as code_postal");
				$query->addField("type_cp_ville_pays.province_etat as province");
				$query->addField("type_cp_ville_pays.ville as ville");
				$query->addField("type_pays.libelle_anglais as pays");
				$query->addCondition("individu.date_deces is null");
				$query->addOrderBy("individu.nom, individu.prenom");
				$sql = $query->buildSelect();
				//		print_r ($sql);
				//		die();
				$stuff = $db->getrows($sql);
				$fdw = fopen("contacts", "w");
				$row = '"Titre","Prénom","Deuxième prénom","Nom","Suffixe","Société ","Service ","Titre","Rue (bureau)","Rue (bureau) 2","Rue (bureau) 3","Ville (bureau)","Dép/Région (bureau)","Code postal (bureau)","Pays (bureau)","Rue (domicile)","Rue (domicile) 2","Rue (domicile) 3","Ville (domicile)","Dép/Région (domicile)","Code postal (domicile)","Pays (domicile)","Rue (autre)","Rue (autre) 2","Rue (autre) 3","Ville (autre)","Dép/Région (autre)","Code postal (autre)","Pays (autre)","Téléphone de l\'assistant(e)","Télécopie (bureau)","Téléphone (bureau)","Téléphone 2 (bureau)","Rappel","Téléphone (voiture)","Téléphone société","Télécopie (domicile)","Téléphone (domicile)","Téléphone 2 (domicile)","RNIS","Tél. mobile","Télécopie (autre)","Téléphone (autre)","Récepteur de radiomessagerie","Téléphone principal","Radio téléphone","Téléphone TDD/TTY","Télex","Adresse de messagerie","Type de messagerie","Nom complet de l\'adresse de messagerie","Adresse de messagerie 2","Type de messagerie 2","Nom complet de l\'adresse de messagerie 2","Adresse de messagerie 3","Type de messagerie 3","Nom complet de l\'adresse de messagerie 3","Anniversaire","Anniversaire de mariage ou fête","Autre boîte postale","B.P. professionnelle","Boîte postale du domicile","Bureau","Catégories","Code gouvernement","Compte","Conjoint(e)","Critère de diffusion","Disponibilité Internet","Emplacement","Enfants","Informations facturation","Initiales","Kilométrage","Langue","Mots clés","Nom de l\'assistant(e)","Notes","Numéro d\'identification de l\'organisation","Page Web","Passe-temps","Priorité","Privé","Profession","Recommandé par","Responsable","Serveur d\'annuaire","Sexe","Utilisateur 1","Utilisateur 2","Utilisateur 3","Utilisateur 4"
																								';
				fwrite($fdw, $row);
				for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
					$row = '"",';
					$row .= '"' . $stuff[$i]["nom"] . '",,';
					$row .= '"' . $stuff[$i]["prenom"] . '",,,,"' . $stuff[$i]["titre"] . '",,,,,,,,';
					$row .= '"' . $stuff[$i]["adresse1"] . '","' . $stuff[$i]["adresse2"] . '",,"' . $stuff[$i]["ville"] . '","' . $stuff[$i]["province"] . '","' . $stuff[$i]["code_postal"] . '","' . $stuff[$i]["pays"] . '",,,,,,,,,,,,,,,,';
					$row .= '"' . $stuff[$i]["telephone_fixe"] . '",,,"' . $stuff[$i]["telephone_mobile"] . '",,,,,,,,';
					$row .= '"' . $stuff[$i]["courriel"] . '",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,""
																														';
					fwrite($fdw, $row);
				}
				fclose($fdw);
				exportFile("contacts", "contacts.csv", "", true);
				break;
		}
	}


		function action_lister() {
			if (is_array($this->m_postvars["atkselector"])) {
				$select = $this->m_postvars["atkselector"];
			} else {
				$select[0] = $this->m_postvars["atkselector"];
			}
			//  atk_var_dump($this->m_postvars["atkselector"], 'selected records');
			// print_r($this->m_postvars["atkselector"]);
			//print_r($select);
			//die();
			$user = getUser();
			$userid = $user["id"];
			$nom_variable = "id_individu";
			$db = & atkGetDb();
			foreach ($select as $id_variable) {
				$array_id_variable = explode('=', $id_variable);
				$array_id_variable[1] = str_replace("''", "", $array_id_variable[1]);
				$db->query("INSERT INTO tmp_copier_coller (id_utilisateur, nom_variable, id_variable, date_creation)  VALUES( '$userid', '$nom_variable'," . $array_id_variable[1] . ", UTC_TIMESTAMP())");
			}
			$db->commit();
			$this->redirect();
		}
		function postAdd(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseProcess('individu', $id_entite);
		}
		function preDelete(& $record) {
			$id_entite = $record["id"];
			$this->RecentUseDelete('individu', $id_entite);
		}
		function postUpdate($rec) {
			if ($rec["date_deces"] == NULL) {
				$id_entite = $rec["id"];
				$this->RecentUseRefresh('individu');
				return true;
			}
			$user = getUser();
			$id = $user["id"];
			if (!isset ($id)) {
				$id = "1";
			}
			$idindividu = $rec["id"];
			$db = & atkGetDb();
			$db->query("UPDATE individu_inscription set date_radiation=UTC_DATE(), id_type_radiation='1', id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_attribut set date_fin=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_fonction set date_fin=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			$db->query("UPDATE individu_groupe_travail set date_fin_groupe=UTC_DATE(),  id_modification=$id, date_modification=UTC_DATE() where id_individu=$idindividu");
			return true;
		}

		function initial_values() {
			return array (
			"date_deces" => null
			);
		}
		function rowColor($record) {
			$date_deces = $record["date_deces"];
			if ($date_deces != "")
			return $this->couleurarchive;
		}
		function validate(& $record, $mode) {
			$record["telephone_fixe"] = normalisation_telephone($record["telephone_fixe"]);
			$record["telephone_mobile"] = normalisation_telephone($record["telephone_mobile"]);

			if (($record["date_deces"]["year"] == '1999') && ($record["date_deces"]["month"] == '12') && ($record["date_deces"]["day"] == '31')) {
				unset ($record["date_deces"]["year"]);
				unset ($record["date_deces"]["month"]);
				unset ($record["date_deces"]["day"]);
			}
			if (($record["date_naissance"]["year"] == '1999') && ($record["date_naissance"]["month"] == '12') && ($record["date_naissance"]["day"] == '31')) {
				unset ($record["date_naissance"]["year"]);
				unset ($record["date_naissance"]["month"]);
				unset ($record["date_naissance"]["day"]);
			}
			parent :: validate($record, $mode);
		}
		function action_normalisation() {
			$db = & atkGetDb();
			$data = $db->getrows("SELECT id, nom , prenom, telephone_fixe, telephone_mobile " . " from individu");
			if (count($data) == 0) {
				return true;
			} else {
				for ($i = 0; $i < count($data); $i++) {
					$data[$i]["nom"] = normalisation_chaine($data[$i]["nom"]);
					$data[$i]["nom"] = addslashes($data[$i]["nom"]);
					$data[$i]["prenom"] = normalisation_chaine($data[$i]["prenom"]);
					$data[$i]["prenom"] = addslashes($data[$i]["prenom"]);
					$data[$i]["telephone_fixe"] = normalisation_telephone($data[$i]["telephone_fixe"]);
					$data[$i]["telephone_fixe"] = addslashes($data[$i]["telephone_fixe"]);
					$data[$i]["telephone_mobile"] = normalisation_telephone($data[$i]["telephone_mobile"]);
					$data[$i]["telephone_mobile"] = addslashes($data[$i]["telephone_mobile"]);
					$db->query("UPDATE individu" . " set nom='" . $data[$i]["nom"] . "'" . " , prenom='" . $data[$i]["prenom"] . "'"
					. " , telephone_fixe='" . $data[$i]["telephone_fixe"] . "'"
					. " , telephone_mobile='" . $data[$i]["telephone_mobile"] . "'"
					. " where id=" . $data[$i]["id"] . "");
				}
			}
			echo "<br> Normalisation des noms, prénoms, téléphones terminée.";
		}
		function action_lien() {
			$id_1 = $this->m_postvars["id1"];
			$id_2 = $this->m_postvars["id2"];
			$recs1 = $this->selectDb("individu.id=$id_1");
			$record1 = $recs1[0];
			$res = "<table border='1'>";
			$res .= "<tr><td class='styletitre'><b>";
			$res .= $record1["id_titre"]["titre_long"] . " " . $record1["prenom"] . " " . $record1["nom"] . "</b></td><td" . $styletitre . "><b>";
			$recs2 = $this->selectDb("individu.id=$id_2");
			$record2 = $recs2[0];
			$res .= $record2["id_titre"]["titre_long"] . " " . $record2["prenom"] . " " . $record2["nom"] . "</b></td></tr>";
			$res .= "<tr><td class='styleligne'>";
			if (!empty ($record1["date_naissance"]["year"])) {
				$res .= $record1["date_naissance"]["year"] . "-" . $record1["date_naissance"]["month"] . "-" . $record1["date_naissance"]["month"] . "<br />";
			}
			if (!empty ($record1["courriel"])) {
				$res .= $record1["courriel"] . "<br />";
			}
			if (!empty ($record1["site_internet"])) {
				$res .= $record1["site_internet"] . "<br />";
			}
			if (!empty ($record1["telephone_fixe"])) {
				$res .= $record1["telephone_fixe"] . "<br />";
			}
			if (!empty ($record1["telephone_mobile"])) {
				$res .= $record1["telephone_mobile"];
			}
			$res .= "</td><td class='styleligne'>";
			if (!empty ($record2["date_naissance"]["year"])) {
				$res .= $record2["date_naissance"]["year"] . "-" . $record2["date_naissance"]["month"] . "-" . $record2["date_naissance"]["month"] . "<br />";
			}
			if (!empty ($record2["courriel"])) {
				$res .= $record2["courriel"] . "<br />";
			}
			if (!empty ($record2["site_internet"])) {
				$res .= $record2["site_internet"] . "<br />";
			}
			if (!empty ($record2["telephone_fixe"])) {
				$res .= $record2["telephone_fixe"] . "<br />";
			}
			if (!empty ($record2["telephone_mobile"])) {
				$res .= $record2["telephone_mobile"];
			}
			$res .= "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Lieux</b></td><td class='styletitre'><b>&nbsp</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_lieux($id_1) . "</td><td class='styleligne'>";
			$res .= $this->get_lieux($id_2) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Attributs</b></td><td class='styletitre'><b>&nbsp</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_liens_attributs($id_1, $id_2) . "</td></tr>";
			/*
			 $res .= "<tr><td".$styletitre."><b>Compétences</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_competences($id_individu,$stylesmallcaps)."</td></tr>";
			 $res .= "<tr><td".$styletitre."><b>Fonctions</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_fonctions($id_individu,$stylesmallcaps)."</td></tr>";
			 $res .= "<tr><td".$styletitre."><b>Inscriptions</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_inscriptions($id_individu,$stylesmallcaps)."</td></tr>";
			 $res .= "<tr><td".$styletitre."><b>Rencontres</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_rencontres($id_individu,$stylesmallcaps)."</td></tr>";
			 $res .= "<tr><td".$styletitre."><b>Contacts</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_contacts($id_individu,$stylesmallcaps)."</td></tr>";
			 $res .= "<tr><td".$styletitre."><b>Activités</b></td></tr>";
			 $res.="<tr><td".$styleligne.">".$this->get_activites($id_individu,$stylesmallcaps)."</td></tr>";
			 */
			$page =   &atkinstance("atk.ui.atkpage");
			$theme = atkinstance("atk.ui.atktheme");
			$page->register_style($theme->stylePath("style.css"));
			$page->addContent( $res);
		}
		function get_liens_attributs($id1, $id2) {
			$db = & atkGetDb();
			$sql = "SELECT  type_attribut.libelle as attribut FROM individu_attribut, type_attribut WHERE individu_attribut.id_individu=$id1
		and individu_attribut.id_attribut in
		( select id_attribut from individu_attribut WHERE id_individu=$id2)
		and individu_attribut.id_attribut=type_attribut.id";
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["attribut"] . "</b>";
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function action_fiche() {
			$id_individu = $this->m_postvars["id"];
			$recs = $this->selectDb("individu.id=$id_individu");
			$record = $recs[0];
			$res = "<table border='1'>";

			$res .= "<tr><td class='styletitre'><b>";
			$res .= $record["id_titre"]["titre_long"] . " " . $record["prenom"] . " " . $record["nom"] . "</b></td></tr>";
			$res .= "<tr><td class='styleligne'>";
			if (!empty ($record["date_naissance"]["year"])) {
				$res .= $record["date_naissance"]["year"] . "-" . $record["date_naissance"]["month"] . "-" . $record["date_naissance"]["month"] . "<br />";
			}
			if (!empty ($record["courriel"])) {
				$res .= $record["courriel"] . "<br />";
			}
			if (!empty ($record["site_internet"])) {
				$res .= $record["site_internet"] . "<br />";
			}
			if (!empty ($record["telephone_fixe"])) {
				$res .= $record["telephone_fixe"] . "<br />";
			}
			if (!empty ($record["telephone_mobile"])) {
				$res .= $record["telephone_mobile"];
			}
			$res .= "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Lieux</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_lieux($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Attributs</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_attributs($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Compétences</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_competences($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Fonctions</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_fonctions($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Inscriptions</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_inscriptions($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Rencontres</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_rencontres($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Contacts</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_contacts($id_individu) . "</td></tr>";
			$res .= "<tr><td class='styletitre'><b>Activités</b></td></tr>";
			$res .= "<tr><td class='styleligne'>" . $this->get_activites($id_individu) . "</td></tr>";
			$res .= "</table>";
			$page =   &atkinstance("atk.ui.atkpage");
			$theme = atkinstance("atk.ui.atktheme");
			$page->register_style($theme->stylePath("style.css"));
			$page->addContent( $res);

		}
		function get_lieux($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_lieu");
			$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
			$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
			$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
			$query->addField("individu_lieu.adresse_defaut_o_n as adresse_postale");
			$query->addField("lieu.adresse1 as adresse1");
			$query->addField("lieu.adresse2 as adresse2");
			$query->addField("type_cp_ville_pays.code_postal as code_postal");
			$query->addField("type_cp_ville_pays.province_etat as province");
			$query->addField("type_cp_ville_pays.ville as ville");
			$query->addField("type_pays.libelle_anglais as pays");
			$query->addCondition("individu_lieu.id_individu = $id_individu");
			$query->addOrderBy("individu_lieu.adresse_defaut_o_n desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				if ($stuff[$i]["adresse_postale"] == '1') {
					$retour .= '';
				} else {
					$retour .= '<b>Adresse supplémentaire :</b><br />';
				}
				if (!empty ($stuff[$i]["adresse1"])) {
					$retour .= $stuff[$i]["adresse1"] . "<br />";
				}
				if (!empty ($stuff[$i]["adresse2"])) {
					$retour .= $stuff[$i]["adresse2"] . "<br />";
				}
				$retour .= $stuff[$i]["code_postal"] . " ";
				$retour .= $stuff[$i]["ville"] . "<br />";
				$retour .= $stuff[$i]["province"] . "<br />";
				$retour .= $stuff[$i]["pays"] . "<br />";
			}
			return $retour;
		}
		function get_attributs($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_attribut");
			$query->addJoin("type_attribut", "", "individu_attribut.id_attribut = type_attribut.id", true);
			$query->addField("type_attribut.libelle as attribut");
			$query->addField("individu_attribut.date_debut as date_debut");
			$query->addField("individu_attribut.date_fin as date_fin");
			$query->addCondition("individu_attribut.id_individu = $id_individu");
			$query->addOrderBy("individu_attribut.date_debut desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["attribut"] . "</b>";
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= " de " . $stuff[$i]["date_debut"];
				}
				if (!empty ($stuff[$i]["date_fin"])) {
					$retour .= " à " . $stuff[$i]["date_fin"];
				}
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_competences($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_competence");
			$query->addJoin("type_competence", "", "individu_competence.id_type_competence = type_competence.id", true);
			$query->addField("type_competence.libelle as competence");
			$query->addCondition("individu_competence.id_individu = $id_individu");
			$query->addOrderBy("type_competence.libelle ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["competence"] . "</b>";
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_fonctions($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_fonction");
			$query->addJoin("type_fonction", "", "individu_fonction.id_fonction = type_fonction.id", true);
			$query->addJoin("organisme", "", "individu_fonction.id_organisme = organisme.id", true);
			$query->addField("type_fonction.libelle as fonction");
			$query->addField("organisme.nom as organisme");
			$query->addField("individu_fonction.date_debut as date_debut");
			$query->addField("individu_fonction.date_fin as date_fin");
			$query->addCondition("individu_fonction.id_individu = $id_individu");
			$query->addOrderBy("individu_fonction.date_debut desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["organisme"] . '</b> : ' . $stuff[$i]["fonction"];
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= "<br /> de " . $stuff[$i]["date_debut"];
				}
				if (!empty ($stuff[$i]["date_fin"])) {
					$retour .= "<br /> à " . $stuff[$i]["date_fin"];
				}
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_inscriptions($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_inscription");
			$query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
			$query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", true);
			$query->addJoin("organisme", "oi", "individu_inscription.id_organisme_inscrit = oi.id", true);
			$query->addField("type_inscription.libelle as inscription");
			$query->addField("organisme.nom as organisme");
			$query->addField("oi.nom as organisme_inscrit");
			$query->addField("individu_inscription.date_inscription as date_debut");
			$query->addField("individu_inscription.date_radiation as date_fin");
			$query->addCondition("individu_inscription.id_individu = $id_individu");
			$query->addOrderBy("individu_inscription.date_inscription desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["organisme"] . '</b> : ' . $stuff[$i]["inscription"] . '<br />';
				if (!empty ($stuff[$i]["organisme_inscrit"])) {
					$retour .= " pour " . $stuff[$i]["organisme_inscrit"] . "<br />";
				}
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= " de " . $stuff[$i]["date_debut"];
				}
				if (!empty ($stuff[$i]["date_fin"])) {
					$retour .= " à " . $stuff[$i]["date_fin"];
				}
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_rencontres($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_rencontre");
			$query->addJoin("type_rencontre_participation", "", "individu_rencontre.id_type_rencontre_participation = type_rencontre_participation.id", true);
			$query->addJoin("organisme_rencontre", "", "organisme_rencontre.id = individu_rencontre.id_rencontre", true);
			$query->addJoin("type_rencontre", "", "organisme_rencontre.id_type_rencontre = type_rencontre.id", true);
			$query->addJoin("organisme", "", "organisme_rencontre.id_organisme = organisme.id", true);
			$query->addField("type_rencontre.libelle as type_rencontre");
			$query->addField("organisme_rencontre.libelle as rencontre");
			$query->addField("type_rencontre_participation.libelle as participation");
			$query->addField("organisme.nom as organisme");
			$query->addField("organisme_rencontre.date_debut as date_debut");
			$query->addCondition("individu_rencontre.id_individu = $id_individu");
			$query->addOrderBy("organisme_rencontre.date_debut desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["organisme"] . '</b> : ' . $stuff[$i]["type_rencontre"] . '<br />';
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= $stuff[$i]["date_debut"];
				}
				$retour .= " : " . $stuff[$i]["participation"] . '<br />';
				$retour .= $stuff[$i]["rencontre"];
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_contacts($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_contact");
			$query->addJoin("type_contact", "", "individu_contact.id_type_contact = type_contact.id", true);
			$query->addJoin("individu", "", "individu_contact.id_individu = individu.id", true);
			$query->addJoin("individu", "ic", "individu_contact.id_contact = ic.id", true);
			$query->addField("type_contact.libelle as contact");
			$query->addField("ic.id as id1");
			$query->addField("ic.nom as nom1");
			$query->addField("ic.prenom as prenom1");
			$query->addField("individu.id as id2");
			$query->addField("individu.nom as nom2");
			$query->addField("individu.prenom as prenom2");
			$query->addField("individu_contact.titre as titre");
			$query->addField("individu_contact.date_prevue as date_debut");
			$query->addField("individu_contact.date_realisee as date_fin");
			$query->addCondition("individu_contact.id_individu = $id_individu or individu_contact.id_contact = $id_individu");
			$query->addOrderBy("individu_contact.date_prevue desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				if ($stuff[$i]["id1"] == $id_individu) {
					$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["nom2"] . " " . $stuff[$i]["prenom2"] . '</b> (Vers) : ' . $stuff[$i]["contact"] . '<br />';
				} else {
					$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["nom1"] . " " . $stuff[$i]["prenom1"] . '</b> (De): ' . $stuff[$i]["contact"] . '<br />';
				}
				if (!empty ($stuff[$i]["titre"])) {
					$retour .= $stuff[$i]["titre"] . '<br />';
				}
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= "Prévu le  " . $stuff[$i]["date_debut"];
				}
				if (!empty ($stuff[$i]["date_fin"])) {
					$retour .= ".Fait le " . $stuff[$i]["date_fin"];
				}
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function get_activites($id_individu) {
			$db = & atkGetDb();
			$query = & $db->createQuery();
			$query->addTable("individu_activite");
			$query->addJoin("type_activite", "", "individu_activite.id_type_activite = type_activite.id", true);
			$query->addJoin("organisme", "", "individu_activite.id_organisme = organisme.id", true);
			$query->addField("type_activite.libelle as activite");
			$query->addField("organisme.nom as organisme");
			$query->addField("individu_activite.libelle as libelle");
			$query->addField("individu_activite.nombre_heures as heures");
			$query->addField("individu_activite.nombre_kilometres as kilometres");
			$query->addField("individu_activite.date_debut_periode as date_debut");
			$query->addField("individu_activite.date_fin_periode as date_fin");
			$query->addCondition("individu_activite.id_individu = $id_individu");
			$query->addOrderBy("individu_activite.date_debut_periode desc ");
			$sql = $query->buildSelect();
			$stuff = $db->getrows($sql);
			$retour = '';
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$retour .= "<b class='stylesmallcaps'>" . $stuff[$i]["organisme"] . '</b> : ' . $stuff[$i]["activite"] . '<br />';
				if (!empty ($stuff[$i]["date_debut"])) {
					$retour .= " de " . $stuff[$i]["date_debut"];
				}
				if (!empty ($stuff[$i]["date_fin"])) {
					$retour .= " à " . $stuff[$i]["date_fin"];
				}
				$retour .= "<br />";
				$retour .= $stuff[$i]["libelle"] . '<br />';
				$retour .= $stuff[$i]["heures"] . ' heures';
				if (!empty ($stuff[$i]["kilometres"])) {
					$retour .= ' et ' . $stuff[$i]["kilometres"] . ' kilomètres';
				}
				$retour .= "<br /><br />";
			}
			return $retour;
		}
		function descriptor_def() {
			return "[nom] [prenom]";
		}
		// GG deb
		/*		function createSearchFilter($searchvalue)
		{

		$searchfields = array("nom","prenom");
		$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
		$parts = preg_split('/\s+/', $searchvalue);
		$mainFilter = array();
		foreach ($parts as $part)
		{
		$filter = array();
		foreach($searchfields as $attribname)
		{
		$tmp = "LOWER(".$table.$attribname.")";
		$tmp.= " LIKE LOWER('%{$part}%')";
		$filter[] = $tmp;

		}

		if (count($filter) > 0)
		$mainFilter[] = "(".implode(") OR (", $filter).")";
		}
		if (count($mainFilter) > 0)
		return "(".implode(") AND (", $mainFilter).")";
		else return "";
		}
		*/
		function action_admin($handler) {

			if  (substr($this->m_postvars["atkfilter"],0,5) =="'%@@@")
			{
				$searchvalue=$this->m_postvars["atkfilter"];
				$searchfields = array("nom","prenom");
				$searchvalue=substr($searchvalue,5,strlen($searchvalue)-8);
				$filter = $this->createSearchFilter($searchfields,$searchvalue,$this->table );
				$this->m_postvars["atkfilter"]=$filter;
			}

			$view = $this->getView();

			if ($view == "active") {
				$this->addFilter("individu.date_deces IS NULL");
				$this->addFilter($this->m_postvars["atkfilter"]);
			}

			return $handler->action_admin();
		}
		function adminHeader()
		{
			$retour=parent::adminHeader();
			if (isset($this->m_postvars['atkfilter']))
			{$retour.='</b>Attention filtre actif :  '.$this->m_postvars['atkfilter'].'<b><br />';	}
			return $retour;
		}

		function modifyDataGrid($grid,$mode)
		{

			if ($mode==2)
			{

				$grid->setPostvar("atkfilter",'');
				$this->m_postvars['atkfilter']='';
				global $ATK_VARS;
				$ATK_VARS['atkfilter'] = '';
				///  print_r ($this->p($grid->getPostvars()));
				// die();
			}

			return true;
		}


		function adminFooter() {
			$retour=parent::adminFooter();
			$view = $this->getView();
			$legende = 'Légende des couleurs : ';
			$legende .= '<font color="' . $this->couleurarchive . '"> <b> Archive ';
			if ($view == "active") {
				return atktext("onlyactiverecordsareshown") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=nonactive', atktext('clicktoviewarchive', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
			} else {
				return atktext("youareinthearchive") . " " . href('dispatch.php?atknodetype=' . $this->atkNodeType() . '&atkaction=' . $this->m_action . '&view=active', atktext('clicktoviewactiverecords', $this->m_module, $this->m_type)) . "<br>" . $legende .$retour;
			}
		}
		function action_vcard() {
			return $this->createVCard($this->m_postvars["individu.id"]);
		}

		function createVCard($id) {
			//		include_once (moduleDir("utils") . "vcard.php");
			//		$v = new vCard();
			//include_once(moduleDir("include") . 'class.vCard.inc.php');
			include_once (atkconfig("atkroot") . "modules/include/class.vCard.inc.php");
			$vCard = new vCard('atkdocumenttmp/vcards', 'fr');
			$recs = $this->selectDb("individu.id='" . $id . "'", "", "", "", array (
			"id",
			"telephone_fixe",
			"telephone_mobile",
			"nom",
			"prenom",
			"courriel"
			));
			$record = $recs[0];
			$vCard->setFirstName($record["prenom"]);
			//$vCard->setMiddleName('Mobil');
			$vCard->setLastName($record["nom"]);
			$vCard->setTelephoneHome1($record["telephone_fixe"]);
			// $vCard->setTelephoneHome2('+43 (05555) 000000');
			$vCard->setCellphone($record["telephone_mobile"]);
			$vCard->setEMail($record["courriel"]);
			$db = & atkGetDb();
			$data = $db->getrows("SELECT tt.titre_court as titre
										from type_titre	tt, individu i
											where i.id='" . $id . "'
										and i.id_titre=tt.id
													");
			$vCard->setEducationTitle($data[0]["titre"]);
			/*		$v->setPhoneNumber($record["telephone_fixe"], "PREF;WORK;VOICE");
				$v->setPhoneNumber($record["telephone_mobile"], "CELL");
				$v->setName($record["nom"], $record["prenom"], "", "");
				$v->setEmail($record["courriel"]);
				*/
			$id_individu = $record['id'];
			$db = & atkGetDb();
			$data = $db->getrows("SELECT adresse1, adresse2,  code_postal, ville, province_etat,libelle_francais
												from individu_lieu il, lieu l, type_cp_ville_pays v , type_pays p
												where il.id_individu='" . $id_individu . "'
												and il.id_lieu=l.id
												and l.id_ville=v.id
												and v.id_pays=p.id
												");
			$pays = strtolower($data[0]["libelle_francais"]);
			$pays = ucwords($pays);
			$vCard->setPostalStreet($data[0]["adresse1"]);
			$vCard->setPostalZIP($data[0]["code_postal"]);
			$vCard->setPostalCity($data[0]["ville"]);
			$vCard->setPostalRegion($data[0]["province_etat"]);
			$vCard->setPostalCountry($pays);
			/*		$v->setAddress("", "", $data[0]["adresse1"], $data[0]["ville"], $data[0]["province_etat"], $data[0]["code_postal"], $pays);
				;
				*/
			//		$output = $v->getVCard();
			$name = str_replace(" ", "_", $record['prenom'] . "_" . $record['nom']);
			//	$filename = $name . ".vcf";
			$output = $vCard->getCardOutput();
			$vCard->writeCardFile();
			$filename = $vCard->getCardFilePath();
			Header("Content-Disposition: attachment; filename=$filename");
			Header("Content-Length: " . strlen($output));
			Header("Connection: close");
			Header("Content-Type: text/x-vCard; name=$filename");
			echo $output;
			/*		echo $vCard->getCardOutput();
			 $vCard->writeCardFile();
			 header('Location:' . $vCard->getCardFilePath());
			 */
		}
		function action_googlemap() {
			$idindividu = $this->m_postvars["id"];
			$user = getUser();
			$iduser = $user["id"];
			if ($idindividu == 0) {
				$selectmapindividu = "SELECT l.id as idlieu, i.id as identity, i.id_document_portrait as id_document_portrait ,i.nom as nom, i.prenom as prenom ,i.courriel as courriel , i.site_internet as site_internet, i.telephone_fixe as telephone_fixe, i.telephone_mobile as telephone_mobile, l.longitude as longitude" . ", l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" . " from " . "individu i left join individu_lieu il on i.id=il.id_individu
																		 left join  lieu l on il.id_lieu=l.id
																		left join type_cp_ville_pays c on  l.id_ville =c.id
																		left join type_pays p on p.id=c.id_pays " . "order by nom, prenom";
			} else {
				$selectmapindividu = "SELECT l.id as idlieu, i.id as identity, i.id_document_portrait as id_document_portrait ,i.nom as nom, i.prenom as prenom ,i.courriel as courriel , i.site_internet as site_internet, i.telephone_fixe as telephone_fixe,i.telephone_mobile as telephone_mobile,l.longitude as longitude" . ", l.latitude as latitude, l.adresse1 as adresse1 , l.adresse2 as adresse2, c.code_postal as code_postal, c.ville as ville, " . "p.libelle_anglais as pays" . " from " . "individu i left join individu_lieu il on i.id=il.id_individu
																		 left join  lieu l on il.id_lieu=l.id
																		left join type_cp_ville_pays c on  l.id_ville =c.id
																		left join type_pays p on p.id=c.id_pays " . " where i.id=$idindividu or i.id in (select id_individu from app_utilisateur where id=$iduser)" . "order by nom, prenom";
			}
			return $this->createMarkers($selectmapindividu, "individu");
		}
		function createMarkers($select, $type) {
			include_once (moduleDir("utils") . "class.googlemapapi.inc");
			$map = new GoogleMapAPI('map', 'association_map');
			$map->setAPIKey($this->get_map_key());
			$map->setHeight("500");
			$map->setWidth("800");
			//$map->disableTypeControls();
			$map->setMapType('hybrid'); // default
			//$map->disableDirections();
			$map->enableZoomEncompass();
			$map->enableOverviewControl();
			$db = & atkGetDb();
			$r = $db->getrows("$select");
			$missing = 0;
			$missingnoms = "";
			$missingadresse = 0;
			$missingadressenoms = "";
			$site = atkHost();
			$urlsite = 'http://' . $site;
			$sitesanswww = substr_replace($site, '', 0, 4);
			$photosdir = atkconfig("photosdir");
			for ($i = 0; $i < count($r); $i++) {
				$address = $r[$i]['adresse1'] . ", " . $r[$i]['code_postal'] . ", " . $r[$i]['ville'] . ", " . $r[$i]['pays'];
				if ($type == "organisme") {
					$html = "<a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>" . "<br />" . $r[$i]['adresse1'] . "<br />" . $r[$i]['code_postal'] . " " . $r[$i]['ville'] . "<br />" . $r[$i]['pays'] . "<br /><a href=\"mailto:" . $r[$i]['courriel'] . "\">" . $r[$i]['courriel'] . "</a><br /><a href=\"" . $r[$i]['site_internet'] . "\">" . $r[$i]['site_internet'] . "</a><br />" . $r[$i]['telephone_fixe'] . "<br />" . $r[$i]['telephone_mobile'];
				} else {
					$idportrait = $r[$i]['id_document_portrait'];
					if (isset ($idportrait) || $idportrait != 0) {
						$sqlp = "select id, file_extension,file_content, file_size from organisme_document
																	 where id=" . $idportrait . "";
						$dataphoto = $db->getrows($sqlp);
						$filename = ".." . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'];
						$file = @ fopen($filename, "w");
						@ fwrite($file, base64_decode($dataphoto[0]["file_content"]));
						@ fclose($file);
						$urlphotozone = "http://" . $sitesanswww . $photosdir . "gis_photo_" . $dataphoto[0]['id'] . "." . $dataphoto[0]['file_extension'] . "";
						//				$htmlphoto = '<b><a href="' . $urlsite . '"> <img src="' . $urlphotozone . '"></a> </b><br><br />';
						$htmlphoto = '<b><a href=""> <img src="' . $urlphotozone . '"></a> </b><br /><br />';
					} else {
						$htmlphoto = '';
					}
					$html = "<a href='dispatch.php?atknodetype=individu.individu&atkaction=edit&atkselector=individu.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>" . "<br />" . $r[$i]['adresse1'] . "<br />" . $r[$i]['code_postal'] . " " . $r[$i]['ville'] . "<br />" . $r[$i]['pays'] . "<br /><a href=\"mailto:" . $r[$i]['courriel'] . "\">" . $r[$i]['courriel'] . "</a><br /><a href=\"" . $r[$i]['site_internet'] . "\">" . $r[$i]['site_internet'] . "</a><br />" . $r[$i]['telephone_fixe'] . "<br />" . $r[$i]['telephone_mobile'] . "</a><br />" . $htmlphoto;
					;
				}
				$title = $r[$i]['nom'] . " " . $r[$i]['prenom'];
				$longitude = $r[$i]['longitude'];
				$latitude = $r[$i]['latitude'];
				$idlieu = $r[$i]['idlieu'];
				if (!isset ($r[$i]['code_postal'])) {
					$missingadresse = $missingadresse +1;
					if ($type == "organisme") {
						$missingadressenoms .= "<br /><a href='dispatch.php?atknodetype=organisme.organisme&atkaction=edit&atkselector=organisme.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
					} else {
						$missingadressenoms .= "<br /><a href='dispatch.php?atknodetype=individu.individu&atkaction=edit&atkselector=individu.id=" . $r[$i]['identity'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
					}
				} else {
					if (!isset ($longitude)) {
						$coords = array ();
						$coords = $map->geoGetCoords($address);
						$map->putCache($idlieu, $coords["lon"], $coords["lat"]);
						$longitude = $coords["lon"];
						$latitude = $coords["lat"];
					}
					if (!isset ($longitude) or !isset ($latitude)) {
						$missing = $missing +1;
						$missingnoms .= "<br /><a href='dispatch.php?atknodetype=individu.lieu&atkaction=edit&atkselector=lieu.id=" . $r[$i]['idlieu'] . "'>" . $r[$i]['nom'] . " " . $r[$i]['prenom'] . "</a>";
					} else {
						$map->addMarkerByCoords($longitude, $latitude, $title, $html);
					}
				}
			}
			$output1 = & atkOutput :: getInstance();
			$output = "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">";
			$output .= "<html xmlns=\"http://www.w3.org/1999/xhtml\" xmlns:v=\"urn:schemas-microsoft-com:vml\">";
			$output .= "<head>";
			$output .= $map->printHeaderJS();
			$output .= $map->printMapJS();
			//  <!-- necessary for google maps polyline drawing in IE -->
			$output .= "<style type=\"text/css\">";
			$output .= "v\:* {";
			$output .= "    behavior:url(#default#VML);";
			$output .= "}";
			$output .= "</style>";
			$output .= "</head>";
			$output .= "<body onload=\"onLoad()\">";
			$output .= "<font face=\"arial\" size=\"1\" >";
			$output .= "<table border=1>";
			$output .= "<tr><td>";
			$output .= $map->printMap();
			$output .= "</td><td>";
			$output .= $map->printSidebar();
			$output .= "</td></tr>";
			$output .= "</table>";
			$output .= "<font face=\"arial\" size=\"1\" color=\"red\">";
			$output .= $missing . " : non géolocalisables";
			$output .= $missingnoms;
			$output .= "<br />" . $missingadresse . " : sans adresse";
			$output .= $missingadressenoms;
			$output .= "</font></body>";
			$output .= "</html>";
			$output1->rawoutput($output);
			$output1->outputFlush();
		}

}

?>
