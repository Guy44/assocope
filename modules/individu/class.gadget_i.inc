<?php

class gadget_i extends atkNode
{
	function gadget_i()
	{
		$this->atkNode("gadget_i",NF_NO_SECURITY);
	}

	function action_gadget_i(&$handler)
	{$res='<table border=2 width:800px>';
	$res.='<tr>';
	$res.='<td>';
	// calendrier
	$res.='<b>Calendrier</b><br /><iframe id="remote_iframe_88" name="remote_iframe_88" style="border:0;padding:0;margin:0;width:300px;height:400px;overflow:hidden" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://www.google.com/calendar/ig?up_calendarFeeds=(mariefrancoise.gourmellet%2540gmail.com,lescailleries.org_t70o2ie6tsf3nksu6k2dhcuchs%2540group.calendar.google.com,guy.gourmellet%2540gmail.com,amicale44.org_d947846jdqo6t8ksf308lu2mls%2540group.calendar.google.com,lescopainsdelile.org_1m737hnbvn0vekcl71ca7a6vqo%2540group.calendar.google.com)&amp;up_calendarColors=(%23AB8B00,%2388880E,%23A32929,%234A716C,%2328754E)&amp;up_firstDay=1&amp;up_dateFormat=1&amp;up_timeFormat=13:00&amp;up_showDatepicker=1&amp;up_hideAgenda=0&amp;up_showEmptyDays=0&amp;up_showExpiredEvents=true&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=88&amp;ifpctok=3342125309049394907&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;libs=DoXS5gxhejE/lib/liberror_tracker.js,mWuUtp2ZV1Y/lib/librpc.js,tjNv-0-mtdo/lib/libcore.js,SQEJmuqdFVs/lib/libdynamic-height.js,iNE3XEZGB9I/lib/libsetprefs.js,NXPKwAquBT0/lib/libviews.js&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;view=home&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Messagerie</b><br /><iframe name="remote_iframe_87" id="remote_iframe_87" style="border:0;margin:0;padding:0;overflow:hidden;width:300px;height:400px" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="https://mail.google.com/mail/ig/mailhome?hl=fr&amp;mid=87&amp;parent=http://www.google.com&amp;ifpctok=6692602817065892376&amp;ver=2"></iframe>';
	$res.='</td><td>';
	// documents
	$res.='<b>Documents</b><br /><iframe id="remote_iframe_91" name="remote_iframe_91" style="border:0;padding:0;margin:0;width:300px;height:400px;overflow:hidden" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="https://docs.google.com/API/IGoogle?up_numDocuments=5&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=91&amp;ifpctok=-4304639650511770285&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;libs=DoXS5gxhejE/lib/liberror_tracker.js,mWuUtp2ZV1Y/lib/librpc.js,tjNv-0-mtdo/lib/libcore.js,SQEJmuqdFVs/lib/libdynamic-height.js&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;view=home&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Tâches</b><br /><iframe id="remote_iframe_90" name="remote_iframe_90" style="border:0;padding:0;margin:0;width:300px;height:400px;overflow:hidden" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="https://mail.google.com/tasks/ig?up_ShowTips=false&amp;up_CurrentListId=04728610879587351257:0:0&amp;up_CurrentViewType=&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=90&amp;ifpctok=701776129584276496&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;libs=DoXS5gxhejE/lib/liberror_tracker.js,mWuUtp2ZV1Y/lib/librpc.js,tjNv-0-mtdo/lib/libcore.js,iNE3XEZGB9I/lib/libsetprefs.js&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;view=home&amp;is_signedin=1"></iframe>';
	$res.='</td></tr><tr><td>';
	// Maps
	$res.='<b>Maps</b><br /><iframe id="remote_iframe_80" name="remote_iframe_80" style="border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left: 0px; width: 100%; overflow-x: hidden; overflow-y: hidden; height: 300px; " frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://www.gmodules.com/ig/ifr?view=home&amp;url=http://www.google.com/uds/modules/elements/localsearch/localsearch.xml&amp;nocache=0&amp;up_location=&amp;up_largeMapMode=1&amp;up_kml=0&amp;up_traffic=&amp;up_locationCacheString=&amp;up_locationCacheLat=&amp;up_locationCacheLng=&amp;up_mapType=k&amp;up_idleZoom=11&amp;up_transitionQuery=&amp;up_rawquery=&amp;up_selectedtext=&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=80&amp;ifpctok=-432767172475834193&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Albums</b><br /><iframe id="remote_iframe_93" name="remote_iframe_93" style="border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left: 0px; width: 300px; overflow-x: hidden; overflow-y: hidden; height: 300px; " frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://ig.gmodules.com/gadgets/ifr?view=home&amp;url=http://www.google.com/ig/modules/picasa.xml&amp;nocache=0&amp;up_feed=http://picasaweb.google.com/data/feed/base/user/guy.gourmellet%3Falt%3Drss%26kind%3Dalbum%26hl%3Dfr&amp;up_title=Photos+Guy&amp;up_gallery=&amp;up_desc=1&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=93&amp;ifpctok=2140904001148611488&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;refresh=3600&amp;libs=core:core.io:core.iglegacy:auth-refresh&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Météo</b><br /><iframe id="remote_iframe_92" name="remote_iframe_92" style="border:0;padding:0;margin:0;width:300px;height:300px;overflow:auto" frameborder="0" scrolling="auto" onload="_ifr_ol(this)" src="http://ig.gmodules.com/gadgets/ifr?view=home&amp;url=http://www.30minutelunchbreak.com/gadgets/meteopr.xml&amp;nocache=0&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=92&amp;ifpctok=6091062077749736176&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;refresh=3600&amp;libs=core:core.io:core.iglegacy:auth-refresh&amp;extern_js=/extern_js/f/CgJmchICdXMrMNIBOALbAeABAdwB2wHgAQDcASxQAXgBwAEB0AEB/SNlwtazbUSQ.js&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Annuaire téléphonique</b><br /><iframe id="remote_iframe_84" name="remote_iframe_84" style="border:0;padding:0;margin:0;width:300px;height:300px;overflow:hidden" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://ig.gmodules.com/gadgets/ifr?view=home&amp;url=http://widget.annuaire-widget.com/annuaire/google/annuaire.xml&amp;nocache=0&amp;up__fe_track_Annuaire_telephonique=&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=84&amp;ifpctok=6897124735163051053&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;refresh=3600&amp;libs=core:core.io:core.iglegacy:auth-refresh&amp;is_signedin=1"></iframe>';
		$res.='</td></tr><tr><td>';
			$res.='<b>Recettes</b><br /><iframe id="remote_iframe_94" name="remote_iframe_94" style="border:0;padding:0;margin:0;width:300px;height:400px;overflow:hidden" frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://ig.gmodules.com/gadgets/ifr?view=home&amp;url=http://www.elle.fr/extension/la_fluxwidget/design/elle/stylesheets/igoogle/widget_eat.xml&amp;nocache=0&amp;up_current_state=jour&amp;up_search_text=&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=94&amp;ifpctok=-6472201276669540436&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;refresh=3600&amp;libs=core:core.io:core.iglegacy:auth-refresh&amp;is_signedin=1"></iframe>';
	$res.='</td><td>';
	$res.='<b>Itinéraires</b><br /><iframe id="remote_iframe_95" name="remote_iframe_95" style="border-top-width: 0px; border-right-width: 0px; border-bottom-width: 0px; border-left-width: 0px; border-style: initial; border-color: initial; padding-top: 0px; padding-right: 0px; padding-bottom: 0px; padding-left: 0px; margin-top: 0px; margin-right: 0px; margin-bottom: 0px; margin-left: 0px; overflow-x: hidden; overflow-y: hidden; height: 91px; width: 100%; " frameborder="0" scrolling="no" onload="_ifr_ol(this)" src="http://ig.gmodules.com/gadgets/ifr?view=home&amp;url=http://www.google.com/ig/modules/driving_directions.xml&amp;nocache=0&amp;lang=fr&amp;country=us&amp;.lang=fr&amp;.country=us&amp;synd=ig&amp;mid=95&amp;ifpctok=-7420913022789581715&amp;exp_rpc_js=1&amp;exp_track_js=1&amp;exp_ids=17259,300891&amp;parent=http://www.google.com&amp;refresh=3600&amp;libs=core:core.io:core.iglegacy:auth-refresh&amp;is_signedin=1&amp;up_from=stanyan%20st%2C%20san%20francisco&amp;up_to=twin%20peaks%20blvd%2C%20san%20francisco&amp;up_country=12"></iframe>';

			
			$res.='</td></tr>';
	$res.='</table>';
	$page = &$this->getPage();



	$page->addContent($res);
	//                      print_r($content);
	//      die();
	}

}

?>