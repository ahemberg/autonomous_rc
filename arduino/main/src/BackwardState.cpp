#include "EngineState.h"
#include "BackwardState.h"
#include "MotorController.h"

BackwardState::BackwardState(MotorController mc) : EngineState(mc) {}

EngineState *BackwardState::act(char command) {
    switch(command) {
        case 'w':
            this->motor_controller.stop();
            return this->ss;//*StopState(this->motor_controller);
        default:
            return this;//BackwardState(this->motor_controller);
    }
};

void BackwardState::setState(EngineState *ss) {
	this->ss = ss;
};