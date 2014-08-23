<?php

useattrib("atkdummyattribute");

  /**
   * This file is part of the Achievo ATK distribution.
   * Detailed copyright and licensing information can be found
   * in the doc/COPYRIGHT and doc/LICENSE files which should be
   * included in the distribution.
   *
   * @package atk
   * @subpackage attributes
   *
   * @copyright (c)2000-2004 Ibuildings.nl BV
   * @license http://www.achievo.org/atk/licensing ATK Open Source License
   *
   */

  /**
   * The atkGoogleMapsAttribute can be used to diplay Google Maps.
   *
   * @author Rik Willems <rik@actiview.nl>
   * @package atk
   * @subpackage attributes
   *
   */
class atkGoogleMapsAttribute extends atkDummyAttribute
{

    var $m_text;

    /**
     * Constructor
     * @param string $name Name of the attribute
     * @param string $text text field
     * @param int $flags Flags for this attribute
     */
    function atkGoogleMapsAttribute($name, $size=array(), $flags=0)
    {
		$this->atkDummyAttribute($name,'',$flags|AF_HIDE_LIST | AF_NO_LABEL | AF_HIDE_SEARCH | AF_NO_SORT); // base class constructor
		
		$this->m_size = $size;
		
    }
		
    /**
     * Parses a record
     * 
     * @param array $record The record that holds the value for this attribute.
     * @param String $fieldprefix The fieldprefix to put in front of the name
     *                            of any html form element for this attribute.
     * @param String $mode The mode we're in ('add' or 'edit')
     * @return Parsed string
     */
    function edit($record="", $fieldprefix="", $mode="")
    {
      return $this->display($record);
    }


    /**
     * Parses a record
     * @param array $record  Array with fields
     * @return Parsed string
     */
    function display($record)
    {
	
		atkimport("atk.utils.atkstringparser");
		$stringparser = new atkStringParser('[latitude],[longitude]');
		$latlng = $stringparser->parse($record);

		$page = &$this->m_ownerInstance->getPage();
		$page->register_script('http://maps.google.com/maps?file=api&v=2&key='.atkconfig('googlemapskey').'&sensor=false');
		$page->register_scriptcode($this->getJavascript($latlng));
  		$page->register_loadscript('initialize()');

		return '<div id="map_canvas" style="width: '.(($this->m_size['width']) ? $this->m_size['width'] : '600px') .'px; height: '.(($this->m_size['height']) ? $this->m_size['height'] : '400px') .'px"></div>';
	  
    }


	function getJavascript($latlng) {

		$latlng = str_replace(' ','', $latlng);
		if ( $latlng == ',' ) {
			$latlng = atkconfig('googlemapsdefaultcenter');
			$zoom = 11;
		}
		else $zoom = 15;
	
		$return = "	

			var map;
			var geocoder;
			var address;

			function initialize() {
				map = new GMap2(document.getElementById('map_canvas'));
				var center = new GLatLng($latlng);
				map.setCenter(center, $zoom);
				map.setUIToDefault();

				var markerD2 = new GMarker(center, {icon: new GIcon(G_DEFAULT_ICON, '".atkconfig('googlemapsmarker')."'), draggable: true}); 
				map.addOverlay(markerD2);
				markerD2.enableDragging();

				GEvent.addListener(markerD2, 'dragend', function(){
					if ( document.forms['entryform'].elements['latitude'] ) document.forms['entryform'].elements['latitude'].value = markerD2.getPoint().lat();
					if ( document.forms['entryform'].elements['longitude'] ) document.forms['entryform'].elements['longitude'].value = markerD2.getPoint().lng();
				});

				geocoder = new GClientGeocoder();
				
			}
			
			function getAddress(overlay, latlng) {
				if (latlng != null) {
					address = latlng;
					geocoder.getLocations(latlng, showAddress);
				}
			}

			function showAddress(response) {

				map.clearOverlays();
				if (!response || response.Status.code != 200) {
					alert('Status Code:' + response.Status.code);
				} 
				else {
					place = response.Placemark[0];
					point = new GLatLng(place.Point.coordinates[1],
										place.Point.coordinates[0]);
					//marker = new GMarker(point,{draggable: true});
					//map.addOverlay(marker);
					marker.openInfoWindowHtml(
						'<b>orig latlng:</b>' + response.name + '<br/>' + 
						'<b>latlng:</b>' + place.Point.coordinates[1] + ',' + place.Point.coordinates[0] + '<br>' +
						'<b>Status Code:</b>' + response.Status.code + '<br>' +
						'<b>Status Request:</b>' + response.Status.request + '<br>' +
						'<b>Address:</b>' + place.address + '<br>' +
						'<b>Accuracy:</b>' + place.AddressDetails.Accuracy + '<br>' +
						'<b>Country code:</b> ' + place.AddressDetails.Country.CountryNameCode);
					}
					
					if ( document.forms['entryform'].elements['latitude'] ) document.forms['entryform'].elements['latitude'].value = place.Point.coordinates[1];
					if ( document.forms['entryform'].elements['longitude'] ) document.forms['entryform'].elements['longitude'].value = place.Point.coordinates[0];

				}
			
			
	
		";
		
		return $return;
	}

}

?>