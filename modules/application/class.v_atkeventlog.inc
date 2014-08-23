<?php

class v_atkeventlog extends assMetaNode {
	var $gChart_array = array ();
	var $table_heure='v_atkeventlog_heure';
	var $table_jour='v_atkeventlog_jour';
	var $table_mois='v_atkeventlog_mois';
	var $table_an='v_atkeventlog_an';



	function v_atkeventlog() {
		$this->atkNode("v_atkeventlog");
		$this->setSecurityAlias("profil.profil");
		$this->m_securityMap["stats_heure"] = "view";
		$this->m_securityMap["stats_jour"] = "view";
		$this->m_securityMap["stats_semaine"] = "view";
		$this->m_securityMap["stats_mois"] = "view";
		$this->m_securityMap["stats_an"] = "view";
	}
	function getEnTete($mode)
	{
		if ($mode=='heure')
		{	$nombre=23;
		$depart=0;
		$res = "<tr><td class='styletitre'>utilisateur";
		for($i=$depart; $i<=$nombre; $i++)
		{			$res.='</td><td>'.$i;		}
		}
		if ($mode=='jour')
		{
			$anmois=$this->m_postvars["mois_debut"];
			$an=substr($anmois,0,4);
			$mois=substr($anmois,5,2);
			$nombre=cal_days_in_month(CAL_GREGORIAN,$mois,$an);
			$depart=1;
			$mois=$this->m_postvars["mois_debut"];
			$res = "<tr><td class='styletitre'>utilisateur";
			for($i=$depart; $i<=$nombre; $i++)
			{			$res.='</td><td>'.href(dispatch_url("application.v_atkeventlog", "stats_heure", array ("jour_debut" => "" .$mois.'-'. str_pad($i,2,"0",STR_PAD_LEFT) . "")), text($i), SESSION_NESTED);
			}
		}
		if ($mode=='mois')
		{	$nombre=12;
		$depart=1;
		$an=$this->m_postvars["an_debut"];
		$res = "<tr><td class='styletitre'>utilisateur";
		for($i=$depart; $i<=$nombre; $i++)
		{			$res.='</td><td>'.href(dispatch_url("application.v_atkeventlog", "stats_jour", array ("mois_debut" => "" .$an.'-'. str_pad($i,2,"0",STR_PAD_LEFT) . "")), text($i), SESSION_NESTED);
		}
		}
		if ($mode=='an')
		{
			$db = & atkGetDb();
			$sql="select max(an) as maxi, min(an) as mini
			from $this->table_an ";	
			$data = $db->getrows($sql);
			$depart=$data[0]["mini"];
			$nombre=$data[0]["maxi"];

			$res = "<tr><td class='styletitre'>utilisateur";
			for($i=$depart; $i<=$nombre; $i++)
			{			$res.='</td><td>'.href(dispatch_url("application.v_atkeventlog", "stats_mois", array ("an_debut" => "" . $i . "")), text($i), SESSION_NESTED);
			}
		}
		$res.='</td><td>Total</td></tr>';
		return $res;
	}
	function getLigne($mode,&$ligne, &$nom, &$activity)
	{
		if ($mode=='heure')
		{	$nombre=24;
		$depart=0;
		}
		if ($mode=='jour')
		{				$anmois=$this->m_postvars["mois_debut"];
		$an=substr($anmois,0,4);
		$mois=substr($anmois,5,2);
		$nombre=cal_days_in_month(CAL_GREGORIAN,$mois,$an);
		$depart=1;
		}
		if ($mode=='mois')
		{	$nombre=12;
		$depart=1;
		}
		if ($mode=='an')
		{				$db = & atkGetDb();
		$sql="select max(an) as maxi, min(an) as mini
			from $this->table_an ";	
		$data = $db->getrows($sql);
		$depart=$data[0]["mini"];
		$nombre=$data[0]["maxi"];
		}
		$res = "<tr><td class='styleligne'>$nom";
		$total=0;
		for($i=$depart; $i<=$nombre; $i++)
		{			$res.='</td><td>'.$ligne[$i];
		if ($activity[$i]!='')
		{$total+=$activity[$i];}
		}
		$res.='</td><td>'.$total.'</td></tr>';
		return $res;
	}

