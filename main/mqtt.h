#ifndef MQTT_H
#define MQTT_H

#include "Arduino.h"
#include <PubSubClient.h>

extern PubSubClient client;
void setupMqtt();
void verifyMqttConnection();
void deserializeRegistrationConfig(const String& message);
void deserializeCommand(const String& message);
void callback(char* topic, byte* message, unsigned int length);
void reconnect();
void sendMessageTest();
void sendMessageInfo(float windSpeed, float airHumidity, float soilHumidity, float temperature, bool status, bool reservatorio);


#endif