<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class categorie_golf extends assMetaNode {
	var $table = "type_categorie_golf";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);
	}
	function categorie_golf() {
		$this->atkMetaNode();
		$this->atkNode("categorie_golf",  NF_ADD_LINK | NF_ADDAFTERADD | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->add(new atkTabbedPane("Pane1", array (
			"Général" => array (
				"libelle",
				"commentaire",
				"id_creation",
				"date_creation",
				"id_modification",
				"date_modification"
				),
			"Cartes" => array (
				"cartes"
				)
				), AF_NO_LABEL));
				$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE),null,5);
				$this->add(new atkNumberAttribute("index_haut", AF_SEARCHABLE, 2, 1));
				$this->add(new atkNumberAttribute("index_bas", AF_SEARCHABLE, 2, 1));
				$this->add(new atkNumberAttribute("coefficient_performance", AF_SEARCHABLE, 2, 1));
				$this->add(new atkNumberAttribute("coefficient_contre_performance", AF_SEARCHABLE, 2, 1));
				$this->add(new atkNumberAttribute("zone_tampon", AF_SEARCHABLE, 2, 0));
				$this->add(new atkOneToManyRelation("cartes", "individu.carte_golf", "id_type_categorie_golf", AF_HIDE_LIST));
				include_once (atkconfig("atkroot") . "modules/include/association.inc");
				$this->add(new atkDummyAttribute("descripteur_module_estampillage",'text',AF_HIDE_ADD | AF_HIDE_EDIT  | AF_NO_LABEL),null,6 );
				$this->setIndex("libelle");
				$this->setOrder("libelle");
	}
		function descriptor_def() {
		return "[libelle]";
		}
	
	function descripteur($record)
	{

		$href=href(dispatch_url("table.categorie_golf", "edit", array (	'atkselector' => "type_categorie_golf.id='" . $record["id"]. "'"
		), "dispatch.php"), $record["libelle"], SESSION_NESTED);
		$retour='<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/categorie_golf-icon.png" alt="Catégorie golf"
			title="Catégorie golf"  ></img>'.' <b>'.$href." ";
		$retour.="<br/></b>Index bas/haut : <b>".$record["index_bas"]."/".$record["index_haut"];
		$retour.="<br/></b>Coefficient performance : <b>".$record["coefficient_performance"];
		$retour.="<br/></b>Coefficient contre-performance : <b>".$record["coefficient_contre_performance"];
		$retour.="<br/></b>Zone tampon : <b>".$record["zone_tampon"];
		$retour.='<br/>'.$this->descripteur_aide('Descripteur_carte_golf','n');

		return $retour;
			}
	function descriptorFields()
	{
		return array("id", "libelle", "index_haut", "index_bas", "coefficient_performance","coefficient_contre_performance", "zone_tampon");
	}

	function libelle_display($record, $mode) {
		$retour=$this->descriptor($record);
		return $retour;
	}

}
?>