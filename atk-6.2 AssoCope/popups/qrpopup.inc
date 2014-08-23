<?php

  include_once($config_atkroot."atk.inc");

  atksession();
  atksecure();
  $type = $_GET["type"];
  $id_entite = $_GET["id"];
  
  $title=$type;
  $node = new assmetanode();
  if ($type=='individu')
  { 	$retour=$node->descripteur_individu($id_entite,'n','o','0','popup').'<br />'.'<br />';
  	$retour.=$node->descripteur_individu($id_entite,'c','n'); 
  
  	(($node->get_acces_restreint())==false) ? $retour.="<br/>".$node->table_operations("individu.individu","individu",$id_entite,"_blank" ):null;
$db = & atkGetDb();
$sql="SELECT id_document_portrait, id_document_signature, id_creation, id_modification, date_creation, date_modification from individu  where id=$id_entite";
$row=$db->getrows($sql);
$id_portrait=$row[0]["id_document_portrait"];
$id_signature=$row[0]["id_document_signature"];
$id_modification=$row[0]["id_modification"];
$id_creation=$row[0]["id_creation"];
$date_creation=$row[0]["date_creation"];
$date_modification=$row[0]["date_modification"];
$sql="SELECT concat(prenom,' ', nom) as nom_creation from individu i, app_utilisateur u  where u.id=$id_creation and u.id_individu=i.id";
$row=$db->getrows($sql);
$nomcreation=$row[0]["nom_creation"];
$sql="SELECT concat(prenom,' ', nom) as nom_modification from individu i, app_utilisateur u  where u.id=$id_modification and u.id_individu=i.id";
$row=$db->getrows($sql);
$nommodification=$row[0]["nom_modification"];


 		if (!empty($id_portrait))
			{
					$sql="select file_content,file_name, file_size from organisme_document where id=$id_portrait";
		$data=$db->getrows($sql);
		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		$filename=$data[0]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[0]["file_content"]="";
		$retour.='<br /><br /><img  border="0" src="'.$url.'" alt="Portrait"
				title="Portrait" width="150px"></img><br />';	
			}
   		if (!empty($id_signature))
			{
					$sql="select file_content,file_name, file_size from individu_document where id=$id_signature";
		$data=$db->getrows($sql);

		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		$filename=$data[0]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[0]["file_content"]="";
		$retour.='<br /><br /><img  border="0" src="'.$url.'" alt="Signature"
				title="Signature" width="150px"></img><br />';	
			}
//		if (!empty($data[0]["id_document_portrait"]))
  }
if ($type=='organisme')
{
	$retour=$node->descripteur_organisme($id_entite,'n','o','0','popup').'<br />'.'<br />';
$retour.=$node->descripteur_organisme($id_entite,'c','n').'<br />';
(($node->get_acces_restreint())==false) ? $retour.="<br/>".$node->table_operations("organisme.organisme","organisme",$id_entite ,"_blank"):null;
$sql="select od.libelle, ti.libelle as type, od.file_content,od.file_name, od.file_size 
from organisme_image od , type_image ti
where 
od.id_entite=$id_entite
and id_type_entite=1 
and od.id_type_image=ti.id
and od.actif_o_n='1'";


		$db = & atkGetDb();
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
		
		$data[$i]["file_content"]=base64_decode($data[$i]["file_content"]);
		$filename=$data[$i]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[$i]["file_content"],$data[$i]["file_size"]);
		@fclose($file);
		$data[$i]["file_content"]="";
		$legende=$data[$i]["type"]." : ".$data[$i]["libelle"];
		$retour.='<br />'.$legende;
		$retour.='<br /><img  border="0" src="'.$url.'" alt="'.$legende.'"
				title="'.$legende.'"  width="150px"></img><br />';		
		}
}
if ($type=='individu')
{
$sql="select od.libelle, ti.libelle as type, od.file_content,od.file_name, od.file_size 
from organisme_image od , type_image ti
where 
od.id_entite=$id_entite
and id_type_entite=2 
and od.id_type_image=ti.id
and od.actif_o_n='1'";


		$db = & atkGetDb();
		$data=$db->getrows($sql);
		for ($i = 0; $i < count($data); $i++) {
		
		$data[$i]["file_content"]=base64_decode($data[$i]["file_content"]);
		$filename=$data[$i]["file_name"];
		$url="./documents/".$filename;
		$file =@fopen($url,"w");
		@fwrite($file,$data[$i]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[$i]["file_content"]="";
		$legende=$data[$i]["type"]." : ".$data[$i]["libelle"];
		$retour.='<br />'.$legende;
		$retour.='<br /><img  border="0" src="'.$url.'" alt="'.$legende.'"
				title="'.$legende.'"  width="150px"></img><br />';		
		}
		
		$retour.= "<br/><br/></b>Créé le <b>".$date_creation."</b> par <b>".$nomcreation."</b>";
		$retour.= "<br/></b>Modifié le <b>".$date_modification."</b> par <b>".$nommodification."</b>";


}

  $page = &atknew("atk.ui.atkpage");
  $ui = &atkinstance("atk.ui.atkui");

  $output = &atkOutput::getInstance();

  $page->register_style($ui->stylePath("style.css"));
  $res='<div align="right"><a href="javascript:window.close();">'.atktext("close").'</a></div><br />';

  $res .= $ui->renderBox(array("title"=>$title,
                                 "content"=>$retour));
  $res.='<br><div align="right"><a href="javascript:window.close();">'.atktext("close").'</a></div>';

  $page->addContent($res);

  $output->output($page->render(atktext('app_title').' - '.atktext('qr-popup'), true));

  $output->outputFlush();

?>