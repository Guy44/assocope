<?php
/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * searchs the entire database
 *
 * @todo    make use of UNION when searching multiple tables
 * @todo    display executed query, optional?
 * @uses    $cfg['UseDbSearch']
 * @uses    $GLOBALS['db']
 * @uses    $GLOBALS['strAccessDenied']
 * @uses    $GLOBALS['strSearchOption1']
 * @uses    $GLOBALS['strSearchOption2']
 * @uses    $GLOBALS['strSearchOption3']
 * @uses    $GLOBALS['strSearchOption4']
 * @uses    $GLOBALS['strSearchResultsFor']
 * @uses    $GLOBALS['strNumSearchResultsInTable']
 * @uses    $GLOBALS['strBrowse']
 * @uses    $GLOBALS['strDelete']
 * @uses    $GLOBALS['strNumSearchResultsTotal']
 * @uses    $GLOBALS['strSearchFormTitle']
 * @uses    $GLOBALS['strSearchNeedle']
 * @uses    $GLOBALS['strSearchType']
 * @uses    $GLOBALS['strSplitWordsWithSpace']
 * @uses    $GLOBALS['strSearchInTables']
 * @uses    $GLOBALS['strUnselectAll']
 * @uses    $GLOBALS['strSelectAll']
 * @uses    PMA_DBI_get_tables()
 * @uses    PMA_sqlAddslashes()
 * @uses    PMA_getSearchSqls()
 * @uses    PMA_DBI_fetch_value()
 * @uses    PMA_linkOrButton()
 * @uses    PMA_generate_common_url()
 * @uses    PMA_generate_common_hidden_inputs()
 * @uses    PMA_showMySQLDocu()
 * @uses    $_REQUEST['search_str']
 * @uses    $_REQUEST['submit_search']
 * @uses    $_REQUEST['search_option']
 * @uses    $_REQUEST['table_select']
 * @uses    $_REQUEST['unselectall']
 * @uses    $_REQUEST['selectall']
 * @uses    $_REQUEST['field_str']
 * @uses    is_string()
 * @uses    htmlspecialchars()
 * @uses    array_key_exists()
 * @uses    is_array()
 * @uses    array_intersect()
 * @uses    sprintf()
 * @uses    in_array()
 * @version $Id$
 * @author  Thomas Chaumeny <chaume92 at aol.com>
 * @package phpMyAdmin
 */

/**
 *
 */
 define('PHPMYADMIN', true);

// require_once atkconfig("atkroot") . "modules/search/libraries/common.inc.php";

/**
 * Gets some core libraries and send headers
 */
// 
// require atkconfig("atkroot") . "modules/search/libraries/db_common.inc.php";
/**
 * core functions
 */
require_once "./atk/class.atkconfig.inc" ;
require_once atkconfig("atkroot") . "modules/search/libraries/core.lib.php";

/**
 * Input sanitizing
 */
require_once atkconfig("atkroot") . "modules/search/libraries/sanitizing.lib.php";

/**
 * the PMA_Theme class
 */
require_once atkconfig("atkroot") . "modules/search/libraries/Theme.class.php";

/**
 * the PMA_Theme_Manager class
 */
require_once atkconfig("atkroot") . "modules/search/libraries/Theme_Manager.class.php";

/**
 * the PMA_Config class
 */
require_once atkconfig("atkroot") . "modules/search/libraries/Config.class.php";

/**
 * the relation lib, tracker needs it
 */
require_once atkconfig("atkroot") . "modules/search/libraries/relation.lib.php";

/**
 * the PMA_Tracker class
 */
require_once atkconfig("atkroot") . "modules/search/libraries/Tracker.class.php";

/**
 * the PMA_Table class
 */
require_once atkconfig("atkroot") . "modules/search/libraries/Table.class.php";


    /**
     * common functions
     */
    require_once atkconfig("atkroot") . "modules/search/libraries/common.lib.php";

    /**
     * Java script escaping.
     */
    require_once atkconfig("atkroot") . "modules/search/libraries/js_escape.lib.php";

    /**
     * Include URL/hidden inputs generating.
     */
    require_once atkconfig("atkroot") . "modules/search/libraries/url_generating.lib.php";

// init

