
function getRecur()
{
  recur = $F('recur');
  if(recur==null) return 'once';
  return recur;
}



function show_daily()
{
  $('ar_daily_choice').style.display = 'block';
  $('ar_weekly_choice').style.display = 'none';
  $('ar_monthly_choice').style.display = 'none';
  $('ar_yearly_choice').style.display = 'none';

}

function show_weekly()
{
  $('ar_daily_choice').style.display = 'none';
  $('ar_weekly_choice').style.display = 'block';
  $('ar_monthly_choice').style.display = 'none';
  $('ar_yearly_choice').style.display = 'none';

}

function show_monthly()
{
  $('ar_daily_choice').style.display = 'none';
  $('ar_weekly_choice').style.display = 'none';
  $('ar_monthly_choice').style.display = 'block';
  $('ar_yearly_choice').style.display = 'none';

}

function show_yearly()
{
  $('ar_daily_choice').style.display = 'none';
  $('ar_weekly_choice').style.display = 'none';
  $('ar_monthly_choice').style.display = 'none';
  $('ar_yearly_choice').style.display = 'block';

}



function change_recur(recur)
{
  
  if(recur==null)
  {
    recur=getRecur();
  }

  switch(recur)
  {

    case 'daily':
      show_daily();
      break;
    case 'weekly':
      show_weekly();
      break;
    case 'monthly':
      show_monthly();
      break;
    case 'yearly':
      show_yearly();
      break;
  }
  showTab(getCurrentTab());
}

function getDuration()
{
  duration = $F('duration');
  if(duration==null) return -1;
  return duration;
}

function change_duration(value)
{
  if(value==null)
  {
    value=getDuration();
  }
  if(value == -1)
  {
  
    $('enddate').show();
    $('endtime').show();
  }
  else
  {

    $('enddate').hide();
    $('endtime').hide();
  }
  showTab(getCurrentTab());
}
function change_duration_f(value)
{
  if(value==null)
  {
    value=getDuration();
  }
  if(value == -1)
  {
  
    $('date_fin').show();
    $('heure_fin').show();
  }
  else
  {

    $('date_fin').hide();
    $('heure_fin').hide();
  }
  showTab(getCurrentTab());
}

function getRecurrent_o_n()
{
	recurrent_o_n= $F('recurrent_o_n');

  if(recurrent_o_n==null) return '0';
  return recurrent_o_n;
}

function change_recurrent_o_n(value)
{

	if(value==null)
	  {
	    value=getRecurrent_o_n();
	
	  }
	value=getRecurrent_o_n();
  if(value == 1)
  {
    
    $('tabbedPaneAttr_end_choice').show();
  
  }
  else
  {
	  
	    $('tabbedPaneAttr_end_choice').hide();

  }
  showTab(getCurrentTab());
 
}
