#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "WiFiConfig.h"
#include "memoryFlash.h"
#include "mqtt.h"


void setup() {
  initMemory();
  Serial.begin(115200);
  setupWebServer();
  setupMqtt();

}

void loop() {

  String ssid = readStringEEPROM(EEPROM_SSID);
  String password = readStringEEPROM(EEPROM_PASS);
  int connectionStatus = loadConnectionStatus();
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Password: ");
  Serial.println(password);
  Serial.print("Status de conexão: ");
  Serial.println(connectionStatus);

  bool hasConnectedToWiFi = loadConnectionStatus();
  Serial.println(hasConnectedToWiFi);

  
  if (hasConnectedToWiFi && WiFi.status() != WL_CONNECTED ) {
    // WiFi não está conectado, tente reconectar
    setupWiFi();
    verifyMqttConnection();
  } else if (hasConnectedToWiFi && WiFi.status() == WL_CONNECTED) {
    verifyMqttConnection();
    sendMessageTest();  
    Serial.println("Lendo sensores");
    Serial.println("Enviando dados dos sensores");
  } else{
    Serial.println("fazendo varios nadas");
    
  }

  delay(3000);

}