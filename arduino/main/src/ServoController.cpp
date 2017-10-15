#include "ServoController.h"
#include "MotorController.h"
#include "Arduino.h"

#define SERVO_MEAS A0
#define MAX_LEFT 700
#define MAX_RIGHT 620

ServoController::ServoController(MotorController mc) : motor_controller(mc) {}

void ServoController::turn_left() {
	if(!overshoot_left()) {
		this->motor_controller.servo_left();
	}
}

void ServoController::turn_right() {
	if(!overshoot_right()) {
		this->motor_controller.servo_right();
	}
}

void ServoController::stop() {
	this->motor_controller.servo_stop();
}

int ServoController::angle() {
	return analogRead(SERVO_MEAS);
}

bool ServoController::overshoot_left() {
  return this->angle() > MAX_LEFT;
}

bool ServoController::overshoot_right() {
  return this->angle() < MAX_RIGHT;
}

bool ServoController::overshoot() {
	return this->overshoot_left() || this->overshoot_right();
}