<?php
/**
 * This file is part of the Achievo ATK distribution.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage attributes
 *
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 5.21 $
 * $Id: class.atkfileattribute.inc,v 5.21 2006/05/29 06:22:50 wim Exp $
 */

useattrib("atkattribute");

/** flag(s) specific for the atkFileAttribute */

/**
 * Disable uploading of files
 */
define("AF_FILE_NO_UPLOAD",           AF_SPECIFIC_1);

/**
 * Disable selecting of files
 */
define("AF_FILE_NO_SELECT",           AF_SPECIFIC_2);

/**
 * Disable deleting of files
 */
define("AF_FILE_NO_DELETE",           AF_SPECIFIC_3);

/**
 * Don't try to detect the file type (shows only filename)
 */
define("AF_FILE_NO_AUTOPREVIEW",      AF_SPECIFIC_4);

/**
 * Removed the files physically
 */
define("AF_FILE_PHYSICAL_DELETE",     AF_SPECIFIC_5);

/**
 * Show preview in popup instead of inline
 */
define("AF_FILE_POPUP",                    AF_POPUP);

/**
 * With this you can upload, select and remove files in a given directory.
 *
 * @todo - Code clean up (del variable is dirty)
 *       - Support for storing the file itself in the db instead of on disk.
 *
 * @author Martin Roest <martin@ibuildings.nl>
 * @package atk
 * @subpackage attributes
 *
 */
class atgFileBlobAttribute extends atkAttribute
{
	/**
	 * Directory with images
	 */
	var $m_dir = "";
	var $m_url = "";

	/**
	 * Name mangle feature. If you set filename tpl, then uploaded files
	 * are renamed to what you set in the template. You can use
	 * fieldnames between brackets to have the filename determined by
	 * the record.
	 *
	 * This is useful in the following case:
	 * Say, you have a class for managing users. Each user has a photo associated
	 * with them. Now, if two users would upload 'gandalf.gif', then you would
	 * have a naming conflicht and the picture of one user is overwritten with the
	 * one from the other user.
	 * If you set m_filenameTpl to "picture_[name]", then the file is renamed before
	 * it is stored. If the user's name is 'Ivo Jansch', and he uploads 'gandalf.gif',
	 * then the file that is stored is picture_Ivo_Jansch.gif. This way, you have a
	 * unique filename per user.
	 */
	var $m_filenameTpl = "";

	/**
	 * When set to true, a file is auto-renumbered if another record exists with the
	 * same filename.
	 *
	 * @var boolean
	 */
	var $m_autonumbering = false;

	/**
	 * Constructor
	 * @param string $name Name of the attribute
	 * @param array $dir Can be a string with the Directory with images/files or an array with a Directory and a Display Url
	 * @param int $flags Flags for this attribute
	 * @param int $size Filename size
	 */
	function atgFileBlobAttribute($name, $dir, $flags=0, $size=0)
	{
		// We use 255 as default filename size if no size specified.
		if ($size==0) $size = 255;

		// Call base class constructor.
		$this->atkAttribute($name,$flags|AF_CASCADE_DELETE, $size);
		if(is_array($dir))
		{
			$this->m_dir = $this->AddSlash($dir[0]);
			$this->m_url = $this->AddSlash($dir[1]);
		}
		else
		{
			$this->m_dir = $this->AddSlash($dir);
			$this->m_url = $this->AddSlash($dir);
		}
	}

	/**
	 * Turn auto-numbering of filenames on/off.
	 *
	 * When autonumbering is turned on, uploading a file with the same name as
	 * the file of another record, will result in the file getting a unique
	 * sequence number.
	 *
	 * @param unknown_type $autonumbering
	 */
	function setAutonumbering($autonumbering=true)
	{
		$this->m_autonumbering = $autonumbering;
	}


	/**
	 * returns a string with a / on the end
	 * @param string $dir_url String with the url/dir
	 * @return string with a / on the end
	 */
	function AddSlash($dir_url)
	{
		if(substr($dir_url,strlen($dir_url)-1,strlen($dir_url))!="/") { $dir_url.="/"; }
		return $dir_url;
	}


