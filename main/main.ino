#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebSrv.h>
#include "WiFiConfig.h"
#include "memoryFlash.h"
#include "mqtt.h"
#include "bomba.h"
#include "sensor.h"


TaskHandle_t taskWiFi, taskMQTT, taskSensor;

void taskWiFiCode(void *pvParameters) {
  while(1) {
    
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

    Serial.println("na task wifi");
    Serial.println(WiFi.status());

    if (hasConnectedToWiFi && WiFi.status() != WL_CONNECTED && WiFi.status() != WL_NO_SSID_AVAIL) {
      // WiFi não está conectado, tente reconectar
      Serial.println("entrou aqui dentro 12345");
          setupWiFi();
          Serial.println("entrou aqui dentro 12345");
        Serial.println(WiFi.status());

    }else if (hasConnectedToWiFi && WiFi.status() == WL_NO_SSID_AVAIL) {
      // WiFi não está conectado, tente reconectar
          Serial.println("dentro do segudo if na task brekando");
        Serial.println(WiFi.status());

    }

    if (hasConnectedToWiFi && WiFi.status() == WL_CONNECTED) {
        Serial.println("entrou aqui dentro");
        verifyMqttConnection();
    }
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}


void taskSensorCode(void *pvParameters) {
  while(1) {

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
    if (hasConnectedToWiFi && WiFi.status() == WL_CONNECTED) {

      Serial.println("Lendo sensores");
      verifySensor();

    } else{
      Serial.println("conexão wifi não estabelecida");
      
    }
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  
  Serial.begin(115200);
  initMemory();
  setupWebServer();
  setupMqtt();
  setupBomba();
  // setupSensor();
  setupWiFi();

  // xTaskCreatePinnedToCore(
  //   taskWiFiCode,
  //   "TaskWiFi",
  //   10000,
  //   NULL,
  //   1,
  //   &taskWiFi,
  //   0
  // );

  xTaskCreatePinnedToCore(
    taskSensorCode,
    "TaskSensor",
    10000,
    NULL,
    1,
    &taskSensor,
    1
  );
}

void loop() {

}