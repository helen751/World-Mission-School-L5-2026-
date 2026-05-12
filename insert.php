<?php

$conn = new mysqli("localhost", "root", "", "climate_db");

if ($conn->connect_error) {
    die("Connection failed");
}

$temp = $_GET['temperature'];
$hum = $_GET['humidity'];

$sql = "INSERT INTO climate_data (temperature, humidity)
VALUES ('$temp', '$hum')";

$conn->query($sql);

$conn->close();

?>