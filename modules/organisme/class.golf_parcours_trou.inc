<?php
	atkimport("atk.assmetanode");
	useattrib("development.atgtextlibelleattribute");
	useattrib("development.atgFileManyToOneRelation");
	
class golf_parcours_trou extends assMetaNode
{
	var $table="organisme_golf_parcours_trou";

function meta(&$policy)
  {

	$policy-> addFlags("libelle",AF_SEARCHABLE);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);

	$policy-> addFlags("commentaire",AF_HIDE_LIST);

}
function golf_parcours_trou()
{
  	$this->atkMetaNode();
  	$this->atkNode("golf_parcours_trou", NF_ADD_LINK| NF_ADDAFTERADD);
	$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (

  "id_organisme_parcours",
  "libelle",
  "numero_trou",
  "distance_blanc",
  "distance_jaune",
  "distance_bleu",
  "distance_rouge",
  "par",
  "coups_recus",
  "temps_de_jeu",
  "id_document_photo",
  "consignes"
				)
				), AF_NO_LABEL));
				
	$this->add(new atkManyToOneRelation("id_organisme_parcours","organisme.golf_parcours",AF_RELATION_AUTOLINK),10); 
	$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),20);
	$this->add(new atkNumberAttribute("numero_trou", AF_SEARCHABLE,2,0),30);
	$this->add(new atkNumberAttribute("distance_blanc", AF_SEARCHABLE,4,0),40);
	$this->add(new atkNumberAttribute("distance_jaune", AF_SEARCHABLE,4,0),50);
	$this->add(new atkNumberAttribute("distance_bleu", AF_SEARCHABLE,4,0),60);
	$this->add(new atkNumberAttribute("distance_rouge", AF_SEARCHABLE,4,0),70);
	$this->add(new atkNumberAttribute("par", AF_SEARCHABLE,1,0),80);
	$this->add(new atkNumberAttribute("coups_recus", AF_SEARCHABLE,2,0),90);
	$this->add(new atkTimeAttribute("temps_de_jeu",0,23,1),100);
	$this->add(new atgFileManyToOneRelation("id_document_photo","organisme.document",AF_HIDE_LIST|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),110); 
	$this->add(new atkfckattribute("consignes","", AF_HIDE_LIST,array(
                 'ToolbarSet'=>'Default',
                 'Width'=>'100%',
                 'Height'=>'150px')),120);
	include_once(atkconfig("atkroot")."modules/include/association.inc");	

$this->setOrder(" numero_trou ASC ");

  }
function descriptor_def()
  {
 //   return " [id]-trou [numero_trou] ";
        return " [id]";
  }
/*function id_organisme_parcours_display($record, $mode) {
		(!empty($record["id_organisme_parcours"])) ? $retour=$this->descripteur_organisme($record["id_organisme_parcours"]["id"],'n') : $retour="";
		return $retour;
	}
	*/
}

?>