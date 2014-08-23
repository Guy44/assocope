function menuload(menuurl, mainurl)
{
  parent.menu.location.href= menuurl;
  parent.main.location.href= mainurl;
}

function reloadTopEntite(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedEntite="+id;
}

function reloadTopValeur(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedValeur="+id;
}
function reloadTopAction(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedAction="+id;
}
function reloadTopType(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedType="+id;
}

function reloadTopEntite1(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedEntite1="+id;
}

function reloadTopValeur1(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedValeur1="+id;
}
function reloadTopAction1(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedAction1="+id;
}
function reloadTopType1(el)
{
  var id = el.options[el.selectedIndex].value;
  window.location= "top.php?selectedType1="+id;
}