<div id="{$paneName}" class="tabbedPane">
  <table border="0" cellpadding="0" cellspacing="0" align="left" valign="top" width="100%"> 

    <tr>
      <td width="100%" align="left">

  	    <table border="0" cellpadding="0" cellspacing="0" class="tabsTabs">
          <tr class="intertab" width="100%"> 
<td class="intertab" > &nbsp;</td>
                             
            {foreach from=$tabs key=tabName item=tab}
              <td class="{$tabName} tabbedPaneTab {if $tab.selected}activetab{else}passivetab{/if}" valign="middle" align="left" nowrap="nowrap">	
                <a href="javascript:void(0)" onclick="ATK.TabbedPane.showTab('{$paneName}', '{$tabName}'); return false;">{$tab.title}</a>
              </td>          
              <td class="intertab" >&nbsp;</td>
            {/foreach}
<td class="intertab" width="100%" ></td>

          </tr>
        </table>
        <table border="0" cellspacing="0" cellpadding="5" width="100%" class="tabsContent">
          <tr>
            <td>
              {$content}
            </td>
          </tr>
        </table>
      </td>
    </tr>
  </table>
</div>