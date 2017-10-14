#include "EngineState.h"
#include "StopState.h"
#include "ForwardState.h"
#include "BackwardState.h"
#include "MotorController.h"

StopState::StopState(MotorController mc, ForwardState *fs, BackwardState *bs) : EngineState(mc) {
    this->bs = bs;
    this->fs = fs;
}

EngineState *StopState::act(char command) {
    switch(command) {
        case 'w':
            this->motor_controller.forward();
            return this->fs;//ForwardState(this->motor_controller);
        case 's':
            this->motor_controller.backward();
            return this->bs;//BackwardState(this->motor_controller);
        default:
            return this//StopState(this->motor_controller);
    }
};