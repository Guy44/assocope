<?php
atkimport("atk.assmetanode");
userelation("atkmanytoonerelation");
userelation("atkonetomanyrelation");
useattrib("atkdateattribute");

useattrib("atktabbedpane");

class menu extends assMetaNode {
	var $table = "menu";

	function meta(& $policy) {

		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("id_creation", "date_creation", "id_modification", "date_modification", AF_READONLY);

		$policy->setOrder("libelle");
	}
	function menu() {
		$this->atkMetaNode();
		$this->atkNode("menu", NF_COPY | NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);

	$this->add(new atkTabbedPane("Pane1",
	array(
	"Général"=>	array("id_type_menu","libelle","col_nom","col_id","table_entite","commentaire",
 "id_modification","date_modification"),
 //"Général.création"=>	array( "id_creation","date_creation"),
	"Items"=> array("menu_item")
	),AF_NO_LABEL));

		$this->add(new atkOneToManyRelation("menu_item", "menu.menu_item", "id_menu", AF_HIDE_LIST));
		$this->add(new atkManyToOneRelation("id_type_menu", "table.type_menu", AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setIndex("libelle");
				$this->setOrder("libelle");
	}
	function descriptor_def() {
		return "[libelle]";
	}

}
?>