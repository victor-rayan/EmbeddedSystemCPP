#include "Arduino.h"
#include "memoryFlash.h"
#include "bomba.h"

const int ledPin = 2;
const int bomba = 27;

void setupBomba() {
  pinMode (bomba, OUTPUT) ;
  pinMode(ledPin, OUTPUT);
  closeBomba();
}

void openBomba(){
  Serial.println("Estado da bomba: LIGADA");
  digitalWrite(ledPin, HIGH);
  digitalWrite(bomba, HIGH);
  saveBombaStatus(true);
}

void closeBomba(){
  Serial.println("Estado da bomba: DESLIGADA");
  digitalWrite(ledPin, LOW);
  digitalWrite(bomba, LOW);
  saveBombaStatus(false);
}