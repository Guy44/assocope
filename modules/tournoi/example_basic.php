<?php
require('class.roundrobin.php');

// Provide opponents in an array format
$teams = array ('Equipe 1', 
                'Equipe 2', 
                'Equipe 3', 
                'Equipe 4', 
                'Equipe 5', 
                'Equipe 6',
				'Equipe 7', 
                'Equipe 8', 
                'Equipe 9', 
                'Equipe 10', 
                'Equipe 11',
                'Equipe 12', 
                'Equipe 13',);

$roundrobin = new roundrobin($teams);

// Generating matches with matchdays
$roundrobin->create_matches();
// The result is a 3-dimension array: matchday->match->opponents
if ($roundrobin->finished) {
   $roundrobin->print_matches();    
}

echo "<br /><br />";


// Generating matches without matchdays
$roundrobin->create_raw_matches();
// The result is a 2-dimension array: match->opponents
if ($roundrobin->finished) {
    $roundrobin->print_matches();    
}

// See 'example_full.php' for the other features
?>