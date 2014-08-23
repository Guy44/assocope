<?php

function biodiversite_observation_descripteur($id_observation)
{
	$db = &atkGetDb();
	$data = $db->getrows(
	"SELECT  id_organisme_observateur,
	 id_observateur,
	  date_observation, 
	`id_type_localisation`,
	`latitude`,
	`longitude`,
	`id_ville`,
	`id_lieu`,
	`id_point_observation` 
	from biodiversite_observation 
	 where id=$id_observation") ;
	$id_organisme_observateur=$data[0]["id_organisme_observateur"];
	$id_observateur=$data[0]["id_observateur"];
	$date_observation=$data[0]["date_observation"];
	$id_ville=$data[0]["id_ville"];
	$id_lieu=$data[0]["id_lieu"];
	$id_point_observation=$data[0]["id_point_observation"];
	$ob_latitude=$data[0]["latitude"];
	$ob_latitude=$data[0]["longitude"];
	
	$data = $db->getrows(
	"SELECT  count(id) as compte
	from biodiversite_observation_detail
		 where id_observation=$id_observation") ;
	$nb_observations=$data[0]["compte"];
	
	$data = $db->getrows(
	"SELECT  nom 
	from organisme
		 where id=$id_organisme_observateur") ;
	$nom_organisme_observateur=$data[0]["nom"];	
	
	$data = $db->getrows(
	"SELECT  nom , prenom
	from individu
		 where id=$id_observateur") ;
	$nom_observateur=$data[0]["nom"];
	$prenom_observateur=$data[0]["prenom"];	
	
	if ( isset($id_ville)	)
	{
	$data = $db->getrows(
	"SELECT  ville, code_postal, tp.code_iso, longitude, latitude 
	from type_cp_ville_pays, type_pays tp
		 where id=$id_ville and id_pays=tp.id)") ;
	$longitude=$data[0]["longitude"];
	$latitude=$data[0]["latitude"];
	$nom_ville=$data[0]["ville"];
	$code_postal=$data[0]["$code_postal"];		
	$code_pays=$data[0]["code_iso"];
	$lieu=$code_postal.' '.$nom_ville.' '.$code_pays.'<br />';		
	}
	
	if ( isset($id_lieu)	)
	{
	$data = $db->getrows(
	"SELECT  l.adresse1, l.adresse2, l.longitude, l.latitude, cp.ville, cp.code_postal,tp.code_iso 
	from lieu l, type_cp_ville_pays cp, type_pays tp
		 where l.id=$id_lieu
		 and l.id_ville.cp.id
		  and cp.id_pays=tp.id)") ;
	$longitude=$data[0]["longitude"];
	$latitude=$data[0]["latitude"];
	$adresse1=$data[0]["adresse1"];
	$adresse2=$data[0]["adresse2"];
	$nom_ville=$data[0]["ville"];
	$code_postal=$data[0]["$code_postal"];		
	$code_pays=$data[0]["code_iso"];
	$lieu=$adresse1.' '.$code_postal.' '.$nom_ville.' '.$code_pays.'<br />';			
	}
	
	if ( isset($id_point_observation)	)
	{
	$data = $db->getrows(
	"SELECT po.libelle, l.adresse1, l.adresse2, l.longitude, l.latitude, cp.ville, cp.code_postal,tp.code_iso 
	from biodivezrsite_point_observation po, lieu l, type_cp_ville_pays cp, type_pays tp
		 where po.id=$id_point_observation
	and po.id_lieu=l.id
		 and l.id_ville.cp.id
		  and cp.id_pays=tp.id)") ;
	$longitude=$data[0]["longitude"];
	$latitude=$data[0]["latitude"];
	$libelle_point_observation=$data[0]["libelle"];
	$adresse1=$data[0]["adresse1"];
	$adresse2=$data[0]["adresse2"];
	$nom_ville=$data[0]["ville"];
	$code_postal=$data[0]["$code_postal"];		
	$code_pays=$data[0]["code_iso"];
	$lieu=$libelle_point_observation.' '.$adresse1.' '.$code_postal.' '.$nom_ville.' '.$code_pays.'<br />';			
	}

	if ( isset($ob_latitude)	)
	{
	$latitude=$ob_latitude;	
	$lieu=$latitude;
	}
	
	if ( isset($ob_longitude)	)
	{
	$longitude=$ob_longitude;
	$lieu.=' '.$longitude;		
	}	
	
	$descripteur=$date_observation;
	$descripteur.="<br />";
	$descripteur.=$nom_organisme_observateur;
	$descripteur.="<br />";	
	$descripteur.=$nom_observateur.' '.$prenom_observateur;
	$descripteur.="<br />";
	$descripteur.=$lieu;
	$descripteur.="<br />";
	$descripteur.=$nb_observations;
	$descripteur.="<br />";
	
	
	
	return  $descripteur;

}

?>
