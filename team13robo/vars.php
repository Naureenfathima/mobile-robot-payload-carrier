<?php

function move($dir){
	$myFile = "direction.txt";
	$fh = fopen($myFile, 'w') or die("can't open file");
	fwrite($fh, $dir);
	fclose($fh);
	
	# launch a Python script to generate the PWM as per the speed value received from the client

	exec("sudo python /var/www/html/team13robo/direction/direction_control.py");

}

?>

