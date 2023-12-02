#include "Arduino.h"
#include "memoryFlash.h"
#include "bomba.h"

const int ledPin = 2;

void setupBomba() {
  pinMode(ledPin, OUTPUT);
  closeBomba();
}

void openBomba(){
  Serial.println("Estado da bomba: LIGADA");
  digitalWrite(ledPin, HIGH);
  saveBombaStatus(true);
}

void closeBomba(){
  Serial.println("Estado da bomba: DESLIGADA");
  digitalWrite(ledPin, LOW);
  saveBombaStatus(false);
}