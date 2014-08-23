<?php
// initialize node
$node->setFlags(0);
$node->setTable('individu', 'seq_individu', 'default');

// attribute: id
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id');
$attr->addFlag(AF_AUTOKEY);
$node->add($attr, NULL, 100);

// attribute: id_titre
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id_titre');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 200);

// attribute: prenom
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('prenom');
$attr->addFlag(0);
$node->add($attr, NULL, 300);

// attribute: sexe
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('sexe');
$attr->addFlag(0);
$node->add($attr, NULL, 400);

// attribute: nom
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('nom');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 500);

// attribute: numero_ss
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('numero_ss');
$attr->addFlag(0);
$node->add($attr, NULL, 600);

// attribute: compte_bancaire
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('compte_bancaire');
$attr->addFlag(0);
$node->add($attr, NULL, 700);

// attribute: id_document_signature
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id_document_signature');
$attr->addFlag(0);
$node->add($attr, NULL, 800);

// attribute: id_document_portrait
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id_document_portrait');
$attr->addFlag(0);
$node->add($attr, NULL, 900);

// attribute: commentaire_portrait
atkimport('atk.attributes.atktextattribute');
$attr = new atktextattribute('commentaire_portrait');
$attr->addFlag(AF_HIDE_LIST);
$node->add($attr, NULL, 1000);

// attribute: courriel
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('courriel');
$attr->addFlag(0);
$node->add($attr, NULL, 1100);

// attribute: calendrier
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier');
$attr->addFlag(0);
$node->add($attr, NULL, 1200);

// attribute: site_internet
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('site_internet');
$attr->addFlag(0);
$node->add($attr, NULL, 1300);

// attribute: telephone_fixe
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('telephone_fixe');
$attr->addFlag(0);
$node->add($attr, NULL, 1400);

// attribute: telephone_mobile
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('telephone_mobile');
$attr->addFlag(0);
$node->add($attr, NULL, 1500);

// attribute: contact_alternatif
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('contact_alternatif');
$attr->addFlag(0);
$node->add($attr, NULL, 1600);

// attribute: date_naissance
atkimport('atk.attributes.atkdateattribute');
$attr = new atkdateattribute('date_naissance');
$attr->addFlag(0);
$node->add($attr, NULL, 1700);

// attribute: annee_naissance
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('annee_naissance');
$attr->addFlag(0);
$node->add($attr, NULL, 1800);

// attribute: lieu_naissance
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('lieu_naissance');
$attr->addFlag(0);
$node->add($attr, NULL, 1900);

// attribute: nationalite
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('nationalite');
$attr->addFlag(0);
$node->add($attr, NULL, 2000);

// attribute: passeport_nom_prenom
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('passeport_nom_prenom');
$attr->addFlag(0);
$node->add($attr, NULL, 2100);

// attribute: passeport_numero
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('passeport_numero');
$attr->addFlag(0);
$node->add($attr, NULL, 2200);

// attribute: passeport_date_expiration
atkimport('atk.attributes.atkdateattribute');
$attr = new atkdateattribute('passeport_date_expiration');
$attr->addFlag(0);
$node->add($attr, NULL, 2300);

// attribute: profession
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('profession');
$attr->addFlag(0);
$node->add($attr, NULL, 2400);

// attribute: date_deces
atkimport('atk.attributes.atkdateattribute');
$attr = new atkdateattribute('date_deces');
$attr->addFlag(0);
$node->add($attr, NULL, 2500);

// attribute: tour_de_cou
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('tour_de_cou');
$attr->addFlag(0);
$node->add($attr, NULL, 2600);

// attribute: tour_de_poitrine
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('tour_de_poitrine');
$attr->addFlag(0);
$node->add($attr, NULL, 2700);

// attribute: tour_de_taille
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('tour_de_taille');
$attr->addFlag(0);
$node->add($attr, NULL, 2800);

// attribute: tour_de_bassin
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('tour_de_bassin');
$attr->addFlag(0);
$node->add($attr, NULL, 2900);

// attribute: pointure
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('pointure');
$attr->addFlag(0);
$node->add($attr, NULL, 3000);

// attribute: taille
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('taille');
$attr->addFlag(0);
$node->add($attr, NULL, 3100);

// attribute: poids
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('poids');
$attr->addFlag(0);
$node->add($attr, NULL, 3200);

