{if isset($formstart)}{$formstart}{/if}

        <table  border="0" class="recordlist">
  
            <tr class="row1">
              {foreach from=$header item=col}
              {if $col.content != ""}
                <th>
                  {$col.content}
                </th>
                {/if}
              {/foreach}
            </tr>

            {foreach from=$rows item=row}
              <tr class="row1">
               {foreach from=$row.cols item=col}
               {if ($col.type != 'actions' and $col.type != 'mra') }
                <td align="left">

            {$col.content} 
                  
                </td>
                {/if}
              {/foreach}
            </tr>
            {/foreach}

   
      </table>
 
{if isset($formend)}{$formend}{/if}