<?php
class testguy extends atkNode {
	function testguy() {
		$this->atkNode("testguy");
		$this->setSecurityAlias("individu.individu");
		$this->m_securityMap["getmodules"] = "view";
		$this->m_securityMap["intro"] = "view";



	}
	/*			function action_intro(& $handler) {
		$this->setupScreen("Introduction", "Test
		<br>
		<br>
		", "getmodules", array (
		id => $this->m_postvars["id"]
		));

			
		}
		*/


	/*		function action_getclasses(& $handler) {

	global $g_modules;


	$traverser = atknew('atk.utils.atkdirectorytraverser');
	$classfinder = new atkClassFinder();
	$traverser->addCallbackObject($classfinder);
	$traverser->traverse(atkconfig('atkroot').'modules/');
	$classes = $classfinder->getClasses();
	$this->p($classes);



	}
	*/
	/*	function action_testgmail(& $handler) {


	require (atkconfig("atkroot") . "modules/include/libgmailer.php");


	$gm = new GMailer();
	$name="guy.gourmellet";
	$pwd="al1913gg";
	$tz=0;

	$gm->setLoginInfo($name, $pwd, $tz);  // only required for connecting the first time,

	// e.g. in your login page

	// in other pages you can simply connect()

	if ($gm->connect()) {
	echo 'Connecté';


	$gm->fetchBox(GM_LABEL, "my_label", 0);  // name of constants can be found in libgmailer.php

	$snapshot = $gm->getSnapshot(GM_LABEL);

	if ($snapshot) {

	echo "Total # of conversations of my_label = " . $snapshot->box_total;



	}

	// $gm->disconnect() only when you really want to logout

	}
	$this->p($this->return_status);
	die();
	}

	*/
	// action_intro_TU_Authors
	function action_intro_TU_Authors(& $handler)
	{
		$base_itis = & atkGetDb('itis');
		$base_itis_update = & atkGetDb('itis');
		$datedebut=gmdate('c');
		$i=0;
		$sql="SELECT id_auteur, shortauthor
		FROM biodiversite_author 
";

		$rows=$base_itis->getrows($sql);
		for ($i = 0; $i < count($rows); $i++) {
			$lb_auteur=$rows[$i]["shortauthor"];
			$lb_auteur=str_replace(')','',$lb_auteur) ;
			$lb_auteur=str_replace('(','',$lb_auteur) ;
			$lb_auteur=str_replace(',','',$lb_auteur) ;
			$lb_auteur=str_replace("'","\'",$lb_auteur);
			$lb_auteur=trim($lb_auteur) ;
			$auteur_an=substr($lb_auteur,strlen($lb_auteur)-4,4) ;
			if (is_numeric($auteur_an))
			{

				$auteur=trim(substr($lb_auteur,0, strlen($lb_auteur)-4) );
			}
			$sqlupdate="UPDATE biodiversite_author
		set auteur='".$auteur."' , auteur_an='".$auteur_an."'
		 WHERE id_auteur='".$rows[$i]["tsn"]."'";
			echo $sqlupdate;
			die();
			 
			$base_itis_update->query($sqlupdate);
		}


		echo "terminé<br />";
		echo $datedebut." : début<br />";
		echo $i." : nombre<br />";
		echo gmdate('c')." : fin<br />";
		die();
	}


