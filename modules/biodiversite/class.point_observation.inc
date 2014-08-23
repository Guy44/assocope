<?php
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgomanytoonerelation");
useattrib("development.atgNumberExpressionAttribute");
useattrib("development.atgFileManyToOneRelation");
class point_observation extends assMetaNode {
	var $table = "biodiversite_point_observation";
	function meta(& $policy) {
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function point_observation() {
		$this->atkMetaNode();
		$this->atkNode("point_observation", NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"id_organisme",
				"id_individu_correspondant",
				"id_lieu",
				"telephone",
				"description_html",
				"id_document_1",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				)
				/*,
				 "Rencontres" => array (
				 "rencontre"
				 )
				 ,
				 "Groupes_de_travail" => array (
				 "groupe"
				 )
				 */
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE),100);
				$this->add(new atgOManyToOneRelation("id_organisme", "organisme.organisme", AF_SEARCHABLE | AF_OBLIGATORY | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),200);
				$this->add(new atkManyToOneRelation("id_individu_correspondant", "individu.individu", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),300);
				$this->add(new atkManyToOneRelation("id_lieu", "individu.lieu", AF_SEARCHABLE | AF_RELATION_AUTOLINK| AF_RELATION_AUTOCOMPLETE ),400);
				$this->add(new atkDummyAttribute("latlon",0 ),405);
				$this->add(new atkAttribute("telephone", AF_SEARCHABLE ),900);
				$this->add(new atgFileManyToOneRelation("id_document_1", "organisme.document",  AF_HIDE_LIST  |AF_RELATION_AUTOLINK | AF_RELATION_AUTOCOMPLETE),1400);
				$this->add(new atkfckattribute("description_html", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '300px'
			)),1300);
			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->setOrder("libelle");
			$this->setIndex("libelle");
	}
	function telephone_display($record,$mode)
	{
		return '<a href="tel:' . $record["telephone"] . ';">' . $record["telephone"] . '</a>';
	}

	function latlon_display($record, $mode) {
		$db = & atkGetDb();
		$sql='SELECT latitude, longitude from biodiversite_point_observation lr , lieu l
					where lr.id='.$record[id].' and lr.id_lieu=l.id ' ;
		$stuff=$db->getrows($sql);
		//		$stuff[0]["latitude"]=substr($stuff[0]["latitude"],0, strlen($stuff[0]["latitude"])-6).'.'.substr($stuff[0]["latitude"],strlen($stuff[0]["latitude"])-6,6);
		//		$stuff[0]["longitude"]=substr($stuff[0]["longitude"],0, strlen($stuff[0]["longitude"])-6).'.'.substr($stuff[0]["longitude"],strlen($stuff[0]["longitude"])-6,6);
		$ret= $stuff[0]["latitude"]."<br />".$stuff[0]["longitude"];
		if ($stuff[0]["latitude"]=="")
		{$carte="";}
		else
		{$carte='<font color="ForestGreen"><b>Géolocalisation</b></font>';}
		return href("http://maps.google.com/maps?q=".$stuff[0]["latitude"].",".$stuff[0]["longitude"], atktext($carte), SESSION_NEW, false, 'target="_blank"') ;
	}

	function action_admin($handler) {
		global $config_recordsperpage;
		$config_recordsperpage = 50;
		return $handler->action_admin();
	}
	function descriptor_def() {
		return "([id_organisme.nom]) [libelle] ";
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions['delete'] = "delete";
	}
function id_individu_correspondant_display($record, $mode) {
		(!empty($record["id_individu_correspondant"])) ? $retour=$this->descripteur_individu($record["id_individu_correspondant"]["id"],'n') : $retour="";
		return $retour;
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}

}
?>