&nbsp;<span  style="color: white; background:red;">&nbsp;{atktext 'show'}: </span>&nbsp;
<select onchange="{$call|escape}">
{foreach from=$options item='option}
  <option value="{$option.value|escape}"{if $option.current} selected="selected"{/if}>{$option.title|escape}</option>
{/foreach}
</select>