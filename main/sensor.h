#ifndef SENSOR_H
#define SENSOR_H

#include "DHT.h"


extern DHT dht;
extern bool reservatorio;

void setupSensor();
void verifySensor();
bool reservatorioVazio();

#endif