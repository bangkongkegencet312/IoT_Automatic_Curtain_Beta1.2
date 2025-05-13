#ifndef DHT11_INPUT_H
#define DHT11_INPUT_H

#include <DHT.h>

// Ganti dengan pin yang kamu gunakan di ESP32
#define DHTPIN 2         
#define DHTTYPE DHT11    

// Membuat objek DHT
extern DHT dht;

void setupDHT();
float readTemperature();


#endif
