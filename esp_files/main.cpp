#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <HX711.h>
#include <Ticker.h>

const char* ssid = "Example_SSID";
const char* password = "Example_Password";
const char* serverAddress = "Example_server_address";
const int serverPort = 80;

HX711 scale;
Ticker weightMeasurementTicker;
const int relayPin = D4;
const int buzzerPin = D5;
const float X = 0.5;
const float Y = 1.5;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(1000);
  scale.begin(D2, D3);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  weightMeasurementTicker.attach(1000, measureWeight);
}

void loop() {}

void measureWeight() {
  float weight = scale.get_units();
  if (weight < X || weight > Y) {
    stopConveyorBelt();
    activateAlarm();
  }
}

void stopConveyorBelt() {
  digitalWrite(relayPin, LOW);
  delay(1000);
}

void activateAlarm() {
  digitalWrite(buzzerPin, HIGH);
  delay(5000);
  digitalWrite(buzzerPin, LOW);
}
