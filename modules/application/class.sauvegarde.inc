<?php
atkimport("atk.assmetanode");

class sauvegarde extends assMetaNode
{
	var $table="app_sauvegarde";

	function meta(&$policy)
	{

		//$policy-> addFlags("libelle",AF_SEARCHABLE);
		$policy-> addFlags("commentaire",AF_HIDE_LIST);
		$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
		//$policy->setOrder("libelle");
	}
	function sauvegarde()
	{
		$this->atkMetaNode();
		$this->atkNode("sauvegarde", NF_MRA|NF_ADD_LINK|NF_COPY);
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"id_organisme",
"id_individu",
				"libelle",
				"type",
				"repertoire_source",
				"repertoire_destination",
				"nom_base",
				"serveur_base",
				"utilisateur_base",
				"mdp_base",
				"actif_o_n",


				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				), AF_NO_LABEL));
				$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
				$this->add(new atkManyToOneRelation("id_individu","individu.individu",AF_SEARCHABLE|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE));
				$this->add(new atkListAttribute("type", array( "fs","db","both")));

				$this->add(new atkAttribute("repertoire_source", AF_SEARCHABLE));
				$this->add(new atkAttribute("repertoire_destination", AF_SEARCHABLE));
				$this->add(new atkAttribute("nom_base", AF_SEARCHABLE));
				$this->add(new atkAttribute("serveur_base", AF_SEARCHABLE));
				$this->add(new atkAttribute("utilisateur_base", AF_SEARCHABLE));
				$this->add(new atkAttribute("mdp_base", AF_SEARCHABLE));
				$this->add(new atkAttribute("actif_o_n", AF_SEARCHABLE));
				$this->add(new atkBoolAttribute("actif_o_n",null));


				include_once(atkconfig("atkroot")."modules/include/association.inc");

				$this->setSecurityAlias("profil.profil");
				$this->m_securityMap["backupall"] = "view";

				global $ATK_VARS,$g_user;

				if ($ATK_VARS["atknodetype"]=="individu.sauvegarde"&& in_array($ATK_VARS["atkaction"],array("admin","add","update","edit")))
				{
					if  ($this->getView() == "active")
					{
						$this->addFilter("(date_fin IS NULL or date_fin='00-00-0000' )" );
					}

				}

				//$this->setIndex("libelle");
	}

	// GG deb



	function rowColor($record)
	{
		$actif_o_n=$record["actif_o_n"];
		if ($actif_o_n=="1")
		return $this->couleuractif;
	}

	function descriptor_def()
	{
		return "[libelle]";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$mraactions['delete'] = "delete";
		$mraactions['backupall'] = "backupall";
	}
	
	function adminFooter()
	{
		$retour=parent::adminfooter();
		$legende='Légende des couleurs : ';
		$legende.='<font color="'. $this->couleuractif.'"> <b> Sauvegarde active '.$retour;

		return $legende;


	}
	function action_backupall() {

		$db = & atkGetDb();
		$sql='SELECT libelle, type, repertoire_source, repertoire_destination,
		utilisateur_base , mdp_base, serveur_base, nom_base
		from app_sauvegarde where actif_o_n="1" ';
		$data = $db->getrows($sql);
		for ($i = 0, $_i = count($data); $i < $_i; $i++) {
			$repertoire_source=$data[$i]["repertoire_source"];
			$repertoire_destination=$data[$i]["repertoire_destination"];
			$utilisateur_base=$data[$i]["utilisateur_base"];
			$mdp_base=$data[$i]["mdp_base"];
			$serveur_base=$data[$i]["serveur_base"];
			$nom_base=$data[$i]["nom_base"];
			$libelle=$data[$i]["libelle"];
			$type=$data[$i]["type"];
			$output = shell_exec('whoami');
			echo '</br>whoami :' .$output;
			$output = shell_exec('cd '.$repertoire_source);
			sleep(3);
			$output = shell_exec('pwd');
			echo $libelle.'<br/>';
			if ($output.'/'!=$repertoire_source)
			{ echo '<br/>Arrêt. Répertoire source inexistant : '.$repertoire_source;
			echo '</br>out :' .$output
		;
			}
			$output = shell_exec('cd '.$repertoire_destination);
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination)
			{ echo '<br/>Création du répertoire destination : '.$repertoire_destination;
			$output = shell_exec('mkdir '.$repertoire_destination);
			}
			$output = shell_exec('cd '.$repertoire_destination);
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination)
			{ echo '<br/>Arrêt. Impossible de créer le répertoire destination inexistant : '.$repertoire_destination;
			}
			$output = shell_exec('cd '.$repertoire_destination.'1');
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination.'1')
			{ echo '<br/>Création du répertoire destination inexistant : '.$repertoire_source;
			$output = shell_exec('mkdir '.$repertoire_destination.'1');
			}
			$output = shell_exec('cd '.$repertoire_destination.'2');
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination.'2')
			{ echo '<br/>Création du répertoire destination inexistant : '.$repertoire_source;
			$output = shell_exec('mkdir '.$repertoire_destination.'2');
			}
			$output = shell_exec('cd '.$repertoire_destination.'3');
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination.'3')
			{ echo '<br/>Création du répertoire destination inexistant : '.$repertoire_source;
			$output = shell_exec('mkdir '.$repertoire_destination.'3');
			}
			$output = shell_exec('cd '.$repertoire_destination.'4');
			$output = shell_exec('pwd');
			if ($output!=$repertoire_destination.'4')
			{ echo '<br/>Création du répertoire destination inexistant : '.$repertoire_source;
			$output = shell_exec('mkdir '.$repertoire_destination.'4');
			}
			$suffix=gmdate('Y').gmdate('z');
			$repertoire_destination_1=$repertoire_destination.'1';
			$repertoire_destination_2=$repertoire_destination.'2';
			$repertoire_destination_3=$repertoire_destination.'3';
			$repertoire_destination_4=$repertoire_destination.'4';
