<?php
  /**
   * This file is part of the Achievo ATK distribution.
   * Detailed copyright and licensing information can be found
   * in the doc/COPYRIGHT and doc/LICENSE files which should be
   * included in the distribution.
   *
   * @package atk
   * @subpackage security
   *
   * @copyright (c)2000-2004 Ivo Jansch
   * @license http://www.achievo.org/atk/licensing ATK Open Source License
   *
   * @version $Revision: 4385 $
   * $Id: class.auth_none.inc 4385 2006-12-09 08:50:55Z ivo $
   */

  /**
   * Dummy driver for non-authentication. When using 'none' as authentication
   * method, any loginname and any password will be accepted.
   *
   * @author Ivo Jansch <ivo@achievo.org>
   * @package atk
   * @subpackage security
   *
   */
   class auth_none extends auth_interface
   {
     function validateUser($user, $passwd)
     {
       if ($user == "")
        return AUTH_SUCCESS;
       else
        return AUTH_MISMATCH;
     }

     function canMd5()
     {
       return false;
     }
   }

?>