$GLOBALS['db']='association';
$GLOBALS['strAccessDenied']=false;
$GLOBALS['strSearchOption1']='au moins un mot';
$GLOBALS['strSearchOption2'] = 'tous les mots';
$GLOBALS['strSearchOption3'] = 'phrase exacte';
$GLOBALS['strSearchOption4'] = 'expression régulière';
$GLOBALS['strSearchResultsFor'] = 'Résultats de la recherche de "<i>%s</i>" %s :';
$GLOBALS['strNumSearchResultsInTable']= '%s occurence(s) dans la table <i>%s</i>';
$GLOBALS['strBrowse']='Afficher';
$GLOBALS['strDelete']='Effacer';
$GLOBALS['strNumSearchResultsTotal'] = '<b>Total :</b> <i>%s</i> occurence(s)';
$GLOBALS['strSearchFormTitle'] = 'Effectuer une nouvelle recherche dans la base de donnÃ©es';
$GLOBALS['strSearchNeedle'] = 'Mot(s) ou Valeur à rechercher (passe-partout: "%") :';
$GLOBALS['strSearchType'] = 'Type de recherche :';
$GLOBALS['strSplitWordsWithSpace'] = 'Séparer les mots par un espace (" ").';
$GLOBALS['strSearchInTables'] = 'Dans la(les) table(s) :';
$GLOBALS['strUnselectAll']='Tout désélectionner';
$GLOBALS['strSelectAll']='Tout sélectionner';

/* $GLOBALS['Servers][1] ou $GLOBALS[Server]
*/
 $GLOBALS[cfg][Server][host] = 'mysql.wikiservas.net';
    $GLOBALS[cfg][Server][port] = '';
    $GLOBALS[cfg][Server][socket]= '';
    $GLOBALS[cfg][Server][ssl]= '';
    $GLOBALS[cfg][Server][connect_type]= 'tcp';
    $GLOBALS[cfg][Server][extension] = 'mysql';
    $GLOBALS[cfg][Server][bs_garbage_threshold]= 50;
    $GLOBALS[cfg][Server][bs_repository_threshold]= '32M';
    $GLOBALS[cfg][Server][bs_temp_blob_timeout] =600;
    $GLOBALS[cfg][Server][bs_temp_log_threshold] = '32M';
    $GLOBALS[cfg][Server][compress] ='';
    $GLOBALS[cfg][Server][controluser] ='';
    $GLOBALS[cfg][Server][controlpass] ='';
    $GLOBALS[cfg][Server][auth_type] = 'cookie';
    $GLOBALS[cfg][Server][auth_swekey_config]=''; 
    $GLOBALS[cfg][Server][user]='webmaster';
    $GLOBALS[cfg][Server][password] ='rf1930';
    $GLOBALS[cfg][Server][SignonSession] =''; 
    $GLOBALS[cfg][Server][SignonURL] =''; 
    $GLOBALS[cfg][Server][LogoutURL] ='';
    $GLOBALS[cfg][Server][nopassword] =''; 
    $GLOBALS[cfg][Server][only_db] =''; 
    $GLOBALS[cfg][Server][hide_db]='';
    $GLOBALS[cfg][Server][verbose]='';
    $GLOBALS[cfg][Server][pmadb]='phpmyadmin';
    $GLOBALS[cfg][Server][bookmarktable] ='pma_bookmark';
    $GLOBALS[cfg][Server][relation] ='pma_relation';
    $GLOBALS[cfg][Server][table_info] ='pma_table_info';
    $GLOBALS[cfg][Server][table_coords] ='pma_table_coords';
    $GLOBALS[cfg][Server][pdf_pages] ='pma_pdf_pages';
    $GLOBALS[cfg][Server][column_info] ='pma_column_info';
    $GLOBALS[cfg][Server][history] ='pma_history';
    $GLOBALS[cfg][Server][designer_coords] ='pma_designer_coords';
    $GLOBALS[cfg][Server][tracking] ='pma_tracking';
    $GLOBALS[cfg][Server][verbose_check] = 1;
    $GLOBALS[cfg][Server][AllowRoot] = 1;
    $GLOBALS[cfg][Server][AllowNoPassword] ='';