	/**
	 * Returns a piece of html code that can be used in a form to edit this
	 * attribute's value.
	 * @param array $record Record
	 * @param string $fieldprefix Field prefix
	 * @return string piece of html code with a browsebox
	 */
	function edit($record="", $fieldprefix="")
	{
		$result=$this->display($record);


		if(is_dir($this->m_dir))
		{
			$file_arr=array();
			$d = dir($this->m_dir);
			while($item = $d->read())
			{
				if(is_file($this->m_dir.$item)) $file_arr[] = $item;
			}
			$d->close();
			if(count($file_arr)>0) natcasesort($file_arr);
		}
		else
		{
			return atktext("no_valid_directory", "atk");
		}

		$id = $fieldprefix.$this->fieldName();

		if ($result!="")
		{
			$result.="<br>";
			$result.='<input type="hidden" name="'.$id.'_orgfilename" value="'.$record[$this->fieldName()]['orgfilename'].'">';
		}

		$result.='<input type="hidden" name="'.$id.'_postfileskey" value="'.$id.'">';

		if(!$this->hasFlag(AF_FILE_NO_UPLOAD))
		{
			$this->registerKeyListener($id, KB_CTRLCURSOR|KB_UPDOWN);
			$result .= '<input type="file" id="'.$id.'" size="150" name="'.$id.'">';
		}
		/*
		 if(!$this->hasFlag(AF_FILE_NO_SELECT) AND count($file_arr) > 0)
		 {
		 $this->registerKeyListener($id.'_select', KB_CTRLCURSOR|KB_LEFTRIGHT);
		 $result .= '<select id="'.$id.'_select" name="'.$id.'[select]">';
		 $result .= "<option value=\"\" selected>".atktext('selection', 'atk');                    // Zorg voor een default met waarde NULL
		 while (list ($key, $val) = each ($file_arr))
		 {
		 (isset($record[$this->fieldName()]['filename']) && $record[$this->fieldName()]['filename']==$val) ? $selected = "selected" : $selected = '';
		 if(is_file($this->m_dir.$val)) $result .= "<option value=\"".$val."\" $selected>".$val;
		 }
		 if(count($file_arr) > 0) $result .= "</select>";
		 }
		 if(!$this->hasFlag(AF_FILE_NO_DELETE)
		 && isset($record[$this->fieldname()]['filename'])
		 && $record[$this->fieldname()]['filename']!='')
		 {
		 $this->registerKeyListener($id.'_del', KB_CTRLCURSOR|KB_CURSOR);
		 $result .= '<br><input id="'.$id.'_del" type="checkbox" name="del['.$fieldprefix.$this->fieldName().']">&nbsp;'.atktext("remove_current_file", "atk");
		 }
		 */
		return $result;
	}

	/**
	 * Convert value to record for database
	 * @param array $rec Array with Fields
	 * @return string Nothing or Fieldname or Original filename
	 */
	function value2db($rec)
	{


		if(isset($_REQUEST["del"])) $del = $_REQUEST["del"];

		if($rec[$this->fieldName()]["tmpfile"]=="" && $rec[$this->fieldName()]["filename"]!=""
		&& !$this->hasFlag(AF_FILE_NO_SELECT)
		&& (!isset($del[$this->fieldName()]) || $del[$this->fieldName()]!="on"))
		{
			return $rec[$this->fieldName()]["filename"];
		}

		if($this->hasFlag(AF_FILE_NO_DELETE)) unset($del);  // Make sure if flag is set $del unset!

		if(isset($del[$this->fieldName()]) && $del[$this->fieldName()] == "on")
		{
			if($this->hasFlag(AF_FILE_PHYSICAL_DELETE))
			{
				$file = "";
				if (isset($rec[$this->fieldName()]["postdel"]) && $rec[$this->fieldName()]["postdel"]!="")
				{
					atkdebug("postdel set");
					$file = $rec[$this->fieldName()]["postdel"];
				}
				else if ( isset($rec[$this->fieldName()]["orgfilename"]))
				{
					atkdebug("postdel not set");
					$file = $rec[$this->fieldName()]["orgfilename"];
				}
				atkdebug("file is now ".$file);
				if ($file!="")
				{
					unlink($this->m_dir.$file);
				}
			}
			return '';
		}
		else
		{
			$filename = $rec[$this->fieldName()]["filename"];
			// why copy if the files are the same?

			if ($this->m_dir.$filename != $rec[$this->fieldName()]["tmpfile"])
			{
				if ($filename!="")
				{
					/*  if (@copy($rec[$this->fieldName()]["tmpfile"],$this->m_dir.$filename))
					 {
					 $this->processFile($this->m_dir, $filename);
					 return $filename;
					 }
					 else
					 {
					 atkerror("File could not be saved");
					 return "";
					 }
					 */
					return $filename;
				}
			}
			return $rec[$this->fieldName()]["orgfilename"];
		}
	}

