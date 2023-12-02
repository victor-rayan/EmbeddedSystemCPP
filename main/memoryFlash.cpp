#include "memoryFlash.h"
#include <EEPROM.h>
#include <Arduino.h>

const int EEPROM_SIZE = 512;
const int EEPROM_SSID = 0;
const int EEPROM_PASS = 100;
const int EEPROM_STATUS = 300;
const int EEPROM_BOMBA_STATUS = 400;
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

void saveBombaStatus(bool status) {
  EEPROM.put(EEPROM_BOMBA_STATUS, status);
  EEPROM.commit();
}

bool loadBombaStatus() {
  bool status;
  EEPROM.get(EEPROM_BOMBA_STATUS, status);
  return status;
}

void initMemory() {
  EEPROM.begin(EEPROM_SIZE);
}