/*        $GLOBALS[cfg][Server][AllowDeny] = Array
        (
            [order]=''; 
            [rules] => Array
                (
                )

        )
*/
    $GLOBALS[cfg][Server][DisableIS] = 1;
    $GLOBALS[cfg][Server][ShowDatabasesCommand]= 'SHOW DATABASES';
    $GLOBALS[cfg][Server][CountTables]= 1;
    $GLOBALS[cfg][Server][tracking_version_auto_create] = '';
    $GLOBALS[cfg][Server][tracking_default_statements] = 'CREATE TABLE,ALTER TABLE,DROP TABLE,RENAME TABLE,CREATE INDEX,DROP INDEX,INSERT,UPDATE,DELETE,TRUNCATE,REPLACE,CREATE VIEW,ALTER VIEW,DROP VIEW,CREATE DATABASE,ALTER DATABASE,DROP DATABASE';
    $GLOBALS[cfg][Server][tracking_add_drop_view] = 1;
    $GLOBALS[cfg][Server][tracking_add_drop_table] = 1;
    $GLOBALS[cfg][Server][tracking_add_drop_database] = 1;
    $GLOBALS[cfg][Server][tracking_version_drop_database] = 1;

$GLOBALS['lang_path']=atkconfig("atkroot") . "modules/search/lang";

/*
* @uses    PMA_DBI_get_tables()
 * @uses    PMA_sqlAddslashes()
 * @uses    PMA_getSearchSqls()
 * @uses    PMA_DBI_fetch_value()
 * @uses    PMA_linkOrButton()
 * @uses    PMA_generate_common_url()
 * @uses    PMA_generate_common_hidden_inputs()
 * @uses    PMA_showMySQLDocu()
 * 
 *  */
// If config variable $GLOBALS['cfg']['Usedbsearch'] is on false : exit.
/*if (! $GLOBALS['cfg']['UseDbSearch']) {
    PMA_mysqlDie($GLOBALS['strAccessDenied'], '', false, $err_url);
} // end if
$url_query .= '&amp;goto=db_search.php';
$url_params['goto'] = 'db_search.php';

/**
 * @global array list of tables from the current database
 * but do not clash with $tables coming from db_info.inc.php
 */

require atkconfig("atkroot") . "modules/search/libraries/database_interface.lib.php";

 $tables_names_only = PMA_DBI_get_tables($GLOBALS['db']);


$search_options = array(
    '1' => $GLOBALS['strSearchOption1'],
    '2' => $GLOBALS['strSearchOption2'],
    '3' => $GLOBALS['strSearchOption3'],
    '4' => $GLOBALS['strSearchOption4'],
);


if (empty($_REQUEST['search_option']) || ! is_string($_REQUEST['search_option'])
 || ! array_key_exists($_REQUEST['search_option'], $search_options)) {
    $search_option = 1;
    unset($_REQUEST['submit_search']);
} else {
    $search_option = (int) $_REQUEST['search_option'];
    $option_str = $search_options[$_REQUEST['search_option']];
}

if (empty($_REQUEST['search_str']) || ! is_string($_REQUEST['search_str'])) {
    unset($_REQUEST['submit_search']);
    $searched = '';
} else {
    $searched = htmlspecialchars($_REQUEST['search_str']);
    // For "as regular expression" (search option 4), we should not treat
    // this as an expression that contains a LIKE (second parameter of
    // PMA_sqlAddslashes()).
    //
    // Usage example: If user is seaching for a literal $ in a regexp search,
    // he should enter \$ as the value.
    $search_str = PMA_sqlAddslashes($_REQUEST['search_str'], ($search_option == 4 ? false : true));
}

$tables_selected = array();
if (empty($_REQUEST['table_select']) || ! is_array($_REQUEST['table_select'])) {
    unset($_REQUEST['submit_search']);
} elseif (! isset($_REQUEST['selectall']) && ! isset($_REQUEST['unselectall'])) {
    $tables_selected = array_intersect($_REQUEST['table_select'], $tables_names_only);
}

if (isset($_REQUEST['selectall'])) {
    $tables_selected = $tables_names_only;
} elseif (isset($_REQUEST['unselectall'])) {
    $tables_selected = array();
}

if (empty($_REQUEST['field_str']) || ! is_string($_REQUEST['field_str'])) {
    unset($field_str);
} else {
    $field_str = PMA_sqlAddslashes($_REQUEST['field_str'], true);
}

/**
 * Displays top links
 */
$sub_part = '';
require atkconfig("atkroot") . "modules/search/libraries/db_info.inc.php";
echo 'GUY';
die();

/**
 * 1. Main search form has been submitted
 */
