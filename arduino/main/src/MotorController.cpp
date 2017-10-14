#include "MotorController.h"
#include "Arduino.h"

#define MOTOR 'A'
#define AIN1 2
#define AIN2 7
#define PWMA 3
#define STBY 4

#define SPEED 130

void MotorController::stop() {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, HIGH);
}

void MotorController::forward() {
    this->enable_engine();
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, SPEED);
}

void MotorController::backward() {
    this->enable_engine();
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, SPEED);
}

void MotorController::disable_engine() {
    digitalWrite(STBY, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(STBY, HIGH);
}
