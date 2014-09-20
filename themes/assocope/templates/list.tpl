{if isset($formstart)}{$formstart}{/if}
<table class="bordfineditform" cellspacing="0" cellpadding="5" width="100%">
  {atkmessages}
  {if count($atkmessages)}
    <tr>
      <td align="center" valign="top">
        <br>  
        <div class="atkmessages">
          {foreach from=$atkmessages item=message}
            <div class="atkmessages_{$message.type}">{$message.message}</div>
          {/foreach}
        </div>
        </div>
      </td>
    </tr>        
  {/if}  
  {if (isset($header) && !empty($header))}
  <tr >
    <td valign="top" align="left" class="listentete" ><b>{$header}</b><br></td>
  </tr>
  {/if}
  {if (isset($index) && !empty($index))}
  <tr>
    <td valign="top" align="left" class="listentete">{$index}<br><br></td>
  </tr>
  {/if}
  {if (isset($navbar) && !empty($navbar))}
  <tr>
    <td valign="top" align="left" class="listentete">{$navbar}<br></td>
  </tr>
  {/if}
  <tr class="listcorps">
    <td valign="top" align="left">{$list}</td>
  </tr>
  {if (isset($navbar) && !empty($navbar))}
  <tr>
    <td valign="top" align="left" class="listpied">{$navbar}<br></td>
  </tr>
  {/if}
  {if (isset($footer) && !empty($footer))}
  <tr>
    <td valign="top" align="left" class="listpied">{$footer}<br></td>
  </tr>
  {/if}
</table>
{if isset($formstart)}{$formend}{/if}