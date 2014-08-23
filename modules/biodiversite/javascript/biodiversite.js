
function getid_type_localisation()
{
	id_type_localisation = $F('id_type_localisation');
  if(id_type_localisation==null) return '1';
  return id_type_localisation;
}



function show_ville()
{
  $('tabbedPaneAttr_id_ville').style.display = 'inline';
  $('tabbedPaneAttr_id_lieu').style.display = 'none';
  $('tabbedPaneAttr_id_point_observation').style.display = 'none';
  $('tabbedPaneAttr_id_point_observation_1').style.display = 'none';
  $('tabbedPaneAttr_id_point_observation_2').style.display = 'none';
  $('tabbedPaneAttr_latitude').style.display = 'none';
  $('tabbedPaneAttr_longitude').style.display = 'none';
}

function show_lieu()
{
	$('tabbedPaneAttr_id_ville').style.display = 'none';
	  $('tabbedPaneAttr_id_lieu').style.display = 'inline';
	  $('tabbedPaneAttr_id_point_observation').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_1').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_2').style.display = 'none';
	  $('tabbedPaneAttr_latitude').style.display = 'none';
	  $('tabbedPaneAttr_longitude').style.display = 'none';
}

function show_point()
{
	$('tabbedPaneAttr_id_ville').style.display = 'none';
	  $('tabbedPaneAttr_id_lieu').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation').style.display = 'inline';
	  $('tabbedPaneAttr_id_point_observation_1').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_2').style.display = 'none';
	  $('tabbedPaneAttr_latitude').style.display = 'none';
	  $('tabbedPaneAttr_longitude').style.display = 'none';

}

function show_points()
{
	$('tabbedPaneAttr_id_ville').style.display = 'none';
	  $('tabbedPaneAttr_id_lieu').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_1').style.display = 'inline';
	  $('tabbedPaneAttr_id_point_observation_2').style.display = 'inline';
	  $('tabbedPaneAttr_latitude').style.display = 'none';
	  $('tabbedPaneAttr_longitude').style.display = 'none';

}
function show_latlon()
{
	$('tabbedPaneAttr_id_ville').style.display = 'none';
	  $('tabbedPaneAttr_id_lieu').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_1').style.display = 'none';
	  $('tabbedPaneAttr_id_point_observation_2').style.display = 'none';
	  $('tabbedPaneAttr_latitude').style.display = 'inline';
	  $('tabbedPaneAttr_longitude').style.display = 'inline';

}


function change_id_type_localisation(id_type_localisation)
{
  
  if(id_type_localisation==null)
  {
    recur=getid_type_localisation();
  }

  switch(id_type_localisation)
  {

    case 'ville':
      show_ville();
      break;
    case 'lieu':
      show_lieu();
      break;
    case 'point':
      show_point();
      break;
    case 'points':
      show_points();
      break;
    case 'latlon':
        show_latlon();
        break;
  }
//  showTab(getCurrentTab());
}