if (isset($_REQUEST['submit_search'])) {

    /**
     * Builds the SQL search query
     *
     * @todo    can we make use of fulltextsearch IN BOOLEAN MODE for this?
     * @uses    PMA_DBI_query
     * PMA_backquote
     * PMA_DBI_free_result
     * PMA_DBI_fetch_assoc
     * $GLOBALS['db']
     * explode
     * count
     * strlen
     * @param   string   the table name
     * @param   string   restrict the search to this field
     * @param   string   the string to search
     * @param   integer  type of search (1 -> 1 word at least, 2 -> all words,
     *                                   3 -> exact string, 4 -> regexp)
     *
     * @return  array    3 SQL querys (for count, display and delete results)
     *
     * @global  string   the url to return to in case of errors
     * @global  string   charset connection
     */
    function PMA_getSearchSqls($table, $field, $search_str, $search_option)
    {
        global $err_url;

        // Statement types
        $sqlstr_select = 'SELECT';
        $sqlstr_delete = 'DELETE';

        // Fields to select
        $tblfields = PMA_DBI_fetch_result('SHOW FIELDS FROM ' . PMA_backquote($table) . ' FROM ' . PMA_backquote($GLOBALS['db']),
            null, 'Field');

        // Table to use
        $sqlstr_from = ' FROM ' . PMA_backquote($GLOBALS['db']) . '.' . PMA_backquote($table);

        $search_words    = (($search_option > 2) ? array($search_str) : explode(' ', $search_str));
        $search_wds_cnt  = count($search_words);

        $like_or_regex   = (($search_option == 4) ? 'REGEXP' : 'LIKE');
        $automatic_wildcard   = (($search_option < 3) ? '%' : '');

        $fieldslikevalues = array();
        foreach ($search_words as $search_word) {
            // Eliminates empty values
            if (strlen($search_word) === 0) {
                continue;
            }

            $thefieldlikevalue = array();
            foreach ($tblfields as $tblfield) {
                if (! isset($field) || strlen($field) == 0 || $tblfield == $field) {
                    $thefieldlikevalue[] = PMA_backquote($tblfield)
                                         . ' ' . $like_or_regex . ' '
                                         . "'" . $automatic_wildcard
                                         . $search_word
                                         . $automatic_wildcard . "'";
                }
            } // end for

            if (count($thefieldlikevalue) > 0) {
                $fieldslikevalues[]      = implode(' OR ', $thefieldlikevalue);
            }
        } // end for

        $implode_str  = ($search_option == 1 ? ' OR ' : ' AND ');
        if ( empty($fieldslikevalues)) {
            // this could happen when the "inside field" does not exist
            // in any selected tables
            $sqlstr_where = ' WHERE FALSE';
        } else {
            $sqlstr_where = ' WHERE (' . implode(') ' . $implode_str . ' (', $fieldslikevalues) . ')';
        }
        unset($fieldslikevalues);

        // Builds complete queries
        $sql['select_fields'] = $sqlstr_select . ' * ' . $sqlstr_from . $sqlstr_where;
        // here, I think we need to still use the COUNT clause, even for
        // VIEWs, anyway we have a WHERE clause that should limit results
        $sql['select_count']  = $sqlstr_select . ' COUNT(*) AS `count`' . $sqlstr_from . $sqlstr_where;
        $sql['delete']        = $sqlstr_delete . $sqlstr_from . $sqlstr_where;

        return $sql;
    } // end of the "PMA_getSearchSqls()" function


    /**
     * Displays the results
     */
    $this_url_params = array(
        'db'    => $GLOBALS['db'],
        'goto'  => 'db_sql.php',
        'pos'   => 0,
        'is_js_confirmed' => 0,
    );

    // Displays search string
    echo '<br />' . "\n"
        .'<table class="data">' . "\n"
        .'<caption class="tblHeaders">' . "\n"
        .sprintf($GLOBALS['strSearchResultsFor'],
            $searched, $option_str) . "\n"
        .'</caption>' . "\n";

    $num_search_result_total = 0;
    $odd_row = true;

    foreach ($tables_selected as $each_table) {
        // Gets the SQL statements
        $newsearchsqls = PMA_getSearchSqls($each_table, (! empty($field_str) ? $field_str : ''), $search_str, $search_option);

        // Executes the "COUNT" statement
        $res_cnt = PMA_DBI_fetch_value($newsearchsqls['select_count']);
        $num_search_result_total += $res_cnt;

        $sql_query .= $newsearchsqls['select_count'];

        echo '<tr class="' . ($odd_row ? 'odd' : 'even') . '">'
            .'<td>' . sprintf($GLOBALS['strNumSearchResultsInTable'], $res_cnt,
                htmlspecialchars($each_table)) . "</td>\n";

        if ($res_cnt > 0) {
            $this_url_params['sql_query'] = $newsearchsqls['select_fields'];
            echo '<td>' . PMA_linkOrButton(
                    'sql.php' . PMA_generate_common_url($this_url_params),
                    $GLOBALS['strBrowse'], '') .  "</td>\n";

            $this_url_params['sql_query'] = $newsearchsqls['delete'];
            echo '<td>' . PMA_linkOrButton(
                    'sql.php' . PMA_generate_common_url($this_url_params),
                    $GLOBALS['strDelete'], $newsearchsqls['delete']) .  "</td>\n";

        } else {
            echo '<td>&nbsp;</td>' . "\n"
                .'<td>&nbsp;</td>' . "\n";
        }// end if else
        $odd_row = ! $odd_row;
        echo '</tr>' . "\n";
    } // end for

    echo '</table>' . "\n";

    if (count($tables_selected) > 1) {
        echo '<p>' . sprintf($GLOBALS['strNumSearchResultsTotal'],
            $num_search_result_total) . '</p>' . "\n";
    }
} // end 1.


