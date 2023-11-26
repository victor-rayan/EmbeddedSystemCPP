#include "Arduino.h"

const int ledPin = 2;

void setupBomba() {
  pinMode(ledPin, OUTPUT);
}

void openBomba(){
  Serial.println("Estado da bomba: LIGADA");
  digitalWrite(ledPin, HIGH);
}

void closeBomba(){
  Serial.println("Estado da bomba: DESLIGADA");
  digitalWrite(ledPin, LOW);
}