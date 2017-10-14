#include "EngineState.h"
#include "BackwardState.h"
#include "StopState.h"
#include "MotorController.h"

BackwardState::BackwardState(MotorController mc) : EngineState(mc) {}

EngineState *BackwardState::act(char command) {
    switch(command) {
        case 'w':
            this->motor_controller.stop();
            return new StopState(this->motor_controller);
        case 's':
            return this;
        default:
            return this;
    }
};