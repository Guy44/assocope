<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">

<html>
<head>
	<title>waitScreen Demo</title>
	<script language=javascript>
	function setDebug( )
	{
		o = event.srcElement;
		if( o.checked && <?=$SHOW_DEBUG?> != 1 )  top.location.href="index.php?ENABLE_DEBUG=1"; 
		if( !o.checked && <?=$SHOW_DEBUG?> == 1 ) top.location.href="index.php?ENABLE_DEBUG=0";
	}
	</script>
</head>

<body>


This is a demo page. By submitting a form, you'll be redirected to a fully customizable wait screen during the process, then redirected to the confirmation page.

<br>
<table cellpadding=2 cellspacing=0 border=0>
	<tr>
		<td><input type=checkbox onclick=setDebug() <?=($SHOW_DEBUG)? 'checked':''?>></td>
		<td><i>Enable debug mode</i></td>
	</tr>
</table>
<br>


<hr>
<table cellpadding=2 cellspacing=0 border=0>
<form method=get action="index.php">
<input type=hidden name=fuseAction value=processContactForm>
	<tr>
		<td><b>GET method demo</b><br></td>
	</tr>
	<tr>
		<td>
			<i>Your name :</i><br>
			<input type=text name=myContactFormName value="John DOE"><br>
		</td>
	</tr>
	<tr>
		<td><input type=submit></td>
	</tr>
</form>
</table>
<hr>

<table cellpadding=2 cellspacing=0 border=0>
<form method=get action="index.php">
<input type=hidden name=fuseAction value=processContactForm>
	<tr>
		<td><b>GET method demo</b><br></td>
	</tr>
	<tr>
		<td>
			<i>Your name :</i><br>
			<input type=text name=myContactFormName value="John DOE"><br>
		</td>
	</tr>
	<tr>
		<td><input type=submit></td>
	</tr>
</form>
</table>


</body>
</html>

