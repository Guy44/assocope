<?php
class v_organisme_comptes_tiers extends assMetaNode
{
	var $table="v_organisme_comptes_tiers";
function meta(&$policy)
  {

	$policy-> addFlags("nom_individu","nom_organisme", AF_SEARCHABLE);

	$policy->setOrder("nom_organisme, nom_individu");
}
function v_organisme_comptes_tiers ()
{
  	$this->atkMetaNode();
  	$this->atkNode("v_organisme_comptes_tiers",NF_NO_ADD | NF_NO_DELETE | NF_NO_VIEW | NF_NO_EDIT);
	$this->add(new atkRowCounter("#"),NULL,1);
	$this->add(new atkAttribute("id_individu", AF_PRIMARY | AF_HIDE_LIST));
	$this->add(new atkAttribute("id_organisme", AF_PRIMARY | AF_HIDE_LIST));
	$this->add(new atkNumberAttribute("total_debit", NULL, 12,2));		
	$this->add(new atkNumberAttribute("total_credit", NULL, 12,2));
	$this->add(new atkNumberAttribute("solde", NULL, 12,2));	
	$this->setExtendedSearchAction('smartsearch');
	$this->setSecurityAlias("organisme.organisme");
	$this->setOrder("ABS(solde) desc"); // set order attribute(s)
	  	$this->m_securityMap["document"] = "view";
  }

function solde_display ($record)
{
	if ($record["solde"]==0)
	{
		return "<b>".$record["solde"]."</b>";
	}
	else 
{
		return '<font color="Red"><b>'.$record["solde"].'</b></font>';
	}
}
function lignes_ecritures_display ($record)
{
			if ($record["lignes_ecritures"] > 0) {
$url = href(dispatch_url("organisme.ligne_ecriture_comptable", "admin", array (
			"atkfilter" => " organisme_ligne_ecriture_comptable.id_individu='" . $record["id_individu"] . "'
and organisme_ligne_ecriture_comptable.id_organisme='" . $record["id_organisme"]. "'
and organisme_ligne_ecriture_comptable.id_compte in ( select id from organisme_compte where code like '40%' or code like '41%')"
		)), atktext($record["lignes_ecritures"]."<br>", "core"), SESSION_NEW, false, 'target="_blank"');
		} else {
			$url='';
		}
		return $url;
}
    
function descriptor_def()
  {
    return "[nom_organisme, nom_individu]";
  }

}

?>