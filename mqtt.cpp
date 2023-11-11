#include "mqtt.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include "UniqueID.h"

const char* mqtt_server = "test.mosquitto.org";

float TEMP_MAX = 0.0;
float TEMP_MIN = 0.0;
float HUMIDITY_MAX = 0.0;
float HUMIDITY_MIN = 0.0;


WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP32Client2044")) {
      Serial.println("connected");

      String id = getUniqueID();
      String topic = "irrigaja/" + id + "/commands/+";
      client.subscribe(topic.c_str());
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      delay(5000);
    }
  }
}

void setupMqtt() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void verifyMqttConnection() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void deserializeRegistrationConfig(const String& message) {
  StaticJsonDocument<200> jsonDoc;
  DeserializationError error = deserializeJson(jsonDoc, message);

  if (error) {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
  } else {
    TEMP_MAX = jsonDoc["temp_max"];
    TEMP_MIN = jsonDoc["temp_min"];
    HUMIDITY_MAX = jsonDoc["humidity_max"];
    HUMIDITY_MIN = jsonDoc["humidity_min"];

    Serial.print("TEMP_MAX: ");
    Serial.println(TEMP_MAX);
    Serial.print("TEMP_MIN: ");
    Serial.println(TEMP_MIN);
    Serial.print("HUMIDITY_MAX: ");
    Serial.println(HUMIDITY_MAX);
    Serial.print("HUMIDITY_MIN: ");
    Serial.println(HUMIDITY_MIN);

  }
}


void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)message[i]);
      messageTemp += (char)message[i];
    }
    Serial.println();

    String id = getUniqueID();

    if (String(topic) == "irrigaja/" + id + "/commands/waterPump") {
      Serial.print("Changing output to ");
      if (messageTemp == "on") {
        Serial.println("on");
      } else if (messageTemp == "off") {
        Serial.println("off");
      }
    } else if (String(topic) == "irrigaja/" + id + "/commands/registrationConfig") {
      Serial.println(messageTemp);
      deserializeRegistrationConfig(messageTemp);
    }
}

void sendMessageTest(){
      
    String id = getUniqueID();
    Serial.println(" chamou send message");
    float t = 25.5;
    float h = 60.0;

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["wind_speed"] = t;
    jsonDoc["air_humidity"] = t;
    jsonDoc["soil_humidity"] = h;
    jsonDoc["temperature"] = h;

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    String topic = "irrigaja/" + id + "/data";
    client.publish(topic.c_str(), jsonString.c_str());
}
