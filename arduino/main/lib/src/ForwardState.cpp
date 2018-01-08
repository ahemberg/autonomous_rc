#include "EngineState.h"
#include "ForwardState.h"
#include "MotorController.h"

ForwardState::ForwardState(MotorController mc) : EngineState(mc) {}

EngineState *ForwardState::act(int setSpeed) {
	if (setSpeed == 0) {
		this->motor_controller.stop();
		return this->ss;//StopState(this->motor_controller);
	}
	else if (setSpeed > 0) {
		this->motor_controller.forward(setSpeed);
		return this;
	}
	else if (setSpeed < 0) { // todo: change this to move backwards
		this->motor_controller.stop();
		return this->ss;//StopState(this->motor_controller);
	}
	else {
		return this;
	}
}

void ForwardState::setState(EngineState *ss) {
	this->ss = ss;
}
