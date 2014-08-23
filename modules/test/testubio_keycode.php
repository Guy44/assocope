<?php

       $keyCode = "7820223808842a299d7d7fd187f9bcb260c1b9d3";
       $nameString="meles";
       $url = sprintf("http://www.ubio.org/webservices/service.php?function=namebank_object&namebankID=2483153&keyCode=".$keyCode);
       echo "<br />";
       echo $url;
       $url = sprintf("http://www.ubio.org/webservices/service.php?function=classificationbank_object&hierarchiesID=4091702&synonymsFlag=1&keyCode=".$keyCode);
       echo "<br />";
       echo $url;
       $url = sprintf("http://www.ubio.org/webservices/service.php?function=classificationbank_object&hierarchiesID=4091702&synonymsFlag=1&keyCode=".$keyCode);
       echo "<br />";
       echo $url;
       die();
       
                $xmlStringContents = file_get_contents( $url );
                 $ubio = json_decode( xml2json::transformXmlStringToJson($xmlStringContents), true );
                              if (count($ubio['results']['scientificNames']['value'])) {
                foreach( $ubio['results']['scientificNames']['value'] as $rec ) {
                        $namebankID[] = $rec['namebankID'];
                        if ($first_name_only) {
                                break;
                        }
                }
                }
                
                print_r ($namebankID);
                die();
 
?>