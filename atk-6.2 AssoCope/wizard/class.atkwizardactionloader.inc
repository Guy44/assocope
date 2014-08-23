<?php

  /**
   * This file is part of the Achievo ATK distribution.
   * Detailed copyright and licensing information can be found
   * in the doc/COPYRIGHT and doc/LICENSE files which should be
   * included in the distribution.
   *
   * @package atk
   * @subpackage wizard
   *
   * @author maurice <maurice@ibuildings.nl>
   *
   * @copyright (c) 2006 Ibuildings.nl BV
   * @license see doc/LICENSE
   *
   * @version $Revision: 5230 $
   * $Id: class.atkwizardactionloader.inc 5230 2007-08-30 08:08:05Z ivo $
   */

  /**
   * Converts a atkwizardaction key array to string value.
   *
   * @author maurice <maurice@ibuildings.nl>
   * @package atk
   * @subpackage wizard
   *
   */
  class AtkWizardActionLoader
  {
    function getWizardAction($wizardAction)
    {
      if(is_array($wizardAction))
        return key($wizardAction);
      else
        return $wizardAction;
    }
  }

?>