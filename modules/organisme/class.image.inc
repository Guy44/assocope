<?php
useattrib("development.atgfileblobattribute");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgblobattribute");
useattrib("development.atgomanytoonerelation");
class image extends assMetaNode {
	var $table = "organisme_image";
	function meta(& $policy) {

		$policy->addFlags("nombre_affichages", "date_dernier_affichage", "id_creation", "date_creation", "id_modification", "date_modification", "file_lock_id", "file_lock_date", "file_extension", "file_name", AF_READONLY);
		$policy->addFlags("commentaire", AF_HIDE_LIST);
		$policy->addFlags("file_content", "file_lock_date", "file_lock_id", AF_HIDE);
	}
	function image() {
		$this->atkMetaNode();
		$this->atkNode("image",  NF_ADD_LINK  );
		$this->setSecurityAlias("organisme.organisme");
		$this->add(new atgTextLibelleAttribute("libelle", AF_SEARCHABLE| AF_OBLIGATORY ));

		$this->add(new atgOManyToOneRelation("id_entite", "organisme.organisme", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY | AF_RELATION_AUTOCOMPLETE));	
		$this->add(new atgOManyToOneRelation("id_type_entite","table.type_entite",AF_READONLY| AF_HIDE_ADD  | AF_HIDE_EDIT| AF_FORCE_LOAD));
		$this->add(new atkManyToOneRelation("id_type_image", "table.type_image", AF_SEARCHABLE | AF_RELATION_AUTOLINK | AF_OBLIGATORY));
		$this->add(new atgBlobAttribute("file_content", AF_HIDE));
		$this->add(new atkAttribute("file_extension", AF_READONLY| AF_SEARCHABLE));
		$this->add(new atkAttribute("file_size", AF_READONLY));
				$this->add(new atgFileBlobAttribute("file_name", "./images", AF_HIDE_LIST | AF_FILE_POPUP));
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
	function postAdd($rec) {
		$uploadfile = $_FILES['file_name'];
		$name = $uploadfile['name'];
		$type = $uploadfile['type'];
		$size = $uploadfile['size'];
		$uperr = $uploadfile['error'];
		$tmpfile = $uploadfile['tmp_name'];
		if (!$tmpfile or $uperr or !is_uploaded_file($tmpfile)) {
			echo "<p>the file was not uploaded </p>\n";
		} else {
			$file = @ fopen($tmpfile, "rb");
			$filecontent = @ fread($file, $size);
			@ fclose($file);
			$filecontent = base64_encode($filecontent);
			$fileextension = strtolower(substr($name, strrpos($name, '.') + 1, strlen($name)));
			$db = & atkGetDb();
			$id_image = $rec['id'];
			$filename = 'organisme_image_' . $id_image . '.' . $fileextension;
			$db->query("UPDATE organisme_image set file_content='" . escapeSQL($filecontent) . "'
						      , file_extension='" . $fileextension . "' , file_size='" . $size . "' , file_name='" . $filename . "' where id=$id_image ");
			return true;
		}
	}
	function postUpdate($rec) {
		$uploadfile = $_FILES['file_name'];
		$name = $uploadfile['name'];
		$type = $uploadfile['type'];
		$size = $uploadfile['size'];
		$uperr = $uploadfile['error'];
		$tmpfile = $uploadfile['tmp_name'];
		if ($_REQUEST["del"]["file_name"] == "on") {
			$db = & atkGetDb();
			$id_image = $rec['id'];
			$db->query("UPDATE organisme_image set file_content=NULL
			, file_extension=NULL , file_size=NULL , file_name=NULL where id=$id_image ");
			return true;
		} else {
			if (!$tmpfile or $uperr or !is_uploaded_file($tmpfile)) {
				//echo "<p>the file was not uploaded </p>\n";
				return true;
			} else {
				$file = @ fopen($tmpfile, "rb");
				$filecontent = @ fread($file, $size);
				@ fclose($file);
				$filecontent = base64_encode($filecontent);
				$fileextension = strtolower(substr($name, strrpos($name, '.') + 1, strlen($name)));
				$db = & atkGetDb();
				$id_image = $rec['id'];
				$filename = 'organisme_image_' . $id_image . '.' . $fileextension;
				$db->query("UPDATE organisme_image set file_content='" . escapeSQL($filecontent) . "'
								      , file_extension='" . $fileextension . "' , file_size='" . $size . "' , file_name='" . $filename . "' where id=$id_image ");
				return true;
			}
		}
	}
	function descriptor_def() {
		return " [id_organisme.nom] - [libelle] ";
	}
function id_organisme_display($record, $mode) {
		(!empty($record["id_organisme"])) ? $retour=$this->descripteur_organisme($record["id_organisme"]["id"],'n') : $retour="";
		return $retour;
	}
}
?>