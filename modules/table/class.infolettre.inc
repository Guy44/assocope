<?php
atkimport("atk.assmetanode");
userelation("atkmanytoonerelation");
userelation("atkonetomanyrelation");
useattrib("atkdateattribute");
useattrib("development.atgtextlibelleattribute");
class infolettre extends assMetaNode {
	var $table = "x99c1c_evennews_members";
	function meta(& $policy) {
		$policy->addFlags("user_name", "user_nick", "user_email", AF_SEARCHABLE);
	}
	function infolettre() {
		$this->atkMetaNode();
		$this->atkNode("infolettre", NF_EXPORT | NF_IMPORT | NF_ADD_LINK | NF_TRACK_CHANGES | NF_MRA);
		$this->add(new atkRowCounter("#"), NULL, 1);
		$this->setExtendedSearchAction('smartsearch');
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE));
		$this->addListener(atknew("atk.utils.atkeventlog"));
		$this->setIndex("user_name");
		$policy->setOrder("user_name");
		$this->setTable("x99c1c_evennews_members", "", $dpg);
	}
	function descriptor_def() {
		return "[user_name]";
	}
	function adminFooter() {
		return "Nombre de lignes : " . $this->m_count . " <br>  " . nodeSourceUrl("table.infolettre");
	}
}
?>