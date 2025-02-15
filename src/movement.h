void init_motors() {
    servo.attach(3);
    motor.attach(2);
    motor.writeMicroseconds(stop_speed);
    servo.write(90);
    delay(5000);
}

// Функция для установки угла сервопривода
void setServoAngle(uint8_t servoId, int angle) {
  // Ограничиваем угол в диапазоне 0-180
  angle = constrain(angle, 0, 180);
  
  // Конвертируем угол в длительность импульса
  uint16_t pulse = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  
  // Устанавливаем позицию сервопривода
  pwm.setPWM(servoId, 0, pulse);
}


void disableAllMotors() {
  for (int i = 0; i < 4; i++) {
    pwm.setPWM(i, 0, 0);  // Устанавливаем длительность импульса в 0 для каждого мотора
  }
//   Serial.println("All motors disabled.");
}

void init_manipulator() {
    pwm.begin();
    pwm.setPWMFreq(50); 

    setServoAngle(servo_catch_id, catch_default);
    setServoAngle(servo_rotate_base_id, rotate_base_default);
    setServoAngle(servo_folding_base_id, folding_base_default);
    setServoAngle(servo_folding_catch_id, folding_catch_default);
    disableAllMotors();
}

// отъезд назад
void run_backward(int milliseconds) {
    motor.writeMicroseconds(stop_speed);
    delay(100);
    motor.writeMicroseconds(backward_speed);
    delay(milliseconds);
    motor.writeMicroseconds(stop_speed);
    delay(100);
}

void stop() {
    motor.writeMicroseconds(stop_speed);
    delay(100);
}