	// Recherche les données INPN pour fusion avec itis
	function action_intro_TU_INPN(& $handler)
//	function action_intro(& $handler)
	{
		$delimiter='	';
		$enclosure='';
		$session=0;
		$total=0;
		$sousespece=false;
		$liste="";
		$debut=gmdate('c');
		$db = & atkGetDb('itis');
		$lignenumber=0;
		$datetest="";
		//		echo 'debut : '.memory_get_usage(true).'<br />' ;

			
		$file=atkconfig("atkroot") . "atktmp/TAXREF_INPN_ESPECES_022008.txt";

			
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{
			$lignenumber+=1;
			if(trim($line)=="")
			continue;
			//large import are a problem for the maximum execution time, so we want to set for each
			//loop of the for-loop an maximum execution time
			set_time_limit(3600);
			//			atkdebug('set_time_limit(0)');

			if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);

			$initial_values["id_parent"]=null;
			$initial_values["nom_binomial"]=null;
			$initial_values["nom_francais"]=null;
			$initial_values["nom_anglais"]=null;
			$initial_values["id_rang_taxinomique"]=null;
			$initial_values["auteur"]=null;
			$initial_values["auteur_an"]=null;
			$initial_values["id_statut_france_metropole"]=null;
			$initial_values["id_statut_martinique"]=null;
			$initial_values["id_statut_guadeloupe"]=null;
			$initial_values["id_statut_st_martin_st_barthelemy"]=null;
			$initial_values["id_statut_guyane_francaise"]=null;
			$initial_values["id_statut_st_pierre_et_miquelon"]=null;
			$initial_values["id_statut_reunion"]=null;
			$initial_values["id_statut_mayotte"]=null;
			$initial_values["id_statut_terres_australes_et_antartiques_francaises"]=null;
			$initial_values["id_taxon_inventaire_patrimoine_naturel"]=null;
			$initial_values["id_taxon_reference"]=null;
			$initial_values["id_taxon_fauna_europaea"]=null;
			$initial_values["id_taxon_conservation_nature"]=null;
			$initial_values["id_taxon_marine_species"]=null;
			$initial_values["id_taxon_kerguelen"]=null;
			$initial_values["id_bock_kerguelen"]=null;
			$initial_values["etymologie"]=null;
			$initial_values["commentaire"]=null;
			$initial_values["id_creation"]='1';
			$initial_values["date_creation"]='2009-05-25';
			$initial_values["id_modification"]='1';
			$initial_values["date_modification"]='2009-05-25';


			//       atkimport("atk.utils.atkstringparser");

			$prev_regne=$regne;
			$prev_phylum=$phylum;
			$prev_classe=$classe;
			$prev_ordre=$ordre;
			$prev_famille=$famille;

			$regne=$dataligne[0];
			$phylum=$dataligne[1];
			$classe=$dataligne[2];
			$ordre=$dataligne[3];
			$famille=$dataligne[4];
			$cd_nom=$dataligne[5];
			$lb_nom=$dataligne[6];
			$lb_auteur=$dataligne[7];
			$nom_complet=$dataligne[8];
			$cd_ref=$dataligne[9];
			$nom_valide=$dataligne[10];
			$rang=$dataligne[11];
			$nom_vern=$dataligne[12];
			$nom_vern_eng=$dataligne[13];
			$fr=$dataligne[14];
			$mar=$dataligne[15];
			$gua=$dataligne[16];
			$smsb=$dataligne[17];
			$gf=$dataligne[18];
			$spm=$dataligne[19];
			$reu=$dataligne[20];
			$may=$dataligne[21];
			$taaf=$dataligne[22];
			$lb_nom=str_replace("'","\'",strtolower(trim($lb_nom)));
			$nom_vern=str_replace("'","\'",strtolower(trim($nom_vern)));
			$nom_vern_eng=str_replace("'","\'",strtolower(trim($nom_vern_eng)));
			$rec=array();
			$rec = $initial_values;
			$i=0;
			while ($i<9)
			{
				$statut=$dataligne[14+$i];
				$sql4="SELECT id from biodiversite_statut_taxinomique WHERE code_statut='$statut' ";
				$data = $db->getrows($sql4);
				$dataligne[14+$i]=$data[0]["id"];
				$i+=1;
			}
			$rec ["id_statut_france_metropole"]=$dataligne[14];
			$rec["id_statut_martinique"]=$dataligne[15];
			$rec["id_statut_guadeloupe"]=$dataligne[16];
			$rec["id_statut_st_martin_st_barthelemy"]=$dataligne[17];
			$rec["id_statut_guyane_francaise"]=$dataligne[18];
			$rec["id_statut_st_pierre_et_miquelon"]=$dataligne[19];
			$rec["id_statut_reunion"]=$dataligne[20];
			$rec["id_statut_mayotte"]=$dataligne[21];
			$rec["id_statut_terres_australes_et_antartiques_francaises"]=$dataligne[22];

			$rec["nom_binomial"]=$lb_nom;
			$rec["nom_francais"]=$nom_vern;
			$rec["nom_anglais"]=$nom_vern_eng;
			$rec["id_taxon_inventaire_patrimoine_naturel"]=$cd_nom;
			$rec["id_taxon_reference"]=$cd_ref;


			if 	($rec["nom_francais"]!=	"" && $rec["nom_anglais"]!="")
			{
				$sqlnom="nom_francais='".$rec["nom_francais"]."',
	 nom_anglais='".$rec["nom_anglais"]."',";
			}
				
			else if 	($rec["nom_francais"]==	"" && $rec["nom_anglais"]=="")
			{
				$sqlnom="";
			}
			else if	($rec["nom_francais"]!=	"" )
			{
				$sqlnom="nom_francais='".$rec["nom_francais"]."',";
			}
			else if	($rec["nom_anglais"]!=	"" )
			{
				$sqlnom="nom_anglais='".$rec["nom_anglais"]."',";
			}

			// enregistrer
			$sql5="UPDATE biodiversite_taxinomie
				set  ".$sqlnom."
	 id_statut_france_metropole='".$rec["id_statut_france_metropole"]."',
	 id_statut_martinique='".$rec["id_statut_martinique"]."',
	 id_statut_guadeloupe='".$rec["id_statut_guadeloupe"]."',
	 id_statut_st_martin_st_barthelemy='".$rec["id_statut_st_martin_st_barthelemy"]."',
	 id_statut_guyane_francaise='".$rec["id_statut_guyane_francaise"]."',
	 id_statut_st_pierre_et_miquelon='".$rec["id_statut_st_pierre_et_miquelon"]."',
	 id_statut_reunion='".$rec["id_statut_reunion"]."',
	 id_statut_mayotte='".$rec["id_statut_mayotte"]."',
	 id_statut_terres_australes_et_antartiques_francaises='".$rec["id_statut_terres_australes_et_antartiques_francaises"]."',
	 id_taxon_inventaire_patrimoine_naturel='".$rec["id_taxon_inventaire_patrimoine_naturel"]."',
	 id_taxon_reference='".$rec["id_taxon_reference"]."',
	 commentaire='".$rec["commentaire"]."',
	 id_creation='".$rec["id_creation"]."',
	 date_creation='".$rec["date_creation"]."',
	 id_modification='".$rec["id_modification"]."',
	 date_modification='".$rec["date_modification"]."'
	 where nom_binomial='".$lb_nom."'
	";
			$sql="SELECT id_taxinomie from biodiversite_taxinomie where nom_binomial='".$lb_nom."'	";
			$data=$db->getrows($sql);
			if (count($data)==0)
			{
				echo $sql5.'<br />';
				echo 'non présent dans la base ITIS';
				die();
			}
			$db->query($sql5);
			$total+=1;
		}

