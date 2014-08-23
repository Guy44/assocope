<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_rencontre extends assMetaNode {
	var $table = "type_rencontre";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function type_rencontre()
	{
		$this->atkMetaNode();
		$this->atkNode("type_rencontre", NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA| NF_COMPACT);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array ("id",
						"libelle",
						"routine_o_n",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Organismes" => array (
						"organisme"
				)
		), AF_NO_LABEL));

		$this->add(new atkOneToManyRelation("organisme", "organisme.rencontre", "id_type_rencontre", AF_HIDE_LIST));
		$this->add(new atkAttribute("id",AF_COMPACT),null,4);
		$this->add(new atkAttribute("libelle",AF_FORCE_LOAD),null,10);
		$this->add(new atkBoolAttribute("routine_o_n"),null,11);
		$this->add(new atkDummyAttribute("stats_rencontres", "Statistiques", AF_DUMMY_SHOW_LABEL|AF_COMPACT), NULL, 5);
		$this->add(new atkDummyAttribute("stats_rencontres_graphique", "Graphique"), NULL, 6);

		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,7);
		//		$this->setIndex("libelle");
		$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}
	function initial_values() {
		$init_vals = array ();
		$init_vals["routine_o_n"] = 0;

		return $init_vals;
	}
	function id_display ($record, $mode) {
		$id_type=$record["id"];
		$retour=$this->descripteur_type_rencontre($id_type,'o');
		$id_organisme=$this->m_postvars["id_organisme"];
		// récupérer id_organisme
		if ($id_organisme>0)
		{
			$retour.="<br />".$this->descripteur_organisme($id_organisme,'n','o','50');
			// récupérer nombre
			$db = & atkGetDb();
			$sql="SELECT count(id) as nombre  from organisme_rencontre
			where  id_organisme=$id_organisme
			and id_type_rencontre = $id_type";
			$data = $db->getrows($sql);

			if ($data[0]["nombre"] > 0) {
				$retour.="<br/>Nombre : <b>". href(dispatch_url("organisme.rencontre", "admin", array (
						'atkfilter' => "organisme_rencontre.id_organisme=" . $id_organisme . " and organisme_rencontre.id_type_rencontre=" . $id_type . ""
				), "dispatch.php"), $data[0]["nombre"], SESSION_NESTED)."</b>";
			} else {
				$retour.="";
			}
		}

		return $retour;
	}
	function get_titre_graphique($record)
	{
		$id_organisme=$this->m_postvars["id_organisme"];
		$id_type_rencontre=$record["id"];
		$db = & atkGetDb();
		if ($id_organisme>0)
		{
			$data = $db->getrows(" select nom from organisme where id=$id_organisme");
			$retour= $data[0]["nom"];
		}
		$data = $db->getrows(" select libelle from type_rencontre where id=$id_type_rencontre");
		$retour.= " - ".$data[0]["libelle"];

		return $retour;
	}

	function stats_rencontres_display(&$record, $mode)
	{
		$titre=$this->get_titre_graphique($record);
		$id_type_rencontre=$record["id"];
		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();
		if ($id_organisme>0)
		{
			$sql="SELECT COUNT( id ) AS nombre, YEAR( date_debut ) AS an
			FROM  `organisme_rencontre`
			WHERE id_organisme =$id_organisme
			AND id_type_rencontre =$id_type_rencontre
			GROUP BY YEAR( date_debut )
			ORDER BY YEAR( date_debut ) ";
		}
		else {
			$sql="SELECT COUNT( id ) AS nombre, YEAR( date_debut ) AS an
			FROM  `organisme_rencontre`
			WHERE  id_type_rencontre =$id_type_rencontre
			GROUP BY YEAR( date_debut )
			ORDER BY YEAR( date_debut ) ";
		}
		$data = $db->getrows($sql);

		$res = $titre."<table border='1'>";

		// rencontres
		$res .= "<tr><td class='styletitre'>Année";
		for($i=0; $i<count($data); $i++)
		{			
			$res.='</td><td>'.'<p style="text-align: center; margin-top:0px; margin-bottom:0px">'.$data[$i]["an"].'</p>';
		}
		$res.='</td></tr>';
		$res .= "<tr><td class='styletitre'>".$record['libelle'];
		for($i=0; $i<count($data); $i++)
		{
			if ($id_organisme>0)
			{
				$lien=href(dispatch_url("organisme.rencontre", "admin", array (
						'atkfilter' => " organisme_rencontre.id_organisme =". $id_organisme
						." and organisme_rencontre.id_type_rencontre =". $record['id']
						." and YEAR(organisme_rencontre.date_debut)=".$data[$i]["an"]
				), "dispatch.php"),$this->nombre_format($data[$i]["nombre"],"b") , SESSION_NESTED);
			}
			else
			{
				$lien=href(dispatch_url("organisme.rencontre", "admin", array (
						'atkfilter' => " organisme_rencontre.id_type_rencontre =". $record['id']
						." and YEAR(organisme_rencontre.date_debut)=".$data[$i]["an"]
				), "dispatch.php"), $this->nombre_format($data[$i]["nombre"],"b"), SESSION_NESTED);
			}
			$res.='</td><td>'.$lien;
		}
		$res.='</td></tr>';
		$res.='</td></tr></table>'.$this->getUserStamp('n','o');;

		$record["graphique"]=$this->afficheGraphique($res,$titre);
			
		return $res;
	}


	function stats_rencontres_graphique_display($record, $mode)
	{
		return $record["graphique"];

	}
	/*function adminHeader()
	 {
	$retour=parent::adminHeader();
	$retour.="</b>".$this->getTotal()."<b>";
	return $retour;
	}
	*/

	function adminFooter()
	{
		$retour=parent::adminFooter();
		$retour.=$this->getTotal();
		return $retour;
	}
	function getTotal()
	{

		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();
		if ($id_organisme>0)
		{
			$sql="SELECT max(YEAR( r.date_debut )) AS an_max, min(YEAR( r.date_debut )) AS an_min, o.nom as nom_organisme
			FROM  `organisme_rencontre` r, organisme o
			WHERE r.id_organisme =o.id and o.id=$id_organisme
		 ";
			$data = $db->getrows($sql);
			$min=$data[0]["an_min"];
			$max=$data[0]["an_max"];
			$res= $data[0]["nom_organisme"]." - Rencontres<br/>";
			$res .= "<table border='1'>";
			$res .= "<tr><td class='styletitre'>Annee";
			for($i=$min; $i<=$max; $i++)
			{
				$res.='</td><td>'.'<p style="text-align: center; margin-top:0px; margin-bottom:0px">'.$i.'</p>';
			}
			$res.="</td></tr>";
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
					$sql="SELECT count(r.id) as nombre_rencontre
					FROM  `organisme_rencontre` r, type_rencontre tr
					WHERE YEAR( r.date_debut )=$j
					AND r.id_organisme =$id_organisme
					AND r.id_type_rencontre =tr.id
						
					AND tr.id=$id_type_rencontre "
					;
					$data1 = $db->getrows($sql);
					$nombre_rencontres=$data1[0]["nombre_rencontre"];
						
					$sql="SELECT  count(ir.id) as nombre_inscrits,
					sum(ir.participation_partielle) as nombre_participants_partiels,
					sum(ir.participation_complete) as nombre_participants_complets
					FROM  individu_rencontre ir
					WHERE ir.id_rencontre in (SELECT r.id
					FROM  `organisme_rencontre` r
					WHERE YEAR( r.date_debut )=$j
					AND r.id_organisme =$id_organisme
					AND r.id_type_rencontre =$id_type_rencontre)"
					;
					$data1 = $db->getrows($sql);
					$nombre_inscrits=$data1[0]["nombre_inscrits"];
					$nombre_participants_partiels=$data1[0]["nombre_participants_partiels"];
					$nombre_participants_complets=$data1[0]["nombre_participants_complets"];
					
					$lien1=href(dispatch_url("organisme.rencontre", "admin", array (
							'atkfilter' => " organisme_rencontre.id_organisme = $id_organisme
							and organisme_rencontre.id_type_rencontre =$id_type_rencontre
							and YEAR(organisme_rencontre.date_debut)=$j "
					), "dispatch.php"), $nombre_rencontres , SESSION_NESTED,null,
							'title="Nombres de rencontres"');
					($nombre_rencontres==0) ? $lien1="" : null;
					
					$lien2=href(dispatch_url("individu.rencontre_i", "admin", array (
							'atkfilter' => " individu_rencontre.id_rencontre
							in
							(SELECT r.id
							FROM  `organisme_rencontre` r
							WHERE YEAR( r.date_debut )=$j
							AND r.id_organisme =$id_organisme
							AND r.id_type_rencontre =$id_type_rencontre)"
					), "dispatch.php"), $nombre_inscrits."(".$nombre_participants_partiels."/".$nombre_participants_complets.")" , SESSION_NESTED,null,
							'title="Inscrits(Partiels/Complets"');
					($nombre_rencontres==0) ? $lien2="" : $lien1=$lien1." / ";
					$res.='</td><td>'.'<b>'.$lien1.'</b>'.$lien2;
						
						
				}$res.="</td></tr>";


			}
			$res.="</table>".$this->getUserStamp('n','o');
		}
			

		return $res;
	}




}
?>