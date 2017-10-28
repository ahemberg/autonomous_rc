#include "MotorController.h"
#include "Arduino.h"

#define AIN1 6
#define AIN2 5
#define PWMA 3

#define STBY 4

#define BIN1 8
#define BIN2 10
#define PWMB 9

#define MOTOR_SPEED 120
#define SERVO_SPEED 120

void MotorController::stop() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, HIGH);
}

void MotorController::break_engine() {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, LOW);    
}

void MotorController::forward() {
    this->enable_engine();
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, MOTOR_SPEED);
}

void MotorController::backward() {
    this->enable_engine();
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, MOTOR_SPEED);
}

void MotorController::disable_engine() {
    digitalWrite(STBY, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(STBY, HIGH);
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