		echo $debut.'<br />';
		echo "total insertions : ".$total.'<br />';
		echo "total lignes : ".$lignenumber.'<br />';
		echo $datetest.'<br />';
		echo gmdate('c');
		die();
	}

	// traitement taxonomic_units :récupère les noms anglais et francais de vernaculars 
	function action_intro_TU_Vernaculars(& $handler)
	{
		$base_itis = & atkGetDb('itis');
		$base_itis_update = & atkGetDb('itis');
		$datedebut=gmdate('c');
		$i=0;
		$sql="SELECT tsn, vernacular_name
		FROM vernaculars 
		 WHERE 
		 language='French'
";
		$rows=$base_itis->getrows($sql);
		for ($i = 0; $i < count($rows); $i++) {
		 $record = $rows[$i];
		 $sqlupdate="UPDATE biodiversite_taxinomie
		set nom_francais='".str_replace("'","\'",strtolower(trim($record["vernacular_name"])))."' 
		 WHERE id_taxinomie='".$record["tsn"]."'";
		 $base_itis_update->query($sqlupdate);
		}
		$sql="SELECT tsn, vernacular_name
		FROM vernaculars 
		 WHERE 
		 ( language='English' or language='unspecified')
		 order by tsn, approved_ind
";
		$rows=$base_itis->getrows($sql);
		for ($i = 0; $i < count($rows); $i++) {
		 $record = $rows[$i];
		 $sqlupdate="UPDATE biodiversite_taxinomie
		set nom_anglais='".str_replace("'","\'",strtolower(trim($record["vernacular_name"])))."' 
		 WHERE id_taxinomie='".$record["tsn"]."'";
		 $base_itis_update->query($sqlupdate);
		}


		echo "terminé<br />";
		echo $datedebut." : début<br />";
		echo $i." : nombre<br />";
		echo gmdate('c')." : fin<br />";
		die();
	}

	// traitement taxonomic_units :récupère les noms longs de longnames 
	function action_intro_TU1(& $handler)
	{

		$base_itis = & atkGetDb('itis');
		$base_itis_update = & atkGetDb('itis');
		$datedebut=gmdate('c');
		$i=0;
		$sql="SELECT id_taxinomie as id, completename as nom_binomial
		FROM biodiversite_taxinomie ,
		 longnames l
		 WHERE 
		 biodiversite_taxinomie.id_taxinomie=l.tsn
";
		$rows=$base_itis->getrows($sql);
		for ($i = 0; $i < count($rows); $i++) {
		 $record = $rows[$i];
		 $sqlupdate="UPDATE biodiversite_taxinomie
		set nom_binomial='".str_replace("'","\'",strtolower(trim($record["nom_binomial"])))."' 
		 WHERE id_taxinomie='".$record["id"]."'";
		 $base_itis_update->query($sqlupdate);
		}
		$lb_auteur=str_replace("'","''",$lb_auteur);
		echo "terminé<br />";
		echo $datedebut." : début<br />";
		echo $i." : nombre<br />";
		echo gmdate('c')." : fin<br />";
		die();
	}
	//	Importation des taxons UICN
	function action_intro_UICN(& $handler)
	{
		$delimiter='	';
		$enclosure='';

		$db = & atkGetDb();
			
		$file=atkconfig("atkroot") . "atktmp/UICN_2006.csv";
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{
			if(trim($line)=="")
			continue;
			set_time_limit(0);
			atkdebug('set_time_limit(0)');

			//		if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);
			$uicn=$dataligne[0];
			$cd_nom=$dataligne[1];


			$sql1="UPDATE biodiversite_taxinomie set id_taxon_conservation_nature='".$uicn."' where id_taxon_inventaire_patrimoine_naturel='".$cd_nom."' ";

			$db->query($sql1);

		}
	}
function action_intro(& $handler)
// Rectification des indemnités kilométriques sur 2008 0.521 -> 0.288
{
	// Lire individu_activite où montant_indemnité =0.521
	$sql="SELECT id, id_ecriture_frais, nombre_kilometres
	from individu_activite
	where montant_indemnite_kilometre=0.521 and  nombre_kilometres is not null and not nombre_kilometres=0";
	$db = & atkGetDb();
	$rows=$db->getrows($sql);
	for ($i = 0; $i < count($rows); $i++)
	{
		$id=$rows[$i]["id"];
		$id_ecriture_frais=$rows[$i]["id_ecriture_frais"];
		$nombre_kilometres=$rows[$i]["nombre_kilometres"];
		$montant_indemnite_kilometre=0.288;
		$creditdebit=$nombre_kilometres*$montant_indemnite_kilometre;

		$sql2="UPDATE organisme_ligne_ecriture_comptable set credit=$creditdebit where id_ecriture=$id_ecriture_frais and id_compte='177'";
		$db->query($sql2);
		$sql2="UPDATE organisme_ligne_ecriture_comptable set debit=$creditdebit where id_ecriture=$id_ecriture_frais and id_compte='1850'";
		$db->query($sql2);
				$sql1="UPDATE individu_activite set montant_indemnite_kilometre=0.288 where id=$id";
		$db->query($sql1);
	}
	echo 'terminé : '.$i;
	die();
	
}
	//	Importation des taxons Kerguélen
