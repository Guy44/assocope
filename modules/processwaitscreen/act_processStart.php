<?
if( !isset( $ENABLE_PROCESS ) || !$ENABLE_PROCESS )
{
	include_once( BASE_PATH . "class_POSTForm.php" );

	if( empty( $HTTP_POST_VARS ) )
	{
		$template_param = array();
		$template_param[ 'title' ]		 = "Wait screen..."; // Titre de la page
		$template_param[ 'requestPage' ] = $PHP_SELF.( isset( $QUERY_STRING )? "?$QUERY_STRING&ENABLE_PROCESS=1":"?ENABLE_PROCESS=1"  );
		$template_param[ 'waitPage' ]	 = BASE_PATH . "index.php?fuseAction=waitScreen";
	}
	else
	{
		$POST_FORM = new POSTform( $HTTP_POST_VARS, $PHP_SELF.( isset( $QUERY_STRING )? "?$QUERY_STRING&ENABLE_PROCESS=1":"?ENABLE_PROCESS=1" ), "requestFrame" );
		$POST_FORM -> output();
		
		$template_param = array();
		$template_param[ 'title' ]		 = "Wait screen..."; // Titre de la page
		$template_param[ 'requestPage' ] = '';
		$template_param[ 'waitPage' ]	 = BASE_PATH . "index.php?fuseAction=waitScreen";
	}
	?>
	
	<html>
	<head>
			<title><?=$template_param[ 'title' ]?></title>
			<script language=JavaScript src=<?=$MOVIESCENEWEBPATH?>home/index.php?fuseAction=javaScript></script>
			<script language=javascript>
				<?
				if( isset( $template_param[ 'requestPage' ] ) && !empty( $template_param[ 'requestPage' ] ) )
				{
				?>
					setTimeout( "requestFrame.location.replace ('<?=$template_param[ 'requestPage' ]?>')", 500 ); 
				<?
				}
				?>
			</script>
			<?
			if( isset( $POST_FORM ) && is_object( $POST_FORM ) )
			{
				$POST_FORM -> post( 500 );
			}
			?>
	</head>
		<frameset rows="<?=($SHOW_DEBUG)? '*,250':'*,0'?>" frameborder=0 framespacing=0 border=2>
			<frame src="<?=$template_param[ 'waitPage' ]?>" noresize name="mainFrame" id="mainFrame" scrolling="no" frameborder="0">
			<frame src="" noresize name="requestFrame" scrolling="yes" frameborder="0">
			<noframes>
			    <body>
			        This text will appear only if the browser does not support frames.
			    </body>
			</noframes>
		</frameset>
		
		
	</html>
	<?
	die(); // Stop all processes
}
?>