/* MENU NAVIGATION */
var defaultIndex = 0;

function initMenu(index)
{
	defaultIndex = index;
	var dtList = gE("menu").getElementsByTagName("dt");
	for(var i = 0 ; i < dtList.length ; i++)
		if(dtList[i].id.indexOf('menudt') == 0)
		{	
			if(gE(dtList[i].id + 'dd').getElementsByTagName("ul").length != 0)
			{
				gE(dtList[i].id + 'dd').initialHeight = gE(dtList[i].id + 'dd').offsetHeight;
				dtList[i].onclick = function(){affichedd(this);};
				dtList[i].className = 'currentRubriqueNotSelecteds';
			}
		}
	effacedd(0);
}
function affichedd(elem)
{
	effacedd(elem.id);
	elem.className = 'currentRubrique';
	var dd = gE(elem.id + 'dd');
	if(dd.style.display == "block")
		changesizedd(dd , '-');
	else
	{
		dd.style.display = 'block';
		changesizedd(dd , '+');
	}
}
function effacedd(id)
{
	var dtList = gE("menu").getElementsByTagName("dt");
	for(var i = 0 ; i < dtList.length ; i++)
		if(dtList[i].id.indexOf('menudt') == 0 && dtList[i].id != id)
		{
			if(dtList[i].className != '')
				dtList[i].className = 'currentRubriqueNotSelected';
			if(dtList[i].id != "menudt"+defaultIndex)
			{
				if(id == 0)
					changesizedd(gE(dtList[i].id + 'dd') , '0');
				else 
					changesizedd(gE(dtList[i].id + 'dd') , '-');
			}
			else
				defaultIndex = 0;
		}
}
function changesizedd(elem, value)
{
	if(value == '-' && elem.offsetHeight > 10)
	{
		elem.style.height = (elem.offsetHeight - 10) + 'px';
		setTimeout(function(){changesizedd(elem, value)}, 20);
	}
	else if(value == '+' && elem.offsetHeight < elem.initialHeight - 10)
	{
		elem.style.height = (elem.offsetHeight + 10) + 'px';
		setTimeout(function(){changesizedd(elem, value)}, 20);
	}
	else if(value == '0' || value == '-')
	{
		elem.style.height = '0px';
		elem.style.display = 'none';
	}
	else if(value == '+')
		elem.style.height = elem.initialHeight + 'px';
}

/* HOME DIAPORAMA */
var nb_diaporama = 0;
var diaporamaOn = 0;
var currentDiapo = -1;
function initHomeDiaporama()
{
	var aList = gE("diapoVignette").getElementsByTagName("a");
	for(var i = 0 ; i < aList.length ; i++)
	{
		if(aList[i].id.indexOf('lien_home_') == 0)
		{	
			aList[i].onmouseover = function(){diaporamaOn = 0;focusDiapo(this)};
			aList[i].onmouseout = function(){diaporamaOn = 1};
			nb_diaporama++;
		}
	}
	diaporamaOn = 1;
	routineDiaporama();
}
function focusDiapo(elem)
{
	currentDiapo = elem.id.replace('lien_home_','');
	unfocusDiapo();
	elem.className = 'selected';
	gE('diapoTitre').innerHTML = gE(elem.id + '_titre').innerHTML;
	gE('diapoChapeau').innerHTML = gE(elem.id + '_chapeau').innerHTML;
	gE('diapoGrande').style.backgroundImage = 'url(' + gE(elem.id + '_image').src + ')';
}

function unfocusDiapo()
{
	var aList = gE("diapoVignette").getElementsByTagName("a");
	for(var i = 0 ; i < aList.length ; i++)
		if(aList[i].id.indexOf('lien_home_') == 0)
			aList[i].className = '';
}
function routineDiaporama()
{
	if(diaporamaOn == 1)
	{
		if(currentDiapo >= nb_diaporama - 1)
			currentDiapo = -1;
		focusDiapo(gE('lien_home_'+(++currentDiapo)));
	}
	setTimeout('routineDiaporama()',4500);
}

