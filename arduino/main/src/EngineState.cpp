#include "EngineState.h"
#include "MotorController.h"

EngineState::EngineState(MotorController mc) : motor_controller(mc) {}

void EngineState::stop() {
	this->motor_controller.break_engine();
	//this->motor_controller.stop();
}
