#include "dht11.h"

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();
}

float readTemperature() {
  float t = dht.readTemperature();
  return isnan(t) ? -999.0 : t;
}

