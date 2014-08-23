<?php
atkimport("atk.assmetanode");
class cotisation_i extends assMetaNode {
	var $table = "individu_cotisation";
	function meta(& $policy) {
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_recu_fiscal","id_creation", "date_creation", "id_modification", "date_modification", "montant_cotisation_organisme", "montant_don", AF_READONLY | AF_FORCE_LOAD);
	}
	function cotisation_i() {
		$this->atkMetaNode();
		$this->atkNode("cotisation_i", NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA | NF_COMPACT);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"descripteur_cotisant",
						"id_individu",
						"id_organisme_cotisant",
						"id_organisme",
						"id_cotisation",
						"ventilation",
						"montant_versement",
						"montant_cotisation_organisme",
						"montant_don",
						"descripteur_reglement",
						"date_reglement",
						"id_reglement",
						"id_banque",
						"numero_cheque",
						"date_envoi_recu_fiscal",
						"id_recu_fiscal",
						"date_envoi_timbre",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Ecritures" => array (
						"ecritures",
						"id_ecriture_cotisation",
						"id_ecriture_cotisation_federation",
						"id_ecriture_reglement",
						"id_cotisation_federation")
		), AF_NO_LABEL));

		$this->setSecurityAlias("individu.individu");
		$this->add(new atkManyToOneRelation("id_individu", "individu.individu", AF_SEARCHABLE | AF_FORCE_LOAD |AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),NULL,43);
		$organisme = & $this->add(new atkManyToOneRelation("id_organisme_cotisant", "organisme.organisme", AF_SEARCHABLE  | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),NULL, 44);
		$organisme = & $this->add(new atkManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE| AF_FORCE_LOAD),NULL,45);
		$organisme->addDependee("id_cotisation");
		//$organisme->addDependee("presence_compta");
		$this->add(new atkDummyAttribute("descripteur_cotisant",0,AF_COMPACT),NULL,39);
		$this->add(new atkDummyAttribute("descripteur_reglement"),NULL, 40);
		$this->add(new atkDummyAttribute("ecritures"),NULL,45);
		$cotisation = & $this->add(new atkManyToOneRelation("id_cotisation", "organisme.cotisation", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK| AF_FORCE_LOAD),NULL,50);
		$cotisation->addDestinationFilter("id_organisme= '[id_organisme.id]'");
		//$cotisation->addDependee("presence_compta");
		$this->add(new atkDummyAttribute("ventilation"),NULL, 60);
		$this->add(new atkNumberAttribute("montant_versement", AF_OBLIGATORY , 12, 2), NULL, 100);
		$this->add(new atkNumberAttribute("montant_cotisation_organisme",AF_HIDE_ADD |AF_READONLY, 12, 2), NULL, 110);
		$this->add(new atkNumberAttribute("montant_don", AF_HIDE_ADD |AF_READONLY, 12, 2), NULL, 120);


		//			$this->add(new atkParserAttribute("presence_compta", "env", AF_NO_LABEL | AF_HIDE_LIST), NULL, 130);
		$this->add(new atkDateAttribute("date_reglement", "Y-m-d", "Y-m-d", 0, 0, AF_OBLIGATORY |AF_DATE_STRING), NULL, 140);
		$this->add(new atkDateAttribute("date_envoi_timbre", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING|AF_READONLY), NULL, 150);
		$this->add(new atkDateAttribute("date_envoi_recu_fiscal", "Y-m-d", "Y-m-d", 0, 0, AF_DATE_STRING|AF_READONLY), NULL, 155);

		$this->add(new atkManyToOneRelation("id_reglement", "table.reglement", AF_OBLIGATORY |AF_SEARCHABLE | AF_RELATION_AUTOLINK), NULL, 160);
		$this->add(new atkManyToOneRelation("id_banque", "table.banque", AF_SEARCHABLE | AF_RELATION_AUTOLINK), NULL, 170);
		//		$this->add(new atkOneToManyRelation("id_ecriture_cotisation", "organisme.ligne_ecriture_comptable", "id_ecriture", AF_HIDE_LIST),5);
		//		$this->add(new atkOneToManyRelation("id_ecriture_cotisation", "organisme.ligne_ecriture_comptable", "id_ecriture", AF_HIDE_LIST),6);
		//		$this->add(new atkOneToManyRelation("id_ecriture_reglement", "organisme.ligne_ecriture_comptable", "id_ecriture", AF_HIDE_LIST),7);
		$this->add(new atkAttribute("id_ecriture_cotisation"),NULL,41);
		$this->add(new atkAttribute("id_ecriture_cotisation_federation"),NULL,42);
		$this->add(new atkAttribute("id_ecriture_reglement"),NULL,43);


		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL|AF_COMPACT),null,45 );
		$this->m_securityMap["admin_liste"] = "view";
		//				$this->setOrder("individu_cotisation.id_individu");
		$this->setOrder("date_creation desc");
			
	}
	function descripteur_reglement_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_reglement('cotisation',$record["id"]).'<br />'.$this->ecritures_display($record, $mode),100);
	}

	function descripteur_cotisant_display($record, $mode) {

		(!empty($record["id_organisme_cotisant"]["id"])) ? $retour.=$this->descripteur_organisme($record["id_organisme_cotisant"]["id"],'n','n','100')."<br />" : $retour.='';
		$retour.=$this->descripteur_individu($record["id_individu"]["id"],'n','n','50')."<br />";
		$retour.=$this->descripteur_reglement('cotisation',$record["id"],'n');
		$retour.=$this->descripteur_organisme($record["id_organisme"]["id"],'n','n','50')."<br />";
		($aide_o_n=='o') ? $retour.='&nbsp;'.$this->descripteur_aide('Descripteur_cotisant','n') : null;

		return $retour;
	}
	function ecritures_display($record, $mode) {
		if (isset ($record["id_ecriture_cotisation"]) || isset ($record["id_ecriture_reglement"]) || isset ($record["id_ecriture_cotisation_federation"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_cotisation'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'
					or organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_cotisation_federation'] . "'"
			), "dispatch.php"), text("Ecritures comptables"), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function ventilation_display($record, $mode) {
		(!empty($record["montant_versement"])) ? $retour="<b>Versement : ".$record["montant_versement"].'</b><br />' : $retour="";
		(!empty($record["montant_cotisation_organisme"])) ? $retour.="Cotisation : ".$record["montant_cotisation_organisme"].'<br />' : $retour.="";
		(!empty($record["montant_don"])) ? $retour.="Don : ".$record["montant_don"].'<br />' : $retour.="";
		return $this->decoupe_affichage_colonne($retour, 40);
	}

	function id_individu_display($record, $mode) {
		(!empty($record["id_individu"])) ? $retour=$this->descripteur_individu($record["id_individu"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function id_organisme_cotisant_display($record, $mode) {
		(!empty($record["id_organisme_cotisant"])) ? $retour=$this->descripteur_organisme($record["id_organisme_cotisant"]["id"],'n') : $retour="";
		return $retour;
	}


	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 100;
		return $handler->action_admin();
	}
	/*function initial_values()
	 {
	$init_vals = array ();
	if ($this->m_postvars['atkfilter']=='')
	{		}
	else
	{$filtre=$this->m_postvars["atkfilter"];
	$filtre=substr($filtre, stripos($filtre, "id_organisme="));
	$filtre=substr($filtre,14);
	$filtre=substr($filtre,0,strlen($filtre)-1);
	$init_vals["id_organisme"]["id"] =$filtre;
	//		$this->p($init_vals);
	}
	return $init_vals;
	}
	*/

	/*	function dispatch(& $postvars, $fullpage = true) {
		if ($postvars['atkaction'] != 'admin')
		{
	if ($postvars['atkfilter']=='')
	{

	}
	else
	{$filtre=$postvars["atkfilter"];
	$filtre=substr($filtre, stripos($filtre, "id_organisme="));
	$filtre=substr($filtre,14);
	$filtre=substr($filtre,0,strlen($filtre)-2);
	$postvars["id_organisme"]=$filtre;}
	unset ($postvars["atkfilter"]);
	}
	return parent :: dispatch($postvars, $fullpage);
	}
	*/
	function id_ecriture_cotisation_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_cotisation"]);
		/*		if (isset ($record["id_ecriture_cotisation"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_cotisation'] . "'"
			), "dispatch.php"), text($record["id_ecriture_cotisation"]), SESSION_NESTED);
		} else {
		return "";
		}
		*/
	}
	function id_ecriture_cotisation_federation_display($record, $mode) {

		return $this-> descripteur_ecriture_comptable($record["id_ecriture_cotisation_federation"]);
		/*		if (isset ($record["id_ecriture_cotisation_federation"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_cotisation_federation'] . "'"
			), "dispatch.php"), text($record["id_ecriture_cotisation_federation"]), SESSION_NESTED);
		} else {
		return "";
		}
		*/
	}
	function id_ecriture_reglement_display($record, $mode) {
		return $this-> descripteur_ecriture_comptable($record["id_ecriture_reglement"]);
		/*	if (isset ($record["id_ecriture_reglement"])) {
			return href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
					'atkfilter' => "organisme_ligne_ecriture_comptable.id_ecriture='" . $record['id_ecriture_reglement'] . "'"
			), "dispatch.php"), text($record["id_ecriture_reglement"]), SESSION_NESTED);
		} else {
		return "";
		}
		*/
	}
	/*	function presence_compta_edit($record, $mode) {
		$this->p($record);
	$id_organisme = $record["id_organisme"]["id"];
	if (!isset ($record["id_organisme"]["id"])) {
	return "";
	}
	$db = & atkGetDb();
	$data = $db->getrows("SELECT date_initialisation_comptabilite, nom  from organisme
			where id ='" . $id_organisme . "'");
	if (isset ($data[0]["date_initialisation_comptabilite"]["year"])) {
	return '';
	} else {
	return '<font color="Red"> <b> La saisie de montant verse ne sera pas prise en compte dans la comptabilite : la comptabilite n\'ayant pas ete initialisee pour ' . $data[0]["nom"] . '.';
	}
	}
	*/
	/*function presence_compta_edit($record, $mode) {

	$id_organisme = $record["id_organisme"];
	if (!isset ($record["id_organisme"])) {
	return "";
	}
	$db = & atkGetDb();
	$data = $db->getrows("SELECT date_initialisation_comptabilite, nom  from organisme
			where id ='" . $id_organisme . "'");
	if (isset ($data[0]["date_initialisation_comptabilite"]["year"])) {
	return '';
	} else {
	return '<font color="Red"> <b> La saisie de montant verse ne sera pas prise en compte dans la comptabilite : la comptabilite n\'ayant pas ete initialisee pour ' . $data[0]["nom"] . '.';
	}
	}
	*/
	public function validate(&$record, $mode)
	{
		$id_organisme = $record["id_organisme"]["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT date_initialisation_comptabilite, nom  from organisme
				where id ='" . $id_organisme . "'");
		if (isset ($data[0]["date_initialisation_comptabilite"]["year"])) {
		} else {
			atkTriggerError($record, $this->getAttribute("id_organisme"), "La saisie de montant verse ne sera pas prise en compte dans la comptabilite :
					la comptabilite n\'ayant pas ete initialisee pour " . $data[0]["nom"]);
		}

		global $g_user;
		$userutilisateur = $g_user["id"];
		$tableautemp = array ();
		$db = & atkGetDb();
		$id_organisme = $record["id_organisme"]["id"];
		$data = $db->getrows("SELECT eclater_cotisations_dons_o_n from organisme where  id ='" . $id_organisme . "'");
		$eclater_cotisations_dons_o_n = $data[0]["eclater_cotisations_dons_o_n"];
		$tableautemp["userid"] = $userutilisateur;
		$id_cotisation_organisme = $record['id_cotisation']['id'];
		if (empty($record['id_cotisation']))
		{
			atkTriggerError($record, $this->getAttribute("id_cotisation"), "Vous n'avez pas sélectionné de cotisation.");
		}
		$id_individu = $record['id_individu']['id'];
		$data = $db->getrows("SELECT id_cotisation, id_individu  FROM individu_cotisation
				where id_cotisation = $id_cotisation_organisme and id_individu=$id_individu");
		$res = $data[0]["id_individu"];
		if (isset ($res)) {
			atkTriggerError($record, $this->getAttribute("id_cotisation"), "La cotisation pour cette personne a déjà été réglée.");
		}
		$id_organisme = $record['id_organisme']['id'];
		$montant_versement = $record['montant_versement'];
		$tableautemp["id_individu"] = $id_individu;
		$tableautemp["montant_versement"] = $montant_versement;
		$db = & atkGetDb();
		$data = $db->getrows("SELECT montant,montant_1, montant_2, montant_3, annee, id_organisme FROM organisme_cotisation where id=$id_cotisation_organisme ");
		if ($id_organisme != $data[0]["id_organisme"]) {
			atkTriggerError($record, $this->getAttribute("id_cotisation"), "Incompatibilité entre organisme et cotisation : modifier organisme ou cotisation.");
		}
		$tableautemp["id_organisme"] = $id_organisme;
		$montant_cotisation_organisme_0 = $data[0]["montant"];
		$montant_cotisation_organisme_1 = $data[0]["montant_1"];
		$montant_cotisation_organisme_2 = $data[0]["montant_2"];
		$montant_cotisation_organisme_3 = $data[0]["montant_3"];
		$annee_cotisation_organisme = $data[0]["annee"];
		$tableautemp["annee_cotisation_organisme"] = $annee_cotisation_organisme;
		$id_organisme = $data[0]["id_organisme"];
		$tableautemp["id_organisme"] = $id_organisme;
		// doit être inscrit dans l'organisme
		$sql="SELECT ii.id, ii.date_adhesion from individu_inscription ii" . " where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme and ii.date_radiation is null";
		$data = $db->getrows($sql);
		if (count($data) == 0) {
			atkTriggerError($record, $this->getAttribute("id_individu"), "Non inscrit à l'organisme ou radié : faire d'abord l'inscription.");
		}
		else
		{
			if ($data[0]["date_adhesion"] == null) {
				atkTriggerError($record, $this->getAttribute("id_individu"), "Pas de date d'adhésion : saisir date adhésion dans inscription.");
			}
		}
		// doit on payer une cotisation fédération
		$data = $db->getrows("SELECT ti.tarif, ti.cotisation_federation_o_n, ti.cotisation_organisme_o_n from individu_inscription ii, type_inscription ti" . "
				where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme" . " and ii.id_type_inscription=ti.id ");
		$cotisation_federation_o_n = $data[0]["cotisation_federation_o_n"];
		$cotisation_organisme_o_n = $data[0]["cotisation_organisme_o_n"];
		$tarif = $data[0]["tarif"];
		// si oui l'individu est bien inscrit à la fédération de l'organisme et n'est pas radié
		if ($cotisation_federation_o_n == 1)
		{
			// rechercher l'id de la fédération
			$data = $db->getrows("SELECT id_organisme_federation from organisme where id='".$id_organisme."'");
			$id_organisme_federation=$data[0]["id_organisme_federation"];
			// inscription ?
			$data = $db->getrows("SELECT ii.id, ii.date_adhesion from individu_inscription ii" . "
					where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme_federation and ii.date_radiation is null");
			if (count($data) == 0) {
				atkTriggerError($record, $this->getAttribute("id_individu"), "Non inscrit à la fédération ou radié : faire d'abord l'inscription.<br/>
						L'inscription se fait automatiquement si on choisit un type d'inscription mentionnant l'inscription à une fédération.<br>");
			}
		}
		if ($tarif ==''){
			atkTriggerError($record, $this->getAttribute("id_cotisation"), "Tarif non renseigné<br/>
					Vérifier type inscription et type cotisation.");
		}
		if ($tarif == '0') {
			$montant_cotisation_organisme = $montant_cotisation_organisme_0;
		}
		if ($tarif == '1') {
			$montant_cotisation_organisme = $montant_cotisation_organisme_1;
		}
		if ($tarif == '2') {
			$montant_cotisation_organisme = $montant_cotisation_organisme_2;
		}
		if ($tarif == '3') {
			$montant_cotisation_organisme = $montant_cotisation_organisme_3;
		}
		if (($cotisation_organisme_o_n == 0) && ($cotisation_federation_o_n == 0)) {
			atkTriggerError($record, $this->getAttribute("id_cotisation"), "Le type d'inscription précise qu'il n'y a pas de cotisation organisme ou fédération : changer le type d'inscription ou ne pas saisir de cotisation.");
		}
		if ($cotisation_organisme_o_n == 0) {
			$montant_cotisation_organisme = 0;
		}
		if ($cotisation_federation_o_n == 0) {
			$montant_cotisation_federation = 0;
		} else {
			// rechercher le montant de la cotisation fédération pour la même année
			$data = $db->getrows("SELECT o.id_organisme_federation, oc.montant, oc.id
					from organisme o, organisme_cotisation oc
					where o.id=$id_organisme and o.id_organisme_federation=oc.id_organisme and oc.annee=$annee_cotisation_organisme ");
			$montant_cotisation_federation = $data[0]["montant"];
			if (!isset ($montant_cotisation_federation)) {
				atkTriggerError($record, $this->getAttribute("id_cotisation"), "La cotisation fédération n'a pas été créée");
			}
			$id_cotisation_federation = $data[0]["id"];
			$id_organisme_federation = $data[0]["id_organisme_federation"];
		}
		$tableautemp["cotisation_organisme_o_n"] = $cotisation_organisme_o_n;
		$tableautemp["cotisation_federation_o_n"] = $cotisation_federation_o_n;
		$montant_don = 0;
		if ($eclater_cotisations_dons_o_n == 1) {
			$montant_don = $montant_versement - $montant_cotisation_organisme;
			if ($montant_don < 0) {
				$montant_don = 0;
				$montant_cotisation_organisme = $montant_versement;
			}
		} else {
			$montant_cotisation_organisme = $montant_versement;
			$montant_don = 0;
		}
		$tableautemp["montant_cotisation_organisme"] = $montant_cotisation_organisme;
		$tableautemp["montant_cotisation_federation"] = $montant_cotisation_federation;
		$tableautemp["montant_don"] = $montant_don;
		$record["montant_cotisation_organisme"] = $montant_cotisation_organisme;
		$record["montant_don"] = $montant_don;
		// L'inscription à fédération doit exister et vérifier si pas déjà cotistaion existante
		if ($cotisation_federation_o_n == 1) {
			$data = $db->getrows("SELECT ii.id from individu_inscription ii" . " where ii.id_individu=$id_individu and ii.id_organisme=$id_organisme_federation ");
			if (count($data) == 0) {
				atkTriggerError($record, $this->getAttribute("id_individu"), "Non inscrit à la fédération.");
			}
			$data = $db->getrows("SELECT ic.id from individu_cotisation ic" . " where ic.id_individu=$id_individu and ic.id_cotisation=$id_cotisation_federation ");
			if (count($data) == 0) {
				$data = $db->query("INSERT into individu_cotisation" . " (id_organisme, id_individu, id_cotisation, montant_versement, montant_cotisation_organisme,id_creation, id_modification, date_creation, date_modification)" . "VALUES ( $id_organisme_federation, $id_individu,$id_cotisation_federation,$montant_cotisation_federation,$montant_cotisation_federation,$userutilisateur,$userutilisateur,UTC_DATE(),UTC_DATE())");
				$data = $db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_cotisation' ");
				$sql = "SELECT id as id from individu_cotisation where id_individu=$id_individu and  id_cotisation=$id_cotisation_federation ";
				$data = $db->getrows($sql);
				$record["id_cotisation_federation"] = $data[0]["id"];
			}
		}
		
		if ($record["id_reglement"]=="")
		{
			atkTriggerError($record, $this->getAttribute("id_reglement"), "Vous devez choisir un type de règlement");
		}
		if ($record["id_reglement"]["id"]==1 && $record["id_banque"]["id"]=="")
		{
			atkTriggerError($record, $this->getAttribute("id_banque"), "Pas de banque et le mode de règlement précise que c'est un règlement par chèque");
		}
		if ($record["id_reglement"]["id"]!=1 && $record["numero_cheque"]!="")
		{
			atkTriggerError($record, $this->getAttribute("numero_cheque"), "Numéro de chèque alors que le mode de règlement précise que ce n'est pas un règlement par chèque");
		}
		if ($record["id_reglement"]["id"]==1 && $record["numero_cheque"]=="")
		{
			atkTriggerError($record, $this->getAttribute("numero_cheque"), "Pas de numéro de chèque alors que le mode de règlement précise que c'est un règlement par chèque");
		}

		if	(parent::validate($record, $mode)==true)
		{
			//$this->p($record);
			if ($mode=="update") $this->supprimer_ecritures($record);
			$record["id_recu_fiscal"] = $this->getProchainIdRecuFiscal($id_organisme);
			$this->creer_ecritures_comptables($record, $tableautemp, "add");
		}
	}
	function supprimer_ecritures(& $record) {
		$db = & atkGetDb();
		$id_ecriture_cotisation = $record["id_ecriture_cotisation"];
		$id_ecriture_cotisation_federation = $record["id_ecriture_cotisation_federation"];
		$id_ecriture_reglement = $record["id_ecriture_reglement"];
		if ($id_ecriture_reglement == "") {
			return true;
		}
		if (isset ($id_ecriture_cotisation)) {
			$this->supprimer_ecriture_comptable($id_ecriture_cotisation);
		}
		if (isset ($id_ecriture_cotisation_federation)) {
			$this->supprimer_ecriture_comptable($id_ecriture_cotisation_federation);
		}
		if (isset ($id_ecriture_reglement)) {
			$this->supprimer_ecriture_comptable($id_ecriture_reglement);
		}
		return true;
	}

	function getProchainIdRecuFiscal($id_organisme) {
		$db = & atkGetDb();
		$data = $db->getrows("SELECT prochain_id_recu_fiscal FROM organisme where id=$id_organisme ");
		$id_recu_fiscal = $data[0]["prochain_id_recu_fiscal"];
		$db->query("UPDATE organisme set prochain_id_recu_fiscal=prochain_id_recu_fiscal+1 where id=$id_organisme ");
		return $id_recu_fiscal;
	}
	function postUpdate($record)
	{
		$this->mise_a_jour_type_ecriture($record);
		parent::postUpdate($record);
		return true;
	}
	function postAdd($record)
	{
		$db = & atkGetDb();
		$data=$db->getrows('Select max(id) as id from individu_cotisation');
		$record["id"]=$data[0]["id"];
		$this->mise_a_jour_type_ecriture($record);
		parent::postAdd($record);
		return true;
	}
	function mise_a_jour_type_ecriture($record)
	{
		if (!empty($record["id_ecriture_cotisation"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_cotisation"],$this->type_ecriture_cotisation,$record["id"]);
		}
		if (!empty($record["id_ecriture_reglement"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_reglement"],$this->type_ecriture_cotisation,$record["id"]);
		}
		if (!empty($record["id_ecriture_cotisation_federation"]))
		{
			$this->ecriture_type_origine_maj($record["id_ecriture_cotisation_federation"],$this->type_ecriture_cotisation,$record["id"]);
		}
		return true;
	}

	function preDelete(& $record) {
		$db = & atkGetDb();
		$id_ecriture_organisme = $record["id_ecriture_cotisation"];
		$id_ecriture_federation = $record["id_ecriture_cotisation_federation"];
		$id_cotisation_federation = $record["id_cotisation_federation"];
		if (isset ($id_cotisation_federation)) {
			$sql = "delete from individu_cotisation where id = '$id_cotisation_federation' ";
			$db->query($sql);
		}
		$id_ecriture_reglement = $record[id_ecriture_reglement];
		if (!isset ($id_ecriture_reglement))
			return true;
		$data = $db->getrows("select r.date_remise_banque as date_remise_banque from organisme_remise_banque r, organisme_ligne_ecriture_comptable l, individu_cotisation c
				where c.id_ecriture_reglement= $id_ecriture_reglement
				and  l.id_ecriture=c.id_ecriture_reglement
				and r.id=l.id_remise
				and id_type_banque  is not null ");
		if (isset ($data[0]["date_remise_banque"])) {
			echo "<br><b> Impossible de supprimer, le règlement a été remis en banque<br>";
			die();
		} else {
			if (isset ($id_ecriture_organisme)) {
				$this->supprimer_ecriture_comptable($id_ecriture_organisme);
			}
			if (isset ($id_ecriture_federation)) {
				$this->supprimer_ecriture_comptable($id_ecriture_federation);
			}
			if (isset ($id_ecriture_reglement)) {
				$this->supprimer_ecriture_comptable($id_ecriture_reglement);
			}
		}
		return true;
	}


	function creer_ecritures_comptables(& $record, & $tableau, $mode) {
		$id_organisme = $record['id_organisme']['id'];
		// récupérer l'organisme i
		// supprimer les écritures existantes id_ecriture_cotisation, id_ecriture_reglement
		// seulement si pas de remise en banque et si mode update
		// récupérer année de cotisation $record["id_cotisation""annee"]
		$db = & atkGetDb();
		$individu = $db->getrows("SELECT nom, prenom
				from individu where id='" . $tableau["id_individu"] . "'");
		$rang = $db->getrows("SELECT o.id_compte_cotisation_organisme_an_prec as id_compte_cotisation_organisme_an_prec,
				o.id_compte_cotisation_organisme_an as id_compte_cotisation_organisme_an,
				o.id_compte_cotisation_organisme_an_suiv as id_compte_cotisation_organisme_an_suiv,
				o.id_compte_dons as id_compte_dons,
				o.id_compte_cotisation_federation_an_prec as id_compte_cotisation_federation_an_prec,
				o.id_compte_cotisation_federation_an as id_compte_cotisation_federation_an,
				o.id_compte_cotisation_federation_an_suiv as id_compte_cotisation_federation_an_suiv,
				o.id_compte_federation as id_compte_federation,
				o.id_compte_adherents as id_compte_adherents,
				o.id_compte_caisse as id_compte_caisse,
				o.id_journal_cotisations_organisme as id_journal_cotisations_organisme,
				o.id_journal_cotisations_federation as id_journal_cotisations_federation,
				o.id_journal_banque_courant as id_journal_banque_courant,
				o.id_journal_caisse as id_journal_caisse,
				jc.id_compte_banque as id_compte_banque
				FROM organisme o, organisme_journal_comptable jc
				where o.id=$id_organisme and o.id_journal_banque_courant=jc.id ");
		//		print_r ($rang);
		//		die();
		// récupérer le montant fofficle cotisation pour l'année
		$id_journal_cotisations_organisme = $rang[0]["id_journal_cotisations_organisme"];
		$id_journal_caisse = $rang[0]["id_journal_caisse"];
		$id_journal_cotisations_federation = $rang[0]["id_journal_cotisations_federation"];
		$id_journal_banque_courant = $rang[0]["id_journal_banque_courant"];
		$id_compte_banque = $rang[0]["id_compte_banque"];
		$id_compte_caisse = $rang[0]["id_compte_caisse"];
		$id_compte_federation = $rang[0]["id_compte_federation"];
		// récupérer compte de cotisation organisme organisme.id_compte_cotisation_organisme
		//  	// calculer le compte en fonction année n, n+1, n-1
		$offset = 2 + $tableau["annee_cotisation_organisme"] - gmdate("Y");
		if ($offset == '1') {
			$id_compte_cotisation_organisme = $rang[0]["id_compte_cotisation_organisme_an_prec"];
			$id_compte_cotisation_federation = $rang[0]["id_compte_cotisation_federation_an_prec"];
		}
		if ($offset == '2') {
			$id_compte_cotisation_organisme = $rang[0]["id_compte_cotisation_organisme_an"];
			$id_compte_cotisation_federation = $rang[0]["id_compte_cotisation_federation_an"];
		}
		if ($offset == '3') {
			$id_compte_cotisation_organisme = $rang[0]["id_compte_cotisation_organisme_an_suiv"];
			$id_compte_cotisation_federation = $rang[0]["id_compte_cotisation_federation_an_suiv"];
		}
		$date_reglement = $this->dateatktodb($record["date_reglement"]);
		$libelle = 'Cotisation organisme ' . $tableau["annee_cotisation_organisme"] . ' ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
		$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_cotisations_organisme, $libelle,$date_reglement);
		$record["id_ecriture_cotisation"] = $id_ecriture;
		$id_compte_dons = $rang[0]["id_compte_dons"];
		$id_compte_federation = $rang[0]["id_compte_federation"];
		$id_compte_adherents = $rang[0]["id_compte_adherents"];
		$id_individu = $tableau["id_individu"];
		$id_type_reglement = $record["id_reglement"]["id"];
		$numero_piece = $record["numero_cheque"];
		$id_type_banque = $record["id_banque"]["id"];
		$debit = $record["montant_versement"];
		//		print_r($record);
		//		die();
		// montant versement
		$credit = 0;
		$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_organisme, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		if ($tableau["cotisation_organisme_o_n"] == 1) {
			$credit = $tableau["montant_cotisation_organisme"];
			;
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_organisme, $id_compte_cotisation_organisme, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		}
		if ($tableau["montant_don"] > 0) {
			$debit = 0;
			$credit = $tableau["montant_don"];
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_organisme, $id_compte_dons, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		}
		if (isset ($tableau["cotisation_federation_o_n"]) && ($tableau["cotisation_federation_o_n"] != 0)) {
			$libelle = 'Cotisation fédération ' . $tableau["annee_cotisation_organisme"] . ' ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_cotisations_federation, $libelle,$date_reglement);
			$record["id_ecriture_cotisation_federation"] = $id_ecriture;
			$debit = 0;
			$credit = $tableau["montant_cotisation_federation"];
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_federation, $id_compte_federation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$credit = 0;
			$debit = $tableau["montant_cotisation_federation"];
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_cotisations_federation, $id_compte_cotisation_federation, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
		}
		// récupérer le compte dons organisme.id_compte_dons
		// récupérer le montant fofficle cotisation fédé pour lannée
		// récupérer compte de cotisation fédération organisme.id_compte_cotisation_federation
		//  	// calculer le compte en fonction année n, n+1, n-1
		// récupérer compte fédération organisme.id_compte_federation
		// récupérer le journal des cotisations organisme.id_journal_cotisations_organisme
		// récupérer le journal de banque organisme.id_journal_banque_courant
		// récupérer compte banque du journal organisme_journal_comptable.id_compte_banque
		// Créer écriture cotisation
		// obtenir un numéro écriture
		// le stocker dans id_ecriture_cotisation
		// Créer une ligne adhérent avec débit = montant_versement
		// Créer une ligne cotisation organisme avec crédit = montant officiel cotisation
		//Créer une ligne don avec crédit= montant_don
		// créer une ligne fédaération avec crédit = montant officiel
		// créer une ligne cotisation fédé avec débit = montant officiel
		if ($id_type_reglement == 1) {
			// chéque à remettre en banque
			$libelle = 'Cotisation ' . $tableau["annee_cotisation_organisme"] . ' ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
			$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_banque_courant, $libelle, $date_reglement);
			$record["id_ecriture_reglement"] = $id_ecriture;
			$credit = $record["montant_versement"];
			$debit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
			$debit = $record["montant_versement"];
			$credit = 0;
			$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_banque_courant, $id_compte_banque, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, $numero_piece, $date_reglement, $id_type_banque);
		} else {
			if ($id_type_reglement == 3) {
				// epèces reçues en caisse
				$libelle = 'Cotisation ' . $tableau["annee_cotisation_organisme"] . ' ' . $individu[0]["nom"] . ' ' . $individu[0]["prenom"];
				$id_ecriture = $this->creer_ecriture_comptable($id_organisme, $id_journal_caisse, $libelle,$date_reglement);
				$record["id_ecriture_reglement"] = $id_ecriture;
				$credit = $record["montant_versement"];
				$debit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_adherents, $id_organisme, $id_individu, $debit, $credit, null, null, null, null);
				$debit = $record["montant_versement"];
				$credit = 0;
				$this -> creer_ligne_ecriture_comptable($id_ecriture, $id_journal_caisse, $id_compte_caisse, $id_organisme, $id_individu, $debit, $credit, $id_type_reglement, null, $date_reglement, null);
			}
		}
		// Créer écriture banque
		// obtenir un numéro écriture
		// le stocker dans id_ecriture_reglement
		// Créer une ligne adhérent avec crédit = montant_versement
		// Créer une ligne banque avec débit = montant_versement
		// créer une ligne fédaération avec débit = montant officiel
		// créer une ligne banque avec crédit = montant officiel
		return;
	}
	function recordActions($rec, &$actions, &$mraactions)
	{
		parent::recordActions($rec, $actions, $mraactions);

	}
	function traitement_select($select, & $idorganisme, & $idindividus, & $idinscriptions) {
		$db = & atkGetDb();

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$data = $db->getrows("select id_individu from individu_cotisation
				 where id=$array_id[1]");
			$idindividus .= $data[0]["id_individu"] . ',';
		}

		$idindividus = substr($idindividus, 0, strlen($idindividus) - 1);
		$idindividus=str_replace("'","",$idindividus);
		$idorganisme = "";
		return true;
	}
	function descriptor_def() {
		return "[id]";
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$filtre=str_replace("individu_cotisation", "ic", $this->m_postvars["atkfilter"]);
		$sql="SELECT
		ic.id	as id_entite,
		ic.id_individu as id_individu,
		ic.numero_cheque,
		tr.libelle as libelle_mode_reglement,
		tb.libelle as libelle_banque,
		oc.libelle as libelle_cotisation,
		ic.date_reglement,
		ic.montant_versement,
		ic.montant_cotisation_organisme,
		ic.montant_don,
		ic.id_recu_fiscal,
		ic.date_envoi_recu_fiscal,
		ic.date_envoi_timbre,
		o.id as id_organisme,
		o.nom as organisme
		from
		individu_cotisation ic LEFT JOIN individu i ON ic.id_individu=i.id
		LEFT JOIN organisme_cotisation oc ON ic.id_cotisation=oc.id
		LEFT JOIN organisme o ON oc.id_organisme=o.id
		LEFT JOIN type_reglement tr ON ic.id_reglement=tr.id
		LEFT JOIN type_banque tb ON ic.id_banque=tb.id
		where
		$filtre
		order by i.nom, i.prenom, ic.date_reglement	";
		$data=$db->getrows($sql);
		$res2= '<table class="toc  sortable">';
		$res2.='<thead>';
		$res2.='<tr><th '.$this->m_styleTitreLigne.'>#';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Cotisation';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Nom';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Contact</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Naissance</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Versement</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Cotisation</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Don</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Date règlement</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Mode règlement</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Chèque</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Banque</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Reçu fiscal</center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Envoyé </center>';
		$res2.='</th><th '.$this->m_styleTitreLigne.'>Envoi timbre</center>';
//		$res2.='</th><th '.$this->m_styleTitreLigne.'>Décès</center>';
		$res2.='</th><th '.$this->m_styleTitreLigneEstampille.'><center><b>Estampille</center></b>';
		$res2.='</th></tr>';
		$res2.='</thead>';
		$res2.='<tbody>';
		for ($i=0;$i<count($data);$i++)
		{
			$idindividus.=$data[$i]["id_individu"].",";
			$arrayIndividu=$this->getIndividuCoordinates($data[$i]["id_individu"]);
			$res2.= '<tr><td>'.($i+1);
			$res2.='</td><td>'.$data[$i]["libelle_cotisation"];
			$res2.='</td><td>'.$arrayIndividu["nom"];
			$res2.='</td><td>'.$arrayIndividu["contacts"];
			$res2.='</td><td>'.$arrayIndividu["date_naissance"];
			$res2.='</td><td>'.$data[$i]["montant_versement"];
			$res2.='</td><td>'.$data[$i]["montant_cotisation_organisme"];
			$res2.='</td><td>'.$data[$i]["montant_don"];
			$res2.='</td><td>'.$data[$i]["date_reglement"];
			$res2.='</td><td>'.$data[$i]["libelle_mode_reglement"];
			$res2.='</td><td>'.$data[$i]["numero_cheque"];
			$res2.='</td><td>'.$data[$i]["libelle_banque"];
			$res2.='</td><td>'.$data[$i]["id_recu_fiscal"];
			$res2.='</td><td>'.$data[$i]["date_envoi_recu_fiscal"];
			$res2.='</td><td>'.$data[$i]["date_envoi_timbre"];
//			$res2.='</td><td>'.$arrayIndividu["date_deces"];
			$res2.='</td><td>'.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n');
			$res2.='</td></tr>';
		}
		$res2.='</tbody>';
		$res2.='</table>'.$this->getUserStamp('n','o');
		$idindividus=substr($idindividus, 0,strlen($idindividus)-1);
		$criteres=$this->m_postvars["atkfiltre"];
		$titre="<h2><b>"."Cotisations"." </b>- ".$data[0]["organisme"]."</h2><b>Critères : </b><br/>".$criteres."<br/><br/>";
		$res2=$titre.$res2;
		$res2.="<br/><br/>".$this->admin_liste_operations($id_organisme, $idindividus);
		$this->page_output($res2);
		
	}
}
?>