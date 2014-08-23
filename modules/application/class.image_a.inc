<?php
useattrib("development.atgfileblobattribute");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgblobattribute");
useattrib("development.atgomanytoonerelation");
include_once (moduleDir("application")."class.document_proto.inc");
class image_a extends document_proto {
	var $table = "organisme_image";
	function meta(& $policy) {

		$policy->addFlags("nombre_affichages", "date_dernier_affichage", "id_creation", "date_creation", "id_modification", "date_modification", "file_lock_id", "file_lock_date", "file_extension", "file_name", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("file_content", "file_lock_date", "file_lock_id", AF_HIDE);
	}
	function image_a() {
				global $ATK_VARS,$g_user;

    $this->document_proto("image_a",null);
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE| AF_OBLIGATORY ));

		$this->add(new atgOManyToOneRelation("id_entite", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));	
		$this->add(new atgOManyToOneRelation("id_type_entite","table.type_entite",AF_READONLY| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_image", "table.type_image", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		$this->add(new atkfckattribute("description", "", AF_HIDE_LIST, array (
			'ToolbarSet' => 'Default',
			'Width' => '100%',
			'Height' => '150px'
			)));
			$this->add(new atkUrlAttribute("url_cible", AF_POPUP | AF_SEARCHABLE));
			$this->add(new atkBoolAttribute("actif_o_n"));
			$this->add(new atkNumberAttribute("nombre_affichages", AF_READONLY, 10, 0));
			$this->add(new atkAttribute("date_dernier_affichage", AF_READONLY | AF_SEARCHABLE));

			include_once (atkconfig("atkroot") . "modules/include/association.inc");
			$this->setOrder(" organisme_image.date_creation DESC ");
	}
	function initial_values() {

		$init_vals = array ();
/*		$filtre = $this->m_postvars["atkfilter"];
		//							$this->p($filtre);
		if (stristr($filtre, ' and ') != false) {
			$filtres = explode('and', $filtre);
			for ($i = 0, $_i = count($filtres); $i < $_i; $i++)
			{	if (stristr($filtres[$i], ' id_type_entite ') != false)
			{$idtypeentite = explode('=', $filtres[$i]);
			$IdTypeEntite=$idtypeentite[1];
			}
			if (stristr($filtres[$i], ' id_entite ') != false)
			{$identite = explode('=', $filtres[$i]);
			$IdEntite=$identite[1];
			}
			}
		}
		$init_vals ["id_entite"]=$IdEntite;
*/
				$init_vals ["id_type_entite"]='1';
		return $init_vals;
	}

	/**
	 * One of the application level triggers that is implemented, is a trigger
	 * that is fired when adding a new record. By giving the method the name
	 * 'postAdd', it is called automatically when a new record was added.
	 * The record that was added is passed as a parameter to the method.
	 */
	function preAdd(&$record) {
		$record["id_type_entite"]='1';
		$record["nombre_affichages"]=0;
		parent :: preAdd($record);
	}

	function descriptor_def() {
		return " [id_organisme.nom] - [libelle] ";
	}
}
?>