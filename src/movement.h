void init_motors() {
    servo.attach(3);
    motor.attach(2);
    motor.writeMicroseconds(stop_speed);
    servo.write(90);
    delay(5000);
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