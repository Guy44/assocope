<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgnumberexpressionattribute");
class requete extends assMetaNode {
	var $table = "biodiversite_requete";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function requete() {
		$this->atkMetaNode();
		$this->atkNode("requete",  NF_ADD_LINK | NF_EDITAFTERADD  | NF_MRA);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_organisme",
				"id_individu",
				"libelle",
				"description_html",
		"details",
		"nb_dates",
		"nb_taxinomies",
		"nb_organismes_commanditaires",
		"nb_organismes_observateurs",
		"nb_individus_observateurs",
		"nb_pays",
		"nb_lieux",
		"id_requete",
				"date_requete",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
				"Dates" => array (
				"dates"),

				"Ordres" => array (
				"taxons"),
				"Commanditaires" => array (
				"commanditaires"),
				"Commandités" => array (
				"commandites"),
				"Observateurs" => array (
				"observateurs"),
				//				"Pays" => array (
				//				"pays"),
				"Lieux" => array (
				"lieux")
				), AF_NO_LABEL));
				$this->add(new atgNumberExpressionAttribute("details", ' select count(id) from biodiversite_requete_detail
	 where id_requete =[table].id 					', 0, 0),138);
				$this->add(new atgNumberExpressionAttribute("nb_dates", ' select count(id) from biodiversite_requete_date_observation
	 where id_biodiversite_requete =[table].id 					', 0, 0),139);
				$this->add(new atgNumberExpressionAttribute("nb_taxinomies", ' select count(id) from biodiversite_requete_taxinomie
	 where id_biodiversite_requete =[table].id 					', 0, 0),140);
				$this->add(new atgNumberExpressionAttribute("nb_organismes_commanditaires", ' select count(id) from biodiversite_requete_organisme_commanditaire
	 where id_biodiversite_requete =[table].id 					', 0, 0),141);
				$this->add(new atgNumberExpressionAttribute("nb_organismes_observateurs", ' select count(id) from biodiversite_requete_organisme_observateur
	 where id_biodiversite_requete =[table].id 					', 0, 0),142);
				$this->add(new atgNumberExpressionAttribute("nb_individus_observateurs", ' select count(id) from biodiversite_requete_individu_observateur
	 where id_biodiversite_requete =[table].id 					', 0, 0),143);
				$this->add(new atgNumberExpressionAttribute("nb_pays", ' select count(id) from biodiversite_requete_pays_observation
	 where id_biodiversite_requete =[table].id 					', 0, 0),144);
				$this->add(new atgNumberExpressionAttribute("nb_lieux", ' select count(id) from biodiversite_requete_lieu_observation
	 where id_biodiversite_requete =[table].id 					', 0, 0),144);


				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),100);
				$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));

				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE));
				$this->add(new atkManyToOneRelation("id_requete", "profil.utilisateur", AF_READONLY| AF_HIDE_ADD| AF_HIDE_VIEW | AF_HIDE_EDIT| AF_FORCE_LOAD));
				$this->add(new atkDateTimeAttribute("date_requete", "Y-m-d", "hh:mm:ss",  AF_DATE_STRING | AF_READONLY| AF_HIDE_VIEW| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD));
				$this->add(new atkfckattribute("description_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '750px',
			'Height' => '300px'
			)));
			$this->add(new atkOneToManyRelation("dates", "biodiversite.requete_date_observation", "id_biodiversite_requete", AF_HIDE_LIST));
			$this->add(new atkOneToManyRelation("taxons", "biodiversite.requete_taxinomie", "id_biodiversite_requete", AF_HIDE_LIST));
			$this->add(new atkOneToManyRelation("commanditaires", "biodiversite.requete_organisme_commanditaire", "id_biodiversite_requete", AF_HIDE_LIST));
			$this->add(new atkOneToManyRelation("commandites", "biodiversite.requete_organisme_observateur", "id_biodiversite_requete", AF_HIDE_LIST));
			$this->add(new atkOneToManyRelation("observateurs", "biodiversite.requete_individu_observateur", "id_biodiversite_requete", AF_HIDE_LIST));
			//			$this->add(new atkOneToManyRelation("pays", "biodiversite.requete_pays_observation", "id_biodiversite_requete", AF_HIDE_LIST));
			$this->add(new atkOneToManyRelation("lieux", "biodiversite.requete_lieu_observation", "id_biodiversite_requete", AF_HIDE_LIST));

			$this->setSecurityAlias("organisme.organisme");
			$this->m_securityMap["requete"] = "view";
			$this->m_securityMap["tableau_export"] = "view";
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			//		$this->setOrder(" organisme_requete.date_creation DESC ");
			$this->setIndex("libelle");
	}
	function descriptor_def() {
		return " [libelle] ";
	}
	function nb_taxinomies_display($record, $mode) {
		if (isset ($record["nb_taxinomies"])) {
			$ret= href(dispatch_url("biodiversite.requete_taxinomie", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_taxinomies"]), SESSION_NESTED);
				if ($record["nb_taxinomies"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_organismes_commanditaires_display($record, $mode) {
		if (isset ($record["nb_organismes_commanditaires"])) {
			$ret= href(dispatch_url("biodiversite.requete_organisme_commanditaire", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_organismes_commanditaires"]), SESSION_NESTED);
				if ($record["nb_organismes_commanditaires"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_organismes_observateurs_display($record, $mode) {
		if (isset ($record["nb_organismes_observateurs"])) {
			$ret= href(dispatch_url("biodiversite.requete_organisme_observateur", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_organismes_observateurs"]), SESSION_NESTED);
				if ($record["nb_organismes_observateurs"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_individus_observateurs_display($record, $mode) {
		if (isset ($record["nb_individus_observateurs"])) {
			$ret= href(dispatch_url("biodiversite.requete_individu_observateur", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_individus_observateurs"]), SESSION_NESTED);
				if ($record["nb_individus_observateurs"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_pays_display($record, $mode) {
		if (isset ($record["nb_pays"])) {
			$ret= href(dispatch_url("biodiversite.requete_pays_observation", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_pays"]), SESSION_NESTED);
				if ($record["nb_pays"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}
	function nb_lieux_display($record, $mode) {
		if (isset ($record["nb_lieux"])) {
			$ret= href(dispatch_url("biodiversite.requete_lieu_observation", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_lieux"]), SESSION_NESTED);
				if ($record["nb_lieux"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}

	function details_display($record, $mode) {

		if (isset ($record["details"])) {
			$ret= href(dispatch_url("biodiversite.requete_detail", "admin", array (
				'atkfilter' => "biodiversite_requete_detail.id_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["details"]), SESSION_NESTED);
				if ($record["details"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}


	function nb_dates_display($record, $mode) {
		if (isset ($record["nb_dates"])) {
			$ret= href(dispatch_url("biodiversite.requete_date_observation", "admin", array (
				'atkfilter' => "id_biodiversite_requete='" . $record['id'] . "'"
				), "dispatch.php"), text($record["nb_dates"]), SESSION_NESTED);
				if ($record["nb_dates"]!=0)			return '<font color="red"><b>'.$ret.'</font></b>';
				else return $ret;
		} else {
			return "";
		}
	}

	function action_requete(& $handler) {
		$select = $this->m_postvars["atkselector"];
		if (count($select)==1)
		{
			$array_id= explode('=', $select[0]);
			$idrequete=$array_id[1];
		}
		else
		{
			echo 'Une ligne et une seule doit être sélectionnée.';
			die();
		}

		global $g_user;
		$userutilisateur = $g_user["id"];
		$db = & atkGetDb();
		$db->query("delete from biodiversite_requete_detail where id_requete=".$idrequete." ");
		$db->query("update biodiversite_requete set id_requete=".$userutilisateur.", date_requete = UTC_TIMESTAMP() where id=".$idrequete." ");
		$data=$db->getrows("select libelle from biodiversite_requete where id=".$idrequete."");
		$commentaire="<b> Libellé de la requête : </b>".$data[0]["libelle"];
		$commentaire.="<br />";
		$sql="select nom, prenom  from individu i, app_utilisateur u
		 where u.id_individu =i.id and 
		 u.id='".$userutilisateur."'";

		$data=$db->getrows($sql);
		$commentaire.="<b> Requête exécutée par : </b>".$data[0]["prenom"]." ".$data[0]["nom"]." le ".gmdate('c')."<br />";
		$data=$db->getrows("select date_debut_observation, date_fin_observation, exclure_o_n
		from biodiversite_requete_date_observation
		where id_biodiversite_requete =".$idrequete." ");
		$date_condition='';
		$date_inclure="";
		$date_exclure="";
		$commentaire.="<b>Dates : </b><br />";
		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$date_exclure .= " o.date_observation not between '".$data[$i]["date_debut_observation"] ."' and '".$data[$i]["date_fin_observation"] ."' and ";
				$commentaire.=" Pas entre le ".$data[$i]["date_debut_observation"]. " et le ".$data[$i]["date_fin_observation"]."<br />";}
				else
				{$date_inclure .= " o.date_observation between '".$data[$i]["date_debut_observation"] ."' and '".$data[$i]["date_fin_observation"] ."' or ";
				$commentaire.=" Entre le ".$data[$i]["date_debut_observation"]. " et le ".$data[$i]["date_fin_observation"]."<br />";}
			}
			if (strlen($date_exclure)>0)
			{$date_exclure=substr($date_exclure, 0, strlen($date_exclure)-4) ;

			}
			if (strlen($date_inclure)>0)
			{$date_inclure=substr($date_inclure, 0, strlen($date_inclure)-3) ;
			}
		}
		else
		{
			$commentaire.="Toutes dates<br />";
		}

		$data=$db->getrows("select id_individu_observateur,i.prenom, i.nom , exclure_o_n
		from biodiversite_requete_individu_observateur, individu i
		where id_biodiversite_requete =".$idrequete." 
		and biodiversite_requete_individu_observateur.id_individu_observateur=i.id ");
		$individu_observateur_condition='';
		$individu_observateur_inclure='';
		$individu_observateur_exclure='';
		$commentaire.="<b>Individus observateurs : </b><br />";
		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$individu_observateur_exclure .= "'".$data[$i]["id_individu_observateur"] ."',";
				$commentaire.= "Exclure : ". $data[$i]["prenom"] ." ".$data[$i]["nom"]."<br />";}
				else
				{$individu_observateur_inclure .= "'".$data[$i]["id_individu_observateur"] ."',";
				$commentaire.= "Inclure : ". $data[$i]["prenom"] ." ".$data[$i]["nom"]."<br />";}
			}
			if (strlen($individu_observateur_exclure)>0)
			{$individu_observateur_exclure="o.id_observateur not in ( ".substr($individu_observateur_exclure, 0, strlen($individu_observateur_exclure)-1).")" ;

			}
			if (strlen($individu_observateur_inclure)>0)
			{$individu_observateur_inclure="o.id_observateur in ( ".substr($individu_observateur_inclure, 0, strlen($individu_observateur_inclure)-1).")" ;
			}
		}
		else
		{
			$commentaire.="Tous individus observateurs<br />";
		}

		$data=$db->getrows("select id_lieu_observation, exclure_o_n, l.adresse1,l.adresse2,cp.code_postal, cp.ville, l.longitude, l.latitude
		from biodiversite_requete_lieu_observation, lieu l, type_cp_ville_pays cp
		where id_biodiversite_requete =".$idrequete." 
		 and id_lieu_observation=l.id
		 and l.id_ville=cp.id");
		$lieu_observation_condition='';
		$lieu_observation_inclure='';
		$lieu_observation_exclure='';
		$commentaire.="<b>Lieux d'observation : </b><br />";
		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$lieu_observation_exclure .= "'".$data[$i]["id_lieu_observation"] ."',";
				$commentaire.= "Exclure : ". $data[$i]["adresse1"] ." ".$data[$i]["adresse2"]." ".$data[$i]["code_postal"]." ".$data[$i]["ville"]
				." (".$data[$i]["longitude"]." ".$data[$i]["latitude"].")<br />";}
				else
				{$lieu_observation_inclure .= "'".$data[$i]["id_lieu_observation"] ."',";
				$commentaire.= "Inclure : ". $data[$i]["adresse1"] ." ".$data[$i]["adresse2"]." ".$data[$i]["code_postal"]." ".$data[$i]["ville"]
				." (".$data[$i]["longitude"]." ".$data[$i]["latitude"].")<br />";}
			}
			if (strlen($lieu_observation_exclure)>0)
			{$lieu_observation_exclure="o.id_lieu not in ( ".substr($lieu_observation_exclure, 0, strlen($lieu_observation_exclure)-1).")" ;
			}
			if (strlen($lieu_observation_inclure)>0)
			{$lieu_observation_inclure="o.id_lieu in ( ".substr($lieu_observation_inclure, 0, strlen($lieu_observation_inclure)-1).")" ;
			}
		}
		else
		{
			$commentaire.="Tous lieux d'observations<br />";
		}


		$data=$db->getrows("select id_organisme_commanditaire, o.nom, exclure_o_n
		from biodiversite_requete_organisme_commanditaire, organisme o
		where id_biodiversite_requete =".$idrequete." 
		and biodiversite_requete_organisme_commanditaire.id_organisme_commanditaire=o.id");
		$organisme_commanditaire_condition='';
		$organisme_commanditaire_inclure='';
		$organisme_commanditaire_exclure='';
		$commentaire.="<b>Organismes commanditaires : </b><br />";
		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$organisme_commanditaire_exclure .= "'".$data[$i]["id_organisme_commanditaire"] ."',";
				$commentaire.= "Exclure : ". $data[$i]["nom"] ."<br />";
				}
				else
				{$organisme_commanditaire_inclure .= "'".$data[$i]["id_organisme_commanditaire"] ."',";
				$commentaire.= "Inclure : ". $data[$i]["nom"] ."<br />";}
			}
			if (strlen($organisme_commanditaire_exclure)>0)
			{$organisme_commanditaire_exclure="o.id_organisme not in ( ".substr($organisme_commanditaire_exclure, 0, strlen($organisme_commanditaire_exclure)-1).")" ;
			}
			if (strlen($organisme_commanditaire_inclure)>0)
			{$organisme_commanditaire_inclure="o.id_organisme in ( ".substr($organisme_commanditaire_inclure, 0, strlen($organisme_commanditaire_inclure)-1).")" ;
			}
		}
		else
		{
			$commentaire.="Tous organismes commanditaires<br />";
		}

		$data=$db->getrows("select id_organisme_observateur,  o.nom,exclure_o_n
		from biodiversite_requete_organisme_observateur , organisme o
		where id_biodiversite_requete =".$idrequete." 
		and biodiversite_requete_organisme_observateur.id_organisme_observateur=o.id");
		$organisme_observateur_condition='';
		$organisme_observateur_inclure='';
		$organisme_observateur_exclure='';
		$commentaire.="<b>Organismes observateurs : </b><br />";
		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$organisme_observateur_exclure .= "'".$data[$i]["id_organisme_observateur"] ."',";
				$commentaire.= "Exclure : ". $data[$i]["nom"] ."<br />";}
				else
				{$organisme_observateur_inclure .= "'".$data[$i]["id_organisme_observateur"] ."',";
				$commentaire.= "Inclure : ". $data[$i]["nom"] ."<br />";}
			}
			if (strlen($organisme_observateur_exclure)>0)
			{$organisme_observateur_exclure="o.id_organisme_observateur not in ( ".substr($organisme_observateur_exclure, 0, strlen($organisme_observateur_exclure)-1).")" ;
			}
			if (strlen($organisme_observateur_inclure)>0)
			{$organisme_observateur_inclure="o.id_organisme_observateur in ( ".substr($organisme_observateur_inclure, 0, strlen($organisme_observateur_inclure)-1).")" ;
			}
		}
		else
		{
			$commentaire.="Tous organismes observateurs <br />";
		}

		/*
		 $data=$db->getrows("select id_pays_observation, exclure_o_n
		 from biodiversite_requete_pays_observation
		 where id_biodiversite_requete =".$idrequete." ");
		 */

		$sqlcondition ="";
		if (strlen($date_exclure) >0) $sqlcondition.=$date_exclure;
		if (strlen($date_inclure) >0) $sqlcondition.=' and '.$date_inclure;
		if (strlen($individu_observateur_exclure) >0) $sqlcondition.=' and '.$individu_observateur_exclure;
		if (strlen($individu_observateur_inclure) >0) $sqlcondition.=' and '.$individu_observateur_inclure;
		if (strlen($lieu_observation_exclure) >0) $sqlcondition.=' and '.$lieu_observation_exclure;
		if (strlen($lieu_observation_inclure) >0) $sqlcondition.=' and '.$lieu_observation_inclure;
		if (strlen($organisme_commanditaire_exclure) >0) $sqlcondition.=' and '.$organisme_commanditaire_exclure;
		if (strlen($organisme_commanditaire_inclure) >0) $sqlcondition.=' and '.$organisme_commanditaire_inclure;
		if (strlen($organisme_observateur_exclure) >0) $sqlcondition.=' and '.$organisme_observateur_exclure;
		if (strlen($organisme_observateur_inclure) >0) $sqlcondition.=' and '.$organisme_observateur_inclure;

		if (substr($sqlcondition,0,4)==' and') $sqlcondition=substr($sqlcondition,4);
		$rows=$db->getrows("select od.id_taxinomie as id_taxinomie, count(od.id_taxinomie) as nombre_observations, sum(od.nombre) as nombre
		from biodiversite_observation_detail od, 
		biodiversite_observation o
		where ". $sqlcondition."
		 and o.id=od.id_observation 
		 group by od.id_taxinomie
		 order by od.id_taxinomie");


		for ($i = 0; $i < count($rows); $i++) {
			$taxinomie=$rows[$i]["id_taxinomie"];
			$nombre_observations=$rows[$i]["nombre_observations"];
			$nombre_individus=$rows[$i]["nombre"];
			$sql="SELECT  t.nom_binomial, t.nom_francais, t.id,  t.id_parent 
			from biodiversite_taxinomie t , biodiversite_rang_taxinomique r
			 where t.id='".$rows[$i]["id_taxinomie"]."'
			  and t.id_rang_taxinomique=r.id  ";

			$data=$db->getrows($sql);
			$nbtaxinomie=$data[0]["nom_binomial"];
			$nftaxinomie=$data[0]["nom_francais"];
			$nftaxinomie=ucfirst(str_replace("'","\'",$nftaxinomie));
			$id_parent=$data[0]["id_parent"];
			while (isset($id_parent))
			{
				$sql="SELECT  t.nom_binomial, t.id,  t.id_parent  , r.rang_inpn
			from biodiversite_taxinomie t , biodiversite_rang_taxinomique r
			 where t.id='".$id_parent."'
			  and t.id_rang_taxinomique=r.id ";
				$data=$db->getrows($sql);
				//				print_r ($data);
				$id_parent=$data[0]["id_parent"];
				if ($data[0]["rang_inpn"]=='KD')
				{ $kd=$data[0]["id"];
				$nbkd=$data[0]["nom_binomial"];}
				if ($data[0]["rang_inpn"]=='PH')
				{$ph=$data[0]["id"];
				$nbph=$data[0]["nom_binomial"];}
				if ($data[0]["rang_inpn"]=='CL')
				{$cl=$data[0]["id"];
				$nbcl=$data[0]["nom_binomial"];}
				if ($data[0]["rang_inpn"]=='OR')
				{$or=$data[0]["id"];
				$nbor=$data[0]["nom_binomial"];}
				if ($data[0]["rang_inpn"]=='FM')
				{$fm=$data[0]["id"];
				$nbfm=$data[0]["nom_binomial"];}

			}

			$sqlinsert="INSERT INTO biodiversite_requete_detail
		( 
		id_requete,
  		id_regnum,
  		n_b_regnum,
  		id_phylum,
  		n_b_phylum,
  		id_classis,
  		n_b_classis,
  		id_ordo,
  		n_b_ordo,
  		id_famille,
  		n_b_famille,
  		id_species,
  		n_b_species,
  		nom_francais,
  		nombre_individus,
  		nombre_observations,
  		commentaire,
  		id_creation,
  		date_creation,
  		id_modification,
  		date_modification
  		)
  Values 
		( 
		".$idrequete.",
		'".$kd."',
		'".$nbkd."',
		'".$ph."',
		'".$nbph."',
		'".$cl."',
		'".$nbcl."',
		'".$or."',
		'".$nbor."',
		'".$fm."',
		'".$nbfm."',
		'".$taxinomie."',
		'".$nbtaxinomie."',
		'".$nftaxinomie."',
		'".$nombre_individus."',
		'".$nombre_observations."',
  		'',
  		$userutilisateur,
  		UTC_TIMESTAMP(),
  		$userutilisateur,
  		UTC_TIMESTAMP()
  		)
  "	;
  		$db->query($sqlinsert);
		}

		$data=$db->getrows("select r.id_taxinomie, r.exclure_o_n
		from biodiversite_requete_taxinomie r
		where r.id_biodiversite_requete =".$idrequete." 
		");
		$commentaire.="<b>Ordres : </b><br />";
		$taxinomie_condition='';
		$taxinomie_inclure='';
		$taxinomie_exclure='';

		if (count($data)>0)
		{
			for ($i = 0; $i < count($data); $i++) {
				if ($data[$i]["exclure_o_n"]==1)
				{$taxinomie_exclure .= "'".$data[$i]["id_taxinomie"] ."',";
				$data1=$db->getrows("select t.id, t.nom_binomial, r.nom_francais, r.rang_inpn
						 from biodiversite_taxinomie t, biodiversite_rang_taxinomique r
						where t.id='".$data[$i]["id_taxinomie"]."'
						 and t.id_rang_taxinomique=r.id
						 ");
				$commentaire.= "Exclure : ". $data1[0]["nom_binomial"] ." (".$data1[0]["nom_francais"].")<br />";
				//			if ($data1[0]["rang_inpn"]=="SP")
				//			 $db->query("delete from biodiversite_requete_detail where id_species ='".$data1[0]["id"]."' ");

				}
				else
				{$taxinomie_inclure .= "'".$data[$i]["id_taxinomie"] ."',";
				$data1=$db->getrows("select t.nom_binomial, r.nom_francais, r.rang_inpn
						 from biodiversite_taxinomie t, biodiversite_rang_taxinomique r
						where t.id='".$data[$i]["id_taxinomie"]."'
						 and t.id_rang_taxinomique=r.id
						 ");
				//							$this->p($taxinomie_inclure);
				$commentaire.= "Inclure : ". $data1[0]["nom_binomial"] ." (".$data1[0]["nom_francais"].")<br />";}
			}
			if (strlen($taxinomie_exclure)>0)
			{$taxinomie_exclure="id_ordo  in ( ".substr($taxinomie_exclure, 0, strlen($taxinomie_exclure)-1).")" ;
			$db->query("delete from  biodiversite_requete_detail where id_requete=".$idrequete." and ".$taxinomie_exclure." ");
			}
			if (strlen($taxinomie_inclure)>0)
			{$taxinomie_inclure="id_ordo not in ( ".substr($taxinomie_inclure, 0, strlen($taxinomie_inclure)-1).")" ;

			$db->query("delete from  biodiversite_requete_detail where id_requete=".$idrequete." and ".$taxinomie_inclure." ");
			}
		}
		else
		{
			$commentaire.="Tous ordres </br>";
		}




		$commentaire=str_replace( "'", "\'", $commentaire);
		$db->query("update biodiversite_requete set description_html='".$commentaire."' where id=".$idrequete." ");
$this->redirect();

		//		header("Location: $url");
		//		exit;

	}

	function action_tableau_export(& $handler) {
		$select = $this->m_postvars["atkselector"];
		if (count($select)==1)
		{
			$array_id= explode('=', $select[0]);
			$idrequete=$array_id[1];
		}
		else
		{
			echo 'Une ligne et une seule doit être sélectionnée.';
			die();
		}
		$tbl = & atknew("atk.utils.atktablerenderer");
		$sql=	"SELECT
  		description_html
  from
  biodiversite_requete
  where id=".$idrequete." 	
  		 ";
		$db = & atkGetDb();
		$data=$db->getrows($sql);

		$description_html=	$data[0]["description_html"];
	
		$sql=	"SELECT
  		n_b_regnum,
  		n_b_phylum,
  		n_b_classis,
  		n_b_ordo,
  		n_b_famille,
  		n_b_species,
  		cd_nom ,
  		bst.code_statut,
  		bst.statut,
  		bt.nom_francais,
  		nombre_individus,
  		nombre_observations
  from
  biodiversite_requete_detail brd, biodiversite_taxinomie bt left outer join biodiversite_statut_taxinomique bst on bt.id_statut_france_metropole=bst.id
  where id_requete=".$idrequete." and brd.id_species=bt.id
  		 ";

		$stuff=$db->getrows($sql);

		$tableau=$description_html;
		if (count($stuff)>0)
		{

			$tbl->setRowClass(1, "superbold");
			// ....
			// Create data
//			$row = array ();
//			$row[] = $tableau;
//			$data[] = $row;
			$row=array();
			$row[]="Rang";
			$row[]="Règne";
			$row[]="Phylum";
			$row[]="Classe";
			$row[]="Ordre";
			$row[]="Famille";
			$row[]="Espèce";
			$row[]="Taxon INPN";
			$row[]="Code statut";
			$row[]="Statut";
			$row[]="Nom_francais";
			$row[]="Nombre d'individus";
			$row[]="Nombre d'observations";
			$data[] = $row;

			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$row = array ();
				$row[] = $i +1;
				$row[]=$stuff[$i]["n_b_regnum"];
				$row[]=$stuff[$i]["n_b_phylum"];
				$row[]=$stuff[$i]["n_b_classis"];
				$row[]=$stuff[$i]["n_b_ordo"];
				$row[]=$stuff[$i]["n_b_famille"];
				$row[]=$stuff[$i]["n_b_species"];
				$row[]=$stuff[$i]["cd_nom"];
				$row[]=$stuff[$i]["code_statut"];
				$row[]=$stuff[$i]["statut"];
				$row[]=ucfirst($stuff[$i]["nom_francais"]);
				$row[]=$stuff[$i]["nombre_individus"];
				$row[]=$stuff[$i]["nombre_observations"];
				$data[] = $row;
			}
			$res = $tableau;
			$res .= $tbl->render($data, 0, "recordlist");
							$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $res);






		}
			
			
	}
	function recordActions($rec, & $actions, & $mraactions) {

		$mraactions['delete'] = "delete";
		$mraactions['requete'] = "requete";
		$mraactions['tableau_export'] = "tableau_export";

	}


}
?>