	function getTop($param,&$sql)
	{
		$an_link=href(dispatch_url("application.v_atkeventlog", "stats_an"), text('Ans'), SESSION_NESTED);
		$mois_link=href(dispatch_url("application.v_atkeventlog", "stats_mois", array ("an_debut" => "" . gmdate('Y'). "")), text('Mois'), SESSION_NESTED);
		$jour_link=href(dispatch_url("application.v_atkeventlog", "stats_jour", array ("mois_debut" => "" . gmdate ('Y-m') . "")), text('Jours'), SESSION_NESTED);
		$heure_link=href(dispatch_url("application.v_atkeventlog", "stats_heure", array ("jour_debut" => "" . gmdate('Y-m-d') . "")), text('Heures'), SESSION_NESTED);
		$heure_link=href(dispatch_url("application.v_atkeventlog", "stats_heure", array ("jour_debut" => "" . gmdate('Y-m-d') . "")), text('Heures'), SESSION_NESTED);

		if ($param=='heures')
		{$heure_link='<b>'.$heure_link.'</b>';
		$jour=$this->m_postvars["jour_debut"];
		$Y=substr($jour,0,4);
		$m=substr($jour,5,2);
		$d=substr($jour,8,2);
		$jour_suiv = mktime(0,0,0,$m,$d+1,$Y);
		$jour_suiv=date("Y-m-d", $jour_suiv);
		$jour_prec = mktime(0,0,0,$m,$d-1,$Y);
		$jour_prec=date("Y-m-d", $jour_prec);

		$prec=href(dispatch_url("application.v_atkeventlog", "stats_heure", array ("jour_debut" => "" . $jour_prec . "")), text('Précédant'), SESSION_NESTED);
		If ($jour==gmdate('Y-m-d'))
		{ $suiv='';}
		else {
			$suiv=href(dispatch_url("application.v_atkeventlog", "stats_heure", array ("jour_debut" => "" . $jour_suiv . "")), text('Suivant'), SESSION_NESTED);
		}
		$sql="select jour,userid,nom,prenom,heure,activity
			from $this->table_heure where jour ='$jour' order by nom, prenom, jour desc, heure";
		$navigation="Navigation : ".$prec.' <b>'.$jour.'</b> '.$suiv.'<br />';
		}

		if ($param=='jours')
		{$jour_link='<b>'.$jour_link.'</b>';
		$mois=$this->m_postvars["mois_debut"];
		$Y=substr($mois,0,4);
		$m=substr($mois,5,2);

		$mois_suiv = mktime(0,0,0,$m+1,1,$Y);
		$mois_suiv=date("Y-m", $mois_suiv);
		$mois_prec = mktime(0,0,0,$m-1,1,$Y);
		$mois_prec=date("Y-m", $mois_prec);

		$prec=href(dispatch_url("application.v_atkeventlog", "stats_jour", array ("mois_debut" => "" . $mois_prec . "")), text('Précédant'), SESSION_NESTED);
		If ($mois==gmdate('Y-m'))
		{ $suiv='';}
		else {
			$suiv=href(dispatch_url("application.v_atkeventlog", "stats_jour", array ("mois_debut" => "" . $mois_suiv . "")), text('Suivant'), SESSION_NESTED);
		}
		$sql="select jour,userid,nom,prenom,activity
			from $this->table_jour where jour like '".$mois."%' order by nom, prenom, jour ";
		$navigation="Navigation : ".$prec.' <b>'.$mois.'</b> '.$suiv.'<br />';
		}
		if ($param=='mois')
		{$mois_link='<b>'.$mois_link.'</b>';
		$an=$this->m_postvars["an_debut"];
		$Y=substr($an,0,4);


		$an_suiv = mktime(0,0,0,1,1,$Y+1);
		$an_suiv=date("Y", $an_suiv);
		$an_prec = mktime(0,0,0,1,1,$Y-1);
		$an_prec=date("Y", $an_prec);

		$prec=href(dispatch_url("application.v_atkeventlog", "stats_mois", array ("an_debut" => "" . $an_prec . "")), text('Précédant'), SESSION_NESTED);
		If ($an==gmdate('Y'))
		{ $suiv='';}
		else {
			$suiv=href(dispatch_url("application.v_atkeventlog", "stats_mois", array ("an_debut" => "" . $an_suiv . "")), text('Suivant'), SESSION_NESTED);
		}
		$sql="select mois,userid,nom,prenom,activity
			from $this->table_mois where mois like '".$an."%' order by nom, prenom, mois ";
		$navigation="Navigation : ".$prec.' <b>'.$an.'</b> '.$suiv.'<br />';

		}
		if ($param=='ans')
		{$an_link='<b>'.$an_link.'</b>';
		$sql="select an,userid,nom,prenom,activity
			from $this->table_an  order by nom, prenom, an ";
		$navigation='<br />';
		}
		$top="Contenu : ".$an_link.' | '.$mois_link.' | '.$jour_link.' | '.$heure_link.'<br />';
		$top.="Apparence : ".'<b>Tableau</b> | Graphique'.'<br />';
		$top.=$navigation;
		return $top;
	}

