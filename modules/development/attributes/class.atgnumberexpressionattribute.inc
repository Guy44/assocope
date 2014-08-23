<?php



class atgNumberExpressionAttribute extends atkExpressionAttribute {


   function display($record, $mode="")
    {
      if (isset($record[$this->fieldName()]) && $record[$this->fieldName()]!=="")
      {
        return '<p style="text-align: right;">'.$record[$this->fieldName()].'</p>';
      }
      return "";
    }
}
?>
