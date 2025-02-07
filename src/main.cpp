#include "Arduino.h"


#include "Adafruit_VL53L0X.h"

// импорт и объявление датчика расстояния vl53l0x.

#define RIGHT_VL53_ADDRESS 0x56
#define LEFT_VL53_ADDRESS 0x41
#define FORWARD_VL53_ADDRESS 0x42
#define BACKWARD_VL53_ADDRESS 0x93

#define SIDE_RIGHT_VL53_ADDRESS 0x44
#define SIDE_LEFT_VL53_ADDRESS 0x40

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


// !!! НЕ ТРОГАТЬ !!! добавляем id vl53l0x
void setID() {
    // all reset
    digitalWrite(SHT_VL53_RIGHT, LOW);    
    digitalWrite(SHT_VL53_LEFT, LOW);
    digitalWrite(SHT_VL53_FORWARD, LOW);
    digitalWrite(SHT_VL53_BACKWARD, LOW);
    digitalWrite(SHT_VL53_SIDE_LEFT, LOW);
    digitalWrite(SHT_VL53_SIDE_RIGHT, LOW);
    delay(10);
    // all unreset
    digitalWrite(SHT_VL53_RIGHT, HIGH);
    digitalWrite(SHT_VL53_LEFT, HIGH);
    digitalWrite(SHT_VL53_FORWARD, HIGH);
    digitalWrite(SHT_VL53_BACKWARD, HIGH);
    digitalWrite(SHT_VL53_SIDE_LEFT, HIGH);
    digitalWrite(SHT_VL53_SIDE_RIGHT, HIGH);
    delay(10);

    // activating LOX1 and resetting LOX2
    digitalWrite(SHT_VL53_RIGHT, HIGH);
    digitalWrite(SHT_VL53_LEFT, LOW);
    digitalWrite(SHT_VL53_FORWARD, LOW);
    digitalWrite(SHT_VL53_BACKWARD, LOW);
    digitalWrite(SHT_VL53_SIDE_LEFT, LOW);
    digitalWrite(SHT_VL53_SIDE_RIGHT, LOW);

    // initing LOX1
    if(!right_VL53.begin(RIGHT_VL53_ADDRESS)) {
        Serial.println(F("Failed to boot 1 VL53L0X"));
        //while(1);
    }
    delay(10);

    // activating LOX2
    digitalWrite(SHT_VL53_LEFT, HIGH);
    delay(10);

    //initing LOX2
    if(!left_VL53.begin(LEFT_VL53_ADDRESS)) {
        Serial.println(F("Failed to boot 2 VL53L0X"));
        //while(1);
    }


    // activating LOX3
    digitalWrite(SHT_VL53_FORWARD, HIGH);
    delay(10);

    //initing LOX3
    if(!forward_VL53.begin(FORWARD_VL53_ADDRESS)) {
        Serial.println(F("Failed to boot 3 VL53L0X"));
        //while(1);
    }

    // activating LOX4
    digitalWrite(SHT_VL53_BACKWARD, HIGH);
    delay(10);

    //initing LOX4
    // if(!backward_VL53.begin(SHT_VL53_BACKWARD)) {
    //     Serial.println(F("Failed to boot 4 VL53L0X"));
    //     //while(1);
    // }

    // activating LOX5
    digitalWrite(SHT_VL53_SIDE_LEFT, HIGH);
    delay(10);

    //initing LOX5
    if(!side_left_VL53.begin(SHT_VL53_SIDE_LEFT)) {
        Serial.println(F("Failed to boot 5 VL53L0X"));
        //while(1);
    }

    // activating LOX6
    digitalWrite(SHT_VL53_SIDE_RIGHT, HIGH);
    delay(10);

    //initing LOX6
    if(!side_right_VL53.begin(SHT_VL53_SIDE_RIGHT)) {
        Serial.println(F("Failed to boot 6 VL53L0X"));
        //while(1);
    }
}

// !!! НЕ ТРОГАТЬ !!! ДЛЯ ТЕСТОВ !!! считывание и вывод информации с датчиков расстояния
void read_three_sensors() {
  
    right_VL53.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
    left_VL53.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
    forward_VL53.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!
    // backward_VL53.rangingTest(&measure4, false); // pass in 'true' to get debug data printout!
    side_right_VL53.rangingTest(&measure5, false); // pass in 'true' to get debug data printout!
    side_left_VL53.rangingTest(&measure6, false); // pass in 'true' to get debug data printout!

    Serial.print(F("Time: "));
    Serial.print(millis());
    Serial.print(F(" => "));

    // print sensor one reading
    Serial.print(F("right: "));
    if(measure1.RangeStatus != 4) {     // if not out of range
        Serial.print(measure1.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.print(F(" "));

    // print sensor two reading
    Serial.print(F("left: "));
    if(measure2.RangeStatus != 4) {
        Serial.print(measure2.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.print(F(" "));

    // print sensor three reading
    Serial.print(F("forward: "));
    if(measure3.RangeStatus != 4) {
        Serial.print(measure3.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.print(F(" "));

    // print sensor three reading
    Serial.print(F("backward: "));
    if(measure4.RangeStatus != 4) {
        Serial.print(measure4.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.print(F(" "));

    // print sensor three reading
    Serial.print(F("side right: "));
    if(measure5.RangeStatus != 4) {
        Serial.print(measure5.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.print(F(" "));

    // print sensor three reading
    Serial.print(F("side left: "));
    if(measure6.RangeStatus != 4) {
        Serial.print(measure6.RangeMilliMeter);
    } else {
        Serial.print(F("Out of range"));
    }

    Serial.println();
    delay(500);
}

// !!! НЕ ТРОГАТЬ !!! инициализация датчиков расстояния vl53l0x
void init_sensors() {

    while (! Serial) { delay(1); }

    pinMode(SHT_VL53_RIGHT, OUTPUT);
    pinMode(SHT_VL53_LEFT, OUTPUT);
    pinMode(SHT_VL53_FORWARD, OUTPUT);
    pinMode(SHT_VL53_SIDE_LEFT, OUTPUT);
    pinMode(SHT_VL53_SIDE_RIGHT, OUTPUT);
    // pinMode(SHT_VL53_BACKWARD, OUTPUT);

    Serial.println(F("Shutdown pins inited..."));

    digitalWrite(SHT_VL53_RIGHT, LOW);
    digitalWrite(SHT_VL53_LEFT, LOW);
    digitalWrite(SHT_VL53_FORWARD, LOW);
    digitalWrite(SHT_VL53_SIDE_LEFT, LOW);
    digitalWrite(SHT_VL53_SIDE_RIGHT, LOW);
    // digitalWrite(SHT_VL53_BACKWARD, LOW);

    Serial.println(F("All in reset mode...(pins are low)"));
    Serial.println(F("Starting..."));

    setID();

    right_VL53.startRangeContinuous();
    left_VL53.startRangeContinuous();
    forward_VL53.startRangeContinuous();
    // backward_VL53.startRangeContinuous();
    side_left_VL53.startRangeContinuous();
    side_right_VL53.startRangeContinuous();

}

void setup() {
  Serial.begin(115200);
  init_sensors();
}


void loop() {
  read_three_sensors();
  delay(20);
}
