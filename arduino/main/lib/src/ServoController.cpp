
#include "ServoController.h"
#include "Arduino.h"

// #define STBY 4 // Enable 11/6
#define MAX_LEFT 780 //THESE VALUES SHOULD BE CALIBRATABLE
#define MAX_RIGHT 580
#define TOLERANCE 10

ServoController::ServoController(
    int pwm_pin, int enable_pin, int in1_pin, int in2_pin, char duty,
    int analog_pin
) {
    this->pwm_pin = pwm_pin;
    this->enable_pin = enable_pin;
    this->in1_pin = in1_pin;
    this->in2_pin = in2_pin;
    this->duty = duty; // TODO: Change this ??
    this->analog_pin = analog_pin;
}

// LOW LEVEL NITTY/GRITTY STUFFS

void ServoController::enable_servo() {
    digitalWrite(this->enable_pin, HIGH);
}

void ServoController::disable_servo() {
    digitalWrite(this->enable_pin, LOW);
}

void ServoController::servo_left() {
    this->enable_servo();
    digitalWrite(this->in1_pin, HIGH);
    digitalWrite(this->in2_pin, LOW);
    analogWrite(this->pwm_pin, this->duty);
}

void ServoController::servo_right() {
    this->enable_servo();
    digitalWrite(this->in1_pin, LOW);
    digitalWrite(this->in2_pin, HIGH);
    analogWrite(this->pwm_pin, this->duty);
}

void ServoController::servo_stop() {
    digitalWrite(this->in1_pin, LOW);
    digitalWrite(this->in2_pin, LOW);
}

int ServoController::angle() {
	return analogRead(this->analog_pin);
}

// PROPER CONTROL STUFFS

void ServoController::turn_left() {
	if(!overshoot_left()) {
		this->servo_left();
	}
}

void ServoController::turn_right() {
	if(!overshoot_right()) {
		this->servo_right();
    }
}

// TODO: Rewrite this function!
void ServoController::set_goal(int direction) {
	this->goal = (MAX_RIGHT-MAX_LEFT) * (float)(direction - 100) / (float)200  + MAX_RIGHT; // direction = [-100, 100]
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
	this->servo_stop();
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
