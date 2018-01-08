#include "ServoController.h"
#include "MotorController.h"
#include <Arduino.h>

#define SERVO_MEAS A0
#define MAX_LEFT 780
#define MAX_RIGHT 580
#define TOLERANCE 10

ServoController::ServoController(MotorController mc) :
	motor_controller(mc) {}

void ServoController::turn_left() {
	if(!overshoot_left()) {
		this->motor_controller.servo_left();
		this->state = 'a';
	}
}

void ServoController::turn_right() {
	if(!overshoot_right()) {
		this->motor_controller.servo_right();
		this->state = 'd';
	}
}

void ServoController::set_goal(int direction) {
	this->goal = (MAX_RIGHT-MAX_LEFT) * (direction - 100) / 200  + MAX_RIGHT; // direction = [-100, 100]
}

void ServoController::reach_goal() {
	int diff = this->goal_diff();

	if(diff < -TOLERANCE) {
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
	this->state = 'x';
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

String ServoController::get_state() {
	String state = "goal: ";
	state += String(this->goal);
	state += ", angle: ";
	state += String(this->angle());
	state += this->state;
	return state;
}
