#include "Arduino.h"
#include "UniqueID.h"
#include <WiFi.h>

String getUniqueID() {
  static String uniqueID;

  if (uniqueID.isEmpty()) {
    uint8_t mac[6];
    WiFi.macAddress(mac);

    for (int i = 0; i < 6; i++) {
      uniqueID += String(mac[i], 16);
      if (i < 5) {
        uniqueID += ":";
      }
    }
  }

  return uniqueID;
}