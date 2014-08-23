<?php
atkimport("atk.assmetanode");
useattrib("development.atgtextlibelleattribute");
class type_ecriture extends assMetaNode {
	var $table = "type_ecriture";
	function meta(& $policy) {
		$policy->addFlags("libelle", AF_SEARCHABLE);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
	}
	function type_ecriture() {
		$this->atkMetaNode();
		$this->atkNode("type_ecriture",NF_ADDAFTERADD | NF_ADD_LINK | NF_MRA);
		$this->setSecurityAlias("table.activite");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE | AF_UNIQUE));
		$this->add(new atkTabbedPane("Pane1", array (
				"Général" => array (
						"id",
						"libelle",
						"modifiable_o_n",
						"commentaire",
						"id_creation",
						"date_creation",
						"id_modification",
						"date_modification"
				)
		), AF_NO_LABEL));
		//		$this->add(new atkOneToManyRelation("liste", "profil.liste", "id_liste", AF_HIDE_LIST));
		$this->m_securityMap["admin_liste"] = "view";
		include_once (atkconfig("atkroot") . "modules/include/association.inc");
		$this->setOrder("libelle");
		$this->add(new atkAttribute("id"));
		$this->add(new atkBoolAttribute("modifiable_o_n", AF_READONLY));
	}
	function descriptor_def() {
		return "[libelle]";
	}
	function action_admin_liste() {
		$db = & atkGetDb();
		$id_organisme=$this->m_postvars["id_organisme"];
		$id_ecriture=$this->m_postvars["id_ecriture"];
		$sql="SELECT
		id_type_ecriture,
		id_origine_ecriture
		from organisme_ecriture_comptable
		WHERE
		id=$id_ecriture
		";
		$data=$db->getrows($sql);
		$id_origine=$data[0]["id_origine_ecriture"];
		$id_type_ecriture=$data[0]["id_type_ecriture"];
		switch ($id_type_ecriture)
		{
			case 1 :
				if ($id_origine>0) {
					
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Ecriture saisie directement dans un journal</b><br/><br/></div>";
					$descripteur.=$this->descripteur_journal_comptable($id_origine,'n')."<br />";
					
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($id_ecriture,'n') : null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;


			case 2 :
				if ($id_origine>0) {
					$sql="SELECT
					id_individu,
					id_organisme,
					id_ecriture_cotisation,
					id_ecriture_reglement,
					id_ecriture_cotisation_federation
					from individu_cotisation
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Cotisation</b><br/><br/></div>";
					$descripteur.=$this->descripteur_individu($data[0]["id_individu"],'n','n','50')."<br />";
					$descripteur.=$this->descripteur_reglement('cotisation',$id_origine,'n');
					$descripteur.=$this->descripteur_organisme($data[0]["id_organisme"],'n','n','50')."<br />";
						
						
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de cotisation</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_cotisation"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de cotisation à la fédération</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_cotisation_federation"],'n') : null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;
			case 3 :
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_participation,
					id_ecriture_reglement,
					id_ecriture_participation_2,
					id_ecriture_reglement_2
					from individu_rencontre
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Participation financière à une rencontre</b><br/><br/></div>";
					$descripteur.=$this->descripteur_participant_rencontre($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de participation 1</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_participation"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement 1</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de participation 2</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_participation"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement 2</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;

					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;
			case 4 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_participation,
					id_ecriture_reglement
					from organisme_rencontre
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Recette non nominative en rencontre</b><br/><br/></div>";
					$descripteur.=$this->descripteur_rencontre($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de participation, recette</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_participation"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;
			case 5 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_depense,
					id_ecriture_reglement,
					id_document_facture
					from organisme_rencontre_fournisseur
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Dépenses pour les rencontres</b><br/><br/></div>";
					$descripteur.=$this->descripteur_rencontre_fournisseur($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de dépense</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_depense"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
					($data[0]["id_document_facture"]>0) ?$this->descripteur_document($type='organisme',$data[0]["id_document_facture"],'n',$lien_justificatif): null;
					($data[0]["id_document_facture"]>0) ? $descripteur.="<div ".$this->m_styleTitreLigne."><b>Facture : </b></div>".$lien_justificatif."<br/>" :
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Facture : </b></div>";
				}
				break;
			case 6 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_depense,
					id_ecriture_reglement,
					id_document_facture
					from organisme_fourniture
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Dépenses - Règlements</b><br/><br/></div>";
					$descripteur.=$this->descripteur_depense($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de dépense</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_depense"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
					($data[0]["id_document_facture"]>0) ?$this->descripteur_document($type='organisme',$data[0]["id_document_facture"],'n',$lien_justificatif): null;
					($data[0]["id_document_facture"]>0) ? $descripteur.="<div ".$this->m_styleTitreLigne."><b>Facture : </b></div>".$lien_justificatif."<br/>" :
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Facture : </b></div>";
				}
				break;

			case 7 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_recette,
					id_ecriture_reglement,
					from organisme_financement
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Recettes - Subventions</b><br/><br/></div>";
					$descripteur.=$this->descripteur_activite_frais($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de recette</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_recette"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;
			case 8 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_virement
					from organisme_virement_comptable
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Virements - Retraits</b><br/><br/></div>";
					$descripteur.=$this->descripteur_virement_comptable($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de virement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_virement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;

			case 9 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_frais,
					id_ecriture_benevolat,
					id_ecriture_reglement,
					id_document_justificatif
					from individu_activite
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Activité - Frais</b><br/><br/></div>";
					$descripteur.=$this->descripteur_activite_frais($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><br/><b>Ecriture de frais</b><br/><br/></div>";
					($data[0]["id_ecriture_frais"]>0) ? $descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_frais"],'n') : null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de bénévolat</b><br/><br/></div>";
					($data[0]["id_ecriture_benevolat"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_benevolat"],'n'): null;
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de règlement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_reglement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
					($data[0]["id_document_justificatif"]>0) ?$this->descripteur_document($type='organisme',$data[0]["id_document_justificatif"],'n',$lien_justificatif): null;
					($data[0]["id_document_justificatif"]>0) ? $descripteur.="<div ".$this->m_styleTitreLigne."><b>Document justificatif : </b></div>".$lien_justificatif."<br/>" :
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Document justificatif : </b></div>";
				}
				break;
			case 10 :
				$descripteur="";
				if ($id_origine>0) {
					$sql="SELECT
					id_ecriture_virement
					from organisme_abandon_creance
					WHERE
					id=$id_origine
					";
					$data=$db->getrows($sql);
					$descripteur="<div ".$this->m_styleTitreLigne."><b>Abandon de créance</b><br/><br/></div>";
					$descripteur.=$this->descripteur_abandon_creance($id_origine,'n');
					$descripteur.="<div ".$this->m_styleTitreLigne."><b>Ecriture de virement</b><br/><br/></div>";
					($data[0]["id_ecriture_reglement"]>0) ?$descripteur.=$this->descripteur_ecriture_comptable($data[0]["id_ecriture_virement"],'n'): null;
					$descripteur=strip_tags($descripteur, "<b><br><br/><img><div>");
				}
				break;
			default :
				$module="";
		}


		$this->page_output($descripteur);


	}

}
?>