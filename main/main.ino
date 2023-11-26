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
  
    if (hasConnectedToWiFi && WiFi.status() != WL_CONNECTED ) {
      // WiFi não está conectado, tente reconectar
      setupWiFi();
      verifyMqttConnection();
    }

    if (hasConnectedToWiFi && WiFi.status() == WL_CONNECTED) {
        verifyMqttConnection();
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}


void taskSensorCode(void *pvParameters) {
  while(1) {
    
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
  setupSensor();

  xTaskCreatePinnedToCore(
    taskWiFiCode,
    "TaskWiFi",
    10000,
    NULL,
    1,
    &taskWiFi,
    0
  );

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