/* HOME RECHERCHE */
function recherche(elem)
{
	if(elem.value != '' && elem.value != elem.oldValue)
		document.location = elem.title + elem.value;
}
	
/* FONCTION AJAX (FLASHINDEX) */
function execAjax(value, elem, type, currentUrl)
{
	//alert(value +","+ elem +","+ type +","+ currentUrl);
	var currentElem = gE(elem);
	var currentType = type;

	var http = getHTTPObject(); // We create the HTTP Object
	http.open("GET", currentUrl + escape(value), true);
	http.onreadystatechange = function () 
		{
			if (http.readyState == 4) 
			{
				// Split the comma delimited response into an array
				results = http.responseText;
				if(results!="")
					if(currentType == "value")
						currentElem.value = results;
					else if(currentType == "innerhtml")
						currentElem.innerHTML = results;
					else if(currentType == "htmladd")
						currentElem.innerHTML += results;
			}
		};
	http.send(null);
}
function getHTTPObject()
{
	var xmlhttp;
	/*@cc_on
	@if (@_jscript_version >= 5)
		try {
			xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
		} catch (e) {
			try {
				xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
			} catch (E) {
				xmlhttp = false;
			}
		}
	@else
		xmlhttp = false;
	@end @*/
	if (!xmlhttp && typeof XMLHttpRequest != 'undefined') 
	{
		try {
			xmlhttp = new XMLHttpRequest();
		} catch (e) {
			xmlhttp = false;
		}
	}
	return xmlhttp;
}	
function ident(formtitle)
{
	//gE("li_alert").style.display = "none";
	if(gE("txt_" + formtitle + "_flash_licence").value != "")
	{
		gE("div_" + formtitle + "_reponse").innerHTML = "Recherche en cours ...";
		var value = gE("txt_" + formtitle + "_flash_licence").value;
		var elem = "div_" + formtitle + "_reponse";
		var type = 'innerhtml';
		var currentUrl = "ajax/$flashIndex$.aspx?num_lic=";
		execAjax(value, elem, type, currentUrl);
		gE("div_" + formtitle + "_form").style.display = "none";
		gE("div_" + formtitle + "_retour").style.display = 'block';
	}
	else
	{
		gE("div_" + formtitle + "_reponse").innerHTML = "Veuillez indiquer un numero de licence valide";
	}
}
function flashRetour(formtitle)
{
	gE('div_' + formtitle + '_form').style.display = "block";
	gE('div_' + formtitle + '_reponse').innerHTML = "";
	gE('div_' + formtitle + '_retour').style.display = 'none';
	gE('txt_' + formtitle + '_flash_licence').value = '';
}
/* OPEN DE FRANCE RUBRIQUE */
var nbOpen = 0;
function selectTab(id, nb)
{
	if(nb != undefined)
		nbOpen = nb;
	for(var i = 0 ; i < nbOpen ; i++)
		gE("lnk_"+i).className = "";
	gE("lnk_"+id).className = "selected";
	gE("div_visible").innerHTML = gE("div_open_"+id).innerHTML;
}

/* LIGHTBOX */
var isLBON = false;
function gradient(id, level)
{
	if(isLBON)
	{
		var box = gE(id);
		box.style.opacity = level;
		box.style.MozOpacity = level;
		box.style.KhtmlOpacity = level;
		box.style.filter = "alpha(opacity=" + level * 100 + ")";
		box.style.display="block";
	}
	return;
}
function fadein(id) 
{
	
	var level = 0;
	while(level <= 1)
	{
		setTimeout( "gradient('" + id + "'," + level + ")", (level* 1000) + 10);
		level += 0.01;
	}
}
function openbox(formtitle, fadin)
{
	isLBON = true;
	var box = gE(formtitle); 
	gE('filter').style.display='block';
	gE('div_' + formtitle + '_form').style.display = 'block';
	if(formtitle == "FLbox")
	{
		gE('div_' + formtitle + '_retour').style.display = 'none';
		gE('div_' + formtitle + '_reponse').innerHTML = '';
		gE('txt_' + formtitle + '_flash_licence').value = '';
	}

	if(fadin)
	{
		gradient(formtitle, 0);
		fadein(formtitle);
	}
	else
		box.style.display='block';	
}
function closebox(formtitle)
{
	isLBON = false;
	gE(formtitle).style.display='none';
	gE('filter').style.display='none';
}