	/**
	 * Perform processing on an image right after it is uploaded.
	 *
	 * If you need any resizing or other postprocessing to be done on a file
	 * after it is uploaded, you can create a derived attribute that
	 * implements the processFile($filepath) method.
	 * The default implementation does not do any processing.
	 * @param String $filepath The path of the uploaded file.
	 * @param String $filename The name of the uploaded file.
	 */
	function processFile($filepath, $filename)
	{
	}

	/**
	 * Convert value to string
	 * @param array $rec Array with fields
	 * @return array Array with tmpfile, orgfilename,filesize
	 */
	function db2value($rec)
	{
		return Array("tmpfile"=>$this->m_dir.$rec[$this->fieldName()],"orgfilename"=>$rec[$this->fieldName()],"filename"=>$rec[$this->fieldName()],"filesize"=>"?");
	}

	function validate(&$record, $mode)
	{
		parent::validate($record, $mode);

		$error = $record[$this->fieldName()]['error'];
		if ($error > 0)
		{
			switch ($error)
			{
				case UPLOAD_ERR_INI_SIZE:
				case UPLOAD_ERR_FORM_SIZE:
					triggerError($record, $this->fieldName(), 'error_file_size', atktext("error_file_size", "atk"));
					break;

				case UPLOAD_ERR_NO_TMP_DIR:
				case UPLOAD_ERR_PARTIAL:
				default:
					triggerError($record, $this->fieldName(), 'error_file_unknown', atktext("error_file_unknown", "atk"));
			}
		}
	}

	/**
	 * Get filename out of Array
	 * @param array $rec Record
	 * @return array Array with tmpfile,filename,filesize,orgfilename
	 */
	function fetchValue($rec)
	{
		if(isset($_REQUEST["del"])) $del=$_REQUEST["del"];

		$postfiles_basename = $rec[$this->fieldName()."_postfileskey"];

		$basename = $this->fieldName();

		if (is_array($_FILES)||($rec[$this->fieldName()]["select"] != "" && !$this->hasFlag(AF_FILE_NO_SELECT)) || ($rec[$this->fieldName()]["filename"]!="")) // php4
		{
			// if an error occured during the upload process
			// and the error is not 'no file' while the field is obligatory
			if ($_FILES[$postfiles_basename]['error'] > 0 && !(!$this->hasFlag(AF_OBLIGATORY) && $_FILES[$postfiles_basename]['error'] == UPLOAD_ERR_NO_FILE))
			{
				return array('error' => $_FILES[$postfiles_basename]['error']);
			}

			// if no new file has been uploaded..
			elseif (count($_FILES)==0||$_FILES[$postfiles_basename]["tmp_name"]=="none"||$_FILES[$postfiles_basename]["tmp_name"]=="")
			{
				// No file to upload, then check if the select box is filled
				if(isset($rec[$this->fieldName()]["select"]) && $rec[$this->fieldName()]["select"] != ""
				&& !$this->hasFlag(AF_FILE_NO_SELECT))
				{
					atkdebug("file selected!");
					$filename=$rec[$this->fieldName()]["select"];
					$orgfilename = $filename;
					$postdel = '';
					if (isset($del[$this->fieldName()]) && $del[$this->fieldName()]=="on")
					{
						$filename = '';
						$orgfilename='';
						$postdel = $rec[$this->fieldName()]["select"];
					}
					$result = array("tmpfile"=>"",
                          "filename"=>$filename,
                          "filesize"=>0,
                          "orgfilename"=>$orgfilename,
                          "postdel"=>$postdel);
				}  // maybe we atk restored data from session
				elseif(isset($rec[$this->fieldName()]["filename"]) && $rec[$this->fieldName()]["filename"]!="")
				{
					$result = $rec[$this->fieldName()];
				}
				else
				{
					$result = array("tmpfile"=>"",
                          "filename"=>"",
                          "filesize"=>0,
                          "orgfilename"=>(isset($rec[$basename."_orgfilename"]))?$rec[$basename."_orgfilename"]:"");
				}
			}
			else
			{
				$realname = $this->_filenameMangle($rec, $_FILES[$postfiles_basename]["name"]);

				if ($this->m_autonumbering)
				{
					$realname = $this->_filenameUnique($rec, $realname);
				}

				$result = array("tmpfile"=>$_FILES[$postfiles_basename]["tmp_name"],
                          "filename"=>$realname,
                          "filesize"=>$_FILES[$postfiles_basename]["size"],
                          "orgfilename"=>$realname);
			}

			return $result;
		}
	}