$doy=gmdate('z');
			if ($type=='fs' || $type=='both')
			{	$output = shell_exec('tar -zcf '.$repertoire_destination_1.'/'.$suffix.'.site.wikistoma.org.tar.gz  '.$repertoire_source.' ');
			echo '<br/>'.$output;
			if ($doy%7=='0')
			{$suffix7=$suffix-7;
				$suffix8=$suffix-8;
				$suffix9=$suffix-9;
				$suffix10=$suffix-10;
				$suffix11=$suffix-11;
				$suffix12=$suffix-12;
				$suffix13=$suffix-13;
				$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix7.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix8.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix9.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix10.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix11.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix12.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');
			$output = shell_exec('rm'.$repertoire_destination_1.'/'.$suffix13.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_2.' ');}
			if ($doy%28=='0')
			{$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_3.' ');}
				if ($doy%365=='0')
			{$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.site.wikistoma.org.tar.gz  '.$repertoire_destination_4.' ');}

			}

			if ($type=='db' || $type=='both')
			{	
				$ordre='mysqldump --opt -u'.$utilisateur_base.' -p'.$mdp_base.' -h '.$serveur_base.' '. $nom_base .' >  '.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql';
				echo '<br/>'.$ordre;
//	die ();
				
				$output = shell_exec($ordre);
			echo '<br/>'.$output;
					die();
					
			$output = shell_exec('tar -zcf '.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.tar.gz '.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql ');
			echo '<br/>'.$output;
			$output = shell_exec( 'rm '.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql ');
			echo '<br/>'.$output;
			if ($doy%7=='0')
			{$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql  '.$repertoire_destination_2.' ');}
			if ($doy%28=='0')
			{$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql   '.$repertoire_destination_3.' ');}
		
			if ($doy%365=='0')
			{$output = shell_exec('mv'.$repertoire_destination_1.'/'.$suffix.'.db.'.$nom_base.'.sql  '.$repertoire_destination_4.' ');}
		
			}


			}
						
		}

	}
	?>