#include "EngineState.h"
#include "ForwardState.h"
#include "MotorController.h"

ForwardState::ForwardState(MotorController mc) : EngineState(mc) {}

EngineState *ForwardState::act(char command) {
	switch(command) {
		case 's':
		   this->motor_controller.stop();
		   return this->ss;//StopState(this->motor_controller);
		default:
			return this;//ForwardState(this->motor_controller);
	};
};

void ForwardState::setState(EngineState *ss) {
	this->ss = ss;
}