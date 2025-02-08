#include "constants.h"
#include "sensors.h"
#include "movement.h"

int mode_obj = 0;
int curr_step = 0;

// 1 - увидели и поварачиваем налево
// 2 - переехали и едем вдоль объекта
// 3 - проехали обратно

void setup() {
  Serial.begin(115200);
  init_sensors();
  init_motors();
//   motor.writeMicroseconds(1580);
}


void loop() {
    int distance_forward = forward_VL53.readRange() / 10; // forward
    int distance_right = right_VL53.readRange() / 10; // right
    int distance_left = left_VL53.readRange() / 10; // left
    int distance_side_left = side_left_VL53.readRange() / 10; // side left
    int distance_side_right = side_right_VL53.readRange() / 10; // side right

    if (!mode_obj) {
        servo.write(90);
        motor.writeMicroseconds(forward_speed);        

        if (distance_forward < 100) mode_obj = 1; curr_step = 1;
    } 
    else {
        // stop();
        servo.write(45);
        while (distance_right < 200) {
            motor.writeMicroseconds(forward_speed); 
        }
        delay(500);
        servo.write(110);
        delay(2000);
        // servo.write(90);
        // delay(3000);
        stop();
        delay(1000000000000000000);
    }
    // else {
    //     if (curr_step == 1) {
    //         stop();
    //         while (distance_right < 90) {
    //             servo.write(45);
    //             motor.writeMicroseconds(forward_speed); 
    //         }
    //         delay(150);
    //         stop();
    //         curr_step = 2;
    //     } else if (curr_step == 2) {
    //         stop();
    //         servo.write(135);
    //         motor.writeMicroseconds(forward_speed); 
    //         delay(1500);
    //         stop();
    //     }
    // }
//   read_three_sensors();
//   delay(20);
}
