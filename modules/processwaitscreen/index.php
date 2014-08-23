<?
include( "inc_config.php" );

switch( $fuseAction )
{

	case "default":
		include( BASE_PATH . "dsp_contactForm.php" );
		break;
	end;
	
	case "processContactForm":
		// Include this line to enable wait screen
		include( BASE_PATH."act_processStart.php" );

		/*** Include all your process here ***/
		include( BASE_PATH."act_processContactForm.php");
		/*************************************/
		
		// Define the GOTO variable to redirect the user
		$GOTO = BASE_PATH . "index.php?fuseAction=processContactFormConfirm";
		
		// Include this line at the end of your process to redirect the user
		include( BASE_PATH."act_processEnd.php" );	
		break;
	end;
	
	case "processContactFormConfirm":
		include( BASE_PATH . "dsp_processContactFormConfirm.php" );
		include( BASE_PATH . "dsp_contactForm.php" );
		break;
	end;

	case "waitScreen":
		include( BASE_PATH . "dsp_waitScreen.php" );
		break;
	end; 
	
	default:
		echo "<font color=red><b>$fuseAction</b> unknow !</font>";
		break;
	end;
	
}

?>