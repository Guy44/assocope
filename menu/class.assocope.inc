<?php
atkimport("atk.menu.atkframesmenu");
atkimport("atk.atktools");
include_once (atkconfig("atkroot") . "modules/include/fairetooltip.inc");
include_once (atkconfig("atkroot") . "atk/atkmenutools.inc");
class assocope extends atkPlainMenu {

	function getFooter($atkmenutop) {
		return "";
	}

	function render()
	{
		// 	$this->menuitem(string libelle_menu_item, "", "parent_menu", true);
		// string libelle_menu_item :  @libellé_pour_tootip@libelle_pour_libelle_menu#nombre
		// si @libellé_pour_tootip@ est absent c'est libelle_pour_libelle_menu qui est utilisé pour vaccès à tooltip
		//dans le fichier lng
		/*
		"menu_libelle_pour_libelle_menu"=>"contenu libellé menu",
		"menu_tooltip_libellé_pour_tootip"=>"contenu tooltip menu",
		"module_nomattribut_tooltip" => "contenu tooltip.",
		"wiki_module.node"=>"critère de recherche pour le wiki"
		'target_blank'
		'target_menu'
		début de name  ' / ' : pas de saut de ligne et insertion de ' | '
		début de name  '-/+' : pas de saut de ligne et insertion de "-|+"
		débute de name '!' : le nom n'est pas traduit  (on garde les _, ...)
		débute de name '%' : le nom est remplacé par rien en sortie
		*/

		global $ATK_VARS,$g_menu, $g_menu_parent;
		$atkmenutop = atkArrayNvl($ATK_VARS, "atkmenutop", "main");
		// GG LOg
		$node =$atkmenutop;
		/*
		 $action="menu";
		 $origine="menu.assocope";
		 atk_log_event($origine, $node, $action, $parametres, $selector, $error_message, null);
		 // GG FIN
		 */
		$page = &atknew("atk.ui.atkpage");
		$theme = &atkinstance("atk.ui.atktheme");
		$page->register_style($theme->stylePath("style.css"));
		$menu = " <div align='".atkconfig("menu_align", "left")."'>";
		$menu.=$this->getHeader($atkmenutop);

		if (is_array($g_menu[$atkmenutop]))
		{
			usort($g_menu[$atkmenutop],array("atkplainmenu","menu_cmp"));
			$menuitems = array();
			for ($i = 0; $i < count($g_menu[$atkmenutop]); $i++)
			{
				if ($i==count($g_menu[$atkmenutop])-1)
				{
					$delimiter = "";
				}
				else
				{
					$delimiter = atkconfig("menu_delimiter");
				}
				$name = $g_menu[$atkmenutop][$i]["name"];
				$menuitems[$i]["name"]=$name;
				$url = $g_menu[$atkmenutop][$i]["url"];
				$enable = $g_menu[$atkmenutop][$i]["enable"];
				$modname = $g_menu[$atkmenutop][$i]["module"];
				$translate = $g_menu[$atkmenutop][$i]["translation"];
				//				if ($name=="testguy" && $translate!="o") echo "trans = ".$translate; die();
				if (is_array($enable))
				{
					$enabled = false;
					for ($j=0;$j<(count($enable)/2);$j++)
					{
						$enabled |= is_allowed($enable[(2*$j)],$enable[(2*$j)+1]);
					}
					$enable = $enabled;
				}
				$menuitems[$i]["enable"]=$enable;
				$menuitems[$i]["url"]=$url;
				$menuitems[$i]['module']=$modname;
				$menuitems[$i]['translation']=$translate;
				/* delimiter ? */
				if ($name == "-") $menu .= $delimiter;
				else if ($enable) // don't show menu items we don't have access to.
				{
					$nombre="";


					if (substr($name,0,3)=='-/+')
					{$name=substr($name,3);
					$delimiter='<font color="Black"><b> -|+</b></font>';}
					if (substr($name,0,1)=='/')
					{$name=substr($name,1);
					$delimiter='<font color="Black"><b>|</b></font>';}

					if (stripos($name,'##')>0)
					{

						$nombre=substr($name,stripos($name,'##')+2);
						$name=substr($name,0,stripos($name,'##'));
						if ($nombre=='0')
						{ $nombre=" (".$nombre.")";}
						else
						{$nombre='<br /><font color="Coral"> <b>('.$nombre.')</b></font>';}

					}

					if (stripos($name,'#')>0)
					{

						$nombre=substr($name,stripos($name,'#')+1);
						$name=substr($name,0,stripos($name,'#'));
						if ($nombre=='0')
						{ $nombre=" (".$nombre.")";}
						else
						{$nombre='<font color="Coral"> <b>('.$nombre.')</b></font>';}

					}

					if (substr($name,0,1)=="@")
					{
						$texte=substr($name,stripos($name,'@',1)+1);

						$tip=substr($name,1,stripos($name,'@',1)-1);
						$ttip=atktext("menu_tooltip_".$tip);
						$name=$texte;
					}
					else if (substr($name,0,1)=="?")
					{
						$ttip=atktext("menu_tooltip_".substr($name,1));
					}
					else
					{
						$ttip=atktext("menu_tooltip_".$name);
					}
					$string=ucfirst(str_replace("_"," ",str_replace('title_','',"menu_tooltip_".$name)));
					if ($ttip!=$string)
					{
						$ttip=str_replace("'","\'",$ttip);
						$ttip=htmlentities($ttip,ENT_QUOTES);
						$menutip= fairetooltip($ttip) ;
					}
					//		$menutip='onmouseover="Tip(\''.$ttip.'\')" onmouseout="UnTip()"';}
					else
					{
						$menutip='';
					}

					$hassub = isset($g_menu[$g_menu[$atkmenutop][$i]["name"]]);
					/* submenu ? */
					if ($hassub)
					{
						if (empty($url)) // normal submenu
						{
							if (substr($name,0,1)=='!')
							{$name=substr($name,1);
							$menu .=$name.$delimiter;
							}
							else
							{$menu .= href('menu.php?atkmenutop='.$name,$this->getMenuTranslation($name, $modname),SESSION_NEW,false,$menutip ).$delimiter;
							}
						}
						else // submenu AND a default url.
						{
							$menuurl = session_url('menu.php?atkmenutop='.$name);
							$mainurl = session_url($url,SESSION_NEW);
							$menu.= '<a href="javascript:menuload(\''.$menuurl.'\', \''.$mainurl.'\');">'.$this->getMenuTranslation($name,$modname).$menutip.'</a>'.$delimiter;
						}
					}
					else // normal menuitem
					{
						if (empty($url) && substr($name,0,1)=='!')
						{ $name=substr($name,1);
						$menu .=$name.$delimiter;
						}
						else if (substr($name,0,1)=='?')
						{
							$name=substr($name,1);
							$menu .=href($url,$nombre,SESSION_NEW,false,$menutip.$target).$delimiter;
						}
						else
						{
							$target='target="main" ';
							if (substr($url,0,12)=='target_blank')
							{$target='target="_blank" ';
							$url=substr($url,12);
							$menu .= str_replace(';?atklevel=-1&atkprevlevel=0&','',href($url,$this->getMenuTranslation($name,$modname).$nombre,SESSION_NEW,false,$menutip.$target).$delimiter);}
							else if (substr($url,0,11)=='target_menu')
							{$target='target="menu" ';
							$url=substr($url,11);
							$menu .= str_replace(';?atklevel=-1&atkprevlevel=0&','',href($url,$this->getMenuTranslation($name,$modname).$nombre,SESSION_NEW,false,$menutip.$target).$delimiter);

							}
							else {
								$menu .=href($url,$this->getMenuTranslation($name,$modname).$nombre,SESSION_NEW,false,$menutip.$target).$delimiter;
							}
						}
					}
				}
			}
			// ajouter stats si administrateur
		}
		/* previous */
		if ($atkmenutop != "main")
		{
			$parent = $g_menu_parent[$atkmenutop];
		}
		$menu.=$this->getFooter($atkmenutop);
		$menu .= "</div>";
		$menustylepath = $theme->stylePath("menu.css");
		if (!empty($menustylepath)) $page->register_style($menustylepath);
		$page->register_script(atkconfig("atkroot")."atk/javascript/menuload.js");
		$ui = &atkinstance("atk.ui.atkui");
		$box = $ui->renderBox(array("title"=>$this->getMenuTranslation($atkmenutop,$modname),
                                               "content"=>$menu,
                                               "menuitems"=>$menuitems,
		),"menu");
		$page->addContent($box);
		$page->register_script(atkconfig("atkroot")."modules/development/javascript/framestart.js");
		return $page->render("Menu", true);
	}

