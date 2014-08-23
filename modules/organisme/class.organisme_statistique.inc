<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class organisme_statistique extends assMetaNode {
	var $table = "organisme_statistique";

	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function organisme_statistique() {
		$this->atkMetaNode();
		$this->atkNode("organisme_statistique",  NF_ADD_LINK  | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_organisme",
				"libelle",
		"id_type_statistique",
		"an_max",
		"an_min",
						"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Lignes" => array (
				"lignes" )
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
				$this->add(new atkManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkManyToOneRelation("id_type_statistique", "table.type_statistique", AF_SEARCHABLE | AF_RELATION_AUTOLINK));
				$this->add(new atkAttribute("an_max"));
				$this->add(new atkAttribute("an_min"));
				$this->add(new atkOneToManyRelation("lignes", "organisme.organisme_statistique_ligne", "id_organisme_statistique", AF_HIDE_LIST));

				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->setIndex("libelle");
				$this->setOrder("date_modification desc");
				$this->m_securityMap["calculer"] = "view";
				$this->m_securityMap["statistiques"] = "view";

	}
	function descriptor_def() {
		return "[libelle]";
	}
	function action_calculer(&$handler)
	{
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];

		foreach ($select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$organisme_statistique_id= $array_id[1];
			$sql="delete from organisme_statistique_ligne where id_organisme_statistique=$organisme_statistique_id";
			$db->query($sql);
			$sql="SELECT id_organisme, sql_an, sql_mois, lien_id_type
			from organisme_statistique os, type_statistique ts
			where os.id =$organisme_statistique_id
			and os.id_type_statistique=ts.id";
			$data = $db->getrows($sql);
			$sqlan=$data[0]["sql_an"];
			$sqlan=str_replace('$id_entite', $data[0]["id_organisme"], $sqlan);
			$sqlmois=$data[0]["sql_mois"];
			$sqlmois=str_replace('$id_entite', $data[0]["id_organisme"], $sqlmois);
			$data[0]["id_organisme"];
			$lien_id_type=$data[0]["lien_id_type"];
			$data = $db->getrows($sqlan);
			for ($i = 0; $i < count($data); $i++)
			{
				(!empty($lien_id_type)) ? $id_type=$data[$i]["id_type"] : $id_type='NULL';
				$an=$data[$i]["an"];
				//			if (empty($an)) continue;
				$mois="NULL";
				$nombre=$data[$i]["nombre"];
				$id=$db->nextid('seq_organisme_statistique_ligne');
				$sql="INSERT into organisme_statistique_ligne
				( id, id_organisme_statistique, id_type, an, mois, nombre, commentaire, id_creation, date_creation, id_modification , date_modification)
				Values 
				($id,
				$organisme_statistique_id,
				$id_type,
				$an,
				$mois,
				$nombre,
				NULL,
				$userid,
				UTC_TIMESTAMP(),
				$userid,
				UTC_TIMESTAMP() )";
				$db->query($sql);
				($i==0) ? $anmin=$an : NULL;
					
			}
			$anmax=$an;
			$sql="update organisme_statistique set an_min=$anmin, an_max=$anmax, id_modification=$userid,
				date_modification=UTC_TIMESTAMP() where id=$organisme_statistique_id ";
			$db->query($sql);
			$data = $db->getrows($sqlmois);
			$i=0;
			for ($i = 0; $i < count($data); $i++)
			{
				(!empty($lien_id_type)) ? $id_type=$data[$i]["id_type"] : $id_type='NULL';
				$an=$data[$i]["an"];
				//		if (empty($an)) continue;
				$mois=$data[$i]["mois"];
				$nombre=$data[$i]["nombre"];
				$id=$db->nextid('seq_organisme_statistique_ligne');
				$sql="INSERT into organisme_statistique_ligne
				( id, id_organisme_statistique, id_type, an, mois, nombre, commentaire, id_creation, date_creation, id_modification , date_modification)
				Values 
				($id,
				$organisme_statistique_id,
				$id_type,
				$an,
				$mois,
				$nombre,
				NULL,
				$userid,
				UTC_TIMESTAMP(),
				$userid,
				UTC_TIMESTAMP() )";
				$db->query($sql);

			}


		}
		$messagefin="Calcul terminé";
		$this->setFeedback("calculer",ACTION_SUCCESS);
		$location = $this->feedbackUrl("calculer", ACTION_SUCCESS, "", $messagefin);
		$this->redirect($location);
	}
	function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
	function action_statistiques(&$handler)
	{
		if (is_array($this->m_postvars["atkselector"])) {
			$select = $this->m_postvars["atkselector"];
		} else {
			$select[0] = $this->m_postvars["atkselector"];
		}
		$this->statistique_an($select);
	}
	function statistique_an($tableau_select)
	{
		$db = & atkGetDb();
		$total_total=0;
		foreach ($tableau_select as $id_variable) {
			$array_id = explode('=', $id_variable);
			$ids_organisme_statistique .= $array_id[1] . ',';
		}
		$ids_organisme_statistique = substr($ids_organisme_statistique, 0, strlen($ids_organisme_statistique) - 1);
		$sql="SELECT MAX(an_max) as an_max, MIN(an_min) as an_min
		 from organisme_statistique	where id in (".$ids_organisme_statistique.") ";
		$data=$db->getrows($sql);
		$an_max=$data[0]["an_max"];
		$an_min=$data[0]["an_min"];
		$id_ligne=0;
		$res["Titre"][]="#";
		$res["Titre"][]="Libelle";
		$res["Titre"][]="Type";
/*		for ($i = $an_min; $i < $an_max+1; $i++)
		{
			$res["Titre"][]=$i;
		}
		*/
	for ($i = $an_max; $i > $an_min-1; $i--)
		{
			$res["Titre"][]=$i;
		}
		$res["Titre"][]="Total";
		for ($j = 0; $j < count($res["Titre"]); $j++)
		{
			$res["Total"][$res["Titre"][$j]]	="";
		}
		foreach ($tableau_select as $id_variable) {
			$id_ligne++;
			for ($j = 0; $j < count($res["Titre"]); $j++)
			{
				$res[$id_ligne][$res["Titre"][$j]]	="";
			}
			$array_id = explode('=', $id_variable);
			$id_organisme_statistique=$array_id[1];

			$sql="SELECT ts.url_date_heure, ts.url_entite, ts.url_type ,ts.url_module, os.id_organisme, os.libelle as libelle_organisme_statistique, lien_id_type
			from type_statistique ts, organisme_statistique os
			where os.id=$id_organisme_statistique and os.id_type_statistique=ts.id ";
			$data=$db->getrows($sql);
			$libelle_organisme_statistique=$data[0]["libelle_organisme_statistique"];
			$url_module=$data[0]["url_module"];
			$url_entite=$data[0]["url_entite"];
			$url_date_heure=$data[0]["url_date_heure"];
			$url_type=$data[0]["url_type"];
			$id_organisme=$data[0]["id_organisme"];
			if (!empty($data[0]["lien_id_type"]))
			{
					
				$array_id = explode('.', $data[0]["lien_id_type"]);
				$table_type=$array_id[0];
				$id_type=$array_id[1];
				$sql="SELECT ".$table_type.".".$id_type." as type_id, libelle  , an, nombre from organisme_statistique_ligne, ".$table_type
				." where organisme_statistique_ligne.id_organisme_statistique=$id_organisme_statistique
				and mois is null 
				and 
				organisme_statistique_ligne.id_type=".$table_type.".".$id_type." order by 2,3";
				//			$this->p($sql);
			}
			else {
				$sql="SELECT  an, nombre from organisme_statistique_ligne
				where id_organisme_statistique=$id_organisme_statistique
				 and mois is null order by 1";
			}
			$data=$db->getrows($sql);

			$res[$id_ligne]["#"]=$id_ligne;
			$total=0;
			$libelle_type_moins1="";
			for ($i = 0; $i < count($data); $i++)
			{
				$libelle_type=$data[$i]["libelle"];
				$type_id=$data[$i]["type_id"];
				if ($i>0 && $libelle_type!=$libelle_type_moins1)
				{
					$res[$id_ligne]["#"]=$id_ligne;
					$href="dispatch.php?atknodetype=".$url_module.'&atkaction=admin&atkfilter='.$url_entite."=".$id_organisme." ";
					(!empty($url_type))? $href.=" and ".$url_type."=".$type_id_moins."&" : $href.="&";
					$res[$id_ligne]["Total"]='<a href="'.$href.'" target="_blank" >'. $total.'</a> ';
					$total=0;
					$id_ligne++;
					for ($j = 0; $j < count($res["Titre"]); $j++)
					{
						$res[$id_ligne][$res["Titre"][$j]]	="";
					}
					$res[$id_ligne]["Libelle"]=$libelle_organisme_statistique;
					$res[$id_ligne]["Type"]=$libelle_type;
				}
				$res[$id_ligne]["#"]=$id_ligne;
				$res[$id_ligne]["Libelle"]=$libelle_organisme_statistique;
				$res[$id_ligne]["Type"]=$libelle_type;
				$res[$id_ligne]["id_type"]=$type_id;
				$href="dispatch.php?atknodetype=".$url_module.'&atkaction=admin&atkfilter='.$url_entite."=".$id_organisme." and year(".$url_date_heure.")=".$data[$i]["an"]."";
				(!empty($url_type))? $href.=" and ".$url_type."=".$type_id."&" : $href.="&";
				$an=$data[$i]["an"];
/*				$url_statistiques_mois=atkHref(dispatch_url("organisme.organisme_statistique", "statistique_mois", array ("id" => "$id_organisme_statistique",
				"an" => "$an"	)),
		'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/statistique_plus.png" alt="Statistiques mensuelles" 
			title="Statistiques mensuelles"  ></img>',SESSION_NESTED, false,
		 'target="_blank"');
*/
				$url_statistiques_mois=atkHref(dispatch_url("organisme.organisme_statistique", "statistique_mois", array ("id" => "$id_organisme_statistique",
				"an" => "$an"	)),
		'...',SESSION_NESTED, false,
		 'target="_blank"');					
//				$res[$id_ligne][$data[$i]["an"]]='<a href="'.$href.'" target="_blank" >'. ceil($data[$i]["nombre"]).'</a>&nbsp;'.$url_statistiques_mois;
$res[$id_ligne][$data[$i]["an"]]= ceil($data[$i]["nombre"]);
$res[$id_ligne][$data[$i]["an"]]=$this->decoupe_affichage_colonne($res[$id_ligne][$data[$i]["an"]], 100);
				$total+=$data[$i]["nombre"];
				$res["Total"][$data[$i]["an"]]+=$data[$i]["nombre"];
				$total_total+=$data[$i]["nombre"];
				$libelle_type_moins1=$data[$i]["libelle"];
				$type_id_moins=$data[$i]["type_id"];
			}
			$href="dispatch.php?atknodetype=".$url_module.'&atkaction=admin&atkfilter='.$url_entite."=".$id_organisme." ";
			(!empty($url_type))? $href.=" and ".$url_type."=".$type_id."&" : $href.="&";
			$res[$id_ligne]["Total"]='<a href="'.$href.'" target="_blank" >'. $total.'</a> ';


		}
		$res["Total"]["Total"]+=$total_total;
//$this->p($res);
		$data=array();
		$row=array();
		for ($j = 0; $j < count($res["Titre"]); $j++)
		{
			$row[]=$res["Titre"][$j]	;
		}
		$data[]=$row;
		$row=array();
		$chd_tableau="";
		for ($k = 1; $k < $id_ligne+1; $k++){
			$chd_ligne="";
			for ($j = 0; $j < count($res["Titre"]); $j++)
			{
				$row[]=$res[$k][$res["Titre"][$j]];
				$type_id=$res[$k]["id_type"];
			}
			$url_chart_ligne=dispatch_url("organisme_statistique", "graphique", 
			array (
			"type" => "ligne",
			"id_organisme"=> $id_organisme ,
			"id_organisme_statistique" => $id_organisme_statistique,
			"id_type" => $type_id
			));
			$url_chart_ligne='<a href="'.$url_chart_ligne.' target="_blank">
			<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/statistique.png" alt="Graphique ligne" 
			title="Graphique ligne"  ></img></a>';
//			$row[1]=$url_chart_ligne.' '.$row[1];
			$data[]=$row;
			$row=array();
		}
		for ($j = 0; $j < count($res["Titre"]); $j++)
		{
			$row[]=$res["Total"][$res["Titre"][$j]];
		
		}
			$url_chart_total=dispatch_url("organisme_statistique", "graphique", 
			array (
			"type" => "total",
			"id_organisme"=> $id_organisme ,
			"ids_organisme_statistique" => $ids_organisme_statistique
			));
			$url_chart_total='<a href="'.$url_chart_total.' target="_blank">
			<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/statistique.png" alt="Graphique lignes" 
			title="Graphique lignes"  ></img></a>';
			$row[1]=$url_chart_total.' '.$row[1];
		$data[]=$row;
		$row=array();
//				$this->p($data);
		$tbl = & atknew("atk.utils.atktablerenderer");
		$tbl->setRowClass(1, "superbold");
		$sortie = $tbl->render($data, 0, "recordlist");

		$page = & atknew("atk.ui.atkpage");
		$ui = & atkinstance("atk.ui.atkui");
		$output = & atkOutput :: getInstance();
		$page->register_style($ui->stylePath("style.css"));
		$page->addContent($sortie);

		$output->output($page->render(atktext('Statistiques organisme'), true,'', '<base target="_blank">'));
			
	}
	function afficheGraphique(&$res,&$top)
	{
		require (atkconfig("atkroot")."modules/gChart/gChart2.php");

		$ligne_valeurs_serie=array();
		$ligne_etiquette_serie=array();
		$x_axis_labels=array();
		$res=str_replace('<tr><td>','',$res);
		$res=str_replace('</td><td>','|',$res);
		$res=str_replace('</td></tr>','|;',$res);
		$res=strip_tags($res);
		$res=str_replace('||','|0|',$res);
		$res=str_replace('||','|0|',$res);
		$chart = new gGroupedBarChart;
		$chart->width = 500;
		$chart->height = 200;
		$chart->axis ="x,y";
		// get x_axis_labels
		$ligne=substr($res,0,strpos($res,';'));
		$res=substr($res,strpos($res,';')+1);
		while (strpos($ligne,'|'))
		{$x_label[]=substr($ligne,0,strpos($ligne,'|'));
		$ligne=substr($ligne,strpos($ligne,'|')+1);}
		array_shift($x_label);
		array_pop($x_label);
		$ymax=0;
		$xmax=$this->getMax($x_label);
		$xlabels="0,0,$xmax,1";
		$chart->addAxisLabels($xlabels);
		while (strpos($res,';'))
		{
			$ligne=substr($res,0,strpos($res,';'));
			$res=substr($res,strpos($res,';')+1);
			$serie=array();
			while (strpos($ligne,'|'))
			{$serie[]=substr($ligne,0,strpos($ligne,'|'));
			$ligne=substr($ligne,strpos($ligne,'|')+1);
			}
			$legende[]=array_shift($serie);
			array_pop($serie);
			$chart->addDataSet($serie);
			if	($ymax<$this->getMax($serie))
			$ymax=$this->getMax($serie);
		}
		$ylabels ="1,0,$ymax";
		$chart->addAxisLabels($ylabels);
			$chart->dataColors="FF0000,00FF00,0000FF,000000,FF7f50,006400,ff8c00,adff2f,ffff00,000080,ff00ff,ff69b4";
		//		die ();

		$chart->valueLabels =$legende;
		$retour='<h2>Graphique</h2>';
		$url=$chart->getUrl();
		$url.='&chbh=r,0.2,0.5';
		$url.='&chdlp=t';
		$url.='&chma=10,10,10,10';
//		$url.='&chof=validate';
//		print_r ($url);
//		die();

		$retour.='<img src="'.$url.'" />';
		return $retour;
	}

	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
		$mraactions['calculer'] = "calculer";
		//		$actions['statistiques']= dispatch_url("traitement.statistique",
		//                                                     "afficher",
		//                                                      array("id"=>$rec["id"]));
		//                                                    $this->p($actions['statistiques']);
		$mraactions['statistiques'] = "statistiques";
	}
	function libelle_display($record, $mode) {
		$retour=$record["libelle"]."<br />";
		$db = & atkGetDb();
		$sql="SELECT count(id) as nombrean from organisme_statistique_ligne
		where id_organisme_statistique=".$record['id']."
		 and mois is null";
		$data=$db->getrows($sql);
		$nombre_an=$data[0]["nombrean"];
		$sql="SELECT count(id) as nombremois from organisme_statistique_ligne
		where id_organisme_statistique=".$record['id']."
		 and mois is not null";
		$data=$db->getrows($sql);
		$nombre_mois=$data[0]["nombremois"];
		($nombre_an>0 || $nombre_mois>0) ? $retour.="(".$nombre_an."/".$nombre_mois.")" : null;
		return $retour;
	}
}
?>