//	function action_intro(& $handler)
		function action_intro_KERG(& $handler)
	{
		$delimiter='	';
		$enclosure='';
		$nombre=0;
		$db = & atkGetDb();
			
		$file=atkconfig("atkroot") . "atktmp/TAXREF_INPN_KERG.txt";
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{
			if(trim($line)=="")
			continue;
			set_time_limit(0);
			atkdebug('set_time_limit(0)');

			//		if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);
			$cd_nom=$dataligne[0];
			$bockkerg=$dataligne[1];
			$kerg=$dataligne[2];

			$sql1="UPDATE biodiversite_taxinomie set id_bock_kerguelen='".$bockkerg."', id_taxon_kerguelen='".$kerg."' where id_taxon_inventaire_patrimoine_naturel='".$cd_nom."' ";

			$db->query($sql1);

				$nombre+=1;

		}
		echo 'Terminé. Nombre = '.$nombre;
		die();
	}

	//	Importation des taxons ERMS
	function action_intro_ERMS(& $handler)
//		function action_intro(& $handler)
	{
		$delimiter='	';
		$enclosure='';

		$db = & atkGetDb();
			
		$file=atkconfig("atkroot") . "atktmp/TAXREF_INPN_ERMS.txt";
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		$nombre=0;
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{
			if(trim($line)=="")
			continue;
			set_time_limit(0);
			atkdebug('set_time_limit(0)');

			//		if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);
			$cd_nom=$dataligne[0];
			$erms=$dataligne[1];
			$sql1="UPDATE biodiversite_taxinomie set id_taxon_marine_species='".$erms."' where id_taxon_inventaire_patrimoine_naturel='".$cd_nom."' ";

			$db->query($sql1);
			$nombre+=1;

		}
		echo 'Terminé. Nombre = '.$nombre;
		die();
		
	}

	//	Importation des taxons européens
	function action_intro_fauna_europaea(& $handler)
	{
		$delimiter='	';
		$enclosure='';

		$db = & atkGetDb();
			
		$file=atkconfig("atkroot") . "atktmp/TAXREF_INPN_FAEU.txt";
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{
			if(trim($line)=="")
			continue;
			set_time_limit(0);
			atkdebug('set_time_limit(0)');

			//			if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);
			$cd_nom=$dataligne[0];
			$faeu=$dataligne[1];
			$sql1="UPDATE biodiversite_taxinomie set id_taxon_fauna_europaea='".$faeu."' where id_taxon_inventaire_patrimoine_naturel='".$cd_nom."' ";

			$db->query($sql1);

		}
	}


	// importation base espèces de inpn
 function action_intro_INPN(& $handler)
