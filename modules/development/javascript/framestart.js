		function startmain()
{
		
    var ggmain=window.top.document.getElementById("ggmainframe");
			var url1=document.getElementById("url_1").value;
			var str1=document.getElementById("idsearchstring_1").value;
			var str2=url1.replace("XXXXXX", "@@@"+str1);
					ggmain.src=str2;
				}
				
		