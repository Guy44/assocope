<?php
useattrib("development.atgfileblobattribute");
useattrib("development.atgtextlibelleattribute");
useattrib("development.atgblobattribute");
useattrib("development.atgomanytoonerelation");
class document_proto extends assMetaNode {

	function document_proto($name="document_proto", $flags=0) {
		$this->atkMetaNode();
		$this->atkNode($name,  $flags|NF_ADD_LINK |NF_ADDAFTERADD | NF_MRA |NF_COMPACT);
		$this->m_securityMap["fichier"] = "view";
		$this->m_securityMap["export_document_vers_google"] = "view";
				
		$this->add(new atgBlobAttribute("file_content", AF_HIDE));
		$this->add(new atkAttribute("file_extension", AF_SEARCHABLE | AF_READONLY));
		$this->add(new atkAttribute("file_size", AF_SEARCHABLE| AF_READONLY));
		$this->add(new atgFileBlobAttribute("file_name", "./documents", AF_HIDE_LIST | AF_FORCE_LOAD | AF_FILE_POPUP));

	}
function libelle_validate(&$record, $mode)
  {
    $record["libelle"]=escapeSQL($record["libelle"]);
   
  }
function file_name_validate(&$record, $mode)
  {
    $record["file_name"]=escapeSQL($record["file_name"]);
   
  }
	/**
	* One of the application level triggers that is implemented, is a trigger
	* that is fired when adding a new record. By giving the method the name
	* 'postAdd', it is called automatically when a new record was added.
	* The record that was added is passed as a parameter to the method.
	*/
	function postAdd($rec) {
		$uploadfile = $_FILES['file_name'];
		$name = $uploadfile['name'];
		$type = $uploadfile['type'];
		$size = $uploadfile['size'];
		$uperr = $uploadfile['error'];
		$tmpfile = $uploadfile['tmp_name'];
		$table=$this->getTable();
		if (!$tmpfile or $uperr or !is_uploaded_file($tmpfile)) {
			echo "<p>the file was not uploaded </p>\n";
		} else {
			$file = @ fopen($tmpfile, "rb");
			$filecontent = @ fread($file, $size);
			@ fclose($file);
			$filecontent = base64_encode($filecontent);
			$fileextension = strtolower(substr($name, strrpos($name, '.') + 1, strlen($name)));
			$db = & atkGetDb();
			$id_document = $rec['id'];
			$filename = $table.'_' . $id_document . '.' . $fileextension;
			$db->query("UPDATE $table set file_content='" . escapeSQL($filecontent) . "' 
						      , file_extension='" . $fileextension . "' , file_size='" . $size . "' , file_name='" . $filename . "' where id=$id_document ");
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
		$table=$this->getTable();
echo 'tronc commun : </br>';
		if ($_REQUEST["del"]["file_name"] == "on") {
			$db = & atkGetDb();
			$id_document = $rec['id'];
			$db->query("UPDATE $table set file_content=NULL 
						      , file_extension=NULL , file_size=NULL , file_name=NULL where id=$id_document ");
			return true;
		} else {
			if (!$tmpfile or $uperr or !is_uploaded_file($tmpfile)) {
				return true;
			} else {
				$file = @ fopen($tmpfile, "rb");
				$filecontent = @ fread($file, $size);
				@ fclose($file);
				$filecontent = base64_encode($filecontent);
				$fileextension = strtolower(substr($name, strrpos($name, '.') + 1, strlen($name)));
				$db = & atkGetDb();
				$id_document = $rec['id'];
				$filename = $table.'_' . $id_document . '.' . $fileextension;
					$db->query("UPDATE $table set file_content='" . escapeSQL($filecontent) . "' 
								      , file_extension='" . $fileextension . "' , file_size='" . $size . "' , file_name='" . $filename . "' where id=$id_document ");
			return true;
			}
		}
	}
	function file_extension_display($record, $mode)
	{
//		$this->p($record);

			if ($record["file_extension"]=="")
		{ return "";}
		else
		{ 
			$id=$this->primaryKey($record);
/*		exporter vers un google document en prenant le libellé du fichier	*/
//		$link=' <a href="dispatch.php?'.$this->atkNodeType
//		.'&atkselector='.$id.'&atkaction=assocope_to_google_export&"><img class="recordlist" border="0" src="./themes/assocope/icons/recordlist/texte.gif" alt="Exporter vers Google" title="Exporter vers Google" target="_blank"></a>';
/*rajouter au display et créer une action pour traiter ce
		 chargement, simplifierv aussi ce qui existes dans action assmetanode*/	
			
		return href(dispatch_url($this->atkNodeType,"fichier",array("atkselector"=>$id,"atkaction"=>"fichier")),
                        ' <font color="ForestGreen"> <b>Ouvrir fichier </b>'.$record['file_extension']
		,
		SESSION_NESTED,
		false,'class="atkmanytoonerelation"')
		.' '.
		href(dispatch_url($this->atkNodeType,"assocope_to_google_export",array("atkselector"=>$id,"atkaction"=>"assocope_to_google_export")),
                       		'<img class="recordlist" border="0" src="./themes/assocope/icons/assocope/google_icon.png" alt="Exporter vers Google" title="Exporter vers Google" target="_blank">',
		SESSION_NESTED,
		false, ' target="_blank"')

		;
		}
		
	}
	function action_fichier()
	{	
		$id_document = $this->m_postvars["atkselector"];
		$this->getAttribute("file_name")->fichier_ouvrir($id_document,'n');
	}
	function action_fichier_url($id_document)
	{
				return $this->getAttribute("file_name")->fichier_ouvrir($id_document,'o');
	}
	function recordActions($rec, & $actions, & $mraactions) {
		$mraactions = array ();
		$actions['export_document_vers_google'] = session_url("dispatch.php?atknodetype=" . $this->atkNodeType() . "&atkaction=assocope_to_google_export&atkselector=[pk]", SESSION_NESTED);
		$mraactions['export_document_vers_google'] = "assocope_to_google_export";
	}
}
?>