<?php
useattrib("development.atgomanytoonerelation");
class google_feed extends assMetaNode {
	var $table = "individu_google_feed";
	function meta(& $policy) {
		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function google_feed() {
		$this->atkMetaNode();
		$this->atkNode("google_feed",  NF_ADD_LINK  |NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu_contact", "individu.individu", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),10);
		$this->add(new atkAttribute("album", AF_SEARCHABLE ),15);
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),20 );
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),10150);
		$this->add(new atkAttribute("compte_google", AF_SEARCHABLE|AF_OBLIGATORY ,200),10160);
		$this->add(new atkListAttribute("type_feed", array("Contacts", "Photos"), array(1,2),AF_SEARCHABLE|AF_OBLIGATORY),10170);
		$this->add(new atkAttribute("url_google", AF_SEARCHABLE ,200),10180);
		$this->add(new atkCurrencyAttribute("nombre_de_photos",  AF_SEARCHABLE|AF_TOTAL, 6,"", 0,",","."),10190);
		$this->add(new atkCurrencyAttribute("taille_octets",  AF_SEARCHABLE|AF_TOTAL , 10,"", 0,",","."),10200);
		$this->add(new atkUrlAttribute("lien_album", AF_POPUP),10210);
		$this->add(new atkAttribute("date_publication_album", AF_SEARCHABLE ),10220);


		$this->add(new atkAttribute("date_synchronisation_google", AF_SEARCHABLE ),10230);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder(" individu_google_feed.date_synchronisation_google desc");
		$this->m_securityMap["inscrire_du_presse_papier"] = "view";
		$this->m_securityMap["delete_album"] = "view";
		$this->m_securityMap["photos_album"] = "view";
		$this->m_securityMap["api_google"] = "view";
		$this->m_securityMap["maj_contacts"] = "view";
		$this->m_securityMap["synchro_liste"] = "view";
		

	}

	function id_individu_display($record, $mode)
	{
		return $this->descripteur_individu($record["id_individu"]["id"],'n');
	}
	function album_display($record, $mode)
	{
		if ($record["type_feed"]=='2') return $this->descripteur_google_feed_album($record["id"],'o');
	}

	function nombre_de_photos_display($record, $mode)
	{
		$id_album=$record["id"];
		$nombre_de_photos=$record["nombre_de_photos"];
			$retour=href(dispatch_url("individu.google_photos", "admin", array (
				'atkfilter' => "individu_google_photo.id_album=$id_album "
				), "dispatch.php"),$nombre_de_photos, SESSION_NESTED);
		return $retour;
	}
	
	function id_individu_contact_display($record, $mode)
	{
		if ($record["id_individu_contact"]["id"]>0)
		{return $this->descripteur_individu($record["id_individu_contact"]["id"],'n');}
		else
		{return $record["id_individu_contact"]["id"];}
	}

	function descriptor_def() {
		return "[id]";
	}

	function preDelete(&$record)
	{
		if ($record["url_google"]!="" and $record["type_feed"]=='1')
		{
			echo "Suppression impossible car référencé dans Google";
			die();

		}
		else
		{if ($record["url_google"]!="" and $record["type_feed"]=='2')
		{
			$this->delete_album($record["url_google"]);
		}
		return true;
		}
	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}


	function adminFooter() {
		$retour=parent::adminfooter();
	}

	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_google_feed
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	function contact_retrieve ()
	{

		// load Zend Gdata libraries
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Http_Client');
		Zend_Loader::loadClass('Zend_Gdata_Query');
		Zend_Loader::loadClass('Zend_Gdata_Feed');

		// set credentials for ClientLogin authentication
		$user = "user@gmail.com";
		$pass = "guessme";

		try {
			// perform login and set protocol version to 3.0
			$client = Zend_Gdata_ClientLogin::getHttpClient(
			$user, $pass, 'cp');
			$gdata = new Zend_Gdata($client);
			$gdata->setMajorProtocolVersion(3);
	

			// perform query and get result feed
			$query = new Zend_Gdata_Query(
        'https://www.google.com/m8/feeds/contacts/default/full');
			$feed = $gdata->getFeed($query);
			echo $feed->totalResults;
			// parse feed and extract contact information
			// into simpler objects
			$results = array();
			foreach($feed as $entry){
				$xml = simplexml_load_string($entry->getXML());
				$obj = new stdClass;
				$obj->name = (string) $entry->title;
				$obj->orgName = (string) $xml->organization->orgName;
				$obj->orgTitle = (string) $xml->organization->orgTitle;

				foreach ($xml->email as $e) {
					$obj->emailAddress[] = (string) $e['address'];
				}

				foreach ($xml->phoneNumber as $p) {
					$obj->phoneNumber[] = (string) $p;
				}
				foreach ($xml->website as $w) {
					$obj->website[] = (string) $w['href'];
				}

				$results[] = $obj;
			}
		} catch (Exception $e) {
			die('<br>ERROR:' . $e->getMessage());
		}

		foreach ($results as $r) {
			echo (!empty($r->name)) ?
			$r->name : 'Name not available';
			echo $r->orgName;
			echo @join(', ', $r->emailAddress);
			echo @join(', ', $r->phoneNumber);
			echo @join(', ', $r->website);
		}

	}
	function contact_add ($gdata,$id_individu_contact, $nom , $user)
	{

		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata_Query');
		Zend_Loader::loadClass('Zend_Gdata_Feed');

		try {
			$doc=$this->get_contact_doc($id_individu_contact,"add");
			// insert entry
			$entryResult = $gdata->insertEntry($doc->saveXML(),
   'https://www.google.com/m8/feeds/contacts/default/full');
			// https://www.google.com/m8/feeds/contacts/liz%40gmail.com/full

			return $entryResult->id;
		} catch (Exception $e) {
//			die('<br>ERROR :' . $e->getMessage()."<br />"."Add : ".$id_individu_contact." (".$nom.")");
			echo ('<br>ERROR :' . $e->getMessage()."<br />"."Add : ".$id_individu_contact." (".$nom.")");
			
		}
	}
	function contact_delete ($gdata, $url_id)
	{

		try {
			// delete entry
			$url_id=str_replace("http://", "https://", $url_id);
			$entry = $gdata->getEntry($url_id);
	//		$gdata->delete($entry); 
			$gdata->delete($url_id);
			return 'Entry deleted';
		} catch (Exception $e) {
			die('<br>ERROR:' . $e->getMessage()."<br />"."Delete : ".$url_id);
		}
	}
	function	google_ClientLogin($user,$pass)
	{
		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Http_Client');
		$client = Zend_Gdata_ClientLogin::getHttpClient(
		$user, $pass, 'cp');
		/*		$client->setHeaders('If-Match: *');
		 $gdata = new Zend_Gdata($client);
		 $gdata->setMajorProtocolVersion(3);
		 */
		return $client;
	}
	function	action_maj_contacts()
	{

		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		global $g_user;
		$userid = $g_user["id"];
		$this->google_contacts_sync($id_individu,$userid,"menu");

	}
	function	google_contacts_sync($id_individu,$userid,$origine)
	{
		$db = & atkGetDb();
		$sql="SELECT  id, identifiant_google, code_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$user=$data[0]["identifiant_google"];
		if ($user=="") die("Vous n'avez pas déclaré de compte google");
		$pass=$data[0]["code_google"];
		
		$this->get_new_assocope_contacts($id_individu,$user,$userid);
		$client=$this->google_ClientLogin($user,$pass);
		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
		if ($origine!="login")
		{echo "<br />".$this->contacts_google_insert($gdata,$id_individu,$user);}
		
	

		if ($origine!="login")
		{$client=$this->google_ClientLogin($user,$pass);
		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
		echo "<br />".$this->contacts_google_update($gdata,$id_individu);
		}
	
		

		if ($origine!="login")
		{$client=$this->google_ClientLogin($user,$pass);
		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
		echo "<br />".$this->contacts_google_delete($gdata);
		echo "<br />Synchronisation terminée";
		}
	
	}

	function get_new_assocope_contacts($id_individu, $user,$userid)
	{
		/*
		 * Get individu_id de recent use pour l'utilisateur, les individu_id des correspondants de l'utilisateur et ajouter dans google_feed "contact" les individu_id qui n'y seraient pas .
		 * Ensuite mettre à jour les contacts qui ont un google_id, créer les contacts qui n'en ont pas et le socker dans l'enregistrement correspondant
		 *  */
		$sql="(select id_entite as id_individu_contact from app_recent_use where id_individu= $id_individu and type_entite='individu')
union
(select id_individu_correspondant as id_individu_contact  from individu_correspondant where id_individu= $id_individu) ";
		$db = & atkGetDb();
		$dbquery = & atkGetDb();
		$dbinsert = & atkGetDb();
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++)
		{
			$id_individu_contact=$data[$i]['id_individu_contact'];
			$sql="select id_individu_contact from individu_google_feed where type_feed='1' and id_individu = $id_individu and id_individu_contact=$id_individu_contact";
			$dataquery=$dbquery->getrows($sql);
			if (count($dataquery)==0)
			{
				$insertsql=" insert into individu_google_feed
				(id_individu,
				compte_google,
				type_feed,
				id_individu_contact,

				url_google,


				date_synchronisation_google,
				commentaire,
				id_creation,
				date_creation,
				id_modification,
				date_modification)
				values
				(
				'$id_individu',
				'$user',
				'1',
				'$id_individu_contact',
				 
				'',
				 
				 
				null,
				'',
				'$userid', UTC_TIMESTAMP(), '$userid',  UTC_TIMESTAMP()			
				)";
				$dbinsert->query($insertsql);
				$dbinsert->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_google_feed' ");
			}
		}


	}
	function	contacts_google_insert($gdata, $id_individu, $user)
	{
		$db = & atkGetDb();
		$dbupdate = & atkGetDb();
		$userid = $g_user["id"];
		$sql="SELECT f.id,  f.id_individu_contact, CONCAT(i.nom,' ', i.prenom) as nom
			from individu_google_feed f, individu i
			where 
			f.type_feed='1' 
			and f.id_individu=$id_individu 
			and f.url_google=''
		and f.id_individu_contact=i.id
		order by i.nom, i.prenom
					";
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++)
		{
			$id_individu_contact=$data[$i]["id_individu_contact"];
			$id=$data[$i]["id"];
			$nom=$data[$i]["nom"];
			$url_google=$this->contact_add ($gdata, $id_individu_contact, $nom, $user);
			$sql="Update individu_google_feed set  date_synchronisation_google=UTC_TIMESTAMP(), url_google='$url_google' where id=$id ";
			$dbupdate->query($sql);
			//			echo $url_google;
			//			die();
		}
		return $i . " créations ";
	}


	function	contacts_google_update($gdata, $id_individu)
	{ 		$db = & atkGetDb();
	$dbupdate = & atkGetDb();
	$userid = $g_user["id"];
	$sql="SELECT f.id, f.url_google, f.id_individu_contact, CONCAT(i.nom,' ', i.prenom) as nom
			from individu_google_feed f, individu i
			where 
			f.type_feed='1' 
			and f.id_individu=$id_individu 
			and f.date_synchronisation_google < SUBTIME( UTC_TIMESTAMP( ) ,  '2:0:0.000000' )
		and f.id_individu_contact=i.id
				order by i.nom, i.prenom	";
	$data=$db->getrows($sql);
	for ($i = 0; $i < count($data); $i++)
	{
		$url_id=$data[$i]["url_google"];
		$url_id=str_replace("/base/", "/full/", $url_id);
		$id_individu_contact=$data[$i]["id_individu_contact"];
		$id=$data[$i]["id"];
		$nom=$data[$i]["nom"];
		$sql="Update individu_google_feed set  date_synchronisation_google=UTC_TIMESTAMP() where id=$id ";
		$this->contact_modify ($gdata, $url_id, $id_individu_contact, $nom);
		$dbupdate->query($sql);
	}
	return $i . " mises à jour";
	}

	function contacts_google_delete($gdata)
	{

		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata_Query');
		Zend_Loader::loadClass('Zend_Gdata_Feed');
		$query = new Zend_Gdata_Query('https://www.google.com/m8/feeds/contacts/default/full');
		$boucle=0;
		$suivant=true;
		$query->maxResults = 1;
		$feed = $gdata->getFeed($query);
		$nombre="". $feed->totalResults ;
		$iterer=true;
		while ($suivant)
		{
			$query->maxResults = 100;
			$query->startIndex=$boucle+1;
			$query->setParam('orderby', 'lastmodified');
			$query->setParam('sortorder', 'descending');
			$feed = $gdata->getFeed($query);
			$total=$feed->getTotalResults();
			$total = sprintf("%s",$total);
			foreach($feed as $entry){
				$dom = new DomDocument;
				$dom->loadXML($entry->getXML());
				$liste=$dom->getElementsByTagName('id');
				foreach($liste as $nombre)
				{
					$url_id=$nombre->firstChild->nodeValue;
					//				echo $id."<br />";
				}
				$db = & atkGetDb();
				$sql="select url_google from individu_google_feed where type_feed='1' and url_google='$url_id'";
				$data=$db->getrows($sql);
				
				$xml = simplexml_load_string($entry->getXML());
				if (count($xml->externalId)==0 || count($data)==0)
				{$this->contact_delete($gdata, $url_id)		;
				++$nombre_sans_assocope;
				}
				++$boucle;
			}
			if ($boucle >= $total) $suivant=false;
		}
		return $nombre_sans_assocope . " suppressions";

	}

	function contact_modify ($gdata, $url_id, $id_individu_contact, $nom)
	{
		//		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		//		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata_Query');
		Zend_Loader::loadClass('Zend_Gdata_Feed');

		try {
			$query = new Zend_Gdata_Query($url_id);
			$entry = $gdata->getEntry($query);
			$uri=$entry->getEditLink()->href;
			$doc=$this->get_contact_doc($id_individu_contact,"modify");
			$extra_header = array();
			$extra_header = array('If-Match'=>'*');
			$entryResult = $gdata->updateEntry($doc->saveXML(),$uri,null,$extra_header);
			return 'Entry updated';
		} catch (Exception $e) {
			echo('<br>ERROR :' . $e->getMessage()."<br />"."Modify : ".$id_individu_contact." (".$nom.")");
		}
	}

	function get_contact_doc($id_individu,$option)
	{
		$contact_items=$this->get_contact_items($id_individu);
		// create new entry
		$doc  = new DOMDocument();
		$doc->formatOutput = true;
		$entry = $doc->createElement('atom:entry');
		$entry->setAttributeNS('http://www.w3.org/2000/xmlns/' ,
   'xmlns:atom', 'http://www.w3.org/2005/Atom');
		$entry->setAttributeNS('http://www.w3.org/2000/xmlns/' ,
   'xmlns:gd', 'http://schemas.google.com/g/2005');
		$entry->setAttributeNS('http://www.w3.org/2000/xmlns/' ,
   'xmlns:gContact', 'http://schemas.google.com/contact/2008');
		$doc->appendChild($entry);

		// add name element
		$name = $doc->createElement('gd:name');
		$entry->appendChild($name);
		$fullName = $doc->createElement('gd:fullName', utf8_encode($contact_items["prenom"]).' '.utf8_encode($contact_items["nom"]));
		$name->appendChild($fullName);
		$givenName = $doc->createElement('gd:givenName', utf8_encode($contact_items["prenom"]));
		($contact_items["prenom"]!="") ? $name->appendChild($givenName): null;
		$familyName = $doc->createElement('gd:familyName', utf8_encode($contact_items["nom"]));
		$name->appendChild($familyName);
		// add postal addresses
		for ($j = 0; $j < count($contact_items["adresses"]); $j++)
		{

			$structuredPostalAddress = $doc->createElement('gd:structuredPostalAddress');
			$structuredPostalAddress->setAttribute('rel' ,'http://schemas.google.com/g/2005#home');
			$street = $doc->createElement('gd:street', utf8_encode($contact_items["adresses"][$j]["adresse1"])." ".utf8_encode($contact_items["adresses"][$j]["adresse2"]));
			($contact_items["adresses"][$j]["adresse1"]!="") ? $structuredPostalAddress->appendChild($street) : null;
			$city = $doc->createElement('gd:city', utf8_encode($contact_items["adresses"][$j]["ville"]));
			($contact_items["adresses"][$j]["ville"]!="") ? $structuredPostalAddress->appendChild($city) : null;
			$postcode = $doc->createElement('gd:postcode', $contact_items["adresses"][$j]["code_postal"]);
			($contact_items["adresses"][$j]["code_postal"]!="") ? $structuredPostalAddress->appendChild($postcode): null;
			$region = $doc->createElement('gd:region', utf8_encode($contact_items["adresses"][$j]["province"]));
			($contact_items["adresses"][$j]["province"]!="") ? $structuredPostalAddress->appendChild($region): null;
			$country = $doc->createElement('gd:country', utf8_encode($contact_items["adresses"][$j]["pays"]));
			($contact_items["adresses"][$j]["pays"]!="") ? $structuredPostalAddress->appendChild($country): null;
			$entry->appendChild($structuredPostalAddress);

		}

		// add email element
		$email = $doc->createElement('gd:email');
		$email->setAttribute('address' ,$contact_items["courriel"]);
		$email->setAttribute('rel' ,'http://schemas.google.com/g/2005#home');
		($contact_items["courriel"]!="")? $entry->appendChild($email) : null;

		// add url element
		$website = $doc->createElement('gContact:website');
		$website->setAttribute('href' ,$contact_items["site_internet"]);
		$website->setAttribute('rel' ,'home');
		($contact_items["site_internet"]!="")? $entry->appendChild($website) : null;

		// add home phone
		$phoneNumber = $doc->createElement('gd:phoneNumber', $contact_items["telephone_fixe"]);
		$phoneNumber->setAttribute('rel' ,'http://schemas.google.com/g/2005#home');
		($contact_items["telephone_fixe"]!="")? $entry->appendChild($phoneNumber) : null;

		// add mobile phone
		$phoneNumber = $doc->createElement('gd:phoneNumber', $contact_items["telephone_mobile"]);
		$phoneNumber->setAttribute('rel' ,'http://schemas.google.com/g/2005#mobile');
		($contact_items["telephone_mobile"]!="")? $entry->appendChild($phoneNumber) : null;

		// add birthday
		$birthDay = $doc->createElement('gContact:birthday');
		$birthDay->setAttribute('when' ,$contact_items["date_naissance"]);
		($contact_items["date_naissance"]!="")? $entry->appendChild($birthDay) : null;

		// external Id
		$externalId = $doc->createElement('gContact:externalId');
		$externalId->setAttribute('label' ,'AssoCope_Id');
		//			$externalId->setAttribute('rel' ,'Organization');
		$externalId->setAttribute('value' ,$contact_items["id_individu"]);
		($contact_items["id_individu"]!="")? $entry->appendChild($externalId) : null;

		$externalId = $doc->createElement('gContact:externalId');
		$externalId->setAttribute('label' ,'AssoCope_Date');
		//			$externalId->setAttribute('rel' ,'Organization');
		$externalId->setAttribute('value' ,gmdate('c'));
		($contact_items["id_individu"]!="")? $entry->appendChild($externalId) : null;
		/*
		 $systemGroup= $doc->createElement('gContact:systemGroup');
		 $systemGroup->setAttribute('id' ,'Contacts');
		 $entry->appendChild($systemGroup);
		 */
		if ($option=='modify')
		{$groupMembershipInfo= $doc->createElement('gContact:groupMembershipInfo');
		$groupMembershipInfo->setAttribute('href' ,'https://www.google.com/m8/feeds/groups/guy.gourmellet%40gmail.com/base/6');
		$groupMembershipInfo->setAttribute('deleted' ,'false');
		$entry->appendChild($groupMembershipInfo);}

		return $doc;

	}
	function get_contact_items($id_individu)
	{
		$db = & atkGetDb();
		$query = & $db->createQuery();
		$query->addTable("individu");
		$query->addField("individu.id as id_individu");
		$query->addField("individu.nom as nom");
		$query->addField("individu.prenom as prenom");
		$query->addField("individu.courriel as courriel");
		$query->addField("individu.site_internet as site_internet");
		$query->addField("individu.telephone_fixe as telephone_fixe");
		$query->addField("individu.telephone_mobile as telephone_mobile");
		$query->addField("individu.date_naissance as date_naissance");
		$query->addCondition("individu.id = $id_individu");
		$sql = $query->buildSelect();
		$stuff = $db->getrows($sql);

		$query = & $db->createQuery();
		$query->addTable("individu_lieu");
		$query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
		$query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
		$query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
		$query->addField("lieu.adresse1 as adresse1");
		$query->addField("lieu.adresse2 as adresse2");
		$query->addField("lieu.latitude as latitude");
		$query->addField("lieu.longitude as longitude");
		$query->addField("type_cp_ville_pays.code_postal as code_postal");
		$query->addField("type_cp_ville_pays.ville as ville");
		$query->addField("type_cp_ville_pays.province_etat as province");
		$query->addField("type_pays.libelle_anglais as pays");
		$query->addCondition("individu_lieu.id_individu=$id_individu");
		$query->addOrderBy("individu_lieu.date_creation desc");
		$sql = $query->buildSelect();
		$adresses = $db->getrows($sql);
		for ($i = 0; $i < count($adresses); $i++)
		{
			$stuff[0]["adresses"][$i]["adresse1"]=$adresses[$i]["adresse1"];
			$stuff[0]["adresses"][$i]["adresse2"]=$adresses[$i]["adresse2"];
			$stuff[0]["adresses"][$i]["latitude"]=$adresses[$i]["latitude"];
			$stuff[0]["adresses"][$i]["longitude"]=$adresses[$i]["longitude"];
			$stuff[0]["adresses"][$i]["code_postal"]=$adresses[$i]["code_postal"];
			$stuff[0]["adresses"][$i]["ville"]=$adresses[$i]["ville"];
			$stuff[0]["adresses"][$i]["province"]=$adresses[$i]["province"];
			$stuff[0]["adresses"][$i]["pays"]=$adresses[$i]["pays"];
		}

		return $stuff[0];

	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		//	parent::recordActions($rec, $actions, $mraactions);
		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		$actions["delete"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=delete&atkselector=[pk]", SESSION_NESTED);
//		if ($rec["type_feed"]=='2')
//		{$actions["photos_album"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=photos_album&atkselector=[pk]", SESSION_NESTED);
//		}

		//		$mraactions["maj_contacts"] ="maj_contacts";

	}
	function action_synchro_liste() 
	{
	if ($this->m_postvars["idindividus"] =="") {
			$db->commit();
			$this->redirect();
		}
	
	global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="SELECT  id, identifiant_google, code_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$identifiant_google=$data[0]["identifiant_google"];

		if ($identifiant_google=="") die("Vous n'avez pas déclaré de compte google");
		$pass=$data[0]["code_google"];
		
		$nom_variable = "id_individu";
		
		$db = & atkGetDb();
		$requete = "SELECT distinct id FROM individu where id in (".$this->m_postvars["idindividus"].")";
		$data = $db->getrows($requete);

		foreach ($data as $id_individu_correspondant) {
			$id_individu_correspondant_1 = $id_individu_correspondant["id"];
			$data1=$db->getrows("SELECT id from individu_google_feed where id_individu=$id_individu and id_individu_contact=$id_individu_correspondant_1 and type_feed=1");
			if (count($data1)==0)
			{$requete = "INSERT INTO individu_google_feed		
										 (  id_individu,id_individu_contact,type_feed,  compte_google,
										commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
					VALUES( $id_individu ,$id_individu_correspondant_1,'1','$identifiant_google',
					'','$userid', UTC_TIMESTAMP(), '$userid',  UTC_TIMESTAMP()) ";
			$db->query($requete);
			$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_google_feed' ");}
			else if (count($data1)==1)
			{
				$requete = "UPDATE individu_google_feed		
							SET date_modification=UTC_TIMESTAMP()
							WHERE id=".$data1[0]["id"];
				$db->query($requete);
			}
			else 
			{echo "Doublon";
			die();}
			
			
			
			
		}
		
		// créations
			$client=$this->google_ClientLogin($identifiant_google,$pass);
		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
	
	$sql="SELECT  f.id, f.url_google, f.id_individu_contact, CONCAT(i.nom,' ', i.prenom) as nom
			from individu_google_feed f, individu i
			where 
			f.type_feed='1' 
			and f.id_individu_contact in (".$this->m_postvars["idindividus"].")
			and f.id_individu=$id_individu 
			and ( f.url_google='' or f.url_google is NULL )
			and f.id_individu_contact=i.id
		
					";
//	$this->p($sql);
	$dbupdate = & atkGetDb();
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++)
		{
			$id_individu_contact=$data[$i]["id_individu_contact"];
			$id=$data[$i]["id"];
			$nom=$data[$i]["nom"];
			$url_google=$this->contact_add ($gdata, $id_individu_contact, $nom);
			$sql="Update individu_google_feed set  date_synchronisation_google=UTC_TIMESTAMP(), url_google='$url_google' where id=$id ";
			$dbupdate->query($sql);
			//			echo $url_google;
			//			die();
		}
		$retour.="<br>".$i . " créations ";
	// Update
	$client=$this->google_ClientLogin($identifiant_google,$pass);
		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
			
	
	$sql="SELECT  f.id, f.url_google, f.id_individu_contact, CONCAT(i.nom,' ', i.prenom) as nom
			from individu_google_feed f, individu i
			where 
			f.type_feed='1' 
			and f.id_individu_contact in (".$this->m_postvars["idindividus"].")
			and f.id_individu=$id_individu 
			and f.date_modification > SUBTIME( UTC_TIMESTAMP( ) ,  '2:0:0.000000' )
		and f.id_individu_contact=i.id
					";
	$data=$db->getrows($sql);
	for ($i = 0; $i < count($data); $i++)
	{
		$url_id=$data[$i]["url_google"];
		$url_id=str_replace("/base/", "/full/", $url_id);
		$url_id=str_replace("http://", "https://", $url_id);
		$id_individu_contact=$data[$i]["id_individu_contact"];
		$id=$data[$i]["id"];
		$nom=$data[$i]["nom"];
		$sql="Update individu_google_feed set  date_synchronisation_google=UTC_TIMESTAMP() where id=$id ";
		$this->contact_modify ($gdata, $url_id, $id_individu_contact, $nom);
		$dbupdate->query($sql);
	}
	$retour.= $i . " mises à jour";

	$client=$this->google_ClientLogin($identifiant_google,$pass);
//		$client->setHeaders('If-Match: *');
		$gdata = new Zend_Gdata($client);
		$gdata->setMajorProtocolVersion(3);
			$retour.="<br />".$this->contacts_google_delete($gdata);
			$retour.="<br />Synchronisation terminée";
			echo $retour;
		

	}
	
	
	function action_inscrire_du_presse_papier() {
		if (count($this->m_postvars["atkselector"])==1)
		{$pk = $this->m_postvars["atkselector"][0];
		}
		else
		{
			$this->setFeedback("inscrire_du_presse_papier",ACTION_FAILED);
			$location = $this->feedbackUrl("inscrire_du_presse_papier", ACTION_FAILED, "", "Vous devez sélectionner une seule ligne");
			$this->redirect($location);
		}

		$array_1 = explode('AND', $pk);
		$array_individu = explode('=', $array_1[0]);
		$id_individu= $array_individu[1];

		$array_type = explode('=', $array_1[1]);
		$id_type= $array_type[1];

		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="SELECT  identifiant_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$identifiant_google=$data[0]["identifiant_google"];


		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$requete = "SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$data = $db->getrows($requete);
		if (count($data) == 0) {
			$db->commit();
			$this->redirect();
		}


		foreach ($data as $id_individu_correspondant) {
			$id_individu_correspondant_1 = $id_individu_correspondant["id_variable"];
			$requete = "INSERT INTO individu_google_feed
										 (  id_individu,id_individu_contact,type_feed,  compte_google,
										commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
					VALUES( $id_individu ,$id_individu_correspondant_1,'1',$identifiant_google,
					'','$userid', UTC_TIMESTAMP(), '$userid',  UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
			$db->query($requete);
			$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_google_feed' ");
		}

		$requete = "DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}

	function action_photos_album ($url_google , $client)
	{
		//	$this->p($this->m_postvars["atkselector"]);
		global $g_user;
		$userid = $g_user["id"];
/*		if (count($this->m_postvars["atkselector"])==1)
		{$feedid = $this->m_postvars["atkselector"];
		}
		else
		{
			die ("Un seul album à la fois");
		}
		$db = & atkGetDb();
		$dbinsert = & atkGetDb();
		$sql="SELECT id, url_google
			from individu_google_feed
		where $feedid ";
		$data=$db->getrows($sql);
		$album_id=$data[0]["id"];
		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$albumid=$data[0]["url_google"];
		$sql="SELECT  id, identifiant_google, code_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$user=$data[0]["identifiant_google"];
		if ($user=="") die("Vous n'avez pas déclaré de compte google");
		$pass=$data[0]["code_google"];

		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata_Photos');
		Zend_Loader::loadClass('Zend_Gdata_Photos_UserQuery');
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Http_Client');
		$service = Zend_Gdata_Photos::AUTH_SERVICE_NAME;
		$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);
		*/
		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$gp = new Zend_Gdata_Photos($client);

		$query = $gp->newAlbumQuery();
		$boucle=0;
		$suivant=true;
		$db = & atkGetDb();
		$dbinsert = & atkGetDb();
		$sql="SELECT id
			from individu_google_feed
		where url_google=$url_google and type_feed='2' and id_individu=$id_individu";
		$data=$db->getrows($sql);
		$album_id=$data[0]["id"];
		
		
	 while ($suivant)
	 {
	 	$query->maxResults = 50;
	 	$query->startIndex=$boucle+1;
	 	$query->setParam('orderby', 'lastmodified');
	 	$query->setParam('sortorder', 'descending');
	 	$query->setAlbumId($url_google);
	 	$albumFeed = $gp->getAlbumFeed($query);

	 	$total=$albumFeed->getTotalResults();
	 	$total = sprintf("%s",$total);

	 	foreach($albumFeed as $entry){
	 		
	 		$dom = new DomDocument;
					$dom->loadXML($entry->getXML());
//echo $entry->getXML();
	 				$liste=$dom->getElementsByTagName('published');
					foreach($liste as $nombre)
					{
						$published=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('updated');
					foreach($liste as $nombre)
					{
						$updated=$nombre->firstChild->nodeValue;
					}
					
			$title = escapeSQL(utf8_decode($entry->getTitle()));
	 		$summary = utf8_decode($entry->getSummary());
	 		$thumbnail = $entry->getMediaGroup()->getThumbnail();
	 		$content=$entry->getMediaGroup()->getContent();
	 		$tags = utf8_decode($entry->getMediaGroup()->getKeywords());
	 		$size = $entry->getGphotoSize();
	 		$height = $entry->getGphotoHeight();
	 		$timestamp = $entry->getGphotoTimestamp();
	 		$timestamp = gmdate('c',sprintf("%s",$timestamp)/1000);
	 		$GeoRssWhere= $entry->getGeoRssWhere();
//	 		echo var_dump($GeoRssWhere);
	 		if ($GeoRssWhere=="NULL") $GeoRssWhere=null;
	 		$width = $entry->getGphotoWidth();
	 		$url_thumbnail=$thumbnail[1]->url;
	 		$url_image=$content[0]->url;
	 		$boucle++;
	 		/*
	 		echo "<h2>$summary</h2>\n";
	 		echo "<table><tr><td><a href=\"".$content[0]->url."\" target=\"_blank\"><img src=\"" .
	 		$thumbnail[1]->url . "\"/></a></td>\n";
	 		echo "<td><span>File<span>: $title
      <br /></td>\n";
	 		echo "<td><span>Pris le </span>: $timestamp
      <br /></td>\n";
	 		echo "<span>Size</span>: $size bytes
      ($height x $width) <br />\n";
	 		echo "<span>Tags</span>: $tags
      </td></tr></table>\n";
*/
	 		$sql="insert into individu_google_photo
	 		( id_album,
	 		url_thumbnail,
			url_image,
			titre,
			date_prise_de_vue,
			geo_rss,
			date_synchronisation_google,
  			size,
  			heigth,
  			width,
  			tags,
  			commentaire,
  			id_creation, date_creation, id_modification, date_modification
)
	 		values
	 		($album_id,
	 		'$url_thumbnail',
	 		'$url_image',
	 		'$title',
	 		'$timestamp',
	 		'$GeoRssWhere',
	 		'$updated',
	 		'$size',
	 		'$height',
	 		'$width',
	 		'$tags',
	 		null,
	 		$userid, 
	 		UTC_TIMESTAMP(),
	 		$userid, 
	 		UTC_TIMESTAMP()
	 		
	 		)
	 		";
	 		$dbinsert->query($sql);
	 	}
	 	if ($boucle >= $total) $suivant=false;
	 }
	 
	}
	function delete_album ( $albumid)
	{

		$db = & atkGetDb();
		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$sql="SELECT  id, identifiant_google, code_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$user=$data[0]["identifiant_google"];
		if ($user=="") die("Vous n'avez pas déclaré de compte google");
		$pass=$data[0]["code_google"];

		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata_Photos');
		Zend_Loader::loadClass('Zend_Gdata_Photos_UserQuery');
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Http_Client');
		// connect to service
		$svc = Zend_Gdata_Photos::AUTH_SERVICE_NAME;
		$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $svc);
		$gphoto = new Zend_Gdata_Photos($client);
		$query = $gphoto->newAlbumQuery();
		$query->setAlbumId($albumid);
		$albumentry=$gphoto->getAlbumEntry($query);
		// get photo entry
		// delete entry
		try {
			$albumentry->delete();
		} catch (Zend_Gdata_App_Exception $e) {
			echo "Error: " . $e->getResponse();
		}
		;
	}
	function action_api_google ()
	{
		$feed_type = $this->m_postvars["feed_type"];
		global $g_sessionManager;
		$id_individu = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="SELECT  identifiant_google, code_google
			from individu
		where id=$id_individu ";
		$data=$db->getrows($sql);
		$user=$data[0]["identifiant_google"];
		$pass=$data[0]["code_google"];

		require_once 'modules/include/cleanmyhtml.class.php';
		$cleaning_object = new CleanOutput();
		$cleaning_object->indent = "\t";

		$path = '/home/wikiservas/wikistoma.org/association/modules/library';
		set_include_path(get_include_path() . PATH_SEPARATOR . $path);
		require_once 'Zend/Loader.php';
		Zend_Loader::loadClass('Zend_Gdata');
		Zend_Loader::loadClass('Zend_Gdata_ClientLogin');
		Zend_Loader::loadClass('Zend_Http_Client');
		Zend_Loader::loadClass('Zend_Gdata_Query');
		Zend_Loader::loadClass('Zend_Gdata_Feed');


		if ($feed_type=="contacts")
		{
			$client = Zend_Gdata_ClientLogin::getHttpClient(
			$user, $pass, 'cp');
			$gdata = new Zend_Gdata($client);
			$gdata->setMajorProtocolVersion(3);
			$query = new Zend_Gdata_Query('https://www.google.com/m8/feeds/contacts/default/full');
			$boucle=0;
			$suivant=true;
			$query->maxResults = 1;
			$feed = $gdata->getFeed($query);
			$nombre="". $feed->totalResults ;
			$data=array();
			$obj = array();
			$obj[] ="#";
			$obj[] ="Titre";
			$obj[] ="Prénom";
			$obj[] ="Nom";
			$obj[] ="Nom complet";
			$obj[] ="Né le";
			$obj[] ="Courriel";
			$obj[] ="URL";
			$obj[] ="Rue";
			$obj[] ="Code postal";
			$obj[] ="Ville";
			$obj[] ="Région";
			$obj[] ="Pays";
			$obj[] ="Fixe";
			$obj[] ="Mobile";
			$obj[]="Id_AssoCope";
			$obj[]="Groupe";
			$obj[]="Deleted";
			$obj[]="edited";
			$obj[]="Id";
			$data[]=$obj;
			$iterer=true;
			while ($suivant)
			{
				$query->maxResults = 5;
				$query->startIndex=$boucle+1;
				$query->setParam('orderby', 'lastmodified');
				$query->setParam('sortorder', 'descending');
				$feed = $gdata->getFeed($query);
				$total=$feed->getTotalResults();
				$total = sprintf("%s",$total);
				foreach($feed as $entry){
					$xml = simplexml_load_string($entry->getXML());
					var_dump ($entry->getXML());
					die();
					$dom = new DomDocument;
					$dom->loadXML($entry->getXML());
					$liste=$dom->getElementsByTagName('id');
					foreach($liste as $nombre)
					{
						$id=$nombre->firstChild->nodeValue;
					}


					$obj = array();
					$obj[] =($boucle++)+1;
					$obj[] =utf8_decode($entry->title);
					$obj[] =utf8_decode($xml->name->givenName);
					$obj[] =utf8_decode($xml->name->familyName);
					$obj[] =utf8_decode($xml->name->fullName);
					$obj[] =$xml->birthday['when'];
					$obj[] =$xml->email['address'];
					$obj[] =$xml->website['href'];
					$obj[] =utf8_decode($xml->structuredPostalAddress->street);
					$obj[] =$xml->structuredPostalAddress->postcode;
					$obj[] =utf8_decode($xml->structuredPostalAddress->city);
					$obj[] =utf8_decode($xml->structuredPostalAddress->region);
					$obj[] =utf8_decode($xml->structuredPostalAddress->country);
					$obj[] =$xml->phoneNumber[0];
					$obj[] =$xml->phoneNumber[1];
					$obj[]=$xml->userDefinedField["value"];
					$obj[] =$xml->groupMembershipInfo['href'];
					$obj[] =$xml->groupMembershipInfo['deleted'];
					$obj[] =$xml->edited;
					$obj[] =$id;
					$data[]=$obj;
				}
				//					if ($boucle >= 10) $suivant=false;
				if ($boucle >= $total) $suivant=false;
			}
			$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$res= $tbl->render($data, TBL_HEADER |  TBL_ALTERNATE, "recordlistgg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

		}
		if ($feed_type=="photos")
		{// Parameters for ClientAuth authentication
			$sql="select google_album_checkpoint from app_utilisateur where id=$userid";
			$data1=$db->getRows($sql);
			$album_checkpoint=$data1[0]["google_album_checkpoint"];
			if ($album_checkpoint==0)
			{$sql="delete from individu_google_feed where type_feed='2' and id_individu=$id_individu";
			$db->query($sql);
			$boucle=0;
			}
			else 
			{$boucle=$album_checkpoint;}
			
			Zend_Loader::loadClass('Zend_Gdata_Photos');
			Zend_Loader::loadClass('Zend_Gdata_Photos_UserQuery');
			$service = Zend_Gdata_Photos::AUTH_SERVICE_NAME;
			$client = Zend_Gdata_ClientLogin::getHttpClient($user, $pass, $service);
			$service = new Zend_Gdata_Photos($client);
			$query = new Zend_Gdata_Photos_UserQuery();
			$query->setUser("guy.gourmellet");
			$query->maxResults = 1;
			$feed = $service->getUserFeed(null, $query);
			$total=$feed->getTotalResults();
			$total = sprintf("%s",$total);
			$data=array();
//			$boucle=0;
			$suivant=true;
			$obj = array();
			$obj[] ="#";
			$obj[] ="Titre";
			$obj[] ="Publié le";
			$obj[] ="Mis à jour le";
			$obj[] ="Photos";
			$obj[] ="Taille";
			$obj[] ="Auteur";
			$obj[] ="Droits";
			$obj[] ="Id";
			while ($suivant)
			{

				$query->setUser("guy.gourmellet");
				$query->maxResults = 50;
				$query->startIndex=$boucle+1;
				$feed = $service->getUserFeed(null, $query);

				//		 $obj[]="Id_AssoCope";
				$data[]=$obj;
				foreach($feed as $entry){

					$dom = new DomDocument;
					$dom->loadXML($entry->getXML());

					$liste=$dom->getElementsByTagName('numphotos');
					foreach($liste as $nombre)
					{
						$numphotos=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('published');
					foreach($liste as $nombre)
					{
						$published=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('updated');
					foreach($liste as $nombre)
					{
						$updated=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('author');
					foreach($liste as $nombre)
					{
						$author=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('rights');
					foreach($liste as $nombre)
					{
						$rights=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('id');
					foreach($liste as $nombre)
					{
						$id=$nombre->firstChild->nodeValue;
					}

					$liste=$dom->getElementsByTagName('bytesUsed');
					foreach($liste as $nombre)
					{
						$bytesUsed=$nombre->firstChild->nodeValue;
					}
					$liste=$dom->getElementsByTagName('link');

					foreach ($liste as $element) {
						if($element->hasAttributes()){
							$attributes = $element->attributes;

							if(!is_null($attributes)){
								foreach ($attributes as $index=>$attr){
									if($attr->name == 'rel'){
										$relvalue = $attr->value;
									}
									if($attr->name == 'href'){
										$hrefvalue = $attr->value;
									}
								}
								if ($relvalue=="alternate") $href=$hrefvalue;
							}

						}
					}
					$obj = array();
					$obj[] =($boucle++)+1;
					$obj[] =utf8_decode($entry->title);
					$obj[] =$published;
					$obj[] =$updated;
					$obj[] =$numphotos;
					$obj[] =$bytesUsed;
					$obj[] =utf8_decode($author);
					$obj[] =$rights;
					$obj[] =$id;
					//				 $obj[]=$xml->userDefinedField["value"];
					$data[]=$obj;
					$titre=escapeSQL(utf8_decode($entry->title));
					$insertsql=" insert into individu_google_feed
				(id_individu,
				compte_google,
				type_feed,
				id_individu_contact,
				album,
				lien_album,
				date_publication_album,
				
				nombre_de_photos,
				taille_octets,
				url_google,
				date_synchronisation_google,
				commentaire,
				id_creation,
				date_creation,
				id_modification,
				date_modification)
				values
				(
				'$id_individu',
				'$user',
				'2',
				null,
				'$titre',
				'$href',
				'$published',
				
				'$numphotos',
				'$bytesUsed',
				'$id',
				'$updated',
				null,
				'$userid', UTC_TIMESTAMP(), '$userid',  UTC_TIMESTAMP()			
				)";
					$db->query($insertsql);
					$sql="update app_utilisateur set google_album_checkpoint=$boucle where id=$userid";
					$db->query($sql);

					/*
					 $photos = new Zend_Gdata_Photos($client);

					 $albumQuery = new Zend_Gdata_Photos_AlbumQuery;
					 $albumQuery->setUser($user);
					 $albumQuery->setAlbumId($albumId);
					 $albumQuery->setType('entry');

					 $entry = $photos->getAlbumEntry($albumQuery);

					 $photos->deleteAlbumEntry($entry, true);

					 outputUserFeed($client, $user);
					 */
					
			$this->action_photos_album($id,$client);

				}
				if ($boucle >= $total ) $suivant=false;
			}
			$sql="update app_utilisateur set google_album_checkpoint='0' where id=$userid";
					$db->query($sql);
			echo "Import des liens photos totalement terminé.";
			die();
			
			/*$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$res= $tbl->render($data, TBL_HEADER |  TBL_ALTERNATE, "recordlistgg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
*/

		}
		if ($feed_type=="contacts_photos")
		{
			// query.KindParameter = "user";
			$client = Zend_Gdata_ClientLogin::getHttpClient(
			$user, $pass, 'cp');
			$gdata = new Zend_Gdata($client);
			$gdata->setMajorProtocolVersion(3);
			$query = new Zend_Gdata_Query('https://picasaweb.google.com/data/feed/api/user/'.$user.'/contacts');
			$boucle=0;
			$suivant=true;
			$query->maxResults = 50;
			$feed = $gdata->getFeed($query);
			$total=$feed->getTotalResults();
			$nombre = sprintf("%s",$total);

			$data=array();
			$obj = array();
			$obj[] ="#";
			$obj[] ="Titre";
			$obj[] ="Prénom";
			$obj[] ="Nom";
			$obj[] ="Nom complet";
			$obj[] ="Né le";
			$obj[] ="Courriel";
			$obj[] ="URL";
			$obj[] ="Rue";
			$obj[] ="Code postal";
			$obj[] ="Ville";
			$obj[] ="Région";
			$obj[] ="Pays";
			$obj[] ="Fixe";
			$obj[] ="Mobile";
			$obj[]="Id_AssoCope";
			$obj[]="Id";
			$data[]=$obj;
			$iterer=true;
			while ($suivant)
			{
				$query->maxResults = 5;
				$query->startIndex=$boucle+1;
				$query->setParam('orderby', 'lastmodified');
				$query->setParam('sortorder', 'descending');
				$feed = $gdata->getFeed($query);
				$total=$feed->getTotalResults();
				$total = sprintf("%s",$total);
				foreach($feed as $entry){
					$xml = simplexml_load_string($entry->getXML());
					$dom = new DomDocument;
					$dom->loadXML($entry->getXML());
					$liste=$dom->getElementsByTagName('id');
					foreach($liste as $nombre)
					{
						$id=$nombre->firstChild->nodeValue;
					}


					$obj = array();
					$obj[] =($boucle++)+1;
					$obj[] =utf8_decode($entry->title);
					$obj[] =utf8_decode($xml->name->givenName);
					$obj[] =utf8_decode($xml->name->familyName);
					$obj[] =utf8_decode($xml->name->fullName);
					$obj[] =$xml->birthday['when'];
					$obj[] =$xml->email['address'];
					$obj[] =$xml->website['href'];
					$obj[] =utf8_decode($xml->structuredPostalAddress->street);
					$obj[] =$xml->structuredPostalAddress->postcode;
					$obj[] =utf8_decode($xml->structuredPostalAddress->city);
					$obj[] =utf8_decode($xml->structuredPostalAddress->region);
					$obj[] =utf8_decode($xml->structuredPostalAddress->country);
					$obj[] =$xml->phoneNumber[0];
					$obj[] =$xml->phoneNumber[1];
					$obj[]=$xml->userDefinedField["value"];
					$obj[] =$id;
					$data[]=$obj;
				}
				if ($boucle >= $nombre) $suivant=false;
			}
			$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$res= $tbl->render($data, TBL_HEADER |  TBL_ALTERNATE, "recordlistgg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

		}



	}





}
?>