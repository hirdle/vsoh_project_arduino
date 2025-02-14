#include "constants.h"
#include "sensors.h"
#include "movement.h"
#include "functions.h"
#include "radio.h"

int mode_obj = 0;
int curr_step = 0;

// 1 - увидели и поварачиваем налево
// 2 - переехали и едем вдоль объекта
// 3 - проехали обратно

void setup() {
    // delay(3000);
  Serial.begin(115200);
  init_sensors();
  init_motors();
  init_manipulator();
  start_radio();
//   motor.writeMicroseconds(1580);
}

int back = 0;


void loop() {
    if (radio.available(&pipe)) {
    // 0 - 1 потенциометр
    // 1 - 2 потенциометр
    // 2 - y джостик
    // 3 - x джостик
    // 4 - кнопка

    radio.read(&data, sizeof(data));
    
    int pot1 = data[0];
    int pot2 = data[1];
    int x = data[3] - 523;
    int y = data[2] - 503;
    


    switch (data[5])
    {
    case 0:
      Serial.println("stop");
      stop();
      break;
    case 1:
      // Serial.println("control motors");
      servo.write(map(data[3], 0, 1023, 45, 135));
      if (y > 0) {
        motor.writeMicroseconds(map(y, 0, 523, 1570, 1590));
        back = 0;
      } else if (y < 0) {
        // if (!back) {
        //     motor.writeMicroseconds(stop_speed);
        //     delay(500);
        //     // motor.writeMicroseconds(stop_speed);
        //     // delay(150);
        // }
        // back = 1;
        
        motor.writeMicroseconds(map(y, 0, 523, 1370, 1400));

      } else {
        stop();
      }
      break;
    case 2:
    //   Serial.println("control manipulator");
      
      rotate_base_pos = limits(rotate_base_pos + x / 50, 0, 180);
      setServoAngle(servo_rotate_base_id, rotate_base_pos);
      folding_base_pos = limits(folding_base_pos + y / 20, 0, 180);
      setServoAngle(servo_folding_base_id, folding_base_pos);
      setServoAngle(servo_catch_id, map(pot2, 0, 1023, 0, 180));
      setServoAngle(servo_folding_catch_id, map(pot1, 0, 1023, 180, 0));
      delay(50);
      break;
    case 3:
      Serial.println("automatic");
      break;
    }
    lastPing = millis();

  } else {
    if (millis() - lastPing > 1000) {
        // Serial.println("Связь потеряна!");
        Serial.println("no data");
        stop();
    }
  }
//   delay(50);
    // int distance_forward = forward_VL53.readRange() / 10; // forward
    // int distance_right = right_VL53.readRange() / 10; // right
    // int distance_left = left_VL53.readRange() / 10; // left
    // int distance_side_left = side_left_VL53.readRange() / 10; // side left
    // int distance_side_right = side_right_VL53.readRange() / 10; // side right

    // if (!mode_obj) {
    //     servo.write(90);
    //     motor.writeMicroseconds(forward_speed);        

    //     if (distance_forward < 100) mode_obj = 1; curr_step = 1;
    // } 
    // else {
    //     // stop();
    //     servo.write(45);
    //     while (distance_right < 200) {
    //         motor.writeMicroseconds(forward_speed); 
    //     }
    //     delay(500);
    //     servo.write(110);
    //     delay(2000);
    //     // servo.write(90);
    //     // delay(3000);
    //     stop();
    //     delay(1000000000000000000);
    // }
    // // else {
    // //     if (curr_step == 1) {
    // //         stop();
    // //         while (distance_right < 90) {
    // //             servo.write(45);
    // //             motor.writeMicroseconds(forward_speed); 
    // //         }
    // //         delay(150);
    // //         stop();
    // //         curr_step = 2;
    // //     } else if (curr_step == 2) {
    // //         stop();
    // //         servo.write(135);
    // //         motor.writeMicroseconds(forward_speed); 
    // //         delay(1500);
    // //         stop();
    // //     }
    // // }
}
