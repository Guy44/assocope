<?php


/**
 * The atkNomsVernaculaires is used for libelle normalization (trim spaces and all in lowercase except first letter.)
 *   
 * @author guy gourmellet
 * 
 *
 */
class atgNomsVernaculairesAttribute extends atkAttribute {

	/**
	 * Constructor
	 * @param $name  Name of the attribute
	 * @param $flags Flags for this attribute
	 * @param $size  The size(s) for this attribute (default 10)
	
	 */
	function atgNomsVernaculairesAttribute($name, $flags = 0, $size = 0) {
		$this->m_name = $name;
		$this->m_flags = (double) $flags;
		$this->setAttribSize($size);

	}

	function validate(& $record, $mode) {
		$record[$this->fieldName()] = $this->normalisation_nom_vernaculaire($record[$this->fieldName()]);
	}

		function normalisation_nom_vernaculaire($nom="")
		{
						if (substr($nom,0,1)=="'") $nom=substr($nom,1);
					$nom =normalisation_libelle($nom);
					$nom =str_replace(',',';',$nom);
					$nom =str_replace('|',';',$nom);
					while (stripos($nom,'  ',0))
					{$nom=str_replace('  ',' ',$nom);}
					$nom=str_replace(' ;',';',$nom);
					$nom=str_replace('; ',';',$nom);
					$nom=str_replace(';',' | ',$nom);
					$nom=trim($nom);
					$pos=0;
					$nom_transforme='';
					while (true)
					{
						$pos=stripos($nom,'|',0);
									
						if ($pos==false) 
						{
							
							$nom=$this->suppression_article_debut_nom($nom)	;	
							$nom=ucfirst($nom);		
							$nom_transforme=$nom_transforme.$nom;
							
	//						echo $nom_transforme;die();
							break;
						}
						$nom_extrait=substr($nom,0,$pos+2);
						$nom_extrait=$this->suppression_article_debut_nom($nom_extrait)	;
						$nom_extrait=ucfirst($nom_extrait);
										
						$nom_transforme=$nom_transforme.$nom_extrait;
						$nom=substr($nom,$pos+2);
					
					}
					return $nom_transforme;
					
		}
function suppression_article_debut_nom($nom="")
		{
								if (substr($nom,0,2)=="L'" || substr($nom,0,2)=="l'") $nom=substr($nom,2);
						if (substr($nom,0,3)=="Le " || substr($nom,0,3)=="le ") $nom=substr($nom,3);
						if (substr($nom,0,3)=="La " || substr($nom,0,3)=="la ") $nom=substr($nom,3);
						 return ucfirst($nom);		
		}
}
?>
