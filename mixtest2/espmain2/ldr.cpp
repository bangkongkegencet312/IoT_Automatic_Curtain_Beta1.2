#include "ldr.h"
#include <Arduino.h>  // <- Ini sudah benar dan diperlukan

void setupLDR() {
  pinMode(LDR_PIN, INPUT);
}

int readLDR() {
  int ldrValue = analogRead(LDR_PIN);
  return ldrValue;
}
