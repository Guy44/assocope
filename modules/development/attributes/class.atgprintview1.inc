<?php


/**
 * The atkTextNom is used for Nom normalization (trim spaces and all in lowercase except first letter.)
 *   
 * @author guy gourmellet
 * 
 *
 */
class atgPrintView1 extends atkDummyAttribute {

	/**
	 * Constructor
	 * @param $name  Name of the attribute
	 * @param $flags Flags for this attribute
	 * @param $size  The size(s) for this attribute (default 10)
	
	 */
	function atgPrintView1($name, $flags = 0, $size = 0) {
		$this->m_name = $name;
		$this->m_flags = (double) $flags;
		$this->setAttribSize($size);

	}
/**
    * Display a record
    * Here it will only returns the text.
    * @param $record  Array with fields
    * @return Parsed string
    */
    function display($record)
    {
      $db = &atkGetDb();
    
      $query = &$db->createQuery();
      $query->addTable("stuff");
      $query->addJoin("item", "", "item.id = stuff.item_id", false);
      $query->addJoin("notes", "", "notes.id = item.notes_id", false);
      $query->addField("item.item");
      $query->addField("item.name");
      $query->addField("notes.note");
      $query->addField("stuff.name as sname");
      $query->addCondition("stuff.person_id = ".$record["id"]);
 
      $stuff = $db->getrows($query->buildSelect());
      $tbl = &atknew("atk.utils.atktablerenderer");
 
      $data = array();
      // Develop a table however you'd like it to display
 
      // Use cascading style sheets to alter the appearance.
      $tbl->setRowClass(1, "superbold");
      // ....
      // Create data
      for ($i=0, $_i=count($stuff); $i<$_i; $i++)
      {
         $row = array();
         $row[]="";
         $row[]=$stuff[$i]["..."];
         $row[]=$stuff[$i]["..."];
         $data[] = $row;
      }
 
      // render table.
      $output = $tbl->render($data, 0, "navpers");
      return $output;
    }
}
?>
