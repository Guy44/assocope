<table  class="bordfin" >
  {foreach from=$fields item=field}
    <tr{if $field.rowid != ""} id="{$field.rowid}"{/if}{if !$field.initial_on_tab} style="display: none"{/if} class="{$field.class}">
      {if isset($field.line)}
        <td class="bordfin" colspan="2" valign="top" class="field">{$field.line}</td>
      {else}
        {if $field.label!=="AF_NO_LABEL"}<td class="bordfin" valign="top" class="fieldlabel">{if $field.label!=""}{$field.label}: {/if}</td>{/if}
        <td class="bordfin" valign="top" class="field" {if $field.label==="AF_NO_LABEL"}colspan="2"{/if}>{$field.full}</td>
      {/if}
    </tr>
  {/foreach}
</table>