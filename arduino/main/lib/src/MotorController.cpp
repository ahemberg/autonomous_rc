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
) : _input_pin_1(input_pin_1), _input_pin_2(input_pin_2), _enable_pin(enable_pin), _speed(0) {  }

void MotorController::set_speed(signed char new_speed){
    byte duty = 2.5 * abs(new_speed);  // [-100,100] -> [0,255]
    if (new_speed<0){
        backward(duty);
    }
    else if (new_speed>0){
        forward(duty);
    }
    else{
        stop();
    }
    _speed = new_speed;
}

signed char MotorController::get_speed(){
    return _speed;
}

void MotorController::stop() {
    disable_engine();
}

void MotorController::break_engine() {
    enable_engine();
    digitalWrite(_input_pin_1, LOW);
    digitalWrite(_input_pin_2, LOW);
}

void MotorController::forward(char duty) {
    enable_engine();
    analogWrite(_input_pin_1, duty);
    analogWrite(_input_pin_2, LOW);
}

void MotorController::backward(char duty) {
    enable_engine();
    analogWrite(_input_pin_1, LOW);
    analogWrite(_input_pin_2, duty);
}

void MotorController::disable_engine() {
    digitalWrite(_enable_pin, LOW);
}

void MotorController::enable_engine() {
    digitalWrite(_enable_pin, HIGH);
}
