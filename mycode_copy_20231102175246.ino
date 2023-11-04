#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "WiFiConfig.h"


void setup() {
  Serial.begin(115200);
  setupWebServer();

}

void loop() {
  // O loop pode permanecer vazio, pois não há necessidade de fazer nada contínuo aqui
}