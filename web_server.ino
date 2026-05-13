#include <ESP8266WiFi.h>

const char* ssid = "CANALBOX-B82B-2G";
const char* password = "RybPFZCSDCDE";

WiFiServer server(80);

// Pins
int ledPin = D1;
int buzzerPin = D2;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // LED control
    if (request.indexOf("/LED_ON") != -1) {
      digitalWrite(ledPin, HIGH);
    }
    if (request.indexOf("/LED_OFF") != -1) {
      digitalWrite(ledPin, LOW);
    }

    // Buzzer control
    if (request.indexOf("/BUZZER_ON") != -1) {
      digitalWrite(buzzerPin, HIGH);
    }
    if (request.indexOf("/BUZZER_OFF") != -1) {
      digitalWrite(buzzerPin, LOW);
    }

    // Send webpage
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println(R"====(
<!DOCTYPE html>
<html>
<head>
  <title>ESP Control Panel</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body {
      font-family: Arial;
      text-align: center;
      background: #f4f4f4;
      margin: 0;
      padding: 20px;
    }
    h1 {
      color: #333;
    }
    .card {
      background: white;
      padding: 20px;
      margin: 15px auto;
      width: 300px;
      border-radius: 10px;
      box-shadow: 0 0 10px rgba(0,0,0,0.1);
    }
    button {
      padding: 12px 20px;
      margin: 10px;
      border: none;
      border-radius: 5px;
      font-size: 16px;
      cursor: pointer;
    }
    .on {
      background-color: #28a745;
      color: white;
    }
    .off {
      background-color: #dc3545;
      color: white;
    }
  </style>
</head>

<body>

<h1>ESP8266 Control Panel</h1>

<div class="card">
  <h3>LED Control</h3>
  <a href="/LED_ON"><button class="on">Turn ON</button></a>
  <a href="/LED_OFF"><button class="off">Turn OFF</button></a>
</div>

<div class="card">
  <h3>Buzzer Control</h3>
  <a href="/BUZZER_ON"><button class="on">Turn ON</button></a>
  <a href="/BUZZER_OFF"><button class="off">Turn OFF</button></a>
</div>

</body>
</html>
)====");

    delay(1);
    client.stop();
  }
}

https://github.com/helen751/World-Mission-School-L5-2026-