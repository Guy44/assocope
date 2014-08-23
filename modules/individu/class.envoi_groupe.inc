<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgFileManyToOneRelation");
class envoi_groupe extends assMetaNode {
	var $table = "individu_envoi_groupe";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", "commentaire", AF_READONLY);
	}
	function envoi_groupe() {
		$this->atkMetaNode();
		$this->setSecurityAlias("individu.individu");
		$this->atkNode("envoi_groupe", NF_ADD_LINK | NF_MRA);
		$this->add(new atgTextLibelleAttribute("objet", AF_SEARCHABLE | AF_OBLIGATORY),100);
		$this->add(new atkManyToOneRelation("id_type_envoi_groupe", "table.type_envoi_groupe", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ),200);
		$this->add(new atkManyToOneRelation("id_utilisateur", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
		$this->add(new atkManyToOneRelation("id_individu_emetteur", "individu.individu", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
		$this->add(new atkManyToOneRelation("id_organisme_emetteur", "organisme.organisme", AF_SEARCHABLE |  AF_RELATION_AUTOLINK| AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),500);
		$this->add(new atkfckattribute("contenu_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
		)),550);
		$this->add(new atgFileManyToOneRelation("id_document_organisme", "organisme.document", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),600);
		$this->add(new atgFileManyToOneRelation("id_document_organisme_1", "organisme.document", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),700);
		$this->add(new atgFileManyToOneRelation("id_document_organisme_2", "organisme.document", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),800);
		$this->addFieldSet("documents_organismes","[id_document_organisme.field] [id_document_organisme_1.field] [id_document_organisme_2.field]",AF_SEARCHABLE|AF_HIDE_SEARCH,NULL,850 );
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $data[0]["idutilisateur"];
		$c120 = $this->add(new atgFileManyToOneRelation("id_document_individu", "individu.document_i", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),900);
		$c120->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		$c121 = $this->add(new atgFileManyToOneRelation("id_document_individu_1", "individu.document_i", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1000);
		$c121->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		$c122 = $this->add(new atgFileManyToOneRelation("id_document_individu_2", "individu.document_i", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1100);
		$c122->addDestinationFilter("individu_document.id_individu= '$idutilisateur'");
		$this->addFieldSet("documents_individu","[id_document_individu.field] [id_document_individu_1.field] [id_document_individu_2.field]",AF_SEARCHABLE|AF_HIDE_SEARCH,NULL,860 );
		$this->add(new atkNumberAttribute(nombre_cible, 0, 6, 0),1200);
		$this->add(new atkNumberAttribute(nombre_avec_courriel, 0, 6, 0),1250);
		$this->add(new atkNumberAttribute(nombre_avec_adresse_postale, 0, 6, 0),1300);
		$this->add(new atkNumberAttribute(nombre_retours, 0, 6, 0),1350);
		$this->add(new atkManyToOneRelation("id_documentorganisme", "organisme.document", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),2000);
		$this->add(new atkManyToOneRelation("id_documentindividu", "individu.document_i", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),2100);
		$this->add(new atkManyToOneRelation("id_gazette", "organisme.gazette", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),2200);								
		$this->add(new atkManyToOneRelation("id_infolettre", "organisme.infolettre", AF_HIDE_LIST | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),2300);				
		$this->setOrder("date_modification  asc");
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
	}
	function dispatch($postvars, $fullpage = true) {
		if ($postvars['atkaction'] != 'add' && $postvars['atkaction'] != 'delete' && $postvars['atkaction'] != 'admin') {
			$atkselect = $postvars["atkselector"];
			if (($atkselect != "") && isset ($atkselect)) {
 sscanf($atkselect, "individu_envoi_groupe.id=%d",$envoiId);
	
				$this->RecentUseProcess('envoi', $envoiId);
			} else {
				$envoiId = 0;
			}
		} else {

			$this->RecentUseRefresh('envoi');

		}
		return parent :: dispatch($postvars, $fullpage);
	}
	
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['delete'] = "delete";
	}

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
		$data = $db->getrows("SELECT au.id_individu as idutilisateur" . " from app_utilisateur au " . " where au.id =" . $id . " ");
		$idutilisateur = $data[0]["idutilisateur"];
		//print_r($record);
		//die();
		$data = $db->getrows("SELECT i.courriel," . "i.prenom, i.nom " . " from individu i " . " where i.id =" . $idutilisateur . " ");
		$mailer->AddReplyTo($data[0]["courriel"], $name = $data[0]["prenom"] . " " . $data[0]["nom"]);
		$mailer->FromName = $data[0]["prenom"] . " " . $data[0]["nom"];
		$adressereponse = $data[0]["courriel"];
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
		if ($record["id_document_organisme"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from organisme_document where id =" . $record["id_document_organisme"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
			if ($record["id_document_organisme_1"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from organisme_document where id =" . $record["id_document_organisme_1"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
				if ($record["id_document_organisme_2"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from organisme_document where id =" . $record["id_document_organisme_2"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_individu"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from individu_document where id =" . $record["id_document_individu"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
			if ($record["id_document_individu_1"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from individu_document where id =" . $record["id_document_individu_1"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		if ($record["id_document_individu_2"]["id"] > 0) {
			$data = $db->getrows("SELECT file_name, file_size, file_content,file_extension, contenu_html
			   from individu_document where id =" . $record["id_document_individu_2"]["id"] . " ");
			if (strlen($data[0]["file_name"]) > 1) {
				$mailer->AddStringAttachment($data[0]["file_content"], $data[0]["file_name"], $encoding = "base64", $type = "application/octet-stream");
			}
			if (strlen($data[0]["contenu_html"]) > 1) {
				$mailer->AddStringAttachment($data[0]["contenu_html"], $data[0]["file_name"] . '.html', $encoding = "base64", $type = "application/octet-stream");
			}
		}
		
		// envoyer le message
		$mailer->Send();
		$record["date_dernier_courriel"] = gmdate(c);
		//		$this->p($record);
	}

	function descriptor_def() {
		return "[objet]";
	}
}
?>