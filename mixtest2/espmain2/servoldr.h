#include "servoldr.h"
#include <Arduino.h>

Servo myServo;

void setupServo() {
  myServo.attach(SERVO_PIN);
}

void kontrolServo(float suhu, int intensitas) {
  if (suhu < 30.0 && intensitas < 50) {
    myServo.write(0);
    Serial.println("Servo ke 0 derajat (suhu < 30 dan intensitas < 50%)");
  } else if (suhu >= 30.0 && intensitas >= 50) {
    myServo.write(90);
    Serial.println("Servo ke 90 derajat (suhu >= 30 dan intensitas >= 50%)");
  } else {
    myServo.write(45);
    Serial.println("Servo ke 45 derajat (kondisi campuran)");
  }
}
