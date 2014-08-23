<?php


/**
 * The atkTextLibelle is used for libelle normalization (trim spaces and all in lowercase except first letter.)
 *   
 * @author guy gourmellet
 * 
 *
 */
class atgTextLibelleAttribute extends atkAttribute {

	/**
	 * Constructor
	 * @param $name  Name of the attribute
	 * @param $flags Flags for this attribute
	 * @param $size  The size(s) for this attribute (default 10)
	
	 */
	function atgTextLibelleAttribute($name, $flags = 0, $size = 0) {
		$this->m_name = $name;
		$this->m_flags = (double) $flags;
		$this->setAttribSize($size);

	}

	function validate(& $record, $mode) {
		$record[$this->fieldName()] = $this->normalisation_libelle($record[$this->fieldName()]);
	}

	function normalisation_libelle($chaine) {
		$chaine = trim($chaine);
		$chaine = strtolower($chaine);
		$chaine_normalisee = ucfirst($chaine);
		return $chaine_normalisee;

	}
}
?>
