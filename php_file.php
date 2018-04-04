<?php
global $Temp;
global $Humidity;
if(isset($_POST['temperature'])){
$Temp=$_POST["temperature"];
}
if(isset($_POST['humidity'])){
$Humidity=$_POST["humidity"];
}
$Write="<p>Temperature  value is : " .$Temp . " Celcius </p>" . "<p>Humidity : " . $Humidity . " % </p>";

file_put_contents('sensor.html',$Write);

    $dbusername = "id4857944_rukman";
    $dbpassword = "password"; 
    $server = "svce-ece-b.000webhostapp.com"; 

    $dbconnect = mysql_pconnect($server, $dbusername, $dbpassword) or die("cannot connect");
    $dbselect = mysql_select_db("id4857944_eceb",$dbconnect) or die("cannot select db");

    $sql = "INSERT INTO id4857944_eceb.sensor_values (temperature, humidity) VALUES (".$Temp.",".$Humidity.")";    

    mysql_query($sql);

 ?>