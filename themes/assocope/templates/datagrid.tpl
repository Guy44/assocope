<table border="0" cellspacing="0" cellpadding="2">
{if $top}
<tr>
  <td align="left" valign="top" colspan="2">
    {$top}
  </td>
</tr>
{/if}
{if $index}
  <tr>
    <td align="left" valign="top">
      {$index}
    </td>
  </tr>
{/if}
{if $paginator || $limit}
  <tr>
    <td align="left" valign="middle">
      {if $paginator}{$paginator} &nbsp; - {/if}
   
      {if $summary}&nbsp; {$summary}{/if}

      {if $limit}&nbsp; -  &nbsp;{$limit}{/if}
    </td>

  </tr>
{/if}
<tr>
  <td align="left" valign="top" colspan="2">
    {$list}
  </td>
</tr>
{if $norecordsfound}
  <tr>
    <td align="left" valign="top">
      <i>{$norecordsfound}</i>
    </td>
  </tr>
{/if}
{if $paginator || $summary}
 <tr>
    <td align="left" valign="middle">
         {if $paginator}{$paginator} &nbsp; - {/if}
   
      {if $summary} &nbsp; {$summary}{/if}

      {if $limit} &nbsp; -  &nbsp;{$limit}{/if}
    </td>

  </tr>
{/if}
{if $bottom}
<tr>
  <td align="left" valign="top" colspan="2">
    {$bottom}
  </td>
</tr>
{/if}
</table>