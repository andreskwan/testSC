<?php
if(isset($_GET['action'])) {
   require("php_serial.class.php");

   $serial = new phpSerial();
   $serial->deviceSet("");
   $serial->confBaudRate(9600);
   $serial->deviceOpen();


if ($_GET['action'] == "a1"){
$serial->sendMessage("0\r");
}else if ($_GET['action'] == "a2"){
$serial->sendMessage("0\r");
}

$serial->deviceClose();
}
?>
