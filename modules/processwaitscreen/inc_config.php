<?
// 
define( "BASE_PATH", "" );

if( isset( $ENABLE_DEBUG ) )
{
	$SHOW_DEBUG = null;
	session_register( 'SHOW_DEBUG' );
	$SHOW_DEBUG = $HTTP_GET_VARS['ENABLE_DEBUG'];
}
if( !isset( $SHOW_DEBUG ) )
{
	$SHOW_DEBUG = 1;
}

session_register( 'SHOW_DEBUG' );


if( !isset( $fuseAction ) || empty( $fuseAction ) )
	$fuseAction = "default";
	
?>