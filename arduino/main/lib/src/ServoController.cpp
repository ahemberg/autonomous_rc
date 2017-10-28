#include "ServoController.h"
#include "MotorController.h"
#include "Arduino.h"

#define SERVO_MEAS A0
#define MAX_LEFT 700
#define MAX_RIGHT 620
#define TOLERANCE 10

ServoController::ServoController(MotorController mc) : motor_controller(mc) {}

void ServoController::turn_left() {
	if(!overshoot_left()) {
		this->motor_controller.servo_left();
		this->state = 'l';
	}
}

void ServoController::turn_right() {
	if(!overshoot_right()) {
		this->motor_controller.servo_right();
		this->state = 'r';
	}
}

void ServoController::set_goal(char direction) {
	if(direction == 'r') {
		this->goal = MAX_RIGHT;
	}
	else if(direction == 'l') {
		this->goal = MAX_LEFT;
	}
	else if(direction == 's') {
		this->goal = (MAX_LEFT - MAX_RIGHT) / 2;
	}
}

void ServoController::reach_goal() {
	int diff = this->goal_diff();

	if(diff < TOLERANCE) {
		this->turn_right();
	}
	else if(diff > TOLERANCE) {
		this->turn_left();
	}
	else {
		this->stop();
	}
}

int ServoController::goal_diff() {
	return this->goal - this->angle();
}

void ServoController::stop() {
	this->motor_controller.servo_stop();
	this->state = 's';
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

char ServoController::get_state() {
	return this->state;
}
