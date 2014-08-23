<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgNumberExpressionAttribute");
class fonction extends assMetaNode {
	var $table = "type_fonction";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function fonction() {
		$this->atkMetaNode();
		$this->atkNode("fonction",NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA | NF_COMPACT );
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE| NF_COMPACT));
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array ("id",
						"libelle",
						"nombre",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				),
				"Individus" => array (
						"fonction_organisme"
				)
		), AF_NO_LABEL));
		$this->add(new atkOneToManyRelation("fonction_organisme", "individu.fonction_i", "id_fonction", AF_HIDE_LIST | AF_FORCE_LOAD));
		$this->add(new atkAttribute("id", AF_FORCE_LOAD), NULL, 4);
		$this->add(new atkAttribute("libelle", AF_COMPACT), NULL, 4);
		$this->add(new atgNumberExpressionAttribute("nombre", ' select count(id) from individu_fonction
				where id_fonction =[table].id
				', 0, 0));
		$this->add(new atkDummyAttribute("stats_fonctions", "Statistiques", AF_DUMMY_SHOW_LABEL|AF_COMPACT), NULL, 5);
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL | AF_COMPACT),null,7);

		$this->setOrder("libelle");
	}


	function nombre_display($record, $mode) {
		if (isset ($record["nombre"])) {
			return href(dispatch_url("individu.fonction_i", "admin", array (
					'atkfilter' => "individu_fonction.id_fonction='" . $record['id'] . "'"
			), "dispatch.php"), text($record["nombre"]), SESSION_NESTED);
		} else {
			return "";
		}
	}
	function descriptor_def() {
		return "[libelle]";
	}

	function libelle_display ($record, $mode) {
		$id_type=$record["id"];
		$retour=$this->descripteur_type_fonction($id_type,'o');
		$id_organisme=$this->m_postvars["id_organisme"];
		// récupérer id_organisme
		if ($id_organisme>0)
		{
			$retour.="<br />".$this->descripteur_organisme($id_organisme,'n','o','50');
			// récupérer nombre
			$db = & atkGetDb();
			$sql="SELECT count(id) as nombre  from individu_fonction
			where   date_fin is  null
			and id_organisme=$id_organisme
			and id_fonction = $id_type";
			$data = $db->getrows($sql);
			$nombre_actif=$data[0]["nombre"];
			$sql="SELECT count(id) as nombre  from individu_fonction
			where   id_organisme=$id_organisme
			and id_fonction = $id_type";
			$data = $db->getrows($sql);
			$nombre_total=$data[0]["nombre"];

			if ($nombre_total > 0) {
				$lien_actif=href(dispatch_url("individu.fonction_i", "admin", array (
						'atkfilter' => "individu_fonction.id_organisme=" . $id_organisme . " and date_fin is null and individu_fonction.id_fonction=" . $id_type . ""
				), "dispatch.php"), $nombre_actif, SESSION_NESTED);
				$lien_total=href(dispatch_url("individu.fonction_i", "admin", array (
						"view"=> "nonactive",
						'atkfilter' => "individu_fonction.id_organisme=" . $id_organisme . "  and individu_fonction.id_fonction=" . $id_type . ""
				), "dispatch.php"), $nombre_total, SESSION_NESTED);
				$retour.="<br/>Nombre (actifs/tout) : <b>". $lien_actif."</b>/<b>".$lien_total."</b>";
			} else {
				$retour.="";
			}
		}

		return $retour;
	}
	function get_titre_graphique($record)
	{
		$id_organisme=$this->m_postvars["id_organisme"];
		$id_type_fonction=$record["id"];
		$db = & atkGetDb();
		if ($id_organisme>0)
		{
			$data = $db->getrows(" select nom from organisme where id=$id_organisme");
			$retour= $data[0]["nom"];
		}
		$data = $db->getrows(" select libelle from type_fonction where id=$id_type_fonction");
		$retour.= " - ".$data[0]["libelle"];
		return $retour;
	}

	function stats_fonctions_display(&$record, $mode)
	{

		$titre=$this->get_titre_graphique($record);
		// Pour un type de fonction et un organisme, trouver le min de date_debut, l'annee courante
		$id_type_fonction=$record["id"];
		$id_organisme=$this->m_postvars["id_organisme"];
		$db = & atkGetDb();
		if ($id_organisme>0)
		{
			//Déterminer date min
			$sql="SELECT min(YEAR( date_debut )) AS an_min
			FROM  `individu_fonction`
			WHERE id_organisme =$id_organisme
	
			AND id_fonction =$id_type_fonction
			";
		}
		else {
			$sql="SELECT min(YEAR( date_debut )) AS an_min
			FROM  `individu_fonction`
			WHERE  id_fonction =$id_type_fonction
		
			";
		}
		$data = $db->getrows($sql);
		$min=$data[0]["an_min"];
		($min=="")?$min=date("Y"):null;
		$max=date("Y");
		$res = $titre."<table border='1'>";
		$res .= "<tr><td class='styletitre'>Année";
		for($i=$min; $i<=$max ; $i++)
		{
			$res.='</td><td>'.'<p style="text-align: center; margin-top:0px; margin-bottom:0px">'.$i.'</p>';
				
		}
		$res.='</td></tr>';
		$res .= "<tr><td class='styletitre'>Nombre";
		for ($i=$min; $i<=$max;$i++)
		{
			if ($id_organisme>0)
			{
				$sql="select count(id) as nombre from individu_fonction
				where id_fonction=$id_type_fonction
				AND id_organisme=$id_organisme
				AND YEAR(date_debut)<= $i
				AND (YEAR(date_fin) >= $i OR date_fin is null)
				";
			}
			else
			{
				$sql="select count(id) as nombre from individu_fonction
				where id_fonction=$id_type_fonction
				AND YEAR(date_debut)<= $i
				AND (YEAR(date_fin) >= $i OR date_fin is null)
				";
			}

			$data = $db->getrows($sql);
			if ($id_organisme>0)
			{
				$lien=href(dispatch_url("individu.fonction_i", "admin", array (
						'view' => "nonactive",
						'atkfilter' => " individu_fonction.id_organisme =". $id_organisme
						." and individu_fonction.id_fonction =". $record['id']
						." AND YEAR(date_debut)<= $i
						AND (YEAR(date_fin) >= $i OR date_fin is null)" )
						, "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b") , SESSION_NESTED);
			}
			else
			{		$lien=href(dispatch_url("individu.fonction_i", "admin", array (
					'view' => "nonactive",
					'atkfilter' => " individu_fonction.id_fonction =". $record['id']
					." AND YEAR(date_debut)<= $i
					AND (YEAR(date_fin) >= $i OR date_fin is null)" )
					, "dispatch.php"), $this->nombre_format($data[0]["nombre"],"b"), SESSION_NESTED);
			}
			$res.='</td><td>'.$lien;

		}
		$res.='</td></tr>';
		$res.='</td></tr></table>'.$this->getUserStamp('n','o');;

		//		$record["graphique"]=$this->afficheGraphique($res,$titre);
			
		return $res;
	}
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
		$max=date(Y);
		if ($id_organisme>0)
		{
			$sql="SELECT min(YEAR( fi.date_debut )) AS an_min, o.nom as nom_organisme
			FROM  `individu_fonction` fi, organisme o
			WHERE fi.id_organisme =o.id and o.id=$id_organisme
			";
			$data = $db->getrows($sql);
			$min=$data[0]["an_min"];
			$res= $data[0]["nom_organisme"]." - Fonctions<br/>";
			$res.= "<table border='1'>";
			$res .= "<tr><td class='styletitre'>Annee";
			for($i=$min; $i<=$max; $i++)
			{
				$res.='</td><td>'.'<p style="text-align: center; margin-top:0px; margin-bottom:0px">'.$i.'</p>';
			}
			$res.="</td></tr>";
			$sql="SELECT distinct tf.libelle as libelle, tf.id as id_fonction
			FROM  `individu_fonction` fi, type_fonction tf
			WHERE fi.id_organisme =$id_organisme
			AND fi.id_fonction =tf.id
			ORDER BY tf.libelle ";
			$data = $db->getrows($sql);

			for ($i=0; $i<count($data); $i++)
			{
				$libelle=$data[$i]["libelle"];
				$id_type_fonction=$data[$i]["id_fonction"];
				$res .= "<tr><td class='styletitre'>$libelle";
				for ($j=$min; $j<=$max; $j++)
				{
					$sql="select count(id) as nombre from individu_fonction
					where id_fonction=$id_type_fonction
					AND id_organisme=$id_organisme
					AND YEAR(date_debut)<= $j
					AND (YEAR(date_fin) >= $j OR date_fin is null)
					";
					$data1 = $db->getrows($sql);
					$lien=href(dispatch_url("individu.fonction_i", "admin", array (
							'view' => "nonactive",
							'atkfilter' => " individu_fonction.id_fonction =". $id_type_fonction
							." AND YEAR(date_debut)<= $i
							AND (YEAR(date_fin) >= $i OR date_fin is null)" )
							, "dispatch.php"), $this->nombre_format($data1[0]["nombre"],"b") , SESSION_NESTED);
					$res.='</td><td>'.$lien;
				}
				$res.="</td></tr>";
			}
			$res.="</table>".$this->getUserStamp('n','o');
		}
			

		return $res;
	}



}
?>