/* Function de cache */
function MM_swapImgRestore() { //v3.0
var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;}
function MM_preloadImages() { //v3.0
var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
	var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
	if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}}
function MM_findObj(n, d) { //v4.01
var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
	d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
if(!x && d.getElementById) x=d.getElementById(n); return x;}
function MM_swapImage() { //v3.0
var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}}

/* OPEN DE FRANCE LEADERBOARD */
tabRefresh = new Array();
tabFonction = new Array();
window.onload = function()
{
	for(var i = 0 ; i < tabRefresh.length; i++)
	{
		var temp_module = tabRefresh[i].split("|||")[0];
		var temp_div = tabRefresh[i].split("|||")[1];
		refreshLeaderBoard(temp_module, temp_div);
	}
	for(var i = 0 ; i < tabFonction.length; i++)
	{
		tabFonction[i]();
	}
}
function addRefresh(module, div)
{
	tabRefresh[tabRefresh.length] = module+'|||'+div;
}  
function addFonction(obj)
{
	tabFonction[tabFonction.length] = obj;
}

function refreshLeaderBoard(module, div)
{
	execAjax(module,div,'innerhtml','/ajax/leaderboard.aspx?id_langue=1&id_module=');
	setTimeout(function(){refreshLeaderBoard(module, div);},120000);
}
/*OPEN DE FRANCE Diaporama*/
function boucleImage()
{
	if(imageboucle == 1)
	{
		getNextImage();
		mI_aI();
	}
	setTimeout("boucleImage()", 6000);
}
function getNextImage()
{
	curImgId++;
	if(gE("imgJ_"+curImgJour+"_"+curImgId) == null)
	{
		curImgJour++;
		curImgId = 0;
		
		if(gE("imgJ_"+curImgJour+"_"+curImgId) == null)
		{
			curImgJour = 0;
			curImgId = 0;
		}
	}
}

function nI_aI()
{
	imageboucle = 0;
	curImgId++;
	mI_aI();
}
function pI_aI()
{
	imageboucle = 0;
	curImgId--;
	mI_aI();
}
function mI_aI()
{
	var nb = gE("div_count").innerHTML;
	for(var i = 0 ; i < nb ; i++)
		gE("lnk_il_"+i).className = "";
	gE("lnk_il_"+curImgJour).className = "selected";
			
	gE("img_currentPhoto").src = gE("imgJ_"+curImgJour+"_"+curImgId).src;
	gE("div_currentLegende").innerHTML = gE("divJ_"+curImgJour+"_"+curImgId).innerHTML;
	
	if(curImgId <= 0)
		gE("precPhoto").style.display = "none";
	else
		gE("precPhoto").style.display = "block";
		
	if(gE("imgJ_"+curImgJour+"_"+(curImgId+1)) == null)
		gE("nextPhoto").style.display = "none";
	else
		gE("nextPhoto").style.display = "block";
}

/* Fonction divers */
function gE(id){return document.getElementById(id)}
function openBourse(id){window.open('annonce.aspx?id='+id,'titre','statusbar=no,scrollbars=yes,resizable=no,width=600,height=450,left=0,top=0,screenX=0,screenY=0');}

