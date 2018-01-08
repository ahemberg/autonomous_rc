#include "MotorController.h"
#include <Arduino.h>

// #define AIN1 6  // 10/5
// #define AIN2 5  // 12/7
#define INPUT1_MOTOR 5
#define INPUT2_MOTOR 6
// #define PWMA 3
#define ENABLE_MOTOR 4

// #define STBY 4 // Enable 11/6
#define ENABLE_SERVO 8
#define PWM_SERVO 9
#define SERVO_AIN1 10
#define SERVO_AIN2 3
//#define INPUT1_SERVO 10
//#define INPUT2_SERVO 12

#define MOTOR_SPEED_MAX 150
#define SERVO_SPEED 90

void MotorController::stop() {
    this->disable_engine();
}

void MotorController::break_engine() {
    this->enable_engine();
    digitalWrite(INPUT1_MOTOR, LOW);
    digitalWrite(INPUT2_MOTOR, LOW);
}

void MotorController::forward(int speed) {
    speed = (speed < 0) ? -1*speed : speed; // get absolute value
    this->enable_engine();
    Serial.println("MSMSMSMS");
    Serial.println(MOTOR_SPEED_MAX * speed / 100);    
    analogWrite(INPUT1_MOTOR, MOTOR_SPEED_MAX * speed / 100);
    analogWrite(INPUT2_MOTOR, LOW);
}

void MotorController::backward(int speed) {
    speed = (speed < 0) ? -1*speed : speed; // get absolute value
    this->enable_engine();
    analogWrite(INPUT1_MOTOR, LOW);
    analogWrite(INPUT2_MOTOR, MOTOR_SPEED_MAX * speed / 100);
}

void MotorController::disable_engine() {
    digitalWrite(ENABLE_MOTOR, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(ENABLE_MOTOR, HIGH);
}

void MotorController::enable_servo() {
    digitalWrite(ENABLE_SERVO, HIGH);
}

void MotorController::disable_servo() {
    digitalWrite(ENABLE_SERVO, LOW);
}

void MotorController::servo_left() {
    this->enable_servo();
    digitalWrite(SERVO_AIN1, HIGH);
    digitalWrite(SERVO_AIN2, LOW);
    analogWrite(PWM_SERVO, SERVO_SPEED);
}

void MotorController::servo_right() {
    this->enable_servo();
    digitalWrite(SERVO_AIN1, LOW);
    digitalWrite(SERVO_AIN2, HIGH);
    analogWrite(PWM_SERVO, SERVO_SPEED);
}

void MotorController::servo_stop() {
    digitalWrite(SERVO_AIN1, LOW);
    digitalWrite(SERVO_AIN2, LOW);
    digitalWrite(PWM_SERVO, HIGH);
}

String MotorController::get_state() {
    return "";
}
