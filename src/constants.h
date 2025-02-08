#include "Arduino.h"

#include "Servo.h"
#include "Adafruit_VL53L0X.h"

// импорт и объявление датчика расстояния vl53l0x.

#define RIGHT_VL53_ADDRESS 0x52
#define LEFT_VL53_ADDRESS 0x41
#define FORWARD_VL53_ADDRESS 0x42
#define BACKWARD_VL53_ADDRESS 0x93

#define SIDE_RIGHT_VL53_ADDRESS 0x44
#define SIDE_LEFT_VL53_ADDRESS 0x49

#define SHT_VL53_RIGHT 50
#define SHT_VL53_LEFT 53
#define SHT_VL53_FORWARD 51
#define SHT_VL53_BACKWARD 41

#define SHT_VL53_SIDE_RIGHT 49
#define SHT_VL53_SIDE_LEFT 52


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


// минимальное и максимальное расстояние для использования в функции range_limits

int min_distance = 5;
int max_distance = 100;

// базовые значения скоростей

int forward_speed = 1580;
int line_speed = 1575;
int backward_speed = 1345;
int stop_speed = 1495;

unsigned long myTime, last_time; // таймер