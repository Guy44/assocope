<?php

class testmysql extends assMetaNode
{

    function testmysql()
    {
        $this->atkNode("testmysql");
        $this->setSecurityAlias("individu.individu");
        $this->m_securityMap["getmodules"] = "view";
        $this->m_securityMap["intro"] = "view";
        $this->m_securityMap["testmysql"] = "view";
        $this->m_securityMap["test_descripteur_individu"] = "view";
        $this->m_securityMap["test_number_format"] = "view";
    }

    function action_testmysql()
    {
        $db = & atkGetDb();
        
        $id_individu = "104";
        $id_organisme = "366";
        $id_type_inscription = "13";
        
        $query = & $db->createQuery();
        $query->addTable("individu_inscription");
        $query->addJoin("individu", "", "individu_inscription.id_individu = individu.id", false);
        $query->addJoin("organisme", "", "individu_inscription.id_organisme = organisme.id", false);
        $query->addJoin("organisme", "organisme_inscrit", "individu_inscription.id_organisme_inscrit = organisme_inscrit.id", true);
        $query->addJoin("individu_lieu", "", "individu.id = individu_lieu.id_individu", true);
        $query->addJoin("individu_attribut", "", "individu.id = individu_attribut.id_individu", true);
        $query->addJoin("type_attribut", "", "type_attribut.id = individu_attribut.id_attribut", true);
        $query->addJoin("lieu", "", "individu_lieu.id_lieu = lieu.id", true);
        $query->addJoin("type_cp_ville_pays", "", "lieu.id_ville = type_cp_ville_pays.id", true);
        $query->addJoin("type_pays", "", "type_cp_ville_pays.id_pays = type_pays.id", true);
        $query->addJoin("type_inscription", "", "individu_inscription.id_type_inscription = type_inscription.id", true);
        
        // $query->addJoin("individu_cotisation", "", "individu_inscription.id_individu = individu_cotisation.id_individu and individu_inscription.id_organisme = individu_cotisation.id_organisme", true);
        // $query->addJoin("organisme_cotisation", "", "individu_cotisation.id_cotisation = organisme_cotisation.id ", true);
        
        $query->addField("organisme.nom as organisme");
        $query->addField("organisme.id as id_organisme");
        $query->addField("organisme_inscrit.nom as nom_organisme_inscrit");
        $query->addField("organisme_inscrit.sigle as sigle_organisme_inscrit");
        $query->addField("organisme_inscrit.site_internet as site_internet");
        $query->addField("organisme_inscrit.objectif_concis as objectif_concis_organisme_inscrit");
        $query->addField("organisme_inscrit.courriel as courriel_organisme_inscrit");
        $query->addField("organisme_inscrit.telephone as telephone_inscrit");
        $query->addField("individu_inscription.id as id_inscription");
        $query->addField("individu_inscription.id_individu as id_individu");
        $query->addField("individu.id as id_individu");
        $query->addField("individu.nom as nom");
        $query->addField("individu.prenom as prenom");
        $query->addField("individu.courriel as courriel");
        $query->addField("individu.telephone_fixe as telephone_fixe");
        $query->addField("individu.telephone_mobile as telephone_mobile");
        $query->addField("type_inscription.libelle as type_inscription");
        $query->addField("individu_inscription.date_inscription as date_inscription");
        $query->addField("lieu.adresse1 as adresse1");
        $query->addField("type_cp_ville_pays.code_postal as code_postal");
        $query->addField("type_cp_ville_pays.ville as ville");
        $query->addField("type_cp_ville_pays.province_etat as province");
        $query->addField("type_pays.libelle_anglais as pays");
        $query->addField("individu.annee_naissance as annee_naissance ");
        $query->addField("individu_attribut.date_debut as date_debut_attribut");
        $query->addField("type_attribut.libelle as libelle_attribut");
        
        $query->addCondition("individu_inscription.id_organisme in ( " . $id_organisme . ")");
        $query->addCondition("individu_inscription.date_radiation is null ");
        $query->addCondition("individu.id in ( " . $id_individu . ")");
        $query->addCondition("individu.date_deces is null");
        $query->addCondition("individu_inscription.id_type_inscription in ( " . $id_type_inscription . ")");
        // $query->addCondition(" ( individu.courriel is null or individu.courriel='' ) ");
        // $query->addCondition(" individu.id not in (select id_individu from individu_lieu) ");
        
        $query->addOrderBy("individu.nom, individu.prenom");
        
        $sql = $query->buildSelect();
        $this->p($sql);
    }

    function action_test_descripteur_individu()
    {
        $id_individu = "104";
        $id_organisme = null;
        // $option = "fiche_complete";
        $option = "icones_portrait_cotisation";
        // $retour = $this->descripteur_individu_new($id_individu, $id_organisme, null, $option = 'icones_publiques');
        echo $this->descripteur_test($param2 = "pp1", $param1 = "pp2");
        
        die();
    }

    function action_test_number_format()
    {
        $number = '-0.52';
        
        // Notation anglaise (par défaut)
        $english_format_number = number_format($number);
        // 1,235
        
        // Notation française
        $nombre_format_francais = number_format($number, 2, ',', ' ');
        // 1 234,56
        
        $nombre = number_format(floatval($number), 2, ",", " ");
        
        $number = 1234.5678;
        
        // Notation anglaise sans séparateur de milliers
        $english_format_number_2 = number_format($number, 2, '.', '');
        // 1234.57
        
        echo $english_format_number . "</br>" . $nombre_format_francais . "</br>" . $nombre . "</br>" . $english_format_number_2;
        die();
    }

    function descripteur_test($param1 = "param1", $param2 = "param2")
    {
        return "parametre1: " . $param1 . "parametre2: " . $param2;
    }
}
?>