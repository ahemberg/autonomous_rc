#include "EngineState.h"
#include "ForwardState.h"
#include "StopState.h"
#include "MotorController.h"

ForwardState::ForwardState(MotorController mc, StopState *ss) : EngineState(mc) {
	this->ss = ss
}

EngineState *ForwardState::act(char command) {
	switch(command) {
		case 's':
		   this->motor_controller.stop();
		   return this->ss;//StopState(this->motor_controller);
		default:
			return this//ForwardState(this->motor_controller);
	}
};