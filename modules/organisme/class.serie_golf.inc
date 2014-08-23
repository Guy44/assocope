<?php
	atkimport("atk.assmetanode");
	useattrib("development.atgtextlibelleattribute");

class serie_golf extends assMetaNode
{
	var $table="organisme_serie_golf";

function meta(&$policy)
  {
	$policy-> addFlags("commentaire",AF_HIDE_LIST);
	$policy-> addFlags("id_creation","date_creation","id_modification","date_modification",AF_READONLY);
}
function serie_golf()
{
  	$this->atkMetaNode();
  	$this->atkNode("serie_golf", NF_ADD_LINK |NF_ADDAFTERADD);

	$this->add(new atkManyToOneRelation("id_organisme","organisme.organisme",AF_SEARCHABLE|AF_OBLIGATORY|AF_RELATION_AUTOLINK|AF_RELATION_AUTOCOMPLETE),10); 
					$this->add(new atkNumberAttribute("numero", AF_SEARCHABLE, 2,0),20);
	$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE),null,30);
				$this->add(new atkNumberAttribute("index_haut", AF_SEARCHABLE, 2, 1),40);
				$this->add(new atkNumberAttribute("index_bas", AF_SEARCHABLE, 2, 1),50); 

	include_once(atkconfig("atkroot")."modules/include/association.inc");	
	$this->setSecurityAlias("organisme.organisme");

	//$this->setIndex("libelle");
  }
function descriptor_def()
  {
    return "[numero] - [libelle]";
  }
function descripteur($record)
	{

		$href=href(dispatch_url("organisme.serie_golf", "edit", array (	'atkselector' => "rganisme_serie_golf.id='" . $record["id"]. "'"
		), "dispatch.php"), $record["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/categorie_golf-icon.png" alt="Série golf"
			title="Série golf"  ></img>'.' <b>'.$href." ";
		$retour.="<br/>".$this->descripteur_organisme($record["id_organisme"]["id"],'n');
		$retour.='<br/>'.$this->descripteur_aide('Descripteur_serie_golf','n');

		return $retour;
			}

function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

}

?>