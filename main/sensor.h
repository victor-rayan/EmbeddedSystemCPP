#ifndef SENSOR_H
#define SENSOR_H

#include "DHT.h"


extern DHT dht;


void setupSensor();
void verifySensor();
bool reservatorioVazio();

#endif