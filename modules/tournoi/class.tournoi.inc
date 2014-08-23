<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
require('modules/tournoi/class.roundrobin.php');


class tournoi extends assMetaNode
{
	var $table="organisme_tournoi";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function tournoi()
	{
		$this->atkMetaNode();
		$this->atkNode("tournoi", NF_ADD_LINK |NF_EDITAFTERADD | NF_MRA | NF_COMPACT_NULL);
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id_organisme",
						"libelle",
						"id_type_tournoi",
						"nombre_d_equipes",
						"nombre_de_participants_individuels",
						"id_lieu_rencontre",
						"date_debut_tournoi",
						"date_fin_tournoi",
						"blocage_generation_o_n",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Descripteurs" => array (
						"participants",
						"equipes",
						"rencontres"
				)
		), AF_NO_LABEL));
		$this->add(new atkDummyAttribute("descripteur_tournoi",0, AF_COMPACT),NULL,10);
		$this->add(new atkDummyAttribute("descripteur_listes_web",0, AF_COMPACT),NULL,11);
			
		$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),20000);
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE|AF_OBLIGATORY), NULL, 20010);
		$this->add(new atkManyToOneRelation("id_type_tournoi", "table.type_tournoi", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK ),null,20020);
		$this->add(new atkNumberAttribute('nombre_d_equipes',null,2,0),20030);
		$this->add(new atkNumberAttribute('nombre_de_participants_individuels',null,2,0),20040);
		$this->add(new atkManyToOneRelation("id_lieu_rencontre", "organisme.golf_parcours", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK |AF_RELATION_AUTOCOMPLETE),null,20055);
		$this->add(new atkDateAttribute("date_debut_tournoi","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),20060);
		$this->add(new atkDateAttribute("date_fin_tournoi","Y-m-d","Y-m-d", 0, 0, AF_DATE_STRING),20070);
		$this->add(new atkBoolAttribute("blocage_generation_o_n"),20075);
		$this->add(new atgNumberExpressionAttribute("participants", ' select count(id) from individu_tournoi
				where  id_tournoi =[table].id 					', 0, 0),20080);
		$this->add(new atgNumberExpressionAttribute("equipes", ' select count(id) from tournoi_equipe
				where  id_tournoi =[table].id 					', 0, 0),20090);

		$this->add(new atgNumberExpressionAttribute("rencontres", ' select count(id) from tournoi_rencontre
				where  id_tournoi =[table].id 					', 0, 0),20100);

		include_once(atkconfig("atkroot")."modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,15);
		$this->setSecurityAlias("organisme.organisme");
		$this->m_securityMap["inscrire_du_presse_papier"] = "view";
		$this->m_securityMap["generer_equipes_et_rencontres"] = "view";
		//			$this->m_securityMap["lister_les_participants"] = "view";
		$this->m_securityMap["lister_les_equipes"] = "view";
		$this->m_securityMap["lister_les_equipes_sans_coordonnées"] = "view";
		$this->m_securityMap["lister_les_rencontres"] = "view";
		$this->m_securityMap["lister_les_rencontres_par_equipe"] = "view";
		$this->m_securityMap["lister_tout"] = "view";
		$this->m_securityMap["bloquer_la_generation_des_rencontres"] = "view";
		$this->m_securityMap["debloquer_la_generation_des_rencontres"] = "view";
	}
	function descriptor_def()
	{
		return "[libelle] - [id_organisme.nom]";
	}
	function descripteur_tournoi_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_tournoi($record["id"]),50);
	}
	function descripteur_listes_web_display($record, $mode) {
		$upload_dir=$this->get_upload_dir($record["id"]);
		return $this->descripteur_tournoi_listes_web($record["id"],$upload_dir,"o");
	}

	function recordActions($rec, & $actions, & $mraactions) {
		parent::recordActions($rec, $actions, $mraactions);
		$actions["inscrire_du_presse_papier"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=inscrire_du_presse_papier&atkselector=[pk]", SESSION_NESTED);
		$mraactions["inscrire_du_presse_papier"] ="inscrire_du_presse_papier";
		$actions["generer_equipes_et_rencontres"] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=generer_equipes_et_rencontres&atkselector=[pk]", SESSION_NESTED);
		$mraactions["bloquer_la_generation_des_rencontres"] ="bloquer_la_generation_des_rencontres";
		$mraactions["debloquer_la_generation_des_rencontres"] ="debloquer_la_generation_des_rencontres";
		//		$mraactions["lister_les_participants"] ="lister_les_participants";
		$mraactions["lister_les_equipes"] ="lister_les_equipes";
		$mraactions["lister_les_rencontres"] ="lister_les_rencontres";
		$mraactions["lister_les_rencontres_par_equipe"] ="lister_les_rencontres_par_equipe";
		$mraactions["lister_les_equipes_sans_coordonnées"] ="lister_les_equipes_sans_coordonnées";
		$mraactions["lister_tout"] ="lister_tout";


	}
	function action_inscrire_du_presse_papier() {
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$user = getUser();
		$userid = $user["id"];
		global $g_sessionManager;
		//		$id_individu_1 = $g_sessionManager->getValue("atgIdIndividuUtilisateur", "globals");
		$userid = $user["id"];
		$nom_variable = "id_individu";
		$db = & atkGetDb();
		$requete = "SELECT distinct id_variable FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$data = $db->getrows($requete);
		//		$this->p($data);
		if (count($data) == 0) {
			$db->commit();
			$this->redirect();
		}
		foreach ($select as $id_variable) {
			$id_tournoi = explode('=', $id_variable);
			$id_tournoi_1 = $id_tournoi[1];

			foreach ($data as $id_individu) {
				$id_individu_1 = $id_individu["id_variable"];
				$requete = "INSERT INTO individu_tournoi
						(  id_individu,id_tournoi,date_inscription,
						commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
						VALUES( '$id_individu_1' ,$id_tournoi_1,UTC_TIMESTAMP(),
						'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
						ON DUPLICATE KEY UPDATE id_modification=id_modification ";
				$db->query($requete);
				$db->query("UPDATE db_sequence set nextid=nextid+1 where seq_name='seq_individu_tournoi' ");
			}
		}

		$requete = "DELETE  FROM tmp_copier_coller where nom_variable='id_individu' and id_utilisateur='" . $userid . "' ";
		$db->query($requete);
		$db->commit();
		$this->redirect();
		die();
	}
	function traitement_select($select, & $idorganisme, & $idindividus, & $idrencontres) {
		$db = & atkGetDb();
		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$chaineid .= $array_id[1] . ',';
		}
		$idrencontres = substr($chaineid, 0, strlen($chaineid) - 1);
		$sql1 = 'select distinct id_individu from individu_tournoi
				where id_tournoi in (' . $idrencontres . ')  ';
		$data = $db->getrows($sql1);
		for ($i = 0; $i < count($data); $i++) {
			$chaineidindividu .= $data[$i]["id_individu"] . ',';
		}
		$idindividus = substr($chaineidindividu, 0, strlen($chaineidindividu) - 1);
		$sql = 'select distinct id_organisme from organisme_tournoi
				where id in (' . $idrencontres . ')';
		$data = $db->getrows($sql);
		$idorganisme = $data[0]["id_organisme"];
		return true;
	}
	function id_lieu_rencontre_display($record, $mode) {
		return $this->decoupe_affichage_colonne($this->descripteur_golf_parcours($record["id_lieu_rencontre"]["id"],'o').'<br />',150);
	}

	function action_lister_les_equipes() {

		$this->	lister_les_equipes(true);
	}
	function action_lister_les_equipes_sans_coordonnées() {
		$this->	lister_les_equipes(false);
	}
	function action_lister_tout() {

		//$this->p($this->m_postvars["atkselector"]);
		$this->action_lister_les_equipes();
		$this->action_lister_les_equipes_sans_coordonnées();
		$this->action_lister_les_rencontres();
		$this->action_lister_les_rencontres_par_equipe();
	}

	function lister_les_equipes($complet_o_n=true) {

		/*
		 *
		$tableau_selection=$this->get_row_selection_information(false);
		$idrencontresin=$tableau_selection["in_id_string"];
		$idtournois=$tableau_selection["node_ids"];
		*/

		$tableau_selection=$this->get_row_selection_information(false);
		$idtournois=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		$idtournoisin=$tableau_selection["in_id_string"];
		$nombretournois=$tableau_selection["rows_number"];
//		$this->p($tableau_selection);
	

		foreach ($idtournois as $tournoi_id)

		{
				

			

			if ($complet_o_n==false)
			{
				$sql="select
				sum(tre.score) as score, count(trm.date_rencontre_effective) as nombre_matches, tre.id_tournoi_equipe as equipe
				from tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_rencontre_match trm
				where te.nom_d_equipe!='Equipe quartier libre' and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is not null
				and tre.id_tournoi_equipe=te.id and te.id_tournoi=$tournoi_id
				group by tre.id_tournoi_equipe
				order by 1 desc, nombre_matches asc, tre.id_tournoi_equipe asc";
			}
			else
			{
				$sql="select
				sum(tre.score) as score, count(trm.date_rencontre_effective) as nombre_matches, tre.id_tournoi_equipe as equipe
				from tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_rencontre_match trm
				where te.nom_d_equipe!='Equipe quartier libre' and tre.id_tournoi_match=trm.id
				and tre.id_tournoi_equipe=te.id and te.id_tournoi=$tournoi_id
				group by tre.id_tournoi_equipe
				order by 1 desc, nombre_matches asc, LENGTH(te.nom_d_equipe), te.nom_d_equipe asc";
			}

			$this -> faire_liste_equipe($sql,$complet_o_n,$tournoi_id,'o' );
		}
		if ($nombretournois >1)
		{
			if ($complet_o_n==false)
			{
				$sql="select
				sum(tre.score) as score, count(trm.date_rencontre_effective) as nombre_matches, tre.id_tournoi_equipe as equipe
				from tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_rencontre_match trm
				where te.nom_d_equipe!='Equipe quartier libre' and tre.id_tournoi_match=trm.id and trm.date_rencontre_effective is not null
				and tre.id_tournoi_equipe=te.id and te.id_tournoi in $idtournoisin
				group by tre.id_tournoi_equipe
				order by 1 desc, nombre_matches asc, tre.id_tournoi_equipe asc";
			}
			else
			{
				$sql="select
				sum(tre.score) as score, count(trm.date_rencontre_effective) as nombre_matches, tre.id_tournoi_equipe as equipe
				from tournoi_rencontre_equipe tre, tournoi_equipe te, tournoi_rencontre_match trm
				where te.nom_d_equipe!='Equipe quartier libre' and tre.id_tournoi_match=trm.id
				and tre.id_tournoi_equipe=te.id and te.id_tournoi in $idtournoisin
				group by tre.id_tournoi_equipe
				order by 1 desc, nombre_matches asc, LENGTH(te.nom_d_equipe), te.nom_d_equipe asc";
			}
		}
		$this -> faire_liste_equipe($sql,$complet_o_n,$idtournoisin,'n' );
	}
	function faire_liste_equipe($sql,$complet_o_n,$tournoi_id, $un_seul_tournoi_o_n='o' )
	{
			global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");
		$individu_node=newNode("individu.individu",true);
			$enreg=array();
			$user = getUser();
			$userid = $user["id"];
			$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$tableau = array ();
			$db = & atkGetDb();
			$data = array ();
		$stuff=$db->getrows($sql);

		$row = array ();
		//		$row[]="<b>#";
		if ($complet_o_n==false)
		{
			$row[]="<b>Classement";
		}
		else
		{$row[]="<b>#";
		}
		$row[] = "<b>Equipe";
		$row[] = "<b>Joueurs";

		$row[] = "<b>Index joueur";
		$row[] = "<b>Index moyen<br/>(Coups rendus)";

		$row[] = "<b>Score";
		$row[] = "<b>Matchs";
		$row[] = "<b>Lieu";
		//		$row[] = "<b>Remarques";
		if ($complet_o_n)
		{
			$row[] = "<b>Courriel";
			$row[] = "<b>Téléphone fixe";
			$row[] = "<b>Téléphone mobile";
		}
		$titre=array();
		$titre= $row;
		//GG
		$tableau[]=$titre;
		//GGF
		$row=array();
		$data=array();

		for ($i = 0; $i < count($stuff); $i++) {
			$id_equipe=$stuff[$i]["equipe"];
			$score=$stuff[$i]["score"];
			$nombre_matches=$stuff[$i]["nombre_matches"];

			$sql="select
			t.libelle,
			te.id,
			te.nom_d_equipe,
			i.id,
			i.nom,
			i.prenom,
			i.courriel,
			i.telephone_fixe,
			i.telephone_mobile,
			i.golf_index
			from
			individu i,
			individu_tournoi it,
			tournoi_equipe_participant tep,
			tournoi_equipe te,
			organisme_tournoi t
			where
			te.id=$id_equipe
			and te.id=tep.id_tournoi_equipe
			and tep.id_individu_tournoi=it.id
			and it.id_individu=i.id and t.id=te.id_tournoi
			order by te.numero_d_equipe, i.nom, i.prenom  ";
			$equipe_rows=$db->getrows($sql);

			$row_numero="";
			$row_nom_equipe="";
			$row_joueurs="";
			$row_courriel="";
			$row_telephone_fixe="" ;
			$row_telephone_mobile="" ;
			$row_golf_index="";
			$row_total_index="";
			$row_total_index_arrondi="";
			$row_score="";
			$row_nombre_matches="";
			for ($j = 0; $j < count($equipe_rows); $j++)
			{
				$row = array ();
				//$tableaumatches=$this->matches_equipe($id_equipe,true);
				( $j==0) ? $row_numero="<b>".($i+1) :null;
				( $equipe_rows[$j-1]["nom_d_equipe"]==$equipe_rows[$j]["nom_d_equipe"]) ?null :$row_nom_equipe="<b>". $equipe_rows[$j]["nom_d_equipe"]."<br/>".$equipe_rows[$j]["libelle"]."</b>";

				$enreg["id"]=$equipe_rows[$j]["id"];
				$photo=$individu_node->portrait_display($enreg, $mode);
				$photo=str_replace("<center>","",$photo);
				$photo=str_replace("</center>","",$photo);
				$photo=str_replace("100px","32px",$photo);
				//GG en attendant mieux
				$photo="";
				//GG
				$row_joueurs .="<b>".$photo.$equipe_rows[$j]["nom"]." ".$equipe_rows[$j]["prenom"]."</b></br>";
				$row_courriel .= $equipe_rows[$j]["courriel"]."</br>";
				$row_telephone_fixe .= $equipe_rows[$j]["telephone_fixe"]."</br>";
				$row_telephone_mobile .= $equipe_rows[$j]["telephone_mobile"]."</br>";


				$row_golf_index .= str_replace('.', ',',$equipe_rows[$j]["golf_index"])."</br>";
				//	$row_total_index+=$equipe_rows[$j]["golf_index"];
				($equipe_rows[$j]["golf_index"]>=36) ? $row_total_index+=36 : $row_total_index+=$equipe_rows[$j]["golf_index"];
				//			$row_total_index=str_replace('.', ',',$row_total_index);
				$row_score ="<b>". $score."</b>";
				$row_nombre_matches="<b>". $nombre_matches."</b>";
				//$row[]=$score;
			}
			//GG
			//		if ($complet_o_n==false)

				$row[]=$row_numero;
			$row[]=$row_nom_equipe;
			$row[]=$row_joueurs;

			$row[]=$row_golf_index;
			$row_total_index=$row_total_index/2;
			//$row_total_index_arrondi=ceil($row_total_index);
			$row[]=str_replace('.', ',',$row_total_index);
				
			//		$row[]=$row_total_index;
			$row[]=$row_score;
			$row[]=$row_nombre_matches;
			$row[] = " ";
			//			$row[] = "Pour voir/cacher les matchs : <br />Cliquer sur la ligne";
			if ($complet_o_n)
			{
				$row[]=$row_courriel;
				$row[]=$row_telephone_fixe ;
				$row[]=$row_telephone_mobile ;
			}
			$tableaumatches=$this->matches_equipe($id_equipe,true);

			$tableau[]=array(
					'type' => 'group',
					'id'  => 'Classement'.($i+1),
					'collapsed' => true,
					'header' => $row,
					'rows' => $tableaumatches);
			//GGF
		//	'id'  => 'Equipes'.$stuff[$i]["numero_de_rencontre"],
			//
		}
			
		/*GG	$tableau[]=array(
		 'type' => 'group',
				'id'  => 'Equipes15055',
			 'collapsed' => false,
			 'header' => $titre,
			 'rows' => $data);
		*/
			
		$haut=array();
		$row=array();
		if ($complet_o_n==false)
		{
			$haut[]=$this->ligne_de_haut_de_tableau($tournoi_id, "Classement");
		}
		else
		{$haut[]=$this->ligne_de_haut_de_tableau($tournoi_id, "Equipes");
		}
		$res=$tbl->render($haut,null,"hautlistegg");
		$res .= $tbl->render($tableau,  TBL_ALTERNATE, "recordlistgg");
		$pied=array();
		$row=array();
		$row[]=$this->ligne_de_bas_de_tableau($tournoi_id);
		$pied[]=$row;
		$res.=$tbl->render($pied,null,"baslistegg");
		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("recordlist.css"));
		$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
		$page->addContent($res);
		if ($g_uploads_organismes_o_n=='1')
		{
			if ($complet_o_n==false)
			{
				$filename=$this->get_upload_dir($tournoi_id)."organisme_tournoi_".$tournoi_id.'_equipes.html' ;
			}
			else
			{$filename=$this->get_upload_dir($tournoi_id)."organisme_tournoi_".$tournoi_id.'_equipes_et_adresses.html' ;
			}
			$file =@fopen($filename,"w");
			$filecontent =($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
			@fwrite($file,$filecontent,strlen($filecontent));
			@fclose($file);

		}
		unset ($individu_node);
		$page->addContent("<br/>Fichier html mis à disposition : <b>$filename</b> </br>");
		$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		//		echo "<br/>Fichier html mis à disposition : <b>$filename</b> </br>";

	}

	function action_lister_les_rencontres() {

		$tableau_selection=$this->get_row_selection_information(false);
		$idtournois=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");

		foreach ($idtournois as $tournoi_id)
		{
				

			$tableau = array ();
			$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$db = & atkGetDb();
			$sql="select
			tr.numero_de_rencontre,
			tr.date_rencontre,
			tr.date_rattrapage_rencontre,
			tr.date_limite_rencontre,
			trm.numero_de_match,
			te.nom_d_equipe,
			te.id,
			tre.score,
			trm.date_rencontre_effective,
			i.nom,
			i.prenom,
			i.golf_index,
			te.jour_rattrapage_o_n
			from
			individu i,
		 individu_tournoi it,
		 tournoi_equipe_participant tep,
		 tournoi_equipe te,
		 tournoi_rencontre tr,
		 tournoi_rencontre_match trm,
		 tournoi_rencontre_equipe tre
		 where
		 tr.id_tournoi=$tournoi_id
		 and tr.id=trm.id_tournoi_rencontre
		 and trm.id=tre.id_tournoi_match
		 and tre.id_tournoi_equipe=te.id
		 and te.id=tep.id_tournoi_equipe
		 and tep.id_individu_tournoi=it.id
		 and it.id_individu=i.id
		 order by tr.id, trm.id, tre.id ,i.nom, i.prenom  ";
			$tableau = array ();
			$stuff=$db->getrows($sql);

			$colorfin="</font>";
			$colordebut='<font color="Red">';
			$i1=0;
			for ($i = 0, $_i = count($stuff); $i < $_i; $i++) {
				$row = array();
				if ($stuff[$i]["numero_de_rencontre"]!=$stuff[$i-1]["numero_de_rencontre"] )
				{
					$row = array ();
					$row[]="<b>#";
					$row[] = "<b>Rencontre ".$stuff[$i]["numero_de_rencontre"]."</br>du</br>".$stuff[$i]["date_rencontre"];
					$row[] = "<b>Date";
					$row[] = "<b>Rattrapage";
					$row[] = "<b>Limite";
					$row[] = "<b>Match";
					$row[] = "<b>Equipe";
					$row[] = "<b>Joueurs";
					$row[] = "<b>Index";
					$row[] = "<b>Date </br>de match</b>";
					$row[] = "<b>Score</b>";
					$titre=array();
					$titre= $row;
					$row=array();
					$data=array();
					$i1=0;
				}
				$row[] = ++$i1;
				($stuff[$i]["numero_de_rencontre"]==$stuff[$i-1]["numero_de_rencontre"]) ? $row[]="" : $row[] = '<b>'.$stuff[$i]["numero_de_rencontre"];
				($stuff[$i]["numero_de_rencontre"]==$stuff[$i-1]["numero_de_rencontre"]) ? $row[]="" : $row[] = '<b>'.str_replace(" 00:00:00", "", $stuff[$i]["date_rencontre"]);
				($stuff[$i]["numero_de_rencontre"]==$stuff[$i-1]["numero_de_rencontre"]) ? $row[]="" : $row[] = '<b>'.str_replace(" 00:00:00", "", $stuff[$i]["date_rattrapage_rencontre"]);
				($stuff[$i]["numero_de_rencontre"]==$stuff[$i-1]["numero_de_rencontre"]) ? $row[]="" : $row[] = '<b>'.str_replace(" 00:00:00", "", $stuff[$i]["date_limite_rencontre"]);
				(
				($stuff[$i+2]["numero_de_match"]!=$stuff[$i]["numero_de_match"])
				&&
				($stuff[$i-1]["numero_de_match"]!=$stuff[$i]["numero_de_match"])
				)
				?	$jour_repos=true		: $jour_repos=false	;
				($stuff[$i]["numero_de_match"]==$stuff[$i-1]["numero_de_match"]) ? $row[]="" : $row[] ='<b>'.$stuff[$i]["numero_de_match"];
				if ($stuff[$i]["nom_d_equipe"]==$stuff[$i-1]["nom_d_equipe"])
				{
					$row[]="";
				}
				else
				{
					if ($jour_repos==true)
					{
						$row[] = '<b><font color="Red">'.$stuff[$i]["nom_d_equipe"].'<br /br> au repos</font><b>';
					}
					else {
						$row[] = $stuff[$i]["nom_d_equipe"];
					}
				}
				$row[] =$stuff[$i]["nom"]." ".$stuff[$i]["prenom"];
				//			($stuff[$i]["score"]==0) ?  $row[] ="" : $row[] = $stuff[$i]["score"];
				$row[] = str_replace('.', ',',$stuff[$i]["golf_index"]);
				(
				(
						($stuff[$i+2]["jour_rattrapage_o_n"]>0 && $stuff[$i+2]["numero_de_match"]==$stuff[$i]["numero_de_match"])
						|| $stuff[$i]["jour_rattrapage_o_n"]>0
				)
				||
				(
						($stuff[$i-2]["jour_rattrapage_o_n"]>0 && $stuff[$i-2]["numero_de_match"]==$stuff[$i]["numero_de_match"])
						|| $stuff[$i]["jour_rattrapage_o_n"]>0
				)
				)
				? $row[]="<b>".str_replace(" 00:00:00", "", $stuff[$i]["date_rattrapage_rencontre"]) ."</b>"
						: $row[] = str_replace(" 00:00:00", "", $stuff[$i]["date_rencontre"]) ;
				if ($stuff[$i]["date_rencontre_effective"]=="") $stuff[$i]["score"]="";
				($stuff[$i]["nom_d_equipe"]==$stuff[$i-1]["nom_d_equipe"]) ? $row[]="" : $row[] = '<b>'.$stuff[$i]["score"].'</b>';
				$data[] = $row;
				if ($stuff[$i]["numero_de_rencontre"]!=$stuff[$i+1]["numero_de_rencontre"])
				{
					$tableau[]=array(
							'type' => 'group',
							'id'  => 'Equipes'.$stuff[$i]["numero_de_rencontre"],
							'collapsed' => true,
							'header' => $titre,
							'rows' => $data);
					//		 $this->p($tableau);
				}
			}
			$haut=array();
			$row=array();
			$haut[]=$this->ligne_de_haut_de_tableau($tournoi_id, "Rencontres");
			$res=$tbl->render($haut,null,"hautlistegg");
			$res.= $tbl->render($tableau, TBL_ALTERNATE, "recordlistgg");
			$pied=array();
			$row=array();
			$row[]=$this->ligne_de_bas_de_tableau($tournoi_id);
			$pied[]=$row;
			$res.=$tbl->render($pied,null,"baslistegg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			if ($g_uploads_organismes_o_n=='1')
			{
				$filename=$this->get_upload_dir($tournoi_id)."organisme_tournoi_".$tournoi_id.'_rencontres.html' ;
				$file =@fopen($filename,"w");
				$filecontent = ($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				@fwrite($file,$filecontent,strlen($filecontent));
				@fclose($file);
			}
			$page->addContent("<br/>Fichier html mis à disposition : <b>$filename</b> </br>");
			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		}
	}
	function get_equipe($id)
	{
		$db = & atkGetDb();
		$sql="select
		te.id,
		te.numero_d_equipe,
		te.nom_d_equipe,
		te.jour_rattrapage_o_n,
		i.nom,
		i.prenom,
		i.courriel,
		i.telephone_fixe,
		i.telephone_mobile,
		i.golf_index
		from
		tournoi_equipe te
		LEFT JOIN tournoi_equipe_participant tep
		ON te.id=tep.id_tournoi_equipe
		LEFT JOIN individu_tournoi it
		ON tep.id_individu_tournoi=it.id
		LEFT JOIN 	individu i
		ON it.id_individu=i.id
		where
		te.id=$id
		order by te.numero_d_equipe, i.nom, i.prenom  ";
		//		$this->p($sql);
		$equipe=$db->getrows($sql);
		return $equipe;


	}
	function get_match($id)
	{
		$db = & atkGetDb();
		$sql="select
		trm.id_lieu_match,
		trm.numero_de_match,
		tr.numero_de_rencontre,
		tr.date_rencontre,
		tr.date_rattrapage_rencontre,
		tr.date_limite_rencontre
		from
		tournoi_rencontre_match trm,
		tournoi_rencontre tr
		where
		trm.id=$id
		and trm.id_tournoi_rencontre=tr.id
		";
		$match=$db->getrows($sql);
		return $match[0];


	}


	function action_lister_les_rencontres_par_equipe() {
		$tableau_selection=$this->get_row_selection_information(false);
		$idtournois=$tableau_selection["node_ids"];
		$userid =$tableau_selection["userid"];
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$g_uploads_organismes_o_n = $g_sessionManager->getValue("uploads_organismes_o_n", "globals");

		foreach ($idtournois as $tournoi_id)
		{
				

			$tableau = array ();
			$tbl = & atknew("atk.utils.atktablerenderergrouped");
			$tbl->setRowClass(1, "superbold");
			$res="";
			$db = & atkGetDb();

			$sql="select
			te.id
			from
			tournoi_equipe te
			where
			te.id_tournoi=$tournoi_id
			order by numero_d_equipe";
			$equipes=$db->getrows($sql);
			$tableau=array();
			$tableautotal=array();
			for ($i = 0; $i < count($equipes); $i++) {
				$matches=array();
				$id_equipe=$equipes[$i]["id"];
				$tableautotal[]=$this->matches_equipe($id_equipe,false);
			}
			$haut=array();
			$row=array();
			$haut[]=$this->ligne_de_haut_de_tableau($tournoi_id, "Matchs par équipe");
			$res=$tbl->render($haut,null,"hautlistegg");
			$res .= $tbl->render($tableautotal, TBL_ALTERNATE, "recordlistgg");
			$pied=array();
			$row=array();
			$row[]=$this->ligne_de_bas_de_tableau($tournoi_id);
			$pied[]=$row;
			$res.=$tbl->render($pied,null,"baslistegg");
			$page = & atknew("atk.ui.atkpage");
			$ui = & atkinstance("atk.ui.atkui");
			$output = & atkOutput :: getInstance();
			$page->register_style($ui->stylePath("recordlist.css"));
			$page->register_script(atkconfig("atkroot")."atk/javascript/tools.js");
			$page->addContent($res);
			if ($g_uploads_organismes_o_n=='1')
			{
				$filename=$this->get_upload_dir($tournoi_id)."organisme_tournoi_".$tournoi_id.'_rencontres_par_equipe.html' ;
				$file =@fopen($filename,"w");
				//	$filecontent = base64_encode($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
				$filecontent = ($page->render(atktext('app_title') . ' - ' . atktext('help'), true));

				@fwrite($file,$filecontent,strlen($filecontent));
				@fclose($file);
					
			}
			$page->addContent("<br/>Fichier html mis à disposition : <b>$filename</b> </br>");
			$output->output($page->render(atktext('app_title') . ' - ' . atktext('help'), true));
		}

	}
	function matches_equipe($id_equipe,$simple_o_n=false){

		$db = & atkGetDb();
		$matches=array();
		$tableau=array();
		$equipe=$this->get_equipe($id_equipe);
		$row=array();
		$row[]="<b>#";
		if ($equipe[0]["nom_d_equipe"]=="Equipe quartier libre")
		{
			$row[] = "<b>Repos";
		}
		else
		{
			$row[] = "<b>Equipe ".$equipe[0]["numero_d_equipe"]."<br />".$equipe[0]["nom"]." ".$equipe[0]["prenom"]."<br />".$equipe[1]["nom"]." ".$equipe[1]["prenom"];
		}
		$row[] = "<b>Joueurs";
		$row[] = "<b>Index";
		($simple_o_n==false) ? $row[] = "<b>Index moyen" : $row[] = "<b>Index moyen<br/>(Coups rendus)";

		$row[] = "<b>Rencontre";
		$row[] = "<b>Date";
		$row[] = "<b>Match";
		$row[] = "<b>Equipe";
		$row[] = "<b>Joueurs";
		$row[] = "<b>Index";
		$row[] = "<b>Index moyen<br />Coups rendus";
		$row[] = "<b>Score</b>";
		$row[] = "<b>Date <br />de match</b>";
		$row[] = "<b>Lieu";
		$row[] = "<b>Remarque</b>";
		$titre=array();
		$titre= $row;
		$row=array();
		$tableau=array();
		$totalindex=0;
		$rattrapage_equipe1=false;
		for ($iequipe = 0; $iequipe < count($equipe); $iequipe++)
		{
			$row=array();
			$row[]="";
			if 	($equipe[$iequipe]["nom_d_equipe"]==$equipe[$iequipe-1]["nom_d_equipe"])
			{
				$row[]= "" ;
			}
			else {
				if ($equipe[$iequipe]["nom_d_equipe"]=="Equipe quartier libre")
				{
					$row[]='<b><font color="Red">Journée de repos';
				}
				else {
					$row[]='<b>'.$equipe[$iequipe]["nom_d_equipe"];
				}
			}

			$row[]="<b>".$equipe[$iequipe]["nom"]." ".$equipe[$iequipe]["prenom"];
			$row[]="<b>".str_replace('.', ',',$equipe[$iequipe]["golf_index"]);
			($equipe[$iequipe]["golf_index"]>=36) ? $totalindex+=36 : $totalindex+=$equipe[$iequipe]["golf_index"];

			//			($iequipe== count($equipe)-1) ? $row[]="<b>".str_replace('.', ',',$totalindex) : $row[]="";
			if ($iequipe== count($equipe)-1)
			{
				$index_moyen_summary=$totalindex/2;
				$index_equipe_summary=str_replace('.', ',',$index_moyen_summary);
				$row[]="<b>".$index_equipe_summary;
			}
			else
			{
				$row[]="";
			}

			if ($equipe[$iequipe]["jour_rattrapage_o_n"]==1)
			{
				$rattrapage_equipe1=true;
			}
			$tableau[]=$row;
		}
		$sql="select
		tre.id_tournoi_match
		from
		tournoi_rencontre_equipe tre,
		tournoi_rencontre_match trm,
		tournoi_rencontre tr
		where
		tre.id_tournoi_equipe=$id_equipe
		and trm.id=tre.id_tournoi_match
		and tr.id=trm.id_tournoi_rencontre

		order by tr.date_rencontre
		";
		$matches=$db->getrows($sql);
		$numseq=0;
		for ($j = 0; $j < count($matches); $j++) {
			$id_match=$matches[$j]["id_tournoi_match"];
			// traiter le match (lieu,date_rencontre)
			$row=array();
			$row[]=++$numseq;
			$row[]="";
			$row[]="";
			$row[]="";
			$row[]="";
			$match=$this->get_match($id_match);
			$row[]='<b>'.$match["numero_de_rencontre"];

			$row[]='<b>'.str_replace(" 00:00:00", "", $match["date_rencontre"]);
			$row[]='<b>'.$match["numero_de_match"];
			$tableau[]=$row;
			$sql="select
			tre.id_tournoi_equipe,
			tre.score, tre.remarque,
			trm.date_rencontre_effective, trm.id_lieu_match
			from
			tournoi_rencontre_equipe tre,
			tournoi_rencontre_match trm
			where
			tre.id_tournoi_equipe!=$id_equipe
			and tre.id_tournoi_match=trm.id
			and trm.id=$id_match
			";
			$scores=$db->getrows($sql);
			$date_rencontre_effective=$scores[0]["date_rencontre_effective"];
			$id_lieu_match=$scores[0]["id_lieu_match"];
			$remarque=$scores[0]["remarque"];
			$id_equipe2=$scores[0]["id_tournoi_equipe"];
			$sql="select
			tre.score				from
			tournoi_rencontre_equipe tre
			where
			tre.id_tournoi_equipe=$id_equipe
			and tre.id_tournoi_match=$id_match
			";
			$scores=$db->getrows($sql);
			$score=$scores[0]["score"];
			//
			$equipe2=$this->get_equipe($id_equipe2);
			$totalindex=0;
			$rattrapage_equipe2=false;
			$row_nom_equipe="";
			$row_joueurs="";
			$row_index="";
			$row_totalindex="";
			$row_score="";
			$row_date_r="";
			$row_lieu="";
			$row_remarque="";
			for ($iequipe = 0; $iequipe < count($equipe2); $iequipe++)
			{
				$row=array();
				if ($simple_o_n==false)
				{
					$row[]="";
					$row[]="";
					//			$row[]="";
					$row[]="";
					$row[]="";
					$row[]="";
					$row[]="";
					$row[]="";
				}
				$row[]="";
				if 	($equipe2[$iequipe]["nom_d_equipe"]==$equipe2[$iequipe-1]["nom_d_equipe"])
				{
					$row[]= "" ;
				}
				else {
					if ($equipe2[$iequipe]["nom_d_equipe"]=="Equipe quartier libre")
					{
						$repos_o_n=true;
						$row[]='<b><font color="Red">Repos';
						$row_nom_equipe='<b><font color="Red">Repos';
					}
					else {
						$repos_o_n=false;
						$row[]='<b>'.$equipe2[$iequipe]["nom_d_equipe"];
						$row_nom_equipe='<b>'.$equipe2[$iequipe]["nom_d_equipe"];
					}
				}
				$row_joueurs.=$equipe2[$iequipe]["nom"]." ".$equipe2[$iequipe]["prenom"]."<br />";
				$row[]=$equipe2[$iequipe]["nom"]." ".$equipe2[$iequipe]["prenom"];
				$row_index.=str_replace('.', ',',$equipe2[$iequipe]["golf_index"])."<br />";
				$row[]=str_replace('.', ',',$equipe2[$iequipe]["golf_index"]);
				//				$totalindex+=$equipe2[$iequipe]["golf_index"];
				($equipe2[$iequipe]["golf_index"]>=36) ? $totalindex+=36 : $totalindex+=$equipe2[$iequipe]["golf_index"];

				if ($iequipe== count($equipe2)-1)
				{
					$index_moyen=$totalindex/2;
					//				$coups_rendus=($index_moyen_summary-$index_moyen)*3/4;
					$coups_rendus=($index_moyen_summary-$index_moyen)*1;
					($coups_rendus<0) ? $coups_rendus=floor($coups_rendus) : $coups_rendus=ceil($coups_rendus) ;
					$index_equipe=str_replace('.', ',',$index_moyen)." / ".$coups_rendus;
					$row[]="<b>".$index_equipe;
				}
				else
				{
					$row[]="";
				}
					

				if ($repos_o_n==true){
					$row_totalindex="";
				}
				if 	($date_rencontre_effective=="")
				{
					$score="";
				}
				($equipe2[$iequipe]["nom_d_equipe"]==$equipe2[$iequipe-1]["nom_d_equipe"]) ? $row[]="" : $row[] = '<b>'.$score.'</b>';
				$row_score='<b>'.$score.'</b>';
				if ($equipe2[$iequipe]["jour_rattrapage_o_n"]==1)
				{
					$rattrapage_equipe2=true;
				}
				if ($date_rencontre_effective=="")
				{
					if ( ($rattrapage_equipe2==true ||  $rattrapage_equipe1==true)  )
					{
						$date_r="<b>".str_replace(" 00:00:00", "", $match["date_rattrapage_rencontre"]);
					}
					else
					{
						$date_r=str_replace(" 00:00:00", "", $match["date_rencontre"]);
					}
				}
				else {
					$date_r=str_replace(" 00:00:00", "", $date_rencontre_effective);
				}
				($equipe2[$iequipe]["nom_d_equipe"]==$equipe2[$iequipe-1]["nom_d_equipe"]) ? $row[]="" : $row[] =$date_r;
				$row_date_r=$date_r;
				if ($repos_o_n==true)
				{
					$row_date_r='<b><font color="Red">'.$date_r;
					$row[]="";
					$row_lieu="";
				}
				else {
					($equipe2[$iequipe]["nom_d_equipe"]==$equipe2[$iequipe-1]["nom_d_equipe"]) ? $row[]="" : $row[] =$this->descripteur_golf_parcours($id_lieu_match,'o');
					$row_lieu=$this->descripteur_golf_parcours($id_lieu_match,'o');
				}
				($equipe2[$iequipe]["nom_d_equipe"]==$equipe2[$iequipe-1]["nom_d_equipe"]) ? $row[]="" : $row[] = '<b>'.$remarque.'</b>';
				$row_remarque='<b>'.$remarque.'</b>';
				$tableau[]=$row;

			}
			if ($simple_o_n==true)
			{
				$row=array();
				$row[]="";
				$row[]=$row_nom_equipe;
				$row[]=$row_joueurs;
				$row[]=$row_index;
				//				$row_totalindex="<b>".str_replace('.', ',',$totalindex/2);
				$index_moyen=$totalindex/2;
				//			$coups_rendus=($index_moyen_summary-$index_moyen)*3/4;
				$coups_rendus=($index_moyen_summary-$index_moyen)*1;
				($coups_rendus<0) ? $coups_rendus=floor($coups_rendus) : $coups_rendus=ceil($coups_rendus) ;
				$row[]=str_replace('.', ',',$index_moyen)." / ".$coups_rendus;

				//			$row[]=$row_totalindex." / ".ceil($totalindex/2);

				$row[]=$row_score;
				$row[]=$row_date_r;
				$row[]=$row_lieu;
				$row[]=$row_remarque;
				$tableausimple[]=$row;
			}

		}
		if ($simple_o_n==true)
		{
			$ta=$tableausimple;
		}
		else
		{$ta=array(
				'type' => 'group',
				'id'  => 'Equipes'.$id_equipe,
				'collapsed' => true,
				'header' => $titre,
				'rows' => $tableau);
		}
		return $ta;

	}

	function ligne_de_bas_de_tableau($id_tournoi)
	{
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$db = & atkGetDb();
		$sql="select
		t.libelle,
		o.nom
		from
		organisme_tournoi t,
		organisme o
		where
		t.id='$id_tournoi' and t.id_organisme=o.id
		";
		//			$this->p($sql);
		$row=$db->getrows($sql);

		$data ="NB : Un clic sur un en-tête jaune permet de révéler/cacher les détails. </br>Liste imprimée par " . $g_nomutilisateur.", valable au " . gmdate(c) ;
		return $data;
	}
	function ligne_de_haut_de_tableau($id_tournoi,$sujet)
	{
		global $g_sessionManager;
		global $g_nomutilisateur;
		$g_nomutilisateur = $g_sessionManager->getValue("atgNomUtilisateur", "globals");
		$db = & atkGetDb();
		if (substr($id_tournoi, 0,1)=="(")
		{
			$sql="select
			t.libelle,
			o.nom,
			o.logo
			from
			organisme_tournoi t,
			organisme o
			where
			t.id in $id_tournoi and t.id_organisme=o.id
			";
		}
			else
		{$sql="select
		t.libelle,
		o.nom,
		o.logo
		from
		organisme_tournoi t,
		organisme o
		where
		t.id='$id_tournoi' and t.id_organisme=o.id
		";
		}
		$row=$db->getrows($sql);
		$nom=$row[0]["nom"];
		$libelle='';
		foreach ($row as $rang)
		{
			$libelle.=$rang["libelle"]." <br/>";
		}
		$ligne=array();
		$ligne[]='<img  border="0" src="./logos/'.$row[0]["logo"].'" alt="Logo" title="Logo" ></img>';
		$ligne[]="<b>".$nom."</br>".$libelle."</br></br>$sujet";
		return $ligne;
	}

	function action_bloquer_la_generation_des_rencontres() {
		$retour=$this->get_row_selection_information(true);
		if ($retour==false)
		{
			echo "un seul tournoi svp ?";
			die ();
		}
		$db = & atkGetDb();
		$id=$retour["node_id"];
		$sql="update organisme_tournoi set blocage_generation_o_n='1' where id=$id ";
		$db->query($sql);
		$this->redirect();


	}
	function action_debloquer_la_generation_des_rencontres() {
		$retour=$this->get_row_selection_information(true);
		if ($retour==false)
		{
			echo "un seul tournoi svp ?";
			die ();
		}
		$db = & atkGetDb();
		$id=$retour["node_id"];
		$sql="update organisme_tournoi set blocage_generation_o_n='0' where id=$id ";
		$db->query($sql);
		$this->redirect();



	}

	function action_generer_equipes_et_rencontres() {

		$user = getUser();
		$userid = $user["id"];
		$db = & atkGetDb();
		$select_tournoi =$this->m_postvars["atkselector"];
		$array_id = explode('=', $select_tournoi);
		$tournoi_id = stripQuotes($array_id[1]) ;
		$requete = "select blocage_generation_o_n
		FROM organisme_tournoi 	 where
		id=$tournoi_id ";
		$row=$db->getrows($requete);
		if ($ros[0]["blocage_generation_o_n"]==1)
		{
			echo "Le tournoi est clos (blocage des générations des rencontres)";
			$this->redirect();
		}

		$requete = "delete
		FROM tournoi_equipe 	 where
		id_tournoi=$tournoi_id ";
		$db->query($requete);
		$requete = "delete
		FROM tournoi_rencontre 	 where
		id_tournoi=$tournoi_id ";
		$db->query($requete);
		$requete = "SELECT
		nombre_d_equipes,
		nombre_de_participants_individuels,
		nombre_par_equipe,
		id_lieu_rencontre,
		type_de_championnat ,
		formule_de_jeu
		FROM organisme_tournoi ot ,
		type_tournoi tt
		where
		ot.id=$tournoi_id and ot.id_type_tournoi=tt.id ";
		$data = $db->getrows($requete);
		$nombre_de_participants_individuels=$data[0]["nombre_de_participants_individuels"];
		$nombre_d_equipes=$data[0]["nombre_d_equipes"];
		$nombre_par_equipe=$data[0]["nombre_par_equipe"];

		$type_de_championnat=$data[0]["type_de_championnat"];
		$formule_de_jeu=$data[0]["formule_de_jeu"];
		$id_lieu_rencontre=$data[0]["id_lieu_rencontre"];
		$nombre_participants_inscrits=0;
		$nombre_equipes_inscrites=0;

		//		Déterminer le nombre d'équipes
		$requete = "SELECT	count(id) as nombre from individu_tournoi
		where 	id_tournoi=$tournoi_id	  ";
		$data = $db->getrows($requete);
		$nombre_participants_inscrits=$data[0]["nombre"];
		if (!empty($nombre_d_equipes))
		{
			$nombre_participants_inscrits=$nombre_d_equipes*$nombre_par_equipe;
		}
		if (!empty($nombre_de_participants_individuels))
		{
			$nombre_participants_inscrits=$nombre_de_participants_individuels;
		}
		$nombre_equipes_inscrites=$nombre_participants_inscrits/$nombre_par_equipe;
		/*		if($nombre_equipes_inscrites % 2)
		 {
		++$nombre_equipes_inscrites;
		}
		*/
		$teams = array ();
		for($i = 1; $i <= $nombre_equipes_inscrites; $i++) {
			$teams[]=$i;
		}
		// $this->p($teams);
		$roundrobin = new roundrobin($teams);
		$roundrobin->create_matches();
		if ($roundrobin->finished) {
			$matchdays=array();
			$matchdays=$roundrobin->print_matches();
			//$this->p($matches);
		}
		$nombre=count($matchdays);

		for ($i = 0; $i < $nombre; $i++) {
			$matchday=array();
			$matchday=$matchdays[$i];
			$nombre1=count($matchday);
			//		echo ' Créer rencontre ' .$i.'<br /br>';
			// Créer tournoi_rencontre si n'existe pas
			$numero_rencontre=$i+1;
			$nextid=$db->nextid('seq_tournoi_rencontre');
			$requete = "INSERT INTO tournoi_rencontre
					(  id,id_tournoi,numero_de_rencontre,date_rencontre, id_lieu_rencontre,
					commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
					VALUES
					( $nextid,$tournoi_id , $numero_rencontre ,null,$id_lieu_rencontre,
					'',$userid, UTC_TIMESTAMP(), $userid, UTC_TIMESTAMP())
					ON DUPLICATE KEY UPDATE id_modification=id_modification ";
			$db->query($requete);
			$requete = "select id from tournoi_rencontre
			where id_tournoi='$tournoi_id' and numero_de_rencontre=$numero_rencontre";
			$data=$db->getRows($requete);
			$rencontre_id=$data[0]["id"];
			echo "Rencontre : ".($i+1)."</br>";


			for ($j = 0; $j < $nombre1; $j++) {
				$match=array();
				$match=$matchday[$j];
				$nombre2=count($match);
				// Créer match
				//				$numero_match=($i+1)."_".($j+1);
				$numero_match=$j+1;

				$nextid=$db->nextid('seq_tournoi_rencontre_match');


				$requete = "INSERT INTO tournoi_rencontre_match
						(  id,
						id_tournoi_rencontre,
						numero_de_match,
						id_lieu_match,
						commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
						VALUES
						( $nextid,
						'$rencontre_id',
					 '$numero_match' ,
					 '$id_lieu_rencontre',
					 '','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
					 ON DUPLICATE KEY UPDATE id_modification=id_modification  ";
				$db->query($requete);
				$requete = "select id from tournoi_rencontre_match
			 where id_tournoi_rencontre='$rencontre_id' and numero_de_match='$numero_match'";
				$data=$db->getRows($requete);
				$match_id=$data[0]["id"];
				echo "Match : ".($j+1)."</br>";



				for ($k = 0; $k < $nombre2; $k++) {
					//			echo ' Créer equipe ' .$k.' '.$match[$k].' <br /br>';
					//			echo ' Créer rencontre-equipe ' .'Rencontre : '.$i.' match : '.$j.' équipe : '.$k.'<br /br>';
					//			echo $match[$k].'<br /br>';
					// $i+1 : tournoi_rencontre.numero_de_rencontre
					// $i+1.'-'.$j+1 : tournoi_rencontre_equipe.numero_de_rencontre_equipes
					// $match[$k] : tournoi_rencontre.numero_d_equipe

					// Créer  tournoi_equipe si n'existe pas : clé unique id_tournoi.numero_d_equipe
					//				$numero_equipe=($i+1)."-".($j+1);
					$numero_equipe=$match[$k];
					$nom_d_equipe="Equipe ".$match[$k];
					$requete="SELECT count(id) as nombre from tournoi_equipe where id_tournoi=$tournoi_id and numero_d_equipe='$numero_equipe'";
					$row=$db->getRows($requete)	;
					if ($row[0]["nombre"]==0	)
					{

						$nextid=$db->nextid('seq_tournoi_equipe');
						$requete = "INSERT INTO tournoi_equipe
								(  id,id_tournoi,numero_d_equipe,nom_d_equipe,
								commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
								VALUES
								( $nextid,'$tournoi_id', '$numero_equipe' ,'$nom_d_equipe',
								'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
								ON DUPLICATE KEY UPDATE id_modification=id_modification ";
						$db->query($requete);

						echo "Equipe : ".$numero_equipe." id ".$nextid."</br>";
					}
					$requete = "select id from tournoi_equipe
					where id_tournoi='$tournoi_id' and numero_d_equipe='$numero_equipe'";
					$data=$db->getRows($requete);
					$equipe_id=$data[0]["id"];
					echo "equipe : ".$numero_equipe." id : ".$equipe_id."</br>";



					$nextid=$db->nextid('seq_tournoi_rencontre_equipe');
					// Créer tournoi_rencontre_equipe
					//							$numero_rencontre_equipe=($i+1)."_".($j+1)."_".($k+1)."_".$match[$k];
					$numero_rencontre_equipe=$match[$k];

					$nextid=$db->nextid('seq_tournoi_rencontre_equipe');


					$requete = "INSERT INTO tournoi_rencontre_equipe
							(  id,
							id_tournoi_match,
							id_tournoi_equipe,
							numero_de_rencontre_equipes,
							commentaire, id_creation, date_creation, id_modification, date_modification)  " . "
							VALUES
							( $nextid,
							'$match_id',
							'$equipe_id',
							'$numero_rencontre_equipe' ,

							'','$userid', UTC_TIMESTAMP(), '$userid', UTC_TIMESTAMP())
							ON DUPLICATE KEY UPDATE id_modification=id_modification  ";
					//					echo $requete;
					//					die();
					$db->query($requete);
					echo "rencontre : ".$numero_rencontre_equipe."</br>";

				}
			}
		}
		$requete = "update tournoi set blocage_generation_o_n='0'
		where 	id_tournoi=$tournoi_id ";

		echo 'Génération terminée. Nouvelle génération désormais impossible sans déblocage manuel.';
		die();

	}
	function get_upload_dir($id_tournoi)
	{
		$db = &atkGetDb();
		if (substr($id_tournoi,0,1)=='(')
		{$sql="select o.id from organisme o, organisme_tournoi ot  where ot.id in $id_tournoi and ot.id_organisme=o.id";}
		else
		{$sql="select o.id from organisme o, organisme_tournoi ot  where ot.id=$id_tournoi and ot.id_organisme=o.id";}
		$data=$db->getrows($sql);
		$uploaddir = atkconfig("uploads_organismes_dir").$data[0]["id"]."/";
		if (!file_exists($uploaddir))
		{
			mkdir($uploaddir);
		}
		return $uploaddir;
	}


	function preAdd(& $record) {
		if (($record["nombre_d_equipes"]>0 && $record["nombre_de_participants_individuels"]>0)
		) {
			triggerError($record, "", "Seul un des deux champs nombre d'équipes, nombres de participants individuels doit être positif ");
		}
		parent :: preAdd($record);
	}
	function preUpdate(& $record) {
		if (($record["nombre_d_equipes"]>0 && $record["nombre_de_participants_individuels"]>0)
		) {
			triggerError($record, "", "Seul un des deux champs nombre d'équipes, nombres de participants individuels doit être positif ");
		}
		parent :: preUpdate($record);
	}
	function initial_values() {
		return array (
				"nombre_d_equipes" => null,
				"nombre_de_participants_individuels" => null,
		);
	}


}

?>