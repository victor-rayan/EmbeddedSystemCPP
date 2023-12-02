#ifndef MEMORY_FLASH_H
#define MEMORY_FLASH_H

#include <Arduino.h>

extern const int EEPROM_SIZE;
extern const int EEPROM_SSID;
extern const int EEPROM_PASS;
extern const int EEPROM_STATUS;
extern const int EEPROM_BOMBA_STATUS;
extern const int MAX_EEPROM_LEN;

void writeStringEEPROM(int add, String data);
String readStringEEPROM(int add);
void writeFloatEEPROM(int add, float data);
float readFloatEEPROM(int add);
void saveConnectionStatus(bool status);
bool loadConnectionStatus();
void initMemory();
void saveBombaStatus(bool status);
bool loadBombaStatus();

#endif