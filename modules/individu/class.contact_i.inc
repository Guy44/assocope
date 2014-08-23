<?php
useattrib("development.atgtextlibelleattribute");

useattrib("development.atgFileManyToOneRelation");
class contact_i extends assMetaNode {
	var $table = "individu_contact";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "commentaire", AF_READONLY);
	}
	function contact_i() {
		$this->atkMetaNode();
		$this->setSecurityAlias("individu.individu");
		$this->atkNode("contact_i", NF_ADD_LINK | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (

						"id_contact",
						"id_type_contact",
						"descripteur_contact",
						"descripteur_contenu_contact",
						"titre",
						"date_prevue",
						"date_realisee",


						"id_organisme_contactant",
						"id_individu",
						"id_organisme_contacte",


						"retour_o_n",
						"id_envoi_groupe",
						//				"documents_organismes",
						//				"documents_individus",


						"attente_reponse_o_n",

						"courriel",
						"date_dernier_courriel",
						"commentaire_html",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Documents" => array (
						"id_document_organisme",
						"id_document_organisme_1",
						"id_document_organisme_2",
						"id_document_individu",
						"id_document_individu_1",
						"id_document_individu_2"
				)
				,
				"Rapport activité" => array (
						"id_rapport_activite"
				)
				

		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_contact",null,AF_COMPACT),null,5);
		$this->add(new atkDummyAttribute("descripteur_contenu_contact"),null,10);
		$this->add(new atgTextLibelleAttribute("titre", AF_SEARCHABLE | AF_OBLIGATORY),100);
		$this->add(new atkManyToOneRelation("id_contact", "individu.individu", AF_SEARCHABLE   |AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),20);
		$this->add(new atkManyToOneRelation("id_organisme_contactant", "organisme.organisme", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),210);

		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE  | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),25);
		$this->add(new atkManyToOneRelation("id_organisme_contacte", "organisme.organisme", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),310);
		$this->add(new atkManyToOneRelation("id_type_contact", "table.contact", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK| AF_FORCE_LOAD),500);
		$this->add(new atkDummyAttribute("contenu", "contenu", AF_NOLABEL), NULL, 101);

		$this->add(new atkBoolAttribute("retour_o_n"),400);
		$this->add(new atkManyToOneRelation("id_envoi_groupe", "individu.envoi_groupe", AF_SEARCHABLE |  AF_RELATION_AUTOLINK),590);
		$this->add(new atgFileManyToOneRelation("id_document_organisme", "organisme.document",  AF_HIDE_LIST | AF_FORCE_LOAD  |AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),600);
		$this->add(new atgFileManyToOneRelation("id_document_organisme_1", "organisme.document",      AF_HIDE_LIST | AF_FORCE_LOAD    |    AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),700);
		$this->add(new atgFileManyToOneRelation("id_document_organisme_2", "organisme.document", AF_HIDE_LIST | AF_FORCE_LOAD | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),800);
		//		$this->addFieldSet("documents_organismes"," [id_document_organisme.field] [id_document_organisme_1.field] [id_document_organisme_2.field]",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL,850 );
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $data[0]["idutilisateur"];
		$c120 = $this->add(new atgFileManyToOneRelation("id_document_individu", "individu.document_i", AF_HIDE_LIST | AF_FORCE_LOAD | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),900);
		$c120->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		$c121 = $this->add(new atgFileManyToOneRelation("id_document_individu_1", "individu.document_i", AF_HIDE_LIST | AF_FORCE_LOAD | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1000);
		$c121->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		$c122 = $this->add(new atgFileManyToOneRelation("id_document_individu_2", "individu.document_i", AF_HIDE_LIST | AF_FORCE_LOAD | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1100);
		$c122->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		//		$this->addFieldSet("documents_individu","[id_document_individu.field] [id_document_individu_1.field] [id_document_individu_2.field]",AF_HIDE_LIST|AF_HIDE_SEARCH,NULL,860 );

		$this->add(new atkDateAttribute("date_prevue", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING | AF_OBLIGATORY| AF_FORCE_LOAD),105);
		//				$this->add(new atkDateAttribute("date_prevue", "d F Y","d F Y", 0, AF_DATE_STRING | AF_OBLIGATORY),505);
		$this->add(new atkBoolAttribute("attente_reponse_o_n",AF_FORCE_LOAD),508);
		$this->add(new atkDateAttribute("date_realisee", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING| AF_FORCE_LOAD),110);
		//				$this->add(new atkDateAttribute("date_realisee", "d F Y","d F Y", 0, AF_DATE_STRING ),510);
		$courriel = & $this->add(new atkAttribute("courriel", AF_SEARCHABLE | AF_READONLY),350);
		$courriel->setForceUpdate(true);
		$courriel->setForceInsert(true);
		$date_dernier_courriel = & $this->add(new atkAttribute("date_dernier_courriel", AF_SEARCHABLE | AF_READONLY),360);
		$date_dernier_courriel->setForceUpdate(true);
		$date_dernier_courriel->setForceInsert(true);
		$this->add(new atkfckattribute("commentaire_html", "", AF_HIDE_LIST | AF_FORCE_LOAD, array (
				'ToolbarSet' => 'Default',
				'Width' => '100%',
				'Height' => '300px'
		)),550);
	$rapp=$this->add(new atkOneToManyRelation("id_rapport_activite", "individu.activite_i" ,"id_individu_contact", null),NULL,800);
		$this->m_securityMap["organisme_contactant"] = "view";
		$this->m_securityMap["organisme_contacte"] = "view";
		$this->m_securityMap["clore"] = "view";
		$this->m_securityMap["rouvrir"] = "view";
		$this->m_securityMap["attente_reponse"] = "view";
		$this->m_securityMap["supprimer_attente"] = "view";
		$this->m_securityMap["admin_liste"] = "view";
		$rapp->setDestinationFilter("[pk]");
		$rapp->setUseFilterForAddLink(true);
		$this->setOrder("date_prevue desc");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,15 );
	}
	function descripteur_contact_display($record, $mode)
	{
		return $this->decoupe_affichage_colonne($this->descripteur_contact($record["id"], 'o'),200);
	}
	function descripteur_contenu_contact_display($record, $mode)
	{
		return $this->decoupe_affichage_colonne($this->descripteur_contenu_contact($record["id"], 'o'),200);
	}

	function id_contact_display($record, $mode) {
		(!empty($record["id_contact"])) ? $retour=$this->descripteur_individu($record["id_contact"]["id"],'n').'<br />' : $retour="";
		(!empty($record["id_organisme_contactant"])) ? $retour.=$this->descripteur_organisme($record["id_organisme_contactant"]["id"],'n') : $retour.="";
		return $retour;
	}
	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n').'<br />' : $retour="";
		(!empty($record["id_organisme_contacte"])) ? $retour.=$this->descripteur_organisme($record["id_organisme_contacte"]["id"],'n') : $retour.="";

		return $retour;
	}
	function id_organisme_contactant_display($record, $mode) {
		(!empty($record["id_organisme_contactant"])) ? $retour=$this->descripteur_organisme($record["id_organisme_contactant"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_contacte_display($record, $mode) {
		(!empty($record["id_organisme_contacte"])) ? $retour=$this->descripteur_organisme($record["id_organisme_contacte"]["id"],'n') : $retour="";
		return $retour;
	}

	function getFormButtons($mode, $record) {
		// Get the normal buttons
		$buttons = parent :: getFormButtons($mode, $record);
		if ($this->m_postvars["atgemail"]!="")
		{
			array_unshift($buttons, '<input type="submit" class="btn_saveandmail" name="saveandmail" value="' . atktext('Envoyer/Sauvegarder', "gg") . '">');
		}
		return $buttons;
	}
	function preAdd(& $record) {
		if ($this->m_postvars['saveandmail']) {
			$this->envoyer_message($record);
			//	$this->redirect();
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		if ($this->m_postvars['saveandmail']) {
			$this->envoyer_message($record);
			//	$this->redirect();
		}
		parent :: preUpdate($record);
	}
	function action_update(& $handler) {
		// Trick the update handler into thinking that when we clicked
		// the saveandsayhello button, we also clicked the save and close button.
		// You could also use atknoclose if you just want to save
		if ($handler->m_postvars['saveandmail'])
			$handler->m_postvars['atksaveandclose'] = 1;
		return $handler->action_update();
	}
	function confirmViewText($atkselector) {
		return "Etes-vous sûr de vouloir envoyer ce message à ?";
	} // end function
	function envoyer_message(& $record) {
		// Todo GG
		// Valide même en add
		// Tester que email existe pour utilisateur et destinataire
		// Ne pas renvoyer si déjà envoyé
		// noter date envoi, email à, email réponse
		// utilise phpmailer
		/*
		if (empty($this->m_postvars['confirm']) && empty($this->m_postvars['cancel']) &&
				empty($this->m_postvars['atkcancel']))
		{
		$page = &$this->getPage();

		// add the confirmation form to the page
		$page->addContent($this->confirmAction($this->m_postvars['atkselector'], "view", false, TRUE));
		return;
		}
		elseif (!empty($this->m_postvars['cancel']))
		{
		// Confirmation page was displayed and 'cancel' was clicked
		$location = $this->feedbackUrl("view", ACTION_CANCELLED);
		$this->redirect($location);
		return;
		}
		*/
		$mailer = & atknew("atk.utils.atkmailer");
		// Récupérer courriel, nom, prénom de l'utilisateur qui exécute l'application.
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$datau = $db->getrows("SELECT au.id_individu as idutilisateur, au.copie_courriel_o_n as copie, au.courriel_copie as courriel_copie " . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $datau[0]["idutilisateur"];
		//print_r($record);
		//die();
		$data = $db->getrows("SELECT i.courriel," . "i.prenom, i.nom " . " from individu i " . " where i.id =" . $idutilisateur . " ");
		$mailer->AddReplyTo($data[0]["courriel"], $name = $data[0]["prenom"] . " " . $data[0]["nom"]);
		//		$mailer->From = "guy.gourmellet@gmail.com";
		$mailer->FromName = $data[0]["prenom"] . " " . $data[0]["nom"];
		$adressereponse = $data[0]["courriel"];
		if ($datau[0]["copie"]=='1' && $datau[0]["courriel_copie"]!="")
		{
			$mailer->AddBCC($datau[0]["courriel_copie"]);
		}
		//$mailer->From=$data[0]["courriel"];
		// Récupérer courriel, nom, prénom de l'individu destinataire du message
		$data = $db->getrows("SELECT i.courriel," . "i.prenom, i.nom " . " from individu i " . " where i.id =" . $record["id_individu"]["id"] . " ");
		$mailer->AddAddress($data[0]["courriel"], $data[0]["prenom"] . " " . $data[0]["nom"]);
		$temoin = atkconfig("maildemande");
		$mailer->AddBCC($temoin);

		$mailer->IsHTML(true);
		//		$mailer->Body ="<b>Utiliser : ".$adressereponse." comme adresse de réponse
		//<br>";
		$mailer->Body = $record["commentaire"];
		$mailer->Body .= $record["commentaire_html"];
		$mailer->Subject = $record["titre"];
		$piecesjointes="";
		if ($record["id_document_organisme"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from organisme_document where id =" . $record["id_document_organisme"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {

				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_organisme_1"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from organisme_document where id =" . $record["id_document_organisme_1"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {

				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_organisme_2"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from organisme_document where id =" . $record["id_document_organisme_2"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_individu"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from individu_document where id =" . $record["id_document_individu"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_individu_1"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from individu_document where id =" . $record["id_document_individu_1"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_individu_2"]["id"] > 0) {
			$data = $db->getrows("SELECT libelle, file_name, file_size, file_content,file_extension, contenu_html
					from individu_document where id =" . $record["id_document_individu_2"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
				$piecesjointes.= $data[0]["file_name"]." : ".$data[0]["libelle"]."<br />";
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		$data[0]["file_content"]="";
		if ($piecesjointes!="")
		{
			$piecesjointes="<b>Pièces jointes :</b> <br> </br>".$piecesjointes;
			$mailer->Body .=$piecesjointes;
		}
		// envoyer le message
		$mailer->Send();
		$record["date_dernier_courriel"] = gmdate(c);
		//		$this->p($record);
	}
	function dispatch(& $postvars, $fullpage = true) {

		if ($postvars['atkaction'] != 'admin') {

			$filtre = $postvars["atkfilter"];
			if (stristr($filtre, ' or ') != false) {
				unset ($postvars["atkfilter"]);
			}

			if (stristr($filtre, '%09or%20') != false) {
				unset ($postvars["atkfilter"]);
			}
		}
		if ($postvars['atkaction'] == 'edit' || $postvars['atkaction'] == 'view' )
		{
			unset ($postvars["atkfilter"]);
		}

		$this->addFilter($postvars["atkfilter"]);
		//	unset ($postvars["atkfilter"]);

		return parent :: dispatch($postvars, $fullpage);
	}

	function initial_values() {
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT au.id_individu as idutilisateur, i.signature_courriel
				as signature_courriel from app_utilisateur au, individu i
		  where au.id =" . $id . " and au.id_individu=i.id");
		$idutilisateur = $data[0]["idutilisateur"];

		if ($this->m_postvars["atgemail"]!="")
		{
			$init_vals["commentaire_html"]=$data[0]["signature_courriel"];
		}

		$init_vals["date_prevue"]["day"]= gmdate('d');
		$init_vals["date_prevue"]["month"]= gmdate('m');
		$init_vals["date_prevue"]["year"]= gmdate('Y');
		$idcontactant=$this->m_postvars["idcontactant"];
		$idcontacte=$this->m_postvars["idcontacte"];
		$filtre=$this->m_postvars["atkfilter"];
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $data[0]["idutilisateur"];
		if (!empty($idcontactant))
		{
			$init_vals["id_contact"]["id"] = $idcontactant;

		}

		if (!empty($idcontacte))
		{
			$init_vals["id_individu"]["id"] = $idcontacte;

		}
		if (!empty ($this->m_postvars["atgemail"])) {
			$init_vals["courriel"] = $this->m_postvars["atgemail"];
			$init_vals["id_type_contact"] = '4';
		}
		//$this->p($this->m_postvars);
		if (empty ($idcontactant) and empty($idcontacte) and  substr_count($filtre, "individu_contact.id_contact=") == 1)
		{
			$init_vals["id_individu"]["id"] = $idutilisateur;
		}
		if (empty ($idcontactant) and empty($idcontacte) and  substr_count($filtre, "individu_contact.id_individu=") == 1)
		{
			$init_vals["id_contact"]["id"] = $idutilisateur;
		}

		/*	$user = getUser();
		 $id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $data[0]["idutilisateur"];
		$selecteur = $this->m_postvars["atkselector"];
		$init_vals = array ();
		if (isset ($selecteur)) {
		if (substr_count($selecteur, "id_contact") == 1) {
		$init_vals["id_contact"]["id"] = $idutilisateur;
		}
		if (substr_count($selecteur, "id_individu") == 1) {
		$init_vals["id_individu"]["id"] = $idutilisateur;
		}
		}
		if (($this->m_postvars["atgtable"] == 'individu')) {
		if ($this->m_postvars["atgsens"] == 'to') {
		$init_vals["id_contact"]["id"] = $idutilisateur;
		$init_vals["id_individu"]["id"] = $this->m_postvars["atgvaleur"];
		if (isset ($this->m_postvars["atgemail"])) {
		$init_vals["courriel"] = $this->m_postvars["atgemail"];
		$init_vals["id_type_contact"] = '4';
		}
		} else {
		$init_vals["id_contact"]["id"] = $this->m_postvars["atgvaleur"];
		$init_vals["id_individu"]["id"] = $idutilisateur;
		}
		}
		*/
		return $init_vals;
	}
	function id_rapport_activite_display($record, $mode)
	{
		$attribute = &$this->getAttribute("id_rapport_activite");
		$original = $attribute->display($record, $mode);

		if ($original==atktext("none"))
		{
			return "";
			/*return href(dispatch_url("individu.activite_i", "add", array (
				'atkfilter' => "individu_activite.id_individu_contact='" . $record['id'] . "'"
			), "dispatch.php"), text("Créer"), SESSION_DEFAULT);
			*/
		}
		else
		{return href(dispatch_url("individu.activite_i", "admin", array (
				'atkfilter' => "individu_activite.id_individu_contact='" . $record['id'] . "'"
		), "dispatch.php"), text("Ouvrir"), SESSION_DEFAULT);
		}
	}

	function descriptor_def() {
		return "[date_prevue.year]-[date_prevue.month]-[date_prevue.day] - [titre]";
	}

	public function recordActions($record, $actions, &$mraactions)
	{
		$mraactions = array ();
		$mraactions['delete'] = "delete";
		$mraactions['clore'] = "clore";
		$mraactions['rouvrir'] = "rouvrir";
		$mraactions['attente_reponse'] = "attente_reponse";
		$mraactions['supprimer_attente'] = "supprimer_attente";
		$mraactions['organisme_contactant'] = "organisme_contactant";
		$mraactions['organisme_contacte'] = "organisme_contacte";
	}

	public function getCustomMraHtml()
	{
		$list = $this->getAttribute('id_organisme_contactant')->edit(null, null, null);
		return $list;
	}

	public function action_organisme_contactant()
	{

		$organisme = $this->getAttribute('id_organisme_contactant')->fetchValue($this->m_postvars);
		if (empty($organisme)) return;
		$idorganisme=$organisme["id"];
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set id_organisme_contactant='".$idorganisme."',
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}

	public function action_organisme_contacte()
	{
		$organisme = $this->getAttribute('id_organisme_contactant')->fetchValue($this->m_postvars);
		if (empty($organisme)) return;
		$idorganisme=$organisme["id"];
		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set id_organisme_contacte='".$idorganisme."',
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP()  where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_clore()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set date_realisee=UTC_DATE(),
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_rouvrir()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set date_realisee=NULL,
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_attente_reponse()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set attente_reponse_o_n='1',
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}
	public function action_supprimer_attente()
	{

		$db = & atkGetDb();
		global $g_user;
		$userutilisateur = $g_user["id"];
		foreach ($this->m_postvars['atkselector'] as $pk)
		{
			$sql="UPDATE individu_contact set attente_reponse_o_n='0',
					id_modification='".$userutilisateur."',
							date_modification= UTC_TIMESTAMP() where ".$pk."";
			$db->query($sql);
		}
		$this->redirect();
	}

	function adminFooter() {
		$retour=parent::adminfooter();

		$legende = 'Légende des couleurs : ';

		/*		$legende .= '<font color="Pink"> <b> Contact prévu ';
		 $legende .= '<font color="' . $this->couleursemaine . '"> <b> Contact en retard ';
		$legende .= '<font color="' . $this->couleurmois . '"> <b> Contact en attente de réponse';
		$legende .= '<font color="' . $this->couleurplusmois . '"> <b> Contact clos';
		*/
		$legende .= '<font color="' . $this->couleurarchive . '"> <b> Contact clos';
		$legende .= '<font color="' . $this->couleursemaine . '"> <b> Contact à traiter en urgence ';
		$legende .= '<font color="' . $this->couleurmois . '"> <b> Contact prévu dans le mois';
		$legende .= '<font color="' . $this->couleurplusmois . '"> <b> Contact prévu au delà du mois';
		$legende .= '<font color="Yellow"> <b> Contact en attente de réponse';

		return $legende . $retour;

	}
	function action_admin($handler) {

		global $config_recordsperpage;
		$config_recordsperpage = 50;
		//		$this->p($postvars["atkfilter"]);
		return $handler->action_admin();
	}

	function rowColor($record)
	{
		include_once (moduleDir("utils") . "class.dateutil.inc");
		$curdate = date("Ymd");
		$dateprevue = $record['date_prevue']["year"] . $record['date_prevue']["month"] . $record['date_prevue']["day"];
		$date_realisee = $record["date_realisee"];
		$attente_reponse=$record["attente_reponse_o_n"];
		if ($attente_reponse=='1')
		{
			return "Yellow";
		}
		if ($date_realisee != "")
		{
			return $this->couleurarchive;
		}
		if (dateutil :: date_diff($curdate, $dateprevue) < 2)
			return $this->couleursemaine;
		if (dateutil :: date_diff($curdate, $dateprevue) > 1 and dateutil :: date_diff($curdate, $dateprevue) < 31) {
			return $this->couleurmois;
		} else {
			return $this->couleurplusmois;
		}
	}
	/*	 function date_prevue_display($record, $mode)
	 {
	return $this->dateatktodb($record["date_prevue"])."<br />".$this->dateatktodb($record["date_realisee"]);
	}
	*/
	/*	 function id_individu_display($record, $mode)
	 {
	$attribute = &$this->getAttribute("id_individu");
	$original = $attribute->display($record, $mode);
	$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone_fixe, telephone_mobile, courriel from individu  where id =" . $record["id_individu"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone_fixe"];
	$telephone_mobile = $data[0]["telephone_mobile"];
	$courriel = $data[0]["courriel"];
	*/
	/* if ($courriel != "") {
	 $courriel1=href(dispatch_url("individu.contact_i", "add", array (
				"atgemail" => $courriel,
				"atgtable" => $this->table,
				"atgcle" => $record["id_individu"]["id"],
				"atgvaleur" => $record["id_individu"]["id"]
	 )), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
	}
	*/
	/*   return $original."<br />".$telephone_fixe." - ".$telephone_mobile."<br />".$courriel;
	 }

	function id_contact_display($record, $mode)
	{
	$attribute = &$this->getAttribute("id_contact");
	$original = $attribute->display($record, $mode);
	$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone_fixe, telephone_mobile, courriel from individu  where id =" . $record["id_contact"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone_fixe"];
	$telephone_mobile = $data[0]["telephone_mobile"];
	$courriel = $data[0]["courriel"];
	*/
	/* if ($courriel != "") {
	 $courriel1=href(dispatch_url("individu.contact_i", "add", array (
				"atgemail" => $courriel,
				"atgtable" => $this->table,
				"atgcle" => $record["id_contact"]["id"],
				"atgvaleur" => $record["id_contact"]["id"]
	 )), atktext($record["courriel"], "core"), SESSION_NEW, false, 'target="_blank"');
	}
	*/
	/*
	 return $original."<br />".$telephone_fixe." - ".$telephone_mobile."<br />".$courriel;
	}
	*/

	function contenu_display($record, $mode)
	{
		$retour=null;
		//	print_r ($record);
		//	die();

		if ( strlen($record["commentaire_html"])>0)
		{
			$retour= href(dispatch_url("individu.contact_i","edit",array("atkselector"=>$this->primaryKey($record))),
					' <font color="ForestGreen"> <b>Texte</b><br />', SESSION_NESTED,
					false);


		}
		if ( $record["id_document_organisme"]!=null)
		{
			$retour .= $this->getAttribute("id_document_organisme")->display($record, $mode)."<br />" ;
		}
		if ( $record["id_document_organisme_1"]!=null)
		{
			$retour .= $this->getAttribute("id_document_organisme_1")->display($record, $mode)."<br />" ;
		}
		if ( $record["id_document_organisme_2"]!=null)
		{
			$retour .= $this->getAttribute("id_document_organisme_2")->display($record, $mode)."<br />" ;
		}
		if ( $record["id_document_individu"]!=null)
		{
			$retour .= $this->getAttribute("id_document_individu")->display($record, $mode)."<br />" ;
		}
		if ( $record["id_document_individu_1"]!=null)
		{
			$retour .= $this->getAttribute("id_document_individu_1")->display($record, $mode)."<br />" ;
		}
		if ( $record["id_document_individu_2"]!=null)
		{
			$retour .= $this->getAttribute("id_document_individu_2")->display($record, $mode)."<br />" ;
		}
		return $retour;
	}
	/*	 function id_organisme_contactant_display($record, $mode)
	 {
	$attribute = &$this->getAttribute("id_organisme_contactant");
	$original = $attribute->display($record, $mode);
	if ($record["id_organisme_contactant"]["id"]!="")
	{		$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone, courriel from organisme  where id =" . $record["id_organisme_contactant"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone"];
	$courriel = $data[0]["courriel"];
	}
	return $original."<br />".$telephone_fixe."<br />".$courriel;
	}
	function id_organisme_contacte_display($record, $mode)
	{
	$attribute = &$this->getAttribute("id_organisme_contacte");
	$original = $attribute->display($record, $mode);
	if ($record["id_organisme_contacte"]["id"]!="")
	{ 		$db = & atkGetDb();
	$data = $db->getrows("SELECT telephone, courriel from organisme  where id =" . $record["id_organisme_contacte"]["id"] . " ");
	$telephone_fixe = $data[0]["telephone"];
	$courriel = $data[0]["courriel"];
	}
	return $original."<br />".$telephone_fixe."<br />".$courriel;
	}
	*/
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace(" OU ", " OR ", $this->m_postvars["atkfilter"]);
		$this->m_filters=array();
		$data = $db->getrows("select nom from organisme where id=$id_organisme");
		$nom_organisme=$data[0]["nom"];
	
		
		/*

  `id_envoi_groupe` int(11) unsigned DEFAULT NULL,
  `retour_o_n` enum('0','1') COLLATE latin1_general_ci NOT NULL DEFAULT '0',
  `courriel` varchar(200) COLLATE latin1_general_ci DEFAULT NULL,
  `date_dernier_courriel` datetime DEFAULT NULL,
  `commentaire` text COLLATE latin1_general_ci,

  `id_document_organisme` int(11) unsigned DEFAULT NULL,
  `id_document_organisme_1` int(11) unsigned DEFAULT NULL,
  `id_document_organisme_2` int(11) unsigned DEFAULT NULL,
  `id_document_individu` int(11) unsigned DEFAULT NULL,
  `id_document_individu_1` int(11) unsigned DEFAULT NULL,
  `id_document_individu_2` int(11) unsigned DEFAULT NULL,

		 */
		$sql="SELECT
		individu_contact.id as id_entite,
		individu_contact.titre,
		ict.id as id_individu_contactant,
		ice.id as id_individu_contacte,
		oct.id as id_organisme_contactant,
		oce.id as id_organisme_contacte,
		tc.libelle as libelle_contact,
		individu_contact.date_prevue,
		individu_contact.attente_reponse_o_n,
		individu_contact.date_realisee
		from
		individu_contact 
		LEFT JOIN individu ict ON individu_contact.id_individu=ict.id
		LEFT JOIN individu ice ON individu_contact.id_contact=ice.id
		LEFT JOIN type_contact tc ON individu_contact.id_type_contact=tc.id
		LEFT JOIN organisme oct ON individu_contact.id_organisme_contactant=oct.id
		LEFT JOIN organisme oce ON individu_contact.id_organisme_contacte=oce.id
		where
		$filtre
		order by individu_contact.date_prevue desc	";
//		$this->p($sql);
		$data=$db->getrows($sql);
		$res2= '<table class="toc sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Type</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Libellé</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Contenu</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>De</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>à</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Prévu le</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Attente de réponse</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'><center><b>Fait le</center></b>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$idindividus.=$data[$i]["id_individu_contactant"].",";
			$idindividus.=$data[$i]["id_individu_contacte"].",";
			$res2.= "<tr><td>".($i+1);
			$res2.='</td><td>'.$data[$i]["libelle_contact"];
			$res2.='</td><td>'.$data[$i]["titre"];
			$res2.='</td><td>'.$this->descripteur_contenu_contact($data[$i]["id_entite"],'n','o');
			$de=$this->descripteur_individu_sans_lien($data[$i]["id_individu_contacte"])."<br/>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_contactant"]);
			$res2.='</td><td>'.$de;
			$vers=$this->descripteur_individu_sans_lien($data[$i]["id_individu_contactant"])."<br/>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_contacte"]);
			$res2.='</td><td>'.$vers;
			$res2.='</td><td>'.$data[$i]["date_prevue"];
			($data[$i]["attente_reponse_o_n"]=="1") ? $prevu="Oui" : $prevu="Non";
			$res2.='</td><td>'.$prevu;
			$res2.='</td><td>'.$data[$i]["date_realisee"];
		$res2.='</td><td>'.$this->descripteur_module_estampillage($data[$i]["id_entite"], 'n');
//			$res2.='</td><td> ';
			$res2.='</td></tr>';
		}
//		echo "fini";die();
		
	
		
		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Contacts"." </b>- ".$nom_organisme."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
			

		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);

	}

}
?>