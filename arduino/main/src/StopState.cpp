#include "EngineState.h"
#include "StopState.h"
#include "ForwardState.h"
#include "BackwardState.h"
#include "MotorController.h"

StopState::StopState(MotorController mc) : EngineState(mc) {}


EngineState *StopState::act(char command) {
    switch(command) {
        case 'w':
            this->motor_controller.forward();
            return new ForwardState(this->motor_controller);
        case 's':
            this->motor_controller.backward();
            return new BackwardState(this->motor_controller);
        default:
            return this;
    }
};