<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage utils
 *
 * @copyright (c) 2000-2007 Ibuildings.nl BV
 *
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 */

atkimport('atk.datagrid.atkdgcomponent');

/**
 * The data grid summary. Can be used to render a
 * summary for an ATK data grid.
 *
 * @author Peter C. Verhage <peter@achievo.org>
 * @package atk
 * @subpackage datagrid
 */
class atkDGSummary extends atkDGComponent
{
	/**
	 * Renders the summary for the given data grid.
	 *
	 * @param atkDataGrid $grid the data grid
	 * @return string rendered HTML
	 */
	public function render()
	{
		$grid = $this->getGrid();

		$limit = $grid->getLimit();
		$count = $grid->getCount();

		if ($count == 0)
		{
			return null;
		}

		if ($limit == -1)
		{
			$limit = $count;
		}

		$start = $grid->getOffset();
		$end = min($start + $limit, $count);
		$page = floor(($start / $limit) + 1);
		$pages = ceil($count / $limit);

		$string = $grid->text('datagrid_summary');

		$params = array(
	    'start' => $start + 1, 
	    'end' => $end, 
	    'count' => $count, 
	    'limit' => $limit, 
	    'page' => $page, 
	    'pages' => $pages
		);

		atkimport("atk.utils.atkstringparser");
		$parser = new atkStringParser($string);
		$result = $parser->parse($params);
		 

		// GG

		 
		global $g_user;
		$db = & atkGetDb();
		$userid = $g_user["id"];
		$sql="select prenom, nom , datagrid, datagrid_csv from individu, app_utilisateur where app_utilisateur.id=$userid and individu.id =app_utilisateur.id_individu";
		$data=$db->getrows($sql);
		$message='<b>'.$data[0]["prenom"].' '.$data[0]["nom"].'</b> le '.gmdate('c');
		$piedcsv='"'.$data[0]["prenom"].' '.$data[0]["nom"].' le '.gmdate('c').'",\n
		';
		$message.="<br></br><b>Module :</b> ";
		$message.=$grid->getNode()->atkNodeType();
		$piedcsv.='"Module :'.$grid->getNode()->atkNodeType().'",\n
		';
		$message.="<br></br><b>Filtre : </b>";
		$message.=$grid->getNode()->m_postvars['atkfilter'];
		$piedcsv.='"Filtre :'.$grid->getNode()->m_postvars['atkfilter'].'",\n
		';
		$message.="<br></br><b> Enregistrements : </b>";
		$message.=$result;
		$message.="<br></br>";
		$piedcsv.='"Enregistrements :'.$result.'",\n
		';
		$mestemp=str_replace('<br>','&&@@',$data[0]["datagrid"]);
		$mestemp=str_replace('</br>','&&/@@',$mestemp);
		$mestemp=$this->strip_only($mestemp,"<a><label><script><b><i>");
		$mestemp=str_replace('&&@@','<br>',$mestemp);
		$mestemp=str_replace('&&/@@','</br>',$mestemp);
		$message.=$mestemp;
		$message=escapeSql($message);
		
		$messagecsv=str_replace('<br>','
		',$data[0]["datagrid_csv"]);
		$messagecsv=strip_tags($messagecsv);
		$messagecsv=str_replace('&nbsp;',' ',$messagecsv);
		$messagecsv.=$piedcsv;
		$messagecsv=escapeSql($messagecsv);
		
		
		$sql="update app_utilisateur
		set datagrid='".$message."' 
		,datagrid_csv='".$messagecsv."' 
		where app_utilisateur.id=$userid ";
		$db->query($sql);

		$module = $grid->getNode()->m_module;
		$nodetype = $grid->getNode()->m_type;
		$link=' ==> '.'<a href="dispatch.php?atknodetype='.$module.'.'.$nodetype.'&atkaction=datagrid_view&" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/tableau_html.gif" alt="Tableau html" title="Tableau html"></a>';
		$link.=' <a href="dispatch.php?atknodetype='.$module.'.'.$nodetype.'&atkaction=datagrid_google_export&" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/tableur.gif" alt="Tableur Google" title="Tableur Google"></a>';
		$link.=' <a href="dispatch.php?atknodetype='.$module.'.'.$nodetype.'&atkaction=datagrid_google_texte_export&" target="_blank"><img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/texte.gif" alt="Texte Google" title="Texte Google"></a>';


		$result=substr($result,0 ,strlen($result)-1).' '.$link.' )';
		// GG Fin
		return $result;
	}
	function strip_only($str, $tags) {
    if(!is_array($tags)) {
        $tags = (strpos($str, '>') !== false ? explode('>', str_replace('<', '', $tags)) : array($tags));
        if(end($tags) == '') array_pop($tags);
    }
    foreach($tags as $tag) $str = preg_replace('#</?'.$tag.'[^>]*>#is', '', $str);
    return $str;
}
	
}
?>