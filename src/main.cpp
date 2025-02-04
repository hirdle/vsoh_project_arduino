#include "Arduino.h"
#include "Servo.h"

Servo servo_catch;
Servo servo_rotate_base;
Servo servo_rotate_catch;
Servo servo_folding_base;
Servo servo_folding_catch;

int servo_catch_pin = 9;
int servo_rotate_base_pin = 10;
int servo_rotate_catch_pin = 11;
int servo_folding_base_pin = 12;
int servo_folding_catch_pin = 13;

int catch_default = 0;
int rotate_base_default = 0;
int rotate_catch_default = 0;
int folding_base_default = 0;
int folding_catch_default = 0;

int drive_rotate_default = 90;
int stop_speed = 1500;

Servo motor;
Servo servo_drive;

int motor_pin = 2;
int servo_drive_pin = 3;


void setup() {
  Serial.begin(115200); // Начинаем серийную связь на скорости 115200 бит/с

  motor.attach(motor_pin);
  servo_drive.attach(servo_drive_pin);

  motor.writeMicroseconds(stop_speed);
  servo_drive.writeMicroseconds(drive_rotate_default);

  servo_catch.attach(servo_catch_pin);
  servo_rotate_base.attach(servo_rotate_base_pin);
  servo_rotate_catch.attach(servo_rotate_catch_pin);
  servo_folding_base.attach(servo_folding_base_pin);
  servo_folding_catch.attach(servo_folding_catch_pin);

  servo_catch.write(catch_default);
  servo_rotate_base.write(rotate_base_default);
  servo_rotate_catch.write(rotate_catch_default);
  servo_folding_base.write(folding_base_default);
  servo_folding_catch.write(folding_catch_default);

  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n'); // Читаем строку до символа новой строки
    int angle1, angle2;

    // Разделяем строку на два значения
    int separatorIndex = input.indexOf(' ');
    if (separatorIndex != -1) {
      // Получаем значения углов
      angle1 = input.substring(0, separatorIndex).toInt();
      angle2 = input.substring(separatorIndex + 1).toInt();
      
      // Ограничиваем значения углов от 0 до 180
      angle1 = constrain(angle1, 0, 180);
      angle2 = constrain(angle2, 0, 180);

      // Устанавливаем углы для сервомоторов
      servo_1.write(angle1);
      servo_2.write(angle2);
      
      delay(100);
    }
  }
}