//		function action_intro(& $handler)
	{
		$delimiter='	';
		$enclosure='';
		$session=0;
		$total=0;
		$sousespece=false;
		$liste="";
		$debut=gmdate('c');
		$db = & atkGetDb();
		$lignenumber=0;
		$datetest="";
		//		echo 'debut : '.memory_get_usage(true).'<br />' ;

			
		$file=atkconfig("atkroot") . "atktmp/TAXREF_INPN_ESPECES_022008.txt";

			
		$fp = fopen($file, "r");
		// ligne titre
		$line = fgets($fp);
		for($line = fgets($fp),$counter=1; $line!==false; $line = fgets($fp),$counter++)
		{

			$lignenumber+=1;
			//			$datetest.='lecture ligne'.	gmdate('c').'<br />';
			//			atkdebug("Validating record nr. $counter");
			//if we have an empty line, pass it
			if(trim($line)=="")
			continue;

			//large import are a problem for the maximum execution time, so we want to set for each
			//loop of the for-loop an maximum execution time
			set_time_limit(3600);
			//			atkdebug('set_time_limit(0)');

			if (atktext('charset') != '' && function_exists("mb_convert_encoding")) $line = mb_convert_encoding($line, atktext('charset'));
			$dataligne = $this->fgetcsvfromline($line, $columncount, $delimiter, $enclosure);

			$initial_values["id_parent"]=null;
			$initial_values["nom_binomial"]=null;
			$initial_values["nom_francais"]=null;
			$initial_values["nom_anglais"]=null;
			$initial_values["id_rang_taxinomique"]=null;
			$initial_values["auteur"]=null;
			$initial_values["auteur_an"]=null;
			$initial_values["id_statut_france_metropole"]=null;
			$initial_values["id_statut_martinique"]=null;
			$initial_values["id_statut_guadeloupe"]=null;
			$initial_values["id_statut_st_martin_st_barthelemy"]=null;
			$initial_values["id_statut_guyane_francaise"]=null;
			$initial_values["id_statut_st_pierre_et_miquelon"]=null;
			$initial_values["id_statut_reunion"]=null;
			$initial_values["id_statut_mayotte"]=null;
			$initial_values["id_statut_terres_australes_et_antartiques_francaises"]=null;
			$initial_values["id_taxon_inventaire_patrimoine_naturel"]=null;
			$initial_values["id_taxon_reference"]=null;
			$initial_values["id_taxon_fauna_europaea"]=null;
			$initial_values["id_taxon_conservation_nature"]=null;
			$initial_values["id_taxon_marine_species"]=null;
			$initial_values["id_taxon_kerguelen"]=null;
			$initial_values["id_bock_kerguelen"]=null;
			$initial_values["etymologie"]=null;
			$initial_values["commentaire"]=null;
			$initial_values["id_creation"]='1';
			$initial_values["date_creation"]='2009-05-25';
			$initial_values["id_modification"]='1';
			$initial_values["date_modification"]='2009-05-25';


			//       atkimport("atk.utils.atkstringparser");

			$prev_regne=$regne;
			$prev_phylum=$phylum;
			$prev_classe=$classe;
			$prev_ordre=$ordre;
			$prev_famille=$famille;

			$regne=$dataligne[0];
			$phylum=$dataligne[1];
			$classe=$dataligne[2];
			$ordre=$dataligne[3];
			$famille=$dataligne[4];
			$cd_nom=$dataligne[5];
			$lb_nom=$dataligne[6];
			$lb_auteur=$dataligne[7];
			$nom_complet=$dataligne[8];
			$cd_ref=$dataligne[9];
			$nom_valide=$dataligne[10];
			$rang=$dataligne[11];
			$nom_vern=$dataligne[12];
			$nom_vern_eng=$dataligne[13];
			$fr=$dataligne[14];
			$mar=$dataligne[15];
			$gua=$dataligne[16];
			$smsb=$dataligne[17];
			$gf=$dataligne[18];
			$spm=$dataligne[19];
			$reu=$dataligne[20];
			$may=$dataligne[21];
			$taaf=$dataligne[22];
			$lb_nom=str_replace("'","''",$lb_nom);
			$nom_vern=str_replace("'","''",$nom_vern);
			$nom_vern_eng=str_replace("'","''",$nom_vern_eng);
			if ($rang=='SSES' )
			{
				if ($sousespece==false)
				{
					$sql0="SELECT LAST_INSERT_ID() as lastid from biodiversite_taxinomie ";
					$data = $db->getrows($sql0);
					$lastid=$data[0]["lastid"];
				}
				$sousespece=true;
				$initial_values["id_parent"]=$lastid;
				$rec=array();
				$rec = $initial_values;
			}
			else

			{
				$sousespece=false;
				$rec=array();
				$rec = $initial_values;

				$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$regne' and id_rang_taxinomique='17'";

				$data = $db->getrows($sql1);
				if (isset($data[0]["id"]))
				{
					$rec["id_parent"]=$data[0]["id"];
				}
				else
				{
					$sql2="INSERT INTO biodiversite_taxinomie
	( id_parent, nom_binomial, id_rang_taxinomique,id_creation, date_creation, id_modification, date_modification  )
	VALUES
	(NULL, '$regne', '17','".$rec["id_creation"]."', '".$rec["date_creation"]."','".$rec["id_modification"]."','".$rec["date_modification"]."')
	";	
					$session+=1;
					$db->query($sql2);
					//			echo 'insert regne : '.memory_get_usage(true).'<br />' ;
					$data = $db->getrows($sql1);
					$rec["id_parent"]=$data[0]["id"];

				}
				$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$phylum' and id_rang_taxinomique='23'";
				$data = $db->getrows($sql1);
				if (isset($data[0]["id"]))
				{
					$rec["id_parent"]=$data[0]["id"];
				}
				else
				{
					$sql2="INSERT INTO biodiversite_taxinomie
	( id_parent, nom_binomial, id_rang_taxinomique,id_creation, date_creation, id_modification, date_modification  )
	VALUES
	(".$rec["id_parent"].", '$phylum', '23','".$rec["id_creation"]."', '".$rec["date_creation"]."','".$rec["id_modification"]."','".$rec["date_modification"]."')
	";	
					$session+=1;
					$db->query($sql2);
					//	echo 'insert phylum : '.memory_get_usage(true).'<br />' ;
					$data = $db->getrows($sql1);
					$rec["id_parent"]=$data[0]["id"];
				}
				$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$classe' and id_rang_taxinomique='2'";
				$data = $db->getrows($sql1);
				if (isset($data[0]["id"]))
				{
					$rec["id_parent"]=$data[0]["id"];
				}
				else
				{
					$sql2="INSERT INTO biodiversite_taxinomie
	( id_parent, nom_binomial, id_rang_taxinomique,id_creation, date_creation, id_modification, date_modification  )
	VALUES
	(".$rec["id_parent"].", '$classe', '2','".$rec["id_creation"]."', '".$rec["date_creation"]."','".$rec["id_modification"]."','".$rec["date_modification"]."')
	";	
					$session+=1;
					$db->query($sql2);
					//	echo 'insert classe : '.memory_get_usage(true).'<br />' ;
					$data = $db->getrows($sql1);
					$rec["id_parent"]=$data[0]["id"];
				}
				$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$ordre' and id_rang_taxinomique='22'";
				$data = $db->getrows($sql1);
				if (isset($data[0]["id"]))
				{
					$rec["id_parent"]=$data[0]["id"];
				}
				else
				{
					$sql2="INSERT INTO biodiversite_taxinomie
	( id_parent, nom_binomial, id_rang_taxinomique,id_creation, date_creation, id_modification, date_modification  )
	VALUES
	(".$rec["id_parent"].", '$ordre', '22','".$rec["id_creation"]."', '".$rec["date_creation"]."','".$rec["id_modification"]."','".$rec["date_modification"]."')
	";	
					$session+=1;
					$db->query($sql2);
					//	echo 'insert ordre : '.memory_get_usage(true).'<br />' ;
					$data = $db->getrows($sql1);
					$rec["id_parent"]=$data[0]["id"];
				}


				$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$famille' and id_rang_taxinomique='9'";
				$data = $db->getrows($sql1);
				if (isset($data[0]["id"]))
				{
					$rec["id_parent"]=$data[0]["id"];
				}
				else
				{
					$sql2="INSERT INTO biodiversite_taxinomie
	( id_parent, nom_binomial, id_rang_taxinomique,id_creation, date_creation, id_modification, date_modification  )
	VALUES
	(".$rec["id_parent"].", '$famille', '9','".$rec["id_creation"]."', '".$rec["date_creation"]."','".$rec["id_modification"]."','".$rec["date_modification"]."')
	";	

					$db->query($sql2);
					//	echo 'insert famille : '.memory_get_usage(true).'<br />' ;
					$session+=1;
					$data = $db->getrows($sql1);
					$rec["id_parent"]=$data[0]["id"];
				}

			}

			$sql3="SELECT id from biodiversite_rang_taxinomique WHERE rang_inpn='$rang' ";
			$data = $db->getrows($sql3);
			$rec["id_rang_taxinomique"]=$data[0]["id"];

			$sql1="SELECT id from biodiversite_taxinomie where nom_binomial='$lb_nom' and id_rang_taxinomique='".$rec["id_rang_taxinomique"]."'";
			$data = $db->getrows($sql1);
			if (isset($data[0]["id"]))
			{
				/*	$session+=1;
				 $liste.='<br />'.$sql1.'  id : '.$data[0]["id"];
				 if ($session>20)
				 {
				 $total+=$session;
				 $session=0;
				 echo $debut.'<br />';

				 echo "total isset data : ".$total.'<br />';
				 echo $liste;
				 echo gmdate('c');
				 die();

				 }
				 */
			}
			else
			{
				$i=0;
				while ($i<9)
				{
					$statut=$dataligne[14+$i];
					$sql4="SELECT id from biodiversite_statut_taxinomique WHERE code_statut='$statut' ";
					$data = $db->getrows($sql4);
					$dataligne[14+$i]=$data[0]["id"];
					$i+=1;
				}
				$rec ["id_statut_france_metropole"]=$dataligne[14];
				$rec["id_statut_martinique"]=$dataligne[15];
				$rec["id_statut_guadeloupe"]=$dataligne[16];
				$rec["id_statut_st_martin_st_barthelemy"]=$dataligne[17];
				$rec["id_statut_guyane_francaise"]=$dataligne[18];
				$rec["id_statut_st_pierre_et_miquelon"]=$dataligne[19];
				$rec["id_statut_reunion"]=$dataligne[20];
				$rec["id_statut_mayotte"]=$dataligne[21];
				$rec["id_statut_terres_australes_et_antartiques_francaises"]=$dataligne[22];

				$rec["nom_binomial"]=$lb_nom;
				$rec["nom_francais"]=$nom_vern;
				$rec["nom_anglais"]=$nom_vern_eng;
				$rec["id_taxon_inventaire_patrimoine_naturel"]=$cd_nom;
				$rec["id_taxon_reference"]=$cd_ref;

				if (isset($lb_auteur))
				{
					$lb_auteur=str_replace(')','',$lb_auteur) ;
					$lb_auteur=str_replace('(','',$lb_auteur) ;
					$lb_auteur=str_replace(',','',$lb_auteur) ;
					$lb_auteur=str_replace("'","''",$lb_auteur);
					$lb_auteur=trim($lb_auteur) ;
					$auteur_an=substr($lb_auteur,strlen($lb_auteur)-4,4) ;
					if (is_numeric($auteur_an))
					{
						$rec["auteur_an"]=$auteur_an;
						$rec["auteur"]=trim(substr($lb_auteur,0, strlen($lb_auteur)-4) );
					}
					else
					{
						$rec["auteur"]=$lb_auteur;
					}

				}

				// enregistrer
				$sql5="INSERT INTO biodiversite_taxinomie
	( id_parent,
	 nom_binomial,
	 nom_francais,
	 nom_anglais,
	 id_rang_taxinomique,
	 auteur,
	 auteur_an,
	 id_statut_france_metropole,
	 id_statut_martinique,
	 id_statut_guadeloupe,
	 id_statut_st_martin_st_barthelemy,
	 id_statut_guyane_francaise,
	 id_statut_st_pierre_et_miquelon,
	 id_statut_reunion,
	 id_statut_mayotte,
	 id_statut_terres_australes_et_antartiques_francaises,
	 
	 id_taxon_inventaire_patrimoine_naturel,
	 id_taxon_reference,
	 
	 id_taxon_fauna_europaea,
	 id_taxon_conservation_nature,
	 id_taxon_marine_species,
	 id_taxon_kerguelen,
	 id_bock_kerguelen,
	 etymologie,
	 
	 commentaire,
	 id_creation,
	 date_creation,
	 id_modification,
	 date_modification
	
			  )
	VALUES
	('".$rec["id_parent"]."',
	'".$rec["nom_binomial"]."',
	'".$rec["nom_francais"]."',
	'".$rec["nom_anglais"]."',
	'".$rec["id_rang_taxinomique"]."',
	'".$rec["auteur"]."',
	'".$rec["auteur_an"]."',
	'".$rec["id_statut_france_metropole"]."',
	'".$rec["id_statut_martinique"]."',
	'".$rec["id_statut_guadeloupe"]."',
	'".$rec["id_statut_st_martin_st_barthelemy"]."',
	'".$rec["id_statut_guyane_francaise"]."',
	'".$rec["id_statut_st_pierre_et_miquelon"]."',
	'".$rec["id_statut_reunion"]."',
	'".$rec["id_statut_mayotte"]."',
	'".$rec["id_statut_terres_australes_et_antartiques_francaises"]."',
	'".$rec["id_taxon_inventaire_patrimoine_naturel"]."',
	'".$rec["id_taxon_reference"]."',
	'".$rec["id_taxon_fauna_europaea"]."',
	'".$rec["id_taxon_conservation_nature"]."',
	'".$rec["id_taxon_marine_species"]."',
	'".$rec["id_taxon_kerguelen"]."',
	'".$rec["id_bock_kerguelen"]."',
	'".$rec["etymologie"]."',
	'".$rec["commentaire"]."',
	'".$rec["id_creation"]."',
	'".$rec["date_creation"]."',
	'".$rec["id_modification"]."',
	'".$rec["date_modification"]."')
	";
				$sql5=str_replace("''","NULL",$sql5);
				//				$db->disconnect();
				//		$db = & atkGetDb();
				$db->query($sql5);
				$data= array();

				/*			echo 'insert espèce : '.memory_get_usage(true).'<br />' 

				$datetest.='après insertion'.	gmdate('c').'<br />';
				$datetest.=count($data).'<br />';
				*/
				$session+=1;
				if ($session>100000)
				{
				 $total+=$session;
				 $session=0;
				 echo $debut.'<br />';
				 echo "total insertions : ".$total.'<br />';
				 echo "total lignes : ".$lignenumber.'<br />';
				 echo $datetest.'<br />';
				 echo gmdate('c');
				 die();

				}
					



			}
		}

	}

	function fgetcsvfromline ($line, $columncount, $delimiterChar = ',', $enclosureChar = '"')
	{
		$line = trim($line);

		if (substr($line, -1) == $delimiterChar)
		$line .= $enclosureChar.$enclosureChar;

		if ($enclosureChar!='')
		{
			$start = (($line[0]==$enclosureChar)?1:0);
			$end = (($line[strlen($line)-1]==$enclosureChar)?-1:NULL);
			$line = substr($line, $start, $end);
		}

		$regExpSpecialChars = array
		(
          "|" => "\\|",
          "&" => "\\&",
          "$" => "\\$",
          "(" => "\\(",
          ")" => "\\)",
          "^" => "\\^",
          "[" => "\\[",
          "]" => "\\]",
          "{" => "\\{",
          "}" => "\\}",
          "." => "\\.",
          "*" => "\\*",
          "\\" => "\\\\",
          "/" => "\\/"
          );

          $delimiterChar = strtr($delimiterChar, $regExpSpecialChars);
          $enclosureChar = strtr($enclosureChar, $regExpSpecialChars);

          // if we haven't got an enclosure char, the only thing we can do is
          // splitting it using the delimiterChar - no further action needed
          if (!$enclosureChar)
          {
          	return explode($delimiterChar,$line);
          }

          // Some exports don't enclose empty or numeric fields with the enclosureChar. Let's fix
          // that first so we can use one preg_split statement that works in those cases too.
          // loop until all occurrences are replaced. Contains an infinite loop prevention.
          for ($fix="", $i=0, $_i=substr_count($line, $enclosureChar); $fix!=$line && $i<$_i;$i++)
          {
          	if ($fix!="") $line = $fix;
          	$fix = preg_replace('/'.$delimiterChar.'(\d*)'.$delimiterChar.'/',
          	$delimiterChar.$enclosureChar.'\\1'.$enclosureChar.$delimiterChar, $line);
          }
          // now split by delimiter
          $expression = '#'.$enclosureChar.' *'.$delimiterChar.' *'.$enclosureChar.'#';
          return preg_split($expression, $line);
	}

	/*
	 function action_intro(& $handler)
	 {
	 $db = & atkGetDb();
	 $sql='SELECT bs.id as id1, bcco.id as id2, bccf.id as id3
	 FROM biodiversite_species bs, biodiversite_classification_classique bcco, biodiversite_classification_classique bccf
	 WHERE bs.ordre = bcco.nom_francais
	 AND bcco.id_hierarchie =4
	 AND bs.famille = bccf.nom_francais
	 AND bccf.id_hierarchie =5
		';
		$data=$db->getrows($sql);
		foreach ($data as $dataunit) {
		$id=$dataunit["id1"];
		$id_ordre=$dataunit["id2"];
		$id_famille=$dataunit["id3"];
		$sql="update biodiversite_species set id_ordre=$id_ordre, id_famille=$id_famille where id=$id";
		$db->query($sql);
		}

		}
		*/
	/*
	 function action_intro(& $handler)
	 {
	 $res = array();
	 $expression="Frais";
	 $noeud="application.aide";
	 $node = &getNode($noeud);
	 $res[$noeud] = $this->recLinks($node ->searchDb($expression), $noeud);

	 $this->p($res);

	 }
	 */
	function recLinks($recordset, $nodetype)
	{
		$node = &getNode($nodetype);

		$res = array();

		for($i=0, $_i=count($recordset); $i<$_i; $i++)
		{
			$item["title"] = $node->descriptor($recordset[$i]);
			$item["url"] = dispatch_url($nodetype, "view", array("atkselector"=>$node->primaryKey($recordset[$i])), "dispatch.php");
			$res[] = $item;
		}

		return $res;
	}



	function setupScreen($title, $output, $nextaction = "", $params = array ()) {
		atkimport("atk.ui.atkui");
		$ui = & atkUI :: getInstance();
		$title = " Tests - " . $title;
		$form = '<div align="left"><b>' . $title . '</b><br><br>';
		$form .= '<form action="dispatch.php">' . session_form(SESSION_NEW) . '<input type="hidden" name="atknodetype" value="traitement.trimestriel">' . '<input type="hidden" name="atkaction" value="' . $nextaction . '">' . $output;
		if (count($params)) {
			foreach ($params as $key => $value) {
				$form .= '<input type="hidden" name="' . $key . '" value="' . $value . '">';
			}
		}
		if ($nextaction != "") {
			if ($nextaction == "achievostart") {
				$btn = "Start using Achievo";
			} else
			if ($nextaction == $this->m_action) {
				$btn = "Retry";
			} else {
				$btn = "Continuer";
			}
			$form .= '<br><br><input type="submit" value="' . $btn . '"><br><br>';
		}
		$form .= '</form></div>';
		$page = & atkPage :: getInstance();
		$theme = & atkTheme :: getInstance();
		$page->register_style($theme->stylePath("style.css"));
		$page->addContent($ui->renderBox(array (
			"content" => $form,
			"title" => $title
		)));
	}
	//This is are two little functions that I made to quickly debug my arrays
	//while making php scripts.  You can pass these things any variable (both
	//arrays and non arrays), and it will print out everything that is in it.
	//It will even print out embedded arrays, so if you have arrays in arrays
	//in arrays, it will print all that out in a consice enough format that you
	//will know exactly what is in that variable.
	//
	//You should get output with "key => val", which should look something like
	//the following:
	//
	// admin =>
	//         user           => 1
	//         screwball      => 2
	//         admin          => 4
	//         . . .
	// is    =>
	//         student worker => 1
	//         hacker         => 2
	//         nerd           => 4
	//         admin          => 8
	// . . .
	//
	//call it like the following (where $testVar is a variable of you choice)
	//
	//  print_array($testVar);
	//
	//if your array contains any html code, you may want to call it instead as:
	//
	//  print_array($testVar,"<xmp>","</xmp>");
	//
	//Should be very easy to throw in your code and use...hope you find it useful
	//            Scott Parish <sRparish@bigfoot.com> 1998/02/24
	function p($a, $btag = "", $etag = "") {
		if (is_array($a)) {
			printf("<table cellpadding=0 cellspacing=0 border='1'> ");
			while (list ($one, $two) = each($a)) {
				/*        printf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
				 "&nbsp;$btag=>$etag</td>".
				 "<td align=right>&nbsp;%s</td></tr>\n"
				 ,$this->sprint_array($two,$btag,$etag));
				 */
				printf("\n<tr valign=baseline><td>$btag$one$etag</td>" .				"<td align=right>&nbsp;%s</td></tr>\n", $this->sprint_array($two, $btag, $etag));
			}
			printf("</table>");
		} else {
			printf("%s%s%s", $btag, $a, $etag);
		}
		die();
	}
	function sprint_array($a, $btag = "", $etag = "") {
		if (is_array($a)) {
			$out = sprintf("<table cellpadding=0 cellspacing=0 border='1'>");
			while (list ($one, $two) = each($a)) {
				/*       $out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td><td>".
				 "&nbsp;$btag=>$etag</td>".
				 "<td align=right>&nbsp;%s</td></tr>\n"
				 ,$this->sprint_array($two,$btag,$etag));
				 */
				$out .= sprintf("\n<tr valign=baseline><td>$btag$one$etag</td>" .				"<td align=right>&nbsp;%s</td></tr>\n", $this->sprint_array($two, $btag, $etag));
			}
			$out .= "</table>";
			return $out;
		} else {
			return sprintf("%s%s%s", $btag, $a, $etag);
		}
	}

}
?>