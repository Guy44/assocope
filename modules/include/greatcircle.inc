<?php


//degree format 121°8'6"  degrees°  minutes'  seconds"
//decimal format 121.135 
//accepts a coordinate in degree format and returns the equivalent decimal
//N & S are latitudes
//E & W are longitudes
//South latitudes and West longitudes are negative decimals
//calling examples   
//degree2decimal('121°8‘6"N'); returns  121.135
//degree2decimal('121°8‘6"S'); returns -121.135
//degree2decimal('121°8‘6"E'); returns  121.135
//degree2decimal('121°8‘6"W'); returns -121.135
function degree2decimal($deg_coord = "") {
	$dpos = strpos($deg_coord, '°');
	$mpos = strpos($deg_coord, "'");
	$spos = strpos($deg_coord, '"');
	$mlen = (($mpos - $dpos) -1);
	$slen = (($spos - $mpos) -1);
	$direction = substr(strrev($deg_coord), 0, 1);
	$degrees = substr($deg_coord, 0, $dpos);
	$minutes = substr($deg_coord, $dpos +1, $mlen);
	$seconds = substr($deg_coord, $mpos +1, $slen);
	$seconds = ($seconds / 60);
	$minutes = ($minutes + $seconds);
	$minutes = ($minutes / 60);
	$decimal = ($degrees + $minutes);
	//South latitudes and West longitudes need to return a negative result
	if (($direction == "S") or ($direction == "W")) {
		$decimal = $decimal * (-1);
	}
	return $decimal;
}

//accepts a coordinate in decimal format and returns the equivalent degree
//as a string
//calling examples
//decimal2degree('121.135,'LAT');  will return 121°8‘6"N
//decimal2degree('-121.135,'LAT');  will return 121°8‘6"S
//decimal2degree('121.135,'LON'); will return 121°8‘6"E
//decimal2degree('-121.135,'LON'); will return 121°8‘6"W
function decimal2degree($decimal_coord = "", $latorlon = "") {
	//121.135
	//degrees=121
	//minutes=.135*60=(8).1
	//seconds=.1*60=(6)
	//121°8‘6"
	$decpos = strpos($decimal_coord, '.');
	$whole_part = substr($decimal_coord, 0, $decpos);
	$decimal_part = abs($decimal_coord - $whole_part);
	$minutes = intval($decimal_part * 60);
	$seconds = intval((($decimal_part * 60) - $minutes) * 60);
	if ($latorlon == 'LAT') {
		if ($whole_part < 0) {
			$whole_part = ($whole_part * (-1));
			$L = 'S';
		} else {
			$L = 'N';
		}
	} //end if
	else {
		if ($latorlon == 'LON') {
			if ($whole_part < 0) {
				$whole_part = ($whole_part * (-1));
				$L = 'W';
			} else {
				$L = 'E';
			}
		} //end if
	} //end if
	$degree = $whole_part . '°' . $minutes . '\'' . $seconds . '"';
	$degree .= $L;
	return $degree;
}

//accepts two decimal latitude, longitude coordinates and returns the distance
//between the two
function decimal_distance($lat1 = "", $lon1 = "", $lat2 = "", $lon2 = "") {
	//$radius is determined using the following formula
	//(360 degrees)*(60 minutes per degree)*(1.852) km per minute 
	//give a circumference of 40003.2 km 
	//radius is circumference/(2*pi) which gives us 6637km or 3956miles
	$radius = 6637;
	$lat1 = deg2rad($lat1);
	$lat2 = deg2rad($lat2);
	$lon1 = deg2rad($lon1);
	$lon2 = deg2rad($lon2);
	//Haversine Formula (from R.W. Sinnott, "Virtues of the Haversine", 
	//Sky and Telescope, vol. 68, no. 2, 1984, p. 159): 
	$dlon = $lon2 - $lon1;
	$dlat = $lat2 - $lat1;
	$sinlat = sin($dlat / 2);
	$sinlon = sin($dlon / 2);
	$a = ($sinlat * $sinlat) + cos($lat1) * cos($lat2) * ($sinlon * $sinlon);
	$c = 2 * asin(min(1, sqrt($a)));
	$d = $radius * $c;
	//
	return round($d, 3);
}

//accepts two degree latitude, longitude coordinates and returns the distance
//between the two
function degree_distance($lat1 = "", $lon1 = "", $lat2 = "", $lon2 = "") {
	$lat1 = degree2decimal($lat1);
	$lat2 = degree2decimal($lat2);
	$lon1 = degree2decimal($lon1);
	$lon2 = degree2decimal($lon2);
	$distance = decimal_distance($lat1, $lon1, $lat2, $lon2);
	return $distance;
}
function compute_heading($lat1 = "", $lon1 = "", $lat2 = "", $lon2 = "") {
	$distnext = decimal_distance($lat1, $lon1, $lat2, $lon2);
	$dist1 = decimal_distance($lat1, $lon1, $lat2, $lon1);
	$dist2 = decimal_distance($lat1, $lon1, $lat1, $lon2);
	$headnext = rad2deg(acos((($dist1 * $dist1) + ($distnext * $distnext) - ($dist2 * $dist2)) / (2 * $dist1 * $distnext)));
	if ($lon2 > $lon1) {
		if ($lat2 > $lat1) {
			$headnext = $headnext;
		} else {
			$headnext = 180 - $headnext;
		}
	} else {
		if ($lat2 < $lat1) {
			$headnext = 180 + $headnext;
		} else {
			$headnext = 360 - $headnext;
		}
	}

	return round($headnext, 1);
}
?>