<?php

class tableaudebord extends assMetaNode {
	var $m_toc = "";
	var $m_nombredesujets = 0;
	var $m_solde_tresorerie = 0;
	var $m_nombredesujets_niveau_2 = 0;
	var $m_aide = "";

	var $recapitulatif=array();
	function tableaudebord() {
		$this->atkMetaNode();
		$this->atkNode("tableaudebord");
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["tableau_organisme"] = "view";
		$this->m_securityMap["tableau_detail_organisme"] = "view";
		$this->m_securityMap["tableau_individu"] = "view";
		$this->m_securityMap["tableau_logs"] = "view";
	}
	function action_tableau_individu(& $handler) {

	}

	
	function action_tableau_organisme(& $handler) {
		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();
		$data=$db->getrows("select nom, date_initialisation_comptabilite from organisme where id=$id_organisme");
		$nom_organisme=$data[0]["nom"];
		$date_initialisation_comptabilite=$data[0]["date_initialisation_comptabilite"];
		$this->m_toc=$this->gettitre($nom_organisme,"Tableaux de bord",false,"h1");
		$texte="Module ".$this->m_module.'.'.$this->m_type;
		$texte=str_replace(' ', '_', $texte);
		$aide=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)),
				'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Button-Help-icon.png" alt="AssoCope wiki" title="Aide sur les tableaux de bord" target="_blank"></img>'
				,	SESSION_NEW,	false,  ' target="_blank"');
		$aide.=' <a href="https://groups.google.com/forum/#!forum/assocope" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/user-group-icon.png" alt="Forum AssoCope" title="Forum AssoCope" target="_blank"></img></a>';
		$this->m_aide=$aide;
		$this->m_toc.='<table id="toc" class="toc  sortable"><tr><td><div id="toctitle">
				<h2>Table des matières ( <a href="index.php?atklogout=1" target="_top"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/deconnexion.png" alt="Déconnexion"
				title="Déconnexion" ></img></a> '.$aide.' ) </h2></div><ol>';



		// Organisme
		//   Logo, tél, courriel, site internet, calendrier public, Objectifs
		$res_coordonnees="<center>".$this->stats_coordonnees_display($id_organisme)."</center>";
		//   Plaquette, Statuts, Numéro d'assoc en préfecture, déclaré le, publié JO, Indemnité km, indemnité heure, fédération
		//   Déclaration préfecture
		// Traitements
		// Immatriculations
		$res_immatriculations="<center>".$this->stats_immatriculations_display($id_organisme)."</center>";
		// Patrimoine
		$res_patrimoine="<center>".$this->stats_patrimoine_display($id_organisme)."</center>";
		// Contrats
		$res_contrats="<center>".$this->stats_contrats_display($id_organisme)."</center>";
		// Domaines
		$res_domaines="<center>".$this->stats_domaines_display($id_organisme)."</center>";
		// Référencements
		$res_referencements="<center>".$this->stats_referencements_display($id_organisme)."</center>";
		// Inscriptions :
		$res_inscriptions="<center>".$this->stats_inscriptions_display($id_organisme)."</center>";
		// Adhésions
		$res_adhesions="<center>".$this->stats_adhesions_display($id_organisme)."</center>";
		// Radiations
		$res_radiations="<center>".$this->stats_radiations_display($id_organisme)."</center>";
		// Fonctions
		$res_fonctions="<center>".$this->stats_fonctions_display($id_organisme)."</center>";
		// Contacts
		// Cotisations
		$res_cotisations="<center>".$this->stats_cotisations_display($id_organisme)."</center>";
		// Gazettes
		$res_gazettes="<center>".$this->stats_gazettes_display($id_organisme)."</center>";
		// Rencontres
		$res_rencontres="<center>".$this->stats_rencontres_display($id_organisme)."</center>";
		// Contacts
		$res_contacts="<center>".$this->stats_contacts_display($id_organisme)."</center>";
		// Résultats
		($date_initialisation_comptabilite!="") ? $res_resultats_comptables="<center>".$this->stats_resultats_comptables_display($id_organisme)."</center>" : null;
		// Documents
		$res_documents="<center>".$this->stats_documents_display($id_organisme)."</center>";
		$res=$this->m_toc."</ol></td></tr></table>";
		$res.$res.=$this->getUserStamp('n','o');
		$res.=$this->sautDePage();

		$res.=$res_coordonnees;
		$res.=$this->sautDePage();
		if ($res_immatriculations!="")
		{
			$res.=$res_immatriculations;
			$res.=$this->sautDePage();
		}
		if ($res_patrimoine!="")
		{
			$res.=$res_patrimoine;
			$res.=$this->sautDePage();
		}
		if ($res_contrats!="")
		{
			$res.=$res_contrats;
			$res.=$this->sautDePage();
		}
		if ($res_domaines!="")
		{
			$res.=$res_domaines;
			$res.=$this->sautDePage();
		}
		if ($res_referencements!="")
		{
			$res.=$res_referencements;
			$res.=$this->sautDePage();
		}
		$res.=$res_inscriptions;
		$res.=$this->sautDePage();
		$res.=$res_adhesions;
		$res.=$this->sautDePage();
		$res.=$res_radiations;
		$res.=$this->sautDePage();
		$res.=$res_fonctions;
		$res.=$this->sautDePage();

		$res.=$res_cotisations;
		$res.=$this->sautDePage();
		$res.=$res_gazettes;
		$res.=$this->sautDePage();
		$res.=$res_rencontres;
		$res.=$this->sautDePage();
		if ($res_contacts!="")
		{
			$res.=$res_contacts;
			$res.=$this->sautDePage();
		}
		$res.=$this->sautDePage();
		if ($date_initialisation_comptabilite!="" && $res_resultats_comptables!="")
		{
			$res.=$res_resultats_comptables;
			$res.=$this->sautDePage();
		}
		if ($res_documents!="")
		{
			$res.=$res_documents;
			$res.=$this->sautDePage();
		}

		//		$res=$this->table_test();
		$this->page_output($res);

	}
	function action_tableau_detail_organisme(& $handler) {
		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();
		$data=$db->getrows("select nom, date_initialisation_comptabilite from organisme where id=$id_organisme");
		$nom_organisme=$data[0]["nom"];
		$date_initialisation_comptabilite=$data[0]["date_initialisation_comptabilite"];
		$this->m_toc=$this->gettitre($nom_organisme,"Tableaux de bord",false,"h1");
		$texte="Module ".$this->m_module.'.'.$this->m_type;
		$texte=str_replace(' ', '_', $texte);
		$aide=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)),
				'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Button-Help-icon.png" alt="AssoCope wiki" title="Aide sur les tableaux de bord" target="_blank"></img>'
				,	SESSION_NEW,	false,  ' target="_blank"');
		$aide.=' <a href="https://groups.google.com/forum/#!forum/assocope" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/user-group-icon.png" alt="Forum AssoCope" title="Forum AssoCope" target="_blank"></img></a>';
				
		$this->m_aide=$aide;
		$this->m_toc.='<table id="toc" class="toc  sortable"><tr><td><div id="toctitle">
				<h2>Table des matières ( <a href="index.php?atklogout=1" target="_top"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/deconnexion.png" alt="Déconnexion"
				title="Déconnexion" ></img></a> '.$aide.' ) </h2></div><ol>';
	
		$detail_organisme=$this->m_postvars["nom_detail_tbdebord"];
		if ($detail_organisme=="Organisme")
		{$res_detail="<center>".$this->stats_coordonnees_display($id_organisme)."</center>";}
		if ($detail_organisme=="Immatriculations")
		{$res_detail="<center>".$this->stats_immatriculations_display($id_organisme)."</center>";}
		if ($detail_organisme=="Patrimoine")
		{$res_detail="<center>".$this->stats_patrimoine_display($id_organisme)."</center>";}
		if ($detail_organisme=="Contrats")
		{$res_detail="<center>".$this->stats_contrats_display($id_organisme)."</center>";}
		if ($detail_organisme=="Domaines internet")
		{$res_detail="<center>".$this->stats_domaines_display($id_organisme)."</center>";}
		if ($detail_organisme=="Référencements")
		{$res_detail="<center>".$this->stats_referencements_display($id_organisme)."</center>";}
		if ($detail_organisme=="Inscriptions")
		{$res_detail="<center>".$this->stats_inscriptions_display($id_organisme)."</center>";}
		if ($detail_organisme=="Adhésions") 
		{$res_detail="<center>".$this->stats_adhesions_display($id_organisme)."</center>";}
		if ($detail_organisme=="Radiations")
		{$res_detail="<center>".$this->stats_radiations_display($id_organisme)."</center>";}
		if ($detail_organisme=="Fonctions")
		{$res_detail="<center>".$this->stats_fonctions_display($id_organisme)."</center>";}
		if ($detail_organisme=="Cotisations")
		{$res_detail="<center>".$this->stats_cotisations_display($id_organisme)."</center>";}
		if ($detail_organisme=="Gazettes")
		{$res_detail="<center>".$this->stats_gazettes_display($id_organisme)."</center>";}
		if ($detail_organisme=="Rencontres")
		{$res_detail="<center>".$this->stats_rencontres_display($id_organisme)."</center>";}
		if ($detail_organisme=="Contacts")
		{$res_detail="<center>".$this->stats_contacts_display($id_organisme)."</center>";}
		if ($detail_organisme=="Résultats comptables")
		{$res_detail="<center>".$this->stats_resultats_comptables_display($id_organisme)."</center>";}
		if ($detail_organisme=="Documents")
		{$res_detail="<center>".$this->stats_documents_display($id_organisme)."</center>";}
		/*
	
		
		Radiations
		
		
		
		Rencontres
		Contacts
		Résultats comptables
		Finances
		Dépenses
		Recettes
		Contributions volontaires
		Résultats
		Documents
		*/
		
		$res=$this->m_toc."</ol></td></tr></table>";
		$res.$res.=$this->getUserStamp('n','o');
		$res.=$this->sautDePage();
	
		$res.=$res_detail;
	
		$this->page_output($res);
	
	
	
	
	}
	function action_tableau_logs(& $handler) {
		global $g_sessionManager;
		$administrateur = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
		$db = & atkGetDb();
		//		echo "Bon";die();
		$this->m_toc=$this->gettitre("Logs","Tableaux de bord",false,"h1");
		$this->m_toc.='<table id="toc" class="toc  sortable"><tr><td><div id="toctitle"><h2>Table des matières ( <a href="index.php?atklogout=1" target="_top"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/deconnexion.png" alt="Déconnexion"
				title="Déconnexion" ></img></a> )</h2></div><ol>';
		$res_logs_2="<center>".$this->stats_logs_display($id_organisme,"heure","utilisateur")."</center>";
		$res_logs_4="<center>".$this->stats_logs_display($id_organisme,"jour","utilisateur")."</center>";
		$res_logs_6="<center>".$this->stats_logs_display($id_organisme,"mois","utilisateur")."</center>";
		//		$res_logs_7="<center>".$this->stats_logs_display($id_organisme,"total","utilisateur")."</center>";
		$res_logs_1="<center>".$this->stats_logs_display($id_organisme,"heure","node_action")."</center>";
		$res_logs_3="<center>".$this->stats_logs_display($id_organisme,"jour","node_action")."</center>";
		//		$res_logs_5="<center>".$this->stats_logs_display($id_organisme,"mois","node_action")."</center>";
		$res_ip_logs="<center>".$this->stats_ip_logs_display()."</center>";
		$res_logs_error_jour="<center>".$this->stats_logs_display($id_organisme,"jour","error")."</center>";

		$res=$this->m_toc."</ol></td></tr></table>";
		$res.=$this->getUserStamp('n','o');
		$res.=$this->sautDePage();
		$res.=$res_logs_2;
		$res.=$res_logs_4;
		$res.=$res_logs_6;
		//		$res.=$res_logs_7;
		$res.=$res_logs_1;
		$res.=$res_logs_3;
		//		$res.=$res_logs_5;
		$res.=$res_ip_logs;
		$res.=$res_logs_error_jour;
		$res.=$this->sautDePage();
		$this->page_output($res);

	}
	function gettitre($nom_organisme, $texte, $toc,$header,$niveau="1")
	{
		if ($toc==true)
		{
			if ($niveau=="1")
			{
				$numero=++$this->m_nombredesujets;
				$this->m_toc.='<li class="toclevel-1 tocsection-1"><a href="'.$this->curPageURL().'#sujet'.$numero.'" id="menu'.$numero.'" >'. $texte.'</a></li>';
				$retour='<b>'.$numero.". ".$texte.' </b>';
				$retour.=' ( <a id="sujet'.$numero.'" href="'.$this->curPageURL().'#menu'.$numero.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Home-icon.png" alt="Retour à la table des matières"
						title="Retour à la table des matières" ></img></a> <a href="index.php?atklogout=1" target="_top"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/deconnexion.png" alt="Déconnexion"
						title="Déconnexion" ></img></a> '.$this->m_aide.' )<br/>';
			}
			if ($niveau=="2")
			{
				$numero=++$this->m_nombredesujets_niveau_2;
				$numero=$this->m_nombredesujets.".".$numero;
				$this->m_toc.='<li class="toclevel-1 tocsection-1"><a href="'.$this->curPageURL().'#sujet'.$numero.'" id="menu'.$numero.'" >'. $texte.'</a></li>';
				$retour='<b>'.$numero.". ".$texte.' </b>';
				$retour.=' ( <a id="sujet'.$numero.'" href="'.$this->curPageURL().'#menu'.$numero.'"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Home-icon.png" alt="Retour à la table des matières"
						title="Retour à la table des matières" ></img></a> <a href="index.php?atklogout=1" target="_top"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/deconnexion.png" alt="Déconnexion"
						title="Déconnexion" ></img></a> '.$this->m_aide.' )<br/>';
			}
		}

		else
		{
			$retour="<b>".$texte." </b>- ".$nom_organisme."<br/>";
		}
		if ($header=="")
		{
		}
		else
		{
			$retour='<'.$header.'>'.$retour.'</'.$header.'>';
		}
		return $retour;
	}
	function stats_inscriptions_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Inscriptions",true,"h2");
		$res2=$this->gettitre($id_organisme,"Types d'inscriptions",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Inscriptions");
		if ($AnMinimum<=0) return false;

		$sql=" SELECT distinct ti.libelle, ti.id
		from individu_inscription ii , type_inscription ti
		where ii.id_organisme=$id_organisme
		and ii.id_type_inscription = ti.id
		order by ti.libelle";
		$data = $db->getrows($sql);
		$res .= '<table class="toc sortable">';
		$res2.= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum);
		$res.='</thead><tbody>';

		$res2.= '<thead><tr><th>Caractéristiques';
		$res2.='</th><th>Lettre';
		$res2.='</th><th>Infolettre';
		$res2.='</th><th>Flash';
		$res2.='</th><th>Cotisation';
		$res2.='</th><th>Tarif';
		$res2.='</th><th>Cotisation<br/>fédération';
		$res2.='</th><th>Carte';
		$res2.='</th><th>Timbre';
		$res2.='</th><th>Délai radiation<br/>pour<br/>non adhésion';
		$res2.='</th><th>Délai radiation<br/>pour<br/>non cotisation';
		$res2.='</th><th>Inscription<br/>d\'organisme';
		$res2.='</th><th>Modifiable';
		$res2.='</th></tr></thead><tbody>';
		$AnDepart=date("Y");
		for ($i=0;$i<count($data);$i++)
		{
			$res .= "<tr><td ".$this->m_styleTitreLigne.">".$data[$i]["libelle"];
			$sql=" SELECT `inscription_organisme_o_n` ,
					`lettre_o_n` ,
					`infolettre_o_n` ,
					`flash_info_o_n` ,
					`cotisation_organisme_o_n`,
					`tarif`,
					`cotisation_federation_o_n`,
					`carte_o_n`,
					`timbre_o_n` ,
					`delai_radiation_non_adhesion`,
					`delai_radiation_non_cotisation`,
					`modifiable_o_n`
					from type_inscription
					where id=".$data[$i]["id"];
			$datatype = $db->getrows($sql);
			$res2.= "<tr><td ".$this->m_styleTitreLigne.">".$data[$i]["libelle"];
			$res2.='</td><td>'.$this->oui_non($datatype[0]["lettre_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["infolettre_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["flash_info_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["cotisation_organisme_o_n"]);
			$res2.='</td><td>'.$this->nombre_format($datatype[0]["tarif"],"b");
			$res2.='</td><td>'.$this->oui_non($datatype[0]["cotisation_federation_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["carte_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["timbre_o_n"]);
			$res2.='</td><td>'.$this->nombre_format($datatype[0]["delai_radiation_non_adhesion"],"b");
			$res2.='</td><td>'.$this->nombre_format($datatype[0]["delai_radiation_non_cotisation"],"b");
			$res2.='</td><td>'.$this->oui_non($datatype[0]["inscription_organisme_o_n"]);
			$res2.='</td><td>'.$this->oui_non($datatype[0]["modifiable_o_n"]);
			$res2.='</td></tr>';

			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_inscription($id_organisme,$j, $data[$i]["id"]);
			}
			$res.='</td><td>'.$this->calcul_inscription($id_organisme,null, $data[$i]["id"]);
			$res.='</td></tr>';
		}
		$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_inscription($id_organisme,$j, null);
		}
		$res.='</td><td>'.$this->calcul_inscription($id_organisme,null, null);
		
		$res2.='</tbody></table>';
		$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		$res.=$res2.$this->getUserStamp('o','o');
		return $res;
	}
	function stats_adhesions_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Adhésions",true,"h2");

		$AnMinimum=$this->getAnMinimum($id_organisme,"Adhésions");
		if ($AnMinimum<=0) return false;

		$sql=" SELECT distinct ti.libelle, ti.id
		from individu_inscription ii , type_inscription ti
		where ii.id_organisme=$id_organisme
		and ii.date_adhesion is not null
		order by ti.libelle";
		$data = $db->getrows($sql);
		$res.= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		$res .= "<tr><td ".$this->m_styleTitreLigne.">Adhésions";
		$AnDepart=date("Y");
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_adhesion($id_organisme,$j);
		}
		$res.='</td><td>'.$this->calcul_adhesion($id_organisme,null);

		$res.='</td></tr></tbody></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_radiations_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Radiations",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Radiations");
		if ($AnMinimum<=0) return false;
		/*	$sql=" SELECT distinct ti.libelle, ti.id
		 from individu_inscription ii , type_inscription ti
		where ii.id_organisme=$id_organisme
		and ii.date_radiation is not null
		order by ti.libelle";
		*/
		$sql=" SELECT distinct tr.libelle, tr.id
		from individu_inscription ii
		LEFT JOIN type_radiation tr ON ii.id_type_radiation=tr.id
		where ii.id_organisme=$id_organisme
		and ii.date_radiation is not null
		order by tr.libelle";

		$data0 = $db->getrows($sql);
		$res .= '<table class="toc  sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		for ($i=0;$i<count($data0);$i++)
		{
			$type_radiation=$data0[$i]["id"];
			$libelle_radiation=$data0[$i]["libelle"];
			$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_radiation";
			$AnDepart=date("Y");
			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_radiation($id_organisme,$j,$type_radiation);
			}
			$res.='</td><td>'.$this->calcul_radiation($id_organisme,null,$type_radiation);
			$res.='</td></tr>';
		}
		$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_radiation($id_organisme,$j,null);
		}
		$res.='</td><td>'.$this->calcul_radiation($id_organisme,null,null);
		$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_documents_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Documents",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Documents");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT
		distinct td.id as id_type_document,
		td.libelle as libelle_type_document
		from organisme_document od
		LEFT JOIN type_document td ON od.id_type_document=td.id
		where od.id_organisme=$id_organisme and td.id is not null
		order by td.libelle";
		$data0 = $db->getrows($sql);
		//		$this->p($data0);
		$res .= '<table class="toc  sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		for ($i=0;$i<count($data0);$i++)
		{
			$id_type_document=$data0[$i]["id_type_document"];
			$libelle_type_document=$data0[$i]["libelle_type_document"];
			$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_type_document";
			$AnDepart=date("Y");
			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_document($id_organisme,$j,$id_type_document);
			}
			$res.='</td><td>'.$this->calcul_document($id_organisme,null,$id_type_document);
			$res.='</td></tr>';
		}
		$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_document($id_organisme,$j,null);
		}
		$res.='</td><td>'.$this->calcul_document($id_organisme,null,null);
		$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_gazettes_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Gazettes",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Gazettes");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT
		distinct
		ta.id as id_type_audience,
		ta.libelle as libelle_audience
		from organisme_gazette og
		LEFT JOIN type_audience ta ON og.id_type_audience=ta.id
		where og.id_organisme=$id_organisme and ta.id is not null
		order by ta.libelle";
		$data0 = $db->getrows($sql);
		//		$this->p($data0);
		$res .= '<table class="toc  sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		for ($i=0;$i<count($data0);$i++)
		{
			$id_type_audience=$data0[$i]["id_type_audience"];
			$libelle_type_audience=$data0[$i]["libelle_audience"];
			$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_type_audience";
			$AnDepart=date("Y");
			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_gazette($id_organisme,$j,$id_type_audience);
			}
			$res.='</td><td>'.$this->calcul_gazette($id_organisme,null,$id_type_audience);
			$res.='</td></tr>';
		}
		$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_gazette($id_organisme,$j,null);
		}
		$res.='</td><td>'.$this->calcul_gazette($id_organisme,null,null);
		$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_contacts_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Contacts",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Contacts");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT distinct tc.libelle, tc.id
		from individu_contact ic
		LEFT JOIN type_contact tc ON ic.id_type_contact=tc.id
		where ( ic.id_organisme_contactant=$id_organisme
		OR ic.id_organisme_contacte=$id_organisme )
		order by tc.libelle";

		$data0 = $db->getrows($sql);
		$res .= '<table class="toc  sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum);
		$res.='</thead><tbody>';
		for ($i=0;$i<count($data0);$i++)
		{
			$type_contact=$data0[$i]["id"];
			$libelle_contact=$data0[$i]["libelle"];
			$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_contact";
			$AnDepart=date("Y");
			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_contact($id_organisme,$j,$type_contact);
			}
			$res.='</td><td>'.$this->calcul_contact($id_organisme,null,$type_contact);
			$res.='</td></tr>';
		}
		$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_contact($id_organisme,$j,null);
		}
		$res.='</td><td>'.$this->calcul_contact($id_organisme,null,null);
		$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}


	function stats_rencontres_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Rencontres",true,"h2");
		$sql="SELECT max(YEAR( r.date_debut )) AS an_max, min(YEAR( r.date_debut )) AS an_min, o.nom as nom_organisme
		FROM  `organisme_rencontre` r, organisme o
		WHERE r.id_organisme =o.id and o.id=$id_organisme
		";
		$data = $db->getrows($sql);
		$min=$data[0]["an_min"];
		($min=="")?$min=date("Y"):null;
		$max=date("Y");
		$res .= '<table class="toc  sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($min);
		$res.='</thead><tbody>';
		$sql="SELECT distinct tr.libelle as libelle, tr.id as id_type_rencontre
		FROM  `organisme_rencontre` r, type_rencontre tr
		WHERE r.id_organisme =$id_organisme
		AND r.id_type_rencontre =tr.id
		ORDER BY tr.libelle ";
		$data = $db->getrows($sql);
		for ($i=0; $i<count($data); $i++)
		{
			$libelle=$data[$i]["libelle"];
			$id_type_rencontre=$data[$i]["id_type_rencontre"];
			$res .= "<tr><td class='styletitre'>$libelle";
			for ($j=$min; $j<=$max; $j++)
			{
				$sql="SELECT count(r.id) as nombre_rencontre, o.nom as organisme, tr.libelle as type_rencontre
				FROM  `organisme_rencontre` r, type_rencontre tr, organisme o
				WHERE YEAR( r.date_debut )=$j
				AND r.id_organisme =$id_organisme
				AND o.id=r.id_organisme
				AND r.id_type_rencontre =tr.id

				AND tr.id=$id_type_rencontre "
				;
				$data1 = $db->getrows($sql);
				$nom_organisme=$data1[0]["organisme"];
				$type_rencontre=$data1[0]["type_rencontre"];
				$nombre_rencontres=$data1[0]["nombre_rencontre"];

				$sql="SELECT  count(ir.id) as nombre_inscrits,
				sum(ir.participation_partielle) as nombre_participants_1,
				sum(ir.participation_complete) as nombre_participants_2,
				sum(ir.participation_3) as nombre_participants_3,
				sum(ir.participation_4) as nombre_participants_4
				FROM  individu_rencontre ir
				WHERE ir.id_rencontre in (SELECT r.id
				FROM  `organisme_rencontre` r
				WHERE YEAR( r.date_debut )=$j
				AND r.id_organisme =$id_organisme
				AND r.id_type_rencontre =$id_type_rencontre)"
				;
				$data1 = $db->getrows($sql);
				$nombre_inscrits=$data1[0]["nombre_inscrits"];
				($data1[0]["nombre_participants_1"] > 0) ? $nombre_participants_1=$data1[0]["nombre_participants_1"] : $nombre_participants_1=0;
				($data1[0]["nombre_participants_2"] > 0) ? $nombre_participants_2=$data1[0]["nombre_participants_2"] : $nombre_participants_2=0;
				($data1[0]["nombre_participants_3"] > 0) ? $nombre_participants_3=$data1[0]["nombre_participants_3"] : $nombre_participants_3=0;
				($data1[0]["nombre_participants_4"] > 0) ? $nombre_participants_4=$data1[0]["nombre_participants_4"] : $nombre_participants_4=0;

				$lien1=href(dispatch_url("organisme.rencontre", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>
						</b>Type de rencontre : <b>'.$type_rencontre.'<br/>'
						.'</b>Année : <b>'.$j,

						'atkfilter' => " organisme_rencontre.id_organisme = $id_organisme
						and organisme_rencontre.id_type_rencontre =$id_type_rencontre
						and YEAR(organisme_rencontre.date_debut)=$j "
				), "dispatch.php"), $nombre_rencontres , SESSION_NESTED,null,
						' target="_blank" title="Nombres de rencontres"');
				($nombre_rencontres==0) ? $lien1="" : null;
					
				$lien2=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>
						</b>Type de rencontre : <b>'.$type_rencontre.'<br/>'
						.'</b>Année : <b>'.$j,
						'atkfilter' => " individu_rencontre.id_rencontre
						in
						(SELECT r.id
						FROM  `organisme_rencontre` r
						WHERE YEAR( r.date_debut )=$j
						AND r.id_organisme =$id_organisme
						AND r.id_type_rencontre =$id_type_rencontre)"
				), "dispatch.php"), "<b>".$nombre_inscrits." </b>(".$nombre_participants_1."/".$nombre_participants_2."/".$nombre_participants_3."/".$nombre_participants_4.")" , SESSION_NESTED,null,
						' target="_blank" title="Inscrits (Participation 1 / 2 / 3 / 4)"');
				($nombre_rencontres==0) ? $lien2="" : $lien1=$lien1." / ";
				$res.='</td><td>'.'<b>'.$lien1.'</b>'.$lien2;

			}
			$sql="SELECT count(r.id) as nombre_rencontre, o.nom as organisme, tr.libelle as type_rencontre
			FROM  `organisme_rencontre` r, type_rencontre tr, organisme o
			WHERE  r.id_organisme =$id_organisme
			AND o.id=r.id_organisme
			AND r.id_type_rencontre =tr.id

			AND tr.id=$id_type_rencontre "
			;
			$data1 = $db->getrows($sql);
			$nom_organisme=$data1[0]["organisme"];
			$type_rencontre=$data1[0]["type_rencontre"];
			$nombre_rencontres=$data1[0]["nombre_rencontre"];
			$lien3=href(dispatch_url("organisme.rencontre", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>
					</b>Type de rencontre : <b>'.$type_rencontre.'<br/>',

					'atkfilter' => " organisme_rencontre.id_organisme = $id_organisme
					and organisme_rencontre.id_type_rencontre =$id_type_rencontre
					"
			), "dispatch.php"), $this->nombre_format($nombre_rencontres,"b") , SESSION_NESTED,null,
					' target="_blank" title="Nombres de rencontres"');
			($nombre_rencontres==0) ? $lien3="" : null;
			$res.='</td><td>'.'<b>'.$lien3.'</b>';
			$res.="</td></tr>";


		}
		// Total
		$res .= "</tbody><tfoot><tr><td class='styletitre'>Total";
		for ($j=$min; $j<=$max; $j++)
		{
			$sql="SELECT count(r.id) as nombre_rencontre, o.nom as organisme
			FROM  `organisme_rencontre` r,  organisme o
			WHERE YEAR( r.date_debut )=$j
			AND r.id_organisme =$id_organisme
			AND o.id=r.id_organisme
			"
			;
			$data1 = $db->getrows($sql);
			$nom_organisme=$data1[0]["organisme"];
			$nombre_rencontres=$data1[0]["nombre_rencontre"];

			$sql="SELECT  count(ir.id) as nombre_inscrits,
			sum(ir.participation_partielle) as nombre_participants_partiels,
			sum(ir.participation_complete) as nombre_participants_complets
			FROM  individu_rencontre ir
			WHERE ir.id_rencontre in (SELECT r.id
			FROM  `organisme_rencontre` r
			WHERE YEAR( r.date_debut )=$j
			AND r.id_organisme =$id_organisme
			)"
			;
			$data1 = $db->getrows($sql);
			$nombre_inscrits=$data1[0]["nombre_inscrits"];
			$nombre_participants_partiels=$data1[0]["nombre_participants_partiels"];
			$nombre_participants_complets=$data1[0]["nombre_participants_complets"];

			$lien1=href(dispatch_url("organisme.rencontre", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'
					.'</b>Année : <b>'.$j,

					'atkfilter' => " organisme_rencontre.id_organisme = $id_organisme

					and YEAR(organisme_rencontre.date_debut)=$j "
			), "dispatch.php"), $nombre_rencontres , SESSION_NESTED,null,
					' target="_blank" title="Nombres de rencontres"');
			($nombre_rencontres==0) ? $lien1="" : null;

			$lien2=href(dispatch_url("individu.rencontre_i", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'

					.'</b>Année : <b>'.$j,
					'atkfilter' => " individu_rencontre.id_rencontre
					in
					(SELECT r.id
					FROM  `organisme_rencontre` r
					WHERE YEAR( r.date_debut )=$j
					AND r.id_organisme =$id_organisme
					"
			), "dispatch.php"), $nombre_inscrits."(".$nombre_participants_partiels."/".$nombre_participants_complets.")" , SESSION_NESTED,null,
					' target="_blank" title="Inscrits(Partiels/Complets)"');
			($nombre_rencontres==0) ? $lien2="" : $lien1=$lien1." / ";
			$res.='</td><td>'.'<b>'.$lien1.'</b>'.$lien2;

		}
		$sql="SELECT count(r.id) as nombre_rencontre, o.nom as organisme
		FROM  `organisme_rencontre` r,  organisme o
		WHERE  r.id_organisme =$id_organisme
		AND o.id=r.id_organisme
		"
		;
		$data1 = $db->getrows($sql);
		$nom_organisme=$data1[0]["organisme"];
			
		$nombre_rencontres=$data1[0]["nombre_rencontre"];
		$lien3=href(dispatch_url("organisme.rencontre", "admin_liste", array (
				'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'
				,

				'atkfilter' => " organisme_rencontre.id_organisme = $id_organisme
					
				"
		), "dispatch.php"), $this->nombre_format($nombre_rencontres,"b") , SESSION_NESTED,null,
				' target="_blank" title="Nombres de rencontres"');
		($nombre_rencontres==0) ? $lien3="" : null;
		$res.='</td><td>'.'<b>'.$lien3.'</b>';
		$res.="</td></tr>";



		$res.="</tfoot></table>".$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}



	function stats_fonctions_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Fonctions",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Fonctions");
		if ($AnMinimum<=0) return false;

		$sql=" SELECT distinct tf.libelle, tf.id
		from individu_fonction ifo , type_fonction tf
		where ifo.id_organisme=$id_organisme
		and ifo.id_fonction = tf.id
		order by tf.libelle";
		$data = $db->getrows($sql);
		$res .= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'n');
		$res.='</thead><tbody>';
		$AnDepart=date("Y");
		for ($i=0;$i<count($data);$i++)
		{
			$res .= "<tr><td ".$this->m_styleTitreLigne.">".$data[$i]["libelle"];

			for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
				$res.='</td><td>'.$this->calcul_fonction($id_organisme,$j, $data[$i]["id"]);
			}
			//			$res.='</td><td>'.$this->calcul_fonction($id_organisme,null, $data[$i]["id"]);
			$res.='</td></tr>';
		}
		$res.='</td></tr></tbody></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_cotisations_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Cotisations",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Cotisations");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT distinct oc.libelle, oc.id as id_cotisation, oc.annee
		from organisme_cotisation oc
		where oc.id_organisme=$id_organisme
		order by oc.annee";
		$data = $db->getrows($sql);
		$res.= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'n');
		$res.='</thead><tbody>';
		$AnDepart=date("Y");
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Nombre";
		for ($i=0;$i<count($data);$i++)
		{
			$res.='</td><td>'.$this->calcul_cotisation($id_organisme,$data[$i]["annee"],$data[$i]["id_cotisation"],"nombre");
		}
		$res.='</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Versements";
		for ($i=0;$i<count($data);$i++)
		{
			$res.='</td><td>'.$this->calcul_cotisation($id_organisme,$data[$i]["annee"],$data[$i]["id_cotisation"],"versement");
		}
		$res.='</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Cotisations";
		for ($i=0;$i<count($data);$i++)
		{
			$res.='</td><td>'.$this->calcul_cotisation($id_organisme,$data[$i]["annee"],$data[$i]["id_cotisation"],"cotisation");
		}
		$res.='</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Dons";
		for ($i=0;$i<count($data);$i++)
		{
			$res.='</td><td>'.$this->calcul_cotisation($id_organisme,$data[$i]["annee"],$data[$i]["id_cotisation"],"don");
		}

		$res.='</td></tr></tbody></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_resultats_comptables_display($id_organisme) {
		//	return "";
		$min=$this->getAnMinimum($id_organisme,"Résultats comptables");
		($min=="")?$min=date("Y"):null;
		$max=date("Y");
		$res=$this->gettitre($id_organisme,"Résultats comptables",true,"h2");
		$nombre_sujets_save=$this->m_nombredesujets;
		$this->m_nombredesujets_niveau_2=0;
		$this->m_toc.="<ol>";
		$res.=$this->gettitre($id_organisme,"Finances",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.=$this->getresultats($id_organisme,'5',$min,$max);
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.=$this->sautDePage();
		$res.=$this->gettitre($id_organisme,"Dépenses",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.=$this->getresultats($id_organisme,'6',$min,$max);
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.=$this->sautDePage();
		$res.=$this->gettitre($id_organisme,"Recettes",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.=$this->getresultats($id_organisme,'7',$min,$max);
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.=$this->sautDePage();
		$res.=$this->gettitre($id_organisme,"Contributions volontaires",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.=$this->getresultats($id_organisme,'8',$min,$max);
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.=$this->sautDePage();
		$res.=$this->gettitre($id_organisme,"Résultats",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.=$this->getrecapitulatif_resultats($id_organisme,$min,$max);
		$res.='</table>'.$this->getUserStamp('o','o');
		$this->m_toc.="</ol>";
		$this->m_nombredesujets=$nombre_sujets_save;
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}

	function getresultats ($id_organisme,$classe_id,$min,$max)
	{
		// si classe 5 mettre les décimales
		$db = & atkGetDb();
		($classe_id==5)?$res=$this->getEnTete($min,'o','o'): $res=$this->getEnTete($min,'n','o');
		$classe_id_like= " LEFT(oc.code,1)=$classe_id ";
		$filtre="oc.id_organisme=$id_organisme and $classe_id_like  and (  oc.usuel='1'
		or oc.id in (select distinct id_compte from organisme_ligne_ecriture_comptable))";
		$sql="SELECT oc.id,
		oc.code,
		oc.libelle
		FROM
		organisme_compte oc
		WHERE $filtre
		ORDER BY  RPAD(code,8,'*')";
		$data = $db->getrows($sql);

		for ($i=0;$i<count($data);$i++)
		{
			$code=$data[$i]["code"];
			$solde_initial=$this->calcul_solde("initial",$code,$data[$i]["id"],$id_organisme);
			(strlen($code) == 1)?$couleur=$this->couleurcompte1 : null;
			(strlen($code) == 2)?$couleur=$this->couleurcompte2 : null;
			(strlen($code) == 3)?$couleur=$this->couleurcompte3 : null;
			(strlen($code) == 4)?$couleur=$this->couleurcompte4 : null;
			(strlen($code) == 5)?$couleur=$this->couleurcompte5 : null;
			(strlen($code) == 6)?$couleur=$this->couleurcompte6 : null;
			$c="<td style=\"background-color:".$couleur.";\">";
			$res.="<tr><td>".($i+1)."</td>".$c.$data[$i]["code"]."</td>".$c.$data[$i]["libelle"]."</td>".$c.$solde_initial;
			/*			$this->confection_recapitulatif("initial",$code,$solde_initial);
			 ((strlen($code)==1 && $code!=8) || $code==86)? $this->recapitulatif["$code"]["initial"]=strip_tags($solde_initial) : null;
			($code==6)?$this->recapitulatif["7-6"]["initial"]+=str_replace(" ","",strip_tags($solde_initial)):null;
			($code==6)?$this->recapitulatif["7-6-8"]["initial"]+=str_replace(" ","",strip_tags($solde_initial)):null;
			($code==7)?$this->recapitulatif["7-6"]["initial"]+=str_replace(" ","",strip_tags($solde_initial)):null;
			($code==7)?$this->recapitulatif["7-6-8"]["initial"]+=str_replace(" ","",strip_tags($solde_initial)):null;
			*/
			for ($j=$min;$j<=$max;$j++)
			{
				$solde=$this->calcul_solde($j,$data[$i]["code"],$data[$i]["id"],$id_organisme);
				$res.="</td>".$c.$solde;
				//				((strlen($code)==1 && $code!=8) || $code==86)? $this->recapitulatif["$code"]["$j"]=strip_tags($solde) : null;
			}
			if ($classe_id==5)
			{
				$solde_total=$this->calcul_solde("total",$code,$data[$i]["id"],$id_organisme);
				$res.="</td>".$c.$solde_total;
				//				((strlen($code)==1 && $code!=8) || $code==87)? $this->recapitulatif["$code"]["total"]=strip_tags($solde_total) : null;
			}
			$res.="</td></tr>";

		}
		return $res;

	}

	function getrecapitulatif_resultats ($id_organisme, $min, $max)
	{
		$res=$this->getEnTete($min,'n','o');
		//		$this->p($this->recapitulatif);
		$recap=array();
		foreach ($this->recapitulatif as $code => $value) {

			($code == "Recettes") ? $recap1["1"]=$value : null;
			($code == "Dépenses") ? $recap1["2"]=$value : null;
			($code == "Résultat") ? $recap1["3"]=$value : null;
			($code == "Finances") ? $recap1["4"]=$value : null;
			($code == "Trésorerie") ? $recap1["5"]=$value : null;
			($code == "Contributions volontaires") ? $recap1["6"]=$value : null;
			($code == "Résultat corrigé") ? $recap1["7"]=$value : null;

		}
		//		$this->p($recap1);
		for ($i=1;$i<8;$i++)
		{
			if ($i == "1")
			{
				$couleur="#90EE90"; $libelle="Recettes";
				$classe="Classe 7";
			}
			if ($i == "2")
			{
				$couleur="#F08080"; $libelle="Dépenses";
				$classe="Classe 6";
			}
			if ($i == "3")
			{
				$couleur="#E0FFFF"; $libelle="<b>Résultat</b>";
				$classe="Classe (7-6)";
			}
			if ($i == "4")
			{
				$couleur="#ADD8E6"; $libelle="Finances";
				$classe="Classe 5";
			}
			if ($i == "5")
			{
				$couleur="#E0FFFF"; $libelle="<b>Trésorerie</b>";
				$classe="";
			}
			if ($i == "6")
			{
				$couleur="#FFB6C1"; $libelle="Contributions volontaires";
				$classe="Classe 8";
			}
			if ($i == "7")
			{
				$couleur="#E0FFFF"; $libelle="Résultat corrigé<br/> des <br/>contributions volontaires";
				$classe="";
			}


			$c="<td style=\"background-color:".$couleur.";\">";
			($i=="3" || $i=="5") ? $solde_initial=$this->nombre_format($recap1["$i"]["initial"],"b") : $solde_initial=$this->nombre_format($recap1["$i"]["initial"],"");
			$res.="<tr><td>".$i."</td>".$c.$classe."</td>".$c.$libelle."</td>".$c.$solde_initial;
			for ($j=$min;$j<=$max;$j++)
			{
				($i=="3" && $recap1["$i"]["$j"]<0) ? $c="<td style=\"color:red;background-color:".$couleur.";\">" : $c="<td style=\"background-color:".$couleur.";\">";
				($i=="3" || $i=="5") ?$solde=$this->nombre_format($recap1["$i"]["$j"],"b") : $solde=$this->nombre_format($recap1["$i"]["$j"],"");
				$res.="</td>".$c.$solde;
			}
			//($i=="4")? $solde_total=$this->nombre_format($recap1["$i"]["total"],"b") : $solde_total="";
			//$res.="</td>".$c.$solde_total;
			$res.="</td></tr>";
		}
		return $res;
	}

	function calcul_solde($annee_ou_initial, $code,$id_compte, $id_organisme )
	{
		$db = & atkGetDb();
		if ($annee_ou_initial=="initial")
		{
			if (strlen($code)<6)
			{
				$codelike=$code.'%';
				$data = $db->getrows(' select sum(debit_initial-credit_initial) as solde_initial from organisme_compte oc
						where oc.id IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' )
						');
				(empty ($data[0]["solde_initial"])) ? $data[0]["solde_initial"] = "" :null;
				if (substr($code,0,1)=="5")
				{
					(strlen($code)==1)? $resultat=$this->nombre_format($data[0]["solde_initial"],"b",2) : null;
					(strlen($code)==2)? $resultat=$this->nombre_format($data[0]["solde_initial"],"bi",2) : null;
					(strlen($code)==3)? $resultat=$this->nombre_format($data[0]["solde_initial"],"i",2) :null ;
					(strlen($code)==4)? $resultat=$this->nombre_format($data[0]["solde_initial"],"u",2) :null ;
					(strlen($code)==5)? $resultat=$this->nombre_format($data[0]["solde_initial"],"u",2) :null ;
				}
				else
				{(strlen($code)==1)? $resultat=$this->nombre_format($data[0]["solde_initial"],"b") : null;
				(strlen($code)==2)? $resultat=$this->nombre_format($data[0]["solde_initial"],"bi") : null;
				(strlen($code)==3)? $resultat=$this->nombre_format($data[0]["solde_initial"],"i") :null ;
				(strlen($code)==4)? $resultat=$this->nombre_format($data[0]["solde_initial"],"u") :null ;
				(strlen($code)==5)? $resultat=$this->nombre_format($data[0]["solde_initial"],"u") :null ;
				}
					
				$this->confection_recapitulatif("initial", $code, $data[0]["solde_initial"]);
				$href=href(dispatch_url("organisme.compte", "admin_liste", array(
						"atkfiltre"=> " Code compte : ".$codelike,
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						"atkfilter" => " organisme_compte.id IN ( select organisme_compte.id from organisme_compte where organisme_compte.code like '$codelike'
						and organisme_compte.id_organisme=$id_organisme )
						")
						, "dispatch.php"), $resultat, SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				$data = $db->getrows(' select sum(debit_initial-credit_initial) as solde_initial from organisme_compte oc
						where oc.id= '.$id_compte.' 				');
				if (empty ($data[0]["solde_initial"])) {
					$data[0]["solde_initial"] = "";
				}
				$resultat=$this->nombre_format($data[0]["solde_initial"],"");
				$href=href(dispatch_url("organisme.compte", "admin_liste", array(
						"atkfiltre"=> " Compte : ".$id_compte,
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						"atkfilter" => " organisme_compte.id= $id_compte		")
						, "dispatch.php"), $resultat, SESSION_NESTED, false, $this->target_tbdebord);
			}
		}
		else if ($annee_ou_initial=="total")
		{
			if (strlen($code)<6 )
			{
				$codelike=$code.'%';
				/*				$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				 where l.id_compte IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' ) and l.id_ecriture=e.id
						');
				*/
				$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l
						where l.id_compte IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' )
						');

				$data1 = $db->getrows(' select sum(debit_initial-credit_initial) as solde from organisme_compte
						where id IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' )
						');
				(empty ($data[0]["solde"])) ? $data[0]["solde"] = "" :null;
				if (substr($code,0,1)=="5")
				{
					(strlen($code)==1)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"b",2) : null;
					(strlen($code)==2)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"bi",2) : null;
					(strlen($code)==3)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"i",2) :null ;
					(strlen($code)==4)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"u",2) :null ;
					(strlen($code)==5)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"u",2) :null ;
				}
				else
				{
					(strlen($code)==1)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"b") : null;
					(strlen($code)==2)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"bi") : null;
					(strlen($code)==3)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"i") :null ;
					(strlen($code)==4)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"u") :null ;
					(strlen($code)==5)? $resultat=$this->nombre_format(($data[0]["solde"]+ $data1[0]["solde"]),"u") :null ;
				}
					

				$resultat_brut=($data[0]["solde"] + $data1[0]["solde"]);
				$this->confection_recapitulatif("total", $code, $resultat_brut);

			}
			else
			{
				/*			$data = $db->getrows(" select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
				 where l.id_compte = $id_compte and l.id_ecriture=e.id ");
				*/
				$data = $db->getrows(" select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l
						where l.id_compte = $id_compte ");
				if (empty ($data[0]["solde"])) {
					$data[0]["solde"] = 0;
				}
				$data1 = $db->getrows(" select debit_initial, credit_initial  from organisme_compte
						where id= $id_compte");
				$resultat=$this->nombre_format(($data[0]["solde"] + $data1[0]["debit_initial"] - $data[1]["credit_initial"]),"b");
			}
			return 	$resultat;

		}
		else
		{	if (strlen($code)<6)
		{
			$codelike=$code.'%';
			/*			$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
			 where l.id_compte IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' )
					and l.id_ecriture=e.id and year(e.date_ecriture)='.$annee_ou_initial )	;
			*/
			$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l
					where l.id_compte IN ( select id from organisme_compte where code like "'.$codelike.'" and id_organisme='.$id_organisme.' )
					and year(l.date_operation)='.$annee_ou_initial )	;
			(empty ($data[0]["solde"])) ? $data[0]["solde"] = "" :null;
			if (substr($code,0,1)=="5")
			{
				(strlen($code)==1)? $resultat=$this->nombre_format($data[0]["solde"],"b",2) : null;
				(strlen($code)==2)? $resultat=$this->nombre_format($data[0]["solde"],"bi",2) : null;
				(strlen($code)==3)? $resultat=$this->nombre_format($data[0]["solde"],"i",2) :null ;
				(strlen($code)==4)? $resultat=$this->nombre_format($data[0]["solde"],"u",2) :null ;
				(strlen($code)==5)? $resultat=$this->nombre_format($data[0]["solde"],"u",2) :null ;
			}
			else
			{
				(strlen($code)==1)? $resultat=$this->nombre_format($data[0]["solde"],"b") : null;
				(strlen($code)==2)? $resultat=$this->nombre_format($data[0]["solde"],"bi") : null;
				(strlen($code)==3)? $resultat=$this->nombre_format($data[0]["solde"],"i") :null ;
				(strlen($code)==4)? $resultat=$this->nombre_format($data[0]["solde"],"u") :null ;
				(strlen($code)==5)? $resultat=$this->nombre_format($data[0]["solde"],"u") :null ;
			}

				
				
			$this->confection_recapitulatif($annee_ou_initial, $code, $data[0]["solde"]);
			$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin_liste", array(
					'atkfiltre'=>'</b>Classe de compte : <b>'.$codelike. ' </b><br/> Année : <b>'.$annee_ou_initial .'</b>',
					'id'=>$id_organisme,
					'id_organisme'=>$id_organisme,
					"atkfilter" => " id_compte IN ( select id from organisme_compte where code like '$codelike'
					and id_organisme=$id_organisme )
					and year(date_operation)=$annee_ou_initial " )
					, "dispatch.php"), $resultat, SESSION_NESTED, false, $this->target_tbdebord);
		}
		else
		{
			/*			$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l, organisme_ecriture_comptable e
			 where l.id_compte = '.$id_compte.' and l.id_ecriture=e.id and year(e.date_ecriture)='.$annee_ou_initial.'
					');
			*/
			$data = $db->getrows(' select sum(debit-credit) as solde from organisme_ligne_ecriture_comptable l
					where l.id_compte = '.$id_compte.' and year(l.date_operation)='.$annee_ou_initial.'
					');
			if (empty ($data[0]["solde"])) {
				$data[0]["solde"] = "";
			}
			$resultat=$this->nombre_format($data[0]["solde"],"");
			$href=href(dispatch_url("organisme.ligne_ecriture_comptable", "admin_liste", array(
					'atkfiltre'=>'</b>Compte : <b>'.$id_compte. ' </b><br/> Année : <b>'.$annee_ou_initial .'</b>',
					'id'=>$id_organisme,
					'id_organisme'=>$id_organisme,
					"atkfilter" => " organisme_ligne_ecriture_comptable.id_compte = $id_compte
					and year(organisme_ligne_ecriture_comptable.date_operation)=$annee_ou_initial
					")
					, "dispatch.php"), $resultat, SESSION_NESTED, false, $this->target_tbdebord);
		}
		}
		return 	$href;


	}
	function confection_recapitulatif ($type, $code, $solde)
	{
		if ((strlen($code)==1 && $code!=8) || $code==86)
		{
			if ($code==5 )
			{
				$this->m_solde_tresorerie+=$solde;
				$this->recapitulatif["Finances"][$type]=$solde;
				($type=="total") ? $this->recapitulatif["Trésorerie"][$type]=$solde : $this->recapitulatif["Trésorerie"][$type]=$this->m_solde_tresorerie ;

			}
			($code==6) ? $this->recapitulatif["Dépenses"][$type]=-($solde) : null;
			($code==7) ? $this->recapitulatif["Recettes"][$type]=-($solde) : null;
			($code==86) ? $this->recapitulatif["Contributions volontaires"][$type]=$solde : null;
		}
		($code==6)?$this->recapitulatif["Résultat"][$type]+=-($solde) :null;
		($code==6)?$this->recapitulatif["Résultat corrigé"][$type]+=-($solde) :null;
		($code==87)?$this->recapitulatif["Résultat corrigé"][$type]+=-$solde :null;
		($code==7)?$this->recapitulatif["Résultat"][$type]+=-$solde :null;
		($code==7)?$this->recapitulatif["Résultat corrigé"][$type]+=-$solde :null;
		//		($code==87)?$this->recapitulatif["Résultat corrigé"][$type]+=-$solde :null;
	}

	function stats_coordonnees_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Organisme",true,"h2");
		$sql=" SELECT
		o.nom ,
		o.sigle,
		o.siret,
		o.siret_recepisse_prefecture,
		o.objectif_concis,
		tor.libelle as type_organisme,
		o.telephone ,
		o.courriel,
		o.calendrier,
		o.site_internet,
			
		o.objectifs,
		o.acces_public_o_n,
		o.numero_association,
		o.date_declaration_association,
		o.date_publication_jo,
		o.id_logo,
		o.id_icone,
		o.id_plaquette,
		o.id_statuts,
		o.id_reglement_interieur,
		o.id_projet_associatif,
		o.id_organigramme_du_personnel,

		o.id_organisme_federation,
		o.id_contact_federation,
		o.id_association_dans_federation,

		o.montant_indemnite_kilometre,
		o.montant_indemnite_heure_benevolat,
		o.eclater_cotisations_dons_o_n,
		o.date_initialisation_comptabilite,

		o.p_texte_carte,
		o.p_explication_carte,
		o.p_texte_timbre,
		o.p_explication_timbre,
		o.p_texte_recu_fiscal,
		o.p_explication_recu_fiscal,
		o.p_texte_rappel_cotisation,
		o.p_explication_rappel_cotisation,
		o.p_texte_radiation_non_cotisation,
		o.p_explication_radiation_non_cotisation,
		o.p_texte_radiation_non_adhesion,
		o.p_explication_radiation_non_adhesion,

		o.date_synchronisation_federation,
		o.id_synchronisation_federation,
		o.date_envoi_recu_fiscal,
		o.id_envoi_recu_fiscal,
		o.date_envoi_timbre,
		o.id_envoi_timbre,
		o.date_envoi_carte,
		o.id_envoi_carte,
		o.date_recu_abandon_creance,
		o.id_recu_abandon_creance,
		o.date_derniere_preparation,
		o.id_derniere_preparation,
		o.date_derniere_preparation_fin,
		o.id_derniere_preparation_fin,

		o.identifiant_google,
		o.code_google,
		o.tz_offset_google,
		o.calendrier_rencontres_nom,
		o.calendrier_rencontres_url,
		o.calendrier_rencontres_uri,
		o.calendrier_rencontres_refresh,
		o.calendrier_contacts_nom,
		o.calendrier_contacts_url,
		o.calendrier_contacts_uri,
		o.calendrier_contacts_refresh

		FROM
		organisme o

		LEFT JOIN type_organisme tor ON o.id_type_organisme=tor.id
		WHERE o.id=$id_organisme

		";
		$data = $db->getrows($sql);
		($data[0]["id_logo"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_logo"],'n',$lien_logo) : $lien_logo="";
		($data[0]["id_icone"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_icone"],'n',$lien_icone) : $lien_icone="";
		($data[0]["id_plaquette"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_plaquette"],'n',$lien_plaquette) : $lien_plaquette="";
		($data[0]["id_statuts"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_statuts"],'n',$lien_statuts) : $lien_statuts="";
		($data[0]["id_reglement_interieur"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_reglement_interieur"],'n',$lien_reglement_interieur) : $lien_reglement_interieur="";
		($data[0]["id_projet_associatif"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_projet_associatif"],'n',$lien_projet_associatif) : $lien_projet_associatif="";
		($data[0]["id_organigramme_du_personnel"]>0) ? $this->descripteur_document($type='organisme',$data[0]["id_organigramme_du_personnel"],'n',$lien_organigramme_du_personnel) : $lien_organigramme_du_personnel="";
		$nombre_sujets_save=$this->m_nombredesujets;
		$this->m_nombredesujets_niveau_2=0;
		$this->m_toc.="<ol>";
		$res.=$this->gettitre($id_organisme,"Coordonnées",true,"h3","2");
		//		$res.="<b>Coordonnées</b><br/>".
		$res.= '<table class="toc  sortable">';
		$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Nom".'</td><td><b>'.$data[0]["nom"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Objectif".'</td><td><b>'.$data[0]["objectif_concis"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Sigle".'</td><td><b>'.$data[0]["sigle"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Siret".'</td><td><b>'.$data[0]["siret"].'</b></td></tr>';
		//		$res.= "<tr><td ".$this->m_styleTitreLigne.">Récépissé préfecture".'</td><td>'.$data[0]["siret_recepisse_prefecture"].'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Type".'</td><td><b>'.$data[0]["type_organisme"].'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Téléphone".'</td><td><b>'.$this->affiche_telephone($data[0]["telephone"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Courriel".'</td><td><b>'.$this->affiche_courriel($data[0]["courriel"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Calendrier".'</td><td><b>'.$this->affiche_calendrier($data[0]["calendrier"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Site internet".'</td><td><b>'.$this->affiche_url($data[0]["site_internet"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Adresse".'</td><td><b>'.$this->descripteur_adresse_organisme($id_organisme,'n','n').'</b></td></tr>';

		$res.="</table>";
		if ($data[0]["objectifs"]!="")
		{
			$res.=$this->gettitre($id_organisme,"Objectifs détaillés",true,"h3","2");
			$res.= '<table class="toc  sortable" style="width:850px;">';
			$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Objectifs".'</td><td>'.$data[0]["objectifs"].'</td></tr>';
			$res.="</table>";
		}
		$res.=$this->gettitre($id_organisme,"Déclaration",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Numéro d'association".'</td><td><b>'.$data[0]["numero_association"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Date de déclaration".'</td><td><b>'.$data[0]["date_declaration_association"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Publié au Journal Officiel ".'</td><td><b>'.$data[0]["date_publication_jo"].'</b></td></tr>';

		$lien_document_declaration='<a href="'.dispatch_url("organisme.organisme", "listeecran", array (
				"atkcode" => "2",
				"atkexport" => "n",
				"idfonctions" => "1,2,4,5,6,7,8,9,10",
				"id" => $id_organisme
		)).'"> Générer la déclaration </a>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Document de déclaration".'</td><td>'.$lien_document_declaration.'</td></tr>';
		$res.="</table>";
		if ($data[0]["id_organisme_federation"]!="")
		{
			$res.=$this->gettitre($id_organisme,"Fédération",true,"h3","2");
			$res.= '<table class="toc  sortable">';
			$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Fédération".'</td><td><b>'.$this->descripteur_organisme_sans_lien($data[0]["id_organisme_federation"]).'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Contact".'</td><td><b>'.$this->descripteur_individu_sans_lien($data[0]["id_contact_federation"]).'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Identifiant dans la fédération ".'</td><td><b>'.$data[0]["id_association_dans_federation"].'</b></td></tr>';
			$res.="</table>";
		}
		$res.=$this->gettitre($id_organisme,"Documents institutionnels",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Logo".'</td><td>'.$lien_logo.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Icone".'</td><td>'.$lien_icone.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Plaquette".'</td><td>'.$lien_plaquette.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Statuts".'</td><td>'.$lien_statuts.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Règlement intérieur".'</td><td>'.$lien_reglement_interieur.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Projet associatif".'</td><td>'.$lien_projet_associatif.'</td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Organigramme".'</td><td>'.$lien_organigramme_du_personnel.'</td></tr>';
		$res.="</table>";
		$res.=$this->gettitre($id_organisme,"Paramètres de la comptabilité",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Date d'initialisation de la comptabilité".'</td><td><b>'.$data[0]["date_initialisation_comptabilite"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Indemnité horaire de bénévolat".'</td><td><b>'.$data[0]["montant_indemnite_heure_benevolat"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Indemnité kilométrique".'</td><td><b>'.$data[0]["montant_indemnite_kilometre"].'</b></td></tr>';
		($data[0]["eclater_cotisations_dons_o_n"]==1) ? $oui_non="Oui" : $oui_non="Non";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Eclater cotisations et dons".'</td><td><b>'.$oui_non.'</b></td></tr>';
		$res.="</table>";
		if ($data[0]["p_texte_carte"]!="" || $data[0]["p_texte_timbre"]!="" || $data[0]["p_texte_recu_fiscal"]!="" || $data[0]["p_texte_rappel_cotisation"]!="" || $data[0]["p_texte_radiation_non_cotisation"]!="" || $data[0]["p_texte_radiation_non_adhesion"]!="")
		{
			$res.=$this->gettitre($id_organisme,"Textes types",true,"h3","2");
			$res.= '<table class="toc  sortable" style="width:850px;">';
			$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Carte (texte)".'</td><td><b>'.$data[0]["p_texte_carte"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Carte (explication)".'</td><td>'.$data[0]["p_explication_carte"].'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Timbre (texte)".'</td><td><b>'.$data[0]["p_texte_timbre"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Timbre (explication)".'</td><td>'.$data[0]["p_explication_timbre"].'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Reçu fiscal (texte)".'</td><td><b>'.$data[0]["p_texte_recu_fiscal"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Reçu fiscal (explication)".'</td><td>'.$data[0]["p_explication_recu_fiscal"].'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Rappel cotisation (texte)".'</td><td><b>'.$data[0]["p_texte_rappel_cotisation"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Rappel cotisation (explication)".'</td><td>'.$data[0]["p_explication_rappel_cotisation"].'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Radiation pour non cotisation (texte)".'</td><td><b>'.$data[0]["p_texte_radiation_non_cotisation"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Radiation pour non cotisation (explication)".'</td><td>'.$data[0]["p_explication_radiation_non_cotisation"].'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Radiation pour non adhésion (texte)".'</td><td><b>'.$data[0]["p_texte_radiation_non_adhesion"].'</b></td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Radiation pour non adhésion (explication)".'</td><td>'.$data[0]["p_explication_radiation_non_adhesion"].'</td></tr>';
			$res.="</table>";
		}
		if ($data[0]["date_derniere_preparation"]!="")
		{
			$res.=$this->gettitre($id_organisme,"Traitement périodique",true,"h3","2");
			$res.= '<table class="toc  sortable">';
			$res.= "<tr><th>Libellé</th><th>Date</th><th>Fait par</th></tr>";
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Début de la dernière préparation".'</td><td><b>'.$data[0]["date_derniere_preparation"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_derniere_preparation"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Fin de la dernière préparation".'</td><td><b>'.$data[0]["date_derniere_preparation_fin"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_derniere_preparation_fin"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernier envoi de cartes".'</td><td><b>'.$data[0]["date_envoi_carte"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_envoi_carte"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernier envoi de timbres".'</td><td><b>'.$data[0]["date_envoi_timbre"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_envoi_timbre"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernier envoi de reçus fiscaux".'</td><td><b>'.$data[0]["date_envoi_recu_fiscal"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_envoi_recu_fiscal"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernier envoi de reçus fiscaux pour abandon de créance".'</td><td><b>'.$data[0]["date_recu_abandon_creance"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_recu_abandon_creance"],'o').'</td></tr>';
			$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernière synchronisation avec la fédération".'</td><td><b>'.$data[0]["date_synchronisation_federation"].'</b></td><td>'.$this->descripteur_individu_utilisateur($data[0]["id_synchronisation_federation"],'o').'</td></tr>';
			$res.="</table>";
		}
		$res.=$this->gettitre($id_organisme,"Calendriers",true,"h3","2");
		$res.= '<table class="toc  sortable">';
		$res.= "<tr><th>Libellé</th><th>Valeur</th></tr>";
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Identifiant".'</td><td><b>'.$data[0]["identifiant_google"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Code".'</td><td><b>'.substr($data[0]["code_google"], 0,3).'******</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Time offset".'</td><td><b>'.$data[0]["tz_offset_google"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Nom du calendrier des rencontres".'</td><td><b>'.$data[0]["calendrier_rencontres_nom"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Url".'</td><td><b>'.$this->affiche_calendrier($data[0]["calendrier_rencontres_url"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Uri".'</td><td><b>'.$data[0]["calendrier_rencontres_uri"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernière actualisation".'</td><td><b>'.$data[0]["calendrier_rencontres_refresh"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Nom du calendrier des contacts".'</td><td><b>'.$data[0]["calendrier_contacts_nom"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Url".'</td><td><b>'.$this->affiche_calendrier($data[0]["calendrier_contacts_url"]).'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Uri".'</td><td><b>'.$data[0]["calendrier_contacts_uri"].'</b></td></tr>';
		$res.= "<tr><td ".$this->m_styleTitreLigne.">Dernière actualisation".'</td><td><b>'.$data[0]["calendrier_contacts_refresh"].'</b></td></tr>';

		/*
		 o.acces_public_o_n,

		*/
		$res.='</table>'.$this->getUserStamp('o','o');
		$this->m_toc.="</ol>";
		$this->m_nombredesujets=$nombre_sujets_save;
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
/*	function stats_immatriculations_display($id_organisme)
	{
		$db = & atkGetDb();
		$sql=" SELECT i.id as id_entite, i.libelle, i.immatriculation, i.url
		from organisme_immatriculation i
		where i.id_organisme=$id_organisme
		order by i.libelle";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Immatriculations",true,"h2");

		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res .= "<tr><th>#</th><th>Libellé</th><th>Immatriculation</th><th>Url</th><th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";
		for ($i=0; $i<count($data);$i++)
		{
			$res .= "<tr><td>".($i+1)."</td><td><b>".$data[$i]["libelle"]."</b></td><td>".$data[$i]["immatriculation"]."</td><td>".$this->affiche_url($data[$i]["url"]).
			"</td><td>".$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n')."</td></tr>";
		}
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	*/
 	function stats_immatriculations_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Immatriculations",true,"h2");

		$AnMinimum=$this->getAnMinimum($id_organisme,"Immatriculations");
		if ($AnMinimum<=0) return false;
		$res.= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		$res .= "<tr><td ".$this->m_styleTitreLigne.">Immatriculations";
		$AnDepart=date("Y");
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_immatriculation($id_organisme,$j);
		}
		$res.='</td><td>'.$this->calcul_immatriculation($id_organisme,null);

		$res.='</td></tr></tbody></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	 
/*	function stats_patrimoine_display($id_organisme)
	{
		$db = & atkGetDb();
		$sql=" SELECT
		p.id as id_entite,
		p.libelle,
		p.date_acquisition,
		p.montant_acquisition,
		p.motif_acquisition,
		p.date_cession,
		p.montant_cession,
		p.motif_cession
		from organisme_patrimoine p
		where p.id_organisme=$id_organisme
		order by p.date_acquisition";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Patrimoine",true,"h2");

		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res .= "<tr><th>#</th><th>Libellé</th><th>Acquis le</th><th>Motif</th><th>Montant</th><th>Cédé le</th><th>Motif</th><th>Montant</th><th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";
		for ($i=0; $i<count($data);$i++)
		{

			$res .= "<tr><td>".($i+1)."</td><td><b>".$data[$i]["libelle"]."</b></td><td>".$data[$i]["date_acquisition"]."</td><td>".$data[$i]["motif_acquisition"]."</td><td>".$data[$i]["montant_acquisition"]."</td>
					<td>".$data[$i]["date_cession"]."</td><td>".$data[$i]["motif_cession"]."</td><td>".$data[$i]["montant_cession"]."</td><td>".$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n')."</td></tr>";
		}
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	*/

	 function stats_patrimoine_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Patrimoine",true,"h2");

		$AnMinimum=$this->getAnMinimum($id_organisme,"Patrimoine");
		if ($AnMinimum<=0) return false;
		$res.= '<table class="toc sortable">';
		$res.='<thead>';
		$res.= $this->getEnTete($AnMinimum,'o');
		$res.='</thead><tbody>';
		$res .= "<tr><td ".$this->m_styleTitreLigne.">Patrimoine";
		$AnDepart=date("Y");
		for($j=$AnMinimum; $j<=$AnDepart; $j++)
		{
			$res.='</td><td>'.$this->calcul_patrimoine($id_organisme,$j);
		}
		$res.='</td><td>'.$this->calcul_patrimoine($id_organisme,null);

		$res.='</td></tr></tbody></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}

	function stats_ip_logs_display()
	{
		$db = & atkGetDb();
		$sql="SELECT u.id_individu , remote_address, max(stamp) as maxstamp  FROM
				`atkeventlog`
				LEFT JOIN app_utilisateur u ON atkeventlog.userid=u.id
				where year(stamp)>(year(now())-1) AND remote_address is not NULL  group by userid,remote_address order by userid, remote_address
				";
		$data = $db->getrows($sql);
		$res=$this->gettitre("","Logs : Ip par individu sur les douze mois écoulés",true,"h2");
		$res.= '<table class="toc  sortable" style="width:50%;">';

		$res.="<tr><th ".$this->m_styleTitreLigne.">".'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">Utilisateur</p>';
		$res.="</th><th ".$this->m_styleTitreLigne.">".'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">Ip</p>';
		$res.="</th><th ".$this->m_styleTitreLigne.">".'<p style="text-align: center;  margin-top:0px; margin-bottom:0px">date récente</p></th></tr>';
		for ($i=0; $i<count($data);$i++)
		{
			$res.= "<tr><td>".$this->descripteur_individu_sans_lien($data[$i]["id_individu"]);
			$res.= "</td><td>".$this->ip_geolocalisation($data[$i]["remote_address"]);
			$res.= "</td><td>".$data[$i]["maxstamp"]."</td></tr>";
		}
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_logs_display($id_organisme,$type_log="total",$contenu_log="node_action")
	{
		$db = & atkGetDb();
		$sql="SELECT
				min(stamp) as stamp_min_total,
				min(year(stamp)) as year_min_total,
				SUBDATE(UTC_TIMESTAMP(), INTERVAL 24 HOUR) as stamp_min_hour,
				SUBDATE(UTC_TIMESTAMP(), INTERVAL 31 DAY) as stamp_min_day,
				SUBDATE(UTC_TIMESTAMP(), INTERVAL 12 MONTH) as stamp_min_month,
				UTC_TIMESTAMP( ) as stamp_now
				FROM atkeventlog
				WHERE stamp >0";
		$data = $db->getrows($sql);
		$stamp_min_total=$data[0]["stamp_min_total"];
		$AnMinimum=$data[0]["year_min"];
		$stamp_min_hour=$data[0]["stamp_min_hour"];
		$stamp_min_day=$data[0]["stamp_min_day"];
		$stamp_min_month=$data[0]["stamp_min_month"];
		$stamp_now=$data[0]["stamp_now"];
		If ($type_log=="total")
		{
			$stamp_min=$stamp_min_total;
			$compteur=date("Y")-$data[0]["year_min"];
		}
		If ($type_log=="heure")
		{
			$stamp_min=$stamp_min_hour;
			$compteur=24;
		}
		If ($type_log=="jour")
		{
			$stamp_min=$stamp_min_day;
			$compteur=31;
		}
		If ($type_log=="mois")
		{
			$stamp_min=$stamp_min_month;
			$compteur=12;
		}
		$AnMinimum=$stamp_min;
		if ($contenu_log=="node_action")
		{
			$sql="SELECT
			distinct
			node as nodename,
			action as action
			FROM atkeventlog
			WHERE  stamp >0
			AND LENGTH(node) >0
			AND node!='.'
			AND LENGTH(action) >0
			AND stamp>='$stamp_min'
			ORDER by node,action";
		}
		if ($contenu_log=="utilisateur")
		{
			$sql="SELECT
			distinct
			lo.userid as id_utilisateur,

			i.id as id_individu
			FROM atkeventlog lo
			LEFT JOIN app_utilisateur ut ON lo.userid=ut.id
			LEFT JOIN individu i ON ut.id_individu=i.id
			WHERE  lo.stamp >0
			AND LENGTH(node) >0
			AND node!='.'
			AND LENGTH(action) >0
			AND lo.stamp>='$stamp_min'
			ORDER by i.nom,i.prenom";
		}
		if ($contenu_log=="error")
		{
			$sql="SELECT
			distinct
			lo.userid as id_utilisateur,

			i.id as id_individu
			FROM atkeventlog lo
			LEFT JOIN app_utilisateur ut ON lo.userid=ut.id
			LEFT JOIN individu i ON ut.id_individu=i.id
			WHERE  lo.stamp >0
			AND LENGTH(error_message) >0
			AND lo.stamp>='$stamp_min'
			ORDER by i.nom,i.prenom";
		}
		$data = $db->getrows($sql);
		//		$this->p($data);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Logs : ".$contenu_log." par ".$type_log,true,"h2");
		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res.= $this->getEnTete($AnMinimum,'o','n',$type_log,$contenu_log);
		for ($i=0; $i<count($data);$i++)
		{
			if ($contenu_log=="utilisateur" || $contenu_log=="error")
			{
				$res.= "<tr><td ".$this->m_styleTitreLigne.">".$this->descripteur_individu_sans_lien($data[$i]["id_individu"]);
				//			$res.= "</td><td ".$this->m_styleTitreLigne.">".$this->ip_geolocalisation($data[$i]["remote_address"]);
			}
			if ($contenu_log=="node_action")
			{
				$res.= "<tr><td ".$this->m_styleTitreLigne.">".($i+1);
				$res.= "</td><td ".$this->m_styleTitreLigne.">".$data[$i]["nodename"];
				$res.= "</td><td ".$this->m_styleTitreLigne.">".$data[$i]["action"];
			}

			for($j=0;$j<$compteur;$j++)
			{

				$resretour='</td><td>'.$this->calcul_log($type_log, $contenu_log,$stamp_min, $j,$data[$i]["nodename"], $data[$i]["action"],$data[$i]["id_utilisateur"]);
				$res.=$resretour;
				//				echo "<br/>".$j;
				//				if (strlen($resretour)>0) {echo "Titi :".$resretour; die();};
			}
			$res.='</td><td>'.$this->calcul_log($type_log, $contenu-log,$stamp_min, "-1",$data[$i]["nodename"], $data[$i]["action"],$data[$i]["id_utilisateur"]);
			$res.='</td></tr>';
		}
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	function stats_contrats_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Contrats",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Contrats");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT
		distinct tc.id as id_type_contrat,
		tc.libelle as libelle_type_contrat
		from organisme_contrat oc
		LEFT JOIN type_contrat tc ON oc.id_type_contrat=tc.id
		where oc.id_organisme=$id_organisme and tc.id is not null
		order by tc.libelle";
		$data0 = $db->getrows($sql);
		$res .= '<table class="toc  sortable">';
				$res.='<thead>';
						$res.= $this->getEnTete($AnMinimum,'o');
						$res.='</thead><tbody>';
						for ($i=0;$i<count($data0);$i++)
						{
							$id_type_contrat=$data0[$i]["id_type_contrat"];
							$libelle_type_contrat=$data0[$i]["libelle_type_contrat"];
							$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_type_contrat";
							$AnDepart=date("Y");
							for($j=$AnMinimum; $j<=$AnDepart; $j++)
			{
									$res.='</td><td>'.$this->calcul_contrat($id_organisme,$j,$id_type_contrat);
						}
						$res.='</td><td>'.$this->calcul_contrat($id_organisme,null,$id_type_contrat);
							$res.='</td></tr>';
	}
							$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
							for($j=$AnMinimum; $j<=$AnDepart; $j++)
							{
							$res.='</td><td>'.$this->calcul_contrat($id_organisme,$j,null);
	}
	$res.='</td><td>'.$this->calcul_contrat($id_organisme,null,null);
	$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
	$res.="<br/><br/>";
			$res.=$this->sautDePage();
			return $res;
		}
		/*
	function stats_contrats_display($id_organisme)
	{
		$db = & atkGetDb();
		$sql=" SELECT
		c.id as id_entite,
		c.libelle,
		tc.libelle as type_contrat,
		c.id_organisme_contrat,
		c.id_interlocuteur,
		c.id_individu_conventionne,
		c.reference_contrat,
		c.avenant,
		c.date_souscription,
		c.motif_souscription,
		c.montant,
		c.periodicite,
		c.date_echeance,
		c.date_resiliation,
		c.motif_resiliation,
		c.id_document,
		c.id_lieu_rencontre
		from organisme_contrat c
		LEFT JOIN type_contrat tc ON c.id_type_contrat=tc.id
		where c.id_organisme=$id_organisme
		order by c.date_souscription";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Contrats",true,"h2");

		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res .= "<tr><th>#</th>
				<th>Type</th>
				<th>Libellé</th>
				<th>Référence</th>
				<th>Organisme</th>
				<th>Interlocuteur</th>
				<th>Conventionné</th>
				<th>Avenant</th>
				<th>Souscrit le</th>
				<th>Motif</th>
				<th>Montant</th>
				<th>Périodicité</th>
				<th>Echéance</th>
				<th>Résilié le</th>
				<th>Motif</th>
				<th>Document</th>
				<th>Lieu</th>
				<th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";

		for ($i=0; $i<count($data);$i++)
		{
			($data[$i]["id_document"]>0) ? $this->descripteur_document($type='organisme',$data[$i]["id_document"],'n',$lien_document) : $lien_document="";
			($data[$i]["id_lieu_rencontre"]>0) ? $lien_lieu=$this->descripteur_lieu_rencontre_lieu($data[$i]["id_lieu_rencontre"],'n','o') : $lien_lieu="";
			$res .= "<tr><td>".($i+1)."</td>
					<td>".$data[$i]["type_contrat"]."</td>
							<td><b>".$data[$i]["libelle"]."</b></td>
									<td>".$data[$i]["reference_contrat"]."</td>
											<td>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_contrat"])."</td>
													<td>".$this->descripteur_individu_sans_lien($data[$i]["id_interlocuteur"])."</td>
															<td>".$this->descripteur_individu_sans_lien($data[$i]["id_individu_conventionne"])."</td>
																	<td>".$data[$i]["avenant"]."</td>
																			<td>".$data[$i]["date_souscription"]."</td>
																					<td>".$data[$i]["motif_souscription"]."</td>
																							<td>".$data[$i]["montant"]."</td>
																									<td>".$data[$i]["periodicite"]."</td>
																											<td>".$data[$i]["date_echeance"]."</td>
																													<td>".$data[$i]["date_resiliation"]."</td>
																															<td>".$data[$i]["motif_resiliation"]."</td>
																																	<td>".$lien_document."</td>
																																			<td>".$lien_lieu."</td>
																																					<td>".$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n')."</td>
																																							</tr>";
		}
		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	*/
	function stats_domaines_display($id_organisme)
	{
		$db = & atkGetDb();
		$sql=" SELECT
		d.id as id_entite,
		d.libelle,
		d.nom_domaine,
		d.id_organisme_registrar,
		d.date_registrar_debut,
		d.date_registrar_fin,
		d.url_administration_registrar,
		d.identifiant_registrar,
		d.mot_de_passe_registrar,
		d.cout_registrar,
		d.commentaire_registrar,
		d.id_organisme_hebergement,
		d.date_contrat_debut_hebergement,
		d.date_contrat_fin_hebergement,
		d.caracteristiques_hebergement,
		d.url_administration_hebergement,
		d.identifiant_hebergement,
		d.mot_de_passe_hebergement,
		d.cout_hebergement,
		d.commentaire_hebergement,
		d.url_administration_mysql,
		d.serveur_mysql,
		d.identifiant_mysql,
		d.mot_de_passe_mysql,
		d.commentaire_mysql,
		d.url_administration_ftp,
		d.serveur_ftp,
		d.identifiant_ftp,
		d.mot_de_passe_ftp,
		d.commentaire_ftp
		from organisme_domaine d
		where d.id_organisme=$id_organisme
		order by d.nom_domaine";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Domaines internet",true,"h2");

		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res .= "<tr><th>#</th><th>Libellé</th><th>Domaine</th><th>Certificat</th><th>Registrar</th><th>Hébergeur</th><th>Base de données</th>
				<th>Ftp</th><th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";
		for ($i=0; $i<count($data);$i++)
		{
			$lien_registry_doc='<a href="http://whois.net/whois/'.$data[$i]["nom_domaine"].'"><b> Document whois</b></a>';
			$registrar="<b>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_registrar"])."</b><br/>".
					"Début : <b>".$data[$i]["date_registrar_debut"]."</b><br/>".
					"Echéance : <b>".$data[$i]["date_registrar_fin"]."</b><br/>".
					"Url : <b>".$this->affiche_url($data[$i]["url_administration_registrar"])."</b><br/>".
					"Identifiant : <b>".$data[$i]["identifiant_registrar"]." / ".$data[$i]["mot_de_passe_registrar"]."</b><br/>".
					"Coût : <b>".$data[$i]["cout_registrar"];
			$hebergement="<b>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_hebergement"])."</b><br/>".
					"Début : <b>".$data[$i]["date_hebergement_debut"]."</b><br/>".
					"Echéance : <b>".$data[$i]["date_hebergement_fin"]."</b><br/>".
					"Url : <b>".$this->affiche_url($data[$i]["url_administration_hebergement"])."</b><br/>".
					"Identifiant : <b>".$data[$i]["identifiant_hebergement"]." / ".$data[$i]["mot_de_passe_hebergement"]."</b><br/>".
					"Coût : <b>".$data[$i]["cout_hebergement"];
			$database="Serveur : <b>".$data[$i]["serveur_mysql"]."</b><br/>".
					"Url : <b>".$this->affiche_url($data[$i]["url_administration_mysql"])."</b><br/>".
					"Identifiant : <b>".$data[$i]["identifiant_mysql"]." / ".$data[$i]["mot_de_passe_mysql"];
			$ftp="Serveur : <b>".$data[$i]["serveur_ftp"]."</b><br/>".
					"Url : <b>".$this->affiche_url($data[$i]["url_administration_ftp"])."</b><br/>".
					"Identifiant : <b>".$data[$i]["identifiant_ftp"]." / ".$data[$i]["mot_de_passe_ftp"];

			$res .= "<tr><td>".($i+1)."</td><td>".$data[$i]["libelle"]."</td><td><b>".$data[$i]["nom_domaine"]."</b></td><td>".$lien_registry_doc."</td><td>".$registrar."</td><td>".$hebergement."</td><td>".$database."</td><td>".$ftp."</td><td>"
					.$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n')."</td></tr>";

		}

		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
/*	function stats_referencements_display($id_organisme)
	{
		$db = & atkGetDb();
		$sql=" SELECT
		orf.id as id_entite,
		orf.id_organisme_referencement,
		orf.id_interlocuteur,
		orf.libelle,
		tr.libelle as type_referencement,
		orf.date_inscription,
		orf.url,
		orf.date_verification,
		ter.libelle as etat_referencement,
		orf.contenu,
		orf.date_echeance,
		orf.date_resiliation,
		orf.motif_resiliation,
		DATE(orf.date_modification) as date_modification,
		orf.id_modification
		from organisme_referencement orf
		LEFT JOIN type_referencement tr ON orf.id_type_referencement=tr.id
		LEFT JOIN type_etat_referencement ter ON orf.id_type_etat_referencement=ter.id
		where orf.id_organisme=$id_organisme
		order by orf.date_modification ";
		$data = $db->getrows($sql);
		if (count($data)==0) return "";
		$res=$this->gettitre($id_organisme,"Référencements",true,"h2");

		$res .= '<table class="toc  sortable" style="width:90%;">';
		$res .= "<tr><th>#</th>
				<th>Libellé</th>
				<th>Type</th>
				<th>Organisme</th>
				<th>Interlocuteur</th>
				<th>Inscription</th>
				<th>Url</th>
				<th>Vérification</th>
				<th>Etat</th>
				<th>Contenu</th>
				<th>Echéance</th>
				<th>Résiliation</th>
				<th>Motif</th>
				<th>Mis à jour</th>
				<th>Par</th>
				<th ".$this->m_styleTitreLigneEstampille.">Estampille</th></tr>";
		for ($i=0; $i<count($data);$i++)
		{
			($data[$i]["url"]!="") ? $lien_reference=$this->affiche_url($data[$i]["url"]) : $lien_reference="";
			$res .= "<tr><td>".($i+1)."</td>
					<td><b>".$data[$i]["libelle"]."</b></td>
							<td>".$data[$i]["type_referencement"]."</td>
									<td>".$this->descripteur_organisme_sans_lien($data[$i]["id_organisme_referencement"])."</td>
											<td>".$this->descripteur_individu_sans_lien($data[$i]["id_interlocuteur"])."</td>
													<td>".$data[$i]["date_inscription"]."</td>
													<td>$lien_reference</td>
													<td>".$data[$i]["date_verification"]."</td>
															<td>".$data[$i]["etat_referencement"]."</td>
																	<td>".$data[$i]["contenu"]."</td>
																			<td>".$data[$i]["date_echeance"]."</td>
																					<td>".$data[$i]["date_resiliation"]."</td>
																							<td>".$data[$i]["motif_resiliation"]."</td>
																									<td>".$data[$i]["date_modification"]."</td>
																											<td>".$this->descripteur_individu_utilisateur($data[$i]["id_modification"],'o')."</td>
																													<td>".$this->descripteur_module_estampillage($this->get_record_info($data[$i]["id_entite"]), 'n')."</td></tr>";
		}

		$res.='</table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
		$res.=$this->sautDePage();
		return $res;
	}
	*/
	function stats_referencements_display($id_organisme)
	{
		$db = & atkGetDb();
		$res=$this->gettitre($id_organisme,"Référencements",true,"h2");
		$AnMinimum=$this->getAnMinimum($id_organisme,"Référencements");
		if ($AnMinimum<=0) return false;
		$sql=" SELECT
		distinct tc.id as id_type_referencement,
		tc.libelle as libelle_type_referencement
		from organisme_referencement oc
		LEFT JOIN type_referencement tc ON oc.id_type_referencement=tc.id
		where oc.id_organisme=$id_organisme and tc.id is not null
		order by tc.libelle";
		$data0 = $db->getrows($sql);
		$res .= '<table class="toc  sortable">';
				$res.='<thead>';
						$res.= $this->getEnTete($AnMinimum,'o');
								$res.='</thead><tbody>';
										for ($i=0;$i<count($data0);$i++)
										{
											$id_type_referencement=$data0[$i]["id_type_referencement"];
											$libelle_type_referencement=$data0[$i]["libelle_type_referencement"];
											$res .= "<tr><td ".$this->m_styleTitreLigne.">$libelle_type_referencement";
											$AnDepart=date("Y");
											for($j=$AnMinimum; $j<=$AnDepart; $j++)
												{
													$res.='</td><td>'.$this->calcul_referencement($id_organisme,$j,$id_type_referencement);
										}
										$res.='</td><td>'.$this->calcul_referencement($id_organisme,null,$id_type_referencement);
											$res.='</td></tr>';
	}
							$res .= "</tbody><tfoot><tr><td ".$this->m_styleTitreLigne.">Total";
								for($j=$AnMinimum; $j<=$AnDepart; $j++)
								{
								$res.='</td><td>'.$this->calcul_referencement($id_organisme,$j,null);
										}
										$res.='</td><td>'.$this->calcul_referencement($id_organisme,null,null);
										$res.='</td></tr></tfoot></table>'.$this->getUserStamp('o','o');
		$res.="<br/><br/>";
				$res.=$this->sautDePage();
				return $res;
			}
			


	function oui_non($value)
	{
		($value==0) ? $retour="" : $retour="<center><img class=\"recordlist\" border=\"0\" src=\"./themes/assocope/icons/assocope/releve-banque.png\" alt=\"Oui\"
				title=\"Oui\"  ></img></center>";
		return $retour;
	}
	function getAnMinimum($id_organisme,$type)
	{
		$db = & atkGetDb();
		$AnMinimum=date("Y");
		If ($type=="Inscriptions")
		{
			$data = $db->getrows("select min(year(i.date_inscription)) as an_minimum_inscription from individu_inscription i
					where i.id_organisme=$id_organisme
					and year(i.date_inscription)>2003 ");
			return $data[0]["an_minimum_inscription"];
		}
		If ($type=="Adhésions")
		{
			$data = $db->getrows("select min(year(i.date_adhesion)) as an_minimum_adhesion from individu_inscription i
					where i.id_organisme=$id_organisme
					and year(i.date_adhesion)>2003
					and i.date_adhesion is not null");
			return $data[0]["an_minimum_adhesion"];
		}
		If ($type=="Radiations")
		{
			$data = $db->getrows("select min(year(i.date_radiation)) as an_minimum_radiation from individu_inscription i
					where i.id_organisme=$id_organisme
					and year(i.date_radiation)>2003
					and i.date_radiation is not null");
			return $data[0]["an_minimum_radiation"];
		}
		If ($type=="Fonctions")
		{
			$data = $db->getrows("select min(year(ifo.date_debut)) as an_minimum_fonction from individu_fonction ifo
					where ifo.id_organisme=$id_organisme
					and year(ifo.date_debut)>2003 ");
			return $data[0]["an_minimum_fonction"];
		}
		If ($type=="Cotisations")
		{
			$data = $db->getrows("select min(oc.annee) as an_minimum_cotisation
					from organisme_cotisation oc
					where oc.id_organisme=$id_organisme
					and oc.annee>2003 ");
			return $data[0]["an_minimum_cotisation"];
		}
		If ($type=="Résultats comptables")
		{
			$data = $db->getrows("select min(year(lec.date_valeur)) as an_minimum_ecritures
					from organisme_ligne_ecriture_comptable lec
					where lec.id_organisme=$id_organisme
					and year(lec.date_valeur)>2003 ");
			return $data[0]["an_minimum_ecritures"];
		}
		If ($type=="Contacts")
		{
			$data = $db->getrows("select min(year(c.date_prevue)) as an_minimum_contact from individu_contact c
					where ( c.id_organisme_contactant=$id_organisme OR c.id_organisme_contacte=$id_organisme)
					and year(c.date_prevue)>2003
					");
			return $data[0]["an_minimum_contact"];
		}
		If ($type=="Documents")
		{
			$data = $db->getrows("select min(year(od.date_creation)) as an_minimum_document from organisme_document od
					where ( od.id_organisme=$id_organisme)
					and year(od.date_creation)>2003
					");
			return $data[0]["an_minimum_document"];
		}
		If ($type=="Gazettes")
		{
			$data = $db->getrows("select min(year(og.date_creation)) as an_minimum_gazette from organisme_gazette og
					where ( og.id_organisme=$id_organisme)
					and year(og.date_creation)>2003
					");
			return $data[0]["an_minimum_gazette"];
		}
		If ($type=="Immatriculations")
		{
			$data = $db->getrows("select min(year(oi.date_creation)) as an_minimum_immatriculation from organisme_immatriculation oi
					where ( oi.id_organisme=$id_organisme)
					and year(oi.date_creation)>2003
					");
					return $data[0]["an_minimum_immatriculation"];
		}
		If ($type=="Patrimoine")
		{
			$data = $db->getrows("select min(year(op.date_creation)) as an_minimum_patrimoine from organisme_patrimoine op
					where ( op.id_organisme=$id_organisme)
					and year(op.date_creation)>2003
					");
					return $data[0]["an_minimum_patrimoine"];
		}
		If ($type=="Contrats")
		{
			$data = $db->getrows("select min(year(oc.date_creation)) as an_minimum_contrat from organisme_contrat oc
					where ( oc.id_organisme=$id_organisme)
					and year(oc.date_creation)>2003
					");
					return $data[0]["an_minimum_contrat"];
		}
		If ($type=="Référencements")
		{
			$data = $db->getrows("select min(year(oref.date_creation)) as an_minimum_referencement from organisme_referencement oref
					where ( oref.id_organisme=$id_organisme)
					and year(oref.date_creation)>2003
					");
					return $data[0]["an_minimum_referencement"];
		}
		
			}

	function getEnTete($AnMinimum,$colonne_actuel_o_n='o',$resultats_comptables_o_n='n',$type_log='',$contenu_log='')
	/*
	 * 	type log : node_action, utilisateur
	* contenu_log : total, heure, jour, mois
	*/
	{

		//		echo "<br/>type".$type_log."<br/>contenu".$contenu_log."<br/>anminimum".$AnMinimum;die();
		$AnDepart=date("Y");
		if ($resultats_comptables_o_n=='o')
		{
			$res="<tr><th>#";
			$res.="</th><th>Code";
			$res.="</th><th>Libellé";
			$res.="</th><th>Solde<br/>initial";
			$textes="Solde<br/>" ;
		}
		if ($contenu_log!="")
		{
			$res="<tr><th>#";
			if ($contenu_log=="utilisateur")
			{
				$res="</th><th>Utilisateur";
			}
			if ($contenu_log=="node_action")
			{
				$res.="</th><th>Noeud";
				$res.="</th><th>Action";
			}
			if	($type_log=="total")
			{
				$AnDepart=date("Y");
			}
			else
			{
				$AnMinimum="0";
				($type_log=="heure") ?$textes="Heure<br/> - <br/>" :null;
				($type_log=="jour") ?$textes="Jour<br/> - <br/>" :null;
				($type_log=="mois") ?$textes="Mois<br/> - <br/>" :null;
				($type_log=="heure")? $AnDepart="23" :null;
				($type_log=="jour") ?$AnDepart="30":null;
				($type_log=="mois") ?$AnDepart="11" :null;
			}
		}
		if ($resultats_comptables_o_n=='n' && $contenu_log=="")
		{
			$res = "<tr><th>Année";
		}
		for($i=$AnMinimum; $i<=$AnDepart; $i++)
		{
			if ($type_log!="" && $type_log!="total")
			{
				$res.="</th><th>".$textes.($AnDepart-$i);
			}
			else
			{
				$res.="</th><th>".$textes.$i;
			}
		}
		($colonne_actuel_o_n=='o') ? $res.='</th><th>Actuel<br/>/ Cumul<br/>/ Total</th></tr>' : $res.='</th></tr>';
		return $res;
	}
	function calcul_inscription($id_organisme,$an, $id_type_inscription)
	{
		($id_type_inscription>0) ? $type=" and individu_inscription.id_type_inscription=$id_type_inscription" : $type="";
		$db = & atkGetDb();
		If ($an>0)
		{
			$data = $db->getrows("select count(individu_inscription.id) as nombre ,
					ti.libelle as type_inscription,
					o.nom as organisme,
					year(individu_inscription.date_inscription) as annee
					from individu_inscription
					LEFT JOIN type_inscription ti ON individu_inscription.id_type_inscription=ti.id
					LEFT JOIN organisme o ON individu_inscription.id_organisme=o.id
					where individu_inscription.id_organisme=$id_organisme ". $type."
					and year(individu_inscription.date_inscription) = $an");
		}
		else {
			$data = $db->getrows("select count(individu_inscription.id) as nombre,
					ti.libelle as type_inscription,
					o.nom as organisme
					from individu_inscription
					LEFT JOIN type_inscription ti ON individu_inscription.id_type_inscription=ti.id
					LEFT JOIN organisme o ON individu_inscription.id_organisme=o.id
					where individu_inscription.id_organisme=$id_organisme  ". $type."
					and individu_inscription.date_radiation is null");
		}
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Type inscription : <b>'.$data[0]["type_inscription"].'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'inscription',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme  . "
						". $type." and year(individu_inscription.date_inscription)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Type inscription : <b>'.$data[0]["type_inscription"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,'type'=>'inscription',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme  . "
						". $type." and individu_inscription.date_radiation is null "
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_adhesion($id_organisme,$an)
	{
		$db = & atkGetDb();
		If ($an>0)
		{
			$data = $db->getrows("select count(i.id) as nombre ,
					ti.libelle as type_inscription,
					o.nom as organisme,
					year(i.date_adhesion) as annee
					from individu_inscription i
					LEFT JOIN type_inscription ti ON i.id_type_inscription=ti.id
					LEFT JOIN organisme o ON i.id_organisme=o.id
					where i.date_adhesion is not null
					and i.id_organisme=$id_organisme
					and year(i.date_adhesion) = $an");
		}
		else {
			$data = $db->getrows("select count(i.id) as nombre,
					ti.libelle as type_inscription,
					o.nom as organisme
					from individu_inscription i
					LEFT JOIN type_inscription ti ON i.id_type_inscription=ti.id
					LEFT JOIN organisme o ON i.id_organisme=o.id
					where i.date_adhesion is not null
					and i.id_organisme=$id_organisme
					and date_radiation is null");
		}
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'adhesion',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme . " and individu_inscription.date_adhesion is not null
						and year(individu_inscription.date_adhesion)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'adhesion',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme . " and individu_inscription.date_adhesion is not null
						and individu_inscription.date_radiation is null "
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_immatriculation($id_organisme,$an)
	{
		$db = & atkGetDb();
		If ($an>0)
		{
			$data = $db->getrows("select count(oi.id) as nombre,
					year(oi.date_creation) as annee,
					o.nom as organisme
					from organisme_immatriculation oi
					LEFT JOIN organisme o ON oi.id_organisme=o.id
					where  oi.id_organisme=$id_organisme
					and year(oi.date_creation) = $an");
		}
		else {
			$data = $db->getrows("select count(oi.id) as nombre,
					o.nom as organisme
					from organisme_immatriculation oi
					LEFT JOIN organisme o ON oi.id_organisme=o.id
					where  oi.id_organisme=$id_organisme
					");
		}
		if ($data[0]["nombre"] > 0) {
		If ($an>0)
		{
		return href(dispatch_url("organisme.immatriculation", "admin_liste", array (
				'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
				.'</b>Année : <b>'.$data[0]["annee"],
				'id'=>$id_organisme,
				'id_organisme'=>$id_organisme,
				'type'=>'immatriculation',
				'atkfilter' => "organisme_immatriculation.id_organisme=" . $id_organisme . " and year(organisme_immatriculation.date_creation)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
		}
		else
		{
		return href(dispatch_url("organisme.immatriculation", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
							'id'=>$id_organisme,
									'id_organisme'=>$id_organisme,
						'type'=>'immatriculation',
							'atkfilter' => "organisme_immatriculation.id_organisme=" . $id_organisme 
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
		}
		} else {
		return "";
		}
		}
		function calcul_patrimoine($id_organisme,$an)
		{
			$db = & atkGetDb();
			If ($an>0)
			{
				$data = $db->getrows("select count(op.id) as nombre,
						year(op.date_creation) as annee,
						o.nom as organisme
						from organisme_patrimoine op
						LEFT JOIN organisme o ON op.id_organisme=o.id
						where  op.id_organisme=$id_organisme
						and year(op.date_creation) = $an");
			}
			else {
				$data = $db->getrows("select count(op.id) as nombre,
						o.nom as organisme
						from organisme_patrimoine op
						LEFT JOIN organisme o ON op.id_organisme=o.id
						where  op.id_organisme=$id_organisme
						");
			}
			if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
			return href(dispatch_url("organisme.patrimoine", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
				.'</b>Année : <b>'.$data[0]["annee"],
					'id'=>$id_organisme,
					'id_organisme'=>$id_organisme,
					'type'=>'patrimoine',
				'atkfilter' => "organisme_patrimoine.id_organisme=" . $id_organisme . " and year(organisme_patrimoine.date_creation)=".$an.""
						), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
			return href(dispatch_url("organisme.patrimoine", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
					'id'=>$id_organisme,
					'id_organisme'=>$id_organisme,
						'type'=>'patrimoine',
					'atkfilter' => "organisme_patrimoine.id_organisme=" . $id_organisme
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			} else {
			return "";
			}
			}
		
	function calcul_radiation($id_organisme,$an,$id_type_radiation)
	{
		$db = & atkGetDb();
		($id_type_radiation>0) ? $type=" and individu_inscription.id_type_radiation=$id_type_radiation" : $type="";
		If ($an>0)
		{
			$data = $db->getrows("select count(individu_inscription.id) as nombre ,
					ti.libelle as type_inscription,
					o.nom as organisme,
					year(individu_inscription.date_radiation) as annee
					from individu_inscription
					LEFT JOIN type_inscription ti ON individu_inscription.id_type_inscription=ti.id
					LEFT JOIN organisme o ON individu_inscription.id_organisme=o.id
					where individu_inscription.date_radiation is not null
					" . $type."
					and individu_inscription.id_organisme=$id_organisme
					and year(individu_inscription.date_radiation) = $an");
		}
		else {
			$data = $db->getrows("select count(individu_inscription.id) as nombre,
					ti.libelle as type_inscription,
					o.nom as organisme
					from individu_inscription
					LEFT JOIN type_inscription ti ON individu_inscription.id_type_inscription=ti.id
					LEFT JOIN organisme o ON individu_inscription.id_organisme=o.id
					where individu_inscription.date_radiation is not null
					" . $type."
					and individu_inscription.id_organisme=$id_organisme
					");
		}
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'radiation',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme . " and individu_inscription.date_radiation is not null " . $type."
						and year(individu_inscription.date_radiation)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("individu.inscription_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'radiation',
						'atkfilter' => "individu_inscription.id_organisme=" . $id_organisme . " and individu_inscription.date_radiation is not null " . $type."
						"
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_document($id_organisme,$an,$id_type_document)
	{
		$db = & atkGetDb();
		($id_type_document>0) ? $type=" and organisme_document.id_type_document=$id_type_document" : $type="";
		If ($an>0)
		{
			$data = $db->getrows("select count(organisme_document.id) as nombre ,
					td.libelle as type_document,
					td.id as id_type_document,
					o.nom as organisme,
					year(organisme_document.date_creation) as annee
					from organisme_document
					LEFT JOIN type_document td ON organisme_document.id_type_document=td.id
					LEFT JOIN organisme o ON organisme_document.id_organisme=o.id
					where
				 organisme_document.id_organisme=$id_organisme
					" . $type."
					and year(organisme_document.date_creation) = $an");
			//			echo $data[0]["nombre"]." ".$data[0]["annee"]." ".$data[0]["type_document"]."<br/>";
			//			($an==2013) ? die() : null;
		}
		else {
			$data = $db->getrows("select count(organisme_document.id) as nombre ,
					td.libelle as type_document,
					o.nom as organisme,
					year(organisme_document.date_creation) as annee
					from organisme_document
					LEFT JOIN type_document td ON organisme_document.id_type_document=td.id
					LEFT JOIN organisme o ON organisme_document.id_organisme=o.id
					where
				 organisme_document.id_organisme=$id_organisme
					" . $type
			);
		}
		//		$this->p($data);
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("organisme.document", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'document',
						'atkfilter' => "organisme_document.id_organisme=" . $id_organisme .  $type."
						and year(organisme_document.date_creation)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("organisme.document", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'document',
						'atkfilter' => "organisme_document.id_organisme=" . $id_organisme . $type."
						"
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_referencement($id_organisme,$an,$id_type_referencement)
	{
		$db = & atkGetDb();
		($id_type_referencement>0) ? $type=" and organisme_referencement.id_type_referencement=$id_type_referencement" : $type="";
		If ($an>0)
		{
			$data = $db->getrows("select count(organisme_referencement.id) as nombre ,
					tc.libelle as type_referencement,
					tc.id as id_type_referencement,
					o.nom as organisme,
					year(organisme_referencement.date_creation) as annee
					from organisme_referencement
					LEFT JOIN type_referencement tc ON organisme_referencement.id_type_referencement=tc.id
					LEFT JOIN organisme o ON organisme_referencement.id_organisme=o.id
					where
					organisme_referencement.id_organisme=$id_organisme
					" . $type."
					and year(organisme_referencement.date_creation) = $an");
			//			echo $data[0]["nombre"]." ".$data[0]["annee"]." ".$data[0]["type_referencement"]."<br/>";
			//			($an==2013) ? die() : null;
		}
		else {
			$data = $db->getrows("select count(organisme_referencement.id) as nombre ,
					tc.libelle as type_referencement,
					o.nom as organisme,
					year(organisme_referencement.date_creation) as annee
					from organisme_referencement
					LEFT JOIN type_referencement tc ON organisme_referencement.id_type_referencement=tc.id
					LEFT JOIN organisme o ON organisme_referencement.id_organisme=o.id
					where
					organisme_referencement.id_organisme=$id_organisme
					" . $type
			);
		}
		//		$this->p($data);
		if ($data[0]["nombre"] > 0) {
		If ($an>0)
		{
		return href(dispatch_url("organisme.referencement", "admin_liste", array (
				'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
				.'</b>Année : <b>'.$data[0]["annee"],
				'id'=>$id_organisme,
				'id_organisme'=>$id_organisme,
				'type'=>'referencement',
				'atkfilter' => "organisme_referencement.id_organisme=" . $id_organisme .  $type."
				and year(organisme_referencement.date_creation)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
		}
		else
		{
		return href(dispatch_url("organisme.referencement", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
						'id'=>$id_organisme,
									'id_organisme'=>$id_organisme,
									'type'=>'referencement',
									'atkfilter' => "organisme_referencement.id_organisme=" . $id_organisme . $type."
						"
											), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
		}
		} else {
		return "";
		}
		}
		function calcul_contrat($id_organisme,$an,$id_type_contrat)
		{
			$db = & atkGetDb();
			($id_type_contrat>0) ? $type=" and organisme_contrat.id_type_contrat=$id_type_contrat" : $type="";
			If ($an>0)
			{
				$data = $db->getrows("select count(organisme_contrat.id) as nombre ,
						tc.libelle as type_contrat,
						tc.id as id_type_contrat,
						o.nom as organisme,
						year(organisme_contrat.date_creation) as annee
						from organisme_contrat
						LEFT JOIN type_contrat tc ON organisme_contrat.id_type_contrat=tc.id
						LEFT JOIN organisme o ON organisme_contrat.id_organisme=o.id
						where
						organisme_contrat.id_organisme=$id_organisme
						" . $type."
						and year(organisme_contrat.date_creation) = $an");
				//			echo $data[0]["nombre"]." ".$data[0]["annee"]." ".$data[0]["type_contrat"]."<br/>";
				//			($an==2013) ? die() : null;
			}
			else {
				$data = $db->getrows("select count(organisme_contrat.id) as nombre ,
						tc.libelle as type_contrat,
						o.nom as organisme,
						year(organisme_contrat.date_creation) as annee
						from organisme_contrat
						LEFT JOIN type_contrat tc ON organisme_contrat.id_type_contrat=tc.id
						LEFT JOIN organisme o ON organisme_contrat.id_organisme=o.id
						where
						organisme_contrat.id_organisme=$id_organisme
						" . $type
				);
			}
			//		$this->p($data);
			if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
			return href(dispatch_url("organisme.contrat", "admin_liste", array (
					'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
					.'</b>Année : <b>'.$data[0]["annee"],
				'id'=>$id_organisme,
					'id_organisme'=>$id_organisme,
					'type'=>'contrat',
				'atkfilter' => "organisme_contrat.id_organisme=" . $id_organisme .  $type."
					and year(organisme_contrat.date_creation)=".$an.""
			), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
					else
					{
					return href(dispatch_url("organisme.contrat", "admin_liste", array (
							'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
							'id'=>$id_organisme,
							'id_organisme'=>$id_organisme,
							'type'=>'contrat',
							'atkfilter' => "organisme_contrat.id_organisme=" . $id_organisme . $type."
							"
					), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
					}
					} else {
					return "";
					}
					}
	function calcul_gazette($id_organisme,$an,$id_type_audience)
	{
		$db = & atkGetDb();
		($id_type_audience>0) ? $type=" and organisme_gazette.id_type_audience=$id_type_audience" : $type="";
		If ($an>0)
		{
			$data = $db->getrows("select count(organisme_gazette.id) as nombre ,
					ta.libelle as type_audience,
					ta.id as id_type_audience,
					o.nom as organisme,
					year(organisme_gazette.date_creation) as annee
					from organisme_gazette
					LEFT JOIN type_audience ta ON organisme_gazette.id_type_audience=ta.id
					LEFT JOIN organisme o ON organisme_gazette.id_organisme=o.id
					where
					organisme_gazette.id_organisme=$id_organisme
					" . $type."
					and year(organisme_gazette.date_creation) = $an");
			//			echo $data[0]["nombre"]." ".$data[0]["annee"]." ".$data[0]["type_document"]."<br/>";
			//			($an==2013) ? die() : null;
		}
		else {
			$data = $db->getrows("select count(organisme_gazette.id) as nombre ,
					ta.libelle as type_audience,
					o.nom as organisme,
					year(organisme_gazette.date_creation) as annee
					from organisme_gazette
					LEFT JOIN type_audience ta ON organisme_gazette.id_type_audience=ta.id
					LEFT JOIN organisme o ON organisme_gazette.id_organisme=o.id
					where
					organisme_gazette.id_organisme=$id_organisme
					" . $type
			);
		}
		//		$this->p($data);
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("organisme.gazette", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'document',
						'atkfilter' => "organisme_gazette.id_organisme=" . $id_organisme .  $type."
						and year(organisme_gazette.date_creation)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("organisme.gazette", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>',
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'type'=>'document',
						'atkfilter' => "organisme_gazette.id_organisme=" . $id_organisme . $type."
						"
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_log($type_log="total",$contenu_log="node-action",$stamp_min, $compteur_interval, $node="", $action="", $id_utilisateur="", $remote_address="")
	{
		$db = & atkGetDb();
		$compteur1=$compteur_interval;
		$compteur2=$compteur_interval+1;

		($type_log=="total") ? $interval="YEAR" : null;
		($type_log=="heure") ? $interval="HOUR" : null;
		($type_log=="jour") ? $interval="DAY" : null;
		($type_log=="mois") ? $interval="MONTH" : null;

		if ($compteur_interval>=0)
		{
			($compteur_interval>0) ? $critere1=" stamp>ADDDATE('$stamp_min', INTERVAL $compteur1 $interval)
			AND stamp<=ADDDATE('$stamp_min', INTERVAL $compteur2 $interval)" : $critere1=" stamp>'$stamp_min'
			AND stamp<=ADDDATE('$stamp_min', INTERVAL $compteur2 $interval)";
		}
		else
		{
			$critere1=" stamp>'$stamp_min'			";
		}

		($contenu_log=="utilisateur") ? $type=" userid='$id_utilisateur' AND LENGTH(node) >0
		AND node!='.'
		AND LENGTH(action) >0 " : null;

		($contenu_log=="error") ? $type=" userid='$id_utilisateur' AND LENGTH(error_message) >0
		" : null;

		($contenu_log=="node_action") ? $type=" atkeventlog.node='$node' AND atkeventlog.action='$action'" : null;
		if ($stamp_min=="")
		{
			$data = $db->getrows("SELECT
				 count(id) as nombre
					FROM atkeventlog
					WHERE  $type

					");
		}
		else
		{	$data = $db->getrows("SELECT
				count(id) as nombre
				FROM atkeventlog
				WHERE  $type
				AND $critere1
				");
		}
		if ($data[0]["nombre"] > 0) {
			If ($stamp_min!="")
			{
				return href(dispatch_url("profil.log", "admin_liste", array (
						'atkfiltre'=>'</b>Type de log : <b>'.$type_log.'<br/>'
						.'</b>Contenu de log : <b>'.$contenu_log
						.' entre '.$stamp_min .' et '.$stamp_max,
						"id_utilisateur"=>$id_utilisateur,
						'atkfilter' => $type." AND ".$critere1
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("organisme.document", "admin_liste", array (
						'atkfiltre'=>'</b>Type de log : <b>'.$type_log.'<br/>'
						.'</b>Contenu de log : <b>'.$contenu_log,
						'id_utilisateur'=>$id_utilisateur,
						'atkfilter' => "organisme_document.id_organisme=" . $id_organisme . $type."
						"
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_contact($id_organisme,$an,$id_type_contact)
	{
		$db = & atkGetDb();
		($id_type_contact>0) ? $type=" and individu_contact.id_type_contact=$id_type_contact " : $type="";
		$data = $db->getrows("select nom from organisme where id=$id_organisme");
		$nom_organisme=$data[0]["nom"];
		If ($an>0)
		{
			$data = $db->getrows("select count(individu_contact.id) as nombre ,
					tc.libelle as type_contact,
					year(individu_contact.date_prevue) as annee
					from individu_contact
					LEFT JOIN type_contact tc ON individu_contact.id_type_contact=tc.id
					where individu_contact.date_prevue is not null
					" . $type."
					and  (individu_contact.id_organisme_contactant=$id_organisme
					OR individu_contact.id_organisme_contacte=$id_organisme )
					and year(individu_contact.date_prevue) = $an");
		}
		else {
			$data = $db->getrows("select count(individu_contact.id) as nombre ,
					tc.libelle as type_contact,
					year(individu_contact.date_prevue) as annee
					from individu_contact
					LEFT JOIN type_contact tc ON individu_contact.id_type_contact=tc.id
					where individu_contact.date_prevue is not null
					" . $type."
					and  (individu_contact.id_organisme_contactant=$id_organisme
					OR individu_contact.id_organisme_contacte=$id_organisme )");
		}
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				/*				return href(dispatch_url("individu.contact_i", "admin_liste", array (
				 'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'atkfilter' => "(individu_contact.id_organisme_contactant=" . $id_organisme . " OR individu_contact.id_organisme_contactant=" . $id_organisme . ")
						and individu_contact.date_prevue is not null " . $type."
						and year(individu_contact.date_prevue)=".$an.""
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
				*/
				$filtre="(individu_contact.id_organisme_contactant=$id_organisme OU individu_contact.id_organisme_contacte=$id_organisme )
				and individu_contact.date_prevue is not null $type and year(individu_contact.date_prevue)= $an ";

				return href(dispatch_url("individu.contact_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'
						.'</b>Année : <b>'.$data[0]["annee"].'<br/>'
						.'</b>Type de contact : <b>'.$data[0]["type_contact"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'atkfilter'=>$filtre
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				$filtre="(individu_contact.id_organisme_contactant= $id_organisme  OU  individu_contact.id_organisme_contacte= $id_organisme )
				and individu_contact.date_prevue is not null  $type ";
				return href(dispatch_url("individu.contact_i", "admin_liste", array (
						'atkfiltre'=>'</b>Organisme : <b>'.$nom_organisme.'<br/>'
						.'</b>Type de contact : <b>'.$data[0]["type_contact"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'atkfilter'=>$filtre
				), "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED, false, $this->target_tbdebord);
			}
		} else {
			return "";
		}
	}
	function calcul_fonction($id_organisme,$an, $id_type_fonction)
	{
		$db = & atkGetDb();
		If ($an>0)
		{
			$sql="select count(ifo.id) as nombre, o.nom as organisme, tf.libelle as type_fonction
			from individu_fonction ifo, organisme o, type_fonction tf
			where ifo.id_fonction=$id_type_fonction
			AND ifo.id_fonction=tf.id
			AND ifo.id_organisme=$id_organisme
			AND ifo.id_organisme=o.id
			AND YEAR(ifo.date_debut)<= $an
			AND (YEAR(ifo.date_fin) >= $an OR ifo.date_fin is null)
			";
			$data = $db->getrows($sql);
		}
		else {
			$sql="select count(ifo.id) as nombre, o.nom as organisme, tf.libelle as type_fonction
			from individu_fonction ifo, organisme o, type_fonction tf
			where ifo.id_fonction=$id_type_fonction
			AND ifo.id_fonction=tf.id
			AND ifo.id_organisme=$id_organisme
			AND ifo.id_organisme=o.id
			AND ifo.date_fin is null
			";
			$data = $db->getrows($sql);
		}
		if ($data[0]["nombre"] > 0) {
			If ($an>0)
			{
				return href(dispatch_url("individu.fonction_i", "admin_liste", array (
						'view' => "nonactive",
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Type fonction : <b>'.$data[0]["type_fonction"].'<br/>'
						.'</b>Année : <b>'.$an,
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'atkfilter' => " individu_fonction.id_organisme =". $id_organisme
						." and individu_fonction.id_fonction =". $id_type_fonction
						." AND YEAR(date_debut)<= $an
						AND (YEAR(date_fin) >= $an OR date_fin is null)" )
						, "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") ,  SESSION_NESTED, false, $this->target_tbdebord);
			}
			else
			{
				return href(dispatch_url("individu.fonction_i", "admin_liste", array (
						'view' => "nonactive",
						'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["organisme"].'<br/>'
						.'</b>Type fonction : <b>'.$data[0]["type_fonction"],
						'id'=>$id_organisme,
						'id_organisme'=>$id_organisme,
						'atkfilter' => " individu_fonction.id_organisme =". $id_organisme
						." and individu_fonction.id_fonction =". $id_type_fonction
						." AND  date_fin is null" )
						, "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") ,  SESSION_NESTED, false, $this->target_tbdebord);
			}
		}
		else {
			return "";
		}
	}
	function calcul_cotisation($id_organisme,$an, $id_cotisation,$agregat)
	{
		$db = & atkGetDb();
		If ($agregat=="nombre")
		{
			$sqlpart=" COUNT( i.id ) AS nombredecotisations	";
		}
		If ($agregat=="versement")
		{
			$sqlpart=" SUM( i.montant_versement ) AS montant_versement	";
		}
		If ($agregat=="cotisation")
		{
			$sqlpart=" SUM( i.`montant_cotisation_organisme` ) AS montant_cotisation_organisme	";
		}
		If ($agregat=="don")
		{
			$sqlpart=" SUM( i.`montant_don` ) AS montant_don	";
		}
		$sql="SELECT oc.annee, oc.libelle, o.nom as nom_organisme, ".
				$sqlpart
				." FROM individu_cotisation i, organisme_cotisation oc, organisme o
				WHERE i.id_cotisation=$id_cotisation
				AND i.id_cotisation=oc.id
				AND oc.id_organisme=o.id
				";
		$data = $db->getrows($sql);

		If ($agregat=="nombre")
		{
			$lien=$this->nombre_format($data[0]["nombredecotisations"],"b");
		}
		If ($agregat=="versement")
		{
			$lien=$this->nombre_format($data[0]["montant_versement"],"b");
		}
		If ($agregat=="cotisation")
		{
			$lien=$this->nombre_format($data[0]["montant_cotisation_organisme"],"b");
		}
		If ($agregat=="don")
		{
			$lien=$this->nombre_format($data[0]["montant_don"],"b");
		}
		return href(dispatch_url("individu.cotisation_i", "admin_liste", array (
				'atkfiltre'=>'</b>Organisme : <b>'.$data[0]["nom_organisme"].'<br/>'
				.'</b>Libellé cotisation : <b>'.$data[0]["libelle"].'<br/>'
				.'</b>Année cotisation : <b>'.$an,
				'id_organisme'=>$id_organisme,
				'id'=>$id_organisme,
				'type'=>'cotisation',
				'atkfilter' => "individu_cotisation.id_cotisation=" . $id_cotisation
		), "dispatch.php"), $lien , SESSION_NESTED, false, $this->target_tbdebord);


	}
	function table_test()
	{
		return		"<table>
				<thead>
				<tr>
				<th ".$this->m_styleTitreLigne.">header1</th>
						<th ".$this->m_styleTitreLigne.">header2</th>
								<th ".$this->m_styleTitreLigne.">header3</th>
										<th ".$this->m_styleTitreLigne.">header4</th>
												<th ".$this->m_styleTitreLigne.">header5</th>
														<th ".$this->m_styleTitreLigne.">header6</th>
																<th ".$this->m_styleTitreLigne.">header7</th>
																		<th ".$this->m_styleTitreLigne.">header8</th>
																				<th ".$this->m_styleTitreLigne.">header9</th>
																						<th ".$this->m_styleTitreLigne.">header10</th>
																								<th ".$this->m_styleTitreLigne.">header11</th>
																										<th ".$this->m_styleTitreLigne.">header12</th>
																												<th ".$this->m_styleTitreLigne.">header13</th>
																														</tr>
																														</thead>
																														<tbody>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																														<tr>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														<td>text</td>
																														</tr>
																															

																															
																															
																															
																														</tbody>
																														<table>";
	}






}
?>