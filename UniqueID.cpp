#include "Arduino.h"
#include "UniqueID.h"
#include <WiFi.h>

String getUniqueID() {
  static String uniqueID; // Variável estática para armazenar o ID único

  // Se o ID único ainda não foi gerado, gere-o
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