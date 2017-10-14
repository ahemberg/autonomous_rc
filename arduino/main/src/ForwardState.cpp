#include "EngineState.h"
#include "ForwardState.h"
#include "StopState.h"
#include "MotorController.h"

ForwardState::ForwardState(MotorController mc) : EngineState(mc) {}

EngineState *ForwardState::act(char command) {
	switch(command) {
		case 'w':
		   return this;
		case 's':
		   this->motor_controller.stop();
		   return new StopState(this->motor_controller);
		default:
			return this;
	}
};