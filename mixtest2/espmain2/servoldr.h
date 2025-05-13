#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>
#include <math.h>

#define SERVO_PIN 18

extern Servo myServo;

void setupServo();
void kontrolServo(float suhu, int intensitas);

#endif