	function getHeader($atkmenutop) {
		$user = getUser();
		$id = $user["id"];
		$db = & atkGetDb();
		$data = $db->getrows("SELECT id_individu from app_utilisateur where id=" . $id . " ");
		$id_individu = $data[0]["id_individu"];
		$node = new assmetanode();

		if (isset ($id) ) {
			if ($atkmenutop == "Individus") {
				$nomformulaire = 'individuselectorform';
				$typeentite = 'individu';
				$nomselection = 'selectedindividu';
				$url = "select aru.id_entite as entiteid, CONCAT_WS(' ',i.nom,i.prenom) as entitename
				from app_recent_use aru, individu i
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=i.id 
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("individu.individu","individu", $data[0]["id_entite"]);
			}
			if ($atkmenutop == "Organismes") {
				$nomformulaire = 'organismeselectorform';
				$typeentite = 'organisme';
				$nomselection = 'selectedorganisme';
				$url = "select aru.id_entite as entiteid, o.nom as entitename
				from app_recent_use aru, organisme o
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=o.id 
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("organisme.organisme","organisme", $data[0]["id_entite"]);

			}
			if ($atkmenutop == "Rencontres") {
				$nomformulaire = 'rencontreselectorform';
				$typeentite = 'rencontre';
				$nomselection = 'selectedrencontre';
				$url = "select aru.id_entite as entiteid,
				concat( ' (', o.nom,') du ', r.date_debut, ' à ', r.heure_debut,' ',  r.libelle) as entitename

				from app_recent_use aru, organisme_rencontre r, organisme o
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=r.id and r.id_organisme=o.id
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("organisme.rencontre","organisme_rencontre", $data[0]["id_entite"]);

			}
			if ($atkmenutop == "Comptes") {
				$nomformulaire = 'compteselectorform';
				$typeentite = 'compte';
				$nomselection = 'selectedcompte';
				$url = "select aru.id_entite as entiteid,
				concat( ' (', o.nom,')',' ', c.libelle,' (',c.code,')') as entitename

				from app_recent_use aru, organisme_compte c, organisme o
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=c.id and c.id_organisme=o.id
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("organisme.compte","organisme_compte", $data[0]["id_entite"]);

			}
			if ($atkmenutop == "Envois") {
				$nomformulaire = 'envoiselectorform';
				$typeentite = 'envoi';
				$nomselection = 'selectedenvoi';
				$url = "select aru.id_entite as entiteid,
				concat( e.objet,' (',i.nom ,' ',i.prenom,')') as entitename

				from app_recent_use aru, individu_envoi_groupe e, individu i
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=e.id 
									and e.id_utilisateur=i.id
						order by entitename";
			}
			if ($atkmenutop == "Langues") {
				$nomformulaire = 'langueselectorform';
				$typeentite = 'langue';
				$nomselection = 'selectedlangue';
				$url = "select aru.id_entite as entiteid,
				l.libelle_francais as entitename

				from app_recent_use aru, type_langue l
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=l.id 
								
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("table.type_langue","type_langue", $data[0]["id_entite"]);

			}
			if ($atkmenutop == "Taxons") {
				$nomformulaire = 'taxonselectorform';
				$typeentite = 'taxon';
				$nomselection = 'selectedtaxon';
				$url = "select aru.id_entite as entiteid,
				CONCAT_WS(' ',t.nom_binomial,'-',t.inpn_nom_complet,'-', t.nom_francais,'-', t.cd_nom,'/', t.cd_ref) as entitename
				from app_recent_use aru, biodiversite_taxinomie t
				where	 id_individu=$id_individu
				and type_entite='" . $typeentite . "'
						and aru.id_entite=t.id 
								
						order by entitename";
				$data = $db->getrows("select id, id_entite, date_recent_use from app_recent_use where
			id_individu=$id_individu and type_entite='$typeentite' order by date_recent_use desc");
				$operations=$node->table_operations ("biodiversite.taxinomie","biodiversite_taxinomie", $data[0]["id_entite"]);

			}
			if ($atkmenutop == "Rd") {
				$w3s_php_tut='<a href="http://www.w3schools.com/php/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/php-pg-icon.png" alt="Php tutorial" title="Php tutorial" ></img></a>'.'' ;
				$w3s_html_tut='<a href="http://www.w3schools.com/html/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Apps-HTML-5-Metro-icon.png" alt="Html tutorial" title="Html tutorial" target="_blank"></img></a>'.'' ;
				$w3s_css_tut='<a href="http://www.w3schools.com/css/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/css-3-icon.png" alt="Css tutorial" title="Css tutorial" target="_blank"></img></a>'.'' ;
				$w3s_js_tut='<a href="http://www.w3schools.com/js/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/javascript-icon.png" alt="Javascript tutorial" title="Javascript tutorial" target="_blank"></img></a>'.'' ;
				$w3s_sql_tut='<a href="http://www.w3schools.com/sql/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/mysql-icon.png" alt="Sql tutorial" title="Sql tutorial" target="_blank"></img></a>'.'' ;
				$w3s_ajax_tut='<a href="http://www.w3schools.com/ajax/default.asp" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/ajax-icon.png" alt="Ajax tutorial" title="Ajax tutorial" target="_blank"></img></a>'.'' ;
				$atk_wiki='<a href="http://www.atk-framework.com/wiki/ATK_Reference" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/wikipedia-icon.png" alt="Atk wiki" title="Atk wiki" target="_blank"></img></a>'.'' ;
				$atk_forum='<a href="http://forum.achievo.org/" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/achievo.png" alt="Atk forum" title="Atk forum" target="_blank"></img></a>'.'' ;
				//			$atk_framework='<a href="http://www.atk-framework.com/"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Groups-Meeting-Light-icon.png" alt="Atk forum" title="Atk forum" target="_blank"></img></a>'.'' ;
				$atk_framework='<a href="http://www.atk-framework.com/" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/atk.png" alt="AssoCope wiki" title="Atk framework" target="_blank"></img></a>'.'' ;
				$assocope_wiki='<a href="http://www.wikistoma.org/wiki/index.php?title=Accueil" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/assocope-wiki.png" alt="AssoCope wiki" title="AssoCope wiki (Guy mdpc)" target="_blank"></img></a>'.'' ;
				$media_wiki='<a href="http://www.mediawiki.org/wiki/MediaWiki" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Icon_Mediawiki_32px.png" alt="MediaWiki" title="MediaWiki" target="_blank"></img></a>'.'' ;
					
				$namebay='<a href="http://www.namebay.com/Default.aspx" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/logo-namebay.png" alt="Namebay domains IL90969|IL86482 mdpc" title="Namebay domains (IL90969|IL86482 mdpc)" target="_blank"></img></a>'.'' ;
				$dreamhost='<a href="https://panel.dreamhost.com/index.cgi" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/dreamhost.png" alt="Dreamhost guy.gourmellet@gmail.com mdpc" title="Dreamhost (guy.gourmellet@gmail.com mdpc)" target="_blank"></img></a>'.'' ;
				$google_code='<a href="https://code.google.com/intl/fr/" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/gd-logo.png" alt="Google code" title="Google code" target="_blank"></img></a>'.'' ;
				$google_script='<a href="https://developers.google.com/apps-script/overview" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google_script.png" alt="Google script" title="Google script" target="_blank"></img></a>'.'' ;
				$google_dashboard='<a href="https://www.google.com/dashboard/b/0/" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/Google-Plus-1-icon.png" alt="Google dashboard" title="Google dashboard (guy.gourmellet@gmail.com mdpl)" target="_blank"></img></a>'.'' ;
				$recordmydesktop='<a href="http://doc.ubuntu-fr.org/recordmydesktop" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/recordmydesktop.png" alt="RecordmyDesktop pour tuto video" title="RecordmyDesktop pour tuto video" target="_blank"></img></a>'.'' ;
				$shutter='<a href="http://doc.ubuntu-fr.org/shutter" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/shutter.png" alt="Shutter pour capture écrans" title="Shutter pour capture écrans" target="_blank"></img></a>'.'' ;
				$pma='<a href="http://www.wikiservas.net/dh_phpmyadmin/mysql.wikiservas.net/index.php" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/PMA.png" alt="PhpMyAdmin" title="PhpMyAdmin (webmaster rf9999)" target="_blank"></img></a>'.'' ;
				$mindomo='<a href="http://www.mindomo.com/fr/dashboard" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/mindomo.png" alt="Mindomo" title="Mindomo (Guy44 mdpc)" target="_blank"></img></a>'.'' ;
				$eclipse='<a href="http://www.eclipse.org/downloads/" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/eclipse.png" alt="Eclipse" title="Eclipse" target="_blank"></img></a>'.'' ;
				
					
				$descripteur="<b><center>Les bonnes adresses</center></b>".	
				$descripteur.='<br/>Internet<br/>' .$namebay.$dreamhost.$google_dashboard.$mindomo;
				$descripteur.="<br/>Langages<br/>".$w3s_php_tut.$w3s_html_tut.$w3s_css_tut.$w3s_ajax_tut.$w3s_js_tut.$w3s_sql_tut.$google_code.$eclipse;
				$descripteur.="<br/>MySql<br/>".$pma.$w3s_sql_tut.$google_script;
				$descripteur.="<br/>Atk<br/>".$atk_framework.$atk_wiki.$atk_forum;
				$descripteur.="<br/>Outils<br/>".$shutter.$recordmydesktop.$assocope_wiki.$media_wiki ;
				$descripteur_rd=$descripteur.'<br/>';
			}



			$atkmenutoptop=$this->getMenuTranslation($atkmenutop.'_top', $modname,$translate);
			$ttip=atktext("menu_tooltip_".$atkmenutop.'_top');
			$ttip=str_replace("'","\'",$ttip);
			$ttip=htmlentities($ttip,ENT_QUOTES);
			$menutip=fairetooltip($ttip) ;
			//			$menutip='onmouseover="Tip(\''.$ttip.'\')" onmouseout="UnTip()"';
			$texte="Menu ".ucfirst(strip_tags(strtolower($atkmenutoptop)));
			$texte=str_replace(' ', '_', $texte);
			$duree=$this->GetWikiPageAge($texte);
			if (empty($duree))
			{$aided='Aide';}
			else if ($duree<8)
			{		$aided='<span style="color:Red"><b>Aide</b></span>';	}
			else if ($duree<32)
			{		$aided='<span style="color:Orange"><b>Aide</b></span>';	}
			else
			{		$aided='<b>Aide</b>';	}

			$href=href(dispatch_url("search.search", "wiki",	array("title"=>$texte)),    $aided,	SESSION_NEW,	false, ' target="_blank"');
			$aide=$href.'</b>';


			$data = $db->getrows("SELECT count(id) as nombre from tmp_copier_coller  where id_utilisateur=$id");
			$titre="Le presse-papier AssoCope contient ".$data[0]["nombre"]." lignes";
			$href=href(dispatch_url("profil.copier_coller", "admin",	array (
			"atkfilter" => "tmp_copier_coller.id_utilisateur=$id",
			"atklimit" => "10000"
			)),    '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/presse_papier.png" alt="'.$titre.'" title="'.$titre.'" ></img>',	SESSION_NEW,	false,' target="_blank"');
			$presse_papier=$href.'</b><font color="Coral">(<b>'.$data[0]["nombre"].'</b>)</font>';

			global  $g_sessionManager;
			$g_Administrateur_o_n = $g_sessionManager->getValue("atgAdministrateur_o_n", "globals");
			$g_tracer_mysqldb_query_o_n = $g_sessionManager->getValue("tracer_mysqldb_query_o_n", "globals");
			$g_en_travaux_o_n = $g_sessionManager->getValue("en_travaux_o_n", "globals");
			$g_debug_o_n = $g_sessionManager->getValue("debug_o_n", "globals");
				
			//$g_debug_level = $g_sessionManager->getValue("debug_level", "globals");
			
			$affiche_travaux_en_cours="";
			if ($g_en_travaux_o_n=="1")
			{$titre="Attention des travaux sont en cours actuellement";
			$affiche_travaux_en_cours='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/travaux.png" alt="'.$titre.'" title="'.$titre.'" ></img>';}
			$etat_trace_mysqldb="";
			$etat_en_travaux="";
			if ($g_Administrateur_o_n=='1')
			{
				if ($g_en_travaux_o_n=="1")
				{
					$titre="Travaux en cours : cliquer pour désactiver";
					$href=href(dispatch_url("organisme.organisme", "travaux", array (	"atktravaux" => "fin","atkmenutop" =>  $atkmenutop )),
			    '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_rouge.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				else {
					$titre="Travaux en cours : cliquer pour activer";
					$href=href(dispatch_url("organisme.organisme", "travaux", array (	"atktravaux" => "debut","atkmenutop" =>  $atkmenutop )),
			    '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_vert.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				$etat_en_travaux=$href;
				if ($g_tracer_mysqldb_query_o_n=="1")
				{
					$titre="Trace query sql : cliquer pour désactiver";
					$href=href(dispatch_url("organisme.organisme", "tracer_mysqldb", array (	"atktracer_mysqldb" => "fin","atkmenutop" =>  $atkmenutop )),
			    '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_rouge.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				else
				{
					$titre="Trace query sql : cliquer pour activer";
					$href=href(dispatch_url("organisme.organisme", "tracer_mysqldb", array (	"atktracer_mysqldb" => "debut","atkmenutop" =>  $atkmenutop )),
			    '<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_vert.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				$etat_trace_mysqldb=$href;
				
				
				
				
				if ($g_debug_o_n=="1")
				{
					$titre="Debugging : cliquer pour désactiver";
					$href=href(dispatch_url("organisme.organisme", "debugging", array (	"atkdebugging" => "fin","atkmenutop" =>  $atkmenutop )),
							'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_rouge.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				else
				{
					$titre="Debugging : cliquer pour activer";
					$href=href(dispatch_url("organisme.organisme", "debugging", array (	"atkdebugging" => "debut","atkmenutop" =>  $atkmenutop )),
							'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/feu_vert.png" alt="'.$titre.'" title="'.$titre.'" ></img>');
				}
				
				$etat_debugging=$href;
			}

			$resultat='<span '.$menutip.'><b><a href="menu.php?atkmenutop='.$atkmenutop.'" target="menu">'.strtoupper($atkmenutoptop).' </a></span>';
			$resultat.='<a href="menu.php?atkmenutop='.$atkmenutop.'"  target="menu"><img class="recordlist" border="0" src="./themes/assocope/icons/assocope/refresh.png" alt="Rafraîchir le menu" title="Rafraîchir le menu" ></img></a><br />';
			$resultat.=$aide.' '.$presse_papier.$affiche_travaux_en_cours.$etat_en_travaux.$etat_trace_mysqldb.$etat_debugging.' <br/>'.$operations.'<br />'.$descripteur_rd.'<br />';
			if (!empty($url))
			{
				$resultat .= $this->createdropdown($nomformulaire, $typeentite, $nomselection, $atkmenutop, $id_individu, $url);

				$retour=$resultat;
			}
			else{
				$retour=$resultat;}



		}

		return $retour;
	}
	function GetWikiPageAge($pagename)
	{

		$dbw = & atkGetDb("assocopewiki");
		$data=$dbw->getrows("select page_touched from mw_page where page_title='". $pagename ."'");
		$page_touched=$data[0]["page_touched"];
		if (empty($page_touched)) return "";
		$hours=substr($page_touched, 8,2);
		$minutes=substr($page_touched, 10,2);
		$seconds=substr($page_touched, 12,2);
		$month=substr($page_touched, 4,2);
		$day=substr($page_touched, 6,2);
		$year=substr($page_touched, 0,4);
		$page_touched= mktime($hours,$minutes,$seconds,$month,$day,$year);
		$time=time();
		return (($time-$page_touched)/3600/24);
	}
	function createdropdown($nomformulaire, $typeentite, $nomselection, $menutop, $id_individu, $url) {
		$menurecherche=" <br></br> Le caractère '%' remplace toute chaîne de caractères, le caractère '_'(trait souligné) remplace un seul caractère : ainsi 'ger' ou '%ger%' recherchera toutes les chaînes contenant 'ger', 'l%ger' ou '%l%ger%' recherchera toutes les chaînes de caractères contenant 'l' et plus loin 'ger'.";
		if ( $typeentite == "individu" )
		{
			$destinationurl=dispatch_url("individu.individu", "admin", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$autocompleteurl=dispatch_url("individu.individu", "autocomplete", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$menutip=fairetooltip('Vous pouvez choisir parmi les individus que vous avez récemment traités') ;
			$menutip2= fairetooltip('Vous pouvez chercher dans la base complète et afficher dans la liste de droite des individus sur une partie du nom. La casse(minuscule, majuscule) est indifférente.'.$menurecherche ) ;
			$menutip3= fairetooltip('Vous pouvez chercher avec sélection immédiate des individus sur une partie du nom, prénom dans n\'importe quel ordre. Lors de la sélection l\'individu choisi s\'affiche dans le menu de gauche. '.$menurecherche ) ;
		}
		if ( $typeentite == "organisme" )
		{
			$destinationurl=dispatch_url("organisme.organisme", "admin", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$autocompleteurl=dispatch_url("organisme.organisme", "autocomplete", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$menutip= fairetooltip('Vous pouvez choisir parmi les organismes que vous avez récemment traités') ;
			$menutip2= fairetooltip('Vous pouvez chercher dans la base complète des organismes sur une partie du nom. La casse(minuscule, majuscule) est indifférente.'.$menurecherche) ;
			$menutip3= fairetooltip('Vous pouvez chercher avec sélection immédiate dans la base complète des organismes sur une partie du nom, sigle dans n\'importe quel ordre. Lors de la sélection l\'organisme choisi s\'affiche dans le menu de gauche.'.$menurecherche ) ;
		}

		if ( $typeentite == "taxon" )
		{
			$destinationurl=dispatch_url("biodiversite.taxinomie", "admin", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$autocompleteurl=dispatch_url("biodiversite.taxinomie", "autocomplete", array (
			"atkfilter" => "'%XXXXXX%' " 
			),'dispatch.php');
			$menutip= fairetooltip('Vous pouvez choisir parmi les taxons que vous avez récemment traités') ;
			$menutip2= fairetooltip('Vous pouvez chercher dans la base complète des taxons sur une partie du nom. La casse(minuscule, majuscule) est indifférente.'.$menurecherche) ;
			$menutip3= fairetooltip('Vous pouvez chercher avec sélection immédiate dans la base complète des taxons sur une partie du nom binomial, nom français dans n\'importe quel ordre. Lors de la sélection le taxon choisi s\'affiche dans le menu de gauche.'.$menurecherche ) ;
		}


		if ( $typeentite == "rencontre" )
		{
			$menutip= fairetooltip('Vous pouvez choisir parmi les rencontres que vous avez récemment traitées') ;
		}
		if ( $typeentite == "envoi" )
		{
			$menutip= fairetooltip('Vous pouvez choisir parmi  les envois que vous avez récemment traités') ;

		}
		if ( $typeentite == "compte" )
		{
			$menutip= fairetooltip('Vous pouvez choisir parmi les comptes que vous avez récemment traités') ;
		}
		if ( $typeentite == "langue" )
		{
			$menutip= fairetooltip('Vous pouvez choisir parmi les langues que vous avez récemment traitées') ;
		}

		$prj = '<FORM name="' . $nomformulaire . '" action="menu.php" method="get">';
		$prj .= session_form(SESSION_DEFAULT);
		$prj .= '<INPUT type="hidden" name="atkmenutop" value="' . $menutop . '">';
		$prj .= 'Choisir dans l\'historique : <br/>';
		$prj .= '<INPUT type="hidden" name="atkmenutop" value="' . $menutop . '">';
		$prj .= '<SELECT style="width: 85%" name="' . $nomselection . '" onchange="document.' . $nomformulaire . '.submit();" '.$menutip.'
		>';
		$prj .= '<OPTION value="0">' . atktext("aucun") . '</OPTION>';
		$db = & atkGetDb();
		$data = $db->getrows("select  id_entite from app_recent_use where
		id_individu=$id_individu and type_entite='" . $typeentite . "' order by date_recent_use desc");
		$selectedentite = $data[0]["id_entite"];
		$entites = $db->getrows($url);
		//		print_r($entites);
		//					die();
		for ($i = 0, $_i = count($entites); $i < $_i; $i++) {
			$selected = ($selectedentite == $entites[$i]['entiteid']) ? ' selected' : '';
			$prj .= sprintf('<OPTION value="%d" %s>%s</OPTION>', $entites[$i]['entiteid'], $selected, $entites[$i]['entitename']);
		}
		$prj .= '</SELECT>';
		if ($typeentite == "individu" || $typeentite == "organisme" || $typeentite == "taxon")
		{			$prj .= '<br/>Rechercher dans la base : <br/>';
		$prj .='<input type="hidden" id="type_entite" value="'.$typeentite.'">';
		$prj .='<input type="hidden" id="url_1" value="'.$destinationurl.'" />';
		$prj .='<input id="idsearchstring_1" name="searchstring_1" style="width: 85%;" type="text" size="30" value=" " />';
		$prj .=' <input class="btn_save" onclick="startmain()" type="submit" '.$menutip2.' value="Ok"/> ' ;
		$prj.='  <br/>Rechercher par suggestion : <br/>';


		$prj.=$this->drawAutoCompleteBox("searchstring_2",  $autocompleteurl , $typeentite, $menutip3);
		}
		$prj .= '</FORM>';
		return $prj;
	}

	function drawAutoCompleteBox($id,  $autocompleteurl, $typeentite, $menutip )
	{
		/*
		 if ($typeentite=='taxon')
		 { $largeur_boite=500; }
		 else
		 {
		 $largeur_boite=120;
		 }
		 *
		 */

		$retour.='<script type="text/javascript" src="atk/javascript/class.atkmanytoonerelation.js"></script>';
		//	$retour.='<link href="themes/assocope/styles/atkmanytoonerelation.css" rel="stylesheet" type="text/css"  />'."\n";
		$retour.='<link href="themes/assocope/styles/atkmanytoonerelation.css" rel="stylesheet" type="text/css"  />';
		$retour .='<input type="hidden" id="'.$id.'" name="'.$id.'" value=""/>';
		$retour .='<input type="hidden" id="type_entite" value="'.$typeentite.'"/>';
		$retour .='<input type="text" id="'.$id.'_search" value="'.atk_htmlentities($label).'" style="width: 85%;" class="atkmanytoonerelation_search" size="30" onfocus="this.select()" />';
		$retour .=' <input class="btn_save"  type="submit" '.$menutip.' value="Ok"/>
		        <img id="'.$id.'_spinner" src="atk/images/spinner.gif" style="vertical-align: middle; display: none" /> 
                <div id="'.$id.'_result" style="display: none" class="atkmanytoonerelation_result"></div>' ;
		$retour .="<script> ATK.ManyToOneRelation.completeEdit('{$id}_search', '{$id}_result', '$id', '{$id}_spinner', '$autocompleteurl', null, 1);
        </script>";

		return $retour;
	}

}
?>