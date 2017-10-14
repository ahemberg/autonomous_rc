#include "EngineState.h"
#include "MotorController.h"
#include "StopState.h"

EngineState::EngineState(MotorController mc) : motor_controller(mc) {}

EngineState EngineState::stop() {
	this->motor_controller.stop();
	return StopState(this->motor_controller);
}