/**
 * 2. Displays the main search form
 */
?>
<a name="db_search"></a>
<form method="post" action="db_search.php" name="db_search">
<?php echo PMA_generate_common_hidden_inputs($GLOBALS['db']); ?>
<fieldset>
    <legend><?php echo $GLOBALS['strSearchFormTitle']; ?></legend>

    <table class="formlayout">
    <tr><td><?php echo $GLOBALS['strSearchNeedle']; ?></td>
        <td><input type="text" name="search_str" size="60"
                value="<?php echo $searched; ?>" /></td>
    </tr>
    <tr><td align="right" valign="top">
            <?php echo $GLOBALS['strSearchType']; ?></td>
            <td><?php

$choices = array(
    '1' => $GLOBALS['strSearchOption1'] . PMA_showHint($GLOBALS['strSplitWordsWithSpace']),
    '2' => $GLOBALS['strSearchOption2'] . PMA_showHint($GLOBALS['strSplitWordsWithSpace']),
    '3' => $GLOBALS['strSearchOption3'],
    '4' => $GLOBALS['strSearchOption4'] . ' ' . PMA_showMySQLDocu('Regexp', 'Regexp')
);
// 4th parameter set to true to add line breaks
// 5th parameter set to false to avoid htmlspecialchars() escaping in the label
//  since we have some HTML in some labels
PMA_display_html_radio('search_option', $choices, $search_option, true, false);
unset($choices);
            ?>
            </td>
    </tr>
    <tr><td align="right" valign="top">
            <?php echo $GLOBALS['strSearchInTables']; ?></td>
        <td rowspan="2">
<?php
echo '            <select name="table_select[]" size="6" multiple="multiple">' . "\n";
foreach ($tables_names_only as $each_table) {
    if (in_array($each_table, $tables_selected)) {
        $is_selected = ' selected="selected"';
    } else {
        $is_selected = '';
    }

    echo '                <option value="' . htmlspecialchars($each_table) . '"'
        . $is_selected . '>'
        . str_replace(' ', '&nbsp;', htmlspecialchars($each_table)) . '</option>' . "\n";
} // end while

echo '            </select>' . "\n";
$alter_select =
    '<a href="db_search.php' . PMA_generate_common_url(array_merge($url_params, array('selectall' => 1))) . '#db_search"'
    . ' onclick="setSelectOptions(\'db_search\', \'table_select[]\', true); return false;">' . $GLOBALS['strSelectAll'] . '</a>'
    . '&nbsp;/&nbsp;'
    . '<a href="db_search.php' . PMA_generate_common_url(array_merge($url_params, array('unselectall' => 1))) . '#db_search"'
    . ' onclick="setSelectOptions(\'db_search\', \'table_select[]\', false); return false;">' . $GLOBALS['strUnselectAll'] . '</a>';
?>
        </td>
    </tr>
    <tr><td align="right" valign="bottom">
            <?php echo $alter_select; ?></td>
    </tr>
    <tr><td align="right">
            <?php echo $GLOBALS['strSearchInField']; ?></td>
        <td><input type="text" name="field_str" size="60"
                value="<?php echo ! empty($field_str) ? $field_str : ''; ?>" /></td>
    </tr>
    </table>
</fieldset>
<fieldset class="tblFooters">
    <input type="submit" name="submit_search" value="<?php echo $GLOBALS['strGo']; ?>"
        id="buttonGo" />
</fieldset>
</form>

<?php
/**
 * Displays the footer
 */
require_once atkconfig("atkroot") . "modules/search/libraries/footer.inc.php";



?>