/* BLOG Legende */ 
function dedans()
{
	if(gE("div_legende").innerHTML != "")
		gE("div_legende").style.display = "block";
}
function dehors()
{
	gE("div_legende").style.display = "none";
}
function update()
{
	gE("div_legende").style.top = (tempY - 30)+"px";
	gE("div_legende").style.left = (tempX - 170 - gE("mycontainer_global").offsetLeft)+"px";
}

var tempX = 0;
var tempY = 0;

function getMouseXY(e) 
{
	if (IE) 
	{
		tempX = event.clientX + document.documentElement.scrollLeft;
		tempY = event.clientY + document.documentElement.scrollTop;
	}
	else 
	{
		tempX = e.pageX;
		tempY = e.pageY;
	}  
	
	if (tempX < 0)
		tempX = 0;
	if (tempY < 0)
		tempY = 0; 
			
	update();
}

/* WINDOW ONLOAD */
$(document).ready(function(){
	//Ajout des LightBox sur les images News
	$(".colorbox").colorbox({maxWidth:"85%", maxHeight:"85%", 
		onOpen:function(){$("#module").toggleClass("invis")},onClosed:function(){$("#module").toggleClass("invis")}});
	//Ajout des css over sur les divs de liste de news
	var listeN = $(".liste");
	for(var i = 0 ; i < listeN.length ; i++)
	{
		listeN[i].oldClass = listeN[i].className;
		listeN[i].onmouseover = function(){this.className += " selected";};
		listeN[i].onmouseout = function(){this.className = this.oldClass;};
		listeN[i].onclick = function(){
			if( this.className.indexOf('target_blank') > -1)
				window.open(this.title);
			else
				document.location = this.title;
		};
	}
	var champT = $(".champT");
	for(var i = 0 ; i < champT.length ; i++)
	{
		champT[i].oldValue = champT[i].alt;
		champT[i].value = champT[i].alt;
		champT[i].onfocus = function(){if(this.value == this.oldValue){this.value = ''};};
		champT[i].onblur = function(){if(this.value == ''){this.value = this.oldValue};};
	}
	
	$(".openFlashIndex").click(function(){
		$("body").scrollTop(0);
		$("html").scrollTop(0);
		openbox('FLbox', 1);
	});
	$(".openLicencie").click(function(){
		$("body").scrollTop(0);
		$("html").scrollTop(0);
		openbox('AUbox', 1);
	});
	
	//ColorBox
	$(".lightGuideDesGolfs").colorbox({width:"825px", height:"785px", iframe:true, opacity:"0.8"});
	$(".lightNews").colorbox({width:"600px", height:"700px", iframe:true, opacity:"0.2"});
	$(".lightVideo").colorbox({width:"502px", height:"470px", iframe:true, opacity:"0.2"});
	$(".lightNews800").colorbox({width:"800px", height:"600px", iframe:true, opacity:"0.2"});
	$(".lightNewsBlanc").colorbox({width:"600px", height:"700px", iframe:true, opacity:"0.2"});
	$(".lightNewsBlanc800").colorbox({width:"800px", height:"600px", iframe:true, opacity:"0.2"});
	$(".lighturl").colorbox({width:"540px", height:"700px", iframe:true, opacity:"0.2"});
	$("a[rel='light1']").colorbox({scrolling:false,height:function () { return ( parseInt( $("div.left_container").innerHeight(),10) +90 )+"px";}, width:"705px",inline:true, href:function () {return $("div.left_container").html();} });
    $("a[rel='light2']").colorbox({scrolling:false, height:function () { return (parseInt( $("div.right_container").innerHeight(),10) +90 ) +"px";},width:"705px",inline:true, href:function () {return $("div.right_container").html();} });
    $("a[rel='light3']").colorbox({scrolling:false,  height:function () { return (parseInt( $("div.switchbarre").innerHeight(),10) +250 )+ "px";},width:"705px",inline:true, href:function () {return $("div.switchbarre").html();} });
    $("#cboxClose").bind('click', function(){

            $.colorbox.remove()
			});
});

