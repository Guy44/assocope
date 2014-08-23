<?
if( !$SHOW_DEBUG )
{
?>

<script language=javascript>
	setTimeout( "top.location.replace('<?=$GOTO?>')", 0 );
</script>	

<?
}
else
{

	echo "<pre><a href=\"$GOTO\" target=_top>Process terminated, continue to <b>$GOTO</b></a></pre>";
	
}

die();
?>

