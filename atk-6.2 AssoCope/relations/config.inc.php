<?php

  // -------------------------------------------
  //           DATABASE CONFIGURATION
  // -------------------------------------------


  $config_db["default"]["driver"] = "mysql";
  $config_db["default"]["host"]     = "mysql.wikiservas.net";
  $config_db["default"]["db"]       = "association";
  $config_db["default"]["user"]     = "webmaster";
  $config_db["default"]["password"] = "rf1930";



  // -------------------------------------------
  //           LAYOUT CONFIGURATION
  // -------------------------------------------

   $config_recordlist_orientation  = "left";
  $config_recordlist_vorientation = "middle";
   $config_recordlist_icons = "true";
  $config_tabs = true;
  $config_stacktrace = true;
   $config_top_frame = 1;
  $config_recordsperpage=50;
  $config_defaulttheme = "t3skin";
  $config_force_theme_recompile=true;
  $config_language="fr";
  $config_atkroot="./";
 $config_extended_search_action = "smartsearch";
$config_dropdown_width=150;



  // Menu configuration. You can have a menu at "top", "left", "right" or
  // "bottom". If you use a horizontal menu (top or bottom, you may want
  // to change the menu_delimiter to " " (menu_delimiter is what atk
  // puts between menu items).
$config_menu_pos = "left";
$config_menu_delimiter = "<br /> ";
  $config_menu_layout = "modern";


  // If the users are using IE, then the application can be run in fullscreen
  // mode. Set the next variable to true to enable this:
  $config_fullscreen = false;

  // Lists that are obligatory, by default have no 'Select none' option. In
  // some applications, this leads to the user just selecting the first item
  // since that is the default. If this is a problem set this config variable
  // to true; this will add a 'Select none' option to obligatory lists so the
  // user is forced to make a selection.
  $config_list_obligatory_null_item = true;

  // Wether or not to use the keyboardhandler for attributes and the recordlist
  // When set to true, arrow keys can be used to navigate through fields and
  // records, as well as shortcuts 'e' for edit, 'd' for delete, and left/right
  // cursor for paging. Note however, that using cursor keys to navigate
  // through fields is not standard web application behaviour.
  $config_use_keyboard_handler = false;
  
    
//  * Should all many-to-one relations have the AF_RELATION_AUTOCOMPLETE flag set?
  $config_manytoone_autocomplete_default = false;
//   * Should all many-to-one relations that have the AF_LARGE flag set also
//   * have the AF_RELATION_AUTOCOMPLETE flag set?
  $config_manytoone_autocomplete_large = false;
//   * Should manytoone relations having the AF_RELATION_AUTOCOMPLETE flag also
 // use auto completion in search forms?
   $config_manytoone_search_autocomplete = true;
//   * Controls how many characters a user must enter before an auto-completion
 //  * search is being performed.
  $config_manytoone_autocomplete_minchars = 4;
//   * The search mode of the autocomplete fields. Can be 'startswith', 'exact' or 'contains'.
//  $config_manytoone_autocomplete_searchmode = "contains";
//   * Value determines wether the search of the autocompletion is case-sensitive.
  $config_manytoone_autocomplete_search_case_sensitive = false;
//   * Warn the user if he/she has changed something in a form
 //  * and leaves the page without pressing save or cancel.
  $config_lose_changes_warning = true;

  

/*********************************** OUTPUT ********************************/

 
  // Set to true, to output pages gzip compressed to the browser if the
  // browser supports it.
  $config_output_gzip = false;


  // -------------------------------------------
  //           SECURITY CONFIGURATION
  // -------------------------------------------

 
  
  $config_auth_mail_server = "localhost";
  $config_administratorpassword = "rf1930";
  $config_auth_dropdown = false;
  $config_session_regenerate = false;

  

  $config_identifier = "wikiassoc";
  $config_top_frame = 1;
  $config_authorization = "db";
  $config_authentication = "db";
  $config_lock_type = "db";
  $config_auth_usertable = "app_utilisateur";
  $config_auth_userfield = "identifiant";
  $config_auth_accesstable = "app_profil_droit_acces";
  $config_auth_passwordfield = "mot_de_passe";
  $config_auth_emailfield = "courriel";
  $config_auth_leveltable  = "app_utilisateur";
  $config_auth_levelfield  = "id_profil";
	$config_auth_usernode = "profil.utilisateur";
  //$config_auth_userfk = "id_utilisateur";
  $config_auth_enablepasswordmailer= true;
  $config_max_loginattempts = 0;
  $config_auth_loginform = true;
  $config_auth_userdescriptor = "[userid]";
  $config_authentication_md5 = true;
   $config_auth_usecryptedpassword = false;
  $config_securityscheme = "group";
  $config_auth_accountenableexpression = " etat='actif'";
  $config_atktempdir = $config_atkroot."atktmp/";
  $config_atkdocumenttempdir = $config_atkroot."atkdocumenttmp/";
  $config_tplcompiledir = $config_atktempdir."compiled/tpl/";
  // $config_auth_grantall_privilege = "utilisateur.profil.grantall";
  // $config_durationformat = 0;
  $config_defaultfavico = "images/ilco.ico";
  $config_corporate_module_base = "modules.associationmodule";
$config_logging=2;
$config_logfile=$config_atktempdir."atksecurity.log";

 //----------------- DEBUGGER CONFIGURATION ----------------------

  // The automatic error reporter
  // Error reports are sent to the given email address.
  // If you set this to "", error reporting will be turned off.
  // WARNING: DO NOT LEAVE THIS TO THE DEFAULT ADDRESS OR PREPARE TO BE
  // SEVERELY FLAMED!
$config_mailreport = "guy.gourmellet@gmail.com";

  // The debug level.
  // -1 - No debug information
  //  0 - No debug information, but still stored for atk errormails
  //  1 - Print some debug information at the bottom of each screen
  //  2 - Print debug information, and pause before redirects
  //  3 - Like 2, but also adds trace information to each statement
  $config_debug =2;
   $config_debuglog=$config_atktempdir."debug.log";

  // Smart debug parameters. Is used to dynamically enable debugging for
  // certain IP addresses or if for example the special atkdebug[key] request
  // variable equals a configured key etc. If smart debugging is enabled
  // you can also change the debug level dynamically using the special
  // atkdebug[level] request variable.
  //
  // $config_smart_debug[] = array("type" => "request", "key" => "test");
  // $config_smart_debug[] = array("type" => "ip", "list" => array("10.0.0.4"));
  $config_smart_debug[] = array("type" => "request", "key" => "test");



  // -------------------------------------------
  //        DOCUMENT WRITER CONFIGURATION
  // -------------------------------------------

  
  $config_doctemplatedir = "doctemplates/";


  // -------------------------------------------
  //        CONFIGURATION R?ertoires pour GIS
  // -------------------------------------------

  
  $config_imagesdir = "/association/gis/images/";
  $config_kmldir = "/association/gis/kml/";
  $config_gpxdir = "/association/gis/gpx/";
$config_photosdir = "/association/gis/photos/";

 // -------------------------------------------
  //        JOURNALISATION DANS atkeventlog en utilisant un listener
// si $config_journalisation=true et si app_utilisateur log_o_n=1
  // -------------------------------------------

$config_journalisation=true ;
$config_maildemande = "guy.gourmellet@gmail.com";
$config_nomapplication = "WikiAssoc";
$config_mail_sender="Webmaster";
$config_mail_enabled=true;
//--------------------------------
// fckeditor
//
$config_fck=array('ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'600px',
                 'Skin'=>'office2003');
?>
