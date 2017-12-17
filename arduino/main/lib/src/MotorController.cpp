#include "MotorController.h"
#include <Arduino.h>

// #define AIN1 6  // 10/5
// #define AIN2 5  // 12/7
#define INPUT1_MOTOR 5
#define INPUT2_MOTOR 6
// #define PWMA 3
#define ENABLE_MOTOR 4

// #define STBY 4 // Enable 11/6 

// #define BIN1 8
// #define BIN2 10
#define INPUT1_SERVO 10
#define INPUT2_SERVO 12

#define ENABLE_SERVO 8
// #define PWMB 9

#define MOTOR_SPEED 150
#define SERVO_SPEED 90

void MotorController::stop() {
    this->disable_engine();
}

void MotorController::break_engine() {
    this->enable_engine();
    digitalWrite(INPUT1_MOTOR, LOW);
    digitalWrite(INPUT2_MOTOR, LOW);
}

void MotorController::forward() {
    this->enable_engine();
    analogWrite(INPUT1_MOTOR, MOTOR_SPEED);
    analogWrite(INPUT2_MOTOR, LOW);
}

void MotorController::backward() {
    this->enable_engine();
    analogWrite(INPUT1_MOTOR, LOW);
    analogWrite(INPUT2_MOTOR, MOTOR_SPEED);
}

void MotorController::disable_engine() {
    digitalWrite(ENABLE_MOTOR, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(ENABLE_MOTOR, HIGH);
}

void MotorController::servo_left() {
    this->enable_engine();
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, SERVO_SPEED);
}

void MotorController::servo_right() {
    this->enable_engine();
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, SERVO_SPEED);
}

void MotorController::servo_stop() {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    digitalWrite(PWMB, HIGH);
}

String MotorController::get_state() {
    return "";
}