	/**
	 * Check if the attribute is empty..
	 * @param array $postvars Array with the postvars
	 * @return boolean true if no image was uploaded
	 */
	function isEmpty($postvars)
	{
		if (is_array($_FILES))
		{
			// php4
			return ($_FILES[$this->fieldName()]["tmp_name"]=="none");
		}
		else
		{
			// php3
			return ($postvars[$this->fieldName()]=="none");
		}
	}

	/**
	 * Deletes file from HD
	 * @param array $record Array with fields
	 * @return boolean False if the delete went wrong
	  
	 function delete($record)
	 {
	 if($this->hasFlag(AF_FILE_PHYSICAL_DELETE)&&($record[$this->fieldname()]["orgfilename"]!=""))
	 {
	 if(!@unlink($this->m_dir.$record[$this->fieldName()]["orgfilename"]))
	 {
	 return false;
	 }
	 }
	 return true;
	 }
	 */
	function fichier_ouvrir($id_document,$url_seule_o_n='n')
	{

		$table=$this->m_ownerInstance->m_table;
		$db = &atkGetDb();
		$sql="select file_content,file_name, file_size from $table where $id_document";
		$data=$db->getrows($sql);

		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		$filename=$data[0]["file_name"];
		$file =@fopen($this->m_dir.$filename,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$data[0]["file_content"]="";
		if ($url_seule_o_n=='n')
		{header('Location:' . $this->m_url . $filename);
		exit;}
		else
		{ return $this->m_url . $filename;}

	}

	function fichier_upload($id_document_selector,$type)
	{
		$user = getUser();
		$userid = $user["id"];
		$db = &atkGetDb();
		$table=$this->m_ownerInstance->m_table;
		global $g_sessionManager;
			$individuid= $g_sessionManager->getValue("id_individu_utilisateur", "globals");
		if ($type=="utilisateur")
		{	
			$uploaddir = atkconfig("uploads_utilisateurs_dir")."$individuid"."/";
				}
		if ($type=="organisme")
		{
			$sql="select id_organisme from $table where $id_document_selector";
			$data=$db->getrows($sql);
			$uploaddir = atkconfig("uploads_organismes_dir").$data[0]["id_organisme"]."/";
		}			
		if (!file_exists($uploaddir))
        {
          mkdir($uploaddir);
        }
		$sql="select id, file_content,file_name, file_size, file_extension from $table where $id_document_selector";
		$data=$db->getrows($sql);
		$data[0]["file_content"]=base64_decode($data[0]["file_content"]);
		($type=="organisme") ? $filename="organisme_document_".$data[0]["id"].'.'.$data[0]["file_extension"] : $filename="individu_document_".$data[0]["id"].'.'.$data[0]["file_extension"];
		$extension=$data[0]["file_extension"];
		$filename=$uploaddir.$filename;
		$file =@fopen($filename,"w");
		@fwrite($file,$data[0]["file_content"],$data[0]["file_size"]);
		@fclose($file);
		$url_upload=$filename;
		$data[0]["file_content"]="";
		if ($type=="organisme")
		{
		$sql=" update $table set id_upload=$individuid, date_upload=UTC_TIMESTAMP(), url_upload='".$url_upload."' 
		, id_modification=$userid, date_modification=UTC_TIMESTAMP() where $id_document_selector";
		}
	if ($type=="utilisateur")
		{
		$sql=" update $table set  date_upload=UTC_TIMESTAMP(), url_upload='".$url_upload."' 
		, id_modification=$userid, date_modification=UTC_TIMESTAMP() where $id_document_selector";
		}
		$db->query($sql);
		return $url_upload;
	}


	/**
	 * Display values
	 * @param array $record Array with fields
	 * @return string Filename or Nothing
	 */
	function display($record)
	{

		$filename    = $record[$this->fieldName()]["orgfilename"];
		$ext = $this->getFileExtension($filename);

		if($filename != "")
		{
			$table=$this->m_ownerInstance->m_table;
			$db = &atkGetDb();
			$sql="select file_content from ".$table." where id='".$record['id']."' ";

			$data=$db->getrows($sql);

			$data[0]["file_content"]=base64_decode($data[0]["file_content"]);

			$file =@fopen($this->m_dir.$filename,"w");
			@fwrite($file,$data[0]["file_content"],$record["file_size"]);
			@fclose($file);
			$data[0]["file_content"]="";


			if(is_file($this->m_dir.$filename))
			{
				//			$page = &atkPage::getInstance();
				//			$page->register_script(atkconfig("atkroot")."atk/javascript/newwindow.js");
				$result="<b><a href=\"".$this->m_url."$filename\" target=\"_blank\">TÚlÚcharger/Ouvrir</a></b>";
				//			$result.='<b><a href="'.$this->m_url.$filename.'" alt="'.$filename.'" onclick="NewWindow(this.href,\'name\',\''.($imagehw[0]+50).'\',\''.($imagehw[1]+50).'\',\'yes\');return false;">Ouvrir</a></b><br />';
				//		exportFile($this->m_tbsooo->GetPathnameDoc(), $outputfilename, ($forcedownload?"application/octet-stream":$this->m_tbsooo->GetMimetypeDoc()));
				return $result;
			}
			else
			{
				return $filename."(<font color=\"#ff0000\">".atktext("file_not_exist", "atk")."</font>)";
			}
		}}


		function getFileExtension($filename)
		{
			return strtolower(substr($filename, strrpos($filename,'.')+1,strlen($filename)));
		}

		function getSearchModes()
		{
			// exact match and substring search should be supported by any database.
			// (the LIKE function is ANSI standard SQL, and both substring and wildcard
			// searches can be implemented using LIKE)
			// Possible values
			//"regexp","exact","substring", "wildcard","greaterthan","greaterthanequal","lessthan","lessthanequal"
			return array("exact","substring","wildcard","regexp");
		}

		/**
		 * Determine the real filename of a file (based on m_filenameTpl).
		 * @access private
		 */
		function _filenameMangle($rec, $default)
		{
			if ($this->m_filenameTpl == "")
			{
				$filename = $default;
			}
			else
			{
				atkimport("atk.utils.atkstringparser");
				$parser = new atkStringParser($this->m_filenameTpl);
				$ext = strtolower(substr($default, strrpos($default,'.')+1));
				$filename = $parser->parse($rec).".".$ext;
			}
			return str_replace(' ','_',$filename);
		}

		/**
		 * Give the file a uniquely numbered filename.
		 *
		 * @access private
		 * @param array $rec The record for thish the file was uploaded
		 * @param String $filename The name of the uploaded file
		 * @return String The name of the uploaded file, renumbered if necessary
		 */
		function _filenameUnique($rec, $filename)
		{
			// check if there's another record using this same name. If so, (re)number the filename.
			atkdebug("unique check");

			$name = substr($filename, 0, strrpos($filename,'.'));
			$ext = substr($filename, strrpos($filename,'.')+1);

			$selector = "(".$this->fieldName()."='$filename' OR ".$this->fieldName()." LIKE '$name-_.$ext')";
			if ($rec[$this->m_ownerInstance->primaryKeyField()]!="")
			{
				$selector.= " AND NOT (".$this->m_ownerInstance->primaryKey($rec).")";
			}

			$count = $this->m_ownerInstance->countDb("($selector)", "", array($this->fieldName()));

			atkdebug("count ".$count);

			if ($count>0)
			{
				// file name exists, so mangle it with a number.
				$filename = $name."-".$count.".".$ext;
			}

			return $filename;
		}

		/**
		 * Returns a piece of html code that can be used in a form to display
		 * hidden values for this attribute.
		 * @param array $record Array with values
		 * @return string Piece of htmlcode
		 */
		function hide($record="", $fieldprefix)
		{
			$field = $record[$this->fieldName()];

			if (is_array($field))
			foreach ($field as $key => $value)
			$result .= '<input type="hidden" name="'.$fieldprefix.$this->formName().'['.$key.']" '.'value="'.$value.'">';

			else
			$result = '<input type="hidden" name="'.$fieldprefix.$this->formName().'" value="'.$field.'">';

			return $result;
		}

		function dbFieldType()
		{
			return "string";
		}

}
?>
