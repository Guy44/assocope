<?php
$wikipediaURL = 'http://wikiservas.net/assocope/config.inc.php';
$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, $wikipediaURL);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_USERAGENT, 'Le site AssoCope (www.wikiwervas.net)');
$resultat = curl_exec ($ch);
curl_close($ch);