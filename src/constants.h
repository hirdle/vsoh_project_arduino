#include "Arduino.h"

#include "Servo.h"
#include "Adafruit_VL53L0X.h"

#include <Adafruit_PWMServoDriver.h>

#include <nRF24L01.h>
#include <RF24.h>

// импорт и объявление датчика расстояния vl53l0x.

#define RIGHT_VL53_ADDRESS 0x52
#define LEFT_VL53_ADDRESS 0x41
#define FORWARD_VL53_ADDRESS 0x42
#define BACKWARD_VL53_ADDRESS 0x93

#define SIDE_RIGHT_VL53_ADDRESS 0x44
#define SIDE_LEFT_VL53_ADDRESS 0x49

#define SHT_VL53_RIGHT 37
#define SHT_VL53_LEFT 40
#define SHT_VL53_FORWARD 38
#define SHT_VL53_BACKWARD 41

#define SHT_VL53_SIDE_RIGHT 36
#define SHT_VL53_SIDE_LEFT 39


VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2; 
VL53L0X_RangingMeasurementData_t measure3;
VL53L0X_RangingMeasurementData_t measure4;
VL53L0X_RangingMeasurementData_t measure5;
VL53L0X_RangingMeasurementData_t measure6;

Adafruit_VL53L0X right_VL53 = Adafruit_VL53L0X();
Adafruit_VL53L0X left_VL53 = Adafruit_VL53L0X();

Adafruit_VL53L0X forward_VL53 = Adafruit_VL53L0X();
Adafruit_VL53L0X backward_VL53 = Adafruit_VL53L0X();
Adafruit_VL53L0X side_right_VL53 = Adafruit_VL53L0X();
Adafruit_VL53L0X side_left_VL53 = Adafruit_VL53L0X();

// объявление сервомотора и двигателя.

Servo servo; // рулевое управление
Servo motor; // регулятор скорости


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Настройки для сервоприводов (может потребоваться подстройка)
#define SERVO_MIN 150  // Минимальная длительность импульса (0°)
#define SERVO_MAX 600  // Максимальная длительность импульса (180°)
#define SERVO_COUNT 4  // Количество сервоприводов

// Индексы сервоприводов
int servo_catch_id = 3;
int servo_rotate_base_id = 0;
int servo_folding_base_id = 1;
int servo_folding_catch_id = 2;

int catch_default = 180;
int rotate_base_default = 60;
int folding_base_default = 90;
int folding_catch_default = 0;

int catch_pos = catch_default;
int rotate_base_pos = rotate_base_default;
int folding_base_pos = folding_base_default;
int folding_catch_pos = folding_catch_default;


// минимальное и максимальное расстояние для использования в функции range_limits

int min_distance = 5;
int max_distance = 100;

// базовые значения скоростей

int forward_speed = 1580;
int line_speed = 1575;
int backward_speed = 1345;
int stop_speed = 1495;

unsigned long myTime, last_time; // таймер


RF24 radio(48, 49);

uint8_t pipe;
uint8_t i;

uint32_t lastPing = 0;

/*
CE - 7 (34)
CSN - 8 (35)
SCK - 13 (52)
MOSI - 11 (51)
MISO - 12 (50)
*/
int data[6];
