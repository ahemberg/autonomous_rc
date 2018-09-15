
#include "ServoController.h"
#include "Arduino.h"

// #define STBY 4 // Enable 11/6
#define MAX_LEFT 780 // THESE VALUES SHOULD BE CALIBRATABLE
#define MAX_RIGHT 580
#define TOLERANCE 10

ServoController::ServoController(int pwm_pin, int enable_pin, int in1_pin,
                                 int in2_pin, char duty, int analog_pin)
    : _pwm_pin(pwm_pin), _enable_pin(enable_pin), _in1_pin(in1_pin),
      _in2_pin(in2_pin), _duty(duty), _analog_pin(analog_pin), _direction(0) {}

int ServoController::get_direction() { return _direction; }

// LOW LEVEL NITTY/GRITTY STUFFS

void ServoController::enable_servo() { digitalWrite(_enable_pin, HIGH); }

void ServoController::disable_servo() { digitalWrite(_enable_pin, LOW); }

void ServoController::servo_left() {
  enable_servo();
  digitalWrite(_in1_pin, HIGH);
  digitalWrite(_in2_pin, LOW);
  analogWrite(_pwm_pin, _duty);
}

void ServoController::servo_right() {
  enable_servo();
  digitalWrite(_in1_pin, LOW);
  digitalWrite(_in2_pin, HIGH);
  analogWrite(_pwm_pin, _duty);
}

void ServoController::servo_stop() {
  digitalWrite(_in1_pin, LOW);
  digitalWrite(_in2_pin, LOW);
}

int ServoController::angle() { return analogRead(_analog_pin); }

// PROPER CONTROL STUFFS

void ServoController::turn_left() {
  if (!overshoot_left()) {
    servo_left();
  }
}

void ServoController::turn_right() {
  if (!overshoot_right()) {
    servo_right();
  }
}

void ServoController::set_goal(int new_direction) {
  _goal = (MAX_RIGHT - MAX_LEFT) * (float)(new_direction - 100) / (float)200 +
          MAX_RIGHT; // direction = [-100, 100]
  _direction = new_direction;
}

void ServoController::reach_goal() {
  int diff = goal_diff();

  if (diff < -TOLERANCE) {
    turn_right();
  } else if (diff > TOLERANCE) {
    turn_left();
  } else {
    stop();
  }
}

int ServoController::goal_diff() { return _goal - angle(); }

void ServoController::stop() { servo_stop(); }

bool ServoController::overshoot_left() { return angle() > MAX_LEFT; }

bool ServoController::overshoot_right() { return angle() < MAX_RIGHT; }

bool ServoController::overshoot() {
  return overshoot_left() || overshoot_right();
}
