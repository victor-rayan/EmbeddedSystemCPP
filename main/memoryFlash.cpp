#include "memoryFlash.h"
#include <EEPROM.h>
#include <Arduino.h>

const int EEPROM_SIZE = 512;
const int EEPROM_SSID = 0;
const int EEPROM_PASS = 100;
const int EEPROM_STATUS = 300;
const int EEPROM_TEMP_MAX = 400;
const int EEPROM_TEMP_MIN = 404;
const int EEPROM_HUMIDITY_MAX = 408;
const int EEPROM_HUMIDITY_MIN = 412;
const int MAX_EEPROM_LEN = 50;


void writeStringEEPROM(int add, String data) {
  int _size = data.length();
  if (_size > MAX_EEPROM_LEN)
    return;
  int i;
  for (i = 0; i < _size; i++) {
    EEPROM.write(add + i, data[i]);
  }
  EEPROM.write(add + _size, '\0');
  EEPROM.commit();
}

String readStringEEPROM(int add) {
  int i;
  char data[MAX_EEPROM_LEN + 1];
  int len = 0;
  unsigned char k;
  k = EEPROM.read(add);
  while (k != '\0' && len < MAX_EEPROM_LEN) {
    k = EEPROM.read(add + len);
    data[len] = k;
    len++;
  }
  data[len] = '\0';
  return String(data);
}

void writeFloatEEPROM(int add, float data) {
  EEPROM.put(add, data);
  EEPROM.commit();
}

float readFloatEEPROM(int add) {
  float data;
  EEPROM.get(add, data);
  return data;
}

void saveConnectionStatus(bool status) {
  EEPROM.put(EEPROM_STATUS, status);
  EEPROM.commit();
}

bool loadConnectionStatus() {
  bool status;
  EEPROM.get(EEPROM_STATUS, status);
  return status;
}

void initMemory() {
  EEPROM.begin(EEPROM_SIZE);
}

// void setup() {
//   Serial.begin(115200);
//   EEPROM.begin(EEPROM_SIZE);

//   // Salvar as credenciais
//   writeStringEEPROM(EEPROM_SSID, "your_ssid!123245");
//   writeStringEEPROM(EEPROM_PASS, "your_password@435#@#@#@");

//   // Salvar o status de conexão
//   saveConnectionStatus(true);

//   // Salvar os valores de temperatura e umidade
//   writeFloatEEPROM(EEPROM_TEMP_MAX, 30.5);
//   writeFloatEEPROM(EEPROM_TEMP_MIN, 20.5);
//   writeFloatEEPROM(EEPROM_HUMIDITY_MAX, 70.0);
//   writeFloatEEPROM(EEPROM_HUMIDITY_MIN, 40.0);

//   // Ler as credenciais
//   String ssid = readStringEEPROM(EEPROM_SSID);
//   String password = readStringEEPROM(EEPROM_PASS);

//   // Ler o status de conexão
//   int connectionStatus = loadConnectionStatus();

//   // Ler os valores de temperatura e umidade
//   float tempMax = readFloatEEPROM(EEPROM_TEMP_MAX);
//   float tempMin = readFloatEEPROM(EEPROM_TEMP_MIN);
//   float humidityMax = readFloatEEPROM(EEPROM_HUMIDITY_MAX);
//   float humidityMin = readFloatEEPROM(EEPROM_HUMIDITY_MIN);

//   Serial.print("SSID: ");
//   Serial.println(ssid);
//   Serial.print("Password: ");
//   Serial.println(password);
//   Serial.print("Status de conexão: ");
//   Serial.println(connectionStatus);
//   Serial.print("Temperatura Máxima: ");
//   Serial.println(tempMax);
//   Serial.print("Temperatura Mínima: ");
//   Serial.println(tempMin);
//   Serial.print("Umidade Máxima: ");
//   Serial.println(humidityMax);
//   Serial.print("Umidade Mínima: ");
//   Serial.println(humidityMin);
// }

// void loop() {
//   // Seu código de loop aqui
// }