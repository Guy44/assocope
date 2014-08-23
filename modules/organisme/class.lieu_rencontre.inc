<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
class lieu_rencontre extends assMetaNode {
	var $table = "organisme_lieu_rencontre";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function lieu_rencontre() {
		$this->atkMetaNode();
		$this->atkNode("lieu_rencontre", NF_ADD_LINK );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
		"contrats",
		"rencontres",
		"groupes",
					"id_organisme",
				"id_individu_correspondant",
				"id_lieu",
				"horaires",
				"capacite",
				"cout_location",
				"telephone",
				"wifi",
		"sonorisation",
				"projection",
				"consignes",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				/*,
				 "Rencontres" => array (
				 "rencontre"
				 )
				 ,
				 "Groupes_de_travail" => array (
				 "groupe"
				 )
				 */
				), AF_NO_LABEL));
				$this->add(new atkDummyAttribute("descripteur_lieu_rencontre_lieu"),NULL, 6);
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),100);
				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				$this->add(new atkManyToOneRelation("id_individu_correspondant", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
				$this->add(new atkManyToOneRelation("id_lieu", "individu.lieu", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_RELATION_AUTOCOMPLETE ),400);
				$this->add(new atkManyToOneRelation("id_individu_correspondant", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),500);
				$this->add(new atkDummyAttribute("latlon",0 ),405);
				$this->add(new atkAttribute("horaires", AF_SEARCHABLE ),600);
				$this->add(new atkAttribute("capacite", AF_SEARCHABLE ),700);
				$this->add(new atkAttribute("cout_location", AF_SEARCHABLE ),800);
				$this->add(new atkAttribute("telephone", AF_SEARCHABLE ),900);
				$this->add(new atkAttribute("wifi", AF_SEARCHABLE ),1000);
				$this->add(new atkAttribute("sonorisation", AF_SEARCHABLE ),1100);
				$this->add(new atkAttribute("projection", AF_SEARCHABLE ),1200);

				$this->add(new atkfckattribute("consignes", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
			)),1300);


			$this->add(new atgNumberExpressionAttribute("contrats", ' select count(id) from organisme_contrat
	 where id_lieu_rencontre =[table].id and ( date_echeance is null or date_echeance > CURDATE() or date_resiliation is null or date_resiliation > CURDATE() )
					', 0, 0),102);
			$this->add(new atgNumberExpressionAttribute("rencontres", ' select count(id) from organisme_rencontre
	 where id_lieu_rencontre =[table].id and ( date_fin > CURDATE())
					', 0, 0),104);
			$this->add(new atgNumberExpressionAttribute("groupes", ' select count(id) from organisme_groupe_travail
	 where id_lieu_rencontre =[table].id and ( date_fin_groupe is null or date_fin_groupe > CURDATE())
					', 0, 0),106);
			
			$this->m_securityMap["latlon_google"] = "view";

			include_once (atkconfig("atkroot") . "modules/include/association.inc");
					$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,10);

			$this->setOrder("libelle");
			$this->setIndex("libelle");
	}
function descripteur_lieu_rencontre_lieu_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_lieu_rencontre_lieu($record["id"],'o').'<br />',100);
	}
	
	function telephone_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone"] . ';">' . $record["telephone"] . '</a>';
	}
	function contrats_display($record, $mode) {
		if (isset ($record["contrats"])) {
			$ret= href(dispatch_url("organisme.contrat", "admin", array (
				'atkfilter' => "organisme_contrat.id_lieu_rencontre='" . $record['id'] . "' and ( date_echeance is null or date_echeance > CURDATE() or date_resiliation is null or date_resiliation > CURDATE() )"
				), "dispatch.php"), text($record["contrats"]), SESSION_NESTED);
				if ($record["contrats"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function rencontres_display($record, $mode) {
		if (isset ($record["rencontres"])) {
			$ret=href(dispatch_url("organisme.rencontre", "admin", array (
				'atkfilter' => "organisme_rencontre.id_lieu_rencontre='" . $record['id'] . "' and date_fin > CURDATE()"
				), "dispatch.php"), text($record["rencontres"]), SESSION_NESTED);
				if ($record["rencontres"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return '0';
		} else {
			return "";
		}
	}
	function groupes_display($record, $mode) {
		if (isset ($record["groupes"])) {
			$ret=href(dispatch_url("organisme.groupe_travail", "admin", array (
				'atkfilter' => "organisme_groupe_travail.id_lieu_rencontre='" . $record['id'] . "' and ( date_fin_groupe is null or date_fin_groupe > CURDATE())"
				), "dispatch.php"), text($record["groupes"]), SESSION_NESTED);
				if ($record["groupes"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return '0';
		} else {
			return "";
		}
	}
	function action_latlon_google() {
		$record["id"]=$this->m_postvars["id_lieu"];
		return $this->latlon_display($record);
	}

	function latlon_display($record, $mode) {
		$db = & atkGetDb();
		$sql='SELECT latitude, longitude from organisme_lieu_rencontre lr , lieu l
					where lr.id='.$record[id].' and lr.id_lieu=l.id ' ;
		$stuff=$db->getrows($sql);
		//		$stuff[0]["latitude"]=substr($stuff[0]["latitude"],0, strlen($stuff[0]["latitude"])-6).'.'.substr($stuff[0]["latitude"],strlen($stuff[0]["latitude"])-6,6);
		//		$stuff[0]["longitude"]=substr($stuff[0]["longitude"],0, strlen($stuff[0]["longitude"])-6).'.'.substr($stuff[0]["longitude"],strlen($stuff[0]["longitude"])-6,6);
		$ret= $stuff[0]["latitude"]."<br />".$stuff[0]["longitude"];
		if ($stuff[0]["latitude"]=="")
		{$carte="";}
		else
		{$carte='<font color="ForestGreen"><b>Carte</b></font>';}
		return href("http://maps.google.com/maps?q=".$stuff[0]["latitude"].",".$stuff[0]["longitude"], atktext($carte), SESSION_NEW, false, 'target="_blank"') ;
	}

	function action_admin(& $handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function descriptor_def() {
		return "([id_organisme.nom]) [libelle] ";
	}

	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);

	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_individu_correspondant_display($record, $mode) {
		(!empty($record["id_individu_correspondant"])) ? $retour=$this->descripteur_individu($record["id_individu_correspondant"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>