	function action_stats_heure(& $handler) {
		$top=$this->getTop('heures',$sql);
		$db = & atkGetDb();
		$data = $db->getrows($sql);
		$res="<br />"."<table border='1'>";
		$res.=$this->getEnTete('heure');
		$nom='';
		foreach ($data as $rec)
		{$pos=stripos($rec["heure"],':');
		if ($pos==2)
		{$rec["heure"]=substr($rec["heure"],0,2);}
		else
		{$rec["heure"]=substr($rec["heure"],0,1);}
		$url= href(dispatch_url("profil.log", "admin", array (
				'atkfilter' => "atkeventlog.userid='". $rec['userid']."' and atkeventlog.stamp like '". $rec['jour'].' '.$rec['heure'].'%'."'"
				), "dispatch.php"), text($rec["activity"]), SESSION_NESTED);
				if ($nom!=$rec["nom"].' '.$rec["prenom"])
				{
					if ($nom!='')
					{
						$res .= $this->getLigne('heure', $ligne, $nom, $activity);
						$ligne=array();
						$activity=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$rec["heure"]]=$url;
						$activity[$rec["heure"]]=$rec["activity"];
					}
					else
					{
						$ligne=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$rec["heure"]]=$url;
						$activity[$rec["heure"]]=$rec["activity"];
					}
				}else
				{$nom=$rec["nom"].' '.$rec["prenom"];
				$ligne[$rec["heure"]]=$url;
				$activity[$rec["heure"]]=$rec["activity"];
				}
		}
		$res .= $this->getLigne('heure', $ligne, $nom, $activity);
		$this->affiche($res,$top);
	}
	function action_stats_jour(& $handler) {
		$top=$this->getTop('jours',$sql);
		$db = & atkGetDb();
		$data = $db->getrows($sql);
		$res ='<br />'."<table border='1'>";
		$res.= $this->getEnTete('jour');
		$nom='';
		foreach ($data as $rec)
		{
			$jour_jj=ltrim(substr($rec["jour"],8,2),'0');
			$url= href(dispatch_url("profil.log", "admin", array (
				'atkfilter' => "atkeventlog.userid='". $rec['userid']."' and atkeventlog.stamp like '". $rec['jour'].'%'."'"
				), "dispatch.php"), text($rec["activity"]), SESSION_NESTED);
				if ($nom!=$rec["nom"].' '.$rec["prenom"])
				{
					if ($nom!='')
					{
						$res .= $this->getLigne('jour', $ligne, $nom, $activity);
						$ligne=array();
						$activity=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$jour_jj]=$url;
						$activity[$jour_jj]=$rec["activity"];
					}
					else
					{
						$ligne=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$jour_jj]=$url;
						$activity[$jour_jj]=$rec["activity"];
					}
				}else
				{$nom=$rec["nom"].' '.$rec["prenom"];
				$ligne[$jour_jj]=$url;
				$activity[$jour_jj]=$rec["activity"];
				}
		}
		$res .= $this->getLigne('jour', $ligne, $nom, $activity);
		$this->affiche($res,$top);
	}
	function action_stats_mois(& $handler) {
		$top=$this->getTop('mois',$sql);
		$db = & atkGetDb();
		$data = $db->getrows($sql);
		$res ='<br />'."<table border='1'>";
		$res .= $this->getEnTete('mois');
		$nom='';
		foreach ($data as $rec)
		{
			$mois_mm=ltrim(substr($rec["mois"],5,2),'0');
			$url= href(dispatch_url("profil.log", "admin", array (
				'atkfilter' => "atkeventlog.userid='". $rec['userid']."' and atkeventlog.stamp like '". $rec['mois'].'%'."'"
				), "dispatch.php"), text($rec["activity"]), SESSION_NESTED);
				if ($nom!=$rec["nom"].' '.$rec["prenom"])
				{
					if ($nom!='')
					{
						$res .= $this->getLigne('mois', $ligne, $nom, $activity);
						$ligne=array();
						$activity=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$mois_mm]=$url;
						$activity[$mois_mm]=$rec["activity"];
					}
					else
					{
						$ligne=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$mois_mm]=$url;
						$activity[$mois_mm]=$rec["activity"];
					}
				}else
				{$nom=$rec["nom"].' '.$rec["prenom"];
				$ligne[$mois_mm]=$url;
				$activity[$mois_mm]=$rec["activity"];
				}
		}
		$res .= $this->getLigne('mois', $ligne, $nom, $activity);
		$this->affiche($res,$top);

	}
	function action_stats_an(& $handler) {
		$top=$this->getTop('ans',$sql);
		$db = & atkGetDb();
		$data = $db->getrows($sql);
		$res = '<br />'."<table border='1'>";
		$res.= $this->getEnTete('an');
		$nom='';
		foreach ($data as $rec)
		{
			$an=$rec["an"];
			$url= href(dispatch_url("profil.log", "admin", array (
				'atkfilter' => "atkeventlog.userid='". $rec['userid']."' and atkeventlog.stamp like '". $rec['an'].'%'."'"
				), "dispatch.php"), text($rec["activity"]), SESSION_NESTED);
				if ($nom!=$rec["nom"].' '.$rec["prenom"])
				{
					if ($nom!='')
					{
						$res .= $this->getLigne('an', $ligne, $nom, $activity);
						$ligne=array();
						$activity=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$an]=$url;
						$activity[$an]=$rec["activity"];
					}
					else
					{
						$ligne=array();
						$nom=$rec["nom"].' '.$rec["prenom"];
						$ligne[$an]=$url;
						$activity[$an]=$rec["activity"];
					}
				}else
				{$nom=$rec["nom"].' '.$rec["prenom"];
				$ligne[$an]=$url;
				$activity[$an]=$rec["activity"];
				}
		}
		$res .= $this->getLigne('an', $ligne, $nom, $activity);
		$this->affiche($res,$top);

	}
	function affiche(&$res,&$top)
	{

		$res .= "</table>";
		$restot=$top.$res;
		
		$restot.=$this->afficheGraphique($res,$top);
		$page =   &atkinstance("atk.ui.atkpage");
		$theme = atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent( $restot);
	}
/*	function afficheGraphique(&$res,&$top)
	{
		//require (atkconfig("atkroot")."modules/gChart/gChart2.php");
		require (atkconfig("atkroot")."modules/GChartPhp/gChart.php");
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
	*/
	function getMax($ArrayToCheck){
		$maxValue = 1;

		foreach($ArrayToCheck as $temp){
			if(is_array($temp)){
				$maxValue = max($maxValue, utility::getMaxOfArray($temp));
			}
			else{
				$maxValue = max($maxValue, $temp);
			}
		}
		return $maxValue;
	}

}
?>