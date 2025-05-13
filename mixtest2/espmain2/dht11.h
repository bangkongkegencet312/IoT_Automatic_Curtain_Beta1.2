#ifndef DHT11_INPUT_H
#define DHT11_INPUT_H

#include <DHT.h>
#include <Arduino.h>

#define DHTPIN 2         // Pin digital untuk DHT11
#define DHTTYPE DHT11

extern DHT dht;

void setupDHT();
float readTemperature();


#endif
