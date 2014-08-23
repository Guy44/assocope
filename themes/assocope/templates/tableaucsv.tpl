{foreach from=$header item=col}{if $col.content != ""}"{$col.content}",{/if}{/foreach}\n
{foreach from=$rows item=row}{foreach from=$row.cols item=col}{if ($col.type != 'actions' and $col.type != 'mra') }"{$col.content}",{/if}{/foreach}\n
{/foreach}