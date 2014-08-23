<?

class POSTForm
{
	var $name;
	
	var $fields = array();

	var $html;
	
	var $target;
	var $action;
	
	
	function POSTForm( $fields, $action = "index.php", $target = "_self" )
	{
		$this -> name = "_".strtoupper(md5(uniqid(time())));
	
		$this -> fields = $fields;
		$this -> action = $action;
		$this -> target = $target;
		
		$this -> build();
	}
	
	function output()
	{
		echo $this -> html;
	}
	
	function post( $timeout = 0 )
	{
		echo "<script language=javascript>setTimeout( \"document.forms['".$this -> name."'].submit()\", $timeout);</script>";
	}
	
	
	
	/**************************************** private */
	
	function build()
	{
		$this -> html =  "<form name=".$this -> name." method=post action=".$this -> action." target=".$this -> target." enctype=\"multipart/form-data\">";
		foreach( $this -> fields as $fieldName => $fieldValue )
		{
			$this -> buildField( $fieldName, $fieldValue );
		}
		$this -> html .= "</form>";
	}
	
	function buildField( $fieldName, $fieldValue )
	{
		if( is_array( $fieldValue ) )
		{
			foreach( $fieldValue as $sFieldName => $sFieldValue )
			{
				$this -> html .= "<input type=hidden name=\"".$fieldName."[".$sFieldName."]\" value=\"".$sFieldValue."\">";
			}
		}
		else
		{
			$this -> html .= "<input type=hidden name=\"".$fieldName."\" value=\"".$fieldValue."\">";
		}
	}
	
	
}


?>