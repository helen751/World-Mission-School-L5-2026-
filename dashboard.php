<?php
$conn = new mysqli("localhost", "root", "", "climate_db");

$result = $conn->query("SELECT * FROM climate_data ORDER BY id DESC LIMIT 1");
$row = $result->fetch_assoc();

$temp = $row['temperature'];
$hum = $row['humidity'];
$time = $row['created_at'];

// Status logic
if ($temp < 25) {
    $status = "SAFE";
    $color = "green";
}
else if ($temp < 35) {
    $status = "WARNING";
    $color = "yellow";
}
else {
    $status = "DANGER";
    $color = "red";
}
?>

<!DOCTYPE html>
<html>
<head>
<meta http-equiv="refresh" content="2">
</head>

<body>

<h2>Temperature: <?php echo $temp; ?> °C</h2>

<div style="width:300px; background:#ccc;">
  <div style="width:<?php echo $temp; ?>%; height:20px; background:<?php echo $color; ?>;"></div>
</div>

<h2>Humidity: <?php echo $hum; ?> %</h2>

<div style="width:300px; background:#ccc;">
  <div style="width:<?php echo $hum; ?>%; height:20px; background:blue;"></div>
</div>

<h3>Status: <?php echo $status; ?></h3>
<p>Time: <?php echo $time; ?> (last sync)</p>

</body>
</html>