// attribute: etp_poids_kg
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('etp_poids_kg');
$attr->addFlag(0);
$node->add($attr, NULL, 3300);

// attribute: etp_pulses_per_minute
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('etp_pulses_per_minute');
$attr->addFlag(0);
$node->add($attr, NULL, 3400);

// attribute: etp_systole_mm_hg
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('etp_systole_mm_hg');
$attr->addFlag(0);
$node->add($attr, NULL, 3500);

// attribute: date_mesure
atkimport('atk.attributes.atkdateattribute');
$attr = new atkdateattribute('date_mesure');
$attr->addFlag(0);
$node->add($attr, NULL, 3600);

// attribute: entree_college
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('entree_college');
$attr->addFlag(0);
$node->add($attr, NULL, 3700);

// attribute: sortie_college
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('sortie_college');
$attr->addFlag(0);
$node->add($attr, NULL, 3800);

// attribute: golf_licence
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('golf_licence');
$attr->addFlag(0);
$node->add($attr, NULL, 3900);

// attribute: golf_index
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('golf_index');
$attr->addFlag(0);
$node->add($attr, NULL, 4000);

// attribute: golf_url_federation
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('golf_url_federation');
$attr->addFlag(0);
$node->add($attr, NULL, 4100);

// attribute: pas_de_courriel_o_n
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('pas_de_courriel_o_n');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 4200);

// attribute: signature_courriel
atkimport('atk.attributes.atktextattribute');
$attr = new atktextattribute('signature_courriel');
$attr->addFlag(AF_HIDE_LIST);
$node->add($attr, NULL, 4300);

// attribute: identifiant_google
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('identifiant_google');
$attr->addFlag(0);
$node->add($attr, NULL, 4400);

// attribute: code_google
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('code_google');
$attr->addFlag(0);
$node->add($attr, NULL, 4500);

// attribute: tz_offset_google
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('tz_offset_google');
$attr->addFlag(0);
$node->add($attr, NULL, 4600);

// attribute: calendrier_rencontres_nom
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_rencontres_nom');
$attr->addFlag(0);
$node->add($attr, NULL, 4700);

// attribute: calendrier_rencontres_url
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_rencontres_url');
$attr->addFlag(0);
$node->add($attr, NULL, 4800);

// attribute: calendrier_rencontres_uri
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_rencontres_uri');
$attr->addFlag(0);
$node->add($attr, NULL, 4900);

// attribute: calendrier_rencontres_refresh
atkimport('atk.attributes.atkdatetimeattribute');
$attr = new atkdatetimeattribute('calendrier_rencontres_refresh');
$attr->addFlag(0);
$node->add($attr, NULL, 5000);

// attribute: calendrier_contacts_nom
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_contacts_nom');
$attr->addFlag(0);
$node->add($attr, NULL, 5100);

// attribute: calendrier_contacts_url
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_contacts_url');
$attr->addFlag(0);
$node->add($attr, NULL, 5200);

// attribute: calendrier_contacts_uri
atkimport('atk.attributes.atkattribute');
$attr = new atkattribute('calendrier_contacts_uri');
$attr->addFlag(0);
$node->add($attr, NULL, 5300);

// attribute: calendrier_contacts_refresh
atkimport('atk.attributes.atkdatetimeattribute');
$attr = new atkdatetimeattribute('calendrier_contacts_refresh');
$attr->addFlag(0);
$node->add($attr, NULL, 5400);

// attribute: google_calendar_entries
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('google_calendar_entries');
$attr->addFlag(0);
$node->add($attr, NULL, 5500);

// attribute: commentaire
atkimport('atk.attributes.atktextattribute');
$attr = new atktextattribute('commentaire');
$attr->addFlag(AF_HIDE_LIST);
$node->add($attr, NULL, 5600);

// attribute: id_creation
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id_creation');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 5700);

// attribute: date_creation
atkimport('atk.attributes.atkdatetimeattribute');
$attr = new atkdatetimeattribute('date_creation');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 5800);

// attribute: id_modification
atkimport('atk.attributes.atknumberattribute');
$attr = new atknumberattribute('id_modification');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 5900);

// attribute: date_modification
atkimport('atk.attributes.atkdatetimeattribute');
$attr = new atkdatetimeattribute('date_modification');
$attr->addFlag(AF_OBLIGATORY);
$node->add($attr, NULL, 6000);

