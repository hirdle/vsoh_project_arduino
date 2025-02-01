#include "Arduino.h"
#include "Servo.h"

Servo servo_1;
Servo servo_2;

int servo_pin_1 = 9;
int servo_pin_2 = 10;

void setup() {

  pinMode(servo_pin_1, OUTPUT);
  pinMode(servo_pin_1, OUTPUT);

  servo_1.attach(servo_pin_1);
  servo_2.attach(servo_pin_2);

  servo_1.write(90);
  servo_2.write(90);

}

void loop() {

}