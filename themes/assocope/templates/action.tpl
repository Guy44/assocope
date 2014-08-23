{$formstart}
<table class="bordfin" cellspacing="0" cellpadding="0" width="100%">
  {if isset($helplink)}<tr><td align="right" class="helplink">{$helplink}</td></tr>{/if}
  
  {atkmessages}
  {if count($atkmessages)}
    <tr>
      <td align="center" valign="top">
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
  <tr>
    <td valign="top" align="left">{$header}</td>
  </tr>
  {/if}
  <tr>
    <td valign="top" align="center">{$content}</td>
  </tr>
  <tr>
    <td align="center" valign="top">
      {foreach from=$buttons item=button}
        &nbsp;{$button}&nbsp;
      {/foreach}</td>
  </tr>
</table>
{$formend}
