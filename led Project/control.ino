#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "CANALBOX-B82B-2G";
const char* password = "RybPFZCSDCDE";

String url = "http://patsolidworks.com/wms/led.txt";

int led1 = D1;
int led2 = D2;

void setup() {

  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected");
}

void loop() {

  if(WiFi.status() == WL_CONNECTED){

    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);

    int httpCode = http.GET();

    if(httpCode > 0){

      String payload = http.getString();

      Serial.println(payload);

      int comma = payload.indexOf(',');

      String led1State = payload.substring(0, comma);
      String led2State = payload.substring(comma + 1);

      // LED1
      if(led1State == "1"){
        digitalWrite(led1, HIGH);
      }
      else{
        digitalWrite(led1, LOW);
      }

      // LED2
      if(led2State == "1"){
        digitalWrite(led2, HIGH);
      }
      else{
        digitalWrite(led2, LOW);
      }

    }

    http.end();
  }

  delay(2000);
}