/* Controls the engine
 *
 */

 #include "MotorController.h"
 #include "Arduino.h"

 #define INPUT1_MOTOR 5
 #define INPUT2_MOTOR 6
 #define ENABLE_MOTOR 4

MotorController::MotorController(
    int input_pin_1, int input_pin_2, int enable_pin
) {
    this->input_pin_1 = input_pin_1;
    this->input_pin_2 = input_pin_2;
    this->enable_pin = enable_pin;
}

void MotorController::stop() {
    this->disable_engine();
}

void MotorController::break_engine() {
    this->enable_engine();
    digitalWrite(this->input_pin_1, LOW);
    digitalWrite(this->input_pin_2, LOW);
}

void MotorController::forward(char duty) {
    this->enable_engine();
    analogWrite(this->input_pin_1, duty);
    analogWrite(this->input_pin_2, LOW);
}

void MotorController::backward(char duty) {
    this->enable_engine();
    analogWrite(this->input_pin_1, LOW);
    analogWrite(this->input_pin_2, duty);
}

void MotorController::disable_engine() {
    digitalWrite(this->enable_pin, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(this->enable_pin, HIGH);
}
