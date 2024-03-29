#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include "Arduino.h"
#include <ESPAsyncWebSrv.h>
#include "UniqueID.h"

extern AsyncWebServer server;
extern SemaphoreHandle_t wifiSemaphore;
void setupWebServer();
bool connectToWiFi(const String& ssid, const String& password);
void notFound(AsyncWebServerRequest *request);
void setupWiFi();

#endif