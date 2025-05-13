#include "dht11.h"
#include <Arduino.h>

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();  // Inisialisasi sensor DHT11
}

float readTemperature() {
  return dht.readTemperature();  // Langsung baca suhu
}
